/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.macro	ventry	label
	.align	7
	b	\label
.endm

.macro	_eentry from type
	stp	x29, x30, [sp, #-0x10]!
	stp	x27, x28, [sp, #-0x10]!
	stp	x25, x26, [sp, #-0x10]!
	stp	x23, x24, [sp, #-0x10]!
	stp	x21, x22, [sp, #-0x10]!
	stp	x19, x20, [sp, #-0x10]!
	stp	x17, x18, [sp, #-0x10]!
	stp	x15, x16, [sp, #-0x10]!
	stp	x13, x14, [sp, #-0x10]!
	stp	x11, x12, [sp, #-0x10]!
	stp	x9, x10, [sp, #-0x10]!
	stp	x7, x8, [sp, #-0x10]!
	stp	x5, x6, [sp, #-0x10]!
	stp	x3, x4, [sp, #-0x10]!
	stp	x1, x2, [sp, #-0x10]!
	str	x0, [sp, #-0x8]!
	mov	x0, #\from
	mov	x1, #\type
	mov	x2, sp
	bl	exception_handler
	b	.
.endm

.macro sentry label from
	.align 7
	str	x0, [sp, #-0x8]!
	mrs	x0, esr_el1
	lsr	x0, x0, #26	/* Exception Class */
	cmp	x0, #0x15	/* SVC */
	ldr	x0, [sp, #0x8]!
	b.eq	\label
	_eentry	\from 0
.endm

.macro	eentry from type
	.align	7
	_eentry	\from \type
.endm

	.section ".boot", "ax"
	.globl Reset_Handler
Reset_Handler:
	mrs	x0, CurrentEL
	cmp	x0, 0xc
	beq	3f
	cmp	x0, 0x8
	beq	2f
	cmp	x0, 0x4
	beq	1f
3:
	/* Run from EL3 */
	/* Current not supported */
	b	.
2:
	/* Run from EL2 */
	mrs	x0, sctlr_el2
	orr	x0, x0, #(0x1 << 12) /* I: I Cache */
	orr	x0, x0, #(0x1 << 3) /* SA: SP Alignment Check*/
	msr	sctlr_el2, x0

	mrs	x0, hcr_el2
	orr	x0, x0, #(0x1 << 31) /*RW: EL1 Execution state is AArch64 */
	msr     hcr_el2, x0

	mov	x0, #(0x32ff) /* Do not trap SVE, SIMD and FP, Do not trap CPACR_EL1 accesses */
	msr	cptr_el2, x0

	/* Set 64-bit virtual timer offset to 0 */
	msr	cntvoff_el2, xzr
	msr	cnthctl_el2, xzr
	msr	cnthp_ctl_el2, xzr

	/* Move to EL1 with all exceptions masked */
	mov	x0, (0xf << 6 | 0x4)
	msr	spsr_el2, x0

	adr	x0, 1f
	msr	elr_el2, x0
	eret
1:
	ldr	x0, =vectors
	msr	vbar_el1, x0

	/*
	 * Mask all exceptions until _freertos_vector_table is registered,
	 * after vTaskStartScheduler() is called
	 */
	msr	DAIFSet, #0xf

	/* Disable alignment fault checking */
	mrs	x0, sctlr_el1
	bic	x0, x0, #(0x1 << 1) /* SCTLR_A_BIT */
	orr	x0, x0, #(0x1 << 2) /* SCTLR_C_BIT: data cache ON */
	orr	x0, x0, #(0x1 << 12) /* SCTLR_I_BIT: instr cache ON */
	msr	sctlr_el1, x0

	# set the stack pointer for EL0
	msr	SPSel, #0
	ldr	x0, =__el0_stack
	mov	sp, x0

	isb

	# set the stack pointer for EL1
	msr	SPSel, #1
	ldr	x0, =__el1_stack
	mov	sp, x0

#ifndef __NO_SYSTEM_INIT
	bl	SystemInit
#endif

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __data_load__: End of code section, i.e., begin of data sections to copy from.
 *      __noncachedata_start__/__noncachedata_end__ : none cachable region
 *      __data_start__/__data_init_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 64-byte boundary.  */

	ldr	x1, =__data_load__
	ldr	x2, =__data_start__
	ldr	x3, =__data_init_end__

/* Here is an implementation that favors performance over code size. */
	subs	x3, x3, x2
	ble	.LC1
.LC0:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC0
.LC1:
#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
	ldr	x1, =__noncachedata_load__
	ldr	x2, =__noncachedata_start__
	ldr	x3, =__noncachedata_init_end__
/* Here is an implementation that favors performance over code size. */
	subs	x3, x3, x2
	ble	.LC3
.LC2:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC2
.LC3:
/* zero init ncache data section */
	ldr	x0, =__noncachedata_init_end__
	ldr	x1, =__noncachedata_end__
	sub	x1, x1, x0
	cbz	x1, .L__noncachedata_cleared
.LC4:
	sub	x1, x1, #8
	str	xzr, [x0], #8
	cbnz	x1, .LC4
.L__noncachedata_cleared:
#endif /* __STARTUP_INITIALIZE_NONCACHEDATA */

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 8
 *      __bss_end__: end of BSS section. Must align to 8
 */
	ldr	x0, =__bss_start__
	ldr	x1, =__bss_end__
	sub	x1, x1, x0
	cbz	x1, .L__bss_cleared
.LC5:
	sub	x1, x1, #8
	str	xzr, [x0], #8
	cbnz	x1, .LC5
.L__bss_cleared:
#endif /* __STARTUP_CLEAR_BSS */

/* Copy OCRAM code from RO region to OCRAM */
	ldr	x1, =__ocramtext_load__
	ldr	x2, =__ocramtext_start__
	ldr	x3, =__ocramtext_init_end__

	subs	x3, x3, x2
	ble	.LC7
.LC6:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC6
	# TODO D-cache flush: make sure code relocation has reached memory
	# __flush_dcache_area(__ocramtext_start__, __ocramtext_init_end__ - __ocramtext_start__);
.LC7:

/* Copy OCRAM data from RO region to OCRAM */
	ldr	x1, =__ocramdata_load__
	ldr	x2, =__ocramdata_start__
	ldr	x3, =__ocramdata_init_end__

	subs	x3, x3, x2
	ble	.LC9
.LC8:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC8
.LC9:
/* zero init OCRAM bss */
	ldr	x0, =__ocramdata_init_end__
	ldr	x1, =__ocramdata_end__
	sub	x1, x1, x0
	cbz	x1, .L__ocramdata_cleared
.LC10:
	sub	x1, x1, #8
	str	xzr, [x0], #8
	cbnz	x1, .LC10
.L__ocramdata_cleared:

/* Copy ITCM code from RO region to ITCM */
	ldr	x1, =__itcm_load__
	ldr	x2, =__itcm_start__
	ldr	x3, =__itcm_init_end__

	subs	x3, x3, x2
	ble	.LC12
.LC11:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC11
	# TODO D-cache flush: make sure code relocation has reached memory
	# __flush_dcache_area(__itcm_start__, __itcm_init_end__ - __itcm_start__);
	ic	ialluis
	isb

.LC12:
	ic	ialluis
	isb

/* Copy DTCM data from RO region to DTCM */
	ldr	x1, =__dtcm_load__
	ldr	x2, =__dtcm_start__
	ldr	x3, =__dtcm_init_end__

	subs	x3, x3, x2
	ble	.LC14
.LC13:
	subs	x3, x3, #8
	ldr	x0, [x1, x3]
	str	x0, [x2, x3]
	bgt	.LC13
.LC14:
/* zero init DTCM bss */
	ldr	x0, =__dtcm_init_end__
	ldr	x1, =__dtcm_end__
	sub	x1, x1, x0
	cbz	x1, .L__dtcm_cleared
.LC15:
	sub	x1, x1, #8
	str	xzr, [x0], #8
	cbnz	x1, .LC15
.L__dtcm_cleared:

	isb

	b	main

	.ltorg

/*      Temporary vector table, used up to FreeRTOS vTaskStartScheduler() */
	.globl vectors
	.align 11
vectors:
	eentry	0 0
	eentry	0 1
	eentry	0 2
	eentry	0 3

	eentry	1 0
	eentry	1 1
	eentry	1 2
	eentry	1 3

	eentry	2 0
	eentry	2 1
	eentry	2 2
	eentry	2 3

	eentry	3 0
	eentry	3 1
	eentry	3 2
	eentry	3 3

	.ltorg

/*      FreeRTOS vector table used after FreeRTOS vTaskStartScheduler() is called */
	.globl _freertos_vector_table
	.align 11
_freertos_vector_table:
	sentry  FreeRTOS_SWI_Handler 0
	ventry	FreeRTOS_IRQ_Handler
	eentry	0 2
	eentry	0 3

	sentry	FreeRTOS_SWI_Handler 0
	ventry	FreeRTOS_IRQ_Handler
	eentry	1 2
	eentry	1 3

	eentry	2 0
	eentry	2 1
	eentry	2 2
	eentry	2 3

	eentry	3 0
	eentry	3 1
	eentry	3 2
	eentry	3 3
