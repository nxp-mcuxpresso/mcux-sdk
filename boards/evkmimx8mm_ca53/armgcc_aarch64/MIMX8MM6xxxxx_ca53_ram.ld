/*
 * Copyright 2021-2022 NXP
 *
 * Abstract:
 * Linker file for the GNU C Compiler
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Entry Point */
ENTRY(Reset_Handler)

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x0400;
/*
 * Let's align the stack size on a page ; note that 2 stacks (for EL0 and El1)
 * are needed -> LENGTH(m_stacks) must fit two 4kB pages.
 */
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x1000;

/* Specify the memory areas */
MEMORY
{
  itcm                  (RX)  : ORIGIN = 0x007E0000, LENGTH = 0x00020000 /* 128 kB */
  dtcm                  (RW)  : ORIGIN = 0x00800000, LENGTH = 0x00020000 /* 128 kB */
  ocram_text            (RX)  : ORIGIN = 0x00900000, LENGTH = 0x00030000 /* 176 kB */
  ocram_data            (RW)  : ORIGIN = 0x00930000, LENGTH = 0x0002e000 /* 174 kB */
  ocram_stacks          (RW)  : ORIGIN = 0x0095E000, LENGTH = 0x00002000 /*  2 kB */
  m_interrupts          (RX)  : ORIGIN = 0x93C00000, LENGTH = 0x00002000 /*  8 kB */
  m_text                (RX)  : ORIGIN = 0x93C02000, LENGTH = 0x005FE000 /* ~6 MB */
  m_data                (RW)  : ORIGIN = 0x94200000, LENGTH = 0x00600000 /*  6 MB */
  m_data_nc             (RW)  : ORIGIN = 0x94800000, LENGTH = 0x00400000 /*  4 MB */
}

/* Define output sections */
SECTIONS
{
/* The startup code goes first into internal RAM */
  .interrupts :
  {
    . = ALIGN(64);
    KEEP(*(.boot))     /* Startup code */
  } > m_interrupts

  /* The program code and other data goes into internal RAM */
  .text :
  {
    . = ALIGN(64);
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    . = ALIGN(64);
    KEEP (*(.init))
    . = ALIGN(64);
    KEEP (*(.fini))
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
    . = ALIGN(64);
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
    . = ALIGN(64);
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
   . = ALIGN(64);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
   . = ALIGN(64);
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  .fini_array :
  {
   . = ALIGN(64);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
   . = ALIGN(4096);
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > m_text

  __text = ORIGIN(m_interrupts);
  __etext = .;    /* define a global symbol at end of code */

  .data :
  {
    __data_load__ = LOADADDR(.data);
    __data_start__ = .;      /* create a global symbol at data start */
    . = ALIGN(8);
    __data_init_end__ = .;        /* define a global symbol at data end */
  } > m_data AT > m_text

  __CACHE_REGION_START = ORIGIN(m_interrupts);
  __CACHE_REGION_SIZE  = 0;

  .ncache.init :
  {
    __noncachedata_load__ = LOADADDR(.ncache.init);
    __noncachedata_start__ = .;   /* create a global symbol at ncache data start */
    *(NonCacheable.init)
    . = ALIGN(8);
    __noncachedata_init_end__ = .;   /* create a global symbol at initialized ncache data end */
  } > m_data_nc AT > m_text

  .ncache :
  {
    *(NonCacheable)
    . = ALIGN(4096);
    __noncachedata_end__ = .;     /* define a global symbol at ncache data end */
  } > m_data_nc

  __DATA_END = __noncachedata_load__ + (__noncachedata_init_end__ - __noncachedata_start__);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(64);
    __START_BSS = .;
    __bss_start__ = .;
    *(COMMON)
    . = ALIGN(64);
    __bss_end__ = .;
    __END_BSS = .;
    . = ALIGN(4096);
    __data_end__ = .;
  } > m_data

  .itcm :
  {
    __itcm_load__ = LOADADDR(.itcm);
    . = ALIGN(4096);
    __itcm_start__ = .;
    /* insert here code that goes in ITCM */
    *tcm.c.obj(.text*)
    . = ALIGN(8);
    __itcm_init_end__ = .;
    . = ALIGN(4096);
    __itcm_end__ = .;
  } > itcm AT > m_text

  .dtcm :
  {
    __dtcm_load__ = LOADADDR(.dtcm);
    . = ALIGN(4096);
    __dtcm_start__ = .;
    /* insert here data that goes in DTCM */
    *tcm.c.obj(.data*)
    *tcm.c.obj(*.rodata)
    . = ALIGN(8);
    __dtcm_init_end__ = .;
  } > dtcm AT > m_text

  .dtcm_bss (NOLOAD):
  {
    /* insert here bss sections that go in OCRAM */
    *tcm.c.obj(.bss*)
    . = ALIGN(4096);
    __dtcm_end__ = .;
  } > dtcm

  .ocram_text :
  {
    __ocramtext_load__ = LOADADDR(.ocram_text);
    . = ALIGN(4096);
    __ocramtext_start__ = .;
    /* insert here code that goes in OCRAM */
    *(.text*)                 /* .text sections (code) */
    *(.text)                 /* .text sections (code) */
    *(.rodata)
    . = ALIGN(8);
    __ocramtext_init_end__ = .;
    . = ALIGN(4096);
    __ocramtext_end__ = .;
  } > ocram_text AT > m_text

  .ocram_data :
  {
    __ocramdata_load__ = LOADADDR(.ocram_data);
    . = ALIGN(4096);
    __ocramdata_start__ = .;
    /* insert here data that goes in OCRAM */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    . = ALIGN(8);
    __ocramdata_init_end__ = .;
  } > ocram_data AT > m_text

  .ocram_bss (NOLOAD):
  {
    /* insert here bss sections that go in OCRAM */
    *(.bss)
    *(.bss*)
    *ocram.c.obj(.bss*)
    . = ALIGN(4096);
  } > ocram_data

  .heap :
  {
    . = ALIGN(64);
    __end__ = .;
    PROVIDE(end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
    __heap_limit = .; /* Add for _sbrk */
    . = ALIGN(4096);
    __ocramdata_end__ = .;
  } > ocram_data

  /* Initializes stack on the end of block */

  .stack :
  {
    . = ALIGN(4096);
    __stacks_limit__ = .;
    _el1_stack_end = .;
    . += STACK_SIZE;
    . = ALIGN(64);
    __el1_stack = .;
    _el0_stack_end = .;
    . += STACK_SIZE;
    . = ALIGN(64);
    __el0_stack = .;
    . = ALIGN(4096);
    __stacks_top__ = .;
  } > ocram_stacks
}
