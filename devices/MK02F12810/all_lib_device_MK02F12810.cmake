list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/led
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
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
#    include(middleware_freertos-kernel_MK22F51212)
#    include(driver_cmp)
#    include(driver_dspi_edma)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(utility_notifier)
#    include(driver_cmsis_dspi)
#    include(driver_uart)
#    include(driver_crc)
#    include(utility_assert)
#    include(driver_dac)
#    include(component_log_backend_debugconsole_MK22F51212)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_adc16)
#    include(driver_gpio)
#    include(component_button_MK22F51212)
#    include(driver_llwu)
#    include(driver_sim)
#    include(component_timer_manager)
#    include(component_gpio_adapter)
#    include(driver_pmc)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(utilities_misc_utilities_MK22F51212)
#    include(component_pwm_ftm_adapter)
#    include(CMSIS_Driver_Include_Common)
#    include(component_log_backend_ringbuffer)
#    include(driver_dspi_freertos)
#    include(utility_debug_console_lite)
#    include(driver_port)
#    include(component_panic)
#    include(driver_dmamux)
#    include(driver_flash)
#    include(driver_i2c_edma)
#    include(driver_smc)
#    include(driver_vref)
#    include(driver_cmsis_uart)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_debug_console)
#    include(driver_i2c_freertos)
#    include(device_system)
#    include(driver_pit)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(component_log)
#    include(component_uart_adapter)
#    include(device_CMSIS)
#    include(component_led)
#    include(driver_wdog)
#    include(driver_uart_edma)
#    include(driver_dspi)
#    include(driver_ewm)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(component_osa)
#    include(middleware_fatfs_MK22F51212)
#    include(driver_i2c)
#    include(driver_common)
#    include(driver_cmsis_i2c)
#    include(component_osa_free_rtos_MK22F51212)
#    include(CMSIS_Include_core_cm)
#    include(driver_ftm)
#    include(middleware_freertos-kernel_heap_1)
#    include(component_serial_manager)
#    include(driver_edma_MK22F51212)
