include_guard(GLOBAL)


if (CONFIG_USE_utility_xmcd_evkmimxrt1180)
# Add set(CONFIG_USE_utility_xmcd_evkmimxrt1180 true) in config.cmake to use this component

message("utility_xmcd_evkmimxrt1180 component is included from ${CMAKE_CURRENT_LIST_FILE}.")


endif()


if (CONFIG_USE_utility_jlinkscript_evkmimxrt1180)
# Add set(CONFIG_USE_utility_jlinkscript_evkmimxrt1180 true) in config.cmake to use this component

message("utility_jlinkscript_evkmimxrt1180 component is included from ${CMAKE_CURRENT_LIST_FILE}.")


endif()


if (CONFIG_USE_BOARD_Project_Template_evkmimxrt1180)
# Add set(CONFIG_USE_BOARD_Project_Template_evkmimxrt1180 true) in config.cmake to use this component

message("BOARD_Project_Template_evkmimxrt1180 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1189xxxxx) AND CONFIG_USE_device_MIMXRT1189_startup AND CONFIG_USE_device_MIMXRT1189_mcux_scripts AND CONFIG_USE_driver_common AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_rgpio AND CONFIG_USE_driver_iomuxc AND CONFIG_USE_driver_misc AND CONFIG_USE_driver_lpuart AND CONFIG_USE_component_lpuart_adapter AND CONFIG_USE_driver_dcdc_soc AND CONFIG_USE_driver_pmu_1 AND CONFIG_USE_driver_xip_board_evkmimxrt1180 AND CONFIG_USE_driver_xip_device AND (CONFIG_USE_driver_cache_armv7_m7 OR CONFIG_USE_driver_cache_xcache) AND ((CONFIG_USE_utility_debug_console AND CONFIG_USE_utility_assert AND CONFIG_USE_component_serial_manager) OR (CONFIG_USE_utility_debug_console_lite AND CONFIG_USE_utility_assert_lite)) AND (CONFIG_BOARD STREQUAL evkmimxrt1180))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/project_template/board.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c
  ${CMAKE_CURRENT_LIST_DIR}/project_template/project_template/peripherals.c
)

if(CONFIG_CORE STREQUAL cm7f)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm7/pin_mux.c
  )
endif()

if(CONFIG_CORE STREQUAL cm33)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/project_template/cm33/pin_mux.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

if(CONFIG_CORE STREQUAL cm7f)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm7
)
endif()

if(CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/cm33
)
endif()

else()

message(SEND_ERROR "BOARD_Project_Template_evkmimxrt1180 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xip_board_evkmimxrt1180)
# Add set(CONFIG_USE_driver_xip_board_evkmimxrt1180 true) in config.cmake to use this component

message("driver_xip_board_evkmimxrt1180 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/xip/evkmimxrt1180_flexspi_nor_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/xip/.
)

else()

message(SEND_ERROR "driver_xip_board_evkmimxrt1180 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

