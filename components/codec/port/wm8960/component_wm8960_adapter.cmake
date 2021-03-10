if(NOT COMPONENT_WM8960_ADAPTER_INCLUDED)

    set(COMPONENT_WM8960_ADAPTER_INCLUDED true CACHE BOOL "component_wm8960_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(driver_codec_MIMXRT1052)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(driver_codec_MIMXRT1064)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(driver_codec_MIMX8QM6_cm4_core0)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_codec_MIMX8QM6_cm4_core1)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_codec_MIMX8QX6)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(driver_codec_MIMXRT1021)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(driver_codec_MIMXRT1062)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
        include(driver_codec_MCIMX7U5)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(driver_codec_MIMXRT1024)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
        include(driver_codec_MIMXRT1011)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
        include(driver_codec_MIMXRT1015)
    endif()

    include(driver_wm8960)

endif()