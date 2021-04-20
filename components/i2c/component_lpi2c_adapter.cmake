#Description: Component lpi2c_adapter; user_visible: True
include_guard(GLOBAL)
message("component_lpi2c_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_lpi2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpi2c)
