/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_SAI_SDMA_ADAPTER_H__
#define __SRTM_SAI_SDMA_ADAPTER_H__

#include "srtm_audio_service.h"
#include "fsl_sai_sdma.h"
/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS           (4U)
#define SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT      (4U)
#define SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK (SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT - 1U)
/*!< @brief select the mclk based of sai  */
typedef enum _sai_mclk_type
{
    SRTM_CLK22M = 0U, /*!< configure the mclk to 22.5792Mhz or its multiple */
    SRTM_CLK24M = 1U, /*!< configure the mclk to 24.5760Mhz or its multiple */
} mclk_type_t;
/*!< reconfig sai for DSD mode */
typedef void (*dsd_saiSetting)(void);
/*!< reconfig sai for PCM mode */
typedef void (*pcm_saiSetting)(void);
/*!< reconfig the sai clock  */
typedef uint32_t (*sai_clkSetting)(mclk_type_t type);
/*!< clock gate operation  */
typedef void (*clockEnable)(bool isEnable);
/*!< init audio devices  */
typedef void (*initDev)(bool enable);

typedef struct _audio_misc_set
{
    dsd_saiSetting dsdSaiSetting;
    pcm_saiSetting pcmSaiSetting;
    sai_clkSetting clkSetting; /* Set the MCLK of SAI per the requirement of different sample rate music stream. */
    clockEnable clkGate;
    initDev audioDevInit;
} audio_misc_set_t;
typedef struct _srtm_sai_sdma_config
{
    sai_transceiver_t config;
    sai_master_clock_t mclkConfig;
    uint8_t dataLine1; /* SAI data line1 number for transaction, use the dataLine1 by default for PCM music stream. */
    uint8_t dataLine2; /* SAI data line2 number for transaction, use the dataLine2 as the another channel of DSD music
                          stream. */
    uint32_t dmaChannel;
    uint8_t ChannelPriority;
    bool stopOnSuspend;
    uint32_t eventSource;
    uint32_t guardTime; /* guardTime (unit:ms): M core needs to make sure there is enough time for A core wake up from
                           suspend and fill the DDR buffer again. The time should not less than the guardTime */
    uint32_t threshold; /* threshold: under which will trigger periodDone notification. */
    sdma_context_data_t txcontext;
    sdma_context_data_t rxcontext;
    audio_misc_set_t extendConfig;
} srtm_sai_sdma_config_t;

typedef struct _srtm_sai_sdma_local_buf
{
    uint8_t *buf;
    uint32_t bufSize;   /* bytes of the whole local buffer */
    uint32_t periods;   /* periods in local buffer */
    uint32_t threshold; /* Threshold period number: under which will trigger copy from share buf to local buf
                           in playback case. */
} srtm_sai_sdma_local_buf_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SAI SDMA adapter.
 *
 * @param sai SAI base address.
 * @param dma DMA base address.
 * @param txConfig SAI Tx channel configuration.
 * @param rxConfig SAI Rx channel configuration.
 * @return SRTM SAI SDMA adapter on success or NULL on failure.
 */
srtm_sai_adapter_t SRTM_SaiSdmaAdapter_Create(I2S_Type *sai,
                                              SDMAARM_Type *dma,
                                              srtm_sai_sdma_config_t *txConfig,
                                              srtm_sai_sdma_config_t *rxConfig);

/*!
 * @brief Destroy SAI SDMA adapter.
 *
 * @param adapter SAI SDMA adapter to destroy.
 */
void SRTM_SaiSdmaAdapter_Destroy(srtm_sai_adapter_t adapter);

/*!
 * @brief Set local buffer to use in DMA transfer. If local buffer is set, the audio data will be copied
 * from shared buffer to local buffer and then transfered to I2S interface. Otherwise the data will be
 * transfered from shared buffer to I2S interface directly.
 * NOTE: it must be called before service start.
 *
 * @param adapter SAI SDMA adapter to set.
 * @param localBuf Local buffer information to be set to the adapter TX path.
 */
void SRTM_SaiSdmaAdapter_SetTxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_sdma_local_buf_t *localBuf);
/*!
 * @brief Get the audio service status.
 * @param sai adapter value.
 * @param Transfer status pointer.
 * @param Receiver status pointer.
 */
void SRTM_SaiSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter,
                                              srtm_audio_state_t *pTxState,
                                              srtm_audio_state_t *pRxState);
/*******************************************************************************
 * Definitions from other files
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SAI_SDMA_ADAPTER_H__ */
