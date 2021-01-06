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
processor: MK28FN2M0Axxx15
package_id: MK28FN2M0AVMI15
mcu_data: ksdk2_0
processor_version: 0.0.8
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
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: A7, peripheral: LPUART0, signal: RX, pin_signal: PTC25/LPUART0_RX/FB_A4/SDRAM_D4/QSPI0A_SCLK}
  - {pin_num: B7, peripheral: LPUART0, signal: TX, pin_signal: PTC24/LPUART0_TX/FB_A5/SDRAM_D5/QSPI0A_DATA3}
  - {pin_num: D5, peripheral: LPUART1, signal: RX, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART1_RX/FB_A16/FXIO0_D24}
  - {pin_num: D4, peripheral: LPUART1, signal: TX, pin_signal: PTD9/I2C0_SDA/LPUART1_TX/FB_A17/FXIO0_D25}
  - {pin_num: D3, peripheral: LPUART1, signal: RTS, pin_signal: PTD10/LPUART1_RTS_b/FB_A18/FXIO0_D26}
  - {pin_num: C2, peripheral: LPUART1, signal: CTS, pin_signal: PTD11/LLWU_P25/SPI2_PCS0/LPUART1_CTS_b/FB_A19/FXIO0_D27}
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
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* PORTC24 (pin B7) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTC, 24U, kPORT_MuxAlt3);

    /* PORTC25 (pin A7) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTC, 25U, kPORT_MuxAlt3);

    /* PORTD10 (pin D3) is configured as LPUART1_RTS_b */
    PORT_SetPinMux(PORTD, 10U, kPORT_MuxAlt3);

    /* PORTD11 (pin C2) is configured as LPUART1_CTS_b */
    PORT_SetPinMux(PORTD, 11U, kPORT_MuxAlt3);

    /* PORTD8 (pin D5) is configured as LPUART1_RX */
    PORT_SetPinMux(PORTD, 8U, kPORT_MuxAlt3);

    /* PORTD9 (pin D4) is configured as LPUART1_TX */
    PORT_SetPinMux(PORTD, 9U, kPORT_MuxAlt3);

    SIM->SOPT5 =
        ((SIM->SOPT5 &
          /* Mask bits to zero which are setting */
          (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK | SIM_SOPT5_LPUART1TXSRC_MASK | SIM_SOPT5_LPUART1RXSRC_MASK)))

         /* LPUART0 transmit data source select: LPUART0_TX pin. */
         | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

         /* LPUART0 receive data source select: LPUART0_RX pin. */
         | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX)

         /* LPUART1 transmit data source select: LPUART1_TX pin. */
         | SIM_SOPT5_LPUART1TXSRC(SOPT5_LPUART1TXSRC_LPUART_TX)

         /* LPUART1 receive data source select: LPUART1_RX pin. */
         | SIM_SOPT5_LPUART1RXSRC(SOPT5_LPUART1RXSRC_LPUART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
