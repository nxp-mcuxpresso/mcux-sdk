#Description: CMSIS DSP Library; user_visible: True
include_guard(GLOBAL)
message("CMSIS_DSP_Library component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Include
)


