/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "tfa2_dev.h"
#include "tfa2_haptic.h"
#include "tfa2_container.h"
#include "tfa_haptic_fw_defs.h"
#include <stddef.h>

static int check_haptic_version = 1;

/* enable or disable version check */
void tfa2_haptic_set_version_check(int check)
{
    check_haptic_version = check;
}

/* print effect object settings to string */
static int tfa2_haptic_current_effect(struct haptic_data *data, char *str, int len)
{
    if (!str)
        return -EINVAL;

    return snprintf(str, len, "index:%d,\tamplitude:%d,\tduration:%d,\tfrequency:%d", data->index, data->amplitude,
                    data->duration, data->frequency ? data->frequency : -1);
}

/* get pointer to object in cache */
static struct haptic_tone_object *get_obj_cache_ptr(struct haptic_data *data, int idx)
{
    struct haptic_tone_object *obj;

    if (idx >= (FW_XMEM_NR_OBJECTS1 + FW_XMEM_NR_OBJECTS2))
        obj = NULL;
    else if (idx >= FW_XMEM_NR_OBJECTS1)
        obj = (struct haptic_tone_object *)&data->object_table2_cache[idx - FW_XMEM_NR_OBJECTS1][0];
    else
        obj = (struct haptic_tone_object *)&data->object_table1_cache[idx][0];

    return obj;
}

/* get xmem address of object */
static int get_obj_xmem_addr(int idx)
{
    int addr;

    if (idx >= (FW_XMEM_NR_OBJECTS1 + FW_XMEM_NR_OBJECTS2))
        addr = -1;
    else if (idx >= FW_XMEM_NR_OBJECTS1)
        addr = FW_XMEM_GENOBJECTS2 + (idx - FW_XMEM_NR_OBJECTS1) * FW_XMEM_OBJECTSIZE;
    else
        addr = FW_XMEM_GENOBJECTS1 + idx * FW_XMEM_OBJECTSIZE;

    return addr;
}

/* get index for CMDOBJSEL0/1 of object */
static int get_cmdobjsel_index(int idx)
{
    int cmdobjsel_idx;

    if (idx >= (FW_XMEM_NR_OBJECTS1 + FW_XMEM_NR_OBJECTS2))
        cmdobjsel_idx = -1;
    else if (idx >= FW_XMEM_NR_OBJECTS1)
        cmdobjsel_idx = idx - FW_XMEM_NR_OBJECTS1 + FW_CMDOBJSEL_TABLE2_OFFFSET;
    else
        cmdobjsel_idx = idx;

    return cmdobjsel_idx;
}

/******************************************************************************
 * haptic front-end functions
 */
/* start resonance */
int tfa2_haptic_start(struct tfa2_device *tfa, struct haptic_data *data, int index)
{
    int rc = -EINVAL; //, virtual_object = index - FW_HB_SEQ_OBJ;

    dev_dbg(&tfa->i2c->dev, "starting obj[%d] of total %d ms\n", index + 1, tfa2_haptic_get_duration(tfa, index));

    if (index < FW_HB_SEQ_OBJ)
    {
        rc = tfa2_haptic_start_object(tfa->i2c, data, index);
    }
    else if (index < FW_HB_SEQ_OBJ + data->seq_max)
    {
        rc = tfa2_hap_sequencer_object(tfa, index + 1);
    }

    return rc;
}
int tfa2_haptic_start_object(struct i2c_client *client, struct haptic_data *data, int index)
{
    int rc;
    char str[256];
    struct haptic_tone_object *obj;
    int address;
    int cmdobjsel_index;
    int object_changed = 0;
    int cmdobjsel      = FW_XMEM_CMDOBJSEL0;
    int level;
#ifdef MEASURE_START_TIMING
    ktime_t start_time, stop_time;
    u64 delta_time;

    start_time = ktime_get_boottime();
#endif

    obj             = get_obj_cache_ptr(data, index);
    address         = get_obj_xmem_addr(index);
    cmdobjsel_index = get_cmdobjsel_index(index);
    if (!obj || (address < 0) || (cmdobjsel_index < 0))
    {
        dev_err(&client->dev, "invalid object idx=%d, addr=%d, cmdobjsel_idx=%d\n", index, address, cmdobjsel_index);
        return -EINVAL;
    }

    tfa2_haptic_current_effect(data, str, sizeof(str));
    dev_dbg(&client->dev, "started (%d) %s\n", index + 1, str);

    /* Make sure the DSP is running! */

    /* level for all types */
    level = (data->amplitude * 0x7fffff + 50) / 100; /* Q1.23, percentage of max */
    object_changed += (obj->level != level);
    obj->level = level;

    if ((obj->type == object_tone) || (obj->type == object_silence))
    {
        int samples;

        /* duration is in sample count : 48k is 48 samples/ms */
        samples = data->duration * 48; /* use DSP timer */
        object_changed += (obj->durationCntMax != samples);
        obj->durationCntMax = samples;

        if (data->frequency)
        {
            int freq = data->frequency << 11; /* Q13.11 */
            object_changed += (obj->freq != freq);
            obj->freq = freq;
        }
    }

    if (object_changed > 0)
    {
        /* write parameters */
        rc = tfa2_i2c_write_cf_mem32(client, address, (int32_t *)obj, FW_XMEM_OBJECTSIZE, TFA2_CF_MEM_XMEM);
        if (rc < 0)
            return rc;
    }

    /* to start write cmdObjSel = index */
    rc = tfa2_i2c_write_cf_mem32(client, cmdobjsel, (int32_t *)&cmdobjsel_index, 1, TFA2_CF_MEM_XMEM);

#ifdef MEASURE_START_TIMING
    stop_time  = ktime_get_boottime();
    delta_time = ktime_to_ns(ktime_sub(stop_time, start_time));
    do_div(delta_time, 1000);
    dev_dbg(&client->dev, "tfa_haptic_start duration = %lld us (%lld )\n", delta_time, delta_time + 900);
#endif
    return rc;
}

/* stop resonance */
int tfa2_haptic_stop(struct tfa2_device *tfa, struct haptic_data *data, int index)
{
    int stop_obj  = FW_HB_STOP_OBJ; /* first table */
    int cmdobjsel = FW_XMEM_CMDOBJSEL0;

    return tfa2_i2c_write_cf_mem32(tfa->i2c, cmdobjsel, (int32_t *)&stop_obj, 1, TFA2_CF_MEM_XMEM);
}

/* duration in msecs of current object */
int tfa2_haptic_get_duration(struct tfa2_device *tfa, int index)
{
    int total_duration;
    struct haptic_data *data = &tfa->hap_data;
    /* error if too high */
    if (index > FW_HB_SEQ_OBJ + data->seq_max)
        return -EINVAL;

    if (index < FW_HB_SEQ_OBJ)
    {
        /* normal object */
        struct haptic_tone_object *obj = get_obj_cache_ptr(data, index);
        /* duration is in sample count : 48k is 48 samples/ms */
        int duration = obj->durationCntMax / 48;

        if (obj->type != object_wave)
        {
            /* take into account that duration might get adjusted in tfa2_haptic_start_object() */
            duration = data->duration ? data->duration : duration;
            if (obj->boostBrakeOn)
                duration += obj->boostLength / 48;
        }
        total_duration = duration + data->delay_attack; /* add object hold time */
    }
    else
    { /* sequencer */
        int rc;
        struct tfa2_sequence seq;
        rc = tfa2_hap_cnt_get_sequencer(tfa->cnt, tfa->dev_idx, index - FW_HB_SEQ_OBJ, &seq);
        if (rc < 0)
        {
            pr_err("No sequencer\n");
            return -EINVAL;
        }
        total_duration = tfa2_hap_get_sequencer_duration(tfa, &seq);
    }
    return total_duration;
}

/* update the duration in msecs for the time spend in boost break */
int tfa2_haptic_update_duration(struct haptic_data *data, int duration)
{
    struct haptic_tone_object *obj = get_obj_cache_ptr(data, data->index);
    int boost_length               = 0;

    data->duration = duration;

    if ((obj->type == object_tone) && (obj->boostBrakeOn == 1))
        boost_length = (obj->boostLength / 48);

    if (boost_length >= duration)
    {
        pr_err("%s: boost break length (%d) is longer then duration (%d)", __func__, boost_length, duration);
        return -EINVAL;
    }

    /* substract boost brake length from user provided duration */
    data->duration -= boost_length;

    return 0;
}

enum tfa_haptic_object_type tfa2_haptic_object_type(struct haptic_data *data, int index)
{
    struct haptic_tone_object *obj = get_obj_cache_ptr(data, index);
    return obj->type ? object_tone : object_wave;
}

/*
 * extract the effect settings from the negative input value
 *   byte[2/3] is the frequency of object (if non-0)
 *   byte[1] is index of object
 *   byte[0] is the amplitude % from level
 *  return 0 if to be ignored for playback
 */
int tfa2_haptic_parse_value(struct haptic_data *data, int value)
{
    uint32_t xvalue;
    int level;

    if (value < 0)
    {
        xvalue      = value * -1;
        data->index = ((xvalue >> 8) & 0xff) - 1; /* get byte[1] */
        level       = xvalue & 0xff;              /* get byte[0] */
        if (level < 4)
            data->amplitude = level * 33;
        else
            data->amplitude = level;
        data->frequency = xvalue >> 16; /* freq */
    }

    return (value > 0) ? 1 : 0;
}

int tfa2_haptic_read_r0(struct i2c_client *client, int *p_value)
{
    return tfa2_i2c_read_cf_mem32(client, FW_XMEM_R0, p_value, 1, TFA2_CF_MEM_XMEM);
}

int tfa2_haptic_read_f0(struct i2c_client *client, int *p_value)
{
    return tfa2_i2c_read_cf_mem32(client, FW_XMEM_F0, p_value, 1, TFA2_CF_MEM_XMEM);
}

int tfa2_haptic_read_sampcnt0(struct i2c_client *client, int *p_value)
{
    return tfa2_i2c_read_cf_mem32(client, FW_XMEM_SAMPCNT0, p_value, 1, TFA2_CF_MEM_XMEM);
}
int tfa2_haptic_read_recalc_selector(struct i2c_client *client, int *p_value)
{
    return tfa2_i2c_read_cf_mem32(client, FW_XMEM_RECALCSEL, p_value, 1, TFA2_CF_MEM_XMEM);
}
int tfa2_haptic_write_recalc_selector(struct i2c_client *client, int value)
{
    return tfa2_i2c_write_cf_mem32(client, FW_XMEM_RECALCSEL, (int32_t *)&value, 1, TFA2_CF_MEM_XMEM);
}

int tfa2_haptic_disable_f0_trc(struct i2c_client *client, int disable)
{
    int disable_f0_trc = (disable != 0);
    return tfa2_i2c_write_cf_mem32(client, FW_XMEM_DISF0TRC, (int32_t *)&disable_f0_trc, 1, TFA2_CF_MEM_XMEM);
}

int tfa2_haptic_obj0_set(struct i2c_client *client, int objnr)
{
    return tfa2_i2c_write_cf_mem32(client, FW_XMEM_CMDOBJSEL0, (int32_t *)&objnr, 1, TFA2_CF_MEM_XMEM);
}

int tfa2_haptic_obj0_wait_finish(struct i2c_client *client)
{
    int rc, loop = 50, ready = 0, sampcnt0;

    do
    {
        rc = tfa2_haptic_read_sampcnt0(client, &sampcnt0);
        if (rc < 0)
            return rc;
        ready = sampcnt0 <= 0;
        if (ready == 1)
            break;
        msleep_interruptible(50); /* wait to avoid busload */ // TODO decrease time?...
    } while (loop--);

    if (sampcnt0 > 0)
        return -ETIMEDOUT;

    return 0;
}
int tfa2_haptic_calibrate_wait(struct i2c_client *client)
{
    int loop = 50, ready = 0, sampcnt0;
    int f0;

    do
    {
        tfa2_haptic_read_sampcnt0(client, &sampcnt0);
        tfa2_haptic_read_f0(client, &f0);
        ready = (sampcnt0 <= 0) && (f0 != 0);
        if (ready == 1)
            break;
        msleep_interruptible(50); /* wait to avoid busload */ // TODO decrease time?...
    } while (loop--);

    if (sampcnt0 > 0)
        return -ETIMEDOUT;

    return 0;
}

int tfa2_haptic_recalculate_wait(struct tfa2_device *tfa, int object)
{
    int loop, ready = 0, sampcnt0 = 0;
    int recalc_selector;
    int manstate = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);

    loop = manstate == 6 ? 250 : 50; /* extend loop if in initcf */

    if (object >= 0)
    {
        int ms, duration;

        /* get this object duration from xmem */
        tfa2_i2c_read_cf_mem32(
            tfa->i2c,
            FW_XMEM_GENOBJECTS1 + object * FW_XMEM_OBJECTSIZE + offsetof(struct haptic_tone_object, durationCntMax) / 4,
            &duration, 1, TFA2_CF_MEM_XMEM);
        /* duration is in sample count : 48k is 48 samples/ms */
        ms = duration / 48;
        if (ms > 0 && ms < 1000000)
        {
            ms += manstate == 6 ? ms : 0; /* extend time if in initcf */
            msleep_interruptible(ms);     /* wait for obj to finish */
        }
        else
            return -EINVAL;
    }

    do
    {
        if (object >= 0)
        {
            tfa2_haptic_read_sampcnt0(tfa->i2c, &sampcnt0);
        }
        tfa2_haptic_read_recalc_selector(tfa->i2c, &recalc_selector);
        ready = (sampcnt0 <= 0) && (recalc_selector < 0);
        if (ready == 1)
            break;
    } while (loop--);

    if (sampcnt0 > 0)
        return -ETIMEDOUT;

    return 0;
}

/* handy wrappers */
static int get_hap_profile(struct tfa2_device *tfa, char *string)
{
    // TODO limit to use .hap names only
    return tfa2_cnt_grep_profile_name(tfa->cnt, tfa->dev_idx, string);
}

int tfa2_hap_patch_version(struct tfa2_device *tfa, char *string)
{
    int rc, fw_version;

    /* this is called after patch load, keep the dsp in reset */
    rc = tfa2_i2c_read_cf_mem32_dsp_reset(tfa->i2c, FW_XMEM_VERSION, &fw_version, 1, TFA2_CF_MEM_XMEM);
    dev_dbg(&tfa->i2c->dev, "%s patch version %d.%d.%d\n", string, (fw_version >> 16) & 0xff, (fw_version >> 8) & 0xff,
            fw_version & 0xff);

    if (check_haptic_version && ((fw_version & FW_VERSION_MASK) != FW_VERSION))
    {
        dev_err(&tfa->i2c->dev, "%s: unsupported firmware version 0x%x, expected 0x%x\n", __func__, fw_version,
                FW_VERSION);
        return -EINVAL;
    }

    return rc;
}

/*
 * execute recalculation, assume data is loaded
 */
static int tfa2_hap_recalc(struct tfa2_device *tfa, int object)
{
    int rc, f0, f0mtp, fresout;

    /* assume that the recalculation is been loaded */

    /* if F0  == 0 assume not calibrated */
    f0mtp = tfa2_dev_mtp_get(tfa, TFA_MTP_F0); /* raw */
    f0    = f0mtp / 2 + 80;                    /* start at 80 */
    dev_dbg(&tfa->i2c->dev, "%s:F0 MTP:%d, F0:%d\n", __func__, f0mtp, f0);

    /* allowed range is between 80 and 336 Hz */
    if ((80 < f0) && (f0 < 336))
    {
        int recalc_obj = -1;
        if (tfa->hap_data.recalc_play_object)
        {
            /* read recalc object id from data patch */
            tfa2_i2c_read_cf_mem32(tfa->i2c, FW_XMEM_CMDOBJSEL0, &recalc_obj, 1, TFA2_CF_MEM_XMEM);
        }
        else
            recalc_obj = object;

        tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 0);
        /* Go to power on state */
        rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
        if (rc < 0)
            return rc;

        msleep_interruptible(1);
        dev_dbg(&tfa->i2c->dev, "%s: manstate:%d\n", __func__, tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate));

        if (recalc_obj >= 0)
        {
            /* Loading startup Object ID */
            tfa2_haptic_obj0_set(tfa->i2c, recalc_obj);
            dev_dbg(&tfa->i2c->dev, "recalculation startup object id: %d\n", recalc_obj);
        }

        /* trigger recalculation */
        tfa2_haptic_write_recalc_selector(tfa->i2c, 1);

        /* wait for recalculation to finish */
        rc = tfa2_haptic_recalculate_wait(tfa, recalc_obj);
        if (rc < 0)
        {
            dev_err(&tfa->i2c->dev, "Error, recalculation did not finish\n");
            return rc;
        }

        rc = tfa2_haptic_read_f0(tfa->i2c, &fresout);
        if (rc < 0)
        {
            dev_err(&tfa->i2c->dev, "Error reading f0\n");
            return rc;
        }
        dev_info(&tfa->i2c->dev, "recalculation %s\n", (fresout == 0) ? "NOT done!" : "done");

        /* stop DSP */
        tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 1);
    }
    else
    {
        dev_dbg(&tfa->i2c->dev, "Warning: f0:%d not in 80/336 Hz range, cannot recalculate\n", f0);
        /* no error return, in case of 1st time calibration it would fail */
    }

    return 0;
}

int tfa2_hap_load_data(struct tfa2_device *tfa)
{
    int rc, hbprofile;
    char profile_name[32];

    strcpy(profile_name, (tfa->need_hb_config & TFA_HB_ROLE_MASK) == tfa_hb_lra ? "lra" : "ls");
    strcat(profile_name, "_data.hap");

    hbprofile = get_hap_profile(tfa, profile_name); /* get "*_data.hap" */
    if (hbprofile < 0)
    {
        dev_err(&tfa->i2c->dev, "No [%s] profile found\n", profile_name);
        return -EINVAL;
    }
    rc = tfa2_cnt_write_files_profile(tfa, hbprofile, 0); /* write patch from profile*/
    if (rc < 0)
        return rc;

    /* print and check version */
    return tfa2_hap_patch_version(tfa, "data");
}

int tfa2_hap_load_recalc(struct tfa2_device *tfa)
{
    int rc, hbprofile;

    hbprofile = get_hap_profile(tfa, "lra_recalculation.hap");
    rc        = tfa2_cnt_write_files_profile(tfa, hbprofile, 0); /* write recalc patch*/
    if (rc < 0)
        return rc;

    /* print and check version */
    rc = tfa2_hap_patch_version(tfa, "recalculation");

    return rc;
}

void tfa2_haptic_obj_get(struct haptic_data *data, int idx)
{
    struct haptic_tone_object *obj = get_obj_cache_ptr(data, idx);

    if (obj == NULL)
        return;

    /* default tone effect */
    data->index     = idx;
    data->amplitude = (100 * obj->level + 0x3fffff) / 0x7fffff;
    data->duration  = obj->durationCntMax / 48;
    data->frequency = obj->freq >> 11; /* Q13.11 */
}

void tfa2_haptic_obj_get_duration(struct haptic_data *data, int idx)
{
    struct haptic_tone_object *obj = get_obj_cache_ptr(data, idx);

    if (obj == NULL)
        return;
    data->duration = obj->durationCntMax / 48;
    if (obj->boostBrakeOn)
        data->duration += obj->boostLength / 48;
}

/* settings for obj[0] */
static void tfa2_haptic_obj_get_defaults(struct haptic_data *data)
{
    tfa2_haptic_obj_get(data, 0);
}

/*
 * front-end recalculation function
 *   return if recalculation has been done already
 *   load data patch and recalculate
 */
int tfa2_hap_recalculate(struct tfa2_device *tfa, int object)
{
    int rc;

    tfa2_dev_update_config_init(tfa);

    /* silent return if not relevant */
    if (tfa->need_hb_config != tfa_hb_lra)
        return 0;

    if (tfa->need_hw_init)
    {
        rc = tfa2_dev_start_hw(tfa, 0);
        if (rc < 0)
            return rc;
    }

    rc = tfa2_hap_load_data(tfa);
    if (rc < 0)
        return rc;

    rc = tfa2_hap_load_recalc(tfa);
    if (rc < 0)
        return rc;

    rc = tfa2_dev_set_state(tfa, TFA_STATE_OPERATING);
    if (rc < 0)
        return rc;
    /* make sure we are in 9 */
    rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_manstate, 9, 50);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error, waiting for operating state in recalculation\n");
        return rc;
    }

    rc = tfa2_hap_recalc(tfa, object);
    if (rc < 0)
        return rc;

    return rc;
}

/*
 * load and activate hapticboost
 *   if entered cold a full fw boot + lra recalculation  will be done
 */
int tfa2_dev_start_hapticboost(struct tfa2_device *tfa)
{
    int rc;
    char profile_name[32];

    strcpy(profile_name, (tfa->need_hb_config & TFA_HB_ROLE_MASK) == tfa_hb_lra ? "lra" : "ls");
    dev_dbg(&tfa->i2c->dev, "%s: cold starting as %s\n", __FUNCTION__, profile_name);

    /* cold start, assume RST=1 */
    //	tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 1); //TODO optimize RST ,fix patches

    /* load data patch first */
    rc = tfa2_hap_load_data(tfa); /* will cache object table */
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error loading data patch\n");
        return rc;
    }

    if ((tfa->need_hb_config & TFA_HB_ROLE_MASK) == tfa_hb_lra)
    {
        rc = tfa2_hap_load_recalc(tfa);
        if (rc < 0)
            return rc;
        /* run recalculation */
        rc = tfa2_hap_recalc(tfa, -1); /* driver mode, no object */
    }

    /* no error check on xmem reads, the current rc will be returned */
    /* cache object tables */
    tfa2_i2c_read_cf_mem32(tfa->i2c, FW_XMEM_GENOBJECTS1, (int *)tfa->hap_data.object_table1_cache,
                           FW_XMEM_OBJECTSIZE * FW_XMEM_NR_OBJECTS1, TFA2_CF_MEM_XMEM);
    tfa2_i2c_read_cf_mem32(tfa->i2c, FW_XMEM_GENOBJECTS2, (int *)tfa->hap_data.object_table2_cache,
                           FW_XMEM_OBJECTSIZE * FW_XMEM_NR_OBJECTS2, TFA2_CF_MEM_XMEM);
    /* cache delay_attack  */
    tfa2_i2c_read_cf_mem32(tfa->i2c, FW_XMEM_DELAY_ATTACK_SMP, &tfa->hap_data.delay_attack, 1, TFA2_CF_MEM_XMEM);
    tfa->hap_data.delay_attack /= 48; /* make it milliseconds */

    /* get max nr of sequencer virtual objects */
    tfa->hap_data.seq_max = tfa2_hap_cnt_sequencer_count(tfa->cnt, tfa->dev_idx);

    /* get the defaults */
    tfa2_haptic_obj_get_defaults(&tfa->hap_data);

    return rc; /* recalc rc in case of lra */
}

int tfa2_hap_calibrate(struct tfa2_device *tfa)
{
    int f0, r0;
    uint16_t mtp_f0;
    int rc, ret, current_profile;
    int range[4];

    /* Update  init state */
    tfa2_dev_update_config_init(tfa);

    if (!tfa->need_hb_config)
    {
        dev_err(&tfa->i2c->dev, "HB calibration not done, no config found in container\n");
        return -EINVAL;
    }

    mtp_f0 = tfa2_dev_mtp_get(tfa, TFA_MTP_F0);

    dev_dbg(&tfa->i2c->dev, "Current MTP F0:%d\n", mtp_f0);

    /* if not 0, wipe it */
    if (mtp_f0)
    {
        /* Go to the powerup state to allow MTP writing*/
        rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
        if (rc < 0)
            return rc;

        /* Clear f0 in MTP */
        rc = tfa2_dev_mtp_set(tfa, TFA_MTP_F0, 0);
        if (rc < 0)
        {
            dev_err(&tfa->i2c->dev, "Error clearing F0 in MTP\n");
            return rc;
        }
        /* turn off again, so we are always enter with pll off */
        rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
        if (rc < 0)
            return rc;
    }

    current_profile = tfa2_dev_get_swprofile(tfa);
    if (current_profile < 0)
    {
        /* no current profile, take the 1st profile */
        current_profile = 0;
    }

    /* cold run of calibration profile */
    rc = tfa2_calibrate_profile_start(tfa);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error, calibration profile start\n");
        return rc;
    }

    /* Trigger calibration */
    tfa2_haptic_obj0_set(tfa->i2c, FW_HB_CAL_OBJ);

    msleep_interruptible(1000 + tfa->hap_data.delay_attack); // TODO determine optimal delay

    /* wait for calibration to finish */
    rc = tfa2_haptic_obj0_wait_finish(tfa->i2c);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error, calibration did not finish\n");
        goto reload_profile;
    }

    rc = tfa2_haptic_read_f0(tfa->i2c, &f0);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error reading f0\n");
        goto reload_profile;
    }
    dev_dbg(&tfa->i2c->dev, "F0 = %d.%03d Hz (0x%x)\n", TFA2_HAPTIC_FP_INT(f0, FW_XMEM_F0_SHIFT),
            TFA2_HAPTIC_FP_FRAC(f0, FW_XMEM_F0_SHIFT), f0);

    rc = tfa2_haptic_read_r0(tfa->i2c, &r0);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error reading r0\n");
        goto reload_profile;
    }
    dev_dbg(&tfa->i2c->dev, "R0 = %d.%03d ohm (0x%x)\n", TFA2_HAPTIC_FP_INT(r0, FW_XMEM_R0_SHIFT),
            TFA2_HAPTIC_FP_FRAC(r0, FW_XMEM_R0_SHIFT), r0);

    /* Check F0/R0 ranges */
    rc = tfa2_i2c_read_cf_mem32(tfa->i2c, FW_XMEM_F0_R0_RANGES, range, 4, TFA2_CF_MEM_XMEM);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error reading F0/R0 ranges\n");
        goto reload_profile;
    }

    rc = 0;
    if ((f0 < range[3]) || (f0 > range[2]))
    {
        dev_err(&tfa->i2c->dev, "F0 out of range: 0x%06x < 0x%06x < 0x%06x\n", range[3], f0, range[2]);
        rc = -ERANGE;
    }
    if ((r0 < range[1]) || (r0 > range[0]))
    {
        dev_err(&tfa->i2c->dev, "R0 out of range: 0x%06x < 0x%06x < 0x%06x\n", range[1], r0, range[0]);
        rc = -ERANGE;
    }
    if (rc != 0)
    {
        dev_err(&tfa->i2c->dev, "range check failed, result not written\n");
        goto reload_profile;
    }

    /* 16 bit f0 value to store in F0  MTP location
     *  Encoding:
     *              MTPValue = round ((  f0 -  80 Hz ) * 2 )
     *              f0 [in Hz]  = MTPValue / 2 + 80 Hz
     * */

    /* convert F0 to Hz */
    f0     = TFA2_HAPTIC_FP_INT(f0, FW_XMEM_F0_SHIFT) + (TFA2_HAPTIC_FP_FRAC(f0, FW_XMEM_F0_SHIFT) > 499 ? 1 : 0);
    mtp_f0 = (f0 - 80) * 2;
    dev_dbg(&tfa->i2c->dev, "MTPF0 = %d (0x%x)\n", mtp_f0 / 2 + 80, mtp_f0);

    // TODO check F0 for non-zero; always make no sense if the FW uses MTP

    /* Store f0 in MTP */
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_F0, mtp_f0);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "Error writing F0 to MTP\n");
        goto reload_profile;
    }

    /* TODO if calibrate always: Store f0 in shadow register */
    //	tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CUSTINFO, mtp_f0);

reload_profile:
    /* force a cold start to do recalculation */
    ret = tfa2_dev_force_cold(tfa);
    if (ret < 0)
    {
        dev_err(&tfa->i2c->dev, "%s: force cold failed\n", __func__);
        return ret;
    }

    /* re-load current profile  */
    ret = tfa2_dev_start(tfa, current_profile, 0);
    if (ret < 0)
    {
        dev_err(&tfa->i2c->dev, "%s: Cannot reload profile %d\n", __func__, current_profile);
        return ret;
    }

    return rc;
}

/*
 * free the sequencer
 *
 */
void tfa2_hap_sequencer_destroy(struct tfa2_sequence *seq)
{
    kfree(seq->object);
    kfree(seq->duration);
    kfree(seq->level);
    kfree(seq->freq);
}
/*
 * run the sequencer
 *
 */
int tfa2_hap_sequencer(struct tfa2_device *tfa, struct tfa2_sequence *seq)
{
    int rc, i, idx, this_duration, total_duration = 0;
    int save_duration, save_amplitude, save_frequency;

    if (seq == 0 || seq->object == 0)
        return -EINVAL;

    /* save default object */
    save_duration  = tfa->hap_data.duration;
    save_amplitude = tfa->hap_data.amplitude;
    save_frequency = tfa->hap_data.frequency;

    for (i = 0; i < seq->length; i++)
    {
        idx = seq->object[i] - 1; /* lists starts counting at 1 */
        /* get current settings */
        tfa2_haptic_obj_get(&tfa->hap_data, idx);
        /* adjust according to table */
        if (seq->duration && seq->duration[i])
            tfa->hap_data.duration = seq->duration[i];
        /* adjust according to table */
        if (seq->level && seq->level[i])
            tfa->hap_data.amplitude = seq->level[i];
        /* adjust according to table */
        if (seq->freq && seq->freq[i])
            tfa->hap_data.frequency = seq->freq[i];

        rc = tfa2_haptic_start_object(tfa->i2c, &tfa->hap_data, idx);
        if (rc < 0)
        {
            total_duration = rc; /* return value */
            break;
        }
        this_duration = tfa2_haptic_get_duration(tfa, idx);
        total_duration += this_duration;
        /* sleep while buzzing */
        msleep_interruptible(this_duration);
        /* obj should be finished by now */
        rc = tfa2_haptic_obj0_wait_finish(tfa->i2c);
        if (rc < 0)
        {
            total_duration = rc; /* return value */
            break;
        }
    }

    /* restore default object */
    tfa->hap_data.duration  = save_duration;
    tfa->hap_data.amplitude = save_amplitude;
    tfa->hap_data.frequency = save_frequency;

    return total_duration;
}
int tfa2_hap_get_sequencer_duration(struct tfa2_device *tfa, struct tfa2_sequence *seq)
{
    int i, idx, this_duration, total_duration = 0;
    struct haptic_data *data = &tfa->hap_data;

    if (seq == 0 || seq->object == 0)
        return -EINVAL;

    for (i = 0; i < seq->length; i++)
    {
        idx = seq->object[i] - 1; /* lists starts counting at 1 */
        /* get current settings */
        tfa2_haptic_obj_get_duration(data, idx);

        /* adjust according to table */
        if (seq->duration && seq->duration[i])
            data->duration = seq->duration[i];

        this_duration = tfa2_haptic_get_duration(tfa, idx);
        total_duration += this_duration;
    }
    seq->total_duration = total_duration;

    return total_duration;
}
void tfa2_hap_save_haptic_cache(struct tfa2_device *tfa, struct tfa2_sequence *seq)
{
    memcpy(&seq->object_table1_cache_save, &tfa->hap_data.object_table1_cache,
           sizeof(tfa->hap_data.object_table1_cache));
    memcpy(&seq->object_table2_cache_save, &tfa->hap_data.object_table2_cache,
           sizeof(tfa->hap_data.object_table2_cache));
}

void tfa2_hap_test_restore_haptic_cache(struct tfa2_device *tfa, struct tfa2_sequence *seq)
{
    if (memcmp(&tfa->hap_data.object_table1_cache, &seq->object_table1_cache_save,
               sizeof(tfa->hap_data.object_table1_cache)))
    {
        memcpy(&tfa->hap_data.object_table1_cache, &seq->object_table1_cache_save,
               sizeof(tfa->hap_data.object_table1_cache));
        tfa2_i2c_write_cf_mem32(tfa->i2c, FW_XMEM_GENOBJECTS1, (int32_t *)tfa->hap_data.object_table1_cache,
                                FW_XMEM_NR_OBJECTS1 * FW_XMEM_OBJECTSIZE, TFA2_CF_MEM_XMEM);
    }

    if (memcmp(&tfa->hap_data.object_table2_cache, &seq->object_table2_cache_save,
               sizeof(tfa->hap_data.object_table2_cache)))
    {
        memcpy(&tfa->hap_data.object_table2_cache, &seq->object_table2_cache_save,
               sizeof(tfa->hap_data.object_table2_cache));
        tfa2_i2c_write_cf_mem32(tfa->i2c, FW_XMEM_GENOBJECTS2, (int32_t *)tfa->hap_data.object_table2_cache,
                                FW_XMEM_NR_OBJECTS2 * FW_XMEM_OBJECTSIZE, TFA2_CF_MEM_XMEM);
    }
}

/*
 * run a sequencer virtual object
 */
int tfa2_hap_sequencer_object(struct tfa2_device *tfa, int virtual_obj)
{
    // sequencer
    struct tfa2_sequence seq;
    int dev_idx = tfa->dev_idx;
    int rc;

    tfa2_hap_save_haptic_cache(tfa, &seq);
    rc = tfa2_hap_cnt_get_sequencer(tfa->cnt, dev_idx, virtual_obj - FW_HB_SEQ_OBJ - 1, &seq);
    if (rc < 0)
    {
        pr_err("No sequencer\n");
        return -EINVAL;
    }
    rc = tfa2_hap_sequencer(tfa, &seq);
    tfa2_hap_test_restore_haptic_cache(tfa, &seq);
    tfa2_hap_sequencer_destroy(&seq);
    if (rc < 0)
    {
        pr_err("Sequencer play error:%d\n", rc);
        return rc;
    }

    return 0;
}

/*
 * return the nr of sequencers
 */
int tfa2_hap_cnt_sequencer_count(nxpTfaContainer_t *cnt, int devidx)
{
    int rc, total = 0;

    do
    {
        rc = tfa2_cnt_grep_nth_profile_name(cnt, devidx, total, ".seq.hap");

        if (rc == -EINVAL)
        {
            rc = 0;
            break;
        }
        total++;
    } while (rc >= 0);

    return rc ? rc : total; /* return error or count */
}

/*
 * find the nth sequencer in the container
 * for each array type
 * 	allocate 32bit buffer
 * 	convert 24 to 32 bits into seq struct
 */
int tfa2_hap_cnt_get_sequencer(nxpTfaContainer_t *cnt, int devidx, int seqidx, struct tfa2_sequence *seq)
{
    int i, rc, seq_profidx;
    uint8_t *array24;
    int length24, length32, type;

    seq_profidx = tfa2_cnt_grep_nth_profile_name(cnt, devidx, seqidx, ".seq.hap");
    if (seq_profidx < 0)
    {
        pr_err("can't find sequencer profile .seq.hap\n");
        return -EINVAL;
    }

    seq->length         = 0;
    seq->object         = 0;
    seq->duration       = 0;
    seq->level          = 0;
    seq->freq           = 0;
    seq->total_duration = 0;

    /* there may be 4 different arrays in a sequencer profile */
    for (i = 0; i < 4; i++)
    {
        rc = tfa2_cnt_get_cmd(cnt, devidx, seq_profidx, i, &array24, &length24);
        if (rc < 0)
        {
            break; /* we are done, no error report here */
        }
        /* get the array type, 1 24bit word */
        type     = (((array24[0] << 16) + (array24[1] << 8) + array24[2]) << 8) >> 8;
        length32 = length24 + length24 / 3 - 4;
        if (seq->length == 0)
            seq->length = length32 / sizeof(int32_t);

        switch (type)
        {
            case 0:
                seq->object = (int32_t *)kmalloc(length32, GFP_KERNEL);
                tfa2_24_to_32(seq->object, array24 + 3, length24 - 3);
                break;
            case 1:
                seq->duration = (int32_t *)kmalloc(length32, GFP_KERNEL);
                tfa2_24_to_32(seq->duration, array24 + 3, length24 - 3);
                break;
            case 2:
                seq->level = (int32_t *)kmalloc(length32, GFP_KERNEL);
                tfa2_24_to_32(seq->level, array24 + 3, length24 - 3);
                break;
            case 3:
                seq->freq = (int32_t *)kmalloc(length32, GFP_KERNEL);
                tfa2_24_to_32(seq->freq, array24 + 3, length24 - 3);
                break;
            default:
                return -EINVAL;
        }
    }

    return 0;
}
