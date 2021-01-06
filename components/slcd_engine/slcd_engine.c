/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "slcd_engine.h"
#include <stdio.h>
#include <stdint.h>

int32_t SLCD_Engine_Show_Num(tSLCD_Engine *slcd_engine, int32_t num, int32_t pos, int32_t on)
{
    int32_t slcd_pin = 0, pin_val = 0;
    const uint16_t **ppSLCD_NumPos   = NULL;
    const uint16_t *pSLCD_NumPosNVal = NULL;

    if ((pos < 0) || (pos >= (int32_t)NUM_POSEND))
    {
        return -1;
    }
    ppSLCD_NumPos = SLCD_NumPos[pos];
    /* A number is comprised of several bytes' value */
    for (pSLCD_NumPosNVal = ppSLCD_NumPos[num]; *pSLCD_NumPosNVal != 0U; pSLCD_NumPosNVal++)
    {
        slcd_pin = (int32_t)(uint16_t)(*pSLCD_NumPosNVal >> 8);
        pin_val  = (int32_t)(uint16_t)(*pSLCD_NumPosNVal & 0xffU);
        slcd_engine->slcd_set_pin_func(SLCD_Set_Num, slcd_pin, pin_val, on);
    }

    return 0;
}

int32_t SLCD_Engine_Show_Icon(tSLCD_Engine *slcd_engine, int32_t icon_pos, int32_t on)
{
    int32_t slcd_pin = 0;
    int32_t pin_val  = 0;
    uint16_t pos_val = 0U;

    if ((icon_pos < 0) || (icon_pos >= (int32_t)ICON_END))
    {
        return -1;
    }
    pos_val  = SLCD_Icon[icon_pos];
    slcd_pin = (int32_t)(uint16_t)(pos_val >> 8);
    pin_val  = (int32_t)(uint16_t)(pos_val & 0xffU);
    slcd_engine->slcd_set_pin_func(SLCD_Set_Icon, slcd_pin, pin_val, on);

    return 0;
}

void SLCD_Engine_Init(tSLCD_Engine *slcd_engine, SLCD_SET_PIN_FUNC pslcd_hw_handler)
{
    slcd_engine->slcd_set_pin_func = pslcd_hw_handler;
}
