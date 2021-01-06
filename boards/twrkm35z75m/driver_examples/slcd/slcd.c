/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_slcd.h"
#include "slcd_engine.h"
#include "fsl_debug_console.h"

#include "fsl_device_registers.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_SLCD_DUTY_CYCLE          kSLCD_1Div8DutyCycle
#define APP_SLCD_LOW_PIN_ENABLED     0xF7D86000U /* LCD_P31/P30/P29/P28/P26/P25/P24/P23/P22/P20/P19/P14/P13. */
#define APP_SLCD_HIGH_PIN_ENABLED    0x0F04387FU /* LCD_P59/P58/P57/P56/P50/P45/P44/P43/P38/P37/P36/P35/P34/P33/P32. */
#define APP_SLCD_BACK_PANEL_LOW_PIN  0x00586000U /* LCD_P22/20/19/14/13 --> b22/b20/b19/b14/b13 = 1. */
#define APP_SLCD_BACK_PANEL_HIGH_PIN 0x07000000U /* LCD_P58/57/56 --> b26/b25/b24 = 1. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_SetSlcdBackPlanePhase(void);

/*!
 * @brief SLCD time delay.
 * @param ms Milli-second
 */
static void SLCD_TimeDelay(uint32_t ms);

/* Demonstrate how to show number. */
static void SLCD_Show_Digital(void);

/* Demonstrate how to show icon. */
static void SLCD_Show_Icon(void);

/* Demonstrate the blink feature. */
static void SLCD_Blink(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
slcd_clock_config_t slcdClkConfig = {kSLCD_DefaultClk, kSLCD_AltClkDivFactor1, kSLCD_ClkPrescaler01
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
                                     ,
                                     false
#endif
};

const uint8_t slcd_lcd_gpio_seg_pin[] = {38, 36, 34, 32, 31, 29, 25, 23, 43, 37,
                                         35, 33, 50, 30, 45, 24, 26, 28, 44, 59};
extern slcd_clock_config_t slcdClkConfig;
extern const uint8_t slcd_lcd_gpio_seg_pin[];
tSLCD_Engine slcdEngine;

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_SetSlcdBackPlanePhase(void)
{
    SLCD_SetBackPlanePhase(LCD, 57, kSLCD_PhaseAActivate); /* SLCD_COM1 --- LCD_P57. */
    SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseBActivate); /* SLCD_COM2 --- LCD_P19. */
    SLCD_SetBackPlanePhase(LCD, 13, kSLCD_PhaseCActivate); /* SLCD_COM3 --- LCD_P13. */
    SLCD_SetBackPlanePhase(LCD, 58, kSLCD_PhaseDActivate); /* SLCD_COM4 --- LCD_P58. */
    SLCD_SetBackPlanePhase(LCD, 56, kSLCD_PhaseEActivate); /* SLCD_COM5 --- LCD_P56. */
    SLCD_SetBackPlanePhase(LCD, 22, kSLCD_PhaseFActivate); /* SLCD_COM6 --- LCD_P22. */
    SLCD_SetBackPlanePhase(LCD, 20, kSLCD_PhaseGActivate); /* SLCD_COM7 --- LCD_P20. */
    SLCD_SetBackPlanePhase(LCD, 14, kSLCD_PhaseHActivate); /* SLCD_COM8 --- LCD_P14. */
}

static void SLCD_SetLCDPin(lcd_set_type_t type, uint32_t lcd_pin, uint8_t pin_val, int32_t on)
{
    assert(lcd_pin > 0);

    uint8_t gpio_pin = 0;
    uint8_t bit_val  = 0;
    uint8_t i        = 0;

    /* lcd _pin starts from 1. */
    gpio_pin = slcd_lcd_gpio_seg_pin[lcd_pin - 1];

    if (type == SLCD_Set_Num)
    {
        SLCD_SetFrontPlaneSegments(LCD, gpio_pin, (on ? pin_val : 0));
    }
    else
    {
        for (i = 0; i < 8; ++i)
        {
            bit_val = (uint8_t)(pin_val >> i) & 0x1U;
            if (bit_val)
            {
                SLCD_SetFrontPlaneOnePhase(LCD, gpio_pin, (slcd_phase_index_t)i, on);
            }
        }
    }
}

static void SLCD_Show_Digital(void)
{
    uint8_t digital;
    int32_t position;

    PRINTF("\r\nShow digital numbers\r\n");

    for (digital = 0; digital < 10; digital++)
    {
        for (position = 0; position < NUM_POSEND; position++)
        {
            SLCD_Engine_Show_Num(&slcdEngine, digital, position, 1);
        }

        SLCD_TimeDelay(500);

        for (position = 0; position < NUM_POSEND; position++)
        {
            SLCD_Engine_Show_Num(&slcdEngine, digital, position, 0);
        }
    }

    PRINTF("\r\nShow digital numbers finished\r\n");
}

static void SLCD_Show_Icon(void)
{
    int32_t icon;

    PRINTF("\r\nTurn on and off the icons one by one\r\n");

    for (icon = 0; icon < ICON_END; icon++)
    {
        SLCD_Engine_Show_Icon(&slcdEngine, icon, 1);

        SLCD_TimeDelay(500);

        SLCD_Engine_Show_Icon(&slcdEngine, icon, 0);
    }

    PRINTF("\r\nShow icons finished\r\n");
}

static void SLCD_Blink(void)
{
    int32_t icon;

    for (icon = 0; icon < ICON_END; icon++)
    {
        SLCD_Engine_Show_Icon(&slcdEngine, icon, 1);
    }

    PRINTF("\r\nSLCD Displays All Segments.\r\n");
    SLCD_TimeDelay(2000);

    PRINTF("\r\nSLCD Starts Blink Mode.\r\n");

    /* Blink mode Display. */
    SLCD_StartBlinkMode(LCD, kSLCD_BlankDisplayBlink, kSLCD_BlinkRate01);
    SLCD_TimeDelay(4000);

    PRINTF("\r\nSLCD Stops Blink Mode.\r\n");
    /* Stops SLCD blink display mode. */
    SLCD_StopBlinkMode(LCD);
    SLCD_TimeDelay(2000);
}

static void SLCD_TimeDelay(uint32_t ms)
{
    SDK_DelayAtLeastUs(1000 * ms, SystemCoreClock);
}

int main(void)
{
    slcd_config_t config;

    /* Hardware initialize. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nSLCD Example Starts.\r\n");

    /* SLCD get default configure. */
    /*
     * config.displayMode = kSLCD_NormalMode;
     * config.powerSupply = kSLCD_InternalVll3UseChargePump;
     * config.voltageTrim = kSLCD_RegulatedVolatgeTrim08;
     * config.lowPowerBehavior = kSLCD_EnabledInWaitStop;
     * config.frameFreqIntEnable = false;
     * config.faultConfig = NULL;
     */
    SLCD_GetDefaultConfig(&config);

    /* Verify and Complete the configuration structure. */
    config.clkConfig          = &slcdClkConfig;
    config.loadAdjust         = kSLCD_HighLoadOrSlowestClkSrc;
    config.dutyCycle          = APP_SLCD_DUTY_CYCLE;
    config.slcdLowPinEnabled  = APP_SLCD_LOW_PIN_ENABLED;
    config.slcdHighPinEnabled = APP_SLCD_HIGH_PIN_ENABLED;
    config.backPlaneLowPin    = APP_SLCD_BACK_PANEL_LOW_PIN;
    config.backPlaneHighPin   = APP_SLCD_BACK_PANEL_HIGH_PIN;

    config.faultConfig = NULL;
    /* SLCD Initialize. */
    SLCD_Init(LCD, &config);

    BOARD_SetSlcdBackPlanePhase();

    memset(&slcdEngine, 0, sizeof(tSLCD_Engine));

    SLCD_Engine_Init(&slcdEngine, SLCD_SetLCDPin);

    /* Starts SLCD display. */
    SLCD_StartDisplay(LCD);

    SLCD_Show_Digital();

    SLCD_Show_Icon();

    SLCD_Blink();

    PRINTF("\r\nSLCD Stops Display.\r\n");
    /* Stops SLCD display. */
    SLCD_StopDisplay(LCD);

    PRINTF("\r\nSLCD Example Ends.\r\n");

    while (1)
    {
    }
}
