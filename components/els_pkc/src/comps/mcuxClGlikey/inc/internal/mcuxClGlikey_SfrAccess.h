/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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
 * @file  mcuxClGlikey_SfrAccess.h
 * @brief Macros for abstracting Glikey hardware SFR access
 */

#ifndef MCUXCLGLIKEY_SFRACCESS_H_
#define MCUXCLGLIKEY_SFRACCESS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>
#include <stdint.h>
#include <stdbool.h>


/****                                   ****/
/**** Glikey Hardware Abstraction Layer ****/
/****                                   ****/

/**
 * Definitions for accessing Glikey SFRs via, e.g., IP_GLIKEY->STATUS.
 */

/** Helper macros for constructing SFR field name constants */
#define MCUXCLGLIKEY_PASTE(a,b)  a ## b
#define MCUXCLGLIKEY_CONCAT(a,b) MCUXCLGLIKEY_PASTE(a,b)
#define MCUXCLGLIKEY_SFR_FIELD(prefix,sfr,field)        MCUXCLGLIKEY_CONCAT(prefix, sfr ## _ ## field)

/** Helper macros to get the mask and shift values for a specific GLIKEY SFR field */
#define MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, field)         MCUXCLGLIKEY_CONCAT(MCUXCLGLIKEY_SFR_FIELD(GLIKEY_SFR_PREFIX,sfr,field), _MASK)
#define MCUXCLGLIKEY_SFR_FIELD_SHIFT(sfr, field)        MCUXCLGLIKEY_CONCAT(MCUXCLGLIKEY_SFR_FIELD(GLIKEY_SFR_PREFIX,sfr,field), _SHIFT)
#define MCUXCLGLIKEY_SFR_FIELD_FORMAT(sfr, field, val)  (MCUXCLGLIKEY_SFR_FIELD(GLIKEY_SFR_PREFIX,sfr,field) (val))

/**********************************************************/
/* Helper macros for GLIKEY SFR access                       */
/**********************************************************/

/** Read from GLIKEY SFR */
#define MCUXCLGLIKEY_SFR_READ(baseAddress,sfr)  \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
    (GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr)) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

/** Write to GLIKEY SFR */
#define MCUXCLGLIKEY_SFR_WRITE(baseAddress, sfr, value)  \
    do{ \
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
        GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) = (value); \
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY() \
    } while(false)

/** Read from GLIKEY SFR bit field */
#define MCUXCLGLIKEY_SFR_BITREAD(baseAddress, sfr, bit)  \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
    ((GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) & MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, bit)) >> MCUXCLGLIKEY_SFR_FIELD_SHIFT(sfr, bit)) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

/** Set bit field of GLIKES SFR (read-modify-write) */
#define MCUXCLGLIKEY_SFR_BITSET(baseAddress, sfr, bit)  \
    do{ \
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
        GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) |= MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, bit); \
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY() \
    } while(false)

/** Clear bit field of GLIKEY SFR (read-modify-write) */
#define MCUXCLGLIKEY_SFR_BITCLEAR(baseAddress, sfr, bit)  \
    do{ \
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
        GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) &= (~ (uint32_t) MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, bit)); \
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY() \
    } while(false)

/** Set value of multi-bit field of GLIKEY SFR (read-modify-write) */
#define MCUXCLGLIKEY_SFR_BITVALSET(baseAddress, sfr, bit, val)  \
    do{ \
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast to IP_GLIKEY_Type * to access hardware SFRs") \
        uint32_t temp = GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) & (~ (uint32_t) MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, bit)); \
        GLIKEY_SFR_BASE(baseAddress)->GLIKEY_SFR_NAME(sfr) = ((val) << MCUXCLGLIKEY_SFR_FIELD_SHIFT(sfr, bit)) & MCUXCLGLIKEY_SFR_FIELD_MASK(sfr, bit); \
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY() \
    } while(false)

/**** ------------------------------ ****/
#endif /* MCUXCLGLIKEY_SFRACCESS_H_ */
