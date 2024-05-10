/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mu1"
#endif

#if defined(MU_RSTS)
#define MU_RESETS_ARRAY MU_RSTS
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to mu clocks for each instance. */
static const clock_ip_name_t s_muClocks[] = MU_CLOCKS;

/*! @brief Pointers to mu bases for each instance. */
static MU_Type *const s_muBases[] = MU_BASE_PTRS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(MU_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_muResets[] = MU_RESETS_ARRAY;
#endif

/******************************************************************************
 * Code
 *****************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint32_t MU_GetInstance(MU_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < (sizeof(s_muBases) / sizeof(s_muBases[0])); instance++)
    {
        if (s_muBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < (sizeof(s_muBases) / sizeof(s_muBases[0])));

    return instance;
}
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * brief Initializes the MU module.
 *
 * This function enables the MU clock only.
 *
 * param base MU peripheral base address.
 */
void MU_Init(MU_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    (void)CLOCK_EnableClock(s_muClocks[MU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(MU_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_muResets[MU_GetInstance(base)]);
#endif
}

/*!
 * brief De-initializes the MU module.
 *
 * This function disables the MU clock only.
 *
 * param base MU peripheral base address.
 */
void MU_Deinit(MU_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    (void)CLOCK_DisableClock(s_muClocks[MU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Blocks to send a message.
 *
 * This function waits until the TX register is empty and sends the message.
 *
 * param base MU peripheral base address.
 * param regIndex  TX register index.
 * param msg      Message to send.
 */
void MU_SendMsg(MU_Type *base, uint32_t regIndex, uint32_t msg)
{
    assert(regIndex < MU_TR_COUNT);

    /* Wait TX register to be empty. */
    while (0U == (base->TSR & (1UL << regIndex)))
    {
        ; /* Intentional empty while*/
    }

    base->TR[regIndex] = msg;
}

/*!
 * brief Blocks to receive a message.
 *
 * This function waits until the RX register is full and receives the message.
 *
 * param base MU peripheral base address.
 * param regIndex  RX register index.
 * return The received message.
 */
uint32_t MU_ReceiveMsg(MU_Type *base, uint32_t regIndex)
{
    assert(regIndex < MU_RR_COUNT);

    /* Wait RX register to be full. */
    while (0U == (base->RSR & (1UL << regIndex)))
    {
        ; /* Intentional empty while*/
    }

    return base->RR[regIndex];
}

/*!
 * brief Blocks setting the 3-bit MU flags reflect on the other MU side.
 *
 * This function blocks setting the 3-bit MU flags. Every time the 3-bit MU flags are changed,
 * the status flag \c kMU_FlagsUpdatingFlag asserts indicating the 3-bit MU flags are
 * updating to the other side. After the 3-bit MU flags are updated, the status flag
 * \c kMU_FlagsUpdatingFlag is cleared by hardware. During the flags updating period,
 * the flags cannot be changed. This function waits for the MU status flag
 * \c kMU_FlagsUpdatingFlag cleared and sets the 3-bit MU flags.
 *
 * param base MU peripheral base address.
 * param flags The 3-bit MU flags to set.
 */
void MU_SetFlags(MU_Type *base, uint32_t flags)
{
    /* Wait for update finished. */
    while (0U != (base->SR & ((uint32_t)MU_SR_FUP_MASK)))
    {
        ; /* Intentional empty while*/
    }

    MU_SetFlagsNonBlocking(base, flags);
}

/*
 * brief Gets the MU status flags.
 *
 * This function returns the bit mask of the MU status flags. See _mu_status_flags.
 *
 * uint32_t flags;
 * flags = MU_GetStatusFlags(base);  Get all status flags.
 * if (kMU_Tx0EmptyFlag & flags)
 * {
 *     The TX0 register is empty. Message can be sent.
 *     MU_SendMsgNonBlocking(base, kMU_MsgReg0, MSG0_VAL);
 * }
 * if (kMU_Tx1EmptyFlag & flags)
 * {
 *     The TX1 register is empty. Message can be sent.
 *     MU_SendMsgNonBlocking(base, kMU_MsgReg1, MSG1_VAL);
 * }
 *
 * param base MU peripheral base address.
 * return      Bit mask of the MU status flags, see _mu_status_flags.
 */
uint32_t MU_GetStatusFlags(MU_Type *base)
{
    uint32_t flags = 0;

    /* TX */
    flags |= MU_TX_FLAG(base->TSR);

    /* RX */
    flags |= MU_RX_FLAG(base->RSR);

    /* General purpose interrupt */
    flags |= MU_GI_FLAG(base->GSR);

    /* Status */
    flags |= MU_STAT_FLAG(base->SR);

#if !(defined(FSL_FEATURE_MU_NO_CORE_STATUS) && (0 != FSL_FEATURE_MU_NO_CORE_STATUS))
    /* Core interrupt. */
    flags |= MU_CORE_FLAG(base->CSSR0);
#endif /* FSL_FEATURE_MU_NO_CORE_STATUS */

    return flags;
}

/*!
 * brief Triggers interrupts to the other core.
 *
 * This function triggers the specific interrupts to the other core. The interrupts
 * to trigger are passed in as bit mask. See \ref _mu_interrupt_trigger.
 * The MU should not trigger an interrupt to the other core when the previous interrupt
 * has not been processed by the other core. This function checks whether the
 * previous interrupts have been processed. If not, it returns an error.
 *
 * code
 * if (kStatus_Success != MU_TriggerInterrupts(base, kMU_GenInt0InterruptTrigger | kMU_GenInt2InterruptTrigger))
 * {
 *     Previous general purpose interrupt 0 or general purpose interrupt 2
 *     has not been processed by the other core.
 * }
 * endcode
 *
 * param base MU peripheral base address.
 * param interrupts Bit mask of the interrupts to trigger. See _mu_interrupt_trigger.
 * retval kStatus_Success    Interrupts have been triggered successfully.
 * retval kStatus_Fail       Previous interrupts have not been accepted.
 */
status_t MU_TriggerInterrupts(MU_Type *base, uint32_t interrupts)
{
    status_t status;
    uint32_t localInerrupts = MU_GET_GI_INTR(interrupts);
    uint32_t gcr            = base->GCR;

    /* Previous interrupt has not been accepted. */
    if (0U != (gcr & localInerrupts))
    {
        status = kStatus_Fail;
    }
    else
    {
        base->GCR = (gcr | localInerrupts);
        status    = kStatus_Success;
    }

    return status;
}

#if !(defined(FSL_FEATURE_MU_NO_NMI) && (0 != FSL_FEATURE_MU_NO_NMI))
/*
 * brief Triggers NMI to the other core.
 *
 * This function triggers the NMI to the other core.
 * The MU should not trigger NMI to the other core when the previous interrupt
 * has not been processed by the other core. This function checks whether the
 * previous interrupts have been processed. If not, it returns an error.
 *
 * param base MU peripheral base address.
 * retval kStatus_Success    Interrupts have been triggered successfully.
 * retval kStatus_Fail       Previous interrupts have not been accepted.
 */
status_t MU_TriggerNmi(MU_Type *base)
{
    status_t status;
    uint32_t ccr0 = base->CCR0;

    if (0U != (ccr0 & MU_CCR0_NMI_MASK))
    {
        status = kStatus_Fail;
    }
    else
    {
#if !(defined(FSL_FEATURE_MU_HAS_HR) && (FSL_FEATURE_MU_HAS_HR == 0))
        ccr0 &= ~MU_CCR0_HR_MASK;
#endif

        base->CCR0 = ccr0 | MU_CCR0_NMI_MASK;
        status     = kStatus_Success;
    }

    return status;
}
#endif /* FSL_FEATURE_MU_NO_NMI */

#if !(defined(FSL_FEATURE_MU_HAS_BOOT) && (0 == FSL_FEATURE_MU_HAS_BOOT))
/*!
 * brief Boots the other core.
 *
 * This function boots the other core with a boot configuration.
 *
 * param base MU peripheral base address.
 * param mode The other core boot mode.
 */
void MU_BootOtherCore(MU_Type *base, mu_core_boot_mode_t mode)
{
    uint32_t ccr0;

#if defined(FSL_FEATURE_MU_HAS_BOOT_BY_INSTANCEn)
    assert(FSL_FEATURE_MU_HAS_BOOT_BY_INSTANCEn(base) != 0);
#endif

    ccr0 = base->CCR0;

#if !(defined(FSL_FEATURE_MU_NO_NMI) && (0 != FSL_FEATURE_MU_NO_NMI))
    ccr0 &= ~MU_CCR0_NMI_MASK;
#endif

#if !(defined(FSL_FEATURE_MU_HAS_HR) && (0 == FSL_FEATURE_MU_HAS_HR))
    /* Don't need to check whether the instance support it, always clear it. */
    ccr0 &= ~MU_CCR0_HR_MASK;
#endif

#if !(defined(FSL_FEATURE_MU_HAS_RSTH) && (0 == FSL_FEATURE_MU_HAS_RSTH))
    /* Don't need to check whether the MU instance support RSTH, always clear the bit. */
    ccr0 &= ~MU_CCR0_RSTH_MASK;
#endif

    ccr0 = (ccr0 & ~MU_CCR0_BOOT_MASK) | MU_CCR0_BOOT(mode);

    base->CCR0 = ccr0;
}
#endif /* FSL_FEATURE_MU_HAS_BOOT */

#if !(defined(FSL_FEATURE_MU_HAS_RSTH) && (0 == FSL_FEATURE_MU_HAS_RSTH))
/*
 * brief Holds the other core reset.
 *
 * This function causes the other core to be held in reset following any reset event.
 *
 * param base MU peripheral base address.
 */
void MU_HoldOtherCoreReset(MU_Type *base)
{
    uint32_t ccr0;

#if defined(FSL_FEATURE_MU_HAS_RSTH_BY_INSTANCEn)
    /* The MU instance must support the feature. */
    assert(FSL_FEATURE_MU_HAS_RSTH_BY_INSTANCEn(base) != 0);
#endif

    ccr0 = base->CCR0;

#if !(defined(FSL_FEATURE_MU_NO_NMI) && (0 != FSL_FEATURE_MU_NO_NMI))
    ccr0 &= ~MU_CCR0_NMI_MASK;
#endif

    ccr0 = (ccr0 & ~(MU_CCR0_HR_MASK)) | MU_CCR0_RSTH_MASK;

    base->CCR0 = ccr0;
}
#endif /* FSL_FEATURE_MU_HAS_RSTH */

#if !(defined(FSL_FEATURE_MU_HAS_HR) && (FSL_FEATURE_MU_HAS_HR == 0))
/*!
 * brief Hardware reset the other core.
 *
 * This function resets the other core, the other core could mask the
 * hardware reset by calling ref MU_MaskHardwareReset. The hardware reset
 * mask feature is only available for some platforms.
 * This function could be used together with MU_BootOtherCore to control the
 * other core reset workflow.
 *
 * Example 1: Reset the other core, and no hold reset
 * code
 * MU_HardwareResetOtherCore(MU_A, true, false, bootMode);
 * endcode
 * In this example, the core at MU side B will reset with the specified boot mode.
 *
 * Example 2: Reset the other core and hold it, then boot the other core later.
 * code
 *    Here the other core enters reset, and the reset is hold
 * MU_HardwareResetOtherCore(MU_A, true, true, modeDontCare);
 *    Current core boot the other core when necessary.
 * MU_BootOtherCore(MU_A, bootMode);
 * endcode
 *
 * param base MU peripheral base address.
 * param waitReset Wait the other core enters reset.
 *                    - true: Wait until the other core enters reset, if the other
 *                      core has masked the hardware reset, then this function will
 *                      be blocked.
 *                    - false: Don't wait the reset.
 * param holdReset Hold the other core reset or not.
 *                    - true: Hold the other core in reset, this function returns
 *                      directly when the other core enters reset.
 *                    - false: Don't hold the other core in reset, this function
 *                      waits until the other core out of reset.
 * param bootMode Boot mode of the other core, if p holdReset is true, this
 *                 parameter is useless.
 */
void MU_HardwareResetOtherCore(MU_Type *base, bool waitReset, bool holdReset, mu_core_boot_mode_t bootMode)
{
#if defined(FSL_FEATURE_MU_HAS_HR_BY_INSTANCEn)
    assert(FSL_FEATURE_MU_HAS_HR_BY_INSTANCEn(base) != 0);
#endif

#if (defined(FSL_FEATURE_MU_HAS_BOOT) && (0 == FSL_FEATURE_MU_HAS_BOOT))
    assert(bootMode == kMU_CoreBootModeDummy);
#endif

#if (defined(FSL_FEATURE_MU_HAS_RSTH) && (0 == FSL_FEATURE_MU_HAS_RSTH))
    assert(holdReset == false);
#endif

#if defined(FSL_FEATURE_MU_HAS_RSTH_BY_INSTANCEn)
    if (FSL_FEATURE_MU_HAS_RSTH_BY_INSTANCEn(base) == 0)
    {
        assert(holdReset == false);
    }
#endif

#if (defined(FSL_FEATURE_MU_NO_CORE_STATUS) && (0 != FSL_FEATURE_MU_NO_CORE_STATUS))
    assert(waitReset == false);
#endif

    uint32_t ccr0 = base->CCR0;

    ccr0 &= ~MU_CCR0_HR_MASK;

#if !(defined(FSL_FEATURE_MU_NO_NMI) && (0 != FSL_FEATURE_MU_NO_NMI))
    ccr0 &= ~MU_CCR0_NMI_MASK;
#endif /* FSL_FEATURE_MU_NO_NMI */

#if !(defined(FSL_FEATURE_MU_HAS_BOOT) && (0 == FSL_FEATURE_MU_HAS_BOOT))
#if defined(FSL_FEATURE_MU_HAS_BOOT_BY_INSTANCEn)
    if (FSL_FEATURE_MU_HAS_BOOT_BY_INSTANCEn(base) != 0)
#endif
    {
        ccr0 &= ~MU_CCR0_BOOT_MASK;
        ccr0 |= MU_CCR0_BOOT(bootMode);
    }
#endif /* FSL_FEATURE_MU_HAS_BOOT */

#if !(defined(FSL_FEATURE_MU_HAS_RSTH) && (0 == FSL_FEATURE_MU_HAS_RSTH))
    ccr0 &= ~MU_CCR0_RSTH_MASK;
    /* Don't need check whether the instance support hold reset, it is already
     * checked at the begining of this function.
     */
    if (holdReset)
    {
        ccr0 |= MU_CCR0_RSTH_MASK;
    }
#endif /* FSL_FEATURE_MU_HAS_RSTH */

#if !(defined(FSL_FEATURE_MU_NO_CORE_STATUS) && (0 != FSL_FEATURE_MU_NO_CORE_STATUS))
#if !(defined(FSL_FEATURE_MU_HAS_RESET_ASSERT_INT) && (FSL_FEATURE_MU_HAS_RESET_ASSERT_INT == 0))
    /* Clean the reset assert pending flag. */
    base->CSSR0 = MU_CSSR0_RAIP_MASK;
#endif
#endif /* FSL_FEATURE_MU_NO_CORE_STATUS */

    /* Set CCR0[HR] to trigger hardware reset. */
    base->CCR0 = ccr0 | MU_CCR0_HR_MASK;

    /* If wait the other core enters reset. */
    if (waitReset)
    {
#if !(defined(FSL_FEATURE_MU_NO_CORE_STATUS) && (0 != FSL_FEATURE_MU_NO_CORE_STATUS))
#if !(defined(FSL_FEATURE_MU_HAS_RESET_ASSERT_INT) && (FSL_FEATURE_MU_HAS_RESET_ASSERT_INT == 0))
        /* Wait for the other core go to reset. */
        while (0U == (base->CSSR0 & MU_CSSR0_RAIP_MASK))
        {
            ; /* Intentional empty while*/
        }
#endif /* FSL_FEATURE_MU_HAS_RESET_ASSERT_INT */
#endif /* FSL_FEATURE_MU_NO_CORE_STATUS */

#if !(defined(FSL_FEATURE_MU_HAS_RSTH) && (0 == FSL_FEATURE_MU_HAS_RSTH))
        if (!holdReset)
        {
            /* Clear CCR[HR]. */
            base->CCR0 = ccr0;
        }
#endif /* FSL_FEATURE_MU_HAS_RSTH */
    }
}
#endif /* FSL_FEATURE_MU_HAS_HR */
