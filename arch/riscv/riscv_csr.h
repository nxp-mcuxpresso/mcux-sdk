/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_CSR_H_
#define RISCV_CSR_H_

/*!
 * @ingroup RISCV_CoreFunc
 * @defgroup RISCV_CoreCSR Definition For CSR register
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* ====================== CSR register definition ============================*/

/*!
 * @name Unprivileged User-Level
 * @{
 */

/* Unprivileged Floating-Point CSRs */
#define CSR_FFLAGS 0x001 /*!< Floating-Point Accrued Exceptions. */
#define CSR_FRM    0x002 /*!< Floating-Point Dynamic Rounding Mode. */
#define CSR_FCSR   0x003 /*!< Floating-Point Control and Status Register (frm + fflags). */

/* Unprivileged Counter/Timers */
#define CSR_CYCLE            0xC00         /*!< Cycle counter for RDCYCLE instruction. */
#define CSR_TIME             0xC01         /*!< Timer for RDTIME instruction. */
#define CSR_INSTRET          0xC02         /*!< Instructions-retired counter for RDINSTRET instruction. */
#define CSR_HPMCOUNTERn(n)   (0xC00 + (n)) /*!< Performance-monitoring counter, n in range 3~31. */
#define CSR_CYCLEH           0xC80         /*!< Upper 32 bits of cycle, RV32 only. */
#define CSR_TIMEH            0xC81         /*!< Upper 32 bits of time, RV32 only. */
#define CSR_INSTRETH         0xC82         /*!< Upper 32 bits of instret, RV32 only. */
#define CSR_HPMCOUNTERHn(n)  (0xC80 + (n)) /*!< Upper 32 bits of CSR_HPMCOUNTERn, n in range 3~31. */

/* --------------------------- Supervisor Level ------------------------------*/
/* Supervisor Trap Setup */
#define CSR_SSTATUS          0x100 /*!< Supervisor status register. */
#define CSR_SIE              0x104 /*!< Supervisor interrupt-enable register. */
#define CSR_STVEC            0x105 /*!< Supervisor trap handler base address. */
#define CSR_SCOUNTEREN       0x106 /*!< Supervisor counter enable. */

/* Supervisor Configuration */
#define CSR_SENVCFG          0x10A /*!< Supervisor environment confi guration register. */

/* Supervisor Trap Handling */
#define CSR_SSCRATCH         0x140 /*!< Scratch register for supervisor trap handlers. */
#define CSR_SEPC             0x141 /*!< Supervisor exception program counter. */
#define CSR_SCAUSE           0x142 /*!< Supervisor trap cause. */
#define CSR_STVAL            0x143 /*!< Supervisor bad address or instruction. */
#define CSR_SIP              0x144 /*!< Supervisor interrupt pending. */

/* Supervisor Protection and Translation */
#define CSR_SATP             0x180 /*!< Supervisor address translation and protection. */

/* Debug/Trace Registers */
#define CSR_SCONTEXT         0x5A8 /*!< Supervisor-mode context register. */

/*!
 * @}
 */

/*!
 * @name Hypervisor Level
 * @{
 */

/* Hypervisor Trap Setup */
#define CSR_HSTATUS          0x600 /*!< Hypervisor status register. */
#define CSR_HEDELEG          0x602 /*!< Hypervisor exception delegation register. */
#define CSR_HIDELEG          0x603 /*!< Hypervisor interrupt delegation register. */
#define CSR_HIE              0x604 /*!< Hypervisor interrupt-enable register. */
#define CSR_HCOUNTEREN       0x606 /*!< Hypervisor counter enable. */
#define CSR_HGEIE            0x607 /*!< Hypervisor guest external interrupt-enable register. */

/* Hypervisor Trap Handling */
#define CSR_HTVAL            0x643 /*!< Hypervisor bad guest physical address. */
#define CSR_HIP              0x644 /*!< Hypervisor interrupt pending. */
#define CSR_HVIP             0x645 /*!< Hypervisor virtual interrupt pending. */
#define CSR_HTINST           0x64A /*!< Hypervisor trap instruction (transformed). */
#define CSR_HGEIP            0xE12 /*!< Hypervisor guest external interrupt pending. */

/* Hypervisor Confi guration */
#define CSR_HENVCFG          0x60A /*!< Hypervisor environment confi guration register. */
#define CSR_HENVCFGH         0x61A /*!< Additional hypervisor env. conf. register, RV32 only. */

/* Hypervisor Protection and Translation */
#define CSR_HGATP            0x680 /*!< Hypervisor guest address translation and protection. */

/* Debug/Trace Registers */
#define CSR_HCONTEXT         0x6A8 /*!< Hypervisor-mode context register. */

/* Hypervisor Counter/Timer Virtualization Registers */
#define CSR_HTIMEDELTA       0x605 /*!< Delta for VS/VU-mode timer. */
#define CSR_HTIMEDELTAH      0x615 /*!< Upper 32 bits of htimedelta, HSXLEN=32 only. */

/* Virtual Supervisor Registers */
#define CSR_VSSTATUS         0x200 /*!< Virtual supervisor status register. */
#define CSR_VSIE             0x204 /*!< Virtual supervisor interrupt-enable register. */
#define CSR_VSTVEC           0x205 /*!< Virtual supervisor trap handler base address. */
#define CSR_VSSCRATCH        0x240 /*!< Virtual supervisor scratch register. */
#define CSR_VSEPC            0x241 /*!< Virtual supervisor exception program counter. */
#define CSR_VSCAUSE          0x242 /*!< Virtual supervisor trap cause. */
#define CSR_VSTVAL           0x243 /*!< Virtual supervisor bad address or instruction. */
#define CSR_VSIP             0x244 /*!< Virtual supervisor interrupt pending. */
#define CSR_VSATP            0x280 /*!< Virtual supervisor address translation and protection. */

/*!
 * @}
 */

/*!
 * @name Machine Level
 * @{
 */

/* Machine Information Registers */
#define CSR_MVENDORID        0xF11 /*!< Vendor ID. */
#define CSR_MARCHID          0xF12 /*!< Architecture ID. */
#define CSR_MIMPID           0xF13 /*!< Implementation ID. */
#define CSR_MHARTID          0xF14 /*!< Hardware thread ID. */
#define CSR_MCONFIGPTR       0xF15 /*!< Pointer to confi guration data structure. */

/* Machine Trap Setup */
#define CSR_MSTATUS          0x300 /*!< Machine status register. */
#define CSR_MISA             0x301 /*!< ISA and extensions */
#define CSR_MEDELEG          0x302 /*!< Machine exception delegation register. */
#define CSR_MIDELEG          0x303 /*!< Machine interrupt delegation register. */
#define CSR_MIE              0x304 /*!< Machine interrupt-enable register. */
#define CSR_MTVEC            0x305 /*!< Machine trap-handler base address. */
#define CSR_MCOUNTEREN       0x306 /*!< Machine counter enable. */
#define CSR_MSTATUSH         0x310 /*!< Additional machine status register, RV32 only. */

/* Machine Trap Handling */
#define CSR_MSCRATCH         0x340 /*!< Scratch register for machine trap handlers. */
#define CSR_MEPC             0x341 /*!< Machine exception program counter. */
#define CSR_MCAUSE           0x342 /*!< Machine trap cause. */
#define CSR_MTVAL            0x343 /*!< Machine bad address or instruction. */
#define CSR_MIP              0x344 /*!< Machine interrupt pending. */
#define CSR_MTINST           0x34A /*!< Machine trap instruction (transformed). */
#define CSR_MTVAL2           0x34B /*!< Machine bad guest physical address. */

/* Machine Configuration */
#define CSR_MENVCFG          0x30A /*!< Machine environmentconfi guration register. */
#define CSR_MENVCFGH         0x31A /*!< Additional machine env. conf. register, RV32 only. */
#define CSR_MSECCFG          0x747 /*!< Machine security confi guration register. */
#define CSR_MSECCFGH         0x757 /*!< Additional machine security conf. register, RV32 only. */

/* Machine Memory Protection */
#define CSR_PMPCFGn(n)       (0x3A0 + (n)) /*!< Physical memory protection configuration, n in range of 0-15, odd value is for RV32 only. */
#define CSR_PMPADDRn(n)      (0x3B0 + (n)) /*!< Physical memory protection address register, n in range of 0-63. */

/* Machine Counter/Timers */
#define CSR_MCYCLE           0xB00         /*!< Machine cycle counter. */
#define CSR_MINSTRET         0xB02         /*!< Machine instructions-retired counter. */
#define CSR_MHPMCOUNTERn     (0xB00 + (n)) /*!< Machine performance-monitoring counter, n in range of 3-31. */
#define CSR_MCYCLEH          0xB80         /*!< Upper 32 bits of mcycle, RV32 only. */
#define CSR_MINSTRETH        0xB82         /*!< Upper 32 bits of minstret, RV32 only. */
#define CSR_MHPMCOUNTERnH(n) (0xB80 +(n))  /*!< Upper 32 bits of mhpmcounter3, RV32 only, n in range of 3-31. */

/* Machine Counter Setup */
#define CSR_MCOUNTINHIBIT    0x320         /*!< Machine counter-inhibit register. */
#define CSR_MHPMEVENTn       (0x320 + (n)) /*!< Machine performance-monitoring event selector, n in range of 3-31. */

/* Debug/Trace Registers (shared with Debug Mode) */
#define CSR_TSELECT          0x7A0 /*!< Debug/Trace trigger register select. */
#define CSR_TDATA1           0x7A1 /*!< First Debug/Trace trigger data register. */
#define CSR_TDATA2           0x7A2 /*!< Second Debug/Trace trigger data register. */
#define CSR_TDATA3           0x7A3 /*!< Third Debug/Trace trigger data register. */
#define CSR_MCONTEXT         0x7A8 /*!< Machine-mode context register. */

/* Debug Mode Registers */
#define CSR_DCSR             0x7B0 /*!< Debug control and status register. */
#define CSR_DPC              0x7B1 /*!< Debug PC. */
#define CSR_DSCRATCH0        0x7B2 /*!< Debug scratch register 0. */
#define CSR_DSCRATCH1        0x7B3 /*!< Debug scratch register 1. */

/*!
 * @}
 */

/*!
 * @name CSR Register Bit Definitions
 * @{
 */

/* MCAUSE */
#define CSR_MCAUSE_INT       (1U << 31) /*!< Interrupt bit in MCAUSE */

/* MSTATUS bits. */
#define CSR_MSTATUS_SIE   (1U<<1)
#define CSR_MSTATUS_MIE   (1U<<3)
#define CSR_MSTATUS_SPIE  (1U<<5)
#define CSR_MSTATUS_MPIE  (1U<<7)
#define CSR_MSTATUS_SPP   (1U<<8)
#define CSR_MSTATUS_MPP   (3U<<11)
#define CSR_MSTATUS_MPRV  (1U<<17)
#define CSR_MSTATUS_SUM   (1U<<18)
#define CSR_MSTATUS_MXR   (1U<<19)
#define CSR_MSTATUS_TVM   (1U<<20)
#define CSR_MSTATUS_TW    (1U<<21)
#define CSR_MSTATUS_TSR   (1U<<22)
#define CSR_MSTATUS_SD    (1U<<31)

/* MIE bits. */
#define CSR_MIE_SSIE  (1U << 1)    /*!< enable S-mode software interrupt */
#define CSR_MIE_MSIE  (1U << 3)    /*!< enable M-mode software interrupt */
#define CSR_MIE_STIE  (1U << 5)    /*!< enable S-mode timer interrupt */
#define CSR_MIE_MTIE  (1U << 7)    /*!< enable M-mode timer interrupt */
#define CSR_MIE_SEIE  (1U << 9)    /*!< enable S-mode external interrupt */
#define CSR_MIE_MEIE  (1U << 11)   /*!< enable M-mode external interrupt */
#define CSR_MIE_MIEE  (1U << 17)   /*!< enable M-mode imprecise exception */

/*!
 * @}
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */ /* End of group RISCV_CoreCSR */

#endif /* RISCV_CSR_H_ */
