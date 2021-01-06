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
#include "board.h"
#include "fsl_common.h"
#include "fsl_slcd.h"
#include "slcd_engine.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_SLCD_DUTY_CYCLE          kSLCD_1Div4DutyCycle
#define APP_SLCD_LOW_PIN_ENABLED     0x0d10c000U /* LCD_P27/26/24/20 -> b27/26/24/20 = 1. */
#define APP_SLCD_HIGH_PIN_ENABLED    0x18001d00U /* LCD_P44/43/42/40 -> b12/11/10/8 = 1. */
#define APP_SLCD_BACK_PANEL_LOW_PIN  0x0000c000U /* LCD_P15/P14 -> b15/b14 = 1. */
#define APP_SLCD_BACK_PANEL_HIGH_PIN 0x18000000U /* LCD_P60/P59 -> b28/27 = 1. */

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
slcd_clock_config_t slcdClkConfig = {kSLCD_AlternateClk1, kSLCD_AltClkDivFactor256, kSLCD_ClkPrescaler01
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
                                     ,
                                     false
#endif
};

const uint8_t slcd_lcd_gpio_seg_pin[] = {
    20, /* SLCD P05 --- LCD_P20. */
    24, /* SLCD P06 --- LCD_P24. */
    26, /* SLCD P07 --- LCD_P26. */
    27, /* SLCD P08 --- LCD_P27. */
    40, /* SLCD P09 --- LCD_P40. */
    42, /* SLCD P10 --- LCD_P42. */
    43, /* SLCD P11 --- LCD_P43. */
    44, /* SLCD P12 --- LCD_P44. */
};
extern slcd_clock_config_t slcdClkConfig;
extern const uint8_t slcd_lcd_gpio_seg_pin[];
tSLCD_Engine slcdEngine;

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_SetSlcdBackPlanePhase(void)
{
    SLCD_SetBackPlanePhase(LCD, 59, kSLCD_PhaseAActivate); /* SLCD COM1 --- LCD_P59. */
    SLCD_SetBackPlanePhase(LCD, 60, kSLCD_PhaseBActivate); /* SLCD COM2 --- LCD_P60. */
    SLCD_SetBackPlanePhase(LCD, 14, kSLCD_PhaseCActivate); /* SLCD COM3 --- LCD_P14. */
    SLCD_SetBackPlanePhase(LCD, 15, kSLCD_PhaseDActivate); /* SLCD COM4 --- LCD_P15. */
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
    /* Enable the MCGIRCLK */
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;

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
