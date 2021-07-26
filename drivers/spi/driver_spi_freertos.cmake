#Description: SPI FREERTOS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_spi_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_spi_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    include(middleware_freertos-kernel_K32L2B31A)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM34ZA5")
    include(middleware_freertos-kernel_MKM34ZA5)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    include(middleware_freertos-kernel_MKM35Z7)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM34Z7")
    include(middleware_freertos-kernel_MKM34Z7)
endif()
if(${MCUX_DEVICE} STREQUAL "MKL27Z644")
    include(middleware_freertos-kernel_MKL27Z644)
endif()

include(driver_spi)
