/*
 * Copyright 2017-2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_AUDIO_SERVICE_H__
#define __SRTM_AUDIO_SERVICE_H__

#include "srtm_service.h"

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief Switch to disable Audio service debugging messages. */
#ifndef SRTM_AUDIO_SERVICE_DEBUG_OFF
#define SRTM_AUDIO_SERVICE_DEBUG_OFF (0)
#endif

#if SRTM_AUDIO_SERVICE_DEBUG_OFF
#undef SRTM_DEBUG_VERBOSE_LEVEL
#define SRTM_DEBUG_VERBOSE_LEVEL SRTM_DEBUG_VERBOSE_NONE
#endif

/* The preallocated prcedure messages for use in ISR. */
#ifndef SRTM_AUDIO_SERVICE_CONFIG_PROC_NUMBER
#define SRTM_AUDIO_SERVICE_CONFIG_PROC_NUMBER (4U)
#endif

typedef enum
{
    SRTM_AudioDirRx = 0U,
    SRTM_AudioDirTx = 1U,
} srtm_audio_dir_t;

typedef enum
{
    SRTM_AudioStateClosed  = 0U,
    SRTM_AudioStateOpened  = 1U,
    SRTM_AudioStateStarted = 2U,
} srtm_audio_state_t;

/*!@brief Define the format info which aligned with Linux side in the SRTM Audio service. */
typedef enum
{
    SRTM_Audio_Stereo16Bits = 0U,
    SRTM_Audio_Stereo24Bits = 1U,
    SRTM_Audio_Stereo32Bits = 2U,
    SRTM_Audio_DSD8bits     = 48U,
    SRTM_Audio_DSD16bits    = 49U,
    SRTM_Audio_DSD32bits    = 50U,
} srtm_audio_format_type_t;

typedef struct _audio_format
{
    srtm_audio_format_type_t format;
    uint8_t bitwidth;
} srtm_audio_format_map_t;

/*!@brief Define the format numbers used in the SRTM Audio service. */
#define FORMAT_NUM_USED (6)

extern srtm_audio_format_map_t saiFormatMap[FORMAT_NUM_USED];
/**
 * @brief SRTM SAI adapter structure pointer.
 */
typedef struct _srtm_sai_adapter *srtm_sai_adapter_t;

/**
 * @brief SRTM Audio Codec adapter structure pointer.
 */
typedef struct _srtm_codec_adapter *srtm_codec_adapter_t;

/**
 * @brief SRTM SAI adapter structure
 */
struct _srtm_sai_adapter
{
    /* Bound service */
    srtm_service_t service;

    /* Interfaces implemented by Audio service. */
    srtm_status_t (*periodDone)(srtm_service_t service, srtm_audio_dir_t dir, uint8_t index, uint32_t periodIdx);

    /* Interfaces implemented by SAI adapter. */
    srtm_status_t (*open)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*start)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*pause)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*restart)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*stop)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*close)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*setParam)(srtm_sai_adapter_t adapter,
                              srtm_audio_dir_t dir,
                              uint8_t index,
                              uint8_t format,
                              uint8_t channels,
                              uint32_t srate);
    srtm_status_t (*setBuf)(srtm_sai_adapter_t adapter,
                            srtm_audio_dir_t dir,
                            uint8_t index,
                            uint8_t *bufAddr,
                            uint32_t bufSize,
                            uint32_t periodSize,
                            uint32_t periodIdx);
    srtm_status_t (*suspend)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*resume)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index);
    srtm_status_t (*getBufOffset)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint32_t *pOffset);
    srtm_status_t (*periodReady)(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint32_t periodIdx);
};

/**
 * @brief SRTM Audio Codec adapter structure
 */
struct _srtm_codec_adapter
{
    /* Interfaces implemented by Audio Codec adapter. */
    srtm_status_t (*setParam)(srtm_codec_adapter_t adapter, uint8_t index, uint8_t format, uint32_t srate);
    srtm_status_t (*setReg)(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t regVal);
    srtm_status_t (*getReg)(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t *pRegVal);
};

/**
 * @brief SRTM Audio payload structure
 */
SRTM_ANON_DEC_BEGIN
SRTM_PACKED_BEGIN struct _srtm_audio_payload
{
    uint8_t index;
    union
    {
        uint8_t format;
        uint8_t retCode;
    };
    uint8_t channels;
    union
    {
        uint32_t bufOffset;
        uint32_t srate;
    };
    union
    {
        uint32_t bufAddr;
        uint32_t reg;
    };
    union
    {
        uint32_t bufSize;
        uint32_t regVal;
    };
    uint32_t periodSize;
    uint32_t periodIdx;
} SRTM_PACKED_END;
SRTM_ANON_DEC_END

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create audio service and register sai/codec adapters as index 0 audio interface.
 *
 * @param sai digital audio driver adapter.
 * @param codec analog audio codec adapter.
 * @return SRTM service handle on success and NULL on failure.
 */
srtm_service_t SRTM_AudioService_Create(srtm_sai_adapter_t sai, srtm_codec_adapter_t codec);

/*!
 * @brief Destroy audio service.
 *
 * @param service SRTM service to destroy.
 */
void SRTM_AudioService_Destroy(srtm_service_t service);

/*!
 * @brief Reset audio service. This is used to stop all audio operations and return to initial state
 *  for corresponding core.
 *
 * @param service SRTM service to reset.
 * @param core Identify which core is to be reset
 */
void SRTM_AudioService_Reset(srtm_service_t service, srtm_peercore_t core);

/*!
 * @brief Bind SRTM channel to audio adapter. The messages from the channel will be delivered to the adapter.
 * @param service SRTM service to set audio interface.
 * @param sai digital audio driver adapter.
 * @param channel SRTM channel to be bound to the adapters.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_AudioService_BindChannel(srtm_service_t service, srtm_sai_adapter_t sai, srtm_channel_t channel);

/*!
 * @brief Add audio adapters to audio service.
 * @param service SRTM service to set audio interface.
 * @param sai digital audio driver adapter.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_AudioService_AddAudioInterface(srtm_service_t service, srtm_sai_adapter_t sai);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_AUDIO_SERVICE_H__ */
