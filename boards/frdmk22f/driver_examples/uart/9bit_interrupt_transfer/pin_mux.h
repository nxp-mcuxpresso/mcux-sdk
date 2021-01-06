/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTE1 (number 2), J2[20]/UART1_RX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                       /* @} */

/*! @name PORTD2 (number 59), J1[2]/J8[P3]/uSD_SPI_MOSI
  @{ */
#define BOARD_SD_CARD_CMD_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SD_CARD_CMD_PIN 2U     /*!<@brief PORTD pin index: 2 */
                                     /* @} */

/*! @name PORTD3 (number 60), J1[4]/J8[P7]/SPI0_SIN/uSD_SPI_MISO
  @{ */
#define BOARD_SD_CARD_DAT0_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SD_CARD_DAT0_PIN 3U     /*!<@brief PORTD pin index: 3 */
                                      /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/