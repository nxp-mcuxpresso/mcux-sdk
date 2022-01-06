#Description: Component tfa9xxx_adapter; user_visible: True
include_guard(GLOBAL)
message("component_tfa9xxx_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/tfa9xxx/fsl_codec_tfa9xxx_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/tfa9xxx
)


include(driver_tfa9xxx)
