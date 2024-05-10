/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smscm.h"
#include "fsl_common.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smscm"
#endif
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
 * API
 ******************************************************************************/

/*!
 * @brief Get ECC attribute.
 * @param base SMSCM peripheral address.
 * @param eccAtt Ecc attribute.
 */
void SMSCM_GetEccAttribute(SMSCM_Type *base, smscm_ecc_fault_attr_t *eccAttribute)
{
    /* Initializes the ECC Attribute structure to zero. */
    (void)memset(eccAttribute, 0, sizeof(*eccAttribute));

    eccAttribute->eccSyn = (uint8_t)((base->OCMFTR & SMSCM_OCMFTR_EFSYN_MASK) >> SMSCM_OCMFTR_EFSYN_SHIFT);

    eccAttribute->eccMasterNum = (uint8_t)((base->OCMFTR & SMSCM_OCMFTR_EFMST_MASK) >> SMSCM_OCMFTR_EFMST_SHIFT);

    eccAttribute->eccWrite = (bool)((base->OCMFTR & SMSCM_OCMFTR_EFW_MASK) >> SMSCM_OCMFTR_EFW_SHIFT);

    eccAttribute->eccMasterSize = (uint8_t)((base->OCMFTR & SMSCM_OCMFTR_EFMS_MASK) >> SMSCM_OCMFTR_EFMS_SHIFT);

    eccAttribute->eccProtect = (uint8_t)((base->OCMFTR & SMSCM_OCMFTR_EFPRT_MASK) >> SMSCM_OCMFTR_EFPRT_SHIFT);
}

/*!
 * @brief Clear each 1-bit correctable or non-correctable error.
 * @param base SMSCM peripheral address.
 * @param errLocation ECC Error Location
 */
void SMSCM_ClearEccError(SMSCM_Type *base, uint8_t errLocation)
{
    if (errLocation < 8U)
    {
        base->OCMEIR = SMSCM_OCMEIR_ENCERRN(1UL << errLocation);
    }
    else
    {
        base->OCMEIR = SMSCM_OCMEIR_E1BERRN(1UL << (errLocation - 8U));
    }
}
