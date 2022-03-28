/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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

#include <stdint.h>

#define SIZEOF_ECCCPUWA_T (4u * sizeof(uint32_t))

#define MCUXCLPKC_WORDSIZE  8u

#define ECC_KEYGEN_NO_OF_BUFFERS   0x18u
#define ECC_SIGN_NO_OF_BUFFERS   0x18u
#define ECC_VERIFY_NO_OF_BUFFERS   0x1Cu
#define ECC_POINTMULT_NO_OF_BUFFERS   0x18u
#define ECC_MONTDH_NO_OF_BUFFERS 0x19u
#define ECC_MONTDH_NO_OF_VIRTUALS  0x10u

#define MCUXCLECC_ALIGN_SIZE_PKC(size)  ((((size) + MCUXCLPKC_WORDSIZE - 1u) / MCUXCLPKC_WORDSIZE) * MCUXCLPKC_WORDSIZE)
#define ALIGNED_SIZE(byteLen)  ((((byteLen) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t))) * (sizeof(uint32_t)))

volatile uint8_t mcuxClEcc_PKC_wordsize[MCUXCLPKC_WORDSIZE];

volatile uint8_t mcuxClEcc_KeyGen_WaPKC_NoOfBuffers   [ECC_KEYGEN_NO_OF_BUFFERS];
volatile uint8_t mcuxClEcc_Sign_WaPKC_NoOfBuffers     [ECC_SIGN_NO_OF_BUFFERS];
volatile uint8_t mcuxClEcc_Verify_WaPKC_NoOfBuffers   [ECC_VERIFY_NO_OF_BUFFERS];
volatile uint8_t mcuxClEcc_PointMult_WaPKC_NoOfBuffers[ECC_POINTMULT_NO_OF_BUFFERS];


volatile uint8_t mcuxClEcc_Mont_DhKeyGeneration_WaCPU_SIZE[SIZEOF_ECCCPUWA_T + ALIGNED_SIZE(sizeof(uint16_t) * (ECC_MONTDH_NO_OF_BUFFERS + ECC_MONTDH_NO_OF_VIRTUALS))];
volatile uint8_t mcuxClEcc_Mont_DhKeyAgreement_WaCPU_SIZE[SIZEOF_ECCCPUWA_T + ALIGNED_SIZE(sizeof(uint16_t) * (ECC_MONTDH_NO_OF_BUFFERS + ECC_MONTDH_NO_OF_VIRTUALS))];
volatile uint8_t mcuxClEcc_Mont_DhKeyGeneration_WaPKC_SIZE[ECC_MONTDH_NO_OF_BUFFERS * (MCUXCLECC_ALIGN_SIZE_PKC(32u) + MCUXCLPKC_WORDSIZE)];
volatile uint8_t mcuxClEcc_Mont_DhKeyAgreement_WaPKC_SIZE[ECC_MONTDH_NO_OF_BUFFERS * (MCUXCLECC_ALIGN_SIZE_PKC(32u) + MCUXCLPKC_WORDSIZE)];
