if(NOT DRIVER_SRTM_FREERTOS_INCLUDED)

    set(DRIVER_SRTM_FREERTOS_INCLUDED true CACHE BOOL "driver_srtm_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/srtm_heap_freertos.c
        ${CMAKE_CURRENT_LIST_DIR}/srtm_mutex_freertos.c
        ${CMAKE_CURRENT_LIST_DIR}/srtm_sem_freertos.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(driver_srtm)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_srtm)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_srtm)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
        include(driver_srtm)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
        include(driver_srtm)
    endif()


endif()