/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ecat.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ecat"
#endif

/* Read PHY register via ESC MII Management Interface. */
status_t ECAT_EscMdioRead(ECAT_Type *ecat, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    ecat->MII_MANAGEMENT_PDI_ACCESS_STATE = ECAT_MII_MANAGEMENT_PDI_ACCESS_STATE_BF0_MASK;

    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF15_MASK)
        return kStatus_Busy;

    /*Clear the error bits*/
    ecat->MII_MANAGEMENT_CONTROL_OR_STATUS = ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF8(0x00);

    /*Set phy and register address*/
    ecat->PHY_ADDRESS          = ECAT_PHY_ADDRESS_BF0(phy_addr);
    ecat->PHY_REGISTER_ADDRESS = ECAT_PHY_REGISTER_ADDRESS_BF0(reg_addr);

    /*Set read command*/
    ecat->MII_MANAGEMENT_CONTROL_OR_STATUS = ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF8(0x01);

    /*wait command done*/
    while (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF15_MASK)
        ;

    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF13_MASK)
        return kStatus_Fail;
    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF14_MASK)
        return kStatus_Fail;

    *data = ecat->PHY_DATA;

    return kStatus_Success;
}

/* Write PHY register via ESC MII Management Interface. */
status_t ECAT_EscMdioWrite(ECAT_Type *ecat, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    ecat->MII_MANAGEMENT_PDI_ACCESS_STATE = ECAT_MII_MANAGEMENT_PDI_ACCESS_STATE_BF0_MASK;

    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF15_MASK)
        return kStatus_Busy;

    /*Clear the error bits*/
    ecat->MII_MANAGEMENT_CONTROL_OR_STATUS = ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF8(0x00);

    /*Set phy and register address*/
    ecat->PHY_ADDRESS          = ECAT_PHY_ADDRESS_BF0(phy_addr);
    ecat->PHY_REGISTER_ADDRESS = ECAT_PHY_REGISTER_ADDRESS_BF0(reg_addr);
    ecat->PHY_DATA             = data;

    /*Set read command*/
    ecat->MII_MANAGEMENT_CONTROL_OR_STATUS =
        ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF8(0x02) | ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF0_MASK;

    /*wait command done*/
    while (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF15_MASK)
        ;

    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF13_MASK)
        return kStatus_Fail;
    if (ecat->MII_MANAGEMENT_CONTROL_OR_STATUS & ECAT_MII_MANAGEMENT_CONTROL_OR_STATUS_BF14_MASK)
        return kStatus_Fail;

    return kStatus_Success;
}
