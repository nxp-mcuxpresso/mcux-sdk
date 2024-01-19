/*
** ###################################################################
**     Processors:          MIMX8UD7CVP08_cm33
**                          MIMX8UD7DVK08_cm33
**                          MIMX8UD7DVP08_cm33
**
**     Compiler:            GNU C Compiler
**     Reference manual:    IMX8ULPRM, Rev. D, December. 2022
**     Version:             rev. 5.0, 2023-04-27
**     Build:               b230927
**
**     Abstract:
**         Linker file for the GNU C Compiler
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/* Entry Point */
ENTRY(Reset_Handler)

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x0400;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x0400;
M_VECTOR_RAM_SIZE = DEFINED(__ram_vector_table__) ? 0x0320 : 0x0;

/* Memory region from [0x04000000-0x04000FFF] is reserved(1st Image Container Offset is 0x1000 = 4 KiB when boot device is FlexSPI NOR Flash) */
/*
 * Memory region from [0x04001000-0x04032000] is reserved for 1st Image Container and 2nd Image Container
 * - 1st Image Container: 1st container header + 1st signature block header + padding for 1 KiB alignment + sentinel firmware(maximum size = 128 KiB) = 2 KiB + 128 KiB = 130 KiB
 *
 * - 2nd Image Container: 2nd container header + 2nd signature block header + padding for 1 KiB alignment + upower firmware(maximum size = 64 KiB) = 2 KiB + 64 KiB = 66 KiB
 *
 * - flexspi0 start address = 0x4000000
 * entry point of m33 in flexspi0 nor flash = flexspi0 start address + 1st Image Container Offset + 1st Image Container size + 2nd Image Container size = 4 KiB + 130 KiB + 66 KiB = 200 KiB = 0x04032000
 * */
/* Memory region from [0x1FFC0000-0x1FFCFFFF] is reserved for shared memory between M33 and DSP. */
/* Memory region from [0x20008000-0x2002FFFF] is reserved for Fusion DSP */
/* Memory region from [0x20040000-0x2006FFFF] is reserved for A35 ATF */
/* Memory region from [0x20070000-0x2007FFFF] is reserved for ROM API and ROM boot */
/* Memory region(ssram) from [0x20030000-0x20037FFF](size is 32 KiB) is reserved for noncacheable data(such as: srcAddr, destAddr of dma3_scatter_gather demo, dma0 will access these non secure address) */

/* Specify the memory areas */
MEMORY
{
  m_interrupts          (RX)  : ORIGIN = 0x04032000, LENGTH = 0x00000320
  m_text                (RX)  : ORIGIN = 0x04032320, LENGTH = 0x003CDCE0
  m_data                (RW)  : ORIGIN = 0x0FFD0000, LENGTH = 0x00030000
  m_m33_suspend_ram     (RW)  : ORIGIN = 0x20000000, LENGTH = 0x00004000
  m_a35_suspend_ram     (RW)  : ORIGIN = 0x20004000, LENGTH = 0x00004000
  m_ncache              (RW)  : ORIGIN = 0x20030000, LENGTH = 0x00008000
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into internal flash */
  .interrupts :
  {
    __VECTOR_TABLE = .;
    __Vectors = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))     /* Startup code */
    . = ALIGN(4);
  } > m_interrupts

  __stext = .; /* start address of text section */
  .resource_table :
  {
    . = ALIGN(8);
    KEEP(*(.resource_table)) /* Resource table */
    . = ALIGN(8);
  } > m_text

  /* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(4);
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_flexspi.c.obj
        */fsl_lpspi.c.obj
    ) .text)                 /* .text sections (code) */
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_flexspi.c.obj
        */fsl_lpspi.c.obj
    ) .text*)                /* .text* sections (code) */
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_flexspi.c.obj
        */fsl_lpspi.c.obj
    ) .rodata)               /* .rodata sections (constants, strings, etc.) */
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_flexspi.c.obj
        */fsl_lpspi.c.obj
    ) .rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
  } > m_text

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > m_text

  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > m_text

 .ctors :
  {
    __CTOR_LIST__ = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text

  .dtors :
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > m_text

  __etext = .;    /* define a global symbol at end of code */
  __DATA_ROM = .; /* Symbol is used by startup for data initialization */

  .interrupts_ram :
  {
    . = ALIGN(4);
    __VECTOR_RAM__ = .;
    __interrupts_ram_start__ = .; /* Create a global symbol at data start */
    *(.m_interrupts_ram)     /* This is a user defined section */
    . += M_VECTOR_RAM_SIZE;
    . = ALIGN(4);
    __interrupts_ram_end__ = .; /* Define a global symbol at data end */
  } > m_data

  __VECTOR_RAM = DEFINED(__ram_vector_table__) ? __VECTOR_RAM__ : ORIGIN(m_interrupts);
  __RAM_VECTOR_TABLE_SIZE_BYTES = DEFINED(__ram_vector_table__) ? (__interrupts_ram_end__ - __interrupts_ram_start__) : 0x0;

  .data : AT(__DATA_ROM)
  {
    __data_start__ = .;      /* create a global symbol at data start */
    __quickaccess_start__ = .;
    . = ALIGN(16); /* the cache line size of D-Cache of Cortex-M33 is 16 bytes */
    *(CodeQuickAccess)
    /* Explicit placement of flash and frequently executed functions in RAM  */
    */fsl_flexspi.c.obj(.text .text* .rodata .rodata*)
    */fsl_lpspi.c.obj(.text .text* .rodata .rodata*)
    *(DataQuickAccess)
    . = ALIGN(16);
    __quickaccess_end__ = .;
    __DATA_RAM = .;
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    KEEP(*(.jcr*))
    . = ALIGN(4);
    __data_end__ = .;        /* define a global symbol at data end */
  } > m_data

  __NDATA_ROM = __DATA_ROM + SIZEOF(.data); /* Symbol is used by startup for ncache data initialization */
  .ncache.init : AT(__NDATA_ROM)
  {
    __noncachedata_start__ = .;   /* create a global symbol at ncache data start */
    *(NonCacheable.init)
    . = ALIGN(4);
    __noncachedata_init_end__ = .;   /* create a global symbol at initialized ncache data end */
  } > m_ncache

  . = __noncachedata_init_end__;
  .ncache :
  {
    *(NonCacheable)
    . = ALIGN(4);
    __noncachedata_end__ = .;     /* define a global symbol at ncache data end */
  } > m_ncache

  __DATA_END = __NDATA_ROM + SIZEOF(.ncache.init);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(4);
    __START_BSS = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __END_BSS = .;
  } > m_data

  .m33_suspend :
  {
    *(M33SuspendRam)
    . = ALIGN(4);
  } > m_m33_suspend_ram

  .heap :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
    __heap_limit = .; /* Add for _sbrk */
  } > m_data

  .stack :
  {
    . = ALIGN(8);
    . += STACK_SIZE;
  } > m_data

  /* Initializes stack on the end of block */
  __StackTop   = ORIGIN(m_data) + LENGTH(m_data);
  __StackLimit = __StackTop - STACK_SIZE;
  PROVIDE(__stack = __StackTop);

  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __HeapLimit, "region m_data overflowed with stack and heap")
}

