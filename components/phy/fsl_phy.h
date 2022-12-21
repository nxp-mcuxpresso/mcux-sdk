/*
 * Copyright 2020-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PHY_H_
#define _FSL_PHY_H_

#include "fsl_common.h"

/*! @brief This abstract layer is to unify the PHY interface in SDK, let application
 *  use one set of PHY interfaces. The data structures are applicable to different
 *  PHYs.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @note The following PHY registers are the IEEE802.3 standard definition, same register and bit field may
          have different names in various PHYs, but the feature they represent should be same or very similar. */

/*! @brief Defines the IEEE802.3 standard PHY registers. */
#define PHY_BASICCONTROL_REG        (0x00U) /*!< The PHY basic control register. */
#define PHY_BASICSTATUS_REG         (0x01U) /*!< The PHY basic status register. */
#define PHY_ID1_REG                 (0x02U) /*!< The PHY ID one register. */
#define PHY_ID2_REG                 (0x03U) /*!< The PHY ID two register. */
#define PHY_AUTONEG_ADVERTISE_REG   (0x04U) /*!< The PHY auto-negotiate advertise register. */
#define PHY_AUTONEG_LINKPARTNER_REG (0x05U) /*!< The PHY auto negotiation link partner ability register. */
#define PHY_AUTONEG_EXPANSION_REG   (0x06U) /*!< The PHY auto negotiation expansion register. */
#define PHY_1000BASET_CONTROL_REG   (0x09U) /*!< The PHY 1000BASE-T control register. */
#define PHY_MMD_ACCESS_CONTROL_REG  (0x0DU) /*!< The PHY MMD access control register. */
#define PHY_MMD_ACCESS_DATA_REG     (0x0EU) /*!< The PHY MMD access data register. */

/*! @brief Defines the mask flag in basic control register(Address 0x00). */
#define PHY_BCTL_SPEED1_MASK          ((uint16_t)0x0040U) /*!< The PHY speed bit mask(MSB).*/
#define PHY_BCTL_ISOLATE_MASK         ((uint16_t)0x0400U) /*!< The PHY isolate mask.*/
#define PHY_BCTL_DUPLEX_MASK          ((uint16_t)0x0100U) /*!< The PHY duplex bit mask. */
#define PHY_BCTL_RESTART_AUTONEG_MASK ((uint16_t)0x0200U) /*!< The PHY restart auto negotiation mask. */
#define PHY_BCTL_AUTONEG_MASK         ((uint16_t)0x1000U) /*!< The PHY auto negotiation bit mask. */
#define PHY_BCTL_SPEED0_MASK          ((uint16_t)0x2000U) /*!< The PHY speed bit mask(LSB). */
#define PHY_BCTL_LOOP_MASK            ((uint16_t)0x4000U) /*!< The PHY loop bit mask. */
#define PHY_BCTL_RESET_MASK           ((uint16_t)0x8000U) /*!< The PHY reset bit mask. */

/*! @brief Defines the mask flag in basic status register(Address 0x01). */
#define PHY_BSTATUS_LINKSTATUS_MASK  ((uint16_t)0x0004U) /*!< The PHY link status mask. */
#define PHY_BSTATUS_AUTONEGABLE_MASK ((uint16_t)0x0008U) /*!< The PHY auto-negotiation ability mask. */
#define PHY_BSTATUS_SPEEDUPLX_MASK   ((uint16_t)0x001CU) /*!< The PHY speed and duplex mask. */
#define PHY_BSTATUS_AUTONEGCOMP_MASK ((uint16_t)0x0020U) /*!< The PHY auto-negotiation complete mask. */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register(Address 0x04). */
#define PHY_100BaseT4_ABILITY_MASK    ((uint16_t)0x200U) /*!< The PHY have the T4 ability. */
#define PHY_100BASETX_FULLDUPLEX_MASK ((uint16_t)0x100U) /*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK ((uint16_t)0x080U) /*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK  ((uint16_t)0x040U) /*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK  ((uint16_t)0x020U) /*!< The PHY has the 10M full duplex ability.*/
#define PHY_IEEE802_3_SELECTOR_MASK   ((uint16_t)0x001U) /*!< The message type being sent by Auto-Nego.*/

/*! @brief Defines the mask flag in the 1000BASE-T control register(Address 0x09). */
#define PHY_1000BASET_FULLDUPLEX_MASK ((uint16_t)0x200U) /*!< The PHY has the 1000M full duplex ability.*/
#define PHY_1000BASET_HALFDUPLEX_MASK ((uint16_t)0x100U) /*!< The PHY has the 1000M half duplex ability.*/

typedef struct _phy_handle phy_handle_t;
typedef struct _phy_config phy_config_t;

/*! @brief IEEE 802.3 Clause 22 MDIO write data. */
typedef status_t (*mdioWrite)(uint8_t phyAddr, uint8_t regAddr, uint16_t data);

/*! @brief IEEE 802.3 Clause 22 MDIO read data. */
typedef status_t (*mdioRead)(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData);

/*! @brief IEEE 802.3 Clause 45 MDIO write data. */
typedef status_t (*mdioWriteExt)(uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t data);

/*! @brief IEEE 802.3 Clause 45 MDIO read data. */
typedef status_t (*mdioReadExt)(uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t *pData);

/*! @brief Defines the PHY link speed. */
typedef enum _phy_speed
{
    kPHY_Speed10M = 0U, /*!< ENET PHY 10M speed. */
    kPHY_Speed100M,     /*!< ENET PHY 100M speed. */
    kPHY_Speed1000M     /*!< ENET PHY 1000M speed. */
} phy_speed_t;

/*! @brief Defines the PHY link duplex. */
typedef enum _phy_duplex
{
    kPHY_HalfDuplex = 0U, /*!< ENET PHY half duplex. */
    kPHY_FullDuplex       /*!< ENET PHY full duplex. */
} phy_duplex_t;

/*! @brief Defines the PHY loopback mode. */
typedef enum _phy_loop
{
    kPHY_LocalLoop = 0U, /*!< ENET PHY local/digital loopback. */
    kPHY_RemoteLoop,     /*!< ENET PHY remote loopback. */
    kPHY_ExternalLoop,   /*!< ENET PHY external loopback. */
} phy_loop_t;

/*! @brief Defines the PHY MMD data access mode. */
typedef enum _phy_mmd_access_mode
{
    kPHY_MMDAccessNoPostIncrement = (1U << 14), /*!< ENET PHY MMD access data with no address post increment. */
    kPHY_MMDAccessRdWrPostIncrement =
        (2U << 14),                             /*!< ENET PHY MMD access data with Read/Write address post increment. */
    kPHY_MMDAccessWrPostIncrement = (3U << 14), /*!< ENET PHY MMD access data with Write address post increment. */
} phy_mmd_access_mode_t;

/*! @brief Defines the PHY interrupt type. */
typedef enum _phy_interrupt_type
{
    kPHY_IntrActiveLow = 0U, /*!< ENET PHY active low. */
    kPHY_IntrActiveHigh,     /*!< ENET PHY active high. */
} phy_interrupt_type_t;

/*! @brief PHY device operations. */
typedef struct _phy_operations
{
    status_t (*phyInit)(phy_handle_t *handle, const phy_config_t *config);
    status_t (*phyWrite)(phy_handle_t *handle, uint8_t phyReg, uint16_t data);
    status_t (*phyRead)(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData);
    status_t (*getAutoNegoStatus)(phy_handle_t *handle, bool *status);
    status_t (*getLinkStatus)(phy_handle_t *handle, bool *status);
    status_t (*getLinkSpeedDuplex)(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex);
    status_t (*setLinkSpeedDuplex)(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex);
    status_t (*enableLoopback)(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable);
    status_t (*enableLinkInterrupt)(phy_handle_t *handle, phy_interrupt_type_t type, bool enable);
    status_t (*clearInterrupt)(phy_handle_t *handle);
} phy_operations_t;

/*! @brief Defines PHY configuration. */
struct _phy_config
{
    uint8_t phyAddr;               /*!< PHY address. */
    void *resource;                /*!< PHY specific resource supporting operation of PHY hardware. */
    const phy_operations_t *ops;   /*!< PHY operational method. */
    phy_speed_t speed;             /*!< PHY speed configuration. */
    phy_duplex_t duplex;           /*!< PHY duplex configuration. */
    bool autoNeg;                  /*!< PHY auto-negotiation, true: enable, false: disable. */
    bool enableEEE;                /*!< PHY Energy Efficient Ethernet, true: enable, false: disable. */
    bool enableLinkIntr;           /*!< PHY Link management interrupt, true: enable, false: disable. */
    phy_interrupt_type_t intrType; /*!< PHY interrupt assert type. */
};

/*! @brief PHY device handle. */
struct _phy_handle
{
    uint8_t phyAddr;             /*!< PHY address. */
    void *resource;              /*!< PHY specific resource supporting operation of PHY hardware. */
    const phy_operations_t *ops; /*!< PHY operational method. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name PHY Driver
 * @{
 */

/*!
 * @brief Initializes PHY.
 * This function initializes PHY.
 *
 * @param handle  PHY device handle.
 * @param config  PHY configuration.
 * @retval kStatus_Success  PHY initialization succeeds
 * @retval kStatus_Fail  PHY initialization fails
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_Init(phy_handle_t *handle, const phy_config_t *config)
{
    handle->ops = config->ops;
    return handle->ops->phyInit(handle, config);
}
/*!
 * @brief PHY Write function.
 * This function writes data over the MDIO to the specified PHY register.
 *
 * @param handle  PHY device handle.
 * @param phyReg  The PHY register.
 * @param data    The data written to the PHY register.
 * @retval kStatus_Success  PHY write success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return handle->ops->phyWrite(handle, phyReg, data);
}

/*!
 * @brief PHY Read function.
 * This interface reads data over the MDIO from the specified PHY register.
 *
 * @param handle  PHY device handle.
 * @param phyReg  The PHY register address.
 * @param pData  The address to store the data read from the PHY register.
 * @retval kStatus_Success  PHY read success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return handle->ops->phyRead(handle, phyReg, pData);
}

/*!
 * @brief Gets the PHY auto-negotiation status.
 *
 * @param handle  PHY device handle.
 * @param status  The auto-negotiation status of the PHY.
 *        - true the auto-negotiation is over.
 *        - false the auto-negotiation is on-going or not started.
 * @retval kStatus_Success   PHY gets status success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    return handle->ops->getAutoNegoStatus(handle, status);
}

/*!
 * @brief Gets the PHY link status.
 *
 * @param handle  PHY device handle.
 * @param status  The link up or down status of the PHY.
 *        - true the link is up.
 *        - false the link is down.
 * @retval kStatus_Success   PHY get link status success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    return handle->ops->getLinkStatus(handle, status);
}

/*!
 * @brief Gets the PHY link speed and duplex.
 *
 * @brief This function gets the speed and duplex mode of PHY. User can give one of speed
 * and duplex address paramter and set the other as NULL if only wants to get one of them.
 *
 * @param handle  PHY device handle.
 * @param speed   The address of PHY link speed.
 * @param duplex  The link duplex of PHY.
 * @retval kStatus_Success   PHY get link speed and duplex success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    return handle->ops->getLinkSpeedDuplex(handle, speed, duplex);
}

/*!
 * @brief Sets the PHY link speed and duplex.
 *
 * @param handle  PHY device handle.
 * @param speed   Specified PHY link speed.
 * @param duplex  Specified PHY link duplex.
 * @retval kStatus_Success   PHY gets status success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    return handle->ops->setLinkSpeedDuplex(handle, speed, duplex);
}

/*!
 * @brief Enables/Disables PHY loopback mode.
 *
 * @param handle  PHY device handle.
 * @param mode    The loopback mode to be enabled, please see "phy_loop_t".
 * All loopback modes should not be set together, when one loopback mode is set
 * another should be disabled.
 * @param speed   PHY speed for loopback mode.
 * @param enable  True to enable, false to disable.
 * @retval kStatus_Success   PHY get link speed and duplex success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    return handle->ops->enableLoopback(handle, mode, speed, enable);
}

/*!
 * @brief Enables/Disables PHY link management interrupt.
 *
 * This function controls link status change interrupt. Application should get
 * status through PHY_GetLinkStatus() and PHY_GetAutoNegotiationStatus() when
 * interrupt triggers.
 *
 * @note Not all PHYs support link up, link down and auto auto-negotiation complete
 * interrupt separately. Some PHY may combine link up/down or no link up or no
 * auto-negotiation complete interrupt. The interrupt trigger situation depends
 * on specific PHY.
 *
 * @param handle  PHY device handle.
 * @param type    PHY interrupt type.
 * @param enable  True to enable, false to disable.
 * @retval kStatus_Success  PHY enables/disables interrupt success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_EnableLinkInterrupt(phy_handle_t *handle, phy_interrupt_type_t type, bool enable)
{
    return handle->ops->enableLinkInterrupt(handle, type, enable);
}

/*!
 * @brief Clears PHY interrupt status.
 * @note Usually this API clears all interrupts of PHY because related register
 * flags are read clear.
 *
 * @param handle  PHY device handle.
 * @retval kStatus_Success  PHY read and clear interrupt success
 * @retval kStatus_Timeout  PHY MDIO visit time out
 */
static inline status_t PHY_ClearInterrupt(phy_handle_t *handle)
{
    return handle->ops->clearInterrupt(handle);
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif
