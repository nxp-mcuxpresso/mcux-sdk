/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MISC_H_
#define _FSL_MISC_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.misc"
#endif

#define BLK_CTRL_SAIMCLK_LOWBITMASK  (0x7U)
#define BLK_CTRL_SAIMCLK_HIGHBITMASK (0x3U)

typedef enum _blk_ctrl_saimclk
{
    kBLK_CTRL_SAI4MClk1Sel = BLK_CTRL_WAKEUPMIX_SAI4_MCLK_CTRL_SAI4_MCLK1_SEL_SHIFT,
    kBLK_CTRL_SAI4MClk2Sel = BLK_CTRL_WAKEUPMIX_SAI4_MCLK_CTRL_SAI4_MCLK2_SEL_SHIFT,
    kBLK_CTRL_SAI4MClk3Sel = BLK_CTRL_WAKEUPMIX_SAI4_MCLK_CTRL_SAI4_MCLK3_SEL_SHIFT,
    kBLK_CTRL_SAI2MClk3Sel = BLK_CTRL_WAKEUPMIX_SAI2_MCLK_CTRL_SAI2_MCLK3_SEL_SHIFT + 8,
    kBLK_CTRL_SAI3MClk3Sel = BLK_CTRL_WAKEUPMIX_SAI3_MCLK_CTRL_SAI3_MCLK3_SEL_SHIFT + 10,
} blk_ctrl_saimclk_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Sets BLK general configuration for SAI MCLK selection.
 *
 * @param base     The BLK CTRL base address.
 * @param mclk     The SAI MCLK.
 * @param clkSrc   The clock source. Take refer to register setting details for the clock source in RM.
 */
static inline void BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX_Type *base,
                                                  blk_ctrl_saimclk_t mclk,
                                                  uint8_t clkSrc)
{
    uint32_t temp;

    if (mclk > kBLK_CTRL_SAI2MClk3Sel)
    {
        temp                 = base->SAI3_MCLK_CTRL & ~(BLK_CTRL_SAIMCLK_HIGHBITMASK);
        base->SAI3_MCLK_CTRL = ((uint32_t)clkSrc & BLK_CTRL_SAIMCLK_HIGHBITMASK) | temp;
    }
    else if (mclk > kBLK_CTRL_SAI4MClk3Sel)
    {
        temp                 = base->SAI2_MCLK_CTRL & ~(BLK_CTRL_SAIMCLK_HIGHBITMASK);
        base->SAI2_MCLK_CTRL = ((uint32_t)clkSrc & BLK_CTRL_SAIMCLK_HIGHBITMASK) | temp;
    }
    else if (mclk > kBLK_CTRL_SAI4MClk2Sel)
    {
        temp                 = base->SAI4_MCLK_CTRL & ~((uint32_t)BLK_CTRL_SAIMCLK_HIGHBITMASK << (uint32_t)mclk);
        base->SAI4_MCLK_CTRL = (((uint32_t)clkSrc & BLK_CTRL_SAIMCLK_HIGHBITMASK) << (uint32_t)mclk) | temp;
    }
    else
    {
        temp                 = base->SAI4_MCLK_CTRL & ~((uint32_t)BLK_CTRL_SAIMCLK_LOWBITMASK << (uint32_t)mclk);
        base->SAI4_MCLK_CTRL = (((uint32_t)clkSrc & BLK_CTRL_SAIMCLK_LOWBITMASK) << (uint32_t)mclk) | temp;
    }
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _FSL_MISC_H_ */
