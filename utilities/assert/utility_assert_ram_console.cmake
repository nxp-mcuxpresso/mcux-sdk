#Description: Utility assert with RAM Console; user_visible: True
include_guard(GLOBAL)
message("utility_assert with RAM Console component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(utility_ram_console)
