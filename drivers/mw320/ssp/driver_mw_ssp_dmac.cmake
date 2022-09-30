#Description: MW_SSP_DMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_mw_ssp_dmac component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ssp_dmac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_mw_dmac)
include(driver_mw_ssp)
