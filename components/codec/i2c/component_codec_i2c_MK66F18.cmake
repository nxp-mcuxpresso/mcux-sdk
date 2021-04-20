#Description: Component codec_i2c; user_visible: True
include_guard(GLOBAL)
message("component_codec_i2c component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_i2c_adapter)
