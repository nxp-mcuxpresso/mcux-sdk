/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "display_support.h"
#include "fsl_gpio.h"
#include "fsl_dc_fb_elcdif.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_HSW 41
#define DEMO_HFP 4
#define DEMO_HBP 8
#define DEMO_VSW 10
#define DEMO_VFP 4
#define DEMO_VBP 2
#define DEMO_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

/* Back light. */
#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
dc_fb_elcdif_handle_t s_dcFbElcdifHandle = {0}; /* The handle must be initialized to 0. */

const dc_fb_elcdif_config_t s_dcFbElcdifConfig = {
    .elcdif        = LCDIF,
    .width         = DEMO_PANEL_WIDTH,
    .height        = DEMO_PANEL_HEIGHT,
    .hsw           = DEMO_HSW,
    .hfp           = DEMO_HFP,
    .hbp           = DEMO_HBP,
    .vsw           = DEMO_VSW,
    .vfp           = DEMO_VFP,
    .vbp           = DEMO_VBP,
    .polarityFlags = DEMO_POL_FLAGS,
    .dataBus       = kELCDIF_DataBus16Bit,
};

const dc_fb_t g_dc = {
    .ops     = &g_dcFbOpsElcdif,
    .prvData = &s_dcFbElcdifHandle,
    .config  = &s_dcFbElcdifConfig,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize the LCD_DISP. */
void BOARD_InitLcdifPixelClock(void)
{
    uint32_t videoPllFreq;
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 60 = 9.2M.
     *
     * Here use the video pll (93MHz) as pixel clock source,
     * pixel clock = F_video_pll / (prediv + 1) / (div + 1) = 93 / 5 / 2 = 9.3M.
     */
    videoPllFreq = CLOCK_GetPllFreq(kCLOCK_PllVideo);

    if (videoPllFreq != 93000000)
    {
        PRINTF("Error: Invalid LCDIF pixel clock source.\r\n");
        while (1)
            ;
    }

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);

    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

static void BOARD_InitLcd(void)
{
    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        0,
        kGPIO_NoIntmode,
    };

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);

    /*
     * Reset the LCDIF, this is only used for flash target project debug.
     *
     * Hardware reset through debugger could not reset the ELCDIF, when reset
     * through debugger, the previous ELCDIF status retains, especially the
     * interrupt pending status. So we need to reset the ELCDIF before enabling
     * interrupt in NVIC. If the application only works with POR (Power on reset),
     * then this could be removed.
     */
    CLOCK_EnableClock(kCLOCK_Lcd);
    CLOCK_EnableClock(kCLOCK_LcdPixel);
    ELCDIF_Reset(LCDIF);
    NVIC_ClearPendingIRQ(LCDIF_IRQn);
    CLOCK_DisableClock(kCLOCK_LcdPixel);
    CLOCK_DisableClock(kCLOCK_Lcd);

    NVIC_SetPriority(LCDIF_IRQn, 3);
    EnableIRQ(LCDIF_IRQn);
}

void LCDIF_IRQHandler(void)
{
    DC_FB_ELCDIF_IRQHandler(&g_dc);
    __DSB();
}

status_t BOARD_PrepareDisplayController(void)
{
    BOARD_InitLcdifPixelClock();
    BOARD_InitLcd();

    return kStatus_Success;
}
