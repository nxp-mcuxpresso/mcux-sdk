#Description: SPI CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_spi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_spi_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM14ZA5")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM34ZA5")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE02Z4")
    include(driver_spi)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2B11A")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2B21A")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM34Z7")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM33ZA5")
    include(driver_spi_dma)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE06Z4")
    include(driver_spi)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE04Z1284")
    include(driver_spi)
endif()

include(CMSIS_Driver_Include_SPI)
