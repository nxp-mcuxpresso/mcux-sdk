/*
 * Copyright 2018-2019 NXP.
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

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT4_FTM0FLT0_FTM 0x00u /*!<@brief FTM0 Fault 0 Select: FTM0_FLT0 pin */

/*! @name PORTC1 (number 71), MB_J11[A14]/MB_U12[18]/MB_PWM_AT/J4[A14]/PWM0
  @{ */
#define MB_PWM_AT_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PWM_AT_PIN 1U     /*!<@brief PORTC pin index: 1 */
                             /* @} */

/*! @name PORTC2 (number 72), MB_J11[A15]/MB_U12[12]/MB_PWM_AB/J4[A15]/PWM1
  @{ */
#define MB_PWM_AB_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PWM_AB_PIN 2U     /*!<@brief PORTC pin index: 2 */
                             /* @} */

/*! @name PORTC4 (number 76), MB_J11[A17]/MB_U12[13]/MB_PWM_BB/J4[A17]/PWM3
  @{ */
#define MB_PWM_BB_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PWM_BB_PIN 4U     /*!<@brief PORTC pin index: 4 */
                             /* @} */

/*! @name PORTC5 (number 77), MB_J11[A16]/MB_U12[19]/MB_PWM_BT/J4[A16]/PWM2
  @{ */
#define MB_PWM_BT_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PWM_BT_PIN 5U     /*!<@brief PORTC pin index: 5 */
                             /* @} */

/*! @name PORTD4 (number 97), MB_J11[A18]/MB_U12[20]/MB_PWM_CT/J4[A18]/PWM4
  @{ */
#define MB_PWM_CT_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_CT_PIN 4U     /*!<@brief PORTD pin index: 4 */
                             /* @} */

/*! @name PORTD5 (number 98), MB_J11[A19]/MB_U12[14]/MB_PWM_CB/J4[A19]/PWM5
  @{ */
#define MB_PWM_CB_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_CB_PIN 5U     /*!<@brief PORTD pin index: 5 */
                             /* @} */

/*! @name PORTA19 (number 51), MB_J11[A25]/MB_U12[11]/MB_TP28/MB_FAULT/MB_FAULT_1/MB_PFC_overcurrent/J4[A25]/FAULT_1
  @{ */
#define MB_FAULT_1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define MB_FAULT_1_PIN 19U    /*!<@brief PORTA pin index: 19 */
                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitMC_PWMPins(void);

/*! @name PORTC6 (number 78), MB_J11[B21]/MB_PFC_zc_2/J4[B21]/MB_TP_27
  @{ */
#define MB_PFC_ZC_2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PFC_ZC_2_PIN 6U     /*!<@brief PORTC pin index: 6 */
                               /* @} */

/*! @name PORTC7 (number 79), MB_J11[B22]/MB_PFC_zc_1/J4[B22]/MB_TP_26
  @{ */
#define MB_PFC_ZC_1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_PFC_ZC_1_PIN 7U     /*!<@brief PORTC pin index: 7 */
                               /* @} */

/*! @name PORTC13 (number 85), MB_J11[B28]/MB_Q3[1]/MB_Relay/J4[B28]/Relay
  @{ */
#define MB_RELAY_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define MB_RELAY_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_RELAY_PIN 13U    /*!<@brief PORTC pin index: 13 */
                            /* @} */

/*! @name PORTE5 (number 6), MB_J11[A22]/MB_U14[4]/MB_TP15/MB_PWM_PFC2/J4[A22]/PWM8
  @{ */
#define MB_PWM_PFC2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_PWM_PFC2_PIN 5U     /*!<@brief PORTE pin index: 5 */
                               /* @} */

/*! @name PORTE6 (number 7), MB_J11[A23]/MB_U14[2]/MB_TP12/MB_PWM_PFC1/J4[A23]/PWM9
  @{ */
#define MB_PWM_PFC1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_PWM_PFC1_PIN 6U     /*!<@brief PORTE pin index: 6 */
                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitPFCPins(void);

/*! @name ADC1_SE18 (number 26), MB_J11[B3]/MB_U8B[7]/MB_TP34/MB_I_sense_DCB/J4[B3]/I_dcb
  @{ */
/* @} */

/*! @name PORTB2 (number 55), MB_J11[B4]/MB_TP31/MB_V_sense_DCB/MB_DCB_Pos/J4[B4]/U_dcb
  @{ */
#define MB_U_DCB_PORT PORTB /*!<@brief PORT device name: PORTB */
#define MB_U_DCB_PIN 2U     /*!<@brief PORTB pin index: 2 */
                            /* @} */

/*! @name PORTC10 (number 82), MB_J11[B5]/MB_TP33/'MB_V_sense_DCB/2'/J4[B5]/'U_dcb/2'
  @{ */
#define MB_U_DCB_HALF_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_U_DCB_HALF_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                 /* @} */

/*! @name PORTC11 (number 83), MB_J11[B9]/MB_U12[2]/MB_TP38/MB_IPM_temp/J4[B9]/Temp_IPM
  @{ */
#define MB_TEMP_IPM_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_TEMP_IPM_PIN 11U    /*!<@brief PORTC pin index: 11 */
                               /* @} */

/*! @name PORTB0 (number 53), MB_J11[A3]/MB_U11A[1]/MB_TP45/MB_I_sense_A/J4[A3]/I_phA
  @{ */
#define MB_I_PH_A_PORT PORTB /*!<@brief PORT device name: PORTB */
#define MB_I_PH_A_PIN 0U     /*!<@brief PORTB pin index: 0 */
                             /* @} */

/*! @name PORTB1 (number 54), MB_J11[A5]/MB_U8A[1]/MB_TP37/MB_I_sense_C/J4[A5]/I_phC
  @{ */
#define MB_I_PH_C_PORT PORTB /*!<@brief PORT device name: PORTB */
#define MB_I_PH_C_PIN 1U     /*!<@brief PORTB pin index: 1 */
                             /* @} */

/*! @name ADC1_DP0 (number 20), MB_J11[A4]/MB_U11B[7]/MB_TP40/MB_I_sense_B/J4[A4]/I_phB
  @{ */
/* @} */

/*! @name ADC1_DP3 (number 18), MB_J11[A5]/MB_U8A[1]/MB_TP37/MB_I_sense_C/J4[A5]/I_phC
  @{ */
/* @} */

/*! @name ADC0_SE23 (number 27), MB_J11[A7]/MB_TP18/MB_Vin/J4[A7]/V_in
  @{ */
/* @} */

/*! @name ADC1_SE23 (number 28), MB_J11[A7]/MB_TP18/MB_Vin/J4[A7]/V_in
  @{ */
/* @} */

/*! @name PORTC8 (number 80), MB_J11[A8]/MB_U2B[7]/MB_TP14/MB_Ipfc1/J4[A8]/I_pfc1
  @{ */
#define MB_I_PFC1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_I_PFC1_PIN 8U     /*!<@brief PORTC pin index: 8 */
                             /* @} */

/*! @name PORTC9 (number 81), MB_J11[A9]/MB_U2A[1]/MB_TP5/MB_Ipfc2/J4[A9]/I_pfc2
  @{ */
#define MB_I_PFC2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_I_PFC2_PIN 9U     /*!<@brief PORTC pin index: 9 */
                             /* @} */

/*! @name PORTC3 (number 73), MB_J11[A6]/MB_TP16/MB_TACHO/J4[A6]/TACHO
  @{ */
#define MB_TACHO_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_TACHO_PIN 3U     /*!<@brief PORTC pin index: 3 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitANA_SENSPins(void);

/*! @name ADC0_DM0 (number 19), MB_J11[B6]/MB_TP44/MB_BEMF_sense_A/MB_Phase_A/J4[B6]/BEMF_A
  @{ */
/* @} */

/*! @name ADC1_DM0 (number 21), MB_J11[B7]/MB_TP43/MB_BEMF_sense_B/MB_Phase_B/J4[B7]/BEMF_B
  @{ */
/* @} */

/*! @name ADC1_DM1 (number 17), MB_J11[B8]/MB_TP41/MB_BEMF_sense_C/MB_Phase_C/J4[B8]/BEMF_C
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitBEMFPins(void);

/*! @name PORTA12 (number 42), MB_J9[3]/MB_J11[B14]/MB_TP13/MB_ENC_PhaseA/J4[B14]/TM0
  @{ */
#define MB_ENC_PHASE_A_PORT PORTA /*!<@brief PORT device name: PORTA */
#define MB_ENC_PHASE_A_PIN 12U    /*!<@brief PORTA pin index: 12 */
                                  /* @} */

/*! @name PORTA13 (number 43), MB_J9[4]/MB_J11[B15]/MB_TP17/MB_ENC_PhaseB/J4[B15]/TM1
  @{ */
#define MB_ENC_PHASE_B_PORT PORTA /*!<@brief PORT device name: PORTA */
#define MB_ENC_PHASE_B_PIN 13U    /*!<@brief PORTA pin index: 13 */
                                  /* @} */

/*! @name PORTD6 (number 99), MB_J9[5]/MB_J11[B16]/MB_TP19/MB_ENC_Index/J4[B16]/TM2
  @{ */
#define MB_ENC_INDEX_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define MB_ENC_INDEX_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_ENC_INDEX_PIN 6U     /*!<@brief PORTD pin index: 6 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitENCPins(void);

/*! @name PORTC0 (number 70), MB_J11[B25]/MB_U9[2]/MB_TP_35/MB_MCU_BRAKE/J4[B25]/MCU_BRAKE
  @{ */
#define MB_MCU_BRAKE_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define MB_MCU_BRAKE_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_MCU_BRAKE_PIN 0U     /*!<@brief PORTC pin index: 0 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitBRAKEPins(void);

/*! @name PORTE16 (number 10), MB_J1[3]/MB_J11[B26]/MB_U1[13]/MB_U3[25]/MB_TP3/MB_TP7/MB_TxD/J4[B26]/TxD
  @{ */
#define MB_TXD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_TXD_PIN 16U    /*!<@brief PORTE pin index: 16 */
                          /* @} */

/*! @name PORTE17 (number 11), MB_J3[2]/MB_J11[B27]/MB_U1[12]/MB_U3[26]/MB_TP2/MB_TP10/MB_RxD/J4[B27]/RxD/MISO/TP19
  @{ */
#define MB_RXD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_RXD_PIN 17U    /*!<@brief PORTE pin index: 17 */
                          /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitUSB_UARTPins(void);

#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTE1 (number 2), MB_J2[4]/MB_J3[4]/MB_J11[A32]/MB_RxD_1/MB_RxD_EXT/J4[A32]/RxD1
  @{ */
#define MB_RXD_1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_RXD_1_PIN 1U     /*!<@brief PORTE pin index: 1 */
                            /* @} */

/*! @name PORTE0 (number 1), MB_J1[1]/MB_J2[3]/MB_J11[A31]/MB_TxD_1/MB_TxD_EXT/J4[A31]/TxD1
  @{ */
#define MB_TXD_1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_TXD_1_PIN 0U     /*!<@brief PORTE pin index: 0 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitEXT_UARTPins(void);

#define SOPT7_ADC0ALTTRGEN_PDB 0x00u /*!<@brief ADC0 alternate trigger enable: PDB trigger selected for ADC0. */
#define SOPT7_ADC1ALTTRGEN_PDB 0x00u /*!<@brief ADC1 alternate trigger enable: PDB trigger selected for ADC1 */

/*! @name PORTC12 (number 84), MB_J11[A26]/MB_U9[2]/MB_TP35/MB_FAULT_2/MB_Over-voltage_FAULT/J4[A26]/FAULT_2
  @{ */
#define MB_FAULT_2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define MB_FAULT_2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_FAULT_2_PIN 12U    /*!<@brief PORTC pin index: 12 */
                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitMISCPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (number 62), U2[24]/U6[13]/TxD_sda/UART_TX_TGTMCU
  @{ */
#define BOARD_UART_TX_TGTMCU_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_UART_TX_TGTMCU_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                        /* @} */

/*! @name PORTB17 (number 63), U2[25]/U6[14]/RxD_sda/UART_RX_TGTMCU
  @{ */
#define BOARD_UART_RX_TGTMCU_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_UART_RX_TGTMCU_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                        /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name PORTB19 (number 65), MB_J11[B20]/MB_U9[4]/MB_USER_LED/J4[B20]/USER_LED
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_LED_GREEN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_LED_GREEN_PIN 19U    /*!<@brief PORTB pin index: 19 */
                                   /* @} */

/*! @name PORTA5 (number 39), USER_LED_2
  @{ */
#define BOARD_LED_RED_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_LED_RED_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_LED_RED_PIN 5U     /*!<@brief PORTA pin index: 5 */
                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDSPins(void);

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
