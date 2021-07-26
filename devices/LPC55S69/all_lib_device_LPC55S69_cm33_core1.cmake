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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(component_usart_adapter)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(component_lists)
#    include(driver_lpc_gpio)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(driver_flexcomm)
#    include(middleware_multicore_rpmsg_lite_lpcxpresso55s69_bm)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_clock)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_inputmux_connections)
#    include(driver_mailbox)
#    include(middleware_multicore_mcmgr_lpc55s69)
#    include(CMSIS_Include_core_cm)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_multicore_rpmsg_lite_lpcxpresso55s69_freertos)
#    include(middleware_baremetal)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(driver_flexcomm_usart)
#    include(device_CMSIS)
#    include(driver_lpc_iocon)
#    include(middleware_multicore_erpc_doc)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_common)
#    include(utilities_misc_utilities)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(middleware_multicore_mcmgr)
#    include(driver_common)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(utility_assert)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(utility_assert_lite)
#    include(driver_inputmux)
#    include(middleware_freertos-kernel_LPC55S69_cm33_core1)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(device_system_LPC55S69_cm33_core1)
#    include(driver_power)
#    include(device_startup_LPC55S69_cm33_core1)
#    include(component_serial_manager_uart)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_reset)
