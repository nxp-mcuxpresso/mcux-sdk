/*
 * Copyright 2019-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 printed number only for pin map

 id01: xx 14D 14E 14C 14G 14F 14B 14A
 id02: xx 13D 13E 13C 13G 13F 13B 13A
 id03: xx 12D 12E 12C 12G 12F 12B 12A
 id04: xx 11D 11E 11C 11G 11F 11B 11A
 id05: xx 10D 10E 10C 10G 10F 10B 10A
 id06: 15D 15E 15C 15G 15F 15B 15A xx
 id07: xx xx xx xx xx xx xx xx
 id08: xx xx xx xx xx xx xx xx
 id09: xx xx xx xx xx xx xx xx
 id10: xx 1A 1F 1B 1G 1E 1C 1D
 id11: xx 2A 2F 2B 2G 2E 2C 2D
 id12: xx 3A 3F 3B 3G 3E 3C 3D
 id13: xx 4A 4F 4B 4G 4E 4C 4D
 id14: xx 5A 5F 5B 5G 5E 5C 5D
 id15: xx 6A 6F 6B 6G 6E 6C 6D
 id16: xx 7A 7F 7B 7G 7E 7C 7D
 id17: xx 8A 8F 8B 8G 8E 8C 8D
 id18: xx 9A 9F 9B 9G 9E 9C 9D
 id19: xx xx xx xx xx xx xx xx
 id20: xx xx xx xx xx xx xx xx
*/
#include <stdint.h>
#include "GDH-1247WP.h"

static const uint16_t SLCD_NumPos1_Num0[] = {
    0xaee,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num1[] = {
    0xa48,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num2[] = {
    0xaba,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num3[] = {
    0xada,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num4[] = {
    0xa5c,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num5[] = {
    0xad6,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num6[] = {
    0xaf6,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num7[] = {
    0xa4a,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num8[] = {
    0xafe,
    0x0,
};

static const uint16_t SLCD_NumPos1_Num9[] = {
    0xade,
    0x0,
};

static const uint16_t *SLCD_NumPos1[] = {

    SLCD_NumPos1_Num0, SLCD_NumPos1_Num1, SLCD_NumPos1_Num2, SLCD_NumPos1_Num3, SLCD_NumPos1_Num4,
    SLCD_NumPos1_Num5, SLCD_NumPos1_Num6, SLCD_NumPos1_Num7, SLCD_NumPos1_Num8, SLCD_NumPos1_Num9,
};

static const uint16_t SLCD_NumPos2_Num0[] = {
    0xbee,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num1[] = {
    0xb48,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num2[] = {
    0xbba,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num3[] = {
    0xbda,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num4[] = {
    0xb5c,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num5[] = {
    0xbd6,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num6[] = {
    0xbf6,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num7[] = {
    0xb4a,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num8[] = {
    0xbfe,
    0x0,
};

static const uint16_t SLCD_NumPos2_Num9[] = {
    0xbde,
    0x0,
};

static const uint16_t *SLCD_NumPos2[] = {

    SLCD_NumPos2_Num0, SLCD_NumPos2_Num1, SLCD_NumPos2_Num2, SLCD_NumPos2_Num3, SLCD_NumPos2_Num4,
    SLCD_NumPos2_Num5, SLCD_NumPos2_Num6, SLCD_NumPos2_Num7, SLCD_NumPos2_Num8, SLCD_NumPos2_Num9,
};

static const uint16_t SLCD_NumPos3_Num0[] = {
    0xcee,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num1[] = {
    0xc48,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num2[] = {
    0xcba,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num3[] = {
    0xcda,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num4[] = {
    0xc5c,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num5[] = {
    0xcd6,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num6[] = {
    0xcf6,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num7[] = {
    0xc4a,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num8[] = {
    0xcfe,
    0x0,
};

static const uint16_t SLCD_NumPos3_Num9[] = {
    0xcde,
    0x0,
};

static const uint16_t *SLCD_NumPos3[] = {

    SLCD_NumPos3_Num0, SLCD_NumPos3_Num1, SLCD_NumPos3_Num2, SLCD_NumPos3_Num3, SLCD_NumPos3_Num4,
    SLCD_NumPos3_Num5, SLCD_NumPos3_Num6, SLCD_NumPos3_Num7, SLCD_NumPos3_Num8, SLCD_NumPos3_Num9,
};

static const uint16_t SLCD_NumPos4_Num0[] = {
    0xdee,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num1[] = {
    0xd48,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num2[] = {
    0xdba,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num3[] = {
    0xdda,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num4[] = {
    0xd5c,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num5[] = {
    0xdd6,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num6[] = {
    0xdf6,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num7[] = {
    0xd4a,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num8[] = {
    0xdfe,
    0x0,
};

static const uint16_t SLCD_NumPos4_Num9[] = {
    0xdde,
    0x0,
};

static const uint16_t *SLCD_NumPos4[] = {

    SLCD_NumPos4_Num0, SLCD_NumPos4_Num1, SLCD_NumPos4_Num2, SLCD_NumPos4_Num3, SLCD_NumPos4_Num4,
    SLCD_NumPos4_Num5, SLCD_NumPos4_Num6, SLCD_NumPos4_Num7, SLCD_NumPos4_Num8, SLCD_NumPos4_Num9,
};

static const uint16_t SLCD_NumPos5_Num0[] = {
    0xeee,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num1[] = {
    0xe48,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num2[] = {
    0xeba,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num3[] = {
    0xeda,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num4[] = {
    0xe5c,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num5[] = {
    0xed6,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num6[] = {
    0xef6,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num7[] = {
    0xe4a,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num8[] = {
    0xefe,
    0x0,
};

static const uint16_t SLCD_NumPos5_Num9[] = {
    0xede,
    0x0,
};

static const uint16_t *SLCD_NumPos5[] = {

    SLCD_NumPos5_Num0, SLCD_NumPos5_Num1, SLCD_NumPos5_Num2, SLCD_NumPos5_Num3, SLCD_NumPos5_Num4,
    SLCD_NumPos5_Num5, SLCD_NumPos5_Num6, SLCD_NumPos5_Num7, SLCD_NumPos5_Num8, SLCD_NumPos5_Num9,
};

static const uint16_t SLCD_NumPos6_Num0[] = {
    0xfee,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num1[] = {
    0xf48,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num2[] = {
    0xfba,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num3[] = {
    0xfda,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num4[] = {
    0xf5c,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num5[] = {
    0xfd6,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num6[] = {
    0xff6,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num7[] = {
    0xf4a,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num8[] = {
    0xffe,
    0x0,
};

static const uint16_t SLCD_NumPos6_Num9[] = {
    0xfde,
    0x0,
};

static const uint16_t *SLCD_NumPos6[] = {

    SLCD_NumPos6_Num0, SLCD_NumPos6_Num1, SLCD_NumPos6_Num2, SLCD_NumPos6_Num3, SLCD_NumPos6_Num4,
    SLCD_NumPos6_Num5, SLCD_NumPos6_Num6, SLCD_NumPos6_Num7, SLCD_NumPos6_Num8, SLCD_NumPos6_Num9,
};

static const uint16_t SLCD_NumPos7_Num0[] = {
    0x10ee,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num1[] = {
    0x1048,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num2[] = {
    0x10ba,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num3[] = {
    0x10da,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num4[] = {
    0x105c,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num5[] = {
    0x10d6,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num6[] = {
    0x10f6,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num7[] = {
    0x104a,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num8[] = {
    0x10fe,
    0x0,
};

static const uint16_t SLCD_NumPos7_Num9[] = {
    0x10de,
    0x0,
};

static const uint16_t *SLCD_NumPos7[] = {

    SLCD_NumPos7_Num0, SLCD_NumPos7_Num1, SLCD_NumPos7_Num2, SLCD_NumPos7_Num3, SLCD_NumPos7_Num4,
    SLCD_NumPos7_Num5, SLCD_NumPos7_Num6, SLCD_NumPos7_Num7, SLCD_NumPos7_Num8, SLCD_NumPos7_Num9,
};

static const uint16_t SLCD_NumPos8_Num0[] = {
    0x11ee,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num1[] = {
    0x1148,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num2[] = {
    0x11ba,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num3[] = {
    0x11da,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num4[] = {
    0x115c,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num5[] = {
    0x11d6,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num6[] = {
    0x11f6,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num7[] = {
    0x114a,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num8[] = {
    0x11fe,
    0x0,
};

static const uint16_t SLCD_NumPos8_Num9[] = {
    0x11de,
    0x0,
};

static const uint16_t *SLCD_NumPos8[] = {

    SLCD_NumPos8_Num0, SLCD_NumPos8_Num1, SLCD_NumPos8_Num2, SLCD_NumPos8_Num3, SLCD_NumPos8_Num4,
    SLCD_NumPos8_Num5, SLCD_NumPos8_Num6, SLCD_NumPos8_Num7, SLCD_NumPos8_Num8, SLCD_NumPos8_Num9,
};

static const uint16_t SLCD_NumPos9_Num0[] = {
    0x12ee,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num1[] = {
    0x1248,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num2[] = {
    0x12ba,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num3[] = {
    0x12da,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num4[] = {
    0x125c,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num5[] = {
    0x12d6,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num6[] = {
    0x12f6,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num7[] = {
    0x124a,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num8[] = {
    0x12fe,
    0x0,
};

static const uint16_t SLCD_NumPos9_Num9[] = {
    0x12de,
    0x0,
};

static const uint16_t *SLCD_NumPos9[] = {

    SLCD_NumPos9_Num0, SLCD_NumPos9_Num1, SLCD_NumPos9_Num2, SLCD_NumPos9_Num3, SLCD_NumPos9_Num4,
    SLCD_NumPos9_Num5, SLCD_NumPos9_Num6, SLCD_NumPos9_Num7, SLCD_NumPos9_Num8, SLCD_NumPos9_Num9,
};

static const uint16_t SLCD_NumPos10_Num0[] = {
    0x5ee,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num1[] = {
    0x548,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num2[] = {
    0x5d6,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num3[] = {
    0x5da,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num4[] = {
    0x578,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num5[] = {
    0x5ba,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num6[] = {
    0x5be,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num7[] = {
    0x5c8,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num8[] = {
    0x5fe,
    0x0,
};

static const uint16_t SLCD_NumPos10_Num9[] = {
    0x5fa,
    0x0,
};

static const uint16_t *SLCD_NumPos10[] = {

    SLCD_NumPos10_Num0, SLCD_NumPos10_Num1, SLCD_NumPos10_Num2, SLCD_NumPos10_Num3, SLCD_NumPos10_Num4,
    SLCD_NumPos10_Num5, SLCD_NumPos10_Num6, SLCD_NumPos10_Num7, SLCD_NumPos10_Num8, SLCD_NumPos10_Num9,
};

static const uint16_t SLCD_NumPos11_Num0[] = {
    0x4ee,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num1[] = {
    0x448,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num2[] = {
    0x4d6,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num3[] = {
    0x4da,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num4[] = {
    0x478,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num5[] = {
    0x4ba,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num6[] = {
    0x4be,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num7[] = {
    0x4c8,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num8[] = {
    0x4fe,
    0x0,
};

static const uint16_t SLCD_NumPos11_Num9[] = {
    0x4fa,
    0x0,
};

static const uint16_t *SLCD_NumPos11[] = {

    SLCD_NumPos11_Num0, SLCD_NumPos11_Num1, SLCD_NumPos11_Num2, SLCD_NumPos11_Num3, SLCD_NumPos11_Num4,
    SLCD_NumPos11_Num5, SLCD_NumPos11_Num6, SLCD_NumPos11_Num7, SLCD_NumPos11_Num8, SLCD_NumPos11_Num9,
};

static const uint16_t SLCD_NumPos12_Num0[] = {
    0x3ee,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num1[] = {
    0x348,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num2[] = {
    0x3d6,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num3[] = {
    0x3da,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num4[] = {
    0x378,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num5[] = {
    0x3ba,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num6[] = {
    0x3be,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num7[] = {
    0x3c8,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num8[] = {
    0x3fe,
    0x0,
};

static const uint16_t SLCD_NumPos12_Num9[] = {
    0x3fa,
    0x0,
};

static const uint16_t *SLCD_NumPos12[] = {

    SLCD_NumPos12_Num0, SLCD_NumPos12_Num1, SLCD_NumPos12_Num2, SLCD_NumPos12_Num3, SLCD_NumPos12_Num4,
    SLCD_NumPos12_Num5, SLCD_NumPos12_Num6, SLCD_NumPos12_Num7, SLCD_NumPos12_Num8, SLCD_NumPos12_Num9,
};

static const uint16_t SLCD_NumPos13_Num0[] = {
    0x2ee,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num1[] = {
    0x248,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num2[] = {
    0x2d6,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num3[] = {
    0x2da,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num4[] = {
    0x278,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num5[] = {
    0x2ba,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num6[] = {
    0x2be,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num7[] = {
    0x2c8,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num8[] = {
    0x2fe,
    0x0,
};

static const uint16_t SLCD_NumPos13_Num9[] = {
    0x2fa,
    0x0,
};

static const uint16_t *SLCD_NumPos13[] = {

    SLCD_NumPos13_Num0, SLCD_NumPos13_Num1, SLCD_NumPos13_Num2, SLCD_NumPos13_Num3, SLCD_NumPos13_Num4,
    SLCD_NumPos13_Num5, SLCD_NumPos13_Num6, SLCD_NumPos13_Num7, SLCD_NumPos13_Num8, SLCD_NumPos13_Num9,
};

static const uint16_t SLCD_NumPos14_Num0[] = {
    0x1ee,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num1[] = {
    0x148,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num2[] = {
    0x1d6,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num3[] = {
    0x1da,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num4[] = {
    0x178,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num5[] = {
    0x1ba,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num6[] = {
    0x1be,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num7[] = {
    0x1c8,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num8[] = {
    0x1fe,
    0x0,
};

static const uint16_t SLCD_NumPos14_Num9[] = {
    0x1fa,
    0x0,
};

static const uint16_t *SLCD_NumPos14[] = {

    SLCD_NumPos14_Num0, SLCD_NumPos14_Num1, SLCD_NumPos14_Num2, SLCD_NumPos14_Num3, SLCD_NumPos14_Num4,
    SLCD_NumPos14_Num5, SLCD_NumPos14_Num6, SLCD_NumPos14_Num7, SLCD_NumPos14_Num8, SLCD_NumPos14_Num9,
};

static const uint16_t SLCD_NumPos15_Num0[] = {
    0x677,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num1[] = {
    0x624,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num2[] = {
    0x66b,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num3[] = {
    0x66d,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num4[] = {
    0x63c,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num5[] = {
    0x65d,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num6[] = {
    0x65f,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num7[] = {
    0x664,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num8[] = {
    0x67f,
    0x0,
};

static const uint16_t SLCD_NumPos15_Num9[] = {
    0x67d,
    0x0,
};

static const uint16_t *SLCD_NumPos15[] = {
    SLCD_NumPos15_Num0, SLCD_NumPos15_Num1, SLCD_NumPos15_Num2, SLCD_NumPos15_Num3, SLCD_NumPos15_Num4,
    SLCD_NumPos15_Num5, SLCD_NumPos15_Num6, SLCD_NumPos15_Num7, SLCD_NumPos15_Num8, SLCD_NumPos15_Num9,
};

const uint16_t **SLCD_NumPos[] = {
    SLCD_NumPos1,  SLCD_NumPos2,  SLCD_NumPos3,  SLCD_NumPos4,  SLCD_NumPos5,
    SLCD_NumPos6,  SLCD_NumPos7,  SLCD_NumPos8,  SLCD_NumPos9,  SLCD_NumPos10,
    SLCD_NumPos11, SLCD_NumPos12, SLCD_NumPos13, SLCD_NumPos14, SLCD_NumPos15,
};

const uint16_t SLCD_Icon[] = {
    /* Number part 1*/
    0xa02, 0xa08, 0xa40, 0xa80, 0xa20, 0xa04, 0xa10,

    /* Number part 2*/
    0xb02, 0xb08, 0xb40, 0xb80, 0xb20, 0xb04, 0xb10,

    /* Number part 3*/
    0xc02, 0xc08, 0xc40, 0xc80, 0xc20, 0xc04, 0xc10,

    /* Number part 4*/
    0xd02, 0xd08, 0xd40, 0xd80, 0xd20, 0xd04, 0xd10,

    /* Number part 5*/
    0xe02, 0xe08, 0xe40, 0xe80, 0xe20, 0xe04, 0xe10,

    /* Number part 6*/
    0xf02, 0xf08, 0xf40, 0xf80, 0xf20, 0xf04, 0xf10,

    /* Number part 7*/
    0x1002, 0x1008, 0x1040, 0x1080, 0x1020, 0x1004, 0x1010,

    /* Number part 8*/
    0x1102, 0x1108, 0x1140, 0x1180, 0x1120, 0x1104, 0x1110,

    /* Number part 9*/
    0x1202, 0x1208, 0x1240, 0x1280, 0x1220, 0x1204, 0x1210,

    /* Number part 10*/
    0x580, 0x540, 0x508, 0x502, 0x504, 0x520, 0x510,

    /* Number part 11*/
    0x480, 0x440, 0x408, 0x402, 0x404, 0x420, 0x410,

    /* Number part 12*/
    0x380, 0x340, 0x308, 0x302, 0x304, 0x320, 0x310,

    /* Number part 13*/
    0x280, 0x240, 0x208, 0x202, 0x204, 0x220, 0x210,

    /* Number part 14*/
    0x180, 0x140, 0x108, 0x102, 0x104, 0x120, 0x110,

    /* Number part 15*/
    0x640, 0x620, 0x604, 0x601, 0x602, 0x610, 0x608,

    0xe01,  /* index 15, L1 */
    0xf01,  /* index 16, L2 */
    0x1001, /* index 17, L3 */
    0x1404, /* index 18, T1 */
    0x1408, /* index 19, T2 */
    0x1410, /* index 20, T3 */
    0x1420, /* index 21, T4 */
    0x1402, /* index 22, RMS */
    0x1380, /* index 23, P1 */
    0x1340, /* index 24, P2 */
    0x1302, /* index 25, P3 */
    0x401,  /* index 26, P4 */
    0x301,  /* index 27, P5 */
    0x201,  /* index 28, P6 */
    0x101,  /* index 29, P7 */
    0x840,  /* index 30, S1 */
    0x1301, /* index 31, S2 */
    0x801,  /* index 32, S3 */
    0x802,  /* index 33, S4 */
    0x808,  /* index 34, S5 */
    0x820,  /* index 35, S6  */
    0x702,  /* index 36, S7 */
    0x804,  /* index 37, S8 */
    0x810,  /* index 38, S9 */
    0x720,  /* index 39, S10  */
    0x710,  /* index 40, S11 */
    0x704,  /* index 41 , S12 */
    0x708,  /* index 42, S13 */
    0x740,  /* index 43, S14  */
    0x1401, /* index 44, S15 */
    0x908,  /* index 45, S16 */
    0x680,  /* index 46, S17 */
    0x501,  /* index 47, S18 */
    0x780,  /* index 48, S19 */
    0x880,  /* index 49, S20 */
    0x940,  /* index 50, S21 */
    0x920,  /* index 51, S22 */
    0x910,  /* index 52, S23 */
    0x904,  /* index 53, S24 */
    0x902,  /* index 54, S25 */
    0xa01,  /* index 55, S26 */
    0xb01,  /* index 56, S27 */
    0x901,  /* index 57, S28 */
    0x1101, /* index 58, S29 */
    0x1201, /* index 59, S30 */
    0x1304, /* index 60, S31 */
    0x1308, /* index 61 , S32*/
    0x1310, /* index 62, S33 */
    0x1320, /* index 63, S34 */
    0x1480, /* index 64, S35 */
    0xd01,  /* index 65, S36 */
    0x1440, /* index 66, S37 */
    0x980,  /* index 67, S38 */
    0xc01,  /* index 68, S39 */
    0x701   /* index 69, S40 */
};
