#Description: Wi-Fi module Tx power limits; user_visible: True
include_guard(GLOBAL)
message("component_wifi_bt_module_tx_pwr_limits component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/AzureWave/tx_pwr_limits
    ${CMAKE_CURRENT_LIST_DIR}/Murata/tx_pwr_limits
)


