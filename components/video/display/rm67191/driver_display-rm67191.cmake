#Description: Driver display-rm67191; user_visible: True
include_guard(GLOBAL)
message("driver_display-rm67191 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_rm67191.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_display-mipi-dsi-cmd)
include(driver_display-common)
