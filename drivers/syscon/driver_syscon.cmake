if(NOT DRIVER_SYSCON_INCLUDED)

    set(DRIVER_SYSCON_INCLUDED true CACHE BOOL "driver_syscon component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_syscon.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC845")
        include(driver_syscon_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC812")
        include(driver_syscon_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC802")
        include(driver_syscon_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC824")
        include(driver_syscon_connections)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC804")
        include(driver_syscon_connections)
    endif()

    include(driver_common)

endif()