/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_irqsteer_rev2.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.irqsteer"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t IRQSTEER_GetMasterIrqCount(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    if (!(FSL_FEATURE_IRQSTEER_IRQ_NUM % 64)) {
        return 64;
    } else {
        if (intMasterIndex == 0) {
            return 32;
	} else {
            return 64;
	}
    }
}

IRQn_Type IRQSTEER_GetMasterNextInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    uint32_t bitOffset, regIndex, chanStatus, sliceNum;
    int i, j;

    sliceNum = IRQSTEER_GetMasterIrqCount(base, intMasterIndex) / 32 - 1;

    for (i = 0; i <= sliceNum; i++) {
        bitOffset = 0;

        /* compute the index of the register to be queried */
        regIndex = FSL_FEATURE_IRQSTEER_CHN_MASK_COUNT - 1 - intMasterIndex * 2 + i;

        /* get register's value */
        chanStatus = base->CHN_STATUS[regIndex];

        for (j = 0; j < IRQSTEER_INT_SRC_REG_WIDTH; j++) {
            if (chanStatus & 1U) {
                return IRQSTEER_INT_SRC_NUM(regIndex, bitOffset);
            }

            bitOffset++;
            chanStatus = chanStatus >> 1U;
	}
    }

    return NotAvail_IRQn;
}
