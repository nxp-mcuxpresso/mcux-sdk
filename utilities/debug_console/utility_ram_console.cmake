#Description: Utility ram_console; user_visible: True
include_guard(GLOBAL)
message("utility_ram_console component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_console/fsl_ram_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/str
)
