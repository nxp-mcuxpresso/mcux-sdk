#Description: Component ii2c_adapter; user_visible: True
include_guard(GLOBAL)
message("component_ii2c_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_ii2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
include(driver_ii2c)
