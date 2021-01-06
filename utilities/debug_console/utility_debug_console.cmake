if(NOT UTILITY_DEBUG_CONSOLE_INCLUDED)

    set(UTILITY_DEBUG_CONSOLE_INCLUDED true CACHE BOOL "utility_debug_console component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
        ${CMAKE_CURRENT_LIST_DIR}/debug_console/fsl_debug_console.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/debug_console
        ${CMAKE_CURRENT_LIST_DIR}/str
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(component_serial_manager_MIMX8MM6)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(component_serial_manager_MIMXRT1064)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
        include(component_serial_manager_MIMXRT1011)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK28FA15")
        include(component_serial_manager_MK28FA15)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(component_serial_manager_MIMXRT1021)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
        include(component_serial_manager_MIMXRT1015)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(component_serial_manager_MIMXRT1024)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(component_serial_manager_MIMXRT1052)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(component_serial_manager_MIMXRT1062)
    endif()

    include(driver_common)

endif()