/**************************************************************************//**
 * @file     core_ca53.h
 * @brief    CMSIS Cortex-A53 Core Peripheral Access Layer Header File
 * @version  V1.0.0
 * @date     05. october 2021
 ******************************************************************************/
/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if   defined ( __ICCARM__ )
 #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CORE_CA53_H_GENERIC
#define __CORE_CA53_H_GENERIC

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/

#define __CORTEX_Axx              (53U)                  /*!< Cortex-Axx Core */

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __CA53_REV
    #define __CA53_REV                0x0000U
    #warning "__CA53_REV not defined in device header file; using default!"
  #endif

  #ifndef __FPU_PRESENT
    #define __FPU_PRESENT             1U
    #define __FPU_USED                1U
    #warning "__FPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __GIC_PRESENT
    #define __GIC_PRESENT             1U
    #warning "__GIC_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __MMU_PRESENT
    #define __MMU_PRESENT             1U
    #warning "__MMU_PRESENT not defined in device header file; using default!"
  #endif
#endif

#include "cmsis_compiler.h"                /* Core Instruction and Function Access */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CA53_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CA53_H_DEPENDANT
#define __CORE_CA53_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 Register Definitions
 ******************************************************************************/

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

/* DAIF Register */
#define DAIF_F_BIT                BIT(6)
#define DAIF_I_BIT                BIT(7)
#define DAIF_A_BIT                BIT(8)
#define DAIF_D_BIT                BIT(9)

/* System Control Register */
#define SCTLR_M_BIT               BIT(0)
#define SCTLR_A_BIT               BIT(1)
#define SCTLR_C_BIT               BIT(2)
#define SCTLR_SA_BIT              BIT(3)
#define SCTLR_I_BIT               BIT(12)

/* Exception levels EL0-EL3 */
#define MODE_EL_SHIFT		(0x2)
#define MODE_EL_MASK		(0x3)

#define MODE_EL3		(0x3)
#define MODE_EL2		(0x2)
#define MODE_EL1		(0x1)
#define MODE_EL0		(0x0)

#define GET_EL(_mode)		(((_mode) >> MODE_EL_SHIFT) & MODE_EL_MASK)

/*******************************************************************************
 *                 L1 Cache Functions
 ******************************************************************************/

/* TODO: L1 Cache Functions are TBD */


/*******************************************************************************
 *                 GIC Functions
 ******************************************************************************/

#if defined (__GIC_PRESENT) && (__GIC_PRESENT == 1U)

  #include "gic_v3.h"

#endif


/*******************************************************************************
 *                 MMU Functions
 ******************************************************************************/

#if defined (__MMU_PRESENT) && (__MMU_PRESENT == 1U)

  #include "mmu_armv8a.h"

#endif


/*******************************************************************************
 *                 Timer Functions
 ******************************************************************************/

#if defined (__TIM_PRESENT) && (__TIM_PRESENT == 1U)
  #include "timer_armv8a.h"
#endif


#ifdef __cplusplus
}
#endif

#endif /* __CORE_CA53_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
