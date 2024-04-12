/*
** ###################################################################
**
** Copyright 2023 NXP
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** o Redistributions of source code must retain the above copyright notice, this list
**   of conditions and the following disclaimer.
**
** o Redistributions in binary form must reproduce the above copyright notice, this
**   list of conditions and the following disclaimer in the documentation and/or
**   other materials provided with the distribution.
**
** o Neither the name of the copyright holder nor the names of its
**   contributors may be used to endorse or promote products derived from this
**   software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
** ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

#ifndef CRC_H
#define CRC_H

/*!
 * @addtogroup crc
 * @{
 */

/*!
 * @file
 * @brief Header file containing CRC functions.
 */

/* Includes */

#include <stdbool.h>
#include <stdint.h>

/* Functions */

/*!
 * @name CRC functions
 * @{
 */

/*!
 * Calculate CRC based on 32-bit XOR.
 *
 * @param[in]  addr  Pointer to data to CRC
 * @param[in]  size  Size of data in words
 *
 * Fast CRC that does a simple XOR of all the data words.
 *
 * @return Returns the checksum.
 */
uint32_t CRC_Xor(const uint32_t *addr, uint32_t size);

/*!
 * Calculate CRC based on the J1850 algorithm.
 *
 * @param[in]  addr  Pointer to data to CRC
 * @param[in]  size  Size of data in bytes
 *
 * CRC based on the SAE-J1850 with a seed of 0xFF and a
 * polynomial of 0x1D.
 *
 * @return Returns the CRC.
 */
uint8_t CRC_J1850(const uint8_t *addr, uint32_t size);

/*!
 * Calculate CRC based on the CRC32 algorithm.
 *
 * @param[in]  addr  Pointer to data to CRC
 * @param[in]  size  Size of data in bytes
 *
 * CRC based on the IEEE polynomial used for Ethernet.
 *
 * @return Returns the CRC.
 */
uint32_t CRC_Crc32(const uint8_t *addr, uint32_t size);

/** @} */

#endif /* CRC_H */

/** @} */

