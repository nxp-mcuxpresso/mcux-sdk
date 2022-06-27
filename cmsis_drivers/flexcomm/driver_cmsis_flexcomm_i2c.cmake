#Description: I2C CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_flexcomm_i2c component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_i2c_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Driver_Include_I2C)
include(driver_flexcomm_i2c_dma)
