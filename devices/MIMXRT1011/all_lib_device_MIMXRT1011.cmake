list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1010/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_12b1msps_sar
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv7-m7
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcdc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexram
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kpp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ocotp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otfad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtwdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/src
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempmon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/azure-rtos
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(middleware_azure_rtos_ux_template_MIMXRT1011)
#    include(driver_lpuart_freertos)
#    include(middleware_usb_device_controller_driver_MIMXRT1011)
#    include(driver_dmamux)
#    include(driver_nor_flash-controller-flexspi)
#    include(driver_cmsis_lpuart)
#    include(device_system)
#    include(driver_snvs_lp)
#    include(driver_flexio_uart)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_azure_rtos_nxd_sp)
#    include(middleware_freertos-kernel_MIMXRT1011)
#    include(middleware_usb_device_ehci_MIMXRT1011)
#    include(driver_flexio)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_wdog01)
#    include(driver_flexio_uart_edma)
#    include(driver_ocotp)
#    include(driver_codec)
#    include(driver_xip_device)
#    include(component_serial_manager)
#    include(driver_pit)
#    include(middleware_usb_device_cdc_external)
#    include(component_serial_manager_uart)
#    include(middleware_mbedtls_port_ksdk)
#    include(middleware_azure_rtos_ux_sp)
#    include(component_log_backend_debugconsole)
#    include(utilities_misc_utilities_MIMXRT1011)
#    include(driver_ili9341)
#    include(driver_tempmon)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(middleware_usb_device_common_header)
#    include(utility_shell)
#    include(device_startup)
#    include(component_panic)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_rtwdog)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_nor_flash-common)
#    include(middleware_usb_common_header)
#    include(driver_cmsis_lpi2c)
#    include(driver_soc_flexram_allocate)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(middleware_usb_host_ehci_MIMXRT1011)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_osa_bm)
#    include(driver_adc_12b1msps_sar)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(driver_kpp)
#    include(component_osa_free_rtos)
#    include(driver_xip_board_evkmimxrt1010)
#    include(driver_adc_etc)
#    include(component_lpi2c_adapter)
#    include(middleware_mbedtls_MIMXRT1011)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_dcdc_1)
#    include(driver_xbara)
#    include(middleware_azure_rtos_fx_sp)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1011)
#    include(driver_snvs_hp)
#    include(middleware_usb_host_msd)
#    include(driver_lpspi)
#    include(driver_flexspi_edma)
#    include(middleware_usb_host_common_header)
#    include(component_log)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(component_audio_sai_edma_adapter)
#    include(middleware_usb_host_printer)
#    include(driver_iomuxc)
#    include(middleware_usb_host_audio)
#    include(driver_flexram)
#    include(utility_assert_lite)
#    include(driver_rtt_MIMXRT1011)
#    include(middleware_azure_rtos_tx_sp)
#    include(utility_debug_console)
#    include(component_codec_i2c_MIMXRT1011)
#    include(component_osa_thread)
#    include(driver_cmsis_lpspi)
#    include(middleware_usb_host_hid)
#    include(component_wm8960_adapter)
#    include(middleware_usb_phy)
#    include(driver_gpc_1)
#    include(driver_dcp)
#    include(middleware_fatfs_usb)
#    include(middleware_fatfs_MIMXRT1011)
#    include(driver_edma_MIMXRT1011)
#    include(driver_flexspi)
#    include(driver_flexio_spi_edma)
#    include(driver_pwm)
#    include(driver_sai_edma)
#    include(component_lists)
#    include(middleware_azure_rtos_tx_template_MIMXRT1011)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(middleware_usb_host_stack_MIMXRT1011)
#    include(driver_flexio_spi)
#    include(component_pit_adapter)
#    include(middleware_mbedtls_rt)
#    include(middleware_azure_rtos_fx_template_MIMXRT1011)
#    include(driver_src)
#    include(driver_lpi2c)
#    include(middleware_usb_host_phdc)
#    include(driver_flexio_i2s)
#    include(driver_otfad)
#    include(driver_igpio)
#    include(driver_trng)
#    include(driver_sai)
#    include(driver_cache_armv7_m7)
#    include(middleware_usb_device_stack_external)
#    include(driver_ft6x06)
#    include(driver_flexio_i2s_edma)
