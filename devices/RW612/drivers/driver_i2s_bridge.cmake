#Description: I2S Bridging and Signal Sharing Driver; user_visible: True
include_guard(GLOBAL)
message("driver_i2s_bridge component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_i2s_bridge.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
