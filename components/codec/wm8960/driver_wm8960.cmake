#Description: Driver wm8960; user_visible: True
include_guard(GLOBAL)
message("driver_wm8960 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_wm8960.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(component_codec_i2c_MIMXRT1052)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(component_codec_i2c_MIMXRT1064)
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
if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
    include(component_codec_i2c_MIMXRT1021)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_codec_i2c_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
    include(component_codec_i2c_MCIMX7U5)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
    include(component_codec_i2c_MIMXRT1024)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
    include(component_codec_i2c_MIMXRT1011)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
    include(component_codec_i2c_MIMXRT1015)
endif()

