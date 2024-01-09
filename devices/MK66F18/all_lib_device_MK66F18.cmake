list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/da7212
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/frdmk66f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rnga
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysmpu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(driver_dspi_edma)
#    include(driver_pdb)
#    include(driver_ili9341)
#    include(utility_notifier)
#    include(driver_cmsis_dspi)
#    include(CMSIS_Driver_Include_Ethernet)
#    include(driver_crc)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(middleware_multicore_erpc_eRPC_dspi_master_c_wrapper)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_adc16)
#    include(driver_llwu)
#    include(driver_mdio-common)
#    include(middleware_usb_host_hid)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_pmc)
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(component_osa_free_rtos_MK66F18)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(middleware_freertos-kernel_heap_3)
#    include(driver_dialog7212)
#    include(middleware_mmcau_common_files)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_clock)
#    include(utilities_misc_utilities_MK66F18)
#    include(driver_lpuart_edma)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(middleware_mmcau_cm4_cm7)
#    include(middleware_usb_device_stack_external)
#    include(driver_dspi)
#    include(middleware_usb_host_ehci_MK66F18)
#    include(driver_cmsis_lpuart)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_common)
#    include(driver_phy-common_MK66F18)
#    include(driver_flexcan)
#    include(component_mflash_common)
#    include(driver_cmp)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(driver_edma_MK66F18)
#    include(middleware_freertos-kernel_MK66F18)
#    include(component_mflash_frdmk66f)
#    include(driver_uart)
#    include(driver_dac)
#    include(middleware_usb_device_controller_driver_MK66F18)
#    include(driver_cmsis_enet)
#    include(driver_rnga)
#    include(driver_gpio)
#    include(component_serial_manager_uart)
#    include(component_log_backend_ringbuffer)
#    include(driver_mdio-enet)
#    include(driver_port)
#    include(component_panic)
#    include(driver_sdhc)
#    include(driver_smc)
#    include(driver_i2c_edma)
#    include(driver_cmsis_uart)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(device_startup)
#    include(middleware_fatfs_MK66F18)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_multicore_erpc_common)
#    include(driver_phy-device-ksz8081)
#    include(component_i2c_adapter)
#    include(CMSIS_Driver_Include_SPI)
#    include(component_codec_i2c_MK66F18)
#    include(driver_cache_lmem)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_sdmmc_host_sdhc)
#    include(middleware_usb_host_common_header)
#    include(middleware_multicore_erpc_doc)
#    include(CMSIS_DSP_Library)
#    include(component_mflash_file_MK66F18)
#    include(middleware_sdmmc_common)
#    include(middleware_usb_host_stack_MK66F18)
#    include(middleware_sdmmc_host_sdhc_interrupt)
#    include(component_audio_sai_edma_adapter)
#    include(driver_cmsis_i2c)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_c_wrapper)
#    include(driver_ftm)
#    include(middleware_usb_device_common_header)
#    include(driver_uart_freertos)
#    include(middleware_sdmmc_sd)
#    include(driver_rtc)
#    include(component_serial_manager_usb_cdc)
#    include(driver_cmt)
#    include(utility_assert)
#    include(driver_ft6x06)
#    include(driver_sysmpu)
#    include(component_lists)
#    include(driver_dspi_freertos)
#    include(middleware_usb_host_msd)
#    include(middleware_usb_device_ehci_MK66F18)
#    include(utility_debug_console)
#    include(middleware_sdmmc_host_sdhc_polling)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_usb_phy)
#    include(driver_i2c_freertos)
#    include(driver_tpm)
#    include(driver_wdog)
#    include(driver_lpuart_freertos)
#    include(driver_uart_edma)
#    include(driver_ewm)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_transport)
#    include(CMSIS_Include_core_cm)
#    include(driver_enet)
#    include(component_log_backend_debugconsole_MK66F18)
#    include(component_da7212_adapter)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(middleware_usb_host_printer)
#    include(driver_sim)
#    include(middleware_baremetal)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(middleware_sdmmc_osa_freertos)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(driver_vref)
#    include(driver_sai_edma)
#    include(middleware_sdmmc_host_sdhc_freertos)
#    include(middleware_usb_device_khci)
#    include(device_system)
#    include(middleware_usb_host_khci)
#    include(utility_assert_lite)
#    include(middleware_usb_host_phdc)
#    include(component_uart_adapter)
#    include(driver_sai)
#    include(middleware_multicore_erpc_eRPC_dspi_master_transport)
#    include(driver_i2c)
#    include(middleware_usb_common_header)
#    include(component_serial_manager)
#    include(driver_fxos8700cq)
