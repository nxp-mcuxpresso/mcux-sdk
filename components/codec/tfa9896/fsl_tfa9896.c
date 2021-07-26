/*
 * Copyright 2019 NXP
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "fsl_common.h"
#include "fsl_tfa9896.h"
#include "fsl_tfa9896_buffer.h"
#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t TFA9896_Init(tfa9896_handle_t *handle, tfa9896_config_t *tfa9896Config)
{
    uint8_t trial        = 10U;
    uint8_t factory_done = 0;
    uint16_t regRead = 0, do_calibrate = 0;
    int status;
    status_t error;
    int calibrateDone = 0;
    float re25;
    int i, tries = 0;
    tfa9896_config_t *config = tfa9896Config;
    handle->config           = config;

    /* i2c bus initialization */
    error = CODEC_I2C_Init(handle->i2cHandle, handle->config->i2cConfig.codecI2CInstance, TFA_I2C_BITRATE,
                           handle->config->i2cConfig.codecI2CSourceClock);
    if (error != kStatus_HAL_I2cSuccess)
    {
        return kStatus_TFA9896_I2C_Fatal;
    }

    /*************************/
    error = TFA9896_SetBits(handle, TFA1_BF_I2CR, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_RST, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /****************************/
    error = TFA9896_WriteRegister(handle, 0x06, (uint16_t)0x000b);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_WriteRegister(handle, 0x07, (uint16_t)0x3e7f);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_WriteRegister(handle, 0x0a, (uint16_t)0x0d8a);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_WriteRegister(handle, 0x48, (uint16_t)0x0300);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_WriteRegister(handle, 0x88, (uint16_t)0x0100);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_ReadRegister(handle, 0x49, &regRead);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    regRead &= ~0x1;
    error = TFA9896_WriteRegister(handle, 0x49, regRead);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /****************************/
    error = TFA9896_SetBits(handle, TFA1_BF_AUDFS, 8);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_TDMSAMSZ, 15);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_NBCK, 0);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    if (handle->config->slaveAddress == 0x34)
    {
        error = TFA9896_SetBits(handle, TFA1_BF_CHS12, 1);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
    }
    else if (handle->config->slaveAddress == 0x36)
    {
        error = TFA9896_SetBits(handle, TFA1_BF_CHS12, 2);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
    }

    error = TFA9896_SetBits(handle, TFA1_BF_IPLL, 0);
    error = TFA9896_SetBits(handle, TFA1_BF_CLIP, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_ATTEN, 5);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_DCTRIP, 7);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, bst_slpcmplvl, 3);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, ignore_flag_voutcomp86, 0);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_DCPWM, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_CFE, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_CHSA, 2);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    error = TFA9896_SetBits(handle, TFA1_BF_AMPC, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    /*******PWUP**********/
    TFA9896_Powerdown(handle, 0);
    /* Check the PLL is powered up from status register 0*/
    error = TFA9896_ReadRegister(handle, 0x00, &regRead);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    while ((regRead & 0x8000) == 0 && (tries < PLL_READ_TRIAL))
    {
        tries++;
        error = TFA9896_ReadRegister(handle, 0x00, &regRead);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
    }
    if (tries >= PLL_READ_TRIAL)
    {
        /* something wrong with communication with DSP */
        error = kStatus_TFA9896_StateTimedOut;
    }
    /*************Force Coldstart*************/
    while (TFA9896_GetBits(handle, TFA1_BF_ACS) != 1)
    {
        /*******************************************/
        (void)TFA9896_DSP_Write_Mem_Word(handle, 0x8100, 1, DMEM_IOMEM);
        /*****************************************************/
        if (trial-- == 0)
        {
            return kStatus_TFA9896_DSP_not_running;
        }
    }
    for (trial = 1; trial < 10; trial++)
    {
        (void)TFA9896_DSP_System_Stable(handle, &status);
        if (status)
        {
            break;
        }
        else
            for (i = 0; i < 0xfff; i++)
                ;
    }
    if (trial >= 10)
    {
        TFA9896_Printf("Timed out , exit, exit\n");
        return kStatus_TFA9896_DSP_not_running;
    }
    else
        TFA9896_Printf(" OK (trial=%d)\n", trial);
    factory_done = TFA9896_isFactory(handle);
    if (handle->config->calibrate)
    {
        do_calibrate = true;
    }
    if (do_calibrate)
    {
        error = TFA9896_ClearOneTimeCalibration(handle);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
        error = TFA9896_SetOneTimeCalibration(handle);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
    }
    else if (!factory_done)
    {
        error = TFA9896_SetFactoryValues(handle);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
    }
    /**************************************************/
    error = TFA9896_CheckICROMversion(handle, patch_patch);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf("SC:%x PATCH loading Start--length to be  loaded:%d\n", handle, patch_patch_len);
    error = TFA9896_ProcessPatchFile(handle, patch_patch_len - TFA9896_PATCH_EXTRA, patch_patch + TFA9896_PATCH_EXTRA);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf(" PATCH OK \n");

    error = TFA9896_DSP_Write_Mem_Word(handle, 512, 0, DMEM_XMEM);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /* Reset DSP once for sure after initializing */
    error = TFA9896_SetBits(handle, TFA1_BF_RST, 0);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_DSPWriteTables(handle);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /************************/
    error = TFA9896_SetMute(handle, Mute_Digital);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf("SL:%x CONFIG loading Start--length to be  loaded:%d\n", config_config_len);
    error = TFA9896_DspWriteConfig(handle, config_config_len, config_config);

    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf(" CONFIG OK \n");
    TFA9896_Printf("SL:%x Speaker loading Start--length to be  loaded:%d\n", speaker_speaker_len);
    error = TFA9896_DspWriteSpeakerParameters(handle, speaker_speaker_len, speaker_speaker);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf("SpeakerOk\n");

    TFA9896_Printf("SC:%x Preset loading Start--length to be  loaded:%d\n", preset_preset_len);
    error = TFA9896_DspWritePreset(handle, preset_preset_len, preset_preset);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    TFA9896_Printf("PresetOk\n");
    /******************************/
    error = TFA9896_Write_FilterBank(handle, (tfa9896FilterM_t *)(eq_eq));
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /*************Wait for AMPS*************/

    error = TFA9896_SetBits(handle, TFA1_BF_SBSL, 1);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    /* Wait for calibration to complete*/
    if (do_calibrate)
    {
        error = TFA9896_WaitCalibrateDone(handle, &calibrateDone);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
        if (calibrateDone)
        {
            error = TFA9896_DspGetCalibrationImpedance(handle, &re25);
            if (error != kStatus_TFA9896_Ok)
            {
                return error;
            }
        }
        else
        {
            re25 = 0;
        }
        TFA9896_Printf("TFA9896 0x%02X Calibration value is %2.2f ohm\n", re25);
    }
    error = TFA9896_PrintCalibration(handle);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_SetMute(handle, Mute_Off);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    return kStatus_TFA9896_Ok;
}

status_t TFA9896_Deinit(tfa9896_handle_t *handle)
{
    TFA9896_Printf("%s: Device 0x%02x deinit", __FUNCTION__);
    TFA9896_Powerdown(handle, 1);
    return kStatus_TFA9896_Ok;
}

void TFA9896_Powerdown(tfa9896_handle_t *handle, int powerdown)
{
    TFA9896_SetBits(handle, TFA1_BF_PWDN, (uint16_t)powerdown);
}

status_t TFA9896_SetVolume(tfa9896_handle_t *handle, uint8_t volume_level)
{
    return TFA9896_SetBits(handle, TFA1_BF_VOL, (uint16_t)volume_level);
}
