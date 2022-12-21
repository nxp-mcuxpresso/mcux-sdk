/*
 * Copyright 2020, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _I3C_COMPONENT_H_
#define _I3C_COMPONENT_H_

#include "fsl_component_generic_list.h"

/*!
 * @addtogroup I3C_Bus_Component
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name I3C BUS management definitions*/
/*@{*/
#define I3C_BUS_MAX_DEVS                          11U   /*!< Bus maximum device count. */
#define I3C_BUS_HOT_JOIN_ADDR                     0x2U  /*!< Hot join event device address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR1 0x3EU /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR2 0x5EU /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR3 0x6EU /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR4 0x76U /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR5 0x7AU /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR6 0x7CU /*!< Broadcast address single bit error detect address. */
#define I3C_BOARDCAST_SINGLE_BIT_ERR_DETECT_ADDR7 0x7FU /*!< Broadcast address single bit error detect address. */
#define I3C_BUS_BROADCAST_ADDR                    0x7EU /*!< Broad cast address. */
#define I3C_BUS_MAX_ADDR                          0x7FU /*!< Maximum address allowed for address assignment. */
#define I3C_BUS_ADDR_SLOTWIDTH                    2U  /*!< Address slot width used in address management in bus pool. */
#define I3C_BUS_ADDR_SLOTDEPTH                    32U /*!< Address slot depth used in address management in bus pool. */
#define I3C_BUS_ADDR_SLOTMASK                     3U  /*!< Address slot mask used in address management in bus pool. */

/*@}*/

/*! @name I3C BUS CCC (Common Command Codes) definitions*/
/*@{*/
#define I3C_BUS_CCC_DIRECT_PREFIX 0x80U /*!< Prefix used for direct access CCC. */

#define I3C_BUS_CCC(cmdID, isDirect) \
    ((cmdID) | ((isDirect) ? I3C_BUS_CCC_DIRECT_PREFIX : 0U)) /*!< CCC ID calculation. */

/* CCC available for both broadcast and direct access */
#define I3C_BUS_CCC_ENEC(isDirect)      I3C_BUS_CCC(0x0U, isDirect)        /*!< Enable Slave Events Command. */
#define I3C_BUS_CCC_DISEC(isDirect)     I3C_BUS_CCC(0x1U, isDirect)        /*!< Disable Slave Events Command. */
#define I3C_BUS_CCC_ENTAS(as, isDirect) I3C_BUS_CCC(0x2U + (as), isDirect) /*!< Enter Activity State 0–3 Command. */
#define I3C_BUS_CCC_RSTDAA(isDirect)    I3C_BUS_CCC(0x6U, isDirect) /*!< Reset Dynamic Address Assignment Command. */
#define I3C_BUS_CCC_SETMWL(isDirect)    I3C_BUS_CCC(0x9U, isDirect) /*!< Set Max Write Length Command. */
#define I3C_BUS_CCC_SETMRL(isDirect)    I3C_BUS_CCC(0xaU, isDirect) /*!< Set Max Read Length Command. */
#define I3C_BUS_CCC_SETXTIME(isDirect)  (isDirect) ? 0x98U : 0x28U  /*!< Set Exchange Timing Information Command. */
#define I3C_BUS_CCC_VENDOR_EXT(cmdID, isDirect) \
    ((cmdID) + ((isDirect) ? 0xe0U : 0x61U)) /*!< Vendor Extension Command. */

/* CCC available only for broadcast access */
#define I3C_BUS_CCC_ENTDAA    0x7U        /*!< Enter Dynamic Address Assignment Command. */
#define I3C_BUS_CCC_DEFSLVS   0x8U        /*!< Send Define List of Slaves Command. */
#define I3C_BUS_CCC_ENTTM     0xbU        /*!< Enter Test Mode Command. */
#define I3C_BUS_CCC_ENTHDR(x) 0x20U + (x) /*!< Enter HDR Command. */

/* CCC available only for direct access */
#define I3C_BUS_CCC_SETDASA   0x87U /*!< Set Dynamic Address from Static Address Command. */
#define I3C_BUS_CCC_SETNEWDA  0x88U /*!< Set New Dynamic Address Command. */
#define I3C_BUS_CCC_GETMWL    0x8bU /*!< Get Max Write Length Command. */
#define I3C_BUS_CCC_GETMRL    0x8cU /*!< Get Max Read Length Command. */
#define I3C_BUS_CCC_GETPID    0x8dU /*!< Get Provisional ID Command. */
#define I3C_BUS_CCC_GETBCR    0x8eU /*!< Get BCR Command. */
#define I3C_BUS_CCC_GETDCR    0x8fU /*!< Get DCR Command. */
#define I3C_BUS_CCC_GETSTATUS 0x90U /*!< Get Device Status Command. */
#define I3C_BUS_CCC_GETACCMST 0x91U /*!< Get Accept Mastership Command. */
#define I3C_BUS_CCC_SETBRGTGT 0x93U /*!< Set Bridge Targets Command. */
#define I3C_BUS_CCC_GETMXDS   0x94U /*!< Get Max Data Speed Command. */
#define I3C_BUS_CCC_GETHDRCAP 0x95U /*!< Get HDR Capability Command. */
#define I3C_BUS_CCC_GETXTIME  0x99U /*!< Get Exchange Timing Support Command. */

/*@}*/

/*! @name I3C device BCR register bit masks*/
/*@{*/

/* @brief I3C device bus characteristics */
#define I3C_BUS_DEV_BCR_DEV_MASTER     0x01U
#define I3C_BUS_DEV_BCR_DEV_ROLE_SHIFT 6U
#define I3C_BUS_DEV_BCR_DEV_ROLE_MASK  0xC0U
#define I3C_BUS_DEV_BCR_DEV_ROLE(x)    (((x) << I3C_BUS_DEV_BCR_DEV_ROLE_SHIFT) & I3C_BUS_DEV_BCR_DEV_ROLE_MASK)

#define I3C_BUS_DEV_BCR_MODE_SHIFT 5U
#define I3C_BUS_DEV_BCR_MODE_MASK  0x20U
#define I3C_BUS_DEV_BCR_MODE(x)    (((x) << I3C_BUS_DEV_BCR_MODE_SHIFT) & I3C_BUS_DEV_BCR_MODE_MASK)

#define I3C_BUS_DEV_BCR_IBI_PAYLOAD_SHIFT 2U
#define I3C_BUS_DEV_BCR_IBI_PAYLOAD_MASK  0x04U
#define I3C_BUS_DEV_BCR_IBI_PAYLOAD(x)    (((x) << I3C_BUS_DEV_BCR_IBI_PAYLOAD_SHIFT) & I3C_BUS_DEV_BCR_IBI_PAYLOAD_MASK)

#define I3C_BUS_DEV_BCR_IBI_REQUEST_SHIFT 1U
#define I3C_BUS_DEV_BCR_IBI_REQUEST_MASK  0x02U
#define I3C_BUS_DEV_BCR_IBI_REQUEST(x)    (((x) << I3C_BUS_DEV_BCR_IBI_REQUEST_SHIFT) & I3C_BUS_DEV_BCR_IBI_REQUEST_MASK)

#define I3C_BUS_DEV_BCR_SPEED_LIMIT_SHIFT 0U
#define I3C_BUS_DEV_BCR_SPEED_LIMIT_MASK  0x01U
#define I3C_BUS_DEV_BCR_SPEED_LIMIT(x)    (((x) << I3C_BUS_DEV_BCR_SPEED_LIMIT_SHIFT) & I3C_BUS_DEV_BCR_SPEED_LIMIT_MASK)

/*@}*/

/*! @brief I3C Bus status. */
enum
{
    kStatus_I3CBus_Success         = kStatus_Success,                      /*!< I3C Bus operation succeed*/
    kStatus_I3CBus_AddrSlotInvalid = MAKE_STATUS(kStatusGroup_I3CBUS, 0U), /*!< I3C Bus address slot invalid */
    kStatus_I3CBus_MasterOpsUnsupport =
        MAKE_STATUS(kStatusGroup_I3CBUS, 1U), /*!< I3C Bus master operation unsupported */
    kStatus_I3CBus_NotCurrentMaster = MAKE_STATUS(
        kStatusGroup_I3CBUS, 2U), /*!< The Bus operation should be made on master but current device is not master */
    kStatus_I3CBus_MasterOpsFailure   = MAKE_STATUS(kStatusGroup_I3CBUS, 3U), /*!< Bus operation failure */
    kStatus_I3CBus_InvalidOps         = MAKE_STATUS(kStatusGroup_I3CBUS, 4U), /*!< Master transfer timeout on bus */
    kStatus_I3CBus_MasterTransTimeout = MAKE_STATUS(kStatusGroup_I3CBUS, 5U), /*!< Master transfer timeout on bus */
    kStatus_I3CBus_SlaveOpsNotSupported =
        MAKE_STATUS(kStatusGroup_I3CBUS, 6U), /*!< I3C Bus slave operation unsupported */
    kStatus_I3CBus_MasterOpsMissing =
        MAKE_STATUS(kStatusGroup_I3CBUS, 7U), /*!< I3C Bus master mandatory operation missing */
};

/*! @brief I3C bus events. */
enum _i3c_bus_events
{
    kI3C_EventIBI = 1U, /*!< I3C Bus event IBI */
    kI3C_EventMR  = 2U, /*!< I3C Bus event Mastership Request */
    kI3C_EventHJ  = 8U, /*!< I3C Bus event Hot Join */
};

/*! @brief I3C device information. */
typedef struct _i3c_device_information
{
    uint8_t dynamicAddr;     /*!< Device dynamic address. */
    uint8_t staticAddr;      /*!< Static address. */
    uint8_t dcr;             /*!< Device characteristics register information. */
    uint8_t bcr;             /*!< Bus characteristics register information. */
    uint16_t vendorID;       /*!< Device vendor ID(manufacture ID). */
    uint32_t partNumber;     /*!< Device part number info */
    uint16_t maxReadLength;  /*!< Maximum read length. */
    uint16_t maxWriteLength; /*!< Maximum write length. */
    uint8_t maxIBILength;    /*!< Maximum ibi payload length. */
    uint8_t hdrMode;         /*!< Support hdr mode, could be OR logic in i3c_hdr_mode. */
} i3c_device_information_t;

/* Forward declaration of the i3c_bus_t typedef. */
typedef struct _i3c_bus i3c_bus_t;

/* Forward declaration of the i3c_device_control_info_t typedef. */
typedef struct _i3c_device_control_info i3c_device_control_info_t;

/* Forward declaration of the i3c_device_ibi_info_t typedef. */
typedef struct _i3c_device_ibi_info i3c_device_ibi_info_t;

/*! @brief I3C device definition. */
typedef struct _i3c_device
{
    list_element_t listNode;                   /*!< list node to link i3c devices in i3c bus. */
    i3c_bus_t *bus;                            /*!< I3C bus pointer, points to current bus the device is attached. */
    i3c_device_control_info_t *devControlInfo; /*!< Pointer to control information structure of the device. */
    i3c_device_information_t info;             /*!< Pointer to device information structure of the device. */
    uint8_t initDynamicAddr;                   /*!< Initial dynamic address for the device. */
    i3c_device_ibi_info_t *ibiInfo;            /*!< Pointer to IBI request information structure of the device. */
} i3c_device_t;

/* Forward declaration of the i2c_device_control_info_t typedef. */
typedef struct _i2c_device_control_info i2c_device_control_info_t;

/*! @brief I2C device definition. */
typedef struct _i2c_device
{
    list_element_t listNode;                   /*!< list node to link i2c devices in i3c bus. */
    i3c_bus_t *bus;                            /*!< I3C bus pointer, points to current bus the device is attached. */
    i2c_device_control_info_t *devControlInfo; /*!< Pointer to device information structure of the device. */
    uint8_t staticAddr;                        /*!< static address for I2C device. */
    uint8_t lvr;                               /*!< LVR for I2C device. */
} i2c_device_t;

/*! @brief CCC command structure for CCC frame */
typedef struct _i3c_ccc_cmd
{
    uint8_t cmdId;     /*!< Command ID. */
    bool isRead;       /*!< Read command or write command. */
    uint8_t destAddr;  /*!< Destination address for the command, broadcast uses 0x7E, direct access uses dest device
                          dynamic address. */
    void *data;        /*!< Pointer to data to be transmitted or received. */
    uint16_t dataSize; /*!< Data size of data to be transmitted or received. */
} i3c_ccc_cmd_t;

/*! @brief I3C bus transfer structure for general data transfer. */
typedef struct _i3c_bus_transfer
{
    uint32_t regAddr;     /*!< Operate register address of the target device.*/
    uint32_t regAddrSize; /*!< Size of Register address. */
    bool isRead;          /*!< Read transfer or write transfer. */
    void *data;           /*!< Pointer to data to be transmitted or received. */
    uint32_t dataSize;    /*!< Data size of data to be transmitted or received. */
} i3c_bus_transfer_t;

/*! @brief I3C device hardware operation API set. */
typedef struct i3c_device_hw_ops
{
    status_t (*Init)(i3c_device_t *dev);          /*!< Init function to initialize I3C device.*/
    void (*Deinit)(i3c_device_t *dev);            /*!< Deinit function to de-initialize I3C device.*/
    status_t (*ProceedDAA)(i3c_device_t *master); /*!< ProceedDAA function, only required for I3C master device.*/
    bool (*CheckSupportCCC)(i3c_device_t *master, i3c_ccc_cmd_t *cmd); /*!< CheckSupportCCC function, optional for I3C
                                                                          master device, not require for slave device.*/
    status_t (*TransmitCCC)(i3c_device_t *master,
                            i3c_ccc_cmd_t *cmd); /*!< TransmitCCC function, only require for I3C master device.*/
    status_t (*DoI3CTransfer)(
        i3c_device_t *dev, i3c_bus_transfer_t *xfer); /*!< DoI3CTransfer function, only require for I3C master device.*/
    status_t (*DoI2CTransfer)(
        i2c_device_t *dev, i3c_bus_transfer_t *xfer); /*!< DoI2CTransfer function, only require for I3C slave device.*/
    void (*HotJoin)(i3c_device_t *master);            /*!< HotJoin function.*/
    void (*RequestMastership)(
        i3c_device_t *master); /*!< RequestMastership function, only require for I3C master device.*/
    void (*RegisterIBI)(i3c_device_t *master, uint8_t ibiAddress); /*!< Register IBI address with mandatory byte.*/
    void (*RequestIBI)(i3c_device_t *device, void *data, size_t dataSize); /*!< RequestIBI function.*/
} i3c_device_hw_ops_t;

/*! @brief I3C device information. */
struct _i3c_device_control_info
{
    i3c_device_hw_ops_t *funcs; /*!< Pointer to I3C device hardware operation API sets.*/
    void *resource;             /*!< Pointer to keep I3C device specific resource.*/
    bool isSecondary;           /*!< Specify if the device is secondary device.*/
    void *privateData;          /*!< Pointer to keep I3C device private data.*/
};

/*! @brief I2C device information. */
typedef struct i2c_device_hw_ops
{
    int (*Init)(i2c_device_t *dev);    /*!< I2C device initialize function.*/
    void (*Deinit)(i2c_device_t *dev); /*!< I2C device de-initialize function.*/
} i2c_device_hw_ops_t;

/*! @brief I3C master information. */
struct _i2c_device_control_info
{
    i2c_device_hw_ops_t *funcs; /*!< Pointer to I2C device hardware operation API sets.*/
    void *resource;             /*!< Pointer to keep I2C device specific resource.*/
    void *privateData;          /*!< Pointer to keep I2C device private data.*/
};

/*! @brief I3C device IBI information. */
typedef void (*i3c_dev_ibi_handler_t)(i3c_device_t *dev, const void *ibiData, uint32_t ibiLen);
struct _i3c_device_ibi_info
{
    uint32_t maxPayloadLength;        /*!< maximum IBI payload length. */
    bool enabled;                     /*!< is IBI enabled. */
    i3c_dev_ibi_handler_t ibiHandler; /*!< IBI handler when device registers IBI. */
};

/*! @brief I3C bus mode definition. */
typedef enum _i3c_bus_mode
{
    kI3C_Bus_PureMode,       /*!< only I3C devices are connected to the bus */
    kI3C_Bus_MixedMode_Fast, /*!<  I2C devices with 50ns spike filter are present on bus */
    kI3C_Bus_MixedMode_Slow, /*!<  I2C devices without 50ns spike filter are present on bus */
} i3c_bus_mode_t;

/*! @brief I3C address slot status in address pool. */
typedef enum _i3c_addr_slot_status
{
    kI3C_Bus_AddrSlot_Free = 0, /*!< Address slot is free. */
    kI3C_Bus_AddrSlot_Reserved, /*!< Address slot is reserved. */
    kI3C_Bus_AddrSlot_I2CDev,   /*!< Address slot is I2C device. */
    kI3C_Bus_AddrSlot_I3CDev,   /*!< Address slot is I3C device. */
} i3c_addr_slot_status_t;

/*! @brief I3C initial bus configuration, user input to configure. */
typedef struct _i3c_bus_config
{
    i3c_bus_mode_t busMode;        /*!< Bus mode. */
    uint32_t i2cBaudRate;          /*!< I2C baud rate. */
    uint32_t i3cOpenDrainBaudRate; /*!< I3C open drain baudrate. */
    uint32_t i3cPushPullBaudRate;  /*!< I3C push-pull baudrate. */
} i3c_bus_config_t;

/*! @brief I3C bus structure, contains bus mandatory informations.*/
struct _i3c_bus
{
    i3c_device_t *volatile currentMaster; /*!< Pointer to current I3C master on bus. */
    uint32_t addrSlots[((I3C_BUS_MAX_ADDR + 1U) * I3C_BUS_ADDR_SLOTWIDTH) /
                       I3C_BUS_ADDR_SLOTDEPTH]; /*!< I3C bus address pool. */
    i3c_bus_mode_t busMode;                     /*!< I3C bus mode. */
    uint32_t i2cBaudRate;                       /*!< I2C baud rate. */
    uint32_t i3cOpenDrainBaudRate;              /*!< I3C open drain baudrate. */
    uint32_t i3cPushPullBaudRate;               /*!< I3C push-pull baudrate. */
    list_label_t i2cDevList;                    /*!< I2C device list. */
    list_label_t i3cDevList;                    /*!< I3C device list. */
};

/*! @brief Device description structure in I3C DEFSLVS device list .*/
typedef struct _i3c_ccc_dev
{
    uint8_t dynamicAddr; /*!< Dynamic address for I3C device. */
    union
    {
        uint8_t dcr; /*!< Device Characteristics register value for I3C device. */
        uint8_t lvr; /*!< Legacy Virtual Register value for I2C device */
    };
    uint8_t bcr;        /*!< Bus characteristics register value. */
    uint8_t staticAddr; /*!< Static address for I3C/I2C device. */
} i3c_ccc_dev_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @name I3C bus operation
 * @{
 */

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the bus configuration structure to a default value. The default
 * values are:
 *   busConfig->busMode = kI3C_Bus_PureMode;
 *   busConfig->i2cBaudRate = 400000U;
 *   busConfig->i3cOpenDrainBaudRate = 1500000U;
 *   busConfig->i3cPushPullBaudRate = 4000000U;
 *
 * @param config Pointer to a configuration structure.
 */
void I3C_BusGetDefaultBusConfig(i3c_bus_config_t *busConfig);

/*!
 * @brief Creates I3C bus structure.
 *
 * This function creates the bus structure with input bus configuration. Address pool set up and device
 * list initialize process will be also done in this function call.
 *
 * @param bus Pointer to bus structure.
 * @param busConfig Pointer to the bus configuration structure.
 */
void I3C_BusCreate(i3c_bus_t *bus, const i3c_bus_config_t *busConfig);

/*!
 * @brief Get valid address slot in the I3C bus.
 *
 * This function will search for available address lot in the I3C bus address pool, the search starts from
 * the startAddr specified by user input, to end address defined in @ref I3C_BUS_MAX_ADDR. Will return the
 * available address if the related address slot is valid.
 *
 * @param bus Pointer to bus structure.
 * @param startAddr Start address for address slot searching, end address is defined in @ref I3C_BUS_MAX_ADDR.
 * @return Available address in the bus address pool.
 */
uint8_t I3C_BusGetValidAddrSlot(i3c_bus_t *bus, uint8_t startAddr);

/*!
 * @brief Set address slot status.
 *
 * This function will set an specified address to address slot and set the status.
 *
 * @param bus Pointer to bus structure.
 * @param addr address to be used.
 * @return status the address status of @ref i3c_addr_slot_status_t.
 */
void I3C_BusSetAddrSlot(i3c_bus_t *bus, uint8_t addr, i3c_addr_slot_status_t status);

/*!
 * @brief Add exist I3C device in bus to the bus device list.
 *
 * This function will simply add the device to the bus device list and set the related address slot.
 *
 * @param bus Pointer to bus structure.
 * @param dev Pointer to I3C device.
 */
void I3C_BusAddI3CDev(i3c_bus_t *bus, i3c_device_t *dev);

/*!
 * @brief Add exist I2C device in bus to the bus device list.
 *
 * This function will simply add the device to the bus device list and set the related address slot.
 *
 * @param bus Pointer to bus structure.
 * @param dev Pointer to I2C device.
 */
void I3C_BusAddI2CDev(i3c_bus_t *bus, i2c_device_t *dev);

/* @} */

/*!
 * @name I3C bus master operation
 * @{
 */

/*!
 * @brief Create I3C master structure on bus.
 *
 * This function will create I3C master bus structure, initialize the master according to bus characteristics, install
 * device information and device control information.
 *
 * @param masterDev Pointer to device structure creating as master.
 * @param bus Pointer to bus structure.
 * @param devInfo Pointer to device information structure.
 * @param masterControlInfo Pointer to master control information structure.
 */
status_t I3C_BusMasterCreate(i3c_device_t *masterDev,
                             i3c_bus_t *bus,
                             i3c_device_information_t *devInfo,
                             i3c_device_control_info_t *masterControlInfo);

/*!
 * @brief Register slave IBI information to bus master.
 *
 * This function will register the slave IBI information to bus master so that bus master know how
 * to handle slave IBI event.
 *
 * @param masterDev Pointer to device structure creating as master.
 * @param i3cDev Pointer to the I3C device master want to register.
 * @param devIbiInfo Pointer to device IBI information structure.
 */
status_t I3C_BusMasterRegisterDevIBI(i3c_device_t *masterDev, i3c_device_t *i3cDev, i3c_device_ibi_info_t *devIbiInfo);

/*!
 * @brief Bus master transfer CCC frame.
 *
 * Bus master call this function to transfer CCC frame, CCC frame command and data is prepared in @ref i3c_ccc_cmd_t
 * structure.
 *
 * @param masterDev Pointer to I3C master device.
 * @param command Pointer to ccc frame.
 */
status_t I3C_BusMasterSendCCC(i3c_device_t *masterDev, i3c_ccc_cmd_t *command);

/*!
 * @brief Bus master reset dynamic assigned address.
 *
 * Bus master call this function to reset dynamic assigned address, the operation could be done to all connected I3C
 * devices by using slave address I3C_BUS_BROADCAST_ADDR or to a specific connected device by using the device's dynamic
 * address.
 *
 * @param masterDev Pointer to I3C master device.
 * @param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 */
status_t I3C_BusMasterResetDAA(i3c_device_t *masterDev, uint8_t slaveAddr);

/*!
 * @brief Bus master do dynamic address assignment.
 *
 * Bus master call this function to do dynamic address assignment to the I3C devices connected on bus.
 *
 * @param masterDev Pointer to I3C master device.
 */
status_t I3C_BusMasterDoDAA(i3c_device_t *masterDev);

/*!
 * @brief Bus master set device dynamic address from static address.
 *
 * Bus master call this function to execute SETDASA CCC command to set device dynamic address from static address.
 *
 * @param masterDev Pointer to I3C master device.
 * @param staticAddr Device static address.
 * @param initDynamicAddr Device initialized dynamic address.
 */
status_t I3C_BusMasterSetDynamicAddrFromStaticAddr(i3c_device_t *master, uint8_t staticAddr, uint8_t initDynamicAddr);

/*!
 * @brief Bus master send slave list on bus.
 *
 * Bus master call this function to send slave list on bus to notify the secondary master.
 *
 * @param masterDev Pointer to I3C master device.
 */
status_t I3C_BusMasterSendSlavesList(i3c_device_t *masterDev);

/*!
 * @brief Bus master handle in-band-interrupt event.
 *
 * Bus master call this function to handle in-band-interrupt event.
 *
 * @param masterDev Pointer to I3C master device.
 * @param ibiAddress slave address which requests the IBI.
 * @param ibiData Pointer to the ibi data buffer.
 * @param payloadSize ibi data buffer size.
 */
status_t I3C_BusMasterHandleIBI(i3c_device_t *masterDev, uint8_t ibiAddress, void *ibiData, uint32_t payloadSize);

/*!
 * @brief Bus master do data transfer to I2C device.
 *
 * Bus master call this function to transfer data to connected I2C device.
 *
 * @param masterDev Pointer to I3C master device.
 * @param i2cDev Pointer to the I2C device master do transfer.
 * @param xfer Pointer to bus transfer.
 */
status_t I3C_BusMasterDoTransferToI2CDev(i3c_device_t *masterDev, i2c_device_t *i2cDev, i3c_bus_transfer_t *xfer);

/*!
 * @brief Bus master do data transfer to I3C device.
 *
 * Bus master call this function to transfer data to connected I3C device.
 *
 * @param masterDev Pointer to I3C master device.
 * @param i3cDev Pointer to the I3C device master do transfer.
 * @param xfer Pointer to bus transfer.
 */
status_t I3C_BusMasterDoTransferToI3CDev(i3c_device_t *masterDev, i3c_device_t *i3cDev, i3c_bus_transfer_t *xfer);

/*!
 * @brief Bus master enable events.
 *
 * Bus master call this function to enable events on bus.
 *
 * @param masterDev Pointer to I3C master device.
 * @param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 * @param busEvents Logic OR or member in @ref _i3c_bus_events.
 */
status_t I3C_BusMasterEnableEvents(i3c_device_t *masterDev, uint8_t slaveAddr, uint8_t busEvents);

/*!
 * @brief Bus master disable events.
 *
 * Bus master call this function to disable events on bus.
 *
 * @param masterDev Pointer to I3C master device.
 * @param slaveAddr Slave address, use I3C_BUS_BROADCAST_ADDR as broadcast address.
 * @param busEvents Logic OR or member in @ref _i3c_bus_events.
 */
status_t I3C_BusMasterDisableEvents(i3c_device_t *masterDev, uint8_t slaveAddr, uint8_t busEvents);

/*!
 * @brief Bus master get device information for a specific I3C device.
 *
 * Bus master call this function to get device information for a specific I3C device.
 *
 * @param masterDev Pointer to I3C master device.
 * @param slaveAddr Slave address, dynamic assigned address for a device.
 * @param devInfo Input pointer to structure i3c_device_information_t to store the read out device information.
 */
status_t I3C_BusMasterGetDeviceInfo(i3c_device_t *masterDev, uint8_t slaveAddr, i3c_device_information_t *devInfo);

/* @} */

/*!
 * @name I3C bus slave operation
 * @{
 */

/*!
 * @brief Create I2C slave structure on bus.
 *
 * This function will create I2C device bus structure, initialize the slave according to bus characteristics, install
 * device information including static address, lvr and device control information.
 *
 * @param i2cDev Pointer to device structure creating as I2C device.
 * @param bus Pointer to bus structure.
 * @param staticAddr Static address of the I2C device
 * @param lvr legacy virtual register value of the device.
 * @param devControlInfo Pointer to device control information structure.
 */
status_t I3C_BusI2CSlaveCreate(
    i2c_device_t *i2cDev, i3c_bus_t *bus, uint8_t staticAddr, uint8_t lvr, i2c_device_control_info_t *devControlInfo);

/*!
 * @brief Create I3C slave structure on bus.
 *
 * This function will create I3C device bus structure, initialize the slave according to bus characteristics, install
 * device information and device control information.
 *
 * @param i3cDev Pointer to device structure creating as I3C device.
 * @param bus Pointer to bus structure.
 * @param devInfo Pointer to device information structure
 * @param devControlInfo Pointer to device control information structure.
 */
status_t I3C_BusI3CSlaveCreate(i3c_device_t *i3cDev,
                               i3c_bus_t *bus,
                               i3c_device_information_t *devInfo,
                               i3c_device_ibi_info_t *ibiInfo,
                               i3c_device_control_info_t *devControlInfo);

/*!
 * @brief I3C slave device request Hot Join on bus.
 *
 * @param i3cDev Pointer to device structure creating as I3C device.
 */
status_t I3C_BusSlaveRequestHotJoin(i3c_device_t *i3cDev);

/*!
 * @brief I3C slave device request mastership on bus.
 *
 * @param i3cDev Pointer to device structure creating as I3C device.
 */
status_t I3C_BusSlaveRequestMasterShip(i3c_device_t *i3cDev);

/*!
 * @brief I3C slave request IBI events.
 *
 * @param i3cDev Pointer to device structure creating as I3C device.
 * @param data Pointer to data buffer to be sent in IBI event.
 * @param dataSize data size of IBI data.
 */
status_t I3C_BusSlaveRequestIBI(i3c_device_t *i3cDev, void *data, size_t dataSize);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif
