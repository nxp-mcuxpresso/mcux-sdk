/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xspi.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xspi"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FREQ_1MHz        (1000000UL)
#define XSPI_LUT_KEY_VAL (0x5AF05AF0UL)

/*! brief Common sets of flags used by the driver, _xspi_flag_constants. */
enum kXSPI_Flags
{
    /*! IRQ sources enabled by the non-blocking transactional API. */
    kIrqFlags = kXSPI_TxBufferFillFlag | kXSPI_TxBufferUnderrunFlag | kXSPI_RxBufferOverflowFlag |
                kXSPI_RxBufferDrainFlag | kXSPI_IllegalInstructionErrorFlag | kXSPI_IpCmdtriggerErrorFlag,

    /*! IP CMD Errors to check for. */
    kIpcmdErrorFlags = kXSPI_IllegalInstructionErrorFlag | kXSPI_IpCmdtriggerErrorFlag,

    kFlashProtectionErrorFlags = kXSPI_FradMatchErrorFlag | kXSPI_FradnAccErrorFlag | kXSPI_IpsErrorFlag |
                                 kXSPI_Tg0SfarErrorFlag | kXSPI_Tg1SfarErrorFlag | kXSPI_TgnIpcrErrorFlag,
};

/* XSPI FSM status. */
enum
{
    kXSPI_TransactionIsGrantedXSPIsBusy = 0x0U, /*!< Transaction is granted, but XSPI is busy
                                                  with any previous DMA transaction is ongoing*/
    kXSPI_TbdrLockIsOpen           = 0x1U,      /*!< TBDR lock is open. IPS master can write in TBDR.*/
    kXSPI_WriteTransferIsTriggered = 0x2U,      /*!< Write transfer is triggered. SEQID is written to XSPI.*/
    kXSPI_ReadTransferIsTriggered  = 0x3U,      /*!< Read transfer is triggered. SEQID is written to XSPI.*/
};

/* XSPI transfer state, _xspi_transfer_state. */
enum
{
    kXSPI_Idle      = 0x0U, /*!< Transfer is done. */
    kXSPI_BusyWrite = 0x1U, /*!< XSPI is busy write transfer. */
    kXSPI_BusyRead  = 0x2U, /*!< XSPI is busy write transfer. */
};

/*! brief Typedef for interrupt handler. */
typedef void (*xspi_isr_t)(XSPI_Type *base, xspi_handle_t *handle);

#define XSPI_TG_MDAD_REG_OFFSET_ARRAY                                                   \
    {                                                                                   \
        (uint32_t) offsetof(XSPI_Type, TG0MDAD), (uint32_t)offsetof(XSPI_Type, TG1MDAD) \
    }

#define XSPI_FRAD_WORD0_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD0), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD0),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD0), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD0), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD0), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD0), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD0), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD0), \
    }

#define XSPI_FRAD_WORD1_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD1), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD1),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD1), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD1), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD1), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD1), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD1), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD1), \
    }

#define XSPI_FRAD_WORD2_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD2), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD2),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD2), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD2), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD2), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD2), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD2), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD2), \
    }

#define XSPI_FRAD_WORD3_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD3), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD3),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD3), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD3), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD3), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD3), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD3), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD3), \
    }

#define XSPI_FRAD_WORD4_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD4), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD4),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD4), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD4), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD4), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD4), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD4), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD4), \
    }

#define XSPI_FRAD_WORD5_REG_OFFSET_ARRAY                                                            \
    {                                                                                               \
        (uint32_t) offsetof(XSPI_Type, FRAD0_WORD5), (uint32_t)offsetof(XSPI_Type, FRAD1_WORD5),    \
            (uint32_t)offsetof(XSPI_Type, FRAD2_WORD5), (uint32_t)offsetof(XSPI_Type, FRAD3_WORD5), \
            (uint32_t)offsetof(XSPI_Type, FRAD4_WORD5), (uint32_t)offsetof(XSPI_Type, FRAD5_WORD5), \
            (uint32_t)offsetof(XSPI_Type, FRAD6_WORD5), (uint32_t)offsetof(XSPI_Type, FRAD7_WORD5), \
    }

#define XSPI_TGSFAR_REG_OFFSET                                                              \
    {                                                                                       \
        offsetof(XSPI_Type, TGSFAR), offsetof(XSPI_Type, SUB_REG_MDAM_ARRAY[0].TGSFAR_SUB), \
    }

#define XSPI_TGSFARS_REG_OFFSET                                                               \
    {                                                                                         \
        offsetof(XSPI_Type, TGSFARS), offsetof(XSPI_Type, SUB_REG_MDAM_ARRAY[0].TGSFARS_SUB), \
    }

#define XSPI_TGIPCRS_REG_OFFSET                                                               \
    {                                                                                         \
        offsetof(XSPI_Type, TGIPCRS), offsetof(XSPI_Type, SUB_REG_MDAM_ARRAY[0].TGIPCRS_SUB), \
    }

#define XSPI_SFP_TG_IPCR_REG_OFFSET                                                                   \
    {                                                                                                 \
        offsetof(XSPI_Type, SFP_TG_IPCR), offsetof(XSPI_Type, SUB_REG_MDAM_ARRAY[0].SFP_TG_SUB_IPCR), \
    }

#define XSPI_SFP_TG_SFAR_REG_OFFSET                                                                   \
    {                                                                                                 \
        offsetof(XSPI_Type, SFP_TG_SFAR), offsetof(XSPI_Type, SUB_REG_MDAM_ARRAY[0].SFP_TG_SUB_SFAR), \
    }

#define XSPI_MCR_X16_MODE_MASK  (0x300000UL)
#define XSPI_MCR_X16_MODE_SHIFT (20UL)
#define XSPI_MCR_X16_MODE(x)    (((uint32_t)(x) << XSPI_MCR_X16_MODE_SHIFT) & XSPI_MCR_X16_MODE_MASK)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint8_t XSPI_GetPPWBFromPageSize(uint32_t pageSize);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to xspi bases for each instance. */
static XSPI_Type *const s_xspiBases[] = XSPI_BASE_PTRS;

/*! brief Pointers to xspi IRQ number for each instance. */
static const IRQn_Type s_xspiIrqs[] = XSPI_IRQS;

/*! brief Pointers to xspi amba base for each instance. */
static uint32_t s_xspiAmbaBase[] = XSPI_AMBA_BASES;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_xspiClock[] = XSPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! brief Pointers to XSPI resets for each instance. */
static const reset_ip_name_t s_xspiResets[] = XSPI_RSTS;

static uint32_t s_tgSfarsRegOffset[]     = XSPI_TGSFARS_REG_OFFSET;
static uint32_t s_tgIpcrsRegOffset[]     = XSPI_TGIPCRS_REG_OFFSET;
static uint32_t s_sfpTgIpcrRegOffset[]   = XSPI_SFP_TG_IPCR_REG_OFFSET;
static uint32_t s_sfpTgIpSfarRegOffset[] = XSPI_SFP_TG_SFAR_REG_OFFSET;
static uint32_t s_tgMdadRegOffset[]      = XSPI_TG_MDAD_REG_OFFSET_ARRAY;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* To avoid compiler opitimizing this API into memset() in library. */
#if defined(__ICCARM__)
#pragma optimize = none
#endif /* defined(__ICCARM__) */

static uint8_t XSPI_GetPPWBFromPageSize(uint32_t pageSize)
{
    uint8_t ppwbValue = 0U;

    switch (pageSize)
    {
        case 64UL:
        {
            ppwbValue = 6U;
            break;
        }
        case 128UL:
        {
            ppwbValue = 7U;
            break;
        }
        case 256UL:
        {
            ppwbValue = 8U;
            break;
        }
        case 512UL:
        {
            ppwbValue = 9U;
            break;
        }
        case 1024UL:
        {
            ppwbValue = 10U;
            break;
        }
        default:
        {
            /* Input pageSize not included. */
            assert(false);
            break;
        }
    }

    return ppwbValue;
}

/******************* Initialization And Deinitialization Functional Interfaces Start ***********************/
/*!
 * brief Get the instance number for XSPI.
 *
 * param base XSPI base pointer.
 */
uint32_t XSPI_GetInstance(XSPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_xspiBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_xspiBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_xspiBases));

    return instance;
}

/*!
 * brief Check and clear IP command execution errors.
 *
 * param base XSPI base pointer.
 * param status interrupt status.
 */
status_t XSPI_CheckAndClearError(XSPI_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. */
    status &= (uint32_t)kFlashProtectionErrorFlags;
    if (0U != status)
    {
        /* Select the correct error code.. */
        if (0U != (status & (uint32_t)kXSPI_SequenceExecutionTimeoutFlag))
        {
            result = kStatus_XSPI_SequenceExecutionTimeout;
            /* Clear the flags. */
            base->ERRSTAT |= (uint32_t)kXSPI_SequenceExecutionTimeoutFlag;
        }
        else if (0U != ((status & (uint32_t)kXSPI_FradMatchErrorFlag) | (status & (uint32_t)kXSPI_FradnAccErrorFlag)))
        {
            result = kStatus_XSPI_FradCheckError;
            /* Clear the flags. */
            if (0U != (status & (uint32_t)kXSPI_FradMatchErrorFlag))
            {
                base->ERRSTAT |= (uint32_t)kXSPI_FradMatchErrorFlag;
            }
            else
            {
                base->ERRSTAT |= (uint32_t)kXSPI_FradnAccErrorFlag;
            }
        }
        else if (0U != (status & (uint32_t)kXSPI_IpsErrorFlag))
        {
            result = kStatus_XSPI_IpsBusTransError;
            /* Clear the flags. */
            base->IPSERROR |= XSPI_IPSERROR_CLR_MASK;
        }
        else if (0U != ((status & (uint32_t)kXSPI_Tg0SfarErrorFlag) | (status & (uint32_t)kXSPI_Tg1SfarErrorFlag) |
                        (status & (uint32_t)kXSPI_TgnIpcrErrorFlag)))
        {
            result = kStatus_XSPI_TgQueueWritingError;
            /* Clear the flags. */
            if (0U != ((status & (uint32_t)kXSPI_Tg0SfarErrorFlag) | (status & (uint32_t)kXSPI_Tg1SfarErrorFlag)))
            {
                base->TGSFARS |= XSPI_TGSFARS_CLR_MASK;
            }
            else
            {
                base->TGIPCRS |= XSPI_TGIPCRS_CLR_MASK;
            }
        }
        else
        {
            assert(false);
        }

        /* Reset fifos. These flags clear automatically. */
        base->MCR |= XSPI_MCR_CLR_RXF_MASK;
        base->MCR |= XSPI_MCR_CLR_TXF_MASK;
    }

    return result;
}

/*!
 * brief Initializes the XSPI module and internal state.
 *
 * This function  configures the XSPI with the
 * input configure parameters. Users should call this function before any XSPI operations.
 *
 * param base XSPI peripheral base address.
 * param config XSPI configure structure.
 */

void XSPI_Init(XSPI_Type *base, const xspi_config_t *ptrConfig)
{
    uint32_t tmp32 = 0UL;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the xspi clock */
    (void)CLOCK_EnableClock(s_xspiClock[XSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Reset the XSPI module */
    RESET_ReleasePeripheralReset(s_xspiResets[XSPI_GetInstance(base)]);

    /* Reset SFM, AHB domain and TG queue. */
    XSPI_SoftwareReset(base);

    /* Disable module before initialization. */
    XSPI_EnableModule(base, false);

    /* Clear AHB buffer, TX buffer, RX buffer. */
    XSPI_ClearAhbBuffer(base);
    XSPI_ClearTxBuffer(base);
    XSPI_ClearRxBuffer(base);

    /* If any flags are asserted, clear firstly. */
    tmp32 = base->FR;
    if (tmp32 != 0UL)
    {
        base->FR = tmp32;
    }

    XSPI_EnableDozeMode(base, ptrConfig->enableDoze);

    base->MCR = ((base->MCR) & (~XSPI_MCR_END_CFG_MASK)) | XSPI_MCR_END_CFG(ptrConfig->byteOrder);

    if (ptrConfig->ptrAhbAccessConfig != NULL)
    {
        (void)XSPI_SetAhbAccessConfig(base, ptrConfig->ptrAhbAccessConfig);
    }

    if (ptrConfig->ptrIpAccessConfig != NULL)
    {
        (void)XSPI_SetIpAccessConfig(base, ptrConfig->ptrIpAccessConfig);
    }

    /* Enable XSPI module. */
    XSPI_EnableModule(base, true);
}

/*!
 * brief Gets default settings for XSPI.
 *
 * param base XSPI peripheral base address.
 * param config XSPI configuration structure.
 * param devconfig Flash configuration parameters.

 */
void XSPI_GetDefaultConfig(xspi_config_t *ptrConfig)
{
    assert(ptrConfig != NULL);

    ptrConfig->byteOrder  = kXSPI_64BitLE;
    ptrConfig->enableDoze = false;

    if (ptrConfig->ptrAhbAccessConfig != NULL)
    {
        /* If ptrAhbAccessConfig is not NULL, it means AHB access feature will be used. */
        ptrConfig->ptrAhbAccessConfig->ahbAlignment                = kXSPI_AhbAlignmentNoLimit;
        ptrConfig->ptrAhbAccessConfig->ahbErrorPayload.highPayload = 0UL;
        ptrConfig->ptrAhbAccessConfig->ahbErrorPayload.lowPayload  = 0UL;
        ptrConfig->ptrAhbAccessConfig->ahbSplitSize                = kXSPI_AhbSplitSizeDisabled;

        for (uint8_t i = 0U; i < XSPI_BUFCR_COUNT; i++)
        {
            ptrConfig->ptrAhbAccessConfig->buffer[i].masterId = i;
            if (i == 3U)
            {
                ptrConfig->ptrAhbAccessConfig->buffer[i].enaPri.enableAllMaster = true;
            }
            else
            {
                ptrConfig->ptrAhbAccessConfig->buffer[i].enaPri.enablePriority = false;
            }
            ptrConfig->ptrAhbAccessConfig->buffer[i].bufferSize = 0x80U;

            ptrConfig->ptrAhbAccessConfig->buffer[i].ptrSubBuffer0Config = NULL;
            ptrConfig->ptrAhbAccessConfig->buffer[i].ptrSubBuffer1Config = NULL;
            ptrConfig->ptrAhbAccessConfig->buffer[i].ptrSubBuffer2Config = NULL;
            ptrConfig->ptrAhbAccessConfig->buffer[i].ptrSubBuffer3Config = NULL;
        }
        ptrConfig->ptrAhbAccessConfig->ptrAhbWriteConfig         = NULL;
        ptrConfig->ptrAhbAccessConfig->enableAHBPrefetch         = true;
        ptrConfig->ptrAhbAccessConfig->enableAHBBufferWriteFlush = false;
        ptrConfig->ptrAhbAccessConfig->ARDSeqIndex               = 0U;
    }

    if (ptrConfig->ptrIpAccessConfig != NULL)
    {
        /* If ptrAhbAccessConfig is not NULL, it means AHB access feature will be used. */
        /* In default settings, FRAD check and MDAD check are both disabled. */
        ptrConfig->ptrIpAccessConfig->ptrSfpMdadConfig               = NULL;
        ptrConfig->ptrIpAccessConfig->ptrSfpFradConfig               = NULL;
        ptrConfig->ptrIpAccessConfig->sfpArbitrationLockTimeoutValue = 0xFFFFFUL;
        ptrConfig->ptrIpAccessConfig->ipAccessTimeoutValue           = 0xFFFFUL;
    }
}

/*!
 * brief Deinitialize the XSPI module.
 *
 * Clears the XSPI state and  XSPI module registers.
 * param base XSPI peripheral base address.
 */
void XSPI_Deinit(XSPI_Type *base)
{
    XSPI_EnableModule(base, false);
    /* Reset peripheral. */
    XSPI_SoftwareReset(base);
}

/*! brief Updates the LUT table.
 *
 * param base XSPI peripheral base address.
 * param index From which index start to update. It could be any index of the LUT table, which
 * also allows user to update command content inside a command. Each command consists of up to
 * 10 instructions and occupy 4*32-bit memory.
 * param cmd Command sequence array.
 * param count Number of instruction-operand pairs.
 */
void XSPI_UpdateLUT(XSPI_Type *base, uint8_t index, const uint32_t *cmd, uint8_t count)
{
    assert(index < 80U);

    uint32_t i = 0;
    volatile uint32_t *lutBase;

    /* Wait for bus to be idle before changing flash configuration. */
    while (!XSPI_GetBusIdleStatus(base))
    {
    }

    /* Unlock LUT for update. */
    base->LUTKEY = XSPI_LUT_KEY_VAL;
    base->LCKCR  = 0x02;

    lutBase = &base->LUT[index];
    for (i = 0; i < count; i++)
    {
        *lutBase++ = *cmd++;
    }

    /* Lock LUT. */
    base->LUTKEY = XSPI_LUT_KEY_VAL;
    base->LCKCR  = 0x01;
}

/******************* Initialization And Deinitialization Functional Interfaces End ***********************/

/***************************** XSPI Controller Low-Level Inferfaces Start ********************************/
/*!
 * brief Reset Serial flash memory domain and AHB domain at the same time.
 *
 * note Resetting only the Serial flash memory domain and AHB domain may cause undesirable side effects.
 *
 * param base XSPI peripheral base address.
 */
void XSPI_ResetSfmAndAhbDomain(XSPI_Type *base)
{
    /* XSPI module must be enabled, before assert reset to domains. */
    XSPI_EnableModule(base, true);

    base->MCR |= XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK;
    for (uint8_t i = 0U; i < 6U; i++)
    {
        __NOP();
    }
    /* Before de-assert the software reset, XSPI module should be disabled. */
    XSPI_EnableModule(base, false);
    base->MCR &= ~(XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK);
    for (uint8_t i = 0U; i < 6U; i++)
    {
        __NOP();
    }
    /* After de-assert the software resets, XSPI module should be enabled. */
    XSPI_EnableModule(base, true);
}

/***************************** XSPI Controller Low-Level Inferfaces End ********************************/

/***************************** External Device Control Low-Level Interfaces Start ********************************/
/*!
 * brief Set Hyper bus X16 mode.
 *
 * param base XSPI peripheral base address.
 * param x16Mode Specify X16 mode.
 */
void XSPI_SetHyperBusX16Mode(XSPI_Type *base, xspi_hyper_bus_x16_mode_t x16Mode)
{
    bool isEnabled = false;

    if (XSPI_CheckModuleEnabled(base))
    {
        isEnabled = true;
        XSPI_EnableModule(base, false);
    }

    base->MCR = ((base->MCR) & (~XSPI_MCR_X16_MODE_MASK)) | XSPI_MCR_X16_MODE(x16Mode);

    if (isEnabled)
    {
        XSPI_EnableModule(base, true);
    }
}

/*!
 * brief Update DLL configuration.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrDllConfig Pointer to the DLL configuration.
 * param[in] enableDDR DDR mode is enabled or not.
 * param[in] enableX16Mode X16 mode is enabled or not.
 * param[in] xspiRootClk The frequency of xspi root clock, the unit is Hz.
 */
void XSPI_UpdateDllValue(XSPI_Type *base, xspi_dll_config_t *ptrDllConfig,
                        bool enableDDR, bool enableX16Mode, uint32_t xspiRootClk)
{
    uint32_t offsetDelayElementCount = 0UL;
    uint8_t tapNum              = ptrDllConfig->dllCustomDelayTapNum;
    bool enableCourseDelayLine8 = ptrDllConfig->enableCdl8;

    if (ptrDllConfig->useRefValue == true)
    {
        if (enableDDR)
        {
            tapNum                 = FSL_FEATURE_XSPI_DLL_REF_VALUE_DDR_DELAY_TAP_NUM;
            enableCourseDelayLine8 = true;
        }
        else
        {
            tapNum                 = FSL_FEATURE_XSPI_DLL_REF_VALUE_SDR_DELAY_TAP_NUM;
            enableCourseDelayLine8 = false;
        }
    }

    base->MCR |= XSPI_MCR_MDIS_MASK;
    base->SMPR = (((base->SMPR) & (~XSPI_SMPR_DLLFSMPFA_MASK)) | XSPI_SMPR_DLLFSMPFA(tapNum));
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    if (ptrDllConfig->dllMode == kXSPI_BypassMode)
    {
        /* In case of DLL mode is selected as Bypass mode. */
        uint32_t delayElementCoarseAdjust = 0UL;
        uint32_t delayElementFineAdjust   = 0UL;

        offsetDelayElementCount  = (uint32_t)((ptrDllConfig->useRefValue) ?
                                       FSL_FEATURE_XSPI_DLL_REF_VALUE_BYPASS_OFFSET_DELAY_ELEMENT_COUNT :
                                       (ptrDllConfig->dllCustomPara.bypassModePara.offsetDelayElementCount));
        delayElementCoarseAdjust = (uint32_t)((ptrDllConfig->useRefValue) ?
                                       FSL_FEATURE_XSPI_DLL_REF_VALUE_BYPASS_DELAY_ELEMENT_COARSE :
                                       (ptrDllConfig->dllCustomPara.bypassModePara.delayElementCoarseValue));
        delayElementFineAdjust   = (uint32_t)((ptrDllConfig->useRefValue) ?
                                       FSL_FEATURE_XSPI_DLL_REF_VALUE_BYPASS_DELAY_ELEMENT_FINE :
                                       (ptrDllConfig->dllCustomPara.bypassModePara.delayElementFineValue));

        base->DLLCR[0] &=
            ~(XSPI_DLLCR_SLAVE_AUTO_UPDT_MASK | XSPI_DLLCR_SLV_DLY_FINE_MASK | XSPI_DLLCR_SLV_DLY_COARSE_MASK |
              XSPI_DLLCR_SLV_FINE_OFFSET_MASK | XSPI_DLLCR_DLL_CDL8_MASK);
        /* Enable subordinate delay chain as bypass mode. */
        base->DLLCR[0] |= XSPI_DLLCR_SLV_EN_MASK | XSPI_DLLCR_SLV_DLL_BYPASS_MASK;
        /* program DLL to desired delay. */
        base->DLLCR[0] |=
            XSPI_DLLCR_SLV_DLY_FINE(delayElementFineAdjust) | XSPI_DLLCR_SLV_DLY_COARSE(delayElementCoarseAdjust) |
            XSPI_DLLCR_SLV_FINE_OFFSET(offsetDelayElementCount) | XSPI_DLLCR_DLL_CDL8(enableCourseDelayLine8);
        /* Load above settings into delay chain. */
        base->DLLCR[0] |= XSPI_DLLCR_SLV_UPD_MASK;

        while ((base->DLLSR & XSPI_DLLSR_SLVA_LOCK_MASK) == 0UL)
        {
        }
        base->DLLCR[0] &= ~XSPI_DLLCR_SLV_UPD_MASK;
    }
    else
    {
        /* In case of DLL mode is selected as auto update mode. */
        bool enableHighFreq                   = false;
        uint32_t refCounterValue               = 0UL;
        uint32_t resolutionValue               = 0UL;
        uint32_t tDiv16OffsetDelayElementCount = 0UL;

        enableHighFreq =
            (ptrDllConfig->useRefValue) ?
                ((xspiRootClk >= FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_FREQ_THRESHOLD) ? true : false) :
                ((bool)(ptrDllConfig->dllCustomPara.autoUpdateModoPara.enableHighFreq));
        refCounterValue = (uint32_t)((ptrDllConfig->useRefValue) ?
                              ((enableX16Mode) ? FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_X16_ENABLED_REF_COUNTER :
                                                 FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_X16_DISABLED_REF_COUNTER) :
                              (ptrDllConfig->dllCustomPara.autoUpdateModoPara.referenceCounter));
        resolutionValue = (uint32_t)((ptrDllConfig->useRefValue) ?
                              ((enableX16Mode) ? FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_X16_ENABLED_RES :
                                                 FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_X16_DISABLE_RES) :
                              (ptrDllConfig->dllCustomPara.autoUpdateModoPara.resolution));
        tDiv16OffsetDelayElementCount =
            (uint32_t)((ptrDllConfig->useRefValue) ?
                FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_T_DIV16_OFFSET_DELAY_ELEMENT_COUNT :
                (ptrDllConfig->dllCustomPara.autoUpdateModoPara.tDiv16OffsetDelayElementCount));
        offsetDelayElementCount = (uint32_t)((ptrDllConfig->useRefValue) ?
                                      FSL_FEATURE_XSPI_DLL_REF_VALUE_AUTOUPDATE_OFFSET_DELAY_ELEMENT_COUNT :
                                      (ptrDllConfig->dllCustomPara.autoUpdateModoPara.offsetDelayElementCount));

        base->DLLCR[0] &= ~(XSPI_DLLCR_SLV_DLL_BYPASS_MASK | XSPI_DLLCR_DLL_CDL8_MASK | XSPI_DLLCR_SLV_DLY_OFFSET_MASK |
                            XSPI_DLLCR_SLV_FINE_OFFSET_MASK | XSPI_DLLCR_DLLRES_MASK | XSPI_DLLCR_DLL_REFCNTR_MASK |
                            XSPI_DLLCR_FREQEN_MASK);
        /* Enable subordinate as auto update mode. */
        base->DLLCR[0] |= XSPI_DLLCR_SLV_EN_MASK | XSPI_DLLCR_SLAVE_AUTO_UPDT_MASK;
        /* program DLL to desired delay. */
        base->DLLCR[0] |= XSPI_DLLCR_DLLRES(resolutionValue) | XSPI_DLLCR_DLL_REFCNTR(refCounterValue) |
                          XSPI_DLLCR_SLV_FINE_OFFSET(offsetDelayElementCount) |
                          XSPI_DLLCR_SLV_DLY_OFFSET(tDiv16OffsetDelayElementCount) | XSPI_DLLCR_FREQEN(enableHighFreq);
        /* Load above settings into delay chain. */
        base->DLLCR[0] |= XSPI_DLLCR_SLV_UPD_MASK;
        base->DLLCR[0] |= XSPI_DLLCR_DLLEN_MASK;
        base->DLLCR[0] &= ~XSPI_DLLCR_SLV_UPD_MASK;
        while ((base->DLLSR & XSPI_DLLSR_SLVA_LOCK_MASK) == 0UL)
        {
        }
    }
}

/*!
 * brief Set Data learning configurations.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrDataLearningConfig Pointer to data learning configuration.
 * 
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail to set data learning configuration due to AHB read access asserted.
 * retval kStatus_XSPI_IPAccessAsserted Fail to set data learning configuration due to a IP access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail to set data learning configuration due to AHB write access asserted.
 * retval kStatus_Success  Successfully to set Data learning configurations.
 */
status_t XSPI_SetDataLearningConfig(XSPI_Type *base, xspi_data_learning_config_t *ptrDataLearningConfig)
{
    assert(ptrDataLearningConfig != NULL);

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckIPAccessAsserted(base))
    {
        return kStatus_XSPI_IPAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    base->DLCR = ((base->DLCR) & ~(XSPI_DLCR_DLP_SEL_FA_MASK | XSPI_DLCR_DL_NONDLP_FLSH_MASK)) |
                 (XSPI_DLCR_DLP_SEL_FA(ptrDataLearningConfig->padSelected) |
                  XSPI_DLCR_DL_NONDLP_FLSH(ptrDataLearningConfig->deviceSupported));

    base->DLPR = ptrDataLearningConfig->pattern;

    return kStatus_Success;
}

/*!
 * brief Update address mode to access external device.
 * 
 * param base XSPI peripheral base address.
 * param addrMode Specify the address mode to update.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail to update address mode due to AHB read access asserted.
 * retval kStatus_XSPI_IPAccessAsserted Fail to update address mode due to a IP access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail to update address mode due to AHB write access asserted.
 * retval kStatus_Success  Successfully to update address mode.
 */
status_t XSPI_UpdateDeviceAddrMode(XSPI_Type *base, xspi_device_addr_mode_t addrMode)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckIPAccessAsserted(base))
    {
        return kStatus_XSPI_IPAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }
    
    if (addrMode != kXSPI_Device4ByteAddressable)
    {
        base->SFACR =
            (base->SFACR & ~(XSPI_SFACR_WA_MASK | XSPI_SFACR_WA_4B_EN_MASK)) | XSPI_SFACR_WA(addrMode);
    }
    else
    {
        base->SFACR &= ~XSPI_SFACR_WA_MASK;
        base->SFACR |= XSPI_SFACR_WA_4B_EN_MASK;
    }
    
    return kStatus_Success;
}

/***************************** External Device Control Low-Level Interfaces End ********************************/

/***************************** External Device Control Functional Interfaces Start ********************************/
/*!
 * brief Set device configuration.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] devConfig Pointer to device configuration.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail to set device configuration due to AHB read access asserted.
 * retval kStatus_XSPI_IPAccessAsserted Fail to set device configuration due to a IP access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail to set device configuration due to AHB write access asserted.
 * retval kStatus_Success  Successfully to set device configurations.
 */
status_t XSPI_SetDeviceConfig(XSPI_Type *base, xspi_device_config_t *devConfig)
{
    assert(devConfig != NULL);

    bool enableDDR     = false;
    bool enableX16Mode = false;
    uint32_t instance  = XSPI_GetInstance(base);

    if (XSPI_CheckIPAccessAsserted(base))
    {
        return kStatus_XSPI_IPAccessAsserted;
    }

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    /* Set sample clock config. */
    bool isEnabled = false;

    if (XSPI_CheckModuleEnabled(base))
    {
        isEnabled = true;
        XSPI_EnableModule(base, false);
    }

    if (devConfig->enableCknPad)
    {
        base->MCR |= XSPI_MCR_CKN_FA_EN_MASK;
    }
    else
    {
        base->MCR &= ~XSPI_MCR_CKN_FA_EN_MASK;
    }

    if (devConfig->deviceInterface == kXSPI_StrandardExtendedSPI)
    {
        uint8_t tmp8 = XSPI_GetPPWBFromPageSize(devConfig->interfaceSettings.strandardExtendedSPISettings.pageSize);
        base->MCR &= ~XSPI_MCR_DQS_OUT_EN_MASK;
        base->SFACR = (base->SFACR & ~XSPI_SFACR_PPWB_MASK) | XSPI_SFACR_PPWB(tmp8);
    }
    else
    {
        XSPI_SetHyperBusX16Mode(base, devConfig->interfaceSettings.hyperBusSettings.x16Mode);
        if (devConfig->interfaceSettings.hyperBusSettings.x16Mode != kXSPI_x16ModeDisable)
        {
            enableX16Mode = true;
        }
        XSPI_EnableVariableLatency(base, devConfig->interfaceSettings.hyperBusSettings.enableVariableLatency);
        base->MCR |= XSPI_MCR_DQS_OUT_EN_MASK;
        base->SFACR = (base->SFACR & ~XSPI_SFACR_FORCE_A10_MASK) |
                      XSPI_SFACR_FORCE_A10(devConfig->interfaceSettings.hyperBusSettings.forceBit10To1);
    }

    base->FLSHCR = ((base->FLSHCR) & ~(XSPI_FLSHCR_TCSS_MASK | XSPI_FLSHCR_TCSH_MASK)) |
                   (XSPI_FLSHCR_TCSS(devConfig->CSSetupTime) | XSPI_FLSHCR_TCSH(devConfig->CSHoldTime));

    if (devConfig->addrMode != kXSPI_Device4ByteAddressable)
    {
        base->SFACR =
            (base->SFACR & ~(XSPI_SFACR_WA_MASK | XSPI_SFACR_WA_4B_EN_MASK)) | XSPI_SFACR_WA(devConfig->addrMode);
    }
    else
    {
        base->SFACR |= XSPI_SFACR_WA_4B_EN_MASK;
    }

    base->SFACR =
        (base->SFACR & ~(XSPI_SFACR_CAS_INTRLVD_MASK | XSPI_SFACR_CAS_MASK)) |
        (XSPI_SFACR_CAS_INTRLVD(devConfig->enableCASInterleaving) | XSPI_SFACR_CAS(devConfig->columnAddrWidth));

    if (devConfig->ptrDeviceRegInfo != NULL)
    {
        (void)XSPI_SetSFMStatusRegInfo(base, devConfig->ptrDeviceRegInfo);
    }

    if (devConfig->ptrDeviceDdrConfig != NULL)
    {
        enableDDR = devConfig->ptrDeviceDdrConfig->enableDdr;
    }

    if (enableDDR)
    {
        base->FLSHCR = ((base->FLSHCR) & ~XSPI_FLSHCR_TDH_MASK) |
                       XSPI_FLSHCR_TDH(devConfig->ptrDeviceDdrConfig->ddrDataAlignedClk);
        base->SFACR = ((base->SFACR) & ~XSPI_SFACR_BYTE_SWAP_MASK) |
                      XSPI_SFACR_BYTE_SWAP(devConfig->ptrDeviceDdrConfig->enableByteSwapInOctalMode);
        base->MCR |= XSPI_MCR_DDR_EN_MASK;
    }
    else
    {
        base->MCR &= ~XSPI_MCR_DDR_EN_MASK;
    }

    for (uint8_t i = 0U; i < XSPI_SFAD_COUNT2; i++)
    {
        base->SFAD[0][i] = s_xspiAmbaBase[instance] + XSPI_SFAD_TPAD(devConfig->deviceSize[i]);
    }

    uint32_t tmp32 = (base->MCR) & ~(XSPI_MCR_DQS_FA_SEL_MASK | XSPI_MCR_DQS_EN_MASK | XSPI_MCR_DQS_LAT_EN_MASK);

    if ((devConfig->sampleClkConfig.sampleClkSource == kXSPI_SampleClkFromDqsPadLoopback) ||
        (devConfig->sampleClkConfig.sampleClkSource == kXSPI_SampleClkFromExternalDQS))
    {
        tmp32 |= XSPI_MCR_DQS_EN_MASK;
    }
    tmp32 |= XSPI_MCR_DQS_LAT_EN(devConfig->sampleClkConfig.enableDQSLatency) |
             XSPI_MCR_DQS_FA_SEL((uint32_t)(devConfig->sampleClkConfig.sampleClkSource) & 0x3UL);
    base->MCR = tmp32;

    base->SMPR &= ~(XSPI_SMPR_FSPHS_MASK | XSPI_SMPR_FSDLY_MASK);

    if (devConfig->sampleClkConfig.sampleClkSource == kXSPI_SampleClkFromInvertedFullySpeedDummyPadLoopback)
    {
        base->SMPR |= XSPI_SMPR_FSPHS_MASK;
    }

    if (devConfig->sampleClkConfig.sampleClkSource == kXSPI_SampleClkFromHalfSpeedDummyPadLoopback)
    {
        base->SMPR |= XSPI_SMPR_FSDLY_MASK;
    }

    XSPI_UpdateDllValue(base, &(devConfig->sampleClkConfig.dllConfig), enableDDR, enableX16Mode,
                        devConfig->xspiRootClk);

    if (isEnabled)
    {
        XSPI_EnableModule(base, true);
    }

    return kStatus_Success;
}
/***************************** External Device Control Functional Interfaces End ********************************/

/***************************** IPS Access Control Low-Level Interfaces Start ********************************/
/*!
 * brief Update watermark for RX buffer.
 *
 * code
 * Set watermark as 4 bytes:
 * XSPI_UpdateRxBufferWaterMark(XSPI0, 4UL);
 * Set watermark as 8 bytes:
 * XSPI_UpdateRxBufferWaterMark(XSPI0, 8UL);
 * endcode
 *
 *
 * param[in] base XSPI peripheral base address.
 * param[in] waterMark Specify the number of bytes in the RX buffer which causes XSPI to assert the watermark exceeded
 * flag, should be in multiple of 4 bytes.
 *
 * retval kStatus_XSPI_IPAccessAsserted Fail to update watermark for Rx buffer, due to IP access is asserted.
 * retval kStatus_XSPI_WaterMarkIllegal Fail to update watermark for Tx buffer, due to input watermark is not the
 * multiple of 4 bytes.
 * retval kStatus_Success Successful to update watermark.
 */
status_t XSPI_UpdateRxBufferWaterMark(XSPI_Type *base, uint32_t waterMark)
{
    assert(waterMark != 0UL);
    assert(waterMark <= 256UL);

    if (XSPI_CheckIPAccessAsserted(base))
    {
        return kStatus_XSPI_IPAccessAsserted;
    }

    if ((waterMark % 4UL) != 0UL)
    {
        return kStatus_XSPI_WaterMarkIllegal;
    }

    base->RBCT = XSPI_RBCT_WMRK((waterMark / 4UL) - 1UL);

    return kStatus_Success;
}

/*!
 * brief Update watermark for TX buffer.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] waterMark The watermark to set, the unit is byte, should be the multiple of 4 byte.
 *
 * retval  kStatus_XSPI_IPAccessAsserted Fail to update watermark for Tx buffer, due to IP access is asserted.
 * retval kStatus_XSPI_WaterMarkIllegal Fail to update watermark for Tx buffer, due to input watermark is not the
 * multiple of 4 bytes.
 * retval kStatus_Success Successful to update watermark.
 */
status_t XSPI_UpdateTxBufferWaterMark(XSPI_Type *base, uint32_t waterMark)
{
    assert(waterMark != 0UL);
    if (XSPI_CheckIPAccessAsserted(base))
    {
        return kStatus_XSPI_IPAccessAsserted;
    }

    if ((waterMark % 4UL) != 0UL)
    {
        return kStatus_XSPI_WaterMarkIllegal;
    }

    base->TBCT = XSPI_TBCT_WMRK((waterMark / 4UL) - 1UL);

    return kStatus_Success;
}

/*!
 * brief Set exclusive access lock mode for the specific frad..
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ealMode Specify the exclusive access lock mode.
 * param[in] fradId Specify the frad.
 */
void XSPI_SetSFPFradEALMode(XSPI_Type *base, xspi_exclusive_access_lock_mode_t ealMode, uint8_t fradId)
{
    uint32_t fradWord3RegOffset[] = XSPI_FRAD_WORD3_REG_OFFSET_ARRAY;

    uint32_t fradWord3RegAddr = (uint32_t)base + fradWord3RegOffset[fradId];

    xspi_exclusive_access_lock_mode_t curEalMode =
        (xspi_exclusive_access_lock_mode_t)(uint32_t)(((*(uint32_t *)fradWord3RegAddr) & XSPI_FRAD0_WORD3_EAL_MASK) >>
                                                      XSPI_FRAD0_WORD3_EAL_SHIFT);

    if (curEalMode != ealMode)
    {
        if (curEalMode == kXSPI_ExclusiveAccessLockEnabled)
        {
            *(uint32_t *)fradWord3RegAddr = (*(uint32_t *)fradWord3RegAddr & ~XSPI_FRAD0_WORD3_EAL_MASK) |
                                            XSPI_FRAD0_WORD3_EAL(kXSPI_ExclusiveAccessLockExceptMasterId);

            if (ealMode == kXSPI_ExclusiveAccessLockDisabled)
            {
                *(uint32_t *)fradWord3RegAddr = (*(uint32_t *)fradWord3RegAddr & ~XSPI_FRAD0_WORD3_EAL_MASK);
            }
        }
        else
        {
            *(uint32_t *)fradWord3RegAddr =
                (*(uint32_t *)fradWord3RegAddr & ~XSPI_FRAD0_WORD3_EAL_MASK) | XSPI_FRAD0_WORD3_EAL(ealMode);
        }
    }
}

/*!
 * brief Update SFP configurations, including MDAD configurations and FRAD configurations.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] ptrMdadConfig Pointer to the SFP MDAD configuration.
 * param[in] ptrFradConfig Pointer to the SFP FRAD configuration.
 */
void XSPI_UpdateSFPConfig(XSPI_Type *base,
                          xspi_sfp_mdad_config_t *ptrSfpMdadConfig,
                          xspi_sfp_frad_config_t *ptrSfpFradConfig)
{
    bool enableSFP  = false;
    bool enableMdad = false;
    bool enableFrad = false;
    uint8_t i       = 0U;

    enableMdad = (ptrSfpMdadConfig != NULL) ? true : false;
    enableFrad = (ptrSfpFradConfig != NULL) ? true : false;
    enableSFP  = (bool)(enableFrad | enableFrad);

    if (enableSFP)
    {
        if (enableMdad)
        {
            base->MGC |= (XSPI_MGC_GVLDMDAD_MASK | XSPI_MGC_GVLD_MASK);
            uint32_t tgMdadRegAddr     = 0UL;

            for (i = 0U; i < XSPI_TARGET_GROUP_COUNT; i++)
            {
                tgMdadRegAddr = (uint32_t)base + s_tgMdadRegOffset[i];

                *(uint32_t *)tgMdadRegAddr = XSPI_TG0MDAD_MIDMATCH(ptrSfpMdadConfig->tgMdad[i].masterIdReference) |
                                             XSPI_TG0MDAD_MASKTYPE(ptrSfpMdadConfig->tgMdad[i].maskType) |
                                             XSPI_TG0MDAD_MASK(ptrSfpMdadConfig->tgMdad[i].mask) |
                                             XSPI_TG0MDAD_VLD(ptrSfpMdadConfig->tgMdad[i].assignIsValid) |
                                             XSPI_TG0MDAD_SA(ptrSfpMdadConfig->tgMdad[i].secureAttribute);

                if (ptrSfpMdadConfig->tgMdad[i].enableDescriptorLock)
                {
                    *(uint32_t *)tgMdadRegAddr |= XSPI_TG0MDAD_LCK_MASK;
                }
            }
        }

        if (enableFrad)
        {
            base->MGC |= (XSPI_MGC_GVLDFRAD_MASK | XSPI_MGC_GVLD_MASK);
            uint32_t fradWord0RegOffset[] = XSPI_FRAD_WORD0_REG_OFFSET_ARRAY;
            uint32_t fradWord1RegOffset[] = XSPI_FRAD_WORD1_REG_OFFSET_ARRAY;
            uint32_t fradWord2RegOffset[] = XSPI_FRAD_WORD2_REG_OFFSET_ARRAY;
            uint32_t fradWord3RegOffset[] = XSPI_FRAD_WORD3_REG_OFFSET_ARRAY;

            uint32_t fradWord0RegAddr = 0UL;
            uint32_t fradWord1RegAddr = 0UL;
            uint32_t fradWord2RegAddr = 0UL;
            uint32_t fradWord3RegAddr = 0UL;

            for (i = 0U; i < XSPI_SFP_FRAD_COUNT; i++)
            {
                fradWord0RegAddr = (uint32_t)base + fradWord0RegOffset[i];
                fradWord1RegAddr = (uint32_t)base + fradWord1RegOffset[i];
                fradWord2RegAddr = (uint32_t)base + fradWord2RegOffset[i];
                fradWord3RegAddr = (uint32_t)base + fradWord3RegOffset[i];

                /* Set the most-significant 16 bits of the starting address(64-KB alignment). */
                *(uint32_t *)fradWord0RegAddr = ptrSfpFradConfig->fradConfig[i].startAddress & 0xFFFF0000UL;
                /* Set the most-significant 16 bits of the ending address(64-KB alignment). */
                *(uint32_t *)fradWord1RegAddr = ptrSfpFradConfig->fradConfig[i].endAddress & 0xFFFF0000UL;

                XSPI_SetSFPFradEALMode(base, ptrSfpFradConfig->fradConfig[i].exclusiveAccessLock, i);
                if (ptrSfpFradConfig->fradConfig[i].exclusiveAccessLock == kXSPI_ExclusiveAccessLockDisabled)
                {
                    *(uint32_t *)fradWord2RegAddr =
                        (*(uint32_t *)fradWord3RegAddr &
                         (~(XSPI_FRAD0_WORD2_MD0ACP_MASK | XSPI_FRAD0_WORD2_MD1ACP_MASK))) |
                        (XSPI_FRAD0_WORD2_MD0ACP(ptrSfpFradConfig->fradConfig[i].tg0MasterAccess) |
                         XSPI_FRAD0_WORD2_MD1ACP(ptrSfpFradConfig->fradConfig[i].tg1MasterAccess));
                }
                *(uint32_t *)fradWord3RegAddr =
                    ((*(uint32_t *)fradWord3RegAddr) & (~(XSPI_FRAD0_WORD3_LOCK_MASK | XSPI_FRAD0_WORD3_VLD_MASK))) |
                    (XSPI_FRAD0_WORD3_VLD(ptrSfpFradConfig->fradConfig[i].assignIsValid) |
                     XSPI_FRAD0_WORD3_LOCK(ptrSfpFradConfig->fradConfig[i].descriptorLock));
            }
        }
    }
    else
    {
        base->MGC &= ~(XSPI_MGC_GVLDFRAD_MASK | XSPI_MGC_GVLDMDAD_MASK | XSPI_MGC_GVLD_MASK);
    }
}

/*!
 * brief Get FARD latest transaction information.
 * 
 * param[in] base XSPI peripheral base address.
 * param[out] ptrInfo Pointer to the variable in type of ref xspi_frad_transaction_info_t to store information.
 * param[in] fradId Specify the frad Id.
 */
void XSPI_GetFradLastTransactionsInfo(XSPI_Type *base, xspi_frad_transaction_info_t *ptrInfo, uint8_t fradId)
{
    uint32_t fradWord4RegOffset[] = XSPI_FRAD_WORD4_REG_OFFSET_ARRAY;
    uint32_t fradWord5RegOffset[] = XSPI_FRAD_WORD5_REG_OFFSET_ARRAY;

    uint32_t fradWord4RegAddr = (uint32_t)base + fradWord4RegOffset[fradId];
    uint32_t fradWord5RegAddr = (uint32_t)base + fradWord5RegOffset[fradId];

    ptrInfo->startAddr = (*(uint32_t *)fradWord4RegAddr);
    ptrInfo->masterId =
        (uint8_t)(((*(uint32_t *)fradWord5RegAddr) & XSPI_FRAD0_WORD5_CMP_MDID_MASK) >> XSPI_FRAD0_WORD5_CMP_MDID_SHIFT);
    ptrInfo->isSecureAccess    = (bool)(((*(uint32_t *)fradWord5RegAddr) & XSPI_FRAD0_WORD5_CMP_SA_MASK) != 0UL);
    ptrInfo->isPrivilegeAccess = (bool)(((*(uint32_t *)fradWord5RegAddr) & XSPI_FRAD0_WORD5_CMP_PA_MASK) != 0UL);
    ptrInfo->isCompError       = (bool)(((*(uint32_t *)fradWord5RegAddr) & XSPI_FRAD0_WORD5_CMP_ERR_MASK) != 0UL);
    ptrInfo->isCompValid       = (bool)(((*(uint32_t *)fradWord5RegAddr) & XSPI_FRAD0_WORD5_CMPVALID_MASK) != 0UL);
}

/*!
 * brief Update SFP arbitration lock timeout counter.
 *
 * note The SFP arbitration lock time out counter starts when Page program wait flag asserted.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] countValue The count value, specify the time in IPS clock cycles.
 *
 * retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_UpdateSFPArbitrationLockTimeoutCounter(XSPI_Type *base, uint32_t countValue)
{
    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->SFP_ARB_TIMEOUT = countValue;

    return kStatus_Success;
}

/*!
 * brief Update the count of SFP access timeout counter.
 *
 * note The counter starts when any IP access pass SFP check(if enabled), and request is granted by XSPI arbiter and
 * XSPI is IDLE.
 *
 * note The counter does not start in case of IP access was granted by XSPI is not IDLE.
 *
 * param base XSPI peripheral base address.
 * param countValue The count value, specify the time in IPS clock cycles.
 *
 * retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_UpdateIPAccessTimeoutCounter(XSPI_Type *base, uint32_t countValue)
{
    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->MTO = countValue;

    return kStatus_Success;
}

/*!
 * brief Get MDAD check error reason for specific target group.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] tgId Specify the target group.
 *
 * return The details of MDAD error reason, in type of ref xspi_mdad_error_reason_t.
 */
xspi_mdad_error_reason_t XSPI_GetMdadErrorReason(XSPI_Type *base, xspi_target_group_t tgId)
{
    uint8_t tmp8 = 0U;

    if (tgId == kXSPI_TargetGroup0)
    {
        tmp8 = (uint8_t)((base->TGIPCRS & XSPI_TGIPCRS_ERR_MASK) >> XSPI_TGIPCRS_ERR_SHIFT);
    }
    else
    {
        tmp8 = (uint8_t)((base->SUB_REG_MDAM_ARRAY[0].TGIPCRS_SUB & XSPI_TGIPCRS_SUB_ERR_MASK) >>
                         XSPI_TGIPCRS_SUB_ERR_SHIFT);
    }

    return (xspi_mdad_error_reason_t)tmp8;
}

/*!
 * brief Clear address write status for specific target group.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] tgId Specify the target group to clear address write status.
 */
void XSPI_ClearTgAddrWriteStatus(XSPI_Type *base, xspi_target_group_t tgId)
{
    uint32_t tgSfarsRegAddr = (uint32_t)base + (uint32_t)s_tgSfarsRegOffset[(uint8_t)(tgId)];

    *((uint32_t *)tgSfarsRegAddr) |= XSPI_TGSFARS_CLR_MASK;
}

/*!
 * brief Get address write status for specific target group.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] tgId Specify the target group.
 * param[out] ptrStatus Pointer to the variable in type of ref xspi_tg_add_write_status_t
                        to store address write status.
 */
void XSPI_GetTgAddrWriteStatus(XSPI_Type *base, xspi_target_group_t tgId, xspi_tg_add_write_status_t *ptrStatus)
{
    uint32_t tgSfarsRegAddr = (uint32_t)base + (uint32_t)s_tgSfarsRegOffset[(uint8_t)(tgId)];
    uint32_t tmp32          = (*(uint32_t *)tgSfarsRegAddr);

    ptrStatus->managerId       = (uint8_t)(tmp32 & XSPI_TGSFARS_TG_MID_MASK);
    ptrStatus->secureWrite     = (bool)((tmp32 & XSPI_TGSFARS_SA_MASK) != 0UL);
    ptrStatus->privilegedWrite = (bool)((tmp32 & XSPI_TGSFARS_PA_MASK) != 0UL);
}

/*!
 * brief Unlock Ip access arbitration.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] tgId Specify the target group.
 */
void XSPI_UnlockIpAccessArbitration(XSPI_Type *base, xspi_target_group_t tgId)
{
    uint32_t tgIpcrRegOffset[] = XSPI_TGIPCRS_REG_OFFSET;
    uint32_t tgIpcrRegAddr     = (uint32_t)base + tgIpcrRegOffset[(uint8_t)tgId];

    *(uint32_t *)tgIpcrRegAddr |= XSPI_SFP_TG_IPCR_ARB_UNLOCK_MASK;
}

/*!
 * brief Start IP access(including read and write).
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] addr Address of external device to read/write.
 * param[in] seqIndex Sequence Id of the pre-programed LUT.
 * param[in] byteSize Size of data to read/write, the unit of byte.
 * param[in] tgId Specify the target group used to write/read.
 * param[in] lockArbitration Lock arbitration or not.
 *
 * retval kStatus_XSPI_IpAccessAddrSettingInvalid Wrong Address input.
 * retval kStatus_XSPI_IpAccessIPCRInvalid Wrong seqindex or bytesize input.
 * retval kStatus_Success Success to start Ip access.
 */
status_t XSPI_StartIpAccess(
    XSPI_Type *base, uint32_t addr, uint8_t seqIndex, size_t byteSize, xspi_target_group_t tgId, bool lockArbitration)
{
    uint32_t tgSfarsRegAddr     = (uint32_t)base + (uint32_t)s_tgSfarsRegOffset[(uint8_t)tgId];
    uint32_t tgIpcrsRegAddr     = (uint32_t)base + (uint32_t)s_tgIpcrsRegOffset[(uint8_t)tgId];
    uint32_t sfpTgIpcrRegAddr   = (uint32_t)base + (uint32_t)s_sfpTgIpcrRegOffset[(uint8_t)tgId];
    uint32_t sfpTgIpSfarRegAddr = (uint32_t)base + (uint32_t)s_sfpTgIpSfarRegOffset[(uint8_t)tgId];
    uint32_t tgMdadRegAddr      = (uint32_t)base + (uint32_t)s_tgMdadRegOffset[(uint8_t)tgId];

    bool mdadEnabled = false;
    bool mdadValid   = false;
    uint32_t tmp32   = 0UL;

    mdadEnabled = (bool)((base->MGC & XSPI_MGC_GVLDMDAD_MASK) != 0UL);
    mdadValid   = (((*(uint32_t *)tgMdadRegAddr) & XSPI_TG0MDAD_VLD_MASK) != 0UL);
    /* Check the selected target group queue is empty. */
    while (((*(uint32_t *)tgSfarsRegAddr) & XSPI_TGSFARS_VLD_MASK) != 0UL)
    {
    }

    /* Set target address. */
    (*(uint32_t *)sfpTgIpSfarRegAddr) = addr;

    if (mdadEnabled && mdadValid)
    {
        do
        {
            tmp32 = (*(uint32_t *)tgSfarsRegAddr & (XSPI_TGSFARS_VLD_MASK | XSPI_TGSFARS_ERR_MASK));
            if (tmp32 == XSPI_TGSFARS_ERR_MASK)
            {
                /* The manager ID or write attributes to set SFAR register is not valid. */
                return kStatus_XSPI_IpAccessAddrSettingInvalid;
            }
        } while (tmp32 != XSPI_TGSFARS_VLD_MASK);
    }

    /* Set transfer size and sequence ID. */
    (*(uint32_t *)sfpTgIpcrRegAddr) = XSPI_SFP_TG_IPCR_IDATSZ(byteSize) | XSPI_SFP_TG_IPCR_ARB_LOCK(lockArbitration) |
                                      XSPI_SFP_TG_IPCR_SEQID(seqIndex);
    if (mdadEnabled && mdadValid)
    {
        do
        {
            tmp32 = (*(uint32_t *)tgIpcrsRegAddr & (XSPI_TGIPCRS_ERR_MASK | XSPI_TGIPCRS_VLD_MASK));
            if ((tmp32 & XSPI_TGIPCRS_ERR_MASK) != 0UL)
            {
                return kStatus_XSPI_IpAccessIPCRInvalid;
            }
        } while ((tmp32 & XSPI_TGIPCRS_VLD_MASK) == 0UL);
    }

    /* Blocking until the IP access is granted. */
    while (XSPI_CheckIPAccessGranted(base) == false)
    {
    }

    return kStatus_Success;
}

/***************************** IPS Access Control Low-Level Interfaces End ********************************/

/***************************** IPS Access Control Functional Interfaces Start ********************************/
/*!
 * brief Set IP access configurations, including SFP configurations, sfp arbitration lock timeout value, Ip access
 * timeout value.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrIpAccessConfig Pointer to the variable which contains Ip access configurations.
 *
 * retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_SetIpAccessConfig(XSPI_Type *base, xspi_ip_access_config_t *ptrIpAccessConfig)
{
    assert(ptrIpAccessConfig != NULL);

    status_t status = kStatus_Success;

    XSPI_ClearIPAccessSeqPointer(base);
    XSPI_UpdateSFPConfig(base, ptrIpAccessConfig->ptrSfpMdadConfig, ptrIpAccessConfig->ptrSfpFradConfig);
    status = XSPI_UpdateSFPArbitrationLockTimeoutCounter(base, ptrIpAccessConfig->sfpArbitrationLockTimeoutValue);

    if (status == kStatus_Success)
    {
        status = XSPI_UpdateIPAccessTimeoutCounter(base, ptrIpAccessConfig->ipAccessTimeoutValue);
    }

    return status;
}

/*!
 * brief Sends a buffer of data bytes using blocking method.
 * note This function blocks via polling until all bytes have been sent.
 * param base XSPI peripheral base address
 * param buffer The data bytes to send
 * param size The number of data bytes to send
 * retval kStatus_Success write success without error
 * retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_WriteBlocking(XSPI_Type *base, uint8_t *buffer, size_t size)
{
    status_t result = kStatus_Success;
    uint32_t i      = 0;

    /* Blocking until TX buffer is unlocked. */
    while (XSPI_CheckTxBuffLockOpen(base) == false)
    {
    }

    base->TBCT = 256UL - ((uint32_t)size / 4UL - 1UL);
    /* Send data buffer */
    while (0U != size)
    {
        result = XSPI_CheckAndClearError(base, base->ERRSTAT);

        if (kStatus_Success != result)
        {
            return result;
        }

        /* Write watermark level data into tx fifo . */
        /* Write word aligned data into tx fifo. */
        for (i = 0U; i < (size / 4U); i++)
        {
            while (1UL == ((base->SR & XSPI_SR_TXFULL_MASK) >> XSPI_SR_TXFULL_SHIFT))
            {
            }
            base->TBDR = *(uint32_t *)buffer;
            buffer += 4U;
        }

        /* Adjust size by the amount processed. */
        size -= 4U * i;

        /* Write word un-aligned data into tx fifo. */
        if (0x00U != size)
        {
            uint32_t tempVal = 0x00U;

            for (uint32_t j = 0U; j < size; j++)
            {
                tempVal |= ((uint32_t)*buffer++ << (8U * j));
            }

            while (1UL == ((base->SR & XSPI_SR_TXFULL_MASK) >> XSPI_SR_TXFULL_SHIFT))
            {
            }
            base->TBDR = tempVal;
        }

        size = 0U;
    }

    /*clear TX Buffer Fill Flag*/
    base->FR = XSPI_FR_TBFF_MASK;

    while (XSPI_CheckIPAccessAsserted(base))
    {
    }

    return result;
}

/*!
 * brief Receives a buffer of data bytes using a blocking method.
 * note This function blocks via polling until all bytes have been sent.
 * param base XSPI peripheral base address
 * param buffer The data bytes to send
 * param size The number of data bytes to receive
 * retval kStatus_Success read success without error
 * retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_ReadBlocking(XSPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t rxWatermark  = base->RBCT + 1UL;
    status_t status       = kStatus_Success;
    uint32_t i            = 0UL;
    uint32_t removedCount = 0UL;

    while ((1UL != (base->SR & XSPI_SR_BUSY_MASK)) && (((base->SR & XSPI_SR_IP_ACC_MASK) >> XSPI_SR_IP_ACC_SHIFT) != 0UL))
    {
    }

    /* Loop until Rx buffer watermark exceeded status asserted. */
    while ((base->SR & XSPI_SR_RXWE_MASK) == 0UL)
    {
        if((base->ERRSTAT & XSPI_ERRSTAT_TO_ERR_MASK) != 0UL)
        {
            base->ERRSTAT = XSPI_ERRSTAT_TO_ERR_MASK;
            return kStatus_Timeout;
        }
    }

    uint32_t adjuestedSize = size + (4UL - size % 4UL) % 4UL;

    if (XSPI_GetRxBufferAvailableBytesCount(base) != adjuestedSize)
    {
        return kStatus_XSPI_RxBufferEntriesCountError;
    }
    /* Send data buffer */
    while (0UL != size)
    {
        status = XSPI_CheckAndClearError(base, base->ERRSTAT);

        if (kStatus_Success != status)
        {
            break;
        }

        /* Read word aligned data from rx fifo. */
        if (size >= 4UL * rxWatermark)
        {
            removedCount = XSPI_GetRxBufferRemovedBytesCount(base);
            for (i = 0UL; i < rxWatermark; i++)
            {
                *(uint32_t *)buffer = base->RBDR[i];
                buffer += 4UL;
            }

            /* RX buffer POP, trigger RX pop event. */
            XSPI_TriggerRxBufferPopEvent(base);
            while ((XSPI_GetRxBufferRemovedBytesCount(base) - removedCount) != (rxWatermark * 4UL))
            {
            }
            size = size - 4UL * rxWatermark;
        }
        else
        {
            for (i = 0UL; i < (size / 4UL); i++)
            {
                *(uint32_t *)buffer = base->RBDR[i];
                buffer += 4UL;
            }

            /* Adjust size by the amount processed. */
            size -= 4UL * i;

            /* Read word un-aligned data from rx fifo. */
            if (0UL != size)
            {
                uint32_t tempVal = base->RBDR[i];

                for (i = 0U; i < size; i++)
                {
                    *buffer++ = ((uint8_t)(tempVal >> (8U * i)) & 0xFFU);
                }
            }

            size = 0UL;
        }
    }

    /* Clear Rx buffer after all entries are read out. */
    XSPI_ClearRxBuffer(base);

    return status;
}

/*!
 * brief Execute command to transfer a buffer data bytes using a blocking method.
 * param base XSPI peripheral base address
 * param xfer pointer to the transfer structure.
 * retval kStatus_Success command transfer success without error
 * retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_TransferBlocking(XSPI_Type *base, xspi_transfer_t *xfer)
{
    status_t status    = kStatus_Success;
    uint32_t dataSize  = xfer->dataSize;
    uint8_t *ptrBuffer = (uint8_t *)xfer->data;

    if ((xfer->cmdType == kXSPI_Write) || (xfer->cmdType == kXSPI_Config))
    {
        status = XSPI_StartIpAccess(base, xfer->deviceAddress, xfer->seqIndex, dataSize, xfer->targetGroup,
                                    xfer->lockArbitration);
        if (status != kStatus_Success)
        {
            return status;
        }
        /* Clear TX buffer pointer. */
        XSPI_ClearTxBuffer(base);

        status = XSPI_WriteBlocking(base, ptrBuffer, xfer->dataSize);
    }
    else if (xfer->cmdType == kXSPI_Read)
    {
        uint32_t rxBufferWaterMark = 0UL;
        uint32_t transferSize      = 0UL;
        while (dataSize > 0UL)
        {
            XSPI_ClearRxBuffer(base);

            /* calculate watermark and transfer size based on data size. */
            if (dataSize >= XSPI_IP_RX_BUFFER_SIZE)
            {
                /* In case of data size bigger than RX buffer size, the big size request should be
                break into small size sub-request, and the transfer size of sub-request is equal to buffer size. */
                rxBufferWaterMark = XSPI_IP_RX_BUFFER_SIZE >> 1UL;
                transferSize      = XSPI_IP_RX_BUFFER_SIZE;
            }
            else if (dataSize > (XSPI_IP_RX_BUFFER_SIZE >> 1UL))
            {
                /* In case of data size bigger than maximum watermark value, watermark set as maxmium value, and
                transfer size is data size. */
                rxBufferWaterMark = XSPI_IP_RX_BUFFER_SIZE >> 1UL;
                transferSize      = dataSize;
            }
            else if (dataSize % 4UL == 0UL)
            {
                /* In case of data size less than maxmum watermark value and is aligned with 4 bytes, watermark set
                as data size, transfer size also set as data size. */
                rxBufferWaterMark = dataSize;
                transferSize      = dataSize;
            }
            else
            {
                /* In case of data size is not 4-byte aligned, watermark set as closest value, and transfer size
                set as data size. */
                rxBufferWaterMark = (dataSize / 4UL) << 2UL;
                if (rxBufferWaterMark == 0UL)
                {
                    rxBufferWaterMark = 4UL;
                }
                transferSize = dataSize;
            }
            (void)XSPI_UpdateRxBufferWaterMark(base, rxBufferWaterMark);

            status =
                XSPI_StartIpAccess(base, xfer->deviceAddress, xfer->seqIndex, transferSize, xfer->targetGroup, false);
            if (status != kStatus_Success)
            {
                return status;
            }
            status = XSPI_ReadBlocking(base, ptrBuffer, transferSize);
            if (status == kStatus_Timeout)
            {
                XSPI_ResetTgQueue(base);
                XSPI_ResetSfmAndAhbDomain(base);
                break;
            }
            dataSize -= transferSize;
            if (dataSize != 0UL)
            {
                ptrBuffer += transferSize;
            }
        }
    }
    else
    {
        /* Set command. */
        status = XSPI_StartIpAccess(base, xfer->deviceAddress, xfer->seqIndex, 0UL, xfer->targetGroup,
                                    xfer->lockArbitration);
        if (status != kStatus_Success)
        {
            return status;
        }
    }

    /* Wait for bus to be idle before changing flash configuration. */
    while (!XSPI_GetBusIdleStatus(base))
    {
    }

    if (xfer->cmdType == kXSPI_Command)
    {
        status = XSPI_CheckAndClearError(base, base->ERRSTAT);
        while (XSPI_CheckIPAccessAsserted(base))
        {
        }
    }

    return status;
}

/*!
 * brief Initializes the XSPI handle which is used in transactional functions.
 *
 * param base XSPI peripheral base address.
 * param handle pointer to xspi_handle_t structure to store the transfer state.
 * param callback pointer to user callback function.
 * param userData user parameter passed to the callback function.
 */
void XSPI_TransferCreateHandle(XSPI_Type *base,
                               xspi_handle_t *handle,
                               xspi_transfer_callback_t callback,
                               void *userData)
{
    assert(NULL != handle);

    uint32_t instance = XSPI_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_xspiIrqs[instance]);
}

/*!
 * brief Performs a interrupt non-blocking transfer on the XSPI bus.
 *
 * note Calling the API returns immediately after transfer initiates. The user needs
 * to call XSPI_GetTransferCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_XSPI_Busy, the transfer
 * is finished. For XSPI_Read, the dataSize should be multiple of rx watermark level, or
 * XSPI could not read data properly.
 *
 * param base XSPI peripheral base address.
 * param handle pointer to xspi_handle_t structure which stores the transfer state.
 * param xfer pointer to xspi_transfer_t structure.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_XSPI_Busy Previous transmission still not finished.
 */
status_t XSPI_TransferNonBlocking(XSPI_Type *base, xspi_handle_t *handle, xspi_transfer_t *xfer)
{
    //    uint32_t configValue = 0;
    status_t status = kStatus_Success;

    assert(NULL != handle);
    assert(NULL != xfer);

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != (uint32_t)kXSPI_Idle)
    {
        status = kStatus_XSPI_Busy;
    }
    else
    {
        handle->data              = (uint8_t *)xfer->data;
        handle->dataSize          = xfer->dataSize;
        handle->transferTotalSize = xfer->dataSize;
        handle->state = (xfer->cmdType == kXSPI_Read) ? (uint32_t)kXSPI_BusyRead : (uint32_t)kXSPI_BusyWrite;

        status = XSPI_StartIpAccess(base, xfer->deviceAddress, xfer->seqIndex, xfer->dataSize, xfer->targetGroup,
                                    xfer->lockArbitration);
        if (status != kStatus_Success)
        {
            return status;
        }

        if (handle->state == (uint32_t)kXSPI_BusyRead)
        {
            XSPI_ClearRxBuffer(base);
            XSPI_EnableInterrupts(base, (uint32_t)kXSPI_RxBufferOverflowFlag | (uint32_t)kXSPI_RxBufferDrainFlag |
                                            (uint32_t)kXSPI_IpCmdtriggerErrorFlag |
                                            (uint32_t)kXSPI_IllegalInstructionErrorFlag);
        }
        else
        {
            /* Clear TX buffer pointer. */
            XSPI_ClearTxBuffer(base);
            XSPI_EnableInterrupts(base, (uint32_t)kXSPI_TxBufferFillFlag | (uint32_t)kXSPI_TxBufferUnderrunFlag |
                                            (uint32_t)kXSPI_IpCmdtriggerErrorFlag |
                                            (uint32_t)kXSPI_IllegalInstructionErrorFlag);
        }
    }

    return status;
}

/*!
 * brief Gets the master transfer status during a interrupt non-blocking transfer.
 *
 * param base XSPI peripheral base address.
 * param handle pointer to xspi_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t XSPI_TransferGetCount(XSPI_Type *base, xspi_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    status_t status = kStatus_Success;

    if (handle->state == (uint32_t)kXSPI_Idle)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->transferTotalSize - handle->dataSize;
    }

    return status;
}

/*!
 * brief Aborts an interrupt non-blocking transfer early.
 *
 * note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base XSPI peripheral base address.
 * param handle pointer to xspi_handle_t structure which stores the transfer state
 */
void XSPI_TransferAbort(XSPI_Type *base, xspi_handle_t *handle)
{
    assert(NULL != handle);

    XSPI_DisableInterrupts(base, (uint32_t)kIrqFlags);
    handle->state = (uint32_t)kXSPI_Idle;
}

/***************************** IPS Access Control Functional Interfaces End ********************************/

/***************************** AHB Access Control Low-Level Interfaces Start ********************************/
/*!
 * brief Set AHB transaction(read/write) boundary.
 *
 * note For AHB write, XSPI keeps track of the start address and then compares it with the address of subsequent
 * transaction receive on the AHB bus, when the input alignment is reached, XSPI negates AHB HREADY to block new
 * accesses. This signal will be kept low until all the previous received write data is written to external memory and
 * chip select is de-asserted. After that it allows next AHB write data to be received by making HREADY high thus
 * ensuring that transaction is split at address boundary on external memory.
 *
 * note For AHB read, XSPI checks the start address and end address to see if it is crossing the address boundary
 * specified by input alignment. If the transaction crosses the address boundary, then it reduces the transaction size
 * such that the data pre-fetch is stopped before the address boundary. Now if the AHB master is reading the data
 * sequentially it will get buffer hits up to the input alignment boundary. When it reaches the next address boundary
 * it will get a buffer miss and a new data pre-fetch will be launched towards the external memory device.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] alignment Specify the AHB alignment, in type of ref xspi_ahb_alignment_t.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB access boundary.
 */
status_t XSPI_SetAhbAccessBoundary(XSPI_Type *base, xspi_ahb_alignment_t alignment)
{
#if defined(XSPI_BFGENCR_ALIGN_MASK)
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->BFGENCR = ((base->BFGENCR & ~(XSPI_BFGENCR_ALIGN_MASK)) | XSPI_BFGENCR_ALIGN(alignment));
#endif /* defined(XSPI_BFGENCR_ALIGN_MASK) */
    
    return kStatus_Success;
}
/*!
 * brief Set AHB read sequence Id.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] seqId Specify the sequence Id in LUT used for AHB read.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB read sequence Id.
 */
status_t XSPI_SetAhbReadDataSeqId(XSPI_Type *base, uint8_t seqId)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->BFGENCR = ((base->BFGENCR & (~XSPI_BFGENCR_SEQID_MASK)) | XSPI_BFGENCR_SEQID(seqId));

    return kStatus_Success;
}
/*!
 * brief Set AHB write sequence Id.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] seqId Specify the sequence Id in LUT used for AHB write.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB write sequence Id.
 */
status_t XSPI_SetAhbWriteDataSeqId(XSPI_Type *base, uint8_t seqId)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->BFGENCR = ((base->BFGENCR & (~XSPI_BFGENCR_SEQID_WR_MASK)) | XSPI_BFGENCR_SEQID_WR(seqId));

    return kStatus_Success;
}
/*!
 * brief Set AHB buffer configurations.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrBuffer0Config Pointer to the variable which contain buffer0 configurations.
 * param[in] ptrBuffer1Config Pointer to the variable which contain buffer1 configurations. 
 * param[in] ptrBuffer2Config Pointer to the variable which contain buffer2 configurations.
 * param[in] ptrBuffer3Config Pointer to the variable which contain buffer3 configurations.
 * 
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * retval kStatus_Success Success to set AHB buffer configurations.
 */
status_t XSPI_SetAhbBufferConfig(XSPI_Type *base,
                                 xspi_ahbBuffer_config_t *ptrBuffer0Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer1Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer2Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer3Config)
{
    assert(ptrBuffer0Config != NULL);
    assert(ptrBuffer1Config != NULL);
    assert(ptrBuffer2Config != NULL);
    assert(ptrBuffer3Config != NULL);

    assert((ptrBuffer0Config->bufferSize + ptrBuffer1Config->bufferSize + ptrBuffer2Config->bufferSize +
            ptrBuffer3Config->bufferSize) == 512U);

    xspi_ahbBuffer_config_t *ahbBufferConfigs[4];
    uint32_t subBufferStartAddr; /* Specify the upper 16-bits of the start addresss range. */
    uint32_t subBufferEndAddr;   /* Specify the upper 16-bits of the end addresss range. */
    xspi_ahbBuffer_sub_buffer_config_t *curSubBufferConfig = NULL;

    ahbBufferConfigs[0] = ptrBuffer0Config;
    ahbBufferConfigs[1] = ptrBuffer1Config;
    ahbBufferConfigs[2] = ptrBuffer2Config;
    ahbBufferConfigs[3] = ptrBuffer3Config;
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    (void)XSPI_UpdateAhbBufferSize(base, ptrBuffer0Config->bufferSize, ptrBuffer1Config->bufferSize,
                                   ptrBuffer2Config->bufferSize, ptrBuffer3Config->bufferSize);

    for (uint8_t i = 0U; i < XSPI_BUFCR_COUNT; i++)
    {
        /* The buffer size is set as transfer size, because when buffer-miss the
        XSPI will clear AHB buffer and fetch size of data from external device.
        If transfer size is less than buffer size, then left space will never used. */
        base->BUFCR[i] =
            XSPI_BUFCR_MSTRID(ahbBufferConfigs[i]->masterId) | XSPI_BUFCR_ADATSZ(ahbBufferConfigs[i]->bufferSize);

        /* Same bit field represent different feature for differnt AHB buffer. */
        if ((i == 0U) || (i == 1U))
        {
            base->BUFCR[i] |= XSPI_BUFCR_HP_EN(ahbBufferConfigs[i]->enaPri.enablePriority);
        }

        if (i == 3U)
        {
            base->BUFCR[i] |= XSPI_BUFCR_ALLMST(ahbBufferConfigs[i]->enaPri.enableAllMaster);
        }

        if ((ahbBufferConfigs[i]->ptrSubBuffer0Config == NULL) && (ahbBufferConfigs[i]->ptrSubBuffer1Config == NULL) &&
            (ahbBufferConfigs[i]->ptrSubBuffer2Config == NULL) && (ahbBufferConfigs[i]->ptrSubBuffer3Config == NULL))
        {
            base->BUFCR[i] &= ~XSPI_BUFCR_SUB_DIV_EN_MASK;
        }
        else
        {
            if (((1U << (4U - (uint8_t)(ahbBufferConfigs[i]->ptrSubBuffer0Config->divFactor))) +
                 (1U << (4U - (uint8_t)(ahbBufferConfigs[i]->ptrSubBuffer1Config->divFactor))) +
                 (1U << (4U - (uint8_t)(ahbBufferConfigs[i]->ptrSubBuffer2Config->divFactor)))) > 16U)
            {
                return kStatus_XSPI_AhbSubBufferFactorError;
            }

            base->BUFCR[i] |= XSPI_BUFCR_SUB_DIV_EN_MASK |
                              XSPI_BUFCR_SUBBUF0_DIV(ahbBufferConfigs[i]->ptrSubBuffer0Config->divFactor) |
                              XSPI_BUFCR_SUBBUF1_DIV(ahbBufferConfigs[i]->ptrSubBuffer1Config->divFactor) |
                              XSPI_BUFCR_SUBBUF1_DIV(ahbBufferConfigs[i]->ptrSubBuffer2Config->divFactor);

            /* Set AHB buffer sub buffer start and end address range. */
            for (uint8_t j = 0U; j < XSPI_BUF_ADDR_RANGE_COUNT2; j++)
            {
                curSubBufferConfig =
                    (xspi_ahbBuffer_sub_buffer_config_t *)(ahbBufferConfigs[i]->ptrSubBuffer0Config) + j;
                subBufferStartAddr = ((curSubBufferConfig->startAddr) & 0xFFFF0000UL) >> 16UL;
                subBufferEndAddr   = ((curSubBufferConfig->startAddr) & 0xFFFF0000UL) >> 16UL;

                base->BUF_ADDR_RANGE[i][j] =
                    XSPI_BUF_ADDR_RANGE_STARTADR(subBufferStartAddr) | XSPI_BUF_ADDR_RANGE_ENDADR(subBufferEndAddr);

                if (curSubBufferConfig->enableAhbMonitor)
                {
                    /* Enable AHB monitor to current sub division. */
                    XSPI_EnableAhbBufferPerfMonitor(base, i, j);
                }
            }
        }
    }
    return kStatus_Success;
}

/*!
 * brief Set AHB transaction(read/write) split size.
 *
 * note For AHB write, if enable split feature(ahbSplitSize not set as kXSPI_AhbSplitSizeDisabled), XSPI will split one
 * single AHB write burst into smaller bursts on external device side.
 *
 * note For AHB read, if enable split feature, HW will realign the prefetch size to split size and in that way split
 * a single read burst into smaller bursts.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] ahbSplitSize Specify the AHB split size.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB access split size.
 */
status_t XSPI_SetAhbAccessSplitSize(XSPI_Type *base, xspi_ahb_split_size_t ahbSplitSize)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    if (ahbSplitSize == kXSPI_AhbSplitSizeDisabled)
    {
        base->BFGENCR &= ~XSPI_BFGENCR_SPLITEN_MASK;
    }
    else
    {
        base->BFGENCR |= XSPI_BFGENCR_SPLITEN_MASK;
        base->BFGENCR = (base->BFGENCR & (~XSPI_BFGENCR_AHBSSIZE_MASK)) | XSPI_BFGENCR_AHBSSIZE(ahbSplitSize);
    }

    return kStatus_Success;
}

/*!
 * brief Specify how long XSPI can hold HEADY low while waiting for response to an AHB transfer.
 *
 * note If the specified time out value expired, an AHB illegal transaction error will be triggerred.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] timeoutValue In multiples of 50000 AHB clock cycles, default value is 3,
 *                      it means waiting for 150000 AHB clock cycles.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_Success Success to set AHB HREADY timeout value.
 */
status_t XSPI_UpdateAhbHreadyTimeOutValue(XSPI_Type *base, uint16_t timeoutValue)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    base->AHRDYTO = XSPI_AHRDYTO_HREADY_TO(timeoutValue);

    return kStatus_Success;
}

/*!
 * brief Pre-define error payload which will be provided on the read data bus when the HEADY timeout counter expires.
 *
 * note If the incoming AHB read request master is not mapped to any of the AHB buffer, the XSPI will keep the AHB
 * HREADY signal low and will provided this pre-defined error payload on the AHB read data bus when the HEADY timeout
 * counter expires.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] highPayload High 32bits payload to set.
 * param[in] lowPayload Low 32bits payload to set.

 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_Success Success to set AHB HREADY timeout value.
 */
status_t XSPI_SetAhbErrorPayload(XSPI_Type *base, uint32_t highPayload, uint32_t lowPayload)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    base->AHB_ERR_PAYLOAD_HI = highPayload;
    base->AHB_ERR_PAYLOAD_LO = lowPayload;

    return kStatus_Success;
}

/*!
 * brief Return AHB read error information.
 * 
 * param[in] base XSPI peripheral base address.
 *
 * return Latest AHB read error information, in type of xspi_ahb_read_error_info_t.
 */
xspi_ahb_read_error_info_t XSPI_ReturnAhbReadErrorInfo(XSPI_Type *base)
{
    xspi_ahb_read_error_info_t errorInfo;

    errorInfo.errorAddr   = base->AHB_RD_ERR_ADDR;
    errorInfo.errMasterId = (uint8_t)(base->AHB_RD_ERR_MID & XSPI_AHB_RD_ERR_MID_REMID_MASK);

    return errorInfo;
}

/*!
 * brief Get Ahb request suspend information if priority mechanism is enabled.
 *
 * param[in] base XSPI peripheral base address.
 * param[out] ptrSuspendInfo Contain latest suspend info, the value may be 0xFF if the item is invalid in current
 * suspend state.
 */
void XSPI_GetAhbRequestSuspendInfo(XSPI_Type *base, xspi_ahb_request_suspend_info_t *ptrSuspendInfo)
{
    uint32_t tmp32 = 0UL;

    tmp32 = base->SPNDST;

    ptrSuspendInfo->state       = (xspi_ahb_request_suspend_state_t)(uint8_t)(tmp32 & XSPI_SPNDST_STATE_MASK);
    ptrSuspendInfo->subBufferId = 0xFFU;
    ptrSuspendInfo->ahbBufferId = 0xFFU;
    ptrSuspendInfo->dataLeft    = 0xFFFFU;
    ptrSuspendInfo->address     = 0xFFFFFFFFUL;

    if ((ptrSuspendInfo->state == kXSPI_AhbRequestSuspended) || (ptrSuspendInfo->state == kXSPI_AhbReqestResumed))
    {
        ptrSuspendInfo->subBufferId = (uint8_t)((tmp32 & XSPI_SPNDST_SPDSBUF_MASK) >> XSPI_SPNDST_SPDSBUF_SHIFT);
        ptrSuspendInfo->ahbBufferId = (uint8_t)((tmp32 & XSPI_SPNDST_SPDBUF_MASK) >> XSPI_SPNDST_SPDBUF_SHIFT);
        ptrSuspendInfo->dataLeft    = (uint16_t)((tmp32 & XSPI_SPNDST_DATLFT_MASK) >> XSPI_SPNDST_DATLFT_SHIFT);

        if (ptrSuspendInfo->state == kXSPI_AhbRequestSuspended)
        {
            ptrSuspendInfo->address = base->SPNDST_ADDR;
        }
    }
}

/*!
 * brief Enable/disable the clearing of AHB read prefetch buffers when the same flash address is written by an
 *   AHB or IP command.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] enable Used to enable/disable write flush.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * retval kStatus_Success Successfully to enable/disable AHB buffer write flush.
 */
status_t XSPI_EnableAhbBufferWriteFlush(XSPI_Type *base, bool enable)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    if (enable)
    {
        base->BFGENCR |= XSPI_BFGENCR_WR_FLUSH_EN_MASK;
    }
    else
    {
        base->BFGENCR &= ~XSPI_BFGENCR_WR_FLUSH_EN_MASK;
    }

    return kStatus_Success;
}

/*!
 * brief Block access(write and read) after the AHB write operation.
 *
 * note If external flash support RWW, read should not be blocked:
 * code
 *  XSPI_BlockAccessAfterAhbWrite(XSPI0, true, false);
 * endcode
 *
 * note If either of access is blocked, the page program wait flag will be asserted after
 * an AHB write sequence completed. The assertion of flag will lock the arbitration and all
 * access to the external memory are blocked. And the internal "page wait time" counter
 * starts(Invoke XSPI_UpdatePageWaitTimeCounter to update counter value). After this counter
 * reaches the value, a read is triggered by the XSPI module to read external device's
 * status register(The seq id should be pre-defiend by XSPI_SetAhbReadStatusRegSeqId),
 * and the value is stored in the XSPI internal regsiter. And there are two
 * options(Invoke XSPI_SelectPPWFlagClearPolicy to select) to clear the asserted page program wait flag.
 *      1. Automatic cleared by XSPI hardware;
 *      2. Cleared by software.
 *
 * note As soon as the page program wait flag is asserted, another counter(SFP arbitration
 * lock counter) also started, if the flag not cleared in desired counter value the
 * arbitration lock timeout error will be generated.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] blockSequentWrite Block sequence write or not.
 * param[in] blockRead Block read or not.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_Success Success to set related registers..
 */
status_t XSPI_BlockAccessAfterAhbWrite(XSPI_Type *base, bool blockSequentWrite, bool blockRead)
{
    uint32_t tmp32 = 0UL;

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    tmp32 = base->AWRCR;
    tmp32 &= ~(XSPI_AWRCR_PPW_RD_DIS_MASK | XSPI_AWRCR_PPW_WR_DIS_MASK);
    tmp32 |= XSPI_AWRCR_PPW_RD_DIS(blockRead) | XSPI_AWRCR_PPW_WR_DIS(blockSequentWrite);

    base->AWRCR = tmp32;

    return kStatus_Success;
}

/*!
 * brief Set Page program wait flag clear policy.
 * 
 * note If set as hardware policy, the device's WIP information should be set by invoking XSPI_SetSFMStatusRegInfo()
 *
 * param[in] base XSPI peripheral base address.
 * param[in] policy Specify the policy to clear page program wait flag.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set PPW flag clear policy.
 */
status_t XSPI_SelectPPWFlagClearPolicy(XSPI_Type *base, xspi_ppw_flag_clear_policy_t policy)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    if (policy == kXSPI_HardwareClearPPWFlag)
    {
        base->BFGENCR |= XSPI_BFGENCR_PPWF_CLR_MASK;
    }
    else
    {
        base->BFGENCR &= ~XSPI_BFGENCR_PPWF_CLR_MASK;
    }

    return kStatus_Success;
}

/*!
 * brief Update page wait timeout counter.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] countValue The value of counter, in AHB clock cycles.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_PageProgramWaitFlagAsserted Page program wait flag already asserted.
 * retval kStatus_Success Successfully to update page wait timeout counter.
 */
status_t XSPI_UpdatePageWaitTimeCounter(XSPI_Type *base, uint32_t countValue)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if ((base->FR & XSPI_FR_PPWF_MASK) != 0UL)
    {
        return kStatus_XSPI_PageProgramWaitFlagAsserted;
    }

    base->PPWF_TCNT = countValue;

    return kStatus_Success;
}

/*!
 * brief Set AHB read status register sequence Id
 *
 * note The read status sequence only triggerred when the page wait time counter expired.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] seqId Specify the sequence Id in LUT used for AHB read status register.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB read status register sequence Id.
 */
status_t XSPI_SetAhbReadStatusRegSeqId(XSPI_Type *base, uint8_t seqId)
{
    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    base->BFGENCR = ((base->BFGENCR & (~XSPI_BFGENCR_SEQID_RDSR_MASK)) | XSPI_BFGENCR_SEQID_RDSR(seqId));

    return kStatus_Success;
}

/*!
 * brief Set Serial flash memory status register information
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrStatusRegInfo Pointer to the variable which contain status register information.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_PageProgramWaitFlagAsserted Page program wait flag already asserted.
 * retval kStatus_Success Successfully to set status register information.
 */
status_t XSPI_SetSFMStatusRegInfo(XSPI_Type *base, xspi_device_status_reg_info_t *ptrStatusRegInfo)
{
    assert(ptrStatusRegInfo != NULL);

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if ((base->FR & XSPI_FR_PPWF_MASK) != 0UL)
    {
        return kStatus_XSPI_PageProgramWaitFlagAsserted;
    }

    uint32_t tmp32 = 0UL;

    tmp32 = (base->PPW_RDSR) &
            ~(XSPI_PPW_RDSR_RDSR_VAL_CHK_MASK | XSPI_PPW_RDSR_RDSR_HWORD_SEL_MASK | XSPI_PPW_RDSR_LOC_MASK);

    tmp32 |= XSPI_PPW_RDSR_RDSR_VAL_CHK(ptrStatusRegInfo->value1Expired) |
             XSPI_PPW_RDSR_RDSR_HWORD_SEL(ptrStatusRegInfo->upperHalfWordSelected) |
             XSPI_PPW_RDSR_LOC(ptrStatusRegInfo->wipLocation);

    base->PPW_RDSR = tmp32;

    return kStatus_Success;
}

/*!
 * brief Set Buffer size for all 4 AHB buffers.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] buf0Size Specify size of AHB buffer0, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * param[in] buf1Size Specify size of AHB buffer1, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * param[in] buf2Size Specify size of AHB buffer2, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * param[in] buf3Size Specify size of AHB buffer3, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * retval kStatus_Success Success to set AHB buffer size.
 */
status_t XSPI_UpdateAhbBufferSize(
    XSPI_Type *base, uint16_t buf0Size, uint16_t buf1Size, uint16_t buf2Size, uint16_t buf3Size)
{
    /* The total size of AHB buffer is 4KB. */
    assert((buf0Size + buf1Size + buf2Size + buf3Size) == 512U);

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    base->BUFIND[0] = XSPI_BUFIND_TPINDX(buf0Size);
    base->BUFIND[1] = XSPI_BUFIND_TPINDX((uint32_t)buf0Size + (uint32_t)buf1Size);
    base->BUFIND[2] = XSPI_BUFIND_TPINDX((uint32_t)buf0Size + (uint32_t)buf1Size + (uint32_t)buf2Size);

    (void)buf3Size;

    return kStatus_Success;
}

/*!
 * brief Get status of AHB sub buffer.
 *
 * note This function only useful when sub-division feature of the selected AHB buffer is enabled.
 *
 * param[in] base XSPI peripheral base address.
 * param[in] ahbBufferId The Id of AHB buffer, range from 0 to 3.
 * param[in] subBufferId The Id of AHB buffer sub division, range from 0 to 3.
 *
 * return Current status of selected AHB sub buffer, in type of ref xspi_ahb_sub_buffer_status_t.
 */
xspi_ahb_sub_buffer_status_t XSPI_GetAhbSubBufferStatus(XSPI_Type *base, uint8_t ahbBufferId, uint8_t subBufferId)
{
    uint32_t tmp32 = 0UL;
    uint32_t shift = 8UL * (uint32_t)ahbBufferId + 2UL * (uint32_t)subBufferId;
    uint32_t mask  = 0x3UL << shift;

    tmp32 = base->AHB_BUF_STATUS;
    return (xspi_ahb_sub_buffer_status_t)(uint32_t)((tmp32 & mask) >> shift);
}

/*!
 * brief Enable AHB buffer performance monitor for selected AHB buffer's sub buffer.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ahbBufferId Specify the selected AHB buffer.
 * param[in] subBufferId Specify the selected sub-buffer.
 */
void XSPI_EnableAhbBufferPerfMonitor(XSPI_Type *base, uint8_t ahbBufferId, uint8_t subBufferId)
{
    uint32_t tmp32 = 0UL;

    tmp32 = base->AHB_PERF_CTRL;

    tmp32 &= ~(XSPI_AHB_PERF_CTRL_SUB_BUF_SEL0_MASK << (2UL * (uint32_t)ahbBufferId));
    tmp32 |= XSPI_AHB_PERF_CTRL_SUB_BUF_SEL0(subBufferId) << (2UL * (uint32_t)ahbBufferId);

    tmp32 |= (uint32_t)XSPI_AHB_PERF_CTRL_BUF0_EN_MASK << (uint32_t)(ahbBufferId);

    base->AHB_PERF_CTRL = tmp32;
}
/***************************** AHB Access Control Low-Level Interfaces End ********************************/

/***************************** AHB Access Control Functional Interfaces Start ********************************/
/*!
 * brief Set AHB access configuration.
 * 
 * param[in] base XSPI peripheral base address.
 * param[in] ptrAhbAccessConfig Pointer to the variable which contains AHB access configurations.
 *
 * retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * retval kStatus_Success Success to set AHB read status register sequence Id.
 */
status_t XSPI_SetAhbAccessConfig(XSPI_Type *base, xspi_ahb_access_config_t *ptrAhbAccessConfig)
{
    assert(ptrAhbAccessConfig != NULL);

    if (XSPI_CheckAhbReadAccessAsserted(base))
    {
        return kStatus_XSPI_AhbReadAccessAsserted;
    }

    if (XSPI_CheckAhbWriteAccessAsserted(base))
    {
        return kStatus_XSPI_AhbWriteAccessAsserted;
    }

    if (XSPI_CheckGlobalConfigLocked(base))
    {
        return kStatus_XSPI_RegWriteLocked;
    }

    /* Configure AHB buffers. */
    (void)XSPI_SetAhbBufferConfig(base, &(ptrAhbAccessConfig->buffer[0]), &(ptrAhbAccessConfig->buffer[1]),
                                  &(ptrAhbAccessConfig->buffer[2]), &(ptrAhbAccessConfig->buffer[3]));
    (void)XSPI_SetAhbReadDataSeqId(base, ptrAhbAccessConfig->ARDSeqIndex);
    (void)XSPI_EnableAhbBufferWriteFlush(base, ptrAhbAccessConfig->enableAHBBufferWriteFlush);
    XSPI_EnableAhbReadPrefetch(base, ptrAhbAccessConfig->enableAHBPrefetch);
    (void)XSPI_SetAhbAccessSplitSize(base, ptrAhbAccessConfig->ahbSplitSize);
    (void)XSPI_SetAhbAccessBoundary(base, ptrAhbAccessConfig->ahbAlignment);

    base->AWRCR &= ~(XSPI_AWRCR_PPW_RD_DIS_MASK | XSPI_AWRCR_PPW_WR_DIS_MASK);

    if (ptrAhbAccessConfig->ptrAhbWriteConfig != NULL)
    {
        (void)XSPI_BlockAccessAfterAhbWrite(base, ptrAhbAccessConfig->ptrAhbWriteConfig->blockSequenceWrite,
                                            ptrAhbAccessConfig->ptrAhbWriteConfig->blockRead);
        (void)XSPI_SelectPPWFlagClearPolicy(base, ptrAhbAccessConfig->ptrAhbWriteConfig->policy);

        (void)XSPI_UpdatePageWaitTimeCounter(base, ptrAhbAccessConfig->ptrAhbWriteConfig->pageWaitTimeoutValue);

        base->BFGENCR = (base->BFGENCR & ~(XSPI_BFGENCR_SEQID_WR_MASK | XSPI_BFGENCR_SEQID_RDSR_MASK)) |
                        XSPI_BFGENCR_SEQID_WR(ptrAhbAccessConfig->ptrAhbWriteConfig->AWRSeqIndex) |
                        XSPI_BFGENCR_SEQID_WR_EN_MASK |
                        XSPI_BFGENCR_SEQID_RDSR(ptrAhbAccessConfig->ptrAhbWriteConfig->ARDSRSeqIndex);
    }

    (void)XSPI_SetAhbErrorPayload(base, ptrAhbAccessConfig->ahbErrorPayload.highPayload,
                                  ptrAhbAccessConfig->ahbErrorPayload.lowPayload);

    return kStatus_Success;
}

/***************************** AHB Access Control Functional Interfaces End ********************************/
