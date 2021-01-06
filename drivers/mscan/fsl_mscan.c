/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mscan.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mscan"
#endif

#define MSCAN_TIME_QUANTA_NUM (8)

#if (defined(FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG) && FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG)
#define MAX_SAMP (MSCAN_CANBTR1_SAMP_MASK >> MSCAN_CANBTR1_SAMP_SHIFT)
#define MAX_SJW  (MSCAN_CANBTR0_SJW_MASK >> MSCAN_CANBTR0_SJW_SHIFT)
#define MAX_BRP  (MSCAN_CANBTR0_BRP_MASK >> MSCAN_CANBTR0_BRP_SHIFT)

#define MAX_TSEG1 (MSCAN_CANBTR1_TSEG1_MASK >> MSCAN_CANBTR1_TSEG1_SHIFT)
#define MIN_TSEG1 (3U)
#define MAX_TSEG2 (MSCAN_CANBTR1_TSEG2_MASK >> MSCAN_CANBTR1_TSEG2_SHIFT)
#define MIN_TSEG2 (1U)

/* MsCAN timing setting formula:
 * MSCAN_TIME_QUANTA_NUM = 1 + (TSEG1 + 1) + (TSEG2 + 1);
 */
#define MSCAN_MAX_TIME_QUANTA (1U + MAX_TSEG1 + 1U + MAX_TSEG2 + 1U)
#define MSCAN_MIN_TIME_QUANTA (1U + MIN_TSEG1 + 1U + MIN_TSEG2 + 1U)

#define IDEAL_SP_LOW     (750U)
#define IDEAL_SP_MID     (800U)
#define IDEAL_SP_HIGH    (875U)
#define IDEAL_SP_FACTOR  (1000U)
#define MAX_CAN_BAUDRATE (1000000U)
#endif

/*! @brief MSCAN Internal State. */
enum _mscan_state
{
    kMSCAN_StateIdle     = 0x0, /*!< MB/RxFIFO idle.*/
    kMSCAN_StateRxData   = 0x1, /*!< MB receiving.*/
    kMSCAN_StateRxRemote = 0x2, /*!< MB receiving remote reply.*/
    kMSCAN_StateTxData   = 0x3, /*!< MB transmitting.*/
    kMSCAN_StateTxRemote = 0x4, /*!< MB transmitting remote request.*/
    kMSCAN_StateRxFifo   = 0x5, /*!< RxFIFO receiving.*/
};

/*! @brief MSCAN message buffer CODE for Rx buffers. */
enum _mscan_mb_code_rx
{
    kMSCAN_RxMbInactive = 0x0, /*!< MB is not active.*/
    kMSCAN_RxMbFull     = 0x2, /*!< MB is full.*/
    kMSCAN_RxMbEmpty    = 0x4, /*!< MB is active and empty.*/
    kMSCAN_RxMbOverrun  = 0x6, /*!< MB is overwritten into a full buffer.*/
    kMSCAN_RxMbBusy     = 0x8, /*!< FlexCAN is updating the contents of the MB.*/
                               /*!  The CPU must not access the MB.*/
    kMSCAN_RxMbRanswer = 0xA,  /*!< A frame was configured to recognize a Remote Request Frame */
                               /*!  and transmit a Response Frame in return.*/
    kMSCAN_RxMbNotUsed = 0xF,  /*!< Not used.*/
};

/*! @brief FlexCAN message buffer CODE FOR Tx buffers. */
enum _mscan_mb_code_tx
{
    kFLEXCAN_TxMbInactive     = 0x8, /*!< MB is not active.*/
    kFLEXCAN_TxMbAbort        = 0x9, /*!< MB is aborted.*/
    kFLEXCAN_TxMbDataOrRemote = 0xC, /*!< MB is a TX Data Frame(when MB RTR = 0) or */
                                     /*!< MB is a TX Remote Request Frame (when MB RTR = 1).*/
    kFLEXCAN_TxMbTanswer = 0xE,      /*!< MB is a TX Response Request Frame from */
                                     /*!  an incoming Remote Request Frame.*/
    kFLEXCAN_TxMbNotUsed = 0xF,      /*!< Not used.*/
};

/* Typedef for interrupt handler. */
typedef void (*mscan_isr_t)(MSCAN_Type *base, mscan_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the MsCAN instance from peripheral base address.
 *
 * @param base MsCAN peripheral base address.
 * @return MsCAN instance.
 */
static uint32_t MSCAN_GetInstance(MSCAN_Type *base);

/*!
 * @brief Enter MsCAN Initial Mode.
 *
 * This function makes the MsCAN work under Initial Mode.
 *
 * @param base MsCAN peripheral base address.
 */
static void MSCAN_EnterInitMode(MSCAN_Type *base);

/*!
 * @brief Exit MsCAN Initial Mode.
 *
 * This function makes the MsCAN leave Initial Mode.
 *
 * @param base MsCAN peripheral base address.
 */
static void MSCAN_ExitInitMode(MSCAN_Type *base);

/*!
 * @brief Set Baud Rate of MsCAN.
 *
 * This function set the baud rate of MsCAN.
 *
 * @param base MsCAN peripheral base address.
 * @param sourceClock_Hz Source Clock in Hz.
 * @param baudRate_Bps Baud Rate in Bps.
 */
static void MSCAN_SetBaudRate(MSCAN_Type *base, uint32_t sourceClock_Hz, uint32_t baudRate_Bps);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG) && FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG)
/*!
 * @brief Calculates the segment values for a single bit time for classical MSCAN
 *
 * @param baudRate The data speed in bps
 * @param tqNum Number of time quantas per bit
 * @param pconfig Pointer to the FlexCAN timing configuration structure.
 *
 * @return TRUE if valid Segments found, FALSE if failed to get valid segments
 */
static bool MSCAN_GetSegments(uint32_t baudRate, uint32_t tqNum, mscan_timing_config_t *pconfig);

/*!
 * @brief Calculates the improved timing values by specific baudrates for classical MSCAN
 *
 * @param baudRate  The classical MSCAN speed in bps defined by user
 * @param sourceClock_Hz The Source clock data speed in bps. Zero to disable baudrate switching
 * @param pconfig Pointer to the MSCAN timing configuration structure.
 *
 * @return TRUE if timing configuration found, FALSE if failed to find configuration
 */
static bool MSCAN_CalculateImprovedTimingValues(uint32_t baudRate,
                                                uint32_t sourceClock_Hz,
                                                mscan_timing_config_t *pconfig);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of MsCAN peripheral base address. */
static MSCAN_Type *const s_mscanBases[] = MSCAN_BASE_PTRS;

/* Array of MSCAN IRQ number. */
static const IRQn_Type s_mscanRxWarningIRQ[] = MSCAN_RX_IRQS;
static const IRQn_Type s_mscanTxWarningIRQ[] = MSCAN_TX_IRQS;
static const IRQn_Type s_mscanWakeUpIRQ[]    = MSCAN_WAKE_UP_IRQS;
static const IRQn_Type s_mscanErrorIRQ[]     = MSCAN_ERR_IRQS;

/* Array of MsCAN handle. */
static mscan_handle_t *s_mscanHandle[ARRAY_SIZE(s_mscanBases)];

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of MsCAN clock name. */
static const clock_ip_name_t s_mscanClock[] = MSCAN_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* MsCAN ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static mscan_isr_t s_mscanIsr = (mscan_isr_t)DefaultISR;
#else
static mscan_isr_t s_mscanIsr;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t MSCAN_GetInstance(MSCAN_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_mscanBases); instance++)
    {
        if (s_mscanBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_mscanBases));

    return instance;
}

static void MSCAN_EnterInitMode(MSCAN_Type *base)
{
    /* Set initial request bit. */
    base->CANCTL0 |= MSCAN_CANCTL0_INITRQ_MASK;

    /* Wait until the MsCAN Module enters initial mode. */
    while (0U == (base->CANCTL1 & MSCAN_CANCTL1_INITAK_MASK))
    {
    }
}

static void MSCAN_ExitInitMode(MSCAN_Type *base)
{
    /* Clear initial request bit. */
    base->CANCTL0 &= ~((uint8_t)MSCAN_CANCTL0_INITRQ_MASK);

    /* Wait until the MsCAN Module exits initial mode. */
    while (0U != (base->CANCTL1 & MSCAN_CANCTL1_INITAK_MASK))
    {
    }
}

#if (defined(FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG) && FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG)
/*!
 * @brief Calculates the segment values for a single bit time for classical MSCAN
 *
 * @param baudRate The data speed in bps
 * @param tqNum Number of time quantas per bit
 * @param pconfig Pointer to the FlexCAN timing configuration structure.
 *
 * @return TRUE if valid Segments found, FALSE if failed to get valid segments
 */
static bool MSCAN_GetSegments(uint32_t baudRate, uint32_t tqNum, mscan_timing_config_t *pconfig)
{
    uint32_t ideal_sp;
    uint32_t p1;
    bool fgRet = false;

    /* get ideal sample point. */
    if (baudRate >= 1000000U)
    {
        ideal_sp = IDEAL_SP_LOW;
    }
    else if (baudRate >= 800000U)
    {
        ideal_sp = IDEAL_SP_MID;
    }
    else
    {
        ideal_sp = IDEAL_SP_HIGH;
    }

    /* distribute time quanta. */
    p1 = tqNum * (uint32_t)ideal_sp;

    /* Caculate for time segment 1. */
    pconfig->timeSeg1 = (uint8_t)(p1 / IDEAL_SP_FACTOR - 1U);
    if ((pconfig->timeSeg1 <= MAX_TSEG1) && (pconfig->timeSeg1 >= MIN_TSEG1))
    {
        if (pconfig->timeSeg1 <= ((uint8_t)tqNum - 3U))
        {
            /* Caculate for time sgement 2. */
            pconfig->timeSeg2 = (uint8_t)tqNum - (pconfig->timeSeg1 + 3U);

            if ((pconfig->timeSeg2 <= MAX_TSEG2) && (pconfig->timeSeg2 >= MIN_TSEG2))
            {
                /* subtract one TQ for sync seg. */
                /* sjw is 20% of total TQ, rounded to nearest int. */
                pconfig->sJumpwidth = ((uint8_t)tqNum + (5U - 1U)) / 5U - 1U;

                if (pconfig->sJumpwidth > MAX_SJW)
                {
                    pconfig->sJumpwidth = MAX_SJW;
                }

                fgRet = true;
            }
        }
    }
    return fgRet;
}

/*!
 * @brief Calculates the improved timing values by specific baudrates for classical MSCAN
 *
 * @param baudRate  The classical MSCAN speed in bps defined by user
 * @param sourceClock_Hz The Source clock data speed in bps. Zero to disable baudrate switching
 * @param pconfig Pointer to the MSCAN timing configuration structure.
 *
 * @return TRUE if timing configuration found, FALSE if failed to find configuration
 */
static bool MSCAN_CalculateImprovedTimingValues(uint32_t baudRate,
                                                uint32_t sourceClock_Hz,
                                                mscan_timing_config_t *pconfig)
{
    uint32_t clk;   /* the clock is tqNumb x baudRateFD. */
    uint32_t tqNum; /* Numbers of TQ. */
    bool fgRet = false;

    /* observe baud rate maximums. */
    assert(baudRate <= MAX_CAN_BAUDRATE);

    /*  Auto Improved Protocal timing for CBT. */
    for (tqNum = MSCAN_MAX_TIME_QUANTA; tqNum >= MSCAN_MIN_TIME_QUANTA; tqNum--)
    {
        clk = baudRate * tqNum;
        if (clk > sourceClock_Hz)
        {
            continue; /* tqNum too large, clk has been exceed sourceClock_Hz. */
        }

        if ((sourceClock_Hz / clk * clk) != sourceClock_Hz)
        {
            continue; /*  Non-supporting: the frequency of clock source is not divisible by target baud rate, the user
                      should change a divisible baud rate. */
        }

        pconfig->priDiv = (uint8_t)(sourceClock_Hz / clk - 1U);
        if (pconfig->priDiv > MAX_BRP)
        {
            break; /* The frequency of source clock is too large or the baud rate is too small, the pre-divider could
                      not handle it. */
        }

        if (MSCAN_GetSegments(baudRate, tqNum, pconfig))
        {
            /* Get the best timing configuration. */
            fgRet = true;
            break;
        }
    }

    return fgRet;
}
#endif

static void MSCAN_SetBaudRate(MSCAN_Type *base, uint32_t sourceClock_Hz, uint32_t baudRate_Bps)
{
    mscan_timing_config_t timingConfig;
    uint32_t priDiv = baudRate_Bps * (uint32_t)MSCAN_TIME_QUANTA_NUM;

    /* Assertion: Desired baud rate is too high. */
    assert(baudRate_Bps <= 1000000U);
    /* Assertion: Source clock should greater than baud rate * MSCAN_TIME_QUANTA_NUM. */
    assert(priDiv <= sourceClock_Hz);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG) && FSL_FEATURE_FLEXCAN_HAS_IMPROVED_TIMING_CONFIG)
    /* MsCAN timing setting formula:
     * MSCAN_TIME_QUANTA_NUM = 1 + (TSEG1 + 1) + (TSEG2 + 1);
     * We can calculate SEG1 and SEG2 according to the load factor
     */
    if (false == MSCAN_CalculateImprovedTimingValues(baudRate_Bps, sourceClock_Hz, &timingConfig))
#endif
    {
        if (0U == priDiv)
        {
            priDiv = 1U;
        }

        priDiv = (sourceClock_Hz / priDiv) - 1U;

        /* Desired baud rate is too low. */
        if (priDiv > 0x3FU)
        {
            priDiv = 0x3FU;
        }

        timingConfig.priDiv     = (uint8_t)priDiv;
        timingConfig.timeSeg1   = 3U;
        timingConfig.timeSeg2   = 2U;
        timingConfig.sJumpwidth = 0U;
    }
    timingConfig.samp = 0;

    /* Update actual timing characteristic. */
    MSCAN_SetTimingConfig(base, &timingConfig);
}

/*!
 * brief Initializes a MsCAN instance.
 *
 * This function initializes the MsCAN module with user-defined settings.
 * This example shows how to set up the mscan_config_t parameters and how
 * to call the MSCAN_Init function by passing in these parameters.
 *  code
 *   mscan_config_t mscanConfig;
 *   mscanConfig.clkSrc            = kMSCAN_ClkSrcOsc;
 *   mscanConfig.baudRate          = 1250000U;
 *   mscanConfig.enableTimer       = false;
 *   mscanConfig.enableLoopBack    = false;
 *   mscanConfig.enableWakeup      = false;
 *   mscanConfig.enableListen      = false;
 *   mscanConfig.busoffrecMode     = kMSCAN_BusoffrecAuto;
 *   mscanConfig.filterConfig.filterMode = kMSCAN_Filter32Bit;
 *   MSCAN_Init(MSCAN, &mscanConfig, 8000000UL);
 *   endcode
 *
 * param base MsCAN peripheral base address.
 * param config Pointer to the user-defined configuration structure.
 * param sourceClock_Hz MsCAN Protocol Engine clock source frequency in Hz.
 */
void MSCAN_Init(MSCAN_Type *base, const mscan_config_t *config, uint32_t sourceClock_Hz)
{
    uint8_t ctl0Temp, ctl1Temp;
    uint32_t u4temp;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance;
#endif

    /* Assertion. */
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    instance = MSCAN_GetInstance(base);
    /* Enable MsCAN clock. */
    CLOCK_EnableClock(s_mscanClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable MsCAN Module for configuartion. */
    MSCAN_Enable(base, true);

    /* Enter initialization mode for MSCAN configuration. */
    MSCAN_EnterInitMode(base);

    ctl0Temp = base->CANCTL0;
    ctl1Temp = base->CANCTL1;

    /* Enable Self Wake Up Mode. */
    ctl0Temp = (config->enableWakeup) ? ctl0Temp | (uint8_t)MSCAN_CANCTL0_WUPE_MASK :
                                        ctl0Temp & ~((uint8_t)MSCAN_CANCTL0_WUPE_MASK);
    /* Enable Loop Back Mode. */
    ctl1Temp = (config->enableLoopBack) ? ctl1Temp | (uint8_t)MSCAN_CANCTL1_LOOPB_MASK :
                                          ctl1Temp & ~((uint8_t)MSCAN_CANCTL1_LOOPB_MASK);
    /* Enable Listen Mode. */
    ctl1Temp = (config->enableListen) ? ctl1Temp | (uint8_t)MSCAN_CANCTL1_LISTEN_MASK :
                                        ctl1Temp & ~((uint8_t)MSCAN_CANCTL1_LISTEN_MASK);
    /* Clock source selection. */
    ctl1Temp = (kMSCAN_ClkSrcBus == config->clkSrc) ? ctl1Temp | (uint8_t)MSCAN_CANCTL1_CLKSRC_MASK :
                                                      ctl1Temp & ~((uint8_t)MSCAN_CANCTL1_CLKSRC_MASK);

    /* Save CTLx Configuation. */
    base->CANCTL0 = ctl0Temp;
    base->CANCTL1 = ctl1Temp;

    /* Configure ID acceptance filter setting. */
    MSCAN_SetIDFilterMode(base, config->filterConfig.filterMode);
    u4temp = config->filterConfig.u32IDAR0; /* To fix MISRA-C 2012 Rule 11.8 issue. */
    MSCAN_WriteIDAR0(base, (uint8_t *)(&u4temp));
    u4temp = config->filterConfig.u32IDMR0;
    MSCAN_WriteIDMR0(base, (uint8_t *)(&u4temp));
    u4temp = config->filterConfig.u32IDAR1;
    MSCAN_WriteIDAR1(base, (uint8_t *)(&u4temp));
    u4temp = config->filterConfig.u32IDMR1;
    MSCAN_WriteIDMR1(base, (uint8_t *)(&u4temp));

    /* Baud Rate Configuration.*/
    MSCAN_SetBaudRate(base, sourceClock_Hz, config->baudRate);

    /* Enter normal mode. */
    MSCAN_ExitInitMode(base);

    /* Enable Timer. */
    base->CANCTL0 = (config->enableTimer) ? base->CANCTL0 | (uint8_t)MSCAN_CANCTL0_TIME_MASK :
                                            base->CANCTL0 & ~((uint8_t)MSCAN_CANCTL0_TIME_MASK);
}

/*!
 * brief De-initializes a MsCAN instance.
 *
 * This function disables the MsCAN module clock and sets all register values
 * to the reset value.
 *
 * param base MsCAN peripheral base address.
 */
void MSCAN_Deinit(MSCAN_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance;
#endif

    /* Disable MsCAN module. */
    MSCAN_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    instance = MSCAN_GetInstance(base);
    /* Disable MsCAN clock. */
    CLOCK_DisableClock(s_mscanClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration structure.
 *
 * This function initializes the MsCAN configuration structure to default values.
 *
 * param config Pointer to the MsCAN configuration structure.
 */
void MSCAN_GetDefaultConfig(mscan_config_t *config)
{
    /* Assertion. */
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Initialize MsCAN Module config struct with default value. */
    config->baudRate                = 1000000U;
    config->enableTimer             = false;
    config->enableWakeup            = false;
    config->clkSrc                  = kMSCAN_ClkSrcOsc;
    config->enableLoopBack          = false;
    config->enableListen            = false;
    config->busoffrecMode           = kMSCAN_BusoffrecAuto;
    config->filterConfig.filterMode = kMSCAN_Filter32Bit;
}

/*!
 * brief Sets the MsCAN protocol timing characteristic.
 *
 * This function gives user settings to CAN bus timing characteristic.
 * The function is for an experienced user. For less experienced users, call
 * the MSCAN_Init() and fill the baud rate field with a desired value.
 * This provides the default timing characteristics to the module.
 *
 * Note that calling MSCAN_SetTimingConfig() overrides the baud rate set
 * in MSCAN_Init().
 *
 * param base MsCAN peripheral base address.
 * param config Pointer to the timing configuration structure.
 */
void MSCAN_SetTimingConfig(MSCAN_Type *base, const mscan_timing_config_t *config)
{
    /* Assertion. */
    assert(NULL != config);

    /* Enter Inialization Mode. */
    MSCAN_EnterInitMode(base);

    /* Cleaning previous Timing Setting. */
    base->CANBTR0 &= ~((uint8_t)MSCAN_CANBTR0_BRP_MASK | (uint8_t)MSCAN_CANBTR0_SJW_MASK);
    base->CANBTR1 &=
        ~((uint8_t)MSCAN_CANBTR1_TSEG1_MASK | (uint8_t)MSCAN_CANBTR1_TSEG2_MASK | (uint8_t)MSCAN_CANBTR1_SAMP_MASK);

    /* Updating Timing Setting according to configuration structure. */
    base->CANBTR0 |= (MSCAN_CANBTR0_BRP(config->priDiv) | MSCAN_CANBTR0_SJW(config->sJumpwidth));
    base->CANBTR1 |= (MSCAN_CANBTR1_TSEG1(config->timeSeg1) | MSCAN_CANBTR1_TSEG2(config->timeSeg2) |
                      MSCAN_CANBTR1_SAMP(config->samp));

    /* Exit Inialization Mode. */
    MSCAN_ExitInitMode(base);
}

/*!
 * brief Writes a MsCAN Message to the Transmit Message Buffer.
 *
 * This function writes a CAN Message to the specified Transmit Message Buffer
 * and changes the Message Buffer state to start CAN Message transmit. After
 * that the function returns immediately.
 *
 * param base MsCAN peripheral base address.
 * param pTxFrame Pointer to CAN message frame to be sent.
 * retval kStatus_Success - Write Tx Message Buffer Successfully.
 * retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_WriteTxMb(MSCAN_Type *base, mscan_frame_t *pTxFrame)
{
    uint8_t txEmptyFlag;
    mscan_mb_t mb = {0};
    IDR1_3_UNION sIDR1, sIDR3;
    status_t status;
    uint8_t i;

    /* Write IDR. */
    if (kMSCAN_FrameFormatExtend == pTxFrame->format)
    {
        /* Deal with Extended frame. */
        sIDR1.IDR1.EID20_18_OR_SID2_0 = (uint8_t)pTxFrame->ID_Type.ExtID.EID20_18;
        sIDR1.IDR1.R_TSRR             = 1U;
        sIDR1.IDR1.R_TEIDE            = 1U;
        sIDR1.IDR1.EID17_15           = (uint8_t)pTxFrame->ID_Type.ExtID.EID17_15;
        sIDR3.IDR3.EID6_0             = (uint8_t)pTxFrame->ID_Type.ExtID.EID6_0;
        sIDR3.IDR3.ERTR               = (kMSCAN_FrameTypeRemote == pTxFrame->type) ? 1U : 0U;
        /* Write into MB structure. */
        mb.EIDR0 = (uint8_t)pTxFrame->ID_Type.ExtID.EID28_21;
        mb.EIDR1 = sIDR1.Bytes;
        mb.EIDR2 = (uint8_t)pTxFrame->ID_Type.ExtID.EID14_7;
        mb.EIDR3 = sIDR3.Bytes;
    }
    else
    {
        /* Deal with Standard frame. */
        sIDR1.IDR1.EID20_18_OR_SID2_0 = (uint8_t)pTxFrame->ID_Type.StdID.EID2_0;
        sIDR1.IDR1.R_TSRR             = 0U;
        sIDR1.IDR1.R_TEIDE            = 0U;
        sIDR1.IDR1.EID17_15           = 0U; /* Reserved for Standard frame*/
        /* Write into MB structure. */
        mb.EIDR0 = (uint8_t)pTxFrame->ID_Type.StdID.EID10_3;
        mb.EIDR1 = sIDR1.Bytes;
    }
    /* Write DLR, BPR */
    mb.DLR = pTxFrame->DLR;
    mb.BPR = pTxFrame->BPR;

    /* Write DSR */
    for (i = 0U; i < mb.DLR; i++)
    {
        mb.EDSR[i] = pTxFrame->DSR[i];
    }

    /* 1.Read TFLG to get the empty transmitter buffers. */
    txEmptyFlag = MSCAN_GetTxBufferEmptyFlag(base);

    if ((uint8_t)kMSCAN_TxBufFull != txEmptyFlag)
    {
        /* 2.Write TFLG value back. */
        MSCAN_TxBufferSelect(base, txEmptyFlag);
        /* Push contents of mb structure into hardware register. */
        base->TEIDR0 = mb.EIDR0;
        base->TEIDR1 = mb.EIDR1;
        base->TEIDR2 = mb.EIDR2;
        base->TEIDR3 = mb.EIDR3;
        for (i = 0U; i < mb.DLR; i++)
        {
            base->TEDSR[i] = mb.EDSR[i];
        }
        base->TDLR = mb.DLR;
        base->TBPR = mb.BPR;

        /* 3.Read TBSEL again to get lowest tx buffer, then write 1 to clear
        the corresponding bit to schedule transmission. */
        MSCAN_TxBufferLaunch(base, MSCAN_GetTxBufferSelect(base));

        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }
    return status;
}

/*!
 * brief Reads a MsCAN Message from Receive Message Buffer.
 *
 * This function reads a CAN message from a specified Receive Message Buffer.
 * The function fills a receive CAN message frame structure with
 * just received data and activates the Message Buffer again.
 * The function returns immediately.
 *
 * param base MsCAN peripheral base address.
 * param pRxFrame Pointer to CAN message frame structure for reception.
 * retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t MSCAN_ReadRxMb(MSCAN_Type *base, mscan_frame_t *pRxFrame)
{
    IDR1_3_UNION sIDR1;
    IDR1_3_UNION sIDR3;
    uint8_t i;
    status_t status;

    if (0U != MSCAN_GetRxBufferFullFlag(base))
    {
        sIDR1.Bytes      = MSCAN_ReadRIDR1(base);
        sIDR3.Bytes      = MSCAN_ReadRIDR3(base);
        pRxFrame->format = (mscan_frame_format_t)(sIDR1.IDR1.R_TEIDE);

        if (kMSCAN_FrameFormatExtend == pRxFrame->format) /* Extended frame. */
        {
            pRxFrame->type                   = (mscan_frame_type_t)(sIDR3.IDR3.ERTR);
            pRxFrame->ID_Type.ExtID.EID28_21 = MSCAN_ReadRIDR0(base);
            pRxFrame->ID_Type.ExtID.EID20_18 = sIDR1.IDR1.EID20_18_OR_SID2_0;
            pRxFrame->ID_Type.ExtID.EID17_15 = sIDR1.IDR1.EID17_15;
            pRxFrame->ID_Type.ExtID.EID14_7  = MSCAN_ReadRIDR2(base);
            pRxFrame->ID_Type.ExtID.EID6_0   = sIDR3.IDR3.EID6_0;
        }
        else /* Standard frame. */
        {
            pRxFrame->type                  = (mscan_frame_type_t)(sIDR1.IDR1.R_TSRR);
            pRxFrame->ID_Type.StdID.EID10_3 = MSCAN_ReadRIDR0(base);
            pRxFrame->ID_Type.StdID.EID2_0  = sIDR1.IDR1.EID20_18_OR_SID2_0;
        }

        pRxFrame->DLR = base->RDLR & 0x0FU;
        for (i = 0; i < pRxFrame->DLR; i++)
        {
            pRxFrame->DSR[i] = base->REDSR[i];
        }

        pRxFrame->TSRH = base->RTSRH;
        pRxFrame->TSRL = base->RTSRL;

        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Performs a polling send transaction on the CAN bus.
 *
 * Note that a transfer handle does not need to be created before calling this API.
 *
 * param base MsCAN peripheral base pointer.
 * param pTxFrame Pointer to CAN message frame to be sent.
 * retval kStatus_Success - Write Tx Message Buffer Successfully.
 * retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_TransferSendBlocking(MSCAN_Type *base, mscan_frame_t *pTxFrame)
{
    status_t status;

    /* Write Tx Message Buffer to initiate a data sending. */
    if (kStatus_Success == MSCAN_WriteTxMb(base, pTxFrame))
    {
        /* Wait until CAN Message send out. */
        while (0U == MSCAN_GetTxBufferStatusFlags(base, MSCAN_GetTxBufferSelect(base)))
        {
        }

        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Performs a polling receive transaction on the CAN bus.
 *
 * Note that a transfer handle does not need to be created before calling this API.
 *
 * param base MsCAN peripheral base pointer.
 * param pRxFrame Pointer to CAN message frame to be received.
 * retval kStatus_Success - Read Rx Message Buffer Successfully.
 * retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_TransferReceiveBlocking(MSCAN_Type *base, mscan_frame_t *pRxFrame)
{
    status_t status;

    /* Wait until a new message is available in Rx Message Buffer. */
    while (0U == MSCAN_GetRxBufferFullFlag(base))
    {
    }

    /* Read Received CAN Message. */
    if (kStatus_Success == MSCAN_ReadRxMb(base, pRxFrame))
    {
        /* Clear RXF flag to release the buffer. */
        MSCAN_ClearRxBufferFullFlag(base);
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Initializes the MsCAN handle.
 *
 * This function initializes the MsCAN handle, which can be used for other MsCAN
 * transactional APIs. Usually, for a specified MsCAN instance,
 * call this API once to get the initialized handle.
 *
 * param base MsCAN peripheral base address.
 * param handle MsCAN handle pointer.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 */
void MSCAN_TransferCreateHandle(MSCAN_Type *base,
                                mscan_handle_t *handle,
                                mscan_transfer_callback_t callback,
                                void *userData)
{
    assert(NULL != handle);

    uint8_t instance;

    /* Clean MSCAN transfer handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Get instance from peripheral base address. */
    instance = (uint8_t)MSCAN_GetInstance(base);

    /* Save the context in global variables to support the double weak mechanism. */
    s_mscanHandle[instance] = handle;

    /* Register Callback function. */
    handle->callback = callback;
    handle->userData = userData;

    s_mscanIsr = MSCAN_TransferHandleIRQ;

    /* We Enable Error & Status interrupt here, because this interrupt just
     * report current status of MSCAN module through Callback function.
     * It is insignificance without a available callback function.
     */
    if (handle->callback != NULL)
    {
        MSCAN_EnableRxInterrupts(base,
                                 (uint8_t)kMSCAN_StatusChangeInterruptEnable | (uint8_t)kMSCAN_WakeUpInterruptEnable);
    }
    else
    {
        MSCAN_DisableRxInterrupts(base,
                                  (uint8_t)kMSCAN_StatusChangeInterruptEnable | (uint8_t)kMSCAN_WakeUpInterruptEnable);
    }

    /* Enable interrupts in NVIC. */
    (void)EnableIRQ((IRQn_Type)(s_mscanRxWarningIRQ[instance]));
    (void)EnableIRQ((IRQn_Type)(s_mscanTxWarningIRQ[instance]));
    (void)EnableIRQ((IRQn_Type)(s_mscanWakeUpIRQ[instance]));
    (void)EnableIRQ((IRQn_Type)(s_mscanErrorIRQ[instance]));
}

/*!
 * brief Sends a message using IRQ.
 *
 * This function sends a message using IRQ. This is a non-blocking function, which returns
 * right away. When messages have been sent out, the send callback function is called.
 *
 * param base MsCAN peripheral base address.
 * param handle MsCAN handle pointer.
 * param xfer MsCAN Message Buffer transfer structure. See the #mscan_mb_transfer_t.
 * retval kStatus_Success        Start Tx Message Buffer sending process successfully.
 * retval kStatus_Fail           Write Tx Message Buffer failed.
 */
status_t MSCAN_TransferSendNonBlocking(MSCAN_Type *base, mscan_handle_t *handle, mscan_mb_transfer_t *xfer)
{
    /* Assertion. */
    assert(NULL != handle);
    assert(NULL != xfer);

    status_t status;

    /* Check if Message Buffer is idle. */

    /* Distinguish transmit type. */
    if (kMSCAN_FrameTypeRemote == xfer->frame->type)
    {
        handle->mbStateTx = (uint8_t)kMSCAN_StateTxRemote;

        /* Register user Frame buffer to receive remote Frame. */
        handle->mbFrameBuf = xfer->frame;
    }
    else
    {
        handle->mbStateTx = (uint8_t)kMSCAN_StateTxData;
    }

    if (kStatus_Success == MSCAN_WriteTxMb(base, xfer->frame))
    {
        /* Enable Message Buffer Interrupt. */
        MSCAN_EnableTxInterrupts(base, xfer->mask);

        status = kStatus_Success;
    }
    else
    {
        handle->mbStateTx = (uint8_t)kMSCAN_StateIdle;
        status            = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Receives a message using IRQ.
 *
 * This function receives a message using IRQ. This is non-blocking function, which returns
 * right away. When the message has been received, the receive callback function is called.
 *
 * param base MsCAN peripheral base address.
 * param handle MsCAN handle pointer.
 * param xfer MsCAN Message Buffer transfer structure. See the #mscan_mb_transfer_t.
 * retval kStatus_Success        - Start Rx Message Buffer receiving process successfully.
 * retval kStatus_MSCAN_RxBusy - Rx Message Buffer is in use.
 */
status_t MSCAN_TransferReceiveNonBlocking(MSCAN_Type *base, mscan_handle_t *handle, mscan_mb_transfer_t *xfer)
{
    /* Assertion. */
    assert(NULL != handle);
    assert(NULL != xfer);

    status_t status;

    /* Check if Message Buffer is idle. */
    if ((uint8_t)kMSCAN_StateIdle == handle->mbStateRx)
    {
        handle->mbStateRx = (uint8_t)kMSCAN_StateRxData;

        /* Register Message Buffer. */
        handle->mbFrameBuf = xfer->frame;

        /* Enable Message Buffer Interrupt. */
        MSCAN_EnableRxInterrupts(base, xfer->mask);

        status = kStatus_Success;
    }
    else
    {
        status = kStatus_MSCAN_RxBusy;
    }

    return status;
}

/*!
 * brief Aborts the interrupt driven message send process.
 *
 * This function aborts the interrupt driven message send process.
 *
 * param base MsCAN peripheral base address.
 * param handle MsCAN handle pointer.
 * param mask The MsCAN Tx Message Buffer mask.
 */
void MSCAN_TransferAbortSend(MSCAN_Type *base, mscan_handle_t *handle, uint8_t mask)
{
    /* Assertion. */
    assert(NULL != handle);

    /* Abort Tx request. */
    MSCAN_AbortTxRequest(base, mask);

    /* Clean Message Buffer. */
    MSCAN_DisableTxInterrupts(base, mask);

    handle->mbStateTx = (uint8_t)kMSCAN_StateIdle;
}

/*!
 * brief Aborts the interrupt driven message receive process.
 *
 * This function aborts the interrupt driven message receive process.
 *
 * param base MsCAN peripheral base address.
 * param handle MsCAN handle pointer.
 * param mask The MsCAN Rx Message Buffer mask.
 */
void MSCAN_TransferAbortReceive(MSCAN_Type *base, mscan_handle_t *handle, uint8_t mask)
{
    /* Assertion. */
    assert(NULL != handle);

    /* Disable Message Buffer Interrupt. */
    MSCAN_DisableRxInterrupts(base, mask);

    /* Un-register handle. */
    handle->mbStateRx = (uint8_t)kMSCAN_StateIdle;
}

/*!
 * brief MSCAN IRQ handle function.
 *
 * This function handles the MSCAN Error, the Message Buffer, and the Rx FIFO IRQ request.
 *
 * param base MSCAN peripheral base address.
 * param handle MSCAN handle pointer.
 */
void MSCAN_TransferHandleIRQ(MSCAN_Type *base, mscan_handle_t *handle)
{
    /* Assertion. */
    assert(NULL != handle);

    status_t status = kStatus_MSCAN_UnHandled;

    /* Get current State of Message Buffer. */
    if (0U != MSCAN_GetRxBufferFullFlag(base))
    {
        switch (handle->mbStateRx)
        {
            /* Solve Rx Data Frame. */
            case (uint8_t)kMSCAN_StateRxData:
                status = MSCAN_ReadRxMb(base, handle->mbFrameBuf);
                if (kStatus_Success == status)
                {
                    status = kStatus_MSCAN_RxIdle;
                }
                MSCAN_TransferAbortReceive(base, handle, (uint8_t)kMSCAN_RxFullInterruptEnable);
                break;

            /* Solve Rx Remote Frame. */
            case (uint8_t)kMSCAN_StateRxRemote:
                status = MSCAN_ReadRxMb(base, handle->mbFrameBuf);
                if (kStatus_Success == status)
                {
                    status = kStatus_MSCAN_RxIdle;
                }
                MSCAN_TransferAbortReceive(base, handle, (uint8_t)kMSCAN_RxFullInterruptEnable);
                break;

            default:
                /* To avoid MISRA-C 2012 rule 16.4 issue. */
                break;
        }
        MSCAN_ClearRxBufferFullFlag(base);
    }
    else
    {
        switch (handle->mbStateTx)
        {
            /* Solve Tx Data Frame. */
            case (uint8_t)kMSCAN_StateTxData:
                status = kStatus_MSCAN_TxIdle;
                MSCAN_TransferAbortSend(base, handle, (uint8_t)kMSCAN_TxEmptyInterruptEnable);
                break;

            /* Solve Tx Remote Frame. */
            case (uint8_t)kMSCAN_StateTxRemote:
                handle->mbStateRx = (uint8_t)kMSCAN_StateRxRemote;
                status            = kStatus_MSCAN_TxSwitchToRx;
                break;

            default:
                status = kStatus_MSCAN_UnHandled;
                break;
        }
    }

    handle->callback(base, handle, status, handle->userData);
}

#if defined(MSCAN)
void MSCAN_DriverIRQHandler(void);
void MSCAN_DriverIRQHandler(void)
{
    assert(NULL != s_mscanHandle[0]);

    s_mscanIsr(MSCAN, s_mscanHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
