/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_ADAPTER_SDU_H
#define FSL_ADAPTER_SDU_H

#include <stdint.h>
#include "fsl_sdioslv_sdu.h"

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FSL_FEATURE_SOC_SDIO_COUNT (3)

#define SDU_CMD_RECEIVED  (1U << 0U)
#define SDU_DATA_RECEIVED (1U << 1U)

typedef enum _sdu_for_read_type
{
    SDU_TYPE_FOR_READ_CMD = 0,
    SDU_TYPE_FOR_READ_EVENT= 1,
    SDU_TYPE_FOR_READ_DATA = 2,
    SDU_TYPE_FOR_READ_MAX,
} sdu_for_read_type_t;

typedef enum _sdu_for_write_type
{
    SDU_TYPE_FOR_WRITE_CMD = 0,
    SDU_TYPE_FOR_WRITE_DATA = 1,
    SDU_TYPE_FOR_WRITE_MAX,
} sdu_for_write_type_t;

typedef struct _sdio_header
{
    uint16_t len;
    uint16_t type;
} sdio_header_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif

/*! @} */

status_t SDU_Init(void);
void SDU_Deinit(void);

typedef void (*sdu_callback_t)(void *tlv, size_t tlv_sz);
status_t SDU_InstallCallback(sdu_for_write_type_t type, sdu_callback_t callback);

/*!
 * @brief SDU send cmd/event/data.
 *
 * @param sdu_for_read_type_t type for cmd/event/data.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success buffer is added to data slot with problem.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_NoData No free buffer to use.
 * @retval #kStatus_Fail Fail to send data.
 */
status_t SDU_Send(sdu_for_read_type_t type, uint8_t *data_addr, uint16_t data_len);

status_t SDU_RecvCmd(void);
status_t SDU_RecvData(void);

void SDU_DriverIRQHandler(void);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
