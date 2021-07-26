#Description: Driver cs42448; user_visible: True
include_guard(GLOBAL)
message("driver_cs42448 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_cs42448.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_codec_i2c_MIMXRT1062)
