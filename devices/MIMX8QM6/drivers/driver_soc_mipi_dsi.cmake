#Description: SOC MIPI DSI Driver; user_visible: True
include_guard(GLOBAL)
message("driver_soc_mipi_dsi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
