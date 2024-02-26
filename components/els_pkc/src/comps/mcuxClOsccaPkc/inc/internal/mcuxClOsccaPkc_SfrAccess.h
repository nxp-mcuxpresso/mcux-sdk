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
 * @file  mcuxClOsccaPkc_SfrAccess.h
 * @brief Macros for abstracting PKC hardware SFR access
 */


#ifndef MCUXCLOSCCAPKC_SFRACCESS_H_
#define MCUXCLOSCCAPKC_SFRACCESS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>

/****                                ****/
/**** PKC Hardware Abstraction Layer ****/
/****                                ****/

/**
 * 2 different PKC hardware definition headers are supported.
 * Only one of them should be used/included.
 */


/** Special definitions of multi-bit bit field. */
#define MCUXCLOSCCAPKC_SFR_CFG_RNDDLY_NODLY   (((uint32_t)(((uint32_t)(0u)) << MCUXCLOSCCAPKC_SFR_BITPOS(CFG,RNDDLY))) & MCUXCLOSCCAPKC_SFR_BITMSK(CFG,RNDDLY))
#define MCUXCLOSCCAPKC_SFR_CTRL_REDMUL_FULLSZ (((uint32_t)(((uint32_t)(0u)) << MCUXCLOSCCAPKC_SFR_BITPOS(CFG,RNDDLY))) & MCUXCLOSCCAPKC_SFR_BITMSK(CFG,RNDDLY))


/**
 * Definitions for accessing PKC SFRs via, e.g., IP_PKC->STATUS.
 */

/** Helper macros for constructing SFR field name constants */
#define MCUXCLOSCCAPKC_PASTE(a,b)  a ## b
#define MCUXCLOSCCAPKC_CONCAT(a,b) MCUXCLOSCCAPKC_PASTE(a,b)
#define MCUXCLOSCCAPKC_SFR_FIELD(prefix,sfr,field)        MCUXCLOSCCAPKC_CONCAT(prefix, sfr ## _ ## field)

/** Helper macros to get the mask and shift values for a specific PKC SFR field */
#define MCUXCLOSCCAPKC_SFR_BITMSK(sfr, field)        MCUXCLOSCCAPKC_CONCAT(MCUXCLOSCCAPKC_SFR_FIELD(PKC_SFR_PREFIX,sfr,field), PKC_SFR_SUFFIX_MSK)
#define MCUXCLOSCCAPKC_SFR_BITPOS(sfr, field)        MCUXCLOSCCAPKC_CONCAT(MCUXCLOSCCAPKC_SFR_FIELD(PKC_SFR_PREFIX,sfr,field), PKC_SFR_SUFFIX_POS)
#define MCUXCLOSCCAPKC_SFR_BITFMT(sfr, field, val)  (MCUXCLOSCCAPKC_SFR_FIELD(PKC_SFR_PREFIX,sfr,field) (val))


/**********************************************************/
/* Helper macros for PKC SFR access                       */
/**********************************************************/

/** Read from PKC SFR */
#define MCUXCLOSCCAPKC_SFR_READ(sfr)  (PKC_SFR_BASE->PKC_SFR_NAME(sfr))

/** Write to PKC SFR */
#define MCUXCLOSCCAPKC_SFR_WRITE(sfr, value)  \
    do{ PKC_SFR_BASE->PKC_SFR_NAME(sfr) = (value); } while(false)

/** Read from PKC SFR bit field */
#define MCUXCLOSCCAPKC_SFR_BITREAD(sfr, bit)  \
    ((PKC_SFR_BASE->PKC_SFR_NAME(sfr) & MCUXCLOSCCAPKC_SFR_BITMSK(sfr, bit)) >> MCUXCLOSCCAPKC_SFR_BITPOS(sfr, bit))

/** Set bit field of PKC SFR (read-modify-write) */
#define MCUXCLOSCCAPKC_SFR_BITSET(sfr, bit)  \
    do{ PKC_SFR_BASE->PKC_SFR_NAME(sfr) |= MCUXCLOSCCAPKC_SFR_BITMSK(sfr, bit); } while(false)

/** Clear bit field of PKC SFR (read-modify-write) */
#define MCUXCLOSCCAPKC_SFR_BITCLEAR(sfr, bit)  \
    do{ PKC_SFR_BASE->PKC_SFR_NAME(sfr) &= (~ (uint32_t) MCUXCLOSCCAPKC_SFR_BITMSK(sfr, bit)); } while(false)

/** Set value of multi-bit field of PKC SFR (read-modify-write) */
#define MCUXCLOSCCAPKC_SFR_BITVALSET(sfr, bit, val)  \
    do{ uint32_t temp = PKC_SFR_BASE->PKC_SFR_NAME(sfr) & (~ (uint32_t) MCUXCLOSCCAPKC_SFR_BITMSK(sfr, bit)); \
        PKC_SFR_BASE->PKC_SFR_NAME(sfr) = (((val) << MCUXCLOSCCAPKC_SFR_BITPOS(sfr, bit)) & MCUXCLOSCCAPKC_SFR_BITMSK(sfr, bit)) | temp; \
    } while(false)


/**** ------------------------------ ****/

#endif /* MCUXCLOSCCAPKC_SFRACCESS_H_ */
