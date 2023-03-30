#Description: DSPI Freertos Driver; user_visible: True
include_guard(GLOBAL)
message("driver_dspi_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dspi_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_dspi)
include(middleware_freertos-kernel_MK22F51212)
