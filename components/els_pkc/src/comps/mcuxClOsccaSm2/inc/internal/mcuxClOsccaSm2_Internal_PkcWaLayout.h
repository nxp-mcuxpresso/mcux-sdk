/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * @file  mcuxClOsccaSm2_Internal_PkcWaLayout.h
 * @brief internal header of mcuxClOccaEcc SM2 PKC workarea layout
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_PKCWALAYOUT_H_
#define MCUXCLOSCCASM2_INTERNAL_PKCWALAYOUT_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClOsccaPkc.h>
#include <internal/mcuxClOsccaPkc_Macros.h>

/*****************************************************************************/
/** PKC workarea memory layout used for SM2 API functions.                   */
/*****************************************************************************/
#define TI_modulus          (0U)
#define TI_xa               (1U)            // the result point
#define TI_ya               (2U)
#define TI_z1               (3U)
#define TI_x0               (4U)
#define TI_y0               (5U)
#define TI_key              (6U)
#define TI_n                (7U)
#define TI_modulusf         (8U)
#define TI_a                (9U)
#define TI_s                (10U)             // temp use
#define TI_t                (11U)             // temp use
#define TI_u                (12U)             // temp use
#define TI_v                (13U)             // temp use
#define TI_moduluss         (14U)
#define TI_z                (15U)
#define TI_scalar           (16U)
#define TI_sx0              (17U)
#define TI_sy0              (18U)
#define TI_sz0_dash         (19U)
#define TI_sx1              (20U)
#define TI_sy1              (21U)
#define TI_sz1_dash         (22U)
#define TI_sx               (23U)
#define TI_sy               (24U)
#define TI_y_neg            (25U)
#define TI_q2               (26U)
#define TI_nf               (27U)
#define TI_b                (28U)
#define TI_tmpx             (29U)
#define TI_tmpy             (30U)
#define TI_tmpz             (31U)
#define TI_scalar1          (32U)
#define TI_scalar2          (33U)
#define TI_n2               (34U)
#define TI_nshift           (35U)
#define TI_tmpconz          (36U)
#define TI_const0           (37U)
#define TI_indexmax         (38U)

// TI alias for sign
#define TI_k          TI_scalar          // random k
#define TI_kGx        TI_xa              // x component of k times G produced by Point Multiplication
#define TI_kGy        TI_ya              // y component of k times G produced by Point Multiplication
#define TI_e          TI_sy              // digest
#define TI_d          TI_sz1_dash        // private key
#define TI_sig_r      TI_z
#define TI_sig_s      TI_b
#define TI_d_inv      TI_sz0_dash        //the inverse of private key
#define TI_kDash      TI_tmpx
#define TI_dDash      TI_tmpz
#define TI_A          TI_y_neg
#define TI_T          TI_scalar1
#define TI_phi        TI_sx1
#define TI_phi1       TI_sy1
#define TI_phi2       TI_tmpy
#define TI_R          TI_a

#define MCUXCLOSCCASM2_GET_PKCBUFFER_BASE_ADDR(opsbase, buffernums) (((uint32_t)(opsbase) + (buffernums)*sizeof(uint16_t) + MCUXCLOSCCAPKC_WORD_SIZE - 1) & (~(MCUXCLOSCCAPKC_WORD_SIZE-1)))

/*********************************************************************************************/
/** @brief  Definition of number of buffers used in PKC workarea for SM2 API                 */
/** @brief  functions                                                                        */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_NO_OF_BUFFERS                       (30U)

/*********************************************************************************************/
/** @brief  Definition of number of virtual buffers used in PKC workarea for                 */
/** @brief  SM2 API functions                                                                */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_NO_OF_VIRTUALS                      (8U)

/*****************************************************************************/
/** PKC workarea memory layout used for SM2 invert-private-key function      */
/*****************************************************************************/
#define TI_privateKey               (0U)
#define TI_privateKeyInverse        (1U)
#define TI_m                        (2U)
#define TI_ms                       (3U)
#define TI_tmp0                     (4U)
#define TI_tmp1                     (5U)
#define TI_tmp2                     (6U)
#define TI_tmp3                     (7U)
#define TI_tmp4                     (8U)
#define num_operands                (9U)

/*********************************************************************************************/
/** @brief  Definition of number of buffers used in PKC workarea for SM2                     */
/** @brief  invert-private-key function                                                      */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_INVERTPRIVATEKEY_NO_OF_BUFFERS      (9U)

/*********************************************************************************************/
/** @brief  Definition of number of virtual buffers used in PKC workarea for SM2             */
/** @brief  invert-private-key function                                                      */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_INVERTPRIVATEKEY_NO_OF_VIRTUALS     (0U)

#endif /* MCUXCLOSCCASM2_INTERNAL_PKCWALAYOUT_H_ */
