/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClEcc_WeierECC_Internal_GenerateDomainParams.h
 * @brief internal header of mcuxClEcc functionalities related to function MCUXCLECC_CUSTOMPARAMS
 */


#ifndef MCUXCLECC_WEIERECC_INTERNAL_GENERATEDOMAINPARAMS_H_
#define MCUXCLECC_WEIERECC_INTERNAL_GENERATEDOMAINPARAMS_H_


#include <internal/mcuxClEcc_Internal.h>


#define MCUXCLECC_CUSTOMPARAMS_OFFSET_PFULL                   (0u)
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_NFULL(byteLenP)         ((byteLenP) + MCUXCLPKC_WORDSIZE)
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_R2P(byteLenP, byteLenN) (MCUXCLECC_CUSTOMPARAMS_OFFSET_NFULL(byteLenP) + (byteLenN) + MCUXCLPKC_WORDSIZE)
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_R2N(byteLenP, byteLenN) (MCUXCLECC_CUSTOMPARAMS_OFFSET_R2P(byteLenP, byteLenN) + (byteLenP))
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_CP1(byteLenP, byteLenN) (MCUXCLECC_CUSTOMPARAMS_OFFSET_R2N(byteLenP, byteLenN) + (byteLenN))
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_CP2(byteLenP, byteLenN) (MCUXCLECC_CUSTOMPARAMS_OFFSET_CP1(byteLenP, byteLenN) + (byteLenP))
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_GX(byteLenP, byteLenN)  (MCUXCLECC_CUSTOMPARAMS_OFFSET_CP2(byteLenP, byteLenN) + (byteLenP))
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_GY(byteLenP, byteLenN)  (MCUXCLECC_CUSTOMPARAMS_OFFSET_GX(byteLenP, byteLenN) + (byteLenP))
#define MCUXCLECC_CUSTOMPARAMS_OFFSET_PP(byteLenP, byteLenN)  (MCUXCLECC_CUSTOMPARAMS_OFFSET_GY(byteLenP, byteLenN) + (byteLenP))

#define MCUXCLECC_CUSTOMPARAMS_SIZE_FIXED (sizeof(mcuxClEcc_Weier_DomainParams_t) + 2u * MCUXCLPKC_WORDSIZE)
#define MCUXCLECC_CUSTOMPARAMS_SIZE_NO_OF_PLEN (8u /* PFULL, R2P, CP1, CP2, GX, GY, PP */)
#define MCUXCLECC_CUSTOMPARAMS_SIZE_NO_OF_NLEN (2u /* NFULL, R2N */)


#endif /* MCUXCLECC_WEIERECC_INTERNAL_GENERATEDOMAINPARAMS_H_ */
