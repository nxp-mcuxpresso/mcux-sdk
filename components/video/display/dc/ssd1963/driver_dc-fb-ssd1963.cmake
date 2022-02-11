#Description: Driver dc-fb-ssd1963; user_visible: True
include_guard(GLOBAL)
message("driver_dc-fb-ssd1963 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dc_fb_ssd1963.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_ssd1963)
include(driver_dc-fb-common)
