/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClKey_Types.h
 * @brief Type definitions for the mcuxClKey component
 */

#ifndef MCUXCLKEY_TYPES_H_
#define MCUXCLKEY_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <mcuxClCss.h>
#include <mcuxClKey_KeyTypes.h>

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClKey_Macros mcuxClKey_Macros
 * @brief Defines all macros of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */
/**
 * \defgroup MCUXCLKEY_STATUS_  MCUXCLKEY_STATUS_
 * @brief Return code definitions
 * @{
 */
#define MCUXCLKEY_STATUS_OK     ((mcuxClKey_Status_t) 0xE2E2E2E2u )  ///< Key operation successful
#define MCUXCLKEY_STATUS_ERROR  ((mcuxClKey_Status_t) 0xE2E22E2Eu )  ///< Error occured during Key operation
/**@}*/

/**
 * @}
 */ /* mcuxClKey_Macros */


/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClKey_Types mcuxClKey_Types
 * @brief Defines all types of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**
 * @brief Type for Key component error codes.
 */
typedef uint32_t mcuxClKey_Status_t;

/**
 * @brief Type for Key component error codes, returned by functions with code-flow protection.
 */
typedef uint64_t mcuxClKey_Status_Protected_t;

/**
 * @brief Type of source information structure.
 */
typedef struct mcuxClKey_SrcAuxDataProvider {
  const uint8_t * pData; ///< Pointer to memory buffer with source information
  uint32_t slot;         ///< Source key slot
} mcuxClKey_SrcAuxDataProvider_t;

/**
 * @brief Type of key location definition
 */
typedef enum mcuxClKey_LoadLocation {
    mcuxClKey_LoadLocation_NOTLOADED,  ///< Key not loaded
    mcuxClKey_LoadLocation_MEMORY,     ///< Use key from memory
    mcuxClKey_LoadLocation_COPRO       ///< Use key from HW IP
} mcuxClKey_LoadLocation_t;

/**
 * @brief Type of destination information structure.
 */
typedef struct mcuxClKey_DstDataProvider {
  uint8_t * pData;    ///< Pointer to memory buffer for used as key destination
  uint32_t byteCount; ///< Length field of the destination memory buffer
  uint32_t slot;      ///< Destination key slot
  mcuxClCss_KeyProp_t key_properties;    ///< Requested properties of the destination key
  mcuxClKey_LoadLocation_t loadLocation; ///< Defines which key is used
} mcuxClKey_DstDataProvider_t;

/* Forward declaration */
struct mcuxClKey_Protection;

/**
 * @brief Type of the key handle.
 */
typedef struct mcuxClKey_Descriptor {
  mcuxClKey_Type_t                       type;           ///< Define which keytype shall be loaded
  const struct mcuxClKey_Protection *    protection;     ///< Define which load and flush mechanism shall be used
  const uint8_t *                       pSrcKeyData;    ///< Provide source information for the key
  mcuxClKey_SrcAuxDataProvider_t         srcAux;         ///< Provide aux information for the key
  mcuxClKey_DstDataProvider_t            dstKey;         ///< Provide destination information for the key
} mcuxClKey_Descriptor_t;

/**
 * @brief Type of opaque key handle.
 */
typedef mcuxClKey_Descriptor_t * mcuxClKey_Handle_t;

/**
 * @brief Functions to load a key into coprocessor or memory buffer.
 *
 * @param[in]  key  Key handle that provides information to load the key
 *
 * @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 */
typedef mcuxClKey_Status_Protected_t (*mcuxClKey_LoadFuncPtr_t)(mcuxClKey_Handle_t key);

/**
 * @brief Functions to flush a key from coprocessor or memory buffer.
 *
 * @param[in]  key  Key handle that provides information to flush the key
 *
 * @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 */
typedef mcuxClKey_Status_Protected_t (*mcuxClKey_FlushFuncPtr_t)(mcuxClKey_Handle_t key);

/**
 * @brief Type to map load and flush functions.
 */
typedef struct mcuxClKey_Protection {
    mcuxClKey_LoadFuncPtr_t loadFunc;   ///< Function pointer to a load function
    mcuxClKey_FlushFuncPtr_t flushFunc; ///< Function pointer to a flush function
    uint32_t protectionTokenLoad; ///< Protection token of the load function
    uint32_t protectionTokenFlush; ///< Protection token of the flush function
} mcuxClKey_Protection_t;

/**
 * @}
 */ /* mcuxClKey_Types */


/**********************************************
 * FUNCTIONS
 **********************************************/
/* None */

#endif /* MCUXCLKEY_TYPES_H_ */
