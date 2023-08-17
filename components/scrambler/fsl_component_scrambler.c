/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_component_scrambler.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

void SCRAMBLER_Whiten(whitener_config_t *whitenerConfig, uint8_t *pBuff, uint32_t buffLength)
{
    uint32_t initialState = ((uint32_t)whitenerConfig->whitenInitValue << (32U - whitenerConfig->whitenSize));
    uint32_t polyValue    = ((uint32_t)whitenerConfig->whitenPolyValue << (32U - whitenerConfig->whitenSize));
    uint32_t currentValue = 0U;

    for (uint32_t i = 0U; i < buffLength; i++)
    {
        currentValue = pBuff[i];

        if (whitenerConfig->type == kSCRAMBLER_GaloisPolyType)
        {
            for (uint8_t j = 0; j < 8U; j++)
            {
                if (0U != (initialState & 0x80000000U))
                {
                    initialState = (initialState << 1U);
                    initialState ^= polyValue;

                    if (whitenerConfig->whitenRefIn == kSCRAMBLER_WhitenRefInput)
                    {
                        currentValue = currentValue ^ (0x80UL >> j);
                    }
                    else
                    {
                        currentValue = currentValue ^ (0x1UL << j);
                    }
                }
                else
                {
                    initialState = initialState << 1U;
                }
            }
        }

        pBuff[i] = (uint8_t)currentValue;
    }
}
