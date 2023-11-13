list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
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
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(utilities_misc_utilities_LPC54114_cm0plus)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(component_usart_adapter)
#    include(component_lists)
#    include(driver_lpc_gpio)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(middleware_freertos-kernel_LPC54114_cm0plus)
#    include(driver_flexcomm)
#    include(middleware_multicore_mcmgr)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_bm)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_inputmux_connections)
#    include(driver_mailbox)
#    include(middleware_multicore_rpmsg_lite_LPC54114_cm0plus)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_baremetal)
#    include(driver_utick)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(driver_flexcomm_usart)
#    include(device_CMSIS)
#    include(device_system_LPC54114_cm0plus)
#    include(driver_lpc_iocon)
#    include(middleware_multicore_erpc_doc)
#    include(device_startup_LPC54114_cm0plus)
#    include(middleware_multicore_erpc_common)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(driver_common)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(utility_assert)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(utility_assert_lite)
#    include(driver_inputmux)
#    include(middleware_multicore_mcmgr_lpc54114)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_power)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_serial_manager_uart)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_freertos)
#    include(driver_reset)
