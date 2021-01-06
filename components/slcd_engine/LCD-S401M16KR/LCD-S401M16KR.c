/*
 * Copyright 2019-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "LCD-S401M16KR.h"

#define __SLCD_1D_COM  (1U << 0U)
#define __SLCD_1E_COM  (1U << 1U)
#define __SLCD_1G_COM  (1U << 2U)
#define __SLCD_1F_COM  (1U << 3U)
#define __SLCD_DP1_COM (1U << 0U)
#define __SLCD_1C_COM  (1U << 1U)
#define __SLCD_1B_COM  (1U << 2U)
#define __SLCD_1A_COM  (1U << 3U)
#define __SLCD_2D_COM  (1U << 0U)
#define __SLCD_2E_COM  (1U << 1U)
#define __SLCD_2G_COM  (1U << 2U)
#define __SLCD_2F_COM  (1U << 3U)
#define __SLCD_DP2_COM (1U << 0U)
#define __SLCD_2C_COM  (1U << 1U)
#define __SLCD_2B_COM  (1U << 2U)
#define __SLCD_2A_COM  (1U << 3U)
#define __SLCD_3D_COM  (1U << 0U)
#define __SLCD_3E_COM  (1U << 1U)
#define __SLCD_3G_COM  (1U << 2U)
#define __SLCD_3F_COM  (1U << 3U)
#define __SLCD_DP3_COM (1U << 0U)
#define __SLCD_3C_COM  (1U << 1U)
#define __SLCD_3B_COM  (1U << 2U)
#define __SLCD_3A_COM  (1U << 3U)
#define __SLCD_4D_COM  (1U << 0U)
#define __SLCD_4E_COM  (1U << 1U)
#define __SLCD_4G_COM  (1U << 2U)
#define __SLCD_4F_COM  (1U << 3U)
#define __SLCD_COL_COM (1U << 0U)
#define __SLCD_4C_COM  (1U << 1U)
#define __SLCD_4B_COM  (1U << 2U)
#define __SLCD_4A_COM  (1U << 3U)

#define __SLCD_PIN5  1U
#define __SLCD_PIN6  2U
#define __SLCD_PIN7  3U
#define __SLCD_PIN8  4U
#define __SLCD_PIN9  5U
#define __SLCD_PIN10 6U
#define __SLCD_PIN11 7U
#define __SLCD_PIN12 8U

static const uint16_t SLCD_NumPos1_Num0[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1E_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num1[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num2[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1E_COM | __SLCD_1G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num3[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num4[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1G_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num5[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1G_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num6[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1E_COM | __SLCD_1G_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num7[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num8[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1E_COM | __SLCD_1G_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos1_Num9[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM | __SLCD_1G_COM | __SLCD_1F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM | __SLCD_1B_COM | __SLCD_1A_COM),
    0x0,
};

static const uint16_t *SLCD_NumPos1[] = {

    SLCD_NumPos1_Num0, SLCD_NumPos1_Num1, SLCD_NumPos1_Num2, SLCD_NumPos1_Num3, SLCD_NumPos1_Num4,
    SLCD_NumPos1_Num5, SLCD_NumPos1_Num6, SLCD_NumPos1_Num7, SLCD_NumPos1_Num8, SLCD_NumPos1_Num9,
};

static const uint16_t SLCD_NumPos2_Num0[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2E_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num1[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num2[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2E_COM | __SLCD_2G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num3[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num4[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2G_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num5[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2G_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num6[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2E_COM | __SLCD_2G_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num7[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num8[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2E_COM | __SLCD_2G_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos2_Num9[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM | __SLCD_2G_COM | __SLCD_2F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM | __SLCD_2B_COM | __SLCD_2A_COM),
    0x0,
};

static const uint16_t *SLCD_NumPos2[] = {

    SLCD_NumPos2_Num0, SLCD_NumPos2_Num1, SLCD_NumPos2_Num2, SLCD_NumPos2_Num3, SLCD_NumPos2_Num4,
    SLCD_NumPos2_Num5, SLCD_NumPos2_Num6, SLCD_NumPos2_Num7, SLCD_NumPos2_Num8, SLCD_NumPos2_Num9,
};

static const uint16_t SLCD_NumPos3_Num0[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3E_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num1[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num2[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3E_COM | __SLCD_3G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num3[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num4[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3G_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num5[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3G_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num6[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3E_COM | __SLCD_3G_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num7[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num8[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3E_COM | __SLCD_3G_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos3_Num9[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM | __SLCD_3G_COM | __SLCD_3F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM | __SLCD_3B_COM | __SLCD_3A_COM),
    0x0,
};

static const uint16_t *SLCD_NumPos3[] = {

    SLCD_NumPos3_Num0, SLCD_NumPos3_Num1, SLCD_NumPos3_Num2, SLCD_NumPos3_Num3, SLCD_NumPos3_Num4,
    SLCD_NumPos3_Num5, SLCD_NumPos3_Num6, SLCD_NumPos3_Num7, SLCD_NumPos3_Num8, SLCD_NumPos3_Num9,
};

static const uint16_t SLCD_NumPos4_Num0[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4E_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num1[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num2[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4E_COM | __SLCD_4G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num3[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4G_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num4[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4G_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num5[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4G_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num6[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4E_COM | __SLCD_4G_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num7[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, 0U),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num8[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4E_COM | __SLCD_4G_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t SLCD_NumPos4_Num9[] = {
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM | __SLCD_4G_COM | __SLCD_4F_COM),
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM | __SLCD_4B_COM | __SLCD_4A_COM),
    0x0,
};

static const uint16_t *SLCD_NumPos4[] = {

    SLCD_NumPos4_Num0, SLCD_NumPos4_Num1, SLCD_NumPos4_Num2, SLCD_NumPos4_Num3, SLCD_NumPos4_Num4,
    SLCD_NumPos4_Num5, SLCD_NumPos4_Num6, SLCD_NumPos4_Num7, SLCD_NumPos4_Num8, SLCD_NumPos4_Num9,
};

const uint16_t **SLCD_NumPos[] = {SLCD_NumPos1, SLCD_NumPos2, SLCD_NumPos3, SLCD_NumPos4};

const uint16_t SLCD_Icon[] = {
    /* Number part 1*/
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1A_COM), /* A */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1B_COM), /* B */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_1C_COM), /* C */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1D_COM), /* D */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1E_COM), /* E */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1F_COM), /* F */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN5, __SLCD_1G_COM), /* G */

    /* Number part 2*/
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2A_COM), /* A */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2B_COM), /* B */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_2C_COM), /* C */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2D_COM), /* D */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2E_COM), /* E */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2F_COM), /* F */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN7, __SLCD_2G_COM), /* G */

    /* Number part 3*/
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3A_COM), /* A */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3B_COM), /* B */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_3C_COM), /* C */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3D_COM),  /* D */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3E_COM),  /* E */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3F_COM),  /* F */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN9, __SLCD_3G_COM),  /* G */

    /* Number part 4*/
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4A_COM), /* A */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4B_COM), /* B */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_4C_COM), /* C */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4D_COM), /* D */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4E_COM), /* E */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4F_COM), /* F */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN11, __SLCD_4G_COM), /* G */

    SLCD_ENGINE_PIN_VAL(__SLCD_PIN6, __SLCD_DP1_COM),  /* index 4, DP1 */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN8, __SLCD_DP2_COM),  /* index 5, DP2 */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN10, __SLCD_DP3_COM), /* index 6, DP3 */
    SLCD_ENGINE_PIN_VAL(__SLCD_PIN12, __SLCD_COL_COM), /* index 7, COL */
};
