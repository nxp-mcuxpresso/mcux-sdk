if(NOT COMPONENT_WM8904_ADAPTER_INCLUDED)

    set(COMPONENT_WM8904_ADAPTER_INCLUDED true CACHE BOOL "component_wm8904_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
        include(driver_codec_LPC54114_cm4)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54628")
        include(driver_codec_LPC54628)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S16")
        include(driver_codec_LPC55S16)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018")
        include(driver_codec_LPC54S018)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
        include(driver_codec_LPC54S018M)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC51U68")
        include(driver_codec_LPC51U68)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
        include(driver_codec_LPC55S69_cm33_core0)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S28")
        include(driver_codec_LPC55S28)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
        include(driver_codec_MIMXRT685S_cm33)
    endif()

    include(driver_wm8904)

endif()