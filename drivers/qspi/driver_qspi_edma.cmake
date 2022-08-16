#Description: QSPI EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_qspi_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_qspi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
    include(driver_edma_MCIMX7U5)
endif()
if(${MCUX_DEVICE} STREQUAL "MCIMX7U3")
    include(driver_edma_MCIMX7U5)
endif()
if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    include(driver_edma_MK28FA15)
endif()
if(${MCUX_DEVICE} STREQUAL "MK27FA15")
    include(driver_edma_MK28FA15)
endif()

include(driver_qspi)
