#Description: NETC SOC Driver; user_visible: True
include_guard(GLOBAL)
message("driver_netc_soc_imxrt1180 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_netc_soc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(driver_common)
