/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************

!!GlobalInfo

product: Pins v3.0

processor: MKL27Z64xxx4

package_id: MKL27Z64VLH4

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
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: LPUART0, signal: RX, pin_signal: PTA1/LPUART0_RX/TPM2_CH0}
  - {pin_num: '24', peripheral: LPUART0, signal: TX, pin_signal: PTA2/LPUART0_TX/TPM2_CH1}
  - {pin_num: '63', peripheral: FLEXIO, signal: 'D, 6', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/LPUART0_RX/I2C1_SDA/SPI1_MISO/FXIO0_D6}
  - {pin_num: '64', peripheral: FLEXIO, signal: 'D, 7', pin_signal: PTD7/SPI1_MISO/LPUART0_TX/I2C1_SCL/SPI1_MOSI/FXIO0_D7}
  - {pin_num: '9', peripheral: FLEXIO, signal: 'D, 4', pin_signal: ADC0_DP0/ADC0_SE0/PTE20/TPM1_CH0/LPUART0_TX/FXIO0_D4, slew_rate: fast}
  - {pin_num: '61', peripheral: SPI1, signal: PCS0, pin_signal: PTD4/LLWU_P14/SPI1_PCS0/UART2_RX/TPM0_CH4/FXIO0_D4, slew_rate: fast}
  - {pin_num: '10', peripheral: FLEXIO, signal: 'D, 5', pin_signal: ADC0_DM0/ADC0_SE4a/PTE21/TPM1_CH1/LPUART0_RX/FXIO0_D5, slew_rate: fast}
  - {pin_num: '62', peripheral: SPI1, signal: SCK, pin_signal: ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5}
  - {pin_num: '1', peripheral: SPI1, signal: MISO, pin_signal: PTE0/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA}
  - {pin_num: '2', peripheral: SPI1, signal: MOSI, pin_signal: PTE1/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL}
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
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTA1 (pin 23) is configured as LPUART0_RX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART0_RX_PORT, BOARD_INITPINS_DEBUG_UART0_RX_PIN, kPORT_MuxAlt2);

    /* PORTA2 (pin 24) is configured as LPUART0_TX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART0_TX_PORT, BOARD_INITPINS_DEBUG_UART0_TX_PIN, kPORT_MuxAlt2);

    /* PORTD4 (pin 61) is configured as SPI1_PCS0 */
    PORT_SetPinMux(BOARD_INITPINS_SDA_LED_PORT, BOARD_INITPINS_SDA_LED_PIN, kPORT_MuxAlt2);

    PORTD->PCR[4] = ((PORTD->PCR[4] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK)))

                     /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is
                      * configured as a digital output. */
                     | PORT_PCR_SRE(kPORT_FastSlewRate));

    /* PORTD5 (pin 62) is configured as SPI1_SCK */
    PORT_SetPinMux(PORTD, 5U, kPORT_MuxAlt2);

    /* PORTD6 (pin 63) is configured as FXIO0_D6 */
    PORT_SetPinMux(PORTD, 6U, kPORT_MuxAlt6);

    /* PORTD7 (pin 64) is configured as FXIO0_D7 */
    PORT_SetPinMux(PORTD, 7U, kPORT_MuxAlt6);

    /* PORTE0 (pin 1) is configured as SPI1_MISO */
    PORT_SetPinMux(BOARD_INITPINS_CLKOUT32K_PORT, BOARD_INITPINS_CLKOUT32K_PIN, kPORT_MuxAlt2);

    /* PORTE1 (pin 2) is configured as SPI1_MOSI */
    PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt2);

    /* PORTE20 (pin 9) is configured as FXIO0_D4 */
    PORT_SetPinMux(BOARD_INITPINS_ADC0_SE0_PORT, BOARD_INITPINS_ADC0_SE0_PIN, kPORT_MuxAlt6);

    PORTE->PCR[20] = ((PORTE->PCR[20] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK)))

                      /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is
                       * configured as a digital output. */
                      | PORT_PCR_SRE(kPORT_FastSlewRate));

    /* PORTE21 (pin 10) is configured as FXIO0_D5 */
    PORT_SetPinMux(PORTE, 21U, kPORT_MuxAlt6);

    PORTE->PCR[21] = ((PORTE->PCR[21] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK)))

                      /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is
                       * configured as a digital output. */
                      | PORT_PCR_SRE(kPORT_FastSlewRate));

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 Transmit Data Source Select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 Receive Data Source Select: LPUART_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
