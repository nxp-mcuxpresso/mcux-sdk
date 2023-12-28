#Description: Component log backend debug console; user_visible: True
include_guard(GLOBAL)
message("component_log_backend_debugconsole component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_log_backend_debugconsole.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_log)
