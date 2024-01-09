list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/cache64
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/casper
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hashcrypt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iopctl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
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
#    include(utility_shell)
#    include(driver_flexcomm_i2c_freertos)
#    include(component_osa_bm)
#    include(driver_lpc_rtc)
#    include(driver_flexcomm_spi)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_fatfs_MIMXRT685S_cm33)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33)
#    include(middleware_usb_host_hid)
#    include(component_button_MIMXRT685S_cm33)
#    include(CMSIS_DSP_Source)
#    include(middleware_sdmmc_host_usdhc)
#    include(component_log_backend_debugconsole_MIMXRT685S_cm33)
#    include(driver_sctimer)
#    include(middleware_mbedtls_MIMXRT685S_cm33)
#    include(driver_ctimer)
#    include(CMSIS_DSP_Include)
#    include(driver_lpadc)
#    include(middleware_freertos-kernel_heap_3)
#    include(driver_reset)
#    include(component_common_task)
#    include(component_osa_free_rtos_MIMXRT685S_cm33)
#    include(driver_clock)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(middleware_usb_device_stack_external)
#    include(driver_flexcomm_usart_dma)
#    include(driver_powerquad_cmsis)
#    include(driver_acmp)
#    include(driver_flexcomm_spi_dma)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_common)
#    include(component_mflash_common)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_usb_device_ip3511hs_MIMXRT685S_cm33)
#    include(driver_i3c)
#    include(driver_power)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_trng)
#    include(driver_flexspi_dma)
#    include(driver_lpc_crc)
#    include(device_startup)
#    include(driver_dmic)
#    include(middleware_sdmmc_osa_bm)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(middleware_usb_device_controller_driver_MIMXRT685S_cm33)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(driver_iap)
#    include(middleware_usb_host_common_header)
#    include(driver_casper)
#    include(middleware_sdmmc_common)
#    include(driver_flexcomm_i2s)
#    include(component_serial_manager_swo)
#    include(middleware_usb_device_common_header)
#    include(middleware_sdmmc_sd)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_flexcomm_i2c)
#    include(driver_cmsis_flexcomm_spi)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(middleware_usb_host_ip3516hs_MIMXRT685S_cm33)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(middleware_usb_host_msd)
#    include(middleware_freertos-kernel_MIMXRT685S_cm33)
#    include(utility_debug_console)
#    include(CMSIS_Device_API_OSTick)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_lpc_iopctl)
#    include(middleware_usb_phy)
#    include(driver_flexcomm)
#    include(driver_flexspi)
#    include(driver_flexcomm_spi_freertos)
#    include(driver_usdhc)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33)
#    include(middleware_usb_host_stack_MIMXRT685S_cm33)
#    include(driver_mrt)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(CMSIS_Include_core_cm)
#    include(driver_lpc_gpio)
#    include(driver_cache_cache64)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(middleware_usb_host_printer)
#    include(driver_utick)
#    include(driver_hashcrypt)
#    include(driver_powerquad)
#    include(driver_cmsis_flexcomm_usart)
#    include(component_lpc_gpio_adapter)
#    include(component_timer_manager)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(component_mrt_adapter)
#    include(middleware_sdmmc_osa_freertos)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_sdmmc_sdio)
#    include(driver_pint)
#    include(utility_assert_lite)
#    include(driver_sema42)
#    include(driver_dmic_dma)
#    include(middleware_usb_host_phdc)
#    include(CMSIS_Device_API_RTOS2)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_fmeas)
#    include(driver_inputmux_connections)
#    include(driver_ostimer)
#    include(middleware_usb_common_header)
#    include(driver_puf)
#    include(component_serial_manager)
#    include(utilities_misc_utilities_MIMXRT685S_cm33)
#    include(driver_inputmux)
