/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "fsl_mu.h"
#include "sm_platform.h"

static MU_Type *const s_muBases[] = MU_BASE_PTRS;
static IRQn_Type const s_muIrqs[] = MU_IRQS;

/*******************************************************************************
 * Definition
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initialize channel and MU interface for communication with SM.
 */
void SM_Platform_Init(void)
{
    MU_Type *base = s_muBases[SM_PLATFORM_MU_INST];
    IRQn_Type irq = s_muIrqs[SM_PLATFORM_MU_INST];

    /* Configure SMT */
    SMT_ChannelConfig(SM_PLATFORM_A2P, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_A2P, SM_PLATFORM_SMA_ADDR);
    SMT_ChannelConfig(SM_PLATFORM_NOTIFY, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_NOTIFY, SM_PLATFORM_SMA_ADDR);
    SMT_ChannelConfig(SM_PLATFORM_PRIORITY, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_PRIORITY, SM_PLATFORM_SMA_ADDR);

    /* Configure MU */
    MU_Init(base);
    EnableIRQ(irq);
    MU_EnableInterrupts(base, kMU_GenInt1InterruptEnable);
    MU_EnableInterrupts(base, kMU_GenInt2InterruptEnable);

    /* Enable system notifications */
    SCMI_SystemPowerStateNotify(SM_PLATFORM_A2P, SCMI_SYS_NOTIFY_ENABLE(1U));
}

/*!
 * @brief Deinitialize MU interface.
 */
void SM_Platform_Deinit(void)
{
}

/*!
 * @brief SM Platform Handler.
 */
void SM_Platform_Handler(void)
{
    MU_Type *base = s_muBases[SM_PLATFORM_MU_INST];
    uint32_t flags;

    /* Get interrupt status flags */
    flags = MU_GetStatusFlags(base);

    /* Clear interrupts */
    MU_ClearStatusFlags(base, flags);

    /* Notification pending? */
    if (flags & kMU_GenInt1Flag)
    {
        uint32_t protocolId, messageId;

        /* Get pending info */
        if (SCMI_P2aPending(SM_PLATFORM_NOTIFY, &protocolId, &messageId) == SCMI_ERR_SUCCESS)
        {
            /* System event? */
            if (protocolId == SCMI_PROTOCOL_SYS)
            {
                uint32_t notifyFlags, systemState;

                if (SCMI_SystemPowerStateNotifier(SM_PLATFORM_NOTIFY, NULL, &notifyFlags, &systemState, NULL) ==
                    SCMI_ERR_SUCCESS)
                {
                    bool graceful = (SCMI_SYS_NOTIFIER_GRACEFUL(notifyFlags) != 0U);

                    PRINTF("\nSCMI system notification: graceful=%u, state=0x%08X\n", graceful, systemState);

                    if (graceful)
                    {
                        switch (systemState)
                        {
                            case SCMI_SYS_STATE_FULL_SHUTDOWN:
                            case SCMI_SYS_STATE_SHUTDOWN:
                                PRINTF("shutdown\r\n");
                                break;
                            case SCMI_SYS_STATE_FULL_RESET:
                            case SCMI_SYS_STATE_COLD_RESET:
                            case SCMI_SYS_STATE_WARM_RESET:
                                PRINTF("reset");
                                break;
                            case SCMI_SYS_STATE_FULL_SUSPEND:
                            case SCMI_SYS_STATE_SUSPEND:
                                PRINTF("suspend");
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            else if (protocolId == SCMI_PROTOCOL_LMM)
            {
                uint32_t notifyFlags, eventLm;

                if (SCMI_LmmEvent(SM_PLATFORM_NOTIFY, NULL, &eventLm, &notifyFlags) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI LMM notification: LM %u, flags=0x%08X\n", eventLm, notifyFlags);
                }
            }
            else if (protocolId == SCMI_PROTOCOL_BBM)
            {
                if (messageId == SCMI_MSG_BBM_RTC_EVENT)
                {
                    uint32_t notifyFlags;

                    if (SCMI_BbmRtcEvent(SM_PLATFORM_NOTIFY, &notifyFlags) == SCMI_ERR_SUCCESS)
                    {
                        PRINTF("\nSCMI BBM RTC notification: flags=0x%08X\n", flags);
                    }
                }
                else
                {
                    uint32_t notifyFlags;

                    if (SCMI_BbmButtonEvent(SM_PLATFORM_NOTIFY, &notifyFlags) == SCMI_ERR_SUCCESS)
                    {
                        PRINTF("\nSCMI BBM button notification: flags=0x%08X\n", flags);
                    }
                }
            }
            else if (protocolId == SCMI_PROTOCOL_SENSOR)
            {
                uint32_t sensorId, desc;

                if (SCMI_SensorTripPointEvent(SM_PLATFORM_NOTIFY, NULL, &sensorId, &desc) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI sensor notification: sensor=%u, desc=0x%08X\n", sensorId, desc);
                }
            }
            else
            {
                PRINTF("\nSCMI unknown notification: 0x%X, 0x%X\n", protocolId, messageId);
            }
        }
    }

    /* Priority notification pending? */
    if (flags & kMU_GenInt2Flag)
    {
        uint32_t protocolId, messageId;

        /* Get pending info */
        if (SCMI_P2aPending(SM_PLATFORM_PRIORITY, &protocolId, &messageId) == SCMI_ERR_SUCCESS)
        {
            if (messageId == SCMI_MSG_FUSA_FEENV_STATE_EVENT)
            {
                uint32_t state, mSel;

                if (SCMI_FusaFeenvStateEvent(SM_PLATFORM_PRIORITY, &state, &mSel) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa F-EENV notification: state=%u, mSel=%u\r\n", state, mSel);
                }
            }
            else if (messageId == SCMI_MSG_FUSA_SEENV_STATE_REQ_EVENT)
            {
                uint32_t cookie;

                if (SCMI_FusaSeenvStateReqEvent(SM_PLATFORM_PRIORITY, &cookie) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa S-EENV notification: cookie=%u\r\n", cookie);
                }
            }
            else
            {
                uint32_t faultId, flag;

                if (SCMI_FusaFaultEvent(SM_PLATFORM_PRIORITY, &faultId, &flag) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa fault notification: faultId=%u, flags=%u\r\n", faultId, flag);

                    if (SCMI_FUSA_FAULT_FLAG_STATE(flag) != 0U)
                    {
                        SCMI_FusaFaultSet(SM_PLATFORM_A2P, faultId, SCMI_FUSA_FAULT_SET_STATE(0U));
                    }
                }
            }
        }
    }
}

/*!
 * @brief MU_A IRQ Handler
 */
void SM_platform_MU_IRQHandler(void *data)
{
    SM_Platform_Handler();
}
