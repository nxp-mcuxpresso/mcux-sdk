list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core_A/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(component_iuart_adapter)
#    include(component_lists)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(device_startup)
#    include(device_system)
#    include(driver_common)
#    include(driver_gpt)
#    include(driver_ii2c)
#    include(driver_iuart)
#    include(middleware_freertos-kernel_ca53)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_freertos-kernel_heap_4)
#    include(utilities_misc_utilities)
#    include(utility_assert)
#    include(utility_debug_console)
#    include(utility_debug_console_lite)
