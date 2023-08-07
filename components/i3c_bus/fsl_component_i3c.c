/*
 * Copyright 2020, 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_component_i3c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void I3C_BusSetAddrSlot(i3c_bus_t *bus, uint8_t addr, i3c_addr_slot_status_t status)
{
    uint16_t bitPos = (uint16_t)addr * I3C_BUS_ADDR_SLOTWIDTH;
    uint32_t *slotPtr;

    if (addr > I3C_BUS_MAX_ADDR)
    {
        return;
    }

    slotPtr = &bus->addrSlots[bitPos / I3C_BUS_ADDR_SLOTDEPTH];
    *slotPtr &= ~((uint32_t)I3C_BUS_ADDR_SLOTMASK << (bitPos % I3C_BUS_ADDR_SLOTDEPTH));
    *slotPtr |= (uint32_t)status << (bitPos % I3C_BUS_ADDR_SLOTDEPTH);
}

static void I3C_BusInitAddrSlots(i3c_bus_t *bus)
{
    uint8_t i;

    /* Reserve address 0x0 to 0x7. */
    for (i = 0; i < 8U; i++)
    {
        I3C_BusSetAddrSlot(bus, i, kI3C_Bus_AddrSlot_Reserved);
    }

    /* Reserve the conditional restriction I3C address. */
    I3C_BusSetAddrSlot(bus, 0x78U, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, 0x79U, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, 0x7BU, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, 0x7DU, kI3C_Bus_AddrSlot_Reserved);

    /* All are prohibited since I3C targets will interpret an I3C address header with any of these addresses as a
     * broadcast address with a single-bit error. */
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR1, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR2, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR3, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR4, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR5, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR6, kI3C_Bus_AddrSlot_Reserved);
    I3C_BusSetAddrSlot(bus, I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR7, kI3C_Bus_AddrSlot_Reserved);

    /* Reserve I3C broadcast address. */
    I3C_BusSetAddrSlot(bus, I3C_BUS_BROADCAST_ADDR, kI3C_Bus_AddrSlot_Reserved);
}

static uint8_t I3C_BusGetAddrSlotStatus(i3c_bus_t *bus, uint8_t checkAddr)
{
    uint16_t bitPos    = (uint16_t)checkAddr * 2U;
    uint32_t useStatus = 0;

    if (checkAddr > I3C_BUS_MAX_ADDR)
    {
        return (uint8_t)kI3C_Bus_AddrSlot_Reserved;
    }

    useStatus = bus->addrSlots[bitPos / I3C_BUS_ADDR_SLOTDEPTH];
    useStatus >>= bitPos % I3C_BUS_ADDR_SLOTDEPTH;

    return (uint8_t)(useStatus & (uint8_t)I3C_BUS_ADDR_SLOTMASK);
}

static status_t I3C_CheckBusMasterOps(i3c_device_hw_ops_t *ops)
{
    if ((ops == NULL) || (ops->Init == NULL) || (ops->DoI3CTransfer == NULL) || (ops->DoI2CTransfer == NULL) ||
        (ops->TransmitCCC == NULL) || (ops->ProceedDAA == NULL))
    {
        return kStatus_I3CBus_MasterOpsMissing;
    }

    return kStatus_Success;
}

static status_t I3C_BusMasterGetMaxReadLength(i3c_device_t *master, i3c_device_information_t *info)
{
    i3c_ccc_cmd_t getMRLCmd = {0};
    status_t result         = kStatus_Success;

    getMRLCmd.isRead   = true;
    getMRLCmd.cmdId    = I3C_BUS_CCC_GETMRL;
    getMRLCmd.destAddr = info->dynamicAddr;
    getMRLCmd.data     = malloc(3U);
    getMRLCmd.dataSize = 3U;

    /*
     * When the device does not have IBI payload GETMRL only returns 2
     * bytes of data.
     */
    if ((info->bcr & I3C_BUS_DEV_BCR_IBI_PAYLOAD_MASK) == 0U)
    {
        getMRLCmd.dataSize -= 1U;
    }

    result = I3C_BusMasterSendCCC(master, &getMRLCmd);

    uint8_t *pData = getMRLCmd.data;
    if ((info->bcr & I3C_BUS_DEV_BCR_IBI_PAYLOAD_MASK) != 0U)
    {
        info->maxIBILength = pData[2];
    }

    info->maxReadLength = (uint16_t)pData[0] << 8UL | (uint16_t)pData[1];

    free(getMRLCmd.data);

    return result;
}

static status_t I3C_BusMasterGetMaxWriteLength(i3c_device_t *master, i3c_device_information_t *info)
{
    i3c_ccc_cmd_t getMWLCmd = {0};
    status_t result         = kStatus_Success;

    uint16_t writelen;
    getMWLCmd.isRead   = true;
    getMWLCmd.cmdId    = I3C_BUS_CCC_GETMWL;
    getMWLCmd.destAddr = info->dynamicAddr;
    getMWLCmd.data     = &writelen;
    getMWLCmd.dataSize = 2U;

    result = I3C_BusMasterSendCCC(master, &getMWLCmd);

    info->maxWriteLength = writelen;

    return result;
}

static status_t I3C_BusMasterGetHDRCapability(i3c_device_t *master, i3c_device_information_t *info)
{
    i3c_ccc_cmd_t getHDRCapCmd = {0};
    status_t result            = kStatus_Success;

    uint8_t hdrMode;
    getHDRCapCmd.isRead   = true;
    getHDRCapCmd.cmdId    = I3C_BUS_CCC_GETHDRCAP;
    getHDRCapCmd.destAddr = info->dynamicAddr;
    getHDRCapCmd.data     = &hdrMode;
    getHDRCapCmd.dataSize = 1U;

    result = I3C_BusMasterSendCCC(master, &getHDRCapCmd);

    info->hdrMode = hdrMode;

    return result;
}

static status_t I3C_BusMasterGetPID(i3c_device_t *master, i3c_device_information_t *info)
{
    uint8_t pid[6];
    i3c_ccc_cmd_t getPidCmd = {0};
    status_t result         = kStatus_Success;

    getPidCmd.isRead   = true;
    getPidCmd.cmdId    = I3C_BUS_CCC_GETPID;
    getPidCmd.destAddr = info->dynamicAddr;
    getPidCmd.data     = pid;
    getPidCmd.dataSize = 6U;

    result = I3C_BusMasterSendCCC(master, &getPidCmd);

    info->vendorID   = (((uint16_t)pid[0] << 8U | (uint16_t)pid[1]) & 0xFFFEU) >> 1U;
    info->partNumber = ((uint32_t)pid[2] << 24U | (uint32_t)pid[3] << 16U | (uint32_t)pid[4] << 8U | (uint32_t)pid[5]);

    return result;
}

static status_t I3C_BusMasterGetBCR(i3c_device_t *master, i3c_device_information_t *info)
{
    uint8_t bcr;
    i3c_ccc_cmd_t getBCRCmd = {0};
    status_t result         = kStatus_Success;

    getBCRCmd.isRead   = true;
    getBCRCmd.cmdId    = I3C_BUS_CCC_GETBCR;
    getBCRCmd.destAddr = info->dynamicAddr;
    getBCRCmd.data     = &bcr;
    getBCRCmd.dataSize = 1U;

    result = I3C_BusMasterSendCCC(master, &getBCRCmd);

    info->bcr = bcr;

    return result;
}

static status_t I3C_BusMasterGetDCR(i3c_device_t *master, i3c_device_information_t *info)
{
    uint8_t dcr;
    i3c_ccc_cmd_t getDCRCmd = {0};
    status_t result         = kStatus_Success;

    getDCRCmd.isRead   = true;
    getDCRCmd.cmdId    = I3C_BUS_CCC_GETDCR;
    getDCRCmd.destAddr = info->dynamicAddr;
    getDCRCmd.data     = &dcr;
    getDCRCmd.dataSize = 1U;

    result = I3C_BusMasterSendCCC(master, &getDCRCmd);

    info->dcr = dcr;

    return result;
}

static status_t I3C_BusMasterAssignDevDynamicAddr(i3c_device_t *masterDev)
{
    i3c_bus_t *i3cBus = masterDev->bus;
    status_t result   = kStatus_Success;

    list_handle_t i3cDevList = &(i3cBus->i3cDevList);

    for (list_element_handle_t listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3c_device_t *tmpDev = (i3c_device_t *)(void *)listItem;
        if (tmpDev == masterDev)
        {
            continue;
        }
        else if ((tmpDev->initDynamicAddr != 0U) && (tmpDev->info.staticAddr != 0U) && (tmpDev->info.dynamicAddr == 0U))
        {
            result =
                I3C_BusMasterSetDynamicAddrFromStaticAddr(masterDev, tmpDev->info.staticAddr, tmpDev->initDynamicAddr);

            if (result != kStatus_Success)
            {
                return result;
            }

            tmpDev->info.dynamicAddr = tmpDev->initDynamicAddr;
            I3C_BusSetAddrSlot(i3cBus, tmpDev->info.dynamicAddr, kI3C_Bus_AddrSlot_I3CDev);

            /* Retrieve device information. */
            result = I3C_BusMasterGetDeviceInfo(masterDev, tmpDev->info.dynamicAddr, &tmpDev->info);
            if (result != kStatus_Success)
            {
                return result;
            }
        }
        else
        {
            /*Empty else to eliminate MISRA 15.7*/
        }
    }

    return result;
}

static status_t I3C_BusMasterAddExistingI3CDevs(i3c_device_t *masterDev)
{
    i3c_bus_t *i3cBus = masterDev->bus;
    status_t result   = kStatus_Success;

    list_handle_t i3cDevList = &(i3cBus->i3cDevList);

    for (list_element_handle_t listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3c_device_t *tmpDev = (i3c_device_t *)(void *)listItem;
        if (tmpDev == masterDev)
        {
            continue;
        }
        else if (tmpDev->ibiInfo != NULL)
        {
            result = I3C_BusMasterRegisterDevIBI(masterDev, tmpDev, tmpDev->ibiInfo);
            if (result != kStatus_Success)
            {
                return result;
            }
        }
        else
        {
            /*Fix MISRA violation 15.7*/
        }
    }

    return result;
}

/*!
 * brief Add exist I3C device in bus to the bus device list.
 *
 * This function will simply add the device to the bus device list and set the related address slot.
 *
 * param bus Pointer to bus structure.
 * param dev Pointer to I3C device.
 */
void I3C_BusAddI3CDev(i3c_bus_t *bus, i3c_device_t *dev)
{
    /* Chain device into i3c_device_list */
    list_handle_t i3cDevList = &bus->i3cDevList;
    (void)LIST_AddTail(i3cDevList, &dev->listNode);

    if (dev->info.dynamicAddr != 0U)
    {
        /* Set slot status I3C device */
        I3C_BusSetAddrSlot(bus, dev->info.dynamicAddr, kI3C_Bus_AddrSlot_I3CDev);
    }

    if (dev->info.staticAddr != 0U)
    {
        /* Set slot status I2C device */
        I3C_BusSetAddrSlot(bus, dev->info.staticAddr, kI3C_Bus_AddrSlot_I2CDev);
    }

    dev->bus = bus;
}

/*!
 * brief Add exist I2C device in bus to the bus device list.
 *
 * This function will simply add the device to the bus device list and set the related address slot.
 *
 * param bus Pointer to bus structure.
 * param dev Pointer to I2C device.
 */
void I3C_BusAddI2CDev(i3c_bus_t *bus, i2c_device_t *dev)
{
    /* Chain device into i2c_device_list */
    dev->bus                 = bus;
    list_handle_t i2cDevList = &bus->i2cDevList;
    (void)LIST_AddTail(i2cDevList, &dev->listNode);
    /* Set slot status I2C device */
    I3C_BusSetAddrSlot(bus, dev->staticAddr, kI3C_Bus_AddrSlot_I2CDev);
    dev->bus = bus;
}

/*!
 * brief Get valid address slot in the I3C bus.
 *
 * This function will search for available address lot in the I3C bus address pool, the search starts from
 * the startAddr specified by user input, to end address defined in @ref I3C_BUS_MAX_ADDR. Will return the
 * available address if the related address slot is valid.
 *
 * param bus Pointer to bus structure.
 * param startAddr Start address for address slot searching, end address is defined in @ref I3C_BUS_MAX_ADDR.
 * return Available address in the bus address pool.
 */
uint8_t I3C_BusGetValidAddrSlot(i3c_bus_t *bus, uint8_t startAddr)
{
    uint8_t validAddr = 0xFF;

    for (validAddr = startAddr; validAddr < I3C_BUS_MAX_ADDR; validAddr++)
    {
        if (I3C_BusGetAddrSlotStatus(bus, validAddr) == (uint8_t)kI3C_Bus_AddrSlot_Free)
        {
            return validAddr;
        }
    }

    return validAddr;
}

/*!
 * brief Gets the default configuration structure.
 *
 * This function initializes the bus configuration structure to a default value. The default
 * values are:
 *   busConfig->busMode = kI3C_Bus_PureMode;
 *   busConfig->i2cBaudRate = 400000U;
 *   busConfig->i3cOpenDrainBaudRate = 1500000U;
 *   busConfig->i3cPushPullBaudRate = 4000000U;
 *
 * param config Pointer to a configuration structure.
 */
void I3C_BusGetDefaultBusConfig(i3c_bus_config_t *busConfig)
{
    busConfig->busMode              = kI3C_Bus_PureMode;
    busConfig->i2cBaudRate          = 400000U;
    busConfig->i3cOpenDrainBaudRate = 1500000U;
    busConfig->i3cPushPullBaudRate  = 4000000U;
}

/*!
 * brief Creates I3C bus structure.
 *
 * This function creates the bus structure with input bus configuration. Address pool set up and device
 * list initialize process will be also done in this function call.
 *
 * param bus Pointer to bus structure.
 * param busConfig Pointer to the bus configuration structure.
 */
void I3C_BusCreate(i3c_bus_t *bus, const i3c_bus_config_t *busConfig)
{
    assert(bus != NULL);

    (void)memset(bus, 0, sizeof(*bus));

    LIST_Init(&bus->i2cDevList, 0);
    LIST_Init(&bus->i3cDevList, 0);
    I3C_BusInitAddrSlots(bus);
    bus->busMode              = busConfig->busMode;
    bus->i2cBaudRate          = busConfig->i2cBaudRate;
    bus->i3cOpenDrainBaudRate = busConfig->i3cOpenDrainBaudRate;
    bus->i3cPushPullBaudRate  = busConfig->i3cPushPullBaudRate;
}

/*!
 * brief Create I3C master structure on bus.
 *
 * This function will create I3C master bus structure, initialize the master according to bus characteristics, install
 * device information and device control information.
 *
 * param masterDev Pointer to device structure creating as master.
 * param bus Pointer to bus structure.
 * param devInfo Pointer to device information structure.
 * param masterControlInfo Pointer to master control information structure.
 */
status_t I3C_BusMasterCreate(i3c_device_t *masterDev,
                             i3c_bus_t *bus,
                             i3c_device_information_t *devInfo,
                             i3c_device_control_info_t *masterControlInfo)
{
    status_t result = kStatus_Success;

    (void)memset(masterDev, 0, sizeof(*masterDev));

    masterDev->info = *devInfo;
    result          = I3C_CheckBusMasterOps(masterControlInfo->funcs);

    if (result != kStatus_Success)
    {
        return result;
    }

    masterDev->devControlInfo = masterControlInfo;
    masterDev->bus            = bus;

    /* call master init to initialize master */
    result = masterControlInfo->funcs->Init(masterDev);

    if (result != kStatus_Success)
    {
        return result;
    }

    if (!masterControlInfo->isSecondary)
    {
        bus->currentMaster = masterDev;
        /*Add masterDev to bus i3c device list */
        I3C_BusAddI3CDev(bus, masterDev);

        /* Execute reset DAA CCC command to reset all i3c device dynamic address */
        result = I3C_BusMasterResetDAA(masterDev, I3C_BUS_BROADCAST_ADDR);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Master assign slave with init dynamic address. */
        result = I3C_BusMasterAssignDevDynamicAddr(masterDev);
        if (result != kStatus_Success)
        {
            return result;
        }

        result = I3C_BusMasterAddExistingI3CDevs(masterDev);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable all events before start doing DAA. */
        result = I3C_BusMasterDisableEvents(masterDev, I3C_BUS_BROADCAST_ADDR,
                                            ((uint8_t)kI3C_EventMR | (uint8_t)kI3C_EventHJ | (uint8_t)kI3C_EventIBI));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Start to do DAA */
        result = I3C_BusMasterDoDAA(masterDev);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable all events before start doing DAA. */
        result = I3C_BusMasterEnableEvents(masterDev, I3C_BUS_BROADCAST_ADDR,
                                           ((uint8_t)kI3C_EventMR | (uint8_t)kI3C_EventHJ | (uint8_t)kI3C_EventIBI));
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    return result;
}

/*!
 * brief Bus master transfer CCC frame.
 *
 * Bus master call this function to transfer CCC frame, CCC frame command and data is prepared in @ref i3c_ccc_cmd_t
 * structure.
 *
 * param masterDev Pointer to I3C master device.
 * param command Pointer to ccc frame.
 */
status_t I3C_BusMasterSendCCC(i3c_device_t *masterDev, i3c_ccc_cmd_t *command)
{
    i3c_device_control_info_t *masterControlInfo = masterDev->devControlInfo;

    if (masterDev != masterDev->bus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    if (masterControlInfo->isSecondary)
    {
        return kStatus_I3CBus_Success;
    }

    if (NULL == masterControlInfo->funcs->TransmitCCC)
    {
        return kStatus_I3CBus_MasterOpsUnsupport;
    }

    return masterControlInfo->funcs->TransmitCCC(masterDev, command);
}

/*!
 * brief Bus master reset dynamic assigned address.
 *
 * Bus master call this function to reset dynamic assigned address, the operation could be done to all connected I3C
 * devices by using slave address I3C_BUS_BROADCAST_ADDR or to a specific connected device by using the device's dynamic
 * address.
 *
 * param masterDev Pointer to I3C master device.
 * param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 */
status_t I3C_BusMasterResetDAA(i3c_device_t *masterDev, uint8_t slaveAddr)
{
    i3c_bus_t *i3cBus = masterDev->bus;
    uint8_t addrStat;
    status_t result;

    if (masterDev != masterDev->bus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    addrStat = I3C_BusGetAddrSlotStatus(i3cBus, slaveAddr);
    if ((slaveAddr != I3C_BUS_BROADCAST_ADDR) && (addrStat != (uint8_t)kI3C_Bus_AddrSlot_I3CDev))
    {
        return kStatus_I3CBus_MasterOpsFailure;
    }

    i3c_ccc_cmd_t rstDaaCmd = {0};

    rstDaaCmd.isRead   = false;
    rstDaaCmd.destAddr = slaveAddr;
    rstDaaCmd.cmdId    = I3C_BUS_CCC_RSTDAA((slaveAddr != I3C_BUS_BROADCAST_ADDR));

    result = I3C_BusMasterSendCCC(masterDev, &rstDaaCmd);
    if (result == kStatus_Success)
    {
        if (slaveAddr != I3C_BUS_BROADCAST_ADDR)
        {
            /* Do not free current Controller's dynamic address. */
            if (masterDev->info.dynamicAddr != slaveAddr)
            {
                I3C_BusSetAddrSlot(i3cBus, slaveAddr, kI3C_Bus_AddrSlot_Free);
            }
        }
        else
        {
            for (uint8_t i = 0; i <= I3C_BUS_MAX_ADDR; i++)
            {
                addrStat = I3C_BusGetAddrSlotStatus(i3cBus, i);
                if ((addrStat == (uint8_t)kI3C_Bus_AddrSlot_I3CDev) && (masterDev->info.dynamicAddr != i))
                {
                    I3C_BusSetAddrSlot(i3cBus, i, kI3C_Bus_AddrSlot_Free);
                }
            }
        }
    }

    return result;
}

/*!
 * brief Bus master do dynamic address assignment.
 *
 * Bus master call this function to do dynamic address assignment to the I3C devices connected on bus.
 *
 * param masterDev Pointer to I3C master device.
 */
status_t I3C_BusMasterDoDAA(i3c_device_t *masterDev)
{
    i3c_device_control_info_t *masterControlInfo = masterDev->devControlInfo;
    i3c_bus_t *i3cBus                            = masterDev->bus;
    status_t result                              = kStatus_Success;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    result = masterControlInfo->funcs->ProceedDAA(masterDev);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Send defslvs command on bus if there's secondary master */
    bool isSend              = false;
    list_handle_t i3cDevList = &(i3cBus->i3cDevList);

    for (list_element_handle_t listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3c_device_t *tmpDev = (i3c_device_t *)(void *)listItem;
        if (tmpDev == masterDev)
        {
            continue;
        }
        else if ((tmpDev->info.bcr & I3C_BUS_DEV_BCR_DEV_ROLE_MASK) ==
                 I3C_BUS_DEV_BCR_DEV_ROLE(I3C_BUS_DEV_BCR_DEV_MASTER))
        {
            isSend = true;
            break;
        }
        else
        {
            /*Empty else to eliminate MISRA 15.7*/
        }
    }

    if (isSend)
    {
        result = I3C_BusMasterSendSlavesList(masterDev);
    }

    return result;
}

/*!
 * brief Bus master set device dynamic address from static address.
 *
 * Bus master call this function to execute SETDASA CCC command to set device dynamic address from static address.
 *
 * param masterDev Pointer to I3C master device.
 * param staticAddr Device static address.
 * param initDynamicAddr Device initialized dynamic address.
 */
status_t I3C_BusMasterSetDynamicAddrFromStaticAddr(i3c_device_t *master, uint8_t staticAddr, uint8_t initDynamicAddr)
{
    i3c_ccc_cmd_t setdasaCCC = {0};
    status_t result          = kStatus_Success;
    uint8_t dynamicAddr      = initDynamicAddr << 1;

    setdasaCCC.cmdId    = I3C_BUS_CCC_SETDASA;
    setdasaCCC.destAddr = staticAddr;
    setdasaCCC.data     = &dynamicAddr;
    setdasaCCC.dataSize = 1U;
    setdasaCCC.isRead   = false;

    result = I3C_BusMasterSendCCC(master, &setdasaCCC);

    return result;
}

/*!
 * brief Bus master send slave list on bus.
 *
 * Bus master call this function to send slave list on bus to notify the secondary master.
 *
 * param masterDev Pointer to I3C master device.
 */
status_t I3C_BusMasterSendSlavesList(i3c_device_t *masterDev)
{
    i3c_bus_t *i3cBus = masterDev->bus;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    list_element_handle_t listItem;
    list_handle_t i2cDevList = &(i3cBus->i2cDevList);
    list_handle_t i3cDevList = &(i3cBus->i3cDevList);

    i3c_ccc_cmd_t defSlavesCmd = {0};
    defSlavesCmd.isRead        = false;
    defSlavesCmd.destAddr      = I3C_BUS_BROADCAST_ADDR;
    defSlavesCmd.cmdId         = I3C_BUS_CCC_DEFSLVS;
    uint8_t devCount           = 1;
    status_t result            = kStatus_Success;

    for (listItem = i2cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        devCount++;
    }

    for (listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3c_device_t *i3cDev = (i3c_device_t *)(void *)listItem;
        if (i3cDev == masterDev)
        {
            continue;
        }
        else
        {
            devCount++;
        }
    }

    defSlavesCmd.dataSize = (uint16_t)sizeof(i3c_ccc_dev_t) * (uint16_t)devCount + 1U;
    defSlavesCmd.data     = malloc(defSlavesCmd.dataSize);

    uint8_t *pData = defSlavesCmd.data;

    *pData                    = devCount;
    i3c_ccc_dev_t *masterInfo = (i3c_ccc_dev_t *)(void *)&pData[1];
    masterInfo->bcr           = masterDev->info.bcr;
    masterInfo->dcr           = masterDev->info.dcr;
    masterInfo->dynamicAddr   = masterDev->info.dynamicAddr << 1U;
    masterInfo->staticAddr    = (I3C_BUS_BROADCAST_ADDR << 1U);

    i3c_ccc_dev_t *slaveInfo = (i3c_ccc_dev_t *)((uint32_t)&pData[1] + sizeof(i3c_ccc_dev_t));
    for (listItem = i2cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        slaveInfo->lvr        = ((i2c_device_t *)(void *)listItem)->lvr;
        slaveInfo->staticAddr = (((i2c_device_t *)(void *)listItem)->staticAddr << 1U);
        slaveInfo++;
    }

    for (listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3c_device_t *i3cDev = (i3c_device_t *)(void *)listItem;
        if (i3cDev == masterDev)
        {
            continue;
        }

        slaveInfo->dcr         = i3cDev->info.dcr;
        slaveInfo->dynamicAddr = i3cDev->info.dynamicAddr << 1U;
        slaveInfo->bcr         = i3cDev->info.bcr;
        slaveInfo->staticAddr  = i3cDev->info.staticAddr << 1U;
        slaveInfo++;
    }

    result = I3C_BusMasterSendCCC(masterDev, &defSlavesCmd);

    free(defSlavesCmd.data);

    return result;
}

/*!
 * brief Bus master enable events.
 *
 * Bus master call this function to enable events on bus.
 *
 * param masterDev Pointer to I3C master device.
 * param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 * param busEvents Logic OR or member in @ref _i3c_bus_events.
 */
status_t I3C_BusMasterEnableEvents(i3c_device_t *masterDev, uint8_t slaveAddr, uint8_t busEvents)
{
    i3c_ccc_cmd_t enEventsCmd = {0};
    status_t result           = kStatus_Success;

    enEventsCmd.isRead   = false;
    enEventsCmd.cmdId    = I3C_BUS_CCC_ENEC((slaveAddr != I3C_BUS_BROADCAST_ADDR));
    enEventsCmd.destAddr = slaveAddr;
    enEventsCmd.data     = &busEvents;
    enEventsCmd.dataSize = 1U;

    result = I3C_BusMasterSendCCC(masterDev, &enEventsCmd);

    return result;
}

/*!
 * brief Bus master disable events.
 *
 * Bus master call this function to disable events on bus.
 *
 * param masterDev Pointer to I3C master device.
 * param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 * param busEvents Logic OR or member in @ref _i3c_bus_events.
 */
status_t I3C_BusMasterDisableEvents(i3c_device_t *masterDev, uint8_t slaveAddr, uint8_t busEvents)
{
    i3c_ccc_cmd_t disEventsCmd = {0};
    status_t result            = kStatus_Success;

    disEventsCmd.isRead   = false;
    disEventsCmd.cmdId    = I3C_BUS_CCC_DISEC((slaveAddr != I3C_BUS_BROADCAST_ADDR));
    disEventsCmd.destAddr = slaveAddr;
    disEventsCmd.data     = &busEvents;
    disEventsCmd.dataSize = 1U;

    result = I3C_BusMasterSendCCC(masterDev, &disEventsCmd);

    return result;
}

/*!
 * brief Bus master get device information for a specific I3C device.
 *
 * Bus master call this function to get device information for a specific I3C device.
 *
 * param masterDev Pointer to I3C master device.
 * param slaveAddr Slave address, dynamic assigned address for a device.
 * param devInfo Input pointer to structure i3c_device_information_t to store the read out device information.
 */
status_t I3C_BusMasterGetDeviceInfo(i3c_device_t *masterDev, uint8_t slaveAddr, i3c_device_information_t *devInfo)
{
    status_t result = kStatus_Success;

    devInfo->dynamicAddr = slaveAddr;

    result = I3C_BusMasterGetPID(masterDev, devInfo);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = I3C_BusMasterGetBCR(masterDev, devInfo);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = I3C_BusMasterGetDCR(masterDev, devInfo);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = I3C_BusMasterGetMaxReadLength(masterDev, devInfo);
    if (result != kStatus_Success)
    {
        return result;
    }
    result = I3C_BusMasterGetMaxWriteLength(masterDev, devInfo);
    if (result != kStatus_Success)
    {
        return result;
    }

    if ((devInfo->bcr & I3C_BUS_DEV_BCR_MODE_MASK) != 0U)
    {
        result = I3C_BusMasterGetHDRCapability(masterDev, devInfo);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    return result;
}

status_t I3C_BusMasterRegisterDevIBI(i3c_device_t *masterDev, i3c_device_t *i3cDev, i3c_device_ibi_info_t *devIbiInfo)
{
    i3c_bus_t *i3cBus = masterDev->bus;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    i3c_device_control_info_t *masterControlInfo = masterDev->devControlInfo;
    i3cDev->ibiInfo                              = devIbiInfo;

    if (I3C_BusGetAddrSlotStatus(i3cBus, i3cDev->info.dynamicAddr) == (uint8_t)kI3C_Bus_AddrSlot_I3CDev)
    {
        masterControlInfo->funcs->RegisterIBI(masterDev, i3cDev->info.dynamicAddr);
    }
    else
    {
        return kStatus_I3CBus_InvalidOps;
    }

    return kStatus_Success;
}
/*!
 * brief Bus master handle in-band-interrupt event.
 *
 * Bus master call this function to handle in-band-interrupt event.
 *
 * param masterDev Pointer to I3C master device.
 * param ibiAddress slave address which requests the IBI.
 * param ibiData Pointer to the ibi data buffer.
 * param payloadSize ibi data buffer size.
 */
status_t I3C_BusMasterHandleIBI(i3c_device_t *masterDev, uint8_t ibiAddress, void *ibiData, uint32_t payloadSize)
{
    i3c_bus_t *i3cBus = masterDev->bus;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    list_element_handle_t listItem;
    list_handle_t i3cDevList = &(i3cBus->i3cDevList);
    i3c_device_t *i3cDev     = NULL;

    for (listItem = i3cDevList->head; listItem != NULL; listItem = listItem->next)
    {
        i3cDev = (i3c_device_t *)(void *)listItem;
        if (i3cDev == masterDev)
        {
            continue;
        }

        if (i3cDev->info.dynamicAddr == ibiAddress)
        {
            break;
        }
    }

    if (i3cDev != NULL)
    {
        assert(i3cDev->ibiInfo != NULL);
        assert(i3cDev->ibiInfo->maxPayloadLength >= payloadSize);
        assert(i3cDev->ibiInfo->ibiHandler != NULL);

        i3cDev->ibiInfo->ibiHandler(i3cDev, ibiData, payloadSize);
    }

    return kStatus_Success;
}

/*!
 * brief Bus master do data transfer to I2C device.
 *
 * Bus master call this function to transfer data to connected I2C device.
 *
 * param masterDev Pointer to I3C master device.
 * param i2cDev Pointer to the I2C device master do transfer.
 * param xfer Pointer to bus transfer.
 */
status_t I3C_BusMasterDoTransferToI2CDev(i3c_device_t *masterDev, i2c_device_t *i2cDev, i3c_bus_transfer_t *xfer)
{
    i3c_bus_t *i3cBus = masterDev->bus;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    status_t result                              = kStatus_Success;
    i3c_device_control_info_t *masterControlInfo = masterDev->devControlInfo;

    if (I3C_BusGetAddrSlotStatus(i3cBus, i2cDev->staticAddr) == (uint8_t)kI3C_Bus_AddrSlot_I2CDev)
    {
        result = masterControlInfo->funcs->DoI2CTransfer(i2cDev, xfer);
    }
    else
    {
        result = kStatus_I3CBus_InvalidOps;
    }

    return result;
}

/*!
 * brief Bus master do data transfer to I3C device.
 *
 * Bus master call this function to transfer data to connected I3C device.
 *
 * param masterDev Pointer to I3C master device.
 * param i3cDev Pointer to the I3C device master do transfer.
 * param xfer Pointer to bus transfer.
 */
status_t I3C_BusMasterDoTransferToI3CDev(i3c_device_t *masterDev, i3c_device_t *i3cDev, i3c_bus_transfer_t *xfer)
{
    i3c_bus_t *i3cBus = masterDev->bus;

    if (masterDev != i3cBus->currentMaster)
    {
        return kStatus_I3CBus_NotCurrentMaster;
    }

    status_t result                              = kStatus_Success;
    i3c_device_control_info_t *masterControlInfo = masterDev->devControlInfo;

    if (I3C_BusGetAddrSlotStatus(i3cBus, i3cDev->info.dynamicAddr) == (uint8_t)kI3C_Bus_AddrSlot_I3CDev)
    {
        result = masterControlInfo->funcs->DoI3CTransfer(i3cDev, xfer);
    }
    else
    {
        result = kStatus_I3CBus_InvalidOps;
    }

    return result;
}

/*!
 * brief Create I2C slave structure on bus.
 *
 * This function will create I2C device bus structure, initialize the slave according to bus characteristics, install
 * device information including static address, lvr and device control information.
 *
 * param i2cDev Pointer to device structure creating as I2C device.
 * param bus Pointer to bus structure.
 * param staticAddr Static address of the I2C device
 * param lvr legacy virtual register value of the device.
 * param devControlInfo Pointer to device control information structure.
 */
status_t I3C_BusI2CSlaveCreate(
    i2c_device_t *i2cDev, i3c_bus_t *bus, uint8_t staticAddr, uint8_t lvr, i2c_device_control_info_t *devControlInfo)
{
    (void)memset(i2cDev, 0, sizeof(*i2cDev));

    i2cDev->bus            = bus;
    i2cDev->staticAddr     = staticAddr;
    i2cDev->lvr            = lvr;
    i2cDev->devControlInfo = devControlInfo;

    i3c_device_t *masterDev = NULL;
    status_t result         = kStatus_Success;

    if (bus != NULL)
    {
        masterDev = (i3c_device_t *)bus->currentMaster;
    }

    if (masterDev != NULL)
    {
        /*Add device to bus i2c device list */
        I3C_BusAddI2CDev(bus, i2cDev);
    }

    if ((devControlInfo != NULL) && (devControlInfo->funcs != NULL) && (devControlInfo->funcs->Init != NULL))
    {
        result = devControlInfo->funcs->Init(i2cDev);
    }

    return result;
}

/*!
 * brief Create I3C slave structure on bus.
 *
 * This function will create I3C device bus structure, initialize the slave according to bus characteristics, install
 * device information and device control information.
 *
 * param i3cDev Pointer to device structure creating as I3C device.
 * param bus Pointer to bus structure.
 * param devInfo Pointer to device information structure
 * param devControlInfo Pointer to device control information structure.
 */
status_t I3C_BusI3CSlaveCreate(i3c_device_t *i3cDev,
                               i3c_bus_t *bus,
                               i3c_device_information_t *devInfo,
                               i3c_device_ibi_info_t *ibiInfo,
                               i3c_device_control_info_t *devControlInfo)
{
    (void)memset(i3cDev, 0, sizeof(*i3cDev));

    i3cDev->bus            = bus;
    i3cDev->ibiInfo        = ibiInfo;
    i3cDev->info           = *devInfo;
    i3cDev->devControlInfo = devControlInfo;
    status_t result        = kStatus_Success;

    i3c_device_t *masterDev = NULL;

    if (bus != NULL)
    {
        masterDev = (i3c_device_t *)bus->currentMaster;
    }

    if (masterDev != NULL)
    {
        /*Add device to bus i3c device list */
        I3C_BusAddI3CDev(bus, i3cDev);
    }

    if ((devControlInfo != NULL) && (devControlInfo->funcs != NULL) && (devControlInfo->funcs->Init != NULL))
    {
        result = devControlInfo->funcs->Init(i3cDev);
    }

    return result;
}

/*!
 * brief I3C slave device request Hot Join on bus.
 *
 * param i3cDev Pointer to device structure creating as I3C device.
 */
status_t I3C_BusSlaveRequestHotJoin(i3c_device_t *i3cDev)
{
    status_t result = kStatus_Success;

    if ((i3cDev->devControlInfo != NULL) && (i3cDev->devControlInfo->funcs != NULL) &&
        (i3cDev->devControlInfo->funcs->HotJoin != NULL))
    {
        i3cDev->devControlInfo->funcs->HotJoin(i3cDev);
    }
    else
    {
        result = kStatus_I3CBus_SlaveOpsNotSupported;
    }

    return result;
}

/*!
 * brief I3C slave device request mastership on bus.
 *
 * param i3cDev Pointer to device structure creating as I3C device.
 */
status_t I3C_BusSlaveRequestMasterShip(i3c_device_t *i3cDev)
{
    status_t result = kStatus_Success;

    if ((i3cDev->devControlInfo != NULL) && (i3cDev->devControlInfo->funcs != NULL) &&
        (i3cDev->devControlInfo->funcs->RequestMastership != NULL))
    {
        i3cDev->devControlInfo->funcs->RequestMastership(i3cDev);
    }
    else
    {
        result = kStatus_I3CBus_SlaveOpsNotSupported;
    }

    return result;
}

/*!
 * brief I3C slave request IBI events.
 *
 * param i3cDev Pointer to device structure creating as I3C device.
 * param data Pointer to data buffer to be sent in IBI event.
 * param dataSize data size of IBI data.
 */
status_t I3C_BusSlaveRequestIBI(i3c_device_t *i3cDev, void *data, size_t dataSize)
{
    status_t result = kStatus_Success;

    if ((i3cDev->devControlInfo != NULL) && (i3cDev->devControlInfo->funcs != NULL) &&
        (i3cDev->devControlInfo->funcs->RequestMastership != NULL))
    {
        i3cDev->devControlInfo->funcs->RequestIBI(i3cDev, data, dataSize);
    }
    else
    {
        result = kStatus_I3CBus_SlaveOpsNotSupported;
    }

    return result;
}
