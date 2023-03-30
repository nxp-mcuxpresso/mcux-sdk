#Description: Middleware issdk drivers host; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_drivers_host component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sensors/host_io_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/host/comm_if_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/host/data_format_hdlc.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/host/data_format_json.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/host/host_interface_service.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers/host
    ${CMAKE_CURRENT_LIST_DIR}/sensors
)


include(middleware_issdk_drivers_cmsis_drivers)
include(driver_common)
