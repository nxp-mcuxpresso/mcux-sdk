#Description: Driver phy-device-lan8720a; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-lan8720a component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phylan8720a.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_phy-common)
