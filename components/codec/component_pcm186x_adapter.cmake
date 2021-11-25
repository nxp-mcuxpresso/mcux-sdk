#Description: Component pcm186x_adapter; user_visible: True
include_guard(GLOBAL)
message("component_pcm186x_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/pcm186x/fsl_codec_pcm186x_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/pcm186x
)


include(driver_pcm186x)
