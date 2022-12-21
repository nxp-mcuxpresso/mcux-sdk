/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MK64FN1M0xxx12'
- !!package 'MK64FN1M0VLL12'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.0.9'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '81', peripheral: LPUART1, signal: RX, pin_signal: ADC1_SE4/TSI0_CH15/PTC6/LPUART1_RX}
  - {pin_num: '80', peripheral: LPUART1, signal: TX, pin_signal: ADC1_SE5/TSI0_CH16/PTC7/LPUART1_TX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_MuxAlt2);            /* PORTC6 (pin 81) is configured as LPUART1_RX */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin 80) is configured as LPUART1_TX */
}


#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART0_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: LPUART0, signal: RX, pin_signal: ADC0_SE4/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3}
  - {pin_num: '53', peripheral: LPUART0, signal: TX, pin_signal: ADC0_SE5/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAlt2);            /* PORTB0 (pin 54) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAlt2);            /* PORTB1 (pin 53) is configured as LPUART0_TX */
}


#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART0_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: ADC0, signal: 'SE, 4', pin_signal: ADC0_SE4/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3}
  - {pin_num: '53', peripheral: ADC0, signal: 'SE, 5', pin_signal: ADC0_SE5/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_PinDisabledOrAnalog); /* PORTB0 (pin 54) is configured as ADC0_SE4 */
  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_PinDisabledOrAnalog); /* PORTB1 (pin 53) is configured as ADC0_SE5 */
}


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART1_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '81', peripheral: LPUART1, signal: RX, pin_signal: ADC1_SE4/TSI0_CH15/PTC6/LPUART1_RX}
  - {pin_num: '80', peripheral: LPUART1, signal: TX, pin_signal: ADC1_SE5/TSI0_CH16/PTC7/LPUART1_TX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART1_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Control: 0x01u */
#ifndef USE_BLUETOOTH_PORT
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_MuxAlt2);            /* PORTC6 (pin 81) is configured as LPUART1_RX */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin 80) is configured as LPUART1_TX */
#else
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt2);            /* PORTC8 (pin 54) is configured as ADC0_SE4 */
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_MuxAlt2);            /* PORTC9 (pin 53) is configured as ADC0_SE5 */
#endif
}


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART1_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '81', peripheral: ADC1, signal: 'SE, 4', pin_signal: ADC1_SE4/TSI0_CH15/PTC6/LPUART1_RX}
  - {pin_num: '80', peripheral: ADC1, signal: 'SE, 5', pin_signal: ADC1_SE5/TSI0_CH16/PTC7/LPUART1_TX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART1_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Control: 0x01u */
#ifndef USE_BLUETOOTH_PORT
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_PinDisabledOrAnalog); /* PORTC6 (pin 81) is configured as ADC1_SE4 */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_PinDisabledOrAnalog); /* PORTC7 (pin 80) is configured as ADC1_SE5 */
#else
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_PinDisabledOrAnalog); /* PORTC8 (pin 54) is configured as ADC0_SE4 */
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_PinDisabledOrAnalog); /* PORTC9 (pin 53) is configured as ADC0_SE5 */
#endif
}


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART2_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '32', peripheral: LPUART2, signal: RX, pin_signal: TSI0_CH7/PTD6/LPUART2_RX/FTM2_FLT2}
  - {pin_num: '31', peripheral: LPUART2, signal: TX, pin_signal: TSI0_CH10/PTD7/LPUART2_TX/FTM2_FLT3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART2_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART2_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt2);            /* PORTD6 (pin 32) is configured as LPUART2_RX */
  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_MuxAlt2);            /* PORTD7 (pin 31) is configured as LPUART2_TX */
}


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPUART2_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '32', peripheral: TSI, signal: 'CH, 7', pin_signal: TSI0_CH7/PTD6/LPUART2_RX/FTM2_FLT2}
  - {pin_num: '31', peripheral: TSI, signal: 'CH, 10', pin_signal: TSI0_CH10/PTD7/LPUART2_TX/FTM2_FLT3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART2_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART2_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_PinDisabledOrAnalog); /* PORTD6 (pin 32) is configured as TSI0_CH7 */
  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_PinDisabledOrAnalog); /* PORTD7 (pin 31) is configured as TSI0_CH10 */
}



#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPI2C0_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '73', peripheral: LPI2C0, signal: SDA, pin_signal: ADC1_SE0/PTA2/LPI2C0_SDA/EWM_OUT_b/LPUART0_RX, drive_strength: low, pull_select: up, pull_enable: enable,
    passive_filter: disable}
  - {pin_num: '72', peripheral: LPI2C0, signal: SCL, pin_signal: ADC1_SE1/PTA3/LPI2C0_SCL/EWM_IN/LPUART0_TX, drive_strength: low, pull_select: up, pull_enable: enable,
    passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Control: 0x01u */

  const port_pin_config_t porta2_pin73_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C0_SDA */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN2_IDX, &porta2_pin73_config);  /* PORTA2 (pin 73) is configured as LPI2C0_SDA */
  const port_pin_config_t porta3_pin72_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C0_SCL */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN3_IDX, &porta3_pin72_config);  /* PORTA3 (pin 72) is configured as LPI2C0_SCL */
}


#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPI2C0_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '73', peripheral: ADC1, signal: 'SE, 0', pin_signal: ADC1_SE0/PTA2/LPI2C0_SDA/EWM_OUT_b/LPUART0_RX}
  - {pin_num: '72', peripheral: ADC1, signal: 'SE, 1', pin_signal: ADC1_SE1/PTA3/LPI2C0_SCL/EWM_IN/LPUART0_TX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN2_IDX, kPORT_PinDisabledOrAnalog); /* PORTA2 (pin 73) is configured as ADC1_SE0 */
  PORT_SetPinMux(PORTA, PIN3_IDX, kPORT_PinDisabledOrAnalog); /* PORTA3 (pin 72) is configured as ADC1_SE1 */
}


#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPI2C1_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '42', peripheral: LPI2C1, signal: SDA, pin_signal: PTD8/LPI2C1_SDA/FTM2_FLT2, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '41', peripheral: LPI2C1, signal: SCL, pin_signal: ACMP1_IN5/PTD9/LPI2C1_SCL/FTM2_FLT3, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C1_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Control: 0x01u */

  const port_pin_config_t portd8_pin42_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as LPI2C1_SDA */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN8_IDX, &portd8_pin42_config);  /* PORTD8 (pin 42) is configured as LPI2C1_SDA */
  const port_pin_config_t portd9_pin41_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as LPI2C1_SCL */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN9_IDX, &portd9_pin41_config);  /* PORTD9 (pin 41) is configured as LPI2C1_SCL */
}


#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPI2C1_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '42', peripheral: n/a, signal: disabled, pin_signal: PTD8/LPI2C1_SDA/FTM2_FLT2}
  - {pin_num: '41', peripheral: CMP1, signal: 'IN, 5', pin_signal: ACMP1_IN5/PTD9/LPI2C1_SCL/FTM2_FLT3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C1_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTD, PIN8_IDX, kPORT_PinDisabledOrAnalog); /* PORTD8 (pin 42) is disabled */
  PORT_SetPinMux(PORTD, PIN9_IDX, kPORT_PinDisabledOrAnalog); /* PORTD9 (pin 41) is configured as ACMP1_IN5 */
}



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPSPI0_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '94', peripheral: LPSPI0, signal: SCK, pin_signal: TSI0_CH13/PTE0/LPSPI0_SCK/TCLK1/LPI2C1_SDA/FTM1_FLT2}
  - {pin_num: '93', peripheral: LPSPI0, signal: SIN, pin_signal: TSI0_CH14/PTE1/LPSPI0_SIN/LPI2C0_HREQ/LPI2C1_SCL}
  - {pin_num: '85', peripheral: LPSPI0, signal: SOUT, pin_signal: ADC1_SE10/TSI0_CH19/PTE2/LPSPI0_SOUT/LPTMR0_ALT3/PWT_IN3/LPUART1_CTS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTE, PIN0_IDX, kPORT_MuxAlt2);            /* PORTE0 (pin 94) is configured as LPSPI0_SCK */
  PORT_SetPinMux(PORTE, PIN1_IDX, kPORT_MuxAlt2);            /* PORTE1 (pin 93) is configured as LPSPI0_SIN */
  PORT_SetPinMux(PORTE, PIN2_IDX, kPORT_MuxAlt2);            /* PORTE2 (pin 85) is configured as LPSPI0_SOUT */
}


#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPSPI0_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '94', peripheral: TSI, signal: 'CH, 13', pin_signal: TSI0_CH13/PTE0/LPSPI0_SCK/TCLK1/LPI2C1_SDA/FTM1_FLT2}
  - {pin_num: '93', peripheral: TSI, signal: 'CH, 14', pin_signal: TSI0_CH14/PTE1/LPSPI0_SIN/LPI2C0_HREQ/LPI2C1_SCL}
  - {pin_num: '85', peripheral: TSI, signal: 'CH, 19', pin_signal: ADC1_SE10/TSI0_CH19/PTE2/LPSPI0_SOUT/LPTMR0_ALT3/PWT_IN3/LPUART1_CTS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTE, PIN0_IDX, kPORT_PinDisabledOrAnalog); /* PORTE0 (pin 94) is configured as TSI0_CH13 */
  PORT_SetPinMux(PORTE, PIN1_IDX, kPORT_PinDisabledOrAnalog); /* PORTE1 (pin 93) is configured as TSI0_CH14 */
  PORT_SetPinMux(PORTE, PIN2_IDX, kPORT_PinDisabledOrAnalog); /* PORTE2 (pin 85) is configured as TSI0_CH19 */
}


#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPSPI1_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '66', peripheral: LPSPI1, signal: SCK, pin_signal: ADC1_SE9/PTB14/FTM0_CH2/LPSPI1_SCK}
  - {pin_num: '65', peripheral: LPSPI1, signal: SIN, pin_signal: PTB15/FTM0_CH3/LPSPI1_SIN}
  - {pin_num: '64', peripheral: LPSPI1, signal: SOUT, pin_signal: PTB16/FTM0_CH4/LPSPI1_SOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI1_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN14_IDX, kPORT_MuxAlt3);           /* PORTB14 (pin 66) is configured as LPSPI1_SCK */
  PORT_SetPinMux(PORTB, PIN15_IDX, kPORT_MuxAlt3);           /* PORTB15 (pin 65) is configured as LPSPI1_SIN */
  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);           /* PORTB16 (pin 64) is configured as LPSPI1_SOUT */
}


#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
LPSPI1_DeinitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '66', peripheral: ADC1, signal: 'SE, 9', pin_signal: ADC1_SE9/PTB14/FTM0_CH2/LPSPI1_SCK}
  - {pin_num: '65', peripheral: n/a, signal: disabled, pin_signal: PTB15/FTM0_CH3/LPSPI1_SIN}
  - {pin_num: '64', peripheral: n/a, signal: disabled, pin_signal: PTB16/FTM0_CH4/LPSPI1_SOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI1_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN14_IDX, kPORT_PinDisabledOrAnalog); /* PORTB14 (pin 66) is configured as ADC1_SE9 */
  PORT_SetPinMux(PORTB, PIN15_IDX, kPORT_PinDisabledOrAnalog); /* PORTB15 (pin 65) is disabled */
  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_PinDisabledOrAnalog); /* PORTB16 (pin 64) is disabled */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
