/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dsp.h"
#include "fsl_reset.h"
#include "fsl_common.h"
#include "fsl_power.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dsp"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(MIMXRT798S_cm33_core0_SERIES)
#define DSP_MEM_PD_MASKS                                                                           \
    (PMC_PDRUNCFG4_DSP_DCACHE_MASK | PMC_PDRUNCFG4_DSP_ICACHE_MASK | PMC_PDRUNCFG4_DSP_DTCM_MASK | \
     PMC_PDRUNCFG4_DSP_ITCM_MASK)
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initializing DSP core.
 *
 * Power up DSP TCM
 * Enable DSP clock
 * Reset DSP peripheral
 */
void DSP_Init(void)
{
#if defined(MIMXRT798S_cm33_core0_SERIES)
    /* Power on VDD2_DSP and HiFi4 RAM */
    if ((PMC0->PDRUNCFG4 & DSP_MEM_PD_MASKS) != 0U || (PMC0->PDRUNCFG5 & DSP_MEM_PD_MASKS) != 0U)
    {
        POWER_DisablePD(kPDRUNCFG_APD_DSP_DTCM);
        POWER_DisablePD(kPDRUNCFG_APD_DSP_ITCM);
        POWER_DisablePD(kPDRUNCFG_APD_DSP_DCACHE);
        POWER_DisablePD(kPDRUNCFG_APD_DSP_ICACHE);

        POWER_DisablePD(kPDRUNCFG_PPD_DSP_DTCM);
        POWER_DisablePD(kPDRUNCFG_PPD_DSP_ITCM);
        POWER_DisablePD(kPDRUNCFG_PPD_DSP_DCACHE);
        POWER_DisablePD(kPDRUNCFG_PPD_DSP_ICACHE);

        POWER_ApplyPD();

        RESET_PeripheralReset(kHIFI4_RST_SHIFT_RSTn);
        RESET_PeripheralReset(kHIFI4_DEBUG_RST_SHIFT_RSTn);
    }
    else if ((RSTCTL0->PRSTCTL5 & RSTCTL0_PRSTCTL5_HIFI4_MASK) != 0U) /* Already power up. */
    {
        RESET_ClearPeripheralReset(kHIFI4_RST_SHIFT_RSTn);
        RESET_ClearPeripheralReset(kHIFI4_DEBUG_RST_SHIFT_RSTn);
    }
    else
    {
        /* Already powered on and reset, do nothing. */
    }

    CLOCK_EnableClock(kCLOCK_Hifi4);
#elif defined(SLEEPCON1)
    RESET_ClearPeripheralReset(kHIFI1_DEBUG_RST_SHIFT_RSTn);
    RESET_ClearPeripheralReset(kHIFI1_RST_SHIFT_RSTn);
    CLOCK_EnableClock(kCLOCK_Hifi1);
#else
#error "Unsupported core!"
#endif
}

/*!
 * @brief Deinit DSP core.
 *
 * Power down DSP TCM
 * Disable DSP clock
 * Set DSP peripheral reset
 */
void DSP_Deinit(void)
{
    DSP_Stop();

#if defined(MIMXRT798S_cm33_core0_SERIES)
    CLOCK_DisableClock(kCLOCK_Hifi4);

    POWER_EnablePD(kPDRUNCFG_APD_DSP_DTCM);
    POWER_EnablePD(kPDRUNCFG_APD_DSP_ITCM);
    POWER_EnablePD(kPDRUNCFG_APD_DSP_DCACHE);
    POWER_EnablePD(kPDRUNCFG_APD_DSP_ICACHE);

    POWER_EnablePD(kPDRUNCFG_PPD_DSP_DTCM);
    POWER_EnablePD(kPDRUNCFG_PPD_DSP_ITCM);
    POWER_EnablePD(kPDRUNCFG_PPD_DSP_DCACHE);
    POWER_EnablePD(kPDRUNCFG_PPD_DSP_ICACHE);

    POWER_ApplyPD();
#elif defined(SLEEPCON1)
    CLOCK_DisableClock(kCLOCK_Hifi1);
#endif
}
/*!
 * @brief Copy DSP image to destination address.
 *
 * Copy DSP image from source address to destination address with given size.
 *
 * @param dspCopyImage Structure contains information for DSP copy image to destination address.
 */
void DSP_CopyImage(dsp_copy_image_t *dspCopyImage)
{
    assert(dspCopyImage != NULL);
    assert(dspCopyImage->srcAddr != NULL);
    assert(dspCopyImage->destAddr != NULL);

    uint32_t *srcAddr  = dspCopyImage->srcAddr;
    uint32_t *destAddr = dspCopyImage->destAddr;
    uint32_t size      = dspCopyImage->size;

    assert((size & 3U) == 0U);

    while (size > 0U)
    {
        *destAddr++ = *srcAddr++;
        size -= 4U;
    }
}
