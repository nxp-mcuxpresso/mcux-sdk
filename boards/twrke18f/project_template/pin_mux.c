/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: MKE18F512xxx16
package_id: MKE18F512VLL16
mcu_data: ksdk2_0
processor_version: 0.0.19
board: TWR-KE18F
pin_labels:
- {pin_num: '1', pin_signal: PTE16/FTM2_CH7/FXIO_D3/TRGMUX_OUT7, label: 'J20[6]'}
- {pin_num: '2', pin_signal: PTE15/FTM2_CH6/FXIO_D2/TRGMUX_OUT6, label: 'J20[5]'}
- {pin_num: '3', pin_signal: ADC2_SE1/PTD1/FTM0_CH3/LPSPI1_SIN/FTM2_CH1/FXIO_D1/TRGMUX_OUT2, label: 'J20[4]/J15[B11]/LPSPI1_SIN'}
- {pin_num: '4', pin_signal: ADC2_SE0/PTD0/FTM0_CH2/LPSPI1_SCK/FTM2_CH0/FXIO_D0/TRGMUX_OUT1, label: 'J15[B7]/J20[3]/LPSPI1_SCK'}
- {pin_num: '5', pin_signal: ADC2_SE13/PTE11/PWT_IN1/LPTMR0_ALT1/FTM2_CH5/FXIO_D5/TRGMUX_OUT5, label: 'J15[B34]/J20[8]/FTM2_CH5'}
- {pin_num: '6', pin_signal: ADC2_SE12/PTE10/CLKOUT/FTM2_CH4/FXIO_D4/TRGMUX_OUT4, label: 'J15[B25]/J20[7]/CLKOUT'}
- {pin_num: '8', pin_signal: PTE5/TCLK2/FTM2_QD_PHA/FTM2_CH3/CAN0_TX/FXIO_D7/EWM_IN, label: 'J6[2]/CAN0_TX', identifier: CAN0_TX}
- {pin_num: '9', pin_signal: PTE4/BUSOUT/FTM2_QD_PHB/FTM2_CH2/CAN0_RX/FXIO_D6/EWM_OUT_b, label: 'J7[2]/CAN0_RX', identifier: CAN0_RX}
- {pin_num: '15', pin_signal: EXTAL/PTB7/LPI2C0_SCL, label: 'J24[2]/EXTAL', identifier: EXTAL0}
- {pin_num: '16', pin_signal: XTAL/PTB6/LPI2C0_SDA, label: 'X2[1]/XTAL', identifier: XTAL0}
- {pin_num: '17', pin_signal: ACMP2_IN3/PTE14/FTM0_FLT1/FTM2_FLT1, label: TP4/IRRX, identifier: IRRX_CMP_IN}
- {pin_num: '18', pin_signal: PTE3/FTM0_FLT0/LPUART2_RTS/FTM2_FLT0/TRGMUX_IN6/ACMP2_OUT, label: 'J15[A41]/PTC6/LPUART1_RX', identifier: IRRX_CMP_OUT}
- {pin_num: '19', pin_signal: PTE12/FTM0_FLT3/LPUART2_TX, label: 'J15[B61]'}
- {pin_num: '20', pin_signal: PTD17/FTM0_FLT2/LPUART2_RX, label: 'J15[B62]'}
- {pin_num: '21', pin_signal: ACMP2_IN0/PTD16/FTM0_CH1, label: 'J15[B59]/D5[1]/TRI_RED', identifier: LED_RED2}
- {pin_num: '22', pin_signal: ACMP2_IN1/PTD15/FTM0_CH0, label: 'J15[B60]/D5[4]/TRI_GR', identifier: LED_GREEN2}
- {pin_num: '23', pin_signal: ACMP2_IN2/DAC0_OUT/PTE9/FTM0_CH7/LPUART2_CTS, label: 'J15[A32]/DAC0_OUT/PTE9_ELEV'}
- {pin_num: '26', pin_signal: ACMP0_IN3/PTE8/FTM0_CH6, label: 'J15[B56]'}
- {pin_num: '27', pin_signal: PTB5/FTM0_CH5/LPSPI0_PCS1/TRGMUX_IN0/ACMP1_OUT, label: 'J15[B57]/D5[3]/TRI_BL', identifier: LED_BLUE}
- {pin_num: '28', pin_signal: ACMP1_IN2/PTB4/FTM0_CH4/LPSPI0_SOUT/TRGMUX_IN1, label: 'J15[B58]'}
- {pin_num: '29', pin_signal: ADC0_SE11/ACMP0_IN4/EXTAL32/PTC3/FTM0_CH3/CAN0_TX, label: 'Y1[1]/EXTAL32', identifier: EXTAL32}
- {pin_num: '30', pin_signal: ADC0_SE10/ACMP0_IN5/XTAL32/PTC2/FTM0_CH2/CAN0_RX, label: 'Y1[2]/XTAL32', identifier: XTAL32}
- {pin_num: '31', pin_signal: PTD7/LPUART2_TX/FTM2_FLT3, label: 'J15[A10]'}
- {pin_num: '32', pin_signal: PTD6/LPUART2_RX/FTM2_FLT2, label: 'J15[A11]/SW3', identifier: SW3}
- {pin_num: '33', pin_signal: PTD5/FTM2_CH3/LPTMR0_ALT2/FTM2_FLT1/PWT_IN2/TRGMUX_IN7, label: 'J15[B23]'}
- {pin_num: '34', pin_signal: PTD12/FTM2_CH2/LPI2C1_HREQ/LPUART2_RTS, label: 'J15[B22]'}
- {pin_num: '35', pin_signal: PTD11/FTM2_CH1/FTM2_QD_PHA/LPUART2_CTS, label: 'J15[A34]/FTM2_QD_PHA'}
- {pin_num: '36', pin_signal: PTD10/FTM2_CH0/FTM2_QD_PHB, label: 'J15[A33]/FTM2_QD_PHB'}
- {pin_num: '39', pin_signal: ADC0_SE9/ACMP1_IN3/PTC1/FTM0_CH1/FTM1_CH7, label: 'J15[B33]/FTM1_CH7'}
- {pin_num: '40', pin_signal: ADC0_SE8/ACMP1_IN4/PTC0/FTM0_CH0/FTM1_CH6, label: 'J15[B24]/FTM1_CH6'}
- {pin_num: '41', pin_signal: ACMP1_IN5/PTD9/LPI2C1_SCL/FTM2_FLT3/FTM1_CH5, label: 'J15[B50]/LPI2C1_SCL'}
- {pin_num: '42', pin_signal: PTD8/LPI2C1_SDA/FTM2_FLT2/FTM1_CH4, label: 'J15[B51]/LPI2C1_SDA'}
- {pin_num: '44', pin_signal: ADC0_SE14/PTC16/FTM1_FLT2/LPI2C1_SDAS, label: 'J15[B55]'}
- {pin_num: '45', pin_signal: ADC0_SE13/ACMP2_IN4/PTC15/FTM1_CH3, label: 'U4[16]/FTM1_CH3/RST_FXOS8700CQ', identifier: ACCEL_I2C_RST}
- {pin_num: '46', pin_signal: ADC0_SE12/ACMP2_IN5/PTC14/FTM1_CH2, label: 'J9[1]/ADC0_SE12/POT_5K', identifier: POT_5K}
- {pin_num: '47', pin_signal: ADC0_SE7/PTB3/FTM1_CH1/LPSPI0_SIN/FTM1_QD_PHA/TRGMUX_IN2, label: 'J15[A53]/ADC0_SE7'}
- {pin_num: '48', pin_signal: ADC0_SE6/PTB2/FTM1_CH0/LPSPI0_SCK/FTM1_QD_PHB/TRGMUX_IN3, label: 'J15[A35]/ADC0_SE6'}
- {pin_num: '49', pin_signal: PTC13/FTM3_CH7/FTM2_CH7, label: 'D9[C]/FTM3_CH7/LEDOR', identifier: LED_ORANGE}
- {pin_num: '50', pin_signal: PTC12/FTM3_CH6/FTM2_CH6, label: 'D8[C]/FTM3_CH6/LEDYL', identifier: LED_YELLOW}
- {pin_num: '100', pin_signal: PTA8/FXIO_D6/FTM3_FLT3, label: 'J20[9]'}
- {pin_num: '99', pin_signal: PTA9/FXIO_D7/FTM3_FLT2/FTM1_FLT3, label: 'J20[10]'}
- {pin_num: '98', pin_signal: PTA4/ACMP0_OUT/EWM_OUT_b/JTAG_TMS/SWD_DIO, label: 'J10[2]/J12[1]/SWD_DIO_TGTMCU'}
- {pin_num: '97', pin_signal: PTA5/TCLK1/JTAG_TRST_b/RESET_b, label: 'J10[10]/J13[1]/J15[A62]/J15[A63]/RST_TGTMCU_b'}
- {pin_num: '96', pin_signal: ACMP0_IN2/PTC4/FTM1_CH0/RTC_CLKOUT/EWM_IN/FTM1_QD_PHB/JTAG_TCLK/SWD_CLK, label: 'J10[4]/J11[1]/SWD_CLK_TGTMCU'}
- {pin_num: '95', pin_signal: PTC5/FTM2_CH0/RTC_CLKOUT/LPI2C1_HREQ/FTM2_QD_PHB/JTAG_TDI, label: 'J10[8]/TDI'}
- {pin_num: '94', pin_signal: ADC2_SE7/PTE0/LPSPI0_SCK/TCLK1/LPI2C1_SDA/FTM1_FLT2, label: 'J15[B48]/SPI0_SCK'}
- {pin_num: '93', pin_signal: ADC2_SE6/PTE1/LPSPI0_SIN/LPI2C0_HREQ/LPI2C1_SCL/FTM1_FLT1, label: 'J15[B44]/SPI0_SIN'}
- {pin_num: '92', pin_signal: PTA10/FTM1_CH4/LPUART0_TX/FXIO_D0/JTAG_TDO/noetm_Trace_SWO, label: 'J10[6]/TDO'}
- {pin_num: '91', pin_signal: PTA11/FTM1_CH5/LPUART0_RX/FXIO_D1, label: FTM1_CH5}
- {pin_num: '90', pin_signal: ADC2_SE5/PTA12/FTM1_CH6/CAN1_RX/LPI2C1_SDAS, label: 'J15[A50]'}
- {pin_num: '89', pin_signal: ADC2_SE4/PTA13/FTM1_CH7/CAN1_TX/LPI2C1_SCLS, label: 'J15[A51]'}
- {pin_num: '85', pin_signal: ADC1_SE10/PTE2/LPSPI0_SOUT/LPTMR0_ALT3/FTM3_CH6/PWT_IN3/LPUART1_CTS, label: 'J15[B45]/LPSPI0_SOUT'}
- {pin_num: '84', pin_signal: ADC1_SE11/ACMP0_IN6/PTE6/LPSPI0_PCS2/FTM3_CH7/LPUART1_RTS, label: 'J15[B46]/LPSPI0_PCS2'}
- {pin_num: '83', pin_signal: ADC1_SE12/PTA15/FTM1_CH2/LPSPI0_PCS3, label: 'J15[B52]/ADC1_SE12'}
- {pin_num: '82', pin_signal: ADC1_SE13/PTA16/FTM1_CH3/LPSPI1_PCS2, label: 'J15[B8]/LPSPI1_PCS2'}
- {pin_num: '81', pin_signal: ADC1_SE4/PTC6/LPUART1_RX/CAN1_RX/FTM3_CH2, label: 'J15[A41]/PTE3/LPUART1_RX', identifier: IRRX_UART}
- {pin_num: '80', pin_signal: ADC1_SE5/PTC7/LPUART1_TX/CAN1_TX/FTM3_CH3, label: 'J15[A42]/TP5/LPUART1_TX/IRTX', identifier: IRTX}
- {pin_num: '79', pin_signal: ADC0_SE0/ACMP0_IN0/PTA0/FTM2_CH1/LPI2C0_SCLS/FXIO_D2/FTM2_QD_PHA/LPUART0_CTS/TRGMUX_OUT3, label: THER_A/ADC0_SE0, identifier: THER_A}
- {pin_num: '78', pin_signal: ADC0_SE1/ACMP0_IN1/PTA1/FTM1_CH1/LPI2C0_SDAS/FXIO_D3/FTM1_QD_PHA/LPUART0_RTS/TRGMUX_OUT0, label: THER_B/ADC0_SE1, identifier: THER_B}
- {pin_num: '77', pin_signal: ADC2_SE11/PTB8/FTM3_CH0, label: 'J15[A29]/ADC2_SE11'}
- {pin_num: '76', pin_signal: ADC2_SE10/PTB9/FTM3_CH1/LPI2C0_SCLS, label: 'J15[B27]/ADC2_SE10'}
- {pin_num: '75', pin_signal: ADC2_SE9/PTB10/FTM3_CH2/LPI2C0_SDAS, label: 'J15[B28]/ADC2_SE9'}
- {pin_num: '74', pin_signal: ADC2_SE8/PTB11/FTM3_CH3/LPI2C0_HREQ, label: 'J15[A30]/ADC2_SE8'}
- {pin_num: '73', pin_signal: ADC1_SE0/PTA2/FTM3_CH0/LPI2C0_SDA/EWM_OUT_b/LPUART0_RX, label: 'J15[A8]/U4[6]/LPI2C0_SDA', identifier: ACCEL_I2C_SDA}
- {pin_num: '72', pin_signal: ADC1_SE1/PTA3/FTM3_CH1/LPI2C0_SCL/EWM_IN/LPUART0_TX, label: 'J15[A7]/U4[4]/LPI2C0_SCL', identifier: ACCEL_I2C_SCL}
- {pin_num: '71', pin_signal: ADC1_SE2/PTD2/FTM3_CH4/LPSPI1_SOUT/FXIO_D4/TRGMUX_IN5, label: 'J15A[B10]/LPSPI1_SOUT'}
- {pin_num: '70', pin_signal: ADC1_SE3/PTD3/FTM3_CH5/LPSPI1_PCS0/FXIO_D5/TRGMUX_IN4/NMI_b, label: 'J15[B9]/SW2/LPSPI1_PCS0', identifier: SW2}
- {pin_num: '69', pin_signal: ADC1_SE6/ACMP1_IN6/PTD4/FTM0_FLT3/FTM3_FLT3, label: 'J15[A27]/ADC1_SE6'}
- {pin_num: '68', pin_signal: ADC1_SE7/PTB12/FTM0_CH0/FTM3_FLT2, label: 'J15[A40]/FTM0_CH0'}
- {pin_num: '67', pin_signal: ADC1_SE8/ADC2_SE8/PTB13/FTM0_CH1/FTM3_FLT1, label: 'J15[A39]/FTM0_CH1'}
- {pin_num: '66', pin_signal: ADC1_SE9/ADC2_SE9/PTB14/FTM0_CH2/LPSPI1_SCK, label: 'J15[A38]/FTM0_CH2'}
- {pin_num: '65', pin_signal: ADC1_SE14/PTB15/FTM0_CH3/LPSPI1_SIN, label: 'J15[A37]/FTM0_CH3'}
- {pin_num: '64', pin_signal: ADC1_SE15/PTB16/FTM0_CH4/LPSPI1_SOUT, label: 'J15[B40]/FTM0_CH4'}
- {pin_num: '63', pin_signal: ADC2_SE3/PTB17/FTM0_CH5/LPSPI1_PCS3, label: 'J15[B39]/FTM0_CH5'}
- {pin_num: '62', pin_signal: PTA17/FTM0_CH6/FTM3_FLT0/EWM_OUT_b, label: 'J15[B35]'}
- {pin_num: '59', pin_signal: ADC2_SE2/ACMP2_IN6/PTE7/FTM0_CH7/FTM3_FLT0, label: 'J15[B30]/ADC2_SE2'}
- {pin_num: '58', pin_signal: ADC0_SE2/ACMP1_IN0/PTA6/FTM0_FLT1/LPSPI1_PCS1/LPUART1_CTS, label: 'J15[A28]/ADC0_SE2'}
- {pin_num: '57', pin_signal: ADC0_SE3/ACMP1_IN1/PTA7/FTM0_FLT2/RTC_CLKIN/LPUART1_RTS, label: 'J15[B29]/ADC0_SE3'}
- {pin_num: '56', pin_signal: ADC2_SE14/PTC8/LPUART1_RX/FTM1_FLT0/LPUART0_CTS, label: 'J15[A9]/LPUART0_CTS'}
- {pin_num: '55', pin_signal: ADC2_SE15/PTC9/LPUART1_TX/FTM1_FLT1/LPUART0_RTS, label: 'J15[B21]/LPUART0_RTS'}
- {pin_num: '54', pin_signal: ADC0_SE4/ADC1_SE14/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3, label: 'J5[2]/LPUART0_RX_TGTMCU', identifier: DEBUG_UART_RX}
- {pin_num: '53', pin_signal: ADC0_SE5/ADC1_SE15/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0, label: 'J3[2]/LPUART0_TX_TGTMCU', identifier: DEBUG_UART_TX}
- {pin_num: '52', pin_signal: PTC10/FTM3_CH4, label: 'D6[C]/FTM3_CH4/LEDRD', identifier: LED_RED1}
- {pin_num: '51', pin_signal: PTC11/FTM3_CH5, label: 'D7[C]/FTM3_CH5/LEDGR', identifier: LED_GREEN1}
- {pin_num: '7', pin_signal: PTE13/FTM2_FLT0, label: NC}
- {pin_num: '10', pin_signal: VDD10, label: MCU_VDD}
- {pin_num: '87', pin_signal: VDD88, label: MCU_VDD}
- {pin_num: '61', pin_signal: VDD62, label: MCU_VDD}
- {pin_num: '38', pin_signal: VDD39, label: MCU_VDD}
- {pin_num: '11', pin_signal: VDDA, label: VDDA}
- {pin_num: '14', pin_signal: VSS15, label: GND}
- {pin_num: '37', pin_signal: VSS38, label: GND}
- {pin_num: '60', pin_signal: VSS61, label: GND}
- {pin_num: '86', pin_signal: VSS87, label: GND}
- {pin_num: '12', pin_signal: VREFH, label: VREFH}
- {pin_num: '13', pin_signal: VREFL, label: GND}
- {pin_num: '24', pin_signal: PTD14/FTM2_CH5/CLKOUT, label: NC}
- {pin_num: '25', pin_signal: PTD13/FTM2_CH4/RTC_CLKOUT, label: NC}
- {pin_num: '43', pin_signal: ADC0_SE15/PTC17/FTM1_FLT3/LPI2C1_SCLS, label: NC}
- {pin_num: '88', pin_signal: PTA14/FTM0_FLT0/FTM3_FLT1/EWM_IN/FTM1_FLT0/BUSOUT, label: NC}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '92', peripheral: CoreDebug, signal: TRACE_SWO, pin_signal: PTA10/FTM1_CH4/LPUART0_TX/FXIO_D0/JTAG_TDO/noetm_Trace_SWO, pull_select: down}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA10 (pin 92) is configured as noetm_Trace_SWO */
    PORT_SetPinMux(PORTA, 10U, kPORT_MuxAlt7);

    PORTA->PCR[10] = ((PORTA->PCR[10] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | PORT_PCR_PS(kPORT_PullDown));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '50', peripheral: GPIOC, signal: 'GPIO, 12', pin_signal: PTC12/FTM3_CH6/FTM2_CH6, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '52', peripheral: GPIOC, signal: 'GPIO, 10', pin_signal: PTC10/FTM3_CH4, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '49', peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/FTM3_CH7/FTM2_CH7, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '51', peripheral: GPIOC, signal: 'GPIO, 11', pin_signal: PTC11/FTM3_CH5, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '27', peripheral: GPIOB, signal: 'GPIO, 5', pin_signal: PTB5/FTM0_CH5/LPSPI0_PCS1/TRGMUX_IN0/ACMP1_OUT, direction: OUTPUT, gpio_init_state: 'true',
    drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '22', peripheral: GPIOD, signal: 'GPIO, 15', pin_signal: ACMP2_IN1/PTD15/FTM0_CH0, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low,
    pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '21', peripheral: GPIOD, signal: 'GPIO, 16', pin_signal: ACMP2_IN0/PTD16/FTM0_CH1, direction: OUTPUT, gpio_init_state: 'true', drive_strength: low,
    pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDsPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTB5 (pin 27)  */
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_RED1_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC10 (pin 52)  */
    GPIO_PinInit(BOARD_LED_RED1_GPIO, BOARD_LED_RED1_PIN, &LED_RED1_config);

    gpio_pin_config_t LED_GREEN1_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC11 (pin 51)  */
    GPIO_PinInit(BOARD_LED_GREEN1_GPIO, BOARD_LED_GREEN1_PIN, &LED_GREEN1_config);

    gpio_pin_config_t LED_YELLOW_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC12 (pin 50)  */
    GPIO_PinInit(BOARD_LED_YELLOW_GPIO, BOARD_LED_YELLOW_PIN, &LED_YELLOW_config);

    gpio_pin_config_t LED_ORANGE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC13 (pin 49)  */
    GPIO_PinInit(BOARD_LED_ORANGE_GPIO, BOARD_LED_ORANGE_PIN, &LED_ORANGE_config);

    gpio_pin_config_t LED_GREEN2_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD15 (pin 22)  */
    GPIO_PinInit(BOARD_LED_GREEN2_GPIO, BOARD_LED_GREEN2_PIN, &LED_GREEN2_config);

    gpio_pin_config_t LED_RED2_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD16 (pin 21)  */
    GPIO_PinInit(BOARD_LED_RED2_GPIO, BOARD_LED_RED2_PIN, &LED_RED2_config);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port B */
        PORTB,
        /* Digital filter is configured for PORTB0 */
        PORT_DFER_DFE_5_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t LED_BLUE = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTB5 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTB5 (pin 27) is configured as PTB5 */
    PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port C */
        PORTC,
        /* Digital filter is configured for PORTC0 */
          PORT_DFER_DFE_10_MASK
            /* Digital filter is configured for PORTC1 */
            | PORT_DFER_DFE_11_MASK
            /* Digital filter is configured for PORTC2 */
            | PORT_DFER_DFE_12_MASK
            /* Digital filter is configured for PORTC3 */
            | PORT_DFER_DFE_13_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t LED_RED1 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTC10 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTC10 (pin 52) is configured as PTC10 */
    PORT_SetPinConfig(BOARD_LED_RED1_PORT, BOARD_LED_RED1_PIN, &LED_RED1);

    const port_pin_config_t LED_GREEN1 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC11 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC11 (pin 51) is configured as PTC11 */
    PORT_SetPinConfig(BOARD_LED_GREEN1_PORT, BOARD_LED_GREEN1_PIN, &LED_GREEN1);

    const port_pin_config_t LED_YELLOW = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC12 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC12 (pin 50) is configured as PTC12 */
    PORT_SetPinConfig(BOARD_LED_YELLOW_PORT, BOARD_LED_YELLOW_PIN, &LED_YELLOW);

    const port_pin_config_t LED_ORANGE = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC13 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC13 (pin 49) is configured as PTC13 */
    PORT_SetPinConfig(BOARD_LED_ORANGE_PORT, BOARD_LED_ORANGE_PIN, &LED_ORANGE);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_15_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_16_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t LED_GREEN2 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTD15 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTD15 (pin 22) is configured as PTD15 */
    PORT_SetPinConfig(BOARD_LED_GREEN2_PORT, BOARD_LED_GREEN2_PIN, &LED_GREEN2);

    const port_pin_config_t LED_RED2 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTD16 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTD16 (pin 21) is configured as PTD16 */
    PORT_SetPinConfig(BOARD_LED_RED2_PORT, BOARD_LED_RED2_PIN, &LED_RED2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONSPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '70', peripheral: GPIOD, signal: 'GPIO, 3', pin_signal: ADC1_SE3/PTD3/FTM3_CH5/LPSPI1_PCS0/FXIO_D5/TRGMUX_IN4/NMI_b, direction: INPUT, drive_strength: low,
    pull_select: up, pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '32', peripheral: GPIOD, signal: 'GPIO, 6', pin_signal: PTD6/LPUART2_RX/FTM2_FLT2, direction: INPUT, drive_strength: low, pull_select: up, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONSPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBUTTONSPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD3 (pin 70)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD6 (pin 32)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_3_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_6_MASK,
        /* Disable digital filter */
        false);

    /* PORTD3 (pin 70) is configured as PTD3 */
    PORT_SetPinMux(BOARD_SW2_PORT, BOARD_SW2_PIN, kPORT_MuxAsGpio);

    PORTD->PCR[3] =
        ((PORTD->PCR[3] &
          /* Mask bits to zero which are setting */
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK)))

         /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE
          * field is set. */
         | PORT_PCR_PS(kPORT_PullUp)

         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
         | PORT_PCR_PE(kPORT_PullDisable)

         /* Passive Filter Enable: Passive input filter is disabled on the corresponding pin. */
         | PORT_PCR_PFE(kPORT_PassiveFilterDisable)

         /* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin is
          * configured as a digital output. */
         | PORT_PCR_DSE(kPORT_LowDriveStrength));

    /* PORTD6 (pin 32) is configured as PTD6 */
    PORT_SetPinMux(BOARD_SW3_PORT, BOARD_SW3_PIN, kPORT_MuxAsGpio);

    PORTD->PCR[6] =
        ((PORTD->PCR[6] &
          /* Mask bits to zero which are setting */
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK)))

         /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE
          * field is set. */
         | PORT_PCR_PS(kPORT_PullUp)

         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
         | PORT_PCR_PE(kPORT_PullDisable)

         /* Passive Filter Enable: Passive input filter is disabled on the corresponding pin. */
         | PORT_PCR_PFE(kPORT_PassiveFilterDisable)

         /* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin is
          * configured as a digital output. */
         | PORT_PCR_DSE(kPORT_LowDriveStrength));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '30', peripheral: OSC32, signal: XTAL32, pin_signal: ADC0_SE10/ACMP0_IN5/XTAL32/PTC2/FTM0_CH2/CAN0_RX, drive_strength: no_init, pull_select: no_init,
    pull_enable: no_init, passive_filter: no_init, digital_filter: no_init}
  - {pin_num: '29', peripheral: OSC32, signal: EXTAL32, pin_signal: ADC0_SE11/ACMP0_IN4/EXTAL32/PTC3/FTM0_CH3/CAN0_TX, drive_strength: no_init, pull_select: no_init,
    pull_enable: no_init, passive_filter: no_init, digital_filter: no_init}
  - {pin_num: '16', peripheral: SCG, signal: XTAL0, pin_signal: XTAL/PTB6/LPI2C0_SDA, drive_strength: no_init, pull_select: no_init, pull_enable: no_init, passive_filter: no_init,
    digital_filter: no_init}
  - {pin_num: '15', peripheral: SCG, signal: EXTAL0, pin_signal: EXTAL/PTB7/LPI2C0_SCL, drive_strength: no_init, pull_select: no_init, pull_enable: no_init, passive_filter: no_init,
    digital_filter: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* PORTB6 (pin 16) is configured as XTAL */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTB7 (pin 15) is configured as EXTAL */
    PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC2 (pin 30) is configured as XTAL32 */
    PORT_SetPinMux(BOARD_XTAL32_PORT, BOARD_XTAL32_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC3 (pin 29) is configured as EXTAL32 */
    PORT_SetPinMux(BOARD_EXTAL32_PORT, BOARD_EXTAL32_PIN, kPORT_PinDisabledOrAnalog);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCELPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '72', peripheral: LPI2C0, signal: SCL, pin_signal: ADC1_SE1/PTA3/FTM3_CH1/LPI2C0_SCL/EWM_IN/LPUART0_TX, direction: OUTPUT, drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '73', peripheral: LPI2C0, signal: SDA, pin_signal: ADC1_SE0/PTA2/FTM3_CH0/LPI2C0_SDA/EWM_OUT_b/LPUART0_RX, direction: INPUT, drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '45', peripheral: GPIOC, signal: 'GPIO, 15', pin_signal: ADC0_SE13/ACMP2_IN4/PTC15/FTM1_CH3, direction: OUTPUT, gpio_init_state: 'false', drive_strength: low,
    pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCELPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCELPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t ACCEL_I2C_RST_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC15 (pin 45)  */
    GPIO_PinInit(BOARD_ACCEL_I2C_RST_GPIO, BOARD_ACCEL_I2C_RST_PIN, &ACCEL_I2C_RST_config);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port A */
        PORTA,
        /* Digital filter is configured for PORTA0 */
          PORT_DFER_DFE_2_MASK
            /* Digital filter is configured for PORTA1 */
            | PORT_DFER_DFE_3_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t ACCEL_I2C_SDA = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as LPI2C0_SDA */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTA2 (pin 73) is configured as LPI2C0_SDA */
    PORT_SetPinConfig(BOARD_ACCEL_I2C_SDA_PORT, BOARD_ACCEL_I2C_SDA_PIN, &ACCEL_I2C_SDA);

    const port_pin_config_t ACCEL_I2C_SCL = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as LPI2C0_SCL */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTA3 (pin 72) is configured as LPI2C0_SCL */
    PORT_SetPinConfig(BOARD_ACCEL_I2C_SCL_PORT, BOARD_ACCEL_I2C_SCL_PIN, &ACCEL_I2C_SCL);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port C */
        PORTC,
        /* Digital filter is configured for PORTC0 */
        PORT_DFER_DFE_15_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t ACCEL_I2C_RST = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as PTC15 */
                                             kPORT_MuxAsGpio,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTC15 (pin 45) is configured as PTC15 */
    PORT_SetPinConfig(BOARD_ACCEL_I2C_RST_PORT, BOARD_ACCEL_I2C_RST_PIN, &ACCEL_I2C_RST);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitTHERMISTORPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '79', peripheral: ADC0, signal: 'SE, 0', pin_signal: ADC0_SE0/ACMP0_IN0/PTA0/FTM2_CH1/LPI2C0_SCLS/FXIO_D2/FTM2_QD_PHA/LPUART0_CTS/TRGMUX_OUT3, drive_strength: low,
    pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '78', peripheral: ADC0, signal: 'SE, 1', pin_signal: ADC0_SE1/ACMP0_IN1/PTA1/FTM1_CH1/LPI2C0_SDAS/FXIO_D3/FTM1_QD_PHA/LPUART0_RTS/TRGMUX_OUT0, drive_strength: low,
    pull_select: down, pull_enable: disable, passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitTHERMISTORPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitTHERMISTORPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port A */
        PORTA,
        /* Digital filter is configured for PORTA0 */
          PORT_DFER_DFE_0_MASK
            /* Digital filter is configured for PORTA1 */
            | PORT_DFER_DFE_1_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t THER_A = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as ADC0_SE0 */
                                      kPORT_PinDisabledOrAnalog,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTA0 (pin 79) is configured as ADC0_SE0 */
    PORT_SetPinConfig(BOARD_THER_A_PORT, BOARD_THER_A_PIN, &THER_A);

    const port_pin_config_t THER_B = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as ADC0_SE1 */
                                      kPORT_PinDisabledOrAnalog,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTA1 (pin 78) is configured as ADC0_SE1 */
    PORT_SetPinConfig(BOARD_THER_B_PORT, BOARD_THER_B_PIN, &THER_B);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPOTPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '46', peripheral: ADC0, signal: 'SE, 12', pin_signal: ADC0_SE12/ACMP2_IN5/PTC14/FTM1_CH2, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPOTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPOTPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port C */
        PORTC,
        /* Digital filter is configured for PORTC0 */
        PORT_DFER_DFE_14_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t POT_5K = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as ADC0_SE12 */
                                      kPORT_PinDisabledOrAnalog,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTC14 (pin 46) is configured as ADC0_SE12 */
    PORT_SetPinConfig(BOARD_POT_5K_PORT, BOARD_POT_5K_PIN, &POT_5K);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitIRPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '80', peripheral: LPUART1, signal: TX, pin_signal: ADC1_SE5/PTC7/LPUART1_TX/CAN1_TX/FTM3_CH3, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
  - {pin_num: '17', peripheral: CMP2, signal: 'IN, 3', pin_signal: ACMP2_IN3/PTE14/FTM0_FLT1/FTM2_FLT1, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
  - {pin_num: '18', peripheral: CMP2, signal: OUT, pin_signal: PTE3/FTM0_FLT0/LPUART2_RTS/FTM2_FLT0/TRGMUX_IN6/ACMP2_OUT, drive_strength: low, pull_select: down,
    pull_enable: disable, passive_filter: disable, digital_filter: disable}
  - {pin_num: '81', peripheral: LPUART1, signal: RX, pin_signal: ADC1_SE4/PTC6/LPUART1_RX/CAN1_RX/FTM3_CH2, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitIRPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitIRPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port C */
        PORTC,
        /* Digital filter is configured for PORTC0 */
          PORT_DFER_DFE_6_MASK
            /* Digital filter is configured for PORTC1 */
            | PORT_DFER_DFE_7_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t IRRX_UART = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as LPUART1_RX */
                                         kPORT_MuxAlt2,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC6 (pin 81) is configured as LPUART1_RX */
    PORT_SetPinConfig(BOARD_IRRX_UART_PORT, BOARD_IRRX_UART_PIN, &IRRX_UART);

    const port_pin_config_t IRTX = {/* Internal pull-up/down resistor is disabled */
                                    kPORT_PullDisable,
                                    /* Passive filter is disabled */
                                    kPORT_PassiveFilterDisable,
                                    /* Low drive strength is configured */
                                    kPORT_LowDriveStrength,
                                    /* Pin is configured as LPUART1_TX */
                                    kPORT_MuxAlt2,
                                    /* Pin Control Register fields [15:0] are not locked */
                                    kPORT_UnlockRegister};
    /* PORTC7 (pin 80) is configured as LPUART1_TX */
    PORT_SetPinConfig(BOARD_IRTX_PORT, BOARD_IRTX_PIN, &IRTX);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port E */
        PORTE,
        /* Digital filter is configured for PORTE0 */
          PORT_DFER_DFE_3_MASK
            /* Digital filter is configured for PORTE1 */
            | PORT_DFER_DFE_14_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t IRRX_CMP_IN = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as ACMP2_IN3 */
                                           kPORT_PinDisabledOrAnalog,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTE14 (pin 17) is configured as ACMP2_IN3 */
    PORT_SetPinConfig(BOARD_IRRX_CMP_IN_PORT, BOARD_IRRX_CMP_IN_PIN, &IRRX_CMP_IN);

    const port_pin_config_t IRRX_CMP_OUT = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as ACMP2_OUT */
                                            kPORT_MuxAlt7,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTE3 (pin 18) is configured as ACMP2_OUT */
    PORT_SetPinConfig(BOARD_IRRX_CMP_OUT_PORT, BOARD_IRRX_CMP_OUT_PIN, &IRRX_CMP_OUT);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitCANPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '8', peripheral: CAN0, signal: TX, pin_signal: PTE5/TCLK2/FTM2_QD_PHA/FTM2_CH3/CAN0_TX/FXIO_D7/EWM_IN, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
  - {pin_num: '9', peripheral: CAN0, signal: RX, pin_signal: PTE4/BUSOUT/FTM2_QD_PHB/FTM2_CH2/CAN0_RX/FXIO_D6/EWM_OUT_b, drive_strength: low, pull_select: down, pull_enable: disable,
    passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitCANPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitCANPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port E */
        PORTE,
        /* Digital filter is configured for PORTE0 */
          PORT_DFER_DFE_4_MASK
            /* Digital filter is configured for PORTE1 */
            | PORT_DFER_DFE_5_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t CAN0_RX = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as CAN0_RX */
                                       kPORT_MuxAlt5,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTE4 (pin 9) is configured as CAN0_RX */
    PORT_SetPinConfig(BOARD_CAN0_RX_PORT, BOARD_CAN0_RX_PIN, &CAN0_RX);

    const port_pin_config_t CAN0_TX = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as CAN0_TX */
                                       kPORT_MuxAlt5,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTE5 (pin 8) is configured as CAN0_TX */
    PORT_SetPinConfig(BOARD_CAN0_TX_PORT, BOARD_CAN0_TX_PIN, &CAN0_TX);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '53', peripheral: LPUART0, signal: TX, pin_signal: ADC0_SE5/ADC1_SE15/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0, drive_strength: low, pull_select: up, pull_enable: enable,
    passive_filter: disable, digital_filter: disable}
  - {pin_num: '54', peripheral: LPUART0, signal: RX, pin_signal: ADC0_SE4/ADC1_SE14/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3, drive_strength: low, pull_select: up,
    pull_enable: enable, passive_filter: disable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port B */
        PORTB,
        /* Digital filter is configured for PORTB0 */
          PORT_DFER_DFE_0_MASK
            /* Digital filter is configured for PORTB1 */
            | PORT_DFER_DFE_1_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t DEBUG_UART_RX = {/* Internal pull-up resistor is enabled */
                                             kPORT_PullUp,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as LPUART0_RX */
                                             kPORT_MuxAlt2,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB0 (pin 54) is configured as LPUART0_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

    const port_pin_config_t DEBUG_UART_TX = {/* Internal pull-up resistor is enabled */
                                             kPORT_PullUp,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as LPUART0_TX */
                                             kPORT_MuxAlt2,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB1 (pin 53) is configured as LPUART0_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
