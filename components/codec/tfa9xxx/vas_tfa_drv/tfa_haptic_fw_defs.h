/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef TFA_HAPTIC_FW_DEFS_H_
#define TFA_HAPTIC_FW_DEFS_H_

/* base version */
#define FW_VERSION      0x0b0000 /* patch version in hex */
#define FW_VERSION_MASK 0xff0000 /* version check mask */
#define FW_XMEM_VERSION 0x11ff   /* TFA9894 xmem version offset */

/* firmware constants */
#define FW_XMEM_NR_OBJECTS1     6 /* nr of objects in table1 */
#define FW_XMEM_NR_OBJECTS2     5 /* nr of objects in table2 */
#define FW_XMEM_OBJECTSIZE      8
#define FW_XMEM_OBJECTSTATESIZE 8

#define FW_CMDOBJSEL_TABLE2_OFFFSET 64

#define FW_XMEM_CMDOBJSEL0       4102 /* pObjState */
#define FW_XMEM_CMDOBJSEL1       (FW_XMEM_CMDOBJSEL0 + FW_XMEM_OBJECTSTATESIZE)
#define FW_XMEM_SAMPCNT0         (FW_XMEM_CMDOBJSEL0 + 2) /* ->timeCnt */
#define FW_XMEM_SAMPCNT1         (FW_XMEM_CMDOBJSEL1 + 2)
#define FW_XMEM_F0               4052 /* fResOut */
#define FW_XMEM_R0               4053 /* Rf0Out */
#define FW_XMEM_GENOBJECTS1      4054 /* objectArray */
#define FW_XMEM_GENOBJECTS2      3152 /* objectArray2 */
#define FW_XMEM_F0_R0_RANGES     4134 /* ZfresMax */
#define FW_XMEM_DISF0TRC         4359 /* disF0Trc */
#define FW_XMEM_DELAY_ATTACK_SMP 4361 /* duckLraPar->delayAttackSmp */
#define FW_XMEM_RECALCSEL        4363 /* recalcSelector */

/* note: obj offsets is a table index, the interface index starts at 1 */
#define FW_HB_CAL_OBJ     (FW_XMEM_NR_OBJECTS1 - 2) /* calibration object */
#define FW_HB_STOP_OBJ    (FW_XMEM_NR_OBJECTS1 - 1) /* silence object */
#define FW_HB_SILENCE_OBJ FW_HB_STOP_OBJ            /* same as stop */
#define FW_HB_RECALC_OBJ  3                         /* default recalc object */
#define FW_HB_MAX_OBJ     (FW_XMEM_NR_OBJECTS1 + FW_XMEM_NR_OBJECTS2)
#define FW_HB_SEQ_OBJ     FW_HB_MAX_OBJ /* sequencer virtual objects base */

#define FW_XMEM_R0_SHIFT 11 /* Q13.11 */
#define FW_XMEM_F0_SHIFT 11 /* Q13.11 */

enum tfa_haptic_object_type
{
    object_wave    = 0,
    object_tone    = 1,
    object_silence = 2
};

/* Tone Generator object definition */
struct haptic_tone_object
{
    int32_t type;
    int32_t freq;
    int32_t level;
    int32_t durationCntMax;
    int32_t boostBrakeOn;
    int32_t trackerOn;
    int32_t boostLength;
    int32_t reserved;
};

/* Wave table object definition */
struct haptic_wave_object
{
    int32_t type;
    int32_t offset;
    int32_t level;
    int32_t durationCntMax;
    int32_t upSampSel;
    int32_t reserved[3];
};

#endif /* TFA_HAPTIC_FW_DEFS_H_ */
