/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "board.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* QSPI1A_DATA1 (coord D14), BB_AUDIN_RST_B(QSPI1A_DATA1)/J20C[32] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_AUDIN_RST_B_PERIPHERAL                     LSIO__GPIO4   /*!< Peripheral name */
#define BOARD_INITPINS_BB_AUDIN_RST_B_SIGNAL                             gpio_io   /*!< Signal name */
#define BOARD_INITPINS_BB_AUDIN_RST_B_CHANNEL                                 25   /*!< Signal channel */
#define BOARD_INITPINS_BB_AUDIN_RST_B_PIN_NAME                      QSPI1A_DATA1   /*!< Routed pin name */
#define BOARD_INITPINS_BB_AUDIN_RST_B_PIN_FUNCTION_ID          SC_P_QSPI1A_DATA1   /*!< Pin function id */
#define BOARD_INITPINS_BB_AUDIN_RST_B_LABEL "BB_AUDIN_RST_B(QSPI1A_DATA1)/J20C[32]" /*!< Label */
#define BOARD_INITPINS_BB_AUDIN_RST_B_NAME                      "BB_AUDIN_RST_B"   /*!< Identifier */
#define BOARD_INITPINS_BB_AUDIN_RST_B_DIRECTION              kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_BB_AUDIN_RST_B_GPIO                           LSIO__GPIO4   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_BB_AUDIN_RST_B_GPIO_PIN                               25U   /*!< GPIO pin number */
#define BOARD_INITPINS_BB_AUDIN_RST_B_GPIO_PIN_MASK                  (1U << 25U)   /*!< GPIO pin mask */

/* UART0_RTS_B (number AU45), BB_UART2_RX/J20A[28] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_UART2_RX_PERIPHERAL                         DMA__UART2   /*!< Peripheral name */
#define BOARD_INITPINS_BB_UART2_RX_SIGNAL                                uart_rx   /*!< Signal name */
#define BOARD_INITPINS_BB_UART2_RX_PIN_NAME                          UART0_RTS_B   /*!< Routed pin name */
#define BOARD_INITPINS_BB_UART2_RX_PIN_FUNCTION_ID              SC_P_UART0_RTS_B   /*!< Pin function id */
#define BOARD_INITPINS_BB_UART2_RX_LABEL                  "BB_UART2_RX/J20A[28]"   /*!< Label */
#define BOARD_INITPINS_BB_UART2_RX_NAME                            "BB_UART2_RX"   /*!< Identifier */

/* UART0_CTS_B (number AW49), BB_UART2_TX/J20A[29] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_UART2_TX_PERIPHERAL                         DMA__UART2   /*!< Peripheral name */
#define BOARD_INITPINS_BB_UART2_TX_SIGNAL                                uart_tx   /*!< Signal name */
#define BOARD_INITPINS_BB_UART2_TX_PIN_NAME                          UART0_CTS_B   /*!< Routed pin name */
#define BOARD_INITPINS_BB_UART2_TX_PIN_FUNCTION_ID              SC_P_UART0_CTS_B   /*!< Pin function id */
#define BOARD_INITPINS_BB_UART2_TX_LABEL                  "BB_UART2_TX/J20A[29]"   /*!< Label */
#define BOARD_INITPINS_BB_UART2_TX_NAME                            "BB_UART2_TX"   /*!< Identifier */

/* M41_I2C0_SCL (number AR45), BB_M41_I2C0_1V8_SCL/J20A[22] */
/* Routed pin properties */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_PERIPHERAL         M41__I2C0   /*!< Peripheral name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_SIGNAL               i2c_scl   /*!< Signal name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_PIN_NAME        M41_I2C0_SCL   /*!< Routed pin name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_PIN_FUNCTION_ID SC_P_M41_I2C0_SCL /*!< Pin function id */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_LABEL "BB_M41_I2C0_1V8_SCL/J20A[22]" /*!< Label */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SCL_NAME   "BB_M41_I2C0_1V8_SCL"   /*!< Identifier */

/* M41_I2C0_SDA (number AU49), BB_M41_I2C0_1V8_SDA/J20A[23] */
/* Routed pin properties */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_PERIPHERAL         M41__I2C0   /*!< Peripheral name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_SIGNAL               i2c_sda   /*!< Signal name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_PIN_NAME        M41_I2C0_SDA   /*!< Routed pin name */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_PIN_FUNCTION_ID SC_P_M41_I2C0_SDA /*!< Pin function id */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_LABEL "BB_M41_I2C0_1V8_SDA/J20A[23]" /*!< Label */
#define BOARD_I2C_CONFIGUREPINS_BB_M41_I2C0_1V8_SDA_NAME   "BB_M41_I2C0_1V8_SDA"   /*!< Identifier */

/* ESAI0_FSR (number AW9), BB_ESAI0_FSR/J20D[24] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_PERIPHERAL              AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_SIGNAL                    esai_fsr   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_PIN_NAME                 ESAI0_FSR   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_PIN_FUNCTION_ID     SC_P_ESAI0_FSR   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_LABEL      "BB_ESAI0_FSR/J20D[24]"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FSR_NAME                "BB_ESAI0_FSR"   /*!< Identifier */

/* ESAI0_FST (number BG9), BB_ESAI0_FST/J20D[20] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_PERIPHERAL              AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_SIGNAL                    esai_fst   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_PIN_NAME                 ESAI0_FST   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_PIN_FUNCTION_ID     SC_P_ESAI0_FST   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_LABEL      "BB_ESAI0_FST/J20D[20]"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_FST_NAME                "BB_ESAI0_FST"   /*!< Identifier */

/* ESAI0_SCKR (number BB8), BB_ESAI0_SCKR/J20D[17] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_PERIPHERAL             AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_SIGNAL                  esai_sckr   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_PIN_NAME               ESAI0_SCKR   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_PIN_FUNCTION_ID   SC_P_ESAI0_SCKR   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_LABEL    "BB_ESAI0_SCKR/J20D[17]"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKR_NAME              "BB_ESAI0_SCKR"   /*!< Identifier */

/* ESAI0_SCKT (number AY8), BB_ESAI0_SCKT/J20D[18] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_PERIPHERAL             AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_SIGNAL                  esai_sckt   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_PIN_NAME               ESAI0_SCKT   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_PIN_FUNCTION_ID   SC_P_ESAI0_SCKT   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_LABEL    "BB_ESAI0_SCKT/J20D[18]"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_SCKT_NAME              "BB_ESAI0_SCKT"   /*!< Identifier */

/* ESAI0_TX0 (number BA9), BB_ESAI0_TX0/J20D[21] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_PERIPHERAL              AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_SIGNAL                     esai_tx   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_CHANNEL                          0   /*!< Signal channel */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_PIN_NAME                 ESAI0_TX0   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_PIN_FUNCTION_ID     SC_P_ESAI0_TX0   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_LABEL      "BB_ESAI0_TX0/J20D[21]"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX0_NAME                "BB_ESAI0_TX0"   /*!< Identifier */

/* ESAI0_TX5_RX0 (number AU7), BB_ESAI0_TX5_RX0/J20D[12] */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_PERIPHERAL          AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_SIGNAL             esai_tx5_rx   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_CHANNEL                      0   /*!< Signal channel */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_PIN_NAME         ESAI0_TX5_RX0   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_PIN_FUNCTION_ID SC_P_ESAI0_TX5_RX0 /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_LABEL "BB_ESAI0_TX5_RX0/J20D[12]" /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_BB_ESAI0_TX5_RX0_NAME        "BB_ESAI0_TX5_RX0"   /*!< Identifier */

/* MCLK_OUT0 (number BD4), MCLK_OUT0 */
/* Routed pin properties */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_PERIPHERAL                 AUD__ESAI0   /*!< Peripheral name */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_SIGNAL                 esai_tx_hf_clk   /*!< Signal name */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_PIN_NAME                    MCLK_OUT0   /*!< Routed pin name */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_PIN_FUNCTION_ID        SC_P_MCLK_OUT0   /*!< Pin function id */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_LABEL                     "MCLK_OUT0"   /*!< Label */
#define BOARD_ESAI_CONFIGUREPINS_MCLK_OUT0_NAME                      "MCLK_OUT0"   /*!< Identifier */

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
 * @param ipc scfw ipchandle.
 *
 */
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[cm4_core1] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void BOARD_I2C_ConfigurePins(sc_ipc_t ipc);                /*!< Function assigned for the core: Cortex-M4F[cm4_core1] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void BOARD_ESAI_ConfigurePins(sc_ipc_t ipc);               /*!< Function assigned for the core: Cortex-M4F[cm4_core1] */

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
