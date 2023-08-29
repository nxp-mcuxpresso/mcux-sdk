#Description: FLEXCOMM I2S Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexcomm_i2s component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/i2s/fsl_i2s.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/i2s/.
)


include(driver_flexcomm)
