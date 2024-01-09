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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_lpc_iocon)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_dsp)
#    include(driver_flexcomm_i2c)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_bm)
#    include(device_startup_LPC54114_cm0plus)
#    include(driver_power)
#    include(driver_utick)
#    include(utility_assert)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(driver_mailbox)
#    include(device_system_LPC54114_cm0plus)
#    include(component_usart_adapter)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(middleware_baremetal)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_flexcomm_usart)
#    include(utility_debug_console_lite)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(middleware_freertos-kernel_heap_3)
#    include(middleware_multicore_rpmsg_lite_LPC54114_cm0plus)
#    include(utility_assert_lite)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_freertos)
#    include(driver_reset)
#    include(middleware_multicore_erpc_common)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(driver_flexcomm)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(CMSIS_Include_core_cm0plus)
#    include(CMSIS_Include_common)
#    include(middleware_multicore_mcmgr)
#    include(middleware_multicore_erpc_doc)
#    include(driver_inputmux_connections)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(middleware_multicore_mcmgr_lpc54114)
#    include(driver_common)
#    include(middleware_freertos-kernel_LPC54114_cm0plus)
#    include(driver_lpc_gpio)
#    include(component_serial_manager)
#    include(utilities_misc_utilities_LPC54114_cm0plus)
#    include(driver_inputmux)
