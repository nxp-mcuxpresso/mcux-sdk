/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SRTM_PDM_SDMA_ADAPTER_H_
#define _SRTM_PDM_SDMA_ADAPTER_H_

#include "srtm_audio_service.h"
#include "fsl_pdm_sdma.h"

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Extra device intitialize function for PDM SDMA adapter. */
typedef void (*pdm_dev_init)(bool enable);
/*! @brief Extra device configuration function based on format and sample rate, return PMD clock source in HZ. */
typedef uint32_t (*pdm_dev_conf)(srtm_audio_format_type_t format, uint32_t srate);

/*! @brief Misc configuration structure. */
typedef struct _pdm_misc_set
{
    pdm_dev_init audioDevInit; /*!< Audio device init function. */
    pdm_dev_conf audioDevConf; /*!< config audio device based on format and sample rate, return source clock in HZ */
} pdm_misc_set_t;

/*! @brief PDM SDMA configuration.  */
typedef struct _srtm_pdm_sdma_config
{
    pdm_config_t config;                /*!< PDM user configuration. */
    pdm_channel_config_t channelConfig; /*!< PDM channel configurations. */
    uint32_t pdmSrcClk;                 /*!< PDM source clock in Hz. */
    uint32_t dmaChannel;                /*!< DMA channel. */
    uint8_t channelPriority;            /*!< The priority of DMA channel. */
    bool stopOnSuspend;                 /*!< Stop capture when received suspend command. */
    uint32_t eventSource;               /*!< DMA request source. */

    sdma_context_data_t rxContext;
    pdm_misc_set_t extendConfig;
} srtm_pdm_sdma_config_t;

/*! @brief The callback function pointer.  Voice data can be passed to application via callback when the host side is
 * suspend.*/
typedef void (*srtm_pdm_sdma_data_callback_t)(srtm_sai_adapter_t adapter, void *data, uint32_t bytes, void *params);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create PDM SDMA adapter.
 *
 * @param pdm PDM base address.
 * @param dma DMA base address.
 * @param rxConfig PDM Rx channel configuration.
 * @return SRTM PDM SDMA adapter on success or NULL on failure.
 */
srtm_sai_adapter_t SRTM_PdmSdmaAdapter_Create(PDM_Type *pdm, SDMAARM_Type *dma, srtm_pdm_sdma_config_t *rxConfig);

/*!
 * @brief Destroy PDM SDMA adapter.
 *
 * @param adapter PDM SDMA adapter to destroy.
 */
void SRTM_PdmSdmaAdapter_Destroy(srtm_sai_adapter_t adapter);

/*!
 * @brief Get the audio service status.
 * @param adapter PDM SDMA adapter.
 * @param pRxState status pointer.
 */
void SRTM_PdmSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter, srtm_audio_state_t *pRxState);

/*!
 * @brief When the host driver suspends, voice data can be passed to application via callback.
 *        The callback is called in SRTM dispatcher task context and should not cost much time.
 *
 * @param adapter PDM SDMA adapter instance.
 * @param cb Callback function pointer.
 * @param param Callback function argument to be passed back to applicaiton.
 */
void SRTM_PdmSdmaAdapter_SetDataHandlerOnHostSuspend(srtm_sai_adapter_t adapter,
                                                     srtm_pdm_sdma_data_callback_t cb,
                                                     void *param);

/*!
 * @brief When key word detected, voice data will be sent to host again.
 *
 * @param adapter PDM SDMA adapter instance.
 */
void SRTM_PdmSdmaAdapter_ResumeHost(srtm_sai_adapter_t adapter);
/*******************************************************************************
 * Definitions from other files
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SAI_SDMA_ADAPTER_H__ */
