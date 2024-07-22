/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __ELE_NVM_MANAGER_H__
#define __ELE_NVM_MANAGER_H__

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "ele_crypto.h"

/*!
 * @addtogroup ele_crypto_nvm
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * NVM Manager
 ******************************************************************************/
typedef struct ele_nvm_manager
{
    /*!
     * @brief Write to NVM
     *
     * This function writes data identifiedby the two-part blob ID and blob_ext to NVM.
     *
     * @param blob_id_msb   1st part of the unique 64 bit identifier of the data
     * @param blob_id_lsb   2nd part of the unique 64 bit identifier of the data
     * @param blob_id_ext   Blob ID extension
     * @param chunk         Data to copy to NVM.
     * @param chunk_sz      Size of data to be copied.
     *
     * @return Status kStatus_Success if success, kStatus_Fail if fail
     */
    status_t (*nvm_write)(
        uint32_t blob_id_msb, uint32_t blob_id_lsb, uint32_t blob_ext, uint32_t *chunk, size_t chunk_sz);

    /*!
     * @brief Read from NVM
     *
     * This function reads data identified by the two-part blob ID and blob_ext
     * from NVM and returns it.
     * If chunk is NULL, the will also allocate memory for chunk.
     *
     * @param blob_id_msb   1st part of the unique 64 bit identifier of the data
     * @param blob_id_lsb   2nd part of the unique 64 bit identifier of the data
     * @param blob_id_ext   Blob ID extension
     * @param chunk         Buffer to copy the data in.
     * @param sz            [in] Size of chunk if not NULL
     *                      [out] Size of the data read form NVM.
     *
     * @return the pointer to memory where data is copied in case of success and NULL
     *         in case of error.
     */
    uint32_t *(*nvm_read)(
        uint32_t blob_id_msb, uint32_t blob_id_lsb, uint32_t blob_id_ext, uint32_t *chunk, size_t *sz);
} ele_nvm_manager_t;

/*******************************************************************************
 * API
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Register a NVM Manager
 *
 * This function provides the NVM manager as a backend for EdgeLock Enclave.
 * The NVM Manger should provide functions read/write a buffer to NVM identifiable
 * by a blob ID and extension.
 *
 * @param manager Structure containing function pointers to read/write nvm functions
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_Register_NVM_Manager(ele_nvm_manager_t *manager);

/*!
 * @brief Unregister the existing NVM Manager
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_Unregister_NVM_Manager(void);

/*!
 * @brief ELE Key Management Service with backend provided by NVM Manager
 *
 * This function provides the Key Group Management Service for EdgeLock Enclave.
 *
 * @param base MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param operation Requested opration, see key_group_mng_t enum
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ManageKeyGroup_To_NVM(S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyGroupID, key_group_mng_t operation);

/*!
 * @brief ELE Storage Master Import Service from backend provided by NVM Manager
 *
 * This function provides Storage Master Import Service for EdgeLock Enclave.
 * This must be called prior opening keystore stored in the NVM.
 *
 * @param base MU peripheral base address
 * @param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_StorageMasterImport_From_NVM(S3MU_Type *mu, uint32_t nvmStorageID);

/*!
 * @brief ELE Export Chunks Management Service to backend provided by NVM Manager
 *
 * This function provides the Key Group Management Service for exporting keygroup, keystore and storage master chunks.
 *
 * @param base MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param exportKeyGroup If true, key group (keyGroupID) chunk is exported, if false, only keystore and master
 * @param keyGroupID unique key group ID choosen by user. Not used if exportKeyGroup is false
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ExportChunks_To_NVM(S3MU_Type *mu, uint32_t keyHandleID, bool exportKeyGroup, uint32_t keyGroupID);

#if defined(__cplusplus)
}
#endif

/*! @} */ /* end of group s3mu */

#endif    /* __ELE_NVM_MANAGER_H__ */
