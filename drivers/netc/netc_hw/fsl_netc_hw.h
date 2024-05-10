/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_HW_H_
#define FSL_NETC_HW_H_

#include "fsl_netc.h"

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw
#endif
/*! @addtogroup netc_hw
 * @{
 */

/*! @brief MSIX table address offset. */
#define NETC_MSIX_TABLE_OFFSET     (0x10000U)
/*! @brief MSIX PBA address offset. */
#define NETC_MSIX_TABLE_PBA_OFFSET (0x800U)

/*! @brief Nanosecond in one second. */
#define NETC_NANOSECOND_ONE_SECOND (1000000000UL)

/*!
 * @brief Register groups for the PCIe function
 *
 */
typedef struct _netc_func
{
    union
    {
        ENETC_PCI_TYPE0_Type *pf;    /*!< PSI function */
        ENETC_VF_PCI_TYPE0_Type *vf; /*!< VSI function */
    };
} netc_func_t;

/*!
 * @brief Register groups for the Port/Link hardware
 *
 */
typedef struct _netc_port_hw
{
    NETC_PORT_Type *port; /*!< Port Address */
    union
    {
        NETC_ETH_LINK_Type *eth;       /*!< MAC Port Address */
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        NETC_PSEUDO_LINK_Type *pseudo; /*!< Pseudo link port address */
#endif
    };
} netc_port_hw_t;

/*!
 * @brief Register group for the ENETC peripheral hardware
 *
 */
typedef struct _netc_enetc_hw
{
    netc_func_t func;             /*!< PCIE function register */
    NETC_ENETC_Type *base;        /*!< Base register of ENETC module */
    NETC_SW_ENETC_Type *common;   /*!< Common register of ENETC module */
    netc_port_hw_t portGroup;     /*!< Port register group */
    ENETC_GLOBAL_Type *global;    /*!< Global NETC address */
    ENETC_SI_Type *si;            /*!< Station Interfce for the P/V SI */
    netc_msix_entry_t *msixTable; /*!< MSIX table address */
} netc_enetc_hw_t;

#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
/*!
 * @brief Register group for the Switch peripheral hardware
 *
 */
typedef struct _netc_switch_hw
{
    ENETC_PCI_TYPE0_Type *func;                                    /*!< Base address for PCIE function */
    NETC_SW_Type *base;                                            /*!< Base address for Switch */
    NETC_SW_ENETC_Type *common;                                    /*!< Common address of ENETC Module */
    netc_port_hw_t ports[FSL_FEATURE_NETC_SWITCH_MAX_PORT_NUMBER]; /*!< Port Register Group */
    ENETC_GLOBAL_Type *global;                                     /*!< GLobal NETC Register Base Address */
    netc_msix_entry_t *msixTable;                                  /*!< MSIX table address */
} netc_switch_hw_t;
#endif

/*!
 * @brief Register group for the Timer peripheral hardware
 *
 */
typedef struct _netc_timer_hw
{
    ENETC_PCI_TYPE0_Type *func;   /*!< PCIE function register */
    ENETC_PF_TMR_Type *base;      /*!< Base register address for timer module */
    ENETC_GLOBAL_Type *global;    /*!< Global NETC register address */
    netc_msix_entry_t *msixTable; /*!< MSIX table address */
} netc_timer_hw_t;

/*! @brief Register group for both EMDIO and port external MDIO. */
typedef struct _netc_mdio_hw
{
    __IO uint32_t EMDIO_CFG;  /*!< External MDIO configuration register, offset: 0x1C00 */
    __IO uint32_t EMDIO_CTL;  /*!< External MDIO interface control register, offset: 0x1C04 */
    __IO uint32_t EMDIO_DATA; /*!< External MDIO interface data register, offset: 0x1C08 */
    __IO uint32_t EMDIO_ADDR; /*!< External MDIO register address register, offset: 0x1C0C */
    __I uint32_t EMDIO_STAT;  /*!< External MDIO status register, offset: 0x1C10 */
    uint8_t RESERVED_1[12];
    __IO uint32_t PHY_STATUS_CFG;   /*!< PHY status configuration register, offset: 0x1C20 */
    __IO uint32_t PHY_STATUS_CTL;   /*!< PHY status control register, offset: 0x1C24 */
    __I uint32_t PHY_STATUS_DATA;   /*!< PHY status data register, offset: 0x1C28 */
    __IO uint32_t PHY_STATUS_ADDR;  /*!< PHY status register address register, offset: 0x1C2C */
    __IO uint32_t PHY_STATUS_EVENT; /*!< PHY status event register, offset: 0x1C30 */
    __IO uint32_t PHY_STATUS_MASK;  /*!< PHY status mask register, offset: 0x1C34 */
} netc_mdio_hw_t;

/*! @} */ // end of netc_hw
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_table
#endif
/*! @addtogroup netc_hw_table
 * @{
 */

/*! @brief Register group for SI/Switch command bd ring */
typedef struct _netc_cbdr_hw
{
    __IO uint32_t CBDRMR; /*!< Command BDR mode register. */
    __I uint32_t CBDRSR;  /*!< Command BDR status register. */
    uint8_t RESERVED_0[8];
    __IO uint32_t CBDRBAR0; /*!< Command BDR base address register 0 */
    __IO uint32_t CBDRBAR1; /*!< Command BDR base address register 1 */
    __IO uint32_t CBDRPIR;  /*!< Command BDR producer index register */
    __IO uint32_t CBDRCIR;  /*!< Command BDR consumer index register */
    __IO uint32_t CBDRLENR; /*!< Command BDR length register */
} netc_cbdr_hw_t;

/*! @brief Handle for common part of EP/Switch NTMP */
typedef struct _netc_cbdr_handle
{
    netc_cbdr_hw_t *base;          /*!< Point to hardware command bd ring register group. */
    netc_cmd_bdr_t *cmdr;          /*!< Point to command BD ring handle. */
    netc_tb_data_buffer_t *buffer; /*!< Point to table common data buffer. */
} netc_cbdr_handle_t;

/*! @} */ // end of netc_hw_table
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_table
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_common
#endif
/*! @addtogroup netc_hw_common
 * @{
 */

static inline uint16_t EP_IncreaseIndex(uint16_t index, uint32_t max)
{
    uint32_t i = (uint32_t)index;

    if (++i >= max)
    {
        i = 0;
    }
    return (uint16_t)i;
}

/*!
 * @brief Get the VSI index
 *
 * @param vsi  The VSI number.
 */
uint16_t NETC_SIGetVsiIndex(netc_vsi_number_t vsi);

/*!
 * @brief Set layer2/3 Dos configuration
 *
 * @param base
 * @param config
 */
static inline void NETC_IPFInit(NETC_SW_ENETC_Type *base, const netc_ipf_config_t *config)
{
    base->DOSL2CR = NETC_SW_ENETC_DOSL2CR_SAMEADDR(config->l2DiscardSmacEquDmac) |
                    NETC_SW_ENETC_DOSL2CR_MSAMCC(config->l2DiscardMCSmac);
    //    base->DOSL3CR = NETC_SW_ENETC_DOSL3CR_SAMEADDR(config->l3DiscardSipEquDip);
}

/*!
 * @brief Initialize the Ingress Stream Identification Key construction rule profiles
 *
 * @param base
 * @param rule
 * @param enKcPair1
 * @return void
 */
void NETC_PSFPKcProfileInit(NETC_SW_ENETC_Type *base, const netc_isi_kc_rule_t *rule, bool enKcPair1);

/*!
 * @brief Initialize the customer vlan type
 *
 * @param base
 * @param config
 * @param enRtag
 * @return void
 */
void NETC_RxVlanCInit(NETC_SW_ENETC_Type *base, const netc_vlan_classify_config_t *config, bool enRtag);

/*!
 * @brief Initialize the ingress QoS classification
 *
 * @param base
 * @param profile
 * @param enProfile1
 */
void NETC_RxQosCInit(NETC_SW_ENETC_Type *base, const netc_qos_classify_profile_t *profile, bool enProfile1);

/*! @} */ // end of netc_hw_common
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_common
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_table
#endif
/*! @addtogroup netc_hw_table
 * @{
 */

/*!
 * @brief Initialize the command BD ring
 *
 * @param base
 * @param config
 * @return kStatus_Success
 * @return kStatus_Fail
 */
status_t NETC_CmdBDRInit(netc_cbdr_hw_t *base, const netc_cmd_bdr_config_t *config);

/*!
 * @brief Deinitialize the command BD ring
 *
 * @param base
 * @return kStatus_Success
 */
status_t NETC_CmdBDRDeinit(netc_cbdr_hw_t *base);

/*!
 * @brief Send the Command Buffer Descriptor to operate on a NTMP table
 *
 * @param base
 * @param cbdr
 * @param cbd
 * @param version
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_CmdBDSendCommand(netc_cbdr_hw_t *base,
                               netc_cmd_bdr_t *cbdr,
                               netc_cmd_bd_t *cbd,
                               netc_cbd_version_t version);

/*!
 * @brief Add entry into the ingress Port Filter Table.
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddIPFTableEntry(netc_cbdr_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_UpdateIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg);

/*!
 * @brief Query entry in the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_ipf_config_t *config);

/*!
 * @brief Delete an entry in the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Reset the counter of an ingress port filter Table entry
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_ResetIPFMatchCounter(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the matched count of an ingress port filter Table entry
 *
 * @param handle
 * @param entryID
 * @param count
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetIPFMatchedCount(netc_cbdr_handle_t *handle, uint32_t entryID, uint64_t *count);
/*!
 * @brief Add entry into Ingress Stream Identification table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddISITableEntry(netc_cbdr_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID);

/*!
 * @brief Delete an entry in Ingress stream identification table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelISITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Query Ingress Stream Identification table
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryISITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isi_config_t *config);

/*!
 * @brief Query Ingress Stream Identification table with key
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryISITableEntryWithKey(netc_cbdr_handle_t *handle, netc_tb_isi_keye_t *keye, netc_tb_isi_rsp_data_t *rsp);

/*!
 * @brief Add or update entry in Ingress Stream table
 *
 * @param handle
 * @param config
 * @param isAdd
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddOrUpdateISTableEntry(netc_cbdr_handle_t *handle, netc_tb_is_config_t *config, bool isAdd);

/*!
 * @brief Query Ingress Stream table
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryISTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_is_config_t *config);

/*!
 * @brief Delete an entry in Ingress stream table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelISTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Add entry into ingress stream filter table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddISFTableEntry(netc_cbdr_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry into ingress stream filter table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_UpdateISFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg);

/*!
 * @brief Delete an entry in Ingress stream filter table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelISFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Query entry from the Ingress stream filter table
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryISFTableEntry(netc_cbdr_handle_t *handle, netc_tb_isf_keye_t *keye, netc_tb_isf_rsp_data_t *rsp);

/*!
 * @brief Add entry in ingress stream count table
 *
 * @param handle
 * @param entryID
 * @return status_t
 */
status_t NETC_AddISCTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get ingress stream count statistic
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetISCStatistic(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic);

/*!
 * @brief Reset the count of the ingress stream count
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_ResetISCStatistic(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Add or update entry in stream gate instance table
 *
 * @param handle
 * @param config
 * @param isAdd
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddOrUpdateSGITableEntry(netc_cbdr_handle_t *handle, netc_tb_sgi_config_t *config, bool isAdd);

/*!
 * @brief Delete entry in the stream gate instance table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelSGITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get statistic of specified stream gate instance table entry
 *
 * @param handle
 * @param entryID
 * @param statis
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetSGIState(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *statis);

/*!
 * @brief Query entry from the stream gate instance table
 *
 * @param handle
 * @param entryID
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QuerySGITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgi_rsp_data_t *rsp);

/*!
 * @brief Add entry into Stream Gate Control List Table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddSGCLTableEntry(netc_cbdr_handle_t *handle, netc_tb_sgcl_gcl_t *config);

/*!
 * @brief Delete entry of Stream Gate Control List Table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelSGCLTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get Stream Gate Control List Table entry gate control list
 *
 * @param handle
 * @param gcl
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetSGCLGateList(netc_cbdr_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length);

/*!
 * @brief Get state (ref count) for Stream Gate Control List table entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetSGCLState(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state);

/*!
 * @brief Query entry from the Rate Policer table
 *
 * @param handle
 * @param entryID
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_QueryRPTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_rp_rsp_data_t *rsp);

/*!
 * @brief Add or update entry in Rate Policer table
 *
 * @param handle
 * @param config
 * @param cmd
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_AddOrUpdateRPTableEntry(netc_cbdr_handle_t *handle, netc_tb_rp_config_t *config, netc_tb_cmd_t cmd);

/*!
 * @brief Delete entry in the Rate Policer table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_DelRPTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get statistic of specified Rate Policer table entry
 *
 * @param handle
 * @param entryID
 * @param statis
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetRPStatistic(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis);

/*!
 * @brief Config the QBV (Time Gate Scheduling)
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_ConfigTGSAdminList(netc_cbdr_handle_t *handle, netc_tb_tgs_gcl_t *config);

/*!
 * @brief Get time gate table operation list
 *
 * @param handle
 * @param gcl
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t NETC_GetTGSOperationList(netc_cbdr_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length);
/*! @} */ // end of netc_hw_table
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_table
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_HW_H_ */
