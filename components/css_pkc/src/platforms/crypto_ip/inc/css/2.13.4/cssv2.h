/* This device file has been adapted from ARM CMSIS-Core sources*/
/* by NXP Semiconductors (2018)*/
/* Copyright(C) NXP B.V. 2018*/
/* All rights are reserved. Reproduction in whole or in part is prohibited*/
/* without the prior written consent of the copy-right owner.*/
/* This source code and any compilation or derivative thereof is the sole*/
/* property of NXP B.V. and is provided pursuant to a Software License*/
/* Agreement. This code is the proprietary information of NXP B.V. and*/
/* is confidential in nature. Its use and dissemination by any party other*/
/* than NXP B.V. is strictly limited by the confidential information*/
/* provisions of the agreement referenced above.*/
/* NXP makes no warranty, expressed, implied or statutory, including but*/
/* not limited to any implied warranty of merchantability or fitness for any*/
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark.*/
/* NXP must not be liable for any loss or damage arising from its use.*/
/********************************************************************************************************
 * @file     ip_css.h
 *
 * @brief    CMSIS  Peripheral Access Layer Header File for ip_css.
 *
 * @version  $Revision:$
 * @date     17. June 2020
 *
 * @note     Generated with csv2a_create_cmsis_cheader V1.41
 *******************************************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup ip_css
  * @{
  */

#ifndef ip_css_H
#define ip_css_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* ================================================================================ */
/* =========================  Interrupt Number Definition  ======================== */
/* ================================================================================ */

//typedef enum {
///* =====================   Processor Exceptions Numbers  ===================== */
//  Reset_IRQn                    = -15,              /*!<   -15  Reset Vector, invoked on Power up and warm reset                 */
//  NonMaskableInt_IRQn           = -14,              /*!<   -14  Non maskable Interrupt, cannot be stopped or preempted           */
//  HardFault_IRQn                = -13,              /*!<   -13  Hard Fault, all classes of Fault                                 */
//  MemoryManagement_IRQn         = -12,              /*!<   -12  Memory Management, MPU mismatch, including Access Violation
//                                                                and No Match                                                     */
//  BusFault_IRQn                 = -11,              /*!<   -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
//                                                                related Fault                                                    */
//  UsageFault_IRQn               = -10,              /*!<   -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
//  SVCall_IRQn                   =  -5,              /*!<    -5  System Service Call via SVC instruction                          */
//  DebugMonitor_IRQn             =  -4,              /*!<    -4  Debug Monitor                                                    */
//  PendSV_IRQn                   =  -2,              /*!<    -2  Pendable request for system service                              */
//  SysTick_IRQn                  =  -1,              /*!<    -1  System Tick Timer                                                */
///* =====================  ip_css Specific Interrupt Numbers  ===================== */
//} IRQn_Type;



/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/** @} */ /* End of group Configuration_of_CMSIS */

//#include "core_.h"                                                 /*!<  processor and core peripherals              */
//#include "system_ip_css.h"                                         /*!< ip_css System                                */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
  #define __IOM  __IO
#endif


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* ===================  Start of section using anonymous unions  ================== */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#elif defined(__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                     ip_css                     ================ */
/* ================================================================================ */


/**
  * @brief SFRs of block ip_css (ip_css)
  */

typedef struct {                                    /*!< ip_css Structure                                                         */

  union {
    __IM  uint32_t  CSS_STATUS;                      /*!< Status register                                                       */

    struct {
      __IM  uint32_t  CSS_BUSY   :  1;              /*!< High to indicate the CSS is executing a Crypto Sequence               */
      __IM  uint32_t  CSS_IRQ    :  1;              /*!< High to indicate the CSS has an active interrupt                      */
      __IM  uint32_t  CSS_ERR    :  1;              /*!< High to indicate the CSS has detected an internal error               */
      __IM  uint32_t  PRNG_RDY   :  1;              /*!< High to indicate the internal PRNG is ready. SFR; CSS_PRNG_DATOUT 
                                                         can be read only when this status flag; is high. Reading SFR      
                                                         CSS_PRNG_DATOUT while this status; is low will trigger a CSS      
                                                         error.                                                                */
      __IM  uint32_t  ECDSA_VFY_STATUS:  2;         /*!< Signature Verify Result Status; 0 == No Verify Run; 1 ==          
                                                         Signature Verify Failed; 2 == Signature Verify Passed; 3 ==       
                                                         Invalid , Error                                                       */
      __IM  uint32_t  PPROT      :  2;              /*!< Current command privilege level                                       */
      __IM  uint32_t  DRBG_ENT_LVL:  2;             /*!< Entropy quality of the current DRBG instance. This value; can     
                                                         change while executing a CSS command but will remain; stable when 
                                                         CSS is not busy.; 00 - NONE. DRBG is not running.; 01 - LOW. DRBG 
                                                         generates random numbers of low quality entropy.; 10 - HIGH. DRBG 
                                                         generates random numbers of high quality entropy.; 11 - RFU.      
                                                         Reserved for Future Use.                                              */
      __IM  uint32_t  DTRNG_BUSY :  1;              /*!< When set, it indicates the DTRNG is gathering entropy                 */
      __IM  uint32_t  GDET_IRQ_POS:  1;             /*!< IRQ for GDET has detected a negative glitch: active high irq          */
      __IM  uint32_t  GDET_IRQ_NEG:  1;             /*!< IRQ for GDET has detected a positive glitch: active high irq          */
      __IM  uint32_t  STATUS_RSVD: 19;              /*!< STATUS_RSVD                                                           */
    } CSS_STATUS_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_CTRL;                        /*!< CSS Control register                                                  */

    struct {
      __IOM uint32_t  CSS_EN     :  1;              /*!< CSS enable 0=CSS disabled, 1= CSS is enabled                          */
      __IOM uint32_t  CSS_START  :  1;              /*!< Write to 1 to start a CSS Operation                                   */
      __IOM uint32_t  CSS_RESET  :  1;              /*!< Write to 1 to perform a CSS synchronous Reset                         */
      __IOM uint32_t  CSS_CMD    :  5;              /*!< CSS Command Field: List of Valid commands:; CIPHER; AUTH_CIPHER;  
                                                         ECSIGN; ECVFY; ECKXCH; KEYGEN; KEYIN; KEYOUT; KDELETE; KEYPROV;   
                                                         CKDF; HKDF; TLS_INIT; HASH; HMAC; CMAC; DRBG_REQ; DRBG_TEST;      
                                                         DTRNG_CFG_LOAD; DTRNG_EVAL; GDET_CFG_LOAD; GDET_TRIM                  */
      __IOM uint32_t  BYTE_ORDER :  1;              /*!< Defines Endianness - 1: BigEndian, 0: Little Endian                   */
      __IOM uint32_t  CTRL_RFU   : 23;              /*!< reserved                                                              */
    } CSS_CTRL_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_CMDCFG0;                     /*!< CSS command configuration register                                    */

    struct {
      __IOM uint32_t  CMDCFG0    : 32;              /*!< refer to reference manual for assignment of this field                */
    } CSS_CMDCFG0_b;                                /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_CFG;                         /*!< CSS configuration register                                            */

    struct {
      __IOM uint32_t  CFG_RSVD0  : 16;              /*!< reserved                                                              */
      __IOM uint32_t  ADCTRL     : 10;              /*!< maximum aes start delay                                               */
      __IOM uint32_t  CFG_RSVD1  :  5;              /*!< reserved                                                              */
      __IOM uint32_t  SHA2_DIRECT:  1;              /*!< 1=enable sha2 direct mode: direct access from external; bus to    
                                                         css internal sha                                                      */
    } CSS_CFG_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_KIDX0;                       /*!< Keystore index 0 - for commands that access a single key              */

    struct {
      __IOM uint32_t  KIDX0      :  7;              /*!< keystore is indexed as an array of 128 bit key slots                  */
            uint32_t             : 25;              /*!< reserved                                                              */
    } CSS_KIDX0_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_KIDX1;                       /*!< Keystore index 1 - for commands that access 2 keys                    */

    struct {
      __IOM uint32_t  KIDX1      :  7;              /*!< keystore is indexed as an array of 128 bit key slots                  */
            uint32_t             : 25;              /*!< reserved                                                              */
    } CSS_KIDX1_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_KPROPIN;                     /*!< key properties request                                                */

    struct {
      __IOM uint32_t  KPROPIN    : 32;              /*!< for commands that create a key - requested properties; of the key 
                                                         that is being created                                                 */
    } CSS_KPROPIN_b;                                /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED0;

  union {
    __IOM uint32_t  CSS_DMA_SRC0;                    /*!< CSS DMA Source 0                                                      */

    struct {
      __IOM uint32_t  ADDR_SRC0  : 32;              /*!< defines the System address of the start of the; data to be        
                                                         transferred to the CSS via DMA                                        */
    } CSS_DMA_SRC0_b;                               /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DMA_SRC0_LEN;                /*!< CSS DMA Source 0 length                                               */

    struct {
      __IOM uint32_t  SIZE_SRC0_LEN: 32;            /*!< Size in bytes of the data to be transferred from; the target      
                                                         defined in SFR CSS_DMA_SRC0                                           */
    } CSS_DMA_SRC0_LEN_b;                           /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DMA_SRC1;                    /*!< CSS DMA Source 1                                                      */

    struct {
      __IOM uint32_t  ADDR_SRC1  : 32;              /*!< defines the System address of the start of the; data to be        
                                                         transferred to the CSS via DMA                                        */
    } CSS_DMA_SRC1_b;                               /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED1;

  union {
    __IOM uint32_t  CSS_DMA_SRC2;                    /*!< CSS DMA Source 2                                                      */

    struct {
      __IOM uint32_t  ADDR_SRC2  : 32;              /*!< defines the System address of the start of the; data to be        
                                                         transferred to the CSS via DMA                                        */
    } CSS_DMA_SRC2_b;                               /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DMA_SRC2_LEN;                /*!< CSS DMA Source 2 length                                               */

    struct {
      __IOM uint32_t  SIZE_SRC2_LEN: 32;            /*!< Size in bytes of the data to be transferred from; the target      
                                                         defined in SFR CSS_DMA_SRC2                                           */
    } CSS_DMA_SRC2_LEN_b;                           /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DMA_RES0;                    /*!< CSS DMA Result 0                                                      */

    struct {
      __IOM uint32_t  ADDR_RES0  : 32;              /*!< defines the System Start address of where the result; of the CSS  
                                                         operation will be transferred via DMA                                 */
    } CSS_DMA_RES0_b;                               /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DMA_RES0_LEN;                /*!< CSS DMA Result 0 Size                                                 */

    struct {
      __IOM uint32_t  SIZE_RES0_LEN: 32;            /*!< Size in bytes of the data to be transferred to                        */
    } CSS_DMA_RES0_LEN_b;                           /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_INT_ENABLE;                  /*!< Interrupt enable                                                      */

    struct {
      __IOM uint32_t  INT_EN     :  1;              /*!< Interrupt enable bit                                                  */
      __IOM uint32_t  GDET_INT_EN:  1;              /*!< GDET Interrupt enable bit                                             */
      __IOM uint32_t  INT_ENA_RSVD: 30;             /*!< reserved                                                              */
    } CSS_INT_ENABLE_b;                             /*!< BitSize                                                               */
  };

  union {
    __OM  uint32_t  CSS_INT_STATUS_CLR;              /*!< Interrupt status clear                                                */

    /* skipped register field struct because it's write-only */
  };

  union {
    __OM  uint32_t  CSS_INT_STATUS_SET;              /*!< Interrupt status set                                                  */

    /* skipped register field struct because it's write-only */
  };

  union {
    __IM  uint32_t  CSS_ERR_STATUS;                  /*!< Status register                                                       */

    struct {
      __IM  uint32_t  BUS_ERR    :  1;              /*!< Bus access error: public or private bus                               */
      __IM  uint32_t  OPN_ERR    :  1;              /*!< Operational error:; CSS has been incorrectly operated                 */
      __IM  uint32_t  ALG_ERR    :  1;              /*!< Algorithm error: An internal algorithm has; produced an           
                                                         unexpected result.                                                    */
      __IM  uint32_t  ITG_ERR    :  1;              /*!< Data integrity error:; Internal data integrity check failed           */
      __IM  uint32_t  FLT_ERR    :  1;              /*!< Hardware fault error: Attempt to change the value; of an internal 
                                                         register                                                              */
      __IM  uint32_t  PRNG_ERR   :  1;              /*!< User Read of CSS_PRNG_DATOUT when CSS_STATUS.PRNG_RDY; is 0           */
      __IM  uint32_t  ERR_LVL    :  2;              /*!< Indicates Error Level which has been triggerer. 0, 1 ,2               */
      __IM  uint32_t  DTRNG_ERR  :  1;              /*!< DTRNG unable to gather entropy with the current; configuration.   
                                                         Provide the DTRNG with a new, valid; configuration via CSS        
                                                         command DTRNG_CFG_LOAD.                                               */
      __IM  uint32_t  ERR_STAT_RSVD: 23;            /*!< ERR_STAT_RSVD                                                         */
    } CSS_ERR_STATUS_b;                             /*!< BitSize                                                               */
  };

  union {
    __OM  uint32_t  CSS_ERR_STATUS_CLR;              /*!< Interrupt status clear                                                */

    /* skipped register field struct because it's write-only */
  };

  union {
    __IM  uint32_t  CSS_VERSION;                     /*!< CSS Version                                                           */

    struct {
      __IM  uint32_t  Z          :  4;              /*!< extended revision version: possible values 0-9                        */
      __IM  uint32_t  Y2         :  4;              /*!< minor release versino digit0: possible values 0-9                     */
      __IM  uint32_t  Y1         :  4;              /*!< minor release version digit1: possible values 0-9                     */
      __IM  uint32_t  X          :  4;              /*!< major release version: possible values 1-9                            */
      __IM  uint32_t  VERSION_RSVD: 16;             /*!< reserved                                                              */
    } CSS_VERSION_b;                                /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_CONFIG;                      /*!< CSS Config                                                            */

    struct {
      __IM  uint32_t  CIPHER_SUP :  1;              /*!< cipher      command is supported                                      */
      __IM  uint32_t  AUTH_CIPHER_SUP:  1;          /*!< auth_cipher command is supported                                      */
      __IM  uint32_t  ECSIGN_SUP :  1;              /*!< ecsign      command is supported                                      */
      __IM  uint32_t  ECVFY_SUP  :  1;              /*!< ecvfy       command is supported                                      */
      __IM  uint32_t  ECKXCH_SUP :  1;              /*!< dhkey_xch   command is supported                                      */
      __IM  uint32_t  KEYGEN_SUP :  1;              /*!< keygen      command is supported                                      */
      __IM  uint32_t  KEYIN_SUP  :  1;              /*!< keyin       command is supported                                      */
      __IM  uint32_t  KEYOUT_SUP :  1;              /*!< keyout      command  is  supported                                    */
      __IM  uint32_t  KDELETE_SUP:  1;              /*!< kdelete     command is supported                                      */
      __IM  uint32_t  KEYPROV_SUP:  1;              /*!< keyprov     command is supported                                      */
      __IM  uint32_t  CKDF_SUP   :  1;              /*!< ckdf        command is supported                                      */
      __IM  uint32_t  HKDF_SUP   :  1;              /*!< hkdf        command is supported                                      */
      __IM  uint32_t  TLS_INIT_SUP:  1;             /*!< tls_init    command is supported                                      */
      __IM  uint32_t  HASH_SUP   :  1;              /*!< hash        command is supported                                      */
      __IM  uint32_t  HMAC_SUP   :  1;              /*!< hmac        command is supported                                      */
      __IM  uint32_t  CMAC_SUP   :  1;              /*!< cmac        command is supported                                      */
      __IM  uint32_t  DRBG_REQ_SUP:  1;             /*!< drbg_req    command is supported                                      */
      __IM  uint32_t  DRBG_TEST_SUP:  1;            /*!< drbg_test   command is supported                                      */
      __IM  uint32_t  DTRNG_CFG_LOAD_SUP:  1;       /*!< dtrng_cfg_load command is supported                                   */
      __IM  uint32_t  DTRNG_EVAL_SUP:  1;           /*!< dtrng_eval     command is supported                                   */
      __IM  uint32_t  GDET_CFG_LOAD_SUP:  1;        /*!< gdet_cfg_load command is supported                                    */
      __IM  uint32_t  GDET_TRIM_SUP:  1;            /*!< gdet_trim command is supported                                        */
      __IM  uint32_t  CONFIG_RSVD: 10;              /*!< reserved                                                              */
    } CSS_CONFIG_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_PRNG_DATOUT;                 /*!< PRNG SW read out register                                             */

    struct {
      __IM  uint32_t  PRNG_DATOUT: 32;              /*!< 32-bit wide pseudo-random number                                      */
    } CSS_PRNG_DATOUT_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_GDET_EVTCNT;                 /*!< CSS GDET Event Counter                                                */

    struct {
      __IM  uint32_t  GDET_EVTCNT:  8;              /*!< Number of glitch event recorded                                       */
      __IM  uint32_t  GDET_EVTCNT_CLR_DONE:  1;     /*!< The GDET event counter has been cleared                               */
      __IM  uint32_t  GDET_EVTCNT_RSVD: 23;         /*!< reserved                                                              */
    } CSS_GDET_EVTCNT_b;                            /*!< BitSize                                                               */
  };

  union {
    __OM  uint32_t  CSS_GDET_EVTCNT_CLR;             /*!< CSS GDET Event Counter Clear                                          */

    /* skipped register field struct because it's write-only */
  };
  __IM  uint32_t  RESERVED2[38];

  union {
    __IM  uint32_t  CSS_SHA2_STATUS;                 /*!< CSS SHA2 Status Register                                              */

    struct {
      __IM  uint32_t  SHA2_BUSY  :  1;              /*!< SHA2_BUSY                                                             */
      __IM  uint32_t  STATUS_RSVD1: 31;             /*!< reserved                                                              */
    } CSS_SHA2_STATUS_b;                            /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_SHA2_CTRL;                   /*!< SHA2 Control register                                                 */

    struct {
      __IOM uint32_t  SHA2_START :  1;              /*!< Write to 1 to Init the SHA2 Module                                    */
      __IOM uint32_t  SHA2_RST   :  1;              /*!< Write to 1 to Reset a SHA2 operation                                  */
      __IOM uint32_t  SHA2_INIT  :  1;              /*!< Write to 1 to Init the SHA2 Kernel                                    */
      __IOM uint32_t  SHA2_LOAD  :  1;              /*!< Write to 1 to Load the SHA2 Kernel                                    */
      __IOM uint32_t  SHA2_MODE  :  2;              /*!< SHA2 MODE:; 2'b11 - SHA512; 2'b10 - SHA384; 2'b01 - SHA224; 2'b00 
                                                         - SHA256                                                              */
      __IOM uint32_t  CTRL_RSVD1 :  3;              /*!< r-eserved                                                             */
      __IOM uint32_t  SHA2_BYTE_ORDER:  1;          /*!< Write to 1 to Reverse byte endianess                                  */
      __IOM uint32_t  CTRL_RSVD  : 22;              /*!< r-eserved                                                             */
    } CSS_SHA2_CTRL_b;                              /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_SHA2_DIN;                    /*!< CSS SHA_DATA IN Register 0                                            */

    struct {
      __IOM uint32_t  SHA_DATIN  : 32;              /*!< Output CSS_SHA_DATIN from CSS Application being executed              */
    } CSS_SHA2_DIN_b;                               /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT0;                  /*!< CSS CSS_SHA_DATA Out Register 0                                       */

    struct {
      __IM  uint32_t  SHA_DATA0  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT0_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT1;                  /*!< CSS SHA_DATA Out Register 1                                           */

    struct {
      __IM  uint32_t  SHA_DATA1  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT1_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT2;                  /*!< CSS SHA_DATA Out Register 2                                           */

    struct {
      __IM  uint32_t  SHA_DATA2  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT2_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT3;                  /*!< CSS SHA_DATA Out Register 3                                           */

    struct {
      __IM  uint32_t  SHA_DATA3  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT3_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT4;                  /*!< CSS SHA_DATA Out Register 4                                           */

    struct {
      __IM  uint32_t  SHA_DATA4  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT4_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT5;                  /*!< CSS SHA_DATA Out Register 5                                           */

    struct {
      __IM  uint32_t  SHA_DATA5  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT5_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT6;                  /*!< CSS SHA_DATA Out Register 6                                           */

    struct {
      __IM  uint32_t  SHA_DATA6  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT6_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT7;                  /*!< CSS SHA_DATA Out Register 7                                           */

    struct {
      __IM  uint32_t  SHA_DATA7  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT7_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT8;                  /*!< CSS CSS_SHA_DATA Out Register 8                                       */

    struct {
      __IM  uint32_t  SHA_DATA8  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT8_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT9;                  /*!< CSS SHA_DATA Out Register 9                                           */

    struct {
      __IM  uint32_t  SHA_DATA9  : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT9_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT10;                 /*!< CSS SHA_DATA Out Register 10                                          */

    struct {
      __IM  uint32_t  SHA_DATA10 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT10_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT11;                 /*!< CSS SHA_DATA Out Register 11                                          */

    struct {
      __IM  uint32_t  SHA_DATA11 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT11_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT12;                 /*!< CSS SHA_DATA Out Register 12                                          */

    struct {
      __IM  uint32_t  SHA_DATA12 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT12_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT13;                 /*!< CSS SHA_DATA Out Register 13                                          */

    struct {
      __IM  uint32_t  SHA_DATA13 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT13_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT14;                 /*!< CSS SHA_DATA Out Register 14                                          */

    struct {
      __IM  uint32_t  SHA_DATA14 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT14_b;                            /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_SHA2_DOUT15;                 /*!< CSS SHA_DATA Out Register 15                                          */

    struct {
      __IM  uint32_t  SHA_DATA15 : 32;              /*!< Output SHA_DATA from CSS Application being executed                   */
    } CSS_SHA2_DOUT15_b;                            /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED3;

  union {
    __IM  uint32_t  CSS_KS0;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS0_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS0_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS0_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS0_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS0_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS0_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS0_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS0_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS0_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS0_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS0_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS0_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS0_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS0_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS0_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS0_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS0_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS0_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS0_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS0_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS0_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS0_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS0_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS0_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS0_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS0_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS0_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS1;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS1_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS1_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS1_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS1_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS1_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS1_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS1_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS1_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS1_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS1_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS1_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS1_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS1_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS1_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS1_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS1_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS1_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS1_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS1_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS1_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS1_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS1_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS1_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS1_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS1_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS1_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS1_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS2;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS2_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS2_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS2_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS2_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS2_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS2_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS2_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS2_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS2_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS2_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS2_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS2_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS2_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS2_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS2_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS2_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS2_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS2_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS2_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS2_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS2_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS2_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS2_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS2_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS2_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS2_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS2_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS3;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS3_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS3_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS3_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS3_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS3_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS3_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS3_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS3_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS3_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS3_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS3_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS3_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS3_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS3_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS3_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS3_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS3_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS3_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS3_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS3_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS3_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS3_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS3_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS3_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS3_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS3_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS3_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS4;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS4_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS4_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS4_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS4_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS4_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS4_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS4_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS4_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS4_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS4_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS4_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS4_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS4_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS4_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS4_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS4_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS4_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS4_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS4_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS4_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS4_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS4_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS4_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS4_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS4_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS4_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS4_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS5;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS5_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS5_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS5_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS5_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS5_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS5_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS5_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS5_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS5_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS5_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS5_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS5_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS5_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS5_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS5_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS5_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS5_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS5_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS5_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS5_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS5_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS5_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS5_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS5_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS5_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS5_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS5_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS6;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS6_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS6_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS6_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS6_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS6_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS6_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS6_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS6_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS6_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS6_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS6_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS6_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS6_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS6_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS6_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS6_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS6_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS6_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS6_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS6_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS6_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS6_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS6_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS6_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS6_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS6_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS6_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS7;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS7_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS7_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS7_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS7_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS7_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS7_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS7_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS7_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS7_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS7_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS7_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS7_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS7_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS7_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS7_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS7_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS7_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS7_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS7_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS7_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS7_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS7_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS7_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS7_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS7_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS7_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS7_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS8;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS8_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS8_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS8_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS8_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS8_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS8_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS8_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS8_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS8_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS8_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS8_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS8_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS8_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS8_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS8_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS8_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS8_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS8_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS8_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS8_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS8_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS8_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS8_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS8_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS8_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS8_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS8_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS9;                         /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS9_KSIZE  :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS9_RSVD0  :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS9_KACT   :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS9_KBASE  :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS9_FGP    :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS9_FRTN   :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS9_FHWO   :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS9_RSVD1  :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS9_UCMAC  :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS9_UKSK   :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS9_URTF   :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS9_UCKDF  :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS9_UHKDF  :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS9_UECSG  :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS9_UECDH  :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS9_UAES   :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS9_UHMAC  :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS9_UKWK   :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS9_UKUOK  :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS9_UTLSPMS:  1;              /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS9_UTLSMS :  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS9_UKGSRC :  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS9_UHWO   :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS9_UWRPOK :  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS9_UDUK   :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS9_UPPROT :  2;              /*!< Priviledge level                                                      */
    } CSS_KS9_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS10;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS10_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS10_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS10_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS10_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS10_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS10_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS10_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS10_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS10_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS10_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS10_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS10_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS10_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS10_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS10_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS10_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS10_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS10_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS10_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS10_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS10_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS10_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS10_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS10_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS10_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS10_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS10_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS11;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS11_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS11_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS11_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS11_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS11_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS11_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS11_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS11_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS11_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS11_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS11_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS11_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS11_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS11_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS11_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS11_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS11_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS11_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS11_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS11_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS11_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS11_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS11_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS11_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS11_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS11_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS11_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS12;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS12_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS12_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS12_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS12_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS12_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS12_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS12_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS12_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS12_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS12_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS12_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS12_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS12_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS12_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS12_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS12_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS12_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS12_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS12_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS12_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS12_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS12_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS12_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS12_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS12_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS12_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS12_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS13;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS13_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS13_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS13_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS13_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS13_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS13_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS13_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS13_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS13_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS13_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS13_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS13_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS13_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS13_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS13_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS13_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS13_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS13_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS13_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS13_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS13_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS13_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS13_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS13_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS13_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS13_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS13_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS14;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS14_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS14_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS14_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS14_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS14_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS14_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS14_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS14_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS14_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS14_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS14_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS14_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS14_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS14_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS14_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS14_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS14_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS14_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS14_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS14_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS14_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS14_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS14_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS14_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS14_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS14_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS14_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS15;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS15_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS15_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS15_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS15_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS15_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS15_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS15_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS15_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS15_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS15_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS15_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS15_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS15_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS15_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS15_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS15_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS15_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS15_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS15_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS15_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS15_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS15_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS15_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS15_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS15_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS15_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS15_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS16;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS16_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS16_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS16_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS16_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS16_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS16_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS16_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS16_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS16_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS16_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS16_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS16_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS16_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS16_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS16_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS16_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS16_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS16_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS16_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS16_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS16_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS16_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS16_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS16_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS16_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS16_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS16_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS17;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS17_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS17_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS17_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS17_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS17_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS17_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS17_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS17_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS17_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS17_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS17_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS17_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS17_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS17_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS17_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS17_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS17_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS17_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS17_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS17_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS17_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS17_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS17_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS17_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS17_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS17_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS17_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS18;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS18_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS18_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS18_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS18_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS18_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS18_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS18_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS18_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS18_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS18_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS18_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS18_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS18_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS18_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS18_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS18_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS18_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS18_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS18_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS18_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS18_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS18_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS18_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS18_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS18_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS18_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS18_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  CSS_KS19;                        /*!< Status register                                                       */

    struct {
      __IM  uint32_t  KS19_KSIZE :  1;              /*!< Key size: 0-128, 1-256                                                */
      __IM  uint32_t  KS19_RSVD0 :  4;              /*!< Reserved 0                                                            */
      __IM  uint32_t  KS19_KACT  :  1;              /*!< Key is active                                                         */
      __IM  uint32_t  KS19_KBASE :  1;              /*!< First slot in a multislot key                                         */
      __IM  uint32_t  KS19_FGP   :  1;              /*!< Hardware Feature General Purpose                                      */
      __IM  uint32_t  KS19_FRTN  :  1;              /*!< Hardware Feature Retention                                            */
      __IM  uint32_t  KS19_FHWO  :  1;              /*!< Hardware Feature Output                                               */
      __IM  uint32_t  KS19_RSVD1 :  3;              /*!< Reserved 1                                                            */
      __IM  uint32_t  KS19_UCMAC :  1;              /*!< CMAC key                                                              */
      __IM  uint32_t  KS19_UKSK  :  1;              /*!< KSK key                                                               */
      __IM  uint32_t  KS19_URTF  :  1;              /*!< Real Time Fingerprint key                                             */
      __IM  uint32_t  KS19_UCKDF :  1;              /*!< Derivation key for CKDF command                                       */
      __IM  uint32_t  KS19_UHKDF :  1;              /*!< Derivation key for HKDF command                                       */
      __IM  uint32_t  KS19_UECSG :  1;              /*!< Ecc signing key                                                       */
      __IM  uint32_t  KS19_UECDH :  1;              /*!< Ecc diffie hellman key                                                */
      __IM  uint32_t  KS19_UAES  :  1;              /*!< Aes key                                                               */
      __IM  uint32_t  KS19_UHMAC :  1;              /*!< Hmac key                                                              */
      __IM  uint32_t  KS19_UKWK  :  1;              /*!< Key wrapping key                                                      */
      __IM  uint32_t  KS19_UKUOK :  1;              /*!< Key unwrapping key                                                    */
      __IM  uint32_t  KS19_UTLSPMS:  1;             /*!< TLS Pre Master Secret                                                 */
      __IM  uint32_t  KS19_UTLSMS:  1;              /*!< TLS Master Secret                                                     */
      __IM  uint32_t  KS19_UKGSRC:  1;              /*!< Supply KEYGEN source                                                  */
      __IM  uint32_t  KS19_UHWO  :  1;              /*!< Hardware out key                                                      */
      __IM  uint32_t  KS19_UWRPOK:  1;              /*!< Ok to wrap key                                                        */
      __IM  uint32_t  KS19_UDUK  :  1;              /*!< Device Unique Key                                                     */
      __IM  uint32_t  KS19_UPPROT:  2;              /*!< Priviledge level                                                      */
    } CSS_KS19_b;                                   /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED4;

  union {
    __IOM uint32_t  CSS_BOOT_ADDR;                   /*!< SW control for the CSS boot addr                                      */

    struct {
      __IOM uint32_t  BOOT_ADDR  : 32;              /*!< 32-bit wide boot offset                                               */
    } CSS_BOOT_ADDR_b;                              /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CSS_DBG_CFG;                     /*!< CSS Debug Config SFR                                                  */

    struct {
      __IOM uint32_t  DBG_CFG0   :  3;              /*!< Debug Config 0                                                        */
      __IOM uint32_t  DBG_CFG1   :  3;              /*!< Debug Config 1                                                        */
      __IOM uint32_t  DBG_CFG_RFU: 26;              /*!< reserved                                                              */
    } CSS_DBG_CFG_b;                                /*!< BitSize                                                               */
  };
} ip_css_Type;


/* ====================  End of section using anonymous unions  =================== */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#elif defined(__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================         struct 'ip_css' Position & Mask        ================ */
/* ================================================================================ */


/* ===============================     CSS_STATUS    ============================== */
#define CSS_STATUS_CSS_BUSY_Pos               0                                                       /*!< CSS_STATUS: CSS_BUSY Position           */
#define CSS_STATUS_CSS_BUSY_Msk               (0x01UL << CSS_STATUS_CSS_BUSY_Pos)                     /*!< CSS_STATUS: CSS_BUSY Mask               */
#define CSS_STATUS_CSS_IRQ_Pos                1                                                       /*!< CSS_STATUS: CSS_IRQ Position            */
#define CSS_STATUS_CSS_IRQ_Msk                (0x01UL << CSS_STATUS_CSS_IRQ_Pos)                      /*!< CSS_STATUS: CSS_IRQ Mask                */
#define CSS_STATUS_CSS_ERR_Pos                2                                                       /*!< CSS_STATUS: CSS_ERR Position            */
#define CSS_STATUS_CSS_ERR_Msk                (0x01UL << CSS_STATUS_CSS_ERR_Pos)                      /*!< CSS_STATUS: CSS_ERR Mask                */
#define CSS_STATUS_PRNG_RDY_Pos               3                                                       /*!< CSS_STATUS: PRNG_RDY Position           */
#define CSS_STATUS_PRNG_RDY_Msk               (0x01UL << CSS_STATUS_PRNG_RDY_Pos)                     /*!< CSS_STATUS: PRNG_RDY Mask               */
#define CSS_STATUS_ECDSA_VFY_STATUS_Pos       4                                                       /*!< CSS_STATUS: ECDSA_VFY_STATUS Position   */
#define CSS_STATUS_ECDSA_VFY_STATUS_Msk       (0x03UL << CSS_STATUS_ECDSA_VFY_STATUS_Pos)             /*!< CSS_STATUS: ECDSA_VFY_STATUS Mask       */
#define CSS_STATUS_PPROT_Pos                  6                                                       /*!< CSS_STATUS: PPROT Position              */
#define CSS_STATUS_PPROT_Msk                  (0x03UL << CSS_STATUS_PPROT_Pos)                        /*!< CSS_STATUS: PPROT Mask                  */
#define CSS_STATUS_DRBG_ENT_LVL_Pos           8                                                       /*!< CSS_STATUS: DRBG_ENT_LVL Position       */
#define CSS_STATUS_DRBG_ENT_LVL_Msk           (0x03UL << CSS_STATUS_DRBG_ENT_LVL_Pos)                 /*!< CSS_STATUS: DRBG_ENT_LVL Mask           */
#define CSS_STATUS_DTRNG_BUSY_Pos             10                                                      /*!< CSS_STATUS: DTRNG_BUSY Position         */
#define CSS_STATUS_DTRNG_BUSY_Msk             (0x01UL << CSS_STATUS_DTRNG_BUSY_Pos)                   /*!< CSS_STATUS: DTRNG_BUSY Mask             */
#define CSS_STATUS_GDET_IRQ_POS_Pos           11                                                      /*!< CSS_STATUS: GDET_IRQ_POS Position       */
#define CSS_STATUS_GDET_IRQ_POS_Msk           (0x01UL << CSS_STATUS_GDET_IRQ_POS_Pos)                 /*!< CSS_STATUS: GDET_IRQ_POS Mask           */
#define CSS_STATUS_GDET_IRQ_NEG_Pos           12                                                      /*!< CSS_STATUS: GDET_IRQ_NEG Position       */
#define CSS_STATUS_GDET_IRQ_NEG_Msk           (0x01UL << CSS_STATUS_GDET_IRQ_NEG_Pos)                 /*!< CSS_STATUS: GDET_IRQ_NEG Mask           */
#define CSS_STATUS_STATUS_RSVD_Pos            13                                                      /*!< CSS_STATUS: STATUS_RSVD Position        */
#define CSS_STATUS_STATUS_RSVD_Msk            (0x0007ffffUL << CSS_STATUS_STATUS_RSVD_Pos)            /*!< CSS_STATUS: STATUS_RSVD Mask            */

/* ===============================      CSS_CTRL     ============================== */
#define CSS_CTRL_CSS_EN_Pos                   0                                                       /*!< CSS_CTRL: CSS_EN Position               */
#define CSS_CTRL_CSS_EN_Msk                   (0x01UL << CSS_CTRL_CSS_EN_Pos)                         /*!< CSS_CTRL: CSS_EN Mask                   */
#define CSS_CTRL_CSS_START_Pos                1                                                       /*!< CSS_CTRL: CSS_START Position            */
#define CSS_CTRL_CSS_START_Msk                (0x01UL << CSS_CTRL_CSS_START_Pos)                      /*!< CSS_CTRL: CSS_START Mask                */
#define CSS_CTRL_CSS_RESET_Pos                2                                                       /*!< CSS_CTRL: CSS_RESET Position            */
#define CSS_CTRL_CSS_RESET_Msk                (0x01UL << CSS_CTRL_CSS_RESET_Pos)                      /*!< CSS_CTRL: CSS_RESET Mask                */
#define CSS_CTRL_CSS_CMD_Pos                  3                                                       /*!< CSS_CTRL: CSS_CMD Position              */
#define CSS_CTRL_CSS_CMD_Msk                  (0x1fUL << CSS_CTRL_CSS_CMD_Pos)                        /*!< CSS_CTRL: CSS_CMD Mask                  */
#define CSS_CTRL_BYTE_ORDER_Pos               8                                                       /*!< CSS_CTRL: BYTE_ORDER Position           */
#define CSS_CTRL_BYTE_ORDER_Msk               (0x01UL << CSS_CTRL_BYTE_ORDER_Pos)                     /*!< CSS_CTRL: BYTE_ORDER Mask               */
#define CSS_CTRL_CTRL_RFU_Pos                 9                                                       /*!< CSS_CTRL: CTRL_RFU Position             */
#define CSS_CTRL_CTRL_RFU_Msk                 (0x007fffffUL << CSS_CTRL_CTRL_RFU_Pos)                 /*!< CSS_CTRL: CTRL_RFU Mask                 */

/* ===============================    CSS_CMDCFG0    ============================== */
#define CSS_CMDCFG0_CMDCFG0_Pos               0                                                       /*!< CSS_CMDCFG0: CMDCFG0 Position           */
#define CSS_CMDCFG0_CMDCFG0_Msk               (0xffffffffUL << CSS_CMDCFG0_CMDCFG0_Pos)               /*!< CSS_CMDCFG0: CMDCFG0 Mask               */

/* ===============================      CSS_CFG      ============================== */
#define CSS_CFG_CFG_RSVD0_Pos                 0                                                       /*!< CSS_CFG: CFG_RSVD0 Position             */
#define CSS_CFG_CFG_RSVD0_Msk                 (0x0000ffffUL << CSS_CFG_CFG_RSVD0_Pos)                 /*!< CSS_CFG: CFG_RSVD0 Mask                 */
#define CSS_CFG_ADCTRL_Pos                    16                                                      /*!< CSS_CFG: ADCTRL Position                */
#define CSS_CFG_ADCTRL_Msk                    (0x000003ffUL << CSS_CFG_ADCTRL_Pos)                    /*!< CSS_CFG: ADCTRL Mask                    */
#define CSS_CFG_CFG_RSVD1_Pos                 26                                                      /*!< CSS_CFG: CFG_RSVD1 Position             */
#define CSS_CFG_CFG_RSVD1_Msk                 (0x1fUL << CSS_CFG_CFG_RSVD1_Pos)                       /*!< CSS_CFG: CFG_RSVD1 Mask                 */
#define CSS_CFG_SHA2_DIRECT_Pos               31                                                      /*!< CSS_CFG: SHA2_DIRECT Position           */
#define CSS_CFG_SHA2_DIRECT_Msk               (0x01UL << CSS_CFG_SHA2_DIRECT_Pos)                     /*!< CSS_CFG: SHA2_DIRECT Mask               */

/* ===============================     CSS_KIDX0     ============================== */
#define CSS_KIDX0_KIDX0_Pos                   0                                                       /*!< CSS_KIDX0: KIDX0 Position               */
#define CSS_KIDX0_KIDX0_Msk                   (0x7fUL << CSS_KIDX0_KIDX0_Pos)                         /*!< CSS_KIDX0: KIDX0 Mask                   */
#define CSS_KIDX0_RESERVED_Pos                7                                                       /*!< CSS_KIDX0: RESERVED Position            */
#define CSS_KIDX0_RESERVED_Msk                (0x01ffffffUL << CSS_KIDX0_RESERVED_Pos)                /*!< CSS_KIDX0: RESERVED Mask                */

/* ===============================     CSS_KIDX1     ============================== */
#define CSS_KIDX1_KIDX1_Pos                   0                                                       /*!< CSS_KIDX1: KIDX1 Position               */
#define CSS_KIDX1_KIDX1_Msk                   (0x7fUL << CSS_KIDX1_KIDX1_Pos)                         /*!< CSS_KIDX1: KIDX1 Mask                   */
#define CSS_KIDX1_RESERVED_Pos                7                                                       /*!< CSS_KIDX1: RESERVED Position            */
#define CSS_KIDX1_RESERVED_Msk                (0x01ffffffUL << CSS_KIDX1_RESERVED_Pos)                /*!< CSS_KIDX1: RESERVED Mask                */

/* ===============================    CSS_KPROPIN    ============================== */
#define CSS_KPROPIN_KPROPIN_Pos               0                                                       /*!< CSS_KPROPIN: KPROPIN Position           */
#define CSS_KPROPIN_KPROPIN_Msk               (0xffffffffUL << CSS_KPROPIN_KPROPIN_Pos)               /*!< CSS_KPROPIN: KPROPIN Mask               */

/* ===============================    CSS_DMA_SRC0   ============================== */
#define CSS_DMA_SRC0_ADDR_SRC0_Pos            0                                                       /*!< CSS_DMA_SRC0: ADDR_SRC0 Position        */
#define CSS_DMA_SRC0_ADDR_SRC0_Msk            (0xffffffffUL << CSS_DMA_SRC0_ADDR_SRC0_Pos)            /*!< CSS_DMA_SRC0: ADDR_SRC0 Mask            */

/* ===============================  CSS_DMA_SRC0_LEN ============================== */
#define CSS_DMA_SRC0_LEN_SIZE_SRC0_LEN_Pos    0                                                       /*!< CSS_DMA_SRC0_LEN: SIZE_SRC0_LEN Position*/
#define CSS_DMA_SRC0_LEN_SIZE_SRC0_LEN_Msk    (0xffffffffUL << CSS_DMA_SRC0_LEN_SIZE_SRC0_LEN_Pos)    /*!< CSS_DMA_SRC0_LEN: SIZE_SRC0_LEN Mask    */

/* ===============================    CSS_DMA_SRC1   ============================== */
#define CSS_DMA_SRC1_ADDR_SRC1_Pos            0                                                       /*!< CSS_DMA_SRC1: ADDR_SRC1 Position        */
#define CSS_DMA_SRC1_ADDR_SRC1_Msk            (0xffffffffUL << CSS_DMA_SRC1_ADDR_SRC1_Pos)            /*!< CSS_DMA_SRC1: ADDR_SRC1 Mask            */

/* ===============================    CSS_DMA_SRC2   ============================== */
#define CSS_DMA_SRC2_ADDR_SRC2_Pos            0                                                       /*!< CSS_DMA_SRC2: ADDR_SRC2 Position        */
#define CSS_DMA_SRC2_ADDR_SRC2_Msk            (0xffffffffUL << CSS_DMA_SRC2_ADDR_SRC2_Pos)            /*!< CSS_DMA_SRC2: ADDR_SRC2 Mask            */

/* ===============================  CSS_DMA_SRC2_LEN ============================== */
#define CSS_DMA_SRC2_LEN_SIZE_SRC2_LEN_Pos    0                                                       /*!< CSS_DMA_SRC2_LEN: SIZE_SRC2_LEN Position*/
#define CSS_DMA_SRC2_LEN_SIZE_SRC2_LEN_Msk    (0xffffffffUL << CSS_DMA_SRC2_LEN_SIZE_SRC2_LEN_Pos)    /*!< CSS_DMA_SRC2_LEN: SIZE_SRC2_LEN Mask    */

/* ===============================    CSS_DMA_RES0   ============================== */
#define CSS_DMA_RES0_ADDR_RES0_Pos            0                                                       /*!< CSS_DMA_RES0: ADDR_RES0 Position        */
#define CSS_DMA_RES0_ADDR_RES0_Msk            (0xffffffffUL << CSS_DMA_RES0_ADDR_RES0_Pos)            /*!< CSS_DMA_RES0: ADDR_RES0 Mask            */

/* ===============================  CSS_DMA_RES0_LEN ============================== */
#define CSS_DMA_RES0_LEN_SIZE_RES0_LEN_Pos    0                                                       /*!< CSS_DMA_RES0_LEN: SIZE_RES0_LEN Position*/
#define CSS_DMA_RES0_LEN_SIZE_RES0_LEN_Msk    (0xffffffffUL << CSS_DMA_RES0_LEN_SIZE_RES0_LEN_Pos)    /*!< CSS_DMA_RES0_LEN: SIZE_RES0_LEN Mask    */

/* ===============================   CSS_INT_ENABLE  ============================== */
#define CSS_INT_ENABLE_INT_EN_Pos             0                                                       /*!< CSS_INT_ENABLE: INT_EN Position         */
#define CSS_INT_ENABLE_INT_EN_Msk             (0x01UL << CSS_INT_ENABLE_INT_EN_Pos)                   /*!< CSS_INT_ENABLE: INT_EN Mask             */
#define CSS_INT_ENABLE_GDET_INT_EN_Pos        1                                                       /*!< CSS_INT_ENABLE: GDET_INT_EN Position    */
#define CSS_INT_ENABLE_GDET_INT_EN_Msk        (0x01UL << CSS_INT_ENABLE_GDET_INT_EN_Pos)              /*!< CSS_INT_ENABLE: GDET_INT_EN Mask        */
#define CSS_INT_ENABLE_INT_ENA_RSVD_Pos       2                                                       /*!< CSS_INT_ENABLE: INT_ENA_RSVD Position   */
#define CSS_INT_ENABLE_INT_ENA_RSVD_Msk       (0x3fffffffUL << CSS_INT_ENABLE_INT_ENA_RSVD_Pos)       /*!< CSS_INT_ENABLE: INT_ENA_RSVD Mask       */

/* =============================== CSS_INT_STATUS_CLR ============================== */
#define CSS_INT_STATUS_CLR_INT_CLR_Pos        0                                                       /*!< CSS_INT_STATUS_CLR: INT_CLR Position    */
#define CSS_INT_STATUS_CLR_INT_CLR_Msk        (0x01UL << CSS_INT_STATUS_CLR_INT_CLR_Pos)              /*!< CSS_INT_STATUS_CLR: INT_CLR Mask        */
#define CSS_INT_STATUS_CLR_GDET_INT_CLR_Pos   1                                                       /*!< CSS_INT_STATUS_CLR: GDET_INT_CLR Position*/
#define CSS_INT_STATUS_CLR_GDET_INT_CLR_Msk   (0x01UL << CSS_INT_STATUS_CLR_GDET_INT_CLR_Pos)         /*!< CSS_INT_STATUS_CLR: GDET_INT_CLR Mask   */
#define CSS_INT_STATUS_CLR_INT_STSC_RSVD_Pos  2                                                       /*!< CSS_INT_STATUS_CLR: INT_STSC_RSVD Position*/
#define CSS_INT_STATUS_CLR_INT_STSC_RSVD_Msk  (0x3fffffffUL << CSS_INT_STATUS_CLR_INT_STSC_RSVD_Pos)  /*!< CSS_INT_STATUS_CLR: INT_STSC_RSVD Mask  */

/* =============================== CSS_INT_STATUS_SET ============================== */
#define CSS_INT_STATUS_SET_INT_SET_Pos        0                                                       /*!< CSS_INT_STATUS_SET: INT_SET Position    */
#define CSS_INT_STATUS_SET_INT_SET_Msk        (0x01UL << CSS_INT_STATUS_SET_INT_SET_Pos)              /*!< CSS_INT_STATUS_SET: INT_SET Mask        */
#define CSS_INT_STATUS_SET_GDET_INT_NEG_SET_Pos 1                                                       /*!< CSS_INT_STATUS_SET: GDET_INT_NEG_SET Position*/
#define CSS_INT_STATUS_SET_GDET_INT_NEG_SET_Msk (0x01UL << CSS_INT_STATUS_SET_GDET_INT_NEG_SET_Pos)     /*!< CSS_INT_STATUS_SET: GDET_INT_NEG_SET Mask*/
#define CSS_INT_STATUS_SET_GDET_INT_POS_SET_Pos 2                                                       /*!< CSS_INT_STATUS_SET: GDET_INT_POS_SET Position*/
#define CSS_INT_STATUS_SET_GDET_INT_POS_SET_Msk (0x01UL << CSS_INT_STATUS_SET_GDET_INT_POS_SET_Pos)     /*!< CSS_INT_STATUS_SET: GDET_INT_POS_SET Mask*/
#define CSS_INT_STATUS_SET_INT_STSS_RSVD_Pos  3                                                       /*!< CSS_INT_STATUS_SET: INT_STSS_RSVD Position*/
#define CSS_INT_STATUS_SET_INT_STSS_RSVD_Msk  (0x1fffffffUL << CSS_INT_STATUS_SET_INT_STSS_RSVD_Pos)  /*!< CSS_INT_STATUS_SET: INT_STSS_RSVD Mask  */

/* ===============================   CSS_ERR_STATUS  ============================== */
#define CSS_ERR_STATUS_BUS_ERR_Pos            0                                                       /*!< CSS_ERR_STATUS: BUS_ERR Position        */
#define CSS_ERR_STATUS_BUS_ERR_Msk            (0x01UL << CSS_ERR_STATUS_BUS_ERR_Pos)                  /*!< CSS_ERR_STATUS: BUS_ERR Mask            */
#define CSS_ERR_STATUS_OPN_ERR_Pos            1                                                       /*!< CSS_ERR_STATUS: OPN_ERR Position        */
#define CSS_ERR_STATUS_OPN_ERR_Msk            (0x01UL << CSS_ERR_STATUS_OPN_ERR_Pos)                  /*!< CSS_ERR_STATUS: OPN_ERR Mask            */
#define CSS_ERR_STATUS_ALG_ERR_Pos            2                                                       /*!< CSS_ERR_STATUS: ALG_ERR Position        */
#define CSS_ERR_STATUS_ALG_ERR_Msk            (0x01UL << CSS_ERR_STATUS_ALG_ERR_Pos)                  /*!< CSS_ERR_STATUS: ALG_ERR Mask            */
#define CSS_ERR_STATUS_ITG_ERR_Pos            3                                                       /*!< CSS_ERR_STATUS: ITG_ERR Position        */
#define CSS_ERR_STATUS_ITG_ERR_Msk            (0x01UL << CSS_ERR_STATUS_ITG_ERR_Pos)                  /*!< CSS_ERR_STATUS: ITG_ERR Mask            */
#define CSS_ERR_STATUS_FLT_ERR_Pos            4                                                       /*!< CSS_ERR_STATUS: FLT_ERR Position        */
#define CSS_ERR_STATUS_FLT_ERR_Msk            (0x01UL << CSS_ERR_STATUS_FLT_ERR_Pos)                  /*!< CSS_ERR_STATUS: FLT_ERR Mask            */
#define CSS_ERR_STATUS_PRNG_ERR_Pos           5                                                       /*!< CSS_ERR_STATUS: PRNG_ERR Position       */
#define CSS_ERR_STATUS_PRNG_ERR_Msk           (0x01UL << CSS_ERR_STATUS_PRNG_ERR_Pos)                 /*!< CSS_ERR_STATUS: PRNG_ERR Mask           */
#define CSS_ERR_STATUS_ERR_LVL_Pos            6                                                       /*!< CSS_ERR_STATUS: ERR_LVL Position        */
#define CSS_ERR_STATUS_ERR_LVL_Msk            (0x03UL << CSS_ERR_STATUS_ERR_LVL_Pos)                  /*!< CSS_ERR_STATUS: ERR_LVL Mask            */
#define CSS_ERR_STATUS_DTRNG_ERR_Pos          8                                                       /*!< CSS_ERR_STATUS: DTRNG_ERR Position      */
#define CSS_ERR_STATUS_DTRNG_ERR_Msk          (0x01UL << CSS_ERR_STATUS_DTRNG_ERR_Pos)                /*!< CSS_ERR_STATUS: DTRNG_ERR Mask          */
#define CSS_ERR_STATUS_ERR_STAT_RSVD_Pos      9                                                       /*!< CSS_ERR_STATUS: ERR_STAT_RSVD Position  */
#define CSS_ERR_STATUS_ERR_STAT_RSVD_Msk      (0x007fffffUL << CSS_ERR_STATUS_ERR_STAT_RSVD_Pos)      /*!< CSS_ERR_STATUS: ERR_STAT_RSVD Mask      */

/* =============================== CSS_ERR_STATUS_CLR ============================== */
#define CSS_ERR_STATUS_CLR_ERR_CLR_Pos        0                                                       /*!< CSS_ERR_STATUS_CLR: ERR_CLR Position    */
#define CSS_ERR_STATUS_CLR_ERR_CLR_Msk        (0x01UL << CSS_ERR_STATUS_CLR_ERR_CLR_Pos)              /*!< CSS_ERR_STATUS_CLR: ERR_CLR Mask        */
#define CSS_ERR_STATUS_CLR_ERR_STSC_RSVD_Pos  1                                                       /*!< CSS_ERR_STATUS_CLR: ERR_STSC_RSVD Position*/
#define CSS_ERR_STATUS_CLR_ERR_STSC_RSVD_Msk  (0x7fffffffUL << CSS_ERR_STATUS_CLR_ERR_STSC_RSVD_Pos)  /*!< CSS_ERR_STATUS_CLR: ERR_STSC_RSVD Mask  */

/* ===============================    CSS_VERSION    ============================== */
#define CSS_VERSION_Z_Pos                     0                                                       /*!< CSS_VERSION: Z Position                 */
#define CSS_VERSION_Z_Msk                     (0x0fUL << CSS_VERSION_Z_Pos)                           /*!< CSS_VERSION: Z Mask                     */
#define CSS_VERSION_Y2_Pos                    4                                                       /*!< CSS_VERSION: Y2 Position                */
#define CSS_VERSION_Y2_Msk                    (0x0fUL << CSS_VERSION_Y2_Pos)                          /*!< CSS_VERSION: Y2 Mask                    */
#define CSS_VERSION_Y1_Pos                    8                                                       /*!< CSS_VERSION: Y1 Position                */
#define CSS_VERSION_Y1_Msk                    (0x0fUL << CSS_VERSION_Y1_Pos)                          /*!< CSS_VERSION: Y1 Mask                    */
#define CSS_VERSION_X_Pos                     12                                                      /*!< CSS_VERSION: X Position                 */
#define CSS_VERSION_X_Msk                     (0x0fUL << CSS_VERSION_X_Pos)                           /*!< CSS_VERSION: X Mask                     */
#define CSS_VERSION_VERSION_RSVD_Pos          16                                                      /*!< CSS_VERSION: VERSION_RSVD Position      */
#define CSS_VERSION_VERSION_RSVD_Msk          (0x0000ffffUL << CSS_VERSION_VERSION_RSVD_Pos)          /*!< CSS_VERSION: VERSION_RSVD Mask          */

/* ===============================     CSS_CONFIG    ============================== */
#define CSS_CONFIG_CIPHER_SUP_Pos             0                                                       /*!< CSS_CONFIG: CIPHER_SUP Position         */
#define CSS_CONFIG_CIPHER_SUP_Msk             (0x01UL << CSS_CONFIG_CIPHER_SUP_Pos)                   /*!< CSS_CONFIG: CIPHER_SUP Mask             */
#define CSS_CONFIG_AUTH_CIPHER_SUP_Pos        1                                                       /*!< CSS_CONFIG: AUTH_CIPHER_SUP Position    */
#define CSS_CONFIG_AUTH_CIPHER_SUP_Msk        (0x01UL << CSS_CONFIG_AUTH_CIPHER_SUP_Pos)              /*!< CSS_CONFIG: AUTH_CIPHER_SUP Mask        */
#define CSS_CONFIG_ECSIGN_SUP_Pos             2                                                       /*!< CSS_CONFIG: ECSIGN_SUP Position         */
#define CSS_CONFIG_ECSIGN_SUP_Msk             (0x01UL << CSS_CONFIG_ECSIGN_SUP_Pos)                   /*!< CSS_CONFIG: ECSIGN_SUP Mask             */
#define CSS_CONFIG_ECVFY_SUP_Pos              3                                                       /*!< CSS_CONFIG: ECVFY_SUP Position          */
#define CSS_CONFIG_ECVFY_SUP_Msk              (0x01UL << CSS_CONFIG_ECVFY_SUP_Pos)                    /*!< CSS_CONFIG: ECVFY_SUP Mask              */
#define CSS_CONFIG_ECKXCH_SUP_Pos             4                                                       /*!< CSS_CONFIG: ECKXCH_SUP Position         */
#define CSS_CONFIG_ECKXCH_SUP_Msk             (0x01UL << CSS_CONFIG_ECKXCH_SUP_Pos)                   /*!< CSS_CONFIG: ECKXCH_SUP Mask             */
#define CSS_CONFIG_KEYGEN_SUP_Pos             5                                                       /*!< CSS_CONFIG: KEYGEN_SUP Position         */
#define CSS_CONFIG_KEYGEN_SUP_Msk             (0x01UL << CSS_CONFIG_KEYGEN_SUP_Pos)                   /*!< CSS_CONFIG: KEYGEN_SUP Mask             */
#define CSS_CONFIG_KEYIN_SUP_Pos              6                                                       /*!< CSS_CONFIG: KEYIN_SUP Position          */
#define CSS_CONFIG_KEYIN_SUP_Msk              (0x01UL << CSS_CONFIG_KEYIN_SUP_Pos)                    /*!< CSS_CONFIG: KEYIN_SUP Mask              */
#define CSS_CONFIG_KEYOUT_SUP_Pos             7                                                       /*!< CSS_CONFIG: KEYOUT_SUP Position         */
#define CSS_CONFIG_KEYOUT_SUP_Msk             (0x01UL << CSS_CONFIG_KEYOUT_SUP_Pos)                   /*!< CSS_CONFIG: KEYOUT_SUP Mask             */
#define CSS_CONFIG_KDELETE_SUP_Pos            8                                                       /*!< CSS_CONFIG: KDELETE_SUP Position        */
#define CSS_CONFIG_KDELETE_SUP_Msk            (0x01UL << CSS_CONFIG_KDELETE_SUP_Pos)                  /*!< CSS_CONFIG: KDELETE_SUP Mask            */
#define CSS_CONFIG_KEYPROV_SUP_Pos            9                                                       /*!< CSS_CONFIG: KEYPROV_SUP Position        */
#define CSS_CONFIG_KEYPROV_SUP_Msk            (0x01UL << CSS_CONFIG_KEYPROV_SUP_Pos)                  /*!< CSS_CONFIG: KEYPROV_SUP Mask            */
#define CSS_CONFIG_CKDF_SUP_Pos               10                                                      /*!< CSS_CONFIG: CKDF_SUP Position           */
#define CSS_CONFIG_CKDF_SUP_Msk               (0x01UL << CSS_CONFIG_CKDF_SUP_Pos)                     /*!< CSS_CONFIG: CKDF_SUP Mask               */
#define CSS_CONFIG_HKDF_SUP_Pos               11                                                      /*!< CSS_CONFIG: HKDF_SUP Position           */
#define CSS_CONFIG_HKDF_SUP_Msk               (0x01UL << CSS_CONFIG_HKDF_SUP_Pos)                     /*!< CSS_CONFIG: HKDF_SUP Mask               */
#define CSS_CONFIG_TLS_INIT_SUP_Pos           12                                                      /*!< CSS_CONFIG: TLS_INIT_SUP Position       */
#define CSS_CONFIG_TLS_INIT_SUP_Msk           (0x01UL << CSS_CONFIG_TLS_INIT_SUP_Pos)                 /*!< CSS_CONFIG: TLS_INIT_SUP Mask           */
#define CSS_CONFIG_HASH_SUP_Pos               13                                                      /*!< CSS_CONFIG: HASH_SUP Position           */
#define CSS_CONFIG_HASH_SUP_Msk               (0x01UL << CSS_CONFIG_HASH_SUP_Pos)                     /*!< CSS_CONFIG: HASH_SUP Mask               */
#define CSS_CONFIG_HMAC_SUP_Pos               14                                                      /*!< CSS_CONFIG: HMAC_SUP Position           */
#define CSS_CONFIG_HMAC_SUP_Msk               (0x01UL << CSS_CONFIG_HMAC_SUP_Pos)                     /*!< CSS_CONFIG: HMAC_SUP Mask               */
#define CSS_CONFIG_CMAC_SUP_Pos               15                                                      /*!< CSS_CONFIG: CMAC_SUP Position           */
#define CSS_CONFIG_CMAC_SUP_Msk               (0x01UL << CSS_CONFIG_CMAC_SUP_Pos)                     /*!< CSS_CONFIG: CMAC_SUP Mask               */
#define CSS_CONFIG_DRBG_REQ_SUP_Pos           16                                                      /*!< CSS_CONFIG: DRBG_REQ_SUP Position       */
#define CSS_CONFIG_DRBG_REQ_SUP_Msk           (0x01UL << CSS_CONFIG_DRBG_REQ_SUP_Pos)                 /*!< CSS_CONFIG: DRBG_REQ_SUP Mask           */
#define CSS_CONFIG_DRBG_TEST_SUP_Pos          17                                                      /*!< CSS_CONFIG: DRBG_TEST_SUP Position      */
#define CSS_CONFIG_DRBG_TEST_SUP_Msk          (0x01UL << CSS_CONFIG_DRBG_TEST_SUP_Pos)                /*!< CSS_CONFIG: DRBG_TEST_SUP Mask          */
#define CSS_CONFIG_DTRNG_CFG_LOAD_SUP_Pos     18                                                      /*!< CSS_CONFIG: DTRNG_CFG_LOAD_SUP Position */
#define CSS_CONFIG_DTRNG_CFG_LOAD_SUP_Msk     (0x01UL << CSS_CONFIG_DTRNG_CFG_LOAD_SUP_Pos)           /*!< CSS_CONFIG: DTRNG_CFG_LOAD_SUP Mask     */
#define CSS_CONFIG_DTRNG_EVAL_SUP_Pos         19                                                      /*!< CSS_CONFIG: DTRNG_EVAL_SUP Position     */
#define CSS_CONFIG_DTRNG_EVAL_SUP_Msk         (0x01UL << CSS_CONFIG_DTRNG_EVAL_SUP_Pos)               /*!< CSS_CONFIG: DTRNG_EVAL_SUP Mask         */
#define CSS_CONFIG_GDET_CFG_LOAD_SUP_Pos      20                                                      /*!< CSS_CONFIG: GDET_CFG_LOAD_SUP Position  */
#define CSS_CONFIG_GDET_CFG_LOAD_SUP_Msk      (0x01UL << CSS_CONFIG_GDET_CFG_LOAD_SUP_Pos)            /*!< CSS_CONFIG: GDET_CFG_LOAD_SUP Mask      */
#define CSS_CONFIG_GDET_TRIM_SUP_Pos          21                                                      /*!< CSS_CONFIG: GDET_TRIM_SUP Position      */
#define CSS_CONFIG_GDET_TRIM_SUP_Msk          (0x01UL << CSS_CONFIG_GDET_TRIM_SUP_Pos)                /*!< CSS_CONFIG: GDET_TRIM_SUP Mask          */
#define CSS_CONFIG_CONFIG_RSVD_Pos            22                                                      /*!< CSS_CONFIG: CONFIG_RSVD Position        */
#define CSS_CONFIG_CONFIG_RSVD_Msk            (0x000003ffUL << CSS_CONFIG_CONFIG_RSVD_Pos)            /*!< CSS_CONFIG: CONFIG_RSVD Mask            */

/* ===============================  CSS_PRNG_DATOUT  ============================== */
#define CSS_PRNG_DATOUT_PRNG_DATOUT_Pos       0                                                       /*!< CSS_PRNG_DATOUT: PRNG_DATOUT Position   */
#define CSS_PRNG_DATOUT_PRNG_DATOUT_Msk       (0xffffffffUL << CSS_PRNG_DATOUT_PRNG_DATOUT_Pos)       /*!< CSS_PRNG_DATOUT: PRNG_DATOUT Mask       */

/* ===============================  CSS_GDET_EVTCNT  ============================== */
#define CSS_GDET_EVTCNT_GDET_EVTCNT_Pos       0                                                       /*!< CSS_GDET_EVTCNT: GDET_EVTCNT Position   */
#define CSS_GDET_EVTCNT_GDET_EVTCNT_Msk       (0x000000ffUL << CSS_GDET_EVTCNT_GDET_EVTCNT_Pos)       /*!< CSS_GDET_EVTCNT: GDET_EVTCNT Mask       */
#define CSS_GDET_EVTCNT_GDET_EVTCNT_CLR_DONE_Pos 8                                                       /*!< CSS_GDET_EVTCNT: GDET_EVTCNT_CLR_DONE Position*/
#define CSS_GDET_EVTCNT_GDET_EVTCNT_CLR_DONE_Msk (0x01UL << CSS_GDET_EVTCNT_GDET_EVTCNT_CLR_DONE_Pos)    /*!< CSS_GDET_EVTCNT: GDET_EVTCNT_CLR_DONE Mask*/
#define CSS_GDET_EVTCNT_GDET_EVTCNT_RSVD_Pos  9                                                       /*!< CSS_GDET_EVTCNT: GDET_EVTCNT_RSVD Position*/
#define CSS_GDET_EVTCNT_GDET_EVTCNT_RSVD_Msk  (0x007fffffUL << CSS_GDET_EVTCNT_GDET_EVTCNT_RSVD_Pos)  /*!< CSS_GDET_EVTCNT: GDET_EVTCNT_RSVD Mask  */

/* =============================== CSS_GDET_EVTCNT_CLR ============================== */
#define CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_Pos 0                                                       /*!< CSS_GDET_EVTCNT_CLR: GDET_EVTCNT_CLR Position*/
#define CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_Msk (0x01UL << CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_Pos)     /*!< CSS_GDET_EVTCNT_CLR: GDET_EVTCNT_CLR Mask*/
#define CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_RSVD_Pos 1                                                       /*!< CSS_GDET_EVTCNT_CLR: GDET_EVTCNT_CLR_RSVD Position*/
#define CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_RSVD_Msk (0x7fffffffUL << CSS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_RSVD_Pos)/*!< CSS_GDET_EVTCNT_CLR: GDET_EVTCNT_CLR_RSVD Mask*/

/* ===============================  CSS_SHA2_STATUS  ============================== */
#define CSS_SHA2_STATUS_SHA2_BUSY_Pos         0                                                       /*!< CSS_SHA2_STATUS: SHA2_BUSY Position     */
#define CSS_SHA2_STATUS_SHA2_BUSY_Msk         (0x01UL << CSS_SHA2_STATUS_SHA2_BUSY_Pos)               /*!< CSS_SHA2_STATUS: SHA2_BUSY Mask         */
#define CSS_SHA2_STATUS_STATUS_RSVD1_Pos      1                                                       /*!< CSS_SHA2_STATUS: STATUS_RSVD1 Position  */
#define CSS_SHA2_STATUS_STATUS_RSVD1_Msk      (0x7fffffffUL << CSS_SHA2_STATUS_STATUS_RSVD1_Pos)      /*!< CSS_SHA2_STATUS: STATUS_RSVD1 Mask      */

/* ===============================   CSS_SHA2_CTRL   ============================== */
#define CSS_SHA2_CTRL_SHA2_START_Pos          0                                                       /*!< CSS_SHA2_CTRL: SHA2_START Position      */
#define CSS_SHA2_CTRL_SHA2_START_Msk          (0x01UL << CSS_SHA2_CTRL_SHA2_START_Pos)                /*!< CSS_SHA2_CTRL: SHA2_START Mask          */
#define CSS_SHA2_CTRL_SHA2_RST_Pos            1                                                       /*!< CSS_SHA2_CTRL: SHA2_RST Position        */
#define CSS_SHA2_CTRL_SHA2_RST_Msk            (0x01UL << CSS_SHA2_CTRL_SHA2_RST_Pos)                  /*!< CSS_SHA2_CTRL: SHA2_RST Mask            */
#define CSS_SHA2_CTRL_SHA2_INIT_Pos           2                                                       /*!< CSS_SHA2_CTRL: SHA2_INIT Position       */
#define CSS_SHA2_CTRL_SHA2_INIT_Msk           (0x01UL << CSS_SHA2_CTRL_SHA2_INIT_Pos)                 /*!< CSS_SHA2_CTRL: SHA2_INIT Mask           */
#define CSS_SHA2_CTRL_SHA2_LOAD_Pos           3                                                       /*!< CSS_SHA2_CTRL: SHA2_LOAD Position       */
#define CSS_SHA2_CTRL_SHA2_LOAD_Msk           (0x01UL << CSS_SHA2_CTRL_SHA2_LOAD_Pos)                 /*!< CSS_SHA2_CTRL: SHA2_LOAD Mask           */
#define CSS_SHA2_CTRL_SHA2_MODE_Pos           4                                                       /*!< CSS_SHA2_CTRL: SHA2_MODE Position       */
#define CSS_SHA2_CTRL_SHA2_MODE_Msk           (0x03UL << CSS_SHA2_CTRL_SHA2_MODE_Pos)                 /*!< CSS_SHA2_CTRL: SHA2_MODE Mask           */
#define CSS_SHA2_CTRL_CTRL_RSVD1_Pos          6                                                       /*!< CSS_SHA2_CTRL: CTRL_RSVD1 Position      */
#define CSS_SHA2_CTRL_CTRL_RSVD1_Msk          (0x07UL << CSS_SHA2_CTRL_CTRL_RSVD1_Pos)                /*!< CSS_SHA2_CTRL: CTRL_RSVD1 Mask          */
#define CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Pos     9                                                       /*!< CSS_SHA2_CTRL: SHA2_BYTE_ORDER Position */
#define CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Msk     (0x01UL << CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Pos)           /*!< CSS_SHA2_CTRL: SHA2_BYTE_ORDER Mask     */
#define CSS_SHA2_CTRL_CTRL_RSVD_Pos           10                                                      /*!< CSS_SHA2_CTRL: CTRL_RSVD Position       */
#define CSS_SHA2_CTRL_CTRL_RSVD_Msk           (0x003fffffUL << CSS_SHA2_CTRL_CTRL_RSVD_Pos)           /*!< CSS_SHA2_CTRL: CTRL_RSVD Mask           */

/* ===============================    CSS_SHA2_DIN   ============================== */
#define CSS_SHA2_DIN_SHA_DATIN_Pos            0                                                       /*!< CSS_SHA2_DIN: SHA_DATIN Position        */
#define CSS_SHA2_DIN_SHA_DATIN_Msk            (0xffffffffUL << CSS_SHA2_DIN_SHA_DATIN_Pos)            /*!< CSS_SHA2_DIN: SHA_DATIN Mask            */

/* ===============================   CSS_SHA2_DOUT0  ============================== */
#define CSS_SHA2_DOUT0_SHA_DATA0_Pos          0                                                       /*!< CSS_SHA2_DOUT0: SHA_DATA0 Position      */
#define CSS_SHA2_DOUT0_SHA_DATA0_Msk          (0xffffffffUL << CSS_SHA2_DOUT0_SHA_DATA0_Pos)          /*!< CSS_SHA2_DOUT0: SHA_DATA0 Mask          */

/* ===============================   CSS_SHA2_DOUT1  ============================== */
#define CSS_SHA2_DOUT1_SHA_DATA1_Pos          0                                                       /*!< CSS_SHA2_DOUT1: SHA_DATA1 Position      */
#define CSS_SHA2_DOUT1_SHA_DATA1_Msk          (0xffffffffUL << CSS_SHA2_DOUT1_SHA_DATA1_Pos)          /*!< CSS_SHA2_DOUT1: SHA_DATA1 Mask          */

/* ===============================   CSS_SHA2_DOUT2  ============================== */
#define CSS_SHA2_DOUT2_SHA_DATA2_Pos          0                                                       /*!< CSS_SHA2_DOUT2: SHA_DATA2 Position      */
#define CSS_SHA2_DOUT2_SHA_DATA2_Msk          (0xffffffffUL << CSS_SHA2_DOUT2_SHA_DATA2_Pos)          /*!< CSS_SHA2_DOUT2: SHA_DATA2 Mask          */

/* ===============================   CSS_SHA2_DOUT3  ============================== */
#define CSS_SHA2_DOUT3_SHA_DATA3_Pos          0                                                       /*!< CSS_SHA2_DOUT3: SHA_DATA3 Position      */
#define CSS_SHA2_DOUT3_SHA_DATA3_Msk          (0xffffffffUL << CSS_SHA2_DOUT3_SHA_DATA3_Pos)          /*!< CSS_SHA2_DOUT3: SHA_DATA3 Mask          */

/* ===============================   CSS_SHA2_DOUT4  ============================== */
#define CSS_SHA2_DOUT4_SHA_DATA4_Pos          0                                                       /*!< CSS_SHA2_DOUT4: SHA_DATA4 Position      */
#define CSS_SHA2_DOUT4_SHA_DATA4_Msk          (0xffffffffUL << CSS_SHA2_DOUT4_SHA_DATA4_Pos)          /*!< CSS_SHA2_DOUT4: SHA_DATA4 Mask          */

/* ===============================   CSS_SHA2_DOUT5  ============================== */
#define CSS_SHA2_DOUT5_SHA_DATA5_Pos          0                                                       /*!< CSS_SHA2_DOUT5: SHA_DATA5 Position      */
#define CSS_SHA2_DOUT5_SHA_DATA5_Msk          (0xffffffffUL << CSS_SHA2_DOUT5_SHA_DATA5_Pos)          /*!< CSS_SHA2_DOUT5: SHA_DATA5 Mask          */

/* ===============================   CSS_SHA2_DOUT6  ============================== */
#define CSS_SHA2_DOUT6_SHA_DATA6_Pos          0                                                       /*!< CSS_SHA2_DOUT6: SHA_DATA6 Position      */
#define CSS_SHA2_DOUT6_SHA_DATA6_Msk          (0xffffffffUL << CSS_SHA2_DOUT6_SHA_DATA6_Pos)          /*!< CSS_SHA2_DOUT6: SHA_DATA6 Mask          */

/* ===============================   CSS_SHA2_DOUT7  ============================== */
#define CSS_SHA2_DOUT7_SHA_DATA7_Pos          0                                                       /*!< CSS_SHA2_DOUT7: SHA_DATA7 Position      */
#define CSS_SHA2_DOUT7_SHA_DATA7_Msk          (0xffffffffUL << CSS_SHA2_DOUT7_SHA_DATA7_Pos)          /*!< CSS_SHA2_DOUT7: SHA_DATA7 Mask          */

/* ===============================   CSS_SHA2_DOUT8  ============================== */
#define CSS_SHA2_DOUT8_SHA_DATA8_Pos          0                                                       /*!< CSS_SHA2_DOUT8: SHA_DATA8 Position      */
#define CSS_SHA2_DOUT8_SHA_DATA8_Msk          (0xffffffffUL << CSS_SHA2_DOUT8_SHA_DATA8_Pos)          /*!< CSS_SHA2_DOUT8: SHA_DATA8 Mask          */

/* ===============================   CSS_SHA2_DOUT9  ============================== */
#define CSS_SHA2_DOUT9_SHA_DATA9_Pos          0                                                       /*!< CSS_SHA2_DOUT9: SHA_DATA9 Position      */
#define CSS_SHA2_DOUT9_SHA_DATA9_Msk          (0xffffffffUL << CSS_SHA2_DOUT9_SHA_DATA9_Pos)          /*!< CSS_SHA2_DOUT9: SHA_DATA9 Mask          */

/* ===============================  CSS_SHA2_DOUT10  ============================== */
#define CSS_SHA2_DOUT10_SHA_DATA10_Pos        0                                                       /*!< CSS_SHA2_DOUT10: SHA_DATA10 Position    */
#define CSS_SHA2_DOUT10_SHA_DATA10_Msk        (0xffffffffUL << CSS_SHA2_DOUT10_SHA_DATA10_Pos)        /*!< CSS_SHA2_DOUT10: SHA_DATA10 Mask        */

/* ===============================  CSS_SHA2_DOUT11  ============================== */
#define CSS_SHA2_DOUT11_SHA_DATA11_Pos        0                                                       /*!< CSS_SHA2_DOUT11: SHA_DATA11 Position    */
#define CSS_SHA2_DOUT11_SHA_DATA11_Msk        (0xffffffffUL << CSS_SHA2_DOUT11_SHA_DATA11_Pos)        /*!< CSS_SHA2_DOUT11: SHA_DATA11 Mask        */

/* ===============================  CSS_SHA2_DOUT12  ============================== */
#define CSS_SHA2_DOUT12_SHA_DATA12_Pos        0                                                       /*!< CSS_SHA2_DOUT12: SHA_DATA12 Position    */
#define CSS_SHA2_DOUT12_SHA_DATA12_Msk        (0xffffffffUL << CSS_SHA2_DOUT12_SHA_DATA12_Pos)        /*!< CSS_SHA2_DOUT12: SHA_DATA12 Mask        */

/* ===============================  CSS_SHA2_DOUT13  ============================== */
#define CSS_SHA2_DOUT13_SHA_DATA13_Pos        0                                                       /*!< CSS_SHA2_DOUT13: SHA_DATA13 Position    */
#define CSS_SHA2_DOUT13_SHA_DATA13_Msk        (0xffffffffUL << CSS_SHA2_DOUT13_SHA_DATA13_Pos)        /*!< CSS_SHA2_DOUT13: SHA_DATA13 Mask        */

/* ===============================  CSS_SHA2_DOUT14  ============================== */
#define CSS_SHA2_DOUT14_SHA_DATA14_Pos        0                                                       /*!< CSS_SHA2_DOUT14: SHA_DATA14 Position    */
#define CSS_SHA2_DOUT14_SHA_DATA14_Msk        (0xffffffffUL << CSS_SHA2_DOUT14_SHA_DATA14_Pos)        /*!< CSS_SHA2_DOUT14: SHA_DATA14 Mask        */

/* ===============================  CSS_SHA2_DOUT15  ============================== */
#define CSS_SHA2_DOUT15_SHA_DATA15_Pos        0                                                       /*!< CSS_SHA2_DOUT15: SHA_DATA15 Position    */
#define CSS_SHA2_DOUT15_SHA_DATA15_Msk        (0xffffffffUL << CSS_SHA2_DOUT15_SHA_DATA15_Pos)        /*!< CSS_SHA2_DOUT15: SHA_DATA15 Mask        */

/* ===============================      CSS_KS0      ============================== */
#define CSS_KS0_KS0_KSIZE_Pos                 0                                                       /*!< CSS_KS0: KS0_KSIZE Position             */
#define CSS_KS0_KS0_KSIZE_Msk                 (0x01UL << CSS_KS0_KS0_KSIZE_Pos)                       /*!< CSS_KS0: KS0_KSIZE Mask                 */
#define CSS_KS0_KS0_RSVD0_Pos                 1                                                       /*!< CSS_KS0: KS0_RSVD0 Position             */
#define CSS_KS0_KS0_RSVD0_Msk                 (0x0fUL << CSS_KS0_KS0_RSVD0_Pos)                       /*!< CSS_KS0: KS0_RSVD0 Mask                 */
#define CSS_KS0_KS0_KACT_Pos                  5                                                       /*!< CSS_KS0: KS0_KACT Position              */
#define CSS_KS0_KS0_KACT_Msk                  (0x01UL << CSS_KS0_KS0_KACT_Pos)                        /*!< CSS_KS0: KS0_KACT Mask                  */
#define CSS_KS0_KS0_KBASE_Pos                 6                                                       /*!< CSS_KS0: KS0_KBASE Position             */
#define CSS_KS0_KS0_KBASE_Msk                 (0x01UL << CSS_KS0_KS0_KBASE_Pos)                       /*!< CSS_KS0: KS0_KBASE Mask                 */
#define CSS_KS0_KS0_FGP_Pos                   7                                                       /*!< CSS_KS0: KS0_FGP Position               */
#define CSS_KS0_KS0_FGP_Msk                   (0x01UL << CSS_KS0_KS0_FGP_Pos)                         /*!< CSS_KS0: KS0_FGP Mask                   */
#define CSS_KS0_KS0_FRTN_Pos                  8                                                       /*!< CSS_KS0: KS0_FRTN Position              */
#define CSS_KS0_KS0_FRTN_Msk                  (0x01UL << CSS_KS0_KS0_FRTN_Pos)                        /*!< CSS_KS0: KS0_FRTN Mask                  */
#define CSS_KS0_KS0_FHWO_Pos                  9                                                       /*!< CSS_KS0: KS0_FHWO Position              */
#define CSS_KS0_KS0_FHWO_Msk                  (0x01UL << CSS_KS0_KS0_FHWO_Pos)                        /*!< CSS_KS0: KS0_FHWO Mask                  */
#define CSS_KS0_KS0_RSVD1_Pos                 10                                                      /*!< CSS_KS0: KS0_RSVD1 Position             */
#define CSS_KS0_KS0_RSVD1_Msk                 (0x07UL << CSS_KS0_KS0_RSVD1_Pos)                       /*!< CSS_KS0: KS0_RSVD1 Mask                 */
#define CSS_KS0_KS0_UCMAC_Pos                 13                                                      /*!< CSS_KS0: KS0_UCMAC Position             */
#define CSS_KS0_KS0_UCMAC_Msk                 (0x01UL << CSS_KS0_KS0_UCMAC_Pos)                       /*!< CSS_KS0: KS0_UCMAC Mask                 */
#define CSS_KS0_KS0_UKSK_Pos                  14                                                      /*!< CSS_KS0: KS0_UKSK Position              */
#define CSS_KS0_KS0_UKSK_Msk                  (0x01UL << CSS_KS0_KS0_UKSK_Pos)                        /*!< CSS_KS0: KS0_UKSK Mask                  */
#define CSS_KS0_KS0_URTF_Pos                  15                                                      /*!< CSS_KS0: KS0_URTF Position              */
#define CSS_KS0_KS0_URTF_Msk                  (0x01UL << CSS_KS0_KS0_URTF_Pos)                        /*!< CSS_KS0: KS0_URTF Mask                  */
#define CSS_KS0_KS0_UCKDF_Pos                 16                                                      /*!< CSS_KS0: KS0_UCKDF Position             */
#define CSS_KS0_KS0_UCKDF_Msk                 (0x01UL << CSS_KS0_KS0_UCKDF_Pos)                       /*!< CSS_KS0: KS0_UCKDF Mask                 */
#define CSS_KS0_KS0_UHKDF_Pos                 17                                                      /*!< CSS_KS0: KS0_UHKDF Position             */
#define CSS_KS0_KS0_UHKDF_Msk                 (0x01UL << CSS_KS0_KS0_UHKDF_Pos)                       /*!< CSS_KS0: KS0_UHKDF Mask                 */
#define CSS_KS0_KS0_UECSG_Pos                 18                                                      /*!< CSS_KS0: KS0_UECSG Position             */
#define CSS_KS0_KS0_UECSG_Msk                 (0x01UL << CSS_KS0_KS0_UECSG_Pos)                       /*!< CSS_KS0: KS0_UECSG Mask                 */
#define CSS_KS0_KS0_UECDH_Pos                 19                                                      /*!< CSS_KS0: KS0_UECDH Position             */
#define CSS_KS0_KS0_UECDH_Msk                 (0x01UL << CSS_KS0_KS0_UECDH_Pos)                       /*!< CSS_KS0: KS0_UECDH Mask                 */
#define CSS_KS0_KS0_UAES_Pos                  20                                                      /*!< CSS_KS0: KS0_UAES Position              */
#define CSS_KS0_KS0_UAES_Msk                  (0x01UL << CSS_KS0_KS0_UAES_Pos)                        /*!< CSS_KS0: KS0_UAES Mask                  */
#define CSS_KS0_KS0_UHMAC_Pos                 21                                                      /*!< CSS_KS0: KS0_UHMAC Position             */
#define CSS_KS0_KS0_UHMAC_Msk                 (0x01UL << CSS_KS0_KS0_UHMAC_Pos)                       /*!< CSS_KS0: KS0_UHMAC Mask                 */
#define CSS_KS0_KS0_UKWK_Pos                  22                                                      /*!< CSS_KS0: KS0_UKWK Position              */
#define CSS_KS0_KS0_UKWK_Msk                  (0x01UL << CSS_KS0_KS0_UKWK_Pos)                        /*!< CSS_KS0: KS0_UKWK Mask                  */
#define CSS_KS0_KS0_UKUOK_Pos                 23                                                      /*!< CSS_KS0: KS0_UKUOK Position             */
#define CSS_KS0_KS0_UKUOK_Msk                 (0x01UL << CSS_KS0_KS0_UKUOK_Pos)                       /*!< CSS_KS0: KS0_UKUOK Mask                 */
#define CSS_KS0_KS0_UTLSPMS_Pos               24                                                      /*!< CSS_KS0: KS0_UTLSPMS Position           */
#define CSS_KS0_KS0_UTLSPMS_Msk               (0x01UL << CSS_KS0_KS0_UTLSPMS_Pos)                     /*!< CSS_KS0: KS0_UTLSPMS Mask               */
#define CSS_KS0_KS0_UTLSMS_Pos                25                                                      /*!< CSS_KS0: KS0_UTLSMS Position            */
#define CSS_KS0_KS0_UTLSMS_Msk                (0x01UL << CSS_KS0_KS0_UTLSMS_Pos)                      /*!< CSS_KS0: KS0_UTLSMS Mask                */
#define CSS_KS0_KS0_UKGSRC_Pos                26                                                      /*!< CSS_KS0: KS0_UKGSRC Position            */
#define CSS_KS0_KS0_UKGSRC_Msk                (0x01UL << CSS_KS0_KS0_UKGSRC_Pos)                      /*!< CSS_KS0: KS0_UKGSRC Mask                */
#define CSS_KS0_KS0_UHWO_Pos                  27                                                      /*!< CSS_KS0: KS0_UHWO Position              */
#define CSS_KS0_KS0_UHWO_Msk                  (0x01UL << CSS_KS0_KS0_UHWO_Pos)                        /*!< CSS_KS0: KS0_UHWO Mask                  */
#define CSS_KS0_KS0_UWRPOK_Pos                28                                                      /*!< CSS_KS0: KS0_UWRPOK Position            */
#define CSS_KS0_KS0_UWRPOK_Msk                (0x01UL << CSS_KS0_KS0_UWRPOK_Pos)                      /*!< CSS_KS0: KS0_UWRPOK Mask                */
#define CSS_KS0_KS0_UDUK_Pos                  29                                                      /*!< CSS_KS0: KS0_UDUK Position              */
#define CSS_KS0_KS0_UDUK_Msk                  (0x01UL << CSS_KS0_KS0_UDUK_Pos)                        /*!< CSS_KS0: KS0_UDUK Mask                  */
#define CSS_KS0_KS0_UPPROT_Pos                30                                                      /*!< CSS_KS0: KS0_UPPROT Position            */
#define CSS_KS0_KS0_UPPROT_Msk                (0x03UL << CSS_KS0_KS0_UPPROT_Pos)                      /*!< CSS_KS0: KS0_UPPROT Mask                */

/* ===============================      CSS_KS1      ============================== */
#define CSS_KS1_KS1_KSIZE_Pos                 0                                                       /*!< CSS_KS1: KS1_KSIZE Position             */
#define CSS_KS1_KS1_KSIZE_Msk                 (0x01UL << CSS_KS1_KS1_KSIZE_Pos)                       /*!< CSS_KS1: KS1_KSIZE Mask                 */
#define CSS_KS1_KS1_RSVD0_Pos                 1                                                       /*!< CSS_KS1: KS1_RSVD0 Position             */
#define CSS_KS1_KS1_RSVD0_Msk                 (0x0fUL << CSS_KS1_KS1_RSVD0_Pos)                       /*!< CSS_KS1: KS1_RSVD0 Mask                 */
#define CSS_KS1_KS1_KACT_Pos                  5                                                       /*!< CSS_KS1: KS1_KACT Position              */
#define CSS_KS1_KS1_KACT_Msk                  (0x01UL << CSS_KS1_KS1_KACT_Pos)                        /*!< CSS_KS1: KS1_KACT Mask                  */
#define CSS_KS1_KS1_KBASE_Pos                 6                                                       /*!< CSS_KS1: KS1_KBASE Position             */
#define CSS_KS1_KS1_KBASE_Msk                 (0x01UL << CSS_KS1_KS1_KBASE_Pos)                       /*!< CSS_KS1: KS1_KBASE Mask                 */
#define CSS_KS1_KS1_FGP_Pos                   7                                                       /*!< CSS_KS1: KS1_FGP Position               */
#define CSS_KS1_KS1_FGP_Msk                   (0x01UL << CSS_KS1_KS1_FGP_Pos)                         /*!< CSS_KS1: KS1_FGP Mask                   */
#define CSS_KS1_KS1_FRTN_Pos                  8                                                       /*!< CSS_KS1: KS1_FRTN Position              */
#define CSS_KS1_KS1_FRTN_Msk                  (0x01UL << CSS_KS1_KS1_FRTN_Pos)                        /*!< CSS_KS1: KS1_FRTN Mask                  */
#define CSS_KS1_KS1_FHWO_Pos                  9                                                       /*!< CSS_KS1: KS1_FHWO Position              */
#define CSS_KS1_KS1_FHWO_Msk                  (0x01UL << CSS_KS1_KS1_FHWO_Pos)                        /*!< CSS_KS1: KS1_FHWO Mask                  */
#define CSS_KS1_KS1_RSVD1_Pos                 10                                                      /*!< CSS_KS1: KS1_RSVD1 Position             */
#define CSS_KS1_KS1_RSVD1_Msk                 (0x07UL << CSS_KS1_KS1_RSVD1_Pos)                       /*!< CSS_KS1: KS1_RSVD1 Mask                 */
#define CSS_KS1_KS1_UCMAC_Pos                 13                                                      /*!< CSS_KS1: KS1_UCMAC Position             */
#define CSS_KS1_KS1_UCMAC_Msk                 (0x01UL << CSS_KS1_KS1_UCMAC_Pos)                       /*!< CSS_KS1: KS1_UCMAC Mask                 */
#define CSS_KS1_KS1_UKSK_Pos                  14                                                      /*!< CSS_KS1: KS1_UKSK Position              */
#define CSS_KS1_KS1_UKSK_Msk                  (0x01UL << CSS_KS1_KS1_UKSK_Pos)                        /*!< CSS_KS1: KS1_UKSK Mask                  */
#define CSS_KS1_KS1_URTF_Pos                  15                                                      /*!< CSS_KS1: KS1_URTF Position              */
#define CSS_KS1_KS1_URTF_Msk                  (0x01UL << CSS_KS1_KS1_URTF_Pos)                        /*!< CSS_KS1: KS1_URTF Mask                  */
#define CSS_KS1_KS1_UCKDF_Pos                 16                                                      /*!< CSS_KS1: KS1_UCKDF Position             */
#define CSS_KS1_KS1_UCKDF_Msk                 (0x01UL << CSS_KS1_KS1_UCKDF_Pos)                       /*!< CSS_KS1: KS1_UCKDF Mask                 */
#define CSS_KS1_KS1_UHKDF_Pos                 17                                                      /*!< CSS_KS1: KS1_UHKDF Position             */
#define CSS_KS1_KS1_UHKDF_Msk                 (0x01UL << CSS_KS1_KS1_UHKDF_Pos)                       /*!< CSS_KS1: KS1_UHKDF Mask                 */
#define CSS_KS1_KS1_UECSG_Pos                 18                                                      /*!< CSS_KS1: KS1_UECSG Position             */
#define CSS_KS1_KS1_UECSG_Msk                 (0x01UL << CSS_KS1_KS1_UECSG_Pos)                       /*!< CSS_KS1: KS1_UECSG Mask                 */
#define CSS_KS1_KS1_UECDH_Pos                 19                                                      /*!< CSS_KS1: KS1_UECDH Position             */
#define CSS_KS1_KS1_UECDH_Msk                 (0x01UL << CSS_KS1_KS1_UECDH_Pos)                       /*!< CSS_KS1: KS1_UECDH Mask                 */
#define CSS_KS1_KS1_UAES_Pos                  20                                                      /*!< CSS_KS1: KS1_UAES Position              */
#define CSS_KS1_KS1_UAES_Msk                  (0x01UL << CSS_KS1_KS1_UAES_Pos)                        /*!< CSS_KS1: KS1_UAES Mask                  */
#define CSS_KS1_KS1_UHMAC_Pos                 21                                                      /*!< CSS_KS1: KS1_UHMAC Position             */
#define CSS_KS1_KS1_UHMAC_Msk                 (0x01UL << CSS_KS1_KS1_UHMAC_Pos)                       /*!< CSS_KS1: KS1_UHMAC Mask                 */
#define CSS_KS1_KS1_UKWK_Pos                  22                                                      /*!< CSS_KS1: KS1_UKWK Position              */
#define CSS_KS1_KS1_UKWK_Msk                  (0x01UL << CSS_KS1_KS1_UKWK_Pos)                        /*!< CSS_KS1: KS1_UKWK Mask                  */
#define CSS_KS1_KS1_UKUOK_Pos                 23                                                      /*!< CSS_KS1: KS1_UKUOK Position             */
#define CSS_KS1_KS1_UKUOK_Msk                 (0x01UL << CSS_KS1_KS1_UKUOK_Pos)                       /*!< CSS_KS1: KS1_UKUOK Mask                 */
#define CSS_KS1_KS1_UTLSPMS_Pos               24                                                      /*!< CSS_KS1: KS1_UTLSPMS Position           */
#define CSS_KS1_KS1_UTLSPMS_Msk               (0x01UL << CSS_KS1_KS1_UTLSPMS_Pos)                     /*!< CSS_KS1: KS1_UTLSPMS Mask               */
#define CSS_KS1_KS1_UTLSMS_Pos                25                                                      /*!< CSS_KS1: KS1_UTLSMS Position            */
#define CSS_KS1_KS1_UTLSMS_Msk                (0x01UL << CSS_KS1_KS1_UTLSMS_Pos)                      /*!< CSS_KS1: KS1_UTLSMS Mask                */
#define CSS_KS1_KS1_UKGSRC_Pos                26                                                      /*!< CSS_KS1: KS1_UKGSRC Position            */
#define CSS_KS1_KS1_UKGSRC_Msk                (0x01UL << CSS_KS1_KS1_UKGSRC_Pos)                      /*!< CSS_KS1: KS1_UKGSRC Mask                */
#define CSS_KS1_KS1_UHWO_Pos                  27                                                      /*!< CSS_KS1: KS1_UHWO Position              */
#define CSS_KS1_KS1_UHWO_Msk                  (0x01UL << CSS_KS1_KS1_UHWO_Pos)                        /*!< CSS_KS1: KS1_UHWO Mask                  */
#define CSS_KS1_KS1_UWRPOK_Pos                28                                                      /*!< CSS_KS1: KS1_UWRPOK Position            */
#define CSS_KS1_KS1_UWRPOK_Msk                (0x01UL << CSS_KS1_KS1_UWRPOK_Pos)                      /*!< CSS_KS1: KS1_UWRPOK Mask                */
#define CSS_KS1_KS1_UDUK_Pos                  29                                                      /*!< CSS_KS1: KS1_UDUK Position              */
#define CSS_KS1_KS1_UDUK_Msk                  (0x01UL << CSS_KS1_KS1_UDUK_Pos)                        /*!< CSS_KS1: KS1_UDUK Mask                  */
#define CSS_KS1_KS1_UPPROT_Pos                30                                                      /*!< CSS_KS1: KS1_UPPROT Position            */
#define CSS_KS1_KS1_UPPROT_Msk                (0x03UL << CSS_KS1_KS1_UPPROT_Pos)                      /*!< CSS_KS1: KS1_UPPROT Mask                */

/* ===============================      CSS_KS2      ============================== */
#define CSS_KS2_KS2_KSIZE_Pos                 0                                                       /*!< CSS_KS2: KS2_KSIZE Position             */
#define CSS_KS2_KS2_KSIZE_Msk                 (0x01UL << CSS_KS2_KS2_KSIZE_Pos)                       /*!< CSS_KS2: KS2_KSIZE Mask                 */
#define CSS_KS2_KS2_RSVD0_Pos                 1                                                       /*!< CSS_KS2: KS2_RSVD0 Position             */
#define CSS_KS2_KS2_RSVD0_Msk                 (0x0fUL << CSS_KS2_KS2_RSVD0_Pos)                       /*!< CSS_KS2: KS2_RSVD0 Mask                 */
#define CSS_KS2_KS2_KACT_Pos                  5                                                       /*!< CSS_KS2: KS2_KACT Position              */
#define CSS_KS2_KS2_KACT_Msk                  (0x01UL << CSS_KS2_KS2_KACT_Pos)                        /*!< CSS_KS2: KS2_KACT Mask                  */
#define CSS_KS2_KS2_KBASE_Pos                 6                                                       /*!< CSS_KS2: KS2_KBASE Position             */
#define CSS_KS2_KS2_KBASE_Msk                 (0x01UL << CSS_KS2_KS2_KBASE_Pos)                       /*!< CSS_KS2: KS2_KBASE Mask                 */
#define CSS_KS2_KS2_FGP_Pos                   7                                                       /*!< CSS_KS2: KS2_FGP Position               */
#define CSS_KS2_KS2_FGP_Msk                   (0x01UL << CSS_KS2_KS2_FGP_Pos)                         /*!< CSS_KS2: KS2_FGP Mask                   */
#define CSS_KS2_KS2_FRTN_Pos                  8                                                       /*!< CSS_KS2: KS2_FRTN Position              */
#define CSS_KS2_KS2_FRTN_Msk                  (0x01UL << CSS_KS2_KS2_FRTN_Pos)                        /*!< CSS_KS2: KS2_FRTN Mask                  */
#define CSS_KS2_KS2_FHWO_Pos                  9                                                       /*!< CSS_KS2: KS2_FHWO Position              */
#define CSS_KS2_KS2_FHWO_Msk                  (0x01UL << CSS_KS2_KS2_FHWO_Pos)                        /*!< CSS_KS2: KS2_FHWO Mask                  */
#define CSS_KS2_KS2_RSVD1_Pos                 10                                                      /*!< CSS_KS2: KS2_RSVD1 Position             */
#define CSS_KS2_KS2_RSVD1_Msk                 (0x07UL << CSS_KS2_KS2_RSVD1_Pos)                       /*!< CSS_KS2: KS2_RSVD1 Mask                 */
#define CSS_KS2_KS2_UCMAC_Pos                 13                                                      /*!< CSS_KS2: KS2_UCMAC Position             */
#define CSS_KS2_KS2_UCMAC_Msk                 (0x01UL << CSS_KS2_KS2_UCMAC_Pos)                       /*!< CSS_KS2: KS2_UCMAC Mask                 */
#define CSS_KS2_KS2_UKSK_Pos                  14                                                      /*!< CSS_KS2: KS2_UKSK Position              */
#define CSS_KS2_KS2_UKSK_Msk                  (0x01UL << CSS_KS2_KS2_UKSK_Pos)                        /*!< CSS_KS2: KS2_UKSK Mask                  */
#define CSS_KS2_KS2_URTF_Pos                  15                                                      /*!< CSS_KS2: KS2_URTF Position              */
#define CSS_KS2_KS2_URTF_Msk                  (0x01UL << CSS_KS2_KS2_URTF_Pos)                        /*!< CSS_KS2: KS2_URTF Mask                  */
#define CSS_KS2_KS2_UCKDF_Pos                 16                                                      /*!< CSS_KS2: KS2_UCKDF Position             */
#define CSS_KS2_KS2_UCKDF_Msk                 (0x01UL << CSS_KS2_KS2_UCKDF_Pos)                       /*!< CSS_KS2: KS2_UCKDF Mask                 */
#define CSS_KS2_KS2_UHKDF_Pos                 17                                                      /*!< CSS_KS2: KS2_UHKDF Position             */
#define CSS_KS2_KS2_UHKDF_Msk                 (0x01UL << CSS_KS2_KS2_UHKDF_Pos)                       /*!< CSS_KS2: KS2_UHKDF Mask                 */
#define CSS_KS2_KS2_UECSG_Pos                 18                                                      /*!< CSS_KS2: KS2_UECSG Position             */
#define CSS_KS2_KS2_UECSG_Msk                 (0x01UL << CSS_KS2_KS2_UECSG_Pos)                       /*!< CSS_KS2: KS2_UECSG Mask                 */
#define CSS_KS2_KS2_UECDH_Pos                 19                                                      /*!< CSS_KS2: KS2_UECDH Position             */
#define CSS_KS2_KS2_UECDH_Msk                 (0x01UL << CSS_KS2_KS2_UECDH_Pos)                       /*!< CSS_KS2: KS2_UECDH Mask                 */
#define CSS_KS2_KS2_UAES_Pos                  20                                                      /*!< CSS_KS2: KS2_UAES Position              */
#define CSS_KS2_KS2_UAES_Msk                  (0x01UL << CSS_KS2_KS2_UAES_Pos)                        /*!< CSS_KS2: KS2_UAES Mask                  */
#define CSS_KS2_KS2_UHMAC_Pos                 21                                                      /*!< CSS_KS2: KS2_UHMAC Position             */
#define CSS_KS2_KS2_UHMAC_Msk                 (0x01UL << CSS_KS2_KS2_UHMAC_Pos)                       /*!< CSS_KS2: KS2_UHMAC Mask                 */
#define CSS_KS2_KS2_UKWK_Pos                  22                                                      /*!< CSS_KS2: KS2_UKWK Position              */
#define CSS_KS2_KS2_UKWK_Msk                  (0x01UL << CSS_KS2_KS2_UKWK_Pos)                        /*!< CSS_KS2: KS2_UKWK Mask                  */
#define CSS_KS2_KS2_UKUOK_Pos                 23                                                      /*!< CSS_KS2: KS2_UKUOK Position             */
#define CSS_KS2_KS2_UKUOK_Msk                 (0x01UL << CSS_KS2_KS2_UKUOK_Pos)                       /*!< CSS_KS2: KS2_UKUOK Mask                 */
#define CSS_KS2_KS2_UTLSPMS_Pos               24                                                      /*!< CSS_KS2: KS2_UTLSPMS Position           */
#define CSS_KS2_KS2_UTLSPMS_Msk               (0x01UL << CSS_KS2_KS2_UTLSPMS_Pos)                     /*!< CSS_KS2: KS2_UTLSPMS Mask               */
#define CSS_KS2_KS2_UTLSMS_Pos                25                                                      /*!< CSS_KS2: KS2_UTLSMS Position            */
#define CSS_KS2_KS2_UTLSMS_Msk                (0x01UL << CSS_KS2_KS2_UTLSMS_Pos)                      /*!< CSS_KS2: KS2_UTLSMS Mask                */
#define CSS_KS2_KS2_UKGSRC_Pos                26                                                      /*!< CSS_KS2: KS2_UKGSRC Position            */
#define CSS_KS2_KS2_UKGSRC_Msk                (0x01UL << CSS_KS2_KS2_UKGSRC_Pos)                      /*!< CSS_KS2: KS2_UKGSRC Mask                */
#define CSS_KS2_KS2_UHWO_Pos                  27                                                      /*!< CSS_KS2: KS2_UHWO Position              */
#define CSS_KS2_KS2_UHWO_Msk                  (0x01UL << CSS_KS2_KS2_UHWO_Pos)                        /*!< CSS_KS2: KS2_UHWO Mask                  */
#define CSS_KS2_KS2_UWRPOK_Pos                28                                                      /*!< CSS_KS2: KS2_UWRPOK Position            */
#define CSS_KS2_KS2_UWRPOK_Msk                (0x01UL << CSS_KS2_KS2_UWRPOK_Pos)                      /*!< CSS_KS2: KS2_UWRPOK Mask                */
#define CSS_KS2_KS2_UDUK_Pos                  29                                                      /*!< CSS_KS2: KS2_UDUK Position              */
#define CSS_KS2_KS2_UDUK_Msk                  (0x01UL << CSS_KS2_KS2_UDUK_Pos)                        /*!< CSS_KS2: KS2_UDUK Mask                  */
#define CSS_KS2_KS2_UPPROT_Pos                30                                                      /*!< CSS_KS2: KS2_UPPROT Position            */
#define CSS_KS2_KS2_UPPROT_Msk                (0x03UL << CSS_KS2_KS2_UPPROT_Pos)                      /*!< CSS_KS2: KS2_UPPROT Mask                */

/* ===============================      CSS_KS3      ============================== */
#define CSS_KS3_KS3_KSIZE_Pos                 0                                                       /*!< CSS_KS3: KS3_KSIZE Position             */
#define CSS_KS3_KS3_KSIZE_Msk                 (0x01UL << CSS_KS3_KS3_KSIZE_Pos)                       /*!< CSS_KS3: KS3_KSIZE Mask                 */
#define CSS_KS3_KS3_RSVD0_Pos                 1                                                       /*!< CSS_KS3: KS3_RSVD0 Position             */
#define CSS_KS3_KS3_RSVD0_Msk                 (0x0fUL << CSS_KS3_KS3_RSVD0_Pos)                       /*!< CSS_KS3: KS3_RSVD0 Mask                 */
#define CSS_KS3_KS3_KACT_Pos                  5                                                       /*!< CSS_KS3: KS3_KACT Position              */
#define CSS_KS3_KS3_KACT_Msk                  (0x01UL << CSS_KS3_KS3_KACT_Pos)                        /*!< CSS_KS3: KS3_KACT Mask                  */
#define CSS_KS3_KS3_KBASE_Pos                 6                                                       /*!< CSS_KS3: KS3_KBASE Position             */
#define CSS_KS3_KS3_KBASE_Msk                 (0x01UL << CSS_KS3_KS3_KBASE_Pos)                       /*!< CSS_KS3: KS3_KBASE Mask                 */
#define CSS_KS3_KS3_FGP_Pos                   7                                                       /*!< CSS_KS3: KS3_FGP Position               */
#define CSS_KS3_KS3_FGP_Msk                   (0x01UL << CSS_KS3_KS3_FGP_Pos)                         /*!< CSS_KS3: KS3_FGP Mask                   */
#define CSS_KS3_KS3_FRTN_Pos                  8                                                       /*!< CSS_KS3: KS3_FRTN Position              */
#define CSS_KS3_KS3_FRTN_Msk                  (0x01UL << CSS_KS3_KS3_FRTN_Pos)                        /*!< CSS_KS3: KS3_FRTN Mask                  */
#define CSS_KS3_KS3_FHWO_Pos                  9                                                       /*!< CSS_KS3: KS3_FHWO Position              */
#define CSS_KS3_KS3_FHWO_Msk                  (0x01UL << CSS_KS3_KS3_FHWO_Pos)                        /*!< CSS_KS3: KS3_FHWO Mask                  */
#define CSS_KS3_KS3_RSVD1_Pos                 10                                                      /*!< CSS_KS3: KS3_RSVD1 Position             */
#define CSS_KS3_KS3_RSVD1_Msk                 (0x07UL << CSS_KS3_KS3_RSVD1_Pos)                       /*!< CSS_KS3: KS3_RSVD1 Mask                 */
#define CSS_KS3_KS3_UCMAC_Pos                 13                                                      /*!< CSS_KS3: KS3_UCMAC Position             */
#define CSS_KS3_KS3_UCMAC_Msk                 (0x01UL << CSS_KS3_KS3_UCMAC_Pos)                       /*!< CSS_KS3: KS3_UCMAC Mask                 */
#define CSS_KS3_KS3_UKSK_Pos                  14                                                      /*!< CSS_KS3: KS3_UKSK Position              */
#define CSS_KS3_KS3_UKSK_Msk                  (0x01UL << CSS_KS3_KS3_UKSK_Pos)                        /*!< CSS_KS3: KS3_UKSK Mask                  */
#define CSS_KS3_KS3_URTF_Pos                  15                                                      /*!< CSS_KS3: KS3_URTF Position              */
#define CSS_KS3_KS3_URTF_Msk                  (0x01UL << CSS_KS3_KS3_URTF_Pos)                        /*!< CSS_KS3: KS3_URTF Mask                  */
#define CSS_KS3_KS3_UCKDF_Pos                 16                                                      /*!< CSS_KS3: KS3_UCKDF Position             */
#define CSS_KS3_KS3_UCKDF_Msk                 (0x01UL << CSS_KS3_KS3_UCKDF_Pos)                       /*!< CSS_KS3: KS3_UCKDF Mask                 */
#define CSS_KS3_KS3_UHKDF_Pos                 17                                                      /*!< CSS_KS3: KS3_UHKDF Position             */
#define CSS_KS3_KS3_UHKDF_Msk                 (0x01UL << CSS_KS3_KS3_UHKDF_Pos)                       /*!< CSS_KS3: KS3_UHKDF Mask                 */
#define CSS_KS3_KS3_UECSG_Pos                 18                                                      /*!< CSS_KS3: KS3_UECSG Position             */
#define CSS_KS3_KS3_UECSG_Msk                 (0x01UL << CSS_KS3_KS3_UECSG_Pos)                       /*!< CSS_KS3: KS3_UECSG Mask                 */
#define CSS_KS3_KS3_UECDH_Pos                 19                                                      /*!< CSS_KS3: KS3_UECDH Position             */
#define CSS_KS3_KS3_UECDH_Msk                 (0x01UL << CSS_KS3_KS3_UECDH_Pos)                       /*!< CSS_KS3: KS3_UECDH Mask                 */
#define CSS_KS3_KS3_UAES_Pos                  20                                                      /*!< CSS_KS3: KS3_UAES Position              */
#define CSS_KS3_KS3_UAES_Msk                  (0x01UL << CSS_KS3_KS3_UAES_Pos)                        /*!< CSS_KS3: KS3_UAES Mask                  */
#define CSS_KS3_KS3_UHMAC_Pos                 21                                                      /*!< CSS_KS3: KS3_UHMAC Position             */
#define CSS_KS3_KS3_UHMAC_Msk                 (0x01UL << CSS_KS3_KS3_UHMAC_Pos)                       /*!< CSS_KS3: KS3_UHMAC Mask                 */
#define CSS_KS3_KS3_UKWK_Pos                  22                                                      /*!< CSS_KS3: KS3_UKWK Position              */
#define CSS_KS3_KS3_UKWK_Msk                  (0x01UL << CSS_KS3_KS3_UKWK_Pos)                        /*!< CSS_KS3: KS3_UKWK Mask                  */
#define CSS_KS3_KS3_UKUOK_Pos                 23                                                      /*!< CSS_KS3: KS3_UKUOK Position             */
#define CSS_KS3_KS3_UKUOK_Msk                 (0x01UL << CSS_KS3_KS3_UKUOK_Pos)                       /*!< CSS_KS3: KS3_UKUOK Mask                 */
#define CSS_KS3_KS3_UTLSPMS_Pos               24                                                      /*!< CSS_KS3: KS3_UTLSPMS Position           */
#define CSS_KS3_KS3_UTLSPMS_Msk               (0x01UL << CSS_KS3_KS3_UTLSPMS_Pos)                     /*!< CSS_KS3: KS3_UTLSPMS Mask               */
#define CSS_KS3_KS3_UTLSMS_Pos                25                                                      /*!< CSS_KS3: KS3_UTLSMS Position            */
#define CSS_KS3_KS3_UTLSMS_Msk                (0x01UL << CSS_KS3_KS3_UTLSMS_Pos)                      /*!< CSS_KS3: KS3_UTLSMS Mask                */
#define CSS_KS3_KS3_UKGSRC_Pos                26                                                      /*!< CSS_KS3: KS3_UKGSRC Position            */
#define CSS_KS3_KS3_UKGSRC_Msk                (0x01UL << CSS_KS3_KS3_UKGSRC_Pos)                      /*!< CSS_KS3: KS3_UKGSRC Mask                */
#define CSS_KS3_KS3_UHWO_Pos                  27                                                      /*!< CSS_KS3: KS3_UHWO Position              */
#define CSS_KS3_KS3_UHWO_Msk                  (0x01UL << CSS_KS3_KS3_UHWO_Pos)                        /*!< CSS_KS3: KS3_UHWO Mask                  */
#define CSS_KS3_KS3_UWRPOK_Pos                28                                                      /*!< CSS_KS3: KS3_UWRPOK Position            */
#define CSS_KS3_KS3_UWRPOK_Msk                (0x01UL << CSS_KS3_KS3_UWRPOK_Pos)                      /*!< CSS_KS3: KS3_UWRPOK Mask                */
#define CSS_KS3_KS3_UDUK_Pos                  29                                                      /*!< CSS_KS3: KS3_UDUK Position              */
#define CSS_KS3_KS3_UDUK_Msk                  (0x01UL << CSS_KS3_KS3_UDUK_Pos)                        /*!< CSS_KS3: KS3_UDUK Mask                  */
#define CSS_KS3_KS3_UPPROT_Pos                30                                                      /*!< CSS_KS3: KS3_UPPROT Position            */
#define CSS_KS3_KS3_UPPROT_Msk                (0x03UL << CSS_KS3_KS3_UPPROT_Pos)                      /*!< CSS_KS3: KS3_UPPROT Mask                */

/* ===============================      CSS_KS4      ============================== */
#define CSS_KS4_KS4_KSIZE_Pos                 0                                                       /*!< CSS_KS4: KS4_KSIZE Position             */
#define CSS_KS4_KS4_KSIZE_Msk                 (0x01UL << CSS_KS4_KS4_KSIZE_Pos)                       /*!< CSS_KS4: KS4_KSIZE Mask                 */
#define CSS_KS4_KS4_RSVD0_Pos                 1                                                       /*!< CSS_KS4: KS4_RSVD0 Position             */
#define CSS_KS4_KS4_RSVD0_Msk                 (0x0fUL << CSS_KS4_KS4_RSVD0_Pos)                       /*!< CSS_KS4: KS4_RSVD0 Mask                 */
#define CSS_KS4_KS4_KACT_Pos                  5                                                       /*!< CSS_KS4: KS4_KACT Position              */
#define CSS_KS4_KS4_KACT_Msk                  (0x01UL << CSS_KS4_KS4_KACT_Pos)                        /*!< CSS_KS4: KS4_KACT Mask                  */
#define CSS_KS4_KS4_KBASE_Pos                 6                                                       /*!< CSS_KS4: KS4_KBASE Position             */
#define CSS_KS4_KS4_KBASE_Msk                 (0x01UL << CSS_KS4_KS4_KBASE_Pos)                       /*!< CSS_KS4: KS4_KBASE Mask                 */
#define CSS_KS4_KS4_FGP_Pos                   7                                                       /*!< CSS_KS4: KS4_FGP Position               */
#define CSS_KS4_KS4_FGP_Msk                   (0x01UL << CSS_KS4_KS4_FGP_Pos)                         /*!< CSS_KS4: KS4_FGP Mask                   */
#define CSS_KS4_KS4_FRTN_Pos                  8                                                       /*!< CSS_KS4: KS4_FRTN Position              */
#define CSS_KS4_KS4_FRTN_Msk                  (0x01UL << CSS_KS4_KS4_FRTN_Pos)                        /*!< CSS_KS4: KS4_FRTN Mask                  */
#define CSS_KS4_KS4_FHWO_Pos                  9                                                       /*!< CSS_KS4: KS4_FHWO Position              */
#define CSS_KS4_KS4_FHWO_Msk                  (0x01UL << CSS_KS4_KS4_FHWO_Pos)                        /*!< CSS_KS4: KS4_FHWO Mask                  */
#define CSS_KS4_KS4_RSVD1_Pos                 10                                                      /*!< CSS_KS4: KS4_RSVD1 Position             */
#define CSS_KS4_KS4_RSVD1_Msk                 (0x07UL << CSS_KS4_KS4_RSVD1_Pos)                       /*!< CSS_KS4: KS4_RSVD1 Mask                 */
#define CSS_KS4_KS4_UCMAC_Pos                 13                                                      /*!< CSS_KS4: KS4_UCMAC Position             */
#define CSS_KS4_KS4_UCMAC_Msk                 (0x01UL << CSS_KS4_KS4_UCMAC_Pos)                       /*!< CSS_KS4: KS4_UCMAC Mask                 */
#define CSS_KS4_KS4_UKSK_Pos                  14                                                      /*!< CSS_KS4: KS4_UKSK Position              */
#define CSS_KS4_KS4_UKSK_Msk                  (0x01UL << CSS_KS4_KS4_UKSK_Pos)                        /*!< CSS_KS4: KS4_UKSK Mask                  */
#define CSS_KS4_KS4_URTF_Pos                  15                                                      /*!< CSS_KS4: KS4_URTF Position              */
#define CSS_KS4_KS4_URTF_Msk                  (0x01UL << CSS_KS4_KS4_URTF_Pos)                        /*!< CSS_KS4: KS4_URTF Mask                  */
#define CSS_KS4_KS4_UCKDF_Pos                 16                                                      /*!< CSS_KS4: KS4_UCKDF Position             */
#define CSS_KS4_KS4_UCKDF_Msk                 (0x01UL << CSS_KS4_KS4_UCKDF_Pos)                       /*!< CSS_KS4: KS4_UCKDF Mask                 */
#define CSS_KS4_KS4_UHKDF_Pos                 17                                                      /*!< CSS_KS4: KS4_UHKDF Position             */
#define CSS_KS4_KS4_UHKDF_Msk                 (0x01UL << CSS_KS4_KS4_UHKDF_Pos)                       /*!< CSS_KS4: KS4_UHKDF Mask                 */
#define CSS_KS4_KS4_UECSG_Pos                 18                                                      /*!< CSS_KS4: KS4_UECSG Position             */
#define CSS_KS4_KS4_UECSG_Msk                 (0x01UL << CSS_KS4_KS4_UECSG_Pos)                       /*!< CSS_KS4: KS4_UECSG Mask                 */
#define CSS_KS4_KS4_UECDH_Pos                 19                                                      /*!< CSS_KS4: KS4_UECDH Position             */
#define CSS_KS4_KS4_UECDH_Msk                 (0x01UL << CSS_KS4_KS4_UECDH_Pos)                       /*!< CSS_KS4: KS4_UECDH Mask                 */
#define CSS_KS4_KS4_UAES_Pos                  20                                                      /*!< CSS_KS4: KS4_UAES Position              */
#define CSS_KS4_KS4_UAES_Msk                  (0x01UL << CSS_KS4_KS4_UAES_Pos)                        /*!< CSS_KS4: KS4_UAES Mask                  */
#define CSS_KS4_KS4_UHMAC_Pos                 21                                                      /*!< CSS_KS4: KS4_UHMAC Position             */
#define CSS_KS4_KS4_UHMAC_Msk                 (0x01UL << CSS_KS4_KS4_UHMAC_Pos)                       /*!< CSS_KS4: KS4_UHMAC Mask                 */
#define CSS_KS4_KS4_UKWK_Pos                  22                                                      /*!< CSS_KS4: KS4_UKWK Position              */
#define CSS_KS4_KS4_UKWK_Msk                  (0x01UL << CSS_KS4_KS4_UKWK_Pos)                        /*!< CSS_KS4: KS4_UKWK Mask                  */
#define CSS_KS4_KS4_UKUOK_Pos                 23                                                      /*!< CSS_KS4: KS4_UKUOK Position             */
#define CSS_KS4_KS4_UKUOK_Msk                 (0x01UL << CSS_KS4_KS4_UKUOK_Pos)                       /*!< CSS_KS4: KS4_UKUOK Mask                 */
#define CSS_KS4_KS4_UTLSPMS_Pos               24                                                      /*!< CSS_KS4: KS4_UTLSPMS Position           */
#define CSS_KS4_KS4_UTLSPMS_Msk               (0x01UL << CSS_KS4_KS4_UTLSPMS_Pos)                     /*!< CSS_KS4: KS4_UTLSPMS Mask               */
#define CSS_KS4_KS4_UTLSMS_Pos                25                                                      /*!< CSS_KS4: KS4_UTLSMS Position            */
#define CSS_KS4_KS4_UTLSMS_Msk                (0x01UL << CSS_KS4_KS4_UTLSMS_Pos)                      /*!< CSS_KS4: KS4_UTLSMS Mask                */
#define CSS_KS4_KS4_UKGSRC_Pos                26                                                      /*!< CSS_KS4: KS4_UKGSRC Position            */
#define CSS_KS4_KS4_UKGSRC_Msk                (0x01UL << CSS_KS4_KS4_UKGSRC_Pos)                      /*!< CSS_KS4: KS4_UKGSRC Mask                */
#define CSS_KS4_KS4_UHWO_Pos                  27                                                      /*!< CSS_KS4: KS4_UHWO Position              */
#define CSS_KS4_KS4_UHWO_Msk                  (0x01UL << CSS_KS4_KS4_UHWO_Pos)                        /*!< CSS_KS4: KS4_UHWO Mask                  */
#define CSS_KS4_KS4_UWRPOK_Pos                28                                                      /*!< CSS_KS4: KS4_UWRPOK Position            */
#define CSS_KS4_KS4_UWRPOK_Msk                (0x01UL << CSS_KS4_KS4_UWRPOK_Pos)                      /*!< CSS_KS4: KS4_UWRPOK Mask                */
#define CSS_KS4_KS4_UDUK_Pos                  29                                                      /*!< CSS_KS4: KS4_UDUK Position              */
#define CSS_KS4_KS4_UDUK_Msk                  (0x01UL << CSS_KS4_KS4_UDUK_Pos)                        /*!< CSS_KS4: KS4_UDUK Mask                  */
#define CSS_KS4_KS4_UPPROT_Pos                30                                                      /*!< CSS_KS4: KS4_UPPROT Position            */
#define CSS_KS4_KS4_UPPROT_Msk                (0x03UL << CSS_KS4_KS4_UPPROT_Pos)                      /*!< CSS_KS4: KS4_UPPROT Mask                */

/* ===============================      CSS_KS5      ============================== */
#define CSS_KS5_KS5_KSIZE_Pos                 0                                                       /*!< CSS_KS5: KS5_KSIZE Position             */
#define CSS_KS5_KS5_KSIZE_Msk                 (0x01UL << CSS_KS5_KS5_KSIZE_Pos)                       /*!< CSS_KS5: KS5_KSIZE Mask                 */
#define CSS_KS5_KS5_RSVD0_Pos                 1                                                       /*!< CSS_KS5: KS5_RSVD0 Position             */
#define CSS_KS5_KS5_RSVD0_Msk                 (0x0fUL << CSS_KS5_KS5_RSVD0_Pos)                       /*!< CSS_KS5: KS5_RSVD0 Mask                 */
#define CSS_KS5_KS5_KACT_Pos                  5                                                       /*!< CSS_KS5: KS5_KACT Position              */
#define CSS_KS5_KS5_KACT_Msk                  (0x01UL << CSS_KS5_KS5_KACT_Pos)                        /*!< CSS_KS5: KS5_KACT Mask                  */
#define CSS_KS5_KS5_KBASE_Pos                 6                                                       /*!< CSS_KS5: KS5_KBASE Position             */
#define CSS_KS5_KS5_KBASE_Msk                 (0x01UL << CSS_KS5_KS5_KBASE_Pos)                       /*!< CSS_KS5: KS5_KBASE Mask                 */
#define CSS_KS5_KS5_FGP_Pos                   7                                                       /*!< CSS_KS5: KS5_FGP Position               */
#define CSS_KS5_KS5_FGP_Msk                   (0x01UL << CSS_KS5_KS5_FGP_Pos)                         /*!< CSS_KS5: KS5_FGP Mask                   */
#define CSS_KS5_KS5_FRTN_Pos                  8                                                       /*!< CSS_KS5: KS5_FRTN Position              */
#define CSS_KS5_KS5_FRTN_Msk                  (0x01UL << CSS_KS5_KS5_FRTN_Pos)                        /*!< CSS_KS5: KS5_FRTN Mask                  */
#define CSS_KS5_KS5_FHWO_Pos                  9                                                       /*!< CSS_KS5: KS5_FHWO Position              */
#define CSS_KS5_KS5_FHWO_Msk                  (0x01UL << CSS_KS5_KS5_FHWO_Pos)                        /*!< CSS_KS5: KS5_FHWO Mask                  */
#define CSS_KS5_KS5_RSVD1_Pos                 10                                                      /*!< CSS_KS5: KS5_RSVD1 Position             */
#define CSS_KS5_KS5_RSVD1_Msk                 (0x07UL << CSS_KS5_KS5_RSVD1_Pos)                       /*!< CSS_KS5: KS5_RSVD1 Mask                 */
#define CSS_KS5_KS5_UCMAC_Pos                 13                                                      /*!< CSS_KS5: KS5_UCMAC Position             */
#define CSS_KS5_KS5_UCMAC_Msk                 (0x01UL << CSS_KS5_KS5_UCMAC_Pos)                       /*!< CSS_KS5: KS5_UCMAC Mask                 */
#define CSS_KS5_KS5_UKSK_Pos                  14                                                      /*!< CSS_KS5: KS5_UKSK Position              */
#define CSS_KS5_KS5_UKSK_Msk                  (0x01UL << CSS_KS5_KS5_UKSK_Pos)                        /*!< CSS_KS5: KS5_UKSK Mask                  */
#define CSS_KS5_KS5_URTF_Pos                  15                                                      /*!< CSS_KS5: KS5_URTF Position              */
#define CSS_KS5_KS5_URTF_Msk                  (0x01UL << CSS_KS5_KS5_URTF_Pos)                        /*!< CSS_KS5: KS5_URTF Mask                  */
#define CSS_KS5_KS5_UCKDF_Pos                 16                                                      /*!< CSS_KS5: KS5_UCKDF Position             */
#define CSS_KS5_KS5_UCKDF_Msk                 (0x01UL << CSS_KS5_KS5_UCKDF_Pos)                       /*!< CSS_KS5: KS5_UCKDF Mask                 */
#define CSS_KS5_KS5_UHKDF_Pos                 17                                                      /*!< CSS_KS5: KS5_UHKDF Position             */
#define CSS_KS5_KS5_UHKDF_Msk                 (0x01UL << CSS_KS5_KS5_UHKDF_Pos)                       /*!< CSS_KS5: KS5_UHKDF Mask                 */
#define CSS_KS5_KS5_UECSG_Pos                 18                                                      /*!< CSS_KS5: KS5_UECSG Position             */
#define CSS_KS5_KS5_UECSG_Msk                 (0x01UL << CSS_KS5_KS5_UECSG_Pos)                       /*!< CSS_KS5: KS5_UECSG Mask                 */
#define CSS_KS5_KS5_UECDH_Pos                 19                                                      /*!< CSS_KS5: KS5_UECDH Position             */
#define CSS_KS5_KS5_UECDH_Msk                 (0x01UL << CSS_KS5_KS5_UECDH_Pos)                       /*!< CSS_KS5: KS5_UECDH Mask                 */
#define CSS_KS5_KS5_UAES_Pos                  20                                                      /*!< CSS_KS5: KS5_UAES Position              */
#define CSS_KS5_KS5_UAES_Msk                  (0x01UL << CSS_KS5_KS5_UAES_Pos)                        /*!< CSS_KS5: KS5_UAES Mask                  */
#define CSS_KS5_KS5_UHMAC_Pos                 21                                                      /*!< CSS_KS5: KS5_UHMAC Position             */
#define CSS_KS5_KS5_UHMAC_Msk                 (0x01UL << CSS_KS5_KS5_UHMAC_Pos)                       /*!< CSS_KS5: KS5_UHMAC Mask                 */
#define CSS_KS5_KS5_UKWK_Pos                  22                                                      /*!< CSS_KS5: KS5_UKWK Position              */
#define CSS_KS5_KS5_UKWK_Msk                  (0x01UL << CSS_KS5_KS5_UKWK_Pos)                        /*!< CSS_KS5: KS5_UKWK Mask                  */
#define CSS_KS5_KS5_UKUOK_Pos                 23                                                      /*!< CSS_KS5: KS5_UKUOK Position             */
#define CSS_KS5_KS5_UKUOK_Msk                 (0x01UL << CSS_KS5_KS5_UKUOK_Pos)                       /*!< CSS_KS5: KS5_UKUOK Mask                 */
#define CSS_KS5_KS5_UTLSPMS_Pos               24                                                      /*!< CSS_KS5: KS5_UTLSPMS Position           */
#define CSS_KS5_KS5_UTLSPMS_Msk               (0x01UL << CSS_KS5_KS5_UTLSPMS_Pos)                     /*!< CSS_KS5: KS5_UTLSPMS Mask               */
#define CSS_KS5_KS5_UTLSMS_Pos                25                                                      /*!< CSS_KS5: KS5_UTLSMS Position            */
#define CSS_KS5_KS5_UTLSMS_Msk                (0x01UL << CSS_KS5_KS5_UTLSMS_Pos)                      /*!< CSS_KS5: KS5_UTLSMS Mask                */
#define CSS_KS5_KS5_UKGSRC_Pos                26                                                      /*!< CSS_KS5: KS5_UKGSRC Position            */
#define CSS_KS5_KS5_UKGSRC_Msk                (0x01UL << CSS_KS5_KS5_UKGSRC_Pos)                      /*!< CSS_KS5: KS5_UKGSRC Mask                */
#define CSS_KS5_KS5_UHWO_Pos                  27                                                      /*!< CSS_KS5: KS5_UHWO Position              */
#define CSS_KS5_KS5_UHWO_Msk                  (0x01UL << CSS_KS5_KS5_UHWO_Pos)                        /*!< CSS_KS5: KS5_UHWO Mask                  */
#define CSS_KS5_KS5_UWRPOK_Pos                28                                                      /*!< CSS_KS5: KS5_UWRPOK Position            */
#define CSS_KS5_KS5_UWRPOK_Msk                (0x01UL << CSS_KS5_KS5_UWRPOK_Pos)                      /*!< CSS_KS5: KS5_UWRPOK Mask                */
#define CSS_KS5_KS5_UDUK_Pos                  29                                                      /*!< CSS_KS5: KS5_UDUK Position              */
#define CSS_KS5_KS5_UDUK_Msk                  (0x01UL << CSS_KS5_KS5_UDUK_Pos)                        /*!< CSS_KS5: KS5_UDUK Mask                  */
#define CSS_KS5_KS5_UPPROT_Pos                30                                                      /*!< CSS_KS5: KS5_UPPROT Position            */
#define CSS_KS5_KS5_UPPROT_Msk                (0x03UL << CSS_KS5_KS5_UPPROT_Pos)                      /*!< CSS_KS5: KS5_UPPROT Mask                */

/* ===============================      CSS_KS6      ============================== */
#define CSS_KS6_KS6_KSIZE_Pos                 0                                                       /*!< CSS_KS6: KS6_KSIZE Position             */
#define CSS_KS6_KS6_KSIZE_Msk                 (0x01UL << CSS_KS6_KS6_KSIZE_Pos)                       /*!< CSS_KS6: KS6_KSIZE Mask                 */
#define CSS_KS6_KS6_RSVD0_Pos                 1                                                       /*!< CSS_KS6: KS6_RSVD0 Position             */
#define CSS_KS6_KS6_RSVD0_Msk                 (0x0fUL << CSS_KS6_KS6_RSVD0_Pos)                       /*!< CSS_KS6: KS6_RSVD0 Mask                 */
#define CSS_KS6_KS6_KACT_Pos                  5                                                       /*!< CSS_KS6: KS6_KACT Position              */
#define CSS_KS6_KS6_KACT_Msk                  (0x01UL << CSS_KS6_KS6_KACT_Pos)                        /*!< CSS_KS6: KS6_KACT Mask                  */
#define CSS_KS6_KS6_KBASE_Pos                 6                                                       /*!< CSS_KS6: KS6_KBASE Position             */
#define CSS_KS6_KS6_KBASE_Msk                 (0x01UL << CSS_KS6_KS6_KBASE_Pos)                       /*!< CSS_KS6: KS6_KBASE Mask                 */
#define CSS_KS6_KS6_FGP_Pos                   7                                                       /*!< CSS_KS6: KS6_FGP Position               */
#define CSS_KS6_KS6_FGP_Msk                   (0x01UL << CSS_KS6_KS6_FGP_Pos)                         /*!< CSS_KS6: KS6_FGP Mask                   */
#define CSS_KS6_KS6_FRTN_Pos                  8                                                       /*!< CSS_KS6: KS6_FRTN Position              */
#define CSS_KS6_KS6_FRTN_Msk                  (0x01UL << CSS_KS6_KS6_FRTN_Pos)                        /*!< CSS_KS6: KS6_FRTN Mask                  */
#define CSS_KS6_KS6_FHWO_Pos                  9                                                       /*!< CSS_KS6: KS6_FHWO Position              */
#define CSS_KS6_KS6_FHWO_Msk                  (0x01UL << CSS_KS6_KS6_FHWO_Pos)                        /*!< CSS_KS6: KS6_FHWO Mask                  */
#define CSS_KS6_KS6_RSVD1_Pos                 10                                                      /*!< CSS_KS6: KS6_RSVD1 Position             */
#define CSS_KS6_KS6_RSVD1_Msk                 (0x07UL << CSS_KS6_KS6_RSVD1_Pos)                       /*!< CSS_KS6: KS6_RSVD1 Mask                 */
#define CSS_KS6_KS6_UCMAC_Pos                 13                                                      /*!< CSS_KS6: KS6_UCMAC Position             */
#define CSS_KS6_KS6_UCMAC_Msk                 (0x01UL << CSS_KS6_KS6_UCMAC_Pos)                       /*!< CSS_KS6: KS6_UCMAC Mask                 */
#define CSS_KS6_KS6_UKSK_Pos                  14                                                      /*!< CSS_KS6: KS6_UKSK Position              */
#define CSS_KS6_KS6_UKSK_Msk                  (0x01UL << CSS_KS6_KS6_UKSK_Pos)                        /*!< CSS_KS6: KS6_UKSK Mask                  */
#define CSS_KS6_KS6_URTF_Pos                  15                                                      /*!< CSS_KS6: KS6_URTF Position              */
#define CSS_KS6_KS6_URTF_Msk                  (0x01UL << CSS_KS6_KS6_URTF_Pos)                        /*!< CSS_KS6: KS6_URTF Mask                  */
#define CSS_KS6_KS6_UCKDF_Pos                 16                                                      /*!< CSS_KS6: KS6_UCKDF Position             */
#define CSS_KS6_KS6_UCKDF_Msk                 (0x01UL << CSS_KS6_KS6_UCKDF_Pos)                       /*!< CSS_KS6: KS6_UCKDF Mask                 */
#define CSS_KS6_KS6_UHKDF_Pos                 17                                                      /*!< CSS_KS6: KS6_UHKDF Position             */
#define CSS_KS6_KS6_UHKDF_Msk                 (0x01UL << CSS_KS6_KS6_UHKDF_Pos)                       /*!< CSS_KS6: KS6_UHKDF Mask                 */
#define CSS_KS6_KS6_UECSG_Pos                 18                                                      /*!< CSS_KS6: KS6_UECSG Position             */
#define CSS_KS6_KS6_UECSG_Msk                 (0x01UL << CSS_KS6_KS6_UECSG_Pos)                       /*!< CSS_KS6: KS6_UECSG Mask                 */
#define CSS_KS6_KS6_UECDH_Pos                 19                                                      /*!< CSS_KS6: KS6_UECDH Position             */
#define CSS_KS6_KS6_UECDH_Msk                 (0x01UL << CSS_KS6_KS6_UECDH_Pos)                       /*!< CSS_KS6: KS6_UECDH Mask                 */
#define CSS_KS6_KS6_UAES_Pos                  20                                                      /*!< CSS_KS6: KS6_UAES Position              */
#define CSS_KS6_KS6_UAES_Msk                  (0x01UL << CSS_KS6_KS6_UAES_Pos)                        /*!< CSS_KS6: KS6_UAES Mask                  */
#define CSS_KS6_KS6_UHMAC_Pos                 21                                                      /*!< CSS_KS6: KS6_UHMAC Position             */
#define CSS_KS6_KS6_UHMAC_Msk                 (0x01UL << CSS_KS6_KS6_UHMAC_Pos)                       /*!< CSS_KS6: KS6_UHMAC Mask                 */
#define CSS_KS6_KS6_UKWK_Pos                  22                                                      /*!< CSS_KS6: KS6_UKWK Position              */
#define CSS_KS6_KS6_UKWK_Msk                  (0x01UL << CSS_KS6_KS6_UKWK_Pos)                        /*!< CSS_KS6: KS6_UKWK Mask                  */
#define CSS_KS6_KS6_UKUOK_Pos                 23                                                      /*!< CSS_KS6: KS6_UKUOK Position             */
#define CSS_KS6_KS6_UKUOK_Msk                 (0x01UL << CSS_KS6_KS6_UKUOK_Pos)                       /*!< CSS_KS6: KS6_UKUOK Mask                 */
#define CSS_KS6_KS6_UTLSPMS_Pos               24                                                      /*!< CSS_KS6: KS6_UTLSPMS Position           */
#define CSS_KS6_KS6_UTLSPMS_Msk               (0x01UL << CSS_KS6_KS6_UTLSPMS_Pos)                     /*!< CSS_KS6: KS6_UTLSPMS Mask               */
#define CSS_KS6_KS6_UTLSMS_Pos                25                                                      /*!< CSS_KS6: KS6_UTLSMS Position            */
#define CSS_KS6_KS6_UTLSMS_Msk                (0x01UL << CSS_KS6_KS6_UTLSMS_Pos)                      /*!< CSS_KS6: KS6_UTLSMS Mask                */
#define CSS_KS6_KS6_UKGSRC_Pos                26                                                      /*!< CSS_KS6: KS6_UKGSRC Position            */
#define CSS_KS6_KS6_UKGSRC_Msk                (0x01UL << CSS_KS6_KS6_UKGSRC_Pos)                      /*!< CSS_KS6: KS6_UKGSRC Mask                */
#define CSS_KS6_KS6_UHWO_Pos                  27                                                      /*!< CSS_KS6: KS6_UHWO Position              */
#define CSS_KS6_KS6_UHWO_Msk                  (0x01UL << CSS_KS6_KS6_UHWO_Pos)                        /*!< CSS_KS6: KS6_UHWO Mask                  */
#define CSS_KS6_KS6_UWRPOK_Pos                28                                                      /*!< CSS_KS6: KS6_UWRPOK Position            */
#define CSS_KS6_KS6_UWRPOK_Msk                (0x01UL << CSS_KS6_KS6_UWRPOK_Pos)                      /*!< CSS_KS6: KS6_UWRPOK Mask                */
#define CSS_KS6_KS6_UDUK_Pos                  29                                                      /*!< CSS_KS6: KS6_UDUK Position              */
#define CSS_KS6_KS6_UDUK_Msk                  (0x01UL << CSS_KS6_KS6_UDUK_Pos)                        /*!< CSS_KS6: KS6_UDUK Mask                  */
#define CSS_KS6_KS6_UPPROT_Pos                30                                                      /*!< CSS_KS6: KS6_UPPROT Position            */
#define CSS_KS6_KS6_UPPROT_Msk                (0x03UL << CSS_KS6_KS6_UPPROT_Pos)                      /*!< CSS_KS6: KS6_UPPROT Mask                */

/* ===============================      CSS_KS7      ============================== */
#define CSS_KS7_KS7_KSIZE_Pos                 0                                                       /*!< CSS_KS7: KS7_KSIZE Position             */
#define CSS_KS7_KS7_KSIZE_Msk                 (0x01UL << CSS_KS7_KS7_KSIZE_Pos)                       /*!< CSS_KS7: KS7_KSIZE Mask                 */
#define CSS_KS7_KS7_RSVD0_Pos                 1                                                       /*!< CSS_KS7: KS7_RSVD0 Position             */
#define CSS_KS7_KS7_RSVD0_Msk                 (0x0fUL << CSS_KS7_KS7_RSVD0_Pos)                       /*!< CSS_KS7: KS7_RSVD0 Mask                 */
#define CSS_KS7_KS7_KACT_Pos                  5                                                       /*!< CSS_KS7: KS7_KACT Position              */
#define CSS_KS7_KS7_KACT_Msk                  (0x01UL << CSS_KS7_KS7_KACT_Pos)                        /*!< CSS_KS7: KS7_KACT Mask                  */
#define CSS_KS7_KS7_KBASE_Pos                 6                                                       /*!< CSS_KS7: KS7_KBASE Position             */
#define CSS_KS7_KS7_KBASE_Msk                 (0x01UL << CSS_KS7_KS7_KBASE_Pos)                       /*!< CSS_KS7: KS7_KBASE Mask                 */
#define CSS_KS7_KS7_FGP_Pos                   7                                                       /*!< CSS_KS7: KS7_FGP Position               */
#define CSS_KS7_KS7_FGP_Msk                   (0x01UL << CSS_KS7_KS7_FGP_Pos)                         /*!< CSS_KS7: KS7_FGP Mask                   */
#define CSS_KS7_KS7_FRTN_Pos                  8                                                       /*!< CSS_KS7: KS7_FRTN Position              */
#define CSS_KS7_KS7_FRTN_Msk                  (0x01UL << CSS_KS7_KS7_FRTN_Pos)                        /*!< CSS_KS7: KS7_FRTN Mask                  */
#define CSS_KS7_KS7_FHWO_Pos                  9                                                       /*!< CSS_KS7: KS7_FHWO Position              */
#define CSS_KS7_KS7_FHWO_Msk                  (0x01UL << CSS_KS7_KS7_FHWO_Pos)                        /*!< CSS_KS7: KS7_FHWO Mask                  */
#define CSS_KS7_KS7_RSVD1_Pos                 10                                                      /*!< CSS_KS7: KS7_RSVD1 Position             */
#define CSS_KS7_KS7_RSVD1_Msk                 (0x07UL << CSS_KS7_KS7_RSVD1_Pos)                       /*!< CSS_KS7: KS7_RSVD1 Mask                 */
#define CSS_KS7_KS7_UCMAC_Pos                 13                                                      /*!< CSS_KS7: KS7_UCMAC Position             */
#define CSS_KS7_KS7_UCMAC_Msk                 (0x01UL << CSS_KS7_KS7_UCMAC_Pos)                       /*!< CSS_KS7: KS7_UCMAC Mask                 */
#define CSS_KS7_KS7_UKSK_Pos                  14                                                      /*!< CSS_KS7: KS7_UKSK Position              */
#define CSS_KS7_KS7_UKSK_Msk                  (0x01UL << CSS_KS7_KS7_UKSK_Pos)                        /*!< CSS_KS7: KS7_UKSK Mask                  */
#define CSS_KS7_KS7_URTF_Pos                  15                                                      /*!< CSS_KS7: KS7_URTF Position              */
#define CSS_KS7_KS7_URTF_Msk                  (0x01UL << CSS_KS7_KS7_URTF_Pos)                        /*!< CSS_KS7: KS7_URTF Mask                  */
#define CSS_KS7_KS7_UCKDF_Pos                 16                                                      /*!< CSS_KS7: KS7_UCKDF Position             */
#define CSS_KS7_KS7_UCKDF_Msk                 (0x01UL << CSS_KS7_KS7_UCKDF_Pos)                       /*!< CSS_KS7: KS7_UCKDF Mask                 */
#define CSS_KS7_KS7_UHKDF_Pos                 17                                                      /*!< CSS_KS7: KS7_UHKDF Position             */
#define CSS_KS7_KS7_UHKDF_Msk                 (0x01UL << CSS_KS7_KS7_UHKDF_Pos)                       /*!< CSS_KS7: KS7_UHKDF Mask                 */
#define CSS_KS7_KS7_UECSG_Pos                 18                                                      /*!< CSS_KS7: KS7_UECSG Position             */
#define CSS_KS7_KS7_UECSG_Msk                 (0x01UL << CSS_KS7_KS7_UECSG_Pos)                       /*!< CSS_KS7: KS7_UECSG Mask                 */
#define CSS_KS7_KS7_UECDH_Pos                 19                                                      /*!< CSS_KS7: KS7_UECDH Position             */
#define CSS_KS7_KS7_UECDH_Msk                 (0x01UL << CSS_KS7_KS7_UECDH_Pos)                       /*!< CSS_KS7: KS7_UECDH Mask                 */
#define CSS_KS7_KS7_UAES_Pos                  20                                                      /*!< CSS_KS7: KS7_UAES Position              */
#define CSS_KS7_KS7_UAES_Msk                  (0x01UL << CSS_KS7_KS7_UAES_Pos)                        /*!< CSS_KS7: KS7_UAES Mask                  */
#define CSS_KS7_KS7_UHMAC_Pos                 21                                                      /*!< CSS_KS7: KS7_UHMAC Position             */
#define CSS_KS7_KS7_UHMAC_Msk                 (0x01UL << CSS_KS7_KS7_UHMAC_Pos)                       /*!< CSS_KS7: KS7_UHMAC Mask                 */
#define CSS_KS7_KS7_UKWK_Pos                  22                                                      /*!< CSS_KS7: KS7_UKWK Position              */
#define CSS_KS7_KS7_UKWK_Msk                  (0x01UL << CSS_KS7_KS7_UKWK_Pos)                        /*!< CSS_KS7: KS7_UKWK Mask                  */
#define CSS_KS7_KS7_UKUOK_Pos                 23                                                      /*!< CSS_KS7: KS7_UKUOK Position             */
#define CSS_KS7_KS7_UKUOK_Msk                 (0x01UL << CSS_KS7_KS7_UKUOK_Pos)                       /*!< CSS_KS7: KS7_UKUOK Mask                 */
#define CSS_KS7_KS7_UTLSPMS_Pos               24                                                      /*!< CSS_KS7: KS7_UTLSPMS Position           */
#define CSS_KS7_KS7_UTLSPMS_Msk               (0x01UL << CSS_KS7_KS7_UTLSPMS_Pos)                     /*!< CSS_KS7: KS7_UTLSPMS Mask               */
#define CSS_KS7_KS7_UTLSMS_Pos                25                                                      /*!< CSS_KS7: KS7_UTLSMS Position            */
#define CSS_KS7_KS7_UTLSMS_Msk                (0x01UL << CSS_KS7_KS7_UTLSMS_Pos)                      /*!< CSS_KS7: KS7_UTLSMS Mask                */
#define CSS_KS7_KS7_UKGSRC_Pos                26                                                      /*!< CSS_KS7: KS7_UKGSRC Position            */
#define CSS_KS7_KS7_UKGSRC_Msk                (0x01UL << CSS_KS7_KS7_UKGSRC_Pos)                      /*!< CSS_KS7: KS7_UKGSRC Mask                */
#define CSS_KS7_KS7_UHWO_Pos                  27                                                      /*!< CSS_KS7: KS7_UHWO Position              */
#define CSS_KS7_KS7_UHWO_Msk                  (0x01UL << CSS_KS7_KS7_UHWO_Pos)                        /*!< CSS_KS7: KS7_UHWO Mask                  */
#define CSS_KS7_KS7_UWRPOK_Pos                28                                                      /*!< CSS_KS7: KS7_UWRPOK Position            */
#define CSS_KS7_KS7_UWRPOK_Msk                (0x01UL << CSS_KS7_KS7_UWRPOK_Pos)                      /*!< CSS_KS7: KS7_UWRPOK Mask                */
#define CSS_KS7_KS7_UDUK_Pos                  29                                                      /*!< CSS_KS7: KS7_UDUK Position              */
#define CSS_KS7_KS7_UDUK_Msk                  (0x01UL << CSS_KS7_KS7_UDUK_Pos)                        /*!< CSS_KS7: KS7_UDUK Mask                  */
#define CSS_KS7_KS7_UPPROT_Pos                30                                                      /*!< CSS_KS7: KS7_UPPROT Position            */
#define CSS_KS7_KS7_UPPROT_Msk                (0x03UL << CSS_KS7_KS7_UPPROT_Pos)                      /*!< CSS_KS7: KS7_UPPROT Mask                */

/* ===============================      CSS_KS8      ============================== */
#define CSS_KS8_KS8_KSIZE_Pos                 0                                                       /*!< CSS_KS8: KS8_KSIZE Position             */
#define CSS_KS8_KS8_KSIZE_Msk                 (0x01UL << CSS_KS8_KS8_KSIZE_Pos)                       /*!< CSS_KS8: KS8_KSIZE Mask                 */
#define CSS_KS8_KS8_RSVD0_Pos                 1                                                       /*!< CSS_KS8: KS8_RSVD0 Position             */
#define CSS_KS8_KS8_RSVD0_Msk                 (0x0fUL << CSS_KS8_KS8_RSVD0_Pos)                       /*!< CSS_KS8: KS8_RSVD0 Mask                 */
#define CSS_KS8_KS8_KACT_Pos                  5                                                       /*!< CSS_KS8: KS8_KACT Position              */
#define CSS_KS8_KS8_KACT_Msk                  (0x01UL << CSS_KS8_KS8_KACT_Pos)                        /*!< CSS_KS8: KS8_KACT Mask                  */
#define CSS_KS8_KS8_KBASE_Pos                 6                                                       /*!< CSS_KS8: KS8_KBASE Position             */
#define CSS_KS8_KS8_KBASE_Msk                 (0x01UL << CSS_KS8_KS8_KBASE_Pos)                       /*!< CSS_KS8: KS8_KBASE Mask                 */
#define CSS_KS8_KS8_FGP_Pos                   7                                                       /*!< CSS_KS8: KS8_FGP Position               */
#define CSS_KS8_KS8_FGP_Msk                   (0x01UL << CSS_KS8_KS8_FGP_Pos)                         /*!< CSS_KS8: KS8_FGP Mask                   */
#define CSS_KS8_KS8_FRTN_Pos                  8                                                       /*!< CSS_KS8: KS8_FRTN Position              */
#define CSS_KS8_KS8_FRTN_Msk                  (0x01UL << CSS_KS8_KS8_FRTN_Pos)                        /*!< CSS_KS8: KS8_FRTN Mask                  */
#define CSS_KS8_KS8_FHWO_Pos                  9                                                       /*!< CSS_KS8: KS8_FHWO Position              */
#define CSS_KS8_KS8_FHWO_Msk                  (0x01UL << CSS_KS8_KS8_FHWO_Pos)                        /*!< CSS_KS8: KS8_FHWO Mask                  */
#define CSS_KS8_KS8_RSVD1_Pos                 10                                                      /*!< CSS_KS8: KS8_RSVD1 Position             */
#define CSS_KS8_KS8_RSVD1_Msk                 (0x07UL << CSS_KS8_KS8_RSVD1_Pos)                       /*!< CSS_KS8: KS8_RSVD1 Mask                 */
#define CSS_KS8_KS8_UCMAC_Pos                 13                                                      /*!< CSS_KS8: KS8_UCMAC Position             */
#define CSS_KS8_KS8_UCMAC_Msk                 (0x01UL << CSS_KS8_KS8_UCMAC_Pos)                       /*!< CSS_KS8: KS8_UCMAC Mask                 */
#define CSS_KS8_KS8_UKSK_Pos                  14                                                      /*!< CSS_KS8: KS8_UKSK Position              */
#define CSS_KS8_KS8_UKSK_Msk                  (0x01UL << CSS_KS8_KS8_UKSK_Pos)                        /*!< CSS_KS8: KS8_UKSK Mask                  */
#define CSS_KS8_KS8_URTF_Pos                  15                                                      /*!< CSS_KS8: KS8_URTF Position              */
#define CSS_KS8_KS8_URTF_Msk                  (0x01UL << CSS_KS8_KS8_URTF_Pos)                        /*!< CSS_KS8: KS8_URTF Mask                  */
#define CSS_KS8_KS8_UCKDF_Pos                 16                                                      /*!< CSS_KS8: KS8_UCKDF Position             */
#define CSS_KS8_KS8_UCKDF_Msk                 (0x01UL << CSS_KS8_KS8_UCKDF_Pos)                       /*!< CSS_KS8: KS8_UCKDF Mask                 */
#define CSS_KS8_KS8_UHKDF_Pos                 17                                                      /*!< CSS_KS8: KS8_UHKDF Position             */
#define CSS_KS8_KS8_UHKDF_Msk                 (0x01UL << CSS_KS8_KS8_UHKDF_Pos)                       /*!< CSS_KS8: KS8_UHKDF Mask                 */
#define CSS_KS8_KS8_UECSG_Pos                 18                                                      /*!< CSS_KS8: KS8_UECSG Position             */
#define CSS_KS8_KS8_UECSG_Msk                 (0x01UL << CSS_KS8_KS8_UECSG_Pos)                       /*!< CSS_KS8: KS8_UECSG Mask                 */
#define CSS_KS8_KS8_UECDH_Pos                 19                                                      /*!< CSS_KS8: KS8_UECDH Position             */
#define CSS_KS8_KS8_UECDH_Msk                 (0x01UL << CSS_KS8_KS8_UECDH_Pos)                       /*!< CSS_KS8: KS8_UECDH Mask                 */
#define CSS_KS8_KS8_UAES_Pos                  20                                                      /*!< CSS_KS8: KS8_UAES Position              */
#define CSS_KS8_KS8_UAES_Msk                  (0x01UL << CSS_KS8_KS8_UAES_Pos)                        /*!< CSS_KS8: KS8_UAES Mask                  */
#define CSS_KS8_KS8_UHMAC_Pos                 21                                                      /*!< CSS_KS8: KS8_UHMAC Position             */
#define CSS_KS8_KS8_UHMAC_Msk                 (0x01UL << CSS_KS8_KS8_UHMAC_Pos)                       /*!< CSS_KS8: KS8_UHMAC Mask                 */
#define CSS_KS8_KS8_UKWK_Pos                  22                                                      /*!< CSS_KS8: KS8_UKWK Position              */
#define CSS_KS8_KS8_UKWK_Msk                  (0x01UL << CSS_KS8_KS8_UKWK_Pos)                        /*!< CSS_KS8: KS8_UKWK Mask                  */
#define CSS_KS8_KS8_UKUOK_Pos                 23                                                      /*!< CSS_KS8: KS8_UKUOK Position             */
#define CSS_KS8_KS8_UKUOK_Msk                 (0x01UL << CSS_KS8_KS8_UKUOK_Pos)                       /*!< CSS_KS8: KS8_UKUOK Mask                 */
#define CSS_KS8_KS8_UTLSPMS_Pos               24                                                      /*!< CSS_KS8: KS8_UTLSPMS Position           */
#define CSS_KS8_KS8_UTLSPMS_Msk               (0x01UL << CSS_KS8_KS8_UTLSPMS_Pos)                     /*!< CSS_KS8: KS8_UTLSPMS Mask               */
#define CSS_KS8_KS8_UTLSMS_Pos                25                                                      /*!< CSS_KS8: KS8_UTLSMS Position            */
#define CSS_KS8_KS8_UTLSMS_Msk                (0x01UL << CSS_KS8_KS8_UTLSMS_Pos)                      /*!< CSS_KS8: KS8_UTLSMS Mask                */
#define CSS_KS8_KS8_UKGSRC_Pos                26                                                      /*!< CSS_KS8: KS8_UKGSRC Position            */
#define CSS_KS8_KS8_UKGSRC_Msk                (0x01UL << CSS_KS8_KS8_UKGSRC_Pos)                      /*!< CSS_KS8: KS8_UKGSRC Mask                */
#define CSS_KS8_KS8_UHWO_Pos                  27                                                      /*!< CSS_KS8: KS8_UHWO Position              */
#define CSS_KS8_KS8_UHWO_Msk                  (0x01UL << CSS_KS8_KS8_UHWO_Pos)                        /*!< CSS_KS8: KS8_UHWO Mask                  */
#define CSS_KS8_KS8_UWRPOK_Pos                28                                                      /*!< CSS_KS8: KS8_UWRPOK Position            */
#define CSS_KS8_KS8_UWRPOK_Msk                (0x01UL << CSS_KS8_KS8_UWRPOK_Pos)                      /*!< CSS_KS8: KS8_UWRPOK Mask                */
#define CSS_KS8_KS8_UDUK_Pos                  29                                                      /*!< CSS_KS8: KS8_UDUK Position              */
#define CSS_KS8_KS8_UDUK_Msk                  (0x01UL << CSS_KS8_KS8_UDUK_Pos)                        /*!< CSS_KS8: KS8_UDUK Mask                  */
#define CSS_KS8_KS8_UPPROT_Pos                30                                                      /*!< CSS_KS8: KS8_UPPROT Position            */
#define CSS_KS8_KS8_UPPROT_Msk                (0x03UL << CSS_KS8_KS8_UPPROT_Pos)                      /*!< CSS_KS8: KS8_UPPROT Mask                */

/* ===============================      CSS_KS9      ============================== */
#define CSS_KS9_KS9_KSIZE_Pos                 0                                                       /*!< CSS_KS9: KS9_KSIZE Position             */
#define CSS_KS9_KS9_KSIZE_Msk                 (0x01UL << CSS_KS9_KS9_KSIZE_Pos)                       /*!< CSS_KS9: KS9_KSIZE Mask                 */
#define CSS_KS9_KS9_RSVD0_Pos                 1                                                       /*!< CSS_KS9: KS9_RSVD0 Position             */
#define CSS_KS9_KS9_RSVD0_Msk                 (0x0fUL << CSS_KS9_KS9_RSVD0_Pos)                       /*!< CSS_KS9: KS9_RSVD0 Mask                 */
#define CSS_KS9_KS9_KACT_Pos                  5                                                       /*!< CSS_KS9: KS9_KACT Position              */
#define CSS_KS9_KS9_KACT_Msk                  (0x01UL << CSS_KS9_KS9_KACT_Pos)                        /*!< CSS_KS9: KS9_KACT Mask                  */
#define CSS_KS9_KS9_KBASE_Pos                 6                                                       /*!< CSS_KS9: KS9_KBASE Position             */
#define CSS_KS9_KS9_KBASE_Msk                 (0x01UL << CSS_KS9_KS9_KBASE_Pos)                       /*!< CSS_KS9: KS9_KBASE Mask                 */
#define CSS_KS9_KS9_FGP_Pos                   7                                                       /*!< CSS_KS9: KS9_FGP Position               */
#define CSS_KS9_KS9_FGP_Msk                   (0x01UL << CSS_KS9_KS9_FGP_Pos)                         /*!< CSS_KS9: KS9_FGP Mask                   */
#define CSS_KS9_KS9_FRTN_Pos                  8                                                       /*!< CSS_KS9: KS9_FRTN Position              */
#define CSS_KS9_KS9_FRTN_Msk                  (0x01UL << CSS_KS9_KS9_FRTN_Pos)                        /*!< CSS_KS9: KS9_FRTN Mask                  */
#define CSS_KS9_KS9_FHWO_Pos                  9                                                       /*!< CSS_KS9: KS9_FHWO Position              */
#define CSS_KS9_KS9_FHWO_Msk                  (0x01UL << CSS_KS9_KS9_FHWO_Pos)                        /*!< CSS_KS9: KS9_FHWO Mask                  */
#define CSS_KS9_KS9_RSVD1_Pos                 10                                                      /*!< CSS_KS9: KS9_RSVD1 Position             */
#define CSS_KS9_KS9_RSVD1_Msk                 (0x07UL << CSS_KS9_KS9_RSVD1_Pos)                       /*!< CSS_KS9: KS9_RSVD1 Mask                 */
#define CSS_KS9_KS9_UCMAC_Pos                 13                                                      /*!< CSS_KS9: KS9_UCMAC Position             */
#define CSS_KS9_KS9_UCMAC_Msk                 (0x01UL << CSS_KS9_KS9_UCMAC_Pos)                       /*!< CSS_KS9: KS9_UCMAC Mask                 */
#define CSS_KS9_KS9_UKSK_Pos                  14                                                      /*!< CSS_KS9: KS9_UKSK Position              */
#define CSS_KS9_KS9_UKSK_Msk                  (0x01UL << CSS_KS9_KS9_UKSK_Pos)                        /*!< CSS_KS9: KS9_UKSK Mask                  */
#define CSS_KS9_KS9_URTF_Pos                  15                                                      /*!< CSS_KS9: KS9_URTF Position              */
#define CSS_KS9_KS9_URTF_Msk                  (0x01UL << CSS_KS9_KS9_URTF_Pos)                        /*!< CSS_KS9: KS9_URTF Mask                  */
#define CSS_KS9_KS9_UCKDF_Pos                 16                                                      /*!< CSS_KS9: KS9_UCKDF Position             */
#define CSS_KS9_KS9_UCKDF_Msk                 (0x01UL << CSS_KS9_KS9_UCKDF_Pos)                       /*!< CSS_KS9: KS9_UCKDF Mask                 */
#define CSS_KS9_KS9_UHKDF_Pos                 17                                                      /*!< CSS_KS9: KS9_UHKDF Position             */
#define CSS_KS9_KS9_UHKDF_Msk                 (0x01UL << CSS_KS9_KS9_UHKDF_Pos)                       /*!< CSS_KS9: KS9_UHKDF Mask                 */
#define CSS_KS9_KS9_UECSG_Pos                 18                                                      /*!< CSS_KS9: KS9_UECSG Position             */
#define CSS_KS9_KS9_UECSG_Msk                 (0x01UL << CSS_KS9_KS9_UECSG_Pos)                       /*!< CSS_KS9: KS9_UECSG Mask                 */
#define CSS_KS9_KS9_UECDH_Pos                 19                                                      /*!< CSS_KS9: KS9_UECDH Position             */
#define CSS_KS9_KS9_UECDH_Msk                 (0x01UL << CSS_KS9_KS9_UECDH_Pos)                       /*!< CSS_KS9: KS9_UECDH Mask                 */
#define CSS_KS9_KS9_UAES_Pos                  20                                                      /*!< CSS_KS9: KS9_UAES Position              */
#define CSS_KS9_KS9_UAES_Msk                  (0x01UL << CSS_KS9_KS9_UAES_Pos)                        /*!< CSS_KS9: KS9_UAES Mask                  */
#define CSS_KS9_KS9_UHMAC_Pos                 21                                                      /*!< CSS_KS9: KS9_UHMAC Position             */
#define CSS_KS9_KS9_UHMAC_Msk                 (0x01UL << CSS_KS9_KS9_UHMAC_Pos)                       /*!< CSS_KS9: KS9_UHMAC Mask                 */
#define CSS_KS9_KS9_UKWK_Pos                  22                                                      /*!< CSS_KS9: KS9_UKWK Position              */
#define CSS_KS9_KS9_UKWK_Msk                  (0x01UL << CSS_KS9_KS9_UKWK_Pos)                        /*!< CSS_KS9: KS9_UKWK Mask                  */
#define CSS_KS9_KS9_UKUOK_Pos                 23                                                      /*!< CSS_KS9: KS9_UKUOK Position             */
#define CSS_KS9_KS9_UKUOK_Msk                 (0x01UL << CSS_KS9_KS9_UKUOK_Pos)                       /*!< CSS_KS9: KS9_UKUOK Mask                 */
#define CSS_KS9_KS9_UTLSPMS_Pos               24                                                      /*!< CSS_KS9: KS9_UTLSPMS Position           */
#define CSS_KS9_KS9_UTLSPMS_Msk               (0x01UL << CSS_KS9_KS9_UTLSPMS_Pos)                     /*!< CSS_KS9: KS9_UTLSPMS Mask               */
#define CSS_KS9_KS9_UTLSMS_Pos                25                                                      /*!< CSS_KS9: KS9_UTLSMS Position            */
#define CSS_KS9_KS9_UTLSMS_Msk                (0x01UL << CSS_KS9_KS9_UTLSMS_Pos)                      /*!< CSS_KS9: KS9_UTLSMS Mask                */
#define CSS_KS9_KS9_UKGSRC_Pos                26                                                      /*!< CSS_KS9: KS9_UKGSRC Position            */
#define CSS_KS9_KS9_UKGSRC_Msk                (0x01UL << CSS_KS9_KS9_UKGSRC_Pos)                      /*!< CSS_KS9: KS9_UKGSRC Mask                */
#define CSS_KS9_KS9_UHWO_Pos                  27                                                      /*!< CSS_KS9: KS9_UHWO Position              */
#define CSS_KS9_KS9_UHWO_Msk                  (0x01UL << CSS_KS9_KS9_UHWO_Pos)                        /*!< CSS_KS9: KS9_UHWO Mask                  */
#define CSS_KS9_KS9_UWRPOK_Pos                28                                                      /*!< CSS_KS9: KS9_UWRPOK Position            */
#define CSS_KS9_KS9_UWRPOK_Msk                (0x01UL << CSS_KS9_KS9_UWRPOK_Pos)                      /*!< CSS_KS9: KS9_UWRPOK Mask                */
#define CSS_KS9_KS9_UDUK_Pos                  29                                                      /*!< CSS_KS9: KS9_UDUK Position              */
#define CSS_KS9_KS9_UDUK_Msk                  (0x01UL << CSS_KS9_KS9_UDUK_Pos)                        /*!< CSS_KS9: KS9_UDUK Mask                  */
#define CSS_KS9_KS9_UPPROT_Pos                30                                                      /*!< CSS_KS9: KS9_UPPROT Position            */
#define CSS_KS9_KS9_UPPROT_Msk                (0x03UL << CSS_KS9_KS9_UPPROT_Pos)                      /*!< CSS_KS9: KS9_UPPROT Mask                */

/* ===============================      CSS_KS10     ============================== */
#define CSS_KS10_KS10_KSIZE_Pos               0                                                       /*!< CSS_KS10: KS10_KSIZE Position           */
#define CSS_KS10_KS10_KSIZE_Msk               (0x01UL << CSS_KS10_KS10_KSIZE_Pos)                     /*!< CSS_KS10: KS10_KSIZE Mask               */
#define CSS_KS10_KS10_RSVD0_Pos               1                                                       /*!< CSS_KS10: KS10_RSVD0 Position           */
#define CSS_KS10_KS10_RSVD0_Msk               (0x0fUL << CSS_KS10_KS10_RSVD0_Pos)                     /*!< CSS_KS10: KS10_RSVD0 Mask               */
#define CSS_KS10_KS10_KACT_Pos                5                                                       /*!< CSS_KS10: KS10_KACT Position            */
#define CSS_KS10_KS10_KACT_Msk                (0x01UL << CSS_KS10_KS10_KACT_Pos)                      /*!< CSS_KS10: KS10_KACT Mask                */
#define CSS_KS10_KS10_KBASE_Pos               6                                                       /*!< CSS_KS10: KS10_KBASE Position           */
#define CSS_KS10_KS10_KBASE_Msk               (0x01UL << CSS_KS10_KS10_KBASE_Pos)                     /*!< CSS_KS10: KS10_KBASE Mask               */
#define CSS_KS10_KS10_FGP_Pos                 7                                                       /*!< CSS_KS10: KS10_FGP Position             */
#define CSS_KS10_KS10_FGP_Msk                 (0x01UL << CSS_KS10_KS10_FGP_Pos)                       /*!< CSS_KS10: KS10_FGP Mask                 */
#define CSS_KS10_KS10_FRTN_Pos                8                                                       /*!< CSS_KS10: KS10_FRTN Position            */
#define CSS_KS10_KS10_FRTN_Msk                (0x01UL << CSS_KS10_KS10_FRTN_Pos)                      /*!< CSS_KS10: KS10_FRTN Mask                */
#define CSS_KS10_KS10_FHWO_Pos                9                                                       /*!< CSS_KS10: KS10_FHWO Position            */
#define CSS_KS10_KS10_FHWO_Msk                (0x01UL << CSS_KS10_KS10_FHWO_Pos)                      /*!< CSS_KS10: KS10_FHWO Mask                */
#define CSS_KS10_KS10_RSVD1_Pos               10                                                      /*!< CSS_KS10: KS10_RSVD1 Position           */
#define CSS_KS10_KS10_RSVD1_Msk               (0x07UL << CSS_KS10_KS10_RSVD1_Pos)                     /*!< CSS_KS10: KS10_RSVD1 Mask               */
#define CSS_KS10_KS10_UCMAC_Pos               13                                                      /*!< CSS_KS10: KS10_UCMAC Position           */
#define CSS_KS10_KS10_UCMAC_Msk               (0x01UL << CSS_KS10_KS10_UCMAC_Pos)                     /*!< CSS_KS10: KS10_UCMAC Mask               */
#define CSS_KS10_KS10_UKSK_Pos                14                                                      /*!< CSS_KS10: KS10_UKSK Position            */
#define CSS_KS10_KS10_UKSK_Msk                (0x01UL << CSS_KS10_KS10_UKSK_Pos)                      /*!< CSS_KS10: KS10_UKSK Mask                */
#define CSS_KS10_KS10_URTF_Pos                15                                                      /*!< CSS_KS10: KS10_URTF Position            */
#define CSS_KS10_KS10_URTF_Msk                (0x01UL << CSS_KS10_KS10_URTF_Pos)                      /*!< CSS_KS10: KS10_URTF Mask                */
#define CSS_KS10_KS10_UCKDF_Pos               16                                                      /*!< CSS_KS10: KS10_UCKDF Position           */
#define CSS_KS10_KS10_UCKDF_Msk               (0x01UL << CSS_KS10_KS10_UCKDF_Pos)                     /*!< CSS_KS10: KS10_UCKDF Mask               */
#define CSS_KS10_KS10_UHKDF_Pos               17                                                      /*!< CSS_KS10: KS10_UHKDF Position           */
#define CSS_KS10_KS10_UHKDF_Msk               (0x01UL << CSS_KS10_KS10_UHKDF_Pos)                     /*!< CSS_KS10: KS10_UHKDF Mask               */
#define CSS_KS10_KS10_UECSG_Pos               18                                                      /*!< CSS_KS10: KS10_UECSG Position           */
#define CSS_KS10_KS10_UECSG_Msk               (0x01UL << CSS_KS10_KS10_UECSG_Pos)                     /*!< CSS_KS10: KS10_UECSG Mask               */
#define CSS_KS10_KS10_UECDH_Pos               19                                                      /*!< CSS_KS10: KS10_UECDH Position           */
#define CSS_KS10_KS10_UECDH_Msk               (0x01UL << CSS_KS10_KS10_UECDH_Pos)                     /*!< CSS_KS10: KS10_UECDH Mask               */
#define CSS_KS10_KS10_UAES_Pos                20                                                      /*!< CSS_KS10: KS10_UAES Position            */
#define CSS_KS10_KS10_UAES_Msk                (0x01UL << CSS_KS10_KS10_UAES_Pos)                      /*!< CSS_KS10: KS10_UAES Mask                */
#define CSS_KS10_KS10_UHMAC_Pos               21                                                      /*!< CSS_KS10: KS10_UHMAC Position           */
#define CSS_KS10_KS10_UHMAC_Msk               (0x01UL << CSS_KS10_KS10_UHMAC_Pos)                     /*!< CSS_KS10: KS10_UHMAC Mask               */
#define CSS_KS10_KS10_UKWK_Pos                22                                                      /*!< CSS_KS10: KS10_UKWK Position            */
#define CSS_KS10_KS10_UKWK_Msk                (0x01UL << CSS_KS10_KS10_UKWK_Pos)                      /*!< CSS_KS10: KS10_UKWK Mask                */
#define CSS_KS10_KS10_UKUOK_Pos               23                                                      /*!< CSS_KS10: KS10_UKUOK Position           */
#define CSS_KS10_KS10_UKUOK_Msk               (0x01UL << CSS_KS10_KS10_UKUOK_Pos)                     /*!< CSS_KS10: KS10_UKUOK Mask               */
#define CSS_KS10_KS10_UTLSPMS_Pos             24                                                      /*!< CSS_KS10: KS10_UTLSPMS Position         */
#define CSS_KS10_KS10_UTLSPMS_Msk             (0x01UL << CSS_KS10_KS10_UTLSPMS_Pos)                   /*!< CSS_KS10: KS10_UTLSPMS Mask             */
#define CSS_KS10_KS10_UTLSMS_Pos              25                                                      /*!< CSS_KS10: KS10_UTLSMS Position          */
#define CSS_KS10_KS10_UTLSMS_Msk              (0x01UL << CSS_KS10_KS10_UTLSMS_Pos)                    /*!< CSS_KS10: KS10_UTLSMS Mask              */
#define CSS_KS10_KS10_UKGSRC_Pos              26                                                      /*!< CSS_KS10: KS10_UKGSRC Position          */
#define CSS_KS10_KS10_UKGSRC_Msk              (0x01UL << CSS_KS10_KS10_UKGSRC_Pos)                    /*!< CSS_KS10: KS10_UKGSRC Mask              */
#define CSS_KS10_KS10_UHWO_Pos                27                                                      /*!< CSS_KS10: KS10_UHWO Position            */
#define CSS_KS10_KS10_UHWO_Msk                (0x01UL << CSS_KS10_KS10_UHWO_Pos)                      /*!< CSS_KS10: KS10_UHWO Mask                */
#define CSS_KS10_KS10_UWRPOK_Pos              28                                                      /*!< CSS_KS10: KS10_UWRPOK Position          */
#define CSS_KS10_KS10_UWRPOK_Msk              (0x01UL << CSS_KS10_KS10_UWRPOK_Pos)                    /*!< CSS_KS10: KS10_UWRPOK Mask              */
#define CSS_KS10_KS10_UDUK_Pos                29                                                      /*!< CSS_KS10: KS10_UDUK Position            */
#define CSS_KS10_KS10_UDUK_Msk                (0x01UL << CSS_KS10_KS10_UDUK_Pos)                      /*!< CSS_KS10: KS10_UDUK Mask                */
#define CSS_KS10_KS10_UPPROT_Pos              30                                                      /*!< CSS_KS10: KS10_UPPROT Position          */
#define CSS_KS10_KS10_UPPROT_Msk              (0x03UL << CSS_KS10_KS10_UPPROT_Pos)                    /*!< CSS_KS10: KS10_UPPROT Mask              */

/* ===============================      CSS_KS11     ============================== */
#define CSS_KS11_KS11_KSIZE_Pos               0                                                       /*!< CSS_KS11: KS11_KSIZE Position           */
#define CSS_KS11_KS11_KSIZE_Msk               (0x01UL << CSS_KS11_KS11_KSIZE_Pos)                     /*!< CSS_KS11: KS11_KSIZE Mask               */
#define CSS_KS11_KS11_RSVD0_Pos               1                                                       /*!< CSS_KS11: KS11_RSVD0 Position           */
#define CSS_KS11_KS11_RSVD0_Msk               (0x0fUL << CSS_KS11_KS11_RSVD0_Pos)                     /*!< CSS_KS11: KS11_RSVD0 Mask               */
#define CSS_KS11_KS11_KACT_Pos                5                                                       /*!< CSS_KS11: KS11_KACT Position            */
#define CSS_KS11_KS11_KACT_Msk                (0x01UL << CSS_KS11_KS11_KACT_Pos)                      /*!< CSS_KS11: KS11_KACT Mask                */
#define CSS_KS11_KS11_KBASE_Pos               6                                                       /*!< CSS_KS11: KS11_KBASE Position           */
#define CSS_KS11_KS11_KBASE_Msk               (0x01UL << CSS_KS11_KS11_KBASE_Pos)                     /*!< CSS_KS11: KS11_KBASE Mask               */
#define CSS_KS11_KS11_FGP_Pos                 7                                                       /*!< CSS_KS11: KS11_FGP Position             */
#define CSS_KS11_KS11_FGP_Msk                 (0x01UL << CSS_KS11_KS11_FGP_Pos)                       /*!< CSS_KS11: KS11_FGP Mask                 */
#define CSS_KS11_KS11_FRTN_Pos                8                                                       /*!< CSS_KS11: KS11_FRTN Position            */
#define CSS_KS11_KS11_FRTN_Msk                (0x01UL << CSS_KS11_KS11_FRTN_Pos)                      /*!< CSS_KS11: KS11_FRTN Mask                */
#define CSS_KS11_KS11_FHWO_Pos                9                                                       /*!< CSS_KS11: KS11_FHWO Position            */
#define CSS_KS11_KS11_FHWO_Msk                (0x01UL << CSS_KS11_KS11_FHWO_Pos)                      /*!< CSS_KS11: KS11_FHWO Mask                */
#define CSS_KS11_KS11_RSVD1_Pos               10                                                      /*!< CSS_KS11: KS11_RSVD1 Position           */
#define CSS_KS11_KS11_RSVD1_Msk               (0x07UL << CSS_KS11_KS11_RSVD1_Pos)                     /*!< CSS_KS11: KS11_RSVD1 Mask               */
#define CSS_KS11_KS11_UCMAC_Pos               13                                                      /*!< CSS_KS11: KS11_UCMAC Position           */
#define CSS_KS11_KS11_UCMAC_Msk               (0x01UL << CSS_KS11_KS11_UCMAC_Pos)                     /*!< CSS_KS11: KS11_UCMAC Mask               */
#define CSS_KS11_KS11_UKSK_Pos                14                                                      /*!< CSS_KS11: KS11_UKSK Position            */
#define CSS_KS11_KS11_UKSK_Msk                (0x01UL << CSS_KS11_KS11_UKSK_Pos)                      /*!< CSS_KS11: KS11_UKSK Mask                */
#define CSS_KS11_KS11_URTF_Pos                15                                                      /*!< CSS_KS11: KS11_URTF Position            */
#define CSS_KS11_KS11_URTF_Msk                (0x01UL << CSS_KS11_KS11_URTF_Pos)                      /*!< CSS_KS11: KS11_URTF Mask                */
#define CSS_KS11_KS11_UCKDF_Pos               16                                                      /*!< CSS_KS11: KS11_UCKDF Position           */
#define CSS_KS11_KS11_UCKDF_Msk               (0x01UL << CSS_KS11_KS11_UCKDF_Pos)                     /*!< CSS_KS11: KS11_UCKDF Mask               */
#define CSS_KS11_KS11_UHKDF_Pos               17                                                      /*!< CSS_KS11: KS11_UHKDF Position           */
#define CSS_KS11_KS11_UHKDF_Msk               (0x01UL << CSS_KS11_KS11_UHKDF_Pos)                     /*!< CSS_KS11: KS11_UHKDF Mask               */
#define CSS_KS11_KS11_UECSG_Pos               18                                                      /*!< CSS_KS11: KS11_UECSG Position           */
#define CSS_KS11_KS11_UECSG_Msk               (0x01UL << CSS_KS11_KS11_UECSG_Pos)                     /*!< CSS_KS11: KS11_UECSG Mask               */
#define CSS_KS11_KS11_UECDH_Pos               19                                                      /*!< CSS_KS11: KS11_UECDH Position           */
#define CSS_KS11_KS11_UECDH_Msk               (0x01UL << CSS_KS11_KS11_UECDH_Pos)                     /*!< CSS_KS11: KS11_UECDH Mask               */
#define CSS_KS11_KS11_UAES_Pos                20                                                      /*!< CSS_KS11: KS11_UAES Position            */
#define CSS_KS11_KS11_UAES_Msk                (0x01UL << CSS_KS11_KS11_UAES_Pos)                      /*!< CSS_KS11: KS11_UAES Mask                */
#define CSS_KS11_KS11_UHMAC_Pos               21                                                      /*!< CSS_KS11: KS11_UHMAC Position           */
#define CSS_KS11_KS11_UHMAC_Msk               (0x01UL << CSS_KS11_KS11_UHMAC_Pos)                     /*!< CSS_KS11: KS11_UHMAC Mask               */
#define CSS_KS11_KS11_UKWK_Pos                22                                                      /*!< CSS_KS11: KS11_UKWK Position            */
#define CSS_KS11_KS11_UKWK_Msk                (0x01UL << CSS_KS11_KS11_UKWK_Pos)                      /*!< CSS_KS11: KS11_UKWK Mask                */
#define CSS_KS11_KS11_UKUOK_Pos               23                                                      /*!< CSS_KS11: KS11_UKUOK Position           */
#define CSS_KS11_KS11_UKUOK_Msk               (0x01UL << CSS_KS11_KS11_UKUOK_Pos)                     /*!< CSS_KS11: KS11_UKUOK Mask               */
#define CSS_KS11_KS11_UTLSPMS_Pos             24                                                      /*!< CSS_KS11: KS11_UTLSPMS Position         */
#define CSS_KS11_KS11_UTLSPMS_Msk             (0x01UL << CSS_KS11_KS11_UTLSPMS_Pos)                   /*!< CSS_KS11: KS11_UTLSPMS Mask             */
#define CSS_KS11_KS11_UTLSMS_Pos              25                                                      /*!< CSS_KS11: KS11_UTLSMS Position          */
#define CSS_KS11_KS11_UTLSMS_Msk              (0x01UL << CSS_KS11_KS11_UTLSMS_Pos)                    /*!< CSS_KS11: KS11_UTLSMS Mask              */
#define CSS_KS11_KS11_UKGSRC_Pos              26                                                      /*!< CSS_KS11: KS11_UKGSRC Position          */
#define CSS_KS11_KS11_UKGSRC_Msk              (0x01UL << CSS_KS11_KS11_UKGSRC_Pos)                    /*!< CSS_KS11: KS11_UKGSRC Mask              */
#define CSS_KS11_KS11_UHWO_Pos                27                                                      /*!< CSS_KS11: KS11_UHWO Position            */
#define CSS_KS11_KS11_UHWO_Msk                (0x01UL << CSS_KS11_KS11_UHWO_Pos)                      /*!< CSS_KS11: KS11_UHWO Mask                */
#define CSS_KS11_KS11_UWRPOK_Pos              28                                                      /*!< CSS_KS11: KS11_UWRPOK Position          */
#define CSS_KS11_KS11_UWRPOK_Msk              (0x01UL << CSS_KS11_KS11_UWRPOK_Pos)                    /*!< CSS_KS11: KS11_UWRPOK Mask              */
#define CSS_KS11_KS11_UDUK_Pos                29                                                      /*!< CSS_KS11: KS11_UDUK Position            */
#define CSS_KS11_KS11_UDUK_Msk                (0x01UL << CSS_KS11_KS11_UDUK_Pos)                      /*!< CSS_KS11: KS11_UDUK Mask                */
#define CSS_KS11_KS11_UPPROT_Pos              30                                                      /*!< CSS_KS11: KS11_UPPROT Position          */
#define CSS_KS11_KS11_UPPROT_Msk              (0x03UL << CSS_KS11_KS11_UPPROT_Pos)                    /*!< CSS_KS11: KS11_UPPROT Mask              */

/* ===============================      CSS_KS12     ============================== */
#define CSS_KS12_KS12_KSIZE_Pos               0                                                       /*!< CSS_KS12: KS12_KSIZE Position           */
#define CSS_KS12_KS12_KSIZE_Msk               (0x01UL << CSS_KS12_KS12_KSIZE_Pos)                     /*!< CSS_KS12: KS12_KSIZE Mask               */
#define CSS_KS12_KS12_RSVD0_Pos               1                                                       /*!< CSS_KS12: KS12_RSVD0 Position           */
#define CSS_KS12_KS12_RSVD0_Msk               (0x0fUL << CSS_KS12_KS12_RSVD0_Pos)                     /*!< CSS_KS12: KS12_RSVD0 Mask               */
#define CSS_KS12_KS12_KACT_Pos                5                                                       /*!< CSS_KS12: KS12_KACT Position            */
#define CSS_KS12_KS12_KACT_Msk                (0x01UL << CSS_KS12_KS12_KACT_Pos)                      /*!< CSS_KS12: KS12_KACT Mask                */
#define CSS_KS12_KS12_KBASE_Pos               6                                                       /*!< CSS_KS12: KS12_KBASE Position           */
#define CSS_KS12_KS12_KBASE_Msk               (0x01UL << CSS_KS12_KS12_KBASE_Pos)                     /*!< CSS_KS12: KS12_KBASE Mask               */
#define CSS_KS12_KS12_FGP_Pos                 7                                                       /*!< CSS_KS12: KS12_FGP Position             */
#define CSS_KS12_KS12_FGP_Msk                 (0x01UL << CSS_KS12_KS12_FGP_Pos)                       /*!< CSS_KS12: KS12_FGP Mask                 */
#define CSS_KS12_KS12_FRTN_Pos                8                                                       /*!< CSS_KS12: KS12_FRTN Position            */
#define CSS_KS12_KS12_FRTN_Msk                (0x01UL << CSS_KS12_KS12_FRTN_Pos)                      /*!< CSS_KS12: KS12_FRTN Mask                */
#define CSS_KS12_KS12_FHWO_Pos                9                                                       /*!< CSS_KS12: KS12_FHWO Position            */
#define CSS_KS12_KS12_FHWO_Msk                (0x01UL << CSS_KS12_KS12_FHWO_Pos)                      /*!< CSS_KS12: KS12_FHWO Mask                */
#define CSS_KS12_KS12_RSVD1_Pos               10                                                      /*!< CSS_KS12: KS12_RSVD1 Position           */
#define CSS_KS12_KS12_RSVD1_Msk               (0x07UL << CSS_KS12_KS12_RSVD1_Pos)                     /*!< CSS_KS12: KS12_RSVD1 Mask               */
#define CSS_KS12_KS12_UCMAC_Pos               13                                                      /*!< CSS_KS12: KS12_UCMAC Position           */
#define CSS_KS12_KS12_UCMAC_Msk               (0x01UL << CSS_KS12_KS12_UCMAC_Pos)                     /*!< CSS_KS12: KS12_UCMAC Mask               */
#define CSS_KS12_KS12_UKSK_Pos                14                                                      /*!< CSS_KS12: KS12_UKSK Position            */
#define CSS_KS12_KS12_UKSK_Msk                (0x01UL << CSS_KS12_KS12_UKSK_Pos)                      /*!< CSS_KS12: KS12_UKSK Mask                */
#define CSS_KS12_KS12_URTF_Pos                15                                                      /*!< CSS_KS12: KS12_URTF Position            */
#define CSS_KS12_KS12_URTF_Msk                (0x01UL << CSS_KS12_KS12_URTF_Pos)                      /*!< CSS_KS12: KS12_URTF Mask                */
#define CSS_KS12_KS12_UCKDF_Pos               16                                                      /*!< CSS_KS12: KS12_UCKDF Position           */
#define CSS_KS12_KS12_UCKDF_Msk               (0x01UL << CSS_KS12_KS12_UCKDF_Pos)                     /*!< CSS_KS12: KS12_UCKDF Mask               */
#define CSS_KS12_KS12_UHKDF_Pos               17                                                      /*!< CSS_KS12: KS12_UHKDF Position           */
#define CSS_KS12_KS12_UHKDF_Msk               (0x01UL << CSS_KS12_KS12_UHKDF_Pos)                     /*!< CSS_KS12: KS12_UHKDF Mask               */
#define CSS_KS12_KS12_UECSG_Pos               18                                                      /*!< CSS_KS12: KS12_UECSG Position           */
#define CSS_KS12_KS12_UECSG_Msk               (0x01UL << CSS_KS12_KS12_UECSG_Pos)                     /*!< CSS_KS12: KS12_UECSG Mask               */
#define CSS_KS12_KS12_UECDH_Pos               19                                                      /*!< CSS_KS12: KS12_UECDH Position           */
#define CSS_KS12_KS12_UECDH_Msk               (0x01UL << CSS_KS12_KS12_UECDH_Pos)                     /*!< CSS_KS12: KS12_UECDH Mask               */
#define CSS_KS12_KS12_UAES_Pos                20                                                      /*!< CSS_KS12: KS12_UAES Position            */
#define CSS_KS12_KS12_UAES_Msk                (0x01UL << CSS_KS12_KS12_UAES_Pos)                      /*!< CSS_KS12: KS12_UAES Mask                */
#define CSS_KS12_KS12_UHMAC_Pos               21                                                      /*!< CSS_KS12: KS12_UHMAC Position           */
#define CSS_KS12_KS12_UHMAC_Msk               (0x01UL << CSS_KS12_KS12_UHMAC_Pos)                     /*!< CSS_KS12: KS12_UHMAC Mask               */
#define CSS_KS12_KS12_UKWK_Pos                22                                                      /*!< CSS_KS12: KS12_UKWK Position            */
#define CSS_KS12_KS12_UKWK_Msk                (0x01UL << CSS_KS12_KS12_UKWK_Pos)                      /*!< CSS_KS12: KS12_UKWK Mask                */
#define CSS_KS12_KS12_UKUOK_Pos               23                                                      /*!< CSS_KS12: KS12_UKUOK Position           */
#define CSS_KS12_KS12_UKUOK_Msk               (0x01UL << CSS_KS12_KS12_UKUOK_Pos)                     /*!< CSS_KS12: KS12_UKUOK Mask               */
#define CSS_KS12_KS12_UTLSPMS_Pos             24                                                      /*!< CSS_KS12: KS12_UTLSPMS Position         */
#define CSS_KS12_KS12_UTLSPMS_Msk             (0x01UL << CSS_KS12_KS12_UTLSPMS_Pos)                   /*!< CSS_KS12: KS12_UTLSPMS Mask             */
#define CSS_KS12_KS12_UTLSMS_Pos              25                                                      /*!< CSS_KS12: KS12_UTLSMS Position          */
#define CSS_KS12_KS12_UTLSMS_Msk              (0x01UL << CSS_KS12_KS12_UTLSMS_Pos)                    /*!< CSS_KS12: KS12_UTLSMS Mask              */
#define CSS_KS12_KS12_UKGSRC_Pos              26                                                      /*!< CSS_KS12: KS12_UKGSRC Position          */
#define CSS_KS12_KS12_UKGSRC_Msk              (0x01UL << CSS_KS12_KS12_UKGSRC_Pos)                    /*!< CSS_KS12: KS12_UKGSRC Mask              */
#define CSS_KS12_KS12_UHWO_Pos                27                                                      /*!< CSS_KS12: KS12_UHWO Position            */
#define CSS_KS12_KS12_UHWO_Msk                (0x01UL << CSS_KS12_KS12_UHWO_Pos)                      /*!< CSS_KS12: KS12_UHWO Mask                */
#define CSS_KS12_KS12_UWRPOK_Pos              28                                                      /*!< CSS_KS12: KS12_UWRPOK Position          */
#define CSS_KS12_KS12_UWRPOK_Msk              (0x01UL << CSS_KS12_KS12_UWRPOK_Pos)                    /*!< CSS_KS12: KS12_UWRPOK Mask              */
#define CSS_KS12_KS12_UDUK_Pos                29                                                      /*!< CSS_KS12: KS12_UDUK Position            */
#define CSS_KS12_KS12_UDUK_Msk                (0x01UL << CSS_KS12_KS12_UDUK_Pos)                      /*!< CSS_KS12: KS12_UDUK Mask                */
#define CSS_KS12_KS12_UPPROT_Pos              30                                                      /*!< CSS_KS12: KS12_UPPROT Position          */
#define CSS_KS12_KS12_UPPROT_Msk              (0x03UL << CSS_KS12_KS12_UPPROT_Pos)                    /*!< CSS_KS12: KS12_UPPROT Mask              */

/* ===============================      CSS_KS13     ============================== */
#define CSS_KS13_KS13_KSIZE_Pos               0                                                       /*!< CSS_KS13: KS13_KSIZE Position           */
#define CSS_KS13_KS13_KSIZE_Msk               (0x01UL << CSS_KS13_KS13_KSIZE_Pos)                     /*!< CSS_KS13: KS13_KSIZE Mask               */
#define CSS_KS13_KS13_RSVD0_Pos               1                                                       /*!< CSS_KS13: KS13_RSVD0 Position           */
#define CSS_KS13_KS13_RSVD0_Msk               (0x0fUL << CSS_KS13_KS13_RSVD0_Pos)                     /*!< CSS_KS13: KS13_RSVD0 Mask               */
#define CSS_KS13_KS13_KACT_Pos                5                                                       /*!< CSS_KS13: KS13_KACT Position            */
#define CSS_KS13_KS13_KACT_Msk                (0x01UL << CSS_KS13_KS13_KACT_Pos)                      /*!< CSS_KS13: KS13_KACT Mask                */
#define CSS_KS13_KS13_KBASE_Pos               6                                                       /*!< CSS_KS13: KS13_KBASE Position           */
#define CSS_KS13_KS13_KBASE_Msk               (0x01UL << CSS_KS13_KS13_KBASE_Pos)                     /*!< CSS_KS13: KS13_KBASE Mask               */
#define CSS_KS13_KS13_FGP_Pos                 7                                                       /*!< CSS_KS13: KS13_FGP Position             */
#define CSS_KS13_KS13_FGP_Msk                 (0x01UL << CSS_KS13_KS13_FGP_Pos)                       /*!< CSS_KS13: KS13_FGP Mask                 */
#define CSS_KS13_KS13_FRTN_Pos                8                                                       /*!< CSS_KS13: KS13_FRTN Position            */
#define CSS_KS13_KS13_FRTN_Msk                (0x01UL << CSS_KS13_KS13_FRTN_Pos)                      /*!< CSS_KS13: KS13_FRTN Mask                */
#define CSS_KS13_KS13_FHWO_Pos                9                                                       /*!< CSS_KS13: KS13_FHWO Position            */
#define CSS_KS13_KS13_FHWO_Msk                (0x01UL << CSS_KS13_KS13_FHWO_Pos)                      /*!< CSS_KS13: KS13_FHWO Mask                */
#define CSS_KS13_KS13_RSVD1_Pos               10                                                      /*!< CSS_KS13: KS13_RSVD1 Position           */
#define CSS_KS13_KS13_RSVD1_Msk               (0x07UL << CSS_KS13_KS13_RSVD1_Pos)                     /*!< CSS_KS13: KS13_RSVD1 Mask               */
#define CSS_KS13_KS13_UCMAC_Pos               13                                                      /*!< CSS_KS13: KS13_UCMAC Position           */
#define CSS_KS13_KS13_UCMAC_Msk               (0x01UL << CSS_KS13_KS13_UCMAC_Pos)                     /*!< CSS_KS13: KS13_UCMAC Mask               */
#define CSS_KS13_KS13_UKSK_Pos                14                                                      /*!< CSS_KS13: KS13_UKSK Position            */
#define CSS_KS13_KS13_UKSK_Msk                (0x01UL << CSS_KS13_KS13_UKSK_Pos)                      /*!< CSS_KS13: KS13_UKSK Mask                */
#define CSS_KS13_KS13_URTF_Pos                15                                                      /*!< CSS_KS13: KS13_URTF Position            */
#define CSS_KS13_KS13_URTF_Msk                (0x01UL << CSS_KS13_KS13_URTF_Pos)                      /*!< CSS_KS13: KS13_URTF Mask                */
#define CSS_KS13_KS13_UCKDF_Pos               16                                                      /*!< CSS_KS13: KS13_UCKDF Position           */
#define CSS_KS13_KS13_UCKDF_Msk               (0x01UL << CSS_KS13_KS13_UCKDF_Pos)                     /*!< CSS_KS13: KS13_UCKDF Mask               */
#define CSS_KS13_KS13_UHKDF_Pos               17                                                      /*!< CSS_KS13: KS13_UHKDF Position           */
#define CSS_KS13_KS13_UHKDF_Msk               (0x01UL << CSS_KS13_KS13_UHKDF_Pos)                     /*!< CSS_KS13: KS13_UHKDF Mask               */
#define CSS_KS13_KS13_UECSG_Pos               18                                                      /*!< CSS_KS13: KS13_UECSG Position           */
#define CSS_KS13_KS13_UECSG_Msk               (0x01UL << CSS_KS13_KS13_UECSG_Pos)                     /*!< CSS_KS13: KS13_UECSG Mask               */
#define CSS_KS13_KS13_UECDH_Pos               19                                                      /*!< CSS_KS13: KS13_UECDH Position           */
#define CSS_KS13_KS13_UECDH_Msk               (0x01UL << CSS_KS13_KS13_UECDH_Pos)                     /*!< CSS_KS13: KS13_UECDH Mask               */
#define CSS_KS13_KS13_UAES_Pos                20                                                      /*!< CSS_KS13: KS13_UAES Position            */
#define CSS_KS13_KS13_UAES_Msk                (0x01UL << CSS_KS13_KS13_UAES_Pos)                      /*!< CSS_KS13: KS13_UAES Mask                */
#define CSS_KS13_KS13_UHMAC_Pos               21                                                      /*!< CSS_KS13: KS13_UHMAC Position           */
#define CSS_KS13_KS13_UHMAC_Msk               (0x01UL << CSS_KS13_KS13_UHMAC_Pos)                     /*!< CSS_KS13: KS13_UHMAC Mask               */
#define CSS_KS13_KS13_UKWK_Pos                22                                                      /*!< CSS_KS13: KS13_UKWK Position            */
#define CSS_KS13_KS13_UKWK_Msk                (0x01UL << CSS_KS13_KS13_UKWK_Pos)                      /*!< CSS_KS13: KS13_UKWK Mask                */
#define CSS_KS13_KS13_UKUOK_Pos               23                                                      /*!< CSS_KS13: KS13_UKUOK Position           */
#define CSS_KS13_KS13_UKUOK_Msk               (0x01UL << CSS_KS13_KS13_UKUOK_Pos)                     /*!< CSS_KS13: KS13_UKUOK Mask               */
#define CSS_KS13_KS13_UTLSPMS_Pos             24                                                      /*!< CSS_KS13: KS13_UTLSPMS Position         */
#define CSS_KS13_KS13_UTLSPMS_Msk             (0x01UL << CSS_KS13_KS13_UTLSPMS_Pos)                   /*!< CSS_KS13: KS13_UTLSPMS Mask             */
#define CSS_KS13_KS13_UTLSMS_Pos              25                                                      /*!< CSS_KS13: KS13_UTLSMS Position          */
#define CSS_KS13_KS13_UTLSMS_Msk              (0x01UL << CSS_KS13_KS13_UTLSMS_Pos)                    /*!< CSS_KS13: KS13_UTLSMS Mask              */
#define CSS_KS13_KS13_UKGSRC_Pos              26                                                      /*!< CSS_KS13: KS13_UKGSRC Position          */
#define CSS_KS13_KS13_UKGSRC_Msk              (0x01UL << CSS_KS13_KS13_UKGSRC_Pos)                    /*!< CSS_KS13: KS13_UKGSRC Mask              */
#define CSS_KS13_KS13_UHWO_Pos                27                                                      /*!< CSS_KS13: KS13_UHWO Position            */
#define CSS_KS13_KS13_UHWO_Msk                (0x01UL << CSS_KS13_KS13_UHWO_Pos)                      /*!< CSS_KS13: KS13_UHWO Mask                */
#define CSS_KS13_KS13_UWRPOK_Pos              28                                                      /*!< CSS_KS13: KS13_UWRPOK Position          */
#define CSS_KS13_KS13_UWRPOK_Msk              (0x01UL << CSS_KS13_KS13_UWRPOK_Pos)                    /*!< CSS_KS13: KS13_UWRPOK Mask              */
#define CSS_KS13_KS13_UDUK_Pos                29                                                      /*!< CSS_KS13: KS13_UDUK Position            */
#define CSS_KS13_KS13_UDUK_Msk                (0x01UL << CSS_KS13_KS13_UDUK_Pos)                      /*!< CSS_KS13: KS13_UDUK Mask                */
#define CSS_KS13_KS13_UPPROT_Pos              30                                                      /*!< CSS_KS13: KS13_UPPROT Position          */
#define CSS_KS13_KS13_UPPROT_Msk              (0x03UL << CSS_KS13_KS13_UPPROT_Pos)                    /*!< CSS_KS13: KS13_UPPROT Mask              */

/* ===============================      CSS_KS14     ============================== */
#define CSS_KS14_KS14_KSIZE_Pos               0                                                       /*!< CSS_KS14: KS14_KSIZE Position           */
#define CSS_KS14_KS14_KSIZE_Msk               (0x01UL << CSS_KS14_KS14_KSIZE_Pos)                     /*!< CSS_KS14: KS14_KSIZE Mask               */
#define CSS_KS14_KS14_RSVD0_Pos               1                                                       /*!< CSS_KS14: KS14_RSVD0 Position           */
#define CSS_KS14_KS14_RSVD0_Msk               (0x0fUL << CSS_KS14_KS14_RSVD0_Pos)                     /*!< CSS_KS14: KS14_RSVD0 Mask               */
#define CSS_KS14_KS14_KACT_Pos                5                                                       /*!< CSS_KS14: KS14_KACT Position            */
#define CSS_KS14_KS14_KACT_Msk                (0x01UL << CSS_KS14_KS14_KACT_Pos)                      /*!< CSS_KS14: KS14_KACT Mask                */
#define CSS_KS14_KS14_KBASE_Pos               6                                                       /*!< CSS_KS14: KS14_KBASE Position           */
#define CSS_KS14_KS14_KBASE_Msk               (0x01UL << CSS_KS14_KS14_KBASE_Pos)                     /*!< CSS_KS14: KS14_KBASE Mask               */
#define CSS_KS14_KS14_FGP_Pos                 7                                                       /*!< CSS_KS14: KS14_FGP Position             */
#define CSS_KS14_KS14_FGP_Msk                 (0x01UL << CSS_KS14_KS14_FGP_Pos)                       /*!< CSS_KS14: KS14_FGP Mask                 */
#define CSS_KS14_KS14_FRTN_Pos                8                                                       /*!< CSS_KS14: KS14_FRTN Position            */
#define CSS_KS14_KS14_FRTN_Msk                (0x01UL << CSS_KS14_KS14_FRTN_Pos)                      /*!< CSS_KS14: KS14_FRTN Mask                */
#define CSS_KS14_KS14_FHWO_Pos                9                                                       /*!< CSS_KS14: KS14_FHWO Position            */
#define CSS_KS14_KS14_FHWO_Msk                (0x01UL << CSS_KS14_KS14_FHWO_Pos)                      /*!< CSS_KS14: KS14_FHWO Mask                */
#define CSS_KS14_KS14_RSVD1_Pos               10                                                      /*!< CSS_KS14: KS14_RSVD1 Position           */
#define CSS_KS14_KS14_RSVD1_Msk               (0x07UL << CSS_KS14_KS14_RSVD1_Pos)                     /*!< CSS_KS14: KS14_RSVD1 Mask               */
#define CSS_KS14_KS14_UCMAC_Pos               13                                                      /*!< CSS_KS14: KS14_UCMAC Position           */
#define CSS_KS14_KS14_UCMAC_Msk               (0x01UL << CSS_KS14_KS14_UCMAC_Pos)                     /*!< CSS_KS14: KS14_UCMAC Mask               */
#define CSS_KS14_KS14_UKSK_Pos                14                                                      /*!< CSS_KS14: KS14_UKSK Position            */
#define CSS_KS14_KS14_UKSK_Msk                (0x01UL << CSS_KS14_KS14_UKSK_Pos)                      /*!< CSS_KS14: KS14_UKSK Mask                */
#define CSS_KS14_KS14_URTF_Pos                15                                                      /*!< CSS_KS14: KS14_URTF Position            */
#define CSS_KS14_KS14_URTF_Msk                (0x01UL << CSS_KS14_KS14_URTF_Pos)                      /*!< CSS_KS14: KS14_URTF Mask                */
#define CSS_KS14_KS14_UCKDF_Pos               16                                                      /*!< CSS_KS14: KS14_UCKDF Position           */
#define CSS_KS14_KS14_UCKDF_Msk               (0x01UL << CSS_KS14_KS14_UCKDF_Pos)                     /*!< CSS_KS14: KS14_UCKDF Mask               */
#define CSS_KS14_KS14_UHKDF_Pos               17                                                      /*!< CSS_KS14: KS14_UHKDF Position           */
#define CSS_KS14_KS14_UHKDF_Msk               (0x01UL << CSS_KS14_KS14_UHKDF_Pos)                     /*!< CSS_KS14: KS14_UHKDF Mask               */
#define CSS_KS14_KS14_UECSG_Pos               18                                                      /*!< CSS_KS14: KS14_UECSG Position           */
#define CSS_KS14_KS14_UECSG_Msk               (0x01UL << CSS_KS14_KS14_UECSG_Pos)                     /*!< CSS_KS14: KS14_UECSG Mask               */
#define CSS_KS14_KS14_UECDH_Pos               19                                                      /*!< CSS_KS14: KS14_UECDH Position           */
#define CSS_KS14_KS14_UECDH_Msk               (0x01UL << CSS_KS14_KS14_UECDH_Pos)                     /*!< CSS_KS14: KS14_UECDH Mask               */
#define CSS_KS14_KS14_UAES_Pos                20                                                      /*!< CSS_KS14: KS14_UAES Position            */
#define CSS_KS14_KS14_UAES_Msk                (0x01UL << CSS_KS14_KS14_UAES_Pos)                      /*!< CSS_KS14: KS14_UAES Mask                */
#define CSS_KS14_KS14_UHMAC_Pos               21                                                      /*!< CSS_KS14: KS14_UHMAC Position           */
#define CSS_KS14_KS14_UHMAC_Msk               (0x01UL << CSS_KS14_KS14_UHMAC_Pos)                     /*!< CSS_KS14: KS14_UHMAC Mask               */
#define CSS_KS14_KS14_UKWK_Pos                22                                                      /*!< CSS_KS14: KS14_UKWK Position            */
#define CSS_KS14_KS14_UKWK_Msk                (0x01UL << CSS_KS14_KS14_UKWK_Pos)                      /*!< CSS_KS14: KS14_UKWK Mask                */
#define CSS_KS14_KS14_UKUOK_Pos               23                                                      /*!< CSS_KS14: KS14_UKUOK Position           */
#define CSS_KS14_KS14_UKUOK_Msk               (0x01UL << CSS_KS14_KS14_UKUOK_Pos)                     /*!< CSS_KS14: KS14_UKUOK Mask               */
#define CSS_KS14_KS14_UTLSPMS_Pos             24                                                      /*!< CSS_KS14: KS14_UTLSPMS Position         */
#define CSS_KS14_KS14_UTLSPMS_Msk             (0x01UL << CSS_KS14_KS14_UTLSPMS_Pos)                   /*!< CSS_KS14: KS14_UTLSPMS Mask             */
#define CSS_KS14_KS14_UTLSMS_Pos              25                                                      /*!< CSS_KS14: KS14_UTLSMS Position          */
#define CSS_KS14_KS14_UTLSMS_Msk              (0x01UL << CSS_KS14_KS14_UTLSMS_Pos)                    /*!< CSS_KS14: KS14_UTLSMS Mask              */
#define CSS_KS14_KS14_UKGSRC_Pos              26                                                      /*!< CSS_KS14: KS14_UKGSRC Position          */
#define CSS_KS14_KS14_UKGSRC_Msk              (0x01UL << CSS_KS14_KS14_UKGSRC_Pos)                    /*!< CSS_KS14: KS14_UKGSRC Mask              */
#define CSS_KS14_KS14_UHWO_Pos                27                                                      /*!< CSS_KS14: KS14_UHWO Position            */
#define CSS_KS14_KS14_UHWO_Msk                (0x01UL << CSS_KS14_KS14_UHWO_Pos)                      /*!< CSS_KS14: KS14_UHWO Mask                */
#define CSS_KS14_KS14_UWRPOK_Pos              28                                                      /*!< CSS_KS14: KS14_UWRPOK Position          */
#define CSS_KS14_KS14_UWRPOK_Msk              (0x01UL << CSS_KS14_KS14_UWRPOK_Pos)                    /*!< CSS_KS14: KS14_UWRPOK Mask              */
#define CSS_KS14_KS14_UDUK_Pos                29                                                      /*!< CSS_KS14: KS14_UDUK Position            */
#define CSS_KS14_KS14_UDUK_Msk                (0x01UL << CSS_KS14_KS14_UDUK_Pos)                      /*!< CSS_KS14: KS14_UDUK Mask                */
#define CSS_KS14_KS14_UPPROT_Pos              30                                                      /*!< CSS_KS14: KS14_UPPROT Position          */
#define CSS_KS14_KS14_UPPROT_Msk              (0x03UL << CSS_KS14_KS14_UPPROT_Pos)                    /*!< CSS_KS14: KS14_UPPROT Mask              */

/* ===============================      CSS_KS15     ============================== */
#define CSS_KS15_KS15_KSIZE_Pos               0                                                       /*!< CSS_KS15: KS15_KSIZE Position           */
#define CSS_KS15_KS15_KSIZE_Msk               (0x01UL << CSS_KS15_KS15_KSIZE_Pos)                     /*!< CSS_KS15: KS15_KSIZE Mask               */
#define CSS_KS15_KS15_RSVD0_Pos               1                                                       /*!< CSS_KS15: KS15_RSVD0 Position           */
#define CSS_KS15_KS15_RSVD0_Msk               (0x0fUL << CSS_KS15_KS15_RSVD0_Pos)                     /*!< CSS_KS15: KS15_RSVD0 Mask               */
#define CSS_KS15_KS15_KACT_Pos                5                                                       /*!< CSS_KS15: KS15_KACT Position            */
#define CSS_KS15_KS15_KACT_Msk                (0x01UL << CSS_KS15_KS15_KACT_Pos)                      /*!< CSS_KS15: KS15_KACT Mask                */
#define CSS_KS15_KS15_KBASE_Pos               6                                                       /*!< CSS_KS15: KS15_KBASE Position           */
#define CSS_KS15_KS15_KBASE_Msk               (0x01UL << CSS_KS15_KS15_KBASE_Pos)                     /*!< CSS_KS15: KS15_KBASE Mask               */
#define CSS_KS15_KS15_FGP_Pos                 7                                                       /*!< CSS_KS15: KS15_FGP Position             */
#define CSS_KS15_KS15_FGP_Msk                 (0x01UL << CSS_KS15_KS15_FGP_Pos)                       /*!< CSS_KS15: KS15_FGP Mask                 */
#define CSS_KS15_KS15_FRTN_Pos                8                                                       /*!< CSS_KS15: KS15_FRTN Position            */
#define CSS_KS15_KS15_FRTN_Msk                (0x01UL << CSS_KS15_KS15_FRTN_Pos)                      /*!< CSS_KS15: KS15_FRTN Mask                */
#define CSS_KS15_KS15_FHWO_Pos                9                                                       /*!< CSS_KS15: KS15_FHWO Position            */
#define CSS_KS15_KS15_FHWO_Msk                (0x01UL << CSS_KS15_KS15_FHWO_Pos)                      /*!< CSS_KS15: KS15_FHWO Mask                */
#define CSS_KS15_KS15_RSVD1_Pos               10                                                      /*!< CSS_KS15: KS15_RSVD1 Position           */
#define CSS_KS15_KS15_RSVD1_Msk               (0x07UL << CSS_KS15_KS15_RSVD1_Pos)                     /*!< CSS_KS15: KS15_RSVD1 Mask               */
#define CSS_KS15_KS15_UCMAC_Pos               13                                                      /*!< CSS_KS15: KS15_UCMAC Position           */
#define CSS_KS15_KS15_UCMAC_Msk               (0x01UL << CSS_KS15_KS15_UCMAC_Pos)                     /*!< CSS_KS15: KS15_UCMAC Mask               */
#define CSS_KS15_KS15_UKSK_Pos                14                                                      /*!< CSS_KS15: KS15_UKSK Position            */
#define CSS_KS15_KS15_UKSK_Msk                (0x01UL << CSS_KS15_KS15_UKSK_Pos)                      /*!< CSS_KS15: KS15_UKSK Mask                */
#define CSS_KS15_KS15_URTF_Pos                15                                                      /*!< CSS_KS15: KS15_URTF Position            */
#define CSS_KS15_KS15_URTF_Msk                (0x01UL << CSS_KS15_KS15_URTF_Pos)                      /*!< CSS_KS15: KS15_URTF Mask                */
#define CSS_KS15_KS15_UCKDF_Pos               16                                                      /*!< CSS_KS15: KS15_UCKDF Position           */
#define CSS_KS15_KS15_UCKDF_Msk               (0x01UL << CSS_KS15_KS15_UCKDF_Pos)                     /*!< CSS_KS15: KS15_UCKDF Mask               */
#define CSS_KS15_KS15_UHKDF_Pos               17                                                      /*!< CSS_KS15: KS15_UHKDF Position           */
#define CSS_KS15_KS15_UHKDF_Msk               (0x01UL << CSS_KS15_KS15_UHKDF_Pos)                     /*!< CSS_KS15: KS15_UHKDF Mask               */
#define CSS_KS15_KS15_UECSG_Pos               18                                                      /*!< CSS_KS15: KS15_UECSG Position           */
#define CSS_KS15_KS15_UECSG_Msk               (0x01UL << CSS_KS15_KS15_UECSG_Pos)                     /*!< CSS_KS15: KS15_UECSG Mask               */
#define CSS_KS15_KS15_UECDH_Pos               19                                                      /*!< CSS_KS15: KS15_UECDH Position           */
#define CSS_KS15_KS15_UECDH_Msk               (0x01UL << CSS_KS15_KS15_UECDH_Pos)                     /*!< CSS_KS15: KS15_UECDH Mask               */
#define CSS_KS15_KS15_UAES_Pos                20                                                      /*!< CSS_KS15: KS15_UAES Position            */
#define CSS_KS15_KS15_UAES_Msk                (0x01UL << CSS_KS15_KS15_UAES_Pos)                      /*!< CSS_KS15: KS15_UAES Mask                */
#define CSS_KS15_KS15_UHMAC_Pos               21                                                      /*!< CSS_KS15: KS15_UHMAC Position           */
#define CSS_KS15_KS15_UHMAC_Msk               (0x01UL << CSS_KS15_KS15_UHMAC_Pos)                     /*!< CSS_KS15: KS15_UHMAC Mask               */
#define CSS_KS15_KS15_UKWK_Pos                22                                                      /*!< CSS_KS15: KS15_UKWK Position            */
#define CSS_KS15_KS15_UKWK_Msk                (0x01UL << CSS_KS15_KS15_UKWK_Pos)                      /*!< CSS_KS15: KS15_UKWK Mask                */
#define CSS_KS15_KS15_UKUOK_Pos               23                                                      /*!< CSS_KS15: KS15_UKUOK Position           */
#define CSS_KS15_KS15_UKUOK_Msk               (0x01UL << CSS_KS15_KS15_UKUOK_Pos)                     /*!< CSS_KS15: KS15_UKUOK Mask               */
#define CSS_KS15_KS15_UTLSPMS_Pos             24                                                      /*!< CSS_KS15: KS15_UTLSPMS Position         */
#define CSS_KS15_KS15_UTLSPMS_Msk             (0x01UL << CSS_KS15_KS15_UTLSPMS_Pos)                   /*!< CSS_KS15: KS15_UTLSPMS Mask             */
#define CSS_KS15_KS15_UTLSMS_Pos              25                                                      /*!< CSS_KS15: KS15_UTLSMS Position          */
#define CSS_KS15_KS15_UTLSMS_Msk              (0x01UL << CSS_KS15_KS15_UTLSMS_Pos)                    /*!< CSS_KS15: KS15_UTLSMS Mask              */
#define CSS_KS15_KS15_UKGSRC_Pos              26                                                      /*!< CSS_KS15: KS15_UKGSRC Position          */
#define CSS_KS15_KS15_UKGSRC_Msk              (0x01UL << CSS_KS15_KS15_UKGSRC_Pos)                    /*!< CSS_KS15: KS15_UKGSRC Mask              */
#define CSS_KS15_KS15_UHWO_Pos                27                                                      /*!< CSS_KS15: KS15_UHWO Position            */
#define CSS_KS15_KS15_UHWO_Msk                (0x01UL << CSS_KS15_KS15_UHWO_Pos)                      /*!< CSS_KS15: KS15_UHWO Mask                */
#define CSS_KS15_KS15_UWRPOK_Pos              28                                                      /*!< CSS_KS15: KS15_UWRPOK Position          */
#define CSS_KS15_KS15_UWRPOK_Msk              (0x01UL << CSS_KS15_KS15_UWRPOK_Pos)                    /*!< CSS_KS15: KS15_UWRPOK Mask              */
#define CSS_KS15_KS15_UDUK_Pos                29                                                      /*!< CSS_KS15: KS15_UDUK Position            */
#define CSS_KS15_KS15_UDUK_Msk                (0x01UL << CSS_KS15_KS15_UDUK_Pos)                      /*!< CSS_KS15: KS15_UDUK Mask                */
#define CSS_KS15_KS15_UPPROT_Pos              30                                                      /*!< CSS_KS15: KS15_UPPROT Position          */
#define CSS_KS15_KS15_UPPROT_Msk              (0x03UL << CSS_KS15_KS15_UPPROT_Pos)                    /*!< CSS_KS15: KS15_UPPROT Mask              */

/* ===============================      CSS_KS16     ============================== */
#define CSS_KS16_KS16_KSIZE_Pos               0                                                       /*!< CSS_KS16: KS16_KSIZE Position           */
#define CSS_KS16_KS16_KSIZE_Msk               (0x01UL << CSS_KS16_KS16_KSIZE_Pos)                     /*!< CSS_KS16: KS16_KSIZE Mask               */
#define CSS_KS16_KS16_RSVD0_Pos               1                                                       /*!< CSS_KS16: KS16_RSVD0 Position           */
#define CSS_KS16_KS16_RSVD0_Msk               (0x0fUL << CSS_KS16_KS16_RSVD0_Pos)                     /*!< CSS_KS16: KS16_RSVD0 Mask               */
#define CSS_KS16_KS16_KACT_Pos                5                                                       /*!< CSS_KS16: KS16_KACT Position            */
#define CSS_KS16_KS16_KACT_Msk                (0x01UL << CSS_KS16_KS16_KACT_Pos)                      /*!< CSS_KS16: KS16_KACT Mask                */
#define CSS_KS16_KS16_KBASE_Pos               6                                                       /*!< CSS_KS16: KS16_KBASE Position           */
#define CSS_KS16_KS16_KBASE_Msk               (0x01UL << CSS_KS16_KS16_KBASE_Pos)                     /*!< CSS_KS16: KS16_KBASE Mask               */
#define CSS_KS16_KS16_FGP_Pos                 7                                                       /*!< CSS_KS16: KS16_FGP Position             */
#define CSS_KS16_KS16_FGP_Msk                 (0x01UL << CSS_KS16_KS16_FGP_Pos)                       /*!< CSS_KS16: KS16_FGP Mask                 */
#define CSS_KS16_KS16_FRTN_Pos                8                                                       /*!< CSS_KS16: KS16_FRTN Position            */
#define CSS_KS16_KS16_FRTN_Msk                (0x01UL << CSS_KS16_KS16_FRTN_Pos)                      /*!< CSS_KS16: KS16_FRTN Mask                */
#define CSS_KS16_KS16_FHWO_Pos                9                                                       /*!< CSS_KS16: KS16_FHWO Position            */
#define CSS_KS16_KS16_FHWO_Msk                (0x01UL << CSS_KS16_KS16_FHWO_Pos)                      /*!< CSS_KS16: KS16_FHWO Mask                */
#define CSS_KS16_KS16_RSVD1_Pos               10                                                      /*!< CSS_KS16: KS16_RSVD1 Position           */
#define CSS_KS16_KS16_RSVD1_Msk               (0x07UL << CSS_KS16_KS16_RSVD1_Pos)                     /*!< CSS_KS16: KS16_RSVD1 Mask               */
#define CSS_KS16_KS16_UCMAC_Pos               13                                                      /*!< CSS_KS16: KS16_UCMAC Position           */
#define CSS_KS16_KS16_UCMAC_Msk               (0x01UL << CSS_KS16_KS16_UCMAC_Pos)                     /*!< CSS_KS16: KS16_UCMAC Mask               */
#define CSS_KS16_KS16_UKSK_Pos                14                                                      /*!< CSS_KS16: KS16_UKSK Position            */
#define CSS_KS16_KS16_UKSK_Msk                (0x01UL << CSS_KS16_KS16_UKSK_Pos)                      /*!< CSS_KS16: KS16_UKSK Mask                */
#define CSS_KS16_KS16_URTF_Pos                15                                                      /*!< CSS_KS16: KS16_URTF Position            */
#define CSS_KS16_KS16_URTF_Msk                (0x01UL << CSS_KS16_KS16_URTF_Pos)                      /*!< CSS_KS16: KS16_URTF Mask                */
#define CSS_KS16_KS16_UCKDF_Pos               16                                                      /*!< CSS_KS16: KS16_UCKDF Position           */
#define CSS_KS16_KS16_UCKDF_Msk               (0x01UL << CSS_KS16_KS16_UCKDF_Pos)                     /*!< CSS_KS16: KS16_UCKDF Mask               */
#define CSS_KS16_KS16_UHKDF_Pos               17                                                      /*!< CSS_KS16: KS16_UHKDF Position           */
#define CSS_KS16_KS16_UHKDF_Msk               (0x01UL << CSS_KS16_KS16_UHKDF_Pos)                     /*!< CSS_KS16: KS16_UHKDF Mask               */
#define CSS_KS16_KS16_UECSG_Pos               18                                                      /*!< CSS_KS16: KS16_UECSG Position           */
#define CSS_KS16_KS16_UECSG_Msk               (0x01UL << CSS_KS16_KS16_UECSG_Pos)                     /*!< CSS_KS16: KS16_UECSG Mask               */
#define CSS_KS16_KS16_UECDH_Pos               19                                                      /*!< CSS_KS16: KS16_UECDH Position           */
#define CSS_KS16_KS16_UECDH_Msk               (0x01UL << CSS_KS16_KS16_UECDH_Pos)                     /*!< CSS_KS16: KS16_UECDH Mask               */
#define CSS_KS16_KS16_UAES_Pos                20                                                      /*!< CSS_KS16: KS16_UAES Position            */
#define CSS_KS16_KS16_UAES_Msk                (0x01UL << CSS_KS16_KS16_UAES_Pos)                      /*!< CSS_KS16: KS16_UAES Mask                */
#define CSS_KS16_KS16_UHMAC_Pos               21                                                      /*!< CSS_KS16: KS16_UHMAC Position           */
#define CSS_KS16_KS16_UHMAC_Msk               (0x01UL << CSS_KS16_KS16_UHMAC_Pos)                     /*!< CSS_KS16: KS16_UHMAC Mask               */
#define CSS_KS16_KS16_UKWK_Pos                22                                                      /*!< CSS_KS16: KS16_UKWK Position            */
#define CSS_KS16_KS16_UKWK_Msk                (0x01UL << CSS_KS16_KS16_UKWK_Pos)                      /*!< CSS_KS16: KS16_UKWK Mask                */
#define CSS_KS16_KS16_UKUOK_Pos               23                                                      /*!< CSS_KS16: KS16_UKUOK Position           */
#define CSS_KS16_KS16_UKUOK_Msk               (0x01UL << CSS_KS16_KS16_UKUOK_Pos)                     /*!< CSS_KS16: KS16_UKUOK Mask               */
#define CSS_KS16_KS16_UTLSPMS_Pos             24                                                      /*!< CSS_KS16: KS16_UTLSPMS Position         */
#define CSS_KS16_KS16_UTLSPMS_Msk             (0x01UL << CSS_KS16_KS16_UTLSPMS_Pos)                   /*!< CSS_KS16: KS16_UTLSPMS Mask             */
#define CSS_KS16_KS16_UTLSMS_Pos              25                                                      /*!< CSS_KS16: KS16_UTLSMS Position          */
#define CSS_KS16_KS16_UTLSMS_Msk              (0x01UL << CSS_KS16_KS16_UTLSMS_Pos)                    /*!< CSS_KS16: KS16_UTLSMS Mask              */
#define CSS_KS16_KS16_UKGSRC_Pos              26                                                      /*!< CSS_KS16: KS16_UKGSRC Position          */
#define CSS_KS16_KS16_UKGSRC_Msk              (0x01UL << CSS_KS16_KS16_UKGSRC_Pos)                    /*!< CSS_KS16: KS16_UKGSRC Mask              */
#define CSS_KS16_KS16_UHWO_Pos                27                                                      /*!< CSS_KS16: KS16_UHWO Position            */
#define CSS_KS16_KS16_UHWO_Msk                (0x01UL << CSS_KS16_KS16_UHWO_Pos)                      /*!< CSS_KS16: KS16_UHWO Mask                */
#define CSS_KS16_KS16_UWRPOK_Pos              28                                                      /*!< CSS_KS16: KS16_UWRPOK Position          */
#define CSS_KS16_KS16_UWRPOK_Msk              (0x01UL << CSS_KS16_KS16_UWRPOK_Pos)                    /*!< CSS_KS16: KS16_UWRPOK Mask              */
#define CSS_KS16_KS16_UDUK_Pos                29                                                      /*!< CSS_KS16: KS16_UDUK Position            */
#define CSS_KS16_KS16_UDUK_Msk                (0x01UL << CSS_KS16_KS16_UDUK_Pos)                      /*!< CSS_KS16: KS16_UDUK Mask                */
#define CSS_KS16_KS16_UPPROT_Pos              30                                                      /*!< CSS_KS16: KS16_UPPROT Position          */
#define CSS_KS16_KS16_UPPROT_Msk              (0x03UL << CSS_KS16_KS16_UPPROT_Pos)                    /*!< CSS_KS16: KS16_UPPROT Mask              */

/* ===============================      CSS_KS17     ============================== */
#define CSS_KS17_KS17_KSIZE_Pos               0                                                       /*!< CSS_KS17: KS17_KSIZE Position           */
#define CSS_KS17_KS17_KSIZE_Msk               (0x01UL << CSS_KS17_KS17_KSIZE_Pos)                     /*!< CSS_KS17: KS17_KSIZE Mask               */
#define CSS_KS17_KS17_RSVD0_Pos               1                                                       /*!< CSS_KS17: KS17_RSVD0 Position           */
#define CSS_KS17_KS17_RSVD0_Msk               (0x0fUL << CSS_KS17_KS17_RSVD0_Pos)                     /*!< CSS_KS17: KS17_RSVD0 Mask               */
#define CSS_KS17_KS17_KACT_Pos                5                                                       /*!< CSS_KS17: KS17_KACT Position            */
#define CSS_KS17_KS17_KACT_Msk                (0x01UL << CSS_KS17_KS17_KACT_Pos)                      /*!< CSS_KS17: KS17_KACT Mask                */
#define CSS_KS17_KS17_KBASE_Pos               6                                                       /*!< CSS_KS17: KS17_KBASE Position           */
#define CSS_KS17_KS17_KBASE_Msk               (0x01UL << CSS_KS17_KS17_KBASE_Pos)                     /*!< CSS_KS17: KS17_KBASE Mask               */
#define CSS_KS17_KS17_FGP_Pos                 7                                                       /*!< CSS_KS17: KS17_FGP Position             */
#define CSS_KS17_KS17_FGP_Msk                 (0x01UL << CSS_KS17_KS17_FGP_Pos)                       /*!< CSS_KS17: KS17_FGP Mask                 */
#define CSS_KS17_KS17_FRTN_Pos                8                                                       /*!< CSS_KS17: KS17_FRTN Position            */
#define CSS_KS17_KS17_FRTN_Msk                (0x01UL << CSS_KS17_KS17_FRTN_Pos)                      /*!< CSS_KS17: KS17_FRTN Mask                */
#define CSS_KS17_KS17_FHWO_Pos                9                                                       /*!< CSS_KS17: KS17_FHWO Position            */
#define CSS_KS17_KS17_FHWO_Msk                (0x01UL << CSS_KS17_KS17_FHWO_Pos)                      /*!< CSS_KS17: KS17_FHWO Mask                */
#define CSS_KS17_KS17_RSVD1_Pos               10                                                      /*!< CSS_KS17: KS17_RSVD1 Position           */
#define CSS_KS17_KS17_RSVD1_Msk               (0x07UL << CSS_KS17_KS17_RSVD1_Pos)                     /*!< CSS_KS17: KS17_RSVD1 Mask               */
#define CSS_KS17_KS17_UCMAC_Pos               13                                                      /*!< CSS_KS17: KS17_UCMAC Position           */
#define CSS_KS17_KS17_UCMAC_Msk               (0x01UL << CSS_KS17_KS17_UCMAC_Pos)                     /*!< CSS_KS17: KS17_UCMAC Mask               */
#define CSS_KS17_KS17_UKSK_Pos                14                                                      /*!< CSS_KS17: KS17_UKSK Position            */
#define CSS_KS17_KS17_UKSK_Msk                (0x01UL << CSS_KS17_KS17_UKSK_Pos)                      /*!< CSS_KS17: KS17_UKSK Mask                */
#define CSS_KS17_KS17_URTF_Pos                15                                                      /*!< CSS_KS17: KS17_URTF Position            */
#define CSS_KS17_KS17_URTF_Msk                (0x01UL << CSS_KS17_KS17_URTF_Pos)                      /*!< CSS_KS17: KS17_URTF Mask                */
#define CSS_KS17_KS17_UCKDF_Pos               16                                                      /*!< CSS_KS17: KS17_UCKDF Position           */
#define CSS_KS17_KS17_UCKDF_Msk               (0x01UL << CSS_KS17_KS17_UCKDF_Pos)                     /*!< CSS_KS17: KS17_UCKDF Mask               */
#define CSS_KS17_KS17_UHKDF_Pos               17                                                      /*!< CSS_KS17: KS17_UHKDF Position           */
#define CSS_KS17_KS17_UHKDF_Msk               (0x01UL << CSS_KS17_KS17_UHKDF_Pos)                     /*!< CSS_KS17: KS17_UHKDF Mask               */
#define CSS_KS17_KS17_UECSG_Pos               18                                                      /*!< CSS_KS17: KS17_UECSG Position           */
#define CSS_KS17_KS17_UECSG_Msk               (0x01UL << CSS_KS17_KS17_UECSG_Pos)                     /*!< CSS_KS17: KS17_UECSG Mask               */
#define CSS_KS17_KS17_UECDH_Pos               19                                                      /*!< CSS_KS17: KS17_UECDH Position           */
#define CSS_KS17_KS17_UECDH_Msk               (0x01UL << CSS_KS17_KS17_UECDH_Pos)                     /*!< CSS_KS17: KS17_UECDH Mask               */
#define CSS_KS17_KS17_UAES_Pos                20                                                      /*!< CSS_KS17: KS17_UAES Position            */
#define CSS_KS17_KS17_UAES_Msk                (0x01UL << CSS_KS17_KS17_UAES_Pos)                      /*!< CSS_KS17: KS17_UAES Mask                */
#define CSS_KS17_KS17_UHMAC_Pos               21                                                      /*!< CSS_KS17: KS17_UHMAC Position           */
#define CSS_KS17_KS17_UHMAC_Msk               (0x01UL << CSS_KS17_KS17_UHMAC_Pos)                     /*!< CSS_KS17: KS17_UHMAC Mask               */
#define CSS_KS17_KS17_UKWK_Pos                22                                                      /*!< CSS_KS17: KS17_UKWK Position            */
#define CSS_KS17_KS17_UKWK_Msk                (0x01UL << CSS_KS17_KS17_UKWK_Pos)                      /*!< CSS_KS17: KS17_UKWK Mask                */
#define CSS_KS17_KS17_UKUOK_Pos               23                                                      /*!< CSS_KS17: KS17_UKUOK Position           */
#define CSS_KS17_KS17_UKUOK_Msk               (0x01UL << CSS_KS17_KS17_UKUOK_Pos)                     /*!< CSS_KS17: KS17_UKUOK Mask               */
#define CSS_KS17_KS17_UTLSPMS_Pos             24                                                      /*!< CSS_KS17: KS17_UTLSPMS Position         */
#define CSS_KS17_KS17_UTLSPMS_Msk             (0x01UL << CSS_KS17_KS17_UTLSPMS_Pos)                   /*!< CSS_KS17: KS17_UTLSPMS Mask             */
#define CSS_KS17_KS17_UTLSMS_Pos              25                                                      /*!< CSS_KS17: KS17_UTLSMS Position          */
#define CSS_KS17_KS17_UTLSMS_Msk              (0x01UL << CSS_KS17_KS17_UTLSMS_Pos)                    /*!< CSS_KS17: KS17_UTLSMS Mask              */
#define CSS_KS17_KS17_UKGSRC_Pos              26                                                      /*!< CSS_KS17: KS17_UKGSRC Position          */
#define CSS_KS17_KS17_UKGSRC_Msk              (0x01UL << CSS_KS17_KS17_UKGSRC_Pos)                    /*!< CSS_KS17: KS17_UKGSRC Mask              */
#define CSS_KS17_KS17_UHWO_Pos                27                                                      /*!< CSS_KS17: KS17_UHWO Position            */
#define CSS_KS17_KS17_UHWO_Msk                (0x01UL << CSS_KS17_KS17_UHWO_Pos)                      /*!< CSS_KS17: KS17_UHWO Mask                */
#define CSS_KS17_KS17_UWRPOK_Pos              28                                                      /*!< CSS_KS17: KS17_UWRPOK Position          */
#define CSS_KS17_KS17_UWRPOK_Msk              (0x01UL << CSS_KS17_KS17_UWRPOK_Pos)                    /*!< CSS_KS17: KS17_UWRPOK Mask              */
#define CSS_KS17_KS17_UDUK_Pos                29                                                      /*!< CSS_KS17: KS17_UDUK Position            */
#define CSS_KS17_KS17_UDUK_Msk                (0x01UL << CSS_KS17_KS17_UDUK_Pos)                      /*!< CSS_KS17: KS17_UDUK Mask                */
#define CSS_KS17_KS17_UPPROT_Pos              30                                                      /*!< CSS_KS17: KS17_UPPROT Position          */
#define CSS_KS17_KS17_UPPROT_Msk              (0x03UL << CSS_KS17_KS17_UPPROT_Pos)                    /*!< CSS_KS17: KS17_UPPROT Mask              */

/* ===============================      CSS_KS18     ============================== */
#define CSS_KS18_KS18_KSIZE_Pos               0                                                       /*!< CSS_KS18: KS18_KSIZE Position           */
#define CSS_KS18_KS18_KSIZE_Msk               (0x01UL << CSS_KS18_KS18_KSIZE_Pos)                     /*!< CSS_KS18: KS18_KSIZE Mask               */
#define CSS_KS18_KS18_RSVD0_Pos               1                                                       /*!< CSS_KS18: KS18_RSVD0 Position           */
#define CSS_KS18_KS18_RSVD0_Msk               (0x0fUL << CSS_KS18_KS18_RSVD0_Pos)                     /*!< CSS_KS18: KS18_RSVD0 Mask               */
#define CSS_KS18_KS18_KACT_Pos                5                                                       /*!< CSS_KS18: KS18_KACT Position            */
#define CSS_KS18_KS18_KACT_Msk                (0x01UL << CSS_KS18_KS18_KACT_Pos)                      /*!< CSS_KS18: KS18_KACT Mask                */
#define CSS_KS18_KS18_KBASE_Pos               6                                                       /*!< CSS_KS18: KS18_KBASE Position           */
#define CSS_KS18_KS18_KBASE_Msk               (0x01UL << CSS_KS18_KS18_KBASE_Pos)                     /*!< CSS_KS18: KS18_KBASE Mask               */
#define CSS_KS18_KS18_FGP_Pos                 7                                                       /*!< CSS_KS18: KS18_FGP Position             */
#define CSS_KS18_KS18_FGP_Msk                 (0x01UL << CSS_KS18_KS18_FGP_Pos)                       /*!< CSS_KS18: KS18_FGP Mask                 */
#define CSS_KS18_KS18_FRTN_Pos                8                                                       /*!< CSS_KS18: KS18_FRTN Position            */
#define CSS_KS18_KS18_FRTN_Msk                (0x01UL << CSS_KS18_KS18_FRTN_Pos)                      /*!< CSS_KS18: KS18_FRTN Mask                */
#define CSS_KS18_KS18_FHWO_Pos                9                                                       /*!< CSS_KS18: KS18_FHWO Position            */
#define CSS_KS18_KS18_FHWO_Msk                (0x01UL << CSS_KS18_KS18_FHWO_Pos)                      /*!< CSS_KS18: KS18_FHWO Mask                */
#define CSS_KS18_KS18_RSVD1_Pos               10                                                      /*!< CSS_KS18: KS18_RSVD1 Position           */
#define CSS_KS18_KS18_RSVD1_Msk               (0x07UL << CSS_KS18_KS18_RSVD1_Pos)                     /*!< CSS_KS18: KS18_RSVD1 Mask               */
#define CSS_KS18_KS18_UCMAC_Pos               13                                                      /*!< CSS_KS18: KS18_UCMAC Position           */
#define CSS_KS18_KS18_UCMAC_Msk               (0x01UL << CSS_KS18_KS18_UCMAC_Pos)                     /*!< CSS_KS18: KS18_UCMAC Mask               */
#define CSS_KS18_KS18_UKSK_Pos                14                                                      /*!< CSS_KS18: KS18_UKSK Position            */
#define CSS_KS18_KS18_UKSK_Msk                (0x01UL << CSS_KS18_KS18_UKSK_Pos)                      /*!< CSS_KS18: KS18_UKSK Mask                */
#define CSS_KS18_KS18_URTF_Pos                15                                                      /*!< CSS_KS18: KS18_URTF Position            */
#define CSS_KS18_KS18_URTF_Msk                (0x01UL << CSS_KS18_KS18_URTF_Pos)                      /*!< CSS_KS18: KS18_URTF Mask                */
#define CSS_KS18_KS18_UCKDF_Pos               16                                                      /*!< CSS_KS18: KS18_UCKDF Position           */
#define CSS_KS18_KS18_UCKDF_Msk               (0x01UL << CSS_KS18_KS18_UCKDF_Pos)                     /*!< CSS_KS18: KS18_UCKDF Mask               */
#define CSS_KS18_KS18_UHKDF_Pos               17                                                      /*!< CSS_KS18: KS18_UHKDF Position           */
#define CSS_KS18_KS18_UHKDF_Msk               (0x01UL << CSS_KS18_KS18_UHKDF_Pos)                     /*!< CSS_KS18: KS18_UHKDF Mask               */
#define CSS_KS18_KS18_UECSG_Pos               18                                                      /*!< CSS_KS18: KS18_UECSG Position           */
#define CSS_KS18_KS18_UECSG_Msk               (0x01UL << CSS_KS18_KS18_UECSG_Pos)                     /*!< CSS_KS18: KS18_UECSG Mask               */
#define CSS_KS18_KS18_UECDH_Pos               19                                                      /*!< CSS_KS18: KS18_UECDH Position           */
#define CSS_KS18_KS18_UECDH_Msk               (0x01UL << CSS_KS18_KS18_UECDH_Pos)                     /*!< CSS_KS18: KS18_UECDH Mask               */
#define CSS_KS18_KS18_UAES_Pos                20                                                      /*!< CSS_KS18: KS18_UAES Position            */
#define CSS_KS18_KS18_UAES_Msk                (0x01UL << CSS_KS18_KS18_UAES_Pos)                      /*!< CSS_KS18: KS18_UAES Mask                */
#define CSS_KS18_KS18_UHMAC_Pos               21                                                      /*!< CSS_KS18: KS18_UHMAC Position           */
#define CSS_KS18_KS18_UHMAC_Msk               (0x01UL << CSS_KS18_KS18_UHMAC_Pos)                     /*!< CSS_KS18: KS18_UHMAC Mask               */
#define CSS_KS18_KS18_UKWK_Pos                22                                                      /*!< CSS_KS18: KS18_UKWK Position            */
#define CSS_KS18_KS18_UKWK_Msk                (0x01UL << CSS_KS18_KS18_UKWK_Pos)                      /*!< CSS_KS18: KS18_UKWK Mask                */
#define CSS_KS18_KS18_UKUOK_Pos               23                                                      /*!< CSS_KS18: KS18_UKUOK Position           */
#define CSS_KS18_KS18_UKUOK_Msk               (0x01UL << CSS_KS18_KS18_UKUOK_Pos)                     /*!< CSS_KS18: KS18_UKUOK Mask               */
#define CSS_KS18_KS18_UTLSPMS_Pos             24                                                      /*!< CSS_KS18: KS18_UTLSPMS Position         */
#define CSS_KS18_KS18_UTLSPMS_Msk             (0x01UL << CSS_KS18_KS18_UTLSPMS_Pos)                   /*!< CSS_KS18: KS18_UTLSPMS Mask             */
#define CSS_KS18_KS18_UTLSMS_Pos              25                                                      /*!< CSS_KS18: KS18_UTLSMS Position          */
#define CSS_KS18_KS18_UTLSMS_Msk              (0x01UL << CSS_KS18_KS18_UTLSMS_Pos)                    /*!< CSS_KS18: KS18_UTLSMS Mask              */
#define CSS_KS18_KS18_UKGSRC_Pos              26                                                      /*!< CSS_KS18: KS18_UKGSRC Position          */
#define CSS_KS18_KS18_UKGSRC_Msk              (0x01UL << CSS_KS18_KS18_UKGSRC_Pos)                    /*!< CSS_KS18: KS18_UKGSRC Mask              */
#define CSS_KS18_KS18_UHWO_Pos                27                                                      /*!< CSS_KS18: KS18_UHWO Position            */
#define CSS_KS18_KS18_UHWO_Msk                (0x01UL << CSS_KS18_KS18_UHWO_Pos)                      /*!< CSS_KS18: KS18_UHWO Mask                */
#define CSS_KS18_KS18_UWRPOK_Pos              28                                                      /*!< CSS_KS18: KS18_UWRPOK Position          */
#define CSS_KS18_KS18_UWRPOK_Msk              (0x01UL << CSS_KS18_KS18_UWRPOK_Pos)                    /*!< CSS_KS18: KS18_UWRPOK Mask              */
#define CSS_KS18_KS18_UDUK_Pos                29                                                      /*!< CSS_KS18: KS18_UDUK Position            */
#define CSS_KS18_KS18_UDUK_Msk                (0x01UL << CSS_KS18_KS18_UDUK_Pos)                      /*!< CSS_KS18: KS18_UDUK Mask                */
#define CSS_KS18_KS18_UPPROT_Pos              30                                                      /*!< CSS_KS18: KS18_UPPROT Position          */
#define CSS_KS18_KS18_UPPROT_Msk              (0x03UL << CSS_KS18_KS18_UPPROT_Pos)                    /*!< CSS_KS18: KS18_UPPROT Mask              */

/* ===============================      CSS_KS19     ============================== */
#define CSS_KS19_KS19_KSIZE_Pos               0                                                       /*!< CSS_KS19: KS19_KSIZE Position           */
#define CSS_KS19_KS19_KSIZE_Msk               (0x01UL << CSS_KS19_KS19_KSIZE_Pos)                     /*!< CSS_KS19: KS19_KSIZE Mask               */
#define CSS_KS19_KS19_RSVD0_Pos               1                                                       /*!< CSS_KS19: KS19_RSVD0 Position           */
#define CSS_KS19_KS19_RSVD0_Msk               (0x0fUL << CSS_KS19_KS19_RSVD0_Pos)                     /*!< CSS_KS19: KS19_RSVD0 Mask               */
#define CSS_KS19_KS19_KACT_Pos                5                                                       /*!< CSS_KS19: KS19_KACT Position            */
#define CSS_KS19_KS19_KACT_Msk                (0x01UL << CSS_KS19_KS19_KACT_Pos)                      /*!< CSS_KS19: KS19_KACT Mask                */
#define CSS_KS19_KS19_KBASE_Pos               6                                                       /*!< CSS_KS19: KS19_KBASE Position           */
#define CSS_KS19_KS19_KBASE_Msk               (0x01UL << CSS_KS19_KS19_KBASE_Pos)                     /*!< CSS_KS19: KS19_KBASE Mask               */
#define CSS_KS19_KS19_FGP_Pos                 7                                                       /*!< CSS_KS19: KS19_FGP Position             */
#define CSS_KS19_KS19_FGP_Msk                 (0x01UL << CSS_KS19_KS19_FGP_Pos)                       /*!< CSS_KS19: KS19_FGP Mask                 */
#define CSS_KS19_KS19_FRTN_Pos                8                                                       /*!< CSS_KS19: KS19_FRTN Position            */
#define CSS_KS19_KS19_FRTN_Msk                (0x01UL << CSS_KS19_KS19_FRTN_Pos)                      /*!< CSS_KS19: KS19_FRTN Mask                */
#define CSS_KS19_KS19_FHWO_Pos                9                                                       /*!< CSS_KS19: KS19_FHWO Position            */
#define CSS_KS19_KS19_FHWO_Msk                (0x01UL << CSS_KS19_KS19_FHWO_Pos)                      /*!< CSS_KS19: KS19_FHWO Mask                */
#define CSS_KS19_KS19_RSVD1_Pos               10                                                      /*!< CSS_KS19: KS19_RSVD1 Position           */
#define CSS_KS19_KS19_RSVD1_Msk               (0x07UL << CSS_KS19_KS19_RSVD1_Pos)                     /*!< CSS_KS19: KS19_RSVD1 Mask               */
#define CSS_KS19_KS19_UCMAC_Pos               13                                                      /*!< CSS_KS19: KS19_UCMAC Position           */
#define CSS_KS19_KS19_UCMAC_Msk               (0x01UL << CSS_KS19_KS19_UCMAC_Pos)                     /*!< CSS_KS19: KS19_UCMAC Mask               */
#define CSS_KS19_KS19_UKSK_Pos                14                                                      /*!< CSS_KS19: KS19_UKSK Position            */
#define CSS_KS19_KS19_UKSK_Msk                (0x01UL << CSS_KS19_KS19_UKSK_Pos)                      /*!< CSS_KS19: KS19_UKSK Mask                */
#define CSS_KS19_KS19_URTF_Pos                15                                                      /*!< CSS_KS19: KS19_URTF Position            */
#define CSS_KS19_KS19_URTF_Msk                (0x01UL << CSS_KS19_KS19_URTF_Pos)                      /*!< CSS_KS19: KS19_URTF Mask                */
#define CSS_KS19_KS19_UCKDF_Pos               16                                                      /*!< CSS_KS19: KS19_UCKDF Position           */
#define CSS_KS19_KS19_UCKDF_Msk               (0x01UL << CSS_KS19_KS19_UCKDF_Pos)                     /*!< CSS_KS19: KS19_UCKDF Mask               */
#define CSS_KS19_KS19_UHKDF_Pos               17                                                      /*!< CSS_KS19: KS19_UHKDF Position           */
#define CSS_KS19_KS19_UHKDF_Msk               (0x01UL << CSS_KS19_KS19_UHKDF_Pos)                     /*!< CSS_KS19: KS19_UHKDF Mask               */
#define CSS_KS19_KS19_UECSG_Pos               18                                                      /*!< CSS_KS19: KS19_UECSG Position           */
#define CSS_KS19_KS19_UECSG_Msk               (0x01UL << CSS_KS19_KS19_UECSG_Pos)                     /*!< CSS_KS19: KS19_UECSG Mask               */
#define CSS_KS19_KS19_UECDH_Pos               19                                                      /*!< CSS_KS19: KS19_UECDH Position           */
#define CSS_KS19_KS19_UECDH_Msk               (0x01UL << CSS_KS19_KS19_UECDH_Pos)                     /*!< CSS_KS19: KS19_UECDH Mask               */
#define CSS_KS19_KS19_UAES_Pos                20                                                      /*!< CSS_KS19: KS19_UAES Position            */
#define CSS_KS19_KS19_UAES_Msk                (0x01UL << CSS_KS19_KS19_UAES_Pos)                      /*!< CSS_KS19: KS19_UAES Mask                */
#define CSS_KS19_KS19_UHMAC_Pos               21                                                      /*!< CSS_KS19: KS19_UHMAC Position           */
#define CSS_KS19_KS19_UHMAC_Msk               (0x01UL << CSS_KS19_KS19_UHMAC_Pos)                     /*!< CSS_KS19: KS19_UHMAC Mask               */
#define CSS_KS19_KS19_UKWK_Pos                22                                                      /*!< CSS_KS19: KS19_UKWK Position            */
#define CSS_KS19_KS19_UKWK_Msk                (0x01UL << CSS_KS19_KS19_UKWK_Pos)                      /*!< CSS_KS19: KS19_UKWK Mask                */
#define CSS_KS19_KS19_UKUOK_Pos               23                                                      /*!< CSS_KS19: KS19_UKUOK Position           */
#define CSS_KS19_KS19_UKUOK_Msk               (0x01UL << CSS_KS19_KS19_UKUOK_Pos)                     /*!< CSS_KS19: KS19_UKUOK Mask               */
#define CSS_KS19_KS19_UTLSPMS_Pos             24                                                      /*!< CSS_KS19: KS19_UTLSPMS Position         */
#define CSS_KS19_KS19_UTLSPMS_Msk             (0x01UL << CSS_KS19_KS19_UTLSPMS_Pos)                   /*!< CSS_KS19: KS19_UTLSPMS Mask             */
#define CSS_KS19_KS19_UTLSMS_Pos              25                                                      /*!< CSS_KS19: KS19_UTLSMS Position          */
#define CSS_KS19_KS19_UTLSMS_Msk              (0x01UL << CSS_KS19_KS19_UTLSMS_Pos)                    /*!< CSS_KS19: KS19_UTLSMS Mask              */
#define CSS_KS19_KS19_UKGSRC_Pos              26                                                      /*!< CSS_KS19: KS19_UKGSRC Position          */
#define CSS_KS19_KS19_UKGSRC_Msk              (0x01UL << CSS_KS19_KS19_UKGSRC_Pos)                    /*!< CSS_KS19: KS19_UKGSRC Mask              */
#define CSS_KS19_KS19_UHWO_Pos                27                                                      /*!< CSS_KS19: KS19_UHWO Position            */
#define CSS_KS19_KS19_UHWO_Msk                (0x01UL << CSS_KS19_KS19_UHWO_Pos)                      /*!< CSS_KS19: KS19_UHWO Mask                */
#define CSS_KS19_KS19_UWRPOK_Pos              28                                                      /*!< CSS_KS19: KS19_UWRPOK Position          */
#define CSS_KS19_KS19_UWRPOK_Msk              (0x01UL << CSS_KS19_KS19_UWRPOK_Pos)                    /*!< CSS_KS19: KS19_UWRPOK Mask              */
#define CSS_KS19_KS19_UDUK_Pos                29                                                      /*!< CSS_KS19: KS19_UDUK Position            */
#define CSS_KS19_KS19_UDUK_Msk                (0x01UL << CSS_KS19_KS19_UDUK_Pos)                      /*!< CSS_KS19: KS19_UDUK Mask                */
#define CSS_KS19_KS19_UPPROT_Pos              30                                                      /*!< CSS_KS19: KS19_UPPROT Position          */
#define CSS_KS19_KS19_UPPROT_Msk              (0x03UL << CSS_KS19_KS19_UPPROT_Pos)                    /*!< CSS_KS19: KS19_UPPROT Mask              */

/* ===============================   CSS_BOOT_ADDR   ============================== */
#define CSS_BOOT_ADDR_BOOT_ADDR_Pos           0                                                       /*!< CSS_BOOT_ADDR: BOOT_ADDR Position       */
#define CSS_BOOT_ADDR_BOOT_ADDR_Msk           (0xffffffffUL << CSS_BOOT_ADDR_BOOT_ADDR_Pos)           /*!< CSS_BOOT_ADDR: BOOT_ADDR Mask           */

/* ===============================    CSS_DBG_CFG    ============================== */
#define CSS_DBG_CFG_DBG_CFG0_Pos              0                                                       /*!< CSS_DBG_CFG: DBG_CFG0 Position          */
#define CSS_DBG_CFG_DBG_CFG0_Msk              (0x07UL << CSS_DBG_CFG_DBG_CFG0_Pos)                    /*!< CSS_DBG_CFG: DBG_CFG0 Mask              */
#define CSS_DBG_CFG_DBG_CFG1_Pos              3                                                       /*!< CSS_DBG_CFG: DBG_CFG1 Position          */
#define CSS_DBG_CFG_DBG_CFG1_Msk              (0x07UL << CSS_DBG_CFG_DBG_CFG1_Pos)                    /*!< CSS_DBG_CFG: DBG_CFG1 Mask              */
#define CSS_DBG_CFG_DBG_CFG_RFU_Pos           6                                                       /*!< CSS_DBG_CFG: DBG_CFG_RFU Position       */
#define CSS_DBG_CFG_DBG_CFG_RFU_Msk           (0x03ffffffUL << CSS_DBG_CFG_DBG_CFG_RFU_Pos)           /*!< CSS_DBG_CFG: DBG_CFG_RFU Mask           */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

//#define IP_CSS_BASE                     0x40022000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

//#define IP_CSS                          ((ip_css_Type             *) IP_CSS_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group ip_css */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* ip_css_H */
