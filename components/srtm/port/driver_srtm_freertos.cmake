#Description: Driver srtm freertos; user_visible: True
include_guard(GLOBAL)
message("driver_srtm_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/srtm_heap_freertos.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm_mutex_freertos.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm_sem_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    include(driver_srtm_MIMX8MM6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
    include(driver_srtm_MIMX8MN6)
endif()
if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
    include(driver_srtm_MCIMX7U5)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8ML8")
    include(driver_srtm_MIMX8ML8)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(driver_srtm_MIMX8QM6_cm4_core1)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(driver_srtm_MIMX8QX6)
endif()

