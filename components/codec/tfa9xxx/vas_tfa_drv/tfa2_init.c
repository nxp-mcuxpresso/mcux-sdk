/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "tfa2_dev.h"

/*
 * TODO can factory_trimmer for tfa9892 done after optimal settings?
 */

static int tfa9894_init(struct tfa2_device *tfa)
{
    int rc = 0;

    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    /* The optimal settings */
    if (tfa->rev == 0x1a94)
    {
        /* V14 */
        /* ----- generated code start ----- */
        tfa2_i2c_write_reg(tfa->i2c, 0x00, 0xa245); // POR=0x8245
        tfa2_i2c_write_reg(tfa->i2c, 0x01, 0x15da); // POR=0x11ca
        tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x5288); // POR=0x55c8
        tfa2_i2c_write_reg(tfa->i2c, 0x52, 0xbe17); // POR=0xb617
        tfa2_i2c_write_reg(tfa->i2c, 0x53, 0x0dbe); // POR=0x0d9e
        tfa2_i2c_write_reg(tfa->i2c, 0x56, 0x05c3); // POR=0x07c3
        tfa2_i2c_write_reg(tfa->i2c, 0x57, 0x0344); // POR=0x0366
        tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0032); // POR=0x0073
        tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x00cf); // POR=0x018d
        tfa2_i2c_write_reg(tfa->i2c, 0x72, 0x34a9); // POR=0x44e8
        tfa2_i2c_write_reg(tfa->i2c, 0x73, 0x38c8); // POR=0x3806
        tfa2_i2c_write_reg(tfa->i2c, 0x76, 0x0067); // POR=0x0065
        tfa2_i2c_write_reg(tfa->i2c, 0x80, 0x0000); // POR=0x0003
        tfa2_i2c_write_reg(tfa->i2c, 0x81, 0x5799); // POR=0x561a
        tfa2_i2c_write_reg(tfa->i2c, 0x82, 0x0104); // POR=0x0044
        /* ----- generated code end ----- */
    }
    else if ((tfa->rev == 0x2a94) || (tfa->rev == 0x3a94))
    {
        /* V10 */
        /* ----- generated code start ----- */
        tfa2_i2c_write_reg(tfa->i2c, 0x00, 0xa245); // POR=0x8245
        tfa2_i2c_write_reg(tfa->i2c, 0x01, 0x15da); // POR=0x11ca
        tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x51e8); // POR=0x55c8
        tfa2_i2c_write_reg(tfa->i2c, 0x52, 0xbe17); // POR=0xb617
        tfa2_i2c_write_reg(tfa->i2c, 0x53, 0x0dbe); // POR=0x0d9e k2
        tfa2_i2c_write_reg(tfa->i2c, 0x57, 0x0344); // POR=0x0366
        tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0033); // POR=0x0073
        tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x6ecf); // POR=0x6f8d
        tfa2_i2c_write_reg(tfa->i2c, 0x72, 0x34a9); // POR=0x44e8
        tfa2_i2c_write_reg(tfa->i2c, 0x73, 0x38c8); // POR=0x3806
        tfa2_i2c_write_reg(tfa->i2c, 0x76, 0x0067); // POR=0x0065 k2
        tfa2_i2c_write_reg(tfa->i2c, 0x80, 0x0000); // POR=0x0003 k2
        tfa2_i2c_write_reg(tfa->i2c, 0x81, 0x5799); // POR=0x561a k2
        tfa2_i2c_write_reg(tfa->i2c, 0x82, 0x0104); // POR=0x0044 k2
        /* ----- generated code end   ----- */
    }
    else
    {
        dev_err(&tfa->i2c->dev, "%s: unknown device revision: 0x%02x\n", __FUNCTION__, tfa->rev);
        rc = -EINVAL;
    }

    /* re-lock */
    tfa2_i2c_hap_key2(tfa->i2c, 1);

    return rc;
}
int tfa9894_tfa_mtp_write_wrapper(struct tfa2_device *tfa,
                                  uint16_t addr,
                                  uint16_t mtp_new,
                                  int (*mtp_write)(struct tfa2_device *, uint16_t, uint16_t))
{
    int rc;
    int save_bit1, save_bit2;
    // int save_state;
    int lpm1mode;
    /********************** mtp setup ************************************/
    /*
     * disable_auto_sel_refclk and FAIMVBGOVRRL need to be set to allow
     * MTP writes in init_cf state
     */
    /* { 0x470, "disable_auto_sel_refclk"},    Automatic PLL reference clock selection for cold start, */
    save_bit1 = tfa2_i2c_read_bf(tfa->i2c, 0x470);
    /*  { 0x1f0, "FAIMVBGOVRRL"},     Overrule the enabling of VBG for faim erase/write access, */
    save_bit2 = tfa2_i2c_read_bf(tfa->i2c, 0x1f0);

    lpm1mode = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_lpm1mode);

    /* disable low power mode */
    tfa2_i2c_write_bf(tfa->i2c, tfa->bf_lpm1mode, 1);

    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_write_bf(tfa->i2c, 0x470, 1);
    tfa2_i2c_write_bf(tfa->i2c, 0x1f0, 1);

    /* do the write */
    rc = (*mtp_write)(tfa, addr, mtp_new);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "error writing MTP: 0x%02x 0x%04x\n", addr, mtp_new);
    }
    /* unlock can't be done anymore tfa2_i2c_lock() open key1 */
    /* restore */
    tfa2_i2c_write_bf(tfa->i2c, 0x470, save_bit1);
    tfa2_i2c_write_bf(tfa->i2c, 0x1f0, save_bit2);
    tfa2_i2c_write_bf(tfa->i2c, tfa->bf_lpm1mode, lpm1mode);

    return rc;
}

static int tfa9872_init(struct tfa2_device *tfa)
{
    const uint16_t bypass_ovp = 0xb020;
    int rc                    = 0;

    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    switch (tfa->rev)
    {
        case 0x1a72:
        case 0x2a72:
            /* ----- generated code start ----- */
            /* -----  version 26 ----- */
            tfa2_i2c_write_reg(tfa->i2c, 0x00, 0x1801); // POR=0x0001
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x2dc8); // POR=0x2028
            tfa2_i2c_write_reg(tfa->i2c, 0x20, 0x0890); // POR=0x2890
            tfa2_i2c_write_reg(tfa->i2c, 0x22, 0x043c); // POR=0x045c
            tfa2_i2c_write_reg(tfa->i2c, 0x51, 0x0000); // POR=0x0080
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x1a1c); // POR=0x7ae8
            tfa2_i2c_write_reg(tfa->i2c, 0x58, 0x161c); // POR=0x101c
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0198); // POR=0x0000
            tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0a8b); // POR=0x0a9a
            tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x07f5); // POR=0x06e6
            tfa2_i2c_write_reg(tfa->i2c, 0x74, 0xcc84); // POR=0xd823
            tfa2_i2c_write_reg(tfa->i2c, 0x82, 0x01ed); // POR=0x000d
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x0014); // POR=0x0013
            tfa2_i2c_write_reg(tfa->i2c, 0x84, 0x0021); // POR=0x0020
            tfa2_i2c_write_reg(tfa->i2c, 0x85, 0x0001); // POR=0x0003
            /* ----- generated code end   ----- */
            break;
        case 0x1b72:
        case 0x2b72:
        case 0x3b72:
            /* ----- generated code start ----- */
            /*  -----  version 25.00 ----- */
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x2dc8); // POR=0x2828
            tfa2_i2c_write_reg(tfa->i2c, 0x20, 0x0890); // POR=0x2890
            tfa2_i2c_write_reg(tfa->i2c, 0x22, 0x043c); // POR=0x045c
            tfa2_i2c_write_reg(tfa->i2c, 0x23, 0x0001); // POR=0x0003
            tfa2_i2c_write_reg(tfa->i2c, 0x51, 0x0000); // POR=0x0080
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x5a1c); // POR=0x7a08
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0198); // POR=0x0000
            tfa2_i2c_write_reg(tfa->i2c, 0x63, 0x0a9a); // POR=0x0a93
            tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0a82); // POR=0x0a8d
            tfa2_i2c_write_reg(tfa->i2c, 0x6f, 0x01e3); // POR=0x02e4
            tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x06fd); // POR=0x06e6
            tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x307e); // POR=0x207e
            tfa2_i2c_write_reg(tfa->i2c, 0x74, 0xcc84); // POR=0xd913
            tfa2_i2c_write_reg(tfa->i2c, 0x75, 0x1132); // POR=0x118a
            tfa2_i2c_write_reg(tfa->i2c, 0x82, 0x01ed); // POR=0x000d
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x001a); // POR=0x0013
            /* ----- generated code end   ----- */
            break;
        default:
            dev_err(&tfa->i2c->dev, "%s: unknown device revision: 0x%02x\n", __FUNCTION__, tfa->rev);
            rc = -EINVAL;
            break;
    }

    if (rc == 0)
    {
        /* Bypass OVP (bypass_ovp=1): PLMA5258 */
        rc = tfa2_i2c_write_bf(tfa->i2c, bypass_ovp, 1);
    }

    /* re-lock can't be done anymore tfa2_i2c_lock() open key1 */

    return rc;
}

static int tfa9873_init(struct tfa2_device *tfa)
{
    int rc = 0;

    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    switch (tfa->rev)
    {
        case 0x0a73: /* Initial revision ID */
            /* ----- generated code start ----- */
            /* -----  version 22 ----- */
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x0628); // POR=0x0008
            tfa2_i2c_write_reg(tfa->i2c, 0x4c, 0x00e9); // POR=0x00ff
            tfa2_i2c_write_reg(tfa->i2c, 0x56, 0x0011); // POR=0x0019
            tfa2_i2c_write_reg(tfa->i2c, 0x5f, 0x0180); // POR=0x0100
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0183); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x63, 0x055a); // POR=0x0a9a
            tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0542); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x009a); // POR=0x0799
            tfa2_i2c_write_reg(tfa->i2c, 0x84, 0x0211); // POR=0x0011
            tfa2_i2c_write_reg(tfa->i2c, 0x8c, 0x0210); // POR=0x0010
            /* ----- generated code end   ----- */
            break;
        case 0x1a73:
            break;
        default:
            dev_err(&tfa->i2c->dev, "%s: unknown device revision: 0x%02x\n", __FUNCTION__, tfa->rev);
            rc = -EINVAL;
            break;
    }

    /* re-lock can't be done anymore tfa2_i2c_lock() open key1 */

    return rc;
}

static int tfa9874_init(struct tfa2_device *tfa)
{
    int rc = 0;

    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    switch (tfa->rev)
    {
        case 0x0a74: /* Initial revision ID */
            /* ----- generated code start ----- */
            /* V25 */
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x22a8); // POR=0x25c8
            tfa2_i2c_write_reg(tfa->i2c, 0x51, 0x0020); // POR=0x0000
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x57dc); // POR=0x56dc
            tfa2_i2c_write_reg(tfa->i2c, 0x58, 0x16a4); // POR=0x1614
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0110); // POR=0x0198
            tfa2_i2c_write_reg(tfa->i2c, 0x66, 0x0701); // POR=0x0700
            tfa2_i2c_write_reg(tfa->i2c, 0x6f, 0x00a3); // POR=0x01a3
            tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x07f8); // POR=0x06f8
            tfa2_i2c_write_reg(tfa->i2c, 0x73, 0x0007); // POR=0x0005
            tfa2_i2c_write_reg(tfa->i2c, 0x74, 0x5068); // POR=0xcc80
            tfa2_i2c_write_reg(tfa->i2c, 0x75, 0x0d28); // POR=0x1138
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x0594); // POR=0x061a
            tfa2_i2c_write_reg(tfa->i2c, 0x84, 0x0001); // POR=0x0021
            tfa2_i2c_write_reg(tfa->i2c, 0x85, 0x0001); // POR=0x0003
            tfa2_i2c_write_reg(tfa->i2c, 0x88, 0x0000); // POR=0x0002
            tfa2_i2c_write_reg(tfa->i2c, 0xc4, 0x2001); // POR=0x0001
            /* ----- generated code end   ----- */
            break;
        case 0x0b74:
            /* ----- generated code start ----- */
            /* V1.6 */
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x22a8); // POR=0x25c8
            tfa2_i2c_write_reg(tfa->i2c, 0x51, 0x0020); // POR=0x0000
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x57dc); // POR=0x56dc
            tfa2_i2c_write_reg(tfa->i2c, 0x58, 0x16a4); // POR=0x1614
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0110); // POR=0x0198
            tfa2_i2c_write_reg(tfa->i2c, 0x66, 0x0701); // POR=0x0700
            tfa2_i2c_write_reg(tfa->i2c, 0x6f, 0x00a3); // POR=0x01a3
            tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x07f8); // POR=0x06f8
            tfa2_i2c_write_reg(tfa->i2c, 0x73, 0x0047); // POR=0x0045
            tfa2_i2c_write_reg(tfa->i2c, 0x74, 0x5068); // POR=0xcc80
            tfa2_i2c_write_reg(tfa->i2c, 0x75, 0x0d28); // POR=0x1138
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x0595); // POR=0x061a
            tfa2_i2c_write_reg(tfa->i2c, 0x84, 0x0001); // POR=0x0021
            tfa2_i2c_write_reg(tfa->i2c, 0x85, 0x0001); // POR=0x0003
            tfa2_i2c_write_reg(tfa->i2c, 0x88, 0x0000); // POR=0x0002
            tfa2_i2c_write_reg(tfa->i2c, 0xc4, 0x2001); // POR=0x0001
            /* ----- generated code end   ----- */
            break;
        case 0x0c74:
            /* ----- generated code start ----- */
            /* V1.16 */
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x22c8); // POR=0x25c8
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x57dc); // POR=0x56dc
            tfa2_i2c_write_reg(tfa->i2c, 0x53, 0x003e); // POR=0x001e
            tfa2_i2c_write_reg(tfa->i2c, 0x56, 0x0400); // POR=0x0600
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0110); // POR=0x0198
            tfa2_i2c_write_reg(tfa->i2c, 0x6f, 0x00a5); // POR=0x01a3
            tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x07f8); // POR=0x06f8
            tfa2_i2c_write_reg(tfa->i2c, 0x73, 0x0047); // POR=0x0045
            tfa2_i2c_write_reg(tfa->i2c, 0x74, 0x5098); // POR=0xcc80
            tfa2_i2c_write_reg(tfa->i2c, 0x75, 0x8d28); // POR=0x1138
            tfa2_i2c_write_reg(tfa->i2c, 0x80, 0x0000); // POR=0x0003
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x0799); // POR=0x061a
            tfa2_i2c_write_reg(tfa->i2c, 0x84, 0x0081); // POR=0x0021
            /* ----- generated code end   ----- */
            break;
        default:
            dev_err(&tfa->i2c->dev, "%s: unknown device revision: 0x%02x\n", __FUNCTION__, tfa->rev);
            rc = -EINVAL;
            break;
    }

    /* re-lock can't be done anymore tfa2_i2c_lock() open key1 */

    return rc;
}

static int tfa9878_init(struct tfa2_device *tfa)
{
    int rc = 0;

    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    switch (tfa->rev)
    {
        case 0x0a78:
            /* ----- generated code start ----- */
            /* -----  version 28 ----- */
            tfa2_i2c_write_reg(tfa->i2c, 0x01, 0x2e18); // POR=0x2e88
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x0628); // POR=0x0008
            tfa2_i2c_write_reg(tfa->i2c, 0x04, 0x0240); // POR=0x0340
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x587c); // POR=0x57dc
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0183); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x63, 0x055a); // POR=0x0a9a
            tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0542); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x303e); // POR=0x307e
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x009a); // POR=0x0799
            /* ----- generated code end   ----- */
            break;
        case 0x1a78:
            /* ----- generated code start ----- */
            /* -----  version 4 ----- */
            tfa2_i2c_write_reg(tfa->i2c, 0x01, 0x2e18); // POR=0x2e88
            tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x0628); // POR=0x0008
            tfa2_i2c_write_reg(tfa->i2c, 0x04, 0x0240); // POR=0x0340
            tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x587c); // POR=0x57dc
            tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x0183); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x63, 0x055a); // POR=0x0a9a
            tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0542); // POR=0x0a82
            tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x303e); // POR=0x307e
            tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x009a); // POR=0x0799
            /* ----- generated code end   ----- */
            break;
        default:
            dev_err(&tfa->i2c->dev, "%s: unknown device revision: 0x%02x\n", __FUNCTION__, tfa->rev);
            rc = -EINVAL;
            break;
    }

    /* re-lock can't be done anymore tfa2_i2c_lock() open key1 */

    return rc;
}

/***********************************************************************************/
/* TFA9912                                                                         */
/***********************************************************************************/

static int tfa9912_init(struct tfa2_device *tfa)
{
    if (tfa->in_use == 0)
        return -ENOENT;

    /* Unlock keys to write settings */
    tfa2_i2c_unlock(tfa->i2c); /* key1 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    /* The optimal settings */
    if (tfa->rev == 0x1a13)
    {
        /* ----- generated code start ----- */
        /* -----  version 1.41  ----- */
        tfa2_i2c_write_reg(tfa->i2c, 0x00, 0x0255); // POR=0x0245
        tfa2_i2c_write_reg(tfa->i2c, 0x01, 0x838a); // POR=0x83ca
        tfa2_i2c_write_reg(tfa->i2c, 0x02, 0x2dc8); // POR=0x2828
        tfa2_i2c_write_reg(tfa->i2c, 0x05, 0x762a); // POR=0x766a
        tfa2_i2c_write_reg(tfa->i2c, 0x22, 0x543c); // POR=0x545c
        tfa2_i2c_write_reg(tfa->i2c, 0x26, 0x0100); // POR=0x0010
        tfa2_i2c_write_reg(tfa->i2c, 0x51, 0x0000); // POR=0x0080
        tfa2_i2c_write_reg(tfa->i2c, 0x52, 0x551c); // POR=0x1afc
        tfa2_i2c_write_reg(tfa->i2c, 0x53, 0x003e); // POR=0x001e
        tfa2_i2c_write_reg(tfa->i2c, 0x61, 0x000c); // POR=0x0018
        tfa2_i2c_write_reg(tfa->i2c, 0x63, 0x0a96); // POR=0x0a9a
        tfa2_i2c_write_reg(tfa->i2c, 0x65, 0x0a82); // POR=0x0a8b
        tfa2_i2c_write_reg(tfa->i2c, 0x66, 0x0701); // POR=0x0700
        tfa2_i2c_write_reg(tfa->i2c, 0x6c, 0x00d5); // POR=0x02d5
        tfa2_i2c_write_reg(tfa->i2c, 0x70, 0x26f8); // POR=0x06e0
        tfa2_i2c_write_reg(tfa->i2c, 0x71, 0x3074); // POR=0x2074
        tfa2_i2c_write_reg(tfa->i2c, 0x75, 0x4484); // POR=0x4585
        tfa2_i2c_write_reg(tfa->i2c, 0x76, 0x72ea); // POR=0x54a2
        tfa2_i2c_write_reg(tfa->i2c, 0x83, 0x0716); // POR=0x0617
        tfa2_i2c_write_reg(tfa->i2c, 0x89, 0x0013); // POR=0x0014
        tfa2_i2c_write_reg(tfa->i2c, 0xb0, 0x4c08); // POR=0x4c00
        tfa2_i2c_write_reg(tfa->i2c, 0xc6, 0x004e); // POR=0x000e /* PLMA5539: Please make sure bit 6 is always on! */
        /* ----- generated code end   ----- */

        /* PLMA5505: default MTP key open makes vulnerable to MTP corruption */
        tfa2_i2c_write_bf(tfa->i2c, tfa->bf_openmtp, 0);
    }
    else
    {
        pr_info("Warning: Optimal settings not found for device with revid = 0x%x \n", tfa->rev);
        return -EINVAL;
    }

    return 0;
}

#define TFA9912_BF_DCMCCAPI 0xf020
#define TFA9912_BF_DCMCC    0x7033
#define TFA9912_BF_DCMCCCL  0xf042
#define TFA9912_BF_DCMCCSB  0xf030

static int tfa9912_factory_trimmer(struct tfa2_device *tfa)
{
    int currentValue, delta;
    int rc = 0;

    /* Factory trimming for the Boost converter */
    /* check if there is a correction needed */
    rc = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCMCCAPI);
    if (rc < 0)
        return rc;

    if (rc)
    {
        /* Get currentvalue of DCMCC and the Delta value */
        rc = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCMCC);
        if (rc < 0)
            return rc;
        currentValue = rc;
        rc           = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCMCCCL);
        if (rc < 0)
            return rc;
        delta = rc;

        /* check the sign bit (+/-) */
        rc = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCMCCSB);
        if (rc < 0)
            return rc;
        if (rc == 0)
        {
            /* Do not exceed the maximum value of 15 */
            if (currentValue + delta < 15)
            {
                rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9912_BF_DCMCC, currentValue + delta);
                if (tfa->verbose)
                    pr_debug("Max coil current is set to: %d \n", currentValue + delta);
            }
            else
            {
                rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9912_BF_DCMCC, 15);
                if (tfa->verbose)
                    pr_debug("Max coil current is set to: 15 \n");
            }
        }
        else if (rc == 1)
        {
            /* Do not exceed the minimum value of 0 */
            if (currentValue - delta > 0)
            {
                rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9912_BF_DCMCC, currentValue - delta);
                if (tfa->verbose)
                    pr_debug("Max coil current is set to: %d \n", currentValue - delta);
            }
            else
            {
                rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9912_BF_DCMCC, 0);
                if (tfa->verbose)
                    pr_debug("Max coil current is set to: 0 \n");
            }
        }
    }

    return rc;
}

/* Maksimum value for combination of boost_voltage and vout calibration offset (see PLMA5322, PLMA5528). */
#define TFA9912_BF_DCVOF         0x7635
#define TFA9912_BF_DCVOS         0x7695
#define TFA9912_VBOOST_MAX       57
#define TFA9912_CALIBR_BOOST_MAX 63
#define TFA9912_DCDCCNT6_REG     (TFA9912_BF_DCVOF >> 8)
#define TFA9912_CALIBR_REG       0xf1

static int tfa9912_vboost_fixup(struct tfa2_device *tfa)
{
    int rc;
    int cal_offset;
    int dcvof, dcvos;

    /* Get current calibr_vout_offset, this register is not supported by bitfields */
    rc = tfa2_i2c_read_reg(tfa->i2c, TFA9912_CALIBR_REG);
    if (rc < 0)
        return rc;
    cal_offset = (rc & 0x001f);

    /* Get current boost_volatage values */
    rc = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCVOF);
    if (rc < 0)
        return rc;
    dcvof = rc;
    rc    = tfa2_i2c_read_bf(tfa->i2c, TFA9912_BF_DCVOS);
    if (rc < 0)
        return rc;
    dcvos = rc;

    /* Check boost voltages, limit them to TFA9912_VBOOST_MAX */
    if (dcvof > TFA9912_VBOOST_MAX)
    {
        dev_warn(&tfa->i2c->dev, "DCVOF exceeding maximum (57), adjusting it to maximum.\n");
        dcvof = TFA9912_VBOOST_MAX;
    }

    if (dcvos > TFA9912_VBOOST_MAX)
    {
        dev_warn(&tfa->i2c->dev, "DCVOS exceeding maximum (57), adjusting it to maximum.\n");
        dcvos = TFA9912_VBOOST_MAX;
    }

    /* Recalculate values, max for the sum is TFA9912_CALIBR_BOOST_MAX */
    if (dcvof + cal_offset > TFA9912_CALIBR_BOOST_MAX)
    {
        dev_dbg(&tfa->i2c->dev, "Recalculate DCVOF based on calibr_vout_offset.\n");
        dcvof = TFA9912_CALIBR_BOOST_MAX - cal_offset;
    }

    if (dcvos + cal_offset > TFA9912_CALIBR_BOOST_MAX)
    {
        dev_dbg(&tfa->i2c->dev, "Recalculate DCVOS based on calibr_vout_offset.\n");
        dcvos = TFA9912_CALIBR_BOOST_MAX - cal_offset;
    }

    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9912_BF_DCVOF, dcvof);
    if (rc < 0)
        return rc;
    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9912_BF_DCVOS, dcvos);
    return rc;
}

int tfa2_init_mtp_write_wrapper(struct tfa2_device *tfa,
                                uint16_t addr,
                                uint16_t mtp_new,
                                int (*mtp_write)(struct tfa2_device *, uint16_t, uint16_t))
{
    int rc;
    int lpm1mode, faimvbgovrrl, bf_faimvbgovrrl = 0;

    /********************** mtp setup ************************************/

    /*
     * FAIMVBGOVRRL needs to be set to allow MTP writes in init_cf state.
     *  (Overrule the enabling of VBG for faim erase/write access)
     */
    if ((tfa->rev & 0xff) == 0x13)
    {
        bf_faimvbgovrrl = 0x5f0;
    }
    else if ((tfa->rev & 0xff) == 0x94)
    {
        bf_faimvbgovrrl = 0x1f0;
    }

    if (bf_faimvbgovrrl)
        faimvbgovrrl = tfa2_i2c_read_bf(tfa->i2c, bf_faimvbgovrrl);

    lpm1mode = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_lpm1mode);

    /* disable low power mode */
    tfa2_i2c_write_bf(tfa->i2c, tfa->bf_lpm1mode, 1);

    tfa2_i2c_unlock(tfa->i2c); /* key1 */

    if (bf_faimvbgovrrl)
        tfa2_i2c_write_bf(tfa->i2c, bf_faimvbgovrrl, 1);

    /* do the write */
    rc = (*mtp_write)(tfa, addr, mtp_new);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "error writing MTP: 0x%02x 0x%04x\n", addr, mtp_new);
    }

    /* unlock can't be done anymore tfa2_i2c_lock() open key1 */
    /* restore */
    if (bf_faimvbgovrrl)
        tfa2_i2c_write_bf(tfa->i2c, bf_faimvbgovrrl, faimvbgovrrl);

    tfa2_i2c_write_bf(tfa->i2c, tfa->bf_lpm1mode, lpm1mode);

    return rc;
}

/* called during cold start before powering up the device */
int tfa2_init_fix_powerup(struct tfa2_device *tfa)
{
    int rc = 0;

    /* only for tfa9912 */
    if ((tfa->rev & 0xff) == 0x13)
    {
        /* overwrite DCMCC if needed */
        rc = tfa9912_factory_trimmer(tfa);
        if (rc < 0)
            return rc;

        /* overwrite DCVOS and DCVOF if needed */
        rc = tfa9912_vboost_fixup(tfa);
    }

    return rc;
}

/* called during warm profile switch */
int tfa2_init_fix_initcf(struct tfa2_device *tfa)
{
    int rc = 0;

    /* only for tfa9912 */
    if ((tfa->rev & 0xff) == 0x13)
    {
        /* The status register from which the CF_ACK bits are read is having a
         * reset signal which is synchronized with the clock which is used by
         * FaIM SS.
         * When the FaIM subsystem is disabled, its clock is gated and hence
         * reset is not released for the status register thereby blocking the
         * CF ack signal from reading correctly. I2C read is blocked.
         * Workaround is to toggle enabling FAIM SS just after entering the
         * INITCF state.
         * Manager keeps the DSP sub-system in RESET state until it reaches
         * INITCF state. We need few clock edges after to release the CFSS reset.
         */
        tfa2_i2c_write_bf_volatile(tfa->i2c, 0x05c0, 1); /* TFA9912_BF_SSFAIME */
        tfa2_i2c_write_bf_volatile(tfa->i2c, 0x05c0, 0); /* TFA9912_BF_SSFAIME */
    }

    return rc;
}

/* called before powering down the device */
int tfa2_init_fix_powerdown(struct tfa2_device *tfa, int manstate)
{
    int rc = 0;

    /* only for tfa9912 */
    if (tfa->rev == 0x1a13 && manstate == 1)
    {
        rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 0);
        if (rc < 0)
            return rc;
        rc = tfa2_i2c_write_bf_volatile(tfa->i2c, 0x0691, 2); // TFA9912_BF_STARTUPMODE
        if (rc < 0)
            return rc;
        rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 1);
        if (rc < 0)
            return rc;
        rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 1);
        if (rc < 0)
            return rc;
        rc = tfa2_i2c_write_bf_volatile(tfa->i2c, 0x0691, 0); // TFA9912_BF_STARTUPMODE
    }

    return rc;
}

/* TODO use the getfeatures() for retrieving the features [artf103523]
tfa->supportDrc = supportNotSet;*/
int tfa2_dev_specific(struct tfa2_device *tfa)
{
    switch (tfa->rev & 0xff)
    {
        case 0x94:
            if ((tfa->rev == 0x2a94) || (tfa->rev == 0x3a94))
            {
                /* bit field overloads */
                tfa->bf_manstate = 0x1333;
            }

            /* tfa9894 */
            tfa->tfa_init = tfa9894_init;
            break;
        case 0x13:
            /* tfa9912 */
            tfa->tfa_init = tfa9912_init;
            /* bit field overloads */
            tfa->bf_clks     = 0x1050;
            tfa->bf_manaoosc = 0x0140;
            tfa->bf_noclk    = 0x1070;
            tfa->bf_mtpb     = 0x1060; /* TFA9912_BF_MTPB */
            tfa->bf_openmtp  = 0x05c0; /* TFA9912_BF_SSFAIME */
            tfa->bf_swprofil = 0xee0f;
            tfa->bf_swvstep  = 0xef0f;
            tfa->bf_lpm1mode = 0x65c0; /* TFA9912_BF_LPM1DIS */
            tfa->bf_r25c     = 0xf40f;

            tfa->status_mask[0] = 0x0014; /* UVDS, OTDS */
            tfa->status_mask[1] = 0x2180; /* SWS, TDMLUTER, CLKS */
            tfa->status_mask[2] = 0x0000;
            tfa->status_mask[3] = 0x0100; /* OVDS */

            tfa->status_err[0] = 0x00e1;
            tfa->status_err[1] = 0x1f05;
            tfa->status_err[2] = 0;
            tfa->status_err[3] = 0x5200;
            break;
        case 0x72:
            /* bit field overloads */
            tfa->bf_clks     = 0x1050;
            tfa->bf_manaoosc = 0x0140;
            tfa->bf_noclk    = 0x1070;
            tfa->bf_mtpb     = 0x1060;
            tfa->bf_swprofil = 0xee0f;
            tfa->bf_swvstep  = 0xef0f;
            tfa->bf_openmtp  = 0x05c0; /* TFA9872_BF_SSFAIME */
            tfa->bf_lpm1mode = 0x65c0; /* TFA9872_BF_LPM1DIS */

            tfa->status_mask[0] = 0x043c; /* SWS, CLKS, UVDS, OVDS, OTDS */
            tfa->status_mask[1] = 0x0100; /* TDMLUTER */
            tfa->status_mask[2] = 0x0000;
            tfa->status_mask[3] = 0x0000;

            tfa->status_err[0] = 0x8bc1;
            tfa->status_err[1] = 0x3f8b;
            tfa->status_err[2] = 0;
            tfa->status_err[3] = 0;

            /* tfa9872 */
            tfa->tfa_init         = tfa9872_init;
            tfa->is_probus_device = 1;
            break;
        case 0x74:
            /* bit field overloads */
            tfa->bf_clks     = 0x1170;
            tfa->bf_manaoosc = 0x0140;
            tfa->bf_noclk    = 0x1070;
            tfa->bf_mtpb     = 0x11c0;
            tfa->bf_swprofil = 0xee0f;
            tfa->bf_swvstep  = 0xef0f;
            tfa->bf_lpm1mode = 0x64e1;

            tfa->status_mask[0] = 0x0014; /* UVDS, OTDS */
            tfa->status_mask[1] = 0x2180; /* SWS, TDMLUTER, CLKS */
            tfa->status_mask[2] = 0x0000;
            tfa->status_mask[3] = 0x0100; /* OVDS */

            tfa->status_err[0] = 0x00e1;
            tfa->status_err[1] = 0x1f05;
            tfa->status_err[2] = 0;
            tfa->status_err[3] = 0x5200;

            /* tfa9874 */
            tfa->tfa_init         = tfa9874_init;
            tfa->is_probus_device = 1;
            break;
        case 0x78:
            /* bit field overloads */
            tfa->bf_lpm1mode = 0x64e1;

            tfa->status_mask[0] = 0x0054; /* CLKS, UVDS, OTDS */
            tfa->status_mask[1] = 0x2100; /* SWS, TDMLUTER */
            tfa->status_mask[2] = 0x0000;
            tfa->status_mask[3] = 0x0100; /* OVDS */

            tfa->status_err[0] = 0x00a1;
            tfa->status_err[1] = 0x1f05;
            tfa->status_err[2] = 0;
            tfa->status_err[3] = 0x5200;

            /* tfa9878 */
            tfa->tfa_init         = tfa9878_init;
            tfa->is_probus_device = 1;
            break;
        case 0x73:
            /* bit field overloads */
            tfa->bf_lpm1mode = 0x64e1;

            tfa->status_mask[0] = 0x0054; /* CLKS, UVDS, OTDS */
            tfa->status_mask[1] = 0x2100; /* SWS, TDMLUTER */
            tfa->status_mask[2] = 0x0000;
            tfa->status_mask[3] = 0x0100; /* OVDS */

            tfa->status_err[0] = 0x00a1;
            tfa->status_err[1] = 0x1f05;
            tfa->status_err[2] = 0;
            tfa->status_err[3] = 0x5200;

            /* tfa9873 */
            tfa->tfa_init         = tfa9873_init;
            tfa->is_probus_device = 1;
            break;
        case 0x00:
            /* external DSP */
            tfa->is_extern_dsp_device = 1;
            break;
        default:
            dev_err(&tfa->i2c->dev, "%s: unknown device type : 0x%02x\n", __FUNCTION__, tfa->rev);
            return -EINVAL;
            break;
    }

    return 0;
}
