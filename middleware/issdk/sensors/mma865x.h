/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MMA865x_H_
#define MMA865x_H_

/**
 **
 **  MMA865x Sensor Internal Registers
 */
enum {
        MMA865x_STATUS             = 0x00,
        MMA865x_F_STATUS           = 0x00,
        MMA865x_OUT_X_MSB          = 0x01,
        MMA865x_OUT_X_LSB          = 0x02,
        MMA865x_OUT_Y_MSB          = 0x03,
        MMA865x_OUT_Y_LSB          = 0x04,
        MMA865x_OUT_Z_MSB          = 0x05,
        MMA865x_OUT_Z_LSB          = 0x06,
        MMA865x_F_SETUP            = 0x09,
        MMA865x_TRIG_CFG           = 0x0A,
        MMA865x_SYSMOD             = 0x0B,
        MMA865x_INT_SOURCE         = 0x0C,
        MMA865x_WHO_AM_I           = 0x0D,
        MMA865x_XYZ_DATA_CFG       = 0x0E,
        MMA865x_HP_FILTER_CUTOFF   = 0x0F,
        MMA865x_PL_STATUS          = 0x10,
        MMA865x_PL_CFG             = 0x11,
        MMA865x_PL_COUNT           = 0x12,
        MMA865x_PL_BF_ZCOMP        = 0x13,
        MMA865x_P_L_THS_REG        = 0x14,
        MMA865x_FF_MT_CFG          = 0x15,
        MMA865x_FF_MT_SRC          = 0x16,
        MMA865x_FF_MT_THS          = 0x17,
        MMA865x_FF_MT_COUNT        = 0x18,
        MMA865x_TRANSIENT_CFG      = 0x1D,
        MMA865x_TRANSIENT_SRC      = 0x1E,
        MMA865x_TRANSIENT_THS      = 0x1F,
        MMA865x_TRANSIENT_COUNT    = 0x20,
        MMA865x_PULSE_CFG          = 0x21,
        MMA865x_PULSE_SRC          = 0x22,
        MMA865x_PULSE_THSX         = 0x23,
        MMA865x_PULSE_THSY         = 0x24,
        MMA865x_PULSE_THSZ         = 0x25,
        MMA865x_PULSE_TMLT         = 0x26,
        MMA865x_PULSE_LTCY         = 0x27,
        MMA865x_PULSE_WIND         = 0x28,
        MMA865x_ASLP_COUNT         = 0x29,
        MMA865x_CTRL_REG1          = 0x2A,
        MMA865x_CTRL_REG2          = 0x2B,
        MMA865x_CTRL_REG3          = 0x2C,
        MMA865x_CTRL_REG4          = 0x2D,
        MMA865x_CTRL_REG5          = 0x2E,
        MMA865x_OFF_X              = 0x2F,
        MMA865x_OFF_Y              = 0x30,
        MMA865x_OFF_Z              = 0x31,
};


#define MMA865x_I2C_ADDRESS     (0x1D)  /* MMA865x I2C Slave Address. */
#define MMA8652_WHOAMI_VALUE    (0x4A)  /* MMA8652 Who_Am_I Value. */
#define MMA8653_WHOAMI_VALUE    (0x5A)  /* MMA8653 Who_Am_I Value. */



/*--------------------------------
** Register: STATUS
** Enum: MMA865x_STATUS
** --
** Offset : 0x00 - Data Status register (F_MODE = 00)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xdr : 1; /*  - X-Axis new Data Available.                                               */

        uint8_t                   ydr : 1; /*  - Y-Axis new data available.                                               */

        uint8_t                   zdr : 1; /*  - Z-Axis new data available.                                               */

        uint8_t                 zyxdr : 1; /*  - X or Y or Z-Axis new data available.                                     */

        uint8_t                   xow : 1; /*  - X-Axis data overwrite.                                                   */

        uint8_t                   yow : 1; /*  - Y-Axis data overwrite.                                                   */

        uint8_t                   zow : 1; /*  - Z-Axis data overwrite.                                                   */

        uint8_t                 zyxow : 1; /*  - X, Y, Z-Axis data overwrite.                                             */

    } b;
    uint8_t w;
} MMA865x_STATUS_t;


/*
** STATUS - Bit field mask definitions 
*/
#define MMA865x_STATUS_XDR_MASK     ((uint8_t) 0x01)
#define MMA865x_STATUS_XDR_SHIFT    ((uint8_t)    0)

#define MMA865x_STATUS_YDR_MASK     ((uint8_t) 0x02)
#define MMA865x_STATUS_YDR_SHIFT    ((uint8_t)    1)

#define MMA865x_STATUS_ZDR_MASK     ((uint8_t) 0x04)
#define MMA865x_STATUS_ZDR_SHIFT    ((uint8_t)    2)

#define MMA865x_STATUS_ZYXDR_MASK   ((uint8_t) 0x08)
#define MMA865x_STATUS_ZYXDR_SHIFT  ((uint8_t)    3)

#define MMA865x_STATUS_XOW_MASK     ((uint8_t) 0x10)
#define MMA865x_STATUS_XOW_SHIFT    ((uint8_t)    4)

#define MMA865x_STATUS_YOW_MASK     ((uint8_t) 0x20)
#define MMA865x_STATUS_YOW_SHIFT    ((uint8_t)    5)

#define MMA865x_STATUS_ZOW_MASK     ((uint8_t) 0x40)
#define MMA865x_STATUS_ZOW_SHIFT    ((uint8_t)    6)

#define MMA865x_STATUS_ZYXOW_MASK   ((uint8_t) 0x80)
#define MMA865x_STATUS_ZYXOW_SHIFT  ((uint8_t)    7)


/*
** STATUS - Bit field value definitions  
*/
#define MMA865x_STATUS_XDR_DRDY              ((uint8_t) 0x01)  /*  - Set to 1 whenever new X-axis data acquisition is     */
                                                               /*  completed. XDR is cleared any time OUT_X_MSB register  */
                                                               /*  is read.                                               */
#define MMA865x_STATUS_YDR_DRDY              ((uint8_t) 0x02)  /*  - Set to 1 whenever new Y-axis data acquisition is     */
                                                               /*  completed. YDR is cleared any time OUT_Y_MSB register  */
                                                               /*  is read.                                               */
#define MMA865x_STATUS_ZDR_DRDY              ((uint8_t) 0x04)  /*  - Set to 1 whenever new Z-axis data acquisition is     */
                                                               /*  completed. ZDR is cleared any time OUT_Z_MSB register  */
                                                               /*  is read.                                               */
#define MMA865x_STATUS_ZYXDR_DRDY            ((uint8_t) 0x08)  /*  - Signals that new acquisition for any of the enabled  */
                                                               /*  channels is available. ZYXDR is cleared when the       */
                                                               /*  high-bytes of the data (OUT_X_MSB, OUT_Y_MSB,          */
                                                               /*  OUT_Z_MSB) of all the enabled channels are read.       */
#define MMA865x_STATUS_XOW_OWR               ((uint8_t) 0x10)  /*  - Set to 1 whenever new X-axis acquisition is          */
                                                               /*  completed before the retrieval of the previous data.   */
                                                               /*  When this occurs the previous data is overwritten. XOW */
                                                               /*  is cleared any time OUT_X_MSB register is read.        */
#define MMA865x_STATUS_YOW_OWR               ((uint8_t) 0x20)  /*  - Set to 1 whenever new Y-axis acquisition is          */
                                                               /*  completed before the retrieval of the previous data.   */
                                                               /*  When this occurs the previous data is overwritten. YOW */
                                                               /*  is cleared any time OUT_Y_MSB register is read.        */
#define MMA865x_STATUS_ZOW_OWR               ((uint8_t) 0x40)  /*  - Set to 1 whenever new Z-axis acquisition is          */
                                                               /*  completed before the retrieval of the previous data.   */
                                                               /*  When this occurs the previous data is overwritten. ZOW */
                                                               /*  is cleared any time OUT_Z_MSB register is read.        */
#define MMA865x_STATUS_ZYXOW_OWR             ((uint8_t) 0x80)  /*  - Set to 1 whenever new data is acquired before        */
                                                               /*  completing the retrieval of the previous set. This     */
                                                               /*  event occurs when the content of at least one data     */
                                                               /*  register (i.e. OUT_X, OUT_Y, OUT_Z) has been           */
                                                               /*  overwritten. ZYXOW is cleared when the highbytes of    */
                                                               /*  the data (OUT_X_MSB, OUT_Y_MSB, OUT_Z_MSB) of all      */
                                                               /*  active channels are read.                              */
/*------------------------------*/




/*--------------------------------
** Register: F_STATUS
** Enum: MMA865x_F_STATUS
** --
** Offset : 0x00 - FIFO Status register (F_MODE > 0)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 f_cnt : 6; /*  - FIFO sample counter; indicates the number of samples currently stored in */
                                           /*  the FIFO.                                                                  */

        uint8_t                f_wmkf : 1; /*  - FIFO sample count greater than or equal to the watermark count (F_SETUP  */
                                           /*  :: F_WMRK) has been detected.                                              */

        uint8_t                 f_ovf : 1; /*  - FIFO overflow event, such as when F_CNT = 32 and a new sample arrives,   */
                                           /*  asserts the F_OVF flag.                                                    */

    } b;
    uint8_t w;
} MMA865x_F_STATUS_t;


/*
** F_STATUS - Bit field mask definitions 
*/
#define MMA865x_F_STATUS_F_CNT_MASK    ((uint8_t) 0x3F)
#define MMA865x_F_STATUS_F_CNT_SHIFT   ((uint8_t)    0)

#define MMA865x_F_STATUS_F_WMKF_MASK   ((uint8_t) 0x40)
#define MMA865x_F_STATUS_F_WMKF_SHIFT  ((uint8_t)    6)

#define MMA865x_F_STATUS_F_OVF_MASK    ((uint8_t) 0x80)
#define MMA865x_F_STATUS_F_OVF_SHIFT   ((uint8_t)    7)


/*
** F_STATUS - Bit field value definitions  
*/
#define MMA865x_F_STATUS_F_WMKF_NONE           ((uint8_t) 0x00)  /*  - FIFO Watermark event has NOT been detected.        */
#define MMA865x_F_STATUS_F_WMKF_DETECTED       ((uint8_t) 0x40)  /*  - FIFO Watermark event has been detected.            */
#define MMA865x_F_STATUS_F_OVF_NONE            ((uint8_t) 0x00)  /*  - FIFO Overflow event has NOT been detected.         */
#define MMA865x_F_STATUS_F_OVF_DETECTED        ((uint8_t) 0x80)  /*  - FIFO Overflow event has been detected.             */
/*------------------------------*/




/*--------------------------------
** Register: OUT_X_MSB
** Enum: MMA865x_OUT_X_MSB
** --
** Offset : 0x01 - Bits 8-15 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_X_MSB_t;


/*--------------------------------
** Register: OUT_X_LSB
** Enum: MMA865x_OUT_X_LSB
** --
** Offset : 0x02 - Bits 0-7 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_X_LSB_t;


/*--------------------------------
** Register: OUT_Y_MSB
** Enum: MMA865x_OUT_Y_MSB
** --
** Offset : 0x03 - Bits 8-15 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_Y_MSB_t;


/*--------------------------------
** Register: OUT_Y_LSB
** Enum: MMA865x_OUT_Y_LSB
** --
** Offset : 0x04 - Bits 0-7 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_Y_LSB_t;


/*--------------------------------
** Register: OUT_Z_MSB
** Enum: MMA865x_OUT_Z_MSB
** --
** Offset : 0x05 - Bits 8-15 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_Z_MSB_t;


/*--------------------------------
** Register: OUT_Z_LSB
** Enum: MMA865x_OUT_Z_LSB
** --
** Offset : 0x06 - Bits 0-7 of 12-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MMA865x_OUT_Z_LSB_t;




/*--------------------------------
** Register: F_SETUP
** Enum: MMA865x_F_SETUP
** --
** Offset : 0x09 - FIFO configuration
** ------------------------------*/
typedef union {
    struct {
        uint8_t                f_wmrk : 6; /*  - FIFO sample count watermark setting.                                     */

        uint8_t                f_mode : 2; /*  - FIFO operating mode selection.                                           */

    } b;
    uint8_t w;
} MMA865x_F_SETUP_t;


/*
** F_SETUP - Bit field mask definitions 
*/
#define MMA865x_F_SETUP_F_WMRK_MASK   ((uint8_t) 0x3F)
#define MMA865x_F_SETUP_F_WMRK_SHIFT  ((uint8_t)    0)

#define MMA865x_F_SETUP_F_MODE_MASK   ((uint8_t) 0xC0)
#define MMA865x_F_SETUP_F_MODE_SHIFT  ((uint8_t)    6)


/*
** F_SETUP - Bit field value definitions  
*/
#define MMA865x_F_SETUP_F_MODE_FIFO_OFF       ((uint8_t) 0x00)  /*  - FIFO is disabled.                                   */
#define MMA865x_F_SETUP_F_MODE_CIR_MODE       ((uint8_t) 0x40)  /*  - FIFO is in Circular Buffer mode.                    */
#define MMA865x_F_SETUP_F_MODE_STOP_MODE      ((uint8_t) 0x80)  /*  - FIFO is in Stop mode.                               */
#define MMA865x_F_SETUP_F_MODE_TRIG_MODE      ((uint8_t) 0xc0)  /*  - FIFO is in Trigger mode. The FIFO will be in a      */
                                                                /*  circular mode until the trigger event occurs, after   */
                                                                /*  which the FIFO will continue to accept samples for    */
                                                                /*  WMRK samples and then stop receiving further samples. */
/*------------------------------*/




/*--------------------------------
** Register: TRIG_CFG
** Enum: MMA865x_TRIG_CFG
** --
** Offset : 0x0A - Trigger Configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 2;
        uint8_t            trig_ff_mt : 1; /*  - Freefall/Motion Trigger.                                                 */

        uint8_t            trig_pulse : 1; /*  - Pulse Interrupt Trigger.                                                 */

        uint8_t           trig_lndprt : 1; /*  - Landscape/Portrait Orientation Interrupt Trigger.                        */

        uint8_t            trig_trans : 1; /*  - Transient Interrupt Trigger.                                             */

    } b;
    uint8_t w;
} MMA865x_TRIG_CFG_t;


/*
** TRIG_CFG - Bit field mask definitions 
*/
#define MMA865x_TRIG_CFG_TRIG_FF_MT_MASK    ((uint8_t) 0x04)
#define MMA865x_TRIG_CFG_TRIG_FF_MT_SHIFT   ((uint8_t)    2)

#define MMA865x_TRIG_CFG_TRIG_PULSE_MASK    ((uint8_t) 0x08)
#define MMA865x_TRIG_CFG_TRIG_PULSE_SHIFT   ((uint8_t)    3)

#define MMA865x_TRIG_CFG_TRIG_LNDPRT_MASK   ((uint8_t) 0x10)
#define MMA865x_TRIG_CFG_TRIG_LNDPRT_SHIFT  ((uint8_t)    4)

#define MMA865x_TRIG_CFG_TRIG_TRANS_MASK    ((uint8_t) 0x20)
#define MMA865x_TRIG_CFG_TRIG_TRANS_SHIFT   ((uint8_t)    5)


/*
** TRIG_CFG - Bit field value definitions  
*/
#define MMA865x_TRIG_CFG_TRIG_TRANS_EN         ((uint8_t) 0x20)  /*  - This function can trigger the FIFO at its (the     */
                                                                 /*  function’s) interrupt.                                */
#define MMA865x_TRIG_CFG_TRIG_TRANS_DISABLED   ((uint8_t) 0x00)  /*  - This function has not asserted its interrupt.      */
#define MMA865x_TRIG_CFG_TRIG_LNDPRT_EN        ((uint8_t) 0x10)  /*  - This function can trigger the FIFO at its (the     */
                                                                 /*  function’s) interrupt.                                */
#define MMA865x_TRIG_CFG_TRIG_LNDPRT_DISABLED  ((uint8_t) 0x00)  /*  - This function has not asserted its interrupt.      */
#define MMA865x_TRIG_CFG_TRIG_PULSE_EN         ((uint8_t) 0x08)  /*  - This function can trigger the FIFO at its (the     */
                                                                 /*  function’s) interrupt.                                */
#define MMA865x_TRIG_CFG_TRIG_PULSE_DISABLED   ((uint8_t) 0x00)  /*  - This function has not asserted its interrupt.      */
#define MMA865x_TRIG_CFG_TRIG_FF_MT_EN         ((uint8_t) 0x04)  /*  - This function can trigger the FIFO at its (the     */
                                                                 /*  function’s) interrupt.                                */
#define MMA865x_TRIG_CFG_TRIG_FF_MT_DISABLED   ((uint8_t) 0x00)  /*  - This function has not asserted its interrupt.      */
/*------------------------------*/




/*--------------------------------
** Register: SYSMOD
** Enum: MMA865x_SYSMOD
** --
** Offset : 0x0B - System Mode register (Read-Only)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                sysmod : 2; /*  - System mode data bits 0-1.                                               */

        uint8_t                   fgt : 5; /*  - Number of ODR time units since FGERR was asserted.                       */

        uint8_t                 fgerr : 1; /*  - FIFO Gate Error.                                                         */

    } b;
    uint8_t w;
} MMA865x_SYSMOD_t;


/*
** SYSMOD - Bit field mask definitions 
*/
#define MMA865x_SYSMOD_SYSMOD_MASK   ((uint8_t) 0x03)
#define MMA865x_SYSMOD_SYSMOD_SHIFT  ((uint8_t)    0)

#define MMA865x_SYSMOD_FGT_MASK      ((uint8_t) 0x7C)
#define MMA865x_SYSMOD_FGT_SHIFT     ((uint8_t)    2)

#define MMA865x_SYSMOD_FGERR_MASK    ((uint8_t) 0x80)
#define MMA865x_SYSMOD_FGERR_SHIFT   ((uint8_t)    7)


/*
** SYSMOD - Bit field value definitions  
*/
#define MMA865x_SYSMOD_FGERR_NONE            ((uint8_t) 0x00)  /*  - No FIFO Gate Error detected.                         */
#define MMA865x_SYSMOD_FGERR_DETECTED        ((uint8_t) 0x80)  /*  - FIFO Gate Error was detected.                        */
#define MMA865x_SYSMOD_SYSMOD_STANDBY        ((uint8_t) 0x00)  /*  - STANDBY Mode.                                        */
#define MMA865x_SYSMOD_SYSMOD_WAKE           ((uint8_t) 0x01)  /*  - WAKE Mode.                                           */
#define MMA865x_SYSMOD_SYSMOD_SLEEP          ((uint8_t) 0x02)  /*  - SLEEP Mode.                                          */
/*------------------------------*/




/*--------------------------------
** Register: INT_SOURCE
** Enum: MMA865x_INT_SOURCE
** --
** Offset : 0x0C - Interrupt source status
** ------------------------------*/
typedef union {
    struct {
        uint8_t              src_drdy : 1; /*  - Data Ready Interrupt bit status bit                                      */

        uint8_t _reserved_            : 1;
        uint8_t             src_ff_mt : 1; /*  - Freefall/Motion interrupt status bit                                     */

        uint8_t             src_pulse : 1; /*  - Pulse interrupt status bit                                               */

        uint8_t            src_lndprt : 1; /*  - Landscape/Portrait Orientation interrupt status bit.                     */

        uint8_t             src_trans : 1; /*  - Transient interrupt status bit.                                          */

        uint8_t              src_fifo : 1; /*  - FIFO interrupt status bit.                                               */

        uint8_t              src_aslp : 1; /*  - Auto-SLEEP/WAKE interrupt status bit.                                    */

    } b;
    uint8_t w;
} MMA865x_INT_SOURCE_t;


/*
** INT_SOURCE - Bit field mask definitions 
*/
#define MMA865x_INT_SOURCE_SRC_DRDY_MASK     ((uint8_t) 0x01)
#define MMA865x_INT_SOURCE_SRC_DRDY_SHIFT    ((uint8_t)    0)

#define MMA865x_INT_SOURCE_SRC_FF_MT_MASK    ((uint8_t) 0x04)
#define MMA865x_INT_SOURCE_SRC_FF_MT_SHIFT   ((uint8_t)    2)

#define MMA865x_INT_SOURCE_SRC_PULSE_MASK    ((uint8_t) 0x08)
#define MMA865x_INT_SOURCE_SRC_PULSE_SHIFT   ((uint8_t)    3)

#define MMA865x_INT_SOURCE_SRC_LNDPRT_MASK   ((uint8_t) 0x10)
#define MMA865x_INT_SOURCE_SRC_LNDPRT_SHIFT  ((uint8_t)    4)

#define MMA865x_INT_SOURCE_SRC_TRANS_MASK    ((uint8_t) 0x20)
#define MMA865x_INT_SOURCE_SRC_TRANS_SHIFT   ((uint8_t)    5)

#define MMA865x_INT_SOURCE_SRC_FIFO_MASK     ((uint8_t) 0x40)
#define MMA865x_INT_SOURCE_SRC_FIFO_SHIFT    ((uint8_t)    6)

#define MMA865x_INT_SOURCE_SRC_ASLP_MASK     ((uint8_t) 0x80)
#define MMA865x_INT_SOURCE_SRC_ASLP_SHIFT    ((uint8_t)    7)


/*
** INT_SOURCE - Bit field value definitions  
*/
#define MMA865x_INT_SOURCE_SRC_ASLP_READY        ((uint8_t) 0x80)  /*  - An interrupt event that can cause a              */
                                                                   /*  WAKE-to-SLEEP or SLEEP-to-WAKE system mode         */
                                                                   /*  transition has occurred.                           */
#define MMA865x_INT_SOURCE_SRC_ASLP_INACTIVE     ((uint8_t) 0x00)  /*  - No WAKE-to-SLEEP or SLEEP-to-WAKE system mode    */
                                                                   /*  transition interrupt event has occurred.           */
#define MMA865x_INT_SOURCE_SRC_FIFO_READY        ((uint8_t) 0x40)  /*  - A FIFO interrupt event (such as an overflow      */
                                                                   /*  event or watermark) has occurred.                  */
#define MMA865x_INT_SOURCE_SRC_FIFO_INACTIVE     ((uint8_t) 0x00)  /*  - No FIFO interrupt event has occurred.            */
#define MMA865x_INT_SOURCE_SRC_TRANS_READY       ((uint8_t) 0x20)  /*  - An acceleration transient value greater than     */
                                                                   /*  user-specified threshold has occurred.             */
#define MMA865x_INT_SOURCE_SRC_TRANS_INACTIVE    ((uint8_t) 0x00)  /*  - No transient event has occurred.                 */
#define MMA865x_INT_SOURCE_SRC_LNDPRT_READY      ((uint8_t) 0x10)  /*  - An interrupt was generated due to a change in    */
                                                                   /*  the device orientation status.                     */
#define MMA865x_INT_SOURCE_SRC_LNDPRT_INACTIVE   ((uint8_t) 0x00)  /*  - No change in orientation status was detected.    */
#define MMA865x_INT_SOURCE_SRC_PULSE_READY       ((uint8_t) 0x08)  /*  - An interrupt was generated due to single and/or  */
                                                                   /*  double pulse event.                                */
#define MMA865x_INT_SOURCE_SRC_PULSE_INACTIVE    ((uint8_t) 0x00)  /*  - No pulse event was detected.                     */
#define MMA865x_INT_SOURCE_SRC_FF_MT_READY       ((uint8_t) 0x04)  /*  - The Freefall/Motion function interrupt is        */
                                                                   /*  active.                                            */
#define MMA865x_INT_SOURCE_SRC_FF_MT_INACTIVE    ((uint8_t) 0x00)  /*  - No Freefall or Motion event was detected.        */
#define MMA865x_INT_SOURCE_SRC_DRDY_READY        ((uint8_t) 0x01)  /*  - The X, Y, Z data ready interrupt is active.      */
#define MMA865x_INT_SOURCE_SRC_DRDY_INACTIVE     ((uint8_t) 0x00)  /*  - The X, Y, Z interrupt is not active.             */
/*------------------------------*/




/*--------------------------------
** Register: WHO_AM_I
** Enum: MMA865x_WHO_AM_I
** --
** Offset : 0x0D - Device identification register containing Fixed Device ID Number
** ------------------------------*/
typedef uint8_t MMA865x_WHO_AM_I_t;




/*--------------------------------
** Register: XYZ_DATA_CFG
** Enum: MMA865x_XYZ_DATA_CFG
** --
** Offset : 0x0E - Sets the dynamic range and sets the high-pass filter for the output data
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    fs : 2; /*  - Full-scale range selection.                                              */

        uint8_t _reserved_            : 2;
        uint8_t               hpf_out : 1; /*  - Enable high-pass output data.                                            */

    } b;
    uint8_t w;
} MMA865x_XYZ_DATA_CFG_t;


/*
** XYZ_DATA_CFG - Bit field mask definitions 
*/
#define MMA865x_XYZ_DATA_CFG_FS_MASK        ((uint8_t) 0x03)
#define MMA865x_XYZ_DATA_CFG_FS_SHIFT       ((uint8_t)    0)

#define MMA865x_XYZ_DATA_CFG_HPF_OUT_MASK   ((uint8_t) 0x10)
#define MMA865x_XYZ_DATA_CFG_HPF_OUT_SHIFT  ((uint8_t)    4)


/*
** XYZ_DATA_CFG - Bit field value definitions  
*/
#define MMA865x_XYZ_DATA_CFG_HPF_OUT_ENABLE        ((uint8_t) 0x10)  /*  - Output data is high-pass filtered.             */
#define MMA865x_XYZ_DATA_CFG_HPF_OUT_DISABLE       ((uint8_t) 0x00)  /*  - Output data is not high-pass filtered.         */
#define MMA865x_XYZ_DATA_CFG_FS_2G                 ((uint8_t) 0x00)  /*  - ±2 g.                                           */
#define MMA865x_XYZ_DATA_CFG_FS_4G                 ((uint8_t) 0x01)  /*  - ±4 g.                                           */
#define MMA865x_XYZ_DATA_CFG_FS_8G                 ((uint8_t) 0x02)  /*  - ±8 g.                                           */
/*------------------------------*/




/*--------------------------------
** Register: HP_FILTER_CUTOFF
** Enum: MMA865x_HP_FILTER_CUTOFF
** --
** Offset : 0x0F - High-Pass Filter register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   sel : 2; /*  - HPF cutoff frequency selection. This value depends on the OSR and ODR    */
                                           /*  (refer to Table 33 of data sheet for more details).                        */

        uint8_t _reserved_            : 2;
        uint8_t          pulse_lpf_en : 1; /*  - Enable Low-Pass Filter (LPF) for pulse processing function.              */

        uint8_t         pulse_hpf_byp : 1; /*  - Bypass High-Pass Filter (HPF) for pulse processing function.             */

    } b;
    uint8_t w;
} MMA865x_HP_FILTER_CUTOFF_t;


/*
** HP_FILTER_CUTOFF - Bit field mask definitions 
*/
#define MMA865x_HP_FILTER_CUTOFF_SEL_MASK             ((uint8_t) 0x03)
#define MMA865x_HP_FILTER_CUTOFF_SEL_SHIFT            ((uint8_t)    0)

#define MMA865x_HP_FILTER_CUTOFF_PULSE_LPF_EN_MASK    ((uint8_t) 0x10)
#define MMA865x_HP_FILTER_CUTOFF_PULSE_LPF_EN_SHIFT   ((uint8_t)    4)

#define MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_MASK   ((uint8_t) 0x20)
#define MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_SHIFT  ((uint8_t)    5)


/*
** HP_FILTER_CUTOFF - Bit field value definitions  
*/
#define MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_ENABLED ((uint8_t) 0x00)  /*  - HPF is enabled for pulse processing.       */
#define MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_BYPASSED ((uint8_t) 0x20)  /*  - HPF is bypassed for pulse processing.     */
#define MMA865x_HP_FILTER_CUTOFF_PULSE_LPF_EN_DISABLED ((uint8_t) 0x00)  /*  - LPF is disabled for pulse processing.      */
#define MMA865x_HP_FILTER_CUTOFF_PULSE_LPF_EN_ENABLED  ((uint8_t) 0x10)  /*  - LPF is enabled for pulse processing.       */
#define MMA865x_HP_FILTER_CUTOFF_SEL_VAL_0             ((uint8_t) 0x00)  /*  - Select 0 0                                 */
#define MMA865x_HP_FILTER_CUTOFF_SEL_VAL_1             ((uint8_t) 0x00)  /*  - Select 0 1                                 */
#define MMA865x_HP_FILTER_CUTOFF_SEL_VAL_2             ((uint8_t) 0x00)  /*  - Select 1 0                                 */
#define MMA865x_HP_FILTER_CUTOFF_SEL_VAL_3             ((uint8_t) 0x00)  /*  - Select 1 1                                 */
/*------------------------------*/




/*--------------------------------
** Register: PL_STATUS
** Enum: MMA865x_PL_STATUS
** --
** Offset : 0x10 - Portrait/Landscape Status register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 bafro : 1; /*  - Back or Front orientation.                                               */

        uint8_t                  lapo : 2; /*  - Landscape/Portrait orientation.                                          */

        uint8_t _reserved_            : 3;
        uint8_t                    lo : 1; /*  - Z-Tilt Angle Lockout.                                                    */

        uint8_t                 newlp : 1; /*  - Landscape/Portrait status change flag.                                   */

    } b;
    uint8_t w;
} MMA865x_PL_STATUS_t;


/*
** PL_STATUS - Bit field mask definitions 
*/
#define MMA865x_PL_STATUS_BAFRO_MASK   ((uint8_t) 0x01)
#define MMA865x_PL_STATUS_BAFRO_SHIFT  ((uint8_t)    0)

#define MMA865x_PL_STATUS_LAPO_MASK    ((uint8_t) 0x06)
#define MMA865x_PL_STATUS_LAPO_SHIFT   ((uint8_t)    1)

#define MMA865x_PL_STATUS_LO_MASK      ((uint8_t) 0x40)
#define MMA865x_PL_STATUS_LO_SHIFT     ((uint8_t)    6)

#define MMA865x_PL_STATUS_NEWLP_MASK   ((uint8_t) 0x80)
#define MMA865x_PL_STATUS_NEWLP_SHIFT  ((uint8_t)    7)


/*
** PL_STATUS - Bit field value definitions  
*/
#define MMA865x_PL_STATUS_NEWLP_NO_CHANGE       ((uint8_t) 0x00)  /*  - No change.                                        */
#define MMA865x_PL_STATUS_NEWLP_DETECTED        ((uint8_t) 0x80)  /*  - BAFRO and/or LAPO and/or Z-Tilt lockout value has */
                                                                  /*  changed.                                            */
#define MMA865x_PL_STATUS_LO_NOT_DETECTED       ((uint8_t) 0x00)  /*  - Lockout condition has not been detected.          */
#define MMA865x_PL_STATUS_LO_DETECTED           ((uint8_t) 0x40)  /*  - Z-Tilt lockout trip angle has been exceeded.      */
                                                                  /*  Lockout has been detected.                          */
#define MMA865x_PL_STATUS_LAPO_PORTRAIT_UP      ((uint8_t) 0x00)  /*  - Portrait Up: Equipment standing vertically in the */
                                                                  /*  normal orientation.                                 */
#define MMA865x_PL_STATUS_LAPO_PORTRAIT_DOWN    ((uint8_t) 0x02)  /*  - Portrait Down: Equipment standing vertically in   */
                                                                  /*  the inverted orientation.                           */
#define MMA865x_PL_STATUS_LAPO_LANDSCAPE_UP     ((uint8_t) 0x04)  /*  - Landscape Right: Equipment is in landscape mode   */
                                                                  /*  to the right.                                       */
#define MMA865x_PL_STATUS_LAPO_LANDSCAPE_DOWN   ((uint8_t) 0x06)  /*  - Landscape Left: Equipment is in landscape mode to */
                                                                  /*  the left.                                           */
#define MMA865x_PL_STATUS_BAFRO_FRONT           ((uint8_t) 0x00)  /*  - Front: Equipment is in the front-facing           */
                                                                  /*  orientation.                                        */
#define MMA865x_PL_STATUS_BAFRO_BACK            ((uint8_t) 0x01)  /*  - Back: Equipment is in the back-facing             */
                                                                  /*  orientation.                                        */
/*------------------------------*/




/*--------------------------------
** Register: PL_CFG
** Enum: MMA865x_PL_CFG
** --
** Offset : 0x11 - Portrait/Landscape Configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 6;
        uint8_t                 pl_en : 1; /*  - Portrait/Landscape detection enable.                                     */

        uint8_t                dbcntm : 1; /*  - Debounce counter mode selection.                                         */

    } b;
    uint8_t w;
} MMA865x_PL_CFG_t;


/*
** PL_CFG - Bit field mask definitions 
*/
#define MMA865x_PL_CFG_PL_EN_MASK    ((uint8_t) 0x40)
#define MMA865x_PL_CFG_PL_EN_SHIFT   ((uint8_t)    6)

#define MMA865x_PL_CFG_DBCNTM_MASK   ((uint8_t) 0x80)
#define MMA865x_PL_CFG_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** PL_CFG - Bit field value definitions  
*/
#define MMA865x_PL_CFG_DBCNTM_DECREMENT      ((uint8_t) 0x00)  /*  - Decrements debounce whenever the condition of        */
                                                               /*  interest is no longer valid.                           */
#define MMA865x_PL_CFG_DBCNTM_CLEAR          ((uint8_t) 0x80)  /*  - Clears the counter whenever the condition of         */
                                                               /*  interest is no longer valid.                           */
#define MMA865x_PL_CFG_PL_EN_DISABLED        ((uint8_t) 0x00)  /*  - Portrait/Landscape Detection is disabled.            */
#define MMA865x_PL_CFG_PL_EN_EN              ((uint8_t) 0x40)  /*  - Portrait/Landscape Detection is enabled.             */
/*------------------------------*/




/*--------------------------------
** Register: PL_COUNT
** Enum: MMA865x_PL_COUNT
** --
** Offset : 0x12 - Portrait/Landscape Debounce register
** ------------------------------*/
typedef uint8_t MMA865x_PL_COUNT_t;




/*--------------------------------
** Register: PL_BF_ZCOMP
** Enum: MMA865x_PL_BF_ZCOMP
** --
** Offset : 0x13 - Back/Front and Z Compensation register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 zlock : 3; /*  - Z-lock angle threshold (Step size is 4 and Range is from 14 to 43).      */

        uint8_t _reserved_            : 3;
        uint8_t                  bkfr : 2; /*  - Back/Front trip angle threshold (Step size = 5 and Range = (65 to 80)).  */

    } b;
    uint8_t w;
} MMA865x_PL_BF_ZCOMP_t;


/*
** PL_BF_ZCOMP - Bit field mask definitions 
*/
#define MMA865x_PL_BF_ZCOMP_ZLOCK_MASK   ((uint8_t) 0x07)
#define MMA865x_PL_BF_ZCOMP_ZLOCK_SHIFT  ((uint8_t)    0)

#define MMA865x_PL_BF_ZCOMP_BKFR_MASK    ((uint8_t) 0xC0)
#define MMA865x_PL_BF_ZCOMP_BKFR_SHIFT   ((uint8_t)    6)


/*
** PL_BF_ZCOMP - Bit field value definitions  
*/
#define MMA865x_PL_BF_ZCOMP_BKFR_VAL_0            ((uint8_t) 0x00)  /*  - Back/Front Transition : 00 Z < 80° or Z > 280°    */
                                                                    /*  and Front/Back Transition : Z > 100° and Z < 260°.  */
#define MMA865x_PL_BF_ZCOMP_BKFR_VAL_1            ((uint8_t) 0x40)  /*  - Back/Front Transition : 01 Z < 75° or Z > 285°    */
                                                                    /*  and Front/Back Transition : Z > 105° and Z < 255°.  */
#define MMA865x_PL_BF_ZCOMP_BKFR_VAL_2            ((uint8_t) 0x80)  /*  - Back/Front Transition : 10 Z < 70° or Z > 290°    */
                                                                    /*  and Front/Back Transition : Z > 110° and Z < 250°.  */
#define MMA865x_PL_BF_ZCOMP_BKFR_VAL_3            ((uint8_t) 0xc0)  /*  - Back/Front Transition : 11 Z < 65° or Z > 295°    */
                                                                    /*  and Front/Back Transition : Z > 115° and Z < 245°.  */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_14          ((uint8_t) 0x00)  /*  - Threshold Angle = 14°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_18          ((uint8_t) 0x01)  /*  - Threshold Angle = 18°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_21          ((uint8_t) 0x02)  /*  - Threshold Angle = 21°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_25          ((uint8_t) 0x03)  /*  - Threshold Angle = 25°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_29          ((uint8_t) 0x04)  /*  - Threshold Angle = 29°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_33          ((uint8_t) 0x05)  /*  - Threshold Angle = 33°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_37          ((uint8_t) 0x06)  /*  - Threshold Angle = 37°.                           */
#define MMA865x_PL_BF_ZCOMP_ZLOCK_VAL_42          ((uint8_t) 0x07)  /*  - Threshold Angle = 42°.                           */
/*------------------------------*/




/*--------------------------------
** Register: P_L_THS_REG
** Enum: MMA865x_P_L_THS_REG
** --
** Offset : 0x14 - Portrait/Landscape Threshold and Hysteresis register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   hys : 3; /*  - Hysteresis value : This angle is added to the threshold angle, for a     */
                                           /*  smoother transition from portrait to landscape and landscape to portrait.  */
                                           /*  This angle ranges from 0 to 24.                                            */

        uint8_t               p_l_ths : 5; /*  - Portrait/Landscape trip threshold angle (from 15 to 75).                 */

    } b;
    uint8_t w;
} MMA865x_P_L_THS_REG_t;


/*
** P_L_THS_REG - Bit field mask definitions 
*/
#define MMA865x_P_L_THS_REG_HYS_MASK       ((uint8_t) 0x07)
#define MMA865x_P_L_THS_REG_HYS_SHIFT      ((uint8_t)    0)

#define MMA865x_P_L_THS_REG_P_L_THS_MASK   ((uint8_t) 0xF8)
#define MMA865x_P_L_THS_REG_P_L_THS_SHIFT  ((uint8_t)    3)


/*
** P_L_THS_REG - Bit field value definitions  
*/
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_15        ((uint8_t) 0x38)  /*  - Threshold Angle = 15°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_20        ((uint8_t) 0x48)  /*  - Threshold Angle = 20°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_30        ((uint8_t) 0x60)  /*  - Threshold Angle = 30°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_35        ((uint8_t) 0x68)  /*  - Threshold Angle = 35°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_40        ((uint8_t) 0x78)  /*  - Threshold Angle = 40°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_45        ((uint8_t) 0x80)  /*  - Threshold Angle = 45°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_55        ((uint8_t) 0x98)  /*  - Threshold Angle = 55°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_60        ((uint8_t) 0xa0)  /*  - Threshold Angle = 60°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_70        ((uint8_t) 0xb8)  /*  - Threshold Angle = 70°                            */
#define MMA865x_P_L_THS_REG_P_L_THS_VAL_75        ((uint8_t) 0xc8)  /*  - Threshold Angle = 75°                            */
#define MMA865x_P_L_THS_REG_HYS_VAL_0             ((uint8_t) 0x00)  /*  - Hysteresis ± Angle Range = ±0                    */
#define MMA865x_P_L_THS_REG_HYS_VAL_1             ((uint8_t) 0x01)  /*  - Hysteresis ± Angle Range = ±4                    */
#define MMA865x_P_L_THS_REG_HYS_VAL_2             ((uint8_t) 0x02)  /*  - Hysteresis ± Angle Range = ±7                    */
#define MMA865x_P_L_THS_REG_HYS_VAL_3             ((uint8_t) 0x03)  /*  - Hysteresis ± Angle Range = ±11                   */
#define MMA865x_P_L_THS_REG_HYS_VAL_4             ((uint8_t) 0x04)  /*  - Hysteresis ± Angle Range = ±14                   */
#define MMA865x_P_L_THS_REG_HYS_VAL_5             ((uint8_t) 0x05)  /*  - Hysteresis ± Angle Range = ±17                   */
#define MMA865x_P_L_THS_REG_HYS_VAL_6             ((uint8_t) 0x06)  /*  - Hysteresis ± Angle Range = ±21                   */
#define MMA865x_P_L_THS_REG_HYS_VAL_7             ((uint8_t) 0x07)  /*  - Hysteresis ± Angle Range = ±24                   */
/*------------------------------*/




/*--------------------------------
** Register: FF_MT_CFG
** Enum: MMA865x_FF_MT_CFG
** --
** Offset : 0x15 - Freefall/Motion Configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 3;
        uint8_t                  xefe : 1; /*  - Event flag enable on X event.                                            */

        uint8_t                  yefe : 1; /*  - Event flag enable on Y event.                                            */

        uint8_t                  zefe : 1; /*  - Event flag enable on Z.                                                  */

        uint8_t                   oae : 1; /*  - Motion detect / Freefall detect flag selection.                          */

        uint8_t                   ele : 1; /*  - Event Latch Enable: Event flags are latched into FF_MT_SRC register.     */

    } b;
    uint8_t w;
} MMA865x_FF_MT_CFG_t;


/*
** FF_MT_CFG - Bit field mask definitions 
*/
#define MMA865x_FF_MT_CFG_XEFE_MASK   ((uint8_t) 0x08)
#define MMA865x_FF_MT_CFG_XEFE_SHIFT  ((uint8_t)    3)

#define MMA865x_FF_MT_CFG_YEFE_MASK   ((uint8_t) 0x10)
#define MMA865x_FF_MT_CFG_YEFE_SHIFT  ((uint8_t)    4)

#define MMA865x_FF_MT_CFG_ZEFE_MASK   ((uint8_t) 0x20)
#define MMA865x_FF_MT_CFG_ZEFE_SHIFT  ((uint8_t)    5)

#define MMA865x_FF_MT_CFG_OAE_MASK    ((uint8_t) 0x40)
#define MMA865x_FF_MT_CFG_OAE_SHIFT   ((uint8_t)    6)

#define MMA865x_FF_MT_CFG_ELE_MASK    ((uint8_t) 0x80)
#define MMA865x_FF_MT_CFG_ELE_SHIFT   ((uint8_t)    7)


/*
** FF_MT_CFG - Bit field value definitions  
*/
#define MMA865x_FF_MT_CFG_ELE_DISABLED          ((uint8_t) 0x00)  /*  - Event flag latch disabled.                        */
#define MMA865x_FF_MT_CFG_ELE_EN                ((uint8_t) 0x80)  /*  - Event flag latch enabled.                         */
#define MMA865x_FF_MT_CFG_OAE_FREEFALL          ((uint8_t) 0x00)  /*  - Freefall flag (Logical AND combination).          */
#define MMA865x_FF_MT_CFG_OAE_MOTION            ((uint8_t) 0x40)  /*  - Motion flag (Logical OR combination).             */
#define MMA865x_FF_MT_CFG_ZEFE_DISABLED         ((uint8_t) 0x00)  /*  - Event detection disabled.                         */
#define MMA865x_FF_MT_CFG_ZEFE_EN               ((uint8_t) 0x20)  /*  - Raise event flag on measured acceleration value   */
                                                                  /*  beyond preset threshold.                            */
#define MMA865x_FF_MT_CFG_YEFE_DISABLED         ((uint8_t) 0x00)  /*  - Event detection disabled.                         */
#define MMA865x_FF_MT_CFG_YEFE_EN               ((uint8_t) 0x10)  /*  - Raise event flag on measured acceleration value   */
                                                                  /*  beyond preset threshold.                            */
#define MMA865x_FF_MT_CFG_XEFE_DISABLED         ((uint8_t) 0x00)  /*  - Event detection disabled.                         */
#define MMA865x_FF_MT_CFG_XEFE_EN               ((uint8_t) 0x08)  /*  - Raise event flag on measured acceleration value   */
                                                                  /*  beyond preset threshold.                            */
/*------------------------------*/




/*--------------------------------
** Register: FF_MT_SRC
** Enum: MMA865x_FF_MT_SRC
** --
** Offset : 0x16 - Freefall/Motion Source register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xhp : 1; /*  - X-Motion Polarity Flag.                                                  */

        uint8_t                   xhe : 1; /*  - X-Motion Flag.                                                           */

        uint8_t                   yhp : 1; /*  - Y-Motion Polarity Flag.                                                  */

        uint8_t                   yhe : 1; /*  - Y-Motion Flag.                                                           */

        uint8_t                   zhp : 1; /*  - Z-Motion Polarity Flag.                                                  */

        uint8_t                   zhe : 1; /*  - Z-Motion flag.                                                           */

        uint8_t _reserved_            : 1;
        uint8_t                    ea : 1; /*  - Event Active flag.                                                       */

    } b;
    uint8_t w;
} MMA865x_FF_MT_SRC_t;


/*
** FF_MT_SRC - Bit field mask definitions 
*/
#define MMA865x_FF_MT_SRC_XHP_MASK   ((uint8_t) 0x01)
#define MMA865x_FF_MT_SRC_XHP_SHIFT  ((uint8_t)    0)

#define MMA865x_FF_MT_SRC_XHE_MASK   ((uint8_t) 0x02)
#define MMA865x_FF_MT_SRC_XHE_SHIFT  ((uint8_t)    1)

#define MMA865x_FF_MT_SRC_YHP_MASK   ((uint8_t) 0x04)
#define MMA865x_FF_MT_SRC_YHP_SHIFT  ((uint8_t)    2)

#define MMA865x_FF_MT_SRC_YHE_MASK   ((uint8_t) 0x08)
#define MMA865x_FF_MT_SRC_YHE_SHIFT  ((uint8_t)    3)

#define MMA865x_FF_MT_SRC_ZHP_MASK   ((uint8_t) 0x10)
#define MMA865x_FF_MT_SRC_ZHP_SHIFT  ((uint8_t)    4)

#define MMA865x_FF_MT_SRC_ZHE_MASK   ((uint8_t) 0x20)
#define MMA865x_FF_MT_SRC_ZHE_SHIFT  ((uint8_t)    5)

#define MMA865x_FF_MT_SRC_EA_MASK    ((uint8_t) 0x80)
#define MMA865x_FF_MT_SRC_EA_SHIFT   ((uint8_t)    7)


/*
** FF_MT_SRC - Bit field value definitions  
*/
#define MMA865x_FF_MT_SRC_EA_NONE               ((uint8_t) 0x00)  /*  - No event flag has been asserted.                  */
#define MMA865x_FF_MT_SRC_EA_DETECTED           ((uint8_t) 0x80)  /*  - One or more event flags has been asserted.        */
#define MMA865x_FF_MT_SRC_ZHE_NONE              ((uint8_t) 0x00)  /*  - No Z motion event detected.                       */
#define MMA865x_FF_MT_SRC_ZHE_DETECTED          ((uint8_t) 0x20)  /*  - Z motion has been detected.                       */
#define MMA865x_FF_MT_SRC_ZHP_POSITIVE          ((uint8_t) 0x00)  /*  - Z event was positive g.                           */
#define MMA865x_FF_MT_SRC_ZHP_NEGATIVE          ((uint8_t) 0x10)  /*  - Z event was negative g.                           */
#define MMA865x_FF_MT_SRC_YHE_NONE              ((uint8_t) 0x00)  /*  - No Y motion event detected.                       */
#define MMA865x_FF_MT_SRC_YHE_DETECTED          ((uint8_t) 0x08)  /*  - Y motion has been detected.                       */
#define MMA865x_FF_MT_SRC_YHP_POSITIVE          ((uint8_t) 0x00)  /*  - Y event detected was positive g.                  */
#define MMA865x_FF_MT_SRC_YHP_NEGATIVE          ((uint8_t) 0x04)  /*  - Y event was negative g.                           */
#define MMA865x_FF_MT_SRC_XHE_NONE              ((uint8_t) 0x00)  /*  - No X motion event detected.                       */
#define MMA865x_FF_MT_SRC_XHE_DETECTED          ((uint8_t) 0x02)  /*  - X motion has been detected.                       */
#define MMA865x_FF_MT_SRC_XHP_POSITIVE          ((uint8_t) 0x00)  /*  - X event was positive g.                           */
#define MMA865x_FF_MT_SRC_XHP_NEGATIVE          ((uint8_t) 0x01)  /*  - X event was negative g.                           */
/*------------------------------*/




/*--------------------------------
** Register: FF_MT_THS
** Enum: MMA865x_FF_MT_THS
** --
** Offset : 0x17 - Freefall and Motion Threshold register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   ths : 7; /*  - Freefall /Motion Threshold.                                              */

        uint8_t                dbcntm : 1; /*  - Debounce counter mode selection.                                         */

    } b;
    uint8_t w;
} MMA865x_FF_MT_THS_t;


/*
** FF_MT_THS - Bit field mask definitions 
*/
#define MMA865x_FF_MT_THS_THS_MASK      ((uint8_t) 0x7F)
#define MMA865x_FF_MT_THS_THS_SHIFT     ((uint8_t)    0)

#define MMA865x_FF_MT_THS_DBCNTM_MASK   ((uint8_t) 0x80)
#define MMA865x_FF_MT_THS_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** FF_MT_THS - Bit field value definitions  
*/
#define MMA865x_FF_MT_THS_DBCNTM_INC_DEC        ((uint8_t) 0x00)  /*  - Increments or decrements debounce.                */
#define MMA865x_FF_MT_THS_DBCNTM_INC_CLR        ((uint8_t) 0x80)  /*  - Increments or clears counter.                     */
/*------------------------------*/




/*--------------------------------
** Register: FF_MT_COUNT
** Enum: MMA865x_FF_MT_COUNT
** --
** Offset : 0x18 - Debounce register
** ------------------------------*/
typedef uint8_t MMA865x_FF_MT_COUNT_t;




/*--------------------------------
** Register: TRANSIENT_CFG
** Enum: MMA865x_TRANSIENT_CFG
** --
** Offset : 0x1D - Transient Configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t               hpf_byp : 1; /*  - Bypass high-pass filter.                                                 */

        uint8_t                 xtefe : 1; /*  - Event flag enable for X-transient acceleration greater than a transient  */
                                           /*  threshold event.                                                           */

        uint8_t                 ytefe : 1; /*  - Event flag enable for Y-transient acceleration greater than a transient  */
                                           /*  threshold event.                                                           */

        uint8_t                 ztefe : 1; /*  - Event flag enable for Z-transient acceleration greater than a transient  */
                                           /*  threshold event.                                                           */

        uint8_t                   ele : 1; /*  - Transient event flags are latched into the TRANSIENT_SRC register.       */

    } b;
    uint8_t w;
} MMA865x_TRANSIENT_CFG_t;


/*
** TRANSIENT_CFG - Bit field mask definitions 
*/
#define MMA865x_TRANSIENT_CFG_HPF_BYP_MASK   ((uint8_t) 0x01)
#define MMA865x_TRANSIENT_CFG_HPF_BYP_SHIFT  ((uint8_t)    0)

#define MMA865x_TRANSIENT_CFG_XTEFE_MASK     ((uint8_t) 0x02)
#define MMA865x_TRANSIENT_CFG_XTEFE_SHIFT    ((uint8_t)    1)

#define MMA865x_TRANSIENT_CFG_YTEFE_MASK     ((uint8_t) 0x04)
#define MMA865x_TRANSIENT_CFG_YTEFE_SHIFT    ((uint8_t)    2)

#define MMA865x_TRANSIENT_CFG_ZTEFE_MASK     ((uint8_t) 0x08)
#define MMA865x_TRANSIENT_CFG_ZTEFE_SHIFT    ((uint8_t)    3)

#define MMA865x_TRANSIENT_CFG_ELE_MASK       ((uint8_t) 0x10)
#define MMA865x_TRANSIENT_CFG_ELE_SHIFT      ((uint8_t)    4)


/*
** TRANSIENT_CFG - Bit field value definitions  
*/
#define MMA865x_TRANSIENT_CFG_ELE_DISABLED          ((uint8_t) 0x00)  /*  - Event flag latch disabled.                    */
#define MMA865x_TRANSIENT_CFG_ELE_EN                ((uint8_t) 0x10)  /*  - Event flag latch enabled.                     */
#define MMA865x_TRANSIENT_CFG_ZTEFE_DISABLED        ((uint8_t) 0x00)  /*  - Event detection disabled.                     */
#define MMA865x_TRANSIENT_CFG_ZTEFE_EN              ((uint8_t) 0x08)  /*  - Raise event flag on measured acceleration     */
                                                                      /*  delta value that is greater than a transient    */
                                                                      /*  threshold.                                      */
#define MMA865x_TRANSIENT_CFG_YTEFE_DISABLED        ((uint8_t) 0x00)  /*  - Event detection disabled.                     */
#define MMA865x_TRANSIENT_CFG_YTEFE_EN              ((uint8_t) 0x04)  /*  - Raise event flag on measured acceleration     */
                                                                      /*  delta value that is greater than a transient    */
                                                                      /*  threshold.                                      */
#define MMA865x_TRANSIENT_CFG_XTEFE_DISABLED        ((uint8_t) 0x00)  /*  - Event detection disabled.                     */
#define MMA865x_TRANSIENT_CFG_XTEFE_EN              ((uint8_t) 0x02)  /*  - Raise event flag on measured acceleration     */
                                                                      /*  delta value that is greater than a transient    */
                                                                      /*  threshold.                                      */
#define MMA865x_TRANSIENT_CFG_HPF_BYP_THROUGH_HPF   ((uint8_t) 0x00)  /*  - Data to transient acceleration detection      */
                                                                      /*  block is through HPF.                           */
#define MMA865x_TRANSIENT_CFG_HPF_BYP_NOT_HPF       ((uint8_t) 0x01)  /*  - Data to transient acceleration detection      */
                                                                      /*  block is NOT Through HPF.                       */
/*------------------------------*/




/*--------------------------------
** Register: TRANSIENT_SRC
** Enum: MMA865x_TRANSIENT_SRC
** --
** Offset : 0x1E - Transient Source register
** ------------------------------*/
typedef union {
    struct {
        uint8_t           x_trans_pol : 1; /*  - Polarity of X-Transient Event that triggered the interrupt.              */

        uint8_t               xtranse : 1; /*  - X-transient event.                                                       */

        uint8_t           y_trans_pol : 1; /*  - Polarity of Y-Transient Event that triggered the interrupt.              */

        uint8_t               ytranse : 1; /*  - Y-transient event.                                                       */

        uint8_t           z_trans_pol : 1; /*  - Polarity of Z-Transient Event that triggered the interrupt.              */

        uint8_t               ztranse : 1; /*  - Z-transient event.                                                       */

        uint8_t                    ea : 1; /*  - Event Active Flag.                                                       */

    } b;
    uint8_t w;
} MMA865x_TRANSIENT_SRC_t;


/*
** TRANSIENT_SRC - Bit field mask definitions 
*/
#define MMA865x_TRANSIENT_SRC_X_TRANS_POL_MASK   ((uint8_t) 0x01)
#define MMA865x_TRANSIENT_SRC_X_TRANS_POL_SHIFT  ((uint8_t)    0)

#define MMA865x_TRANSIENT_SRC_XTRANSE_MASK       ((uint8_t) 0x02)
#define MMA865x_TRANSIENT_SRC_XTRANSE_SHIFT      ((uint8_t)    1)

#define MMA865x_TRANSIENT_SRC_Y_TRANS_POL_MASK   ((uint8_t) 0x04)
#define MMA865x_TRANSIENT_SRC_Y_TRANS_POL_SHIFT  ((uint8_t)    2)

#define MMA865x_TRANSIENT_SRC_YTRANSE_MASK       ((uint8_t) 0x08)
#define MMA865x_TRANSIENT_SRC_YTRANSE_SHIFT      ((uint8_t)    3)

#define MMA865x_TRANSIENT_SRC_Z_TRANS_POL_MASK   ((uint8_t) 0x10)
#define MMA865x_TRANSIENT_SRC_Z_TRANS_POL_SHIFT  ((uint8_t)    4)

#define MMA865x_TRANSIENT_SRC_ZTRANSE_MASK       ((uint8_t) 0x20)
#define MMA865x_TRANSIENT_SRC_ZTRANSE_SHIFT      ((uint8_t)    5)

#define MMA865x_TRANSIENT_SRC_EA_MASK            ((uint8_t) 0x40)
#define MMA865x_TRANSIENT_SRC_EA_SHIFT           ((uint8_t)    6)


/*
** TRANSIENT_SRC - Bit field value definitions  
*/
#define MMA865x_TRANSIENT_SRC_EA_NONE               ((uint8_t) 0x00)  /*  - No event flag has been asserted.              */
#define MMA865x_TRANSIENT_SRC_EA_DETECTED           ((uint8_t) 0x40)  /*  - One or more event flags has been asserted.    */
#define MMA865x_TRANSIENT_SRC_ZTRANSE_NONE          ((uint8_t) 0x00)  /*  - No interrupt.                                 */
#define MMA865x_TRANSIENT_SRC_ZTRANSE_DETECTED      ((uint8_t) 0x20)  /*  - Z-transient acceleration greater than the     */
                                                                      /*  value of TRANSIENT_THS event has occurred.      */
#define MMA865x_TRANSIENT_SRC_Z_TRANS_POL_POSITIVE  ((uint8_t) 0x00)  /*  - Z-event was positive g.                       */
#define MMA865x_TRANSIENT_SRC_Z_TRANS_POL_NEGATIVE  ((uint8_t) 0x10)  /*  - Z-event was negative g.                       */
#define MMA865x_TRANSIENT_SRC_YTRANSE_NONE          ((uint8_t) 0x00)  /*  - No interrupt.                                 */
#define MMA865x_TRANSIENT_SRC_YTRANSE_DETECTED      ((uint8_t) 0x08)  /*  - Y-transient acceleration greater than the     */
                                                                      /*  value of TRANSIENT_THS event has occurred.      */
#define MMA865x_TRANSIENT_SRC_Y_TRANS_POL_POSITIVE  ((uint8_t) 0x00)  /*  - Y-event was Positive g.                       */
#define MMA865x_TRANSIENT_SRC_Y_TRANS_POL_NEGATIVE  ((uint8_t) 0x04)  /*  - Y-event was Negative g.                       */
#define MMA865x_TRANSIENT_SRC_XTRANSE_NONE          ((uint8_t) 0x00)  /*  - No interrupt.                                 */
#define MMA865x_TRANSIENT_SRC_XTRANSE_DETECTED      ((uint8_t) 0x02)  /*  - X-transient acceleration greater than the     */
                                                                      /*  value of TRANSIENT_THS event has occurred.      */
#define MMA865x_TRANSIENT_SRC_X_TRANS_POL_POSITIVE  ((uint8_t) 0x00)  /*  - X-event was Positive g.                       */
#define MMA865x_TRANSIENT_SRC_X_TRANS_POL_NEGATIVE  ((uint8_t) 0x01)  /*  - X-event was Negative g.                       */
/*------------------------------*/




/*--------------------------------
** Register: TRANSIENT_THS
** Enum: MMA865x_TRANSIENT_THS
** --
** Offset : 0x1F - Transient threshold register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   ths : 7; /*  - Transient Threshold (A 7-bit unsigned number, with 0.063 g/LSB. The      */
                                           /*  maximum threshold is 8 g).                                                 */

        uint8_t                dbcntm : 1; /*  - Debounce counter mode selection.                                         */

    } b;
    uint8_t w;
} MMA865x_TRANSIENT_THS_t;


/*
** TRANSIENT_THS - Bit field mask definitions 
*/
#define MMA865x_TRANSIENT_THS_THS_MASK      ((uint8_t) 0x7F)
#define MMA865x_TRANSIENT_THS_THS_SHIFT     ((uint8_t)    0)

#define MMA865x_TRANSIENT_THS_DBCNTM_MASK   ((uint8_t) 0x80)
#define MMA865x_TRANSIENT_THS_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** TRANSIENT_THS - Bit field value definitions  
*/
#define MMA865x_TRANSIENT_THS_DBCNTM_INC_DEC        ((uint8_t) 0x00)  /*  - Increments or decrements debounce.            */
#define MMA865x_TRANSIENT_THS_DBCNTM_INC_CLR        ((uint8_t) 0x80)  /*  - Increments or clears counter.                 */
/*------------------------------*/




/*--------------------------------
** Register: TRANSIENT_COUNT
** Enum: MMA865x_TRANSIENT_COUNT
** --
** Offset : 0x20 - Transient count register
** ------------------------------*/
typedef uint8_t MMA865x_TRANSIENT_COUNT_t;




/*--------------------------------
** Register: PULSE_CFG
** Enum: MMA865x_PULSE_CFG
** --
** Offset : 0x21 - Pulse configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                xspefe : 1; /*  - Event flag enable for a single pulse event on X-axis.                    */

        uint8_t                xdpefe : 1; /*  - Event flag enable for a double pulse event on X-axis.                    */

        uint8_t                yspefe : 1; /*  - Event flag enable for a single pulse event on Y-axis.                    */

        uint8_t                ydpefe : 1; /*  - Event flag enable for a double pulse event on Y-axis.                    */

        uint8_t                zspefe : 1; /*  - Event flag enable for a single pulse event on Z-axis.                    */

        uint8_t                zdpefe : 1; /*  - Event flag enable for a double pulse event on Z-axis.                    */

        uint8_t                   ele : 1; /*  - Pulse event flags are latched into the PULSE_SRC register.               */

        uint8_t                   dpa : 1; /*  - Double Pulse Abort.                                                      */

    } b;
    uint8_t w;
} MMA865x_PULSE_CFG_t;


/*
** PULSE_CFG - Bit field mask definitions 
*/
#define MMA865x_PULSE_CFG_XSPEFE_MASK   ((uint8_t) 0x01)
#define MMA865x_PULSE_CFG_XSPEFE_SHIFT  ((uint8_t)    0)

#define MMA865x_PULSE_CFG_XDPEFE_MASK   ((uint8_t) 0x02)
#define MMA865x_PULSE_CFG_XDPEFE_SHIFT  ((uint8_t)    1)

#define MMA865x_PULSE_CFG_YSPEFE_MASK   ((uint8_t) 0x04)
#define MMA865x_PULSE_CFG_YSPEFE_SHIFT  ((uint8_t)    2)

#define MMA865x_PULSE_CFG_YDPEFE_MASK   ((uint8_t) 0x08)
#define MMA865x_PULSE_CFG_YDPEFE_SHIFT  ((uint8_t)    3)

#define MMA865x_PULSE_CFG_ZSPEFE_MASK   ((uint8_t) 0x10)
#define MMA865x_PULSE_CFG_ZSPEFE_SHIFT  ((uint8_t)    4)

#define MMA865x_PULSE_CFG_ZDPEFE_MASK   ((uint8_t) 0x20)
#define MMA865x_PULSE_CFG_ZDPEFE_SHIFT  ((uint8_t)    5)

#define MMA865x_PULSE_CFG_ELE_MASK      ((uint8_t) 0x40)
#define MMA865x_PULSE_CFG_ELE_SHIFT     ((uint8_t)    6)

#define MMA865x_PULSE_CFG_DPA_MASK      ((uint8_t) 0x80)
#define MMA865x_PULSE_CFG_DPA_SHIFT     ((uint8_t)    7)


/*
** PULSE_CFG - Bit field value definitions  
*/
#define MMA865x_PULSE_CFG_DPA_NOT_ABORTED       ((uint8_t) 0x00)  /*  - Double Pulse detection is not aborted if the      */
                                                                  /*  start of a pulse is detected during the time period */
                                                                  /*  specified by the PULSE_LTCY register.               */
#define MMA865x_PULSE_CFG_DPA_SUSPENDED         ((uint8_t) 0x80)  /*  - Setting the DPA bit momentarily suspends the      */
                                                                  /*  double tap detection if the start of a pulse is     */
                                                                  /*  detected during the time period specified by the    */
                                                                  /*  PULSE_LTCY register, and the pulse ends before the  */
                                                                  /*  end of the time period specified by the PULSE_LTCY  */
                                                                  /*  register.                                           */
#define MMA865x_PULSE_CFG_ELE_DISABLED          ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_ELE_EN                ((uint8_t) 0x40)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_ZDPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_ZDPEFE_EN             ((uint8_t) 0x20)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_ZSPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_ZSPEFE_EN             ((uint8_t) 0x10)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_YDPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_YDPEFE_EN             ((uint8_t) 0x08)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_YSPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_YSPEFE_EN             ((uint8_t) 0x04)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_XDPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_XDPEFE_EN             ((uint8_t) 0x02)  /*  - Event detection is enabled.                       */
#define MMA865x_PULSE_CFG_XSPEFE_DISABLED       ((uint8_t) 0x00)  /*  - Event detection is disabled.                      */
#define MMA865x_PULSE_CFG_XSPEFE_EN             ((uint8_t) 0x01)  /*  - Event detection is enabled.                       */
/*------------------------------*/




/*--------------------------------
** Register: PULSE_SRC
** Enum: MMA865x_PULSE_SRC
** --
** Offset : 0x22 - Pulse source register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 pol_x : 1; /*  - Pulse polarity of X-axis event.                                          */

        uint8_t                 pol_y : 1; /*  - Pulse polarity of Y-axis event.                                          */

        uint8_t                 pol_z : 1; /*  - Pulse polarity of Z-axis event.                                          */

        uint8_t                   dpe : 1; /*  - Double pulse on first event.                                             */

        uint8_t                   axx : 1; /*  - X-axis event.                                                            */

        uint8_t                   axy : 1; /*  - Y-axis event.                                                            */

        uint8_t                   axz : 1; /*  - Z-axis event.                                                            */

        uint8_t                    ea : 1; /*  - Event Active Flag.                                                       */

    } b;
    uint8_t w;
} MMA865x_PULSE_SRC_t;


/*
** PULSE_SRC - Bit field mask definitions 
*/
#define MMA865x_PULSE_SRC_POL_X_MASK   ((uint8_t) 0x01)
#define MMA865x_PULSE_SRC_POL_X_SHIFT  ((uint8_t)    0)

#define MMA865x_PULSE_SRC_POL_Y_MASK   ((uint8_t) 0x02)
#define MMA865x_PULSE_SRC_POL_Y_SHIFT  ((uint8_t)    1)

#define MMA865x_PULSE_SRC_POL_Z_MASK   ((uint8_t) 0x04)
#define MMA865x_PULSE_SRC_POL_Z_SHIFT  ((uint8_t)    2)

#define MMA865x_PULSE_SRC_DPE_MASK     ((uint8_t) 0x08)
#define MMA865x_PULSE_SRC_DPE_SHIFT    ((uint8_t)    3)

#define MMA865x_PULSE_SRC_AXX_MASK     ((uint8_t) 0x10)
#define MMA865x_PULSE_SRC_AXX_SHIFT    ((uint8_t)    4)

#define MMA865x_PULSE_SRC_AXY_MASK     ((uint8_t) 0x20)
#define MMA865x_PULSE_SRC_AXY_SHIFT    ((uint8_t)    5)

#define MMA865x_PULSE_SRC_AXZ_MASK     ((uint8_t) 0x40)
#define MMA865x_PULSE_SRC_AXZ_SHIFT    ((uint8_t)    6)

#define MMA865x_PULSE_SRC_EA_MASK      ((uint8_t) 0x80)
#define MMA865x_PULSE_SRC_EA_SHIFT     ((uint8_t)    7)


/*
** PULSE_SRC - Bit field value definitions  
*/
#define MMA865x_PULSE_SRC_EA_NONE               ((uint8_t) 0x00)  /*  - No interrupt has been generated.                  */
#define MMA865x_PULSE_SRC_EA_DETECTED           ((uint8_t) 0x80)  /*  - One or more interrupt events have been generated. */
#define MMA865x_PULSE_SRC_AXZ_NONE              ((uint8_t) 0x00)  /*  - No interrupt.                                     */
#define MMA865x_PULSE_SRC_AXZ_DETECTED          ((uint8_t) 0x40)  /*  - Z-axis event has occurred.                        */
#define MMA865x_PULSE_SRC_AXY_NONE              ((uint8_t) 0x00)  /*  - No interrupt.                                     */
#define MMA865x_PULSE_SRC_AXY_DETECTED          ((uint8_t) 0x20)  /*  - Y-axis event has occurred.                        */
#define MMA865x_PULSE_SRC_AXX_NONE              ((uint8_t) 0x00)  /*  - No interrupt.                                     */
#define MMA865x_PULSE_SRC_AXX_DETECTED          ((uint8_t) 0x10)  /*  - X-axis event has occurred.                        */
#define MMA865x_PULSE_SRC_DPE_SINGLE            ((uint8_t) 0x00)  /*  - Single pulse event triggered interrupt.           */
#define MMA865x_PULSE_SRC_DPE_DOUBLE            ((uint8_t) 0x08)  /*  - Double pulse event triggered interrupt.           */
#define MMA865x_PULSE_SRC_POL_Z_POSITIVE        ((uint8_t) 0x00)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  positive.                                           */
#define MMA865x_PULSE_SRC_POL_Z_NEGATIVE        ((uint8_t) 0x04)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  negative.                                           */
#define MMA865x_PULSE_SRC_POL_Y_POSITIVE        ((uint8_t) 0x00)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  positive.                                           */
#define MMA865x_PULSE_SRC_POL_Y_NEGATIVE        ((uint8_t) 0x02)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  negative.                                           */
#define MMA865x_PULSE_SRC_POL_X_POSITIVE        ((uint8_t) 0x00)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  positive.                                           */
#define MMA865x_PULSE_SRC_POL_X_NEGATIVE        ((uint8_t) 0x01)  /*  - Pulse event that triggered interrupt was          */
                                                                  /*  negative.                                           */
/*------------------------------*/




/*--------------------------------
** Register: PULSE_THSX
** Enum: MMA865x_PULSE_THSX
** --
** Offset : 0x23 - Pulse threshold for X-axes register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  thsx : 7; /*  - Pulse threshold on X-axis.                                               */

    } b;
    uint8_t w;
} MMA865x_PULSE_THSX_t;


/*
** PULSE_THSX - Bit field mask definitions 
*/
#define MMA865x_PULSE_THSX_THSX_MASK   ((uint8_t) 0x7F)
#define MMA865x_PULSE_THSX_THSX_SHIFT  ((uint8_t)    0)


/*------------------------------*/




/*--------------------------------
** Register: PULSE_THSY
** Enum: MMA865x_PULSE_THSY
** --
** Offset : 0x24 - Pulse threshold for Y-axes register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  thsy : 7; /*  - Pulse threshold on Y-axis.                                               */

    } b;
    uint8_t w;
} MMA865x_PULSE_THSY_t;


/*
** PULSE_THSY - Bit field mask definitions 
*/
#define MMA865x_PULSE_THSY_THSY_MASK   ((uint8_t) 0x7F)
#define MMA865x_PULSE_THSY_THSY_SHIFT  ((uint8_t)    0)


/*------------------------------*/




/*--------------------------------
** Register: PULSE_THSZ
** Enum: MMA865x_PULSE_THSZ
** --
** Offset : 0x25 - Pulse threshold for Z-axes register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  thsz : 7; /*  - Pulse threshold on Z-axis.                                               */

    } b;
    uint8_t w;
} MMA865x_PULSE_THSZ_t;


/*
** PULSE_THSZ - Bit field mask definitions 
*/
#define MMA865x_PULSE_THSZ_THSZ_MASK   ((uint8_t) 0x7F)
#define MMA865x_PULSE_THSZ_THSZ_SHIFT  ((uint8_t)    0)


/*------------------------------*/




/*--------------------------------
** Register: PULSE_TMLT
** Enum: MMA865x_PULSE_TMLT
** --
** Offset : 0x26 - First Pulse Time Window register
** ------------------------------*/
typedef uint8_t MMA865x_PULSE_TMLT_t;


/*--------------------------------
** Register: PULSE_LTCY
** Enum: MMA865x_PULSE_LTCY
** --
** Offset : 0x27 - Pulse Latency Timer register
** ------------------------------*/
typedef uint8_t MMA865x_PULSE_LTCY_t;


/*--------------------------------
** Register: PULSE_WIND
** Enum: MMA865x_PULSE_WIND
** --
** Offset : 0x28 - Second Pulse Time Window register
** ------------------------------*/
typedef uint8_t MMA865x_PULSE_WIND_t;


/*--------------------------------
** Register: ASLP_COUNT
** Enum: MMA865x_ASLP_COUNT
** --
** Offset : 0x29 - Auto-WAKE/SLEEP Detection register
** ------------------------------*/
typedef uint8_t MMA865x_ASLP_COUNT_t;




/*--------------------------------
** Register: CTRL_REG1
** Enum: MMA865x_CTRL_REG1
** --
** Offset : 0x2A - System Control 1 register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                active : 1; /*  - Full-scale selection.                                                    */

        uint8_t                f_read : 1; /*  - Fast-read mode: Data format is limited to single byte.                   */

        uint8_t _reserved_            : 1;
        uint8_t                    dr : 3; /*  - Data rate selection.                                                     */

        uint8_t             aslp_rate : 2; /*  - Configures the Auto-WAKE sample frequency when the device is in SLEEP    */
                                           /*  Mode.                                                                      */

    } b;
    uint8_t w;
} MMA865x_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions 
*/
#define MMA865x_CTRL_REG1_ACTIVE_MASK      ((uint8_t) 0x01)
#define MMA865x_CTRL_REG1_ACTIVE_SHIFT     ((uint8_t)    0)

#define MMA865x_CTRL_REG1_F_READ_MASK      ((uint8_t) 0x02)
#define MMA865x_CTRL_REG1_F_READ_SHIFT     ((uint8_t)    1)

#define MMA865x_CTRL_REG1_DR_MASK          ((uint8_t) 0x38)
#define MMA865x_CTRL_REG1_DR_SHIFT         ((uint8_t)    3)

#define MMA865x_CTRL_REG1_ASLP_RATE_MASK   ((uint8_t) 0xC0)
#define MMA865x_CTRL_REG1_ASLP_RATE_SHIFT  ((uint8_t)    6)


/*
** CTRL_REG1 - Bit field value definitions  
*/
#define MMA865x_CTRL_REG1_ASLP_RATE_50HZ        ((uint8_t) 0x00)  /*  - Frequency = 50Hz                                  */
#define MMA865x_CTRL_REG1_ASLP_RATE_12_5HZ      ((uint8_t) 0x40)  /*  - Frequency = 12.5Hz                                */
#define MMA865x_CTRL_REG1_ASLP_RATE_6_25HZ      ((uint8_t) 0x80)  /*  - Frequency = 6.25Hz                                */
#define MMA865x_CTRL_REG1_ASLP_RATE_1_56HZ      ((uint8_t) 0xc0)  /*  - Frequency = 1.56Hz                                */
#define MMA865x_CTRL_REG1_DR_800HZ              ((uint8_t) 0x00)  /*  - ODR = 800Hz.                                      */
#define MMA865x_CTRL_REG1_DR_400HZ              ((uint8_t) 0x08)  /*  - ODR = 400Hz.                                      */
#define MMA865x_CTRL_REG1_DR_200HZ              ((uint8_t) 0x10)  /*  - ODR = 200Hz.                                      */
#define MMA865x_CTRL_REG1_DR_100HZ              ((uint8_t) 0x18)  /*  - ODR = 100Hz.                                      */
#define MMA865x_CTRL_REG1_DR_50HZ               ((uint8_t) 0x20)  /*  - ODR = 50Hz.                                       */
#define MMA865x_CTRL_REG1_DR_12_5HZ             ((uint8_t) 0x28)  /*  - ODR = 12.5Hz.                                     */
#define MMA865x_CTRL_REG1_DR_6_25HZ             ((uint8_t) 0x30)  /*  - ODR = 6.25Hz.                                     */
#define MMA865x_CTRL_REG1_DR_1_56HZ             ((uint8_t) 0x38)  /*  - ODR = 1.56Hz.                                     */
#define MMA865x_CTRL_REG1_F_READ_NORMAL         ((uint8_t) 0x00)  /*  - Normal Mode.                                      */
#define MMA865x_CTRL_REG1_F_READ_FAST           ((uint8_t) 0x02)  /*  - Fast Read Mode.                                   */
#define MMA865x_CTRL_REG1_ACTIVE_STANDBY        ((uint8_t) 0x00)  /*  - STANDBY mode.                                     */
#define MMA865x_CTRL_REG1_ACTIVE_ACTIVATED      ((uint8_t) 0x01)  /*  - ACTIVE mode.                                      */
/*------------------------------*/




/*--------------------------------
** Register: CTRL_REG2
** Enum: MMA865x_CTRL_REG2
** --
** Offset : 0x2B - System Control 2 register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  mods : 2; /*  - ACTIVE mode power scheme selection.                                      */

        uint8_t                  slpe : 1; /*  - Auto-SLEEP enable.                                                       */

        uint8_t                 smods : 2; /*  - SLEEP mode power scheme selection.                                       */

        uint8_t _reserved_            : 1;
        uint8_t                   rst : 1; /*  - Software Reset.                                                          */

        uint8_t                    st : 1; /*  - Self-Test Enable.                                                        */

    } b;
    uint8_t w;
} MMA865x_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions 
*/
#define MMA865x_CTRL_REG2_MODS_MASK    ((uint8_t) 0x03)
#define MMA865x_CTRL_REG2_MODS_SHIFT   ((uint8_t)    0)

#define MMA865x_CTRL_REG2_SLPE_MASK    ((uint8_t) 0x04)
#define MMA865x_CTRL_REG2_SLPE_SHIFT   ((uint8_t)    2)

#define MMA865x_CTRL_REG2_SMODS_MASK   ((uint8_t) 0x18)
#define MMA865x_CTRL_REG2_SMODS_SHIFT  ((uint8_t)    3)

#define MMA865x_CTRL_REG2_RST_MASK     ((uint8_t) 0x40)
#define MMA865x_CTRL_REG2_RST_SHIFT    ((uint8_t)    6)

#define MMA865x_CTRL_REG2_ST_MASK      ((uint8_t) 0x80)
#define MMA865x_CTRL_REG2_ST_SHIFT     ((uint8_t)    7)


/*
** CTRL_REG2 - Bit field value definitions  
*/
#define MMA865x_CTRL_REG2_ST_DISABLED           ((uint8_t) 0x00)  /*  - Self-Test disabled.                               */
#define MMA865x_CTRL_REG2_ST_EN                 ((uint8_t) 0x80)  /*  - Self-Test enabled.                                */
#define MMA865x_CTRL_REG2_RST_DISABLED          ((uint8_t) 0x00)  /*  - Device reset disabled.                            */
#define MMA865x_CTRL_REG2_RST_EN                ((uint8_t) 0x40)  /*  - Device reset enabled.                             */
#define MMA865x_CTRL_REG2_SMODS_NORMAL          ((uint8_t) 0x00)  /*  - Normal Mode.                                      */
#define MMA865x_CTRL_REG2_SMODS_LNLP            ((uint8_t) 0x08)  /*  - Low Noise Low Power Mode.                         */
#define MMA865x_CTRL_REG2_SMODS_HR              ((uint8_t) 0x10)  /*  - High Resolution Mode.                             */
#define MMA865x_CTRL_REG2_SMODS_LP              ((uint8_t) 0x18)  /*  - Low Power Mode.                                   */
#define MMA865x_CTRL_REG2_SLPE_DISABLED         ((uint8_t) 0x00)  /*  - Auto-SLEEP is not enabled.                        */
#define MMA865x_CTRL_REG2_SLPE_EN               ((uint8_t) 0x04)  /*  - Auto-SLEEP is enabled.                            */
#define MMA865x_CTRL_REG2_MODS_NORMAL           ((uint8_t) 0x00)  /*  - Normal Mode.                                      */
#define MMA865x_CTRL_REG2_MODS_LNLP             ((uint8_t) 0x01)  /*  - Low Noise Low Power Mode.                         */
#define MMA865x_CTRL_REG2_MODS_HR               ((uint8_t) 0x02)  /*  - High Resolution Mode.                             */
#define MMA865x_CTRL_REG2_MODS_LP               ((uint8_t) 0x03)  /*  - Low Power Mode.                                   */
/*------------------------------*/




/*--------------------------------
** Register: CTRL_REG3
** Enum: MMA865x_CTRL_REG3
** --
** Offset : 0x2C - Interrupt Control register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 pp_od : 1; /*  - Configures the interrupt pins to Push-Pull or to Open-Drain mode.        */

        uint8_t                  ipol : 1; /*  - Selects the polarity of the interrupt signals.                           */

        uint8_t _reserved_            : 1;
        uint8_t            wake_ff_mt : 1; /*  - Wake from Freefall/Motion interrupt.                                     */

        uint8_t            wake_pulse : 1; /*  - Wake from Pulse interrupt.                                               */

        uint8_t           wake_lndprt : 1; /*  - Wake from Orientation interrupt.                                         */

        uint8_t            wake_trans : 1; /*  - Wake from Transient interrupt.                                           */

        uint8_t             fifo_gate : 1; /*  - FIFO Gate                                                                */

    } b;
    uint8_t w;
} MMA865x_CTRL_REG3_t;


/*
** CTRL_REG3 - Bit field mask definitions 
*/
#define MMA865x_CTRL_REG3_PP_OD_MASK         ((uint8_t) 0x01)
#define MMA865x_CTRL_REG3_PP_OD_SHIFT        ((uint8_t)    0)

#define MMA865x_CTRL_REG3_IPOL_MASK          ((uint8_t) 0x02)
#define MMA865x_CTRL_REG3_IPOL_SHIFT         ((uint8_t)    1)

#define MMA865x_CTRL_REG3_WAKE_FF_MT_MASK    ((uint8_t) 0x08)
#define MMA865x_CTRL_REG3_WAKE_FF_MT_SHIFT   ((uint8_t)    3)

#define MMA865x_CTRL_REG3_WAKE_PULSE_MASK    ((uint8_t) 0x10)
#define MMA865x_CTRL_REG3_WAKE_PULSE_SHIFT   ((uint8_t)    4)

#define MMA865x_CTRL_REG3_WAKE_LNDPRT_MASK   ((uint8_t) 0x20)
#define MMA865x_CTRL_REG3_WAKE_LNDPRT_SHIFT  ((uint8_t)    5)

#define MMA865x_CTRL_REG3_WAKE_TRANS_MASK    ((uint8_t) 0x40)
#define MMA865x_CTRL_REG3_WAKE_TRANS_SHIFT   ((uint8_t)    6)

#define MMA865x_CTRL_REG3_FIFO_GATE_MASK     ((uint8_t) 0x80)
#define MMA865x_CTRL_REG3_FIFO_GATE_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG3 - Bit field value definitions  
*/
#define MMA865x_CTRL_REG3_FIFO_GATE_BYPASSED    ((uint8_t) 0x00)  /*  - FIFO gate is bypassed.                            */
#define MMA865x_CTRL_REG3_FIFO_GATE_BLOCKED     ((uint8_t) 0x80)  /*  - The FIFO input buffer is blocked when             */
                                                                  /*  transitioning from WAKE to SLEEP mode or from SLEEP */
                                                                  /*  to WAKE mode, until the FIFO is flushed.            */
#define MMA865x_CTRL_REG3_WAKE_TRANS_BYPASSED   ((uint8_t) 0x00)  /*  - Transient function is bypassed in SLEEP mode.     */
#define MMA865x_CTRL_REG3_WAKE_TRANS_EN         ((uint8_t) 0x40)  /*  - Transient function interrupt can wake up system.  */
#define MMA865x_CTRL_REG3_WAKE_LNDPRT_BYPASSED  ((uint8_t) 0x00)  /*  - Orientation function is bypassed in SLEEP mode.   */
#define MMA865x_CTRL_REG3_WAKE_LNDPRT_EN        ((uint8_t) 0x20)  /*  - Orientation function interrupt can wake up        */
                                                                  /*  system.                                             */
#define MMA865x_CTRL_REG3_WAKE_PULSE_BYPASSED   ((uint8_t) 0x00)  /*  - Pulse function is bypassed in SLEEP mode.         */
#define MMA865x_CTRL_REG3_WAKE_PULSE_EN         ((uint8_t) 0x10)  /*  - Pulse function interrupt can wake up system.      */
#define MMA865x_CTRL_REG3_WAKE_FF_MT_BYPASSED   ((uint8_t) 0x00)  /*  - Freefall/Motion function is bypassed in SLEEP     */
                                                                  /*  mode.                                               */
#define MMA865x_CTRL_REG3_WAKE_FF_MT_EN         ((uint8_t) 0x08)  /*  - Freefall/Motion function interrupt can wake up.   */
#define MMA865x_CTRL_REG3_IPOL_ACTIVE_LOW       ((uint8_t) 0x00)  /*  - ACTIVE low.                                       */
#define MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH      ((uint8_t) 0x02)  /*  - ACTIVE high.                                      */
#define MMA865x_CTRL_REG3_PP_OD_PUSH_PULL       ((uint8_t) 0x00)  /*  - Push-Pull.                                        */
#define MMA865x_CTRL_REG3_PP_OD_OPEN_DRAIN      ((uint8_t) 0x01)  /*  - Open Drain.                                       */
/*------------------------------*/




/*--------------------------------
** Register: CTRL_REG4
** Enum: MMA865x_CTRL_REG4
** --
** Offset : 0x2D - Interrupt Enable register
** ------------------------------*/
typedef union {
    struct {
        uint8_t           int_en_drdy : 1; /*  - Data Ready Interrupt Enable.                                             */

        uint8_t _reserved_            : 1;
        uint8_t          int_en_ff_mt : 1; /*  - Freefall/Motion Interrupt Enable.                                        */

        uint8_t          int_en_pulse : 1; /*  - Pulse Detection Interrupt Enable.                                        */

        uint8_t         int_en_lndprt : 1; /*  - Orientation (Landscape/Portrait) Interrupt Enable.                       */

        uint8_t          int_en_trans : 1; /*  - Transient Interrupt Enable.                                              */

        uint8_t           int_en_fifo : 1; /*  - FIFO Interrupt Enable.                                                   */

        uint8_t           int_en_aslp : 1; /*  - Auto-SLEEP/WAKE Interrupt Enable.                                        */

    } b;
    uint8_t w;
} MMA865x_CTRL_REG4_t;


/*
** CTRL_REG4 - Bit field mask definitions 
*/
#define MMA865x_CTRL_REG4_INT_EN_DRDY_MASK     ((uint8_t) 0x01)
#define MMA865x_CTRL_REG4_INT_EN_DRDY_SHIFT    ((uint8_t)    0)

#define MMA865x_CTRL_REG4_INT_EN_FF_MT_MASK    ((uint8_t) 0x04)
#define MMA865x_CTRL_REG4_INT_EN_FF_MT_SHIFT   ((uint8_t)    2)

#define MMA865x_CTRL_REG4_INT_EN_PULSE_MASK    ((uint8_t) 0x08)
#define MMA865x_CTRL_REG4_INT_EN_PULSE_SHIFT   ((uint8_t)    3)

#define MMA865x_CTRL_REG4_INT_EN_LNDPRT_MASK   ((uint8_t) 0x10)
#define MMA865x_CTRL_REG4_INT_EN_LNDPRT_SHIFT  ((uint8_t)    4)

#define MMA865x_CTRL_REG4_INT_EN_TRANS_MASK    ((uint8_t) 0x20)
#define MMA865x_CTRL_REG4_INT_EN_TRANS_SHIFT   ((uint8_t)    5)

#define MMA865x_CTRL_REG4_INT_EN_FIFO_MASK     ((uint8_t) 0x40)
#define MMA865x_CTRL_REG4_INT_EN_FIFO_SHIFT    ((uint8_t)    6)

#define MMA865x_CTRL_REG4_INT_EN_ASLP_MASK     ((uint8_t) 0x80)
#define MMA865x_CTRL_REG4_INT_EN_ASLP_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG4 - Bit field value definitions  
*/
#define MMA865x_CTRL_REG4_INT_EN_ASLP_DISABLED  ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_ASLP_EN        ((uint8_t) 0x80)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_FIFO_DISABLED  ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_FIFO_EN        ((uint8_t) 0x40)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_TRANS_DISABLED ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_TRANS_EN       ((uint8_t) 0x20)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_LNDPRT_DISABLED ((uint8_t) 0x00)  /*  - Interrupt is disabled.                           */
#define MMA865x_CTRL_REG4_INT_EN_LNDPRT_EN      ((uint8_t) 0x10)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_PULSE_DISABLED ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_PULSE_EN       ((uint8_t) 0x08)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_FF_MT_DISABLED ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_FF_MT_EN       ((uint8_t) 0x04)  /*  - Interrupt is enabled.                             */
#define MMA865x_CTRL_REG4_INT_EN_DRDY_DISABLED  ((uint8_t) 0x00)  /*  - Interrupt is disabled.                            */
#define MMA865x_CTRL_REG4_INT_EN_DRDY_EN        ((uint8_t) 0x01)  /*  - Interrupt is enabled.                             */
/*------------------------------*/




/*--------------------------------
** Register: CTRL_REG5
** Enum: MMA865x_CTRL_REG5
** --
** Offset : 0x2E - Interrupt Configuration register
** ------------------------------*/
typedef union {
    struct {
        uint8_t          int_cfg_drdy : 1; /*  - Data Ready INT1/INT2 Configuration.                                      */

        uint8_t _reserved_            : 1;
        uint8_t         int_cfg_ff_mt : 1; /*  - Freefall/Motion INT1/INT2 Configuration.                                 */

        uint8_t         int_cfg_pulse : 1; /*  - Pulse INT1/INT2 Configuration.                                           */

        uint8_t        int_cfg_lndprt : 1; /*  - Orientation INT1/INT2 Configuration.                                     */

        uint8_t         int_cfg_trans : 1; /*  - Transient INT1/INT2 Configuration.                                       */

        uint8_t          int_cfg_fifo : 1; /*  - FIFO INT1/INT2 Configuration.                                            */

        uint8_t          int_cfg_aslp : 1; /*  - Auto-SLEEP/WAKE INT1/INT2 Configuration.                                 */

    } b;
    uint8_t w;
} MMA865x_CTRL_REG5_t;


/*
** CTRL_REG5 - Bit field mask definitions 
*/
#define MMA865x_CTRL_REG5_INT_CFG_DRDY_MASK     ((uint8_t) 0x01)
#define MMA865x_CTRL_REG5_INT_CFG_DRDY_SHIFT    ((uint8_t)    0)

#define MMA865x_CTRL_REG5_INT_CFG_FF_MT_MASK    ((uint8_t) 0x04)
#define MMA865x_CTRL_REG5_INT_CFG_FF_MT_SHIFT   ((uint8_t)    2)

#define MMA865x_CTRL_REG5_INT_CFG_PULSE_MASK    ((uint8_t) 0x08)
#define MMA865x_CTRL_REG5_INT_CFG_PULSE_SHIFT   ((uint8_t)    3)

#define MMA865x_CTRL_REG5_INT_CFG_LNDPRT_MASK   ((uint8_t) 0x10)
#define MMA865x_CTRL_REG5_INT_CFG_LNDPRT_SHIFT  ((uint8_t)    4)

#define MMA865x_CTRL_REG5_INT_CFG_TRANS_MASK    ((uint8_t) 0x20)
#define MMA865x_CTRL_REG5_INT_CFG_TRANS_SHIFT   ((uint8_t)    5)

#define MMA865x_CTRL_REG5_INT_CFG_FIFO_MASK     ((uint8_t) 0x40)
#define MMA865x_CTRL_REG5_INT_CFG_FIFO_SHIFT    ((uint8_t)    6)

#define MMA865x_CTRL_REG5_INT_CFG_ASLP_MASK     ((uint8_t) 0x80)
#define MMA865x_CTRL_REG5_INT_CFG_ASLP_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG5 - Bit field value definitions  
*/
#define MMA865x_CTRL_REG5_INT_CFG_ASLP_INT2     ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_ASLP_INT1     ((uint8_t) 0x80)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_FIFO_INT2     ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_FIFO_INT1     ((uint8_t) 0x40)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_TRANS_INT2    ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_TRANS_INT1    ((uint8_t) 0x20)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_LNDPRT_INT2   ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_LNDPRT_INT1   ((uint8_t) 0x10)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_PULSE_INT2    ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_PULSE_INT1    ((uint8_t) 0x08)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT2    ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT1    ((uint8_t) 0x04)  /*  - Interrupt is routed to INT1 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_DRDY_INT2     ((uint8_t) 0x00)  /*  - Interrupt is routed to INT2 pin.                  */
#define MMA865x_CTRL_REG5_INT_CFG_DRDY_INT1     ((uint8_t) 0x01)  /*  - Interrupt is routed to INT1 pin.                  */
/*------------------------------*/




/*--------------------------------
** Register: OFF_X
** Enum: MMA865x_OFF_X
** --
** Offset : 0x2F - Offset Correction X register
** ------------------------------*/
typedef uint8_t MMA865x_OFF_X_t;


/*--------------------------------
** Register: OFF_Y
** Enum: MMA865x_OFF_Y
** --
** Offset : 0x30 - Offset Correction Y register
** ------------------------------*/
typedef uint8_t MMA865x_OFF_Y_t;


/*--------------------------------
** Register: OFF_Z
** Enum: MMA865x_OFF_Z
** --
** Offset : 0x31 - Offset Correction Z register
** ------------------------------*/
typedef uint8_t MMA865x_OFF_Z_t;



#endif  /* MMA865x_H_ */ 
