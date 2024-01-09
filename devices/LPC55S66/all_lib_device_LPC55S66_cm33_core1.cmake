list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mailbox
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_lpc_iocon)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_freertos-kernel_LPC55S69_cm33_core1)
#    include(utilities_misc_utilities_LPC55S69_cm33_core1)
#    include(driver_power)
#    include(utility_assert)
#    include(driver_mailbox)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_flexcomm_usart)
#    include(utility_debug_console_lite)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_assert_lite)
#    include(driver_reset)
#    include(driver_flexcomm)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(driver_inputmux_connections)
#    include(device_startup_LPC55S66_cm33_core1)
#    include(device_system_LPC55S66_cm33_core1)
#    include(driver_common)
#    include(CMSIS_Include_core_cm)
#    include(driver_lpc_gpio)
#    include(component_serial_manager)
#    include(driver_inputmux)
