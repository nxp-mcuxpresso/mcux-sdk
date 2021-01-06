/*
 * Copyright 2019-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Change log:
 *
 * 1.0.1:
 *   - Fix MISRA 2012 issues.
 *
 * 1.0.0:
 *   - Initial version.
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
#ifndef _GDH_1247WP_H_
#define _GDH_1247WP_H_

#include <stdint.h>

#define SLCD_PIN_NUM       20 /* pin number */
#define SLCD_BACKPLANE_NUM 8  /* backplane number */
#define SLCD_FIELD_NUM     (LCD_PIN_NUM * LCD_BACKPLANE_NUM)

typedef enum
{
    NUM_POS1 = 0,
    NUM_POS2,
    NUM_POS3,
    NUM_POS4,
    NUM_POS5,
    NUM_POS6,
    NUM_POS7,
    NUM_POS8,
    NUM_POS9,
    NUM_POS10,
    NUM_POS11,
    NUM_POS12,
    NUM_POS13,
    NUM_POS14,
    NUM_POS15,
    NUM_POSEND
} tSLCD_Segment_Num;

typedef enum
{
    /* Number part 1 */
    ICON_1A = 0,
    ICON_1B,
    ICON_1C,
    ICON_1D,
    ICON_1E,
    ICON_1F,
    ICON_1G,

    /* Number part 2 */
    ICON_2A,
    ICON_2B,
    ICON_2C,
    ICON_2D,
    ICON_2E,
    ICON_2F,
    ICON_2G,

    /* Number part 3 */
    ICON_3A,
    ICON_3B,
    ICON_3C,
    ICON_3D,
    ICON_3E,
    ICON_3F,
    ICON_3G,

    /* Number part 4 */
    ICON_4A,
    ICON_4B,
    ICON_4C,
    ICON_4D,
    ICON_4E,
    ICON_4F,
    ICON_4G,

    /* Number part 5 */
    ICON_5A,
    ICON_5B,
    ICON_5C,
    ICON_5D,
    ICON_5E,
    ICON_5F,
    ICON_5G,

    /* Number part 6 */
    ICON_6A,
    ICON_6B,
    ICON_6C,
    ICON_6D,
    ICON_6E,
    ICON_6F,
    ICON_6G,

    /* Number part 7 */
    ICON_7A,
    ICON_7B,
    ICON_7C,
    ICON_7D,
    ICON_7E,
    ICON_7F,
    ICON_7G,

    /* Number part 8 */
    ICON_8A,
    ICON_8B,
    ICON_8C,
    ICON_8D,
    ICON_8E,
    ICON_8F,
    ICON_8G,

    /* Number part 9 */
    ICON_9A,
    ICON_9B,
    ICON_9C,
    ICON_9D,
    ICON_9E,
    ICON_9F,
    ICON_9G,

    /* Number part 10 */
    ICON_10A,
    ICON_10B,
    ICON_10C,
    ICON_10D,
    ICON_10E,
    ICON_10F,
    ICON_10G,

    /* Number part 11 */
    ICON_11A,
    ICON_11B,
    ICON_11C,
    ICON_11D,
    ICON_11E,
    ICON_11F,
    ICON_11G,

    /* Number part 12 */
    ICON_12A,
    ICON_12B,
    ICON_12C,
    ICON_12D,
    ICON_12E,
    ICON_12F,
    ICON_12G,

    /* Number part 13 */
    ICON_13A,
    ICON_13B,
    ICON_13C,
    ICON_13D,
    ICON_13E,
    ICON_13F,
    ICON_13G,

    /* Number part 14 */
    ICON_14A,
    ICON_14B,
    ICON_14C,
    ICON_14D,
    ICON_14E,
    ICON_14F,
    ICON_14G,

    /* Number part 15 */
    ICON_15A,
    ICON_15B,
    ICON_15C,
    ICON_15D,
    ICON_15E,
    ICON_15F,
    ICON_15G,

    /* icon part */
    ICON_L1,
    ICON_L2,
    ICON_L3,
    ICON_T1,
    ICON_T2,
    ICON_T3,
    ICON_T4,
    ICON_RMS,
    ICON_P1,
    ICON_P2,
    ICON_P3,
    ICON_P4,
    ICON_P5,
    ICON_P6,
    ICON_P7,

    ICON_S1,
    ICON_S2,
    ICON_S3,
    ICON_S4,
    ICON_S5,
    ICON_S6,
    ICON_S7,
    ICON_S8,
    ICON_S9,
    ICON_S10,
    ICON_S11,
    ICON_S12,
    ICON_S13,
    ICON_S14,
    ICON_S15,
    ICON_S16,
    ICON_S17,
    ICON_S18,
    ICON_S19,
    ICON_S20,
    ICON_S21,
    ICON_S22,
    ICON_S23,
    ICON_S24,
    ICON_S25,
    ICON_S26,
    ICON_S27,
    ICON_S28,
    ICON_S29,
    ICON_S30,
    ICON_S31,
    ICON_S32,
    ICON_S33,
    ICON_S34,
    ICON_S35,
    ICON_S36,
    ICON_S37,
    ICON_S38,
    ICON_S39,
    ICON_S40,
    ICON_END
} tSLCD_Segment_Icon;

extern const uint16_t SLCD_Icon[];
extern const uint16_t **SLCD_NumPos[];

#endif /* _GDH_1247WP_H_ */
