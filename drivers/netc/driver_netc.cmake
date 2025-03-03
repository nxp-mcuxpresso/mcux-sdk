#Description: NETC Driver; user_visible: True
include_guard(GLOBAL)
message("driver_netc component is included.")

if(${MCUX_DEVICE} MATCHES "MIMX9596")
    set(NETC_SWITCH_FILE "")
else()
    set(NETC_SWITCH_FILE "${CMAKE_CURRENT_LIST_DIR}/fsl_netc_switch.c")
endif()

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_netc_endpoint.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_netc_timer.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_netc_ierb.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_netc_mdio.c
    ${CMAKE_CURRENT_LIST_DIR}/netc_hw/fsl_netc_hw.c
    ${CMAKE_CURRENT_LIST_DIR}/netc_hw/fsl_netc_hw_port.c
    ${CMAKE_CURRENT_LIST_DIR}/netc_hw/fsl_netc_hw_si.c
    ${CMAKE_CURRENT_LIST_DIR}/netc_hw/fsl_netc_hw_enetc.c
    ${NETC_SWITCH_FILE}
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/netc_hw/.
)

include(driver_common)
