/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/**
 * @file  mcuxClMac_Constants.h
 * @brief Constants and status codes for the mcuxClMac component
 */

#ifndef MCUXCLMAC_CONSTANTS_H_
#define MCUXCLMAC_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClMac_Constants mcuxClMac_Constants
 * @brief Constants of @ref mcuxClMac component
 * @ingroup mcuxClMac
 * @{
 */
/* TODO CLNS-8684: Unionize and describe return codes */
#define MCUXCLMAC_STATUS_ERROR           ((mcuxClMac_Status_t) 0x08885330u)
#define MCUXCLMAC_STATUS_FAILURE         ((mcuxClMac_Status_t) 0x08885334u)
#define MCUXCLMAC_STATUS_INVALID_PARAM   ((mcuxClMac_Status_t) 0x088853F8u)
#define MCUXCLMAC_STATUS_FAULT_ATTACK    ((mcuxClMac_Status_t) 0x0888F0F0u)
#define MCUXCLMAC_STATUS_OK              ((mcuxClMac_Status_t) 0x08882E03u)
#define MCUXCLMAC_STATUS_COMPARE_NOK     ((mcuxClMac_Status_t) 0x088853FCu)
/** @}*/

#endif /* MCUXCLMAC_CONSTANTS_H_ */
