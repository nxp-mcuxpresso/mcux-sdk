#Description: Kinetis MMCAU security function library for Arm Cortex-M4 and Cortex-M7; user_visible: True
include_guard(GLOBAL)
message("middleware_mmcau_cm4_cm7 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(middleware_mmcau_common_files)
