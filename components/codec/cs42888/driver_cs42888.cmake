#Description: Driver cs42888; user_visible: True
include_guard(GLOBAL)
message("driver_cs42888 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_cs42888.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(component_codec_i2c_MIMXRT1052)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    include(component_codec_i2c_MIMX8QM6_cm4_core0)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(component_codec_i2c_MIMX8QM6_cm4_core1)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(component_codec_i2c_MIMX8QX6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(component_codec_i2c_MIMXRT685S_cm33)
endif()

