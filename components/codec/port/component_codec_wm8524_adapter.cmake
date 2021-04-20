#Description: Component wm8524 adapter for multi codecs; user_visible: True
include_guard(GLOBAL)
message("component_codec_wm8524_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_wm8524_adapter.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_wm8524)
