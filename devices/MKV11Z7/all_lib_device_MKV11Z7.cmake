list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
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
#    include(driver_uart_freertos)
#    include(utility_shell)
#    include(driver_cmp)
#    include(driver_dspi_edma)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(utility_notifier)
#    include(driver_cmsis_dspi)
#    include(driver_mmdvsq)
#    include(driver_uart)
#    include(driver_crc)
#    include(utility_assert)
#    include(driver_dac)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_gpio)
#    include(driver_llwu)
#    include(driver_sim)
#    include(component_osa_free_rtos_MKV11Z7)
#    include(driver_edma_MKV11Z7)
#    include(driver_pmc)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(component_log_backend_ringbuffer)
#    include(component_log_backend_debugconsole_MKV11Z7)
#    include(driver_port)
#    include(component_panic)
#    include(driver_dmamux)
#    include(driver_flash)
#    include(driver_i2c_edma)
#    include(driver_smc)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_cmsis_uart)
#    include(driver_flexcan_edma)
#    include(utility_debug_console)
#    include(driver_i2c_freertos)
#    include(device_system)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(component_log)
#    include(component_uart_adapter)
#    include(device_CMSIS)
#    include(driver_wdog)
#    include(driver_uart_edma)
#    include(driver_dspi)
#    include(driver_ewm)
#    include(CMSIS_Driver_Include_USART)
#    include(utilities_misc_utilities_MKV11Z7)
#    include(driver_i2c)
#    include(driver_common)
#    include(driver_cmsis_i2c)
#    include(CMSIS_Include_core_cm)
#    include(driver_ftm)
#    include(component_serial_manager)
#    include(driver_flexcan)
#    include(middleware_freertos-kernel_MKV11Z7)
#    include(driver_fxos8700cq)
