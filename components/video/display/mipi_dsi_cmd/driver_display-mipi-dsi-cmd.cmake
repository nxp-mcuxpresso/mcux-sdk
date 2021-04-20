#Description: Driver display-mipi-dsi-cmd; user_visible: True
include_guard(GLOBAL)
message("driver_display-mipi-dsi-cmd component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_dsi_cmd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_mipi_dsi)
