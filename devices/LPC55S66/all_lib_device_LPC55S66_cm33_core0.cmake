list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/anactrl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/casper
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hashcrypt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mailbox
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/plu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/prince
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rng_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysctl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
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
#    include(driver_anactrl)
#    include(utility_incbin)
#    include(driver_ctimer)
#    include(middleware_usb_device_ip3511fs)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_lpc_gpio)
#    include(middleware_sdmmc_host_sdif_azurertos)
#    include(driver_lpadc)
#    include(driver_lpc_crc)
#    include(component_log_backend_ringbuffer)
#    include(driver_flexcomm_usart)
#    include(utilities_misc_utilities)
#    include(driver_ostimer)
#    include(driver_gint)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager)
#    include(middleware_usb_device_cdc_external)
#    include(device_system_LPC55S66_cm33_core0)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_flexcomm_i2s)
#    include(component_log_backend_debugconsole)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_sdmmc_host_sdif_polling)
#    include(driver_pint)
#    include(driver_sctimer)
#    include(middleware_usb_device_common_header)
#    include(driver_flexcomm)
#    include(driver_casper)
#    include(component_panic)
#    include(driver_lpc_dma)
#    include(utility_assert)
#    include(driver_rng_1)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_iap1)
#    include(middleware_usb_common_header)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(driver_prince)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_lpc_iocon)
#    include(utility_debug_console_lite)
#    include(component_osa_bm)
#    include(middleware_usb_host_ohci)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(middleware_freertos-kernel_LPC55S69_cm33_core0)
#    include(component_mrt_adapter)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(middleware_usb_device_controller_driver_LPC55S69_cm33_core0)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(driver_hashcrypt)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(component_usart_adapter)
#    include(middleware_usb_host_msd)
#    include(driver_wwdt)
#    include(component_gint_adapter)
#    include(component_log)
#    include(driver_plu)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_inputmux_connections)
#    include(driver_mailbox)
#    include(middleware_usb_host_printer)
#    include(driver_cmp_1)
#    include(middleware_usb_device_ip3511hs)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_usb_host_audio)
#    include(utility_assert_lite)
#    include(middleware_fatfs)
#    include(utility_shell)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_osa_thread)
#    include(middleware_fatfs_ram)
#    include(component_mflash_common)
#    include(component_lpc_gpio_adapter)
#    include(middleware_sdmmc_host_sdif)
#    include(driver_puf)
#    include(driver_sysctl)
#    include(driver_power)
#    include(middleware_usb_phy)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(middleware_fatfs_usb)
#    include(component_serial_manager_uart_LPC55S69_cm33_core0)
#    include(device_startup_LPC55S66_cm33_core0)
#    include(driver_lpc_rtc)
#    include(middleware_sdmmc_common)
#    include(middleware_fatfs_sd)
#    include(middleware_sdmmc_osa_azurertos)
#    include(driver_cmsis_flexcomm_spi)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(driver_mrt)
#    include(component_osa)
#    include(driver_sdif)
#    include(middleware_sdmmc_host_sdif_interrupt)
#    include(driver_flexcomm_usart_dma)
#    include(middleware_usb_host_ip3516hs)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_powerquad_cmsis)
#    include(driver_powerquad)
#    include(middleware_sdmmc_host_sdif_freertos)
#    include(middleware_usb_host_phdc)
#    include(driver_flexcomm_usart_freertos)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(middleware_mbedtls_LPC55S69_cm33_core0)
#    include(middleware_usb_host_stack_LPC55S69_cm33_core0)
#    include(driver_reset)
#    include(middleware_usb_device_stack_external)
