if(NOT COMPONENT_CS42888_ADAPTER_INCLUDED)

    set(COMPONENT_CS42888_ADAPTER_INCLUDED true CACHE BOOL "component_cs42888_adapter component is included.")

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
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(driver_codec_MIMX8QM6_cm4_core0)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_codec_MIMX8QM6_cm4_core1)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_codec_MIMX8QX6)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
        include(driver_codec_MIMXRT685S_cm33)
    endif()

    include(driver_cs42888)

endif()