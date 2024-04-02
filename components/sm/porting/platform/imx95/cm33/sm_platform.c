/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "sm_platform.h"

/*
 * Note:
 *     1. System Manager is running on a cortex-m33(SCMI Server Side) on iMX95.
 *     2. The file is used for SCMI Client Side.
 *     3. Add it for fix build issue when build legacy demo(Non-SM) for cortex-m33.
 */
/*******************************************************************************
 * Definition
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initialize channel and MU interface for communication with SM.
 */
void SM_Platform_Init(void)
{
}

/*!
 * @brief Deinitialize MU interface.
 */
void SM_Platform_Deinit(void)
{
}

/*!
 * @brief SM Platform Handler.
 */
void SM_Platform_Handler(void)
{
}
