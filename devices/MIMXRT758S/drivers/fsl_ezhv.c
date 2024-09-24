/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fsl_power.h"
#include "fsl_ezhv.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ezhv"
#endif

#define EZHV_M_EXT_INT    (11UL)
/* shared ram space between arm and ezhv, size=256Bytes */
#define EZHV_ARM2EZHV_PARA_ADDR    (0x2410FF00U)

/*******************************************************************************
 * Variables
 ******************************************************************************/
static ezhv_callback_t s_ezhvCallback;
static void *s_ezhvCallbackParam;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void EZHV_Init(ezhv_copy_image_t *ezhvCopyImage)
{
    EZHV_InitWithoutFirmware();
    EZHV_InstallFirmware(ezhvCopyImage);
}

void EZHV_InitWithoutFirmware(void)
{
    CLOCK_EnableClock(kCLOCK_Ezhv);
    CLOCK_EnableClock(kCLOCK_AxbsEzh);

    POWER_DisablePD(kPDRUNCFG_APD_EZHV_TCM);
    POWER_DisablePD(kPDRUNCFG_PPD_EZHV_TCM);
    POWER_ApplyPD();
}

void EZHV_InstallFirmware(ezhv_copy_image_t *ezhvCopyImage)
{
    uint32_t dstAddr;
    uint32_t srcAddr;
    uint32_t size;

    assert(ezhvCopyImage != NULL);
    assert(ezhvCopyImage->srcAddr != 0U);
    assert(ezhvCopyImage->destAddr != 0U);
    assert(ezhvCopyImage->size != 0U);

    dstAddr = ezhvCopyImage->destAddr;
    srcAddr = ezhvCopyImage->srcAddr;
    size = ezhvCopyImage->size;

    memcpy((void*)(uint32_t*)dstAddr, (const void*)(uint32_t*)srcAddr, size);
}

void EZHV_Boot(uint32_t bootAddr)
{
    SYSCON4->EZHV_RSTBASE = bootAddr >> 2;
    SYSCON4->EZHV_RSTMTVEC = bootAddr;
    SYSCON4->EZHV_VOFFSET_T = EZHV_M_EXT_INT;
    /* reset to start ezhv */
    RESET_PeripheralReset(kEZHV_RST_SHIFT_RSTn);
}

void EZHV_SetPara(ezhv_param_t *para)
{
    assert(para != NULL);
    memcpy((void*)EZHV_ARM2EZHV_PARA_ADDR, para, sizeof(ezhv_param_t));
}

uint32_t *EZHV_GetParaAddr(void)
{
    return (uint32_t *)EZHV_ARM2EZHV_PARA_ADDR;
}

void EZHV_WakeupEzhv(arm2ezhv_intctl_t arm2ezhvInt)
{
    SYSCON4->ARM2EZHV_INT_CTRL = arm2ezhvInt;
}

void EZHV_Deinit(void)
{
    CLOCK_DisableClock(kCLOCK_Ezhv);
    CLOCK_DisableClock(kCLOCK_AxbsEzh);

    POWER_EnablePD(kPDRUNCFG_APD_EZHV_TCM);
    POWER_EnablePD(kPDRUNCFG_PPD_EZHV_TCM);
    POWER_ApplyPD();
}

void EZHV_InstallCallback(ezhv_callback_t callback, void *param)
{
    s_ezhvCallback       = callback;
    s_ezhvCallbackParam  = param;
}

void EZHV_HandleIRQ(void)
{
    if (NULL != s_ezhvCallback)
    {
        s_ezhvCallback(s_ezhvCallbackParam);
    }
}

void EZHV_DriverIRQHandler(void)
{
    EZHV_HandleIRQ();
}
