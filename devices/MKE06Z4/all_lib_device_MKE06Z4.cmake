list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_5v12b_ll18_015
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash_ftmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kbi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mscan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwt_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog8
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_mscan)
#    include(driver_i2c)
#    include(driver_kbi)
#    include(driver_pwt_1)
#    include(component_lists)
#    include(utilities_misc_utilities_MKE06Z4)
#    include(device_system)
#    include(driver_tpm)
#    include(driver_cmsis_spi)
#    include(driver_cmsis_i2c)
#    include(device_startup)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_acmp_1)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_ftm)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_gpio_1)
#    include(utility_assert_lite)
#    include(driver_port_ke06)
#    include(driver_spi)
#    include(component_uart_adapter)
#    include(driver_clock)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog8)
#    include(driver_uart)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_common)
#    include(driver_cmsis_uart)
#    include(utility_assert)
#    include(driver_irq)
#    include(component_serial_manager)
#    include(driver_rtc_1)
#    include(driver_pit)
#    include(component_serial_manager_uart)
#    include(driver_adc_5v12b_ll18_015)
#    include(driver_flash_ftmr)
