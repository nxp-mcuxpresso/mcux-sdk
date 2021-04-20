#Description: Driver mdio-lpc-enet; user_visible: True
include_guard(GLOBAL)
message("driver_mdio-lpc-enet component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_mdio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpc_enet)
include(driver_mdio-common)
