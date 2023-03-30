#Description: asrc_edma Driver; user_visible: True
include_guard(GLOBAL)
message("driver_asrc_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_asrc_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(driver_edma_MIMXRT1166_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1171_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1172_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1165_cm7")
    include(driver_edma_MIMXRT1166_cm7)
endif()

include(driver_edma_MIMXRT1176_cm7)
include(driver_asrc)
