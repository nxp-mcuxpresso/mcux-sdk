#Description: MIPI DSI Driver; user_visible: True
include_guard(GLOBAL)
message("driver_mipi_dsi_split component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_dsi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_soc_mipi_csi2rx)
