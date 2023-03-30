#Description: Driver phy-device-rtl8201; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-rtl8201 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phyrtl8201.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_phy-common)
