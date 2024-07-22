/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_TSTMR_H_
#define FSL_TSTMR_H_

#include "fsl_common.h"

/*!
 * @addtogroup tstmr_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tstmr"
#endif

/*! @name Driver version */
/*! @{ */
#define FSL_TSTMR_DRIVER_VERSION (MAKE_VERSION(2, 0, 2)) /*!< Version 2.0.2 */
                                                         /*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Reads the time stamp.
 *
 * This function reads the low and high registers and returns the 56-bit free running
 * counter value. This can be read by software at any time to determine the software ticks.
 * TSTMR registers can be read with 32-bit accesses only. The TSTMR LOW read should occur first, 
 * followed by the TSTMR HIGH read.
 *
 * @param base TSTMR peripheral base address.
 *
 * @return The 56-bit time stamp value.
 */
static inline uint64_t TSTMR_ReadTimeStamp(TSTMR_Type *base)
{
    uint32_t reg_l;
    uint32_t reg_h;
    uint32_t regPrimask = DisableGlobalIRQ();
    /* A complete read operation should include both TSTMR LOW and HIGH reads. If a HIGH read does not follow a LOW
     * read, then any other Time Stamp value read will be locked at a fixed value. The TSTMR LOW read should occur
     * first, followed by the TSTMR HIGH read.
     * */
    reg_l = base->L;
    __DMB();
    reg_h = base->H;

    EnableGlobalIRQ(regPrimask);

    return (uint64_t)reg_l | (((uint64_t)reg_h) << 32U);
}

/*!
 * @brief Delays for a specified number of microseconds.
 *
 * This function repeatedly reads the timestamp register and waits for the user-specified
 * delay value.
 *
 * @param base      TSTMR peripheral base address.
 * @param delayInUs Delay value in microseconds.
 */
static inline void TSTMR_DelayUs(TSTMR_Type *base, uint64_t delayInUs)
{
#if defined(TSTMR_CLOCK_FREQUENCY_MHZ)
    uint64_t startTime = TSTMR_ReadTimeStamp(base);
    while (TSTMR_ReadTimeStamp(base) - startTime < TSTMR_CLOCK_FREQUENCY_MHZ * delayInUs)
    {
    }
#else
    assert(0);
#endif
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_TSTMR_H_ */
