#Description: FLEXIO I2S EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexio_i2s_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_i2s_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexio_i2s)
include(driver_edma)
