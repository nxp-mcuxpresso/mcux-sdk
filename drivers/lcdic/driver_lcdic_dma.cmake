#Description: LCDIC DMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_lcdic_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_lcdic_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpc_dma)
include(driver_lcdic)
