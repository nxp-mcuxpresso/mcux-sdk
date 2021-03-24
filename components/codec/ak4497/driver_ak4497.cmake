if(NOT DRIVER_AK4497_INCLUDED)

    set(DRIVER_AK4497_INCLUDED true CACHE BOOL "driver_ak4497 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ak4497.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)
    include(component_codec_i2c_MIMX8MM6)

endif()