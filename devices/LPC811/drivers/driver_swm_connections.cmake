<<<<<<<< HEAD:devices/LPC811/drivers/driver_swm_connections.cmake
#Description: Swm_connections Driver; user_visible: True
include_guard(GLOBAL)
message("driver_swm_connections component is included.")
========
#Description: Utility shell; user_visible: True
include_guard(GLOBAL)
message("utility_shell component is included.")
>>>>>>>> MCUX_2.14.0:devices/K32L2A31A/utilities/utility_shell.cmake

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_shell.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
