#Description: DMIC DMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_dmic_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dmic_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpc_dma)
include(driver_dmic)
