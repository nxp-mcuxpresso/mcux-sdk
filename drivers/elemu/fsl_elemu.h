/*
 * Copyright 2019-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __ELEMU_DRIVER_H__
#define __ELEMU_DRIVER_H__

#include "fsl_common.h"
#include "fsl_device_registers.h"

#define MU_MSG_HEADER_SIZE (1U)

#define MESSAGING_TAG_COMMAND (0x17u)
#define MESSAGING_TAG_REPLY   (0x0Cu)
#define STATIC_CHECK_BITS     (0xD7u)

enum
{
    kStatus_ELEMU_AgumentOutOfRange =
        MAKE_STATUS(kStatusGroup_ELEMU, 0x1u), /*!< ELEMU status for out of range access. */
    kStatus_ELEMU_InvalidArgument =
        MAKE_STATUS(kStatusGroup_ELEMU, 0x2u), /*!< ELEMU status for invalid argument check. */
    kStatus_ELEMU_RequestTimeout = MAKE_STATUS(kStatusGroup_ELEMU, 0x3u), /*!< ELEMU status for timeout. */
    kStatus_ELEMU_Busy = MAKE_STATUS(kStatusGroup_ELEMU, 0x4u), /*!< ELEMU status for reservation by other core. */
};

typedef enum
{
    kStatus_ELEMU_Unknown       = 0x0u, /*!< Unexpected ELEMU ownership. */
    kStatus_ELEMU_LockedByMe    = 0x1u, /*!< ELEMU reserved for current core. */
    kStatus_ELEMU_LockedByOther = 0x2u, /*!< ELEMU reserved for other core. */
    kStatus_ELEMU_Free          = 0x3u, /*!< ELEMU not reserved. */
} elemu_ownership_status_t;

typedef struct mu_hdr
{
    uint8_t tag_sts;
    uint8_t check_bits;
    uint8_t size;
    uint8_t command;
} mu_hdr_t;

void ELEMU_mu_hal_send_data(ELEMU_Type *mu, uint8_t regid, uint32_t *data);
void ELEMU_mu_hal_receive_data(ELEMU_Type *mu, uint8_t regid, uint32_t *data);
status_t ELEMU_mu_hal_receive_data_wait(ELEMU_Type *mu, uint8_t regid, uint32_t *data, uint32_t wait);
status_t ELEMU_mu_read_message(ELEMU_Type *mu, uint32_t *buf, uint8_t *size, uint8_t read_header);
status_t ELEMU_mu_read_data_wait(ELEMU_Type *mu, uint32_t buf[], uint8_t *size, uint32_t wait);

status_t ELEMU_mu_send_message(ELEMU_Type *mu, uint32_t buf[], size_t wordCount);
status_t ELEMU_mu_get_response(ELEMU_Type *mu, uint32_t *buf, size_t wordCount);
status_t ELEMU_mu_wait_for_data(ELEMU_Type *mu, uint32_t *buf, size_t wordCount, uint32_t wait);

status_t ELEMU_mu_wait_for_ready(ELEMU_Type *mu, uint32_t wait);

#if (defined(FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER) && FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER)
elemu_ownership_status_t ELEMU_mu_get_ownership_status(ELEMU_Type *mu);
status_t ELEMU_mu_get_ownership(ELEMU_Type *mu);
status_t ELEMU_mu_release_ownership(ELEMU_Type *mu);
status_t ELEMU_mu_release_ownership_force(ELEMU_Type *mu);
#endif /* FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER */

void ELEMU_mu_init(ELEMU_Type *mu);
status_t ELEMU_LP_WakeupPathInit(ELEMU_Type *mu);

#if (defined(ELEMU_HAS_LOADABLE_FW) && ELEMU_HAS_LOADABLE_FW)
status_t ELEMU_loadFw(ELEMU_Type *mu, uint32_t image[]);
#endif /* ELEMU_HAS_LOADABLE_FW */

#endif /* __ELEMU_DRIVER_H__ */
