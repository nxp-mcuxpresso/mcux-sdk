/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define pr_fmt(fmt) "%s(): " fmt, __FUNCTION__

#include "tfa2_dev.h"
#include "tfa2_haptic.h"
#include "tfa2_container.h"
#include "tfa_haptic_fw_defs.h"
#include "tfa2_dsp_fw.h"

static int mtp_open(struct tfa2_device *tfa, int state);

/* enum tfa9xxx_Status_ID */
static const char *tfa2_status_id_string[] = {
    "No response from DSP",
    "Ok",
    "Request is being processed",
    "Provided M-ID does not fit in valid rang [0..2]",
    "Provided P-ID is not valid in the given M-ID context",
    "Invalid channel configuration bits (SC|DS|DP|DC) combination",
    "Invalid sequence of commands, in case the DSP expects some commands in a specific order",
    "Generic error, invalid parameter",
    "I2C buffer has overflowed: host has sent too many parameters, memory integrity is not guaranteed",
    "Calibration not completed",
    "Calibration failed",
    "Unspecified error"};

const char *tfa2_get_i2c_status_id_string(int status)
{
    if ((status < tfa9xxx_no_dsp_response) || (status > tfa9xxx_I2C_Req_Calib_Failed))
        status = tfa9xxx_I2C_Req_Calib_Failed + 1; /* Unspecified error */

    /*  enum tfa9xxx_Status_ID starts at -1 */
    return tfa2_status_id_string[status + 1];
}

static const char *tfa2_manstate_string[] = {"power_down_state",
                                             "wait_for_source_settings_state",
                                             "connnect_pll_input_state",
                                             "disconnect_pll_input_state",
                                             "enable_pll_state",
                                             "enable_cgu_state",
                                             "init_cf_state",
                                             "enable_amplifier_state",
                                             "alarm_state",
                                             "operating_state",
                                             "mute_audio_state",
                                             "disable_cgu_pll_state",
                                             "Unable to find current state"};

/* align with enum tfa_state */
static const char *tfa2_state_enum_string[] = {
    "",                          /**< none or unknown or invalid */
    "TFA_STATE_POWERDOWN",       /**< PLL in powerdown, Algo is up/warm */
    "TFA_STATE_POWERUP",         /**< PLL to powerup, Algo can be up/warm */
    "TFA_STATE_OPERATING",       /**< Amp and Algo running */
    "TFA_STATE_RESET",           /**< I2C reset and ACS set */
    "TFA_STATE_INIT_CF",         /**< coolflux HW access possible (~initcf) */
    "TFA_STATE_OSC",             /**< internal oscillator */
    "TFA_STATE_CLOCK",           /**< always return with clock, use OSC if no external clock  */
    "TFA_STATE_POWERDOWN_HAPTIC" /**< PLL in powerdown, skip mute sequence */
};
/* align with enum tfa_state modifiers */
static const char *tfa2_state_mod_enum_string[] = {
    "", "MUTE", /**< Algo & Amp mute */
    "UNMUTE",   /**< Algo & Amp unmute */
};

/*
 * Print the current state of the hardware manager
 * Device manager status information, man_state from TFA9888_N1B_I2C_regmap_V12
 */
void tfa2_show_current_state(struct tfa2_device *tfa)
{
    int manstate = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);
    if (manstate < 0)
    {
        dev_err(&tfa->i2c->dev, "can't read MANSTATE\n");
        return;
    }

    if (manstate > 12)
        manstate = 12; /* Unable to find current state */

    dev_dbg(&tfa->i2c->dev, "Current HW manager state: %s \n", tfa2_manstate_string[manstate]);
}

int tfa2_dev_get_revid(struct tfa2_device *tfa) // TODO remove
{
    return tfa2_i2c_get_revid(tfa->i2c);
}

int tfa2_i2c_get_revid(struct i2c_client *i2c)
{
    int rc;

    rc = tfa2_i2c_read_bf(i2c, TFA9XXX_BF_REV);
    if (rc < 0)
        return rc;

    dev_dbg(&i2c->dev, "HW rev: 0x%04x\n", (uint16_t)rc);

    return rc;
}

/* fill context info */
int tfa2_dev_probe(struct tfa2_device *tfa)
{
    int rc = 0;

    tfa->slave_address = tfa->i2c->addr; /* used by HostSDK */

    if (tfa->i2c->addr > 0)
    {
        /* read revid via low level hal */
        rc = tfa2_i2c_get_revid(tfa->i2c);
        if (rc < 0)
        {
            dev_err(&tfa->i2c->dev, "error reading revid from slave 0x%02x\n", tfa->i2c->addr);
            return rc;
        }
    }

    tfa->rev = (uint16_t)rc;
    // TODO needed ? tfa->state = TFA_STATE_UNKNOWN;

    tfa2_set_query_info(tfa);

    tfa->in_use = 1;

    return 0;
}
/*
 *  set device info and register device ops
 */
int tfa2_set_query_info(struct tfa2_device *tfa)
{
    /* invalidate device struct cached values */
    tfa->hw_feature_bits    = -1;
    tfa->sw_feature_bits[0] = -1;
    tfa->sw_feature_bits[1] = -1;
    tfa->profile            = -1;
    tfa->vstep              = -1;
    tfa->need_hw_init       = -1;
    tfa->need_sb_config     = -1;
    tfa->need_hb_config     = tfa_hb_undetermined;
    /* defaults */
    //	tfa->supportDrc = supportNotSet;
    //	tfa->support_saam = supportNotSet;
    tfa->daimap               = Tfa9xxx_DAI_NONE;
    tfa->bus                  = 0;
    tfa->partial_enable       = 0;
    tfa->convert_dsp32        = 0;
    tfa->is_probus_device     = 0;
    tfa->is_extern_dsp_device = 0;
    /* bit fields per variant if needed */
    tfa->bf_clks     = TFA9XXX_BF_CLKS;     /* default 94N1A */
    tfa->bf_manstate = TFA9XXX_BF_MANSTATE; /* default 94N1A */
    tfa->bf_manaoosc = TFA9XXX_BF_MANAOOSC; /* default 94N1A */
    tfa->bf_noclk    = TFA9XXX_BF_NOCLK;    /* default 94N1A */
    tfa->bf_mtpb     = TFA9XXX_BF_MTPB;     /* default 94N1A */
    tfa->bf_swprofil = TFA9XXX_BF_SWPROFIL; /* default 94N1A */
    tfa->bf_swvstep  = TFA9XXX_BF_SWVSTEP;  /* default 94N1A */
    tfa->bf_openmtp  = TFA9XXX_BF_OPENMTP;  /* default 94N1A */
    tfa->bf_lpm1mode = TFA9XXX_BF_LPM1MODE; /* default 94N1A */
    tfa->bf_r25c     = TFA9XXX_BF_R25C;     /* default 94N1A */

    tfa->status_mask[0] = 0x085c; /* SWS, CLKS, UVDS, OVDS, OTDS */
    tfa->status_mask[1] = 0x0c00; /* TDMLUTER, TDMERR */
    tfa->status_mask[2] = 0x0000;
    tfa->status_mask[3] = 0x0000;

    tfa->status_err[0] = 0x87A1;
    tfa->status_err[1] = 0x0F89;
    tfa->status_err[2] = 0;
    tfa->status_err[3] = 0;

    tfa->dsp_init    = tfa2_i2c_dsp_init;    /* default */
    tfa->dsp_execute = tfa2_i2c_dsp_execute; /* default */

    /* per- device specific overload functions and/or values  */
    return tfa2_dev_specific(tfa);
}

/*
 * start the clocks and wait until the PLL is running
 *  on return state is INIT_CF :
 *      the DSP sub system will be ready for loading
 *
 *  former: tfaRunStartup
 */
int tfa2_dev_start_hw(struct tfa2_device *tfa, int profile)
{
    int rc = 0;

    dev_dbg(&tfa->i2c->dev, "%s\n", __FUNCTION__);

    /* load the optimal TFA98XX in HW settings */
    rc = tfa2_dev_init(tfa);
    if (rc < 0)
        return (rc);

    /* I2S settings to define the audio input properties
     *  these must be set before the subsys is up */
    /* this will run the list until a clock dependent item is encountered */
    rc = tfa2_cnt_write_regs_dev(tfa); // write device register settings
    if (rc < 0)
        return rc;

    /* also write register  settings from the default profile
     * NOTE PLL is still off, we set switch sample rate here */
    rc = tfa2_cnt_write_regs_profile(tfa, profile);
    if (rc < 0)
        return rc;

    /* device specific fixes */
    tfa2_init_fix_powerup(tfa);

    /* Go to the initCF state in mute */
    rc = tfa2_dev_set_state(tfa, (enum tfa_state)(TFA_STATE_POWERUP | TFA_STATE_MUTE));
    if (rc < 0)
        return rc;

    rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);
    if (rc < 0)
        return rc;
    dev_dbg(&tfa->i2c->dev, "HW manager state: %d=%s (%s)\n", rc, tfa2_manstate_string[rc], __func__);

    if (rc == 4 || rc == 5)
        msleep_interruptible(2); /* wait for transition states */

    tfa->need_hw_init = 0; /* hw init has been done now */

    return rc;
}

/*
 * start DSP firmware
 *  former: tfaRunSpeakerStartup
 */
int tfa2_dev_load_config(struct tfa2_device *tfa, int profile)
{
    int rc;

    dev_dbg(&tfa->i2c->dev, "%s\n", __FUNCTION__);

    /* write all the files from the device list */
    rc = tfa2_cnt_write_files(tfa);
    if (rc < 0)
    {
        dev_dbg(&tfa->i2c->dev, "[%s] tfa2_cnt_write_files error = %d \n", __FUNCTION__, rc);
        return rc;
    }

    /* write all the files from the profile list (use volumstep 0) */
    rc = tfa2_cnt_write_files_profile(tfa, profile, 0);
    if (rc < 0)
    {
        dev_dbg(&tfa->i2c->dev, "[%s] tfaContWriteFilesProf error = %d \n", __FUNCTION__, rc);
        return rc;
    }

    return rc;
}
/*
 * start CoolFlux DSP subsystem
 *  this will load patch witch may implicitly start the DSP
 *   if no patch is available the DSP is started immediately
 *  former: tfaRunStartDSP
 */
int tfa2_dev_start_cf(struct tfa2_device *tfa)
{
    int rc, clock_ok;
    int data    = 0;
    int control = 1; /*  ACS set*/

    dev_dbg(&tfa->i2c->dev, "%s\n", __FUNCTION__);

    /* clock is needed  */
    clock_ok = rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks);
    if (rc < 0)
        return rc;
    if (!clock_ok)     /* if clock is not running, go back */
        return -EPERM; /* not permitted without clock */

    /* DSP in reset  while initializing */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 1);

    /*  ACS must be set to cold start firmware, keep in reset */
    rc = tfa2_i2c_write_cf_mem32_dsp_reset(tfa->i2c, 0x8100, (int32_t *)&control, 1, TFA2_CF_MEM_IOMEM);
    if (rc < 0)
        return rc;

    /* first handle hapticboost if needed */
    /*  this will load the haptic data and and run recalculation if needed */
    /* check for hb and not ready */
    if (tfa->need_hb_config && !(tfa->need_hb_config & tfa_hb_ready))
    {
        rc = tfa2_dev_start_hapticboost(tfa);
        if (rc < 0)
            return rc;
        tfa->need_hb_config |= tfa_hb_ready; /* ready, don't do it again */
    }

    /* Clear count_boot, reset to 0
     * the DSP reset is released later */
    /* Only for counting firmware soft restarts*/
    rc = tfa2_i2c_write_cf_mem32_dsp_reset(tfa->i2c, 512, (int32_t *)&data, 1, TFA2_CF_MEM_XMEM);
    if (rc < 0)
    { /* any error is fatal so return immediately*/
        return rc;
    }

    /* load all patches from dev list, including main patch */
    rc = tfa2_cnt_write_patches(tfa);

    if (rc < 0)
    { /* patch load is fatal so return immediately*/
        dev_dbg(&tfa->i2c->dev, "patch load failed (%d)\n", rc);
        return rc;
    }

    /* release DSP reset (patch may have done this as well) */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 0);

    /* the framework should be running now */
    tfa->need_cf_init = 0;

    return rc;
}

/*
 * load and activate a speakerboost profile
 *     former : tfaRunSpeakerBoost
 */
int tfa2_dev_start_speakerboost(struct tfa2_device *tfa, int profile)
{
    int rc = 0;

    tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 1);

    /* always a reload when this is called */

    /* Run startup and write all files/messages */
    rc = tfa2_dev_load_config(tfa, profile);
    if (rc < 0)
        return rc;

    /* Save the current profile and set the vstep to 0 */
    /* This needs to be overwriten even in CF bypass */
    tfa2_dev_set_swprofile(tfa, (uint16_t)profile);
    tfa2_dev_set_swvstep(tfa, 0);

    /* load done
     *  tfa->need_sb_config will be cleared when SBSL is cleared to go to operating mode
     */
    tfa->need_sb_config = 0;

    return rc;
}
/*
 * tfa_dev_start : start the audio profile
 */
int tfa2_dev_start(struct tfa2_device *tfa, int next_profile, int vstep)
{
    int rc             = 0;
    int active_profile = -1;
    int have_dsp;
    char *active_profile_name;

    /* Update  init state */
    tfa2_dev_update_config_init(tfa);

    dev_dbg(&tfa->i2c->dev, "%s ", __FUNCTION__);

    dev_dbg(&tfa->i2c->dev, "HW:%s ", tfa->need_hw_init ? "cold" : "warm");
    dev_dbg(&tfa->i2c->dev, "SB:%s ", tfa->need_sb_config ? "cold" : "warm");
    if (tfa->need_hb_config)
    {
        dev_dbg(&tfa->i2c->dev, "HB:%s %s\n", (tfa->need_hb_config & TFA_HB_ROLE_MASK) == tfa_hb_lra ? "lra" : "ls",
                (tfa->need_hb_config & tfa_hb_ready) ? "warm" : "cold"); /* ready is warm */
    }
    else
    {
        dev_dbg(&tfa->i2c->dev, "HB:none\n");
    }

    /* Get currentprofile */
    active_profile = tfa2_dev_get_swprofile(tfa);
    if (active_profile == 0xff)
        active_profile = -1;

    active_profile_name = tfa2_cnt_profile_name(tfa->cnt, tfa->dev_idx, active_profile);

    dev_info(&tfa->i2c->dev, " [SB] active profile:%s, next profile:%s\n",
             active_profile_name ? active_profile_name : "none",
             tfa2_cnt_profile_name(tfa->cnt, tfa->dev_idx, next_profile));

    /* start hardware: init tfa registers and start PLL */
    if (tfa->need_hw_init)
    {
        rc = tfa2_dev_start_hw(tfa, next_profile); /* return muted in initcf state */
        if (rc < 0)
        {
            dev_dbg(&tfa->i2c->dev, "%s : error when starting hardware\n", __FUNCTION__);
            return rc;
        }
    }
    else
    {
        /* start the  clocks */
        rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
        if (rc < 0)
            return rc;
    }

    /* if started without DSP */
    have_dsp = tfa2_dev_cf_enabled(tfa);
    /* start coolflux if needed : not in bypass or any firmware config needed */
    if (tfa->need_cf_init && have_dsp)
    {
        /* start CoolFlux DSP subsystem, will check if clock is there */
        rc = tfa2_dev_start_cf(tfa);
        if (rc < 0)
            return rc;
    }
    /* the framework should be running now */
    /* speakerboost parameters can be loaded */
    if (tfa->need_sb_config && have_dsp)
    {
        rc = tfa2_dev_start_speakerboost(tfa, next_profile);
        if (rc < 0)
            return rc;
    }

    /* Should be operating state if audio clock is present
     *  or in powerdown  if there is no audio clock
     */
    dev_dbg(&tfa->i2c->dev, "HW manager state: %d (%s 1)\n", tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate), __func__);

    active_profile = tfa2_dev_get_swprofile(tfa);

    /* Profile switching */
    if ((next_profile != active_profile && active_profile >= 0))
    {
        rc = tfa2_cnt_write_profile(tfa, next_profile, vstep);
        if (rc < 0)
        {
            dev_err(&tfa->i2c->dev, "%s : error %d returned by write profile\n", __FUNCTION__, rc);
            goto error_exit;
        }
    }

    /* Go to the Operating state */
    rc = tfa2_dev_set_state(tfa, (enum tfa_state)(TFA_STATE_OPERATING | TFA_STATE_MUTE));
    if (rc < 0)
        return rc;

    /* If the profile contains the .standby suffix go to powerdown
     * else we should be in operating state
     */
    if (strstr(tfa2_cnt_profile_name(tfa->cnt, tfa->dev_idx, next_profile), ".standby") != NULL)
    {
        tfa2_dev_set_swprofile(tfa, (unsigned short)next_profile);
        tfa2_dev_set_swvstep(tfa, (unsigned short)tfa->vstep);
        goto error_exit;
    }

    tfa2_dev_set_swprofile(tfa, (unsigned short)next_profile);
    tfa2_dev_set_swvstep(tfa, (unsigned short)tfa->vstep);

error_exit:

    /* close MTP access */
    tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 0);

    dev_dbg(&tfa->i2c->dev, "HW manager state: %d (%s 2)\n", tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate), __func__);

    return rc;
}

int tfa2_dev_stop(struct tfa2_device *tfa)
{
    return tfa2_dev_set_state(tfa, (enum tfa_state)(TFA_STATE_POWERDOWN | TFA_STATE_MUTE));
}

/*
 * set ISTVDDS
 * clear SBSL and ACS (need clock for ACS)
 */
int tfa2_dev_force_cold(struct tfa2_device *tfa)
{
    int rc;
    int cf_control = 1; /* ACS set*/

    dev_dbg(&tfa->i2c->dev, "%s\n", __FUNCTION__);

    tfa->need_hw_init   = -1;
    tfa->need_cf_init   = -1;
    tfa->need_sb_config = -1;
    tfa->need_hb_config = tfa_hb_undetermined;

    tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 0);
    rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
    //	if ( rc < 0 )

    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 1);
    if (rc < 0)
        return rc;
    rc = tfa2_dev_set_state(tfa, TFA_STATE_OSC);
    if (rc < 0)
        return rc;

    if (!tfa->is_probus_device)
    {
        /* set ACS */
        tfa2_i2c_write_cf_mem32_dsp_reset(tfa->i2c, 0x8100, (int32_t *)&cf_control, 1, TFA2_CF_MEM_IOMEM);
    }

    /* Powerdown */
    tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 0);
    rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
    /* set I2CR  */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_I2CR, 1); /*this will also stop the PLL */

    /* toggle IPOVDDS (polarity) to set ISTVDDS */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_IPOVDDS, 0);      /* low */
    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_IPOVDDS, 1); /* high */

    tfa2_dev_update_config_init(tfa);

    return rc;
}
/* small get state functions */
int tfa2_dev_is_fw_cold(struct tfa2_device *tfa)
{
    return tfa->need_sb_config; /* SBSL is not set if config not done */
                                // TODO confirm/test return tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ACS);
}

int tfa2_cf_enabled(struct tfa2_device *tfa)
{
    return tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_CFE);
}
int tfa2_dev_set_configured(struct tfa2_device *tfa)
{
    return tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_SBSL, 1);
}

/**
 * central function to control manager and clock states relevant to driver.
 *
 * TFA_STATE_NONE				not requested, unknown or invalid
 * TFA_STATE_POWERDOWN	PLL in powerdown, Algo is up/warm
 * TFA_STATE_POWERUP			PLL to powerup, Algo can be up/warm
 * TFA_STATE_OPERATING		Amp and Algo running
 * --helper states for MTP and control--
 * TFA_STATE_RESET				I2C reset and ACS set
 * TFA_STATE_INIT_CF				coolflux HW access possible (~initcf)
 * TFA_STATE_OSC					internal oscillator
 * --sticky state modifiers--
 * TFA_STATE_MUTE=0x10	  	 Algo & Amp mute
 * TFA_STATE_UNMUTE=0x20 Algo & Amp unmute
 *
 */
// TODO  determine max poll tims
#define TFA_STATE_INIT_CF_POLL          100
#define TFA_STATE_POWERDOWN_POLL        2000
#define TFA_STATE_OPERATING_POLL        50
#define TFA_STATE_POWERDOWN_HAPTIC_POLL 50

int tfa2_dev_set_state(struct tfa2_device *tfa, enum tfa_state state)
{
    int rc = 0;
    int manstate;
    int ext_clock_wait;

    dev_dbg(&tfa->i2c->dev, "set logical state: %s %s\n", tfa2_state_enum_string[state & 0x0f],
            tfa2_state_mod_enum_string[(state & 0x30) >> 4]);

    /* state modifiers pre */
    if (state & TFA_STATE_MUTE)
    {
        rc = tfa2_dev_mute(tfa, 1);
        if (rc < 0)
            return rc;
    }

    /* Base states */
    rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);
    if (rc < 0)
        return rc;
    manstate = rc;
    rc       = 0;

    dev_dbg(&tfa->i2c->dev, "Current HW manager state: %s \n", tfa2_manstate_string[manstate]);

    switch (state & 0x0f)
    {
        case TFA_STATE_POWERDOWN: /* PLL in powerdown, Algo up */
            if (manstate == 0)    /* done if already there */
            {
                rc = 0;
                break;
            }

            /* device specific fixes */
            rc = tfa2_init_fix_powerdown(tfa, manstate);
            if (rc < 0)
                break;

            rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 1);
            if (rc < 0)
                break;
            tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 0);

            /* wait  for powerdown state */
            rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_manstate, 0, TFA_STATE_POWERDOWN_POLL);

            if (rc == 0)
                tfa2_i2c_write_bf(tfa->i2c, tfa->bf_manaoosc, 0 /*1*/); /* 1 = off */
            else
                dev_err(&tfa->i2c->dev, "Powerdown wait timedout.\n");

            break;
        case TFA_STATE_POWERDOWN_HAPTIC:
            if (manstate == 0) /* done if already there */
            {
                rc = 0;
                break;
            }
            tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_AMPC, 0);
            tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_AMPE, 0);
            tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 0);
            rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 1);
            if (rc < 0)
                break;

            /* wait  for powerdown state */
            rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_manstate, 0, TFA_STATE_POWERDOWN_HAPTIC_POLL);
            if (rc == 0)
                tfa2_i2c_write_bf(tfa->i2c, tfa->bf_manaoosc, 0 /*1*/); /* 1 = off */
            else
                dev_err(&tfa->i2c->dev, "Powerdown wait timedout.\n");

            tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_AMPC, 1);
            break;
        case TFA_STATE_POWERUP: /**< PLL to powerup, Algo can be up/warm */
            /* power on the sub system */
            if (manstate == 9 || manstate == 6) /* done if already there */
            {
                rc = 0;
                break;
            }
            /* powerup osc */
            tfa2_i2c_write_bf(tfa->i2c, tfa->bf_manaoosc, 0); /* 0 = on */
            tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 1);
            rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 0);
            if (rc < 0)
                return rc;

            if (tfa2_dev_cf_enabled(tfa))
                /* if not on internal osc then we wait for external clock */
                ext_clock_wait = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MANCOLD) == 0;
            else
                ext_clock_wait = 1;
            if (ext_clock_wait)
            {
                dev_dbg(&tfa->i2c->dev, "Waiting for external clock ...\n");
            }
            else
            {
                dev_dbg(&tfa->i2c->dev, "Waiting for clock stable...\n");
                rc = tfa2_dev_clock_stable_wait(tfa);
            }
            break;
        case TFA_STATE_CLOCK: /**< always return with clock, use OSC if no external clock  */
            /* power on the sub system */
            if (tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks) == 1) /* done if already there */
            {
                rc = 0;
                break;
            }

            /* no immediate clock needed if no DSP, just powerup */
            if (!tfa2_dev_cf_enabled(tfa))
            {
                rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
                break;
            }
            /* go the wait_for_source_settings_state for checking NOCLK
             * this will tell if the external clock is active or not
             */
            tfa2_i2c_write_bf(tfa->i2c, tfa->bf_manaoosc, 0); /* 0 = on */
            /* stay in  wait_for_source_settings */
            tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_MANSCONF, 0);
            /* goto wait_for_source_settings */
            tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 0);

            /* if NOCLK then we wait for external clock */
            if (tfa2_i2c_read_bf(tfa->i2c, tfa->bf_noclk) == 1)
            { /* use the oscillator */
                rc = tfa2_dev_set_state(tfa, TFA_STATE_OSC);
                if (rc < 0)
                    break;
            }
            else
            { /* normal power up on external clock */
                rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
                if (rc < 0)
                    break;
            }
            /* in this case we always need a clock, fail if not ready */
            rc = tfa2_dev_clock_stable_wait(tfa);
            break;
        case TFA_STATE_OPERATING: /* Amp and Algo running */
            if (manstate == 9)    /* done if already there */
            {
                rc = 0;
                break;
            }

            ext_clock_wait = 0;
            /* restart if on internal clock */
            if (manstate == 6)
            {
                tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 1);
                tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_PWDN, 0);
                ext_clock_wait = 1;
            }
            /* powerup first if off or coming from initcf */
            rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
            if (rc < 0)
                break;

            /* if in wait2srcsetting and mansconf is done then we wait for external clock */
            if (manstate == 1)
            {
                ext_clock_wait =
                    tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MANSCONF) && tfa2_i2c_read_bf(tfa->i2c, tfa->bf_noclk);
            }

            if (tfa2_dev_cf_enabled(tfa))
            {
                /* set SBSL to go to operating */
                rc = tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_SBSL, 1);

                /* if calibration once is in progress wait to allow CF to write MTP */
                if (tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ACS) == 0 && /* warm */
                    tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPOTC) == 1)
                {                       /* once */
                    int count = 50 * 4; /* Calibration takes ~500mS */
                    while ((tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPEX) != 1) && count)
                    {
                        msleep_interruptible(10);
                        count--;
                    }
                    if (!count)
                    {
                        pr_err("Calibration once timed out\n");
                        rc = -ETIME;
                    }
                }
                /* only wait for operating if we are not on internal clock
                 * and not waiting for external clock
                 * external clock may not be running yet */
                if (ext_clock_wait == 0)
                    rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_manstate, 9, TFA_STATE_OPERATING_POLL);
            }
            break;
        case TFA_STATE_RESET: /* I2C reset and sbls  set */
            /* goes to powerdown first */
            rc = tfa2_dev_force_cold(tfa);
            break;
        case TFA_STATE_INIT_CF: /**< coolflux HW access possible (~initcf) */
            /* init_cf is mainly used for MTP manual copy */
            if (manstate == 6) /* done if already there */
            {
                rc = 0;
                break;
            }
            /* if SBSL is 0, we'll be in init_cf after powerup */
            rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
            if (rc < 0)
                break;
            tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_SBSL, 0);
            rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
            if (rc < 0)
            { /* restore SBSL back to 1 on failure here */
                if (tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ACS) == 0)
                    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_SBSL, 1);
                rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
                break;
            }
            rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_manstate, 6, TFA_STATE_INIT_CF_POLL);
            break;
        case TFA_STATE_OSC: /* run on internal oscillator, in init_cf */
            rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
            if (rc < 0)
                break;
            if (tfa2_dev_cf_enabled(tfa))
            {
                tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MANCOLD, 1);
                tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_SBSL, 0);
            }
            /* will poll until clock ready */
            rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERUP);
            break;
        case TFA_STATE_NONE: /* nothing */
            break;
        default:
            if (state & 0x0f)
                rc = -EINVAL;
            break;
    }

    /* state modifiers post */
    if (state & TFA_STATE_UNMUTE)
    {
        /* only update return code in case rc was 0 */
        rc = (rc == 0) ? tfa2_dev_mute(tfa, 0) : rc;
    }

    if (rc == 0 && state != TFA_STATE_NONE)
        tfa->state = state;

    //	dev_dbg(&tfa->i2c->dev, "done logical state: %s\n",
    //			tfa2_state_enum_string[tfa->state & 0x0f]);

    return rc;
}

/*
 * bring the device into a state similar to reset
 */
int tfa2_dev_init(struct tfa2_device *tfa)
{
    int error;
    uint16_t value = 0;

    /* reset all i2C registers to default
     *  Write the register directly to avoid the read in the bitfield function.
     *  The I2CR bit may overwrite the full register because it is reset anyway.
     */
    tfa2_i2c_set_bf_value(TFA9XXX_BF_I2CR, 1, &value); /* This will save an i2c reg read */
    error = tfa2_i2c_write_reg(tfa->i2c, TFA9XXX_BF_I2CR, value);
    if (error)
        return error;
    /* Put DSP in reset */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_RST, 1); // TODO remove?

    /* some other registers must be set for optimal amplifier behaviour
     * This is implemented in a file specific for the type number
     */
    if (tfa->tfa_init)
        error = (tfa->tfa_init)(tfa);
    else
        return -ENODEV;

    /* clear so next  time no init */
    error = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_ICLVDDS, 1);
    if (error)
        return error;

    return error;
}

int tfa2_dev_mute(struct tfa2_device *tfa, int state)
{
    if (tfa->is_probus_device == 1)
    {
        dev_dbg(&tfa->i2c->dev, "no DSP %smute for Probus device\n", state ? "" : "un");
        return 0;
    }

    dev_dbg(&tfa->i2c->dev, "DSP %smute\n", state ? "" : "un");
    return tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CFSM, state);
}

/*
 * the register will always start counting @1 because the reset value==0
 */
int tfa2_dev_set_swprofile(struct tfa2_device *tfa, unsigned short new_value)
{
    int active_value = tfa2_dev_get_swprofile(tfa);

    /* Set the new value in the struct */
    tfa->profile = new_value;

    /* Set the new value in the hw register */
    tfa2_i2c_write_bf_volatile(tfa->i2c, tfa->bf_swprofil, new_value + 1);

    return active_value;
}

int tfa2_dev_get_swprofile(struct tfa2_device *tfa)
{
    return tfa2_i2c_read_bf(tfa->i2c, tfa->bf_swprofil) - 1;
}

/*
 * the register will always start counting @1 because the reset value==0
 */
int tfa2_dev_set_swvstep(struct tfa2_device *tfa, unsigned short new_value)
{
    /* Set the new value in the struct */
    tfa->vstep = new_value;

    /* Set the new value in the hw register */
    tfa2_i2c_write_bf_volatile(tfa->i2c, tfa->bf_swvstep, new_value + 1);

    return new_value;
}
int tfa2_dev_get_swvstep(struct tfa2_device *tfa)
{
    return tfa2_i2c_read_bf(tfa->i2c, tfa->bf_swvstep) - 1;
}

/*
 * update the struct for hw and fw init fields
 *  if no DSP need_sb_config can be skipped
 */
int tfa2_dev_update_config_init(struct tfa2_device *tfa)
{
    int rc = 0;
    int cf_enabled;

    rc = tfa2_dev_cf_enabled(tfa);
    if (rc < 0)
        return rc;
    cf_enabled = rc;

    /* tfa->need_hw_init :returns 1 when tfa  is "cold" and 0 when device is warm */
    if (cf_enabled)
    {
        tfa->need_hw_init   = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ACS);
        tfa->need_cf_init   = tfa->need_hw_init;
        tfa->need_sb_config = tfa->need_hw_init;
    }
    else
    {
        tfa->need_hw_init   = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ISTVDDS);
        tfa->need_cf_init   = 0;
        tfa->need_sb_config = 0; // this may be needed in case of in-kernel messaging
    }

    /* haptic boost configs relies on profile names: LRA, speaker or none */
    if (tfa->need_hb_config == tfa_hb_undetermined)
    {
        /* if we have lra_ profile prefixes we have the lra */
        if (tfa2_cnt_grep_profile_name(tfa->cnt, tfa->dev_idx, "lra_") >= 0)
            tfa->need_hb_config = tfa_hb_lra;
        else if (tfa2_cnt_grep_profile_name(tfa->cnt, tfa->dev_idx, "ls_") >= 0)
            tfa->need_hb_config = tfa_hb_ls;
        else
            tfa->need_hb_config = tfa_hb_none;
    }

    return 0;
}

int tfa2_dev_faim_protect(struct tfa2_device *tfa, int state)
{
    /* 0b = FAIM protection enabled:default  1b = FAIM protection disabled */
    return tfa2_i2c_write_bf_volatile(tfa->i2c, tfa->bf_openmtp, (uint16_t)(state));
}

int tfa2_dev_dsp_system_stable(struct tfa2_device *tfa, int *ready)
{
    int rc;

    if (tfa->reg_time)
    {
        /* extra wait delay */
        int loop = tfa->reg_time;
        do
        {
            tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks); /* dummy read */
        } while (loop--);
    }
    /* read CLKS: ready if set */
    rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "I2C fails when read clks!\n");
    }
    else
    {
        *ready = rc;
    }

    return rc;
}

#define TFA_CLKS_POLL 50
int tfa2_dev_clock_stable_wait(struct tfa2_device *tfa)
{
    return tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_clks, 1, TFA_CLKS_POLL);
}

int tfa2_dev_cf_enabled(struct tfa2_device *tfa)
{
    int value;

    if (tfa->is_probus_device)
    { /* probus has no CFE bit */
        value = 0;
    }
    else
    {
        value = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_CFE);
    }

    return value;
}

#define FW_PATCH_HEADER_LENGTH 6
int tfa2_dev_dsp_patch(struct tfa2_device *tfa, int patchLength, const uint8_t *patchBytes)
{
    int rc;

    if (tfa->in_use == 0)
        return -EPERM;

    // TODO add low level test?
    //	rc = tfa2_check_patch(patchBytes+6,patchLength-6, tfa->rev );
    //	if ( rc < 0 )
    //		return rc;

    rc = tfa2_process_patch_file(tfa->i2c, patchLength - FW_PATCH_HEADER_LENGTH, patchBytes + FW_PATCH_HEADER_LENGTH);

    return rc;
}
/****************************** DSP RPC ************************************/
#define TFA98XX_WAITRESULT_NTRIES      40
#define TFA98XX_WAITRESULT_NTRIES_LONG 2000
/** Value used by tfa_dsp_msg_status() to determine busy-wait time for DSP message acknowledgement*/
#define CF_RPC_RETRY_NUM      16 /*  wait loop count */
#define CF_STATUS_I2C_CMD_ACK 0x01

/* dsp RPC message for I2C */
int tfa2_i2c_rpc_write(struct i2c_client *i2c, int length, const char *buffer)
{
    int rc;
    uint16_t cfctl;
    int cfctl_reg = (TFA9XXX_BF_DMEM >> 8) & 0xff; /* where DMEM is */

    /* write the RPC message to the i2c buffer @xmem[1] */
    rc = tfa2_i2c_write_cf_mem24(i2c, 1, (uint8_t *)buffer, length, TFA2_CF_MEM_XMEM);

    rc = tfa2_i2c_read_reg(i2c, cfctl_reg); /* will report error */
    if (rc < 0)
        return rc;
    cfctl = (uint16_t)rc;

    /* notify the DSP */

    /* cf_int=0, cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
    /* set the cf_req1 and cf_int bit */
    tfa2_i2c_set_bf_value(TFA9XXX_BF_REQCMD, 0x01, &cfctl); /* REQ bit 0 */
    tfa2_i2c_set_bf_value(TFA9XXX_BF_CFINT, 1, &cfctl);
    rc = tfa2_i2c_write_reg(i2c, cfctl_reg, cfctl);

    return rc;
}

int tfa2_i2c_rpc_status(struct i2c_client *i2c, int *pRpcStatus)
{
    int rc;                 /* return value */
    unsigned retry_cnt = 0; /* Retry counter for ACK busy-wait */
    uint16_t cf_status = 0;
    uint8_t xmem0[4];

    /* Set RPC result initially to tfa9xxx_no_dsp_response. In case we have comm. problems */

    /* Start waiting for DSP response */
    while (retry_cnt < CF_RPC_RETRY_NUM)
    {
        rc = tfa2_i2c_read_bf(i2c, TFA9XXX_BF_ACKCMD);
        if (rc < 0)
            return rc;
        cf_status = (uint16_t)rc; /* ret contains flags, when no error */

        if ((cf_status & CF_STATUS_I2C_CMD_ACK))
            break; /* There is no error and DSP already ACK-ed message */
        retry_cnt++;
    }
    // TODO check more status ACK
    /* If DSP timed out on giving response */
    if ((retry_cnt >= CF_RPC_RETRY_NUM) && !(cf_status & CF_STATUS_I2C_CMD_ACK))
    {
        /* Set RPC result initially to tfa9xxx_no_dsp_response. In case we have comm. problems */
        *pRpcStatus = tfa9xxx_no_dsp_response; // TODO no_dsp_response is misleading, should be error response
        rc          = -ENXIO;
    }
    else
    {
        /* Get  DSP status (could be busy, RPC error or OK) */
        rc          = tfa2_i2c_read_cf_mem24(i2c, 0, xmem0, 3, TFA2_CF_MEM_XMEM);
        *pRpcStatus = xmem0[2]; /* result is high byte in big endian */
    }

    return rc;
}

/*****************************************************************************
 *
 * 	      I2C level functions
 */

/*
 * poll for the bf until value or loopcount exhaust return timeout
 */
int tfa2_i2c_bf_poll(struct i2c_client *client, uint16_t bf, uint16_t wait_value, int loop)
{
    // TODO use tfa->reg_time;
    int value, rc;
    int loop_arg = loop;

    /* @400k take 500uS/cycle : wait 500ms first */
    if (loop > 1000)
    {
        loop -= 1000;
        msleep_interruptible(500);
    }
    do
        value = tfa2_i2c_read_bf(client, bf); /* read */
    while (value != wait_value && --loop);

    rc = loop ? 0 : -ETIME;

    if (rc == -ETIME)
        dev_err(&client->dev, "timeout waiting for bitfield:0x%04x, value:%d, %d times\n", bf, wait_value, loop_arg);

    return rc;
}

int tfa2_i2c_dsp_init(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len)
{
    (void)tfa;
    (void)cmd_buf;
    (void)cmd_len;

    return 0;
}

int tfa2_i2c_dsp_execute(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len)
{
    struct i2c_client *i2c = tfa->i2c;
    int rc;
    int tries, rpc_status = -1;

    if (cmd_len)
    {
        /* Write the message and notify the DSP */
        rc = tfa2_i2c_rpc_write(i2c, cmd_len, cmd_buf);
        if (rc)
            return rc;
    }

    /* Get the result from the DSP (polling) */
    for (tries = TFA98XX_WAITRESULT_NTRIES; tries > 0; tries--)
    {
        rc = tfa2_i2c_rpc_status(i2c, &rpc_status);
        if (rc || rpc_status != tfa9xxx_I2C_Req_Busy)
            break; /* Return on I/O error or error status from DSP */

        msleep_interruptible(1); /* Add non-busy wait to give DSP processing time */
    }

    if (rpc_status != tfa9xxx_I2C_Req_Done)
    {
        /* DSP RPC call returned an error  */
        dev_dbg(&i2c->dev, "DSP msg status: %d (%s)\n", rpc_status, tfa2_get_i2c_status_id_string(rpc_status));
        /* return rc; */
    }

    /* if a result is requested get it now */
    if (res_len > 0)
    {
        /* put the result from xmem[0] at the beginning */
        *res_buf++ = rpc_status >> 16;
        *res_buf++ = rpc_status >> 8;
        *res_buf++ = rpc_status;
        res_len -= 3;

        /* get the rest */
        if (res_len > 0)
            rc = tfa2_i2c_read_cf_mem24(i2c, 1, (uint8_t *)res_buf, res_len, TFA2_CF_MEM_XMEM);
        else
            rc = 0;
    }

    return rc;
}

int tfa2_dsp_init(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len)
{
    return tfa->dsp_init(tfa, cmd_buf, cmd_len);
}

/*
 * the dsp execute funtion will execute the RPC message in the cmd_buf and return the result
 */
int tfa2_dsp_execute(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len)
{
    return tfa->dsp_execute(tfa, cmd_buf, cmd_len, res_buf, res_len);
}

int tfa2_get_noclk(struct tfa2_device *tfa)
{
    return tfa2_i2c_read_bf(tfa->i2c, tfa->bf_noclk);
}

/******************************************************************************
 * i2c and register  functions
 */
/*
 * tfa_ functions copied from tfa_dsp.c
 */
uint16_t tfa2_i2c_get_bf_value(const uint16_t bf, const uint16_t reg_value)
{
    uint16_t msk, value;

    /*
     * bitfield enum:
     * - 0..3  : len
     * - 4..7  : pos
     * - 8..15 : address
     */
    uint8_t len = bf & 0x0f;
    uint8_t pos = (bf >> 4) & 0x0f;

    msk   = ((1 << (len + 1)) - 1) << pos;
    value = (reg_value & msk) >> pos;

    return value;
}

int tfa2_i2c_set_bf_value(const uint16_t bf, const uint16_t bf_value, uint16_t *p_reg_value)
{
    uint16_t value, regvalue, msk;

    /*
     * bitfield enum:
     * - 0..3  : len
     * - 4..7  : pos
     * - 8..15 : address
     */
    uint8_t len = bf & 0x0f;
    uint8_t pos = (bf >> 4) & 0x0f;

    regvalue = *p_reg_value;

    msk   = ((1 << (len + 1)) - 1) << pos;
    value = bf_value << pos;
    value &= msk;
    regvalue &= ~msk;
    regvalue |= value;

    *p_reg_value = regvalue;

    return 0;
}

int tfa2_i2c_read_reg(struct i2c_client *client, uint8_t reg)
{
    int rc;
    uint16_t value;
    uint8_t buffer[2];

    rc = tfa2_i2c_write_read_raw(client, 1, &reg, 2, buffer);
    if (rc < 0)
    {
        dev_err(&client->dev, "i2c reg read for 0x%x failed\n", reg);
        return rc;
    }
    else
    {
        value = (buffer[0] << 8) | buffer[1];
    }

    return value;
}

int tfa2_i2c_write_reg(struct i2c_client *client, uint8_t reg, uint16_t val)
{
    int rc;
    uint8_t buffer[3];

    buffer[0] = reg;
    buffer[1] = val >> 8;
    buffer[2] = val;

    rc = tfa2_i2c_write_raw(client, 3, buffer);

    if (rc < 0)
    {
        dev_err(&client->dev, "i2c reg write for 0x%x failed\n", reg);
    }

    return rc;
}

int tfa2_i2c_read_regs(struct i2c_client *i2c, uint8_t addr, int nr, uint16_t *regs)
{
    int rc, i;
    uint8_t *buffer;

    buffer = kmalloc(2 * nr, GFP_KERNEL);
    if (!buffer)
        return -ENOMEM;

    rc = tfa2_i2c_write_read_raw(i2c, 1, &addr, 2 * nr, buffer);
    if (rc < 0)
    {
        dev_err(&i2c->dev, "i2c reg read for 0x%x failed\n", addr);
        goto error;
    }

    for (i = 0; i < nr; i++)
    {
        regs[i] = (buffer[i * 2] << 8) | buffer[i * 2 + 1];
    }

error:
    kfree(buffer);

    return rc;
}

int tfa2_i2c_read_bf(struct i2c_client *client, uint16_t bitfield)
{
    uint8_t reg = (bitfield >> 8) & 0xff; /* extract register addess */
    uint16_t value;
    int rc;

    rc = tfa2_i2c_read_reg(client, reg);
    if (rc < 0)
        return rc;
    value = (uint16_t)rc;

    return tfa2_i2c_get_bf_value(bitfield, value); /* extract the value */
}

static int tfa2_i2c_write_bf_internal(struct i2c_client *client, uint16_t bitfield, uint16_t value, int write_always)
{
    int rc;
    uint16_t newvalue, oldvalue;
    uint8_t address;

    /*
     * bitfield enum:
     * - 0..3  : len-1
     * - 4..7  : pos
     * - 8..15 : address
     */
    address = (bitfield >> 8) & 0xff;

    rc = tfa2_i2c_read_reg(client, address); /* will report error */
    if (rc < 0)
        return rc;
    oldvalue = (uint16_t)rc;
    newvalue = oldvalue;
    tfa2_i2c_set_bf_value(bitfield, value, &newvalue);

    /* Only write when the current register value is not the same as the new value */
    if (write_always || (oldvalue != newvalue))
        return tfa2_i2c_write_reg(client, (bitfield >> 8) & 0xff, newvalue);
    return 0;
}

void tfa2_i2c_unlock(struct i2c_client *client)
{
    uint16_t value, xor;

    /* Unlock keys */
    tfa2_i2c_write_reg(client, 0x0F, 0x5A6B);
    value = tfa2_i2c_read_reg(client, 0xFB);
    xor   = value ^ 0x005A;
    tfa2_i2c_write_reg(client, 0xA0, xor);
}

int tfa2_i2c_write_bf(struct i2c_client *client, uint16_t bitfield, uint16_t value)
{
    return tfa2_i2c_write_bf_internal(client, bitfield, value, 0);
}

int tfa2_i2c_write_bf_volatile(struct i2c_client *client, uint16_t bitfield, uint16_t value)
{
    return tfa2_i2c_write_bf_internal(client, bitfield, value, 1);
}

/******************************************************************************
 * DSP related  functions
 */
/**
 *  @brief convert 24 bit BE DSP messages to a 32 bit signed LE integer
 *
 *  The input is sign extended to 32-bit from 24-bit.
 *
 *  @param data32 output 32 bit signed LE integer buffer
 *  @param data24 input 24 bit BE buffer
 *  @param length_bytes24 bytes in 24 bit BE buffer
 *  @return total nr of bytes in the result
 */
int tfa2_24_to_32(int32_t *data32, uint8_t *data24, int length_bytes24)
{
    int i, idx = 0;

    for (i = 0; i < length_bytes24; i += 3)
    {
        int tmp = ((uint8_t)data24[i] << 16) + ((uint8_t)data24[i + 1] << 8) + (uint8_t)data24[i + 2];
        /* Sign extend to 32-bit from 24-bit */
        data32[idx++] = ((int32_t)tmp << 8) >> 8;
    }
    return idx;
}

/**
 *   @brief  truncate 32 bit  integer buffer  to 24 bit BE
 *
 *   The input is truncated by chopping the highest byte.
 *  @param data24 output 24 bit BE buffer
 *  @param data32 input 32 bit signed LE integer buffer
 *  @param length_words32 number of words in 32bit  buffer
 *  @return total nr of bytes in the result
 */
int tfa2_32_to_24(uint8_t *data24, int32_t *data32, int length_words32)
{
    int i, idx = 0;

    for (i = 0; i < length_words32; i++)
    {
        uint8_t *buf8 = (uint8_t *)&data32[i];
        data24[idx++] = buf8[2];
        data24[idx++] = buf8[1];
        data24[idx++] = buf8[0];
    }
    return idx;
}

enum tfa2_cf_flags
{
    convert   = 1,
    dsp_reset = 2,
};

/* implement functionality for tfa2_i2c_write_cf_mem24() and tfa2_i2c_write_cf_mem32() */
static int write_cf_mem(struct i2c_client *client,
                        uint16_t address,
                        int32_t *input,
                        int size,
                        enum tfa2_cf_mem type,
                        enum tfa2_cf_flags flags)
{
    int idx = 0;
    uint8_t *output;
    int rc;

    output = kmalloc(5 + size * 3, GFP_KERNEL);
    if (!output)
        return -ENOMEM;

    output[idx++] = 0x90; /* CF_CONTROLS */
    output[idx++] = 0x00;
    if (flags & dsp_reset)
    {
        output[idx++] = (type << 1) | 1; /* AIF:0 (ON) DMEM:1 (xmem) RST:1 */
    }
    else
    {
        output[idx++] = (type << 1); /* AIF:0 (ON) DMEM:1 (xmem) RST:0 */
    }
    output[idx++] = (address >> 8) & 0xff;
    output[idx++] = address & 0xff;

    if (flags & convert)
    {
        idx += tfa2_32_to_24(&output[idx], input, size);
    }
    else
    {
        memcpy(&output[idx], input, size * 3);
        idx += size * 3;
    }

    rc = tfa2_i2c_write_raw(client, idx, output);
    if (rc < 0)
    {
        dev_err(&client->dev, "%s  failed\n", __FUNCTION__);
    }

    kfree(output);

    return rc;
}

int tfa2_i2c_write_cf_mem24(
    struct i2c_client *client, uint16_t address, uint8_t *input, int size, enum tfa2_cf_mem type)
{
    return write_cf_mem(client, address, (int32_t *)input, size / 3, type, (enum tfa2_cf_flags)0);
}

int tfa2_i2c_write_cf_mem32(
    struct i2c_client *client, uint16_t address, int32_t *input, int size, enum tfa2_cf_mem type)
{
    return write_cf_mem(client, address, input, size, type, convert);
}

int tfa2_i2c_write_cf_mem32_dsp_reset(
    struct i2c_client *client, uint16_t address, int32_t *data, int size, enum tfa2_cf_mem type)
{
    return write_cf_mem(client, address, data, size, type, (enum tfa2_cf_flags)(convert | dsp_reset));
}

/* implement functionality for tfa2_i2c_read_cf_mem24() and tfa2_i2c_read_cf_mem32() */
static int read_cf_mem(
    struct i2c_client *client, uint16_t address, int *data, int size, enum tfa2_cf_mem type, enum tfa2_cf_flags flags)
{
    int rc;
    uint8_t output[5];
    uint8_t *data24;

    data24 = kmalloc(size * 3, GFP_KERNEL);
    if (!data24)
        return -ENOMEM;

    output[0] = 0x90; /* CF_CONTROLS */
    output[1] = 0x00;
    if (flags & dsp_reset)
    {
        output[2] = (type << 1) | 1; /* AIF:0 (ON) DMEM:1 (xmem) RST:1 */
    }
    else
    {
        output[2] = (type << 1); /* AIF:0 (ON) DMEM:1 (xmem) RST:0 */
    }
    output[3] = (address >> 8) & 0xff;
    output[4] = address & 0xff;
    rc        = tfa2_i2c_write_read_raw(client, 5, output, size * 3, data24);
    if (rc < 0)
        goto error;

    if (flags & convert)
    {
        tfa2_24_to_32((int32_t *)data, data24, size * 3);
    }
    else
    {
        memcpy(data, data24, size * 3);
    }
error:
    kfree(data24);

    if (rc < 0)
    {
        dev_err(&client->dev, "%s  failed\n", __FUNCTION__);
    }

    return rc;
}

int tfa2_i2c_read_cf_mem24(struct i2c_client *client, uint16_t address, uint8_t *data, int size, enum tfa2_cf_mem type)
{
    return read_cf_mem(client, address, (int *)data, size / 3, type, (enum tfa2_cf_flags)0);
}

int tfa2_i2c_read_cf_mem32(struct i2c_client *client, uint16_t address, int *data, int size, enum tfa2_cf_mem type)
{
    return read_cf_mem(client, address, data, size, type, convert);
}

int tfa2_i2c_read_cf_mem32_dsp_reset(
    struct i2c_client *client, uint16_t address, int *data, int size, enum tfa2_cf_mem type)
{
    return read_cf_mem(client, address, data, size, type, (enum tfa2_cf_flags)(convert | dsp_reset));
}

/****************************** calibration support **************************/

/***** mtp manual write/auto read *************/
int tfa2_dev_mtp_busy(struct tfa2_device *tfa)
{
    int rc;
    int count = 0;
    msleep_interruptible(20); // TODO address sleeptime
    while (count < 10)
    {
        msleep_interruptible(10);
        rc = tfa2_i2c_bf_poll(tfa->i2c, tfa->bf_mtpb, 0, 100); // TODO mtpbusy max poll time
        count++;
    }

    if (rc < 0)
        dev_err(&tfa->i2c->dev, "MTP busy poll timed out\n");
    else
        dev_dbg(&tfa->i2c->dev, "MTP not busy eventually\n");

    return rc;
}
/************************************************************************/
/**
 *  Function MTP_UpdateI2C.
 *
 *           Read all the I2C 'volatile' registers from MTP bank.
 *
 *  @param   [in] wait : .
 *  @return  .
 */
/************************************************************************/

int tfa2_dev_mtp_to_i2c(struct tfa2_device *tfa)
{
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CMTPI, 1);
    return tfa2_dev_mtp_busy(tfa);
}

/************************************************************************/
/**
 *  Function MTP_ReadPair.
 *
 *           Read a pair of words from MTP.
 *
 *  @param   [in] mtp_address   : MTP address where to read from 0
 *                            ( range from to 15 ).
 *  @param   [out] mtp_data : Content of the MTP's at requested address.
 *  @return
 */
/************************************************************************/

int tfa2_dev_mtp_readpair(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_data[2])
{
    int rc;

    /* Program the address */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MTPADDR, mtp_address >> 1);
    //	msleep_interruptible(50);
    /* Launch the copy from MTP */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MANCMTPI, 1);
    rc = tfa2_dev_mtp_busy(tfa);
    if (rc < 0)
        return rc;
    mtp_data[0] = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPRDLSB);
    mtp_data[1] = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPRDMSB);
    dev_dbg(&tfa->i2c->dev, "%s  MTP[%d]: 0x%04x 0x%04x\n", __func__, mtp_address & 0x0f, mtp_data[1], mtp_data[0]);

    return 0;
}

/************************************************************************/
/**
 *  Function MTP_Read.
 *
 *           Read one word from MTP.
 *
 *  @param   [in] mtp_address : MTP address where to read from
 *                           ( range from 0 to 15 ).
 *  @return  Content of the MTP at requested address.
 */
/************************************************************************/

int tfa2_dev_mtp_read(struct tfa2_device *tfa, uint16_t mtp_address)
{
    uint16_t mtp_data[2];

    tfa2_dev_mtp_readpair(tfa, mtp_address, mtp_data);
    return mtp_data[mtp_address & 0x1];
}

/************************************************************************/
/**
 *  Function MTP_WritePair.
 *
 *           Write a pair of words to MTP.
 *
 *  @param   [in] mtp_address  : MTP Address where to write to
 *                           ( range from 0 to 15 ).
 *  @param   [in] mtp_data : Data to be written.
 *  @return  .
 */
/************************************************************************/

int tfa2_dev_mtp_writepair(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_data[2])
{
    int rc;

    /* Program the address */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MTPADDR, mtp_address >> 1);
    /* Program the data */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MTPWRLSB, mtp_data[0]);
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MTPWRMSB, mtp_data[1]);
    //	msleep_interruptible(50);
    /* Launch the copy to MTP */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_MANCIMTP, 1);
    rc = tfa2_dev_mtp_busy(tfa);
    if (rc < 0)
        return rc;

    dev_dbg(&tfa->i2c->dev, "%s MTP[%d]: 0x%04x 0x%04x\n", __func__, mtp_address & 0x0f, mtp_data[1], mtp_data[0]);

    return tfa2_dev_mtp_to_i2c(tfa);
}

/************************************************************************/
/**
 *  Function MTP_Write.
 *
 *           Write one word to MTP.
 *
 *  @param   [in] mtp_address   : MTP Address where to write to
 *                            ( range from 0  to 15 ).
 *  @param   [in] mtp_value : Data to be written.
 *  @return  .
 */
/************************************************************************/

int tfa2_dev_mtp_write(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_value)
{
    uint16_t mtp_data[2];
    int rc;

    /* Program the address */
    rc = tfa2_dev_mtp_readpair(tfa, mtp_address, mtp_data);
    if (rc < 0)
        return rc; /* Program the data */
    mtp_data[mtp_address & 0x1] = mtp_value;
    /* Launch the copy to MTP */
    return tfa2_dev_mtp_writepair(tfa, mtp_address, mtp_data);
}

/************************************************************************/

/*
 * get/set the mtp with user controllable values
 *
 *  check if the relevant clocks are available
 */
static int get_mtp(struct tfa2_device *tfa, uint16_t addr, uint16_t *value)
{
    int rc;
    struct i2c_client *i2c = tfa->i2c;

    rc = tfa2_dev_clock_stable_wait(tfa);
    if (rc < 0)
    {
        dev_err(&i2c->dev, "no clock\n");
        return rc;
    }

    rc = tfa2_i2c_read_reg(i2c, addr);
    if (rc < 0)
    {
        dev_err(&i2c->dev, "error reading MTP (0x%x)\n", addr);
        return rc;
    }
    *value = (uint16_t)rc;

    return rc;
}

/*
 * lock or unlock KEY2
 *  lock = 1 will lock
 *  lock = 0 will unlock
 *
 *  note that on return all the hidden key will be off
 */
int tfa2_i2c_hap_key2(struct i2c_client *i2c, int lock)
{
    int rc;
    uint16_t addr = (TFA9XXX_BF_MTPK >> 8) & 0xff;

    /* unhide lock registers */
    rc = tfa2_i2c_write_reg(i2c, 0x0F, 0x5A6B);
    if (rc < 0)
        return -EIO;
    /* lock/unlock key2 MTPK */
    if (lock)
    {
        rc = tfa2_i2c_write_reg(i2c, addr, 0); /* lock */
        if (rc < 0)
            return -EIO;
        /* hide lock registers */
        rc = tfa2_i2c_write_reg(i2c, 0x0F, 0);
        if (rc < 0)
            return -EIO;
    }
    else
    {
        rc = tfa2_i2c_write_reg(i2c, addr, 0x5A); /* unlock */
        if (rc < 0)
            return -EIO;
    }

    return 0;
}

static int mtp_open(struct tfa2_device *tfa, int state)
{
    /* FAIM protection */
    dev_dbg(&tfa->i2c->dev, "MTP %s\n", state ? "enabled" : "disabled");
    return tfa2_i2c_write_bf(tfa->i2c, tfa->bf_openmtp, state);
}

static int set_mtp(struct tfa2_device *tfa, uint16_t bf, uint16_t value)
{
    uint16_t mtp_old, mtp_new, mtp_value;
    int rc;
    int save_state;

    /*
     * bitfield enum:
     * - 0..3  : len
     * - 4..7  : pos
     * - 8..15 : address
     */
    uint8_t len  = bf & 0x0f;
    uint8_t pos  = (bf >> 4) & 0x0f;
    uint8_t addr = (bf >> 8) & 0xff;
    uint16_t msk = ((1 << (len + 1)) - 1) << pos;

    /* execute the MTP writes in init_cf state */
    save_state = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);

    /* Go to the initCF state in mute */
    rc = tfa2_dev_set_state(tfa, TFA_STATE_INIT_CF);
    if (rc < 0)
        return rc;

    /* open mtp */
    rc = mtp_open(tfa, 1);
    if (rc < 0)
    {
        return rc;
    }

    rc = get_mtp(tfa, addr, &mtp_old);
    if (rc < 0)
        return rc;

    mtp_value = value << pos;
    mtp_new   = (mtp_value & msk) | (mtp_old & ~msk);

    if (mtp_old == mtp_new)
    { /* no change */
        dev_dbg(&tfa->i2c->dev, "MTP 0x%02x: no change\n", addr);
        goto restore_state;
    }

    dev_dbg(&tfa->i2c->dev, "MTP 0x%02x: writing 0x%x\n", addr, mtp_new);

    /* do the write */
    rc = tfa2_init_mtp_write_wrapper(tfa, addr, mtp_new, tfa2_dev_mtp_write);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "error writing MTP: 0x%02x 0x%04x\n", addr, mtp_new);
    }

restore_state:
    /* close mtp */
    rc = mtp_open(tfa, 0);
    if (rc < 0)
    {
        dev_err(&tfa->i2c->dev, "not able to enable protection\n");
        return rc;
    }

    /* restore state  */
    rc = tfa2_dev_set_state(tfa, (save_state == 6) ? TFA_STATE_INIT_CF : TFA_STATE_POWERDOWN);
    if (rc < 0)
        return rc;
    return 0;
}

/* will return EIO error if no clock */
int tfa2_dev_mtp_get(struct tfa2_device *tfa, enum tfa_mtp item)
{
    int rc, clock;

    clock = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks);
    if (!clock)
    {
        rc = tfa2_dev_set_state(tfa, TFA_STATE_OSC);
        if (rc < 0)
            return rc;
    }

    /* copy MTP to I2C shadow regs */
    tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CMTPI, 1);

    /* return error if there is no clock */
    if (tfa2_i2c_read_bf(tfa->i2c, tfa->bf_clks) == 0)
        return -EIO;

    rc = tfa2_dev_mtp_busy(tfa);
    if (rc < 0)
        goto restore;

    switch (item)
    {
        case TFA_MTP_OTC:
            rc = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPOTC);
            break;
        case TFA_MTP_EX:
            rc = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_MTPEX);
            break;
        case TFA_MTP_R25C:
            rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_r25c);
            break;
        case TFA_MTP_F0:
            rc = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_CUSTINFO);
            break;
        case TFA_MTP_OPEN:
            rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_openmtp);
            break;
        default:
            rc = -EINVAL;
            break;
    }

restore:
    /* restore state */
    if (!clock)
    {
        rc = tfa2_dev_set_state(tfa, TFA_STATE_POWERDOWN);
    }

    return rc;
}
#ifdef MTP_READ_MANCOPY
int tfa2_dev_mtp_get(struct tfa2_device *tfa, enum tfa_mtp item)
{
    int rc = -EINVAL;
    int mtp_addr, value;

    switch (item)
    {
        case TFA_MTP_OTC:
            mtp_addr = (TFA9XXX_BF_MTPOTC >> 8) & 0x0f;
            value    = tfa2_i2c_mtp_read(tfa->i2c, mtp_addr);
            rc       = tfa2_i2c_get_bf_value(TFA9XXX_BF_MTPOTC, value);
            break;
        case TFA_MTP_EX:
            mtp_addr = (TFA9XXX_BF_MTPEX >> 8) & 0x0f;
            value    = tfa2_i2c_mtp_read(tfa->i2c, mtp_addr);
            rc       = tfa2_i2c_get_bf_value(TFA9XXX_BF_MTPEX, value);
            break;
        case TFA_MTP_R25C:
            mtp_addr = (tfa->bf_r25c >> 8) & 0x0f;
            value    = tfa2_i2c_mtp_read(tfa->i2c, mtp_addr);
            rc       = tfa2_i2c_get_bf_value(tfa->bf_r25c, value);
            break;
        case TFA_MTP_F0:
            mtp_addr = (TFA9XXX_BF_CUSTINFO >> 8) & 0x0f;
            value    = tfa2_i2c_mtp_read(tfa->i2c, mtp_addr);
            rc       = tfa2_i2c_get_bf_value(TFA9XXX_BF_CUSTINFO, value);
            break;
        case TFA_MTP_OPEN:
            break;
    }

    return rc;
}
#endif
int tfa2_dev_mtp_set(struct tfa2_device *tfa, enum tfa_mtp item, uint16_t value)
{
    int rc;

    switch (item)
    {
        case TFA_MTP_OTC:
            rc = set_mtp(tfa, TFA9XXX_BF_MTPOTC, value);
            break;
        case TFA_MTP_EX:
            rc = set_mtp(tfa, TFA9XXX_BF_MTPEX, value);
            break;
        case TFA_MTP_R25C:
            rc = set_mtp(tfa, tfa->bf_r25c, value);
            break;
        case TFA_MTP_F0:
            rc = set_mtp(tfa, TFA9XXX_BF_CUSTINFO, value);
            break;
        case TFA_MTP_OPEN:
            rc = mtp_open(tfa, value);
            break;
        default:
            rc = -EINVAL;
            break;
    }

    return rc;
}

/* return twos complement */
static inline short twos(short x)
{
    return (x < 0) ? x + 512 : x;
}

void tfa2_set_exttemp(struct tfa2_device *tfa, short ext_temp)
{
    if ((-256 <= ext_temp) && (ext_temp <= 255))
    {
        /* make twos complement */
        dev_dbg(&tfa->i2c->dev, "Using ext temp %d C\n", twos(ext_temp));
        tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_TROS, 1);
        tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_EXTTS, twos(ext_temp));
    }
    else
    {
        dev_dbg(&tfa->i2c->dev, "Clearing ext temp settings\n");
        tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_TROS, 0);
    }
}

short tfa2_get_exttemp(struct tfa2_device *tfa)
{
    short ext_temp = (short)tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_EXTTS);
    return (twos(ext_temp));
}

/****************** patching **************************************************/
int tfa2_process_patch_file(struct i2c_client *client, int length, const uint8_t *bytes)
{
    uint16_t size;
    int index = 0;
    int error = 0;

    dev_dbg(&client->dev, "patch length is %d bytes\n", length);

    while (index + 1 < length)
    {
        size = bytes[index] + bytes[index + 1] * 256;
        index += 2;
        if ((index + size) > length)
        {
            /* outside the buffer, error in the input data */
            return -EINVAL;
        }

        error = tfa2_i2c_write_raw(client, size, &bytes[index]);
        if (error != 0)
            break;
        index += size;
    }

    return error;
}

int tfa2_check_patch(const uint8_t *data, const int length, const uint16_t revid)
{
    struct tfa_patch_header *hdr = (struct tfa_patch_header *)data;
    uint32_t crc;
    uint8_t *ptr;
    size_t size;

    if (data == NULL)
    {
        pr_err("NULL pointer\n");
        return -EINVAL;
    }

    if (length < sizeof(struct tfa_patch_header))
    {
        pr_err("Invalid patch file length: %d\n", length);
        return -EINVAL;
    }

    if (hdr->size < sizeof(struct tfa_patch_header))
    {
        pr_err("Invalid patch size (header): %d\n", hdr->size);
        return -EINVAL;
    }

    if (hdr->size > length)
    {
        pr_err("Invalid patch size (length): %d\n", hdr->size);
        return -EINVAL;
    }

    if (hdr->id != le16_to_cpu('A' << 8 | 'P'))
    {
        pr_err("Invalid id\n");
        return -EINVAL;
    }

    if (strncmp(hdr->version, "1_", 2))
    {
        pr_err("Invalid version\n");
        return -EINVAL;
    }

    if (strncmp(hdr->subversion, "00", 2))
    {
        pr_err("Invalid subversion\n");
        return -EINVAL;
    }

    /* crc is calulated over the data following the crc field */
    ptr  = (uint8_t *)hdr + offsetof(struct tfa_patch_header, crc) + sizeof(hdr->crc);
    size = hdr->size - (ptr - data);
    crc  = ~crc32_le(~0u, ptr, size);
    if (crc != hdr->crc)
    {
        pr_err("Invalid crc\n");
        return -EINVAL;
    }

    if (hdr->rev != (revid & 0xff))
    {
        pr_err("patch file revision check failed: expected: 0x%02x, actual: 0x%02x\n", revid & 0xff, hdr->rev);
        return -EINVAL;
    }

    /* indicate if more data is available */
    return (int)(hdr->size < length);
}

/*
 * cold start the calibration profile
 */
int tfa2_calibrate_profile_start(struct tfa2_device *tfa)
{
    int rc;
    int cal_profile;
    int count, manstate;

    /* force a cold start */
    rc = tfa2_dev_force_cold(tfa);
    if (rc < 0)
        return rc;

    /* get SB calibration profile: with .cal extension */
    cal_profile = tfa2_cnt_grep_profile_name(tfa->cnt, tfa->dev_idx, ".cal");
    if (cal_profile < 0)
    {
        dev_err(&tfa->i2c->dev, "No [*.cal] profile found for calibration\n");
        return -EINVAL;
    }

    rc = tfa2_dev_start(tfa, cal_profile, 0);
    if (rc < 0)
    {
        dev_dbg(&tfa->i2c->dev, "%s : error when starting device\n", __FUNCTION__);
        return rc;
    }

    /* wait until we are in operating state */
    manstate = 0;
    count    = 20;
    while ((manstate != 9) && (count > 0))
    {
        msleep_interruptible(1);
        manstate = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);
        if (manstate < 0)
            return manstate; /* error */
        count--;
    }
    if (count == 0)
    {
        dev_dbg(&tfa->i2c->dev, "Device is not in operating state, can't calibrate!\n");
        return -EIO;
    }

    return 0;
}
// CalibrateDone = xmem[516]
/****************************** speakerboost calibration  **************************/
static int tfa2_sb_calibrate_ackwait(struct tfa2_device *tfa)
{
    int loop = 50, ready = 0;

    do
    {
        ready = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_ACKCAL);
        if (ready == 1)
            break;
        else if (ready < 0)
            return -EIO;
        msleep_interruptible(50); /* wait to avoid busload */
    } while (loop--);

    return 0;
}

int tfa2_sb_calibrate(struct tfa2_device *tfa)
{
    int rc;
    int sbcal_profile, current_profile, always;
    int current_mute = 0;
    int cf_enabled;

    /* get SB calibration profile: with .cal extension */
    sbcal_profile = tfa2_cnt_grep_profile_name(tfa->cnt, tfa->dev_idx, ".cal");
    if (sbcal_profile < 0)
    {
        dev_err(&tfa->i2c->dev, "No [*.cal] profile found for calibration\n");
        return -EINVAL;
    }

    rc = tfa2_dev_mtp_get(tfa, TFA_MTP_OTC);
    if (rc < 0)
        return rc;

    always = !rc; /* OTC==1 if once */

    current_profile = tfa2_dev_get_swprofile(tfa);
    if (current_profile < 0)
    {
        /* no current profile, take the 1st profile */
        current_profile = 0;
    }

    cf_enabled = tfa2_dev_cf_enabled(tfa);
    if (cf_enabled)
    {
        rc = tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_CFSM);
        if (rc < 0)
            return rc;
        current_mute = rc;
    }

    /* force a cold start */
    rc = tfa2_dev_force_cold(tfa);
    if (rc < 0)
        return rc;

    /* start hw & fw, no  speakerboost */

    /* start hardware: init tfa registers and start PLL */
    rc = tfa2_dev_start_hw(tfa, sbcal_profile); /* return muted in initcf state */
    if (rc < 0)
    {
        dev_dbg(&tfa->i2c->dev, "%s : error when starting hardware\n", __FUNCTION__);
        return rc;
    }

    /* start CoolFlux DSP subsystem, will check if clock is there */
    rc = tfa2_dev_start_cf(tfa);
    if (rc < 0)
        return rc;

    if (!always)
    {
        /* open key2 */
        tfa2_i2c_hap_key2(tfa->i2c, 0);

        /* open mtp */
        tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 1);
    }

    /* start with speakerboost only */
    rc = tfa2_dev_start(tfa, sbcal_profile, 0);

    if (rc == 0 && tfa2_sb_calibrate_ackwait(tfa))
    {
        dev_err(&tfa->i2c->dev, "Eror: calibration timed out\n");
        rc = -EIO; // TODO get proper timeout errno
    }

    if (!always)
    {
        /* close key2 */
        tfa2_i2c_hap_key2(tfa->i2c, 1);

        /* close mtp */
        tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 0);
    }

    if (rc >= 0)
    {
        dev_dbg(&tfa->i2c->dev, "%s : RE25 = %d mohm\n", __FUNCTION__, tfa2_get_calibration_impedance(tfa));

        /* re-load current profile and restore CF mute */
        rc = tfa2_dev_start(tfa, current_profile, 0);
        if ((rc >= 0) && cf_enabled)
        {
            rc = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CFSM, current_mute);
        }
    }

    return rc;
}

int tfa2_get_calibration_impedance(struct tfa2_device *tfa)
{
    int mohm, fixed, ret;
    uint8_t buf[9];

    memset(buf, 0, 9);

    ret = tfa2dsp_fw_get_re25(tfa, buf);
    if (ret < 0)
    {
        dev_err(&tfa->i2c->dev, "%s: error when trying to read Re25\n", __func__);
        return ret;
    }

    fixed = buf[6] << 16 | buf[7] << 8 | buf[8];
    mohm  = 1000 * fixed / TFA2_FW_ReZ_SCALE;

    return mohm;
}

/********************** firmware info get ************************************/
int tfa2dsp_fw_get_re25(struct tfa2_device *tfa, uint8_t *buffer)
{
    int command_length = 3;
    int result_length  = 9;
    char *pbuf         = (char *)buffer;
    int rc;

    *pbuf++ = 4; // channel configuration bits (SC|DS|DP|DC)
    *pbuf++ = MODULE_SPEAKERBOOST + 0x80;
    *pbuf++ = SB_PARAM_GET_RE25C;

    // hal_error = tfadsp_writeread(tfa, command_length, buffer, result_length);
    rc = tfa->dsp_execute(tfa, (const char *)buffer, command_length, (char *)buffer, result_length);

    return rc;
}
#if 0 // TODO fix tfadsp_writeread
int tfa2dsp_fw_get_api_version(struct tfa2_device *tfa, uint8_t *buffer) {

	int command_length = 3;
	int result_length = 6;
	uint8_t *pbuf = buffer;
	int hal_error;

	*pbuf++ = 0;
	*pbuf++ = MODULE_FRAMEWORK + 0x80;
	*pbuf++ = FW_PAR_ID_GET_API_VERSION;

	hal_error = tfadsp_writeread(tfa, command_length, buffer, result_length);

	if ( hal_error != 0)
		return hal_error * -1;

	return 6;
}
int tfa2dsp_fw_get_status_change(struct tfa2_device *tfa, uint8_t *buffer) {

	int command_length = 3;
	int result_length = 9;
	uint8_t *pbuf = buffer;
	int hal_error;

	*pbuf++ = 0;
	*pbuf++ = MODULE_FRAMEWORK + 0x80;
	*pbuf++ = FW_PAR_ID_GET_STATUS_CHANGE;

	hal_error = tfadsp_writeread(tfa, command_length, buffer, result_length);

	if ( hal_error != 0)
		return hal_error * -1;

	return result_length;
}
int tfa2dsp_fw_get_tag(struct tfa2_device *tfa, uint8_t *buffer) {

	int command_length = 3;
	int result_length = FW_MAXTAG+3;
	uint8_t *pbuf = buffer;
	int hal_error;

	*pbuf++ = 0;
	*pbuf++ = MODULE_FRAMEWORK + 0x80;
	*pbuf++ = FW_PAR_ID_GET_TAG;

	hal_error = tfadsp_writeread(tfa, command_length, buffer, result_length);

	if ( hal_error != 0)
		return hal_error * -1;

	return 6;
}
#endif

#define BF_REG(bitfield) ((bitfield >> 8) & 0xff)

int tfa2_dev_status(struct tfa2_device *tfa)
{
    const int status0 = BF_REG(TFA9XXX_BF_VDDS);
    int rc, err, i;
    uint16_t status[4];

    /* read status registers */
    rc = tfa2_i2c_read_regs(tfa->i2c, status0, 4, &status[0]);
    if (rc < 0)
        return rc;

    /*
     * check IC status bits: cold start
     * and DSP watch dog bit to re init
     */
    err = 0;
    if (tfa2_dev_cf_enabled(tfa))
    {
        if (tfa2_i2c_get_bf_value(TFA9XXX_BF_ACS, status[0]))
        {
            dev_err(&tfa->i2c->dev, "ERROR: ACS\n");
            err = -ERANGE;
        }
        if (tfa2_i2c_get_bf_value(TFA9XXX_BF_WDS, status[0]))
        {
            dev_err(&tfa->i2c->dev, "ERROR: WDS\n");
            err = -ERANGE;
        }
        if (err < 0)
            return err;

        if (tfa2_i2c_get_bf_value(TFA9XXX_BF_SPKS, status[0]))
            dev_err(&tfa->i2c->dev, "ERROR: SPKS\n");
    }

    for (i = 0; i < 4; i++)
    {
        err = (status[i] ^ ~tfa->status_err[i]) & tfa->status_mask[i];
        if (err)
        {
            dev_err(&tfa->i2c->dev, "error(s) detected: 0x%x = 0x%x (0x%x)\n", status0 + i, status[i], err);
        }
    }

    return 0;
}

int tfa2_dev_set_volume(struct tfa2_device *tfa, uint8_t volume)
{
    /* Set the new value in the hw register */
    return tfa2_i2c_write_bf_volatile(tfa->i2c, TFA9XXX_BF_VOL, volume);
}

int tfa2_dev_get_volume(struct tfa2_device *tfa)
{
    return tfa2_i2c_read_bf(tfa->i2c, TFA9XXX_BF_VOL);
}
