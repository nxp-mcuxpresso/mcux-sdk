/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cmsis_compiler.h"
#include "fsl_debug_console.h"

__WEAK void putc(int c)
{
	PRINTF("%c", c);
}

__WEAK void puts(const char *s)
{
	PRINTF("%s", s);
}
__WEAK void put_hex(uint64_t v)
{
	PRINTF("0x%llx", v);
}
__WEAK void put_dec(uint64_t v)
{
	PRINTF("%lld", v);
}

struct exception_class_handler {
	const char *name;
	void (*handler)(uint32_t);
};

static const char *serror_str[] = {
	[0b0000] = "DECERR",
	[0b0001] = "L2 error",
	[0b0010] = "SLVERR",
	[0b0100] = "nSEI/nVSEI",
	[0b0101] = "nREI",
};

static void serror_handler(uint32_t iss)
{
	if (iss & (1 << 24)) {
		/* A53 specific decoding */
		uint8_t serror = ((iss >> 22) & 0x3) | (iss & 0x3);
		puts(": ");
		puts(serror_str[serror]);
		puts("\r\n");
	}
}

/* ARMv8-A Architecture Reference Manual, Table D1-6 */
static const struct exception_class_handler ec_handler[0x3f] = {
	[0b000000] = {"Unknown", },
	[0b000001] = {"Trapped WF*", },
	[0b000011] = {"Trapped MCR/MRC", },
	[0b000100] = {"Trapped MCRR/MRRC", },
	[0b000101] = {"Trapped MCR/MRC", },
	[0b000110] = {"Trapped LDC/STC", },
	[0b000111] = {"SVE", },
	[0b001000] = {"VMRS", },

	[0b001100] = {"Trapped MRRC", },
	[0b001110] = {"Illegal Execution state", },

	[0b100000] = {"Instruction Abort", },
	[0b100001] = {"Instruction Abort", },

	[0b100010] = {"PC alignment", },

	[0b100100] = {"Data Abort", },
	[0b100101] = {"Data Abort", },

	[0b100110] = {"SP alignment",},
	[0b101000] = {"FP AARCH32",},
	[0b101100] = {"FP AARCH64",},
	[0b101111] = {"Serror", serror_handler},
	[0b111000] = {"BRKPT AARCH32", },
	[0b111100] = {"BRK AARCH64", },
};

static const char *exception_from[] = {
	[0] = "Current level SP_EL0",
	[1] = "Current level SP_ELx",
	[2] = "Lower level, AArch64",
	[3] = "Lower level, AArch32",
};

static const char *exception_type[] = {
	[0] = "Synchronous",
	[1] = "IRQ/vIRQ",
	[2] = "FIQ/vFIQ",
	[3] = "Serror/vSerror",
};

static void dump_registers(uint64_t *regs)
{
	int i;

	puts("registers:\r\n");
	for (i = 0; i < 31; i++) {
		puts("x");
		put_dec(i);

		if (i < 10)
			puts(":  ");
		else
			puts(": ");

		put_hex(regs[i]);

		if (i & 0x1)
			puts("\r\n");
		else
			puts(" ");
	}
}

void exception_handler(uint64_t from, uint64_t type, uint64_t *sp)
{
	uint64_t sctlr_el1;
	uint64_t elr_el1;
	uint64_t esr_el1;
	uint64_t far_el1;
	uint32_t ec, iss;

	__MRS(ELR_EL1, &elr_el1);
	__MRS(FAR_EL1, &far_el1);
	__MRS(ESR_EL1, &esr_el1);
	__MRS(SCTLR_EL1, &sctlr_el1);

	ec = (esr_el1 >> 26) & 0x3f;
	iss = esr_el1 & 0x1ffffff;

	puts("\r\nException: ");
	puts(exception_type[type]);
	puts("\r\nFrom: ");
	puts(exception_from[from]);
	puts("\r\nClass: ");
	if (ec_handler[ec].name)
		puts(ec_handler[ec].name);

	puts("\r\nelr: ");
	put_hex(elr_el1);

	puts("\r\nfar: ");
	put_hex(far_el1);

	puts("\r\nesr: ");
	put_hex(esr_el1);

	puts("\r\nsctlr: ");
	put_hex(sctlr_el1);

	puts("\r\n");

	if (ec_handler[ec].handler)
		ec_handler[ec].handler(iss);

	dump_registers(sp);
}
