/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EZHV_H_
#define FSL_EZHV_H_

#include "fsl_common.h"

/*!
 * @addtogroup ezhv
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief cache driver version. */
#define FSL_EZHV_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Callback function prototype for the ezhv driver. */
typedef void (*ezhv_callback_t)(void *param);

/*!
 * @brief Structure for EZHV copy image to destination address
 *
 * Defines source and destination address for copying image with given size.
 */
typedef struct _ezhv_copy_image
{
    uint32_t srcAddr;
    uint32_t destAddr;
    uint32_t size;
} ezhv_copy_image_t;

/*!
 * @Brief List of EZHV APIs
 */
typedef uint32_t ezhv_api_t;

#define EZHV_API_MAX_ARG 8U

/*!
 * @brief parameters used by EZHV
 */
typedef struct _ezhv_param {
    ezhv_api_t ezhvApi;
    uint32_t argc;
    uint32_t *argv[EZHV_API_MAX_ARG];
} ezhv_param_t;

/*! @brief ARM to wake up EZHV by 4 kinds of interrupt requests */
typedef enum _ARM2EZHV_INT {
    kEZHV_ARM2EZHV_MEI = SYSCON4_ARM2EZHV_INT_CTRL_MEIP_MASK,
    kEZHV_ARM2EZHV_SEI = SYSCON4_ARM2EZHV_INT_CTRL_SEIP_MASK,
    kEZHV_ARM2EZHV_MSI = SYSCON4_ARM2EZHV_INT_CTRL_MSIP_MASK,
    kEZHV_ARM2EZHV_MTI = SYSCON4_ARM2EZHV_INT_CTRL_MTIP_MASK,
} arm2ezhv_intctl_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the EZHV.
 *
 * @param ezhvCopyImage The information about the EZHV image to copy.
 */
void EZHV_Init(ezhv_copy_image_t *ezhvCopyImage);

 /*!
 * @brief Initialize the EZHV.
 *
 * This function is similar with EZHV_Init, the difference is this function
 * does not install the firmware, the firmware could be installed using
 * EZHV_InstallFirmware.
 */
void EZHV_InitWithoutFirmware(void);

/*!
 * @brief install EZHV firmware by given image info
 *
 * @param ezhvCopyImage The information about the EZHV image to copy.
 */
void EZHV_InstallFirmware(ezhv_copy_image_t *ezhvCopyImage);

/*!
 * @brief Boot EZHV from given address bootAddr
 *
 * @param bootAddr The boot address.
 */
void EZHV_Boot(uint32_t bootAddr);

/*!
 * @brief Deinitialize the EZHV.
 */
void EZHV_Deinit(void);

/*!
 * @brief Install the complete callback function.
 *
 * @param callback The callback called when EZHV program finished.
 * @param param parameter for callback function
 */
void EZHV_InstallCallback(ezhv_callback_t callback, void *param);

/*!
 * @brief Install the complete callback function..
 *
 * @return The base address of arm2ezhv paramter
 */
uint32_t *EZHV_GetParaAddr(void);

/*!
 * @brief When EZHV is in wait state, this is used to wake up EZHV.
 *
 * @param arm2ezhvInt The interrupt to wake up EZHV.
 */
void EZHV_WakeupEzhv(arm2ezhv_intctl_t arm2ezhvInt);

/*!
 * @brief Set the parameter used by EZHV.
 *
 * @param para Parameter written into shared mem between ARM and EZHV.
 */
void EZHV_SetPara(ezhv_param_t *para);
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
