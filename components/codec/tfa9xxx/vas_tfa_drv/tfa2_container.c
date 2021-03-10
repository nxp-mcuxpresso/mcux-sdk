/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "tfa2_dev.h" /* for regwrite */
#include "tfa2_container.h"

static int tfa2_cnt_write_item(struct tfa2_device *tfa, nxpTfaDescPtr_t *dsc);
/* write all  descripters from the dsc list which type is in the items list  */
static int tfa2_cnt_write_items_list(struct tfa2_device *tfa,
                                     nxpTfaDescPtr_t *dsc_list,
                                     int length,
                                     nxpTfaDescriptorType_t *items_list);

/* items that require clock to run */
static nxpTfaDescriptorType_t clockdep_items_list[] = {dscFile, dscCmd, dscCfMem, dscProfile, dsc_listend};

/*
 dsp mem direct write
 */
static int tfa2_cnt_write_dspmem(struct tfa2_device *tfa, nxpTfaDspMem_t *cfmem)
{
    int rc           = 0, i;
    uint16_t address = cfmem->address;

    for (i = 0; i < cfmem->size; i++)
    {
        dev_dbg(&tfa->i2c->dev, "dsp mem (%d): 0x%02x=0x%04x\n", cfmem->type, address, cfmem->words[i]);
        rc = tfa2_i2c_write_cf_mem32(tfa->i2c, address++, (int32_t *)cfmem + offsetof(nxpTfaDspMem_t, words) + i, 1,
                                     (enum tfa2_cf_mem)(cfmem->type));
        if (rc < 0)
            return rc;
    }

    return rc;
}

/*
 * check the container file
 */
int tfa2_load_cnt(void *cnt, int length)
{
    nxpTfaContainer_t *cntbuf = (nxpTfaContainer_t *)cnt;

    if (length > TFA_MAX_CNT_LENGTH)
    {
        pr_err("incorrect length\n");
        return -EINVAL;
    }

    if (HDR(cntbuf->id[0], cntbuf->id[1]) == 0)
    {
        pr_err("header is 0\n");
        return -EINVAL;
    }

    if ((HDR(cntbuf->id[0], cntbuf->id[1])) != paramsHdr)
    {
        pr_err("wrong header type: 0x%02x 0x%02x\n", cntbuf->id[0], cntbuf->id[1]);
        return -EINVAL;
    }

    if (cntbuf->size == 0)
    {
        pr_err("data size is 0\n");
        return -EINVAL;
    }

    /* check CRC */
    if (tfa2_cnt_crc_check_container(cntbuf))
    {
        pr_err("CRC error\n");
        return -EINVAL;
    }

    /* check sub version level */
    if ((cntbuf->subversion[1] != NXPTFA_PM_SUBVERSION) && (cntbuf->subversion[0] != '0'))
    {
        pr_err("container sub-version not supported: %c%c\n", cntbuf->subversion[0], cntbuf->subversion[1]);
        return -EINVAL;
    }

    return 0;
}

/*
 * check CRC for container
 *   CRC is calculated over the bytes following the CRC field
 *
 *   return non zero value on error
 */
int tfa2_cnt_crc_check_container(nxpTfaContainer_t *cont)
{
    uint8_t *base;
    size_t size;
    uint32_t crc;

    base = (uint8_t *)cont + offsetof(nxpTfaContainer_t, CRC) + 4; // ptr to bytes following the CRC field
    size = (size_t)(cont->size - (base - (uint8_t *)cont));        // nr of bytes following the CRC field
    crc  = ~crc32_le(~0u, base, size);

    return crc != cont->CRC;
}

int tfa2_cnt_check_revid(struct tfa2_device *tfa)
{
    nxpTfaPatch_t *patchfile;
    nxpTfaDescPtr_t *patchdsc;

    if (!tfa->cnt)
        return -EINVAL;

    patchdsc = tfa2_cnt_get_dsc(tfa->cnt, dscPatch, tfa->dev_idx);
    if (!patchdsc) /* no patch for this device */
        return -ENXIO;

    patchdsc += 2; /* first the filename dsc and filesize, so skip them */
    patchfile = (nxpTfaPatch_t *)patchdsc;

    return tfa2_check_patch((const uint8_t *)patchfile, patchfile->hdr.size, tfa->rev);
}

/*
 * return 1 if the item is in the list
 *   list must end with dsc_listend
 */
static int hitlist(nxpTfaDescriptorType_t *items, nxpTfaDescriptorType_t item)
{
    nxpTfaDescriptorType_t *list_item = items;

    while (*list_item != dsc_listend && *list_item < dsc_last)
    {
        if (*list_item++ == item)
            return 1;
    }
    return 0;
}

/*****************************************************************************/
/*   cnt getinfo  */
// int tfa2_cnt_get_init_multi_msg(nxpTfaContainer_t *cnt,
//		int dev_idx, int profile, char *mmsg, int *length) {
//
//	return 0;
//}

char *tfa2_cnt_get_string(nxpTfaContainer_t *cnt, nxpTfaDescPtr_t *dsc)
{
    if (dsc->type != dscString)
        return NULL;

    return dsc->offset + (char *)cnt;
}

int tfa2_cnt_get_cmd(nxpTfaContainer_t *cnt, int dev, int profidx, int offset, uint8_t **array, int *length)
{
    int i;
    char *pcnt                = (char *)cnt;
    nxpTfaProfileList_t *prof = tfa2_cnt_get_dev_prof_list(cnt, dev, profidx);
    nxpTfaDescPtr_t *dsc;

    if (!prof)
        return -EINVAL;

    /* process the list until the end of the profile */
    for (i = offset; i < prof->length - 1; i++)
    {
        dsc = &prof->list[i];
        if (dsc->type == dscCmd)
        {
            *length = get_unaligned_le16((uint16_t *)(dsc->offset + pcnt));
            *array  = (uint8_t *)(dsc->offset + 2 + pcnt);
            return i;
        }
    }

    return -EINVAL; /* not found */
}

/*
 * Get the name of the device at a certain index in the container file
 *  return device name
 */
char *tfa2_cnt_device_name(nxpTfaContainer_t *cnt, int dev_idx)
{
    nxpTfaDeviceList_t *dev;

    dev = tfa2_cnt_device(cnt, dev_idx);
    if (dev == NULL)
        return NULL;

    return tfa2_cnt_get_string(cnt, &dev->name);
}
/*
 * Get the name of the profile at certain index for a device in the container file
 *  return profile name
 */
char *tfa2_cnt_profile_name(nxpTfaContainer_t *cnt, int dev_idx, int prof_idx)
{
    nxpTfaProfileList_t *prof = NULL;

    /* the Nth profiles for this device */
    prof = tfa2_cnt_get_dev_prof_list(cnt, dev_idx, prof_idx);

    /* If the index is out of bound */
    if (prof == NULL)
        return NULL;

    return tfa2_cnt_get_string(cnt, &prof->name);
}
/*
 * Get the application name from the container file application field
 * note that the input stringbuffer should be sizeof(application field)+1
 *
 */
int tfa2_cnt_get_app_name(struct tfa2_device *tfa, char *name)
{
    unsigned int i;
    int len = 0;

    for (i = 0; i < sizeof(tfa->cnt->application); i++)
    {
        if (isalnum(tfa->cnt->application[i])) /* copy char if valid */
            name[len++] = tfa->cnt->application[i];
        if (tfa->cnt->application[i] == '\0')
            break;
    }
    name[len++] = '\0';

    return len;
}

/*
 * Dump the contents of the file header
 */
void tfa2_cnt_show_header(nxpTfaHeader_t *hdr)
{
    char _id[2];

    pr_debug("File header\n");

    _id[1] = hdr->id >> 8;
    _id[0] = hdr->id & 0xff;
    pr_debug("\tid:%.2s version:%.2s subversion:%.2s\n", _id, hdr->version, hdr->subversion);
    pr_debug("\tsize:%d CRC:0x%08x \n", hdr->size, hdr->CRC);
    pr_debug("\tcustomer:%.8s application:%.8s type:%.8s\n", hdr->customer, hdr->application,
             hdr->type); /* TODO fix leading zeroes */
}

/*****************************************************************************/
/*   cnt infra lookups  */

/*
 * get the slave for the device if it exists
 */
int tfa2_cnt_get_slave(nxpTfaContainer_t *cnt, int dev_idx)
{
    nxpTfaDeviceList_t *dev;

    /* Make sure the cnt file is loaded */
    if (!cnt)
        return -EINVAL;

    dev = tfa2_cnt_device(cnt, dev_idx);
    if (!dev)
        return -EINVAL;

    return dev->dev;
}

/*
 * return the device list pointer
 */
nxpTfaDeviceList_t *tfa2_cnt_device(nxpTfaContainer_t *cnt, int dev_idx)
{
    return tfa2_cnt_get_dev_list(cnt, dev_idx);
}

/**
 * get the 1st of this dsc type from this devicelist
 */
nxpTfaDescPtr_t *tfa2_cnt_get_dsc(nxpTfaContainer_t *cnt, nxpTfaDescriptorType_t type, int dev_idx)
{
    nxpTfaDeviceList_t *dev = tfa2_cnt_get_dev_list(cnt, dev_idx);
    nxpTfaDescPtr_t *_this;
    int i;

    if (!dev)
    {
        return NULL;
    }
    /* process the list until a the type is encountered */
    for (i = 0; i < dev->length; i++)
    {
        if (dev->list[i].type == (uint32_t)type)
        {
            _this = (nxpTfaDescPtr_t *)(dev->list[i].offset + (uint8_t *)cnt);
            return _this;
        }
    }

    return NULL;
}

/*
 * return device list dsc from index
 */
nxpTfaDeviceList_t *tfa2_cnt_get_dev_list(nxpTfaContainer_t *cont, int dev_idx)
{
    uint8_t *base = (uint8_t *)cont;
    nxpTfaDeviceList_t *this_dev;

    if (cont == NULL)
        return NULL;

    if ((dev_idx < 0) || (dev_idx >= cont->ndev))
        return NULL;

    if (cont->index[dev_idx].type != dscDevice)
        return NULL;

    base += cont->index[dev_idx].offset;
    this_dev = (nxpTfaDeviceList_t *)base;

    if (this_dev->name.type != dscString)
    {
        pr_err("fatal corruption: device[%d] has no name\n", dev_idx);
        return NULL;
    }

    return this_dev;
}

/*
 * get the Nth profile for the Nth device
 */
nxpTfaProfileList_t *tfa2_cnt_get_dev_prof_list(nxpTfaContainer_t *cont, int devIdx, int profIdx)
{
    nxpTfaDeviceList_t *dev;
    int idx, hit;
    uint8_t *base = (uint8_t *)cont;

    dev = tfa2_cnt_get_dev_list(cont, devIdx);
    if (dev)
    {
        for (idx = 0, hit = 0; idx < dev->length; idx++)
        {
            if (dev->list[idx].type == dscProfile)
            {
                if (profIdx == hit++)
                    return (nxpTfaProfileList_t *)(dev->list[idx].offset + base);
            }
        }
    }

    return NULL;
}

/*
 * get the number of profiles for the Nth device of this tfa
 */
int tfa2_dev_get_dev_nprof(struct tfa2_device *tfa) // TODO call tfa2_cnt_get_dev_nprof
{
    nxpTfaDeviceList_t *dev;
    int idx, nprof = 0;

    if (tfa->cnt == NULL)
        return 0;

    if ((tfa->dev_idx < 0) || (tfa->dev_idx >= tfa->cnt->ndev))
        return 0;

    dev = tfa2_cnt_get_dev_list(tfa->cnt, tfa->dev_idx);
    if (dev)
    {
        for (idx = 0; idx < dev->length; idx++)
        {
            if (dev->list[idx].type == dscProfile)
            {
                nprof++;
            }
        }
    }

    return nprof;
}

/*
 * get the number of profiles for the Nth device
 */
int tfa2_cnt_get_dev_nprof(nxpTfaContainer_t *cnt, int dev_idx)
{
    nxpTfaDeviceList_t *dev;
    int idx, nprof = 0;

    if (cnt == NULL)
        return 0;

    if ((dev_idx < 0) || (dev_idx >= cnt->ndev))
        return 0;

    dev = tfa2_cnt_get_dev_list(cnt, dev_idx);
    if (dev)
    {
        for (idx = 0; idx < dev->length; idx++)
        {
            if (dev->list[idx].type == dscProfile)
            {
                nprof++;
            }
        }
    }

    return nprof;
}

/*
 * get the n-th profilename match for this  device
 */
int tfa2_cnt_grep_nth_profile_name(nxpTfaContainer_t *cnt, int dev_idx, int n, const char *string)
{
    int prof, count = 0;

    /* compare string to  the  profile name  in the list of profiles */
    for (prof = 0; prof < cnt->nprof; prof++)
    {
        char *profile = tfa2_cnt_profile_name(cnt, dev_idx, prof);
        if (profile && strstr(profile, string))
        {
            if (n == count++)
                return prof; // tfa2_cnt_get_dev_prof_list(cnt, dev_idx, prof);
        }
    }

    return -EINVAL;
}
/*
 * get the 1st profilename match for this  device
 */
int tfa2_cnt_grep_profile_name(nxpTfaContainer_t *cnt, int dev_idx, const char *string)
{
    return tfa2_cnt_grep_nth_profile_name(cnt, dev_idx, 0, string);
}

/*
 * get the index of the 1st item in the list that depends on clock
 * get the index of the default section marker
 *  if not found return -1
 */
int tfa2_cnt_get_clockdep_idx(
    struct tfa2_device *tfa, nxpTfaDescPtr_t *dsc_list, int length, int *clockdep_idx, int *default_section_idx)
{
    int i;

    if (clockdep_idx == NULL || default_section_idx == NULL || tfa == NULL || dsc_list == NULL)
        return -EINVAL;

    *clockdep_idx        = -1;
    *default_section_idx = -1;

    /* find the matches in the list */
    for (i = 0; i < length; i++)
    {
        if (*clockdep_idx == -1 && hitlist(clockdep_items_list, (nxpTfaDescriptorType_t)(dsc_list[i].type)))
            *clockdep_idx = i;
        if (dsc_list[i].type == dscDefault)
        {
            *default_section_idx = i;
            break; /* clock dep items cannot be in the default section */
        }
    }

    return 0;
}
///*
// * return the index of the default section marker of this profile
// *  if not found return -1
// */
// int tfa2_cnt_get_default_idx(struct tfa2_device *tfa, nxpTfaProfileList_t *prof) {
//	int i;
//
//	/* find a match in the list */
//	for(i=0;i < prof->length  ;i++) {
//		if ( prof->list[i].type == dscDefault )
//			return i;
//	}
//
//	return -1 ;
//}

/*
 * write the register based on the input address, value and mask
 *  only the part that is masked will be updated
 */
static int tfa2_dev_cnt_write_register(struct tfa2_device *tfa, nxpTfaRegpatch_t *reg)
{
    int rc;
    uint16_t value, newvalue;

    if (tfa->verbose)
        dev_dbg(&tfa->i2c->dev, "register: 0x%02x=0x%04x (msk=0x%04x)\n", reg->address, reg->value, reg->mask);

    rc = tfa2_i2c_read_reg(tfa->i2c, reg->address); /* will report error */
    if (rc < 0)
        return rc;
    value = (uint16_t)rc;

    value &= ~reg->mask;
    newvalue = reg->value & reg->mask;

    value |= newvalue;

    rc = tfa2_i2c_write_reg(tfa->i2c, reg->address, value);

    return rc;
}

/* write reg and bitfield items in the devicelist
 * until a clock dependent item is encountered
 *  this is called during called start init
 */
int tfa2_cnt_write_regs_dev(struct tfa2_device *tfa)
{
    int i, rc = 0;
    nxpTfaDeviceList_t *dev = tfa2_cnt_device(tfa->cnt, tfa->dev_idx);
    /* write these items until break */
    nxpTfaDescriptorType_t items_list[] = {dscBitfield, dscRegister, dsc_listend};

    if (!dev)
    {
        return -EINVAL;
    }

    /* process the list until a clock dependent  is encountered */
    for (i = 0; i < dev->length; i++)
    {
        if (hitlist(clockdep_items_list, (nxpTfaDescriptorType_t)(dev->list[i].type)))
            break;
        if (hitlist(items_list, (nxpTfaDescriptorType_t)(dev->list[i].type)))
        {
            rc = tfa2_cnt_write_item(tfa, &dev->list[i]);
            if (rc < 0)
                break;
        }
    }

    return rc;
}

/* write reg and bitfield items in the profilelist the target */
int tfa2_cnt_write_regs_profile(struct tfa2_device *tfa, int prof_idx)
{
    int i, rc = 0;
    char *profile                       = NULL;
    nxpTfaProfileList_t *prof           = tfa2_cnt_get_dev_prof_list(tfa->cnt, tfa->dev_idx, prof_idx);
    nxpTfaDescriptorType_t items_list[] = {dscBitfield, dscRegister, dsc_listend};

    if (!prof)
    {
        return -EINVAL;
    }

    profile = tfa2_cnt_get_string(tfa->cnt, &prof->name);
    if (profile == NULL)
    {
        dev_dbg(&tfa->i2c->dev, "Invalid profile index given: %d\n", prof_idx);
        return -EINVAL;
    }
    else
    {
        dev_dbg(&tfa->i2c->dev, "----- profile: %s (%d) -----\n", profile, prof_idx);
    }

    /* process the list until the end of the profile or the default section */
    for (i = 0; i < prof->length - 1; i++)
    {
        /* We only want to write the values before the default section when we switch profile */
        if (prof->list[i].type == dscDefault)
            break;
        if (hitlist(items_list, (nxpTfaDescriptorType_t)(prof->list[i].type)))
        {
            rc = tfa2_cnt_write_item(tfa, &prof->list[i]);
            if (rc < 0)
                break;
        }
    }
    return rc;
}

int tfa2_cnt_write_patch(struct tfa2_device *tfa, nxpTfaPatch_t *patchfile)
{
    int rc, size;

    if (tfa->verbose)
        tfa2_cnt_show_header(&patchfile->hdr);

    size = patchfile->hdr.size - sizeof(nxpTfaPatch_t); // size is total length
    rc   = tfa2_check_patch((const uint8_t *)patchfile, patchfile->hdr.size,
                          tfa->rev); // TODO fix for single patch header type
    if (rc < 0)
        return rc;

    rc = tfa2_dev_dsp_patch(tfa, size, (const unsigned char *)patchfile->data);

    return rc;
}
/*
 * write the item from the dsc
 * ignore if not a content item
 */
static int tfa2_cnt_write_item(struct tfa2_device *tfa, nxpTfaDescPtr_t *dsc)
{
    int rc = 0;
    nxpTfaRegpatch_t *reg;
    nxpTfaBitfield_t *bitf;
    nxpTfaFileDsc_t *file;
    void *cnt_offset;

    cnt_offset = dsc->offset + (uint8_t *)tfa->cnt; /* payload offset in cnt */

    switch (dsc->type)
    {
        case dscBitfield:
            bitf = (nxpTfaBitfield_t *)(cnt_offset);
            rc   = tfa2_i2c_write_bf_volatile(tfa->i2c, bitf->field, bitf->value);
            break;
        case dscFile:
            rc = tfa2_cnt_write_file(tfa, (nxpTfaFileDsc_t *)(cnt_offset));
            break;
        case dscCmd:
            rc = tfa2_cnt_write_msg_dsc(tfa, dsc);
            break;
        case dscCfMem:
            rc = tfa2_cnt_write_dspmem(tfa, (nxpTfaDspMem_t *)cnt_offset);
            break;
        case dscDefault: /* default listpoint marker */
        case dscDevice:  /*  device list */
        case dscProfile: /*  profile list */
        case dscGroup:
        case dscMarker:
        case dscTfaHal:
        case dscLiveDataString:
        case dscLiveData:
        case dscInfoText:
        case dscInfoFile:
        case dscFilter:
            break;      /* ignore */
        case dscString: // ascii: zero terminated string
            dev_dbg(&tfa->i2c->dev, ";string: %s\n", tfa2_cnt_get_string(tfa->cnt, dsc));
            break;
        case dscRegister: // register patch
            reg = (nxpTfaRegpatch_t *)(cnt_offset);
            rc  = tfa2_dev_cnt_write_register(tfa, reg);
            // dev_dbg(&tfa->i2c->dev, "$0x%2x=0x%02x,0x%02x\n", reg->address, reg->mask, reg->value);
            break;
            //	case dscFile:       // filename + file contents
        case dscPatch:
            file = (nxpTfaFileDsc_t *)(cnt_offset);                         /* get the payload from the file dsc */
            rc   = tfa2_cnt_write_patch(tfa, (nxpTfaPatch_t *)&file->data); /* data is the patch header */
            break;
        default:
            dev_err(&tfa->i2c->dev, "unsupported list item:%d\n", dsc->type);
            rc = -EINVAL;
    }

    return rc;
}

/*
 * all container originated RPC msgs goes through this
 *
 *  the cmd_id is monitored here to insert 		{"SetAlgoParams", 0x48100},
  {"SetAlgoParamsWithoutReset", 0x48102},
  {"SetMBDrc", 0x48107},
  {"SetMBDrcWithoutReset", 0x48108},
 */
int tfa2_cnt_write_msg(struct tfa2_device *tfa, int wlength, char *wbuf)
{
    int rc            = 0;
    uint8_t *cmd_id24 = (uint8_t *)wbuf;
    int cmd_id        = cmd_id24[0] << 16 | cmd_id24[1] << 8 | cmd_id24[2];
    uint8_t *cmd_lsb  = &cmd_id24[2];
    int coldstarting  = tfa2_dev_is_fw_cold(tfa); /* set if FW is cold */
    char rbuf[3];
    uint32_t rpc_status;

    /*
     * select the cmd_id variant based on the init state
     */
    switch (cmd_id & 0x7fff)
    {
        default:
            break;
        case 0x100:                          /* SetAlgoParams 0x48100*/
        case 0x102:                          /* SetAlgoParamsWithoutReset 0x48102*/
            *cmd_lsb = coldstarting ? 0 : 2; /* if cold cmd_id = coldstart variant */
            break;
        case 0x107:                          /* SetMBDrc 0x48107*/
        case 0x108:                          /* SetMBDrcWithoutReset 0x48108*/
            *cmd_lsb = coldstarting ? 7 : 8; /* if cold cmd_id = coldstart variant */
            break;
    }

    if (tfa->verbose)
    {
        int cmd_id = cmd_id24[0] << 16 | cmd_id24[1] << 8 | cmd_id24[2];
        dev_dbg(&tfa->i2c->dev, "Writing cmd=0x%06x,size=%d\n", cmd_id, wlength);
    }

    rc = tfa2_dsp_execute(tfa, wbuf, wlength, rbuf, 3);
    if (rc < 0)
        return rc;
    rpc_status = (rbuf[0] << 16) | (rbuf[1] << 8) | rbuf[2];
    if (rpc_status != 0)
    {
        dev_err(&tfa->i2c->dev, "%s: rpc_status = 0x%x\n", __func__, rpc_status);
        return -1;
    }

    return rc;
}

/*  write  all patchfiles in the devicelist to the target */
int tfa2_cnt_write_patches(struct tfa2_device *tfa)
{
    int rc                  = 0;
    nxpTfaDeviceList_t *dev = tfa2_cnt_get_dev_list(tfa->cnt, tfa->dev_idx);
    int i;

    if (!dev)
    {
        return -EINVAL;
    }

    /* process the list until a patch  is encountered and load it */
    for (i = 0; i < dev->length; i++)
    {
        if (dev->list[i].type == dscPatch)
        {
            rc = tfa2_cnt_write_item(tfa, &dev->list[i]);
        }
    }

    return rc;
}

int tfa2_cnt_write_msg_dsc(struct tfa2_device *tfa, nxpTfaDescPtr_t *dsc)
{
    char *cnt = (char *)tfa->cnt;
    int size;

    size = get_unaligned_le16((uint16_t *)(dsc->offset + cnt));
    return tfa2_cnt_write_msg(tfa, size, dsc->offset + 2 + cnt);
}

/*
 * write all  descripters from the dsc list which type is in the items list
 */
static int tfa2_cnt_write_items_list(struct tfa2_device *tfa,
                                     nxpTfaDescPtr_t *dsc_list,
                                     int length,
                                     nxpTfaDescriptorType_t *items_list)
{
    int i, rc = 0;

    /* process the list and write all files  */
    for (i = 0; i < length; i++)
    {
        if (hitlist(items_list, (nxpTfaDescriptorType_t)(dsc_list[i].type)))
        {
            rc = tfa2_cnt_write_item(tfa, &dsc_list[i]);
            if (rc < 0)
                break;
        }
    }

    return rc;
}

/* write all param files  and cfmem from the devicelist to the target */
int tfa2_cnt_write_files(struct tfa2_device *tfa)
{
    nxpTfaDeviceList_t *dev;
    nxpTfaDescriptorType_t items_list[] = {dscFile, dscCmd, dscCfMem, dsc_listend};

    dev = tfa2_cnt_device(tfa->cnt, tfa->dev_idx);
    if (!dev)
        return -EINVAL;

    /* process the list and write all files  */
    return tfa2_cnt_write_items_list(tfa, dev->list, dev->length, items_list);
}

/* write all param files in the profile list  to the target */
int tfa2_cnt_write_files_profile(struct tfa2_device *tfa, int prof_idx, int vstep_idx)
{
    nxpTfaProfileList_t *prof           = tfa2_cnt_get_dev_prof_list(tfa->cnt, tfa->dev_idx, prof_idx);
    nxpTfaDescriptorType_t items_list[] = {dscFile, dscCmd, dscCfMem, dscPatch, dsc_listend};

    if (!prof)
    {
        return -EINVAL;
    }

    /* process the list and write all files  */
    return tfa2_cnt_write_items_list(tfa, prof->list, prof->length - 1, items_list);
}

/*
 * write a parameter file to the device
 *   only generic rpc msg and speaker/lsmodel files are supported
 */
int tfa2_cnt_write_file(struct tfa2_device *tfa, nxpTfaFileDsc_t *file)
{
    int rc              = 0;
    nxpTfaHeader_t *hdr = (nxpTfaHeader_t *)file->data;
    nxpTfaHeaderType_t type;
    int size;

    if (tfa->verbose)
    {
        tfa2_cnt_show_header(hdr);
    }

    type = (nxpTfaHeaderType_t)hdr->id;

    switch (type)
    {
        case msgHdr: /* generic DSP message */
        case equalizerHdr:
            size = hdr->size - sizeof(tfa_msg_file_t);
            rc   = tfa2_cnt_write_msg(tfa, size, (char *)((tfa_msg_file_t *)hdr)->data);
            break;
        case speakerHdr:
            /* Remove header and xml_id */
            size = hdr->size - sizeof(struct nxpTfaSpkHeader) - sizeof(struct nxpTfaFWVer);
            rc   = tfa2_cnt_write_msg(tfa, size,
                                    (char *)(((nxpTfaSpeakerFile_t *)hdr)->data + (sizeof(struct nxpTfaFWVer))));
            break;
        case infoHdr:
            /* Ignore */
            break;
        case patchHdr:
            rc = tfa2_cnt_write_patch(tfa, (nxpTfaPatch_t *)&file->data);
            break;

        default:
            dev_err(&tfa->i2c->dev, "Header is of unknown type: %c%c (0x%x)\n", type & 0xff, (type >> 8) & 0xff, type);
            return -EINVAL;
    }

    return rc;
}

/*
 *  process all items in the profilelist
 *   NOTE an error return during processing will leave the device muted
 *
 */
int tfa2_cnt_write_profile(struct tfa2_device *tfa, int prof_idx, int vstep_idx)
{
    int i, rc = 0;
    int previous_prof_idx              = tfa2_dev_get_swprofile(tfa);
    nxpTfaProfileList_t *prof          = tfa2_cnt_get_dev_prof_list(tfa->cnt, tfa->dev_idx, prof_idx);
    nxpTfaProfileList_t *previous_prof = tfa2_cnt_get_dev_prof_list(tfa->cnt, tfa->dev_idx, previous_prof_idx);
    int in_group;
    int prof_clockdep_idx, prof_default_section_idx;
    int previous_clockdep_idx, previous_default_section_idx;

    if (!prof || !previous_prof)
    {
        dev_err(&tfa->i2c->dev, "Error trying to get the (previous) swprofile \n");
        return -EINVAL;
    }

    /* grouping enabled ? */
    in_group = prof->group == previous_prof->group && prof->group != 0;

    /* get indexes of relevant points in the profiles:
     *    1st clock dependent item and default settings  marker  */
    rc = tfa2_cnt_get_clockdep_idx(tfa, previous_prof->list, previous_prof->length, &previous_clockdep_idx,
                                   &previous_default_section_idx);
    if (rc < 0)
        return rc;
    /* new profile */
    rc = tfa2_cnt_get_clockdep_idx(tfa, prof->list, prof->length, &prof_clockdep_idx, &prof_default_section_idx);
    if (rc < 0)
        return rc;

    dev_dbg(&tfa->i2c->dev, "profile switch device:%s, %s > %s (%s pwdn)\n",
            tfa2_cnt_device_name(tfa->cnt, tfa->dev_idx),
            tfa2_cnt_profile_name(tfa->cnt, tfa->dev_idx, previous_prof_idx),
            tfa2_cnt_profile_name(tfa->cnt, tfa->dev_idx, prof_idx), in_group ? "no" : "with");

    /* We only  power cycle when the profiles are not in the same group */
    if (!in_group)
    {
        /* When we switch profile we first power down thePLL */
        rc = tfa2_dev_set_state(tfa, (enum tfa_state)(TFA_STATE_POWERDOWN | TFA_STATE_MUTE)); /* with  mute */
        if (rc < 0)
            return rc;
    }

    if (tfa->verbose)
        tfa2_show_current_state(tfa);

    /* restore defaults/ non-clock dependent  settings from the active (previous) profile */
    for (i = previous_default_section_idx; i < previous_prof->length - 1; i++)
    {
        rc = tfa2_cnt_write_item(tfa, &previous_prof->list[i]);
        if (rc < 0)
            return rc;
    }
    /* apply all non-clock dependent  settings from new profile */
    for (i = 0; i < prof_clockdep_idx; i++)
    {
        rc = tfa2_cnt_write_item(tfa, &prof->list[i]);
        if (rc < 0)
            return rc;
    }

    /* We only power cycle when the profiles are not in the same group */
    if (!in_group)
    {
        /* Leave powerdown state */
        rc = tfa2_dev_set_state(tfa, TFA_STATE_CLOCK); /* clock will be there on return */
        if (rc < 0)
            return rc;
        /*  hook for workaround */
        tfa2_init_fix_initcf(tfa);
    }

    /* write everything until end or the default section */
    for (i = prof_clockdep_idx; i < prof_default_section_idx; i++)
    {
        rc = tfa2_cnt_write_item(tfa, &prof->list[i]);
        if (rc < 0)
            return rc;
    }

    return rc;
}
/*
 * direct write of all items in the profile
 */
int tfa2_cnt_write_transient_profile(struct tfa2_device *tfa, int prof_idx)
{
    int i, rc = 0;
    nxpTfaProfileList_t *prof = tfa2_cnt_get_dev_prof_list(tfa->cnt, tfa->dev_idx, prof_idx);
    int prof_clockdep_idx, prof_default_section_idx;

    if (!prof)
    {
        dev_err(&tfa->i2c->dev, "Error trying to get the (previous) swprofile \n");
        return -EINVAL;
    }
    /* get indexes of relevant points in the profiles:
     *    1st clock dependent item and default settings  marker  */
    rc = tfa2_cnt_get_clockdep_idx(tfa, prof->list, prof->length, &prof_clockdep_idx, &prof_default_section_idx);
    if (rc < 0)
        return rc;

    /* write everything until end or the default section */
    for (i = 0; i < prof_default_section_idx; i++)
    {
        rc = tfa2_cnt_write_item(tfa, &prof->list[i]);
        if (rc < 0)
            break;
    }

    return rc;
}
/*
 * lookup slave and return device index
 */
int tfa2_cnt_get_idx(struct tfa2_device *tfa)
{
    nxpTfaDeviceList_t *dev = NULL;
    int i;

    for (i = 0; i < tfa->cnt->ndev; i++)
    {
        dev = tfa2_cnt_device(tfa->cnt, i);
        if (!dev)
            return -1;
        if (dev->dev == tfa->slave_address)
            break;
    }
    if (i == tfa->cnt->ndev)
        return -1;

    return i;
}
