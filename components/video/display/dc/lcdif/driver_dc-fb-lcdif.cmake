#Description: Driver dc-fb-lcdif; user_visible: True
include_guard(GLOBAL)
message("driver_dc-fb-lcdif component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dc_fb_lcdif.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lcdif)
include(driver_dc-fb-common)
