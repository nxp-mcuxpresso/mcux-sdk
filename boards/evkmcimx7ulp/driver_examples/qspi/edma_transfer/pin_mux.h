/*
 * Copyright 2020 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* PTA19 (number AB19), UART0_RX */
/* Routed pin properties */
#define BOARD_UART0_RX_PERIPHERAL                                        LPUART0   /*!< Peripheral name */
#define BOARD_UART0_RX_SIGNAL                                          lpuart_rx   /*!< Signal name */
#define BOARD_UART0_RX_PIN_NAME                                            PTA19   /*!< Routed pin name */
#define BOARD_UART0_RX_PIN_FUNCTION_ID                   IOMUXC_PTA19_LPUART0_RX   /*!< Pin function id */
#define BOARD_UART0_RX_LABEL                                          "UART0_RX"   /*!< Label */
#define BOARD_UART0_RX_NAME                                           "UART0_RX"   /*!< Identifier */

/* PTA18 (number AC19), UART0_TX */
/* Routed pin properties */
#define BOARD_UART0_TX_PERIPHERAL                                        LPUART0   /*!< Peripheral name */
#define BOARD_UART0_TX_SIGNAL                                          lpuart_tx   /*!< Signal name */
#define BOARD_UART0_TX_PIN_NAME                                            PTA18   /*!< Routed pin name */
#define BOARD_UART0_TX_PIN_FUNCTION_ID                   IOMUXC_PTA18_LPUART0_TX   /*!< Pin function id */
#define BOARD_UART0_TX_LABEL                                          "UART0_TX"   /*!< Label */
#define BOARD_UART0_TX_NAME                                           "UART0_TX"   /*!< Identifier */

/* PTB19 (number AD10), QSPIA_DATA0 */
/* Routed pin properties */
#define BOARD_QSPIA_DATA0_PERIPHERAL                                       QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_DATA0_SIGNAL                                      qspia_data   /*!< Signal name */
#define BOARD_QSPIA_DATA0_CHANNEL                                              0   /*!< Signal channel */
#define BOARD_QSPIA_DATA0_PIN_NAME                                         PTB19   /*!< Routed pin name */
#define BOARD_QSPIA_DATA0_PIN_FUNCTION_ID               IOMUXC_PTB19_QSPIA_DATA0   /*!< Pin function id */
#define BOARD_QSPIA_DATA0_LABEL                                    "QSPIA_DATA0"   /*!< Label */
#define BOARD_QSPIA_DATA0_NAME                                     "QSPIA_DATA0"   /*!< Identifier */

/* PTB18 (number AG10), QSPIA_DATA1 */
/* Routed pin properties */
#define BOARD_QSPIA_DATA1_PERIPHERAL                                       QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_DATA1_SIGNAL                                      qspia_data   /*!< Signal name */
#define BOARD_QSPIA_DATA1_CHANNEL                                              1   /*!< Signal channel */
#define BOARD_QSPIA_DATA1_PIN_NAME                                         PTB18   /*!< Routed pin name */
#define BOARD_QSPIA_DATA1_PIN_FUNCTION_ID               IOMUXC_PTB18_QSPIA_DATA1   /*!< Pin function id */
#define BOARD_QSPIA_DATA1_LABEL                                    "QSPIA_DATA1"   /*!< Label */
#define BOARD_QSPIA_DATA1_NAME                                     "QSPIA_DATA1"   /*!< Identifier */

/* PTB17 (number AF10), QSPIA_DATA2 */
/* Routed pin properties */
#define BOARD_QSPIA_DATA2_PERIPHERAL                                       QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_DATA2_SIGNAL                                      qspia_data   /*!< Signal name */
#define BOARD_QSPIA_DATA2_CHANNEL                                              2   /*!< Signal channel */
#define BOARD_QSPIA_DATA2_PIN_NAME                                         PTB17   /*!< Routed pin name */
#define BOARD_QSPIA_DATA2_PIN_FUNCTION_ID               IOMUXC_PTB17_QSPIA_DATA2   /*!< Pin function id */
#define BOARD_QSPIA_DATA2_LABEL                                    "QSPIA_DATA2"   /*!< Label */
#define BOARD_QSPIA_DATA2_NAME                                     "QSPIA_DATA2"   /*!< Identifier */

/* PTB16 (number AF9), QSPIA_DATA3 */
/* Routed pin properties */
#define BOARD_QSPIA_DATA3_PERIPHERAL                                       QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_DATA3_SIGNAL                                      qspia_data   /*!< Signal name */
#define BOARD_QSPIA_DATA3_CHANNEL                                              3   /*!< Signal channel */
#define BOARD_QSPIA_DATA3_PIN_NAME                                         PTB16   /*!< Routed pin name */
#define BOARD_QSPIA_DATA3_PIN_FUNCTION_ID               IOMUXC_PTB16_QSPIA_DATA3   /*!< Pin function id */
#define BOARD_QSPIA_DATA3_LABEL                                    "QSPIA_DATA3"   /*!< Label */
#define BOARD_QSPIA_DATA3_NAME                                     "QSPIA_DATA3"   /*!< Identifier */

/* PTB15 (number AF8), QSPIA_SCLK */
/* Routed pin properties */
#define BOARD_QSPIA_SCLK_PERIPHERAL                                        QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_SCLK_SIGNAL                                       qspia_sclk   /*!< Signal name */
#define BOARD_QSPIA_SCLK_PIN_NAME                                          PTB15   /*!< Routed pin name */
#define BOARD_QSPIA_SCLK_PIN_FUNCTION_ID                 IOMUXC_PTB15_QSPIA_SCLK   /*!< Pin function id */
#define BOARD_QSPIA_SCLK_LABEL                                      "QSPIA_SCLK"   /*!< Label */
#define BOARD_QSPIA_SCLK_NAME                                       "QSPIA_SCLK"   /*!< Identifier */

/* PTB8 (number AG6), QSPIA_SS0_B */
/* Routed pin properties */
#define BOARD_QSPIA_SS0_B_PERIPHERAL                                       QSPIA   /*!< Peripheral name */
#define BOARD_QSPIA_SS0_B_SIGNAL                                      qspia_ss_b   /*!< Signal name */
#define BOARD_QSPIA_SS0_B_CHANNEL                                              0   /*!< Signal channel */
#define BOARD_QSPIA_SS0_B_PIN_NAME                                          PTB8   /*!< Routed pin name */
#define BOARD_QSPIA_SS0_B_PIN_FUNCTION_ID                IOMUXC_PTB8_QSPIA_SS0_B   /*!< Pin function id */
#define BOARD_QSPIA_SS0_B_LABEL                                    "QSPIA_SS0_B"   /*!< Label */
#define BOARD_QSPIA_SS0_B_NAME                                     "QSPIA_SS0_B"   /*!< Identifier */

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


/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);                                 /*!< Function assigned for the core: Cortex-M4[cm4] */

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
