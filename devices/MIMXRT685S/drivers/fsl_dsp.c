/*
 * Copyright 2019-2020, NXP
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
    if ((SYSCTL0->PDRUNCFG1 & (SYSCTL0_PDRUNCFG1_DSPCACHE_REGF_APD_MASK | SYSCTL0_PDRUNCFG1_DSPCACHE_REGF_PPD_MASK |
                               SYSCTL0_PDRUNCFG1_DSPTCM_REGF_APD_MASK | SYSCTL0_PDRUNCFG1_DSPTCM_REGF_PPD_MASK)) != 0U)
    {
        /* Not powered on. */
        POWER_DisablePD(kPDRUNCFG_APD_DSP_TCM_REGF);
        POWER_DisablePD(kPDRUNCFG_PPD_DSP_TCM_REGF);
        POWER_DisablePD(kPDRUNCFG_APD_DSP_CACHE_REGF);
        POWER_DisablePD(kPDRUNCFG_PPD_DSP_CACHE_REGF);
        POWER_ApplyPD();

        RESET_PeripheralReset(kDSP_RST_SHIFT_RSTn);
    }
    else if ((RSTCTL0->PRSTCTL0 & RSTCTL0_PRSTCTL0_HIFI_DSP_MASK) != 0U)
    {
        /* Powered on but not reset. */
        RESET_ClearPeripheralReset(kDSP_RST_SHIFT_RSTn);
    }
    else
    {
        /* Already powered on and reset, do nothing. */
    }
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

    POWER_EnablePD(kPDRUNCFG_APD_DSP_TCM_REGF);
    POWER_EnablePD(kPDRUNCFG_PPD_DSP_TCM_REGF);
    POWER_EnablePD(kPDRUNCFG_APD_DSP_CACHE_REGF);
    POWER_EnablePD(kPDRUNCFG_PPD_DSP_CACHE_REGF);
    POWER_ApplyPD();
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
