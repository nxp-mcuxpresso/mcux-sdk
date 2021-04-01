list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mailbox
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
mcux_include_from_kconfig(CMSIS_Include_dsp)
mcux_include_from_kconfig(component_usart_adapter)
mcux_include_from_kconfig(component_lists)
mcux_include_from_kconfig(driver_lpc_gpio)
mcux_include_from_kconfig(driver_flexcomm)
mcux_include_from_kconfig(driver_clock)
mcux_include_from_kconfig(utility_debug_console_lite)
mcux_include_from_kconfig(driver_inputmux_connections)
mcux_include_from_kconfig(driver_mailbox)
mcux_include_from_kconfig(driver_flexcomm_usart)
mcux_include_from_kconfig(device_CMSIS)
mcux_include_from_kconfig(driver_lpc_iocon)
mcux_include_from_kconfig(utility_assert_lite_LPC55S69_cm33_core1)
mcux_include_from_kconfig(utilities_misc_utilities)
mcux_include_from_kconfig(CMSIS_Include_common)
mcux_include_from_kconfig(driver_common)
mcux_include_from_kconfig(driver_inputmux)
mcux_include_from_kconfig(device_startup_LPC55S69_cm33_core1)
mcux_include_from_kconfig(device_system_LPC55S69_cm33_core1)
mcux_include_from_kconfig(driver_power)
mcux_include_from_kconfig(CMSIS_Include_core_cm33)
mcux_include_from_kconfig(driver_reset)
