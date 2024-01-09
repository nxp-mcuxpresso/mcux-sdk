list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/led
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/eeprom
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/emc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flashiap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spifi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_flexcomm_i2c_freertos)
#    include(component_osa_bm)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_lpc_rtc)
#    include(driver_flexcomm_spi)
#    include(driver_otp)
#    include(component_ctimer_adapter)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_usb_host_hid)
#    include(driver_mcan)
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_spifi_dma)
#    include(driver_sctimer)
#    include(driver_ctimer)
#    include(driver_flashiap)
#    include(middleware_freertos-kernel_heap_3)
#    include(middleware_mbedtls_LPC54628)
#    include(driver_reset)
#    include(driver_spifi)
#    include(driver_clock)
#    include(middleware_sdmmc_host_sdif_polling)
#    include(middleware_fatfs_sd)
#    include(component_button_LPC54628)
#    include(component_log)
#    include(component_osa_free_rtos_LPC54628)
#    include(middleware_usb_device_stack_external)
#    include(driver_flexcomm_usart_dma)
#    include(driver_flexcomm_spi_dma)
#    include(middleware_sdmmc_mmc)
#    include(CMSIS_Driver_Include_USART)
#    include(middleware_usb_host_stack_LPC54628)
#    include(driver_common)
#    include(component_mflash_common)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_sdmmc_host_sdif_interrupt)
#    include(driver_lpc_iocon)
#    include(middleware_freertos-kernel_extension)
#    include(driver_lpc_enet)
#    include(middleware_lwip_contrib_ping)
#    include(driver_power)
#    include(middleware_freertos-kernel_LPC54628)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(utilities_misc_utilities_LPC54628)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_fmc)
#    include(driver_lpc_crc)
#    include(device_startup)
#    include(driver_dmic)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_lwip_apps_httpsrv_LPC54628)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(driver_iap)
#    include(middleware_usb_host_common_header)
#    include(middleware_sdmmc_common)
#    include(driver_flexcomm_i2s)
#    include(driver_rit)
#    include(middleware_lwip_apps_httpd_support)
#    include(middleware_lwip_usb_ethernetif_LPC54628)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_sdmmc_sd)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_flexcomm_i2c)
#    include(driver_cmsis_flexcomm_spi)
#    include(middleware_lwip_apps_mdns_LPC54628)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(middleware_sdmmc_host_sdif)
#    include(middleware_mbedtls_port_ksdk)
#    include(component_lists)
#    include(middleware_usb_host_msd)
#    include(middleware_fatfs_mmc)
#    include(utility_debug_console)
#    include(driver_gint)
#    include(middleware_freertos-kernel_heap_4)
#    include(component_log_backend_debugconsole_LPC54628)
#    include(middleware_lwip_apps_lwiperf_LPC54628)
#    include(middleware_lwip_LPC54628)
#    include(driver_flexcomm)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_usb_device_ip3511hs_LPC54628)
#    include(driver_emc)
#    include(driver_mrt)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(CMSIS_Include_core_cm)
#    include(driver_lpc_gpio)
#    include(middleware_usb_device_controller_driver_LPC54628)
#    include(middleware_usb_host_ip3516hs_LPC54628)
#    include(driver_rng)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_usb_host_printer)
#    include(middleware_usb_device_ip3511fs)
#    include(driver_utick)
#    include(middleware_lwip_apps_mqtt)
#    include(driver_cmsis_flexcomm_usart)
#    include(component_lpc_gpio_adapter)
#    include(component_timer_manager)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(component_mrt_adapter)
#    include(driver_eeprom)
#    include(middleware_sdmmc_osa_freertos)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_sdmmc_sdio)
#    include(driver_pint)
#    include(device_system)
#    include(driver_lpc_adc)
#    include(utility_assert_lite)
#    include(driver_dmic_dma)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_ohci)
#    include(driver_sdif)
#    include(component_led)
#    include(driver_flexcomm_i2s_dma)
#    include(middleware_fatfs_LPC54628)
#    include(driver_fmeas)
#    include(driver_inputmux_connections)
#    include(middleware_usb_common_header)
#    include(middleware_sdmmc_host_sdif_freertos)
#    include(component_serial_manager)
#    include(driver_inputmux)
