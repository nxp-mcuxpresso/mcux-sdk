/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TFA2_DSP_FW_H
#define TFA2_DSP_FW_H

#include "tfa2_dev.h"

/*
 * the order matches the ACK bits order in TFA98XX_CF_STATUS
 */
enum tfa_fw_event
{ /* not all available on each device */
  tfa_fw_i2c_cmd_ack,
  tfa_fw_reset_start,
  tfa_fw_short_on_mips,
  tfa_fw_soft_mute_ready,
  tfa_fw_volume_ready,
  tfa_fw_error_damage,
  tfa_fw_calibrate_done,
  tfa_fw_max
};

/* the following type mappings are compiler specific */
#define subaddress_t unsigned char

/* module Ids */
#define MODULE_FRAMEWORK        0
#define MODULE_SPEAKERBOOST     1
#define MODULE_BIQUADFILTERBANK 2
#define MODULE_TAPTRIGGER       5
#define MODULE_SETRE            9

/* RPC commands */
/* SET */
#define FW_PAR_ID_SET_MEMORY             0x03
#define FW_PAR_ID_SET_SENSES_DELAY       0x04
#define FW_PAR_ID_SETSENSESCAL           0x05
#define FW_PAR_ID_SET_INPUT_SELECTOR     0x06
#define FW_PAR_ID_SET_OUTPUT_SELECTOR    0x08
#define FW_PAR_ID_SET_PROGRAM_CONFIG     0x09
#define FW_PAR_ID_SET_GAINS              0x0A
#define FW_PAR_ID_SET_MEMTRACK           0x0B
#define FW_PAR_ID_SET_FWKUSECASE         0x11
#define TFA1_FW_PAR_ID_SET_CURRENT_DELAY 0x03
#define TFA1_FW_PAR_ID_SET_CURFRAC_DELAY 0x06
/* GET */
#define FW_PAR_ID_GET_MEMORY        0x83
#define FW_PAR_ID_GLOBAL_GET_INFO   0x84
#define FW_PAR_ID_GET_FEATURE_INFO  0x85
#define FW_PAR_ID_GET_MEMTRACK      0x8B
#define FW_PAR_ID_GET_TAG           0xFF
#define FW_PAR_ID_GET_API_VERSION   0xFE
#define FW_PAR_ID_GET_STATUS_CHANGE 0x8D

/* Load a full model into SpeakerBoost. */
/* SET */
#define SB_PARAM_SET_ALGO_PARAMS               0x00
#define SB_PARAM_SET_LAGW                      0x01
#define SB_PARAM_SET_ALGO_PARAMS_WITHOUT_RESET 0x02
#define SB_PARAM_SET_RE25C                     0x05
#define SB_PARAM_SET_LSMODEL                   0x06
#define SB_PARAM_SET_MBDRC                     0x07
#define SB_PARAM_SET_MBDRC_WITHOUT_RESET       0x08
#define SB_PARAM_SET_EXCURSION_FILTERS         0x0A
#define SB_PARAM_SET_DRC                       0x0F
/* GET */
#define SB_PARAM_GET_ALGO_PARAMS       0x80
#define SB_PARAM_GET_LAGW              0x81
#define SB_PARAM_GET_RE25C             0x85
#define SB_PARAM_GET_LSMODEL           0x86
#define SB_PARAM_GET_MBDRC             0x87
#define SB_PARAM_GET_MBDRC_DYNAMICS    0x89
#define SB_PARAM_GET_EXCURSION_FILTERS 0x8A
#define SB_PARAM_GET_TAG               0xFF
#define FW_MAXTAG                      150

#define SB_PARAM_GET_ZFILTER 0x8F
#define SB_PARAM_GET_XFILTER 0x90

#define SB_PARAM_SET_EQ                0x0A /* 2 Equaliser Filters. */
#define SB_PARAM_SET_PRESET            0x0D /* Load a preset */
#define SB_PARAM_SET_CONFIG            0x0E /* Load a config */
#define SB_PARAM_SET_AGCINS            0x10
#define SB_PARAM_SET_CURRENT_DELAY     0x03
#define SB_PARAM_GET_STATE             0xC0
#define SB_PARAM_GET_XMODEL            0xC1 /* Gets current Excursion Model. */
#define SB_PARAM_GET_XMODEL_COEFFS     0x8C /* Get coefficients for XModel */
#define SB_PARAM_GET_EXCURSION_FILTERS 0x8A /* Get excursion filters */
#define SB_PARAM_SET_EXCURSION_FILTERS 0x0A /* Set excursion filters */

/*	SET: TAPTRIGGER */
#define TAP_PARAM_SET_ALGO_PARAMS       0x01
#define TAP_PARAM_SET_DECIMATION_PARAMS 0x02

/* GET: TAPTRIGGER*/
#define TAP_PARAM_GET_ALGO_PARAMS 0x81
#define TAP_PARAM_GET_TAP_RESULTS 0x84

/* sets the speaker calibration impedance (@25 degrees celsius) */
#define SB_PARAM_SET_RE0 0x89

#define BFB_PAR_ID_SET_COEFS  0x00
#define BFB_PAR_ID_GET_COEFS  0x80
#define BFB_PAR_ID_GET_CONFIG 0x81

/* for compatibility */
#define FW_PARAM_GET_STATE        FW_PAR_ID_GLOBAL_GET_INFO
#define FW_PARAM_GET_FEATURE_BITS FW_PAR_ID_GET_FEATURE_BITS

/* RPC Status results */
#define STATUS_OK                0
#define STATUS_INVALID_MODULE_ID 2
#define STATUS_INVALID_PARAM_ID  3
#define STATUS_INVALID_INFO_ID   4

/* parameter size in words including command id */
#define TIB_MONO_ALGOPARAMETER_LENGTH   (180 + 1)
#define TIB_STEREO_ALGOPARAMETER_LENGTH (348 + 1)
#define TFA_ALGOPARAMETER_LENGTH        (180 + 1)

#define TIB_MONO_SPEAKERPARAMETER_LENGTH   (151 + 1)
#define TIB_STEREO_SPEAKERPARAMETER_LENGTH (302 + 1)
#define TFA_SPEAKERPARAMETER_LENGTH        (151 + 1)

#define TIB_MONO_MBDRC_LENGTH   (99 + 1)
#define TIB_STEREO_MBDRC_LENGTH (99 + 1)
#define TFA_MBDRC_LENGTH        (95 + 1)

#define TIB_MONO_FILTERCOEFS_LENGTH   (1 + 6 * (10 + 2 + 1) + 1)
#define TIB_STEREO_FILTERCOEFS_LENGTH (1 + 6 * (10 + 10 + 2 + 2 + 1) + 1)
#define TFA_FILTERCOEFS_LENGTH        (193) // itf(1+6*10)

#define TIB_MONO_EXCURSIONFILTER_LENGTH   (25 + 1)
#define TIB_STEREO_EXCURSIONFILTER_LENGTH (50 + 1)
#define TFA_EXCURSIONFILTER_LENGTH        (25 + 1)

/* the maximum message length in the communication with the DSP */
#define TFA2_MAX_PARAM_SIZE (TIB_STEREO_ALGOPARAMETER_LENGTH) /*  */

#define ROUND_DOWN(a, n) (((a) / (n)) * (n))

/* feature bits */
#define FEATURE1_TCOEF 0x100 /* bit8 set means tCoefA expected */
#define FEATURE1_DRC   0x200 /* bit9 NOT set means DRC expected */

/* DSP firmware xmem defines */
#define TFA2_FW_XMEM_CALIBRATION_DONE 516
#define TFA2_FW_XMEM_COUNT_BOOT       512
#define TFA2_FW_XMEM_CMD_COUNT        520

/* note that the following defs rely on the handle variable */
#define TFA_FW_XMEM_CALIBRATION_DONE TFA_FAM_FW(tfa, XMEM_CALIBRATION_DONE)
#define TFA_FW_XMEM_COUNT_BOOT       TFA_FAM_FW(tfa, XMEM_COUNT_BOOT)
#define TFA_FW_XMEM_CMD_COUNT        TFA_FAM_FW(tfa, XMEM_CMD_COUNT)

#define TFA2_FW_ReZ_SCALE 65536

#endif /* TFA2_DSP_FW_H */
