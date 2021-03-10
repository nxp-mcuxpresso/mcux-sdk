if(NOT DRIVER_DISPLAY-COMMON_INCLUDED)

    set(DRIVER_DISPLAY-COMMON_INCLUDED true CACHE BOOL "driver_display-common component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_video-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_video-common)
    endif()


endif()