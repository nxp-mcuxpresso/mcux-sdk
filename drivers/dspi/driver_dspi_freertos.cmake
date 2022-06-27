#Description: DSPI Freertos Driver; user_visible: True
include_guard(GLOBAL)
message("driver_dspi_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dspi_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MKV58F24")
    include(middleware_freertos-kernel_MKV58F24)
endif()
if(${MCUX_DEVICE} STREQUAL "MK64F12")
    include(middleware_freertos-kernel_MK64F12)
endif()
if(${MCUX_DEVICE} STREQUAL "MK66F18")
    include(middleware_freertos-kernel_MK66F18)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV31F51212")
    include(middleware_freertos-kernel_MKV31F51212)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    include(middleware_freertos-kernel_MK22F51212)
endif()
if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    include(middleware_freertos-kernel_MK28FA15)
endif()

include(driver_dspi)
