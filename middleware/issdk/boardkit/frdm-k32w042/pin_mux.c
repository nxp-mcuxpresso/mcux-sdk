/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: K32W042S1M2xxx
package_id: K32W042S1M2VPJ
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"


#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
}


#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C0_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: R1, peripheral: LPI2C0, signal: SDA, pin_signal: ADC0_SE4/LPCMP0_IN2/PTC9/LLWU_P16/LPSPI0_SOUT/LPUART0_CTS_b/LPI2C0_SDA/TPM0_CH2/LPTMR0_ALT2, slew_rate: fast,
    open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: R2, peripheral: LPI2C0, signal: SCL, pin_signal: ADC0_SE5/PTC10/LPSPI0_PCS2/LPUART0_RTS_b/LPI2C0_SCL/TPM0_CH3, slew_rate: fast, open_drain: enable,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAlt4);           /* PORTC10 (pin R2) is configured as LPI2C0_SCL */
  PORTC->PCR[10] = ((PORTC->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x01u)                                  /* Open Drain Enable: 0x01u */
    );
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_MuxAlt4);            /* PORTC9 (pin R1) is configured as LPI2C0_SDA */
  PORTC->PCR[9] = ((PORTC->PCR[9] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x01u)                                  /* Open Drain Enable: 0x01u */
    );
}



#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C0_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: R2, peripheral: ADC0, signal: 'SE, 5', pin_signal: ADC0_SE5/PTC10/LPSPI0_PCS2/LPUART0_RTS_b/LPI2C0_SCL/TPM0_CH3}
  - {pin_num: R1, peripheral: ADC0, signal: 'SE, 4', pin_signal: ADC0_SE4/LPCMP0_IN2/PTC9/LLWU_P16/LPSPI0_SOUT/LPUART0_CTS_b/LPI2C0_SDA/TPM0_CH2/LPTMR0_ALT2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_PinDisabledOrAnalog); /* PORTC10 (pin R2) is configured as ADC0_SE5 */
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_PinDisabledOrAnalog); /* PORTC9 (pin R1) is configured as ADC0_SE4 */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C1_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C1_InitPins(void) {
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C1_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C1_DeinitPins(void) {
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C2_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C2_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C2_InitPins(void) {
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C2_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C2_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C2_DeinitPins(void) {
}


#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C3_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: G15, peripheral: LPI2C3, signal: SDA, pin_signal: PTE29/LPUART3_RX/LPI2C3_SDA/FXIO0_D30, slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: G17, peripheral: LPI2C3, signal: SCL, pin_signal: PTE30/LPUART3_TX/LPI2C3_SCL/TPM2_CLKIN/FXIO0_D31, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C3_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C3_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t porte29_pinG15_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SDA */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN29_IDX, &porte29_pinG15_config); /* PORTE29 (pin G15) is configured as LPI2C3_SDA */
  const port_pin_config_t porte30_pinG17_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SCL */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN30_IDX, &porte30_pinG17_config); /* PORTE30 (pin G17) is configured as LPI2C3_SCL */
}


#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPI2C3_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: H5, peripheral: n/a, signal: disabled, pin_signal: PTB16/LLWU_P10/LPUART3_CTS_b/LPI2C3_SDA/FB_CS4_b/FB_TSIZ0/FB_BE31_24_b/FXIO0_D6}
  - {pin_num: G1, peripheral: n/a, signal: disabled, pin_signal: PTB15/LPI2C1_HREQ/LPI2C3_SCL/FB_CS5_b/FB_TSIZ1/FB_BE23_16_b/TPM0_CLKIN/FXIO0_D5}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C3_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPI2C3_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTE, PIN29_IDX, kPORT_PinDisabledOrAnalog); /* PORTB15 (pin G1) is disabled */
  PORT_SetPinMux(PORTE, PIN30_IDX, kPORT_PinDisabledOrAnalog); /* PORTB16 (pin H5) is disabled */
}

#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
}



#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART0_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: P3, peripheral: LPCMP0, signal: 'IN, 1', pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
  - {pin_num: N2, peripheral: LPCMP0, signal: 'IN, 0', pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_PinDisabledOrAnalog); /* PORTC7 (pin N2) is configured as LPCMP0_IN0 */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_PinDisabledOrAnalog); /* PORTC8 (pin P3) is configured as LPCMP0_IN1 */
}

#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART1_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART1_InitPins(void) {
    CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_MuxAlt2);           /* PORTA25 (pin B5) is configured as LPUART1_RX */
  PORT_SetPinMux(PORTA, PIN26_IDX, kPORT_MuxAlt2);           /* PORTA26 (pin A5) is configured as LPUART1_TX */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART1_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART1_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_PinDisabledOrAnalog); /* PORTC7 (pin N2) is configured as LPCMP0_IN0 */
  PORT_SetPinMux(PORTA, PIN26_IDX, kPORT_PinDisabledOrAnalog); /* PORTC8 (pin P3) is configured as LPCMP0_IN1 */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART2_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART2_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART2_InitPins(void) {
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART2_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART2_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPUART2_DeinitPins(void) {
}


#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPSPI0_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: C2, peripheral: LPSPI0, signal: SCK, pin_signal: ADC0_SE1/PTB4/LLWU_P6/RF0_RF_OFF/RF0_DFT_RESET/LPSPI0_SCK/LPUART1_CTS_b/SAI0_TX_BCLK/FB_AD9/TPM0_CH2}
  - {pin_num: D2, peripheral: LPSPI0, signal: OUT, pin_signal: PTB5/RF0_ACTIVE/LPSPI0_SOUT/LPUART1_RTS_b/SAI0_MCLK/FB_AD8/TPM0_CH3}
  - {pin_num: E2, peripheral: LPSPI0, signal: IN, pin_signal: ADC0_SE2/PTB7/LLWU_P8/LPSPI0_SIN/LPI2C1_SDAS/SAI0_RX_FS/FB_AD6/TPM0_CH5/RF0_BSM_DATA}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI0_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAlt2);            /* PORTB4 (pin C2) is configured as LPSPI0_SCK */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAlt2);            /* PORTB5 (pin D2) is configured as LPSPI0_SOUT */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAlt2);            /* PORTB7 (pin E2) is configured as LPSPI0_SIN */
}


#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPSPI0_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: E2, peripheral: GPIOB, signal: 'GPIO, 7', pin_signal: ADC0_SE2/PTB7/LLWU_P8/LPSPI0_SIN/LPI2C1_SDAS/SAI0_RX_FS/FB_AD6/TPM0_CH5/RF0_BSM_DATA}
  - {pin_num: C2, peripheral: GPIOB, signal: 'GPIO, 4', pin_signal: ADC0_SE1/PTB4/LLWU_P6/RF0_RF_OFF/RF0_DFT_RESET/LPSPI0_SCK/LPUART1_CTS_b/SAI0_TX_BCLK/FB_AD9/TPM0_CH2}
  - {pin_num: D2, peripheral: n/a, signal: disabled, pin_signal: PTB5/RF0_ACTIVE/LPSPI0_SOUT/LPUART1_RTS_b/SAI0_MCLK/FB_AD8/TPM0_CH3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void LPSPI0_DeinitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_PinDisabledOrAnalog);          /* PORTB4 (pin C2) is disabled */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_PinDisabledOrAnalog);          /* PORTB5 (pin D2) is disabled */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_PinDisabledOrAnalog);          /* PORTB7 (pin E2) is disabled */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
