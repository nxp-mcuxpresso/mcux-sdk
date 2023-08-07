/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! File: nmh1000.h
* @brief The \b nmh1000.h file contains the register definitions for NMH1000 sensor.
*/

#ifndef NMH1000_H_
#define NMH1000_H_

/**
 **
 ** @brief The NMH1000 Sensor Internal  Map.
 */
enum {
     NMH1000_STATUS               = 0x00,
     NMH1000_CONTROL_REG1         = 0x01,
     NMH1000_RESERVED1            = 0x02,
     NMH1000_OUT_M_REG            = 0x03,
     NMH1000_USER_ASSERT_THRESH   = 0x04,
     NMH1000_USER_CLEAR_THRESH    = 0x05,
     NMH1000_ODR                  = 0x06,
     NMH1000_RESERVED2            = 0x07,
     NMH1000_WHO_AM_I             = 0x08,
     NMH1000_I2C_ADDR             = 0x09,
};

#define NMH1000_WHO_AM_I_VALUE     (0x01)

/*--------------------------------
** Register: STATUS
** Enum: NMH1000_STATUS
** --
** Offset : 0x0 - Status reporting register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 out_b : 1; /*  Output Buffer indicate a latched state of the VOUT pin after a transition  */
                                           /*  from either Asserted to Clear or Clear to Asserted.                        */

        uint8_t              rst_stat : 1; /*  Reset Status shall indicate the state-machine reset sequence.              */

        uint8_t _reserved_            : 1;
        uint8_t                opmode : 1; /*  The read-only OPMODE shall indicate the mode of the internal               */
                                           /*  state-machine.                                                             */

        uint8_t _reserved_1           : 1;
        uint8_t                   mdr : 1; /*  Magnetic Data Ready shall indicate the value in register $03 is available  */
                                           /*  for read operation.                                                        */

        uint8_t                   mdo : 1; /*  Magnetic Data Overwrite shall indicate the validity of the value in        */
                                           /*  register $03.                                                              */

        uint8_t                output : 1; /*  Vout control block state.                                                  */

    } b;
    uint8_t w;
} NMH1000_STATUS_t;


/*
** STATUS - Bit field mask definitions 
*/
#define NMH1000_STATUS_OUT_B_MASK      ((uint8_t) 0x01)
#define NMH1000_STATUS_OUT_B_SHIFT     ((uint8_t)    0)

#define NMH1000_STATUS_RST_STAT_MASK   ((uint8_t) 0x02)
#define NMH1000_STATUS_RST_STAT_SHIFT  ((uint8_t)    1)

#define NMH1000_STATUS_OPMODE_MASK     ((uint8_t) 0x08)
#define NMH1000_STATUS_OPMODE_SHIFT    ((uint8_t)    3)

#define NMH1000_STATUS_MDR_MASK        ((uint8_t) 0x20)
#define NMH1000_STATUS_MDR_SHIFT       ((uint8_t)    5)

#define NMH1000_STATUS_MDO_MASK        ((uint8_t) 0x40)
#define NMH1000_STATUS_MDO_SHIFT       ((uint8_t)    6)

#define NMH1000_STATUS_OUTPUT_MASK     ((uint8_t) 0x80)
#define NMH1000_STATUS_OUTPUT_SHIFT    ((uint8_t)    7)


/*
** STATUS - Bit field value definitions  
*/
#define NMH1000_STATUS_OUT_B_CLEARED         ((uint8_t) 0x00)  /*  OUT Cleared on previous cycle.                         */
#define NMH1000_STATUS_OUT_B_ASSERTED        ((uint8_t) 0x01)  /*  OUT asserted on previous cycle.                        */
#define NMH1000_STATUS_RST_STAT_RST_SEQ_COMPLETED ((uint8_t) 0x00)  /*  Reset sequence complete and read operation        */
                                                                    /*  performed on register $00.                        */
#define NMH1000_STATUS_RST_STAT_RST_SEQ_NOT_COMPLETED ((uint8_t) 0x02)  /*  Reset sequence not complete. Result of Reset. */
#define NMH1000_STATUS_OPMODE_STATE_MACHINE_FAULT ((uint8_t) 0x00)  /*  ndicates VPP < VSTAND and the device in           */
                                                                    /*  Standalone mode indicating a state machine fault, */
                                                                    /*  since the registers are only accessible in the    */
                                                                    /*  I2C mode.                                         */
#define NMH1000_STATUS_OPMODE_USER_MODE      ((uint8_t) 0x08)  /*  Indicates VPP >= VSTAND and the device in I2C User     */
                                                               /*  Mode.                                                  */
#define NMH1000_STATUS_MDR_DATA_AVAILABLE    ((uint8_t) 0x00)  /*  $03 data available.                                    */
#define NMH1000_STATUS_MDR_DATA_NOT_AVAILABLE ((uint8_t) 0x20)  /*  $03 data not available. Result of Reset.              */
#define NMH1000_STATUS_MDO_VALIDITY_IN_RANGE ((uint8_t) 0x00)  /*  Register $03 value is within the range $00 to $1F.     */
#define NMH1000_STATUS_MDO_VALIDITY_OUT_OF_RANGE ((uint8_t) 0x40)  /*  Register $03 value is >$1F indicating out-of-range */
                                                                   /*  or fault. Result of Reset.                         */
#define NMH1000_STATUS_OUTPUT_VOUT_DRIVEN_TO_VOL ((uint8_t) 0x00)  /*  The state of VOUT is driven to VOL; Result of      */
                                                                   /*  Reset.                                             */
#define NMH1000_STATUS_OUTPUT_VOUT_DRIVEN_TO_VOH ((uint8_t) 0x80)  /*  The state of VOUT is driven to VOH.                */
/*------------------------------*/




/*--------------------------------
** Register: CONTROL_REG1
** Enum: NMH1000_CONTROL_REG1
** --
** Offset : 0x01 - Control Register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   rst : 1; /*  Internal device Soft Reset.                                                */

        uint8_t _reserved_            : 1;
        uint8_t             one_short : 1; /*  It provides control of the state machine to trigger a single sequence of   */
                                           /*  Compare to Vout Control, then halt. The bit shall clear upon the sequence  */
                                           /*  being completed.                                                           */

        uint8_t             auto_mode : 1; /*  It provides control of the state machine to enter a sequential autonomous  */
                                           /*  mode cycling from Sleep to Compare to Vout Control, then back to Sleep,    */
                                           /*  etc. The sequence shall be halted when the AUTO is written to 0.           */

        uint8_t               i2c_dis : 1; /*  Control of the operating mode "on-the'fly" after the device has exited POR */
                                           /*  or Soft Reset. This allows the user to force the device into standalone    */
                                           /*  mode.                                                                      */

        uint8_t                 v_pol : 1; /*  Control of the user-defined OUT pin and resultant OUT_B register bit       */
                                           /*  assert / clear polarity.                                                   */

    } b;
    uint8_t w;
} NMH1000_CONTROL_REG1_t;


/*
** CONTROL_REG1 - Bit field mask definitions 
*/
#define NMH1000_CONTROL_REG1_RST_MASK         ((uint8_t) 0x01)
#define NMH1000_CONTROL_REG1_RST_SHIFT        ((uint8_t)    0)

#define NMH1000_CONTROL_REG1_ONE_SHORT_MASK   ((uint8_t) 0x04)
#define NMH1000_CONTROL_REG1_ONE_SHORT_SHIFT  ((uint8_t)    2)

#define NMH1000_CONTROL_REG1_AUTO_MODE_MASK   ((uint8_t) 0x08)
#define NMH1000_CONTROL_REG1_AUTO_MODE_SHIFT  ((uint8_t)    3)

#define NMH1000_CONTROL_REG1_I2C_DIS_MASK     ((uint8_t) 0x10)
#define NMH1000_CONTROL_REG1_I2C_DIS_SHIFT    ((uint8_t)    4)

#define NMH1000_CONTROL_REG1_V_POL_MASK       ((uint8_t) 0x20)
#define NMH1000_CONTROL_REG1_V_POL_SHIFT      ((uint8_t)    5)


/*
** CONTROL_REG1 - Bit field value definitions  
*/
#define NMH1000_CONTROL_REG1_RST_NO_RESET          ((uint8_t) 0x00)  /*  No reset is forced.                              */
#define NMH1000_CONTROL_REG1_RST_RESET             ((uint8_t) 0x01)  /*  Internal device reset is be forced.              */
#define NMH1000_CONTROL_REG1_ONE_SHORT_EN          ((uint8_t) 0x04)  /*  Trigger a One-Shot sequence.                     */
#define NMH1000_CONTROL_REG1_AUTO_MODE_HALT        ((uint8_t) 0x00)  /*  Halts or prevents Autonomous mode.               */
#define NMH1000_CONTROL_REG1_AUTO_MODE_START       ((uint8_t) 0x08)  /*  Start the Autonomous mode.                       */
#define NMH1000_CONTROL_REG1_I2C_DIS_STANDALONE_MODE ((uint8_t) 0x10)  /*  force the device into i2c standalone mode.     */
#define NMH1000_CONTROL_REG1_V_POL_ASSERT_VOH_CLR_VOL ((uint8_t) 0x00)  /*  Assert = VOH, Clear = VOL; Result of Reset    */
#define NMH1000_CONTROL_REG1_V_POL_ASSERT_VOL_CLR_VOH ((uint8_t) 0x20)  /*  Assert = VOL, Clear = VOH.                    */
/*------------------------------*/




/*--------------------------------
** Register: RESERVED_REG_1
** Enum: NMH1000_RESERVED_REG_1
** --
** Offset : 0x02
** ------------------------------*/
typedef uint8_t NMH1000_RESERVED_REG_1_t;


/*--------------------------------
** Register: OUT_M_REG
** Enum: NMH1000_OUT_M_REG
** --
** Offset : 0x03 - Report of Magnetic Field Strength
** ------------------------------*/
typedef uint8_t NMH1000_OUT_M_REG_t;


/*--------------------------------
** Register: USER_ASSERT_THRESH
** Enum: NMH1000_USER_ASSERT_THRESH
** --
** Offset : 0x04 - User selectable output Assert Threshold value from $01 to $1F;provides the capability for the user to override the fixed threshold controlling the output assert condition.
** ------------------------------*/
typedef uint8_t NMH1000_USER_ASSERT_THRESH_t;


/*--------------------------------
** Register: USER_CLEAR_THRESH
** Enum: NMH1000_USER_CLEAR_THRESH
** --
** Offset : 0x05 - User selectable output Clear Threshold value from $01 to $1F;provides the capability for the user to override the fixed threshold controlling the output clear condition.
** ------------------------------*/
typedef uint8_t NMH1000_USER_CLEAR_THRESH_t;


/*--------------------------------
** Register: USER_ODR
** Enum: NMH1000_USER_ODR
** --
** Offset : 0x06 - User Setting of Sample Rate(ODR)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   odr : 3;
    } b;
    uint8_t w;
} NMH1000_USER_ODR_t;


/*
** USER_ODR - Bit field mask definitions 
*/
#define NMH1000_USER_ODR_ODR_MASK   ((uint8_t) 0x07)
#define NMH1000_USER_ODR_ODR_SHIFT  ((uint8_t)    0)


/*
** USER_ODR - Bit field value definitions  
*/
#define NMH1000_USER_ODR_ODR_LSP               ((uint8_t) 0x00)  /*  Low sample rate selected                             */
#define NMH1000_USER_ODR_ODR_5X_LSP            ((uint8_t) 0x01)  /*  5*Low sample rate selected                           */
#define NMH1000_USER_ODR_ODR_MSP               ((uint8_t) 0x02)  /*  Medium sample rate selected                          */
#define NMH1000_USER_ODR_ODR_HSP               ((uint8_t) 0x04)  /*  High sample rate selected                            */
#define NMH1000_USER_ODR_ODR_5X_HSP            ((uint8_t) 0x05)  /*  5*High sample rate selected                          */
#define NMH1000_USER_ODR_ODR_10X_HSP           ((uint8_t) 0x06)  /*  10*High sample rate selected                         */
#define NMH1000_USER_ODR_ODR_CONFIG_ERR        ((uint8_t) 0x07)  /*  Coniguration error                                   */
/*------------------------------*/



/*--------------------------------
** Register: RESERVED_REG_2
** Enum: NMH1000_RESERVED_REG_2
** --
** Offset : 0x07
** ------------------------------*/
typedef uint8_t NMH1000_RESERVED_REG_2_t;


/*--------------------------------
** Register: WHO_AM_I
** Enum: NMH1000_WHO_AM_I
** --
** Offset : 0x08 - Device identification register
** ------------------------------*/
typedef uint8_t NMH1000_WHO_AM_I_t;


/*--------------------------------
** Register: I2C_ADDR
** Enum: NMH1000_I2C_ADDR
** --
** Offset : 0x09 - I2C Address register
** ------------------------------*/
#endif /* NMH1000_H_ */
// RESERVED1 :  0x02
// RESERVED2 :  0x07
// ODR :  0x06
