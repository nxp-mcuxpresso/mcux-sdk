include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_evk9mimx8ulp)
# Add set(CONFIG_USE_BOARD_Project_Template_evk9mimx8ulp true) in config.cmake to use this component

message("BOARD_Project_Template_evk9mimx8ulp component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_BOARD STREQUAL evk9mimx8ulp) AND CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL MIMX8UD5xxx08) AND CONFIG_USE_device_MIMX8UD5_startup AND CONFIG_USE_driver_cache_cache64 AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_flexspi AND CONFIG_USE_driver_fusion AND CONFIG_USE_driver_iomuxc AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_reset AND CONFIG_USE_driver_rgpio AND CONFIG_USE_driver_upower AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_evk9mimx8ulp)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" BOARD_Project_Template_evk9mimx8ulp)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1
  )

endif()

else()

message(SEND_ERROR "BOARD_Project_Template_evk9mimx8ulp dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

