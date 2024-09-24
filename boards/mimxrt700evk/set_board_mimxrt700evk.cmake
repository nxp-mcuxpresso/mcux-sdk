include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_mimxrt700evk)
# Add set(CONFIG_USE_BOARD_Project_Template_mimxrt700evk true) in config.cmake to use this component

message("BOARD_Project_Template_mimxrt700evk component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpflexcomm AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_lpc_iopctl AND CONFIG_USE_driver_gpio AND CONFIG_USE_driver_reset AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_device_MIMXRT798S_startup AND CONFIG_USE_driver_common AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_glikey AND (CONFIG_BOARD STREQUAL mimxrt700evk) AND ((CONFIG_USE_utility_debug_console AND CONFIG_USE_utility_assert AND CONFIG_USE_component_serial_manager) OR (CONFIG_USE_utility_debug_console_lite AND CONFIG_USE_utility_assert_lite)) AND ((CONFIG_USE_driver_xspi AND CONFIG_USE_driver_cache_xcache AND CONFIG_USE_driver_flash_config_mimxrt700evk AND CONFIG_USE_driver_power AND (CONFIG_CORE_ID STREQUAL cm33_core0)) OR (CONFIG_USE_driver_power AND (CONFIG_CORE_ID STREQUAL cm33_core1))))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.h "" BOARD_Project_Template_mimxrt700evk)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.c "" BOARD_Project_Template_mimxrt700evk)

if(CONFIG_CORE_ID STREQUAL cm33_core0)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/clock_config.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/clock_config.c "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/pin_mux.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/pin_mux.c "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/peripherals.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0/peripherals.c "" BOARD_Project_Template_mimxrt700evk)
endif()

if(CONFIG_CORE_ID STREQUAL cm33_core1)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/clock_config.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/clock_config.c "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/pin_mux.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/pin_mux.c "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/peripherals.h "" BOARD_Project_Template_mimxrt700evk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1/peripherals.c "" BOARD_Project_Template_mimxrt700evk)
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

if(CONFIG_CORE_ID STREQUAL cm33_core0)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core0
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1
  ${CMAKE_CURRENT_LIST_DIR}/project_template/ezhv
  ${CMAKE_CURRENT_LIST_DIR}/project_template/hifi1
  ${CMAKE_CURRENT_LIST_DIR}/project_template/hifi4
)
endif()

if(CONFIG_CORE_ID STREQUAL cm33_core1)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm33_core1
)
endif()

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1
  )

endif()

else()

message(SEND_ERROR "BOARD_Project_Template_mimxrt700evk dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

