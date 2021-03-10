if(NOT DRIVER_INPUTMUX_INCLUDED)

    set(DRIVER_INPUTMUX_INCLUDED true CACHE BOOL "driver_inputmux component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_inputmux.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC845")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm0plus")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54628")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC824")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S16")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC51U68")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core1")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S28")
        include(driver_inputmux_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
        include(driver_inputmux_connections)
    endif()

    include(driver_common)

endif()