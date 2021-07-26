/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_rdc.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

/* Initialize MPU, configure memory attributes for each region */
void BOARD_InitMemory(void)
{
    /* __CACHE_REGION_START and __CACHE_REGION_SIZE are defined in the linker file */
    extern uint32_t __CACHE_REGION_START[];
    extern uint32_t __CACHE_REGION_SIZE[];
    uint32_t cacheStart = (uint32_t)__CACHE_REGION_START;
    uint32_t size       = (uint32_t)__CACHE_REGION_SIZE;
    uint32_t i          = 0;

    /* Disable I cache and D cache */
    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_DisableICache();
    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        SCB_DisableDCache();
    }

    /* Disable MPU */
    ARM_MPU_Disable();

    /* MPU configure:
     * Use ARM_MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable,
     * SubRegionDisable, Size)
     * API in mpu_armv7.h.
     * param DisableExec       Instruction access (XN) disable bit,0=instruction fetches enabled, 1=instruction fetches
     * disabled.
     * param AccessPermission  Data access permissions, allows you to configure read/write access for User and
     * Privileged mode.
     *      Use MACROS defined in mpu_armv7.h:
     * ARM_MPU_AP_NONE/ARM_MPU_AP_PRIV/ARM_MPU_AP_URO/ARM_MPU_AP_FULL/ARM_MPU_AP_PRO/ARM_MPU_AP_RO
     * Combine TypeExtField/IsShareable/IsCacheable/IsBufferable to configure MPU memory access attributes.
     *  TypeExtField  IsShareable  IsCacheable  IsBufferable   Memory Attribtue    Shareability        Cache
     *     0             x           0           0             Strongly Ordered    shareable
     *     0             x           0           1              Device             shareable
     *     0             0           1           0              Normal             not shareable   Outer and inner write
     * through no write allocate
     *     0             0           1           1              Normal             not shareable   Outer and inner write
     * back no write allocate
     *     0             1           1           0              Normal             shareable       Outer and inner write
     * through no write allocate
     *     0             1           1           1              Normal             shareable       Outer and inner write
     * back no write allocate
     *     1             0           0           0              Normal             not shareable   outer and inner
     * noncache
     *     1             1           0           0              Normal             shareable       outer and inner
     * noncache
     *     1             0           1           1              Normal             not shareable   outer and inner write
     * back write/read acllocate
     *     1             1           1           1              Normal             shareable       outer and inner write
     * back write/read acllocate
     *     2             x           0           0              Device              not shareable
     *  Above are normal use settings, if your want to see more details or want to config different inner/outter cache
     * policy.
     *  please refer to Table 4-55 /4-56 in arm cortex-M7 generic user guide <dui0646b_cortex_m7_dgug.pdf>
     * param SubRegionDisable  Sub-region disable field. 0=sub-region is enabled, 1=sub-region is disabled.
     * param Size              Region size of the region to be configured. use ARM_MPU_REGION_SIZE_xxx MACRO in
     * mpu_armv7.h.
     */

    /* Region 0 [0x0000_0000 - 0x4000_0000] : Memory with Device type, not executable, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(1, ARM_MPU_AP_FULL, 0, 0, 0, 1, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 1 TCML[0x0000_0000 - 0x0001_FFFF]: Memory with Normal type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 2 QSPI[0x0800_0000 - 0x0FFF_FFFF]: Memory with Normal type, not shareable, cacheable */
    MPU->RBAR = ARM_MPU_RBAR(2, 0x08000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128MB);

    /* Region 3 TCMU[0x2000_0000 - 0x2002_0000]: Memory with Normal type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 4 DDR[0x4000_0000 - 0x8000_0000]: Memory with Normal type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(4, 0x40000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /*
       Non-cacheable area is provided in DDR memory, the DDR region [0x80000000 ~ 0x81000000](please see the
       imx8mp-evk-rpmsg.dts) totally 16MB is revserved for CM7 core. You can put global or static uninitialized
       variables in NonCacheable section(initialized variables in NonCacheable.init section) to make them uncacheable.
       Since the base address of MPU region should be multiples of region size, to make it simple, the MPU region 5 set
       the address space 0x80000000 ~ 0xBFFFFFFF to be non-cacheable. Then MPU region 6 set the text and data section to
       be cacheable if the program running on DDR. The cacheable area base address should be multiples of its size in
       linker file, they can be modified per your needs.
    */
    /* Region 5 DDR[0x8000_0000 - 0xBFFFFFFF]: Memory with Normal type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(5, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    while ((size >> i) > 0x1U)
    {
        i++;
    }
    /* If run on DDR, configure text and data section to be cacheable */
    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert((size & (size - 1)) == 0);
        assert(!(cacheStart % size));
        assert(size == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 6 DDR[cacheStart]: Memory with Normal type, not shareable, cacheable */
        MPU->RBAR = ARM_MPU_RBAR(6, cacheStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 1, 1, 0, (i - 1));
    }

    /*
     * Enable MPU and HFNMIENA feature
     * HFNMIENA ensures that M7 core uses MPU configuration when in hard fault, NMI, and FAULTMASK handlers,
     * otherwise all memory regions are accessed without MPU protection, which has high risks of cacheable,
     * especially for AIPS systems.
     */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);

    /* Enable I cache and D cache */
    SCB_EnableICache();
    SCB_EnableDCache();
}

void BOARD_RdcInit(void)
{
    /* Move M7 core to specific RDC domain 1 */
    rdc_domain_assignment_t assignment = {0};
    uint8_t domainId                   = 0U;

    domainId = RDC_GetCurrentMasterDomainId(RDC);
    /* Only configure the RDC if RDC peripheral write access allowed. */
    if ((0x1U & RDC_GetPeriphAccessPolicy(RDC, kRDC_Periph_RDC, domainId)) != 0U)
    {
        assignment.domainId = BOARD_DOMAIN_ID;
        RDC_SetMasterDomainAssignment(RDC, kRDC_Master_M7, &assignment);
    }

    /*
     * The M7 core is running at domain 1, now enable the clock gate of the following IP/BUS/PLL in domain 1 in the CCM.
     * In this way, to ensure the clock of the peripherals used by M core not be affected by A core which is running at
     * domain 0.
     */
    CLOCK_EnableClock(kCLOCK_Iomux);

    CLOCK_EnableClock(kCLOCK_Ipmux1);
    CLOCK_EnableClock(kCLOCK_Ipmux2);
    CLOCK_EnableClock(kCLOCK_Ipmux3);

#if defined(FLASH_TARGET)
    CLOCK_EnableClock(kCLOCK_Qspi);
#endif

    CLOCK_ControlGate(kCLOCK_SysPll1Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL1 in Domain 1 */
    CLOCK_ControlGate(kCLOCK_SysPll2Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL2 in Domain 1 */
    CLOCK_ControlGate(kCLOCK_SysPll3Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL3 in Domain 1 */
    CLOCK_ControlGate(kCLOCK_AudioPll1Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for AudioPLL1 in Domain 1 */
    CLOCK_ControlGate(kCLOCK_AudioPll2Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for AudioPLL2 in Domain 1 */
    CLOCK_ControlGate(kCLOCK_VideoPll1Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for VideoPLL1 in Domain 1 */
}
