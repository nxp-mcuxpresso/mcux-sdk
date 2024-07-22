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
 * @file  mcuxClKey_Functions_Internal.h
 * @brief Internal function definitions for the mcuxClKey component
 */

#ifndef MCUXCLKEY_FUNCTIONS_INTERNAL_H_
#define MCUXCLKEY_FUNCTIONS_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClKey_Types.h>
#include <mcuxClKey_Constants.h>
#include <internal/mcuxClKey_Types_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************
 * INTERNAL INLINED FUNCTIONS TO ACCESS THE KEY DESCRIPTOR
 ************************************************************/

/**
 * Returns the key data pointer of the key handle
 *
 * @return Key data pointer of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getKeyData)
static inline uint8_t * mcuxClKey_getKeyData(mcuxClKey_Handle_t key)
{
  return key->container.pData;
}

/**
 * Sets the key data pointer of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setKeyData)
static inline void mcuxClKey_setKeyData(mcuxClKey_Handle_t key, uint8_t * pKeyData)
{
  key->container.pData = pKeyData;
}


/**
 * Returns the aux data pointer of the key handle
 *
 * @return Aux data pointer of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getAuxData)
static inline uint8_t * mcuxClKey_getAuxData(mcuxClKey_Handle_t key)
{
  return key->container.pAuxData;
}

/**
 * Sets the aux data pointer of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setAuxData)
static inline void mcuxClKey_setAuxData(mcuxClKey_Handle_t key, uint8_t * pAuxData)
{
  key->container.pAuxData = pAuxData;
}


/**
 * Sets the protection descriptor pointer of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setProtectionType)
static inline void mcuxClKey_setProtectionType(mcuxClKey_Handle_t key, const mcuxClKey_ProtectionDescriptor_t * pProtection)
{
  key->protection = pProtection;
}

/**
 * Returns the linked data pointer of the key handle
 *
 * @return linked data pointer of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getLinkedData)
static inline void * mcuxClKey_getLinkedData(mcuxClKey_Handle_t key)
{
  return key->pLinkedData;
}

/**
 * Sets the linked data pointer of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setLinkedData)
static inline void mcuxClKey_setLinkedData(mcuxClKey_Handle_t key, void * pLinkedData)
{
  key->pLinkedData = pLinkedData;
}

/**
 * Gets the type structure of the key handle
 *
 * @return Type structure of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getTypeDescriptor)
static inline mcuxClKey_TypeDescriptor_t mcuxClKey_getTypeDescriptor(mcuxClKey_Handle_t key)
{
  return key->type;
}

/**
 * Sets the type structure of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setTypeDescriptor)
static inline void mcuxClKey_setTypeDescriptor(mcuxClKey_Handle_t key, mcuxClKey_TypeDescriptor_t pType)
{
  key->type = pType;
}


/**
 * Gets the type info field of the key handle, which might contain pointer to ECC domain parameters
 *
 * @return Type info of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getTypeInfo)
static inline void * mcuxClKey_getTypeInfo(mcuxClKey_Handle_t key)
{
  return key->type.info;
}


/**
 * Returns the key size in bytes of the key handle
 *
 * @return Key size in bytes of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getSize)
static inline mcuxClKey_Size_t mcuxClKey_getSize(mcuxClKey_Handle_t key)
{
  return key->type.size;
}


/**
 * Returns the algorithm identifier of the key handle
 *
 * @return Algorithm identifier of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getAlgoId)
static inline mcuxClKey_AlgorithmId_t mcuxClKey_getAlgoId(mcuxClKey_Handle_t key)
{
  return key->type.algoId;
}

/**
 * Returns the algorithm of the key handle
 *
 * @return Algorithm identifier of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getAlgorithm)
static inline mcuxClKey_AlgorithmId_t mcuxClKey_getAlgorithm(mcuxClKey_Handle_t key)
{
  return key->type.algoId & MCUXCLKEY_ALGO_ID_ALGO_MASK;
}

/**
 * Returns the key usage of the key handle
 *
 * @return Algorithm identifier of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getKeyUsage)
static inline mcuxClKey_AlgorithmId_t mcuxClKey_getKeyUsage(mcuxClKey_Handle_t key)
{
  return key->type.algoId & MCUXCLKEY_ALGO_ID_USAGE_MASK;
}


/**
 * Returns the pointer of the loaded key data of the key handle
 *
 * @return Pointer to the loaded key data
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getLoadedKeyData)
static inline uint8_t * mcuxClKey_getLoadedKeyData(mcuxClKey_Handle_t key)
{
  return key->location.pData;
}

/**
 * Sets the pointer of the (to be) loaded key data
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setLoadedKeyData)
static inline void mcuxClKey_setLoadedKeyData(mcuxClKey_Handle_t key, uint32_t * pKeyDataLoadLocation)
{
  key->location.pData = (uint8_t *) pKeyDataLoadLocation;
}


/**
 * Returns the length of the loaded key data
 *
 * @return Length of to the loaded key data of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getLoadedKeyLength)
static inline uint32_t mcuxClKey_getLoadedKeyLength(mcuxClKey_Handle_t key)
{
  return key->location.length;
}

/**
 * Sets the length of the loaded key data
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setLoadedKeyLength)
static inline void mcuxClKey_setLoadedKeyLength(mcuxClKey_Handle_t key, uint32_t keyLength)
{
  key->location.length = keyLength;
}


/**
 * Returns the hardware slot of the loaded key
 *
 * @return Hardware slot of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getLoadedKeySlot)
static inline uint32_t mcuxClKey_getLoadedKeySlot(mcuxClKey_Handle_t key)
{
  return key->location.slot;
}

/**
 * Sets the pointer of the (to be) loaded data of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setLoadedKeySlot)
static inline void mcuxClKey_setLoadedKeySlot(mcuxClKey_Handle_t key, uint32_t keySlot)
{
  key->location.slot = keySlot;
}


/**
 * Returns the load status of the key handle
 *
 * @return Load status of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getLoadStatus)
static inline mcuxClKey_LoadStatus_t mcuxClKey_getLoadStatus(mcuxClKey_Handle_t key)
{
  return key->location.status;
}

/**
 * Sets the load status of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setLoadStatus)
static inline void mcuxClKey_setLoadStatus(mcuxClKey_Handle_t key, mcuxClKey_LoadStatus_t loadStatus)
{
  key->location.status = loadStatus;
}


/**
 * Returns the pointer to the parent key of the key handle
 *
 * @return Pointer to the parent key of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getParentKey)
static inline mcuxClKey_Descriptor_t * mcuxClKey_getParentKey(mcuxClKey_Handle_t key)
{
  return key->container.parentKey;
}

/**
 * Sets the pointer to the parent key of the key handle
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setParentKey)
static inline void mcuxClKey_setParentKey(mcuxClKey_Handle_t key, mcuxClKey_Descriptor_t * pParentKey)
{
  key->container.parentKey = pParentKey;
}


/**
 * Returns the size of the key data container
 *
 * @return Size of the key data container of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getKeyContainerSize)
static inline uint32_t mcuxClKey_getKeyContainerSize(mcuxClKey_Handle_t key)
{
  return key->container.length;
}

/**
 * Sets the size of the key data container of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setKeyContainerSize)
static inline void mcuxClKey_setKeyContainerSize(mcuxClKey_Handle_t key, uint32_t keyContainerSize)
{
  key->container.length = keyContainerSize;
}


/**
 * Returns the used size of the key data container
 *
 * @return Used size of the key data container of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_getKeyContainerUsedSize)
static inline uint32_t mcuxClKey_getKeyContainerUsedSize(mcuxClKey_Handle_t key)
{
  return key->container.used;
}

/**
 * Sets the used size of the key data container of the given key
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setKeyContainerUsedSize)
static inline void mcuxClKey_setKeyContainerUsedSize(mcuxClKey_Handle_t key, uint32_t keyContainerUsedSize)
{
  key->container.used = keyContainerUsedSize;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_FUNCTIONS_INTERNAL_H_ */
