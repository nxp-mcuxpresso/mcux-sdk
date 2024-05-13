//*****************************************************************************
// boot_multicore_slave.c
//
// Provides functions to allow booting of secondary core in multicore system
//
//*****************************************************************************
//
// Copyright 2022-2023 NXP
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************
#if defined(__MULTICORE_MASTER_SLAVE_M7SLAVE)
/* Not relevant in case of SDK multicore projects that use another release scheme */
#if !defined(MULTICORE_APP) || (MULTICORE_APP == 0)

#include "fsl_device_registers.h"

extern uint8_t __vectors_start___core_m7slave;

#define BOOT_ADDRESS (uint32_t)(char *)&__vectors_start___core_m7slave

/* Overload the SystemInitHook() weak function */
void SystemInitHook(void)
{
    Prepare_CM7(BOOT_ADDRESS);
}

void boot_multicore_slave(void)
{
    volatile uint32_t bootAddress;

    /* Kicking off the CM7 core from the CM33 core */
    bootAddress = BOOT_ADDRESS;
    bootAddress &= BLK_CTRL_S_AONMIX_M7_CFG_INITVTOR_MASK;

    BLK_CTRL_S_AONMIX->M7_CFG = BLK_CTRL_S_AONMIX_M7_CFG_INITVTOR(bootAddress >> 7) | BLK_CTRL_S_AONMIX_M7_CFG_WAIT(1);
    SRC_GENERAL_REG->SCR |= SRC_GENERAL_SCR_BT_RELEASE_M7(1);

    /* Trigger EdgeLock*/
    uint32_t result1, result2;
    while ((MU_RT_S3MUA->TSR & MU_TSR_TE0_MASK) == 0)
        ; /*Wait TR empty*/
    MU_RT_S3MUA->TR[0] = 0x17d20106;
    while ((MU_RT_S3MUA->RSR & MU_RSR_RF0_MASK) == 0)
        ; /*Wait RR Full*/
    result1 = MU_RT_S3MUA->RR[0];
    while ((MU_RT_S3MUA->RSR & MU_RSR_RF1_MASK) == 0)
        ; /*Wait RR Full*/
    result2 = MU_RT_S3MUA->RR[1];
    if (!(result1 == 0xE1D20206 && result2 == 0xD6))
        while (1)
            ;

    /* De-assert Wait */
    BLK_CTRL_S_AONMIX->M7_CFG =
        (BLK_CTRL_S_AONMIX->M7_CFG & (~BLK_CTRL_S_AONMIX_M7_CFG_WAIT_MASK)) | BLK_CTRL_S_AONMIX_M7_CFG_WAIT(0);
}
#endif // !defined(MULTICORE_APP) || (MULTICORE_APP == 0)
#endif // defined (__MULTICORE_MASTER_SLAVE_M7SLAVE)
