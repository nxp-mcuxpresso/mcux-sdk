#Description: power_s; user_visible: True
include_guard(GLOBAL)
message("driver_power_s component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_power.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


include(driver_common)
