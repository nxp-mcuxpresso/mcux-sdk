list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/intmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tsi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tstmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_lpuart_freertos)
#    include(component_lpit_adapter)
#    include(driver_dmamux)
#    include(utility_shell)
#    include(driver_cmsis_lpuart)
#    include(driver_dac)
#    include(device_system)
#    include(driver_flexio_uart)
#    include(middleware_mmcau_common_files)
#    include(driver_flexio)
#    include(middleware_freertos-kernel_K32L2A41A)
#    include(driver_flexio_i2c_master)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_flexio_uart_edma)
#    include(driver_rtc)
#    include(driver_wdog32)
#    include(component_gpio_adapter)
#    include(component_serial_manager)
#    include(middleware_usb_device_cdc_external)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(middleware_mbedtls_port_ksdk)
#    include(component_log_backend_debugconsole)
#    include(driver_llwu)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(driver_cmsis_lpi2c)
#    include(utilities_misc_utilities_K32L2A41A)
#    include(device_startup)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_mmdvsq)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(component_led)
#    include(middleware_usb_common_header)
#    include(middleware_usb_device_common_header)
#    include(component_panic)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_tstmr)
#    include(component_osa_bm)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(driver_smc)
#    include(component_osa_free_rtos)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(middleware_fatfs_K32L2A41A)
#    include(driver_trgmux)
#    include(middleware_usb_host_msd)
#    include(driver_port)
#    include(driver_lpspi)
#    include(driver_gpio)
#    include(component_log)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(middleware_usb_host_printer)
#    include(middleware_usb_host_audio)
#    include(utility_assert_lite)
#    include(driver_tsi_v4)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(driver_cmsis_lpspi)
#    include(driver_crc)
#    include(driver_lptmr)
#    include(driver_pmc)
#    include(middleware_usb_host_stack_K32L2A41A)
#    include(middleware_fatfs_usb)
#    include(driver_flexio_spi_edma)
#    include(middleware_usb_host_khci)
#    include(component_timer_manager)
#    include(driver_lpi2c_freertos)
#    include(component_lists)
#    include(driver_tpm)
#    include(component_button_K32L2A41A)
#    include(driver_cmp)
#    include(driver_lpit)
#    include(component_osa)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(middleware_usb_device_khci)
#    include(driver_edma_K32L2A41A)
#    include(middleware_mmcau_cm0p)
#    include(utility_notifier)
#    include(driver_sim)
#    include(middleware_usb_device_controller_driver_K32L2A41A)
#    include(driver_lpi2c)
#    include(middleware_usb_host_phdc)
#    include(driver_trng)
#    include(driver_intmux)
#    include(middleware_mbedtls_K32L2A41A)
#    include(middleware_usb_device_stack_external)
