#Description: Component tfa9896_adapter; user_visible: True
include_guard(GLOBAL)
message("component_tfa9896_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/tfa9896/fsl_codec_tfa9896_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/tfa9896
)


include(driver_tfa9896)
