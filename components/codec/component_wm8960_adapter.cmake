#Description: Component wm8960_adapter; user_visible: True
include_guard(GLOBAL)
message("component_wm8960_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/wm8960/fsl_codec_wm8960_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/wm8960
)


include(driver_wm8960)
