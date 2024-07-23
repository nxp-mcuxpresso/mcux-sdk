/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ELE_BASE_API_H_
#define _FSL_ELE_BASE_API_H_

#include "fsl_common.h"
#include "fsl_device_registers.h"

/*! @addtogroup ele_base_api */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Configurations
 ******************************************************************************/


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RESPONSE_SUCCESS                                                   (0xd6u)
#define SHIFT_16                                                           (16u)
#define SHIFT_8                                                            (8u)
#define MSG_RESPONSE_MAX                                                   (16u)
#define MSG_TAG_CMD                                                        (0x17u)
#define MSG_TAG_RESP                                                       (0xE1u)

#define PING                                                               (0x17010106u)
#define PING_SIZE                                                          (0x1u)
#define PING_RESPONSE_HDR                                                  (0xe1010206u)

#define GET_FW_VERSION                                                     (0x179D0106u)
#define GET_FW_VERSION_SIZE                                                (0x1u)
#define GET_FW_VERSION_RESPONSE_HDR                                        (0xe19D0406u)

#define CLOCK_CHANGE_START                                                 (0x17100106u)
#define CLOCK_CHANGE_START_SIZE                                            (0x1u)
#define CLOCK_CHANGE_START_RESPONSE_HDR                                    (0xe1100206u)

#define CLOCK_CHANGE_FINISH                                                (0x17110206u)
#define CLOCK_CHANGE_FINISH_SIZE                                           (0x2u)
#define CLOCK_CHANGE_FINISH_RESPONSE_HDR                                   (0xe1110206u)

#define VOLTAGE_CHANGE_START                                               (0x17120106u)
#define VOLTAGE_CHANGE_START_SIZE                                          (0x1u)
#define VOLTAGE_CHANGE_START_RESPONSE_HDR                                  (0xe1120206u)

#define VOLTAGE_CHANGE_FINISH                                              (0x17130106u)
#define VOLTAGE_CHANGE_FINISH_SIZE                                         (0x1u)
#define VOLTAGE_CHANGE_FINISH_RESPONSE_HDR                                 (0xe1130206u)

#define GET_FW_STATUS                                                      (0x17C50106u)
#define GET_FW_STATUS_SIZE                                                 (0x1u)
#define GET_FW_STATUS_RESPONSE_HDR                                         (0xe1C50306u)

#define ENABLE_APC                                                         (0x17D20106u)
#define ENABLE_APC_SIZE                                                    (0x1u)
#define ENABLE_APC_RESPONSE_HDR                                            (0xe1D20206u)

#define START_RNG                                                          (0x17a30106u)
#define START_RNG_SIZE                                                     (0x1u)
#define START_RNG_RESPONSE_HDR                                             (0xe1a30206u)

#define FORWARD_LIFECYCLE                                                  (0x17950206u)
#define FORWARD_LIFECYCLE_SIZE                                             (0x2u)
#define FORWARD_LIFECYCLE_RESPONSE_HDR                                     (0xe1950206u)

#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && (FSL_FEATURE_SOC_OTFAD_COUNT > 1)
#define ENABLE_OTFAD                                                       (0x17c60206u)
#define ENABLE_OTFAD_SIZE                                                  (2u)
#else
#define ENABLE_OTFAD                                                       (0x17c60106u)
#define ENABLE_OTFAD_SIZE                                                  (1u)
#endif  /* FSL_FEATURE_SOC_OTFAD_COUNT */
#define ENABLE_OTFAD_RESPONSE_HDR                                          (0xe1c60206u)

#define RELEASE_RDC                                                        (0x17C40206u)
#define RELEASE_RDC_SIZE                                                   (0x2u)
#define RELEASE_RDC_RESPONSE_HDR                                           (0xe1C40206u)

/*! @name Driver version */
/*@{*/
/*! @brief Defines ELE Base API version 1.0.1.*/
#define FSL_ELE_BASE_API_DRIVER_VERSION (MAKE_VERSION(1, 0, 1))
/*@}*/


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Ping ELE
 *
 * This function Ping EdgeLock Enclave, can be sent at any time to verify ELE is alive.
 * Additionally, this command reloads the fuse shadow registers and kick the Sentinel active bit.
 * This active bit must be kicked at least once every day (24 hours).
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_Ping(S3MU_Type *mu);

/*!
 * @brief Get ELE FW Version
 *
 * This function is used to retrieve the Sentinel FW version.
 *
 * @param mu MU peripheral base address
 * @param EleFwVersion Pointer where ElE firmware version will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_GetFwVersion(S3MU_Type *mu, uint32_t *EleFwVersion);

/*!
 * @brief Get ELE FW Status
 *
 * This function is used to retrieve the Sentinel FW status.
 *
 * @param mu MU peripheral base address
 * @param EleFwStatus Pointer where ElE firmware status will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_GetFwStatus(S3MU_Type *mu, uint32_t *EleFwStatus);

/*!
 * @brief Enable APC (Application core)
 *
 * This function is used by RTC (real time core) to release APC (Application core) when needed.
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_EnableAPC(S3MU_Type *mu);

/*!
 * @brief Forward Lifecycle update
 *
 * This function is to change chip lifecycle
 *  0x01U for NXP provisoned
 *  0x02U for OEM Open
 *  0x08U for OEM Closed
 *  0x80U for OEM Locked
 *
 * @param mu MU peripheral base address
 * @param Lifecycle to switch
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_ForwardLifecycle(S3MU_Type *mu, uint32_t Lifecycle);

/*!
 * @brief Release RDC
 *
 * This function is used to release specifed RDC to the core identified in this function.
 * The RDC will be released only if the FW of the core to which is the RDC ownership is going to be
 * transferred has been properly authenticated and verified.
 *
 * @param mu MU peripheral base address
 * @param RdcID Resource Domain Control identifier
 * @param CoreID Core identifier
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_ReleaseRDC(S3MU_Type *mu, uint32_t RdcID, uint32_t CoreID);

/*!
 * @brief Start the initialization of the RNG context.
 *
 * The RNG must be started before using some of the ELE services.
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_StartRng(S3MU_Type *mu);

/*!
 * @brief Enable an instance of OTFAD.
 *
 * @param mu MU peripheral base address
 * @param OtfadID ID of the OTFAD instance to enable - used only if there are
 * multiple instances on the SoC
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_EnableOtfad(S3MU_Type *mu, uint8_t OtfadID);

/*!
 * @brief Start the clock change process
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_ClockChangeStart(S3MU_Type *mu);

/*!
 * @brief Change ELE and/or CM33 clock
 *
 * It is valid to pass both parameters at the same time if the SoC supports both.
 *
 * @param mu MU peripheral base address
 * @param NewClockRateELE the new clock rate for ELE
 * @param NewClockRateCM33 the new clock rate for the CM33 core
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_ClockChangeFinish(S3MU_Type *mu, uint8_t NewClockRateELE, uint8_t NewClockRateCM33);

/*!
 * @brief Start the voltage change process
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_VoltageChangeStart(S3MU_Type *mu);

/*!
 * @brief Finish the voltage change process
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_BaseAPI_VoltageChangeFinish(S3MU_Type *mu);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */


#endif /* _FSL_ELE_BASE_API_H_ */
