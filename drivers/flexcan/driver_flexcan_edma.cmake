#Description: FLEXCAN EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexcan_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexcan_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(driver_edma)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    include(driver_dma3)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(driver_dma3)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV11Z7")
    include(driver_edma)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(driver_dma3)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(driver_edma)
endif()

include(driver_flexcan)
