#Description: Driver dc-fb-dsi-cmd; user_visible: True
include_guard(GLOBAL)
message("driver_dc-fb-dsi-cmd component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dc_fb_dsi_cmd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_dc-fb-common)
include(driver_display-common)
include(driver_display-mipi-dsi-cmd)
