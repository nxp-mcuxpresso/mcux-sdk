if(NOT COMPONENT_CODEC_WM8524_ADAPTER_INCLUDED)

    set(COMPONENT_CODEC_WM8524_ADAPTER_INCLUDED true CACHE BOOL "component_codec_wm8524_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_wm8524_adapter.c
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(driver_codec_MIMX8MM6)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
        include(driver_codec_MIMX8MN6)
    endif()

    include(driver_wm8524)

endif()