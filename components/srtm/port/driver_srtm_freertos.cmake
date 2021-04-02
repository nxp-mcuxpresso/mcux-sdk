if(NOT DRIVER_SRTM_FREERTOS_INCLUDED)

    set(DRIVER_SRTM_FREERTOS_INCLUDED true CACHE BOOL "driver_srtm_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/srtm_heap_freertos.c
        ${CMAKE_CURRENT_LIST_DIR}/srtm_mutex_freertos.c
        ${CMAKE_CURRENT_LIST_DIR}/srtm_sem_freertos.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )


    include(driver_srtm)

endif()