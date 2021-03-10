if(NOT DRIVER_CLOCK_INCLUDED)

    set(DRIVER_CLOCK_INCLUDED true CACHE BOOL "driver_clock component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_clock.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm0plus")
        include(driver_power)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
        include(driver_power)
    endif()

    include(driver_common)

endif()