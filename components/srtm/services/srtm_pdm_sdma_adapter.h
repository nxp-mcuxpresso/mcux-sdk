/*
 * Copyright 2021-2022 NXP
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
#ifndef SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
#define SRTM_PDM_SDMA_ADAPTER_USE_HWVAD (1U)
#endif
#ifndef SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
#define SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER (1U)
#endif

/* Compile option to force usage of local and extra buffers.
 * Help saving code space by removing code needed when one of
 * these buffers is not used.
 * Will generate errors if application does not configure them.
 */
#ifndef SRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS
#define SRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS 0
#endif

#define SRTM_PDM_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT (4U)

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

/*! @brief PDM SDMA local buffer.  */
typedef struct _srtm_pdm_sdma_local_buf
{
    uint8_t *buf;              /*!< Pointer of the buffer */
    uint32_t bufSize;          /*!< bytes of the whole local buffer */
    uint32_t periods;          /*!< periods in local buffer */
    uint32_t samplesPerPeriod; /*!< number of samples per period (ignored if set to 0 - otherwise "periods" field is
re-computed based on the value and bufSize) */
    uint32_t threshold; /*!< Threshold period number: under which will trigger copy from local buffer to extra buffer if
                           extra buffer is used. Otherwise the local buffer is overwritten.*/
} srtm_pdm_sdma_local_buf_t;

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
/*! @brief PDM SDMA extra buffer. When the local buffer is full, the data can be copied to extra buffer.  */
typedef struct _srtm_pdm_sdma_ext_buf
{
    uint8_t *buf;     /*!< Pointer of the buffer */
    uint32_t bufSize; /*!< bytes of the whole extra buffer */
    uint32_t periods; /*!< periods in the buffer, it will be recalculated by the driver using given bufSize and local
                         buffer configuration. */
    uint32_t bufWriteDmaChannel; /*!< The extra buffer write DMA channel. */
    uint32_t bufReadDmaChannel;  /*!< The extra buffer read DMA channel. */
    uint8_t channelPriority;     /*!< The priority of DMA channel. */
} srtm_pdm_sdma_ext_buf_t;
#endif

#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
typedef enum _srtm_pdm_hwvad_mode
{
    kSRTM_PDM_Hwvad_Disabled          = 0U,
    kSRTM_PDM_Hwvad_EnergyBasedMode   = 1U,
    kSRTM_PDM_Hwvad_EnvelopeBasedMode = 2U,
} srtm_pdm_hwvad_mode_t;

typedef struct _srtm_pdm_hwvad_config
{
    srtm_pdm_hwvad_mode_t mode;
    pdm_hwvad_config_t hwvadConfig;
    pdm_hwvad_noise_filter_t noiseFilterConfig;
    pdm_hwvad_zero_cross_detector_t zcdConfig;
    uint32_t signalGain;
} srtm_pdm_hwvad_config_t;

/*! @brief HWVAD callback function pointer. The callback is called when voice activity is detected by HWVAD.
 */
typedef void (*srtm_pdm_sdma_hwvad_callback_t)(srtm_sai_adapter_t adapter, void *params);
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_HWVAD */

/*! @brief The callback function pointer.  Voice data can be passed to application via callback when the host side is
 * suspend. The callback is also a notification to the application for the host side resumes from suspend when the data
 * and bytes are 0(NULL). */
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
 * @brief Set local buffer to use in DMA transfer. If local buffer is set, the audio data will be captured
 * and transfered to local buffer, then copied to share buffer. Otherwise the data will be
 * transfered from PDM interface to shared buffer directly.
 * NOTE: it must be called before service start.
 *
 * @param adapter PDM SDMA adapter to set.
 * @param localBuf Local buffer information to be set to the adapter RX path.
 */
void SRTM_PdmSdmaAdapter_SetRxLocalBuf(srtm_sai_adapter_t adapter, srtm_pdm_sdma_local_buf_t *localBuf);

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
/*!
 * @brief Set extra buffer to be used when local buffer is full. The extra buffer could be in external memory.
 * If extra buffer is set, once the local buffer is full it will not be overwritten, instead the audio data in the local
 * buffer will be copied to the extra buffer, then copied to the shared buffer.
 * NOTE: It used only if local buffer is set by SRTM_PdmSdmaAdapter_SetRxLocalBuf and it must be called before service
 * start.
 *
 * @param adapter PDM SDMA adapter to set.
 * @param extBuf extra buffer information to be set to the adapter RX path.
 */
void SRTM_PdmSdmaAdapter_SetRxExtBuf(srtm_sai_adapter_t adapter, srtm_pdm_sdma_ext_buf_t *extBuf);
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER */

/*!
 * @brief When the host driver suspends, voice data can be passed to application via callback.
 *        When the host driver is waking up, the notfication is sent via callback.
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

/*!
 * @brief get audio format currently configured on an adapter.
 *
 * @return audio format setting
 */
srtm_audio_format_type_t SRTM_PdmSdmaAdapter_GetDataFormat(srtm_sai_adapter_t adapter);

#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD

/* clang-format off */
/*!
 * @brief Setup HWVAD. This function is used to configure the HWVAD function of PDM module, the API should be called
 * before the start of PDM capture. Once successfully configured and HWVAD mode is not kSRTM_PDM_Hwvad_Disabled mode,
 * the HWVAD will be enabled when the PDM capture starts. SRTM_PdmSdmaAdapter_EnableHwvad can be used to disable or
 * re-enable the HWVAD function during capture.
 * Sample configurations for EnvelopeBasedMode,
 * code
 * static srtm_pdm_hwvad_config_t pdm_hwvad_config = {
 *     .mode = kSRTM_PDM_Hwvad_EnvelopeBasedMode,
 *     .hwvadConfig.channel = 0U,
 *     .hwvadConfig.initializeTime = 10U,
 *     .hwvadConfig.cicOverSampleRate = 0U,
 *     .hwvadConfig.inputGain = 0U,
 *     .hwvadConfig.frameTime = 10U,
 *     .hwvadConfig.cutOffFreq        = kPDM_HwvadHpfBypassed,
 *     .hwvadConfig.enableFrameEnergy = false,
 *     .hwvadConfig.enablePreFilter   = true,
 *     .noiseFilterConfig.enableAutoNoiseFilter = false,
 *     .noiseFilterConfig.enableNoiseMin        = true,
 *     .noiseFilterConfig.enableNoiseDecimation = true,
 *     .noiseFilterConfig.noiseFilterAdjustment = 0U,
 *     .noiseFilterConfig.noiseGain             = 7U,
 *     .noiseFilterConfig.enableNoiseDetectOR   = true,
 *     .signalGain = 0U,
 *  };
 * code
 * @param adapter PDM SDMA adapter instance.
 * @param hwvadConfig The HWVAD configuration structure.
 * @param cb The callback function pointer.
 * @param param Callback function argument to be passed back to applicaiton.
 * @return Configured the HWVAD successfully or with failure.
 */
/* clang-format on */
srtm_status_t SRTM_PdmSdmaAdapter_ConfigHwvad(srtm_sai_adapter_t adapter,
                                              const srtm_pdm_hwvad_config_t *hwvadConfig,
                                              srtm_pdm_sdma_hwvad_callback_t cb,
                                              void *param);

/*!
 * @brief Enable/Disable the HWVAD, this API is used to enable/disable the HWVAD during PDM capture.
 *
 * @param adapter PDM SDMA adapter instance.
 * @param enable Enable or disable the HWVAD.
 */
void SRTM_PdmSdmaAdapter_EnableHwvad(srtm_sai_adapter_t adapter, bool enable);
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_HWVAD */
/*******************************************************************************
 * Definitions from other files
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SAI_SDMA_ADAPTER_H__ */
