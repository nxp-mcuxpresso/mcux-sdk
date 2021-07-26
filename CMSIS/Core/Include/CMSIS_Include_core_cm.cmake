#Description: CMSIS Include For Cortex-M, ARMv8-M, ARMv8.1-M; user_visible: True
include_guard(GLOBAL)
message("CMSIS_Include_core_cm component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


