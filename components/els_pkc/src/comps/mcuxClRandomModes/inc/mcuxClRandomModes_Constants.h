/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClRandomModes_Constants.h
 * @brief Mode definitions of mcuxClRandomModes component
 */

#ifndef MCUXCLRANDOMMODES_CONSTANTS_H_
#define MCUXCLRANDOMMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClRandom_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Values for reseeds                                     */
/**********************************************************/


/**********************************************************/
/* Types of mcuxClRandom                                   */
/**********************************************************/
/**
 * @defgroup mcuxClRandomModes_Constants mcuxClRandom_Constants
 * @brief Defines all modes of @ref mcuxClRandomModes
 * @ingroup mcuxClRandom
 * @{
 */


/**
 * @brief Mode for a DRBG implemented by the ELS
 *
 * This mode provides a function to get random values from a DRBG implemented by the ELS. The provided security strength
 * is HW dependent and can be determined using the function mcuxClRandom_checkSecurityStrength
 */
extern const mcuxClRandom_ModeDescriptor_t mcuxClRandomModes_mdELS_Drbg;
static const mcuxClRandom_Mode_t mcuxClRandomModes_Mode_ELS_Drbg =
    &mcuxClRandomModes_mdELS_Drbg;


#if defined(MCUXCL_FEATURE_RANDOMMODES_NORMALMODE) && defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)

#ifdef MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED



#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256

/**
 * @brief Mode for a NIST SP800-90A CTR_DRBG based on AES-256 configured to not provide prediction resistance and realize a DRG.3 at 256 bit security level.
 *
 * This mode realizes a NIST SP800-90A CTR_DRBG based on AES-256 which does not provide prediction resistance. It is designed in a way
 * to comply to FIPS 140-3 on the one hand and realize a DRG.3 at 256 bit security level on the other.
 * For an up to date list of evaluations and certifications one should refer to the product (HW) documentation.
 */
extern const mcuxClRandom_ModeDescriptor_t mcuxClRandomModes_mdCtrDrbg_AES256_DRG3;
static const mcuxClRandom_Mode_t mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3 =
    &mcuxClRandomModes_mdCtrDrbg_AES256_DRG3;

/**
 * @brief Mode for a NIST SP800-90A CTR_DRBG based on AES-256 configured to not provide prediction resistance and realize a DRG.4 at 256 bit security level.
 *
 * This mode realizes a NIST SP800-90A CTR_DRBG based on AES-256 which does not provide prediction resistance. It is designed in a way
 * to comply to FIPS 140-3 on the one hand and realize a DRG.4 at 256 bit security level on the other.
 * For an up to date list of evaluations and certifications one should refer to the product (HW) documentation.
 *
* NOTE: This mode is an alias of mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3 and does not perform any internal reseeding.
* To realize the desired DRG.4 functionality by on-demand reseeding, the mcuxClRandom_reseed function is provided.
 */
#define mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG4 mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3

/**
 * @brief Mode for a NIST SP800-90A CTR_DRBG based on AES-256 configured to not provide prediction resistance.
 *
 * This mode realizes a NIST SP800-90A CTR_DRBG based on AES-256 which does not provide prediction resistance and
 * is designed in a way to comply to FIPS 140-3.
 * For an up to date list of evaluations and certifications one should refer to the product (HW) documentation.
 *
 * This is an alias of mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3, as both modes offer the same functionality.
 */
#define mcuxClRandomModes_Mode_CtrDrbg_AES256 mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3

#endif /* MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256 */

#endif /* MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED */



#endif /* defined(MCUXCL_FEATURE_RANDOMMODES_NORMALMODE) && defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG) */

/**
 * @}
 */ /* mcuxClRandom_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_CONSTANTS_H_ */
