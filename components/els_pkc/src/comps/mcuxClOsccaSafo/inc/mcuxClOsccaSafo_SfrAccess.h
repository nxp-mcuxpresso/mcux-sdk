/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClOsccaSafo_SfrAccess.h
 * @brief Macros for abstracting SAFO hardware SFR access
 */

#ifndef MCUXCLOSCCASAFO_SFRACCESS_H_
#define MCUXCLOSCCASAFO_SFRACCESS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>


/** Helper macros for constructing SFR field name constants */
#define MCUXCLOSCCASAFO_PASTE(a,b)  a ## b
#define MCUXCLOSCCASAFO_CONCAT(a,b) MCUXCLOSCCASAFO_PASTE(a,b)
#define MCUXCLOSCCASAFO_SFR_FIELD(prefix,sfr,field)  MCUXCLOSCCASAFO_CONCAT(prefix, sfr ## _ ## field)


/** Helper macros to get the mask and shift values for a specific SAFO SFR field */
#define MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, field)         MCUXCLOSCCASAFO_CONCAT(MCUXCLOSCCASAFO_SFR_FIELD(SAFO_SFR_PREFIX,sfr,field), _MASK)
#define MCUXCLOSCCASAFO_SFR_FIELD_SHIFT(sfr, field)        MCUXCLOSCCASAFO_CONCAT(MCUXCLOSCCASAFO_SFR_FIELD(SAFO_SFR_PREFIX,sfr,field), _SHIFT)
#define MCUXCLOSCCASAFO_SFR_FIELD_FORMAT(sfr, field, val)  (MCUXCLOSCCASAFO_SFR_FIELD(SAFO_SFR_PREFIX,sfr,field) (val))

/**********************************************************/
/* Helper macros for SAFO SFR access                      */
/**********************************************************/

/** Read from SAFO SFR */
#define MCUXCLOSCCASAFO_SFR_READ(sfr)  (SAFO_SFR_BASE->SAFO_SFR_NAME(sfr))

/** Write to SAFO SFR */
#define MCUXCLOSCCASAFO_SFR_WRITE(sfr, value)  \
    do{ SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) = (value); } while(false)

/** Read from SAFO SFR bit field */
#define MCUXCLOSCCASAFO_SFR_BITREAD(sfr, bit)  \
    ((SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) & MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, bit)) >> MCUXCLOSCCASAFO_SFR_FIELD_SHIFT(sfr, bit))

/** Set bit field of SAFO SFR (read-modify-write) */
#define MCUXCLOSCCASAFO_SFR_BITSET(sfr, bit)  \
    do{ SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) |= MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, bit); } while(false)

/** Clear bit field of SAFO SFR (read-modify-write) */
#define MCUXCLOSCCASAFO_SFR_BITCLEAR(sfr, bit)  \
    do{ SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) &= (~ (uint32_t) MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, bit)); } while(false)

/** Set value of multi-bit field of SAFO SFR (read-modify-write) */
#define MCUXCLOSCCASAFO_SFR_BITVALSET(sfr, bit, val)  \
    do{ uint32_t temp = SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) & (~ (uint32_t) MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, bit)); \
        SAFO_SFR_BASE->SAFO_SFR_NAME(sfr) = ((val) << MCUXCLOSCCASAFO_SFR_FIELD_SHIFT(sfr, bit)) & MCUXCLOSCCASAFO_SFR_FIELD_MASK(sfr, bit); \
    } while(false)

/**** ------------------------------ ****/

#endif /* MCUXCLOSCCASAFO_SFRACCESS_H_ */
