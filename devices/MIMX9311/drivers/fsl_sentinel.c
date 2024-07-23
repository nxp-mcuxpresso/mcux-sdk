/*
 * Copyright 2020-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sentinel.h"
#include "fsl_debug_console.h"
#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** MU_RTD - Register Layout Typedef */
typedef struct
{
    __I uint32_t VER;     /**< Version ID Register, offset: 0x0 */
    __I uint32_t PAR;     /**< Parameter Register, offset: 0x4 */
    uint32_t UNUSED0;     /**< Unused Register 0, offset: 0x8 */
    __I uint32_t SR;      /**< Status Register, offset: 0xC */
    __I uint32_t RSVD[9]; /**< Reserved Register, array offset: 0x10, array step: 0x4 */
    uint8_t RESERVED_0[236];
    __IO uint32_t TCR; /**< Transmit Control Register, offset: 0x120 */
    __I uint32_t TSR;  /**< Transmit Status Register, offset: 0x124 */
    __IO uint32_t RCR; /**< Receive Control Register, offset: 0x128 */
    __I uint32_t RSR;  /**< Receive Status Register, offset: 0x12C */
    uint8_t RESERVED_1[204];
    __IO uint32_t UNUSED1; /**< Unused Register 1, offset: 0x1FC */
    __O uint32_t TR[8];    /**< Transmit Register, array offset: 0x200, array step: 0x4 */
    uint8_t RESERVED_2[96];
    __I uint32_t RR[4]; /**< Receive Register, array offset: 0x280, array step: 0x4 */
} MU_RTD_Type;

/** Peripheral SENTINEL__MUA_RTD base address */
#define SENTINEL__MUA_RTD_BASE (0x47540000u)
/** Peripheral SENTINEL__MUA_RTD base pointer */
#define SENTINEL__MUA_RTD ((MU_RTD_Type *)SENTINEL__MUA_RTD_BASE)
/** Array initializer of MU_RTD peripheral base addresses */
#define MU_RTD_BASE_ADDRS      \
    {                          \
        SENTINEL__MUA_RTD_BASE \
    }
/** Array initializer of MU_RTD peripheral base pointers */
#define MU_RTD_BASE_PTRS  \
    {                     \
        SENTINEL__MUA_RTD \
    }

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sentinel"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint32_t compute_msg_crc(uint32_t *msg, uint32_t msg_len);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize MU interface for Sentinel access.
 */
void SENTINEL_Init(void)
{
    SENTINEL__MUA_RTD->TCR = 0U; /* Disable all transmit interrupts. */
    SENTINEL__MUA_RTD->RCR = 0U; /* Disable all receive interrupts. */
}

/*!
 * @brief Deinitialize MU interface for Sentinel access.
 */
void SENTINEL_Deinit(void)
{
}

/*!
 * @brief Send message to Sentinel.
 *
 * @param param Command parameters pointer. Each parameter is a 32bit word.
 * @param paramCount Command parameter count.
 */
void SENTINEL_SendMessage(uint32_t *param, uint32_t paramCount)
{
    uint32_t word;
    uint32_t i = 0U;

    while (param != NULL && paramCount > 0U)
    {
        word = *param++;

        while ((SENTINEL__MUA_RTD->TSR & ((uint32_t)MU_TSR_TE0_MASK << i)) == 0U)
        {
            /* Wait transmit register empty */
        }
        SENTINEL__MUA_RTD->TR[i] = word;
        paramCount--;
        i = (i + 1U) % SENTINEL_TR_CNT;
    }
}

/*!
 * @brief Receive message from Sentinel.
 *
 * @param pParam Pointer to save command parameters. Each parameter is a 32bit word.
 * @param pParamCount Inout pointer to command parameter count.
 */
void SENTINEL_ReceiveMessage(uint32_t *pParam, uint32_t *pParamCount)
{
    uint32_t word;
    uint32_t msgSize;
    struct msg_hdr hdr;
    uint32_t i          = 1U;
    uint32_t paramCount = (pParamCount != NULL) ? *pParamCount : 0U;

    while ((SENTINEL__MUA_RTD->RSR & MU_RSR_RF0_MASK) == 0U)
    {
        /* Wait receive register full */
    }

    word      = SENTINEL__MUA_RTD->RR[0];
    *pParam++ = word;
    if (paramCount != 0U)
    {
        paramCount--;
    }

    (void)memcpy((void *)&hdr, (void *)&word, sizeof(word));
    msgSize = hdr.size;
    assert(msgSize >= 1U);

    for (msgSize--; msgSize > 0U; msgSize--)
    {
        while ((SENTINEL__MUA_RTD->RSR & ((uint32_t)MU_RSR_RF0_MASK << i)) == 0U)
        {
            /* Wait receive register full */
        }
        word = SENTINEL__MUA_RTD->RR[i];
        if (paramCount != 0U)
        {
            *pParam++ = word;
            paramCount--;
        }

        i = (i + 1U) % SENTINEL_RR_CNT;
    }

    if (pParamCount != NULL)
    {
        /* Save received param count. */
        *pParamCount -= paramCount;
    }
    else
    {
    }
}

/*!
 * @brief Send command to Sentinel and receive response.
 *
 * @param cmdParam Command parameters pointer. Each parameter is a 32bit word.
 * @param cmdParamCount Command parameter count.
 * @param pRespParam Pointer to save response parameters. Each parameter is a 32bit word.
 * @param pRespParamCount Inout pointer to response parameter count.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_Command(uint32_t *cmdParam, uint32_t cmdParamCount, uint32_t *pRespParam, uint32_t *pRespParamCount)
{
    struct common_rsp rsp;
    uint32_t rspLen = sizeof(rsp) / sizeof(uint32_t);
    struct msg_hdr hdr;

    (void)memcpy((void *)&hdr, (void *)cmdParam, sizeof(hdr));
    (void)memset((void *)&rsp, 0, sizeof(rsp));
#ifdef FSL_RTOS_FREE_RTOS
    /* Suspends the scheduler to make sure there's only one rpc call ongoing at a time. */
    vTaskSuspendAll();
#endif

    SENTINEL_SendMessage(cmdParam, cmdParamCount);

    if (pRespParam != NULL && pRespParamCount != NULL && (uint32_t)(*pRespParamCount) > 0U)
    {
        rspLen = *pRespParamCount;
        SENTINEL_ReceiveMessage(pRespParam, pRespParamCount);
        (void)memcpy((void *)&rsp, (void *)pRespParam, sizeof(rsp));
    }
    else
    {
        SENTINEL_ReceiveMessage((uint32_t *)(void *)&rsp, (uint32_t *)&rspLen);
    }
    assert(hdr.cmd == rsp.hdr.cmd);
    assert(rspLen >= sizeof(rsp) / sizeof(uint32_t));

#ifdef FSL_RTOS_FREE_RTOS
    (void)xTaskResumeAll();
#endif

    return rsp.rsp_code.code;
}

/*!
 * @brief Ping Sentinel to see if it is alive.
 *
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_Ping(void)
{
    struct msg_hdr hdr;

    hdr.cmd  = SENTINEL_BASELINE_API_CMD_PING;
    hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    hdr.size = sizeof(hdr) / sizeof(uint32_t);
    hdr.ver  = SENTINEL_BASELINE_API_VER;

    return SENTINEL_Command((uint32_t *)(void *)&hdr, sizeof(hdr) / sizeof(uint32_t), NULL, NULL);
}

/*!
 * @brief Get Sentinel firmware version.
 *
 * @param pVersion Pointer to save firmware version.
 * @param pCommitSha Pointer to save first 4 bytes of the git commit ID.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_GetFirmwareVersion(uint32_t *pVersion, uint32_t *pCommitSha)
{
    struct get_fw_version_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);
    struct get_fw_version_msg_cmd cmdParam;

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_GET_FW_VERSION;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        if (pVersion != NULL)
        {
            *pVersion = respParam.fw_version;
        }

        if (pCommitSha != NULL)
        {
            *pCommitSha = respParam.commit_id;
        }
    }
    else
    {
    }

    return respParam.rsp.rsp_code.baseline_rsp_code.status;
}

/*!
 * @brief Get Sentinel firmware status.
 *
 * @param pStatus Pointer to save firmware status. 0: No firmware in place. 1: Firmware authenticated and operational.
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_GetFirmwareStatus(uint8_t *pStatus)
{
    struct get_fw_status_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);
    struct get_fw_status_msg_cmd cmdParam;

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_GET_FW_STATUS;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);
    if (respParam.rsp.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        if (pStatus != NULL)
        {
            *pStatus = respParam.status;
        }
    }
    else
    {
    }

    return respParam.rsp.rsp_code.baseline_rsp_code.status;
}

/*!
 * @brief Request Sentinel to enter power down.
 *
 * @param resumeAddr Base address in memory for resume code
 * @param size Length of resume code in memory
 * @return 0 for success, otherwise return error code.
 */
uint32_t SENTINEL_SetPowerDown(uint32_t resumeAddr, uint32_t size)
{
    struct power_down_cmd cmdParam;
    struct power_down_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_POWER_DOWN;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;

    cmdParam.resume_addr = resumeAddr;
    cmdParam.size        = size;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
    }
    else
    {
    }

    return respParam.rsp.rsp_code.baseline_rsp_code.status;
}

uint32_t SENTINEL_SessionOpen(uint32_t *pSessionHandle,
                              uint8_t muId,        /* MU index, MURT A is 1, MUAP A is 2 */
                              uint8_t interruptId, /* Interrupt number */
                              uint8_t tz,          /* Trust Zone(secure) flag(Not supported yet, must be set to 0) */
                              uint8_t did,         /* Domain ID */
                              uint8_t priority,    /* Priority associated with the MU in the XRDC configuration */
                              uint8_t operatingMode)
{
    struct open_session_msg_cmd cmdParam;
    struct open_session_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BRIDGE_API_CMD_SESSION_OPEN;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BRIDGE_API_VER;

    if (pSessionHandle != NULL)
    {
        cmdParam.mu_id         = muId;
        cmdParam.interrupt_num = interruptId;
        cmdParam.tz            = tz;
        cmdParam.did           = did;
        cmdParam.priority      = priority;
        cmdParam.op_mode       = operatingMode;
    }

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.bridge_rsp_code.status == BRIDGE_SUCCESS_STATUS) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        if (pSessionHandle != NULL)
        {
            *pSessionHandle = respParam.session_handle;
        }
    }
    else
    {
    }

    return respParam.rsp.rsp_code.bridge_rsp_code.status;
}

uint32_t SENTINEL_SessionClose(uint32_t *pSessionHandle)
{
    struct close_session_msg_cmd cmdParam;
    struct close_session_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd        = SENTINEL_BRIDGE_API_CMD_SESSION_CLOSE;
    cmdParam.hdr.tag        = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size       = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver        = SENTINEL_BRIDGE_API_VER;
    cmdParam.session_handle = *pSessionHandle;
    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.bridge_rsp_code.status == BRIDGE_SUCCESS_STATUS) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
    }
    else
    {
    }

    return respParam.rsp.rsp_code.bridge_rsp_code.status;
}

uint32_t compute_msg_crc(uint32_t *msg, uint32_t msg_len)
{
    uint32_t crc       = 0U;
    uint32_t i         = 0U;
    uint32_t word_nums = msg_len / sizeof(uint32_t);

    if (msg != NULL)
    {
        for (; i < word_nums; i++)
        {
            crc ^= *(msg + i);
        }
    }

    return crc;
}

uint32_t SENTINEL_RngOpen(uint32_t *pRngHandle, uint32_t sessionHandle, uint8_t flags)
{
    struct rng_open_msg_cmd cmdParam;
    struct rng_open_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BRIDGE_API_CMD_RNG_OPEN;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BRIDGE_API_VER;
    if (pRngHandle != NULL)
    {
        cmdParam.session_handle     = sessionHandle;
        cmdParam.input_address_ext  = 0U;
        cmdParam.output_address_ext = 0U;
        cmdParam.flags              = flags;
        cmdParam.crc = compute_msg_crc((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) - sizeof(uint32_t));
    }

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);
    if (respParam.rsp.rsp_code.bridge_rsp_code.status == BRIDGE_SUCCESS_STATUS) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        if (pRngHandle != NULL)
        {
            *pRngHandle = respParam.rng_handle;
        }
    }
    else
    {
    }

    return respParam.rsp.rsp_code.bridge_rsp_code.status;
}

uint32_t SENTINEL_RngClose(uint32_t *pRngHandle)
{
    struct rng_close_msg_cmd cmdParam;
    struct rng_close_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd    = SENTINEL_BRIDGE_API_CMD_SESSION_CLOSE;
    cmdParam.hdr.tag    = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size   = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver    = SENTINEL_BRIDGE_API_VER;
    cmdParam.rng_handle = *pRngHandle;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.bridge_rsp_code.status == BRIDGE_SUCCESS_STATUS) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
    }
    else
    {
    }

    return respParam.rsp.rsp_code.bridge_rsp_code.status;
}

/*
 * The memory(TCM) is used to store the random number from sentinel.
 * Note:
 *     1. The memory need align with 8 bytes.
 *     2. Must ensure that the memory is accessible by sentinel.
 */
AT_QUICKACCESS_SECTION_DATA_ALIGN(static uint8_t share_buffer[4096], SENTINEL_ACCESS_ADDR_ALIGN_SIZE);

uint32_t SENTINEL_RngGetRandom(uint32_t *pRngHandle, uint32_t outAddr, uint32_t outSize)
{
    struct rng_get_rnd_msg_cmd cmdParam;
    struct rng_get_rnd_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    if (outSize > sizeof(share_buffer))
    {
        return BRIDGE_FAILURE_STATUS;
    }

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd    = SENTINEL_BRIDGE_API_CMD_RNG_GET_RANDOM;
    cmdParam.hdr.tag    = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size   = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver    = SENTINEL_BRIDGE_API_VER;
    cmdParam.rng_handle = *pRngHandle;
    cmdParam.out_addr   = (uint32_t)share_buffer;
    cmdParam.out_size   = outSize;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.bridge_rsp_code.status == BRIDGE_SUCCESS_STATUS) /* Successful */
    {
        /* Copy the random number that processed by sentinel to the destination address that m33 provided */
        (void)memcpy((void *)outAddr, (void *)share_buffer, outSize);
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
    }
    else
    {
    }

    return respParam.rsp.rsp_code.bridge_rsp_code.status;
}

uint32_t SENTINEL_DumpDebugBuffer(void)
{
    struct dump_debug_buffer_msg_cmd cmdParam;
    struct dump_debug_buffer_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_DUMP_DEBUG_BUFFER;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        uint32_t i = 0U;
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        for (i = 0U; i < sizeof(respParam.debug_words) / sizeof(uint32_t); i++)
        {
            (void)PRINTF("\r\n respParam.debug_words[%d] = 0x%x\r\n", i, respParam.debug_words[i]);
        }
    }
    else
    {
    }

    return respParam.rsp.rsp_code.baseline_rsp_code.status;
}

status_t SENTINEL_RNG_GetRandomData(uint32_t output, uint32_t len)
{
    uint32_t sessionHandle = 0;
    uint32_t rngHandle     = 0;
    status_t result        = kStatus_Fail;

    if (SENTINEL_SessionOpen(&sessionHandle, RTC_MU_ID, 0U, 0U, CM33_DOMAIN_ID, 0U, 0U) == BRIDGE_SUCCESS_STATUS)
    {
        if (SENTINEL_RngOpen(&rngHandle, sessionHandle, 0U) == BRIDGE_SUCCESS_STATUS)
        {
            if (SENTINEL_RngGetRandom(&rngHandle, (uint32_t)output, len) == BRIDGE_SUCCESS_STATUS)
            {
                result = kStatus_Success;
            }
            else
            {
                result = kStatus_Fail;
            }
            SENTINEL_RngClose(&rngHandle);
        }
        SENTINEL_SessionClose(&sessionHandle);
    }

    return result;
}

uint32_t SENTINEL_ReleaseRDC(enum rdc_type type)
{
    struct release_rdc_msg_cmd cmdParam;
    struct release_rdc_msg_cmd_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_RELEASE_RDC;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;
    cmdParam.core_id  = (type == TRDC_TYPE) ? (RTD_CORE_ID) : (APD_CORE_ID);
    cmdParam.rdc_id   = (type == TRDC_TYPE) ? (TRDC_ID) : (XRDC_ID);

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);
    if (respParam.rsp.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
    }
    else
    {
    }

    return respParam.rsp.rsp_code.baseline_rsp_code.status;
}

uint32_t SENTINEL_GetSocInfo(uint16_t *pSoc_id, uint16_t *pSoc_rev)
{
    struct common_rsp respParam;
    uint32_t respParamCount = sizeof(respParam) / sizeof(uint32_t);
    struct get_info_msg_cmd cmdParam;
    struct sentinel_get_info_data info_data;

    (void)memset((void *)&cmdParam, 0, sizeof(cmdParam));
    cmdParam.hdr.cmd  = SENTINEL_BASELINE_API_CMD_GET_INFO;
    cmdParam.hdr.tag  = SENTINEL_MSG_HDR_CMD_TAG;
    cmdParam.hdr.size = sizeof(cmdParam) / sizeof(uint32_t);
    cmdParam.hdr.ver  = SENTINEL_BASELINE_API_VER;
    cmdParam.rsp_msb  = 0;
    cmdParam.rsp_lsb  = (uint32_t)(&info_data);
    cmdParam.buf_size = (uint16_t)sizeof(struct sentinel_get_info_data);

    (void)SENTINEL_Command((uint32_t *)(void *)&cmdParam, sizeof(cmdParam) / sizeof(uint32_t),
                           (uint32_t *)(void *)&respParam, &respParamCount);
    assert(respParamCount > 0U);

    if (respParam.rsp_code.baseline_rsp_code.status == BASELINE_SUCCESS_IND) /* Successful */
    {
        assert(respParamCount == sizeof(respParam) / sizeof(uint32_t));
        if (pSoc_id != NULL)
        {
            *pSoc_id = info_data.soc_id;
        }
        if (pSoc_rev != NULL)
        {
            *pSoc_rev = info_data.soc_rev;
        }
    }

    return respParam.rsp_code.baseline_rsp_code.status;
}
