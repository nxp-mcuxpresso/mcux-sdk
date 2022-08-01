/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef ISL29023_H_
#define ISL29023_H_

/**
 **
 **  ISL29023 Ambient Light Sensor Internal Registers
 */
enum {
	ISL29023_CMD_I                  = 0x00,
	ISL29023_CMD_II                 = 0x01,
	ISL29023_DATA_LSB               = 0x02,
	ISL29023_DATA_MSB               = 0x03,
	ISL29023_INT_LT_LSB             = 0x04,
	ISL29023_INT_LT_MSB             = 0x05,
	ISL29023_INT_HT_LSB             = 0x06,
	ISL29023_INT_HT_MSB             = 0x07,
	ISL29023_TEST                   = 0x08,
};

#define ISL29023_I2C_ADDRESS     (0x44)  /*ISL29023 I2C Address */
#define ISL29023_I2C_TEST_VALUE  (0x00)  /*ISL29023 test register value */

/*--------------------------------
** Register: COMMAND-I
** Enum: ISL29023_CMD_I
** --
** Offset : 0x00 - Control & Status bits
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   prst: 2; /*  IRQ persist bits.              */

        uint8_t                   flag: 1; /*  IRQ flag bit.                  */

        uint8_t _reserved_            : 2;
        uint8_t                   op  : 3; /*  Operation mode bits.           */

    } b;
    uint8_t w;
} ISL29023_CMD_I_t;


/*
** COMMAND-I - Bit field mask definitions 
*/
#define ISL29023_CMD_I_PRST_MASK    ((uint8_t) 0x03)
#define ISL29023_CMD_I_PRST_SHIFT   ((uint8_t)    0)

#define ISL29023_CMD_I_FLAG_MASK    ((uint8_t) 0x04)
#define ISL29023_CMD_I_FLAG_SHIFT   ((uint8_t)    2)

#define ISL29023_CMD_I_OP_MASK      ((uint8_t) 0xe0)
#define ISL29023_CMD_I_OP_SHIFT     ((uint8_t)    5)


/*
** COMMAND-I - Bit field value definitions  
*/
#define ISL29023_CMD_I_PRST_1              ((uint8_t) 0x00)  /*  Number of Integration Samples = 1 */
#define ISL29023_CMD_I_PRST_4              ((uint8_t) 0x01)  /*  Number of Integration Samples = 4 */
#define ISL29023_CMD_I_PRST_8              ((uint8_t) 0x02)  /*  Number of Integration Samples = 8 */
#define ISL29023_CMD_I_PRST_16             ((uint8_t) 0x03)  /*  Number of Integration Samples = 16 */
#define ISL29023_CMD_I_FLAG_CLEARED        ((uint8_t) 0x00)  /*  IRQ flag is cleared or not triggered yet */
#define ISL29023_CMD_I_FLAG_TRIGGERED      ((uint8_t) 0x04)  /*  IRQ flag is triggered */
#define ISL29023_CMD_I_OP_POWER_DOWN       ((uint8_t) 0x00)  /*  Power-down the device (default) */
#define ISL29023_CMD_I_OP_ALS_ONCE         ((uint8_t) 0x20)  /*  IC measures ALS only once */
#define ISL29023_CMD_I_OP_IR_ONCE          ((uint8_t) 0x40)  /*  IC meausres IR only once */
#define ISL29023_CMD_I_OP_ALS_CONT         ((uint8_t) 0xA0)  /*  IC meausres ALS continuously */
#define ISL29023_CMD_I_OP_IR_CONT          ((uint8_t) 0xC0)  /*  IC meausres IR continuous */

/*------------------------------*/



/*--------------------------------
** Register: COMMAND-II
** Enum: ISL29023_CMD_II
** --
** Offset : 0x01 - Control bits
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   range: 2; /*  Full scale range bits         */

        uint8_t                   res  : 2; /*  ADC resolution bits           */

        uint8_t _reserved_             : 4;

    } b;
    uint8_t w;
} ISL29023_CMD_II_t;


/*
** COMMAND-II - Bit field mask definitions 
*/
#define ISL29023_CMD_II_RANGE_MASK    ((uint8_t) 0x03)
#define ISL29023_CMD_II_RANGE_SHIFT   ((uint8_t)    0)

#define ISL29023_CMD_II_RES_MASK      ((uint8_t) 0x0C)
#define ISL29023_CMD_II_RES_SHIFT     ((uint8_t)    2)


/*
** COMMAND-II - Bit field value definitions  
*/
#define ISL29023_CMD_II_RANGE_1              ((uint8_t) 0x00)  /*  FSR @ALS Sensing = 1.000 */
#define ISL29023_CMD_II_RANGE_2              ((uint8_t) 0x01)  /*  FSR @ALS Sensing = 4.000 */
#define ISL29023_CMD_II_RANGE_3              ((uint8_t) 0x02)  /*  FSR @ALS Sensing = 16.000 */
#define ISL29023_CMD_II_RANGE_4              ((uint8_t) 0x03)  /*  FSR @ALS Sensing = 64.000 */
#define ISL29023_CMD_II_RES_16               ((uint8_t) 0x00)  /*  2^16 ADC resolution */
#define ISL29023_CMD_II_RES_12               ((uint8_t) 0x04)  /*  2^12 ADC resolution */
#define ISL29023_CMD_II_RES_8                ((uint8_t) 0x08)  /*  2^8 ADC resolution */
#define ISL29023_CMD_II_RES_4                ((uint8_t) 0x0C)  /*  2^4 ADC resolution */

/*------------------------------*/


/*--------------------------------
** Register: DATA_LSB 
** Enum: ISL29023_DATA_LSB 
** --
** Offset : 0x02 - Bits 7-0 of the 16-bit data register.
** ------------------------------*/
typedef uint8_t ISL29023_DATA_LSB_t;


/*--------------------------------
** Register: DATA_MSB 
** Enum: ISL29023_DATA_MSB 
** --
** Offset : 0x03 - Bits 15-8 of the 16-bit data register.
** ------------------------------*/
typedef uint8_t ISL29023_DATA_MSB_t;


/*--------------------------------
** Register: INT_LT_LSB 
** Enum: ISL29023_INT_LT_LSB 
** --
** Offset : 0x04 - Bits 7-0 of the 16-bit lower IRQ treshold register.
** ------------------------------*/
typedef uint8_t ISL29023_INT_LT_LSB_t;


/*--------------------------------
** Register: INT_LT_MSB 
** Enum: ISL29023_INT_LT_MSB 
** --
** Offset : 0x05 - Bits 15-8 of the 16-bit lower IRQ treshold register.
** ------------------------------*/
typedef uint8_t ISL29023_INT_LT_MSB_t;


/*--------------------------------
** Register: INT_HT_LSB 
** Enum: ISL29023_INT_HT_LSB 
** --
** Offset : 0x06 - Bits 7-0 of the 16-bit upper IRQ treshold register.
** ------------------------------*/
typedef uint8_t ISL29023_INT_HT_LSB_t;


/*--------------------------------
** Register: INT_HT_MSB 
** Enum: ISL29023_INT_HT_MSB 
** --
** Offset : 0x07 - Bits 15-8 of the 16-bit upper IRQ treshold register.
** ------------------------------*/
typedef uint8_t ISL29023_INT_HT_MSB_t;


/*--------------------------------
** Register: TEST 
** Enum: ISL29023_TEST 
** --
** Offset : 0x08 - Test register (hold 00h during normal operation).
** ------------------------------*/
typedef uint8_t ISL29023_TEST_t;

#endif  /* ISL29023_H_ */ 
