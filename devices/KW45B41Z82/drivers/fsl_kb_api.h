/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _API_KB_API_H_
#define _API_KB_API_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define kStatusGroup_SBLoader (102U) /*!< SB loader status group number */

typedef struct _kb_interface
{
    /*!< Initialize the API. */
    status_t (*kb_init)(void);
    status_t (*kb_deinit)(void);
    status_t (*kb_execute)(const uint8_t *data, uint32_t dataLength, uint32_t isUpdateExt);
} kb_interface_t;

/*! @brief SB loader status codes.*/
enum
{
    kStatus_RomLdr_SectionOverrun  = MAKE_STATUS(kStatusGroup_SBLoader, 0),
    kStatus_RomLdr_Signature       = MAKE_STATUS(kStatusGroup_SBLoader, 1),
    kStatus_RomLdr_SectionLength   = MAKE_STATUS(kStatusGroup_SBLoader, 2),
    kStatus_RomLdr_UnencryptedOnly = MAKE_STATUS(kStatusGroup_SBLoader, 3),
    kStatus_RomLdr_EOFReached      = MAKE_STATUS(kStatusGroup_SBLoader, 4),
    kStatus_RomLdr_Checksum        = MAKE_STATUS(kStatusGroup_SBLoader, 5),
    kStatus_RomLdr_Crc32Error      = MAKE_STATUS(kStatusGroup_SBLoader, 6),
    kStatus_RomLdr_UnknownCommand  = MAKE_STATUS(kStatusGroup_SBLoader, 7),
    kStatus_RomLdr_IdNotFound      = MAKE_STATUS(kStatusGroup_SBLoader, 8),
    kStatus_RomLdr_DataUnderrun    = MAKE_STATUS(kStatusGroup_SBLoader, 9),
    kStatus_RomLdr_JumpReturned    = MAKE_STATUS(kStatusGroup_SBLoader, 10),
    kStatus_RomLdr_CallFailed      = MAKE_STATUS(kStatusGroup_SBLoader, 11),
    kStatus_RomLdr_KeyNotFound     = MAKE_STATUS(kStatusGroup_SBLoader, 12),
    kStatus_RomLdr_SecureOnly      = MAKE_STATUS(kStatusGroup_SBLoader, 13),
    kStatus_RomLdr_ResetReturned   = MAKE_STATUS(kStatusGroup_SBLoader, 14),

    kStatus_RomLdr_RollbackBlocked        = MAKE_STATUS(kStatusGroup_SBLoader, 15),
    kStatus_RomLdr_InvalidSectionMacCount = MAKE_STATUS(kStatusGroup_SBLoader, 16),
    kStatus_RomLdr_UnexpectedCommand      = MAKE_STATUS(kStatusGroup_SBLoader, 17),
    kStatus_RomLdr_BadSBKEK               = MAKE_STATUS(kStatusGroup_SBLoader, 18),
    kStatus_RomLdr_PendingJumpCommand     = MAKE_STATUS(kStatusGroup_SBLoader, 19),
};

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief This API is used to initialize bootloader and nboot context necessary to process sb3 file format.
 *
 * @retval #kStatus_Success API was executed successfully.
 * @retval #kStatus_Fail API execution failed.
 */
status_t KB_Init(void);

/*!
 * @brief This API is used to decrypt sb3 file and store signed image contents specified by loader command supported
 * while generating sb3 image through Json configuration. If sb3 file to be processed includes sblaoder command
 * "programFuses" then voltage must be regulated for over-drive and normalize voltage once operation is completed.
 *
 * @param data A Pointer to start of sb file data in memory.
 * @param dataLength sb file data length in bytes.
 * @param isUpdateExt Indicator for update(sb) file start address is in internal or external flash.
 *
 * @retval #kStatus_Success API was executed successfully.
 * @retval #kStatus_Fail API execution failed.
 * @retval #kStatus_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_ROM_LPSPI_Busy LPSPI transfer is busy.
 * @retval #kStatus_RomLdr_DataUnderrun
 */
status_t KB_Execute(const uint8_t *data, uint32_t dataLength, uint32_t isUpdateExt);

/*!
 * @brief This API is used to release nboot context and finalize sb3 file processing.
 *
 * @retval #kStatus_Success API was executed successfully.
 * @retval #kStatus_Fail API execution failed.
 */
status_t KB_Deinit(void);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _API_KB_API_H_ */
