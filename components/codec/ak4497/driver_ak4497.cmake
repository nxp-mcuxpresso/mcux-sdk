#Description: Driver ak4497; user_visible: True
include_guard(GLOBAL)
message("driver_ak4497 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ak4497.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_codec_i2c_MIMX8MM6)
