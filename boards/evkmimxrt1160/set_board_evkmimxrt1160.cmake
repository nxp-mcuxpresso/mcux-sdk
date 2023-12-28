include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_evkmimxrt1160)
# Add set(CONFIG_USE_BOARD_Project_Template_evkmimxrt1160 true) in config.cmake to use this component

message("BOARD_Project_Template_evkmimxrt1160 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx) AND CONFIG_USE_device_MIMXRT1166_startup AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_dcdc_soc AND CONFIG_USE_driver_igpio AND CONFIG_USE_driver_iomuxc AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_nic301 AND CONFIG_USE_driver_pmu_1 AND CONFIG_USE_driver_xip_board_evkmimxrt1160 AND CONFIG_USE_driver_xip_device AND CONFIG_USE_driver_xmcd_evkmimxrt1160 AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)) AND (CONFIG_BOARD STREQUAL evkmimxrt1160))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/project_template/board.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/project_template/peripherals.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/project_template/dcd.c
)

if(CONFIG_CORE STREQUAL cm7f)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm7/pin_mux.c
  )
endif()

if(CONFIG_CORE STREQUAL cm4f)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm4/pin_mux.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
  ${CMAKE_CURRENT_LIST_DIR}/project_template/project_template
)

if(CONFIG_CORE STREQUAL cm7f)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm7
)
endif()

if(CONFIG_CORE STREQUAL cm4f)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm4
)
endif()

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DXIP_EXTERNAL_FLASH=1
    -DXIP_BOOT_HEADER_ENABLE=1
    -DXIP_BOOT_HEADER_DCD_ENABLE=0
    -DXIP_BOOT_HEADER_XMCD_ENABLE=1
  )

endif()

else()

message(SEND_ERROR "BOARD_Project_Template_evkmimxrt1160 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xip_board_evkmimxrt1160)
# Add set(CONFIG_USE_driver_xip_board_evkmimxrt1160 true) in config.cmake to use this component

message("driver_xip_board_evkmimxrt1160 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/xip/evkmimxrt1160_flexspi_nor_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/xip/.
)

else()

message(SEND_ERROR "driver_xip_board_evkmimxrt1160 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xmcd_evkmimxrt1160)
# Add set(CONFIG_USE_driver_xmcd_evkmimxrt1160 true) in config.cmake to use this component

message("driver_xmcd_evkmimxrt1160 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_BOARD STREQUAL evkmimxrt1160))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/xmcd/xmcd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/xmcd/.
)

else()

message(SEND_ERROR "driver_xmcd_evkmimxrt1160 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

