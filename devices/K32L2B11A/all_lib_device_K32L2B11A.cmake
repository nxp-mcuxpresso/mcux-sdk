list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cop
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/slcd
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_llwu)
#    include(driver_port)
#    include(driver_lpuart_freertos)
#    include(component_button_K32L2B31A)
#    include(utility_shell)
#    include(utility_debug_console_lite)
#    include(driver_uart_freertos)
#    include(driver_cop)
#    include(component_lpuart_adapter)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(driver_dmamux)
#    include(driver_lptmr)
#    include(driver_gpio)
#    include(component_lists)
#    include(driver_dac)
#    include(device_system)
#    include(driver_tpm)
#    include(utility_debug_console)
#    include(component_log)
#    include(driver_cmp)
#    include(device_startup)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_spi)
#    include(component_panic)
#    include(component_osa)
#    include(driver_lpuart_dma)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(component_serial_manager_uart)
#    include(driver_flexio_spi)
#    include(driver_cmsis_i2c)
#    include(middleware_usb_device_khci)
#    include(component_pit_adapter)
#    include(middleware_freertos-kernel_extension)
#    include(driver_flexio)
#    include(middleware_usb_device_common_header)
#    include(utility_notifier)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(component_led)
#    include(utility_assert_lite)
#    include(driver_flexio_i2c_master)
#    include(driver_pmc)
#    include(utilities_misc_utilities_K32L2B31A)
#    include(driver_spi)
#    include(driver_flash)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(component_timer_manager)
#    include(component_log_backend_ringbuffer)
#    include(driver_flexio_uart_dma)
#    include(device_CMSIS)
#    include(driver_uart)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_usb_device_controller_driver_K32L2B31A)
#    include(driver_dma)
#    include(component_tpm_adapter)
#    include(component_osa_bm)
#    include(driver_spi_freertos)
#    include(driver_common)
#    include(driver_rtc)
#    include(driver_uart_dma)
#    include(driver_smc)
#    include(driver_flexio_uart)
#    include(driver_spi_dma)
#    include(component_gpio_adapter)
#    include(driver_i2c_dma)
#    include(driver_sim)
#    include(component_osa_free_rtos)
#    include(middleware_freertos-kernel_K32L2B31A)
#    include(driver_slcd)
#    include(driver_pit)
#    include(middleware_usb_device_cdc_external)
#    include(component_serial_manager)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_flexio_spi_dma)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(component_log_backend_debugconsole)
#    include(driver_cmsis_lpuart)
#    include(driver_cmsis_uart)
#    include(middleware_usb_common_header)
#    include(middleware_usb_device_stack_external)
