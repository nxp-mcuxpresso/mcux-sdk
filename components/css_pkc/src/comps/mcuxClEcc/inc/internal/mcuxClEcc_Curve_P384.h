/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClEcc_Curve_P384.h
 *  @brief Curve P-384 parameters
 */

#ifndef MCUXCLECC_CURVE_P384_H_
#define MCUXCLECC_CURVE_P384_H_

#define MCUXCLECC_CURVE_P384_PRIME_P_LO192  \
  0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFEu, 0xFFFFFFFFu
#define MCUXCLECC_CURVE_P384_PRIME_P_HI192  \
  0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu
#define MCUXCLECC_CURVE_P384_PRIME_P  \
  MCUXCLECC_CURVE_P384_PRIME_P_LO192, MCUXCLECC_CURVE_P384_PRIME_P_HI192

#define MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN  48u
#define MCUXCLECC_CURVE_P384_PRIME_P_LOWHALF_BYTELEN  24u

#define MCUXCLECC_CURVE_P384_PRIME_P_NDASH  \
  0x00000001u, 0x00000001u

#define MCUXCLECC_CURVE_P384_PRIME_P_QSQR  \
  0x00000001u, 0xFFFFFFFEu, 0x00000000u, 0x00000002u, 0x00000000u, 0xFFFFFFFEu,  \
  0x00000000u, 0x00000002u, 0x00000001u, 0x00000000u, 0x00000000u, 0x00000000u

#define MCUXCLECC_CURVE_P384_COEFFICIENT_A  \
  0xFFFFFFFCu, 0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFEu, 0xFFFFFFFFu,  \
  0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu

#define MCUXCLECC_CURVE_P384_COEFFICIENT_B  \
  0xD3EC2AEFu, 0x2A85C8EDu, 0x8A2ED19Du, 0xC656398Du, 0x5013875Au, 0x0314088Fu,  \
  0xFE814112u, 0x181D9C6Eu, 0xE3F82D19u, 0x988E056Bu, 0xE23EE7E4u, 0xB3312FA7u

#define MCUXCLECC_CURVE_P384_BASEPOINT_X  \
  0x72760AB7u, 0x3A545E38u, 0xBF55296Cu, 0x5502F25Du, 0x82542A38u, 0x59F741E0u,  \
  0x8BA79B98u, 0x6E1D3B62u, 0xF320AD74u, 0x8EB1C71Eu, 0xBE8B0537u, 0xAA87CA22u

#define MCUXCLECC_CURVE_P384_BASEPOINT_Y  \
  0x90EA0E5Fu, 0x7A431D7Cu, 0x1D7E819Du, 0x0A60B1CEu, 0xB5F0B8C0u, 0xE9DA3113u,  \
  0x289A147Cu, 0xF8F41DBDu, 0x9292DC29u, 0x5D9E98BFu, 0x96262C6Fu, 0x3617DE4Au

#define MCUXCLECC_CURVE_P384_ORDER_N_LO192  \
  0xCCC52973u, 0xECEC196Au, 0x48B0A77Au, 0x581A0DB2u, 0xF4372DDFu, 0xC7634D81u
#define MCUXCLECC_CURVE_P384_ORDER_N_HI192  \
  0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu
#define MCUXCLECC_CURVE_P384_ORDER_N  \
  MCUXCLECC_CURVE_P384_ORDER_N_LO192, MCUXCLECC_CURVE_P384_ORDER_N_HI192

#define MCUXCLECC_CURVE_P384_ORDER_N_BYTELEN  48u
#define MCUXCLECC_CURVE_P384_ORDER_N_LOWHALF_BYTELEN  24u

#define MCUXCLECC_CURVE_P384_ORDER_N_NDASH  \
  0xE88FDC45u, 0x6ED46089u

#define MCUXCLECC_CURVE_P384_PRECBP_X  \
  0xAA03BD53u, 0xA628B09Au, 0xA4F52D78u, 0xBA065458u, 0x4D10DDEAu, 0xDB298789u,  \
  0x8A3E297Du, 0xB42A31AFu, 0x06421279u, 0x40F7F9E7u, 0x800119C4u, 0xC19E0B4Cu

#define MCUXCLECC_CURVE_P384_PRECBP_Y  \
  0xE6C88C41u, 0x822D0FC5u, 0xE639D858u, 0xAF68AA6Du, 0x35F6EBF2u, 0xC1C7CAD1u,  \
  0xE3567AF9u, 0x577A30EAu, 0x1F5B77F6u, 0xE5A0191Du, 0x0356B301u, 0x16F3FDBFu

#endif
