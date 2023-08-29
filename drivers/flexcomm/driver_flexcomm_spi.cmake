#Description: FLEXCOMM SPI Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexcomm_spi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/spi/fsl_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/spi/.
)


include(driver_flexcomm)
