#Description: Driver srtm freertos; user_visible: True
include_guard(GLOBAL)
message("driver_srtm_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/srtm_heap_freertos.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm_mutex_freertos.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm_sem_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
)


include(driver_srtm)
