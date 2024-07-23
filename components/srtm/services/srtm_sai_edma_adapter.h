/*
 * Copyright 2017-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_SAI_EDMA_ADAPTER_H__
#define __SRTM_SAI_EDMA_ADAPTER_H__

#include "srtm_audio_service.h"
#include "fsl_sai_edma.h"

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef SRTM_SAI_EDMA_LOCAL_BUF_ENABLE
#define SRTM_SAI_EDMA_LOCAL_BUF_ENABLE (0)
#endif

#ifndef SRTM_SAI_EDMA_CONFIG_RX_ENABLE
#define SRTM_SAI_EDMA_CONFIG_RX_ENABLE (1)
#endif

#if SRTM_SAI_EDMA_LOCAL_BUF_ENABLE
#ifndef SRTM_SAI_EDMA_MAX_LOCAL_BUF_PERIODS
#define SRTM_SAI_EDMA_MAX_LOCAL_BUF_PERIODS (4U)
#endif
#define SRTM_SAI_EDMA_MAX_LOCAL_PERIOD_ALIGNMENT      (4U)
#define SRTM_SAI_EDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK (SRTM_SAI_EDMA_MAX_LOCAL_PERIOD_ALIGNMENT - 1U)
#endif

typedef struct _srtm_sai_edma_config
{
    sai_transceiver_t config;
    uint32_t mclk;
    uint32_t dmaChannel;
    bool stopOnSuspend;
    uint32_t guardTime; /* TX ONLY guardTime (ms): M core needs to make sure there is enough time for A core wake up
                           from suspend and fill the DDR buffer again. The time should not less than the guardTime */
    uint32_t threshold; /* threshold period number: under which will trigger periodDone notification. */
} srtm_sai_edma_config_t;

#if SRTM_SAI_EDMA_LOCAL_BUF_ENABLE
typedef struct _srtm_sai_edma_local_buf
{
    uint8_t *buf;
    uint32_t bufSize;   /* bytes of the whole local buffer */
    uint32_t periods;   /* periods in local buffer */
    uint32_t threshold; /* Threshold period number: under which will trigger copy from share buf to local buf
                           in playback case. */
} srtm_sai_edma_local_buf_t;
#endif

/*!
 * @brief The callback function pointer.  Voice data can be passed to application via callback when the host side is
 * suspend. The callback is also a notification to the application for the host side resumes from suspend when the data
 * and bytes are 0(NULL).
 */
typedef void (*srtm_sai_edma_data_callback_t)(srtm_sai_adapter_t adapter, void *data, uint32_t bytes, void *params);

/*!
 * @brief The callback function pointer.  Allow application to do some preparation before copy data from/to DDR, such
 * as put DDR out of retention
 */
typedef void (*srtm_sai_edma_pre_copy_callback_t)(void);

/*!
 * @brief The callback function pointer.  Allow application to do some clean up after copy data to/from DDR, such as
 * put DDR into retention again
 */
typedef void (*srtm_sai_edma_post_copy_callback_t)(void);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SAI EDMA adapter.
 *
 * @param sai SAI base address.
 * @param dma DMA base address.
 * @param txConfig SAI Tx channel configuration.
 * @param rxConfig SAI Rx channel configuration.
 * @return SRTM SAI EDMA adapter on success or NULL on failure.
 */
srtm_sai_adapter_t SRTM_SaiEdmaAdapter_Create(I2S_Type *sai,
                                              void *dma,
                                              srtm_sai_edma_config_t *txConfig,
                                              srtm_sai_edma_config_t *rxConfig);

/*!
 * @brief Destroy SAI EDMA adapter.
 *
 * @param adapter SAI EDMA adapter to destroy.
 */
void SRTM_SaiEdmaAdapter_Destroy(srtm_sai_adapter_t adapter);

#if SRTM_SAI_EDMA_LOCAL_BUF_ENABLE
/*!
 * @brief Set local buffer to use in DMA transfer. If local buffer is set, the audio data will be copied
 * from shared buffer to local buffer and then transfered to I2S interface. Otherwise the data will be
 * transfered from shared buffer to I2S interface directly.
 * NOTE: it must be called before service start.
 *
 * @param adapter SAI EDMA adapter to set.
 * @param localBuf Local buffer information to be set to the adapter TX path.
 */
void SRTM_SaiEdmaAdapter_SetTxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_edma_local_buf_t *localBuf);

/*!
 * @brief Set local buffer to use in DMA transfer. If local buffer is set, the audio data will be transfered
 * from the I2S interface to local buffer and then copied from local buffer to shared buffer. Otherwise the data will be
 * transfered from I2S interface to shared buffer directly.
 * NOTE: it must be called before service start.
 *
 * @param adapter SAI EDMA adapter to set.
 * @param localBuf Local buffer information to be set to the adapter RX path.
 */
void SRTM_SaiEdmaAdapter_SetRxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_edma_local_buf_t *localBuf);

/*!
 * @brief Set callback function for preparing work (such as init DDR controller) before accessing shared buffer.
 * NOTE: it must be called before service start.
 *
 * @param adapter SAI EDMA adapter to set.
 * @param preCopyCallback Callback funciton pointer, which will be called when about to access shared buffer in adapter
 * TX path.
 */
void SRTM_SaiEdmaAdapter_SetTxPreCopyCallback(srtm_sai_adapter_t adapter,
                                              srtm_sai_edma_pre_copy_callback_t preCopyCallback);

/*!
 * @brief Set callback function for cleanup work (such as shutdown DDR controller) after accessing shared buffer.
 * NOTE: it must be called before service start.
 *
 * @param adapter SAI EDMA adapter to set.
 * @param postCopyCallback Callback funciton pointer, which will be called after accessing shared buffer in adapter TX
 * path.
 */
void SRTM_SaiEdmaAdapter_SetTxPostCopyCallback(srtm_sai_adapter_t adapter,
                                               srtm_sai_edma_post_copy_callback_t postCopyCallback);
#endif

/*!
 * @brief Get the audio service status.
 *
 * @param adapter SAI EDMA adapter instance.
 * @param pTxState Transfer status pointer.
 * @param pRxState Receiver status pointer.
 */
void SRTM_SaiEdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter,
                                              srtm_audio_state_t *pTxState,
                                              srtm_audio_state_t *pRxState);

/*!
 * @brief When the host driver suspends, voice data can be passed to application via callback.
          When the host driver is waking up, the notfication is sent via callback.
 *        The callback is called in SRTM dispatcher task context and should not cost much time.
 *
 * @param adapter SAI EDMA adapter instance.
 * @param cb Callback function pointer.
 * @param param Callback function argument to be passed back to applicaiton.
 */
void SRTM_SaiEdmaAdapter_SetDataHandlerOnHostSuspend(srtm_sai_adapter_t adapter,
                                                     srtm_sai_edma_data_callback_t cb,
                                                     void *param);

/*!
 * @brief When key word detected, voice data will be sent to host again.
 *
 * @param adapter SAI EDMA adapter instance.
 * @param cb Callback function pointer.
 * @param params Callback function argument to be passed back to applicaiton.
 */
void SRTM_SaiEdmaAdapter_ResumeHost(srtm_sai_adapter_t adapter);
#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SAI_EDMA_ADAPTER_H__ */
