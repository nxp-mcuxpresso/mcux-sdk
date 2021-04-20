#Description: Driver dbi_flexio_edma; user_visible: True
include_guard(GLOBAL)
message("driver_dbi_flexio_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dbi_flexio_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexio_mculcd_edma)
include(driver_dbi)
