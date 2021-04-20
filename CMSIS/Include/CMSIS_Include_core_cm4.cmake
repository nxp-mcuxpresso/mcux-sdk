#Description: Cmsis_include_core_cm4; user_visible: True
include_guard(GLOBAL)
message("CMSIS_Include_core_cm4 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Include_common)
include(CMSIS_Include_dsp)
