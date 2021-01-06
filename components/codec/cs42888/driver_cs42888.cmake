if(NOT DRIVER_CS42888_INCLUDED)

    set(DRIVER_CS42888_INCLUDED true CACHE BOOL "driver_cs42888 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_cs42888.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(component_codec_i2c)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(component_codec_i2c)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(component_codec_i2c)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(component_codec_i2c)
    endif()

    include(driver_common)

endif()