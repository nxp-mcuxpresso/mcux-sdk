if(NOT COMPONENT_CTIMER_ADAPTER_INCLUDED)

    set(COMPONENT_CTIMER_ADAPTER_INCLUDED true CACHE BOOL "component_ctimer_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_ctimer.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
        include(driver_ctimer)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54628")
        include(driver_ctimer)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018")
        include(driver_ctimer)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
        include(driver_ctimer)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC51U68")
        include(driver_ctimer)
    endif()

    include(driver_common)

endif()