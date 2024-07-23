/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_os_abstraction.h"
#include "fsl_debug_console.h"
#include "fsl_adapter_sdu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define os_InterruptMaskClear(irq_num) DisableIRQ(irq_num)
#define os_InterruptMaskSet(irq_num)   EnableIRQ(irq_num)
#define os_ClearPendingISR(irq_num)    NVIC_ClearPendingIRQ(irq_num)

#define SDU_TRANSFER_TASK_STACK_SIZE (1000U)

#define SDU_DEFAULT_BLOCK_SIZE (512U)

#define SDU_CMD_EVENT_BLOCK_COUNT (8U)
#define SDU_DATA_BLOCK_COUNT (8U)

#define SDU_BUFF_ALIGN (32U)
#define SDU_SIZE_ALIGN (32U)

#define SDU_SDIO_HDR_EXTRA (sizeof(sdio_header_t) + 4U)

#define SDU_ACTUAL_USE_PORT_NUM (1U)

#define SDU_MAX_CMD_BUFFER  (2U)
#define SDU_CMD_BUFFER_SIZE  (SDU_DEFAULT_BLOCK_SIZE * SDU_CMD_EVENT_BLOCK_COUNT)//(4096U + SDU_SDIO_HDR_EXTRA)

#define SDU_MAX_EVENT_BUFFER  (2U)
#define SDU_EVENT_BUFFER_SIZE  (SDU_DEFAULT_BLOCK_SIZE * SDU_CMD_EVENT_BLOCK_COUNT)//(4096U + SDU_SDIO_HDR_EXTRA)

#define SDU_MAX_DATA_BUFFER  (SDU_PORT_MAX_TRANSFER * 16U * SDU_ACTUAL_USE_PORT_NUM)
#define SDU_DATA_BUFFER_SIZE  (SDU_DEFAULT_BLOCK_SIZE * SDU_DATA_BLOCK_COUNT)//(4096U + SDU_SDIO_HDR_EXTRA)

/*! @brief Constants for transfer direction */
#define SDU_PORT_FOR_READ     (0U) /*!< For command/data upload */
#define SDU_PORT_FOR_WRITE    (1U) /*!< For command/data download */
#define SDU_PORT_MAX_TRANSFER (2U) /*!< Maximum transfer direction */


#define ROM_SDIO_VID  0x0471UL
#define ROM_SDIO_PID0 0x0208UL
#define ROM_SDIO_PID1 0x0209UL

static const uint32_t SD_CIS_DATA0_FN0 = 0x800u;

static const uint32_t SD_CIS_DATA0_FN1 = 0x880u;

/** Type command */
#define SDU_TYPE_CMD (1U)
/** Type data */
#define SDU_TYPE_DATA (0U)
/** Type event */
#define SDU_TYPE_EVENT (3U)

#define CRC_LEN (4U)

/*! @brief Buffer structure used for transfer */
typedef struct _transfer_buffer
{
    uint32_t user_data; /*!< User data attached with this buffer */
    uint16_t data_size; /*!< Data buffer full size */
    uint16_t data_len;  /*!< Valid data length */
    uint8_t *data_addr; /*!< Data address. */
} transfer_buffer_t;

/*! @brief SDIO transfer callback structure. */
typedef void (*sdioslv_transfer_callback_t)(
    status_t status, sdioslv_func_t func, sdioslv_port_t port, transfer_buffer_t *buffer, void *user_data);

/*! @brief Data structure to configure SDIO handle for specific function */
typedef struct _sdioslv_handle_config
{
    uint8_t fun_num;        /*!< SDIO function number (1..7). */
    uint8_t used_port_num;  /*!< How many data ports are used inside this function */
    uint8_t cpu_num;        /*!< Specify interrupt should be generated to which CPU */
    uint8_t reserved;       /*!< Reserved */
    uint8_t cmd_tx_format;  /*!< Command Tx length format. 0: no tx_len, 1: 2 bytes, 2: 3 bytes */
    uint8_t cmd_rd_format;  /*!< Command Rx length format. 0: blk_num * blk_size, 1: CMD_PORT_RD_LEN */
    uint8_t data_tx_format; /*!< Data Tx length format. 0: no tx_len, 1: 2 bytes, 2: 3 bytes */
    uint8_t data_rd_format; /*!< Data Rx length format.
                              0: blk_num * blk_size, 1: PORT_RD_LEN[15:0], 2: PORT1_RD_LEN[7:0] && PORT0_RD_LEN[15:0] */
    /* Callback function for command */
    sdioslv_transfer_callback_t cmd_callback; /*!< Command callback function. */
    void *cmd_user_data;                      /*!< Parameter passed to the callback. */
    /* Callback function for data */
    sdioslv_transfer_callback_t data_callback; /*!< Data callback function. */
    void *data_user_data;                      /*!< Parameter passed to the callback. */
} sdioslv_handle_config_t;


/*! @brief Data structure used to handle command or data port */
typedef struct _sdioslv_port_ctrl
{
    uint8_t valid;             /*!< Indicate if this port is valid, 1 means valid */
    uint8_t occupied;          /*!< Indicate if this port is occupied for transfer, 1 means occupied */
    uint8_t reserved[2];       /*!< Reserved */
    transfer_buffer_t *buffer; /*!< Assigned buffer */
} sdioslv_port_ctrl_t;

/*! @brief Data structure used to handle SDU fucntion */
typedef struct _sdioslv_fun_ctrl
{
    uint8_t initialized;          /*!< Indicate if this function is initialized, 1 means initialized */
    uint8_t enable;               /*!< Indicate if this function is enabled, 1 means enabled */
    uint8_t curr_data_tx_port;    /*!< current available data tx port */
    uint8_t reserved;             /*!< Reserved */
    sdioslv_sdu_regmap_t *regmap; /*!< SDU register map */
    sdioslv_port_ctrl_t cmd_port[SDU_PORT_MAX_TRANSFER];                    /*!< command port */
    sdioslv_port_ctrl_t data_port[SDU_PORT_MAX_TRANSFER][SDU_MAX_PORT_NUM]; /*!< data ports */
    sdioslv_handle_config_t config;                                         /*!< User configurations */
} sdioslv_fun_ctrl_t;

/*! @brief Data structure used to handle SDU chip */
typedef struct _sdioslv_sdu_ctrl
{
    uint8_t initialized;                                 /*!< Indicate if SDU is initialized, 1 means initialized */
    uint8_t cpu_num;                                     /*!< Specify interrupt should be generated to which CPU */
    uint8_t used_fun_num;                                /*!< How many functions will be used */
    uint8_t reserved;                                    /*!< Reserved */
    sdioslv_fun_ctrl_t *func_ctrl[SDU_MAX_FUNCTION_NUM]; /*!< Pointer to function handle */
} sdioslv_sdu_ctrl_t;

typedef struct _sdu_buffer
{
    list_element_t link;
    transfer_buffer_t buffer;
} sdu_buffer_t;

typedef struct _sdu_stat
{
    uint32_t err_tx_cmd_sdio_hdr;
    uint32_t err_tx_cmd_call_cb;
    uint32_t drop_tx_cmd;
    uint32_t succ_tx_cmd;
    uint32_t err_tx_data_sdio_hdr;
    uint32_t err_tx_data_call_cb;
    uint32_t drop_tx_data;
    uint32_t succ_tx_data;
} sdu_stat_t;


/*! @brief SDU initialization state. */
typedef enum _sdu_state_t
{
    SDU_UNINITIALIZED,
    SDU_INITIALIZING,
    SDU_INITIALIZED
}sdu_state_t;


typedef void *sdioslv_handle_t;

typedef struct _sdu_ctrl
{
    sdu_state_t sdu_state;
    sdioslv_handle_t handle;
    list_label_t cmd_q[SDU_PORT_MAX_TRANSFER];
    list_label_t cmd_free_buffer[SDU_PORT_MAX_TRANSFER];
    list_label_t event_q;
    list_label_t event_free_buffer;
    list_label_t data_q[SDU_PORT_MAX_TRANSFER];
    list_label_t data_free_buffer;
    sdu_callback_t sdu_cb_fn[SDU_TYPE_FOR_WRITE_MAX];
    sdu_stat_t stat;
    OSA_TASK_HANDLE_DEFINE(recvTaskId);
    OSA_EVENT_HANDLE_DEFINE(event);
} sdu_ctrl_t;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
#define SDU_TASK_PRIORITY (6U)
static void SDU_RecvTask(void *param);
static OSA_TASK_DEFINE(SDU_RecvTask, SDU_TASK_PRIORITY, 1, SDU_TRANSFER_TASK_STACK_SIZE, false);

static sdu_ctrl_t ctrl_sdu;
static sdu_buffer_t cmd_buffer[SDU_PORT_MAX_TRANSFER][SDU_MAX_CMD_BUFFER];
static sdu_buffer_t event_buffer[SDU_MAX_EVENT_BUFFER];
static sdu_buffer_t data_buffer[SDU_MAX_DATA_BUFFER];

typedef uint8_t cmd_trans_buffer_t[SDK_SIZEALIGN(SDU_CMD_BUFFER_SIZE, SDU_SIZE_ALIGN)];
typedef uint8_t event_trans_buffer_t[SDK_SIZEALIGN(SDU_EVENT_BUFFER_SIZE, SDU_SIZE_ALIGN)];
typedef uint8_t data_trans_buffer_t[SDK_SIZEALIGN(SDU_DATA_BUFFER_SIZE, SDU_SIZE_ALIGN)];

SDK_ALIGN(static cmd_trans_buffer_t cmd_trans_buffer[SDU_MAX_CMD_BUFFER], SDU_BUFF_ALIGN);
SDK_ALIGN(static cmd_trans_buffer_t cmdrsp_trans_buffer[SDU_MAX_CMD_BUFFER], SDU_BUFF_ALIGN);
SDK_ALIGN(static event_trans_buffer_t event_trans_buffer[SDU_MAX_EVENT_BUFFER], SDU_BUFF_ALIGN);
SDK_ALIGN(static data_trans_buffer_t data_trans_buffer[SDU_MAX_DATA_BUFFER], SDU_BUFF_ALIGN);

static sdioslv_sdu_ctrl_t sdu_ctrl;

#ifndef BIT
#define BIT(n) (1U << (n))
#endif

#define SDU_DBG_LEVEL_WARN BIT(3U)
#define SDU_DBG_LEVEL_ERROR BIT(2U)
#define SDU_DBG_LEVEL_DEBUG BIT(1U)
#define SDU_DBG_LEVEL_DUMP BIT(0U)

static uint32_t sdu_dbg_level = SDU_DBG_LEVEL_WARN | SDU_DBG_LEVEL_ERROR;

#define sdu_e(_fmt_, ...) \
    if (((uint32_t)(sdu_dbg_level) & (uint32_t)(SDU_DBG_LEVEL_ERROR)) != 0U) \
        {(void)PRINTF("[SDU]Error: " _fmt_ "\n\r", ##__VA_ARGS__);}
#define sdu_w(_fmt_, ...) \
    if (((uint32_t)(sdu_dbg_level) & (uint32_t)(SDU_DBG_LEVEL_WARN)) != 0U) \
        {(void)PRINTF("[SDU]Warn: " _fmt_ "\n\r", ##__VA_ARGS__);}

#define CONFIG_ADAPTER_SDU_DEBUG
#ifdef CONFIG_ADAPTER_SDU_DEBUG
#define sdu_d(_fmt_, ...) \
    if (((uint32_t)(sdu_dbg_level) & (uint32_t)(SDU_DBG_LEVEL_DEBUG)) != 0U) \
        {(void)PRINTF("[SDU]Debug: " _fmt_ "\n\r", ##__VA_ARGS__);}
#else
#define sdu_d(_fmt_, ...)
#endif


/*******************************************************************************
 * Public Functions
 ******************************************************************************/


/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static status_t SDU_InnerInit(void);
static void SDU_InnerDeinit(void);
static bool SDU_IsLinkUp(void);

static void SDU_CmdCallback(
    status_t status, sdioslv_func_t func, sdioslv_port_t port, transfer_buffer_t *buffer, void *user_data);
static void SDU_DataCallback(
    status_t status, sdioslv_func_t func, sdioslv_port_t port, transfer_buffer_t *buffer, void *user_data);

static status_t SDU_SendCmdNonBlocking(sdioslv_handle_t handle, transfer_buffer_t *buffer);
static status_t SDU_RefillCmdBuffer(sdu_ctrl_t *ctrl);
static status_t SDU_SendDataNonBlocking(sdioslv_handle_t handle, transfer_buffer_t *buffer);
static status_t SDU_RefillDataBuffer(sdu_ctrl_t *ctrl, sdioslv_port_t port);
static status_t SDU_RefillFreePortsDataBuffer(sdu_ctrl_t *ctrl);

static status_t SDU_RecvCmdProcess(void);
static status_t SDU_RecvDataProcess(void);

#define DUMP_WRAPAROUND 16U
/** Dump buffer in hex format on console
 *
 * This function prints the received buffer in HEX format on the console
 *
 * \param[in] data Pointer to the data buffer
 * \param[in] len Length of the data
 */
static inline void SDU_dump_hex(uint32_t level, const void *data, unsigned len)
{
    unsigned int i    = 0;
    const char *data8 = (const char *)data;

    if ((level & SDU_DBG_LEVEL_DUMP) == 0U)
	{
        return;
	}
	
    (void)PRINTF("**** Dump @ %p Len: %d ****\n\r", data, len);
    while (i < len)
    {
        (void)PRINTF("%02x ", data8[i++]);
        if ((i % DUMP_WRAPAROUND) == 0U)
        {
            (void)PRINTF("\n\r");
        }
    }

    (void)PRINTF("\n\r******** End Dump *******\n\r");
}


/*!
 * @brief SDU data initialization function.
 *
 * @param fun_num Specify how many functions will be used.
 . @param cpu_num Specify interrupt should be generated to which CPU.
 * @retval #kStatus_Success Initialize SDU sucessfully.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_Fail Fail to initialize SDU.
 */
static status_t SDU_InitData(uint32_t used_fun_num, sdioslv_int_cpu_num_t cpu_num)
{
    uint32_t fun_num = 0U;
    sdioslv_fun_ctrl_t *fun_ctrl;
    OSA_SR_ALLOC();

    if (used_fun_num > (uint32_t)SDU_MAX_FUNCTION_NUM)
    {
        return (status_t)kStatus_InvalidArgument;
    }
	
    if (sdu_ctrl.initialized != 0U)
    {
        return (status_t)kStatus_Success;
    }
	
    OSA_ENTER_CRITICAL();
    for (fun_num = 0; fun_num < used_fun_num; fun_num++)
    {
        fun_ctrl = (sdioslv_fun_ctrl_t *)OSA_MemoryAllocate(sizeof(sdioslv_fun_ctrl_t));
        if (fun_ctrl == NULL)
        {
            break;
        }
        /* OSA_MemoryAllocate() sets contents of allocated memory to be zero */
        fun_ctrl->regmap = (sdioslv_sdu_regmap_t *)((uint32_t)SDU_SDIO_CFG_BASE + (uint32_t)(SDIO_CCR_FUNC_OFFSET *(uint32_t)(fun_num + 1U)));
        sdu_ctrl.func_ctrl[fun_num] = fun_ctrl;
    }

    if (fun_num < used_fun_num)
    {
        while(fun_num > 0U)
        {
            OSA_MemoryFree(sdu_ctrl.func_ctrl[fun_num - 1U]);
            fun_num--;
        }
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_Fail;
    }

    SDU_REGS8_SETBITS(SDIO_CCR_FUNC0_CARD_INT_MSK, cpu_num);

    sdu_ctrl.used_fun_num = (uint8_t)used_fun_num;
    sdu_ctrl.cpu_num      = (uint8_t)cpu_num;
    sdu_ctrl.initialized  = 1;
    OSA_EXIT_CRITICAL();
    return (status_t)kStatus_Success;
}

/*!
 * @brief SDU data deinitialization function.
 *
 * @param void None.
 */
static void SDU_DeinitData(void)
{
    uint8_t fun_num;
    OSA_SR_ALLOC();

    if (sdu_ctrl.initialized == 0U)
    {
        return;
    }
    OSA_ENTER_CRITICAL();
    for (fun_num = 0U; fun_num < sdu_ctrl.used_fun_num; fun_num++)
    {
        if (sdu_ctrl.func_ctrl[fun_num] != NULL)
        {
            OSA_MemoryFree(sdu_ctrl.func_ctrl[fun_num]);
        }
    }
    sdu_ctrl.used_fun_num = 0;
    sdu_ctrl.cpu_num      = 0;
    sdu_ctrl.initialized  = 0;
    OSA_EXIT_CRITICAL();
}

/*!
 * @brief Create handle for specified function.
 *
 * @param config Configuration used to create this handle.
 * @retval !NULL Created handle pointer.
 * @retval NULL Fail to create handle.
 */
static sdioslv_handle_t SDU_CreateHandle(sdioslv_handle_config_t *config)
{
    uint8_t fun_num;
    sdioslv_fun_ctrl_t *fun_ctrl;
    sdioslv_sdu_regmap_t *sdu_fsr;
    uint8_t i, j;
    OSA_SR_ALLOC();

    fun_num = config->fun_num;
    if ((fun_num < 1U) || (fun_num > sdu_ctrl.used_fun_num))
    {
        return NULL;
    }

    if (config->used_port_num > (uint8_t)(SDU_MAX_PORT_NUM))
    {
        return NULL;
    }
	
    if ((config->cpu_num != (uint8_t)kSDIOSLV_INT_CPUNum1) && (config->cpu_num != (uint8_t)kSDIOSLV_INT_CPUNum2) &&
        (config->cpu_num != (uint8_t)kSDIOSLV_INT_CPUNum3))
    {
        return NULL;
    }

    if ((config->cmd_tx_format > 2U) || (config->cmd_rd_format > 1U))
    {
        return NULL;
    }
	
    if ((config->data_tx_format > 2U) || (config->data_rd_format > 2U))
    {
        return NULL;
    }
	
    if ((config->cmd_callback == NULL) || (config->data_callback == NULL))
    {
        return NULL;
    }
	
    OSA_ENTER_CRITICAL();
    fun_ctrl = sdu_ctrl.func_ctrl[fun_num - 1U];
    if (fun_ctrl == NULL)
    {
        goto create_err;
    }
	
    sdu_fsr = fun_ctrl->regmap;
    sdu_fsr->RdBitMap			= 0;
    sdu_fsr->WrBitMap			= 0;
    sdu_fsr->FunctionCardIntMsk = config->cpu_num;
    sdu_fsr->CardIntMask		= SDIO_CCR_CIM_MASK ;//SDIO_CCR_CIM_MASK | SDIO_CCR_CIM_PwrUp;
    /* toggle SDIO_CCR_CIC_DnLdOvr */
    sdu_fsr->CardIntStatus = SDIO_CCR_CIC_DnLdOvr;
    sdu_fsr->CardIntStatus = 0;
    sdu_fsr->CardIntMode   = 0;//0x00000C02;//CARD_INT_MODE_MSK;
    sdu_fsr->CmdPortConfig =
        (uint32_t)((config->cmd_tx_format << (uint8_t)CMD_TX_LEN_BIT_OFFSET) | (config->cmd_rd_format << (uint8_t)CMD_RD_LEN_BIT_OFFSET));
    sdu_fsr->Config2 = (uint32_t)((uint8_t)CONFIG2_DEFAULT_SETTING | (config->data_tx_format << (uint8_t)(CONFIG2_TX_LEN_BIT_OFFSET)) |
        (config->data_rd_format << (uint8_t)(CONFIG2_RD_LEN_BIT_OFFSET)));

    for (i = 0; i < SDU_PORT_MAX_TRANSFER; i++)
    {
        fun_ctrl->cmd_port[i].valid = 1;
        for (j = 0; j < config->used_port_num; j++)
        {
            fun_ctrl->data_port[i][j].valid = 1;
        }
    }

    (void)memcpy(&fun_ctrl->config, config, sizeof(*config));
    fun_ctrl->initialized = 1;
    fun_ctrl->enable      = 1;
    OSA_EXIT_CRITICAL();

    return (sdioslv_handle_t)fun_ctrl;

create_err:
    OSA_EXIT_CRITICAL();
    return NULL;
}


static status_t SDU_InnerInit(void)
{
    sdioslv_handle_config_t config;
    status_t rc;
    uint32_t i = 0;
    uint32_t direction = 0;
    transfer_buffer_t *trans_buf;

    rc = SDU_InitData(SDU_USED_FUN_NUM, SDU_INT_CPU_NUM);
    if (rc != kStatus_Success)
    {
        sdu_e("Fail to initialize SDU: %d\r\n", (uint32_t)rc);
        return rc;
    }
    config.fun_num        = 1;
    config.used_port_num  = SDU_ACTUAL_USE_PORT_NUM;
    config.cpu_num        = 1;//kSDIOSLV_INT_CPUNum3;
    config.cmd_tx_format  = 2;
    config.cmd_rd_format  = 1;
    config.data_tx_format = 2;
    config.data_rd_format = 1;
    config.cmd_callback   = SDU_CmdCallback;
    config.cmd_user_data  = &ctrl_sdu;
    config.data_callback  = SDU_DataCallback;
    config.data_user_data = &ctrl_sdu;

    for (direction = 0; direction < SDU_PORT_MAX_TRANSFER; direction++)
    {
        LIST_Init(&ctrl_sdu.cmd_q[direction], 0);
        LIST_Init(&ctrl_sdu.cmd_free_buffer[direction], SDU_MAX_CMD_BUFFER);
        LIST_Init(&ctrl_sdu.data_q[direction], 0);
    }
    LIST_Init(&ctrl_sdu.data_free_buffer, SDU_MAX_DATA_BUFFER);
    LIST_Init(&ctrl_sdu.event_q, 0);
    LIST_Init(&ctrl_sdu.event_free_buffer, SDU_MAX_EVENT_BUFFER);

    for (direction = 0; direction < SDU_PORT_MAX_TRANSFER; direction++)
    {
        for (i = 0; i < SDU_MAX_CMD_BUFFER; i++)
        {
            trans_buf            = &cmd_buffer[direction][i].buffer;
            if (direction == SDU_PORT_FOR_WRITE)
            {
                trans_buf->data_addr = (uint8_t *)cmd_trans_buffer[i];
                trans_buf->data_size = (uint16_t)sizeof(cmd_trans_buffer[i]);
                sdu_d("%s: cmd_trans_buffer[%u]=%p sizeof=%lu\r\n", __FUNCTION__, i, cmd_trans_buffer[i], sizeof(cmd_trans_buffer[i]));
            }
            else
            {
                trans_buf->data_addr = (uint8_t *)cmdrsp_trans_buffer[i];
                trans_buf->data_size = (uint16_t)sizeof(cmdrsp_trans_buffer[i]);
                sdu_d("%s: cmdrsp_trans_buffer[%u]=%p sizeof=%lu\r\n", __FUNCTION__, i, cmdrsp_trans_buffer[i], sizeof(cmdrsp_trans_buffer[i]));
            }
            if (trans_buf->data_addr == NULL)
            {
                sdu_e("%s: cmd free list buffer alloc fail!\r\n", __FUNCTION__);
                rc = kStatus_Fail;
                goto done;
            }
            trans_buf->data_len  = 0;
            trans_buf->user_data = 0;
            (void)LIST_AddTail(&ctrl_sdu.cmd_free_buffer[direction], &cmd_buffer[direction][i].link);
            sdu_d("%s: trans_buf: data_addr=%p data_size=%u\r\n", __FUNCTION__, trans_buf->data_addr, trans_buf->data_size);
        }
    }

    for (i = 0; i < SDU_MAX_EVENT_BUFFER; i++)
    {
        trans_buf            = &event_buffer[i].buffer;
        trans_buf->data_addr = (uint8_t *)event_trans_buffer[i];
        if (trans_buf->data_addr == NULL)
        {
            sdu_e("%s: event free list buffer alloc fail!\r\n", __FUNCTION__);
            rc = kStatus_Fail;
            goto done;
        }
        trans_buf->data_size = (uint16_t)sizeof(event_trans_buffer[i]);
        trans_buf->data_len  = 0;
        trans_buf->user_data = 0;
        (void)LIST_AddTail(&ctrl_sdu.event_free_buffer, &event_buffer[i].link);
        sdu_d("%s: event_trans_buffer[%u]=%p sizeof=%lu\r\n", __FUNCTION__, i, event_trans_buffer[i], sizeof(event_trans_buffer[i]));
        sdu_d("%s: trans_buf: data_addr=%p data_size=%u\r\n", __FUNCTION__, trans_buf->data_addr, trans_buf->data_size);
    }

    for (i = 0; i < (uint32_t)SDU_MAX_DATA_BUFFER; i++)
    {
        trans_buf            = &data_buffer[i].buffer;
        trans_buf->data_addr = (uint8_t *)data_trans_buffer[i];
        if (trans_buf->data_addr == NULL)
        {
            sdu_e("%s: data free list buffer alloc fail!\r\n", __FUNCTION__);
            rc = kStatus_Fail;
            goto done;
        }
        trans_buf->data_size = (uint16_t)sizeof(data_trans_buffer[i]);
        trans_buf->data_len  = 0;
        trans_buf->user_data = 0;
        (void)LIST_AddTail(&ctrl_sdu.data_free_buffer, &data_buffer[i].link);
        sdu_d("%s: data_trans_buffer[%u]=%p sizeof=%lu\r\n", __FUNCTION__, i, data_trans_buffer[i], sizeof(data_trans_buffer[i]));
        sdu_d("%s: trans_buf: data_addr=%p data_size=%u\r\n", __FUNCTION__, trans_buf->data_addr, trans_buf->data_size);
    }

    ctrl_sdu.handle = SDU_CreateHandle(&config);
    if (ctrl_sdu.handle == NULL)
    {
        sdu_e("Fail to create handle for function %d\r\n", config.fun_num);
        rc = kStatus_Fail;
        goto done;
    }

    /* reguest for command buffer */
    config.cmd_callback(kStatus_SDIOSLV_FuncRequestBuffer, (sdioslv_func_t)(config.fun_num), kSDIOSLV_CmdPortNum0, NULL,
                         config.cmd_user_data);

    /* request for data buffer */
    for (i = 0; i < config.used_port_num; i++)
    {
        config.data_callback(kStatus_SDIOSLV_FuncRequestBuffer, (sdioslv_func_t)(config.fun_num), (sdioslv_port_t)i, NULL,
                              config.data_user_data);
    }
done:
    if (rc != kStatus_Success)
    {
        SDU_DeinitData();
    }
	
    return rc;
}

static void SDU_InnerDeinit(void)
{
    SDU_DeinitData();

    ctrl_sdu.sdu_state = SDU_UNINITIALIZED;
}

static void SDU_CmdCallback(
    status_t status, sdioslv_func_t func, sdioslv_port_t port, transfer_buffer_t *buffer, void *user_data)
{
    sdu_ctrl_t *ctrl = (sdu_ctrl_t *)user_data;
    sdu_buffer_t *cmd_event_buf = NULL;

    switch (status)
    {
        case (status_t)kStatus_SDIOSLV_FuncRequestBuffer:
            (void)SDU_RefillCmdBuffer(ctrl);
            break;
        case (status_t)kStatus_SDIOSLV_FuncReadComplete:
            cmd_event_buf = (sdu_buffer_t *)buffer->user_data;
            (void)LIST_AddTail(&ctrl_sdu.cmd_q[SDU_PORT_FOR_WRITE], &cmd_event_buf->link);
            (void)OSA_EventSet(ctrl->event, SDU_CMD_RECEIVED);
            break;
        case (status_t)kStatus_SDIOSLV_FuncSendComplete:
            cmd_event_buf = (sdu_buffer_t *)buffer->user_data;
            if (&(cmd_event_buf->link) == LIST_GetHead(&ctrl_sdu.cmd_q[SDU_PORT_FOR_READ]))
            {
                (void)LIST_RemoveElement(&cmd_event_buf->link);
                (void)LIST_AddTail(&ctrl_sdu.cmd_free_buffer[SDU_PORT_FOR_READ], &cmd_event_buf->link);
            }
            else if (&(cmd_event_buf->link) == LIST_GetHead(&ctrl_sdu.event_q))
            {
                (void)LIST_RemoveElement(&cmd_event_buf->link);
                (void)LIST_AddTail(&ctrl_sdu.event_free_buffer, &cmd_event_buf->link);
            }
            else
            {
                sdu_e("%s: Unknown cmd_event_buf=%p buffer=%p.\n\r", __func__, cmd_event_buf, buffer);
            }
            break;
        default:
            sdu_e("%s: Unknown callback status %d.\n\r", __func__, status);
            break;
    }

	return;
}

static void SDU_DataCallback(
    status_t status, sdioslv_func_t func, sdioslv_port_t port, transfer_buffer_t *buffer, void *user_data)
{
    sdu_ctrl_t *ctrl = (sdu_ctrl_t *)user_data;
    sdu_buffer_t *data_buf = NULL;
    sdio_header_t *sdio_hdr = (sdio_header_t *)(buffer->data_addr);

    switch (status)
    {
        case (status_t)kStatus_SDIOSLV_FuncRequestBuffer:
            (void)SDU_RefillDataBuffer(ctrl, port);
            break;
#if 0
        case kStatus_SDIOSLV_FuncRequestFreePortsBuffer:
            SDU_RefillFreePortsDataBuffer(ctrl);
            break;
#endif
        case (status_t)kStatus_SDIOSLV_FuncReadComplete:
            sdu_d("Dump %p %p len=%u\n\r", buffer, buffer->data_addr, MIN(sdio_hdr->len, buffer->data_size));
            SDU_dump_hex(sdu_dbg_level, buffer->data_addr, sdio_hdr->len);
            data_buf = (sdu_buffer_t *)buffer->user_data;
            (void)LIST_AddTail(&ctrl_sdu.data_q[SDU_PORT_FOR_WRITE], &data_buf->link);
            (void)OSA_EventSet(ctrl->event, SDU_DATA_RECEIVED);
            break;
        case (status_t)kStatus_SDIOSLV_FuncSendComplete:
            data_buf = (sdu_buffer_t *)buffer->user_data;
            (void)LIST_RemoveElement(&data_buf->link);
            (void)LIST_AddTail(&ctrl_sdu.data_free_buffer, &data_buf->link);
            break;
        default:
            sdu_e("Unknown callback status %d (%s).\n\r", status, __func__);
            break;
    }
	return;
}


#ifdef CONFIG_SDIO_TEST_LOOPBACK

#if 0
static void SDU_TransferCmdRecv(sdu_ctrl_t *ctrl)
{
    sdu_buffer_t *cmd_rcv = NULL;

    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    while (1)
    {
        cmd_rcv = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->cmd_q[SDU_PORT_FOR_WRITE]);
        if (!cmd_rcv)
            break;

        //cmd_send                  = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->cmd_free_buffer[SDU_PORT_FOR_READ]);
        cmd_rcv->buffer.data_len = ((sdio_header_t *)(cmd_rcv->buffer.data_addr))->len;
        //*(uint16_t *)((uint8_t *)(cmd_rcv->buffer.data_addr) + 4) |= 0x8000;
        sdu_d("CmdRecv data_len: %d", cmd_rcv->buffer.data_len);
        SDU_dump_hex(sdu_dbg_level, cmd_rcv->buffer.data_addr, cmd_rcv->buffer.data_len);

        //cmd_send->buffer.data_len = cmd_rcv->buffer.data_len;
        //memcpy(cmd_send->buffer.data_addr, cmd_rcv->buffer.data_addr, cmd_send->buffer.data_len);
        //cmd_send->buffer.user_data = (uint32_t)cmd_send;
        //SDU_SendCmdNonBlocking(ctrl->handle, &cmd_send->buffer);

        SDU_Send(SDU_TYPE_FOR_READ_CMD, cmd_rcv->buffer.data_addr + sizeof(sdio_header_t),
            cmd_rcv->buffer.data_len - sizeof(sdio_header_t));

        (void)LIST_AddTail(&ctrl->cmd_free_buffer[SDU_PORT_FOR_WRITE], &cmd_rcv->link);
        SDU_RefillCmdBuffer(&ctrl_sdu);
    }
    OSA_EXIT_CRITICAL();
}

static void SDU_TransferDataRecv(sdu_ctrl_t *ctrl)
{
    sdu_buffer_t *data_rcv = NULL;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    while (1)
    {
        data_rcv = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->data_q[SDU_PORT_FOR_WRITE]);
        if (!data_rcv)
            break;

        //data_send                  = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->data_free_buffer);
        data_rcv->buffer.data_len = ((sdio_header_t *)(data_rcv->buffer.data_addr))->len;
        sdu_d("DataRecv data_len: %d\r\n", data_rcv->buffer.data_len);
        SDU_dump_hex(sdu_dbg_level, data_rcv->buffer.data_addr, data_rcv->buffer.data_len);

        //data_send->buffer.data_len = data_rcv->buffer.data_len;
        //memcpy(data_send->buffer.data_addr, data_rcv->buffer.data_addr, data_send->buffer.data_len);
        //data_send->buffer.user_data = (uint32_t)data_send;
        //SDU_SendDataNonBlocking(ctrl->handle, &data_send->buffer);

        SDU_Send(SDU_TYPE_FOR_READ_DATA, data_rcv->buffer.data_addr + sizeof(sdio_header_t),
            data_rcv->buffer.data_len - sizeof(sdio_header_t));

        (void)LIST_AddTail(&ctrl->data_free_buffer, &data_rcv->link);
        SDU_RefillFreePortsDataBuffer(&ctrl_sdu);

        if (!LIST_GetSize(&ctrl->data_q[SDU_PORT_FOR_WRITE]))
            break;

        /* Let command get priority */
        if (LIST_GetSize(&ctrl->cmd_q[SDU_PORT_FOR_WRITE]))
        {
            OSA_EventSet(ctrl->event, SDU_DATA_RECEIVED);
            break;
        }
    }
    OSA_EXIT_CRITICAL();
}

static void SDU_TransferTask(void *param)
{
    sdu_ctrl_t *ctrl     = (sdu_ctrl_t *)param;
    osa_event_flags_t ev = 0;

    do
    {
        if (KOSA_StatusSuccess ==
            OSA_EventWait((osa_event_handle_t)ctrl->event, osaEventFlagsAll_c, 0U, osaWaitForever_c, &ev))
        {
            if (ev & SDU_CMD_RECEIVED)
                SDU_TransferCmdRecv(ctrl);

            if (ev & SDU_DATA_RECEIVED)
                SDU_TransferDataRecv(ctrl);
        }
    } while (0U != gUseRtos_c);
}
#endif

static void SDU_LoopbackRecvCmdHandler(void *tlv, size_t tlv_sz)
{
    assert(NULL != tlv);
    assert(0U != tlv_sz);

    sdu_d("RecvCmd len: %d", tlv_sz);
    SDU_dump_hex(sdu_dbg_level, tlv, tlv_sz);

    (void)SDU_Send(SDU_TYPE_FOR_READ_CMD, (uint8_t *)tlv, (uint16_t)(tlv_sz + CRC_LEN));
}

static void SDU_LoopbackRecvDataHandler(void *tlv, size_t tlv_sz)
{
    assert(NULL != tlv);
    assert(0U != tlv_sz);

    sdu_d("RecvData len: %d\r\n", tlv_sz);
    SDU_dump_hex(sdu_dbg_level, tlv, tlv_sz);

    (void)SDU_Send(SDU_TYPE_FOR_READ_DATA, (uint8_t *)tlv, (uint16_t)(tlv_sz + CRC_LEN));
}
#endif

static void SDU_RecvTask(void *param)
{
    sdu_ctrl_t *ctrl	 = (sdu_ctrl_t *)param;
    osa_event_flags_t ev = 0;

    do
    {
        if (KOSA_StatusSuccess ==
                OSA_EventWait((osa_event_handle_t)ctrl->event, osaEventFlagsAll_c, 0U, osaWaitForever_c, &ev))
        {
            if ((ev & SDU_CMD_RECEIVED) != 0U)
            {
                (void)SDU_RecvCmdProcess();
            }
			
            if ((ev & SDU_DATA_RECEIVED) != 0U)
            {
			    (void)SDU_RecvDataProcess();
            }
        }
    } while (0U != gUseRtos_c);

}

/*!
 * @brief SDU Link is up or not.
 *
 * Call this API to check if SDU Link is up or not.
 *
 * @param void.
 * @retval TRUE SDU Link is UP.
 * @retval FALSE SDU Link is not UP.
 */
static bool SDU_IsLinkUp(void)
{
    if (SDU_INITIALIZED == ctrl_sdu.sdu_state)
    {
        return true;
    }
	
    return false;
}

#if 0
/*!
 * @brief SDU send data transfer checking.
 *
 * Call this API to check if tranmist is available.
 *
 * @param void.
 * @retval TRUE all data slots are occupied.
 * @retval FALSE data transmit is availalbe.
 */
bool SDU_IsSendDataFull(void)
{
    sdioslv_fun_ctrl_t *fun_ctrl = NULL;
    bool data_full;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    fun_ctrl = (sdioslv_fun_ctrl_t *)&(ctrl_sdu.handle);
    if (fun_ctrl->curr_data_tx_port >= fun_ctrl->config.used_port_num)
        data_full = true;
    else
        data_full = false;
    OSA_EXIT_CRITICAL();

    return data_full;
}

/*!
 * @brief SDU check and move available data port pointer.
 *
 * @param fun_ctrl Spcified which function to be adjusted for available data port pointer.
 * @retval None.
 */
static inline void SDU_AdjustAvailDataPort(sdioslv_fun_ctrl_t *fun_ctrl)
{
    int i;
    OSA_SR_ALLOC();

    if (!fun_ctrl)
        return;

    OSA_ENTER_CRITICAL();
    for (i = 0; i < fun_ctrl->config.used_port_num; i++)
    {
        if (!fun_ctrl->data_port[SDU_PORT_FOR_READ][i].occupied)
        {
            fun_ctrl->curr_data_tx_port = i;
            break;
        }
    }
    if (i == fun_ctrl->config.used_port_num)
        fun_ctrl->curr_data_tx_port = SDU_MAX_PORT_NUM;
    OSA_EXIT_CRITICAL();
}
#endif

/*!
 * @brief SDU process interrupt status 'SDIO_CCR_CIC_CmdUpLdOvr'.
 *
 * @param fun_ctrl Spcified which function to be processed.
 * @retval None.
 */
static inline void SDU_ProcessCmdUpLdOvr(sdioslv_fun_ctrl_t *fun_ctrl)
{
    sdioslv_port_ctrl_t *port_ctrl = NULL;
    sdu_buffer_t *send_buffer = NULL;
    //sdu_buffer_t *return_buf = NULL;
    status_t status = kStatus_Success;

    port_ctrl = &fun_ctrl->cmd_port[SDU_PORT_FOR_READ];

    if ((port_ctrl->valid == 0U) || (port_ctrl->occupied == 0U))
    {
        return;    
    }

    fun_ctrl->config.cmd_callback(kStatus_SDIOSLV_FuncSendComplete, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                  kSDIOSLV_CmdPortNum0, port_ctrl->buffer, fun_ctrl->config.cmd_user_data);

    port_ctrl->buffer   = NULL;
    port_ctrl->occupied = 0;

    /* If any pending cmdrsp or event in q, send one of them here */
    if ((send_buffer = (sdu_buffer_t *)LIST_GetHead(&ctrl_sdu.cmd_q[SDU_PORT_FOR_READ])) != NULL)
    {
        status = SDU_SendCmdNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
        if (status != kStatus_Success)
        {
            //return_buf = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.cmd_q[SDU_PORT_FOR_READ]);
            //assert(return_buf == send_buffer);
            //(void)LIST_AddTail(&ctrl_sdu.cmd_free_buffer[SDU_PORT_FOR_READ], &return_buf->link);
            sdu_e("%s: cmd SendCmdNonBlocking fail 0x%x!\r\n", __FUNCTION__, status);
        }
    }
    else if ((send_buffer = (sdu_buffer_t *)LIST_GetHead(&ctrl_sdu.event_q)) != NULL)
    {
        status = SDU_SendCmdNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
        if (status != kStatus_Success)
        {
            //return_buf = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.event_q);
            //assert(return_buf == send_buffer);
            //(void)LIST_AddTail(&ctrl_sdu.event_free_buffer, &return_buf->link);
            sdu_e("%s: event SendCmdNonBlocking fail 0x%x!\r\n", __FUNCTION__, status);
        }
    }
	else
	{
        ;
	}
}

/*!
 * @brief SDU process interrupt status 'SDIO_CCR_CIC_CmdDnLdOvr'.
 *
 * @param fun_ctrl Spcified which function to be processed.
 * @retval None.
 */
static inline void SDU_ProcessCmdDnLdOvr(sdioslv_fun_ctrl_t *fun_ctrl)
{
    sdioslv_port_ctrl_t *port_ctrl;

    port_ctrl = &fun_ctrl->cmd_port[SDU_PORT_FOR_WRITE];

    if ((port_ctrl->valid == 0U) || (port_ctrl->occupied == 0U))
    {
    	return;
    }
       
    fun_ctrl->config.cmd_callback(kStatus_SDIOSLV_FuncReadComplete, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                  kSDIOSLV_CmdPortNum0, port_ctrl->buffer, fun_ctrl->config.cmd_user_data);

    port_ctrl->buffer   = NULL;
    port_ctrl->occupied = 0;

#if 0
    fun_ctrl->config.cmd_callback(kStatus_SDIOSLV_FuncRequestBuffer, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                  kSDIOSLV_CmdPortNum0, NULL, fun_ctrl->config.cmd_user_data);
#endif
}

/*!
 * @brief SDU process interrupt status 'SDIO_CCR_CIC_UpLdOvr'.
 *
 * @param fun_ctrl Spcified which function to be processed.
 * @retval None.
 */
static inline void SDU_ProcessDataUpLdOvr(sdioslv_fun_ctrl_t *fun_ctrl)
{
    sdioslv_port_ctrl_t *port_ctrl;
    sdioslv_sdu_regmap_t *sdu_fsr;
    uint32_t rd_bit_map;
    uint32_t i = 0;
    sdu_buffer_t *send_buffer = NULL;
    status_t status = kStatus_Success;

    sdu_fsr    = fun_ctrl->regmap;
    rd_bit_map = sdu_fsr->RdBitMap;

    for (i = 0; i < fun_ctrl->config.used_port_num; i++)
    {
        if ((rd_bit_map & ((uint32_t)(1U << i))) == 0U)
        {
            port_ctrl = &fun_ctrl->data_port[SDU_PORT_FOR_READ][i];
            if ((port_ctrl->valid == 0U) || (port_ctrl->occupied == 0U))
            {
            	continue;
            }

            fun_ctrl->config.data_callback(kStatus_SDIOSLV_FuncSendComplete, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                          (sdioslv_port_t)i, port_ctrl->buffer, fun_ctrl->config.cmd_user_data);

            port_ctrl->buffer   = NULL;
            port_ctrl->occupied = 0;
        }
    }

#if 0
    SDU_AdjustAvailDataPort(fun_ctrl);
#endif

    if ((send_buffer = (sdu_buffer_t *)LIST_GetHead(&ctrl_sdu.data_q[SDU_PORT_FOR_READ])) != NULL)
    {
        status = SDU_SendDataNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
        if (status != kStatus_Success)
        {
            sdu_e("%s: SDU_SendDataNonBlocking fail 0x%x!send_buffer %p [%p %u]\r\n", __FUNCTION__,
                status, send_buffer, send_buffer->buffer.data_addr, send_buffer->buffer.data_len);
        }
    }

}

/*!
 * @brief SDU process interrupt status 'SDIO_CCR_CIC_DnLdOvr'.
 *
 * @param fun_ctrl Spcified which function to be processed.
 * @retval None.
 */
static inline void SDU_ProcessDataDnLdOvr(sdioslv_fun_ctrl_t *fun_ctrl)
{
    sdioslv_port_ctrl_t *port_ctrl;
    sdioslv_sdu_regmap_t *sdu_fsr;
    uint32_t wr_bit_map;
    uint32_t i;

    sdu_fsr    = fun_ctrl->regmap;
    wr_bit_map = sdu_fsr->WrBitMap;

    for (i = 0; i < (uint32_t)fun_ctrl->config.used_port_num; i++)
    {
        if ((wr_bit_map & (uint32_t)(1U << i)) == (uint32_t)0U)
        {
            port_ctrl = &fun_ctrl->data_port[SDU_PORT_FOR_WRITE][i];
            if ((port_ctrl->valid == 0U) || (port_ctrl->occupied == 0U))
            {
            	continue;
            }

            fun_ctrl->config.data_callback(kStatus_SDIOSLV_FuncReadComplete, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                          (sdioslv_port_t)i, port_ctrl->buffer, fun_ctrl->config.cmd_user_data);

            port_ctrl->buffer   = NULL;
            port_ctrl->occupied = 0;

#if 0
            fun_ctrl->config.data_callback(kStatus_SDIOSLV_FuncRequestBuffer, (sdioslv_func_t)fun_ctrl->config.fun_num,
                                          (sdioslv_port_t)i, NULL, fun_ctrl->config.cmd_user_data);
#endif
        }
    }
}

/*!
 * @brief SDU send command.
 *
 * Call this API after calling the SDU_InitData() and SDU_CreateHandle()
 * to send command to host driver. The callback is always invoked from the
 * interrupt context.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @param buffer Buffer used to exchange command to SDIO host driver.
 * @retval #kStatus_Success command is ready to be sent to host driver.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDIOSLV_CmdPending previous command is still under working.
 * @retval #kStatus_Fail Fail to send command.
 */
static status_t SDU_SendCmdNonBlocking(sdioslv_handle_t handle, transfer_buffer_t *buffer)
{
    sdioslv_fun_ctrl_t *fun_ctrl;
    sdioslv_port_ctrl_t *port_ctrl;

    OSA_SR_ALLOC();

    if ((handle == NULL) || (buffer == NULL))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    OSA_ENTER_CRITICAL();
    fun_ctrl  = (sdioslv_fun_ctrl_t *)handle;
    port_ctrl = &fun_ctrl->cmd_port[SDU_PORT_FOR_READ];

    if (port_ctrl->valid == 0U)
    {
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_Fail;
    }

    if (port_ctrl->occupied != 0U )
    {
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_SDIOSLV_CmdPending;
    }

    port_ctrl->buffer          = buffer;
    port_ctrl->occupied        = 1;
    if (SDIOSLV_SendCmdNonBlocking(fun_ctrl->regmap, buffer->data_addr, buffer->data_len) != kStatus_Success)
    {
        port_ctrl->buffer		   = NULL;
        port_ctrl->occupied 	   = 0;
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_InvalidArgument;
    }

    OSA_EXIT_CRITICAL();
    return (status_t)kStatus_Success;
}

/*!
 * @brief SDU provide command buffer.
 *
 * Call this API after receiving #kStatus_SDIOSLV_FuncRequestBuffer from command
 * callback function to provide receive command buffer to SDU driver.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @param buffer Buffer used to refill receive command buffer.
 * @retval #kStatus_Success buffer refill sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
static status_t SDU_RefillCmdBuffer(sdu_ctrl_t *ctrl)
{
    sdioslv_fun_ctrl_t *fun_ctrl = NULL;
    sdioslv_port_ctrl_t *port_ctrl = NULL;
    sdu_buffer_t *sdu_node_buf = NULL;
    OSA_SR_ALLOC();

    if ((ctrl == NULL) || (ctrl->handle == NULL))
    {
        return (status_t)kStatus_InvalidArgument;
    }
	
    sdu_node_buf = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->cmd_free_buffer[SDU_PORT_FOR_WRITE]);
    if (sdu_node_buf == NULL)
    {
        sdu_e("%s: No cmd free buffer for cmd_buf!\r\n", __FUNCTION__);
        return (status_t)kStatus_NoData;
    }
    sdu_node_buf->buffer.data_len  = 0;
    sdu_node_buf->buffer.user_data = (uint32_t)sdu_node_buf;

    OSA_ENTER_CRITICAL();
    fun_ctrl  = (sdioslv_fun_ctrl_t *)(ctrl->handle);
    port_ctrl = &fun_ctrl->cmd_port[SDU_PORT_FOR_WRITE];

    if (port_ctrl->valid == 0U)
    {
        goto refill_cmd_err;
    }

    if (port_ctrl->occupied != 0U)
    {
        goto refill_cmd_err;
    }
	
    port_ctrl->buffer           = &(sdu_node_buf->buffer);
    port_ctrl->occupied         = 1;
    if (SDIOSLV_RefillCmdBuffer(fun_ctrl->regmap, port_ctrl->buffer->data_addr) != kStatus_Success)
    {
        sdu_e("%s: SDIOSLV_RefillCmdBuffer fail!\r\n", __FUNCTION__);
        port_ctrl->buffer		   = NULL;
        port_ctrl->occupied 	   = 0;
        goto refill_cmd_err;
    }

    OSA_EXIT_CRITICAL();
    return (status_t)kStatus_Success;

refill_cmd_err:
    OSA_EXIT_CRITICAL();
    (void)LIST_AddTail(&ctrl->cmd_free_buffer[SDU_PORT_FOR_WRITE], &sdu_node_buf->link);
    return (status_t)kStatus_Fail;
}

/*!
 * @brief SDU send data transfer.
 *
 * Call this API after calling the SDU_InitData() and SDU_CreateHandle()
 * to send data to host driver. The callback is always invoked from the
 * interrupt context.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @param buffer Buffer used to exchange to data SDIO host driver.
 * @retval #kStatus_Success buffer is added to data slot with problem.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDIOSLV_SendFull all data slots are occupied, application
 * should check and wait until data slot is available.
 * @retval #kStatus_Fail Fail to send data.
 */
static status_t SDU_SendDataNonBlocking(sdioslv_handle_t handle, transfer_buffer_t *buffer)
{
    sdioslv_fun_ctrl_t *fun_ctrl;
    sdioslv_port_ctrl_t *port_ctrl;
    uint8_t tx_port;
    OSA_SR_ALLOC();

    if ((handle == NULL) || (buffer == NULL))
    {
        return (status_t)kStatus_InvalidArgument;
    }
	
    OSA_ENTER_CRITICAL();
    fun_ctrl = (sdioslv_fun_ctrl_t *)handle;
    tx_port  = fun_ctrl->curr_data_tx_port;
    if (tx_port >= fun_ctrl->config.used_port_num)
    {
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_SDIOSLV_SendFull;
    }
    port_ctrl = &fun_ctrl->data_port[SDU_PORT_FOR_READ][tx_port];

    port_ctrl->buffer        = buffer;
    port_ctrl->occupied      = 1;
    if (SDIOSLV_SendDataNonBlocking(fun_ctrl->regmap, (sdioslv_port_t)tx_port, buffer->data_addr, buffer->data_len) != kStatus_Success)
    {
        port_ctrl->buffer		   = NULL;
        port_ctrl->occupied 	   = 0;
        OSA_EXIT_CRITICAL();
        return (status_t)kStatus_InvalidArgument;
    }

    OSA_EXIT_CRITICAL();
#if 0
    SDU_AdjustAvailDataPort(fun_ctrl);
#endif
    return (status_t)kStatus_Success;
}

/*!
 * @brief SDU provide receive data buffer.
 *
 * Call this API after receiving #kStatus_SDIOSLV_FuncRequestBuffer from data
 * callback function to provide receive data buffer to SDU driver.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @param buffer Buffer used to refill receive data slots.
 * @param which slot should be refilled (got from kStatus_SDIOSLV_FuncRequestBuffer).
 * @retval #kStatus_Success refill buffer sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
static status_t SDU_RefillDataBuffer(sdu_ctrl_t *ctrl, sdioslv_port_t port)
{
    sdioslv_fun_ctrl_t *fun_ctrl = NULL;
    sdioslv_port_ctrl_t *port_ctrl = NULL;
    sdu_buffer_t *data_buf = NULL;
    OSA_SR_ALLOC();

    if ((ctrl == NULL) || (ctrl->handle == NULL))
    {
        return (status_t)kStatus_InvalidArgument;
    }
	
    if ((uint32_t)port >= SDU_MAX_PORT_NUM)
    {
        return (status_t)kStatus_InvalidArgument;
    }
	
    data_buf = (sdu_buffer_t *)LIST_RemoveHead(&ctrl->data_free_buffer);
    if (data_buf == NULL)
    {
        sdu_e("%s: No free buffer for data_buf!\r\n", __FUNCTION__);
        return (status_t)kStatus_NoData;
    }
	
    data_buf->buffer.data_len  = 0;
    data_buf->buffer.user_data = (uint32_t)data_buf;

    OSA_ENTER_CRITICAL();
    fun_ctrl  = (sdioslv_fun_ctrl_t *)(ctrl->handle);
    port_ctrl = &fun_ctrl->data_port[SDU_PORT_FOR_WRITE][port];

    if (port_ctrl->valid == 0U)
    {
        goto refill_data_err;
    }
	
    if (port_ctrl->occupied != 0U)
    {
        goto refill_data_err;
    }
	
    port_ctrl->buffer        = &(data_buf->buffer);
    port_ctrl->occupied      = 1;
    if (SDIOSLV_RefillDataBuffer(fun_ctrl->regmap, port, port_ctrl->buffer->data_addr) != kStatus_Success)
    {
        sdu_e("%s: SDIOSLV_RefillDataBuffer on port %x fail!\r\n", __FUNCTION__, port);
        port_ctrl->buffer		   = NULL;
        port_ctrl->occupied 	   = 0;
        goto refill_data_err;
    }

    OSA_EXIT_CRITICAL();
    return (status_t)kStatus_Success;

refill_data_err:
    OSA_EXIT_CRITICAL();
    (void)LIST_AddTail(&ctrl->data_free_buffer, &data_buf->link);
    return (status_t)kStatus_Fail;
}

/*!
 * @brief SDU provide all free ports receive data buffer.
 *
 * @param ctrl Pointer to sdu_ctrl_t .
 * @retval #kStatus_Success refill buffer sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
static status_t SDU_RefillFreePortsDataBuffer(sdu_ctrl_t *ctrl)
{
    sdioslv_fun_ctrl_t *fun_ctrl = NULL;
    sdioslv_sdu_regmap_t *sdu_fsr = NULL;
    uint32_t wr_bit_map = 0;
    uint32_t i = 0;
    OSA_SR_ALLOC();

    if (ctrl_sdu.sdu_state != SDU_INITIALIZED)
    {
        sdu_e("%s: return for sdu_state %d!\r\n", __FUNCTION__, ctrl_sdu.sdu_state);
        return (status_t)kStatus_Fail;
    }

    OSA_ENTER_CRITICAL();
    fun_ctrl = (sdioslv_fun_ctrl_t *)(ctrl_sdu.handle);
    sdu_fsr    = fun_ctrl->regmap;
    wr_bit_map = sdu_fsr->WrBitMap;
    for (i = 0; i < (uint32_t)fun_ctrl->config.used_port_num; i++)
    {
        if ((wr_bit_map & (uint32_t)(1U << i)) == (uint32_t)0U)
        {
            (void)SDU_RefillDataBuffer(&ctrl_sdu, (sdioslv_port_t)i);
        }
    }

    OSA_EXIT_CRITICAL();
    return (status_t)kStatus_Success;
}

static status_t SDU_RecvCmdProcess(void)
{
    sdu_buffer_t *cmd_rcv = NULL;
    sdio_header_t *sdio_hdr = NULL;
    status_t ret = kStatus_Fail;

    cmd_rcv = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.cmd_q[SDU_PORT_FOR_WRITE]);
    if (cmd_rcv == NULL)
    {
        sdu_e("%s: NO buffer on cmd_rcv list!\r\n", __FUNCTION__);
        return ret;
    }

    sdio_hdr = (sdio_header_t *)(cmd_rcv->buffer.data_addr);
    if ((sdio_hdr->len <= sizeof(sdio_header_t)) || (sdio_hdr->len > SDU_CMD_BUFFER_SIZE)
        || (sdio_hdr->type != SDU_TYPE_CMD))
    {
        sdu_e("%s: bad sdio_hdr: len=0x%x type=0x%x!\r\n", __FUNCTION__, sdio_hdr->len, sdio_hdr->type);
        ctrl_sdu.stat.err_tx_cmd_sdio_hdr++;
    }
    else
    {
        sdu_d("%s: SDIO hdr: len=%d type=%d!\r\n", __FUNCTION__, sdio_hdr->len, sdio_hdr->type);
        if (ctrl_sdu.sdu_cb_fn[SDU_TYPE_FOR_WRITE_CMD] != NULL)
        {
            //memcpy(data_addr, cmd_rcv->buffer.data_addr + sizeof(sdio_header_t), MIN(sdio_hdr->len, data_size));
            ctrl_sdu.sdu_cb_fn[SDU_TYPE_FOR_WRITE_CMD](cmd_rcv->buffer.data_addr + sizeof(sdio_header_t), sdio_hdr->len - sizeof(sdio_header_t) - CRC_LEN);
            ret = kStatus_Success;
        }
        if (kStatus_Success == ret)
        {
            ctrl_sdu.stat.succ_tx_cmd++;
        }
        else
        {
            ctrl_sdu.stat.err_tx_cmd_call_cb++;
        }
    }
    (void)LIST_AddTail(&ctrl_sdu.cmd_free_buffer[SDU_PORT_FOR_WRITE], &cmd_rcv->link);
    (void)SDU_RefillCmdBuffer(&ctrl_sdu);

    return ret;
}

status_t SDU_RecvCmd(void)
{
    osa_event_flags_t ev = 0;
    osa_status_t status = KOSA_StatusSuccess;
    status_t ret = kStatus_Fail;

    while(true)
    {
        status = OSA_EventWait((osa_event_handle_t)(ctrl_sdu.event), SDU_CMD_RECEIVED, 0U, osaWaitForever_c, &ev);

        if (KOSA_StatusSuccess == status)
        {
            if ((ev & SDU_CMD_RECEIVED) != 0U)
   			{
   	            ret = SDU_RecvCmdProcess();

   	            if (kStatus_Success == ret)
   	            {
   	                return ret;
   	            }
   	        }
   	        else
   	        {
   	            sdu_e("%s: wrong ev 0x%x!\r\n", __FUNCTION__, ev);
   	        }
   	    }
   	    else
   	    {
   	        sdu_e("%s: OSA_EventWait fail status=0x%x!\r\n", __FUNCTION__, status);
   	    }
   	}
}

static status_t SDU_RecvDataProcess(void)
{
    sdu_buffer_t *data_rcv = NULL;
    sdio_header_t *sdio_hdr = NULL;
    status_t ret = kStatus_Fail;

    data_rcv = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.data_q[SDU_PORT_FOR_WRITE]);
    if (data_rcv == NULL)
    {
        sdu_e("%s: NO buffer on data_rcv list!\r\n", __FUNCTION__);
        return ret;
    }

    sdio_hdr = (sdio_header_t *)(data_rcv->buffer.data_addr);
    if ((sdio_hdr->len <= sizeof(sdio_header_t)) || (sdio_hdr->len > SDU_DATA_BUFFER_SIZE)
        || (sdio_hdr->type != SDU_TYPE_DATA))
    {
        sdu_e("%s: bad sdio_hdr: len=0x%x type=0x%x!\r\n", __FUNCTION__, sdio_hdr->len, sdio_hdr->type);
        ctrl_sdu.stat.err_tx_data_sdio_hdr++;
    }
    else
    {
        sdu_d("%s: SDIO hdr: len=%d type=%d!\r\n", __FUNCTION__, sdio_hdr->len, sdio_hdr->type);
        if (ctrl_sdu.sdu_cb_fn[SDU_TYPE_FOR_WRITE_DATA] != NULL)
        {
            //memcpy(data_addr, data_rcv->buffer.data_addr + sizeof(sdio_header_t), MIN(sdio_hdr->len, data_size));
            ctrl_sdu.sdu_cb_fn[SDU_TYPE_FOR_WRITE_DATA](data_rcv->buffer.data_addr + sizeof(sdio_header_t), sdio_hdr->len - sizeof(sdio_header_t) - CRC_LEN);
            ret = kStatus_Success;
        }
    }
    (void)LIST_AddTail(&ctrl_sdu.data_free_buffer, &data_rcv->link);
    //SDU_RefillDataBuffer(&ctrl_sdu);
    (void)SDU_RefillFreePortsDataBuffer(&ctrl_sdu);

    return ret;
}

status_t SDU_RecvData(void)
{
    osa_event_flags_t ev = 0;
    osa_status_t status = KOSA_StatusSuccess;
    status_t ret = kStatus_Fail;
    uint32_t succ_count = 0;

	while(true)
	{
	    status = OSA_EventWait((osa_event_handle_t)(ctrl_sdu.event), SDU_DATA_RECEIVED, 0U, osaWaitForever_c, &ev);

	    if (KOSA_StatusSuccess == status)
	    {
	        if ((ev & SDU_DATA_RECEIVED) != 0U)
	        {
	            while (LIST_GetHead(&ctrl_sdu.data_q[SDU_PORT_FOR_WRITE]) != NULL)
	            {
	                ret = SDU_RecvDataProcess();
	                if (kStatus_Success == ret)
	                {
	                    succ_count++;
	                    ctrl_sdu.stat.succ_tx_data++;
	                }
	                else
	                {
	                    ctrl_sdu.stat.err_tx_data_call_cb++;
	                }
	            }
				
	            if (succ_count != 0U)
	            {
	                return ret;
	            }
	        }
	        else
	        {
	            sdu_e("%s: wrong ev 0x%x!\r\n", __FUNCTION__, ev);
	        }
	    }
	    else
	    {
	        sdu_e("%s: OSA_EventWait fail status=0x%x!\r\n", __FUNCTION__, status);
	    }
	}

}

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
status_t SDU_Send(sdu_for_read_type_t type, uint8_t *data_addr, uint16_t data_len)
{
    sdu_buffer_t *send_buffer = NULL;
    status_t status = kStatus_Fail;
    sdio_header_t *sdio_hdr = NULL;

    if ((data_addr == NULL) || (data_len == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    if (type >= SDU_TYPE_FOR_READ_MAX)
    {
        return (status_t)kStatus_InvalidArgument;
    }

    if (SDU_IsLinkUp() != true)
    {
        return (status_t)kStatus_Fail;
    }
	
    switch (type)
    {
        case SDU_TYPE_FOR_READ_CMD:
            send_buffer = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.cmd_free_buffer[SDU_PORT_FOR_READ]);
            break;
        case SDU_TYPE_FOR_READ_EVENT:
            send_buffer = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.event_free_buffer);
            break;
        case SDU_TYPE_FOR_READ_DATA:
            send_buffer = (sdu_buffer_t *)LIST_RemoveHead(&ctrl_sdu.data_free_buffer);
            break;
        default:
            sdu_e("%s: Unknown type %d.\n\r", __func__, type);
            break;
    }

    if (send_buffer == NULL)
    {
        if (type == SDU_TYPE_FOR_READ_DATA)
        {
            ctrl_sdu.stat.drop_tx_data++;
        }
        else
        {
            ctrl_sdu.stat.drop_tx_cmd++;
        }
		
        sdu_d("%s: NO free_buffer for type %d!\r\n", __FUNCTION__, type);
        return (status_t)kStatus_NoData;
    }

    if (data_len + sizeof(sdio_header_t) > send_buffer->buffer.data_size)
    {
        sdu_e("%s: data_len(%u) + sdiohdr(%lu) > buffersize(%u)!\r\n", __FUNCTION__,
            data_len, sizeof(sdio_header_t), send_buffer->buffer.data_size);
        return (status_t)kStatus_InvalidArgument;
    }

    sdio_hdr = (sdio_header_t *)(send_buffer->buffer.data_addr);
    switch (type)
    {
        case SDU_TYPE_FOR_READ_CMD:
            sdio_hdr->type = SDU_TYPE_CMD;
            break;
        case SDU_TYPE_FOR_READ_EVENT:
            sdio_hdr->type = SDU_TYPE_EVENT;
            break;
        case SDU_TYPE_FOR_READ_DATA:
            sdio_hdr->type = SDU_TYPE_DATA;
            break;
        default:
            sdu_e("%s: Unknown type %d.\n\r", __func__, type);
            break;
    }
    sdio_hdr->len = (uint16_t)MIN(data_len + sizeof(sdio_header_t), send_buffer->buffer.data_size);

    sdu_d("%s: buffer.data_size=%u data_len=%u sdio_hdr->len=%u\r\n", __FUNCTION__,
        send_buffer->buffer.data_size, data_len, sdio_hdr->len);
    (void)memcpy(send_buffer->buffer.data_addr + sizeof(sdio_header_t), data_addr, sdio_hdr->len - sizeof(sdio_header_t));
    send_buffer->buffer.data_len = sdio_hdr->len;
    send_buffer->buffer.user_data = (uint32_t)send_buffer;

    switch (type)
    {
        case SDU_TYPE_FOR_READ_CMD:
            (void)LIST_AddTail(&ctrl_sdu.cmd_q[SDU_PORT_FOR_READ], &send_buffer->link);
            status = SDU_SendCmdNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
            if ((status == (status_t)kStatus_Success) || (status == (status_t)kStatus_SDIOSLV_CmdPending))
            {
                sdu_d("%s: %d SendCmdNonBlocking ok 0x%x!\r\n", __FUNCTION__, type, status);
            }
            else
            {
                sdu_e("%s: %d SendCmdNonBlocking fail 0x%x!\r\n", __FUNCTION__, type, status);
                (void)LIST_RemoveElement(&send_buffer->link);
                (void)LIST_AddTail(&ctrl_sdu.cmd_free_buffer[SDU_PORT_FOR_READ], &send_buffer->link);
                return (status_t)kStatus_Fail;
            }
            break;
        case SDU_TYPE_FOR_READ_EVENT:
            (void)LIST_AddTail(&ctrl_sdu.event_q, &send_buffer->link);
            status = SDU_SendCmdNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
            if ((status == (status_t)kStatus_Success) || (status == (status_t)kStatus_SDIOSLV_CmdPending))
            {
                sdu_d("%s: %d SendCmdNonBlocking ok 0x%x!\r\n", __FUNCTION__, type, status);
            }
            else
            {
                sdu_e("%s: %d SendCmdNonBlocking fail 0x%x!\r\n", __FUNCTION__, type, status);
                (void)LIST_RemoveElement(&send_buffer->link);
                (void)LIST_AddTail(&ctrl_sdu.event_free_buffer, &send_buffer->link);
                return (status_t)kStatus_Fail;
            }
            break;
        case SDU_TYPE_FOR_READ_DATA:
            (void)LIST_AddTail(&ctrl_sdu.data_q[SDU_PORT_FOR_READ], &send_buffer->link);
            status = SDU_SendDataNonBlocking(ctrl_sdu.handle, &send_buffer->buffer);
            if ((status == (status_t)kStatus_Success) || (status == (status_t)kStatus_SDIOSLV_SendFull))
            {
                sdu_d("%s: SendDataNonBlocking ok 0x%x!\r\n", __FUNCTION__, status);
            }
            else
            {
                sdu_e("%s: SendDataNonBlocking fail 0x%x!\r\n", __FUNCTION__, status);
                (void)LIST_RemoveElement(&send_buffer->link);
                (void)LIST_AddTail(&ctrl_sdu.data_free_buffer, &send_buffer->link);
                return (status_t)kStatus_Fail;
            }
            break;
        default:
            sdu_e("%s: Unknown type %d.\n\r", __func__, type);
            break;
    }

    return (status_t)kStatus_Success;
}


/*!
 * @brief SDU interrupt service routine.
 *
 * @param void None.
 */
static uint32_t g_SDU_IRQHandler_cnt = 0;

static void SDU_SLV_IRQHandler(void)
{
    sdioslv_fun_ctrl_t *fun_ctrl;
    sdioslv_sdu_regmap_t *sdu_fsr;
    uint32_t int_status;
    uint8_t i, crc_err;

    g_SDU_IRQHandler_cnt++;

    for (i = 0; i < sdu_ctrl.used_fun_num; i++)
    {
        fun_ctrl = sdu_ctrl.func_ctrl[i];
        if ((fun_ctrl->initialized != 0U) && (fun_ctrl->enable != 0U))
        {
            sdu_fsr    = fun_ctrl->regmap;
            int_status = sdu_fsr->CardIntStatus;
            crc_err    = sdu_fsr->HostTransferStatus;

            if ((int_status & (uint32_t)SDIO_CCR_CIC_CmdUpLdOvr) != 0U)
            {
                SDU_ProcessCmdUpLdOvr(fun_ctrl);
                sdu_fsr->CardIntStatus &= ~((uint32_t)SDIO_CCR_CIC_CmdUpLdOvr);
            }

            if (((int_status & (uint32_t)SDIO_CCR_CIC_CmdDnLdOvr) != 0U) && ((crc_err & (uint32_t)SDIO_CCR_HOST_DnLdCRC_err) == 0U))
            {
                SDU_ProcessCmdDnLdOvr(fun_ctrl);
                sdu_fsr->CardIntStatus &= ~((uint32_t)SDIO_CCR_CIC_CmdDnLdOvr);
            }

            if ((int_status & (uint32_t)SDIO_CCR_CIC_UpLdOvr) != 0U)
            {
                SDU_ProcessDataUpLdOvr(fun_ctrl);
                sdu_fsr->CardIntStatus &= ~((uint32_t)SDIO_CCR_CIC_UpLdOvr);
            }

            if (((int_status & (uint32_t)SDIO_CCR_CIC_DnLdOvr) != 0U) && ((crc_err & (uint32_t)SDIO_CCR_HOST_DnLdCRC_err) == 0U))
            {
                SDU_ProcessDataDnLdOvr(fun_ctrl);
                sdu_fsr->CardIntStatus &= ~((uint32_t)SDIO_CCR_CIC_DnLdOvr);
            }

            if ((int_status & ((uint32_t)SDIO_CCR_CIC_PwrUp)) != 0U)
            {
                sdu_fsr->CardIntStatus &= ~((uint32_t)SDIO_CCR_CIC_PwrUp);
            }
        }
    }
}

void SDU_DriverIRQHandler(void)
{
    SDU_SLV_IRQHandler();
}

static void SDU_GetDefaultCISTable(const uint32_t SDU_BASE)
{
    //uint32_t vid = ROM_SDIO_VID; // 0x1;
    uint32_t pid;
    uint32_t i;
    uint32_t curr_offset;
    uint32_t cis_addr;

    char *vers[4] = {"NXP\000Wireless Device ID: XX\000\000\377", "NXP WiFi Device\000\000\377",
                           "NXP Bluetooth Device\000\000\377", "NXP 802.15.4 Device\000\000\377"};

    curr_offset = SDU_BASE + SD_CIS_DATA0_FN0;

    for (i = 0; i < 4U; i++)
    {
        (void)memset((uint8_t *)curr_offset, 0, 0x80);
        REG8(curr_offset + 0U) = 0xffU;
        curr_offset += 0x80U;
    }

    // FN0
    cis_addr = SDU_BASE + SD_CIS_DATA0_FN0;
    pid      = ROM_SDIO_PID0; // 0; // FIXME g_SDIO_pid[0];
    emitvers(&cis_addr, (uint8_t *)vers[0], 1);
    emitvidpid(&cis_addr, ROM_SDIO_VID, pid);
    emitfuncid(&cis_addr);
    emitfunce(&cis_addr);
    emit1(&cis_addr, 0xff);
    emit1(&cis_addr, 0x00);

    // FN1
    cis_addr = SDU_BASE + SD_CIS_DATA0_FN1;
    pid      = ROM_SDIO_PID1; // 0;  // FIXME g_SDIO_pid[1];
    emitvers(&cis_addr, (uint8_t *)vers[1], 0);
    emitvidpid(&cis_addr, ROM_SDIO_VID, pid);
    emitfuncid(&cis_addr);
    emitfunce_extended(&cis_addr, 1);
    emit1(&cis_addr, 0xff);
    emit1(&cis_addr, 0x00);
}

static void SDU_GetDefaultConfig(sdio_slave_config_t *config)
{
    assert(NULL != config);

    config->cpu_num            = SDU_INT_CPU_NUM;
    config->cis_table_callback = SDU_GetDefaultCISTable;
    config->cmd_tx_format      = 2;
    config->cmd_rd_format      = 1;
    config->data_tx_format     = 2;
    config->data_rd_format     = 1;
}

static status_t SDU_SDIOSLVInit(void)
{
    sdio_slave_config_t config;
    status_t rc;

    SDIOSLV_Init0();

    SDU_GetDefaultConfig(&config);
    rc = SDIOSLV_Init1(SDU_FN_CARD, &config);
    if (rc != kStatus_Success)
    {
        sdu_e("%s: SDIOSLV_Init1 fail: %d\r\n", __FUNCTION__, rc);
        return rc;
    }

    return rc;
}

static status_t SDU_SetFwReady(void)
{
    status_t ret = kStatus_Fail;

    ret = SDIOSLV_WriteScratchRegister(kSDIOSLV_FunctionNum1,
        kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset0, 0xdc);
    if (ret != kStatus_Success) {
        sdu_e("%s: SDIOSLV_WriteScratchRegister Group%u Offset%u fail: %d\r\n",
            __FUNCTION__, kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset0, ret);
        goto done;
    }

    ret = SDIOSLV_WriteScratchRegister(kSDIOSLV_FunctionNum1,
        kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset1, 0xfe);
    if (ret != kStatus_Success) {
        sdu_e("%s: SDIOSLV_WriteScratchRegister Group%u Offset%u fail: %d\r\n",
            __FUNCTION__, kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset1, ret);
        goto done;
    }

done:
    return ret;
}

static status_t SDU_ClrFwReady(void)
{
    status_t ret = kStatus_Fail;

    ret = SDIOSLV_WriteScratchRegister(kSDIOSLV_FunctionNum1,
        kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset0, 0x00);
    if (ret != kStatus_Success) {
        sdu_e("%s: SDIOSLV_WriteScratchRegister Group%u Offset%u fail: %d\r\n",
            __FUNCTION__, kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset0, ret);
        goto done;
    }

    ret = SDIOSLV_WriteScratchRegister(kSDIOSLV_FunctionNum1,
        kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset1, 0x00);
    if (ret != kStatus_Success) {
        sdu_e("%s: SDIOSLV_WriteScratchRegister Group%u Offset%u fail: %d\r\n",
            __FUNCTION__, kSDIOSLV_ScratchGroup2, kSDIOSLV_ScratchOffset1, ret);
        goto done;
    }

done:
    return ret;
}

status_t SDU_Init(void)
{
    status_t rc = kStatus_Success;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    sdu_d("Enter %s: sdu_state=%d.\r\n", __FUNCTION__, ctrl_sdu.sdu_state);

    if (ctrl_sdu.sdu_state != SDU_UNINITIALIZED)
    {
        sdu_e("%s: ctrl_sdu.sdu_state=0x%x\r\n", __FUNCTION__, ctrl_sdu.sdu_state);
        goto done;
    }
    ctrl_sdu.sdu_state = SDU_INITIALIZING;

    sdu_d("SDIOSLV Init.\r\n");
    rc = SDU_SDIOSLVInit();
    if (kStatus_Success != rc)
    {
        sdu_e("%s: SDU_SDIOSLVInit fail: 0x%x\r\n", __FUNCTION__, rc);
        goto done;
    }

    sdu_d("SDU Inner Init.\r\n");
    rc = SDU_InnerInit();
    if (kStatus_Success != rc)
    {
        sdu_e("%s: SDU_InnerInit fail: 0x%x\r\n", __FUNCTION__, rc);
        goto done;
    }

    sdu_d("Create Data Recv Task.\r\n");
    if (KOSA_StatusSuccess != OSA_TaskCreate((osa_task_handle_t)ctrl_sdu.recvTaskId, OSA_TASK(SDU_RecvTask), &ctrl_sdu))
    {
        sdu_e("Can't create SDU data recv task.\r\n");
        rc = kStatus_Fail;
        goto done;
    }

    sdu_d("Create SDU event.\r\n");
    if (KOSA_StatusSuccess != OSA_EventCreate((osa_event_handle_t)ctrl_sdu.event, 1U))
    {
        sdu_e("Can't create SDU event.\r\n");
        (void)OSA_TaskDestroy((osa_task_handle_t)ctrl_sdu.recvTaskId);
        rc = kStatus_Fail;
        goto done;
    }

    os_ClearPendingISR(SDU_IRQn);
    /* Interrupt must be maskable by FreeRTOS critical section */
    NVIC_SetPriority(SDU_IRQn, 2);
    (void)os_InterruptMaskSet(SDU_IRQn);

    rc = SDU_SetFwReady();
    if (kStatus_Success != rc)
    {
        sdu_e("%s: SDU_SetFwReady fail: 0x%x\r\n", __FUNCTION__, rc);
        goto done;
    }

    ctrl_sdu.sdu_state = SDU_INITIALIZED;

#ifdef CONFIG_SDIO_TEST_LOOPBACK
    (void)SDU_InstallCallback(SDU_TYPE_FOR_WRITE_CMD, SDU_LoopbackRecvCmdHandler);
    (void)SDU_InstallCallback(SDU_TYPE_FOR_WRITE_DATA, SDU_LoopbackRecvDataHandler);
#endif

done:
    if (kStatus_Success != rc)
    {
        SDU_InnerDeinit();
    }

    sdu_d("Leave %s: sdu_state=%d rc=0x%x.\r\n", __FUNCTION__, ctrl_sdu.sdu_state, rc);
    OSA_EXIT_CRITICAL();
    return rc;
}

void SDU_Deinit(void)
{
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();

    sdu_d("Enter %s: sdu_state=%d.\r\n", __FUNCTION__, ctrl_sdu.sdu_state);
    if (ctrl_sdu.sdu_state == SDU_UNINITIALIZED)
    {
        sdu_e("%s: ctrl_sdu.sdu_state=0x%x\r\n", __FUNCTION__, ctrl_sdu.sdu_state);
        goto done;
    }

    (void)SDU_ClrFwReady();

    (void)OSA_TaskDestroy((osa_task_handle_t)ctrl_sdu.recvTaskId);
    (void)OSA_EventDestroy((osa_event_handle_t)ctrl_sdu.event);

    SDU_InnerDeinit();

done:
    sdu_d("Leave %s: sdu_state=%d.\r\n", __FUNCTION__, ctrl_sdu.sdu_state);
    OSA_EXIT_CRITICAL();
}

status_t SDU_InstallCallback(sdu_for_write_type_t type, sdu_callback_t callback)
{
    assert(SDU_TYPE_FOR_WRITE_MAX > type);

    ctrl_sdu.sdu_cb_fn[type] = callback;

    return (status_t)kStatus_Success;
}

