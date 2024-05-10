/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_MDIO_H_
#define FSL_NETC_MDIO_H_

#include "fsl_netc.h"
#include "fsl_netc_soc.h"
#include "netc_hw/fsl_netc_hw.h"

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region api_mdio
#endif
//////////////////////////////////////
// Group for the MDIO Driver
//////////////////////////////////////
/*!
 * @defgroup netc_mdio NETC MDIO Driver
 * @details Group for MDIO API and data structure.
 * API starts with NETC_MDIO.
 * Parameter starts with netc_mdio_handle_t.
 * Driver supports to access external actual PHY for normal ethernet transmission and internel virtual PHY for RevMII
 * mode. For each MAC port, initialization should be done to bound a handle to specified MDIO port. Use handle to
 * indicate specific MAC port to do MDIO read/write. All Clause 22/45 MDIO read/write functions will send command and
 * wait transmission over through polling busy bit. PHY status automatical check is used to polling the register status
 * of PHY with hardware at regular intervals.
 * @ingroup netc_api
 */

/*!
 * @defgroup netc_mdio_init MDIO initialization module
 * @details Configurate specified MAC port MDIO
 * @ingroup netc_mdio
 */
/*!
 * @defgroup netc_mdio_xfer MDIO write/read module
 * @details IEEE Clause 22/45 MDIO access for PHY
 *
 * @ingroup netc_mdio
 */
/*!
 * @defgroup netc_mdio_phy_status MDIO PHY status module
 * @details Automatically polling to read PHY register with hardware
 *
 * @ingroup netc_mdio
 */

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion api_mdio
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_mdio_init
#endif
/*! @addtogroup netc_mdio_init
 * @{
 */

/*!
 * @brief Enumeration for the MAC port MDIO type
 */
typedef enum _netc_mdio_type
{
    kNETC_EMdio,        /*!< Bound handle to EMDIO access, submodule of NETC. */
    kNETC_InternalMdio, /*!< Bound handle to MAC port internal MDIO access, submodule of EP/Switch. */
    kNETC_ExternalMdio, /*!< Bound handle to MAC port external MDIO access, submodule of EP/Switch. */
} netc_mdio_type_t;

/*!
 * @brief Structure to choose MDIO entity(Internal/external MDIO for specified EP/Switch port)
 */
typedef struct _netc_mdio
{
    netc_mdio_type_t type;       /*!< Internal or external MAC port MDIO. */
    netc_hw_eth_port_idx_t port; /*!< MDIO port index, only meaningful when port MDIO type is used. */
} netc_mdio_t;

/*!
 * @brief MDIO handle
 */
typedef struct _netc_mdio_handle
{
    netc_mdio_t mdio; /*!< MDIO identificator. */
} netc_mdio_handle_t;

/*!
 * @brief MDIO configuration structure
 */
typedef struct _netc_mdio_config
{
    netc_mdio_t mdio;       /*!< MDIO identificator. */
    uint32_t srcClockHz;    /*!< MDIO reference clock for MDC frequency calculation. */
    bool isNegativeDriven;  /*!< MDIO driven at positive(false)/negative(true) of MDC edge. */
    bool isPreambleDisable; /*!< Enable/Disable generation of MDIO preamble. */
} netc_mdio_config_t;

/*! @} */ // end of netc_mdio_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_mdio_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_mdio_phy_status
#endif
/*! @addtogroup netc_mdio_phy_status
 * @{
 */

/*!
 * @brief PHY auto status check configuration structure
 */
typedef struct _netc_mdio_phy_status
{
    uint16_t interval;           /*!< PHY status read interval in units of 1-2 ms. A value of 0 indicates disable. */
    bool isC45Used;              /*!< PHY status read with Clause 22/45 MDIO access. */
    uint8_t phyOrPortAddr;       /*!< MDIO PHY address(Clause 22) / port address(Clause 45). */
    uint8_t regiOrDevAddr;       /*!< MDIO register address(Clause 22) / device address(Clause 45). */
    uint16_t c45RegiAddr;        /*!< MDIO register address(Clause 45). */
    uint16_t enableIntrHigh2Low; /*!< Bit high-to-low event interrupt enable. */
    uint16_t enableIntrLow2High; /*!< Bit low-to-high event interrupt enable. */
} netc_mdio_phy_status_t;

/*! @} */ // end of netc_mdio_phy_status
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_mdio_phy_status
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_mdio_init
#endif
/*! @addtogroup netc_mdio_init
 * @{
 */

/*!
 * @brief Initialize the MDIO
 * @note The EMDIO can be used independently. The port internal/external MDIO is a part of EP/Switch,
 * should be initialized and used after EP/Switch is enabled.
 *
 * @param handle MDIO handle.
 * @param config MDIO configuration.
 * @return status_t
 */
status_t NETC_MDIOInit(netc_mdio_handle_t *handle, netc_mdio_config_t *config);

/*! @} */ // end of netc_mdio_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_mdio_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_mdio_xfer
#endif
/*! @addtogroup netc_mdio_xfer
 * @{
 */

/*!
 * @brief IEEE802.3 Clause 22 MDIO write data
 *
 * @param handle MDIO handle.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register address.
 * @param data The data written to PHY.
 * @return status_t
 */
status_t NETC_MDIOWrite(netc_mdio_handle_t *handle, uint8_t phyAddr, uint8_t regAddr, uint16_t data);

/*!
 * @brief IEEE802.3 Clause 22 MDIO read data
 *
 * @param handle MDIO handle.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register address.
 * @param pData The received data from PHY.
 * @return status_t
 */
status_t NETC_MDIORead(netc_mdio_handle_t *handle, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData);

/*!
 * @brief IEEE802.3 Clause 45 MDIO write data
 *
 * @param handle MDIO handle.
 * @param portAddr The MDIO port address(PHY address).
 * @param devAddr The device address.
 * @param regAddr The PHY register address.
 * @param data The data written to PHY.
 * @return status_t
 */
status_t NETC_MDIOC45Write(
    netc_mdio_handle_t *handle, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t data);

/*!
 * @brief IEEE802.3 Clause 45 MDIO read data
 *
 * @param handle MDIO handle.
 * @param portAddr The MDIO port address(PHY address).
 * @param devAddr The device address.
 * @param regAddr The PHY register address.
 * @param pData The received data from PHY.
 * @return status_t
 */
status_t NETC_MDIOC45Read(
    netc_mdio_handle_t *handle, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t *pData);

/*! @} */ // end of netc_mdio_xfer
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_mdio_xfer
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_mdio_phy_status
#endif
/*! @addtogroup netc_mdio_phy_status
 * @{
 */

/*!
 * @brief Setup the mechanism to check PHY status automatically
 * This is a hardware mechanism to read specified PHY register in a configured time interval
 * instead of polling the PHY in software.
 *
 * @param handle  MDIO handle.
 * @param config  The configuration of the PHY status automatical check.
 * @return status_t
 */
status_t NETC_MDIOSetPhyStatusCheck(netc_mdio_handle_t *handle, netc_mdio_phy_status_t *config);

/*!
 * @brief Get the PHY register bit status transition interrupt flag(s).
 *
 * @param handle  MDIO handle.
 * @param low2HighMask  The interrupt flag of a 0->1 transition on a corresponding bit of PHY register.
 * @param high2LowMask  The interrupt flag of a 1->0 transition on a corresponding bit of PHY register.
 */
void NETC_MDIOPhyStatusGetFlags(netc_mdio_handle_t *handle, uint16_t *low2HighMask, uint16_t *high2LowMask);

/*!
 * @brief Clear the PHY register bit status transition interrupt flag(s).
 *
 * @param handle  MDIO handle.
 * @param low2HighMask  Clear the interrupt flag of a 0->1 transition on a corresponding bit of PHY register.
 * @param high2LowMask  Clear the interrupt flag of a 1->0 transition on a corresponding bit of PHY register.
 */
void NETC_MDIOPhyStatusClearFlags(netc_mdio_handle_t *handle, uint16_t low2HighMask, uint16_t high2LowMask);

/*! @} */ // end of netc_mdio_phy_status
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_mdio_phy_status
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_MDIO_H_ */
