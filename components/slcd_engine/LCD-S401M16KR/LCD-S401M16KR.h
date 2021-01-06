/*
 * Copyright 2019-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _LCD_S401M16KR_H_
#define _LCD_S401M16KR_H_

#include <stdint.h>

/*
 * Change log:
 *
 * 1.0.2:
 *   - Fix MISRA 2012 issues.
 *
 * 1.0.1:
 *   - Add macro SLCD_ENGINE_PIN_VAL.
 *
 * 1.0.0:
 *   - Initial version.
 */

#define SLCD_PIN_NUM                  8 /* pin number */
#define SLCD_BACKPLANE_NUM            4 /* backplane number */
#define SLCD_FIELD_NUM                (LCD_PIN_NUM * LCD_BACKPLANE_NUM)
#define SLCD_ENGINE_PIN_VAL(pin, val) (((pin) << 8U) | ((val) << 0U))

typedef enum
{
    NUM_POS1 = 0,
    NUM_POS2,
    NUM_POS3,
    NUM_POS4,
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

    /* icon part */
    ICON_DP1,
    ICON_DP2,
    ICON_DP3,
    ICON_COL,
    ICON_END
} tSLCD_Segment_Icon;

extern const uint16_t SLCD_Icon[];
extern const uint16_t **SLCD_NumPos[];

#endif /* _LCD_S401M16KR_H_ */
