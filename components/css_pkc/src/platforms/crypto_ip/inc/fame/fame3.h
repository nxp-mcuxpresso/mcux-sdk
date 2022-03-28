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
 * @file     CoSimPKC.h
 *
 * @brief    CMSIS  Peripheral Access Layer Header File for CoSimPKC.
 *
 * @version  $Revision: 25425 $
 * @date     26. November 2019
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

/** @addtogroup CoSimPKC
  * @{
  */

#ifndef CoSimPKC_H
#define CoSimPKC_H

#ifdef __cplusplus
extern "C" {
#endif


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
/* ================                       PKC                      ================ */
/* ================================================================================ */


/**
  * @brief SFRs of block PKC (PKC)
  */

typedef struct {                                    /*!< PKC Structure                                                         */

  union {
    __IM  uint32_t  STATUS;                          /*!< Status register                                                       */

    struct {
      __IM  uint32_t  ACTIV      :  1;              /*!< PKC active: ACTIV=1 signals that a calculation is in progress or  
                                                         about to start. At the end of a calculation ACTIV is              
                                                         automatically reset to logic 0 in case no further GO bit is set.  
                                                         If the next PKC operation has been started by setting a GO bit    
                                                         during a calculation, ACTIV remains high. ACTIV is always '1' in  
                                                         case PKC_STATUS.GOANY is set. ACTIV is always '0' in case         
                                                         PKC_CTRL_RESET is set.; While ACTIV is '1' the PKC is active also 
                                                         in using the PKC RAM. Concurrent accesses to PKC RAM via the CPU  
                                                         is still possible, but may reduce the performance of the PKC      
                                                         calculation. Write accesses to the operand and result area        
                                                         defined by the PKC pointer and length registers is prohibited     
                                                         during a running calculation and may result in wrong calcuation   
                                                         results.                                                              */
      __IM  uint32_t  CARRY      :  1;              /*!< Carry overflow flag: CARRY is set by the PKC at the end of a      
                                                         calculation in case; - an addition or multiplication with         
                                                         addition operation has been executed and an overflow in the most  
                                                         significant bit has occured.; - a subtraction or multiplication   
                                                         with subtraction operation has been executed with negative result 
                                                         in twos complement notation.; - a shift or rotate operation has   
                                                         been executed (most/least significant shifted/rotated bit is      
                                                         stored in CARRY flag).; - a LSB0s or MSB0s operation has been     
                                                         executed (CARRY indicates zero least/most-significant zero        
                                                         bits).; - a compare operation habe been executed with Z&gt;Y.;    
                                                         CARRY is updated for each PKC calculation mode, except for MUL1   
                                                         (opcode 0x20) and MUL1_GF2 (opcode 0x24). This holds also for     
                                                         operation modes where CARRY is always zero, e.g. logical          
                                                         operations (AND, OR, ...).; If PKC is in reset                    
                                                         (PKC_CTRL.RESET=1), CARRY is set to logic 0 (default).                */
      __IM  uint32_t  ZERO       :  1;              /*!< Zero result flag: ZERO is set by the PKC at the end of a          
                                                         calculation in case the result of the calculation is equal zero.  
                                                         ZERO is updated for each PKC calculation mode, except for MUL1    
                                                         (opcode 0x20) and MUL1_GF2 (opcode 0x24).; NOTE: A set ZERO flag  
                                                         only indicates that the result written to PKC RAM is zero, but    
                                                         does not imply that there is no overflow (i.e., CARRY flag set).; 
                                                         If PKC is in reset (PKC_CTRL.RESET=1), ZERO is set to logic 0     
                                                         (default).                                                            */
      __IM  uint32_t  GOANY      :  1;              /*!< Combined GO status flag: GOANY is set in case either              
                                                         PKC_CTRL.GOD1, GOD2, GOM1, GOM2 or GOU is set. The 1-to-0         
                                                         transition of GOANY indicates that a calculation has been started 
                                                         and that a new GO bit can be set. If GOANY is cleared also all    
                                                         PKC_STATUS.LOCKED bits are cleared to indicate that the parameter 
                                                         set can be updated. GOANY is always '0' in case PKC_CTRL.RESET is 
                                                         set.                                                                  */
            uint32_t             :  1;              /*!< reserved                                                              */
      __IM  uint32_t  LOCKED     :  2;              /*!< Parameter set locked: Indicates if parameter set is locked due to 
                                                         a pending calculation start or can be overwritten.; x1b-          
                                                         parameter set 1 is locked; 1xb- parameter set 2 is locked;        
                                                         LOCKED[0] is set in case a PKC calculation is started with        
                                                         parameter set 1 via PKC_CTRL.GOD1 or PKC_CTRL.GOM1.; In case one  
                                                         of the parameter set 1 SFRs PKC_MODE1, PKC_XYPTR1, PKC_ZRPTR1,    
                                                         PKC_LEN1 is updated while LOCKED[0] is set a PKC security alarm   
                                                         will be triggered (PKC_ACCESS_ERR.CTRL is set).; LOCKED[1] is set 
                                                         in case a PKC calculation is started with parameter set 2 via     
                                                         PKC_CTRL.GOD2 or PKC_CTRL.GOM2.; In case one of the parameter set 
                                                         2 SFRs PKC_MODE2, PKC_XYPTR2, PKC_ZRPTR2, PKC_LEN2 is updated     
                                                         while LOCKED[1] is set a PKC security alarm will be triggered     
                                                         (PKC_ACCESS_ERR.CTRL is set).; LOCKED[1:0] is not set for a       
                                                         universal pointer fetch (layer2) PKC calculation started via      
                                                         PKC_CTRL.GOU. All parameter set SFRs can be updated during a      
                                                         universal pointer fetch operation, except PKC_LEN1 and PKC_LEN2.  
                                                         Updating PKC_LEN1 or PKC_LEN2 during a layer2 calculation         
                                                         indicated by PKC_STATUS.GOANY will trigger a PKC security alarm   
                                                         (PKC_ACCESS_ERR.CTRL is set).; LOCKED[1:0] is cleared with the    
                                                         start of the calculation in parallel with the 1-to-0 transition   
                                                         of PKC_STATUS.GOANY and in case PKC_CTRL.RESET is set.                */
            uint32_t             : 25;              /*!< reserved                                                              */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CTRL;                            /*!< Control register                                                      */

    struct {
      __IOM uint32_t  RESET      :  1;              /*!< PKC reset control bit: RESET=1 enforces the PKC's reset state     
                                                         during which a calculation cannot be started and by which any     
                                                         ongoing calculation process is stopped. RESET can be set/cleared  
                                                         by the CPU in order to switch between PKC reset and calculation   
                                                         enable. RESET=1 is the default state after a chip reset.; RESET=1 
                                                         disables PKC activity and accordingly also provides its           
                                                         power-saving state. When PKC reset is released (RESET=0) and idle 
                                                         operation is activiated (PKC_CFG.IDLEOP=1) the power consumption  
                                                         is increased even before a calculation is started by setting a GO 
                                                         bit.; When RESET is set to '1' the read-only status flags         
                                                         PKC_STATUS.CARRY and PKC_STATUS.ZERO are cleared. If required     
                                                         these flags have to be evaluated before RESET is set. The status  
                                                         bits PKC_STATUS.GOANY and PKC_STATUS.LOCKED are reset as well in  
                                                         case RESET is set. RESET does not have an impact on the content   
                                                         of any other PKC SFRs. The parameter set and universal pointer    
                                                         SFRs can be read and written also while RESET is set.; Software   
                                                         must clear bit RESET to enable the PKC before it can start a      
                                                         calculation via one of the GO bits in PKC_CTRL. Any attempt to    
                                                         start a calculation via a GO bit while RESET=1 will trigger a PKC 
                                                         security alarm (PKC_ACCESS_ERR.CTRL is set).; The PKC             
                                                         configuration setting in PKC_CFG can only be updated while        
                                                         RESET=1. A write access to PKC_CFG while RESET=0 will trigger a   
                                                         PKC security alarm (PKC_ACCESS_ERR.CTRL is set).                      */
      __IOM uint32_t  STOP       :  1;              /*!< Freeze PKC calculation: STOP=1 freezes all PKC activity incl. RAM 
                                                         accesses and reduces the PKC power consumption to its minimum.    
                                                         The difference compared to the reset of the PKC is that a stopped 
                                                         calculation can be continued when STOP is released (reset to '0') 
                                                         again. The status flags are not affected by the STOP control bit.     */
      __IOM uint32_t  GOD1       :  1;              /*!< Control bit to start direct operation using parameter set 1: If   
                                                         GOD1 is set PKC will start a direct / layer0 operation using      
                                                         parameter set 1 (PKC_MODE1, PKC_XYPTR1, PKC_ZRPTR1, PKC_LEN1).;   
                                                         Section 'Operating the PKC via the Parameter Set interface (layer 
                                                         0)' describes how to start layer0 operations.; GOD1 is a          
                                                         write-only bit and always read '0'. It is only allowed to set     
                                                         GOD1 when PKC_STATUS.GOANY and PKC_CTRL.RESET are cleared.        
                                                         Otherwise a security alarm is triggered (PKC_ACCESS_ERR.CTRL is   
                                                         set). An alarm is also triggered in case more than one GO bit is  
                                                         set for the PKC_CTRL SFR write access (PKC_ACCESS_ERR.CTRL is     
                                                         set).                                                                 */
      __IOM uint32_t  GOD2       :  1;              /*!< Control bit to start direct operation using parameter set 2: If   
                                                         GOD2 is set PKC will start a direct / layer0 operation using      
                                                         parameter set 2 (PKC_MODE2, PKC_XYPTR2, PKC_ZRPTR2, PKC_LEN2).;   
                                                         Section 'Operating the PKC via the Parameter Set interface (layer 
                                                         0)' describes how to start layer0 operations.; GOD2 is a          
                                                         write-only bit and always read '0'. It is only allowed to set     
                                                         GOD2 when PKC_STATUS.GOANY and PKC_CTRL.RESET are cleared.        
                                                         Otherwise a security alarm is triggered(PKC_ACCESS_ERR.CTRL is    
                                                         set). An alarm is also triggered in case more than one GO bit is  
                                                         set for the PKC_CTRL SFR write access (PKC_ACCESS_ERR.CTRL is     
                                                         set).                                                                 */
      __IOM uint32_t  GOM1       :  1;              /*!< Control bit to start MC pattern using parameter set 1: If GOM1 is 
                                                         set PKC will start a MC pattern / layer1 operation using          
                                                         parameter set 1 (PKC_MODE1, PKC_XYPTR1, PKC_ZRPTR1, PKC_LEN1).;   
                                                         Section 'Operating the PKC via the Micro Code interface (layer    
                                                         1)' describes how to start layer1 operations.; GOM1 is a          
                                                         write-only bit and always read '0'. It is only allowed to set     
                                                         GOM1 when PKC_STATUS.GOANY and PKC_CTRL.RESET are cleared.        
                                                         Otherwise a security alarm is triggered (PKC_ACCESS_ERR.CTRL is   
                                                         set). An alarm is also triggered in case more than one GO bit is  
                                                         set for the PKC_CTRL SFR write access (PKC_ACCESS_ERR.CTRL is     
                                                         set).                                                                 */
      __IOM uint32_t  GOM2       :  1;              /*!< Control bit to start MC pattern using parameter set 2: If GOM2 is 
                                                         set PKC will start a MC pattern / layer1 operation using          
                                                         parameter set 2 (PKC_MODE2, PKC_XYPTR2, PKC_ZRPTR2, PKC_LEN2).;   
                                                         Section 'Operating the PKC via the Micro Code interface (layer    
                                                         1)' describes how to start layer1 operations.; GOM2 is a          
                                                         write-only bit and always read '0'. It is only allowed to set     
                                                         GOM2 when PKC_STATUS.GOANY and PKC_CTRL.RESET are cleared.        
                                                         Otherwise a security alarm is triggered (PKC_ACCESS_ERR.CTRL is   
                                                         set). An alarm is also triggered in case more than one GO bit is  
                                                         set for the PKC_CTRL SFR write access (PKC_ACCESS_ERR.CTRL is     
                                                         set).                                                                 */
      __IOM uint32_t  GOU        :  1;              /*!< Control bit to start pipe operation: If GOU is set PKC will start 
                                                         the pipe / layer2 operation (parameter fetch &amp; calculation)   
                                                         described in section 'PKC Universal Pointer Fetch Operation'.;    
                                                         Section 'Operating the PKC via the Universal Pointer Fetch Unit   
                                                         (layer 2)' describes how to start layer2 operations.; GOU is a    
                                                         write-only bit and always read '0'. It is only allowed to set GOU 
                                                         when PKC_STATUS.GOANY and PKC_CTRL.RESET are cleared,             
                                                         PKC_ULEN&gt;0 and PKC_UPTR(T) point to valid addresses (defined   
                                                         by MMU). Otherwise a security alarm is triggered                  
                                                         (PKC_ACCESS_ERR.CTRL or PKC_ACCESS_ERR.AHB is set). An alarm is   
                                                         also triggered in case more than one GO bit is set for the        
                                                         PKC_CTRL SFR write access (PKC_ACCESS_ERR.CTRL is set).               */
      __IOM uint32_t  GF2CONV    :  1;              /*!< Convert to GF2 calculation modes: If GF2CONV is set operations    
                                                         are mapped to their GF(2) equivalent operation modes.; GF2CONV    
                                                         influences all PKC operation modes layer0/1/2.; GF2CONV can be    
                                                         updated at any point in time, even during a running calculation.  
                                                         However the change is only applied when a new calculation is      
                                                         started via PKC_CTRL.GO*.                                             */
      __IOM uint32_t  CLRCACHE   :  1;              /*!< Clear universal pointer cache: Invalidates the cache such that    
                                                         all previously fetched parameters are withdrawn and have to be    
                                                         fetched again via DMA accesses.; CLRCACHE can be triggered at any 
                                                         point in time, even during a running universal pointer fetch      
                                                         calculation. CLRCACHE is write-only and always read '0'. CLRCACHE 
                                                         has no impact in case the cache is disabled via                   
                                                         PKC_CTRL.CACHE_EN=0 or in case no layer2 calculations are         
                                                         executed.; Beside CLRCACHE the cache is also invalidated when it  
                                                         is disabled (PKC_CTRL.CACHE_EN=0) or in case of any write access  
                                                         to PKC_UPTRT.                                                         */
      __IOM uint32_t  CACHE_EN   :  1;              /*!< Enable universal pointer cache: If CACHE_EN=1 the cache for the   
                                                         universal pointer parameters is enabled. In case a parameter      
                                                         value is found in the cache (from a previous fetch) no DMA access 
                                                         is triggered. As such the amount of DMA accesses for the          
                                                         parameter fetch vary between 0 and 4. To further optimize the     
                                                         cache utilization not used parameters, e.g. XPTR for a plain      
                                                         addition (opcode 0x0A), could be defined equal to a used one      
                                                         (e.g. equal YPTR or RPTR) or a previously fetched parameter.; The 
                                                         univeral pointer cache can store up to 6 16-bit parameter values. 
                                                         In case the cache is full the entry that has not been used        
                                                         longest is overwritten by the newly fetched parameter.; The cache 
                                                         can be enabled and disabled at any point in time, even during a   
                                                         running universal pointer fetch calculation.                          */
      __IOM uint32_t  REDMUL     :  2;              /*!< Reduced multiplier mode: REDMUL defines the operand width         
                                                         processed by the PKC coprocessor. The operand width can be        
                                                         reduced to; - perform calculations on short operands, e.g.        
                                                         32-bit.; - reduce power consumption and power peaks.; - add       
                                                         additional noise in combination with PKC_CFG.REDMULNOISE = 1.;    
                                                         PKC calculation performance is reduced when operating in reduced  
                                                         multiplier mode because the operand length in PKC-words (64/32    
                                                         bit) is increased.; For hard coded layer1 calculation modular     
                                                         multiplication and modular reduction the pre-computed inverse of  
                                                         the modul depends on the PKC-word size setting and as such is not 
                                                         the same for different REDMUL configurations.; The operand        
                                                         pointers and length definitions are independant from the REDMUL   
                                                         setting as long as they are 64-bit aligned. The amount of ignored 
                                                         least significiant bits of the pointer and length SFRs depends on 
                                                         REDMUL. As a consequence also the minimum supported operand       
                                                         length defined via PKC_LEN[1,2].LEN and PKC_LEN[1,2].MCLEN are    
                                                         affected by REDMUL.; REDMUL must not be updated during a running  
                                                         calculation while PKC_STATUS.ACTIV is set.; Changing REDMUL       
                                                         during a running calculation may result in wrong calculation      
                                                         results and/or a PKC security alarm (PKC_ACCESS_ERR.PKCC).            */
            uint32_t             : 20;              /*!< reserved                                                              */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  CFG;                             /*!< Configuration register                                                */

    struct {
      __IOM uint32_t  IDLEOP     :  1;              /*!< Idle operation configuration: If IDLEOP is set idle / dummy       
                                                         operations are executed as soon as PKC_CTRL.RESET is cleared. The 
                                                         idle / dummy operations cycles are inserted also in case of gaps  
                                                         between two real calculation, e.g. between two layer0             
                                                         calculations. The idle / dummy operation is aborted when a real   
                                                         calculation is triggered, e.g., via a set GO bit in PKC_CTRL SFR. 
                                                         In case RNDDLY is unequal 0x0 additional clock cycles with idle / 
                                                         dummy calculation are introduced after setting the GO bit before  
                                                         and after the real calculation.; Due to the idle / dummy activity 
                                                         the average power consumption of the PKC is increased when IDLEOP 
                                                         is set. Beside that the idle / dummy operations have no impact on 
                                                         the calculation time.; IDLEOP can only be updated while the PKC   
                                                         is disabled (PKC_CTRL.RESET=1). Any attempt to update the         
                                                         configuration while RESET=0 will trigger a PKC security alarm     
                                                         (PKC_ACCESS_ERR.CTRL is set).                                         */
      __IOM uint32_t  RFU1       :  1;              /*!< RFU                                                                   */
      __IOM uint32_t  RFU2       :  1;              /*!< RFU                                                                   */
      __IOM uint32_t  CLKRND     :  1;              /*!< Clock randomization configuration: CLKRND=1 activates the PKC     
                                                         clock randomization. The performance decreases by approx. 8&#37;. 
                                                         Impact on power consumption is negligible.; CLKRND can only be    
                                                         updated while the PKC is disabled (PKC_CTRL.RESET=1). Any attempt 
                                                         to update the configuration while RESET=0 will trigger a PKC      
                                                         security alarm (PKC_ACCESS_ERR.CTRL is set).                          */
      __IOM uint32_t  REDMULNOISE:  1;              /*!< Noise in reduced multiplier mode configuration: In reduced        
                                                         multiplier mode only parts of the arithmetic PKC logic is         
                                                         utilized. When REDMULNOISE=1 the not used circuitry is loaded     
                                                         with random data to increase the noise level.; REDMULNOISE has no 
                                                         impact in case PKC_CTRL.REDMUL is set to 0x0 or 0x2 (the max.     
                                                         multiplier width). When REDMULNOISE is set for REDMUL equal 0x1   
                                                         the power consumption is increased to the level of REDMUL equal   
                                                         0x0 or 0x2 (full size resp. 64-bit mode).; REDMULNOISE can only   
                                                         be updated while the PKC is disabled (PKC_CTRL.RESET=1). Any      
                                                         attempt to update the configuration while RESET=0 will trigger a  
                                                         PKC security alarm (PKC_ACCESS_ERR.CTRL is set).                      */
      __IOM uint32_t  RNDDLY     :  3;              /*!< Random delay configuration: Define random delay cycles introduced 
                                                         randomly before and after real calculation. The sum of the idle / 
                                                         dummy cycles before and after the real calculation and as such    
                                                         the total calculation time is constant per RNDDLY setting.; The   
                                                         random delay is introduced for each single direct calculation,    
                                                         e.g., for a layer1 MC calculation the delay is inserted for each  
                                                         single Execute opcode.; In case RNDDLY is unequal 0x0             
                                                         PKC_STATUS.ACTIV is cleared and the interrupt is triggered after  
                                                         the real calculation and all delay cycles have finalized. In case 
                                                         PKC_CFG.IDLEOP is set idle / dummy calculations are executed      
                                                         during the delay cycles. Otherwise only the start of the real     
                                                         calculation and the end of calculation signalling is delayed      
                                                         without any activity during the delay cycles.; RNDDLY can only be 
                                                         updated while the PKC is disabled (PKC_CTRL.RESET=1). Any attempt 
                                                         to update the configuration while RESET=0 will trigger a PKC      
                                                         security alarm (PKC_ACCESS_ERR.CTRL is set).                          */
      __IOM uint32_t  SBXNOISE   :  1;              /*!< Noise feature not available in this version.                          */
      __IOM uint32_t  ALPNOISE   :  1;              /*!< Noise feature not available in this version.                          */
      __IOM uint32_t  FMULNOISE  :  1;              /*!< Noise feature not available in this version.                          */
            uint32_t             : 21;              /*!< reserved                                                              */
    } CFG_b;                                        /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED0;

  union {
    __IOM uint32_t  MODE1;                           /*!< Mode register, parameter set 1                                        */

    struct {
      __IOM uint32_t  MODE       :  8;              /*!< Calculation Mode / MC Start address:; Calculation mode of direct  
                                                         calculation (layer0) are listed in a table in Section 'PKC        
                                                         arithmetic unit (layer 0)'. In case of a not supported            
                                                         calculation mode for layer0 calculation a PKC security alarm is   
                                                         triggered (PKC_ACCESS_ERR.PKCC is set).; MC start addresses for   
                                                         hard coded MC pattern are listed in a table in Section 'Fixed     
                                                         Layer 1 MC Patterns'. The start address for the flexible MC       
                                                         pattern depends on the customized MC code previously stored using 
                                                         SFR PKC_MCDATA (data) and PKC_MODE1 (address).; PKC_MODE1 is      
                                                         additionally used as pointer for the flexible MC initialization.  
                                                         As PKC_MCDATA can only be accessed in chunks of 32-bit the least  
                                                         significant two bits PKC_MODE1[1:0] are ignored. PKC_MODE1 is     
                                                         automatically incremented by 4 for each read/write to PKC_MCDATA. 
                                                         In case PKC_MCDATA is read/written while PKC_CTRL.RESET=0 a       
                                                         security alarm is triggered (PKC_ACCESS_ERR.CTRL is set).             */
            uint32_t             : 24;              /*!< reserved                                                              */
    } MODE1_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  XYPTR1;                          /*!< X+Y pointer register, parameter set 1                                 */

    struct {
      __IOM uint32_t  XPTR       : 16;              /*!< Start address of X operand in PKCRAM with byte granularity: Least 
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
      __IOM uint32_t  YPTR       : 16;              /*!< Start address of Y operand in PKCRAM with byte granularity: Least 
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
    } XYPTR1_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  ZRPTR1;                          /*!< Z+R pointer register, parameter set 1                                 */

    struct {
      __IOM uint32_t  ZPTR       : 16;              /*!< Start address of Z operand in PKCRAM with byte granularity or     
                                                         constant for calculation modes using CONST:; If ZPTR is used as   
                                                         address pointer the least significant bits are ignored depending  
                                                         on PKC_CTRL.REDMUL setting. Most significant bits are ignored     
                                                         depending on available PKCRAM size.; If ZPTR is used as CONST     
                                                         operand the high byte is ignored and only ZPTR[7:0] is used for   
                                                         the calculation. For shift/rotate operation further most          
                                                         signficant bits are ignored depending on PKC_CTRL.REDMUL.             */
      __IOM uint32_t  RPTR       : 16;              /*!< Start address of R result in PKCRAM with byte granularity: Least  
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
    } ZRPTR1_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  LEN1;                            /*!< Length register, parameter set 1                                      */

    struct {
      __IOM uint32_t  LEN        : 16;              /*!< Operand length: LEN defines the length of the operands and the    
                                                         result in bytes. The length of Y, Z and R depend furthermore on   
                                                         the selected calculation mode.; The least significant bits are    
                                                         ignored depending on PKC_CTRL.REDMUL setting. Most significant    
                                                         bits are ignored depending on available PKCRAM size. In case LEN  
                                                         is too short such that the resulting length depending on          
                                                         PKC_CTRL.REDMUL is zero a PKC security alarm is triggered         
                                                         (PKC_ACCESS_ERR.PKCC is set).                                         */
      __IOM uint32_t  MCLEN      : 16;              /*!< Loop counter for microcode pattern: MCLEN defines the length of   
                                                         the loop counter that can be used in layer1 calculation mode,     
                                                         e.g. in MC opcode DecrTBNZ. For the hardcoded MC patterns Modular 
                                                         Multiplication (MC start address 0x00), Plain Multiplication      
                                                         (0x13), Plain Multiplication with Addition (0x1D) and Modular     
                                                         Reduction (0x33) MCLEN defines the length of the X operand in     
                                                         bytes.; The least significant bits are ignored depending on       
                                                         PKC_CTRL.REDMUL setting. Most significant bits are ignored        
                                                         depending on available PKCRAM size. In case MCLEN is too short    
                                                         such that a DecrTBNZ MC opcode is executed on a zero loop counter 
                                                         value a PKC security alarm is triggered (PKC_ACCESS_ERR.PKCC is   
                                                         set).                                                                 */
    } LEN1_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  MODE2;                           /*!< Mode register, parameter set 2                                        */

    struct {
      __IOM uint32_t  MODE       :  8;              /*!< Calculation Mode / MC Start address:; Calculation mode of direct  
                                                         calculation (layer0) are listed in a table in Section 'PKC        
                                                         arithmetic unit (layer 0)'. In case of a not supported            
                                                         calculation mode for layer0 calculation a PKC security alarm is   
                                                         triggered (PKC_ACCESS_ERR.PKCC is set).; MC start addresses for   
                                                         hard coded MC pattern are listed in a table in Section 'Fixed     
                                                         Layer 1 MC Patterns'. The start address for the flexible MC       
                                                         pattern depends on the customized MC code previously stored using 
                                                         SFR PKC_MCDATA (data) and PKC_MODE1 (address).                        */
            uint32_t             : 24;              /*!< reserved                                                              */
    } MODE2_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  XYPTR2;                          /*!< X+Y pointer register, parameter set 2                                 */

    struct {
      __IOM uint32_t  XPTR       : 16;              /*!< Start address of X operand in PKCRAM with byte granularity: Least 
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
      __IOM uint32_t  YPTR       : 16;              /*!< Start address of Y operand in PKCRAM with byte granularity: Least 
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
    } XYPTR2_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  ZRPTR2;                          /*!< Z+R pointer register, parameter set 2                                 */

    struct {
      __IOM uint32_t  ZPTR       : 16;              /*!< Start address of Z operand in PKCRAM with byte granularity or     
                                                         constant for calculation modes using CONST:; If ZPTR is used as   
                                                         address pointer the least significant bits are ignored depending  
                                                         on PKC_CTRL.REDMUL setting. Most significant bits are ignored     
                                                         depending on available PKCRAM size.; If ZPTR is used as CONST     
                                                         operand the high byte is ignored and only ZPTR[7:0] is used for   
                                                         the calculation. For shift/rotate operation further most          
                                                         signficant bits are ignored depending on PKC_CTRL.REDMUL.             */
      __IOM uint32_t  RPTR       : 16;              /*!< Start address of R result in PKCRAM with byte granularity: Least  
                                                         significant bits are ignored depending on PKC_CTRL.REDMUL         
                                                         setting. Most significant bits are ignored depending on available 
                                                         PKCRAM size.                                                          */
    } ZRPTR2_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  LEN2;                            /*!< Length register, parameter set 2                                      */

    struct {
      __IOM uint32_t  LEN        : 16;              /*!< Operand length: LEN defines the length of the operands and the    
                                                         result in bytes. The length of Y, Z and R depend furthermore on   
                                                         the selected calculation mode.; The least significant bits are    
                                                         ignored depending on PKC_CTRL.REDMUL setting. Most significant    
                                                         bits are ignored depending on available PKCRAM size. In case LEN  
                                                         is too short such that the resulting length depending on          
                                                         PKC_CTRL.REDMUL is zero a PKC security alarm is triggered         
                                                         (PKC_ACCESS_ERR.PKCC is set).                                         */
      __IOM uint32_t  MCLEN      : 16;              /*!< Loop counter for microcode pattern: MCLEN defines the length of   
                                                         the loop counter that can be used in layer1 calculation mode,     
                                                         e.g. in MC opcode DecrTBNZ. For the hardcoded MC patterns Modular 
                                                         Multiplication (MC start address 0x00); The least significant     
                                                         bits are ignored depending on PKC_CTRL.REDMUL setting. Most       
                                                         significant bits are ignored depending on available PKCRAM size.  
                                                         In case MCLEN is too short such that a DecrTBNZ MC opcode is      
                                                         executed on a zero loop counter value a PKC security alarm is     
                                                         triggered (PKC_ACCESS_ERR.PKCC is set).                               */
    } LEN2_b;                                       /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED1[4];

  union {
    __IOM uint32_t  UPTR;                            /*!< Universal pointer FUP program                                         */

    struct {
      __IOM uint32_t  PTR        : 32;              /*!< Pointer to start address of PKC FUP program: PKC_UPTR needs to be 
                                                         defined before starting a universal pointer PKC calculation       
                                                         (layer2) via PKC_CTRL.GOU. The pointer address needs to be valid  
                                                         and the memory space the pointer addresses needs to be enabled    
                                                         for PKC access by the system. Otherwise a security alarm is       
                                                         triggered (PKC_ACCESS_ERR.AHB is set).; PKC_UPTR must not be      
                                                         updated during a running layer2 calculation while                 
                                                         PKC_STATUS.GOANY is set. Update of this SFR during a universal    
                                                         pointer fetch calculation may result in wrong calculation results 
                                                         and/or security alarms.; PKC_UPTR is updated by HW during a       
                                                         layer2 calculation, resp. incremented by 6 for each processed FUP 
                                                         program entry. The least signficant bit of PKC_UPTR is ignored as 
                                                         the FUP program has to be stored at even addresses.                   */
    } UPTR_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  UPTRT;                           /*!< Universal pointer FUP table                                           */

    struct {
      __IOM uint32_t  PTR        : 32;              /*!< Pointer to start address of PKC FUP table: PKC_UPTRT needs to be  
                                                         defined before starting a universal pointer PKC calculation       
                                                         (layer2) via PKC_CTRL.GOU. The pointer address needs to be valid  
                                                         and the memory space the pointer addresses needs to be enabled    
                                                         for PKC access by the system. Otherwise a security alarm is       
                                                         triggered (PKC_ACCESS_ERR.AHB is set).; PKC_UPTRT must not be     
                                                         updated during a running layer2 calculation while                 
                                                         PKC_STATUS.GOANY is set. Update of this SFR during a universal    
                                                         pointer fetch calculation may result in wrong calculation results 
                                                         and/or security alarms.; PKC_UPTRT is not updated by HW during a  
                                                         layer2 calculation. The least signficant bit of PKC_UPTRT is      
                                                         ignored as the FUP table has to be stored at even addresses.; Any 
                                                         SFR write access to PKC_UPTRT triggers the invalidation of the    
                                                         universal pointer cache, similar to PKC_CTRL.CLRCACHE.                */
    } UPTRT_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  ULEN;                            /*!< Universal pointer length                                              */

    struct {
      __IOM uint32_t  LEN        :  8;              /*!< Length of universal pointer calculation: PKC_ULEN defines how     
                                                         many FUP program entries shall be processed for one layer2        
                                                         calculation started via PKC_CTRL.GOU. The FUP program entries     
                                                         include layer0 calculations, layer1 calculations and CRC entries  
                                                         for FUP program integrity protection.; PKC_ULEN must not be       
                                                         updated during a running layer2 calculation while                 
                                                         PKC_STATUS.GOANY is set. Update of this SFR during a universal    
                                                         pointer fetch calculation may result in wrong calculation results 
                                                         and/or security alarms.; Starting a univesal pointer fetch        
                                                         calculation via PKC_CTRL.GOU while PKC_ULEN is zero triggers a    
                                                         security alarm (PKC_ACCESS_ERR.CTRL is set).; PKC_ULEN is updated 
                                                         by HW during a layer2 calculation, resp. decremented for each     
                                                         processed FUP program entry. When PKC_ULEN has been decremented   
                                                         to zero PKC_STATUS.GOANY is cleared to indicate the start of the  
                                                         last calculation. When the PKC has finalized its last pipe        
                                                         calculation PKC_STATUS.ACTIV is cleared and the interrupt status  
                                                         bit PKC_INT_STATUS.INT_PDONE is set.                                  */
            uint32_t             : 24;              /*!< reserved                                                              */
    } ULEN_b;                                       /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED2;

  union {
    __IOM uint32_t  MCDATA;                          /*!< MC pattern data interface                                             */

    struct {
      __IOM uint32_t  MCDATA     : 32;              /*!< Microcode read/write data: Read access to PKC_MCDATA returns the  
                                                         32-bit MC pattern addressed by PKC_MODE1. Default value of all    
                                                         flexible MC bytes after reset is 0xFF (invalid MC instruction).   
                                                         Read to PKC_MCDATA while PKC_CTRL.RESET=0 or PKC_MODE1&lt;0x80    
                                                         (fixed MC pattern) triggers a security alarm (PKC_ACCESS_ERR.CTRL 
                                                         is set).; NOTE: When trying to read flexible MC bytes not         
                                                         existing (e.g., fixed MC bytes) a data value of 0 is returned.; A 
                                                         SFR write to PKC_MCDATA initializes the MC pattern PKC_MODE1      
                                                         points to. Write to PKC_MCDATA while PKC_CTRL.RESET=0 or          
                                                         PKC_MODE1&lt;0x80 (fixed MC pattern) triggers a security alarm    
                                                         (PKC_ACCESS_ERR.CTRL is set).; Any SFR access to PKC_MCDATA       
                                                         increments the PKC_MODE1 SFR by 4. As PKC_MCDATA is always        
                                                         accessed with 32-bit width the least signficant bits              
                                                         PKC_MODE1[1:0] are ignored for the MC flexible data addressing.       */
    } MCDATA_b;                                     /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED3[3];

  union {
    __IM  uint32_t  VERSION;                         /*!< PKC version register                                                  */

    struct {
      __IM  uint32_t  MULSIZE    :  2;              /*!< native multiplier size and operand granularity                        */
      __IM  uint32_t  MCAVAIL    :  1;              /*!< MC feature (layer1 calculation) is available                          */
      __IM  uint32_t  UPAVAIL    :  1;              /*!< UP feature (layer2 calculation) is available                          */
      __IM  uint32_t  UPCACHEAVAIL:  1;             /*!< UP cache is available                                                 */
      __IM  uint32_t  GF2AVAIL   :  1;              /*!< GF2 calculation modes are available                                   */
      __IM  uint32_t  PARAMNUM   :  2;              /*!< Number of parameter sets for real calculation                         */
      __IM  uint32_t  SBX0AVAIL  :  1;              /*!< SBX0 operation is available                                           */
      __IM  uint32_t  SBX1AVAIL  :  1;              /*!< SBX1 operation is available                                           */
      __IM  uint32_t  SBX2AVAIL  :  1;              /*!< SBX2 operation is available                                           */
      __IM  uint32_t  SBX3AVAIL  :  1;              /*!< SBX3 operation is available                                           */
      __IM  uint32_t  MCRECONF_SIZE:  8;            /*!< Size of reconfigurable MC table in bytes                              */
            uint32_t             : 12;              /*!< reserved                                                              */
    } VERSION_b;                                    /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED4[979];

  union {
    __IOM uint32_t  SOFT_RST;                        /*!< Software reset                                                        */

    struct {
      __IOM uint32_t  SOFT_RST   :  1;              /*!< Write 1 to reset module (0 has no effect). All running and        
                                                         pending PKC calculation are stopped. All PKC SFRs are reset       
                                                         except PKC_ACCESS_ERR.                                                */
            uint32_t             : 31;              /*!< reserved                                                              */
    } SOFT_RST_b;                                   /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED5[3];

  union {
    __IM  uint32_t  ACCESS_ERR;                      /*!< Access Error                                                          */

    struct {
      __IM  uint32_t  APB_NOTAV  :  1;              /*!< APB Error: address not available                                      */
      __IM  uint32_t  APB_WRGMD  :  1;              /*!< APB Error: Wrong access mode                                          */
            uint32_t             :  2;              /*!< reserved for future erors on SPB I/F                                  */
      __IM  uint32_t  APB_MASTER :  4;              /*!< APB Master that triggered first APB error (APB_WRGMD or APB_NOTAV     */
            uint32_t             :  2;              /*!< reserved for future erors on AHB I/F Layer2 Only                      */
      __IM  uint32_t  AHB        :  1;              /*!< AHB Error: invalid AHB access Layer2 Only                             */
            uint32_t             :  5;              /*!< reserved for future erors on AHB I/F Layer2 Only                      */
      __IM  uint32_t  PKCC       :  1;              /*!< Error in PKC coprocessor kernel                                       */
      __IM  uint32_t  FDET       :  1;              /*!< Error due to error detection circuitry                                */
      __IM  uint32_t  CTRL       :  1;              /*!< Error in PKC software control                                         */
      __IM  uint32_t  UCRC       :  1;              /*!< Error in layer2 CRC check                                             */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 11;              /*!< reserved for more block errors                                        */
    } ACCESS_ERR_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  ACCESS_ERR_CLR;                  /*!< Clear Access Error                                                    */

    struct {
      __IOM uint32_t  ERR_CLR    :  1;              /*!< Write 1 to reset PKC_ACCESS_ERR SFR.                                  */
            uint32_t             : 31;              /*!< reserved                                                              */
    } ACCESS_ERR_CLR_b;                             /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED6[4];

  union {
    __IOM uint32_t  INT_CLR_ENABLE;                  /*!< Interrupt enable clear                                                */

    struct {
      __IOM uint32_t  EN_PDONE   :  1;              /*!< Write to clear PDONE interrupt enable flag                        
                                                         (PKC_INT_ENABLE.EN_PDONE=0).                                          */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_CLR_ENABLE_b;                             /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  INT_SET_ENABLE;                  /*!< Interrupt enable set                                                  */

    struct {
      __IOM uint32_t  EN_PDONE   :  1;              /*!< Write to set PDONE interrupt enable flag                          
                                                         (PKC_INT_ENABLE.EN_PDONE=1).                                          */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_SET_ENABLE_b;                             /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  INT_STATUS;                      /*!< Interrupt status                                                      */

    struct {
      __IM  uint32_t  INT_PDONE  :  1;              /*!< End-of-computation status flag: INT_PDONE is set after EACH       
                                                         single PKC layer0 or layer1 calculation. In case of a universal   
                                                         pointer calculation (layer2) INT_PDONE is set at the end of the   
                                                         pipe calculation when PKC_ULEN has been decremented to zero and   
                                                         the final PKC calculation has completed.; INT_PDONE is set        
                                                         independent from the interrupt enable PKC_INT_ENABLE.EN_PDONE. In 
                                                         case PKC_INT_ENABLE.EN_PDONE=1 an interrupt towards the CPU is    
                                                         triggered when INT_PDONE is set (level triggered).; INT_PDONE is  
                                                         not cleared by PKC hardware but has to be cleared by software,    
                                                         except in case of a reset (chip/block reset, PKC_SOFT_RST, PKC    
                                                         security alarm).                                                      */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_STATUS_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IM  uint32_t  INT_ENABLE;                      /*!< Interrupt enable                                                      */

    struct {
      __IM  uint32_t  EN_PDONE   :  1;              /*!< PDONE interrupt enable flag: If EN_PDONE=1 an interrupt is        
                                                         triggered every time PKC_INT_STATUS.INT_PDONE is set. Otherwise   
                                                         the interrupt generation is suppressed.                               */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_ENABLE_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  INT_CLR_STATUS;                  /*!< Interrupt status clear                                                */

    struct {
      __IOM uint32_t  INT_PDONE  :  1;              /*!< Write to clear End-of-computation status flag                     
                                                         (PKC_INT_STATUS.INT_PDONE=0).                                         */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_CLR_STATUS_b;                             /*!< BitSize                                                               */
  };

  union {
    __IOM uint32_t  INT_SET_STATUS;                  /*!< Interrupt status set                                                  */

    struct {
      __IOM uint32_t  INT_PDONE  :  1;              /*!< Write to set End-of-computation status flag                       
                                                         (PKC_INT_STATUS.INT_PDONE=1) to trigger a PKC interrupt via       
                                                         software, e.g. for debug purposes.                                    */
            uint32_t             :  1;              /*!< reserved                                                              */
            uint32_t             : 30;              /*!< reserved                                                              */
    } INT_SET_STATUS_b;                             /*!< BitSize                                                               */
  };
  __IM  uint32_t  RESERVED7[3];

  union {
    __IM  uint32_t  MODULE_ID;                       /*!< Module ID                                                             */

    struct {
      __IM  uint32_t  SIZE       :  8;              /*!< Address space of the IP                                               */
      __IM  uint32_t  MINOR_REV  :  4;              /*!< Minor revision                                                        */
      __IM  uint32_t  MAJOR_REV  :  4;              /*!< Major revision                                                        */
      __IM  uint32_t  ID         : 16;              /*!< Module ID                                                             */
    } MODULE_ID_b;                                  /*!< BitSize                                                               */
  };
} ip_pkc_Type;


/* ================================================================================ */
/* ================            Detailed bit description            ================ */
/* ================================================================================ */

/* ================                 Bit field only                 ================ */
#define PKC_CTRL_b_REDMUL_FULLSZ                        0x0             /*!< full size mode, 3 least significant bits of pointer and length are ignored, minimum supported length 0x0008*/
#define PKC_CTRL_b_REDMUL_32BIT                         0x1             /*!< RFU Error Generated if selected                                       */
#define PKC_CTRL_b_REDMUL_64BIT                         0x2             /*!< 64-bit mode, 3 least significant bits of pointer and length are ignored, minimum supported length 0x0008*/
#define PKC_CTRL_b_REDMUL_128BIT                        0x3             /*!< RFU Error Generated if selected                                       */

#define PKC_CFG_b_RNDDLY_NODLY                          0x0             /*!< no random delay                                                       */
#define PKC_CFG_b_RNDDLY_1DLY                           0x1             /*!< 1x4 clocks delay                                                      */
#define PKC_CFG_b_RNDDLY_3DLY                           0x2             /*!< 3x4 clocks delay                                                      */
#define PKC_CFG_b_RNDDLY_7DLY                           0x3             /*!< 7x4 clocks delay                                                      */
#define PKC_CFG_b_RNDDLY_15DLY                          0x4             /*!< 15x4 clocks delay                                                     */
#define PKC_CFG_b_RNDDLY_31DLY                          0x5             /*!< 31x4 clocks delay                                                     */
#define PKC_CFG_b_RNDDLY_63DLY                          0x6             /*!< 63x4 clocks delay                                                     */
#define PKC_CFG_b_RNDDLY_127DLY                         0x7             /*!< 127x4 clocks delay                                                    */

#define PKC_VERSION_b_MULSIZE_32B                       0x1             /*!< 32-bit multiplier                                                     */
#define PKC_VERSION_b_MULSIZE_64B                       0x2             /*!< 64-bit multiplier                                                     */
#define PKC_VERSION_b_MULSIZE_128B                      0x3             /*!< 128-bit multiplier                                                    */

/* ================                  Complete SFR                  ================ */
#define PKC_CTRL_REDMUL_FULLSZ                          0x00000000      /*!< full size mode, 3 least significant bits of pointer and length are ignored, minimum supported length 0x0008*/
#define PKC_CTRL_REDMUL_32BIT                           0x00000400      /*!< RFU Error Generated if selected                                       */
#define PKC_CTRL_REDMUL_64BIT                           0x00000800      /*!< 64-bit mode, 3 least significant bits of pointer and length are ignored, minimum supported length 0x0008*/
#define PKC_CTRL_REDMUL_128BIT                          0x00000C00      /*!< RFU Error Generated if selected                                       */

#define PKC_CFG_RNDDLY_NODLY                            0x00000000      /*!< no random delay                                                       */
#define PKC_CFG_RNDDLY_1DLY                             0x00000020      /*!< 1x4 clocks delay                                                      */
#define PKC_CFG_RNDDLY_3DLY                             0x00000040      /*!< 3x4 clocks delay                                                      */
#define PKC_CFG_RNDDLY_7DLY                             0x00000060      /*!< 7x4 clocks delay                                                      */
#define PKC_CFG_RNDDLY_15DLY                            0x00000080      /*!< 15x4 clocks delay                                                     */
#define PKC_CFG_RNDDLY_31DLY                            0x000000A0      /*!< 31x4 clocks delay                                                     */
#define PKC_CFG_RNDDLY_63DLY                            0x000000C0      /*!< 63x4 clocks delay                                                     */
#define PKC_CFG_RNDDLY_127DLY                           0x000000E0      /*!< 127x4 clocks delay                                                    */

#define PKC_VERSION_MULSIZE_32B                         0x00000001      /*!< 32-bit multiplier                                                     */
#define PKC_VERSION_MULSIZE_64B                         0x00000002      /*!< 64-bit multiplier                                                     */
#define PKC_VERSION_MULSIZE_128B                        0x00000003      /*!< 128-bit multiplier                                                    */



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
/* ================          struct 'PKC' Position & Mask          ================ */
/* ================================================================================ */


/* ===============================     PKC_STATUS    ============================== */
#define PKC_STATUS_ACTIV_Pos                  0                                                       /*!< PKC_STATUS: ACTIV Position              */
#define PKC_STATUS_ACTIV_Msk                  (0x01UL << PKC_STATUS_ACTIV_Pos)                        /*!< PKC_STATUS: ACTIV Mask                  */
#define PKC_STATUS_CARRY_Pos                  1                                                       /*!< PKC_STATUS: CARRY Position              */
#define PKC_STATUS_CARRY_Msk                  (0x01UL << PKC_STATUS_CARRY_Pos)                        /*!< PKC_STATUS: CARRY Mask                  */
#define PKC_STATUS_ZERO_Pos                   2                                                       /*!< PKC_STATUS: ZERO Position               */
#define PKC_STATUS_ZERO_Msk                   (0x01UL << PKC_STATUS_ZERO_Pos)                         /*!< PKC_STATUS: ZERO Mask                   */
#define PKC_STATUS_GOANY_Pos                  3                                                       /*!< PKC_STATUS: GOANY Position              */
#define PKC_STATUS_GOANY_Msk                  (0x01UL << PKC_STATUS_GOANY_Pos)                        /*!< PKC_STATUS: GOANY Mask                  */
#define PKC_STATUS_RESERVED0_Pos              4                                                       /*!< PKC_STATUS: RESERVED0 Position          */
#define PKC_STATUS_RESERVED0_Msk              (0x01UL << PKC_STATUS_RESERVED0_Pos)                    /*!< PKC_STATUS: RESERVED0 Mask              */
#define PKC_STATUS_LOCKED_Pos                 5                                                       /*!< PKC_STATUS: LOCKED Position             */
#define PKC_STATUS_LOCKED_Msk                 (0x03UL << PKC_STATUS_LOCKED_Pos)                       /*!< PKC_STATUS: LOCKED Mask                 */
#define PKC_STATUS_RESERVED1_Pos              7                                                       /*!< PKC_STATUS: RESERVED1 Position          */
#define PKC_STATUS_RESERVED1_Msk              (0x01ffffffUL << PKC_STATUS_RESERVED1_Pos)              /*!< PKC_STATUS: RESERVED1 Mask              */

/* ===============================      PKC_CTRL     ============================== */
#define PKC_CTRL_RESET_Pos                    0                                                       /*!< PKC_CTRL: RESET Position                */
#define PKC_CTRL_RESET_Msk                    (0x01UL << PKC_CTRL_RESET_Pos)                          /*!< PKC_CTRL: RESET Mask                    */
#define PKC_CTRL_STOP_Pos                     1                                                       /*!< PKC_CTRL: STOP Position                 */
#define PKC_CTRL_STOP_Msk                     (0x01UL << PKC_CTRL_STOP_Pos)                           /*!< PKC_CTRL: STOP Mask                     */
#define PKC_CTRL_GOD1_Pos                     2                                                       /*!< PKC_CTRL: GOD1 Position                 */
#define PKC_CTRL_GOD1_Msk                     (0x01UL << PKC_CTRL_GOD1_Pos)                           /*!< PKC_CTRL: GOD1 Mask                     */
#define PKC_CTRL_GOD2_Pos                     3                                                       /*!< PKC_CTRL: GOD2 Position                 */
#define PKC_CTRL_GOD2_Msk                     (0x01UL << PKC_CTRL_GOD2_Pos)                           /*!< PKC_CTRL: GOD2 Mask                     */
#define PKC_CTRL_GOM1_Pos                     4                                                       /*!< PKC_CTRL: GOM1 Position                 */
#define PKC_CTRL_GOM1_Msk                     (0x01UL << PKC_CTRL_GOM1_Pos)                           /*!< PKC_CTRL: GOM1 Mask                     */
#define PKC_CTRL_GOM2_Pos                     5                                                       /*!< PKC_CTRL: GOM2 Position                 */
#define PKC_CTRL_GOM2_Msk                     (0x01UL << PKC_CTRL_GOM2_Pos)                           /*!< PKC_CTRL: GOM2 Mask                     */
#define PKC_CTRL_GOU_Pos                      6                                                       /*!< PKC_CTRL: GOU Position                  */
#define PKC_CTRL_GOU_Msk                      (0x01UL << PKC_CTRL_GOU_Pos)                            /*!< PKC_CTRL: GOU Mask                      */
#define PKC_CTRL_GF2CONV_Pos                  7                                                       /*!< PKC_CTRL: GF2CONV Position              */
#define PKC_CTRL_GF2CONV_Msk                  (0x01UL << PKC_CTRL_GF2CONV_Pos)                        /*!< PKC_CTRL: GF2CONV Mask                  */
#define PKC_CTRL_CLRCACHE_Pos                 8                                                       /*!< PKC_CTRL: CLRCACHE Position             */
#define PKC_CTRL_CLRCACHE_Msk                 (0x01UL << PKC_CTRL_CLRCACHE_Pos)                       /*!< PKC_CTRL: CLRCACHE Mask                 */
#define PKC_CTRL_CACHE_EN_Pos                 9                                                       /*!< PKC_CTRL: CACHE_EN Position             */
#define PKC_CTRL_CACHE_EN_Msk                 (0x01UL << PKC_CTRL_CACHE_EN_Pos)                       /*!< PKC_CTRL: CACHE_EN Mask                 */
#define PKC_CTRL_REDMUL_Pos                   10                                                      /*!< PKC_CTRL: REDMUL Position               */
#define PKC_CTRL_REDMUL_Msk                   (0x03UL << PKC_CTRL_REDMUL_Pos)                         /*!< PKC_CTRL: REDMUL Mask                   */
#define PKC_CTRL_RESERVED_Pos                 12                                                      /*!< PKC_CTRL: RESERVED Position             */
#define PKC_CTRL_RESERVED_Msk                 (0x000fffffUL << PKC_CTRL_RESERVED_Pos)                 /*!< PKC_CTRL: RESERVED Mask                 */

/* ===============================      PKC_CFG      ============================== */
#define PKC_CFG_IDLEOP_Pos                    0                                                       /*!< PKC_CFG: IDLEOP Position                */
#define PKC_CFG_IDLEOP_Msk                    (0x01UL << PKC_CFG_IDLEOP_Pos)                          /*!< PKC_CFG: IDLEOP Mask                    */
#define PKC_CFG_RFU1_Pos                      1                                                       /*!< PKC_CFG: RFU1 Position                  */
#define PKC_CFG_RFU1_Msk                      (0x01UL << PKC_CFG_RFU1_Pos)                            /*!< PKC_CFG: RFU1 Mask                      */
#define PKC_CFG_RFU2_Pos                      2                                                       /*!< PKC_CFG: RFU2 Position                  */
#define PKC_CFG_RFU2_Msk                      (0x01UL << PKC_CFG_RFU2_Pos)                            /*!< PKC_CFG: RFU2 Mask                      */
#define PKC_CFG_CLKRND_Pos                    3                                                       /*!< PKC_CFG: CLKRND Position                */
#define PKC_CFG_CLKRND_Msk                    (0x01UL << PKC_CFG_CLKRND_Pos)                          /*!< PKC_CFG: CLKRND Mask                    */
#define PKC_CFG_REDMULNOISE_Pos               4                                                       /*!< PKC_CFG: REDMULNOISE Position           */
#define PKC_CFG_REDMULNOISE_Msk               (0x01UL << PKC_CFG_REDMULNOISE_Pos)                     /*!< PKC_CFG: REDMULNOISE Mask               */
#define PKC_CFG_RNDDLY_Pos                    5                                                       /*!< PKC_CFG: RNDDLY Position                */
#define PKC_CFG_RNDDLY_Msk                    (0x07UL << PKC_CFG_RNDDLY_Pos)                          /*!< PKC_CFG: RNDDLY Mask                    */
#define PKC_CFG_SBXNOISE_Pos                  8                                                       /*!< PKC_CFG: SBXNOISE Position              */
#define PKC_CFG_SBXNOISE_Msk                  (0x01UL << PKC_CFG_SBXNOISE_Pos)                        /*!< PKC_CFG: SBXNOISE Mask                  */
#define PKC_CFG_ALPNOISE_Pos                  9                                                       /*!< PKC_CFG: ALPNOISE Position              */
#define PKC_CFG_ALPNOISE_Msk                  (0x01UL << PKC_CFG_ALPNOISE_Pos)                        /*!< PKC_CFG: ALPNOISE Mask                  */
#define PKC_CFG_FMULNOISE_Pos                 10                                                      /*!< PKC_CFG: FMULNOISE Position             */
#define PKC_CFG_FMULNOISE_Msk                 (0x01UL << PKC_CFG_FMULNOISE_Pos)                       /*!< PKC_CFG: FMULNOISE Mask                 */
#define PKC_CFG_RESERVED_Pos                  11                                                      /*!< PKC_CFG: RESERVED Position              */
#define PKC_CFG_RESERVED_Msk                  (0x001fffffUL << PKC_CFG_RESERVED_Pos)                  /*!< PKC_CFG: RESERVED Mask                  */

/* ===============================     PKC_MODE1     ============================== */
#define PKC_MODE1_MODE_Pos                    0                                                       /*!< PKC_MODE1: MODE Position                */
#define PKC_MODE1_MODE_Msk                    (0x000000ffUL << PKC_MODE1_MODE_Pos)                    /*!< PKC_MODE1: MODE Mask                    */
#define PKC_MODE1_RESERVED_Pos                8                                                       /*!< PKC_MODE1: RESERVED Position            */
#define PKC_MODE1_RESERVED_Msk                (0x00ffffffUL << PKC_MODE1_RESERVED_Pos)                /*!< PKC_MODE1: RESERVED Mask                */

/* ===============================     PKC_XYPTR1    ============================== */
#define PKC_XYPTR1_XPTR_Pos                   0                                                       /*!< PKC_XYPTR1: XPTR Position               */
#define PKC_XYPTR1_XPTR_Msk                   (0x0000ffffUL << PKC_XYPTR1_XPTR_Pos)                   /*!< PKC_XYPTR1: XPTR Mask                   */
#define PKC_XYPTR1_YPTR_Pos                   16                                                      /*!< PKC_XYPTR1: YPTR Position               */
#define PKC_XYPTR1_YPTR_Msk                   (0x0000ffffUL << PKC_XYPTR1_YPTR_Pos)                   /*!< PKC_XYPTR1: YPTR Mask                   */

/* ===============================     PKC_ZRPTR1    ============================== */
#define PKC_ZRPTR1_ZPTR_Pos                   0                                                       /*!< PKC_ZRPTR1: ZPTR Position               */
#define PKC_ZRPTR1_ZPTR_Msk                   (0x0000ffffUL << PKC_ZRPTR1_ZPTR_Pos)                   /*!< PKC_ZRPTR1: ZPTR Mask                   */
#define PKC_ZRPTR1_RPTR_Pos                   16                                                      /*!< PKC_ZRPTR1: RPTR Position               */
#define PKC_ZRPTR1_RPTR_Msk                   (0x0000ffffUL << PKC_ZRPTR1_RPTR_Pos)                   /*!< PKC_ZRPTR1: RPTR Mask                   */

/* ===============================      PKC_LEN1     ============================== */
#define PKC_LEN1_LEN_Pos                      0                                                       /*!< PKC_LEN1: LEN Position                  */
#define PKC_LEN1_LEN_Msk                      (0x0000ffffUL << PKC_LEN1_LEN_Pos)                      /*!< PKC_LEN1: LEN Mask                      */
#define PKC_LEN1_MCLEN_Pos                    16                                                      /*!< PKC_LEN1: MCLEN Position                */
#define PKC_LEN1_MCLEN_Msk                    (0x0000ffffUL << PKC_LEN1_MCLEN_Pos)                    /*!< PKC_LEN1: MCLEN Mask                    */

/* ===============================     PKC_MODE2     ============================== */
#define PKC_MODE2_MODE_Pos                    0                                                       /*!< PKC_MODE2: MODE Position                */
#define PKC_MODE2_MODE_Msk                    (0x000000ffUL << PKC_MODE2_MODE_Pos)                    /*!< PKC_MODE2: MODE Mask                    */
#define PKC_MODE2_RESERVED_Pos                8                                                       /*!< PKC_MODE2: RESERVED Position            */
#define PKC_MODE2_RESERVED_Msk                (0x00ffffffUL << PKC_MODE2_RESERVED_Pos)                /*!< PKC_MODE2: RESERVED Mask                */

/* ===============================     PKC_XYPTR2    ============================== */
#define PKC_XYPTR2_XPTR_Pos                   0                                                       /*!< PKC_XYPTR2: XPTR Position               */
#define PKC_XYPTR2_XPTR_Msk                   (0x0000ffffUL << PKC_XYPTR2_XPTR_Pos)                   /*!< PKC_XYPTR2: XPTR Mask                   */
#define PKC_XYPTR2_YPTR_Pos                   16                                                      /*!< PKC_XYPTR2: YPTR Position               */
#define PKC_XYPTR2_YPTR_Msk                   (0x0000ffffUL << PKC_XYPTR2_YPTR_Pos)                   /*!< PKC_XYPTR2: YPTR Mask                   */

/* ===============================     PKC_ZRPTR2    ============================== */
#define PKC_ZRPTR2_ZPTR_Pos                   0                                                       /*!< PKC_ZRPTR2: ZPTR Position               */
#define PKC_ZRPTR2_ZPTR_Msk                   (0x0000ffffUL << PKC_ZRPTR2_ZPTR_Pos)                   /*!< PKC_ZRPTR2: ZPTR Mask                   */
#define PKC_ZRPTR2_RPTR_Pos                   16                                                      /*!< PKC_ZRPTR2: RPTR Position               */
#define PKC_ZRPTR2_RPTR_Msk                   (0x0000ffffUL << PKC_ZRPTR2_RPTR_Pos)                   /*!< PKC_ZRPTR2: RPTR Mask                   */

/* ===============================      PKC_LEN2     ============================== */
#define PKC_LEN2_LEN_Pos                      0                                                       /*!< PKC_LEN2: LEN Position                  */
#define PKC_LEN2_LEN_Msk                      (0x0000ffffUL << PKC_LEN2_LEN_Pos)                      /*!< PKC_LEN2: LEN Mask                      */
#define PKC_LEN2_MCLEN_Pos                    16                                                      /*!< PKC_LEN2: MCLEN Position                */
#define PKC_LEN2_MCLEN_Msk                    (0x0000ffffUL << PKC_LEN2_MCLEN_Pos)                    /*!< PKC_LEN2: MCLEN Mask                    */

/* ===============================      PKC_UPTR     ============================== */
#define PKC_UPTR_PTR_Pos                      0                                                       /*!< PKC_UPTR: PTR Position                  */
#define PKC_UPTR_PTR_Msk                      (0xffffffffUL << PKC_UPTR_PTR_Pos)                      /*!< PKC_UPTR: PTR Mask                      */

/* ===============================     PKC_UPTRT     ============================== */
#define PKC_UPTRT_PTR_Pos                     0                                                       /*!< PKC_UPTRT: PTR Position                 */
#define PKC_UPTRT_PTR_Msk                     (0xffffffffUL << PKC_UPTRT_PTR_Pos)                     /*!< PKC_UPTRT: PTR Mask                     */

/* ===============================      PKC_ULEN     ============================== */
#define PKC_ULEN_LEN_Pos                      0                                                       /*!< PKC_ULEN: LEN Position                  */
#define PKC_ULEN_LEN_Msk                      (0x000000ffUL << PKC_ULEN_LEN_Pos)                      /*!< PKC_ULEN: LEN Mask                      */
#define PKC_ULEN_RESERVED_Pos                 8                                                       /*!< PKC_ULEN: RESERVED Position             */
#define PKC_ULEN_RESERVED_Msk                 (0x00ffffffUL << PKC_ULEN_RESERVED_Pos)                 /*!< PKC_ULEN: RESERVED Mask                 */

/* ===============================     PKC_MCDATA    ============================== */
#define PKC_MCDATA_MCDATA_Pos                 0                                                       /*!< PKC_MCDATA: MCDATA Position             */
#define PKC_MCDATA_MCDATA_Msk                 (0xffffffffUL << PKC_MCDATA_MCDATA_Pos)                 /*!< PKC_MCDATA: MCDATA Mask                 */

/* ===============================    PKC_VERSION    ============================== */
#define PKC_VERSION_MULSIZE_Pos               0                                                       /*!< PKC_VERSION: MULSIZE Position           */
#define PKC_VERSION_MULSIZE_Msk               (0x03UL << PKC_VERSION_MULSIZE_Pos)                     /*!< PKC_VERSION: MULSIZE Mask               */
#define PKC_VERSION_MCAVAIL_Pos               2                                                       /*!< PKC_VERSION: MCAVAIL Position           */
#define PKC_VERSION_MCAVAIL_Msk               (0x01UL << PKC_VERSION_MCAVAIL_Pos)                     /*!< PKC_VERSION: MCAVAIL Mask               */
#define PKC_VERSION_UPAVAIL_Pos               3                                                       /*!< PKC_VERSION: UPAVAIL Position           */
#define PKC_VERSION_UPAVAIL_Msk               (0x01UL << PKC_VERSION_UPAVAIL_Pos)                     /*!< PKC_VERSION: UPAVAIL Mask               */
#define PKC_VERSION_UPCACHEAVAIL_Pos          4                                                       /*!< PKC_VERSION: UPCACHEAVAIL Position      */
#define PKC_VERSION_UPCACHEAVAIL_Msk          (0x01UL << PKC_VERSION_UPCACHEAVAIL_Pos)                /*!< PKC_VERSION: UPCACHEAVAIL Mask          */
#define PKC_VERSION_GF2AVAIL_Pos              5                                                       /*!< PKC_VERSION: GF2AVAIL Position          */
#define PKC_VERSION_GF2AVAIL_Msk              (0x01UL << PKC_VERSION_GF2AVAIL_Pos)                    /*!< PKC_VERSION: GF2AVAIL Mask              */
#define PKC_VERSION_PARAMNUM_Pos              6                                                       /*!< PKC_VERSION: PARAMNUM Position          */
#define PKC_VERSION_PARAMNUM_Msk              (0x03UL << PKC_VERSION_PARAMNUM_Pos)                    /*!< PKC_VERSION: PARAMNUM Mask              */
#define PKC_VERSION_SBX0AVAIL_Pos             8                                                       /*!< PKC_VERSION: SBX0AVAIL Position         */
#define PKC_VERSION_SBX0AVAIL_Msk             (0x01UL << PKC_VERSION_SBX0AVAIL_Pos)                   /*!< PKC_VERSION: SBX0AVAIL Mask             */
#define PKC_VERSION_SBX1AVAIL_Pos             9                                                       /*!< PKC_VERSION: SBX1AVAIL Position         */
#define PKC_VERSION_SBX1AVAIL_Msk             (0x01UL << PKC_VERSION_SBX1AVAIL_Pos)                   /*!< PKC_VERSION: SBX1AVAIL Mask             */
#define PKC_VERSION_SBX2AVAIL_Pos             10                                                      /*!< PKC_VERSION: SBX2AVAIL Position         */
#define PKC_VERSION_SBX2AVAIL_Msk             (0x01UL << PKC_VERSION_SBX2AVAIL_Pos)                   /*!< PKC_VERSION: SBX2AVAIL Mask             */
#define PKC_VERSION_SBX3AVAIL_Pos             11                                                      /*!< PKC_VERSION: SBX3AVAIL Position         */
#define PKC_VERSION_SBX3AVAIL_Msk             (0x01UL << PKC_VERSION_SBX3AVAIL_Pos)                   /*!< PKC_VERSION: SBX3AVAIL Mask             */
#define PKC_VERSION_MCRECONF_SIZE_Pos         12                                                      /*!< PKC_VERSION: MCRECONF_SIZE Position     */
#define PKC_VERSION_MCRECONF_SIZE_Msk         (0x000000ffUL << PKC_VERSION_MCRECONF_SIZE_Pos)         /*!< PKC_VERSION: MCRECONF_SIZE Mask         */
#define PKC_VERSION_RESERVED_Pos              20                                                      /*!< PKC_VERSION: RESERVED Position          */
#define PKC_VERSION_RESERVED_Msk              (0x00000fffUL << PKC_VERSION_RESERVED_Pos)              /*!< PKC_VERSION: RESERVED Mask              */

/* ===============================    PKC_SOFT_RST   ============================== */
#define PKC_SOFT_RST_SOFT_RST_Pos             0                                                       /*!< PKC_SOFT_RST: SOFT_RST Position         */
#define PKC_SOFT_RST_SOFT_RST_Msk             (0x01UL << PKC_SOFT_RST_SOFT_RST_Pos)                   /*!< PKC_SOFT_RST: SOFT_RST Mask             */
#define PKC_SOFT_RST_RESERVED_Pos             1                                                       /*!< PKC_SOFT_RST: RESERVED Position         */
#define PKC_SOFT_RST_RESERVED_Msk             (0x7fffffffUL << PKC_SOFT_RST_RESERVED_Pos)             /*!< PKC_SOFT_RST: RESERVED Mask             */

/* ===============================   PKC_ACCESS_ERR  ============================== */
#define PKC_ACCESS_ERR_APB_NOTAV_Pos          0                                                       /*!< PKC_ACCESS_ERR: APB_NOTAV Position      */
#define PKC_ACCESS_ERR_APB_NOTAV_Msk          (0x01UL << PKC_ACCESS_ERR_APB_NOTAV_Pos)                /*!< PKC_ACCESS_ERR: APB_NOTAV Mask          */
#define PKC_ACCESS_ERR_APB_WRGMD_Pos          1                                                       /*!< PKC_ACCESS_ERR: APB_WRGMD Position      */
#define PKC_ACCESS_ERR_APB_WRGMD_Msk          (0x01UL << PKC_ACCESS_ERR_APB_WRGMD_Pos)                /*!< PKC_ACCESS_ERR: APB_WRGMD Mask          */
#define PKC_ACCESS_ERR_RESERVED0_Pos          2                                                       /*!< PKC_ACCESS_ERR: RESERVED0 Position      */
#define PKC_ACCESS_ERR_RESERVED0_Msk          (0x03UL << PKC_ACCESS_ERR_RESERVED0_Pos)                /*!< PKC_ACCESS_ERR: RESERVED0 Mask          */
#define PKC_ACCESS_ERR_APB_MASTER_Pos         4                                                       /*!< PKC_ACCESS_ERR: APB_MASTER Position     */
#define PKC_ACCESS_ERR_APB_MASTER_Msk         (0x0fUL << PKC_ACCESS_ERR_APB_MASTER_Pos)               /*!< PKC_ACCESS_ERR: APB_MASTER Mask         */
#define PKC_ACCESS_ERR_RESERVED1_Pos          8                                                       /*!< PKC_ACCESS_ERR: RESERVED1 Position      */
#define PKC_ACCESS_ERR_RESERVED1_Msk          (0x03UL << PKC_ACCESS_ERR_RESERVED1_Pos)                /*!< PKC_ACCESS_ERR: RESERVED1 Mask          */
#define PKC_ACCESS_ERR_AHB_Pos                10                                                      /*!< PKC_ACCESS_ERR: AHB Position            */
#define PKC_ACCESS_ERR_AHB_Msk                (0x01UL << PKC_ACCESS_ERR_AHB_Pos)                      /*!< PKC_ACCESS_ERR: AHB Mask                */
#define PKC_ACCESS_ERR_RESERVED2_Pos          11                                                      /*!< PKC_ACCESS_ERR: RESERVED2 Position      */
#define PKC_ACCESS_ERR_RESERVED2_Msk          (0x1fUL << PKC_ACCESS_ERR_RESERVED2_Pos)                /*!< PKC_ACCESS_ERR: RESERVED2 Mask          */
#define PKC_ACCESS_ERR_PKCC_Pos               16                                                      /*!< PKC_ACCESS_ERR: PKCC Position           */
#define PKC_ACCESS_ERR_PKCC_Msk               (0x01UL << PKC_ACCESS_ERR_PKCC_Pos)                     /*!< PKC_ACCESS_ERR: PKCC Mask               */
#define PKC_ACCESS_ERR_FDET_Pos               17                                                      /*!< PKC_ACCESS_ERR: FDET Position           */
#define PKC_ACCESS_ERR_FDET_Msk               (0x01UL << PKC_ACCESS_ERR_FDET_Pos)                     /*!< PKC_ACCESS_ERR: FDET Mask               */
#define PKC_ACCESS_ERR_CTRL_Pos               18                                                      /*!< PKC_ACCESS_ERR: CTRL Position           */
#define PKC_ACCESS_ERR_CTRL_Msk               (0x01UL << PKC_ACCESS_ERR_CTRL_Pos)                     /*!< PKC_ACCESS_ERR: CTRL Mask               */
#define PKC_ACCESS_ERR_UCRC_Pos               19                                                      /*!< PKC_ACCESS_ERR: UCRC Position           */
#define PKC_ACCESS_ERR_UCRC_Msk               (0x01UL << PKC_ACCESS_ERR_UCRC_Pos)                     /*!< PKC_ACCESS_ERR: UCRC Mask               */
#define PKC_ACCESS_ERR_RESERVED3_Pos          20                                                      /*!< PKC_ACCESS_ERR: RESERVED3 Position      */
#define PKC_ACCESS_ERR_RESERVED3_Msk          (0x01UL << PKC_ACCESS_ERR_RESERVED3_Pos)                /*!< PKC_ACCESS_ERR: RESERVED3 Mask          */
#define PKC_ACCESS_ERR_RESERVED4_Pos          21                                                      /*!< PKC_ACCESS_ERR: RESERVED4 Position      */
#define PKC_ACCESS_ERR_RESERVED4_Msk          (0x000007ffUL << PKC_ACCESS_ERR_RESERVED4_Pos)          /*!< PKC_ACCESS_ERR: RESERVED4 Mask          */

/* =============================== PKC_ACCESS_ERR_CLR ============================== */
#define PKC_ACCESS_ERR_CLR_ERR_CLR_Pos        0                                                       /*!< PKC_ACCESS_ERR_CLR: ERR_CLR Position    */
#define PKC_ACCESS_ERR_CLR_ERR_CLR_Msk        (0x01UL << PKC_ACCESS_ERR_CLR_ERR_CLR_Pos)              /*!< PKC_ACCESS_ERR_CLR: ERR_CLR Mask        */
#define PKC_ACCESS_ERR_CLR_RESERVED_Pos       1                                                       /*!< PKC_ACCESS_ERR_CLR: RESERVED Position   */
#define PKC_ACCESS_ERR_CLR_RESERVED_Msk       (0x7fffffffUL << PKC_ACCESS_ERR_CLR_RESERVED_Pos)       /*!< PKC_ACCESS_ERR_CLR: RESERVED Mask       */

/* =============================== PKC_INT_CLR_ENABLE ============================== */
#define PKC_INT_CLR_ENABLE_EN_PDONE_Pos       0                                                       /*!< PKC_INT_CLR_ENABLE: EN_PDONE Position   */
#define PKC_INT_CLR_ENABLE_EN_PDONE_Msk       (0x01UL << PKC_INT_CLR_ENABLE_EN_PDONE_Pos)             /*!< PKC_INT_CLR_ENABLE: EN_PDONE Mask       */
#define PKC_INT_CLR_ENABLE_RESERVED0_Pos      1                                                       /*!< PKC_INT_CLR_ENABLE: RESERVED0 Position  */
#define PKC_INT_CLR_ENABLE_RESERVED0_Msk      (0x01UL << PKC_INT_CLR_ENABLE_RESERVED0_Pos)            /*!< PKC_INT_CLR_ENABLE: RESERVED0 Mask      */
#define PKC_INT_CLR_ENABLE_RESERVED1_Pos      2                                                       /*!< PKC_INT_CLR_ENABLE: RESERVED1 Position  */
#define PKC_INT_CLR_ENABLE_RESERVED1_Msk      (0x3fffffffUL << PKC_INT_CLR_ENABLE_RESERVED1_Pos)      /*!< PKC_INT_CLR_ENABLE: RESERVED1 Mask      */

/* =============================== PKC_INT_SET_ENABLE ============================== */
#define PKC_INT_SET_ENABLE_EN_PDONE_Pos       0                                                       /*!< PKC_INT_SET_ENABLE: EN_PDONE Position   */
#define PKC_INT_SET_ENABLE_EN_PDONE_Msk       (0x01UL << PKC_INT_SET_ENABLE_EN_PDONE_Pos)             /*!< PKC_INT_SET_ENABLE: EN_PDONE Mask       */
#define PKC_INT_SET_ENABLE_RESERVED0_Pos      1                                                       /*!< PKC_INT_SET_ENABLE: RESERVED0 Position  */
#define PKC_INT_SET_ENABLE_RESERVED0_Msk      (0x01UL << PKC_INT_SET_ENABLE_RESERVED0_Pos)            /*!< PKC_INT_SET_ENABLE: RESERVED0 Mask      */
#define PKC_INT_SET_ENABLE_RESERVED1_Pos      2                                                       /*!< PKC_INT_SET_ENABLE: RESERVED1 Position  */
#define PKC_INT_SET_ENABLE_RESERVED1_Msk      (0x3fffffffUL << PKC_INT_SET_ENABLE_RESERVED1_Pos)      /*!< PKC_INT_SET_ENABLE: RESERVED1 Mask      */

/* ===============================   PKC_INT_STATUS  ============================== */
#define PKC_INT_STATUS_INT_PDONE_Pos          0                                                       /*!< PKC_INT_STATUS: INT_PDONE Position      */
#define PKC_INT_STATUS_INT_PDONE_Msk          (0x01UL << PKC_INT_STATUS_INT_PDONE_Pos)                /*!< PKC_INT_STATUS: INT_PDONE Mask          */
#define PKC_INT_STATUS_RESERVED0_Pos          1                                                       /*!< PKC_INT_STATUS: RESERVED0 Position      */
#define PKC_INT_STATUS_RESERVED0_Msk          (0x01UL << PKC_INT_STATUS_RESERVED0_Pos)                /*!< PKC_INT_STATUS: RESERVED0 Mask          */
#define PKC_INT_STATUS_RESERVED1_Pos          2                                                       /*!< PKC_INT_STATUS: RESERVED1 Position      */
#define PKC_INT_STATUS_RESERVED1_Msk          (0x3fffffffUL << PKC_INT_STATUS_RESERVED1_Pos)          /*!< PKC_INT_STATUS: RESERVED1 Mask          */

/* ===============================   PKC_INT_ENABLE  ============================== */
#define PKC_INT_ENABLE_EN_PDONE_Pos           0                                                       /*!< PKC_INT_ENABLE: EN_PDONE Position       */
#define PKC_INT_ENABLE_EN_PDONE_Msk           (0x01UL << PKC_INT_ENABLE_EN_PDONE_Pos)                 /*!< PKC_INT_ENABLE: EN_PDONE Mask           */
#define PKC_INT_ENABLE_RESERVED0_Pos          1                                                       /*!< PKC_INT_ENABLE: RESERVED0 Position      */
#define PKC_INT_ENABLE_RESERVED0_Msk          (0x01UL << PKC_INT_ENABLE_RESERVED0_Pos)                /*!< PKC_INT_ENABLE: RESERVED0 Mask          */
#define PKC_INT_ENABLE_RESERVED1_Pos          2                                                       /*!< PKC_INT_ENABLE: RESERVED1 Position      */
#define PKC_INT_ENABLE_RESERVED1_Msk          (0x3fffffffUL << PKC_INT_ENABLE_RESERVED1_Pos)          /*!< PKC_INT_ENABLE: RESERVED1 Mask          */

/* =============================== PKC_INT_CLR_STATUS ============================== */
#define PKC_INT_CLR_STATUS_INT_PDONE_Pos      0                                                       /*!< PKC_INT_CLR_STATUS: INT_PDONE Position  */
#define PKC_INT_CLR_STATUS_INT_PDONE_Msk      (0x01UL << PKC_INT_CLR_STATUS_INT_PDONE_Pos)            /*!< PKC_INT_CLR_STATUS: INT_PDONE Mask      */
#define PKC_INT_CLR_STATUS_RESERVED0_Pos      1                                                       /*!< PKC_INT_CLR_STATUS: RESERVED0 Position  */
#define PKC_INT_CLR_STATUS_RESERVED0_Msk      (0x01UL << PKC_INT_CLR_STATUS_RESERVED0_Pos)            /*!< PKC_INT_CLR_STATUS: RESERVED0 Mask      */
#define PKC_INT_CLR_STATUS_RESERVED1_Pos      2                                                       /*!< PKC_INT_CLR_STATUS: RESERVED1 Position  */
#define PKC_INT_CLR_STATUS_RESERVED1_Msk      (0x3fffffffUL << PKC_INT_CLR_STATUS_RESERVED1_Pos)      /*!< PKC_INT_CLR_STATUS: RESERVED1 Mask      */

/* =============================== PKC_INT_SET_STATUS ============================== */
#define PKC_INT_SET_STATUS_INT_PDONE_Pos      0                                                       /*!< PKC_INT_SET_STATUS: INT_PDONE Position  */
#define PKC_INT_SET_STATUS_INT_PDONE_Msk      (0x01UL << PKC_INT_SET_STATUS_INT_PDONE_Pos)            /*!< PKC_INT_SET_STATUS: INT_PDONE Mask      */
#define PKC_INT_SET_STATUS_RESERVED0_Pos      1                                                       /*!< PKC_INT_SET_STATUS: RESERVED0 Position  */
#define PKC_INT_SET_STATUS_RESERVED0_Msk      (0x01UL << PKC_INT_SET_STATUS_RESERVED0_Pos)            /*!< PKC_INT_SET_STATUS: RESERVED0 Mask      */
#define PKC_INT_SET_STATUS_RESERVED1_Pos      2                                                       /*!< PKC_INT_SET_STATUS: RESERVED1 Position  */
#define PKC_INT_SET_STATUS_RESERVED1_Msk      (0x3fffffffUL << PKC_INT_SET_STATUS_RESERVED1_Pos)      /*!< PKC_INT_SET_STATUS: RESERVED1 Mask      */

/* ===============================   PKC_MODULE_ID   ============================== */
#define PKC_MODULE_ID_SIZE_Pos                0                                                       /*!< PKC_MODULE_ID: SIZE Position            */
#define PKC_MODULE_ID_SIZE_Msk                (0x000000ffUL << PKC_MODULE_ID_SIZE_Pos)                /*!< PKC_MODULE_ID: SIZE Mask                */
#define PKC_MODULE_ID_MINOR_REV_Pos           8                                                       /*!< PKC_MODULE_ID: MINOR_REV Position       */
#define PKC_MODULE_ID_MINOR_REV_Msk           (0x0fUL << PKC_MODULE_ID_MINOR_REV_Pos)                 /*!< PKC_MODULE_ID: MINOR_REV Mask           */
#define PKC_MODULE_ID_MAJOR_REV_Pos           12                                                      /*!< PKC_MODULE_ID: MAJOR_REV Position       */
#define PKC_MODULE_ID_MAJOR_REV_Msk           (0x0fUL << PKC_MODULE_ID_MAJOR_REV_Pos)                 /*!< PKC_MODULE_ID: MAJOR_REV Mask           */
#define PKC_MODULE_ID_ID_Pos                  16                                                      /*!< PKC_MODULE_ID: ID Position              */
#define PKC_MODULE_ID_ID_Msk                  (0x0000ffffUL << PKC_MODULE_ID_ID_Pos)                  /*!< PKC_MODULE_ID: ID Mask                  */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

//#define PKC_BASE                        0x50031000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

//#define PKC                             ((PKC_Type                *) PKC_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group CoSimPKC */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* CoSimPKC_H */
