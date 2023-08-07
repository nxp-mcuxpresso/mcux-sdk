/*
 * Copyright 2020, 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_component_i3c_adapter.h"
#include "fsl_i3c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I3C_TIME_OUT_INDEX 100000000U

/* I3C master adapter internal resource*/
typedef struct _i3c_master_adapter_private
{
    uint8_t devCount;
    i3c_ccc_dev_t *devList;
} i3c_master_adapter_private_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t I3C_MasterAdapterInit(i3c_device_t *master);
static status_t I3C_MasterAdapterProcessDAA(i3c_device_t *master);
static status_t I3C_MasterAdapterTransmitCCC(i3c_device_t *master, i3c_ccc_cmd_t *cmd);
static status_t I3C_MasterAdapterDoI3CTransfer(i3c_device_t *device, i3c_bus_transfer_t *xfer);
static status_t I3C_MasterAdapterDoI2CTransfer(i2c_device_t *device, i3c_bus_transfer_t *xfer);
static void I3C_SlaveAdapterRequestMastership(i3c_device_t *dev);
static void I3C_SlaveAdapterRequestHotJoin(i3c_device_t *dev);
static status_t I3C_SlaveAdapterInit(i3c_device_t *dev);
static status_t I3C_MasterAdapterHandOffMasterShip(i3c_device_t *master, uint8_t slaveAddr);
static void I3C_MasterAdapterTakeOverMasterShip(i3c_device_t *master);
static void I3C_SlaveAdapterRequestIBI(i3c_device_t *dev, void *data, size_t dataSize);
static void I3C_MasterAdapterRegisterIBI(i3c_device_t *master, uint8_t ibiAddress);
static void i3c_master_ibi_callback(I3C_Type *base,
                                    i3c_master_handle_t *handle,
                                    i3c_ibi_type_t ibiType,
                                    i3c_ibi_state_t ibiState);
static void i3c_master_callback(I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData);
static void i3c_slave2master_callback(I3C_Type *base, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile bool g_masterCompletionFlag = false;
static volatile bool g_ibiWonFlag           = false;
static volatile status_t g_completionStatus = kStatus_Success;
static volatile bool g_transferPolling      = false;

const i3c_device_hw_ops_t master_ops = {.Init              = I3C_MasterAdapterInit,
                                        .Deinit            = NULL,
                                        .ProceedDAA        = I3C_MasterAdapterProcessDAA,
                                        .CheckSupportCCC   = NULL,
                                        .TransmitCCC       = I3C_MasterAdapterTransmitCCC,
                                        .DoI3CTransfer     = I3C_MasterAdapterDoI3CTransfer,
                                        .DoI2CTransfer     = I3C_MasterAdapterDoI2CTransfer,
                                        .HotJoin           = I3C_SlaveAdapterRequestHotJoin,
                                        .RequestMastership = I3C_SlaveAdapterRequestMastership,
                                        .RegisterIBI       = I3C_MasterAdapterRegisterIBI,
                                        .RequestIBI        = I3C_SlaveAdapterRequestIBI};

const i3c_device_hw_ops_t slave_ops                        = {.Init              = I3C_SlaveAdapterInit,
                                       .Deinit            = NULL,
                                       .ProceedDAA        = NULL,
                                       .CheckSupportCCC   = NULL,
                                       .TransmitCCC       = NULL,
                                       .DoI3CTransfer     = NULL,
                                       .DoI2CTransfer     = NULL,
                                       .RegisterIBI       = NULL,
                                       .HotJoin           = I3C_SlaveAdapterRequestHotJoin,
                                       .RequestMastership = I3C_SlaveAdapterRequestMastership,
                                       .RequestIBI        = I3C_SlaveAdapterRequestIBI};
static const i3c_master_transfer_callback_t masterCallback = {.slave2Master     = i3c_slave2master_callback,
                                                              .ibiCallback      = i3c_master_ibi_callback,
                                                              .transferComplete = i3c_master_callback};

/*******************************************************************************
 * Code
 ******************************************************************************/
#define I3C_SLAVELIST_MAX_LEN    50U
#define I3C_MASTER_IBI_BUFF_SIZE 50U

static void i3c_secondarymaster_callback(I3C_Type *base, i3c_slave_transfer_t *xfer, void *userData)
{
    i3c_device_t *dev                           = (i3c_device_t *)userData;
    i3c_device_control_info_t *devControlInfo   = dev->devControlInfo;
    i3c_master_adapter_private_t *masterPrivate = (i3c_master_adapter_private_t *)devControlInfo->privateData;
    switch ((uint32_t)xfer->event)
    {
        case (uint32_t)kI3C_SlaveReceivedCCCEvent:
            if (0UL != (base->SDATACTRL & I3C_SDATACTRL_RXCOUNT_MASK))
            {
                uint8_t cmdID = (uint8_t)(base->SRDATAB & I3C_SRDATAB_DATA0_MASK);
                /* DEFSLVLIST command */
                if (cmdID == 0x08U)
                {
                    xfer->rxData     = (uint8_t *)masterPrivate->devList;
                    xfer->rxDataSize = I3C_SLAVELIST_MAX_LEN;
                }
            }
            break;

        case (uint32_t)kI3C_SlaveCompletionEvent:
            if (xfer->rxData != NULL)
            {
                uint8_t *pDevList       = (uint8_t *)masterPrivate->devList;
                masterPrivate->devCount = pDevList[0];
                masterPrivate->devList  = (i3c_ccc_dev_t *)(void *)&pDevList[1];
            }
            break;

        case (uint32_t)kI3C_SlaveTransmitEvent:
        case (uint32_t)kI3C_SlaveReceiveEvent:
        case (uint32_t)kI3C_SlaveRequestSentEvent:
            break;

        default:
            assert(false);
            break;
    }
}

static void i3c_master_ibi_callback(I3C_Type *base,
                                    i3c_master_handle_t *handle,
                                    i3c_ibi_type_t ibiType,
                                    i3c_ibi_state_t ibiState)
{
    g_transferPolling    = true;
    i3c_device_t *master = (i3c_device_t *)handle->userData;
    switch (ibiType)
    {
        case kI3C_IbiNormal:
            if (ibiState == kI3C_IbiDataBuffNeed)
            {
                handle->ibiBuff = malloc(I3C_MASTER_IBI_BUFF_SIZE);
            }
            else
            {
                /* Handle ibi data*/
                void *ibiData = malloc(handle->ibiPayloadSize);
                (void)memcpy(ibiData, (void *)handle->ibiBuff, handle->ibiPayloadSize);
                (void)I3C_BusMasterHandleIBI(master, handle->ibiAddress, ibiData, handle->ibiPayloadSize);
                free(ibiData);
            }
            break;

        case kI3C_IbiMasterRequest:
            if (ibiState == kI3C_IbiAckNackPending)
            {
                I3C_MasterEmitIBIResponse(base, kI3C_IbiRespAck);
            }
            else
            {
                (void)I3C_MasterAdapterHandOffMasterShip(master, handle->ibiAddress);
            }
            break;

        case kI3C_IbiHotJoin:
            (void)I3C_BusMasterDoDAA(master);
            break;

        default:
            assert(false);
            break;
    }
    g_transferPolling = false;
}

static void i3c_slave2master_callback(I3C_Type *base, void *userData)
{
    i3c_device_t *master = (i3c_device_t *)userData;
    I3C_MasterAdapterTakeOverMasterShip(master);
}

static void i3c_master_callback(I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_masterCompletionFlag = true;
    }

    if (status == kStatus_I3C_IBIWon)
    {
        g_ibiWonFlag = true;
    }

    g_completionStatus = status;
}

static status_t I3C_MasterAdapterInit(i3c_device_t *master)
{
    assert(master != NULL);
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_bus_t *bus                                = master->bus;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;

    I3C_Type *base                       = masterResource->base;
    i3c_master_transfer_mode_t transMode = masterResource->transMode;
    i3c_master_adapter_private_t *masterPrivate;

    i3c_config_t masterConfig;
    I3C_GetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz.i2cBaud          = bus->i2cBaudRate;
    masterConfig.baudRate_Hz.i3cPushPullBaud  = bus->i3cPushPullBaudRate;
    masterConfig.baudRate_Hz.i3cOpenDrainBaud = bus->i3cOpenDrainBaudRate;
    masterConfig.enableOpenDrainStop          = false;
    masterConfig.masterDynamicAddress         = master->info.dynamicAddr;
    masterConfig.maxWriteLength               = master->info.maxWriteLength;
    masterConfig.maxReadLength                = master->info.maxReadLength;
    masterConfig.staticAddr                   = master->info.staticAddr;
    masterConfig.vendorID                     = master->info.vendorID;
    masterConfig.partNumber                   = master->info.partNumber;
    masterConfig.dcr                          = master->info.dcr;
    masterConfig.bcr                          = master->info.bcr;
    masterConfig.hdrMode                      = master->info.hdrMode;

    masterPrivate                  = malloc(sizeof(i3c_master_adapter_private_t));
    masterControlInfo->privateData = masterPrivate;

    /* Master is capable of working as master but work as slave for now */
    if (masterControlInfo->isSecondary)
    {
        masterConfig.enableMaster = kI3C_MasterCapable;
        masterConfig.enableSlave  = true;
        masterPrivate->devList    = malloc(I3C_SLAVELIST_MAX_LEN);
        masterPrivate->devCount   = 0U;
        (void)memset((void *)masterPrivate->devList, 0, I3C_SLAVELIST_MAX_LEN);
    }
    else
    {
        masterConfig.enableMaster = kI3C_MasterOn;
        masterConfig.enableSlave  = false;
    }

    I3C_Init(base, &masterConfig, masterResource->clockInHz);

    if (transMode == kI3C_MasterTransferInterruptMode)
    {
        i3c_master_handle_t *g_i3c_m_handle = malloc(sizeof(i3c_master_handle_t));
        I3C_MasterTransferCreateHandle(base, g_i3c_m_handle, &masterCallback, master);
    }

    status_t result = kStatus_Success;

    if (masterControlInfo->isSecondary)
    {
        /* Create slave handle. */
        i3c_slave_handle_t *g_i3c_s_handle = malloc(sizeof(*g_i3c_s_handle));
        I3C_SlaveTransferCreateHandle(base, g_i3c_s_handle, i3c_secondarymaster_callback, master);

        /* Start slave non-blocking transfer. */
        result =
            I3C_SlaveTransferNonBlocking(base, g_i3c_s_handle,
                                         ((uint32_t)kI3C_SlaveCompletionEvent | (uint32_t)kI3C_SlaveReceivedCCCEvent |
                                          (uint32_t)kI3C_SlaveRequestSentEvent));
        I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
    }
    return result;
}

static status_t I3C_MasterAdapterProcessDAA(i3c_device_t *master)
{
    assert(master != NULL);
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    status_t result                               = kStatus_Success;
    uint32_t status;
    uint32_t errStatus;
    size_t rxCount;
    uint8_t rxBuffer[8] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    uint8_t rxSize      = 0;
    i3c_bus_t *i3cBus   = master->bus;

    /* Return an error if the bus is already in use not by us. */
    result = I3C_CheckForBusyBus(base);
    if (kStatus_Success != result)
    {
        return result;
    }

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kI3C_MasterAllErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterClearFlags);

    /* Disable I3C IRQ sources while we configure stuff. */
    uint32_t enabledInts = I3C_MasterGetEnabledInterrupts(base);
    I3C_MasterDisableInterrupts(base, enabledInts);

    /* Emit process DAA */
    I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);

    do
    {
        do
        {
            status = I3C_MasterGetStatusFlags(base);
            I3C_MasterGetFifoCounts(base, &rxCount, NULL);

            /* Check for error flags. */
            errStatus = I3C_MasterGetErrorStatusFlags(base);
            result    = I3C_MasterCheckAndClearError(base, errStatus);
            if (kStatus_Success != result)
            {
                return result;
            }

            if ((0UL != (status & (uint32_t)kI3C_MasterRxReadyFlag)) && (rxCount != 0U))
            {
                rxBuffer[rxSize++] = (uint8_t)(base->MRDATAB & I3C_MRDATAB_VALUE_MASK);
            }
        } while ((status & (uint32_t)kI3C_MasterControlDoneFlag) != (uint32_t)kI3C_MasterControlDoneFlag);

        I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterControlDoneFlag);

        if ((I3C_MasterGetState(base) == kI3C_MasterStateDaa) &&
            (0UL != (I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterBetweenFlag)))
        {
            rxSize = 0;

            uint8_t validAddr = I3C_BusGetValidAddrSlot(i3cBus, 0x0);
            if (validAddr < I3C_BUS_MAX_ADDR)
            {
                i3c_device_t *newI3CDev = malloc(sizeof(i3c_device_t));
                (void)memset(newI3CDev, 0, sizeof(i3c_device_t));

                newI3CDev->info.dynamicAddr = validAddr;
                newI3CDev->info.vendorID    = (((uint16_t)rxBuffer[0] << 8U | (uint16_t)rxBuffer[1]) & 0xFFFEU) >> 1U;
                newI3CDev->info.partNumber  = ((uint32_t)rxBuffer[2] << 24U | (uint32_t)rxBuffer[3] << 16U |
                                              (uint32_t)rxBuffer[4] << 8U | (uint32_t)rxBuffer[5]);
                newI3CDev->info.bcr         = rxBuffer[6];
                newI3CDev->info.dcr         = rxBuffer[7];
                base->MWDATAB               = validAddr;

                I3C_BusAddI3CDev(i3cBus, newI3CDev);
                /* Emit process DAA again. */
                I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);
            }
            else
            {
                return kStatus_I3CBus_AddrSlotInvalid;
            }
        }
    } while ((status & (uint32_t)kI3C_MasterCompleteFlag) != (uint32_t)kI3C_MasterCompleteFlag);

    I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterCompleteFlag);

    /* Enable I3C IRQ sources while we configure stuff. */
    I3C_MasterEnableInterrupts(base, enabledInts);

    return kStatus_Success;
}

static status_t I3CMasterAdapterTransfer(I3C_Type *base,
                                         i3c_master_transfer_t *xfer,
                                         i3c_master_transfer_mode_t transMode)
{
    g_ibiWonFlag           = false;
    g_masterCompletionFlag = false;
    uint32_t timeout       = 0U;
    status_t result        = kStatus_Success;
    g_completionStatus     = kStatus_Success;

    /*TODO: wait for module idle */
    if (g_transferPolling == true)
    {
        result = I3C_MasterTransferBlocking(base, xfer);
    }
    else
    {
        void *handle = s_i3cMasterHandle[I3C_GetInstance(base)];

        if (transMode == kI3C_MasterTransferInterruptMode)
        {
            result = I3C_MasterTransferNonBlocking(base, handle, xfer);
            if (kStatus_Success != result)
            {
                return result;
            }

            /* Wait for transfer completed. */
            while (!g_masterCompletionFlag)
            {
                timeout++;
                __NOP();
                if (g_ibiWonFlag)
                {
                    break;
                }
                else if ((g_completionStatus != kStatus_Success) || (timeout > I3C_TIME_OUT_INDEX))
                {
                    break;
                }
                else
                {
                    /* Add this to fix MISRA C2012 rule15.7 issue: Empty else without comment. */
                }
            }

            result = g_completionStatus;
        }

        if (timeout == I3C_TIME_OUT_INDEX)
        {
            result = kStatus_I3CBus_MasterTransTimeout;
        }
    }

    return result;
}
static status_t I3C_MasterAdapterTransmitCCC(i3c_device_t *master, i3c_ccc_cmd_t *cmd)
{
    assert(master != NULL);
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    i3c_master_transfer_mode_t transMode          = masterResource->transMode;
    status_t result                               = kStatus_Success;

    i3c_master_transfer_t xfer;
    (void)memset(&xfer, 0, sizeof(xfer));

    if (cmd->destAddr == I3C_BUS_BROADCAST_ADDR)
    {
        xfer.slaveAddress   = I3C_BUS_BROADCAST_ADDR;
        xfer.subaddress     = cmd->cmdId;
        xfer.subaddressSize = 1U;
        xfer.data           = cmd->data;
        xfer.dataSize       = cmd->dataSize;
        xfer.direction      = cmd->isRead ? kI3C_Read : kI3C_Write;
        xfer.busType        = kI3C_TypeI3CSdr;
        xfer.flags          = (uint32_t)kI3C_TransferDefaultFlag;
        result              = I3CMasterAdapterTransfer(base, &xfer, transMode);
        if (result != kStatus_Success)
        {
            return result;
        }
    }
    else
    {
        xfer.slaveAddress = I3C_BUS_BROADCAST_ADDR;
        xfer.data         = &cmd->cmdId;
        xfer.dataSize     = 1U;
        xfer.direction    = kI3C_Write;
        xfer.busType      = kI3C_TypeI3CSdr;
        xfer.flags        = (uint32_t)kI3C_TransferNoStopFlag;
        result            = I3CMasterAdapterTransfer(base, &xfer, transMode);
        if (result != kStatus_Success)
        {
            return result;
        }

        xfer.slaveAddress = cmd->destAddr;
        xfer.data         = cmd->data;
        xfer.dataSize     = cmd->dataSize;
        xfer.direction    = cmd->isRead ? kI3C_Read : kI3C_Write;
        xfer.busType      = kI3C_TypeI3CSdr;
        xfer.flags        = (uint32_t)kI3C_TransferRepeatedStartFlag;
        result            = I3CMasterAdapterTransfer(base, &xfer, transMode);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    return result;
}

static status_t I3C_MasterAdapterDoI3CTransfer(i3c_device_t *device, i3c_bus_transfer_t *xfer)
{
    assert(device != NULL);
    i3c_bus_t *bus       = device->bus;
    i3c_device_t *master = (i3c_device_t *)bus->currentMaster;
    assert(master != NULL);

    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    i3c_master_transfer_mode_t transMode          = masterResource->transMode;

    i3c_master_transfer_t masterXfer;
    (void)memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = device->info.dynamicAddr;
    masterXfer.subaddress     = xfer->regAddr;
    masterXfer.subaddressSize = xfer->regAddrSize;
    masterXfer.data           = xfer->data;
    masterXfer.dataSize       = xfer->dataSize;
    masterXfer.direction      = xfer->isRead ? kI3C_Read : kI3C_Write;
    masterXfer.busType        = kI3C_TypeI3CSdr;
    masterXfer.flags          = (uint32_t)kI3C_TransferDefaultFlag;

    return I3CMasterAdapterTransfer(base, &masterXfer, transMode);
}

static status_t I3C_MasterAdapterDoI2CTransfer(i2c_device_t *device, i3c_bus_transfer_t *xfer)
{
    assert(device != NULL);
    i3c_bus_t *bus       = device->bus;
    i3c_device_t *master = (i3c_device_t *)bus->currentMaster;
    assert(master != NULL);

    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    i3c_master_transfer_mode_t transMode          = masterResource->transMode;

    i3c_master_transfer_t masterXfer;
    (void)memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = device->staticAddr;
    masterXfer.subaddress     = xfer->regAddr;
    masterXfer.subaddressSize = xfer->regAddrSize;
    masterXfer.data           = xfer->data;
    masterXfer.dataSize       = xfer->dataSize;
    masterXfer.direction      = xfer->isRead ? kI3C_Read : kI3C_Write;
    masterXfer.busType        = kI3C_TypeI2C;
    masterXfer.flags          = (uint32_t)kI3C_TransferDefaultFlag;

    return I3CMasterAdapterTransfer(base, &masterXfer, transMode);
}

static void I3C_MasterAdapterTakeOverMasterShip(i3c_device_t *master)
{
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    i3c_bus_t *i3cBus                             = master->bus;
    i3c_master_adapter_private_t *masterPrivate   = (i3c_master_adapter_private_t *)masterControlInfo->privateData;

    uint8_t devCount       = masterPrivate->devCount;
    i3c_ccc_dev_t *devList = masterPrivate->devList;

    /* Register bus devices detected from SLAVE */
    if ((devCount != 0U) && (devList != NULL))
    {
        for (uint8_t i = 0U; i < devCount; i++)
        {
            i3c_ccc_dev_t *cccDev = &devList[i];
#if defined(I3C_SDYNADDR_DADDR_MASK)
            if (cccDev->dynamicAddr != (base->SDYNADDR & I3C_SDYNADDR_DADDR_MASK))
#else
            if (cccDev->dynamicAddr != (base->SMAPCTRL0 & I3C_SMAPCTRL0_DA_MASK))
#endif
            {
                if (cccDev->dynamicAddr != 0U)
                {
                    i3c_device_t *newI3CDev = malloc(sizeof(i3c_device_t));
                    (void)memset(newI3CDev, 0, sizeof(i3c_device_t));

                    newI3CDev->info.dynamicAddr = cccDev->dynamicAddr >> 1U;
                    newI3CDev->info.bcr         = cccDev->dcr;
                    newI3CDev->info.dcr         = cccDev->dcr;
                    newI3CDev->info.staticAddr  = cccDev->staticAddr >> 1U;

                    I3C_BusAddI3CDev(i3cBus, newI3CDev);
                }
                else
                {
                    i2c_device_t *newI2CDev = malloc(sizeof(i2c_device_t));
                    (void)memset(newI2CDev, 0, sizeof(i2c_device_t));

                    newI2CDev->lvr        = cccDev->lvr;
                    newI2CDev->staticAddr = cccDev->staticAddr >> 1U;

                    I3C_BusAddI2CDev(i3cBus, newI2CDev);
                }
            }
            else
            {
                master->info.dynamicAddr = cccDev->dynamicAddr >> 1U;
            }
        }
    }

    i3cBus->currentMaster          = master;
    masterControlInfo->isSecondary = false;

    /* Clear all flags. */
    I3C_SlaveClearStatusFlags(base, (uint32_t)kI3C_SlaveClearFlags);

    /* Disable I3C slave IRQ resources */
    I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveAllIrqFlags);

    I3C_MasterEnable(base, kI3C_MasterOn);
    I3C_SlaveEnable(base, false);
}

static status_t I3C_MasterAdapterHandOffMasterShip(i3c_device_t *master, uint8_t slaveAddr)
{
    status_t result                               = kStatus_Success;
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;
    i3c_bus_t *bus                                = master->bus;

    /* Disable MR and hotjoin events */
    result =
        I3C_BusMasterDisableEvents(master, I3C_BUS_BROADCAST_ADDR, ((uint8_t)kI3C_EventMR | (uint8_t)kI3C_EventHJ));
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Send device list on bus */
    result = I3C_BusMasterSendSlavesList(master);
    if (result != kStatus_Success)
    {
        return result;
    }

    uint8_t accData;
    i3c_ccc_cmd_t getAccMstCmd = {0};

    getAccMstCmd.isRead   = true;
    getAccMstCmd.cmdId    = I3C_BUS_CCC_GETACCMST;
    getAccMstCmd.destAddr = slaveAddr;
    getAccMstCmd.data     = &accData;
    getAccMstCmd.dataSize = 1;

    result = I3C_MasterAdapterTransmitCCC(master, &getAccMstCmd);

    /* Change current master to secondary master */
    bus->currentMaster             = NULL;
    masterControlInfo->isSecondary = true;

    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterClearFlags);
    I3C_MasterEnable(base, kI3C_MasterCapable);
    I3C_SlaveEnable(base, true);

    /* Create slave handle. */
    i3c_slave_handle_t *g_i3c_s_handle = malloc(sizeof(*g_i3c_s_handle));
    I3C_SlaveTransferCreateHandle(base, g_i3c_s_handle, i3c_secondarymaster_callback, master);

    /* Start slave non-blocking transfer. */
    result = I3C_SlaveTransferNonBlocking(base, g_i3c_s_handle,
                                          ((uint32_t)kI3C_SlaveCompletionEvent | (uint32_t)kI3C_SlaveReceivedCCCEvent));
    I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);

    return result;
}

static void I3C_MasterAdapterRegisterIBI(i3c_device_t *master, uint8_t ibiAddress)
{
    i3c_device_control_info_t *masterControlInfo  = master->devControlInfo;
    i3c_master_adapter_resource_t *masterResource = (i3c_master_adapter_resource_t *)masterControlInfo->resource;
    I3C_Type *base                                = masterResource->base;

    i3c_register_ibi_addr_t ibiRule;
    I3C_MasterGetIBIRules(base, &ibiRule);
    if (ibiRule.ibiHasPayload)
    {
        ibiRule.ibiHasPayload = true;
    }

    for (uint32_t count = 0; count < ARRAY_SIZE(ibiRule.address); count++)
    {
        if (0U == ibiRule.address[count])
        {
            ibiRule.address[count] = ibiAddress;
            break;
        }
    }

    I3C_MasterRegisterIBI(base, &ibiRule);
}

static status_t I3C_SlaveAdapterInit(i3c_device_t *dev)
{
    assert(dev != NULL);

    i3c_device_control_info_t *devControlInfo  = dev->devControlInfo;
    i3c_device_information_t *devInfo          = &dev->info;
    i3c_device_adapter_resource_t *devResource = (i3c_device_adapter_resource_t *)devControlInfo->resource;

    I3C_Type *base = devResource->base;

    i3c_slave_config_t slaveConfig;
    I3C_SlaveGetDefaultConfig(&slaveConfig);
    slaveConfig.staticAddr = devInfo->staticAddr;
    slaveConfig.dcr        = devInfo->dcr;
    slaveConfig.bcr        = devInfo->bcr;
    slaveConfig.partNumber = devInfo->partNumber;
    slaveConfig.vendorID   = devInfo->vendorID;
    slaveConfig.offline    = false;

    I3C_SlaveInit(base, &slaveConfig, devResource->clockInHz);

    /* Create slave handle. */
    i3c_slave_handle_t *g_i3c_s_handle = malloc(sizeof(*g_i3c_s_handle));
    I3C_SlaveTransferCreateHandle(base, g_i3c_s_handle, devResource->callback, dev);

    /* Start slave non-blocking transfer. */
    status_t result = kStatus_Success;
    result          = I3C_SlaveTransferNonBlocking(base, g_i3c_s_handle, (uint32_t)kI3C_SlaveCompletionEvent);

    return result;
}

static void I3C_SlaveAdapterRequestHotJoin(i3c_device_t *dev)
{
    assert(dev != NULL);

    i3c_device_control_info_t *devControlInfo  = dev->devControlInfo;
    i3c_device_adapter_resource_t *devResource = (i3c_device_adapter_resource_t *)devControlInfo->resource;

    I3C_Type *base = devResource->base;

    I3C_SlaveRequestEvent(base, kI3C_SlaveEventHotJoinReq);
}

static void I3C_SlaveAdapterRequestMastership(i3c_device_t *dev)
{
    assert(dev != NULL);

    i3c_device_control_info_t *devControlInfo  = dev->devControlInfo;
    i3c_device_adapter_resource_t *devResource = (i3c_device_adapter_resource_t *)devControlInfo->resource;

    I3C_Type *base = devResource->base;

    I3C_SlaveRequestEvent(base, kI3C_SlaveEventMasterReq);
}

static void I3C_SlaveAdapterRequestIBI(i3c_device_t *dev, void *data, size_t dataSize)
{
    assert(dev != NULL);

    i3c_device_control_info_t *devControlInfo  = dev->devControlInfo;
    i3c_device_adapter_resource_t *devResource = (i3c_device_adapter_resource_t *)devControlInfo->resource;

    I3C_Type *base = devResource->base;

    if (data != NULL)
    {
        I3C_SlaveRequestIBIWithData(base, (uint8_t *)data, dataSize);
    }
    else
    {
        I3C_SlaveRequestEvent(base, kI3C_SlaveEventIBI);
    }
}
