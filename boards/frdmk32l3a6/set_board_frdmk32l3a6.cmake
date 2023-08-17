include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_frdmk32l3a6)
# Add set(CONFIG_USE_BOARD_Project_Template_frdmk32l3a6 true) in config.cmake to use this component

message("BOARD_Project_Template_frdmk32l3a6 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL K32L3A60xxx) AND CONFIG_USE_device_K32L3A60_startup AND CONFIG_USE_driver_common AND CONFIG_USE_driver_gpio AND CONFIG_USE_driver_lpi2c AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_msmc AND CONFIG_USE_driver_port AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)) AND (CONFIG_BOARD STREQUAL frdmk32l3a6))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/project_template/board.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c
)

if(CONFIG_CORE STREQUAL cm4f)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm4/pin_mux.c
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm4/peripherals.c
  )
endif()

if(CONFIG_CORE STREQUAL cm0p)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm0plus/pin_mux.c
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm0plus/peripherals.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

if(CONFIG_CORE STREQUAL cm4f)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm4
)
endif()

if(CONFIG_CORE STREQUAL cm0p)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm0plus
)
endif()

else()

message(SEND_ERROR "BOARD_Project_Template_frdmk32l3a6 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

