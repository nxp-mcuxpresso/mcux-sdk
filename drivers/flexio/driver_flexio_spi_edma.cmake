#Description: FLEXIO SPI EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexio_spi_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_spi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexio_spi)
include(driver_edma)
