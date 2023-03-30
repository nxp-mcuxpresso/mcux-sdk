#Description: ENET CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_enet component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_cmsis.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_phy_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Driver_Include_Ethernet_PHY)
include(driver_enet)
include(CMSIS_Driver_Include_Ethernet_MAC)
include(driver_phy-common)
