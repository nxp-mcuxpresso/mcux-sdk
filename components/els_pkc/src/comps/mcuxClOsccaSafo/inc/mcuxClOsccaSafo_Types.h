/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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
 * @file  mcuxClOsccaSafo_Types.h
 * @brief Type and associated constant definitions of the mcuxClOsccaSafo component.
 */

#ifndef MCUXCLOSCCASAFO_TYPES_H_
#define MCUXCLOSCCASAFO_TYPES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOsccaSafo_Sfr_Ctrl.h>
#include <mcuxClOsccaSafo_Sfr_RegBank.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClOsccaSafo_Types mcuxClOsccaSafo_Types
 * @brief Defines the types and associated constants of the @ref mcuxClOsccaSafo component.
 * @ingroup mcuxClOsccaSafo
 * @{
 */

/**
 * @brief SAFO status code
 *
 * This type provides information about the status of the SAFO operation that
 * has been performed.
 */
typedef uint32_t mcuxClOsccaSafo_Status_t;

/**
 * @}
 */ /* MCUXCLOSCCASAFO_STATUS_ */


/**********************************************************/
/* Helper macros                                          */
/**********************************************************/
/**
 * @addtogroup MCUXCLOSCCASAFO_MISC_
 * mcuxClOsccaSafo misc macros and definitions
 * @{
 */
/** Datout update handling */
#define MCUXCLOSCCASAFO_DRV_CTRL_DATOUT_RES_END_UP     (MCUXCLOSCCASAFO_SFR_CTRL_DATOUT_RES_END_UP)

#define MCUXCLOSCCASAFO_DRV_CTRL_END_UP   (MCUXCLOSCCASAFO_SFR_CTRL_END_UP)
#define MCUXCLOSCCASAFO_DRV_CTRL_NO_UP    (MCUXCLOSCCASAFO_SFR_CTRL_NO_UP)

#define MCUXCLOSCCASAFO_DRV_CTRL_INVALID  (MCUXCLOSCCASAFO_SFR_CTRL_INVALID)
#define MCUXCLOSCCASAFO_DRV_CTRL_GFMUL    (MCUXCLOSCCASAFO_SFR_CTRL_GFMUL)
#define MCUXCLOSCCASAFO_DRV_CTRL_CMAC     (MCUXCLOSCCASAFO_SFR_CTRL_CMAC)
#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
#define MCUXCLOSCCASAFO_DRV_CTRL_SM3      (MCUXCLOSCCASAFO_SFR_CTRL_SM3)
#endif
#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
#define MCUXCLOSCCASAFO_DRV_CTRL_SM4      (MCUXCLOSCCASAFO_SFR_CTRL_SM4)
#endif

/** Base index of data input */
#define MCUXCLOSCCASAFO_DRV_DATIN0_INDEX    (MCUXCLOSCCASAFO_SFR_DATIN0_INDEX)
#define MCUXCLOSCCASAFO_DRV_DATIN1_INDEX    (MCUXCLOSCCASAFO_SFR_DATIN1_INDEX)
#define MCUXCLOSCCASAFO_DRV_DATIN2_INDEX    (MCUXCLOSCCASAFO_SFR_DATIN2_INDEX)
#define MCUXCLOSCCASAFO_DRV_DATIN3_INDEX    (MCUXCLOSCCASAFO_SFR_DATIN3_INDEX)

/** Base index of data output, starting from DATIN0A */
#define MCUXCLOSCCASAFO_DRV_DATOUT_INDEX    (MCUXCLOSCCASAFO_SFR_DATOUT_INDEX)

/** Address of an SAFO DATA (DATIN or DATOUT) SFR */
#define MCUXCLOSCCASAFO_DRV_DATAREG_ADDRESS(datIndex) (mcuxClOsccaSafo_Sfr_getAddrOfDataReg(datIndex))

/** Base index of key input */
#define MCUXCLOSCCASAFO_DRV_KEY0_INDEX    (MCUXCLOSCCASAFO_SFR_KEY0_INDEX)
#define MCUXCLOSCCASAFO_DRV_KEY1_INDEX    (MCUXCLOSCCASAFO_SFR_KEY1_INDEX)
#define MCUXCLOSCCASAFO_DRV_KEY2_INDEX    (MCUXCLOSCCASAFO_SFR_KEY2_INDEX)
#define MCUXCLOSCCASAFO_DRV_KEY3_INDEX    (MCUXCLOSCCASAFO_SFR_KEY3_INDEX)

/** Address of an SAFO KEY SFR */
#define MCUXCLOSCCASAFO_DRV_KEYREG_ADDRESS(keyIndex) (mcuxClOsccaSafo_Sfr_getAddrOfKeyReg(keyIndex))

/** Input selection and pre-processing handling */
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATIN0            (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATIN0)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATIN1            (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATIN1)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATIN2            (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATIN2)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATIN0_XOR_DATOUT (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATIN0_XOR_DATOUT)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATIN2_XOR_DATOUT (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATIN2_XOR_DATOUT)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_DATOUT            (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_DATOUT)
#define MCUXCLOSCCASAFO_DRV_CTRL_INSEL_INDEX(index)      (MCUXCLOSCCASAFO_SFR_CTRL_INSEL_INDEX(index))

/** Output selection and post-processing handling */
#define MCUXCLOSCCASAFO_DRV_CTRL_OUTSEL_RES               (MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_RES)
#define MCUXCLOSCCASAFO_DRV_CTRL_OUTSEL_RES_XOR_DATIN0    (MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_RES_XOR_DATIN0)
#define MCUXCLOSCCASAFO_DRV_CTRL_OUTSEL_RES_XOR_DATIN1    (MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_RES_XOR_DATIN1)
#define MCUXCLOSCCASAFO_DRV_CTRL_OUTSEL_RES_XOR_DATIN2    (MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_RES_XOR_DATIN2)
#define MCUXCLOSCCASAFO_DRV_CTRL_OUTSEL_RES_INDEX(index)  (MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_RES_INDEX(index))

/** Encryption/Decryption mode selection */
#define MCUXCLOSCCASAFO_DRV_CTRL_ENC                   (MCUXCLOSCCASAFO_SFR_CTRL_ENC)
#define MCUXCLOSCCASAFO_DRV_CTRL_DEC                   (MCUXCLOSCCASAFO_SFR_CTRL_DEC)

/** Start operation trigger */
#define MCUXCLOSCCASAFO_DRV_CTRL_START                   (MCUXCLOSCCASAFO_SFR_CTRL_START)

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
#define MCUXCLOSCCASAFO_DRV_CTRL_SM4_EN               (MCUXCLOSCCASAFO_SFR_CTRL_SM4_EN)
#endif

#define MCUXCLOSCCASAFO_DRV_CTRL_INKEYSEL(keyIndex)    (MCUXCLOSCCASAFO_SFR_CTRL_INKEYSEL(keyIndex))

/** Selection of fixed key */
#define MCUXCLOSCCASAFO_DRV_CTRL_INKEYSEL_KEY0         (MCUXCLOSCCASAFO_SFR_CTRL_INKEYSEL_KEY0)
/**
 * @}
 */ /* mcuxClOsccaSafo_Types */
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASAFO_TYPES_H_ */
