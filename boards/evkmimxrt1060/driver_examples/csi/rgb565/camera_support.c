/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "camera_support.h"
#include "fsl_gpio.h"
#include "fsl_csi.h"
#include "fsl_csi_camera_adapter.h"
#include "fsl_ov7725.h"
#include "fsl_mt9m114.h"
#include "fsl_iomuxc.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if (DEMO_CAMERA == DEMO_CAMERA_OV7725)
static void BOARD_PullCameraPowerDownPin(bool pullUp);
#endif
static void BOARD_PullCameraResetPin(bool pullUp);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Camera connect to CSI. */
static csi_resource_t csiResource = {
    .csiBase = CSI,
    .dataBus = kCSI_DataBus8Bit,
};

static csi_private_data_t csiPrivateData;

camera_receiver_handle_t cameraReceiver = {
    .resource    = &csiResource,
    .ops         = &csi_ops,
    .privateData = &csiPrivateData,
};

#if (DEMO_CAMERA == DEMO_CAMERA_OV7725)

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

/*******************************************************************************
 * Code
 ******************************************************************************/
extern void CSI_DriverIRQHandler(void);

void CSI_IRQHandler(void)
{
    CSI_DriverIRQHandler();
    __DSB();
}

static void BOARD_PullCameraResetPin(bool pullUp)
{
    /* Reset pin is connected to DCDC_3V3. */
    return;
}

#if (DEMO_CAMERA == DEMO_CAMERA_OV7725)
static void BOARD_PullCameraPowerDownPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_CAMERA_PWDN_GPIO, BOARD_CAMERA_PWDN_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_CAMERA_PWDN_GPIO, BOARD_CAMERA_PWDN_PIN, 0);
    }
}

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
    SDK_DelayAtLeastUs(5, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

static void BOARD_I2C_ReleaseBus(void)
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

    GPIO_PinInit(BOARD_CAMERA_I2C_SCL_GPIO, BOARD_CAMERA_I2C_SCL_PIN, &pin_config);
    GPIO_PinInit(BOARD_CAMERA_I2C_SDA_GPIO, BOARD_CAMERA_I2C_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(BOARD_CAMERA_I2C_SDA_GPIO, BOARD_CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(BOARD_CAMERA_I2C_SCL_GPIO, BOARD_CAMERA_I2C_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(BOARD_CAMERA_I2C_SDA_GPIO, BOARD_CAMERA_I2C_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(BOARD_CAMERA_I2C_SCL_GPIO, BOARD_CAMERA_I2C_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(BOARD_CAMERA_I2C_SCL_GPIO, BOARD_CAMERA_I2C_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_CAMERA_I2C_SDA_GPIO, BOARD_CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_CAMERA_I2C_SCL_GPIO, BOARD_CAMERA_I2C_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_CAMERA_I2C_SDA_GPIO, BOARD_CAMERA_I2C_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

#endif

void BOARD_EarlyPrepareCamera(void)
{
#if (DEMO_CAMERA != DEMO_CAMERA_OV7725)
    BOARD_I2C_ReleaseBus();
#endif
}

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

    GPIO_PinInit(BOARD_CAMERA_PWDN_GPIO, BOARD_CAMERA_PWDN_PIN, &pinConfig);
}
