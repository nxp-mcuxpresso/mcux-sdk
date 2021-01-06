if(NOT DRIVER_CODEC_MIMXRT1064_INCLUDED)

    set(DRIVER_CODEC_MIMXRT1064_INCLUDED true CACHE BOOL "driver_codec component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_common.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(CONFIG_USE_component_wm8960_adapter) 
        include(component_wm8960_adapter)
    endif()

    include(driver_common)

endif()