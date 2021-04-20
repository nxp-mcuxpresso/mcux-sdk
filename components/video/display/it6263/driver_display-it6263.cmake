#Description: Driver display-it6263; user_visible: True
include_guard(GLOBAL)
message("driver_display-it6263 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_it6263.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_display-common)
include(driver_video-i2c)
