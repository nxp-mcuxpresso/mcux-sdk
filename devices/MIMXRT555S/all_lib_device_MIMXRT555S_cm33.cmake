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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hashcrypt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iopctl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otfad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smartdma
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
#    include(middleware_freertos-kernel_MIMXRT595S_cm33)
#    include(driver_ctimer)
#    include(driver_sema42)
#    include(middleware_sdmmc_mmc)
#    include(driver_lpc_gpio)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT595S_cm33)
#    include(driver_lpadc)
#    include(driver_flexio_uart)
#    include(driver_lpc_crc)
#    include(middleware_usb_device_controller_driver_MIMXRT595S_cm33)
#    include(driver_flexio)
#    include(driver_flexio_i2c_master)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_sdmmc_osa_bm)
#    include(component_log_backend_ringbuffer)
#    include(driver_flexcomm_usart)
#    include(middleware_mbedtls_MIMXRT595S_cm33)
#    include(driver_i3c)
#    include(driver_ostimer)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(driver_iap)
#    include(component_serial_manager)
#    include(middleware_usb_device_cdc_external)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_flexcomm_i2s)
#    include(component_log_backend_debugconsole)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(driver_pint)
#    include(driver_sctimer)
#    include(middleware_usb_device_common_header)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT595S_cm33)
#    include(driver_flexcomm)
#    include(device_startup)
#    include(driver_casper)
#    include(component_panic)
#    include(driver_usdhc)
#    include(middleware_usb_host_stack_MIMXRT595S_cm33)
#    include(driver_flexio_mculcd_smartdma)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_lpc_smartdma)
#    include(middleware_usb_common_header)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(driver_soc_mipi_dsi)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(utility_debug_console_lite)
#    include(component_osa_bm)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(driver_cache_cache64)
#    include(driver_flexspi_dma)
#    include(component_mrt_adapter)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_flexio_mculcd)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT595S_cm33)
#    include(driver_mipi_dsi)
#    include(driver_hashcrypt)
#    include(middleware_sdmmc_sdio)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(component_usart_adapter)
#    include(middleware_usb_host_msd)
#    include(driver_wwdt)
#    include(component_log)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_inputmux_connections)
#    include(middleware_usb_host_printer)
#    include(component_button_MIMXRT595S_cm33)
#    include(middleware_fatfs_mmc)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_usb_host_audio)
#    include(utility_assert_lite)
#    include(middleware_usb_host_ip3516hs_MIMXRT595S_cm33)
#    include(driver_lcdif)
#    include(utility_shell)
#    include(driver_otfad)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_mflash_common)
#    include(middleware_fatfs_MIMXRT595S_cm33)
#    include(driver_cmsis_flexcomm_spi)
#    include(driver_puf)
#    include(driver_power)
#    include(middleware_usb_phy)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(middleware_fatfs_usb)
#    include(driver_dmic_dma)
#    include(utilities_misc_utilities_MIMXRT595S_cm33)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(driver_lpc_rtc)
#    include(middleware_sdmmc_common)
#    include(middleware_fatfs_sd)
#    include(driver_flexspi)
#    include(driver_dmic)
#    include(component_timer_manager)
#    include(component_common_task)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(driver_mipi_dsi_smartdma)
#    include(driver_mrt)
#    include(driver_acmp)
#    include(component_osa)
#    include(driver_fmeas)
#    include(driver_flexio_spi)
#    include(middleware_usb_device_ip3511hs_MIMXRT595S_cm33)
#    include(driver_flexcomm_usart_dma)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_powerquad_cmsis)
#    include(driver_powerquad)
#    include(middleware_usb_host_phdc)
#    include(utility_assert)
#    include(driver_flexcomm_usart_freertos)
#    include(driver_lpc_iopctl)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(driver_trng)
#    include(driver_mu)
#    include(driver_reset)
#    include(middleware_usb_device_stack_external)
