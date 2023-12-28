#Description: DMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_lpc_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(driver_memory)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(driver_memory)
endif()

include(driver_common)
