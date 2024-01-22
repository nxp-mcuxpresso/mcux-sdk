#Description: II2C CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_ii2c component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_i2c_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_ii2c)
include(CMSIS_Driver_Include_I2C)
