/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_format.h"

/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/
static uint8_t s_convertedString[CONVERT_STRING_LENGTH];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*Convert a uint32 to string*/
uint8_t *FORMAT_Dec2Str(uint32_t num)
{
    uint8_t i;

    s_convertedString[CONVERT_STRING_LENGTH - 1U] = (uint8_t)'\0';

    i = CONVERT_STRING_LENGTH - 2u;

    if (0U == num)
    {
        s_convertedString[i] = (uint8_t)'0';
    }
    else
    {
        while (0U != num)
        {
            s_convertedString[i] = ((uint8_t)'0' + (uint8_t)(num % 10u));
            num                  = num / 10u;
            i--;
        }
        i++;
    }
    return &s_convertedString[i];
}

/*Convert a hex array to string*/
uint8_t *FORMAT_Hex2Ascii(uint8_t hex)
{
    s_convertedString[0] = (((hex >> 4U) & (uint8_t)0x0F) + ((((hex >> 4U) & (uint8_t)0x0F) <= 9U) ? '0' : ('A' - 10)));
    s_convertedString[1] = (((hex) & (uint8_t)0x0F) + ((((hex) & (uint8_t)0x0F) <= 9U) ? '0' : ('A' - 10)));
    s_convertedString[2] = '\0';

    return &s_convertedString[0];
}
