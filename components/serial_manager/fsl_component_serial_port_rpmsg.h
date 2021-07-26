/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SERIAL_PORT_RPMSG_H__
#define __SERIAL_PORT_RPMSG_H__

#include "fsl_adapter_rpmsg.h"

/*!
 * @addtogroup serial_port_rpmsg
 * @ingroup serialmanager
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief serial port uart handle size*/
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#define SERIAL_PORT_RPMSG_HANDLE_SIZE (HAL_RPMSG_HANDLE_SIZE + 16U)
#else /* !SERIAL_MANAGER_NON_BLOCKING_MODE */
#define SERIAL_PORT_RPMSG_HANDLE_SIZE (HAL_RPMSG_HANDLE_SIZE + 32U)
#endif

/*! @} */
#endif /* __SERIAL_PORT_RPMSG_H__ */
