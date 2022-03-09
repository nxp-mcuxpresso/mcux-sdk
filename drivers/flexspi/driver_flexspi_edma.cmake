#Description: FLEXSPI EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexspi_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexspi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(driver_edma_MIMXRT1166_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(driver_edma_MIMXRT1166_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(driver_edma_MIMXRT1064)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
    include(driver_edma_MIMXRT1021)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(driver_edma_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(driver_edma_MIMXRT1176_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
    include(driver_edma_MIMXRT1024)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
    include(driver_edma_MIMXRT1011)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
    include(driver_edma_MIMXRT1015)
endif()

include(driver_flexspi)
