#Description: MMCAU library for ARM Cortex M0+ core; user_visible: True
include_guard(GLOBAL)
message("middleware_mmcau_cm0p component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(middleware_mmcau_common_files)
