include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_evkmimxrt1015)
# Add set(CONFIG_USE_BOARD_Project_Template_evkmimxrt1015 true) in config.cmake to use this component

message("BOARD_Project_Template_evkmimxrt1015 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_BOARD STREQUAL evkmimxrt1015) AND CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx) AND CONFIG_USE_device_MIMXRT1015_startup AND CONFIG_USE_driver_common AND CONFIG_USE_driver_igpio AND CONFIG_USE_driver_iomuxc AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_nic301 AND CONFIG_USE_driver_xip_board_evkmimxrt1015 AND CONFIG_USE_driver_xip_device AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.h "" BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.c "" BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c "" BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_evkmimxrt1015)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.c "" BOARD_Project_Template_evkmimxrt1015)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DXIP_EXTERNAL_FLASH=1
    -DXIP_BOOT_HEADER_ENABLE=1
  )

endif()

else()

message(SEND_ERROR "BOARD_Project_Template_evkmimxrt1015 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xip_board_evkmimxrt1015)
# Add set(CONFIG_USE_driver_xip_board_evkmimxrt1015 true) in config.cmake to use this component

message("driver_xip_board_evkmimxrt1015 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/xip/evkmimxrt1015_flexspi_nor_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/xip/.
)

else()

message(SEND_ERROR "driver_xip_board_evkmimxrt1015 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

