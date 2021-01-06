/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SLCD_ENGINE_H_
#define _SLCD_ENGINE_H_

#include "slcd_panel.h"
#include <stdint.h>

/*
 * Change log:
 *
 * 1.0.2:
 *   - Fix MISRA 2012 issues.
 *
 * 1.0.1:
 *   - Move SLCD_ENGINE_PIN_VAL to panel driver.
 *
 * 1.0.0:
 *   - Initial version.
 */

typedef enum _lcd_set_type
{
    SLCD_Set_Num = 0U, /*!< Number setting - front pin setting with all phase. */
    SLCD_Set_Icon      /*!< Icon setting. - front pin setting with one phase. */
} lcd_set_type_t;

typedef void (*SLCD_SET_PIN_FUNC)(lcd_set_type_t type, uint32_t lcd_pin, uint8_t pin_val, int32_t on);

typedef struct
{
    SLCD_SET_PIN_FUNC slcd_set_pin_func;
} tSLCD_Engine;

void SLCD_Engine_Init(tSLCD_Engine *slcd_engine, SLCD_SET_PIN_FUNC pslcd_hw_handler);
int32_t SLCD_Engine_Show_Icon(tSLCD_Engine *slcd_engine, int32_t icon_pos, int32_t on);
int32_t SLCD_Engine_Show_Num(tSLCD_Engine *slcd_engine, int32_t num, int32_t pos, int32_t on);

#endif /* _SLCD_ENGINE_H_ */
