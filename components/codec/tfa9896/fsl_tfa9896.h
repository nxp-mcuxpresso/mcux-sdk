/*
 * Copyright 2019 NXP
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_TFA9896_H_
#define _FSL_TFA9896_H_

#include "fsl_common.h"
#include "fsl_codec_i2c.h"

/*!
 * @addtogroup tfa9896
 * @ingroup codec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifdef TFA9896_DEBUG
#include "fsl_debug_console.h"
#define TFA9896_Printf DbgConsole_Printf
#else
#define TFA9896_Printf(format, args...) ((void)0)
#endif

#define TFA9896_PATCH_EXTRA        6
#define FSL_TFA9896_DRIVER_VERSION (MAKE_VERSION(6, 0, 2))

/*!@brief TFA I2S bit clock */
#define TFA_I2C_BITRATE (400000U)

/*! @brief tfa9896 handle size */
#ifndef TFA9896_I2C_HANDLER_SIZE
#define TFA9896_I2C_HANDLER_SIZE (CODEC_I2C_MASTER_HANDLER_SIZE)
#endif

#define Sleep(ms)                 usleep((ms)*1000)
#define TFA9896_I2C_ADDRESS_LEFT  (0x34)
#define TFA9896_I2C_ADDRESS_RIGHT (0x36)
#define TFA9896_LIVEDATA_CAPTURE
#define TFA1_FW_ReZ_SCALE             16384
#define MAX_PARAM_SIZE                (145 * 3)
#define TFA1_MAX_PARAM_SIZE           (145 * 3) /* TFA1 */
#define NXP_I2C_MAX_SIZE              254
#define MAX_I2C_LENGTH                NXP_I2C_MAX_SIZE
#define ROUND_DOWN(a, n)              (((a) / (n)) * (n))
#define TFA9896_API_WAITRESULT_NTRIES 30000
#define TFA1_BF_PWDN                  0x0900
/* RPC Status results */
#define STATUS_OK                0
#define STATUS_INVALID_MODULE_ID 2
#define STATUS_INVALID_PARAM_ID  3
#define STATUS_INVALID_INFO_ID   4
/* module Ids */
#define MODULE_FRAMEWORK        0
#define MODULE_SPEAKERBOOST     1
#define MODULE_BIQUADFILTERBANK 2
#define SB_PARAM_GET_STATE      0xC0
#define FW_PARAM_GET_STATE      0x84
/* RPC commands */
#define SB_PARAM_GET_RE0     0x85
#define SB_PARAM_SET_LSMODEL 0x06 /* Load a full model into SpeakerBoost.*/
#define SB_PARAM_SET_EQ      0x0A /* 2 Equaliser Filters.*/
#define SB_PARAM_SET_PRESET  0x0D /* Load a preset*/
#define SB_PARAM_SET_CONFIG  0x0E /* Load a config*/
#define SB_PARAM_SET_DRC     0x0F
#define SB_PARAM_SET_AGCINS  0x10
#define PARAM_GET_LSMODEL    0x86 /* Gets current LoudSpeaker impedance Model.*/
#define PARAM_GET_LSMODELW   0xC1 /* Gets current LoudSpeaker xcursion Model.*/

#define FW_STATE_SIZE           9
#define FW_STATE_MAX_SIZE       FW_STATE_SIZE
#define SPKRBST_HEADROOM        7                /* Headroom applied to the main input signal */
#define SPKRBST_AGCGAIN_EXP     SPKRBST_HEADROOM /* Exponent used for AGC Gain related variables */
#define SPKRBST_TEMPERATURE_EXP 9
#define SPKRBST_LIMGAIN_EXP     4 /* Exponent used for Gain Corection related variables */
#define SPKRBST_TIMECTE_EXP     1
#define TFA1_BF_VOL             0x0687
#define TFA1_BF_ACS             0x00b0
#define TFA1_BF_DMEM            0x7011
#define TFA1_BF_MADD            0x710f
#define TFA1_BF_I2SDOE          0x04b0
#define TFA1_BF_PLLS            0x0010
#define TFA1_BF_SBSL            0x0950
#define TFA1_BF_RST             0x7000
#define TFA1_BF_I2CR            0x0910
#define TFA1_BF_AMPS            0x00e0
#define TFA1_BF_MTPB            0x0080
#define TFA1_BF_MTPK            0x0b07
#define TFA1_BF_SPKS            0x00a0
#define TFA1_BF_MTPOTC          0x8000
#define TFA1_BF_MTPEX           0x8010
#define TFA1_BF_MTP0            TFA1_BF_MTPOTC
#define TFA1_BF_CIMTP           0x62b0
#define TFA_MTPOTC_POS          0
#define TFA_MTPEX_POS           1
#ifndef MIN
#define MIN(A, B) (A < B ? A : B)
#endif //
#define TFA9896_CURRENTSENSE4_CTRL_CLKGATECFOFF (1 << 2)
#define TFA1_BF_RST                             0x7000
#define TFA1_BF_AREFS                           0x00f0
#define TFA1_BF_CLKS                            0x0060
#define TFA1_BF_AMPS                            0x00e0
#define TFA1_BF_MTPB                            0x0080
#ifdef ENABLE_AEC_DIRECTION
#define TFA1_BF_DOLS 0xa02
#define TFA1_BF_DORS 0xa32
#endif //
#define TFA1_BF_TDMSAMSZ           0x10a4
#define TFA1_BF_NBCK               0x14c3
#define TFA1_BF_AUDFS              0x04c3
#define TFA1_BF_CLIP               0x4900
#define TFA1_BF_CHS12              0x0431
#define TFA1_BF_CFE                0x0920
#define TFA1_BF_CHSA               0x0461
#define TFA1_BF_AMPC               0x0960
#define TFA1_BF_IPLL               0x09e0
#define TFA1_BF_ATTEN              0x0613
#define TFA1_BF_DCTRIP             0x0a04
#define TFA1_BF_DCPWM              0x07d0
#define bst_slpcmplvl              0xaa1
#define ignore_flag_voutcomp86     0x7e0
#define TFA9896_AUDIO_CTR          0x06
#define TFA9896_SYS_CTRL           0x09
#define TFA9896_CURRENTSENSE4      0x49
#define TFA9896_AUDIO_CTR_CFSM_MSK 0x20
#define TFA9896_SYS_CTRL_AMPE_MSK  0x8
#define TFA9896_SYS_CTRL_DCA_MSK   0x10
#define OPTIMIZED_RPC
#define PLL_READ_TRIAL 50

/*! @brief status flag
 *  @anchor _tfa9896_error
 */
enum
{
    kStatus_TFA9896_Ok              = MAKE_STATUS(kStatusGroup_Generic, 0), /*!< kStatus_TFA9896_Ok = 0,*/
    kStatus_TFA9896_DSP_not_running = MAKE_STATUS(kStatusGroup_Generic, 1),
    /*!< communication with the DSP failed, presumably because DSP not running  kStatus_TFA9896_DSP_not_running */
    kStatus_TFA9896_Bad_Parameter = MAKE_STATUS(kStatusGroup_Generic, 2), /*!< kStatus_TFA9896_Bad_Parameter*/
    kStatus_TFA9896_NotOpen =
        MAKE_STATUS(kStatusGroup_Generic, 3), /*!< kStatus_TFA9896_NotOpen, the given handle is not open */
    kStatus_TFA9896_OutOfHandles = MAKE_STATUS(kStatusGroup_Generic, 4), /*!< too many handles*/
    kStatus_TFA9896_StateTimedOut =
        MAKE_STATUS(kStatusGroup_Generic,
                    5), /*!< the expected response did not occur within the expected time  Tfa9896_Error_StateTimedOut,
                       the expected response did not occur within the expected time */
    kStatus_TFA9896_RpcBase    = MAKE_STATUS(kStatusGroup_Generic, 100), /*!< kStatus_TFA9896_RpcBase = 100,*/
    kStatus_TFA9896_RpcBusy    = MAKE_STATUS(kStatusGroup_Generic, 101), /*!< kStatus_TFA9896_RpcBusy = 101,*/
    kStatus_TFA9896_RpcModId   = MAKE_STATUS(kStatusGroup_Generic, 102), /*!< kStatus_TFA9896_RpcModId = 102,*/
    kStatus_TFA9896_RpcParamId = MAKE_STATUS(kStatusGroup_Generic, 103), /*!< kStatus_TFA9896_RpcParamId = 103*/
    kStatus_TFA9896_RpcInfoId  = MAKE_STATUS(kStatusGroup_Generic, 104), /*!< kStatus_TFA9896_RpcInfoId = 104*/
    kStatus_TFA9896_RpcNotAllowedSpeaker =
        MAKE_STATUS(kStatusGroup_Generic, 105), /*!< kStatus_TFA9896_RpcNotAllowedSpeaker = 105*/
    kStatus_TFA9896_Not_Implemented = MAKE_STATUS(kStatusGroup_Generic, 106), /*!< kStatus_TFA9896_Not_Implemented*/
    kStatus_TFA9896_Not_Supported   = MAKE_STATUS(kStatusGroup_Generic, 107), /*!< kStatus_TFA9896_Not_Supported*/
    kStatus_TFA9896_I2C_Fatal =
        MAKE_STATUS(kStatusGroup_Generic, 108), /*!< Fatal I2C error occurred  kStatus_TFA9896_I2C_Fatal*/
    kStatus_TFA9896_I2C_NonFatal =
        MAKE_STATUS(kStatusGroup_Generic, 109),                     /*!< Nonfatal I2C error, and retry count reached */
    kStatus_TFA9896_Other = MAKE_STATUS(kStatusGroup_Generic, 1000) /*!< kStatus_TFA9896_Other = 1000*/
};

/*! @brief type definition */
typedef int int24;
typedef struct uint24M
{
    uint8_t b[3];
} uint24M_t;

/*! @brief biquadm */
typedef struct _tfa9896BiquadM
{
    uint8_t bytes[6 * sizeof(uint24M_t)];
} tfa9896BiquadM_t;

/*! @brief filter */
typedef struct _tfa9896FilterM
{
    tfa9896BiquadM_t biquad;
    uint8_t enabled;
    uint8_t type; /*!< (== enum FilterTypes, assure 8bits length)*/
    float frequency;
    float Q;
    float gain;
} tfa9896FilterM_t; /*!< 8 * float + int32 + byte == 37*/

#ifdef SUPPORT_EXCURSION_FILTER
/*! @brief cont anti alias*/
typedef struct _tfa9896ContAntiAliasM
{
    unsigned char index; /*!< index determines destination type; anti-alias, integrator,eq */
    unsigned char type;
    float cutOffFreq; /*!< cut off frequency*/
    float samplingFreq;
    float rippleDb; /*!< integrator leakage*/
    float rolloff;
    uint8_t bytes[5 * 3]; /*!< payload 5*24buts coeffs*/
} tfa9896ContAntiAliasM_t;

/*! @brief cont integrator */
typedef struct _tfa9896ContIntegratorM
{
    int8_t index; /*!< index determines destination type; anti-alias, integrator,eq */
    uint8_t type;
    float cutOffFreq; /*!< cut off frequency*/
    float samplingFreq;
    float leakage; /*!< integrator leakage*/
    float reserved;
    uint8_t bytes[5 * 3]; /*!< payload 5*24buts coeffs*/
} tfa9896ContIntegratorM_t;

/*! @brief cont eqm */
typedef struct _tfa9896ContEqM
{
    int8_t index;
    uint8_t type;         /*!< (== enum FilterTypes, assure 8bits length)*/
    float cutOffFreq;     /*!< cut off frequency, // range: [100.0 4000.0]*/
    float samplingFreq;   /*!< sampling frequency*/
    float Q;              /*!< range: [0.5 5.0]*/
    float gainDb;         /*!< range: [-10.0 10.0]*/
    uint8_t bytes[5 * 3]; /*!< payload 5*24buts coeffs*/
} tfa9896ContEqM_t;

/*! @brief cont biquadm */
typedef struct _tfa9896ContBiquadM
{
    /*tfaContEqM_t eq;*/
    tfaContAntiAliasM_t aa;
    /*tfaContIntegratorM_t in;*/
} tfaContBiquadM_t;
#endif

/*! @brief mute dmem */
typedef enum _tfa9896_DMEM
{
    DMEM_PMEM  = 0, /*!< pmem */
    DMEM_XMEM  = 1, /*!< xmem */
    DMEM_YMEM  = 2, /*!< ymem */
    DMEM_IOMEM = 3, /*!< iomem */
} tfa9896_DMEM_t;

/*! @brief mute status */
typedef enum _tfa9896_Mute
{
    Mute_Off,
    Mute_Digital,
    Mute_Amplifier
} tfa9896_mute_t;

/*! @brief status info live */
typedef struct _tfa9896_StateInfoLive
{
    /* SpeakerBoost State */
    float agcGain;  /* Current AGC Gain value */
    float limGain;  /* Current Limiter Gain value */
    float sMax;     /* Current Clip/Lim threshold */
    int T;          /* Current Speaker Temperature value */
    int statusFlag; /* Masked bit word, see TFA9896_SpeakerBoostStatusFlags */
    float X1;       /* Current estimated Excursion value caused by Speakerboost gain control */
    float X2;       /* Current estimated Excursion value caused by manual gain setting */
    float Re;       /* Current Loudspeaker blocked resistance */
    /* Framework state */
    int shortOnMips; /* increments each time a MIPS problem is detected on the DSP, only presenton newer ICs */
} tfa9896_StateInfoLive_t;

/*! @brief speaker boost status flag*/
typedef enum _tfa9896_SpeakerBoostStatusFlagsLive
{
    tfa9896_SpeakerBoost_ActivityLive = 0,  /* Input signal activity. */
    tfa9896_SpeakerBoost_S_CtrlLive,        /* S Control triggers the limiter */
    tfa9896_SpeakerBoost_MutedLive,         /* 1 when signal is muted */
    tfa9896_SpeakerBoost_X_CtrlLive,        /* X Control triggers the limiter */
    tfa9896_SpeakerBoost_T_CtrlLive,        /* T Control triggers the limiter */
    tfa9896_SpeakerBoost_NewModelLive,      /* New model is available */
    tfa9896_SpeakerBoost_VolumeRdyLive,     /* 0 means stable volume, 1 means volume is still smoothing */
    tfa9896_SpeakerBoost_DamagedLive,       /* Speaker Damage detected  */
    tfa9896_SpeakerBoost_SignalClippingLive /* Input Signal clipping detected */
} tfa9896_SpeakerBoostStatusFlagsLive_t;

/*! @brief speaker mode */
typedef struct _tfa9896SPKRBST_SpkrModel
{
    double pFIR[128];         /* Pointer to Excurcussion  Impulse response or
      Admittance Impulse response (reversed order!!) */
    int Shift_FIR;            /* Exponent of HX data */
    float leakageFactor;      /* Excursion model integration leakage */
    float ReCorrection;       /* Correction factor for Re */
    float xInitMargin;        /*(1)Margin on excursion model during startup */
    float xDamageMargin;      /* Margin on excursion modelwhen damage has been detected */
    float xMargin;            /* Margin on excursion model activated when LookaHead is 0 */
    float Bl;                 /* Loudspeaker force factor */
    int fRes;                 /*(1)Estimated Speaker Resonance Compensation Filter cutoff frequency */
    int fResInit;             /* Initial Speaker Resonance Compensation Filter cutoff frequency */
    float Qt;                 /* Speaker Resonance Compensation Filter Q-factor */
    float xMax;               /* Maximum excursion of the speaker membrane */
    float tMax;               /* Maximum Temperature of the speaker coil */
    float tCoefA;             /*(1)Temperature coefficient */
} tfa9896SPKRBST_SpkrModel_t; /* (1) this value may change dynamically */

/*! @brief Bit width. */
typedef enum _tfa9896_bit_width
{
    ktfa9896_BitWidth16 = 0x0, /*!< 16 bits */

} tfa9896_bit_width_t;

/*! @brief The audio data transfer protocol. */
typedef enum _tfa9896_protocol
{
    kTFA9896_ProtocolI2S = 0x2, /*!< I2S type */
} tfa9896_protocol_t;

/*! @brief Sample rate. */
typedef enum _tfa9896_sample_rate
{
    ktfa9896_SampleRate48kHz = 0x5 /*48kHz */
} tfa9896_sample_rate_t;

/*! @brief Audio format configuration. */
typedef struct _tfa9896_audio_format
{
    tfa9896_sample_rate_t sampleRate; /*!< Sample rate */
    tfa9896_bit_width_t bitWidth;     /*!< Bit width */
} tfa9896_audio_format_t;

/*! @brief Initialize structure of TFA9896 */
typedef struct _tfa9896_config
{
    tfa9896_protocol_t protocol;   /*!< Audio transfer protocol */
    tfa9896_audio_format_t format; /*!< Audio format */
    bool master;                   /*!< true is master, false is slave */
    uint8_t slaveAddress;          /*!< slave address */
    codec_i2c_config_t i2cConfig;  /*!< i2c bus configuration */
    uint8_t calibrate;             /*!< user handles calibration! */

} tfa9896_config_t;

/*! @brief tfa9896 handler */
typedef struct _tfa9896_handle
{
    tfa9896_config_t *config; /*!< tfa9896 config pointer */
    uint8_t i2cHandle[TFA9896_I2C_HANDLER_SIZE];
} tfa9896_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief check if TFA9896 Hardware factory registers are set .
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
uint16_t TFA9896_isFactory(tfa9896_handle_t *handle);

/*!
 * @brief get TFA9896 bitfield value .
 *
 * @param handle TFA9896 codec handle.
 * @param bf to be read
 * @return Returns 16 bits read value.
 */
uint16_t TFA9896_GetBits(tfa9896_handle_t *handle, const uint16_t bf);
/*!
 * @brief set TFA9896 bitfield value .
 *
 * @param handle TFA9896 codec handle.
 * @param bf to be set
 * @param value to be set
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetBits(tfa9896_handle_t *handle, const uint16_t bf, const uint16_t value);
/*!
 * @brief wait for DSP to be stable before RPC communictaons .
 *
 * @param handle TFA9896 codec handle.
 * @param ready DSP system stable status.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DSP_System_Stable(tfa9896_handle_t *handle, int *ready);
/*!
 * @brief clear MTP regsiters to prepare calibraion .
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_ClearOneTimeCalibration(tfa9896_handle_t *handle);

/*!
 * @brief set calibartion once registers.
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetOneTimeCalibration(tfa9896_handle_t *handle);
/*!
 * @brief set MTP factory values .
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetFactoryValues(tfa9896_handle_t *handle);
/*!
 * @brief check DSP patch suitability to the TFA9896 device .
 *
 * @param handle TFA9896 codec handle.
 * @param patchheader pattern to check with.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_CheckICROMversion(tfa9896_handle_t *handle, const unsigned char patchheader[]);
/*!
 * @brief load DSP patch to DSP memeory .
 *
 * @param handle TFA9896 codec handle.
 * @param length of the patch.
 * @param bytes that contains patch data.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_ProcessPatchFile(tfa9896_handle_t *handle, int length, const unsigned char *bytes);
/*!
 * @brief set DSP memery table .
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DSPWriteTables(tfa9896_handle_t *handle);

/*!
 * @brief write DSP config file to DSP memery .
 *
 * @param handle TFA9896 codec handle.
 * @param length of the config.
 * @param pConfigBytes that contains config data.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DspWriteConfig(tfa9896_handle_t *handle, int length, const unsigned char *pConfigBytes);
/*!
 * @brief write DSP speaker file to DSP memery .
 *
 * @param handle TFA9896 codec handle.
 * @param length of the speaker data.
 * @param pSpeakerBytes that contains speaker data.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DspWriteSpeakerParameters(tfa9896_handle_t *handle, int length, const unsigned char *pSpeakerBytes);
/*!
 * @brief write DSP preset file to DSP memery .
 *
 * @param handle TFA9896 codec handle.
 * @param length of the preset data.
 * @param pPresetBytes that contains preset data.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DspWritePreset(tfa9896_handle_t *handle, int length, const unsigned char *pPresetBytes);
/*!
 * @brief write DSP filter params to DSP memery .
 *
 * @param handle TFA9896 codec handle.
 * @param filter of the filter data.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_Write_FilterBank(tfa9896_handle_t *handle, tfa9896FilterM_t *filter);
/*!
 * @brief wait calibration to be finalized .
 *
 * @param handle TFA9896 codec handle.
 * @param calibrateDone calibration done flag.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_WaitCalibrateDone(tfa9896_handle_t *handle, int *calibrateDone);
/*!
 * @brief retrieve calibration impedance value and expose it to user.
 *
 * @param handle TFA9896 codec handle.
 * @param pRe25 calibration value.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DspGetCalibrationImpedance(tfa9896_handle_t *handle, float *pRe25);
/*!
 * @brief print calibration value .
 *
 * @param handle TFA9896 codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_PrintCalibration(tfa9896_handle_t *handle);

/*!
 * @brief write word to IOMEM DSP memeory  .
 *
 * @param handle TFA9896 codec handle.
 * @param address to be written.
 * @param value value write.
 * @param memtype to be written.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_DSP_Write_Mem_Word(tfa9896_handle_t *handle, unsigned short address, int value, int memtype);

/*!
 * @brief read a hardware regsiter .
 *
 * @param handle TFA9896 codec handle.
 * @param subaddress register address.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_ReadRegister(tfa9896_handle_t *handle, uint8_t subaddress, unsigned short *value);

/*!
 * @brief write a hardware register .
 *
 * @param handle TFA9896 codec handle.
 * @param subaddress register address.
 * @param value value to write.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_WriteRegister(tfa9896_handle_t *handle, uint8_t subaddress, uint16_t value);

/*!
 * @brief mute/unmute TFA9896 codec
 *
 * @param handle TFA9896 codec handle.
 * @param mute mute mode.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetMute(tfa9896_handle_t *handle, tfa9896_mute_t mute);

/*!
 * @brief Set amplifier volume.
 * @param handle TFA9896 codec handle.
 * @param volume_level volume level.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetVolume(tfa9896_handle_t *handle, uint8_t volume_level);

/*!
 * @brief set OVP in bypass .
 *
 * @param handle TFA98xx codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetOVPBypass(tfa9896_handle_t *handle);

/*!
 * @brief Initialize TFA9896.
 *
 * @param handle TFA98xx codec handle.
 * @param tfa9896Config Codec configuration.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_Init(tfa9896_handle_t *handle, tfa9896_config_t *tfa9896Config);

/*!
 * @brief DeInitilize TFA9896.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_Deinit(tfa9896_handle_t *handle);

/*!
 * @brief read a hardware regsiter .
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress register address.
 * @param value read out register value.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_ReadRegister(tfa9896_handle_t *handle, uint8_t subaddress, unsigned short *value);
/*!
 * @brief write a hardware register .
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress register address.
 * @param value value to write.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_WriteRegister(tfa9896_handle_t *handle, uint8_t subaddress, uint16_t value);
/*!
 * @brief set audio input format .
 *
 * @param handle TFA98xx codec handle.
 * @param mclk master clock frequency
 * @param sampleRate to be set.
 * @param bitWidth to be set.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetFormat(tfa9896_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth);
/*!
 * @brief power-on/off TFA98xx device.
 *
 * @param handle TFA98xx codec handle.
 * @param powerdown to on/off
 */
void TFA9896_Powerdown(tfa9896_handle_t *handle, int powerdown);

/*!
 * @brief mute/unmute TFA98XX codec
 *
 * @param handle TFA98xx codec handle.
 * @param mute mute mode.
 * @return Returns ::kStatus_TFA9896_Ok if success, otherwise returns error code.
 */
status_t TFA9896_SetMute(tfa9896_handle_t *handle, tfa9896_mute_t mute);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_TFA9896_H_ */
