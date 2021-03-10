if(NOT COMPONENT_CODEC_I2C_MK66F18_INCLUDED)

    set(COMPONENT_CODEC_I2C_MK66F18_INCLUDED true CACHE BOOL "component_codec_i2c component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_i2c.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(component_i2c_adapter)
    include(driver_common)

endif()