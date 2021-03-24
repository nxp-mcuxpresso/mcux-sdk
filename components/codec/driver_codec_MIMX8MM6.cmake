if(NOT DRIVER_CODEC_MIMX8MM6_INCLUDED)

    set(DRIVER_CODEC_MIMX8MM6_INCLUDED true CACHE BOOL "driver_codec component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_common.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(CONFIG_USE_component_wm8524_adapter) 
        include(component_wm8524_adapter)
    endif()
    if(CONFIG_USE_component_codec_wm8524_adapter) 
        include(component_codec_wm8524_adapter)
    endif()
    if(CONFIG_USE_component_codec_ak4497_adapter) 
        include(component_codec_ak4497_adapter)
    endif()

    include(driver_common)

endif()