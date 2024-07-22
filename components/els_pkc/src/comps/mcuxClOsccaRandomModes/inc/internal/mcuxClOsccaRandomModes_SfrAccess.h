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
 * @file  mcuxClOsccaRandomModes_SfrAccess.h
 * @brief Macros for abstracting TRNG hardware SFR access
 */


#ifndef MCUXCLOSCCARANDOMMODES_SFRACCESS_H_
#define MCUXCLOSCCARANDOMMODES_SFRACCESS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>

/****                                 ****/
/**** TRNG Hardware Abstraction Layer ****/
/****                                 ****/

/**
 * 2 different TRNG hardware definition headers are supported.
 * Only one of them should be used/included.
 */


/**
 * Definitions for accessing TRNG SFRs via, e.g., IP_TRNG->STATUS.
 */

/** Helper macros for constructing SFR field name constants */
#define MCUXCLOSCCARANDOMMODES_PASTE(a,b)  a ## b
#define MCUXCLOSCCARANDOMMODES_CONCAT(a,b) MCUXCLOSCCARANDOMMODES_PASTE(a,b)
#define MCUXCLOSCCARANDOMMODES_SFR_FIELD(prefix,sfr,field)  MCUXCLOSCCARANDOMMODES_CONCAT(prefix, sfr ## _ ## field)

/** Helper macros to get the mask and shift values for a specific TRNG SFR field */
#define MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, field)       MCUXCLOSCCARANDOMMODES_CONCAT(MCUXCLOSCCARANDOMMODES_SFR_FIELD(TRNG_SFR_PREFIX,sfr,field), TRNG_SFR_SUFFIX_MSK)
#define MCUXCLOSCCARANDOMMODES_SFR_BITPOS(sfr, field)       MCUXCLOSCCARANDOMMODES_CONCAT(MCUXCLOSCCARANDOMMODES_SFR_FIELD(TRNG_SFR_PREFIX,sfr,field), TRNG_SFR_SUFFIX_POS)

/**********************************************************/
/* Helper macros for TRNG SFR access                       */
/**********************************************************/

/** Read from TRNG0 SFR */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_READ(sfr)  (TRNG_SFR_BASE->TRNG_SFR_NAME(sfr))

/** Write to TRNG0 SFR */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_WRITE(sfr, value)  \
    do{ TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) = (value); } while(false)

/** Read from TRNG0 SFR bit field */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_BITREAD(sfr, bit)  \
    ((TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) & MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, bit)) >> MCUXCLOSCCARANDOMMODES_SFR_BITPOS(sfr, bit))

/** Set bit field of TRNG0 SFR (read-modify-write) */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_BITSET(sfr, bit)  \
    do{ TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) |= MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, bit); } while(false)

/** Clear bit field of TRNG0 SFR (read-modify-write) */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_BITCLEAR(sfr, bit)  \
    do{ TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) &= (~ (uint32_t) MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, bit)); } while(false)

/** Set value of multi-bit field of TRNG0 SFR (read-modify-write) */
#define MCUXCLOSCCARANDOMMODES_TRNG0_SFR_BITVALSET(sfr, bit, val)  \
    do{ uint32_t temp = TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) & (~ (uint32_t) MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, bit)); \
        TRNG_SFR_BASE->TRNG_SFR_NAME(sfr) = (((val) << MCUXCLOSCCARANDOMMODES_SFR_BITPOS(sfr, bit)) & MCUXCLOSCCARANDOMMODES_SFR_BITMSK(sfr, bit)) | temp; \
    } while(false)


/**** ------------------------------ ****/

#endif /* MCUXCLOSCCARANDOMMODES_SFRACCESS_H_ */
