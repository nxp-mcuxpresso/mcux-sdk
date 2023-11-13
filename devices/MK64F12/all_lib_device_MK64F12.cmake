list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/frdmk64f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/led
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rnga
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysmpu
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
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_dspi)
#    include(component_i2c_adapter)
#    include(driver_uart_freertos)
#    include(driver_vref)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_dmamux)
#    include(utility_shell)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(driver_dac)
#    include(device_system)
#    include(utilities_misc_utilities_MK64F12)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_mdio-enet)
#    include(driver_ewm)
#    include(middleware_mmcau_common_files)
#    include(middleware_sdmmc_host_sdhc_interrupt)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(middleware_baremetal)
#    include(component_log_backend_ringbuffer)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_uart)
#    include(driver_rtc)
#    include(component_mflash_frdmk64f)
#    include(component_gpio_adapter)
#    include(component_serial_manager)
#    include(driver_pit)
#    include(middleware_usb_device_cdc_external)
#    include(driver_phy-common_MK64F12)
#    include(component_serial_manager_uart)
#    include(component_log_backend_debugconsole)
#    include(driver_llwu)
#    include(driver_ili9341)
#    include(driver_flexcan)
#    include(driver_lptmr)
#    include(middleware_usb_device_common_header)
#    include(driver_i2c_edma)
#    include(driver_cmsis_enet)
#    include(device_startup)
#    include(driver_dspi_freertos)
#    include(middleware_freertos-kernel_MK64F12)
#    include(component_serial_manager_usb_cdc)
#    include(driver_phy-device-ksz8081)
#    include(utility_assert)
#    include(driver_enet)
#    include(component_ftm_adapter)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(middleware_sdmmc_host_sdhc_freertos)
#    include(component_led)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_c_wrapper)
#    include(middleware_usb_common_header)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_sdmmc_osa_freertos)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(component_uart_adapter)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(driver_edma_MK64F12)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(middleware_usb_host_common_header)
#    include(driver_rnga)
#    include(driver_common)
#    include(middleware_fatfs_usb)
#    include(driver_smc)
#    include(middleware_usb_host_stack_MK64F12)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_1)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(middleware_usb_host_msd)
#    include(driver_port)
#    include(middleware_multicore_erpc_eRPC_dspi_master_c_wrapper)
#    include(driver_gpio)
#    include(component_log)
#    include(middleware_usb_host_cdc)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_mdio-common)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_printer)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(component_button_MK64F12)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_device_controller_driver_MK64F12)
#    include(utility_assert_lite)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_mflash_common)
#    include(driver_crc)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_pmc)
#    include(driver_cmsis_uart)
#    include(driver_cmsis_dspi)
#    include(driver_uart_edma)
#    include(middleware_fatfs_sd)
#    include(middleware_sdmmc_host_sdhc_polling)
#    include(middleware_usb_host_khci)
#    include(component_timer_manager)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(middleware_fatfs_MK64F12)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_cmt)
#    include(driver_cmp)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_i2c)
#    include(middleware_usb_device_khci)
#    include(component_pit_adapter)
#    include(component_mflash_file_MK64F12)
#    include(driver_wdog)
#    include(utility_notifier)
#    include(driver_sim)
#    include(middleware_sdmmc_host_sdhc)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_transport)
#    include(component_panic)
#    include(middleware_multicore_erpc_eRPC_dspi_master_transport)
#    include(driver_sdhc)
#    include(driver_sysmpu)
#    include(middleware_usb_device_stack_external)
#    include(driver_ft6x06)
#    include(driver_dspi_edma)
