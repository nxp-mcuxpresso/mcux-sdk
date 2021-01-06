/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKE15Z256xxx7
package_id: MKE15Z256VLL7
mcu_data: ksdk2_0
processor_version: 0.0.9
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"



/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '81', peripheral: LPUART1, signal: RX, pin_signal: ADC1_SE4/TSI0_CH15/PTC6/LPUART1_RX}
  - {pin_num: '80', peripheral: LPUART1, signal: TX, pin_signal: ADC1_SE5/TSI0_CH16/PTC7/LPUART1_TX}
  - {pin_num: '6', peripheral: TSI, signal: 'CH, 2', pin_signal: TSI0_CH2/PTE10/CLKOUT/FXIO_D4/TRGMUX_OUT4}
  - {pin_num: '4', peripheral: GPIOD, signal: 'GPIO, 0', pin_signal: TSI0_CH4/PTD0/FTM0_CH2/LPSPI1_SCK/FTM2_CH0/FXIO_D0/TRGMUX_OUT1}
  - {pin_num: '33', peripheral: TSI, signal: 'CH, 6', pin_signal: TSI0_CH6/PTD5/FTM2_CH3/LPTMR0_ALT2/PWT_IN2/TRGMUX_IN7}
  - {pin_num: '21', peripheral: GPIOD, signal: 'GPIO, 16', pin_signal: PTD16/FTM0_CH1}
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
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTC6 (pin 81) is configured as LPUART1_RX */
    PORT_SetPinMux(PORTC, 6U, kPORT_MuxAlt2);

    /* PORTC7 (pin 80) is configured as LPUART1_TX */
    PORT_SetPinMux(PORTC, 7U, kPORT_MuxAlt2);

    /* PORTD0 (pin 4) is configured as PTD0 */
    PORT_SetPinMux(PORTD, 0U, kPORT_MuxAsGpio);

    /* PORTD16 (pin 21) is configured as PTD16 */
    PORT_SetPinMux(PORTD, 16U, kPORT_MuxAsGpio);

    /* PORTD5 (pin 33) is configured as TSI0_CH6 */
    PORT_SetPinMux(PORTD, 5U, kPORT_PinDisabledOrAnalog);

    /* PORTE10 (pin 6) is configured as TSI0_CH2 */
    PORT_SetPinMux(PORTE, 10U, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
