/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MPL3115_H_
#define MPL3115_H_

/**
 **
 **  MPL3115 Sensor Internal Registers
 */
enum {
	MPL3115_STATUS                 = 0x00,
	MPL3115_OUT_P_MSB              = 0x01,
	MPL3115_OUT_P_CSB              = 0x02,
	MPL3115_OUT_P_LSB              = 0x03,
	MPL3115_OUT_T_MSB              = 0x04,
	MPL3115_OUT_T_LSB              = 0x05,
	MPL3115_DR_STATUS              = 0x06,
	MPL3115_OUT_P_DELTA_MSB        = 0x07,
	MPL3115_OUT_P_DELTA_CSB        = 0x08,
	MPL3115_OUT_P_DELTA_LSB        = 0x09,
	MPL3115_OUT_T_DELTA_MSB        = 0x0A,
	MPL3115_OUT_T_DELTA_LSB        = 0x0B,
	MPL3115_WHO_AM_I               = 0x0C,
	MPL3115_F_STATUS               = 0x0D,
	MPL3115_F_DATA                 = 0x0E,
	MPL3115_F_SETUP                = 0x0F,
	MPL3115_TIME_DLY               = 0x10,
	MPL3115_SYSMOD                 = 0x11,
	MPL3115_INT_SOURCE             = 0x12,
	MPL3115_PT_DATA_CFG            = 0x13,
	MPL3115_BAR_IN_MSB             = 0x14,
	MPL3115_BAR_IN_LSB             = 0x15,
	MPL3115_P_TGT_MSB              = 0x16,
	MPL3115_P_TGT_LSB              = 0x17,
	MPL3115_T_TGT                  = 0x18,
	MPL3115_P_WND_MSB              = 0x19,
	MPL3115_P_WND_LSB              = 0x1A,
	MPL3115_T_WND                  = 0x1B,
	MPL3115_P_MIN_MSB              = 0x1C,
	MPL3115_P_MIN_CSB              = 0x1D,
	MPL3115_P_MIN_LSB              = 0x1E,
	MPL3115_T_MIN_MSB              = 0x1F,
	MPL3115_T_MIN_LSB              = 0x20,
	MPL3115_P_MAX_MSB              = 0x21,
	MPL3115_P_MAX_CSB              = 0x22,
	MPL3115_P_MAX_LSB              = 0x23,
	MPL3115_T_MAX_MSB              = 0x24,
	MPL3115_T_MAX_LSB              = 0x25,
	MPL3115_CTRL_REG1              = 0x26,
	MPL3115_CTRL_REG2              = 0x27,
	MPL3115_CTRL_REG3              = 0x28,
	MPL3115_CTRL_REG4              = 0x29,
	MPL3115_CTRL_REG5              = 0x2A,
	MPL3115_OFF_P                  = 0x2B,
	MPL3115_OFF_T                  = 0x2C,
	MPL3115_OFF_H                  = 0x2D,
};

#define MPL3115_I2C_ADDRESS     (0x60)  /*MPL3115A2 Address*/
#define MPL3115_WHOAMI_VALUE    (0xC4)  /*!< Who AM I address. */


/*--------------------------------
** Register: STATUS
** Enum: MPL3115_STATUS
** --
** Offset : 0x00 - Alias for DR_STATUS or F_STATUS.
** ------------------------------*/
typedef uint8_t MPL3115_STATUS_t;



/*--------------------------------
** Register: OUT_P_MSB
** Enum: MPL3115_OUT_P_MSB
** --
** Offset : 0x01 - Bits 12-19 of 20-bit real-time Pressure sample.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_P_MSB_t;


/*--------------------------------
** Register: OUT_P_CSB
** Enum: MPL3115_OUT_P_CSB
** --
** Offset : 0x02 - Bits 4-11 of 20-bit real-time Pressure sample.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_P_CSB_t;


/*--------------------------------
** Register: OUT_P_LSB
** Enum: MPL3115_OUT_P_LSB
** --
** Offset : 0x03 - Bits 0-3 of 20-bit real-time Pressure sample.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                    pd : 4; /*  - 20-bit pressure sample measurement data bits 3:0                         */

    } b;
    uint8_t w;
} MPL3115_OUT_P_LSB_t;


/*
** OUT_P_LSB - Bit field mask definitions 
*/
#define MPL3115_OUT_P_LSB_PD_MASK   ((uint8_t) 0xF0)
#define MPL3115_OUT_P_LSB_PD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: OUT_T_MSB
** Enum: MPL3115_OUT_T_MSB
** --
** Offset : 0x04 - Bits 4-11 of 12-bit real-time Temperature sample.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_T_MSB_t;


/*--------------------------------
** Register: OUT_T_LSB
** Enum: MPL3115_OUT_T_LSB
** --
** Offset : 0x05 - Bits 0-3 of 12-bit real-time Temperature sample.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                    pd : 4; /*  - 12-bit temperature sample measurement data bits 3:0                      */

    } b;
    uint8_t w;
} MPL3115_OUT_T_LSB_t;


/*
** OUT_T_LSB - Bit field mask definitions 
*/
#define MPL3115_OUT_T_LSB_PD_MASK   ((uint8_t) 0xF0)
#define MPL3115_OUT_T_LSB_PD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: DR_STATUS
** Enum: MPL3115_DR_STATUS
** --
** Offset : 0x06 - Data-ready status information
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t                   tdr : 1; /*  Temperature new Data Available.                                            */

        uint8_t                   pdr : 1; /*  Pressure/Altitude new data available.                                      */

        uint8_t                  ptdr : 1; /*  Pressure/Altitude OR Temperature data ready.                               */

        uint8_t _reserved_1           : 1;
        uint8_t                   tow : 1; /*  Temperature data overwrite.                                                */

        uint8_t                   pow : 1; /*  Pressure/Altitude data overwrite.                                          */

        uint8_t                  ptow : 1; /*  Pressure/Altitude OR Temperature data overwrite.                           */

    } b;
    uint8_t w;
} MPL3115_DR_STATUS_t;


/*
** DR_STATUS - Bit field mask definitions 
*/
#define MPL3115_DR_STATUS_TDR_MASK    ((uint8_t) 0x02)
#define MPL3115_DR_STATUS_TDR_SHIFT   ((uint8_t)    1)

#define MPL3115_DR_STATUS_PDR_MASK    ((uint8_t) 0x04)
#define MPL3115_DR_STATUS_PDR_SHIFT   ((uint8_t)    2)

#define MPL3115_DR_STATUS_PTDR_MASK   ((uint8_t) 0x08)
#define MPL3115_DR_STATUS_PTDR_SHIFT  ((uint8_t)    3)

#define MPL3115_DR_STATUS_TOW_MASK    ((uint8_t) 0x20)
#define MPL3115_DR_STATUS_TOW_SHIFT   ((uint8_t)    5)

#define MPL3115_DR_STATUS_POW_MASK    ((uint8_t) 0x40)
#define MPL3115_DR_STATUS_POW_SHIFT   ((uint8_t)    6)

#define MPL3115_DR_STATUS_PTOW_MASK   ((uint8_t) 0x80)
#define MPL3115_DR_STATUS_PTOW_SHIFT  ((uint8_t)    7)


/*
** DR_STATUS - Bit field value definitions  
*/
#define MPL3115_DR_STATUS_TDR_DRDY              ((uint8_t) 0x02)  /*  Set to 1 whenever a Temperature data acquisition is */
                                                                  /*  completed. Cleared anytime OUT_T_MSB register is    */
                                                                  /*  read, when F_MODE is zero                           */
#define MPL3115_DR_STATUS_PDR_DRDY              ((uint8_t) 0x04)  /*  Set to 1 whenever a new Pressure/Altitude data      */
                                                                  /*  acquisition is completed. Cleared anytime OUT_P_MSB */
                                                                  /*  register is read, when F_MODE is zero               */
#define MPL3115_DR_STATUS_PTDR_DRDY             ((uint8_t) 0x08)  /*  Signals that a new acquisition for either           */
                                                                  /*  Pressure/Altitude or Temperature is available.      */
                                                                  /*  Cleared anytime OUT_P_MSB or OUT_T_MSB register is  */
                                                                  /*  read, when F_MODE is zero                           */
#define MPL3115_DR_STATUS_TOW_OWR               ((uint8_t) 0x20)  /*  Set to 1 whenever a new Temperature acquisition is  */
                                                                  /*  completed before the retrieval of the previous      */
                                                                  /*  data. When this occurs the previous data is         */
                                                                  /*  overwritten. Cleared anytime OUT_T_MSB register is  */
                                                                  /*  read, when F_MODE is zero                           */
#define MPL3115_DR_STATUS_POW_OWR               ((uint8_t) 0x40)  /*  Set to 1 whenever a new Pressure/Altitude           */
                                                                  /*  acquisition is completed before the retrieval of    */
                                                                  /*  the previous data. When this occurs the previous    */
                                                                  /*  data is overwritten. POW is cleared anytime         */
                                                                  /*  OUT_P_MSB register is read, when F_MODE is zero     */
#define MPL3115_DR_STATUS_PTOW_OWR              ((uint8_t) 0x80)  /*  Set to 1 whenever new data is acquired before       */
                                                                  /*  completing the retrieval of the previous set. This  */
                                                                  /*  event occurs when the content of at least one data  */
                                                                  /*  register (i.e. OUT_P, OUT_T) has been overwritten.  */
                                                                  /*  PTOW is cleared when the high-bytes of the data     */
                                                                  /*  (OUT_P_MSB or OUT_T_MSB) are read, when F_MODE is   */
                                                                  /*  zero                                                */
/*------------------------------*/



/*--------------------------------
** Register: OUT_P_DELTA_MSB
** Enum: MPL3115_OUT_P_DELTA_MSB
** --
** Offset : 0x07 - Bits 12-19 of 20-bit Pressure change data.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_P_DELTA_MSB_t;


/*--------------------------------
** Register: OUT_P_DELTA_CSB
** Enum: MPL3115_OUT_P_DELTA_CSB
** --
** Offset : 0x08 - Bits 4-11 of 20-bit Pressure change data.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_P_DELTA_CSB_t;


/*--------------------------------
** Register: OUT_P_DELTA_LSB
** Enum: MPL3115_OUT_P_DELTA_LSB
** --
** Offset : 0x09 - Bits 0-3 of 20-bit Pressure change data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                   pcd : 4; /*  - 20-bit pressure change measurement data bits 3:0                         */

    } b;
    uint8_t w;
} MPL3115_OUT_P_DELTA_LSB_t;


/*
** OUT_P_DELTA_LSB - Bit field mask definitions 
*/
#define MPL3115_OUT_P_DELTA_LSB_PCD_MASK   ((uint8_t) 0xF0)
#define MPL3115_OUT_P_DELTA_LSB_PCD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: OUT_T_DELTA_MSB
** Enum: MPL3115_OUT_T_DELTA_MSB
** --
** Offset : 0x0A - Bits 4-11 of 12-bit Temperature change data.
** ------------------------------*/
typedef uint8_t MPL3115_OUT_T_DELTA_MSB_t;


/*--------------------------------
** Register: OUT_T_DELTA_LSB
** Enum: MPL3115_OUT_T_DELTA_LSB
** --
** Offset : 0x0B - Bits 0-3 of 12-bit Temperature change data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                   tcd : 4; /*  - 12-bit temperature change measurement data bits 3:0                      */

    } b;
    uint8_t w;
} MPL3115_OUT_T_DELTA_LSB_t;


/*
** OUT_T_DELTA_LSB - Bit field mask definitions 
*/
#define MPL3115_OUT_T_DELTA_LSB_TCD_MASK   ((uint8_t) 0xF0)
#define MPL3115_OUT_T_DELTA_LSB_TCD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: WHO_AM_I
** Enum: MPL3115_WHO_AM_I
** --
** Offset : 0x0C - Fixed Device ID Number.
** ------------------------------*/
typedef uint8_t MPL3115_WHO_AM_I_t;



/*--------------------------------
** Register: F_STATUS
** Enum: MPL3115_F_STATUS
** --
** Offset : 0x0D - FIFO Status: No FIFO event detected.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 f_cnt : 6; /*  FIFO sample counter. F_CNT[5:0] bits indicate the number of samples        */
                                           /*  currently stored in the FIFO buffer                                        */

        uint8_t           f_wmkf_flag : 1; /*  FIFO Watermark event                                                       */

        uint8_t                 f_ovf : 1; /*  FIFO overflow event.                                                       */

    } b;
    uint8_t w;
} MPL3115_F_STATUS_t;


/*
** F_STATUS - Bit field mask definitions 
*/
#define MPL3115_F_STATUS_F_CNT_MASK         ((uint8_t) 0x3F)
#define MPL3115_F_STATUS_F_CNT_SHIFT        ((uint8_t)    0)

#define MPL3115_F_STATUS_F_WMKF_FLAG_MASK   ((uint8_t) 0x40)
#define MPL3115_F_STATUS_F_WMKF_FLAG_SHIFT  ((uint8_t)    6)

#define MPL3115_F_STATUS_F_OVF_MASK         ((uint8_t) 0x80)
#define MPL3115_F_STATUS_F_OVF_SHIFT        ((uint8_t)    7)


/*
** F_STATUS - Bit field value definitions  
*/
#define MPL3115_F_STATUS_F_WMKF_FLAG_NOEVT     ((uint8_t) 0x00)  /*  No FIFO watermark event detected.                    */
#define MPL3115_F_STATUS_F_WMKF_FLAG_EVTDET    ((uint8_t) 0x40)  /*  FIFO Watermark event has been detected.              */
#define MPL3115_F_STATUS_F_OVF_NOOVFL          ((uint8_t) 0x00)  /*  No FIFO overflow events detected.                    */
#define MPL3115_F_STATUS_F_OVF_OVFLDET         ((uint8_t) 0x80)  /*  FIFO Overflow event has been detected.               */
/*------------------------------*/



/*--------------------------------
** Register: F_DATA
** Enum: MPL3115_F_DATA
** --
** Offset : 0x0E - FIFO 8-bit data access.
** ------------------------------*/
typedef uint8_t MPL3115_F_DATA_t;



/*--------------------------------
** Register: F_SETUP
** Enum: MPL3115_F_SETUP
** --
** Offset : 0x0F - FIFO setup.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                f_wmrk : 6; /*  FIFO Event Sample Count Watermark.                                         */

        uint8_t                f_mode : 2; /*  FIFO buffer overflow mode.                                                 */

    } b;
    uint8_t w;
} MPL3115_F_SETUP_t;


/*
** F_SETUP - Bit field mask definitions 
*/
#define MPL3115_F_SETUP_F_WMRK_MASK   ((uint8_t) 0x3F)
#define MPL3115_F_SETUP_F_WMRK_SHIFT  ((uint8_t)    0)

#define MPL3115_F_SETUP_F_MODE_MASK   ((uint8_t) 0xC0)
#define MPL3115_F_SETUP_F_MODE_SHIFT  ((uint8_t)    6)


/*
** F_SETUP - Bit field value definitions  
*/
#define MPL3115_F_SETUP_F_MODE_FIFO_OFF       ((uint8_t) 0x00)  /*  FIFO is disabled.                                     */
#define MPL3115_F_SETUP_F_MODE_CIR_MODE       ((uint8_t) 0x40)  /*  FIFO contains the most recent samples when overflowed */
                                                                /*  (circular buffer).                                    */
#define MPL3115_F_SETUP_F_MODE_STOP_MODE      ((uint8_t) 0x80)  /*  FIFO stops accepting new samples when overflowed.     */
/*------------------------------*/



/*--------------------------------
** Register: TIME_DLY
** Enum: MPL3115_TIME_DLY
** --
** Offset : 0x10 - Time since FIFO overflow.
** ------------------------------*/
typedef uint8_t MPL3115_TIME_DLY_t;



/*--------------------------------
** Register: SYSMOD
** Enum: MPL3115_SYSMOD
** --
** Offset : 0x11 - Current system mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                sysmod : 1; /*  - System mode data bit 0. (Bits 7-1 are reserved, will always read 0.)     */

    } b;
    uint8_t w;
} MPL3115_SYSMOD_t;


/*
** SYSMOD - Bit field mask definitions 
*/
#define MPL3115_SYSMOD_SYSMOD_MASK   ((uint8_t) 0x01)
#define MPL3115_SYSMOD_SYSMOD_SHIFT  ((uint8_t)    0)


/*
** SYSMOD - Bit field value definitions  
*/
#define MPL3115_SYSMOD_SYSMOD_STANDBY        ((uint8_t) 0x00)  /*  STANDBY Mode.                                          */
#define MPL3115_SYSMOD_SYSMOD_ACTIVE         ((uint8_t) 0x01)  /*  ACTIVE Mode.                                           */
/*------------------------------*/



/*--------------------------------
** Register: INT_SOURCE
** Enum: MPL3115_INT_SOURCE
** --
** Offset : 0x12 - Interrupt status. The bits that are set (logic ‘1’) indicate which function has asserted its interrupt and conversely, bits that are cleared (logic ‘0’) indicate which function has not asserted its interrupt.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              src_tchg : 1; /*  Delta T interrupt status bit.                                              */

        uint8_t              src_pchg : 1; /*  Delta P interrupt status bit.                                              */

        uint8_t               src_tth : 1; /*  Temperature threshold interrupt.                                           */

        uint8_t               src_pth : 1; /*  Altitude/Pressure threshold interrupt.                                     */

        uint8_t                src_tw : 1; /*  Temperature alerter status bit near or equal to target temperature.        */

        uint8_t                src_pw : 1; /*  Altitude/Pressure alerter status bit near or equal to target               */
                                           /*  Pressure/Altitude.                                                         */

        uint8_t              src_fifo : 1; /*  FIFO interrupt status bit.                                                 */

        uint8_t              src_drdy : 1; /*  Data ready interrupt status bit.                                           */

    } b;
    uint8_t w;
} MPL3115_INT_SOURCE_t;


/*
** INT_SOURCE - Bit field mask definitions 
*/
#define MPL3115_INT_SOURCE_SRC_TCHG_MASK   ((uint8_t) 0x01)
#define MPL3115_INT_SOURCE_SRC_TCHG_SHIFT  ((uint8_t)    0)

#define MPL3115_INT_SOURCE_SRC_PCHG_MASK   ((uint8_t) 0x02)
#define MPL3115_INT_SOURCE_SRC_PCHG_SHIFT  ((uint8_t)    1)

#define MPL3115_INT_SOURCE_SRC_TTH_MASK    ((uint8_t) 0x04)
#define MPL3115_INT_SOURCE_SRC_TTH_SHIFT   ((uint8_t)    2)

#define MPL3115_INT_SOURCE_SRC_PTH_MASK    ((uint8_t) 0x08)
#define MPL3115_INT_SOURCE_SRC_PTH_SHIFT   ((uint8_t)    3)

#define MPL3115_INT_SOURCE_SRC_TW_MASK     ((uint8_t) 0x10)
#define MPL3115_INT_SOURCE_SRC_TW_SHIFT    ((uint8_t)    4)

#define MPL3115_INT_SOURCE_SRC_PW_MASK     ((uint8_t) 0x20)
#define MPL3115_INT_SOURCE_SRC_PW_SHIFT    ((uint8_t)    5)

#define MPL3115_INT_SOURCE_SRC_FIFO_MASK   ((uint8_t) 0x40)
#define MPL3115_INT_SOURCE_SRC_FIFO_SHIFT  ((uint8_t)    6)

#define MPL3115_INT_SOURCE_SRC_DRDY_MASK   ((uint8_t) 0x80)
#define MPL3115_INT_SOURCE_SRC_DRDY_SHIFT  ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: PT_DATA_CFG
** Enum: MPL3115_PT_DATA_CFG
** --
** Offset : 0x13 - Data event flag configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 tdefe : 1; /*  Data event flag enable on new Temperature data.                            */

        uint8_t                 pdefe : 1; /*  Data event flag enable on new Pressure/Altitude data.                      */

        uint8_t                  drem : 1; /*  Data ready event mode.                                                     */

    } b;
    uint8_t w;
} MPL3115_PT_DATA_CFG_t;


/*
** PT_DATA_CFG - Bit field mask definitions 
*/
#define MPL3115_PT_DATA_CFG_TDEFE_MASK   ((uint8_t) 0x01)
#define MPL3115_PT_DATA_CFG_TDEFE_SHIFT  ((uint8_t)    0)

#define MPL3115_PT_DATA_CFG_PDEFE_MASK   ((uint8_t) 0x02)
#define MPL3115_PT_DATA_CFG_PDEFE_SHIFT  ((uint8_t)    1)

#define MPL3115_PT_DATA_CFG_DREM_MASK    ((uint8_t) 0x04)
#define MPL3115_PT_DATA_CFG_DREM_SHIFT   ((uint8_t)    2)


/*
** PT_DATA_CFG - Bit field value definitions  
*/
#define MPL3115_PT_DATA_CFG_TDEFE_DISABLED        ((uint8_t) 0x00)  /*  Event detection disabled.                         */
#define MPL3115_PT_DATA_CFG_TDEFE_ENABLED         ((uint8_t) 0x01)  /*  Event detection enabled. Raise event flag on new  */
                                                                    /*  Temperature data.                                 */
#define MPL3115_PT_DATA_CFG_PDEFE_DISABLED        ((uint8_t) 0x00)  /*  Event detection disabled.                         */
#define MPL3115_PT_DATA_CFG_PDEFE_ENABLED         ((uint8_t) 0x02)  /*  Event detection enabled. Raise event flag on new  */
                                                                    /*  Pressure/Altitude data.                           */
#define MPL3115_PT_DATA_CFG_DREM_DISABLED         ((uint8_t) 0x00)  /*  Event detection disabled.                         */
#define MPL3115_PT_DATA_CFG_DREM_ENABLED          ((uint8_t) 0x04)  /*  Event detection enabled. Generate data ready      */
                                                                    /*  event flag on new Pressure/Altitude or            */
                                                                    /*  Temperature data.                                 */
/*------------------------------*/



/*--------------------------------
** Register: BAR_IN_MSB
** Enum: MPL3115_BAR_IN_MSB
** --
** Offset : 0x14 - Bits 8-15 of Barometric input for Altitude calculation.
** ------------------------------*/
typedef uint8_t MPL3115_BAR_IN_MSB_t;


/*--------------------------------
** Register: BAR_IN_LSB
** Enum: MPL3115_BAR_IN_LSB
** --
** Offset : 0x15 - Bits 0-7 of Barometric input for Altitude calculation.
** ------------------------------*/
typedef uint8_t MPL3115_BAR_IN_LSB_t;



/*--------------------------------
** Register: P_TGT_MSB
** Enum: MPL3115_P_TGT_MSB
** --
** Offset : 0x16 - Bits 8-15 of Pressure/Altitude target value.
** ------------------------------*/
typedef uint8_t MPL3115_P_TGT_MSB_t;


/*--------------------------------
** Register: P_TGT_LSB
** Enum: MPL3115_P_TGT_LSB
** --
** Offset : 0x17 - Bits 0-7 of Pressure/Altitude target value.
** ------------------------------*/
typedef uint8_t MPL3115_P_TGT_LSB_t;



/*--------------------------------
** Register: T_TGT
** Enum: MPL3115_T_TGT
** --
** Offset : 0x18 - Temperature target value.
** ------------------------------*/
typedef uint8_t MPL3115_T_TGT_t;



/*--------------------------------
** Register: P_WND_MSB
** Enum: MPL3115_P_WND_MSB
** --
** Offset : 0x19 - Bits 8-15 of Pressure/Altitude window value.
** ------------------------------*/
typedef uint8_t MPL3115_P_WND_MSB_t;


/*--------------------------------
** Register: P_WND_LSB
** Enum: MPL3115_P_WND_LSB
** --
** Offset : 0x1A - Bits 0-7 of Pressure/Altitude window value.
** ------------------------------*/
typedef uint8_t MPL3115_P_WND_LSB_t;



/*--------------------------------
** Register: T_WND
** Enum: MPL3115_T_WND
** --
** Offset : 0x1B - Temperature window value.
** ------------------------------*/
typedef uint8_t MPL3115_T_WND_t;



/*--------------------------------
** Register: P_MIN_MSB
** Enum: MPL3115_P_MIN_MSB
** --
** Offset : 0x1C - Bits 12-19 of 20-bit Minimum Pressure/Altitude data.
** ------------------------------*/
typedef uint8_t MPL3115_P_MIN_MSB_t;


/*--------------------------------
** Register: P_MIN_CSB
** Enum: MPL3115_P_MIN_CSB
** --
** Offset : 0x1D - Bits 4-11 of 20-bit Minimum Pressure/Altitude data.
** ------------------------------*/
typedef uint8_t MPL3115_P_MIN_CSB_t;


/*--------------------------------
** Register: P_MIN_LSB
** Enum: MPL3115_P_MIN_LSB
** --
** Offset : 0x1E - Bits 0-3 of 20-bit Minimum Pressure/Altitude data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                minpad : 4; /*  - 20-bit Minimum Pressure/Altitude data bits 3:0.                          */

    } b;
    uint8_t w;
} MPL3115_P_MIN_LSB_t;


/*
** P_MIN_LSB - Bit field mask definitions 
*/
#define MPL3115_P_MIN_LSB_MINPAD_MASK   ((uint8_t) 0xF0)
#define MPL3115_P_MIN_LSB_MINPAD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: T_MIN_MSB
** Enum: MPL3115_T_MIN_MSB
** --
** Offset : 0x1F - Bits 4-11 of 12-bit Minimum Temperature data.
** ------------------------------*/
typedef uint8_t MPL3115_T_MIN_MSB_t;


/*--------------------------------
** Register: T_MIN_LSB
** Enum: MPL3115_T_MIN_LSB
** --
** Offset : 0x20 - Bits 0-3 of 12-bit Minimum Temperature data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                 mintd : 4; /*  - 12-bit Minimum Temperature data bits 3:0.                                */

    } b;
    uint8_t w;
} MPL3115_T_MIN_LSB_t;


/*
** T_MIN_LSB - Bit field mask definitions 
*/
#define MPL3115_T_MIN_LSB_MINTD_MASK   ((uint8_t) 0xF0)
#define MPL3115_T_MIN_LSB_MINTD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: P_MAX_MSB
** Enum: MPL3115_P_MAX_MSB
** --
** Offset : 0x21 - Bits 12-19 of 20-bit Maximum Pressure/Altitude data.
** ------------------------------*/
typedef uint8_t MPL3115_P_MAX_MSB_t;


/*--------------------------------
** Register: P_MAX_CSB
** Enum: MPL3115_P_MAX_CSB
** --
** Offset : 0x22 - Bits 4-11 of 20-bit Maximum Pressure/Altitude data.
** ------------------------------*/
typedef uint8_t MPL3115_P_MAX_CSB_t;


/*--------------------------------
** Register: P_MAX_LSB
** Enum: MPL3115_P_MAX_LSB
** --
** Offset : 0x23 - Bits 0-3 of 20-bit Maximum Pressure/Altitude data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                maxpad : 4; /*  - 20-bit Maximum Pressure/Altitude data bits 3:0.                          */

    } b;
    uint8_t w;
} MPL3115_P_MAX_LSB_t;


/*
** P_MAX_LSB - Bit field mask definitions 
*/
#define MPL3115_P_MAX_LSB_MAXPAD_MASK   ((uint8_t) 0xF0)
#define MPL3115_P_MAX_LSB_MAXPAD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: T_MAX_MSB
** Enum: MPL3115_T_MAX_MSB
** --
** Offset : 0x24 - Bits 4-11 of 12-bit Maximum Temperature data.
** ------------------------------*/
typedef uint8_t MPL3115_T_MAX_MSB_t;


/*--------------------------------
** Register: T_MAX_LSB
** Enum: MPL3115_T_MAX_LSB
** --
** Offset : 0x25 - Bits 0-3 of 12-bit Maximum Temperature data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t                 maxtd : 4; /*  - 12-bit Maximum Temperature data bits 3:0.                                */

    } b;
    uint8_t w;
} MPL3115_T_MAX_LSB_t;


/*
** T_MAX_LSB - Bit field mask definitions 
*/
#define MPL3115_T_MAX_LSB_MAXTD_MASK   ((uint8_t) 0xF0)
#define MPL3115_T_MAX_LSB_MAXTD_SHIFT  ((uint8_t)    4)


/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG1
** Enum: MPL3115_CTRL_REG1
** --
** Offset : 0x26 - Control Register 1: Modes, Oversampling.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  sbyb : 1; /*  Operation Mode.                                                            */

        uint8_t                   ost : 1; /*  OST bit to initiate a measurement immediately, If the SBYB bit is set to   */
                                           /*  active.                                                                    */

        uint8_t                   rst : 1; /*  Software Reset. This bit is used to activate the software reset.           */

        uint8_t                    os : 3; /*  Oversample Ratio. These bits select the oversampling ratio.                */

        uint8_t                   raw : 1; /*  RAW output mode. RAW bit will output ADC data with no post processing,     */
                                           /*  except for oversampling.                                                   */

        uint8_t                   alt : 1; /*  Altimeter-Barometer mode.                                                  */

    } b;
    uint8_t w;
} MPL3115_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions 
*/
#define MPL3115_CTRL_REG1_SBYB_MASK   ((uint8_t) 0x01)
#define MPL3115_CTRL_REG1_SBYB_SHIFT  ((uint8_t)    0)

#define MPL3115_CTRL_REG1_OST_MASK    ((uint8_t) 0x02)
#define MPL3115_CTRL_REG1_OST_SHIFT   ((uint8_t)    1)

#define MPL3115_CTRL_REG1_RST_MASK    ((uint8_t) 0x04)
#define MPL3115_CTRL_REG1_RST_SHIFT   ((uint8_t)    2)

#define MPL3115_CTRL_REG1_OS_MASK     ((uint8_t) 0x38)
#define MPL3115_CTRL_REG1_OS_SHIFT    ((uint8_t)    3)

#define MPL3115_CTRL_REG1_RAW_MASK    ((uint8_t) 0x40)
#define MPL3115_CTRL_REG1_RAW_SHIFT   ((uint8_t)    6)

#define MPL3115_CTRL_REG1_ALT_MASK    ((uint8_t) 0x80)
#define MPL3115_CTRL_REG1_ALT_SHIFT   ((uint8_t)    7)


/*
** CTRL_REG1 - Bit field value definitions  
*/
#define MPL3115_CTRL_REG1_SBYB_STANDBY          ((uint8_t) 0x00)  /*  Standby Mode.                                       */
#define MPL3115_CTRL_REG1_SBYB_ACTIVE           ((uint8_t) 0x01)  /*  Active Mode.                                        */
#define MPL3115_CTRL_REG1_OST_RESET             ((uint8_t) 0x00)  /*  Reset OST Bit.                                      */
#define MPL3115_CTRL_REG1_OST_SET               ((uint8_t) 0x02)  /*  SET OST Bit.                                        */
#define MPL3115_CTRL_REG1_RST_DIS               ((uint8_t) 0x00)  /*  Device reset disabled.                              */
#define MPL3115_CTRL_REG1_RST_EN                ((uint8_t) 0x04)  /*  Device reset enabled.                               */
#define MPL3115_CTRL_REG1_OS_OSR_1              ((uint8_t) 0x00)  /*  OSR = 1 and Minimum Time Between Data Samples 6 ms  */
#define MPL3115_CTRL_REG1_OS_OSR_2              ((uint8_t) 0x08)  /*  OSR = 2 and Minimum Time Between Data Samples 10 ms */
#define MPL3115_CTRL_REG1_OS_OSR_4              ((uint8_t) 0x10)  /*  OSR = 4 and Minimum Time Between Data Samples 18 ms */
#define MPL3115_CTRL_REG1_OS_OSR_8              ((uint8_t) 0x18)  /*  OSR = 8 and Minimum Time Between Data Samples 34 ms */
#define MPL3115_CTRL_REG1_OS_OSR_16             ((uint8_t) 0x20)  /*  OSR = 16 and Minimum Time Between Data Samples 66   */
                                                                  /*  ms                                                  */
#define MPL3115_CTRL_REG1_OS_OSR_32             ((uint8_t) 0x28)  /*  OSR = 32 and Minimum Time Between Data Samples 130  */
                                                                  /*  ms                                                  */
#define MPL3115_CTRL_REG1_OS_OSR_64             ((uint8_t) 0x30)  /*  OSR = 64 and Minimum Time Between Data Samples 258  */
                                                                  /*  ms                                                  */
#define MPL3115_CTRL_REG1_OS_OSR_128            ((uint8_t) 0x38)  /*  OSR = 128 and Minimum Time Between Data Samples 512 */
                                                                  /*  ms                                                  */
#define MPL3115_CTRL_REG1_RAW_DIS               ((uint8_t) 0x00)  /*  Raw output disabled.                                */
#define MPL3115_CTRL_REG1_RAW_EN                ((uint8_t) 0x40)  /*  Raw output enabled.                                 */
#define MPL3115_CTRL_REG1_ALT_ALT               ((uint8_t) 0x80)  /*  Altimeter Mode.                                     */
#define MPL3115_CTRL_REG1_ALT_BAR               ((uint8_t) 0x00)  /*  Barometer Mode.                                     */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG2
** Enum: MPL3115_CTRL_REG2
** --
** Offset : 0x27 - Control Register 2: Acquisition time step.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    st : 4; /*  Auto acquisition time step..                                               */

        uint8_t             alarm_sel : 1; /*  The bit selects the Target value for SRC_PW/SRC_TW and SRC_PTH/SRC_TTH.    */

        uint8_t           load_output : 1; /*  This is to load the target values for SRC_PW/SRC_TW and SRC_PTH/SRC_TTH.   */

    } b;
    uint8_t w;
} MPL3115_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions 
*/
#define MPL3115_CTRL_REG2_ST_MASK            ((uint8_t) 0x0F)
#define MPL3115_CTRL_REG2_ST_SHIFT           ((uint8_t)    0)

#define MPL3115_CTRL_REG2_ALARM_SEL_MASK     ((uint8_t) 0x10)
#define MPL3115_CTRL_REG2_ALARM_SEL_SHIFT    ((uint8_t)    4)

#define MPL3115_CTRL_REG2_LOAD_OUTPUT_MASK   ((uint8_t) 0x20)
#define MPL3115_CTRL_REG2_LOAD_OUTPUT_SHIFT  ((uint8_t)    5)


/*
** CTRL_REG2 - Bit field value definitions  
*/
#define MPL3115_CTRL_REG2_ALARM_SEL_USE_TGT     ((uint8_t) 0x00)  /*  The values in P_TGT_MSB, P_TGT_LSB and T_TGT are    */
                                                                  /*  used.                                               */
#define MPL3115_CTRL_REG2_ALARM_SEL_USE_OUT     ((uint8_t) 0x10)  /*  The values in OUT_P/OUT_T are used for calculating  */
                                                                  /*  the interrupts SRC_PW/SRC_TW and SRC_PTH/SRC_TTH.   */
#define MPL3115_CTRL_REG2_LOAD_OUTPUT_DNL       ((uint8_t) 0x00)  /*  Do not load OUT_P/OUT_T as target values.           */
#define MPL3115_CTRL_REG2_LOAD_OUTPUT_NXT_VAL   ((uint8_t) 0x20)  /*  The next values of OUT_P/OUT_T are used to set the  */
                                                                  /*  target values for the interrupts.                   */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG3
** Enum: MPL3115_CTRL_REG3
** --
** Offset : 0x28 - Control Register 3: Interrupt pin configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                pp_od2 : 1; /*  This bit configures the interrupt pad INT2 to Push-Pull or in Open Drain   */
                                           /*  mode.                                                                      */

        uint8_t                 ipol2 : 1; /*  Interrupt Polarity active high, or active low on interrupt pad INT2.       */

        uint8_t _reserved_            : 2;
        uint8_t                pp_od1 : 1; /*  This bit configures the interrupt pad INT1 to Push-Pull or in Open Drain   */
                                           /*  mode.                                                                      */

        uint8_t                 ipol1 : 1; /*  Interrupt Polarity active high, or active low on interrupt pad INT1.       */

    } b;
    uint8_t w;
} MPL3115_CTRL_REG3_t;


/*
** CTRL_REG3 - Bit field mask definitions 
*/
#define MPL3115_CTRL_REG3_PP_OD2_MASK   ((uint8_t) 0x01)
#define MPL3115_CTRL_REG3_PP_OD2_SHIFT  ((uint8_t)    0)

#define MPL3115_CTRL_REG3_IPOL2_MASK    ((uint8_t) 0x02)
#define MPL3115_CTRL_REG3_IPOL2_SHIFT   ((uint8_t)    1)

#define MPL3115_CTRL_REG3_PP_OD1_MASK   ((uint8_t) 0x10)
#define MPL3115_CTRL_REG3_PP_OD1_SHIFT  ((uint8_t)    4)

#define MPL3115_CTRL_REG3_IPOL1_MASK    ((uint8_t) 0x20)
#define MPL3115_CTRL_REG3_IPOL1_SHIFT   ((uint8_t)    5)


/*
** CTRL_REG3 - Bit field value definitions  
*/
#define MPL3115_CTRL_REG3_PP_OD2_INTPULLUP      ((uint8_t) 0x00)  /*  Internal Pull-up.                                   */
#define MPL3115_CTRL_REG3_PP_OD2_OPENDRAIN      ((uint8_t) 0x01)  /*  Open drain.                                         */
#define MPL3115_CTRL_REG3_IPOL2_LOW             ((uint8_t) 0x00)  /*  Active low.                                         */
#define MPL3115_CTRL_REG3_IPOL2_HIGH            ((uint8_t) 0x02)  /*  Active high.                                        */
#define MPL3115_CTRL_REG3_PP_OD1_INTPULLUP      ((uint8_t) 0x00)  /*  Internal Pull-up.                                   */
#define MPL3115_CTRL_REG3_PP_OD1_OPENDRAIN      ((uint8_t) 0x10)  /*  Open drain.                                         */
#define MPL3115_CTRL_REG3_IPOL1_LOW             ((uint8_t) 0x00)  /*  Active low.                                         */
#define MPL3115_CTRL_REG3_IPOL1_HIGH            ((uint8_t) 0x20)  /*  Active high.                                        */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG4
** Enum: MPL3115_CTRL_REG4
** --
** Offset : 0x29 - Control Register 4: Interrupt enables.
** ------------------------------*/
typedef union {
    struct {
        uint8_t           int_en_tchg : 1; /*  Temperature Change Interrupt Enable.                                       */

        uint8_t           int_en_pchg : 1; /*  Pressure Change Interrupt Enable.                                          */

        uint8_t            int_en_tth : 1; /*  Temperature Threshold Interrupt Enable.                                    */

        uint8_t            int_en_pth : 1; /*  Pressure Threshold Interrupt Enable.                                       */

        uint8_t             int_en_tw : 1; /*  Temperature window Interrupt Enable.                                       */

        uint8_t             int_en_pw : 1; /*  Pressure window Interrupt Enable.                                          */

        uint8_t           int_en_fifo : 1; /*  FIFO Interrupt Enable.                                                     */

        uint8_t           int_en_drdy : 1; /*  Data Ready Interrupt Enable.                                               */

    } b;
    uint8_t w;
} MPL3115_CTRL_REG4_t;


/*
** CTRL_REG4 - Bit field mask definitions 
*/
#define MPL3115_CTRL_REG4_INT_EN_TCHG_MASK   ((uint8_t) 0x01)
#define MPL3115_CTRL_REG4_INT_EN_TCHG_SHIFT  ((uint8_t)    0)

#define MPL3115_CTRL_REG4_INT_EN_PCHG_MASK   ((uint8_t) 0x02)
#define MPL3115_CTRL_REG4_INT_EN_PCHG_SHIFT  ((uint8_t)    1)

#define MPL3115_CTRL_REG4_INT_EN_TTH_MASK    ((uint8_t) 0x04)
#define MPL3115_CTRL_REG4_INT_EN_TTH_SHIFT   ((uint8_t)    2)

#define MPL3115_CTRL_REG4_INT_EN_PTH_MASK    ((uint8_t) 0x08)
#define MPL3115_CTRL_REG4_INT_EN_PTH_SHIFT   ((uint8_t)    3)

#define MPL3115_CTRL_REG4_INT_EN_TW_MASK     ((uint8_t) 0x10)
#define MPL3115_CTRL_REG4_INT_EN_TW_SHIFT    ((uint8_t)    4)

#define MPL3115_CTRL_REG4_INT_EN_PW_MASK     ((uint8_t) 0x20)
#define MPL3115_CTRL_REG4_INT_EN_PW_SHIFT    ((uint8_t)    5)

#define MPL3115_CTRL_REG4_INT_EN_FIFO_MASK   ((uint8_t) 0x40)
#define MPL3115_CTRL_REG4_INT_EN_FIFO_SHIFT  ((uint8_t)    6)

#define MPL3115_CTRL_REG4_INT_EN_DRDY_MASK   ((uint8_t) 0x80)
#define MPL3115_CTRL_REG4_INT_EN_DRDY_SHIFT  ((uint8_t)    7)


/*
** CTRL_REG4 - Bit field value definitions  
*/
#define MPL3115_CTRL_REG4_INT_EN_TCHG_INTDISABLED ((uint8_t) 0x00)  /*  Temperature Change interrupt disabled.            */
#define MPL3115_CTRL_REG4_INT_EN_TCHG_INTENABLED ((uint8_t) 0x01)  /*  Temperature Change interrupt enabled               */
#define MPL3115_CTRL_REG4_INT_EN_PCHG_INTDISABLED ((uint8_t) 0x00)  /*  Pressure Change interrupt disabled.               */
#define MPL3115_CTRL_REG4_INT_EN_PCHG_INTENABLED ((uint8_t) 0x02)  /*  Pressure Change interrupt enabled                  */
#define MPL3115_CTRL_REG4_INT_EN_TTH_INTDISABLED ((uint8_t) 0x00)  /*  Temperature Threshold interrupt disabled.          */
#define MPL3115_CTRL_REG4_INT_EN_TTH_INTENABLED ((uint8_t) 0x04)  /*  Temperature Threshold interrupt enabled             */
#define MPL3115_CTRL_REG4_INT_EN_PTH_INTDISABLED ((uint8_t) 0x00)  /*  Pressure Threshold interrupt disabled.             */
#define MPL3115_CTRL_REG4_INT_EN_PTH_INTENABLED ((uint8_t) 0x08)  /*  Pressure Threshold interrupt enabled                */
#define MPL3115_CTRL_REG4_INT_EN_TW_INTDISABLED ((uint8_t) 0x00)  /*  Temperature window interrupt disabled.              */
#define MPL3115_CTRL_REG4_INT_EN_TW_INTENABLED  ((uint8_t) 0x10)  /*  Temperature window interrupt enabled                */
#define MPL3115_CTRL_REG4_INT_EN_PW_INTDISABLED ((uint8_t) 0x00)  /*  Pressure window interrupt disabled.                 */
#define MPL3115_CTRL_REG4_INT_EN_PW_INTENABLED  ((uint8_t) 0x20)  /*  Pressure window interrupt enabled                   */
#define MPL3115_CTRL_REG4_INT_EN_FIFO_INTDISABLED ((uint8_t) 0x00)  /*  FIFO interrupt disabled.                          */
#define MPL3115_CTRL_REG4_INT_EN_FIFO_INTENABLED ((uint8_t) 0x40)  /*  FIFO interrupt enabled                             */
#define MPL3115_CTRL_REG4_INT_EN_DRDY_INTDISABLED ((uint8_t) 0x00)  /*  Data Ready interrupt disabled.                    */
#define MPL3115_CTRL_REG4_INT_EN_DRDY_INTENABLED ((uint8_t) 0x80)  /*  Data Ready interrupt enabled.                      */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG5
** Enum: MPL3115_CTRL_REG5
** --
** Offset : 0x2A - Control Register 5: Interrupt output pin assignment.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          int_cfg_tchg : 1; /*  Temperature Change INT1/INT2 Configuration.                                */

        uint8_t          int_cfg_pchg : 1; /*  Pressure Change INT1/INT2 Configuration.                                   */

        uint8_t           int_cfg_tth : 1; /*  Temperature Threshold INT1/INT2 Configuration.                             */

        uint8_t           int_cfg_pth : 1; /*  Pressure Threshold INT1/INT2 Configuration.                                */

        uint8_t            int_cfg_tw : 1; /*  Temperature window INT1/INT2 Configuration.                                */

        uint8_t            int_cfg_pw : 1; /*  Pressure window INT1/INT2 Configuration.                                   */

        uint8_t          int_cfg_fifo : 1; /*  FIFO INT1/INT2 Configuration.                                              */

        uint8_t          int_cfg_drdy : 1; /*  Data Ready INT1/INT2 Configuration.                                        */

    } b;
    uint8_t w;
} MPL3115_CTRL_REG5_t;


/*
** CTRL_REG5 - Bit field mask definitions 
*/
#define MPL3115_CTRL_REG5_INT_CFG_TCHG_MASK   ((uint8_t) 0x01)
#define MPL3115_CTRL_REG5_INT_CFG_TCHG_SHIFT  ((uint8_t)    0)

#define MPL3115_CTRL_REG5_INT_CFG_PCHG_MASK   ((uint8_t) 0x02)
#define MPL3115_CTRL_REG5_INT_CFG_PCHG_SHIFT  ((uint8_t)    1)

#define MPL3115_CTRL_REG5_INT_CFG_TTH_MASK    ((uint8_t) 0x04)
#define MPL3115_CTRL_REG5_INT_CFG_TTH_SHIFT   ((uint8_t)    2)

#define MPL3115_CTRL_REG5_INT_CFG_PTH_MASK    ((uint8_t) 0x08)
#define MPL3115_CTRL_REG5_INT_CFG_PTH_SHIFT   ((uint8_t)    3)

#define MPL3115_CTRL_REG5_INT_CFG_TW_MASK     ((uint8_t) 0x10)
#define MPL3115_CTRL_REG5_INT_CFG_TW_SHIFT    ((uint8_t)    4)

#define MPL3115_CTRL_REG5_INT_CFG_PW_MASK     ((uint8_t) 0x20)
#define MPL3115_CTRL_REG5_INT_CFG_PW_SHIFT    ((uint8_t)    5)

#define MPL3115_CTRL_REG5_INT_CFG_FIFO_MASK   ((uint8_t) 0x40)
#define MPL3115_CTRL_REG5_INT_CFG_FIFO_SHIFT  ((uint8_t)    6)

#define MPL3115_CTRL_REG5_INT_CFG_DRDY_MASK   ((uint8_t) 0x80)
#define MPL3115_CTRL_REG5_INT_CFG_DRDY_SHIFT  ((uint8_t)    7)


/*
** CTRL_REG5 - Bit field value definitions  
*/
#define MPL3115_CTRL_REG5_INT_CFG_TCHG_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_TCHG_INT1     ((uint8_t) 0x01)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PCHG_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PCHG_INT1     ((uint8_t) 0x02)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_TTH_INT2      ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_TTH_INT1      ((uint8_t) 0x04)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PTH_INT2      ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PTH_INT1      ((uint8_t) 0x08)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_TW_INT2       ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_TW_INT1       ((uint8_t) 0x10)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PW_INT2       ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_PW_INT1       ((uint8_t) 0x20)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_FIFO_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_FIFO_INT1     ((uint8_t) 0x40)  /*  Interrupt is routed to INT1 Pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_DRDY_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                    */
#define MPL3115_CTRL_REG5_INT_CFG_DRDY_INT1     ((uint8_t) 0x80)  /*  Interrupt is routed to INT1 Pin.                    */
/*------------------------------*/



/*--------------------------------
** Register: OFF_P
** Enum: MPL3115_OFF_P
** --
** Offset : 0x2B - Pressure data offset.
** ------------------------------*/
typedef uint8_t MPL3115_OFF_P_t;



/*--------------------------------
** Register: OFF_T
** Enum: MPL3115_OFF_T
** --
** Offset : 0x2C - Temperature data offset.
** ------------------------------*/
typedef uint8_t MPL3115_OFF_T_t;



/*--------------------------------
** Register: OFF_H
** Enum: MPL3115_OFF_H
** --
** Offset : 0x2D - Altitude data offset.
** ------------------------------*/
typedef uint8_t MPL3115_OFF_H_t;


#endif  /* MPL3115_H_ */ 
