/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SENTINEL_H_
#define _FSL_SENTINEL_H_

#include "fsl_common.h"

/*!
 * @addtogroup sentinel
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief sentinel command definition. */
/* baseline apis command */
#define SENTINEL_BASELINE_API_CMD_PING              (0x01U)
#define SENTINEL_BASELINE_API_CMD_DUMP_DEBUG_BUFFER (0x21U)
#define SENTINEL_BASELINE_API_CMD_OEM_CNTN_AUTH     (0x87U)
#define SENTINEL_BASELINE_API_CMD_VERIFY_IMAGE      (0x88U)
#define SENTINEL_BASELINE_API_CMD_RELEASE_CONTAINER (0x89U)
#define SENTINEL_BASELINE_API_CMD_GET_FW_VERSION    (0x9DU)
#define SENTINEL_BASELINE_API_CMD_RELEASE_RDC       (0xC4U)
#define SENTINEL_BASELINE_API_CMD_GET_FW_STATUS     (0xC5U)
#define SENTINEL_BASELINE_API_CMD_POWER_DOWN        (0xD1U)
#define SENTINEL_BASELINE_API_CMD_GET_INFO          (0xDAU)
/* bridge apis command */
#define SENTINEL_BRIDGE_API_CMD_SESSION_OPEN   (0x10U)
#define SENTINEL_BRIDGE_API_CMD_SESSION_CLOSE  (0x11U)
#define SENTINEL_BRIDGE_API_CMD_RNG_OPEN       (0x20U)
#define SENTINEL_BRIDGE_API_CMD_RNG_CLOSE      (0x21U)
#define SENTINEL_BRIDGE_API_CMD_RNG_GET_RANDOM (0x22U)

#define SENTINEL_MSG_HDR_CMD_TAG     (0x17U)
#define SENTINEL_MSG_HDR_CMD_RSP_TAG (0xe1U)
#define SENTINEL_BASELINE_API_VER    (0x06U)
#define SENTINEL_BRIDGE_API_VER      (0x07U)

/* SENTINEL Receive Register Count */
#define SENTINEL_RR_CNT (0x4U)

/* SENTINEL Transmit Register Count */
#define SENTINEL_TR_CNT (0x8U)

/* MU ID */
#define RTC_MU_ID (0x01U)
#define AP_MU_ID  (0x02U)

/* Domain ID */
#define CM33_DOMAIN_ID (0x06)

#define BASELINE_SUCCESS_IND (0xD6U)
#define BASELINE_FAILURE_IND (0x29U)

#define BRIDGE_SUCCESS_STATUS (0xD6U)
#define BRIDGE_FAILURE_STATUS (0x29U)

/* Align size for sentinel to access address */
#define SENTINEL_ACCESS_ADDR_ALIGN_SIZE (8U)

/* Core Identifier */
#define RTD_CORE_ID (0x01U)
#define APD_CORE_ID (0x02U)

/* Resource Domain Control Identifier */
#define TRDC_ID (0x74U)
#define XRDC_ID (0x78U)

struct msg_hdr
{
    uint8_t ver;
    uint8_t size;
    uint8_t cmd;
    uint8_t tag;
};

struct baseline_api_rsp_code
{
    uint8_t status;
    uint8_t indication;
    uint16_t abort_code;
};

struct bridge_api_rsp_code
{
    uint8_t status;
    uint8_t rating;
    uint16_t rating_ext;
};

union response_code
{
    uint32_t code;
    struct baseline_api_rsp_code baseline_rsp_code;
    struct bridge_api_rsp_code bridge_rsp_code;
};

struct common_rsp
{
    struct msg_hdr hdr;
    union response_code rsp_code;
};

struct get_fw_version_msg_cmd
{
    struct msg_hdr hdr;
};

struct get_fw_version_msg_cmd_rsp
{
    struct common_rsp rsp;
    uint32_t fw_version;
    uint32_t commit_id;
};

struct get_fw_status_msg_cmd
{
    struct msg_hdr hdr;
};

struct get_fw_status_msg_cmd_rsp
{
    struct common_rsp rsp;
    uint8_t status;
    uint8_t rsv[3];
};

struct open_session_msg_cmd
{
    struct msg_hdr hdr;
    uint8_t mu_id;
    uint8_t interrupt_num;
    uint8_t tz;
    uint8_t did;
    uint8_t priority;
    uint8_t op_mode;
    uint16_t reserved;
};

struct open_session_msg_cmd_rsp
{
    struct common_rsp rsp;
    uint32_t session_handle;
};

struct power_down_cmd
{
    struct msg_hdr hdr;
    uint32_t size;
    uint32_t resume_addr;
};

struct power_down_cmd_rsp
{
    struct common_rsp rsp;
};

struct close_session_msg_cmd
{
    struct msg_hdr hdr;
    uint32_t session_handle;
};

struct close_session_msg_cmd_rsp
{
    struct common_rsp rsp;
};

struct rng_open_msg_cmd
{
    struct msg_hdr hdr;
    uint32_t session_handle;
    uint32_t input_address_ext;
    uint32_t output_address_ext;
    uint8_t flags;
    uint8_t rsv[3];
    uint32_t crc;
};

struct rng_open_msg_cmd_rsp
{
    struct common_rsp rsp;
    uint32_t rng_handle;
};

struct rng_close_msg_cmd
{
    struct msg_hdr hdr;
    uint32_t rng_handle;
};

struct rng_close_msg_cmd_rsp
{
    struct common_rsp rsp;
};

struct rng_get_rnd_msg_cmd
{
    struct msg_hdr hdr;
    uint32_t rng_handle;
    uint32_t out_addr;
    uint32_t out_size;
};

struct rng_get_rnd_msg_cmd_rsp
{
    struct common_rsp rsp;
};

struct dump_debug_buffer_msg_cmd
{
    struct msg_hdr hdr;
};

struct dump_debug_buffer_msg_cmd_rsp
{
    struct common_rsp rsp;
    uint32_t debug_words[20];
    uint32_t crc;
};

struct release_rdc_msg_cmd
{
    struct msg_hdr hdr;
    uint8_t core_id;
    uint8_t rdc_id;
    uint8_t rsv[2];
};

struct release_rdc_msg_cmd_rsp
{
    struct common_rsp rsp;
};

struct get_info_msg_cmd
{
    struct msg_hdr hdr;
    uint32_t rsp_msb;
    uint32_t rsp_lsb;
    uint16_t buf_size;
    uint16_t rsv;
};
struct sentinel_get_info_data
{
    uint8_t cmd;
    uint8_t ver;
    uint16_t len;
    uint16_t soc_id;
    uint16_t soc_rev;
    uint16_t lc;
    uint8_t sssm;
    uint8_t rsv;
    uint32_t uid[4];
    uint32_t sha256_rom_patch[8];
    uint32_t sha_fw[8];
    uint32_t oem_srkh[16];
    uint8_t trng;
    uint8_t csal;
    uint8_t imem;
    uint8_t rsv2;
};

enum rdc_type
{
    TRDC_TYPE,
    XRDC_TYPE,
};

/*! @name Driver version */
/*@{*/
/*! @brief sentinel driver version 2.0.3. */
#define FSL_SENTINEL_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))
/*@}*/

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

/*!
 * @brief Initialize MU interface for Sentinel access.
 */
void SENTINEL_Init(void);

/*!
 * @brief Deinitialize MU interface for Sentinel access.
 */
void SENTINEL_Deinit(void);

/*!
 * @brief Send message to Sentinel.
 *
 * @param param Command parameters pointer. Each parameter is a 32bit word.
 * @param paramCount Command parameter count.
 */
void SENTINEL_SendMessage(uint32_t *param, uint32_t paramCount);

/*!
 * @brief Receive message from Sentinel.
 *
 * @param pParam Pointer to save command parameters. Each parameter is a 32bit word.
 * @param pParamCount Inout pointer to command parameter count.
 */
void SENTINEL_ReceiveMessage(uint32_t *pParam, uint32_t *pParamCount);

/*!
 * @brief Send command to Sentinel and receive response.
 *
 * @param cmdParam Command parameters pointer. Each parameter is a 32bit word.
 * @param cmdParamCount Command parameter count.
 * @param pRespParam Pointer to save response parameters. Each parameter is a 32bit word.
 * @param pRespParamCount Inout pointer to response parameter count.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_Command(uint32_t *cmdParam, uint32_t cmdParamCount, uint32_t *pRespParam, uint32_t *pRespParamCount);

/*!
 * @brief Ping Sentinel to see if it is alive.
 *
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_Ping(void);

/*!
 * @brief Get Sentinel firmware version.
 *
 * @param pVersion Pointer to save firmware version.
 * @param pCommitSha Pointer to save first 4 bytes of the git commit ID.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_GetFirmwareVersion(uint32_t *pVersion, uint32_t *pCommitSha);

/*!
 * @brief Get Sentinel firmware status.
 *
 * @param pStatus Pointer to save firmware status. 0: No firmware in place. 1: Firmware authenticated and operational.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_GetFirmwareStatus(uint8_t *pStatus);

/*!
 * @brief Request Sentinel to enter power down.
 *
 * @param resumeAddr Base address in memory for resume code
 * @param size Length of resume code in memory
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_SetPowerDown(uint32_t resumeAddr, uint32_t size);

uint32_t SENTINEL_SessionOpen(uint32_t *pSessionHandle,
                              uint8_t muId,
                              uint8_t interruptId,
                              uint8_t tz,
                              uint8_t did,
                              uint8_t priority,
                              uint8_t operatingMode);

uint32_t SENTINEL_SessionClose(uint32_t *pSessionHandle);

uint32_t SENTINEL_RngOpen(uint32_t *pRngHandle, uint32_t sessionHandle, uint8_t flags);

uint32_t SENTINEL_RngClose(uint32_t *pRngHandle);

uint32_t SENTINEL_RngGetRandom(uint32_t *pRngHandle, uint32_t outAddr, uint32_t outSize);

uint32_t SENTINEL_DumpDebugBuffer(void);

status_t SENTINEL_RNG_GetRandomData(uint32_t output, uint32_t len);

uint32_t SENTINEL_ReleaseRDC(enum rdc_type type);

/*!
 * @brief Get Sentinel cpu version.
 *
 * @param pSoc_id Pointer to soc id.
 * @param pSoc_rev Pointer to soc revision number.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_GetSocInfo(uint16_t *pSoc_id, uint16_t *pSoc_rev);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* _FSL_SENTINEL_H_ */
