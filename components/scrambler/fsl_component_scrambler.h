/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SCRAMBLER_H_
#define _SCRAMBLER_H_

/*!
 * @addtogroup Scrambler
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief scrambler_whiten_poly_type bit definitions. */
typedef enum _scrambler_whiten_poly_type
{
    kSCRAMBLER_GaloisPolyType    = 0U, /*!< A Galois type LFSR is used with the whiten polynomial. */
    kSCRAMBLER_FibonnaciPolyType = 1U  /*!< A Fibonacci type LFSR is used with the whiten polynomial. */
} scrambler_whiten_poly_type_t;

/*!
 * @brief whitenRefIn bit definitions.
 *
 * @note The input data stream is reflected bit-wise, per byte. Bit 7 becomes bit 0, bit 6 becomes bit 1, etc.
 * Will only cause the reflection of the payload data bits as they are used in the whiten calculation
 * and will not cause any change in the output bit order.
 */
typedef enum _scrambler_whiten_cfg_ref_in
{
    kSCRAMBLER_WhitenInputNoRef = 0U, /*!< Do not manipulate input data stream. */
    kSCRAMBLER_WhitenRefInput   = 1U  /*!< Reflect each byte in the input stream bitwise. */
} scrambler_whiten_cfg_ref_in_t;

/*! * @brief Whitener module configure structure. */
typedef struct _whitener_config
{
    scrambler_whiten_poly_type_t type;         /*!< Whiten polynomial type. See "scrambler_whiten_poly_type_t". */
    scrambler_whiten_cfg_ref_in_t whitenRefIn; /*!< Whiten reflect input. See "scrambler_whiten_cfg_ref_in_t". */
    uint16_t whitenInitValue;                  /*!< Initialization value for Whitening/De-whitening. Maximum 9 bits. */
    uint16_t whitenPolyValue; /*!< Whitener polynomial vaule. The polynomial value must be right-justified
                                   if smaller than 9-bits. Maximum 9 bits. */
    uint8_t whitenSize;       /*!< Length of whitener LFSR. Maximum value 9. */
} whitener_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Software whitening function.
 *
 * The function whitens/de-whitens the input buffer.
 *
 * @note This function will store the result in the input buffer.
 * @code
 * config = (whitener_config_t) {
 *         .type      = kSCRAMBLER_GaloisPolyType,
 *         .whitenRefIn        = kSCRAMBLER_WhitenInputNoRef,
 *         .whitenSize        = 8,
 *         .whitenInit        = 0x1f,
 *         .whitenPoly        = 0x0,
 *     };
 *
 *     SCRAMBLER_Whiten(&config, p, SCRAMBLER_BUF_SZ);
 *
 * @endcode
 * @param whitenerConfig whitener configuration structure pointer. See "whitener_config_t".
 * @param pBuff Input buffer pointer and store the result in the input buffer.
 * @param buffLength buffer length.
 */
void SCRAMBLER_Whiten(whitener_config_t *whitenerConfig, uint8_t *pBuff, uint32_t buffLength);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _SCRAMBLER_H_ */
