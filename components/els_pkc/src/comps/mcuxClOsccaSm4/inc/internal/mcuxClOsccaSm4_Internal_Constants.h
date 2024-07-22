/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClOsccaSm4_Internal_Constants.h
 *  @brief Internal constant definitions for the mcuxClOsccaSm4 component
 */

#ifndef MCUXCLOSCCASM4_INTERNAL_CONSTANTS_H_
#define MCUXCLOSCCASM4_INTERNAL_CONSTANTS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MCUXCLOSCCASM4_ROTATE_LEFT_UINT32(x, n) (((x) << (n)) | ((x) >> (32U - (n))))
#define MCUXCLOSCCASM4_RK_WORDS            (32U)
#define MCUXCLOSCCASM4_ENCRYPT             (0x1U)
#define MCUXCLOSCCASM4_DECRYPT             (0x0U)
#define MCUXCLOSCCASM4_BLOCK_SIZE          (16u)
#define MCUXCLOSCCASM4_BLOCK_SIZE_WORDS    (MCUXCLOSCCASM4_BLOCK_SIZE / sizeof(uint32_t))

typedef uint32_t mcuxClOsccaSm4_Status_t;

#define MCUXCLOSCCASM4_STATUS_LOADKEY_OK                                      ((mcuxClOsccaSm4_Status_t) 0x011A2E03U)            /**< \brief LoadKey successful */
#define MCUXCLOSCCASM4_STATUS_CRYPT_OK                                        ((mcuxClOsccaSm4_Status_t) 0x011A2E0BU)            /**< \brief Crypt operation successful */
#define MCUXCLOSCCASM4_STATUS_FAULT_ATTACK                                    ((mcuxClOsccaSm4_Status_t) 0x011AF0F0U)            /**< \brief Fault attack detected */
#define MCUXCLOSCCASM4_STATUS_ERROR                                           ((mcuxClOsccaSm4_Status_t) 0x011A533CU)            /**< \brief Feature Failed */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASM4_INTERNAL_CONSTANTS_H_ */
