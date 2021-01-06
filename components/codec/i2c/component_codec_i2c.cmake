if(NOT COMPONENT_CODEC_I2C_INCLUDED)

    set(COMPONENT_CODEC_I2C_INCLUDED true CACHE BOOL "component_codec_i2c component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_i2c.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MK66F18")
        include(component_i2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(component_lpi2c_adapter)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(component_lpi2c_adapter)
    endif()

    include(driver_common)

endif()