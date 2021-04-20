#Description: Driver phy-device-ar8031; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-ar8031 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phyar8031.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_phy-common)
