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
#    include(utility_shell)
#    include(component_osa_bm)
#    include(utility_notifier)
#    include(middleware_usb_device_controller_driver_K32L2A41A)
#    include(driver_crc)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_adc16)
#    include(driver_llwu)
#    include(middleware_usb_host_hid)
#    include(driver_pmc)
#    include(driver_lpi2c_edma)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(middleware_freertos-kernel_K32L2A41A)
#    include(driver_lpuart)
#    include(middleware_mmcau_common_files)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(component_log)
#    include(driver_edma_K32L2A41A)
#    include(driver_flexio_i2c_master)
#    include(component_lpuart_adapter)
#    include(middleware_fatfs_K32L2A41A)
#    include(middleware_usb_device_stack_external)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_lpspi)
#    include(utilities_misc_utilities_K32L2A41A)
#    include(middleware_mmcau_cm0p)
#    include(component_lpit_adapter)
#    include(driver_common)
#    include(driver_cmp)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(driver_dac)
#    include(driver_gpio)
#    include(component_serial_manager_uart)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(driver_smc)
#    include(driver_trng)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(component_log_backend_debugconsole_K32L2A41A)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_device_common_header)
#    include(driver_intmux)
#    include(driver_cmsis_lpspi)
#    include(driver_mmdvsq)
#    include(driver_rtc)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_lpspi_freertos)
#    include(component_lists)
#    include(middleware_usb_host_msd)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_tpm)
#    include(component_osa_free_rtos_K32L2A41A)
#    include(driver_wdog32)
#    include(driver_flexio_uart)
#    include(middleware_mbedtls_K32L2A41A)
#    include(driver_lpuart_freertos)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(CMSIS_Include_core_cm)
#    include(driver_tstmr)
#    include(middleware_usb_host_printer)
#    include(driver_lpspi_edma)
#    include(driver_sim)
#    include(middleware_usb_host_stack_K32L2A41A)
#    include(component_timer_manager)
#    include(component_gpio_adapter)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_usb_device_khci)
#    include(device_system)
#    include(middleware_usb_host_khci)
#    include(utility_assert_lite)
#    include(middleware_usb_host_phdc)
#    include(component_button_K32L2A41A)
#    include(component_led)
#    include(driver_trgmux)
#    include(driver_flexio_uart_edma)
#    include(driver_tsi_v4)
#    include(driver_flexio)
#    include(driver_flexio_spi)
#    include(middleware_usb_common_header)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_cmsis_lpi2c)
