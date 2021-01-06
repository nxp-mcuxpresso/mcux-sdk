/*
 * Copyright  2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_elcdif.h"
#include "fsl_camera.h"
#include "fsl_camera_device.h"
#include "fsl_csi.h"

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"

#include "fsl_gpio.h"
#include "fsl_ov7725.h"
#include "fsl_mt9m114.h"
#include "fsl_iomuxc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* LCD definition. */
#define DEMO_ELCDIF LCDIF

#define DEMO_LCD_HEIGHT 272
#define DEMO_LCD_WIDTH  480
#define DEMO_HSW        41
#define DEMO_HFP        4
#define DEMO_HBP        8
#define DEMO_VSW        10
#define DEMO_VFP        4
#define DEMO_VBP        2
#define DEMO_LCD_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

#define DEMO_LCDIF_DATA_BUS_WIDTH 16

/* Display. */
#define LCD_DISP_GPIO     GPIO1
#define LCD_DISP_GPIO_PIN 2
/* Back light. */
#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31

/* Camera definition. */
#define DEMO_CSI           CSI
#define DEMO_CAMERA_HEIGHT 272
#define DEMO_CAMERA_WIDTH  480

#define DEMO_CAMERA_OV7725  0
#define DEMO_CAMERA_MT9M114 1

#define DEMO_CAMERA_TYPE DEMO_CAMERA_MT9M114

/* Frame buffer data alignment. */
#define FRAME_BUFFER_ALIGN 64


#define DEMO_CSI_DMA_BUFFER_LINE 4

#define DEMO_WINDOW_ULX    (DEMO_CAMERA_WIDTH / 4)
#define DEMO_WINDOW_ULY    (DEMO_CAMERA_HEIGHT / 4)
#define DEMO_WINDOW_LRX    (DEMO_CAMERA_WIDTH * 3 / 4 - 1)
#define DEMO_WINDOW_LRY    (DEMO_CAMERA_HEIGHT * 3 / 4 - 1)
#define DEMO_WINDOW_HEIGHT (DEMO_WINDOW_LRY - DEMO_WINDOW_ULY + 1)
#define DEMO_WINDOW_WIDTH  (DEMO_WINDOW_LRX - DEMO_WINDOW_ULX + 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern camera_device_handle_t cameraDevice;

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t s_frameBuffer[DEMO_LCD_HEIGHT][DEMO_LCD_WIDTH], FRAME_BUFFER_ALIGN);

SDK_ALIGN(static uint16_t s_dmaBuffer[2][DEMO_CSI_DMA_BUFFER_LINE][DEMO_CAMERA_WIDTH], FRAME_BUFFER_ALIGN);

SDK_ALIGN(static uint8_t s_windowBuffer[DEMO_WINDOW_HEIGHT][DEMO_WINDOW_WIDTH], FRAME_BUFFER_ALIGN);

static volatile bool s_frameDone = false;

static csi_frag_handle_t s_csiHandle;

uint32_t lutData[ELCDIF_LUT_ENTRY_NUM];

/*******************************************************************************
 * Code
 ******************************************************************************/

extern void CSI_DriverIRQHandler(void);

void CSI_IRQHandler(void)
{
    CSI_DriverIRQHandler();
}

/* Initialize the LCD_DISP. */
void BOARD_InitLcd(void)
{
    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        0,
        kGPIO_NoIntmode,
    };

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

void BOARD_InitLcdifPixClock(void)
{
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 60 = 9.2M.
     * Here set the LCDIF pixel clock to 9.3M.
     */

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 31,
        .postDivider = 8,
        .numerator   = 0,
        .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

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

static void BOARD_PullCameraResetPin(bool pullUp)
{
    /* Reset pin is connected to DCDC_3V3. */
    return;
}

#if (DEMO_CAMERA_TYPE == DEMO_CAMERA_OV7725)
static void BOARD_PullCameraPowerDownPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(GPIO1, 4, 1);
    }
    else
    {
        GPIO_PinWrite(GPIO1, 4, 0);
    }
}

static ov7725_resource_t ov7725Resource = {
    .i2cSendFunc       = BOARD_Camera_I2C_SendSCCB,
    .i2cReceiveFunc    = BOARD_Camera_I2C_ReceiveSCCB,
    .pullResetPin      = BOARD_PullCameraResetPin,
    .pullPowerDownPin  = BOARD_PullCameraPowerDownPin,
    .inputClockFreq_Hz = 24000000,
};

camera_device_handle_t cameraDevice = {
    .resource = &ov7725Resource,
    .ops      = &ov7725_ops,
};
#else
/*
 * MT9M114 camera module has PWDN pin, but the pin is not
 * connected internally, MT9M114 does not have power down pin.
 * The reset pin is connected to high, so the module could
 * not be reseted, so at the begining, use GPIO to let camera
 * release the I2C bus.
 */
static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 0x200; i++)
    {
        __NOP();
    }
}

#define CAMERA_I2C_SCL_GPIO GPIO1
#define CAMERA_I2C_SCL_PIN  16
#define CAMERA_I2C_SDA_GPIO GPIO1
#define CAMERA_I2C_SDA_PIN  17

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i                          = 0;
    const gpio_pin_config_t pin_config = {
        .direction     = kGPIO_DigitalOutput,
        .outputLogic   = 1,
        .interruptMode = kGPIO_NoIntmode,
    };

    CLOCK_EnableClock(kCLOCK_Iomuxc);

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16, 0U);

    GPIO_PinInit(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, &pin_config);
    GPIO_PinInit(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

static mt9m114_resource_t mt9m114Resource = {
    .i2cSendFunc       = BOARD_Camera_I2C_Send,
    .i2cReceiveFunc    = BOARD_Camera_I2C_Receive,
    .pullResetPin      = BOARD_PullCameraResetPin,
    .inputClockFreq_Hz = 24000000,
};

camera_device_handle_t cameraDevice = {
    .resource = &mt9m114Resource,
    .ops      = &mt9m114_ops,
};
#endif

void BOARD_InitCameraResource(void)
{
    BOARD_Camera_I2C_Init();

    /* CSI MCLK select 24M. */
    /*
     * CSI clock source:
     *
     * 00 derive clock from osc_clk (24M)
     * 01 derive clock from PLL2 PFD2
     * 10 derive clock from pll3_120M
     * 11 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_CsiMux, 0);
    /*
     * CSI clock divider:
     *
     * 000 divide by 1
     * 001 divide by 2
     * 010 divide by 3
     * 011 divide by 4
     * 100 divide by 5
     * 101 divide by 6
     * 110 divide by 7
     * 111 divide by 8
     */
    CLOCK_SetDiv(kCLOCK_CsiDiv, 0);

    /*
     * For RT1050, there is not dedicate clock gate for CSI MCLK, it use CSI
     * clock gate.
     */

    /* Set the pins for CSI reset and power down. */
    gpio_pin_config_t pinConfig = {
        kGPIO_DigitalOutput,
        1,
        kGPIO_NoIntmode,
    };

    GPIO_PinInit(GPIO1, 4, &pinConfig);
}



uint32_t DEMO_MakeLutData(uint8_t r, uint8_t g, uint8_t b)
{
#if (DEMO_LCDIF_DATA_BUS_WIDTH == 16)
    /* 16 bit data bus. */
    return (((r >> 3)) << 11) | (((g >> 2)) << 5) | (((b >> 3)) << 0);
#elif (DEMO_LCDIF_DATA_BUS_WIDTH == 24)
    /* 24-bit data bus. */
    return (r << 16) | (g << 8) | (b << 0);
#else
#error Data bus not supported
#endif
}

void DEMO_FillLutData(void)
{
    uint32_t i;

    for (i = 0; i < ELCDIF_LUT_ENTRY_NUM; i++)
    {
        lutData[i] = DEMO_MakeLutData(i, i, i);
    }
}

void CSI_TransferCallBack(CSI_Type *base, csi_frag_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_CSI_FrameDone)
    {
        s_frameDone = true;
    }
}

void DEMO_InitLCD(void)
{
    elcdif_rgb_mode_config_t lcdConfig = {
        .panelWidth    = DEMO_LCD_WIDTH,
        .panelHeight   = DEMO_LCD_HEIGHT,
        .hsw           = DEMO_HSW,
        .hfp           = DEMO_HFP,
        .hbp           = DEMO_HBP,
        .vsw           = DEMO_VSW,
        .vfp           = DEMO_VFP,
        .vbp           = DEMO_VBP,
        .polarityFlags = DEMO_LCD_POL_FLAGS,
        .pixelFormat   = kELCDIF_PixelFormatRAW8,
        .dataBus       = kELCDIF_DataBus8Bit,
        .bufferAddr    = (uint32_t)s_frameBuffer,
    };

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

    ELCDIF_RgbModeInit(DEMO_ELCDIF, &lcdConfig);

    DEMO_FillLutData();

    /* Load the LUT data. */
    ELCDIF_UpdateLut(DEMO_ELCDIF, kELCDIF_Lut0, 0, lutData, ELCDIF_LUT_ENTRY_NUM);

    ELCDIF_EnableLut(DEMO_ELCDIF, true);

    ELCDIF_RgbModeStart(DEMO_ELCDIF);
}

void DEMO_InitCamera(void)
{
    const camera_config_t cameraConfig = {
        .pixelFormat                = kVIDEO_PixelFormatYUYV,
        .bytesPerPixel              = 2,
        .resolution                 = FSL_VIDEO_RESOLUTION(DEMO_CAMERA_WIDTH, DEMO_CAMERA_HEIGHT),
        .frameBufferLinePitch_Bytes = DEMO_CAMERA_WIDTH * 2,
        .interface                  = kCAMERA_InterfaceGatedClock,
        .controlFlags               = kCAMERA_HrefActiveHigh | kCAMERA_DataLatchOnRisingEdge | kCAMERA_VsyncActiveLow,
        .framePerSec                = 30,
    };

    csi_frag_config_t csiFragConfig = {
        .width               = DEMO_CAMERA_WIDTH,
        .height              = DEMO_CAMERA_HEIGHT,
        .polarityFlags       = kCSI_HsyncActiveHigh | kCSI_DataLatchOnRisingEdge | kCSI_VsyncActiveLow,
        .inputFormat         = kCSI_FragInputYUYV,
        .workMode            = kCSI_GatedClockMode,
        .dataBus             = kCSI_DataBus8Bit,
        .useExtVsync         = true,
        .dmaBufferAddr0      = (uint32_t)s_dmaBuffer[0],
        .dmaBufferAddr1      = (uint32_t)s_dmaBuffer[1],
        .dmaBufferLine       = DEMO_CSI_DMA_BUFFER_LINE,
        .isDmaBufferCachable = true,
    };

    CSI_FragModeInit(DEMO_CSI);

    CSI_FragModeCreateHandle(DEMO_CSI, &s_csiHandle, &csiFragConfig, CSI_TransferCallBack, NULL);

    if (kStatus_Success != CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig))
    {
        PRINTF("Camera init failed\r\n");
        while (1)
            ;
    }

    CAMERA_DEVICE_Start(&cameraDevice);
}

/*!
 * @brief Main function
 */
int main(void)
{
    csi_frag_window_t window = {
        .windowULX = DEMO_WINDOW_ULX,
        .windowULY = DEMO_WINDOW_ULY,
        .windowLRX = DEMO_WINDOW_LRX,
        .windowLRY = DEMO_WINDOW_LRY,
    };

    csi_frag_capture_config_t csiFragCaptureConfig = {
        .outputGrayScale = true,
        .buffer          = (uint32_t)s_windowBuffer,
        .window          = &window,
    };

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
#if (DEMO_CAMERA_TYPE != DEMO_CAMERA_OV7725)
    BOARD_I2C_ReleaseBus();
#endif
    BOARD_InitCSIPins();
    BOARD_InitLCDPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();
    BOARD_InitCameraResource();

    PRINTF("CSI fragment mode example start...\r\n");

    DEMO_InitLCD();

    DEMO_InitCamera();

    while (1)
    {
        PRINTF("Press any key to capture image.\r\n");

        GETCHAR();

        s_frameDone = false;

        CSI_FragModeTransferCaptureImage(DEMO_CSI, &s_csiHandle, &csiFragCaptureConfig);

        while (!s_frameDone)
        {
        }

        /* Copy the captured image to LCD buffer. */
        for (uint32_t y = 0; y < DEMO_WINDOW_HEIGHT; y++)
        {
            memcpy(&(s_frameBuffer[y + DEMO_WINDOW_ULY][DEMO_WINDOW_ULX]), &s_windowBuffer[y][0], DEMO_WINDOW_WIDTH);
        }
    }
}
