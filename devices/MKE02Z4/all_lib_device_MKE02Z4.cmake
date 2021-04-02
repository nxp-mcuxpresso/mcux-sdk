list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog8
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(CMSIS_Include_dsp)
#    include(driver_i2c)
#    include(component_lists)
#    include(device_system)
#    include(driver_tpm)
#    include(device_startup)
#    include(driver_clock)
#    include(driver_wdog8)
#    include(utility_debug_console_lite)
#    include(driver_acmp_1)
#    include(driver_kbi)
#    include(driver_ftm)
#    include(driver_gpio_1)
#    include(CMSIS_Include_core_cm0plus)
#    include(driver_spi)
#    include(component_uart_adapter)
#    include(utility_assert)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_uart)
#    include(utilities_misc_utilities)
#    include(driver_port_ke02)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_irq)
#    include(utility_assert_lite)
#    include(component_serial_manager)
#    include(driver_rtc_1)
#    include(driver_pit)
#    include(component_serial_manager_uart)
#    include(driver_adc_5v12b_ll18_015)
#    include(driver_flash_ftmr)
