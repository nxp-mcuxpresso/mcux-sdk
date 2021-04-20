#Description: Driver dc-fb-elcdif; user_visible: True
include_guard(GLOBAL)
message("driver_dc-fb-elcdif component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_dc_fb_elcdif.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_dc-fb-common)
include(driver_elcdif)
