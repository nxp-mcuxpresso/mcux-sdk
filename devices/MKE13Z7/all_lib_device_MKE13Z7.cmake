list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tsi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_lpuart_freertos)
#    include(middleware_freertos-kernel_MKE17Z7)
#    include(utility_shell)
#    include(driver_flexio_spi_edma)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_freertos)
#    include(driver_port)
#    include(driver_dmamux)
#    include(driver_lpspi)
#    include(driver_lpi2c_edma)
#    include(driver_gpio)
#    include(component_lists)
#    include(device_system)
#    include(driver_lpit)
#    include(utility_debug_console)
#    include(component_log)
#    include(driver_acmp)
#    include(device_startup)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_adc12)
#    include(driver_flexio_uart)
#    include(utility_notifier)
#    include(driver_ewm)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_flexio_spi)
#    include(middleware_freertos-kernel_extension)
#    include(utilities_misc_utilities_MKE17Z7)
#    include(driver_flexio)
#    include(driver_ftm)
#    include(driver_trgmux)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(utility_assert_lite)
#    include(driver_tsi_v5)
#    include(driver_flexio_i2c_master)
#    include(driver_sim)
#    include(driver_cmsis_lpi2c)
#    include(driver_flash)
#    include(component_panic)
#    include(driver_clock)
#    include(driver_lpspi_edma)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(device_CMSIS)
#    include(driver_edma_MKE17Z7)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_osa_bm)
#    include(driver_wdog32)
#    include(driver_lpi2c)
#    include(driver_common)
#    include(driver_cmsis_lpspi)
#    include(driver_smc)
#    include(driver_crc)
#    include(driver_flexio_uart_edma)
#    include(component_osa_free_rtos)
#    include(driver_lptmr)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(driver_pwt)
#    include(driver_pmc)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(component_log_backend_debugconsole)
#    include(driver_cmsis_lpuart)
