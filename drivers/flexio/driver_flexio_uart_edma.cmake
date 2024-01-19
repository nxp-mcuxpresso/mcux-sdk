#Description: FLEXIO UART EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexio_uart_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/uart/fsl_flexio_uart_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/uart/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(driver_edma_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(driver_edma_MIMXRT1042)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(driver_edma_MIMXRT1176_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(driver_edma_MIMXRT1176_cm7)
endif()

include(driver_flexio_uart)
