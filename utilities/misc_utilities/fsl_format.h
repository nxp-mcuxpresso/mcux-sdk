/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FORMAT_H_
#define _FSL_FORMAT_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef CONVERT_STRING_LENGTH
#define CONVERT_STRING_LENGTH 12U
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
/*!
 * @brief Convert a uint32 number to a string.
 *
 * Call this function to convert a uint32 to string.
 *
 * @param   num Number to be converted.
 * @return  Returns the string converted.
 */
uint8_t *FORMAT_Dec2Str(uint32_t num);

/*!
 * @brief Convert a hex to a ascii.
 *
 * Call this function to convert a hex to ascii.
 *
 * @param   hex    Hex to be converted.
 * @return  Returns the ascii converted.
 */
uint8_t *FORMAT_Hex2Ascii(uint8_t hex);

#endif /*_FSL_FORMAT_H_*/
