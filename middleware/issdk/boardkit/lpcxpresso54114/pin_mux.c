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
- !!processor 'LPC54114J256'
- !!package 'LPC54114J256BD64'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.1.0'
- !!board 'LPCXpresso54114'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_inputmux.h"
#include "pin_mux.h"

#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port 0 */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '31', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI, pin_signal: PIO0_0/FC0_RXD_SDA_MOSI/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_OUT3, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '32', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO, pin_signal: PIO0_1/FC0_TXD_SCL_MISO/FC3_RTS_SCL_SSEL1/CTIMER0_CAP1/SCT0_OUT1, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin0_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC0_RXD_SDA_MOSI */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN0_IDX, port0_pin0_config); /* PORT0 PIN0 (coords: 31) is configured as FC0_RXD_SDA_MOSI */
  const uint32_t port0_pin1_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC0_TXD_SCL_MISO */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN1_IDX, port0_pin1_config); /* PORT0 PIN1 (coords: 32) is configured as FC0_TXD_SCL_MISO */
}


#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port 0 */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
USART0_InitPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '31', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI, pin_signal: PIO0_0/FC0_RXD_SDA_MOSI/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_OUT3, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '32', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO, pin_signal: PIO0_1/FC0_TXD_SCL_MISO/FC3_RTS_SCL_SSEL1/CTIMER0_CAP1/SCT0_OUT1, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : USART0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void USART0_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin0_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC0_RXD_SDA_MOSI */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN0_IDX, port0_pin0_config); /* PORT0 PIN0 (coords: 31) is configured as FC0_RXD_SDA_MOSI */
  const uint32_t port0_pin1_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC0_TXD_SCL_MISO */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN1_IDX, port0_pin1_config); /* PORT0 PIN1 (coords: 32) is configured as FC0_TXD_SCL_MISO */
}


#define PIO00_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO00_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO01_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO01_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
USART0_DeinitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '31', peripheral: GPIO, signal: 'PIO0, 0', pin_signal: PIO0_0/FC0_RXD_SDA_MOSI/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_OUT3}
  - {pin_num: '32', peripheral: GPIO, signal: 'PIO0, 1', pin_signal: PIO0_1/FC0_TXD_SCL_MISO/FC3_RTS_SCL_SSEL1/CTIMER0_CAP1/SCT0_OUT1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : USART0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void USART0_DeinitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][0] = ((IOCON->PIO[0][0] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO00_FUNC_ALT0)                      /* Selects pin function.: PORT00 (pin 31) is configured as PIO0_0 */
      | IOCON_PIO_DIGIMODE(PIO00_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][1] = ((IOCON->PIO[0][1] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO01_FUNC_ALT0)                      /* Selects pin function.: PORT01 (pin 32) is configured as PIO0_1 */
      | IOCON_PIO_DIGIMODE(PIO01_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_I2CDRIVE_LOW        0x00u   /*!< Low drive: 4 mA */
#define IOCON_PIO_I2CFILTER_EN        0x00u   /*!< I2C 50 ns glitch filter enabled */
#define IOCON_PIO_I2CSLEW_I2C         0x00u   /*!< I2C mode */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port 0 */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C4_InitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: FLEXCOMM4, signal: CTS_SDA_SSEL0, pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3, invert: disabled, glitch_filter: disabled, i2c_slew: i2c,
    i2c_drive: low, i2c_filter: enabled}
  - {pin_num: '3', peripheral: FLEXCOMM4, signal: RTS_SCL_SSEL1, pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1, invert: disabled,
    glitch_filter: disabled, i2c_slew: i2c, i2c_drive: low, i2c_filter: enabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C4_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C4_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin25_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC4_RTS_SCL_SSEL1 */
    IOCON_PIO_I2CSLEW_I2C |                                  /* I2C mode */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_I2CDRIVE_LOW |                                 /* Low drive: 4 mA */
    IOCON_PIO_I2CFILTER_EN                                   /* I2C 50 ns glitch filter enabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN25_IDX, port0_pin25_config); /* PORT0 PIN25 (coords: 3) is configured as FC4_RTS_SCL_SSEL1 */
  const uint32_t port0_pin26_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC4_CTS_SDA_SSEL0 */
    IOCON_PIO_I2CSLEW_I2C |                                  /* I2C mode */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_I2CDRIVE_LOW |                                 /* Low drive: 4 mA */
    IOCON_PIO_I2CFILTER_EN                                   /* I2C 50 ns glitch filter enabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN26_IDX, port0_pin26_config); /* PORT0 PIN26 (coords: 4) is configured as FC4_CTS_SDA_SSEL0 */
}


#define PIO025_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO025_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO026_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO026_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C4_DeinitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: GPIO, signal: 'PIO0, 26', pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3}
  - {pin_num: '3', peripheral: GPIO, signal: 'PIO0, 25', pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C4_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C4_DeinitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][25] = ((IOCON->PIO[0][25] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO025_FUNC_ALT0)                     /* Selects pin function.: PORT025 (pin 3) is configured as PIO0_25 */
      | IOCON_PIO_DIGIMODE(PIO025_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO026_FUNC_ALT0)                     /* Selects pin function.: PORT026 (pin 4) is configured as PIO0_26 */
      | IOCON_PIO_DIGIMODE(PIO026_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port 0 */
#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C5_InitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '58', peripheral: FLEXCOMM5, signal: TXD_SCL_MISO, pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, mode: inactive, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '60', peripheral: FLEXCOMM5, signal: RXD_SDA_MOSI, pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, mode: inactive, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C5_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C5_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin18_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC5_TXD_SCL_MISO */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN18_IDX, port0_pin18_config); /* PORT0 PIN18 (coords: 58) is configured as FC5_TXD_SCL_MISO */
  const uint32_t port0_pin20_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC5_RXD_SDA_MOSI */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN20_IDX, port0_pin20_config); /* PORT0 PIN20 (coords: 60) is configured as FC5_RXD_SDA_MOSI */
}


#define PIO018_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO018_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO020_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO020_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C5_DeinitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '60', peripheral: GPIO, signal: 'PIO0, 20', pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0}
  - {pin_num: '58', peripheral: GPIO, signal: 'PIO0, 18', pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C5_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C5_DeinitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO018_FUNC_ALT0)                     /* Selects pin function.: PORT018 (pin 58) is configured as PIO0_18 */
      | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO020_FUNC_ALT0)                     /* Selects pin function.: PORT020 (pin 60) is configured as PIO0_20 */
      | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC2               0x02u   /*!< Selects pin function 2 */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_PULLUP         0x10u   /*!< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port 0 */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port 0 */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port 0 */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
SPI3_InitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '47', peripheral: FLEXCOMM3, signal: RXD_SDA_MOSI, pin_signal: PIO0_12/FC3_RXD_SDA_MOSI/FC6_TXD_SCL_MISO_WS/CTIMER2_MAT3, mode: pullUp, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '46', peripheral: FLEXCOMM3, signal: SCK, pin_signal: PIO0_11/FC3_SCK/FC6_RXD_SDA_MOSI_DATA/CTIMER2_MAT1, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '48', peripheral: FLEXCOMM3, signal: TXD_SCL_MISO, pin_signal: PIO0_13/FC3_TXD_SCL_MISO/SCT0_OUT4/CTIMER2_MAT0, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '38', peripheral: FLEXCOMM3, signal: SSEL2, pin_signal: PIO0_4/FC0_SCK/FC3_SSEL2/CTIMER0_CAP2, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI3_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void SPI3_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin11_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC3_SCK */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN11_IDX, port0_pin11_config); /* PORT0 PIN11 (coords: 46) is configured as FC3_SCK */
  const uint32_t port0_pin12_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC3_RXD_SDA_MOSI */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN12_IDX, port0_pin12_config); /* PORT0 PIN12 (coords: 47) is configured as FC3_RXD_SDA_MOSI */
  const uint32_t port0_pin13_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC3_TXD_SCL_MISO */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN13_IDX, port0_pin13_config); /* PORT0 PIN13 (coords: 48) is configured as FC3_TXD_SCL_MISO */
  const uint32_t port0_pin4_config = (
    IOCON_PIO_FUNC2 |                                        /* Pin is configured as FC3_SSEL2 */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN4_IDX, port0_pin4_config); /* PORT0 PIN4 (coords: 38) is configured as FC3_SSEL2 */
}


#define DMA_ITRIG_INMUX0_IDX             0u   /*!< Inputmux DMA_ITRIG_INMUX register index 0 */
#define DMA_ITRIG_INMUX1_IDX             1u   /*!< Inputmux DMA_ITRIG_INMUX register index 1 */
#define PINTSEL0_IDX                     0u   /*!< Inputmux PINTSEL register index 0 */
#define PINTSEL1_IDX                     1u   /*!< Inputmux PINTSEL register index 1 */
#define PINTSEL2_IDX                     2u   /*!< Inputmux PINTSEL register index 2 */
#define PINTSEL3_IDX                     3u   /*!< Inputmux PINTSEL register index 3 */
#define PIO011_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO011_FILTEROFF_DISABLED     0x01u   /*!< Controls input glitch filter.: Filter disabled. No input filtering is done. */
#define PIO011_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO011_INVERT_DISABLED        0x00u   /*!< Input polarity.: Disabled. Input function is not inverted. */
#define PIO011_OD_NORMAL              0x00u   /*!< Controls open-drain mode.: Normal. Normal push-pull output */
#define PIO012_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO012_FILTEROFF_DISABLED     0x01u   /*!< Controls input glitch filter.: Filter disabled. No input filtering is done. */
#define PIO012_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO012_INVERT_DISABLED        0x00u   /*!< Input polarity.: Disabled. Input function is not inverted. */
#define PIO012_OD_NORMAL              0x00u   /*!< Controls open-drain mode.: Normal. Normal push-pull output */
#define PIO013_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO013_FILTEROFF_DISABLED     0x01u   /*!< Controls input glitch filter.: Filter disabled. No input filtering is done. */
#define PIO013_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO013_INVERT_DISABLED        0x00u   /*!< Input polarity.: Disabled. Input function is not inverted. */
#define PIO013_OD_NORMAL              0x00u   /*!< Controls open-drain mode.: Normal. Normal push-pull output */
#define PIO04_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO04_FILTEROFF_DISABLED      0x01u   /*!< Controls input glitch filter.: Filter disabled. No input filtering is done. */
#define PIO04_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO04_INVERT_DISABLED         0x00u   /*!< Input polarity.: Disabled. Input function is not inverted. */
#define PIO04_OD_NORMAL               0x00u   /*!< Controls open-drain mode.: Normal. Normal push-pull output */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
SPI3_DeinitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '46', peripheral: ADC0, signal: 'TRIG, 0', pin_signal: PIO0_11/FC3_SCK/FC6_RXD_SDA_MOSI_DATA/CTIMER2_MAT1, mode: no_init, invert: disabled, glitch_filter: disabled,
    slew_rate: no_init, open_drain: disabled}
  - {pin_num: '47', peripheral: ADC0, signal: 'TRIG, 1', pin_signal: PIO0_12/FC3_RXD_SDA_MOSI/FC6_TXD_SCL_MISO_WS/CTIMER2_MAT3, mode: no_init, invert: disabled, glitch_filter: disabled,
    slew_rate: no_init, open_drain: disabled}
  - {pin_num: '48', peripheral: DMA0, signal: 'TRIG, 0', pin_signal: PIO0_13/FC3_TXD_SCL_MISO/SCT0_OUT4/CTIMER2_MAT0, mode: no_init, invert: disabled, glitch_filter: disabled,
    slew_rate: no_init, open_drain: disabled}
  - {pin_num: '38', peripheral: DMA0, signal: 'TRIG, 1', pin_signal: PIO0_4/FC0_SCK/FC3_SSEL2/CTIMER0_CAP2, mode: no_init, invert: disabled, glitch_filter: disabled,
    slew_rate: no_init, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI3_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void SPI3_DeinitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_InputMux);                        /* Enables the clock for the input muxes. 0 = Disable; 1 = Enable.: 0x01u */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX0_IDX,kINPUTMUX_PinInt2ToDma); /* Pin interrupt 2 is selected as trigger input for DMA channel 0 */
  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX1_IDX,kINPUTMUX_PinInt3ToDma); /* Pin interrupt 3 is selected as trigger input for DMA channel 1 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL0_IDX,kINPUTMUX_GpioPort0Pin11ToPintsel); /* PIO0_11 is selected for PINT input 0 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL1_IDX,kINPUTMUX_GpioPort0Pin12ToPintsel); /* PIO0_12 is selected for PINT input 1 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL2_IDX,kINPUTMUX_GpioPort0Pin13ToPintsel); /* PIO0_13 is selected for PINT input 2 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL3_IDX,kINPUTMUX_GpioPort0Pin4ToPintsel); /* PIO0_4 is selected for PINT input 3 */
  IOCON->PIO[0][11] = ((IOCON->PIO[0][11] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_INVERT_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK | IOCON_PIO_OD_MASK))) /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO011_FUNC_ALT0)                     /* Selects pin function.: PORT011 (pin 46) is configured as PIO0_11 */
      | IOCON_PIO_INVERT(PIO011_INVERT_DISABLED)             /* Input polarity.: Disabled. Input function is not inverted. */
      | IOCON_PIO_DIGIMODE(PIO011_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
      | IOCON_PIO_FILTEROFF(PIO011_FILTEROFF_DISABLED)       /* Controls input glitch filter.: Filter disabled. No input filtering is done. */
      | IOCON_PIO_OD(PIO011_OD_NORMAL)                       /* Controls open-drain mode.: Normal. Normal push-pull output */
    );
  IOCON->PIO[0][12] = ((IOCON->PIO[0][12] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_INVERT_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK | IOCON_PIO_OD_MASK))) /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO012_FUNC_ALT0)                     /* Selects pin function.: PORT012 (pin 47) is configured as PIO0_12 */
      | IOCON_PIO_INVERT(PIO012_INVERT_DISABLED)             /* Input polarity.: Disabled. Input function is not inverted. */
      | IOCON_PIO_DIGIMODE(PIO012_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
      | IOCON_PIO_FILTEROFF(PIO012_FILTEROFF_DISABLED)       /* Controls input glitch filter.: Filter disabled. No input filtering is done. */
      | IOCON_PIO_OD(PIO012_OD_NORMAL)                       /* Controls open-drain mode.: Normal. Normal push-pull output */
    );
  IOCON->PIO[0][13] = ((IOCON->PIO[0][13] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_INVERT_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK | IOCON_PIO_OD_MASK))) /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO013_FUNC_ALT0)                     /* Selects pin function.: PORT013 (pin 48) is configured as PIO0_13 */
      | IOCON_PIO_INVERT(PIO013_INVERT_DISABLED)             /* Input polarity.: Disabled. Input function is not inverted. */
      | IOCON_PIO_DIGIMODE(PIO013_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
      | IOCON_PIO_FILTEROFF(PIO013_FILTEROFF_DISABLED)       /* Controls input glitch filter.: Filter disabled. No input filtering is done. */
      | IOCON_PIO_OD(PIO013_OD_NORMAL)                       /* Controls open-drain mode.: Normal. Normal push-pull output */
    );
  IOCON->PIO[0][4] = ((IOCON->PIO[0][4] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_INVERT_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK | IOCON_PIO_OD_MASK))) /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO04_FUNC_ALT0)                      /* Selects pin function.: PORT04 (pin 38) is configured as PIO0_4 */
      | IOCON_PIO_INVERT(PIO04_INVERT_DISABLED)              /* Input polarity.: Disabled. Input function is not inverted. */
      | IOCON_PIO_DIGIMODE(PIO04_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
      | IOCON_PIO_FILTEROFF(PIO04_FILTEROFF_DISABLED)        /* Controls input glitch filter.: Filter disabled. No input filtering is done. */
      | IOCON_PIO_OD(PIO04_OD_NORMAL)                        /* Controls open-drain mode.: Normal. Normal push-pull output */
    );
}


#define IOCON_PIO_DIGITAL_EN          0x80u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC4               0x04u   /*!< Selects pin function 4 */
#define IOCON_PIO_INPFILT_OFF       0x0100u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_PULLUP         0x10u   /*!< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port 1 */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port 0 */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port 0 */
#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */
#define PORT1_IDX                        1u   /*!< Port index */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
SPI5_InitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '15', peripheral: FLEXCOMM5, signal: SSEL2, pin_signal: PIO1_1/SWO/SCT0_OUT4/FC5_SSEL2/FC4_TXD_SCL_MISO/ADC0_4, mode: pullUp, invert: disabled, glitch_filter: disabled,
    open_drain: disabled}
  - {pin_num: '58', peripheral: FLEXCOMM5, signal: TXD_SCL_MISO, pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '59', peripheral: FLEXCOMM5, signal: SCK, pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '60', peripheral: FLEXCOMM5, signal: RXD_SDA_MOSI, pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI5_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void SPI5_InitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t port0_pin18_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC5_TXD_SCL_MISO */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN18_IDX, port0_pin18_config); /* PORT0 PIN18 (coords: 58) is configured as FC5_TXD_SCL_MISO */
  const uint32_t port0_pin19_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC5_SCK */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN19_IDX, port0_pin19_config); /* PORT0 PIN19 (coords: 59) is configured as FC5_SCK */
  const uint32_t port0_pin20_config = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC5_RXD_SDA_MOSI */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN20_IDX, port0_pin20_config); /* PORT0 PIN20 (coords: 60) is configured as FC5_RXD_SDA_MOSI */
  const uint32_t port1_pin1_config = (
    IOCON_PIO_FUNC4 |                                        /* Pin is configured as FC5_SSEL2 */
    IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN1_IDX, port1_pin1_config); /* PORT1 PIN1 (coords: 15) is configured as FC5_SSEL2 */
}


#define DMA_ITRIG_INMUX10_IDX           10u   /*!< Inputmux DMA_ITRIG_INMUX register index 10 */
#define DMA_ITRIG_INMUX11_IDX           11u   /*!< Inputmux DMA_ITRIG_INMUX register index 11 */
#define DMA_ITRIG_INMUX12_IDX           12u   /*!< Inputmux DMA_ITRIG_INMUX register index 12 */
#define DMA_ITRIG_INMUX13_IDX           13u   /*!< Inputmux DMA_ITRIG_INMUX register index 13 */
#define PINTSEL0_IDX                     0u   /*!< Inputmux PINTSEL register index 0 */
#define PINTSEL1_IDX                     1u   /*!< Inputmux PINTSEL register index 1 */
#define PINTSEL2_IDX                     2u   /*!< Inputmux PINTSEL register index 2 */
#define PINTSEL3_IDX                     3u   /*!< Inputmux PINTSEL register index 3 */
#define PIO018_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO018_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO019_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO019_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO020_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO020_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO11_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO11_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
SPI5_DeinitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '15', peripheral: DMA0, signal: 'TRIG, 10', pin_signal: PIO1_1/SWO/SCT0_OUT4/FC5_SSEL2/FC4_TXD_SCL_MISO/ADC0_4, mode: no_init, invert: no_init, glitch_filter: no_init,
    open_drain: no_init}
  - {pin_num: '58', peripheral: DMA0, signal: 'TRIG, 11', pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
  - {pin_num: '59', peripheral: DMA0, signal: 'TRIG, 12', pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
  - {pin_num: '60', peripheral: DMA0, signal: 'TRIG, 13', pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI5_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void SPI5_DeinitPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_InputMux);                        /* Enables the clock for the input muxes. 0 = Disable; 1 = Enable.: 0x01u */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX10_IDX,kINPUTMUX_PinInt1ToDma); /* Pin interrupt 1 is selected as trigger input for DMA channel 10 */
  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX11_IDX,kINPUTMUX_PinInt2ToDma); /* Pin interrupt 2 is selected as trigger input for DMA channel 11 */
  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX12_IDX,kINPUTMUX_PinInt3ToDma); /* Pin interrupt 3 is selected as trigger input for DMA channel 12 */
  INPUTMUX_AttachSignal(INPUTMUX,DMA_ITRIG_INMUX13_IDX,kINPUTMUX_PinInt0ToDma); /* Pin interrupt 0 is selected as trigger input for DMA channel 13 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL0_IDX,kINPUTMUX_GpioPort0Pin20ToPintsel); /* PIO0_20 is selected for PINT input 0 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL1_IDX,kINPUTMUX_GpioPort1Pin1ToPintsel); /* PIO1_1 is selected for PINT input 1 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL2_IDX,kINPUTMUX_GpioPort0Pin18ToPintsel); /* PIO0_18 is selected for PINT input 2 */
  INPUTMUX_AttachSignal(INPUTMUX,PINTSEL3_IDX,kINPUTMUX_GpioPort0Pin19ToPintsel); /* PIO0_19 is selected for PINT input 3 */
  IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO018_FUNC_ALT0)                     /* Selects pin function.: PORT018 (pin 58) is configured as PIO0_18 */
      | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO019_FUNC_ALT0)                     /* Selects pin function.: PORT019 (pin 59) is configured as PIO0_19 */
      | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO020_FUNC_ALT0)                     /* Selects pin function.: PORT020 (pin 60) is configured as PIO0_20 */
      | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][1] = ((IOCON->PIO[1][1] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO11_FUNC_ALT0)                      /* Selects pin function.: PORT11 (pin 15) is configured as PIO1_1 */
      | IOCON_PIO_DIGIMODE(PIO11_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
