/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* FC0_RXD_SDA_MOSI (coord B13), U24[13]/P0_29-ISP_FC0_RXD */
#define BOARD_ISP_FC0_RXD_PERIPHERAL                                   FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_ISP_FC0_RXD_SIGNAL                                    RXD_SDA_MOSI   /*!< FLEXCOMM0 signal: RXD_SDA_MOSI */
#define BOARD_ISP_FC0_RXD_PIN_NAME                              FC0_RXD_SDA_MOSI   /*!< Pin name */
#define BOARD_ISP_FC0_RXD_LABEL                      "U24[13]/P0_29-ISP_FC0_RXD"   /*!< Label */
#define BOARD_ISP_FC0_RXD_NAME                                     "ISP_FC0_RXD"   /*!< Identifier name */

/* FC0_TXD_SCL_MISO (coord A2), U24[12]/P0_30-ISP_FC0_TXD */
#define BOARD_ISP_FC0_TXD_PERIPHERAL                                   FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_ISP_FC0_TXD_SIGNAL                                    TXD_SCL_MISO   /*!< FLEXCOMM0 signal: TXD_SCL_MISO */
#define BOARD_ISP_FC0_TXD_PIN_NAME                              FC0_TXD_SCL_MISO   /*!< Pin name */
#define BOARD_ISP_FC0_TXD_LABEL                      "U24[12]/P0_30-ISP_FC0_TXD"   /*!< Label */
#define BOARD_ISP_FC0_TXD_NAME                                     "ISP_FC0_TXD"   /*!< Identifier name */

/* SWO (coord P2), U16[12]/SWO_TRGT */
#define BOARD_SWO_TRGT_PERIPHERAL                                            SWD   /*!< Device name: SWD */
#define BOARD_SWO_TRGT_SIGNAL                                                SWO   /*!< SWD signal: SWO */
#define BOARD_SWO_TRGT_PIN_NAME                                              SWO   /*!< Pin name */
#define BOARD_SWO_TRGT_LABEL                                  "U16[12]/SWO_TRGT"   /*!< Label */
#define BOARD_SWO_TRGT_NAME                                           "SWO_TRGT"   /*!< Identifier name */

/*!
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M4F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
