list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mailbox
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(CMSIS_Include_dsp)
#    include(component_usart_adapter)
#    include(component_lists)
#    include(driver_lpc_gpio)
#    include(middleware_freertos-kernel_LPC54114_cm0plus)
#    include(driver_flexcomm)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_inputmux_connections)
#    include(driver_mailbox)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_core_cm0plus)
#    include(middleware_baremetal)
#    include(driver_utick)
#    include(utility_debug_console)
#    include(utility_assert)
#    include(driver_flexcomm_usart)
#    include(device_CMSIS)
#    include(device_system_LPC54114_cm0plus)
#    include(driver_lpc_iocon)
#    include(device_startup_LPC54114_cm0plus)
#    include(utilities_misc_utilities)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(utility_assert_lite)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager)
#    include(driver_power)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_serial_manager_uart)
#    include(driver_reset)
