#Description: Driver display-rm68191; user_visible: True
include_guard(GLOBAL)
message("driver_display-rm68191 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_rm68191.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_display-mipi-dsi-cmd)
include(driver_display-common)
