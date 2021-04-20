#Description: Utility assert; user_visible: True
include_guard(GLOBAL)
message("utility_assert component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
)


include(utility_debug_console)
