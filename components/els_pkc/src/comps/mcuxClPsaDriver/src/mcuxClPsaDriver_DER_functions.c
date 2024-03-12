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

#include "common.h"

#include <mcuxClMemory.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClRsa.h>
#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClPsaDriver_Functions.h>

/**
 * \brief       Updates the pointer to immediately behind the full tag.
 *
 * \param p     *p points to the start of the DER element.
 *              On successful completion, *p points to the first byte
 *              beyond the DER element.
 *              On error, the value of *p is undefined.
 *
 * \return      PSA_SUCCESS if successful.
 * \return      An PSA_ERROR_INVALID_ARGUMENT error code if the parsed input is incorrect
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(const uint8_t **p,
                          uint8_t tag)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    uint32_t length = 0u;

    if((NULL == p) || (NULL == *p) || (**p != tag))
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    uint32_t ptrLen = 1u;

    //check length
    if((*(*p + 1u) & 0x80u) == 0u) //short from
    {
     length = *(*p + 1u);
     ptrLen = 2u;
    }
    else //long form
    {
      uint8_t numberBytes = *(*p + 1u) & 0x7Fu;
      ptrLen = 2u;

      /* If length is less than 128bytes it should be short form */
      if ((numberBytes == 1u) && (*(*p + ptrLen) < 128u))
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      for(uint8_t i = 0u; i < numberBytes; ++i)
      {
       length = length << 8u;
       length |= *(*p + ptrLen);
       ptrLen++;
      }
    }

    *p += ptrLen;
    if((tag & 0x20u) != 0x20u)
    {
      // not constructed tag, skip the content
      *p += length;
    }
    return PSA_SUCCESS;
}

/**
 * \brief       Retrieve an integer DER tag and its value.
 *              Updates the pointer to immediately behind the full tag.
 *
 * \param p     *p points to the start of the DER element.
 *              On successful completion, *p points to the first byte
 *              beyond the DER element.
 *              On error, the value of *p is undefined.
 *
 * \return      PSA_SUCCESS if successful.
 * \return      An PSA_ERROR_INVALID_ARGUMENT error code if the parsed input is incorrect
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(const uint8_t **p,
                          mcuxClRsa_KeyEntry_t  * key)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    //check tag
    if(**p != 0x02u)
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    uint32_t ptrLen = 1u;

    //check length
    if((*(*p + 1u) & 0x80u) == 0u) //short from
    {
      key->keyEntryLength = *(*p + 1u);
      ptrLen = 2u;
    }
    else //long form
    {
      uint8_t numberBytes = *(*p + 1u) & 0x7Fu;
      ptrLen = 2u;

      if(numberBytes > 4u) // too big to fit into uint32
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // if length is less than 128 bytes it should be short form
      if ((numberBytes == 1u) && (*(*p + ptrLen) < 128u))
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      key->keyEntryLength = 0u;

      for(uint32_t i = 0u; i < numberBytes; ++i)
      {
        key->keyEntryLength = key->keyEntryLength << 8;
        key->keyEntryLength |= *(*p + ptrLen);
        ptrLen++;
      }
    }

    //check first and second octet of integers
    uint8_t first_octet = *(*p + ptrLen);
    uint8_t second_octet = *(*p + ptrLen + 1u);
    if((first_octet == 0u) && ((second_octet & 0x80u) == 0u))
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    if((first_octet == 0xFFu) && ((second_octet & 0x80u) == 0x80u))
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    if(first_octet == 0u)
    {
      //take next non-zero octet, the key date is unsigned
      ptrLen++;
      key->keyEntryLength -= 1u;
    }
    *p += ptrLen;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
    key->pKeyEntryData = (uint8_t *)*p;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

    *p += key->keyEntryLength;

    return PSA_SUCCESS;
}

/**
 * \brief       Generate an integer DER tag and its value
 *              Updates the pointer to immediately behind the full tag.
 *
 * \param p     *p points to the start of the DER element.
 *              On successful completion, *p points to the first byte
 *              beyond the DER element.
 *              On error, the value of *p is undefined.
  * \param key  *key points to the origin key element.

 *
 * \return      PSA_SUCCESS if successful.
 * \return      An PSA_ERROR_INVALID_ARGUMENT error code if the parsed input is incorrect
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_integer(uint8_t **p,
                          mcuxClRsa_KeyEntry_t  * key)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    uint8_t *ptr = *p;
    uint32_t ptrLen = 1u;

    //check tag
    *ptr = 0x02u;
    if(key->keyEntryLength > 0x7Fu) //long form
    {
        uint8_t h3_byte = (uint8_t)(((key->keyEntryLength) & 0xFF000000u) >> 24u);
        uint8_t h2_byte = (uint8_t)(((key->keyEntryLength) & 0xFF0000u) >> 16u);
        uint8_t h1_byte = (uint8_t)(((key->keyEntryLength) & 0xFF00u) >> 8u);
        uint8_t h0_byte = (uint8_t)((key->keyEntryLength) & 0xFFu);
        if(h3_byte != 0u)
        {
            ptr[1u] = 0x84u;
            ptr[2u] = h3_byte;
            ptr[3u] = h2_byte;
            ptr[4u] = h1_byte;
            ptr[5u] = h0_byte;
            ptrLen = 6u;
        }
        else if(h2_byte != 0u)
        {
            ptr[1u] = 0x83u;
            ptr[2u] = h2_byte;
            ptr[3u] = h1_byte;
            ptr[4u] = h0_byte;
            ptrLen = 5u;
        }
        else if(h1_byte != 0u)
        {
            ptr[1u] = 0x82u;
            ptr[2u] = h1_byte;
            ptr[3u] = h0_byte;
            ptrLen = 4u;
        }
        else
        {
            ptr[1u] = 0x81u;
            ptr[2u] = h0_byte;
            ptrLen = 3u;
        }
    }
    else                           //short from
    {
        ptr[1] = (uint8_t)key->keyEntryLength;
        ptrLen = 2u;
    }

    *p = ptr + ptrLen;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                                                  *p,
                                                  key->pKeyEntryData,
                                                  key->keyEntryLength,
                                                  key->keyEntryLength));
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    *p += key->keyEntryLength;

    return PSA_SUCCESS;
}


