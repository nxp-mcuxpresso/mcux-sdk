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

/*==========================================================================*/
/* Implementation of the various CRC algorithms.                            */
/*==========================================================================*/

/* Includes */

#include "crc.h"

/* Defines */

#define CRC_J1850_POLY  0x1DU

/* Types */

/* Local Functions */

/*--------------------------------------------------------------------------*/
/* Calculate XOR CRC                                                        */
/*--------------------------------------------------------------------------*/
uint32_t CRC_Xor(const uint32_t *addr, uint32_t size)
{
    const uint32_t *a = addr;
    uint32_t sz = size;
    uint32_t crc = 0U;

    /* Loop over data */
    while (sz > 0U)
    {
        /* Update CRC */
        crc ^= *a;
        a++;
        sz--;
    }

    /* Return CRC */
    return crc;
}

/*--------------------------------------------------------------------------*/
/* Calculate J1850                                                          */
/*--------------------------------------------------------------------------*/
uint8_t CRC_J1850(const uint8_t *addr, uint32_t size)
{
    const uint8_t *a = addr;
    uint32_t sz = size;
    uint32_t crc = 0xFFUL;

    /* Loop over data */
    while (sz > 0U)
    {
        crc ^= *a;

        /* Loop over data bits */
        for (uint32_t i = 0U; i < 8U; i++)
        {
            crc = ((crc & 0x80U) != 0U) ? ((crc << 1U) ^ CRC_J1850_POLY)
                : ((uint8_t) (crc << 1U));
        }

        a++;
        sz--;
    }

    /* Return CRC */
    return (uint8_t) crc;
}

/*--------------------------------------------------------------------------*/
/* Calculate CRC32                                                          */
/*--------------------------------------------------------------------------*/
uint32_t CRC_Crc32(const uint8_t *addr, uint32_t size)
{
    const uint8_t *a = addr;
    uint32_t sz = size;
    uint32_t crc = 0U;

    /* Poly table */
    static uint32_t const s_crcTable[] =
    {
        0x4DBDF21CU, 0x500AE278U, 0x76D3D2D4U, 0x6B64C2B0U,
        0x3B61B38CU, 0x26D6A3E8U, 0x000F9344U, 0x1DB88320U,
        0xA005713CU, 0xBDB26158U, 0x9B6B51F4U, 0x86DC4190U,
        0xD6D930ACU, 0xCB6E20C8U, 0xEDB71064U, 0xF0000000U
    };

    /* Loop over data */
    while (sz > 0U)
    {
        crc = (crc >> 4U) ^ s_crcTable[(crc ^ (((uint32_t)(*a)) >> 0U))
                & 0x0FU];
        crc = (crc >> 4U) ^ s_crcTable[(crc ^ (((uint32_t) (*a)) >> 4U))
                & 0x0FU];
        a++;
        sz--;
    }

    /* Return CRC */
    return crc;
}

