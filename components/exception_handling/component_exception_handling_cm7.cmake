#Description: Component exception_handling_cm7; user_visible: True
include_guard(GLOBAL)
message("component_exception_handling_cm7 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/cm7/fsl_component_exception_handling.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(utility_debug_console)
