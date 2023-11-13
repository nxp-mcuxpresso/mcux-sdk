list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rnga
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
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
#    include(driver_cmsis_dspi)
#    include(driver_uart_edma)
#    include(utility_shell)
#    include(driver_uart_freertos)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(driver_dmamux)
#    include(driver_lptmr)
#    include(driver_gpio)
#    include(component_lists)
#    include(driver_dac)
#    include(device_system)
#    include(driver_i2c_edma)
#    include(driver_dspi)
#    include(component_log)
#    include(driver_cmp)
#    include(device_startup)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(middleware_freertos-kernel_MKV31F51212)
#    include(component_panic)
#    include(driver_edma_MKV31F51212)
#    include(driver_ewm)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_cmsis_i2c)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(utility_notifier)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_wdog)
#    include(utility_assert_lite)
#    include(driver_lpuart_freertos)
#    include(driver_dspi_freertos)
#    include(utility_debug_console)
#    include(driver_flash)
#    include(component_uart_adapter)
#    include(driver_clock)
#    include(driver_sim)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(device_CMSIS)
#    include(driver_uart)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(utility_debug_console_lite)
#    include(component_osa_bm)
#    include(driver_rnga)
#    include(driver_common)
#    include(driver_smc)
#    include(driver_crc)
#    include(utilities_misc_utilities_MKV31F51212)
#    include(component_osa_free_rtos)
#    include(driver_pit)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(driver_pmc)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(component_log_backend_debugconsole)
#    include(driver_cmsis_lpuart)
#    include(driver_cmsis_uart)
#    include(driver_dspi_edma)
