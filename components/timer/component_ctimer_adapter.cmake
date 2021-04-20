#Description: Component ctimer_adapter; user_visible: True
include_guard(GLOBAL)
message("component_ctimer_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_ctimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_ctimer)
