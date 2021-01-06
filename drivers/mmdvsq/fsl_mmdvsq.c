/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mmdvsq.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mmdvsq"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Performs the MMDVSQ division operation and returns the remainder.
 *
 * param   base        MMDVSQ peripheral address
 * param   dividend    Dividend value
 * param   divisor     Divisor value
 * param   isUnsigned  Mode of unsigned divide
 *                      - true   unsigned divide
 *                      - false  signed divide
 *
 */
int32_t MMDVSQ_GetDivideRemainder(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned)
{
    uint32_t temp = 0;

    temp = base->CSR;
    temp &= ~(MMDVSQ_CSR_USGN_MASK | MMDVSQ_CSR_REM_MASK);
    /* Prepare setting for calculation */
    temp |= MMDVSQ_CSR_USGN(isUnsigned) | MMDVSQ_CSR_REM(true);
    /* Write setting to CSR register */
    base->CSR = temp;
    /* Write dividend to DEND register */
    base->DEND = (uint32_t)dividend;
    /* Write divisor to DSOR register and start calculation if Fast-Start is enabled */
    base->DSOR = (uint32_t)divisor;
    /* Start calculation by writing 1 to SRT bit in case Fast-Start is disabled */
    base->CSR |= MMDVSQ_CSR_SRT_MASK;
    /* Return remainder, if divide-by-zero is enabled and occurred, reading from
     * RES result is error terminated */
    return (int32_t)base->RES;
}

/*!
 * brief Performs the MMDVSQ division operation and returns the quotient.
 *
 * param   base        MMDVSQ peripheral address
 * param   dividend    Dividend value
 * param   divisor     Divisor value
 * param   isUnsigned  Mode of unsigned divide
 *                      - true   unsigned divide
 *                      - false  signed divide
 *
 */
int32_t MMDVSQ_GetDivideQuotient(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned)
{
    uint32_t temp = 0;

    temp = base->CSR;
    temp &= ~(MMDVSQ_CSR_USGN_MASK | MMDVSQ_CSR_REM_MASK);
    /* Prepare setting for calculation */
    temp |= MMDVSQ_CSR_USGN(isUnsigned) | MMDVSQ_CSR_REM(false);
    /* Write setting mode to CSR register */
    base->CSR = temp;
    /* Write dividend to DEND register */
    base->DEND = (uint32_t)dividend;
    /* Write divisor to DSOR register and start calculation when Fast-Start is enabled */
    base->DSOR = (uint32_t)divisor;
    /* Start calculation by writing 1 to SRT bit in case Fast-Start is disabled */
    base->CSR |= MMDVSQ_CSR_SRT_MASK;
    /* Return quotient, if divide-by-zero is enabled and occurred, reading from
     * RES result is error terminated */
    return (int32_t)base->RES;
}

/*!
 * brief Performs the MMDVSQ square root operation.
 *
 * This function performs the MMDVSQ square root operation and returns the square root
 * result of a given radicand value.
 *
 * param   base        MMDVSQ peripheral address
 * param   radicand    Radicand value
 *
 */
uint16_t MMDVSQ_Sqrt(MMDVSQ_Type *base, uint32_t radicand)
{
    /* Write radicand to RCND register , and start calculation */
    base->RCND = radicand;
    /* Return result */
    return (uint16_t)base->RES;
}
