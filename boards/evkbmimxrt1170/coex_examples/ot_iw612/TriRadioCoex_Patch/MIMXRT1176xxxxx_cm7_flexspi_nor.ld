/*
** ###################################################################
**     Processors:          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176DVMAA_cm7
**
**     Compiler:            GNU C Compiler
**     Reference manual:    IMXRT1170RM, Rev 1, 02/2021
**     Version:             rev. 1.1, 2022-04-02
**     Build:               b220402
**
**     Abstract:
**         Linker file for the GNU C Compiler
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/* Entry Point */
ENTRY(Reset_Handler)

FLASH_START       = 0x30000000;
FLASH_SIZE        = 0xDC0000; /* 16 MBytes */
FLASH_END         = FLASH_START + FLASH_SIZE - 1;
FLASH_SECTOR_SIZE = 0x1000;  /* 4k flash sector size */

/*** FileSystem Configuration ***/
/* OT/Matter/BLE  filesystem configuration*/
NV_STORAGE_END_ADDRESS       = FLASH_END;
NV_STORAGE_MAX_SECTORS       = DEFINED(gNVMSectorCountLink_d) ? gNVMSectorCountLink_d : 32;
NV_STORAGE_SECTOR_SIZE       = FLASH_SECTOR_SIZE;
NV_STORAGE_SIZE              = FLASH_SECTOR_SIZE * NV_STORAGE_MAX_SECTORS;
NV_STORAGE_START_ADDRESS     = NV_STORAGE_END_ADDRESS - NV_STORAGE_SIZE + 1;
NV_STORAGE_START_ADDRESS_OFFSET = NV_STORAGE_START_ADDRESS - FLASH_START;

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x1000;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x1000;
VECTOR_RAM_SIZE = DEFINED(__ram_vector_table__) ? 0x00000400 : 0;
__NCACHE_REGION_START        = 0x00020000;
__NCACHE_REGION_SIZE         = 0x20000;

/* Specify the memory areas */
MEMORY
{
  m_flash_config        (RX)  : ORIGIN = 0x30000400, LENGTH = 0x00000C00
  m_ivt                 (RX)  : ORIGIN = 0x30001000, LENGTH = 0x00001000
  m_interrupts          (RX)  : ORIGIN = 0x30002000, LENGTH = 0x00000400
  m_text                (RX)  : ORIGIN = 0x30002400, LENGTH = 0x00FFDC00
  m_qacode              (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00020000
  m_data                (RW)  : ORIGIN = 0x20240000, LENGTH = 0x00100000
  m_ncache              (RW)  : ORIGIN = __NCACHE_REGION_START, LENGTH = __NCACHE_REGION_SIZE
}



/* Define output sections */
SECTIONS
{
  .flash_config :
  {
    . = ALIGN(4);
    __FLASH_BASE = .;
    KEEP(* (.boot_hdr.conf))     /* flash config section */
    . = ALIGN(4);
  } > m_flash_config

  .ivt :
  {
    . = ALIGN(4);
    KEEP(* (.boot_hdr.ivt))           /* ivt section */
    KEEP(* (.boot_hdr.boot_data))     /* boot section */
    KEEP(* (.boot_hdr.dcd_data))      /* dcd section */
    . = ALIGN(4);
  } > m_ivt


  /* The startup code goes first into internal RAM */
  .interrupts :
  {
    __VECTOR_TABLE = .;
    __Vectors = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))     /* Startup code */
    . = ALIGN(4);
  } > m_interrupts

  /* The program code and other data goes into internal RAM */
  .text :
  {
    m_text_start = .;
    . = ALIGN(4);
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_adapter_flexspi_nor_flash.c.obj
        */NV_Flash.c.obj
        */mflash_drv.c.obj
        */fsl_flexspi.c.obj
        */libethermind_lc3_common.a
        */libethermind_lc3_encoder.a
        */libethermind_lc3_decoder.a
        */fsl_edma.obj
	    */fsl_sai.obj
	    */fsl_sai_edma.obj
	    */fsl_sai_edma.obj
		*/leaudio_pl_ext.obj
    ) .text)                 /* .text sections (code) */
    *(EXCLUDE_FILE(
        /* Exclude flash and frequently executed functions from XIP */
        */fsl_adapter_flexspi_nor_flash.c.obj
        */NV_Flash.c.obj
        */mflash_drv.c.obj
        */fsl_flexspi.c.obj
        */libethermind_lc3_common.a
        */libethermind_lc3_encoder.a
        */libethermind_lc3_decoder.a
        */fsl_edma.obj
        */fsl_sai.obj
        */fsl_sai_edma.obj
        */fsl_sai_edma.obj
        */leaudio_pl_ext.obj
        *queue.c.obj
        *tcp_out.c.obj
        *mlan_sdio.c.obj
        *mlan_11n.c.obj
        *mlan_11n_aggr.c.obj
        *mlan_11n_rxreorder.c.obj
        *tcp_in.c.obj
        *inet_chksum.c.obj
        *timers.c.obj
        *fsl_usdhc.c.obj
        *port.c.obj
        *wifi-sdio.c.obj
        *fsl_sdio.c.obj
        *pbuf.c.obj
        *tcp.c.obj
        *udp.c.obj
        *tcpip.c.obj
        *sockets.c.obj
        *tasks.c.obj
        *lib_a-memset.o
        *fsl_cache.c.obj
        *wifi.c.obj
        *wifi_netif.c.obj
        *fsl_os_abstraction_free_rtos.c.obj
        *fsl_memcpy.S.obj
    ) .text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    m_text_end = .;
  } > m_text

  ._bt_conn_cb :
  {
    . = ALIGN(4);
    _bt_conn_cb_list_start = .;
    KEEP(*(SORT(._bt_conn_cb.static.*)))
    _bt_conn_cb_list_end = .;
    . = ALIGN(4);
  } > m_text
  
  ._bt_settings_area :
  {
    . = ALIGN(4);
    _bt_settings_start = .;
    KEEP(*(SORT(._bt_settings.static.*)))
    _bt_settings_end = .;
    . = ALIGN(4);
  } > m_text

  ._settings_handler_static :
  {
    . = ALIGN(4);
    _settings_handler_static_list_start = .;
    KEEP(*(SORT(._settings_handler_static.static.*)))
    _settings_handler_static_list_end = .;
    . = ALIGN(4);
  } > m_text

  ._bt_gatt_service_static :
  {
    . = ALIGN(4);
    _bt_gatt_service_static_list_start = .;
    KEEP(*(SORT(._bt_gatt_service_static.static.*)))
    _bt_gatt_service_static_list_end = .;
    . = ALIGN(4);
  } > m_text

  ._bt_l2cap_fixed_chan :
  {
    . = ALIGN(4);
    _bt_l2cap_fixed_chan_list_start = .;
    KEEP(*(SORT(._bt_l2cap_fixed_chan.static.*)))
    _bt_l2cap_fixed_chan_list_end = .;
    . = ALIGN(4);
  } > m_text

  ._bt_l2cap_br_fixed_chan :
  {
    . = ALIGN(4);
    _bt_l2cap_br_fixed_chan_list_start = .;
    KEEP(*(SORT(._bt_l2cap_br_fixed_chan.static.*)))
    _bt_l2cap_br_fixed_chan_list_end = .;
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
    . += VECTOR_RAM_SIZE;
    . = ALIGN(4);
    __interrupts_ram_end__ = .; /* Define a global symbol at data end */
  } > m_data

  __VECTOR_RAM = DEFINED(__ram_vector_table__) ? __VECTOR_RAM__ : ORIGIN(m_interrupts);
  __RAM_VECTOR_TABLE_SIZE_BYTES = DEFINED(__ram_vector_table__) ? (__interrupts_ram_end__ - __interrupts_ram_start__) : 0x0;

  .data : AT(__DATA_ROM)
  {
    . = ALIGN(4);
    __DATA_RAM = .;
    __data_start__ = .;      /* create a global symbol at data start */
    *(m_usb_dma_init_data)
    *(.wlan_data* .wlan_data)
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    *(vtable)
    *(DataQuickAccess)       /* quick access data section */
    *(.wlan_data .wlan_data.*)                /* .data* sections */
    KEEP(*(.jcr*))
    . = ALIGN(4);
    _net_buf_pool_list = .;
    KEEP(*(SORT(._net_buf_pool*)))
    __data_end__ = .;        /* define a global symbol at data end */
  } > m_data

  __ram_function_flash_start = __DATA_ROM + (__data_end__ - __data_start__); /* Symbol is used by startup for TCM data initialization */

  .ram_function : AT(__ram_function_flash_start)
  {
    . = ALIGN(32);
    __ram_function_start__ = .;
    *(CodeQuickAccess)
    /* Explicit placement of flash and frequently executed functions in RAM */
    */fsl_adapter_flexspi_nor_flash.c.obj
    */NV_Flash.c.obj
    */mflash_drv.c.obj
    */fsl_flexspi.c.obj
    */libethermind_lc3_common.a
    */libethermind_lc3_encoder.a
    */libethermind_lc3_decoder.a
    */fsl_edma.obj
    */fsl_sai.obj
    */fsl_sai_edma.obj
    */fsl_sai_edma.obj
    */leaudio_pl_ext.obj
    *queue.c.obj(.text*)
    *tcp_out.c.obj(.text*)
    *mlan_sdio.c.obj(.text*)
    *mlan_11n.c.obj(.text*)
    *mlan_11n_aggr.c.obj(.text*)
    *mlan_11n_rxreorder.c.obj(.text*)
    *tcp_in.c.obj(.text*)
    *inet_chksum.c.obj(.text*)
    *timers.c.obj(.text*)
    *fsl_usdhc.c.obj(.text*)
    *port.c.obj(.text*)
    *wifi-sdio.c.obj(.text*)
    *fsl_sdio.c.obj(.text*)
    *pbuf.c.obj(.text*)
    *tcp.c.obj(.text*)
    *udp.c.obj(.text*)
    *tcpip.c.obj(.text*)
    *sockets.c.obj(.text*)
    *tasks.c.obj(.text*)
    *lib_a-memset.o(.text*)
    *fsl_cache.c.obj(.text*)
    *wifi.c.obj(.text*)
    *wifi_netif.c.obj(.text*)
    *fsl_os_abstraction_free_rtos.c.obj(.text*)
    *fsl_memcpy.S.obj(.text)
    . = ALIGN(128);
    __ram_function_end__ = .;
  } > m_qacode

  __NDATA_ROM = __ram_function_flash_start + (__ram_function_end__ - __ram_function_start__);
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

  __DATA_END = __NDATA_ROM + (__noncachedata_init_end__ - __noncachedata_start__);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  .qadata :
  {
    . = ALIGN(4);
    *(DataQuickAccess)       /* quick access data section */
    *(_java_heap)
    *(.bss.vm.stacks.java)
    *(ICETEA_HEAP)
    *(.bss.soar)
    *(MicroJvm*)
    *(VMCORE*)
    *(core_*)
    *(microejapp.o)
    . = ALIGN(4);
  } > m_data

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(4);
    __START_BSS = .;
    __bss_start__ = .;
    *(m_usb_dma_noninit_data)
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __END_BSS = .;
  } > m_data

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
}

