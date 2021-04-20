#Description: Driver phy-device-ksz8081; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-ksz8081 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phyksz8081.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_phy-common)
