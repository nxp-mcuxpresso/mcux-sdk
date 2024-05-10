/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_SOC_H_
#define FSL_NETC_SOC_H_

#include "netc_hw/fsl_netc_hw.h"

#define TMR_PCI_HDR_TYPE0    NETC_F0_PCI_HDR_TYPE0
#define EMDIO_PCI_HDR_TYPE0  NETC_F1_PCI_HDR_TYPE0
#define SWITCH_PCI_HDR_TYPE0 NETC_F2_PCI_HDR_TYPE0
#define ENETC0_PCI_HDR_TYPE0 NETC_F3_PCI_HDR_TYPE0
#define ENETC1_PCI_HDR_TYPE0 NETC_F4_PCI_HDR_TYPE0

/*! @name NETC register map. */
/*@{*/
#define NETC_ENETC_PCIE_FUNC_OFFSET       (3U)       /*!< The ENETC PCIE function index. */
#define NETC_ENETC_PORT_GROUP_BASE_OFFSET (0x4000U)  /*!< The ENETC port group register base address offset. */
#define NETC_ENETC_GLOBAL_BASE_OFFSET     (0x10000U) /*!< The ENETC global register base address offset. */
/*@}*/

/*! @brief Defines the NETC link index. */
typedef enum _netc_soc_link
{
    kNETC_SocLinkSwitchPort0 = 0U,
    kNETC_SocLinkSwitchPort1,
    kNETC_SocLinkSwitchPort2,
    kNETC_SocLinkSwitchPort3,
    kNETC_SocLinkEp0,
} netc_soc_link_t;

/*! @brief Defines the speed for the MII data interface in RevMII mode. */
typedef enum _netc_soc_revmii_mii_speed
{
    kNETC_SocRevMiiSpeed100M = 0U, /*!< RevMII MII mode speed 100 Mbps. */
    kNETC_SocRevMiiSpeed10M, /*!< RevMII MII mode speed 10 Mbps. */
} netc_soc_revmii_mii_speed_t;

/*! @brief Defines clock source for NETC timer. */
typedef enum _netc_soc_timer_clk_sel
{
    kNETC_SocTimerCcmClk = 0U, /*!< PTP timer clock source is from CCM tmr_1588_clk_root. */
    kNETC_SocTimerExtPinClk, /*!< PTP timer clock source is from chip pin. */
} netc_soc_timer_clk_sel_t;

/*! @brief Defines the timer trigger input source. */
typedef enum _netc_soc_timer_trig_input
{
    kNETC_SocTimerTrigIomuxInput = 0U, /*!< Input from IOMUX. */
    kNETC_SocTimerTrigXbarInput, /*!< Input from XBAR. */
} netc_soc_timer_trig_input_t;

/*! @brief Station interface index enumerator */
typedef enum _netc_hw_si_idx
{
    kNETC_ENETC0PSI0 = (0U << 8U) | (0U << 4U) | 0U, /*!< ENETC0 PSI0, index 0 */
    kNETC_ENETC1PSI0 = (1U << 8U) | (0U << 4U) | 1U, /*!< ENETC1 PSI0, index 1 */
    kNETC_ENETC1VSI1 = (1U << 8U) | (1U << 4U) | 2U, /*!< ENETC1 VSI1, index 2 */
} netc_hw_si_idx_t;

/*! @brief Ethernet MAC port resource for the NETC module */
typedef enum _netc_hw_eth_port_idx
{
    kNETC_ENETC0EthPort   = 0U, /*!< Ethernet MAC port for ENETC0 */
    kNETC_SWITCH0EthPort0 = 1U, /*!< Ethernet MAC port0 for SWITCH */
    kNETC_SWITCH0EthPort1 = 2U, /*!< Ethernet MAC port1 for SWITCH */
    kNETC_SWITCH0EthPort2 = 3U, /*!< Ethernet MAC port2 for SWITCH */
    kNETC_SWITCH0EthPort3 = 4U, /*!< Ethernet MAC port3 for SWITCH */
} netc_hw_eth_port_idx_t;

/*!
 * @brief Enumeration for NETC timer external trigger index
 */
typedef enum _netc_timer_exttrig_index
{
    kNETC_TimerExtTrig1 = 0,
    kNETC_TimerExtTrig2,
} netc_timer_exttrig_index_t;

/*!
 * @brief Set link MII mode
 * @note If RevMII is enabled on this port, addr represents RevMII slave PHY address.
 * RevMII is disabled, addr represents external physical PHY address which is used by
 * port MDIO.
 *
 * @param link  Link port.
 * @param addr  Link port PHY address.
 * @return status_t
 */
status_t NETC_SocSetMiiMode(netc_soc_link_t link, netc_hw_mii_mode_t miiMode);

/*!
 * @brief Enable RevMII mode for specified link
 *
 * @param link  Link port.
 * @param enable  Enable/Disable RevMII.
 * @return status_t
 */
status_t NETC_SocEnableRevmii(netc_soc_link_t link, bool enable);

/*!
 * @brief Set RevMII speed when this port uses MII mode
 *
 * @param link  Link port.
 * @param miiRate  MII speed.
 * @return status_t
 */
status_t NETC_SocSetRevmiiMiiRate(netc_soc_link_t link, netc_soc_revmii_mii_speed_t miiRate);

/*!
 * @brief Set RGMII delay for both TXC and RXC
 * Reference clock is fixed to 200MHz clock sourced from PLL 1G.
 * Delay time = ((DLY_TARGET+1) * 1/32 * clock cycle of reference clock.
 *
 * @param link  Link port.
 * @param delayTarget  RGMII delay. Delay time = ((delayTarget + 1) * 5 / 32) nanosecond.
 * @return status_t
 */
status_t NETC_SocSetRevmiiRgmiiDelay(netc_soc_link_t link, uint8_t delayTarget);

/*!
 * @brief Select the PTP timer clock source
 *
 * @param clkSel  PTP timer clock source.
 * @return status_t
 */
status_t NETC_SocTimerClkSel(netc_soc_timer_clk_sel_t clkSel);

/*!
 * @brief Select the timer external trigger source
 *
 * @param timerTrigger  Timer trigger instance.
 * @param inputSel  Input source.
 * @return status_t
 */
status_t NETC_SocSetTimer(netc_timer_exttrig_index_t timerTrigger, netc_soc_timer_trig_input_t inputSel);

/*!
 * @brief Set link RMII mode time clock output on ceratin pin
 *
 * @param output  True: output, False: input.
 * @return status_t
 */
status_t NETC_SocSetRmiiRefClk(netc_soc_link_t link, bool output);

/*!
 * @brief Get register map resource
 *
 * @param handle  The enetc hw handle.
 * @param si      The SI object.
 */
void NETC_SocGetBaseResource(netc_enetc_hw_t *hw, netc_hw_si_idx_t si);

/*!
 * @brief Set link port PHY address
 * @note If RevMII is enabled on this port, addr represents RevMII slave PHY address.
 * RevMII is disabled, addr represents external physical PHY address which is used by
 * port MDIO.
 *
 * @param link  Link port.
 * @param phyAddr  Link port PHY address.
 * @return status_t
 */
status_t NETC_SocSetLinkAddr(netc_soc_link_t link, uint8_t phyAddr);

/*!
 * @brief Get func instance from mac port
 *
 * @param port  The enetc mac port.
 * @return uint32_t
 */
uint32_t NETC_SocGetFuncInstance(netc_hw_eth_port_idx_t port);

#endif /* FSL_NETC_SOC_H_ */
