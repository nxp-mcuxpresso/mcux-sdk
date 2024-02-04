#Description: SMARTDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_lpc_smartdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_smartdma.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_smartdma_rt500.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_smartdma_mcxn.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
