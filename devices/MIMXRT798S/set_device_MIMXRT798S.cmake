include_guard(GLOBAL)


if (CONFIG_USE_driver_flash_config_mimxrt700evk)
# Add set(CONFIG_USE_driver_flash_config_mimxrt700evk true) in config.cmake to use this component

message("driver_flash_config_mimxrt700evk component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/mimxrt700evk/flash_config/flash_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/mimxrt700evk/flash_config/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DBOOT_HEADER_ENABLE=1
  )

endif()


endif()


if (CONFIG_USE_utility_incbin)
# Add set(CONFIG_USE_utility_incbin true) in config.cmake to use this component

message("utility_incbin component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_incbin.S
  )
endif()


endif()


if (CONFIG_USE_middleware_baremetal)
# Add set(CONFIG_USE_middleware_baremetal true) in config.cmake to use this component

message("middleware_baremetal component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_OS_BAREMETAL
  )

endif()


endif()


if (CONFIG_USE_RTE_Device)
# Add set(CONFIG_USE_RTE_Device true) in config.cmake to use this component

message("RTE_Device component is included from ${CMAKE_CURRENT_LIST_FILE}.")

add_config_file(${CMAKE_CURRENT_LIST_DIR}/template/RTE_Device.h ${CMAKE_CURRENT_LIST_DIR}/template/. RTE_Device.MIMXRT798S)


endif()


if (CONFIG_USE_utilities_misc_utilities)
# Add set(CONFIG_USE_utilities_misc_utilities true) in config.cmake to use this component

message("utilities_misc_utilities component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_sbrk.c
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_syscall_stub.c
  )
endif()

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux) AND CONFIG_CORE STREQUAL cm33)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_memcpy.S
  )
endif()


endif()


if (CONFIG_USE_driver_nand_flash-common)
# Add set(CONFIG_USE_driver_nand_flash-common true) in config.cmake to use this component

message("driver_nand_flash-common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nand/.
)


endif()


if (CONFIG_USE_driver_nor_flash-common)
# Add set(CONFIG_USE_driver_nor_flash-common true) in config.cmake to use this component

message("driver_nor_flash-common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/.
)


endif()


if (CONFIG_USE_driver_sfdp_parser)
# Add set(CONFIG_USE_driver_sfdp_parser true) in config.cmake to use this component

message("driver_sfdp_parser component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/fsl_sfdp_parser.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/.
)


endif()


if (CONFIG_USE_component_mflash_common)
# Add set(CONFIG_USE_component_mflash_common true) in config.cmake to use this component

message("component_mflash_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/.
)


endif()


if (CONFIG_USE_driver_p3t1755)
# Add set(CONFIG_USE_driver_p3t1755 true) in config.cmake to use this component

message("driver_p3t1755 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/p3t1755/fsl_p3t1755.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/p3t1755/.
)


endif()


if (CONFIG_USE_component_wifi_bt_module_tx_pwr_limits)
# Add set(CONFIG_USE_component_wifi_bt_module_tx_pwr_limits true) in config.cmake to use this component

message("component_wifi_bt_module_tx_pwr_limits component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module/AzureWave/tx_pwr_limits
  ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module/Murata/tx_pwr_limits
  ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module/u-blox/tx_pwr_limits
)


endif()


if (CONFIG_USE_component_wifi_bt_module_config)
# Add set(CONFIG_USE_component_wifi_bt_module_config true) in config.cmake to use this component

message("component_wifi_bt_module_config component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module/incl
)


endif()


if (CONFIG_USE_arch_RISCV_Include_core)
# Add set(CONFIG_USE_arch_RISCV_Include_core true) in config.cmake to use this component

message("arch_RISCV_Include_core component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../arch/riscv/.
)


endif()


if (CONFIG_USE_utilities_unity)
# Add set(CONFIG_USE_utilities_unity true) in config.cmake to use this component

message("utilities_unity component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_TOOLCHAIN STREQUAL mcux)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/unity/linkscripts/main_text.ldt
  )
endif()

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/unity/unity.c
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/unity/gcov_support.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/unity/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  if(CONFIG_TOOLCHAIN STREQUAL mcux)
    target_compile_options(${MCUX_SDK_PROJECT_NAME} PUBLIC
    )
  endif()

endif()


endif()


if (CONFIG_USE_driver_rtt_template)
# Add set(CONFIG_USE_driver_rtt_template true) in config.cmake to use this component

message("driver_rtt_template component is included from ${CMAKE_CURRENT_LIST_FILE}.")

add_config_file(${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/template/SEGGER_RTT_Conf.h ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/template driver_rtt_template.MIMXRT798S)


endif()


if (CONFIG_USE_DEVICES_Project_Template_MIMXRT798S)
# Add set(CONFIG_USE_DEVICES_Project_Template_MIMXRT798S true) in config.cmake to use this component

message("DEVICES_Project_Template_MIMXRT798S component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpflexcomm AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_lpc_iopctl AND CONFIG_USE_driver_gpio AND CONFIG_USE_driver_cache_xcache AND CONFIG_USE_driver_reset AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_device_MIMXRT798S_startup AND CONFIG_USE_driver_common AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_power AND ((CONFIG_USE_utility_debug_console AND CONFIG_USE_utility_assert AND CONFIG_USE_component_serial_manager) OR (CONFIG_USE_utility_debug_console_lite AND CONFIG_USE_utility_assert_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.h "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.c "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.h "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.h "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.c "" DEVICES_Project_Template_MIMXRT798S.MIMXRT798S)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

else()

message(SEND_ERROR "DEVICES_Project_Template_MIMXRT798S.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_system)
# Add set(CONFIG_USE_device_MIMXRT798S_system true) in config.cmake to use this component

message("device_MIMXRT798S_system component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_device_MIMXRT798S_CMSIS)

if(CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core0)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_cm33_core0.c
  )
endif()

if(CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core1)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_cm33_core1.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "device_MIMXRT798S_system.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_startup)
# Add set(CONFIG_USE_device_MIMXRT798S_startup true) in config.cmake to use this component

message("device_MIMXRT798S_startup component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_USE_device_MIMXRT798S_system AND (CONFIG_CORE STREQUAL cm33)) OR (CONFIG_USE_device_MIMXRT798S_cm33_core0 AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_USE_device_MIMXRT798S_cm33_core1 AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_USE_device_MIMXRT798S_ezhv AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_USE_device_MIMXRT798S_hifi1 AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_USE_device_MIMXRT798S_hifi4 AND (CONFIG_CORE STREQUAL ezhv)))

if(CONFIG_TOOLCHAIN STREQUAL armgcc AND CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core0)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./gcc/startup_MIMXRT798S_cm33_core0.S
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux AND CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core0)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mimxrt798s_cm33_core0.c
      ${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mimxrt798s_cm33_core0.cpp
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc AND CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core1)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./gcc/startup_MIMXRT798S_cm33_core1.S
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux AND CONFIG_CORE STREQUAL cm33 AND CONFIG_CORE_ID STREQUAL cm33_core1)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mimxrt798s_cm33_core1.c
      ${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mimxrt798s_cm33_core1.cpp
  )
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_startup.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_CMSIS)
# Add set(CONFIG_USE_device_MIMXRT798S_CMSIS true) in config.cmake to use this component

message("device_MIMXRT798S_CMSIS component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_CMSIS_Include_core_cm)

if(CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_CMSIS.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_cm33_core0)
# Add set(CONFIG_USE_device_MIMXRT798S_cm33_core0 true) in config.cmake to use this component

message("device_MIMXRT798S_cm33_core0 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND ((CONFIG_USE_arch_RISCV_Include_core AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_CORE STREQUAL dsp)))

if(CONFIG_TOOLCHAIN STREQUAL xcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_cm33_core0.c
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL xcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_cm33_core0.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dbi_lcdif)
# Add set(CONFIG_USE_driver_dbi_lcdif true) in config.cmake to use this component

message("driver_dbi_lcdif component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_mipi_dsi AND CONFIG_USE_driver_dbi AND CONFIG_USE_driver_lcdif)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/lcdif/fsl_dbi_lcdif.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/lcdif/.
)

else()

message(SEND_ERROR "driver_dbi_lcdif.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_utick)
# Add set(CONFIG_USE_driver_utick true) in config.cmake to use this component

message("driver_utick component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_power AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick/fsl_utick.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick/.
)

else()

message(SEND_ERROR "driver_utick.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dsp)
# Add set(CONFIG_USE_driver_dsp true) in config.cmake to use this component

message("driver_dsp component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_power AND CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_dsp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_dsp.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_edma4)
# Add set(CONFIG_USE_driver_edma4 true) in config.cmake to use this component

message("driver_edma4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma_soc AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma4/fsl_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma4/.
)

else()

message(SEND_ERROR "driver_edma4.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_edma_soc)
# Add set(CONFIG_USE_driver_edma_soc true) in config.cmake to use this component

message("driver_edma_soc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_edma_soc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_edma_soc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_uart)
# Add set(CONFIG_USE_component_serial_manager_uart true) in config.cmake to use this component

message("component_serial_manager_uart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_lpuart_adapter AND CONFIG_USE_component_serial_manager AND (CONFIG_USE_driver_lpuart))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_port_uart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSERIAL_PORT_TYPE_UART=1
  )

endif()

else()

message(SEND_ERROR "component_serial_manager_uart.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_debug_console_lite)
# Add set(CONFIG_USE_utility_debug_console_lite true) in config.cmake to use this component

message("utility_debug_console_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_utility_str)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
)

else()

message(SEND_ERROR "utility_debug_console_lite.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_sai_edma)
# Add set(CONFIG_USE_driver_sai_edma true) in config.cmake to use this component

message("driver_sai_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_sai AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai/fsl_sai_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai/.
)

else()

message(SEND_ERROR "driver_sai_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpuart_edma)
# Add set(CONFIG_USE_driver_lpuart_edma true) in config.cmake to use this component

message("driver_lpuart_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpuart/fsl_lpuart_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpuart/.
)

else()

message(SEND_ERROR "driver_lpuart_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpspi_edma)
# Add set(CONFIG_USE_driver_lpspi_edma true) in config.cmake to use this component

message("driver_lpspi_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_lpspi AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpspi/fsl_lpspi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpspi/.
)

else()

message(SEND_ERROR "driver_lpspi_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpi2c_edma)
# Add set(CONFIG_USE_driver_lpi2c_edma true) in config.cmake to use this component

message("driver_lpi2c_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_lpi2c AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpi2c/fsl_lpi2c_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpi2c/.
)

else()

message(SEND_ERROR "driver_lpi2c_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_lpuart)
# Add set(CONFIG_USE_driver_cmsis_lpuart true) in config.cmake to use this component

message("driver_cmsis_lpuart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpuart_edma AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_lpuart AND CONFIG_USE_CMSIS_Driver_Include_USART AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart/fsl_lpuart_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart/.
)

else()

message(SEND_ERROR "driver_cmsis_lpuart.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_lpspi)
# Add set(CONFIG_USE_driver_cmsis_lpspi true) in config.cmake to use this component

message("driver_cmsis_lpspi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpspi_edma AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_lpspi AND CONFIG_USE_CMSIS_Driver_Include_SPI AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi/fsl_lpspi_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi/.
)

else()

message(SEND_ERROR "driver_cmsis_lpspi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_lpi2c)
# Add set(CONFIG_USE_driver_cmsis_lpi2c true) in config.cmake to use this component

message("driver_cmsis_lpi2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpi2c_edma AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_lpi2c AND CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c/fsl_lpi2c_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c/.
)

else()

message(SEND_ERROR "driver_cmsis_lpi2c.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xspi_edma)
# Add set(CONFIG_USE_driver_xspi_edma true) in config.cmake to use this component

message("driver_xspi_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_xspi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xspi/fsl_xspi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xspi/.
)

else()

message(SEND_ERROR "driver_xspi_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_mculcd_edma)
# Add set(CONFIG_USE_driver_flexio_mculcd_edma true) in config.cmake to use this component

message("driver_flexio_mculcd_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_flexio_mculcd AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/mculcd/fsl_flexio_mculcd_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/mculcd/.
)

else()

message(SEND_ERROR "driver_flexio_mculcd_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_spi_edma)
# Add set(CONFIG_USE_driver_flexio_spi_edma true) in config.cmake to use this component

message("driver_flexio_spi_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_flexio_spi AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/spi/fsl_flexio_spi_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/spi/.
)

else()

message(SEND_ERROR "driver_flexio_spi_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_uart_edma)
# Add set(CONFIG_USE_driver_flexio_uart_edma true) in config.cmake to use this component

message("driver_flexio_uart_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_flexio_uart AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/uart/fsl_flexio_uart_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/uart/.
)

else()

message(SEND_ERROR "driver_flexio_uart_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pdm_edma)
# Add set(CONFIG_USE_driver_pdm_edma true) in config.cmake to use this component

message("driver_pdm_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_edma4 AND CONFIG_USE_driver_pdm AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm/fsl_pdm_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm/.
)

else()

message(SEND_ERROR "driver_pdm_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_crc)
# Add set(CONFIG_USE_driver_crc true) in config.cmake to use this component

message("driver_crc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc/fsl_crc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc/.
)

else()

message(SEND_ERROR "driver_crc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_itrc)
# Add set(CONFIG_USE_driver_itrc true) in config.cmake to use this component

message("driver_itrc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/itrc/fsl_itrc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/itrc/.
)

else()

message(SEND_ERROR "driver_itrc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_freqme)
# Add set(CONFIG_USE_driver_lpc_freqme true) in config.cmake to use this component

message("driver_lpc_freqme component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_freqme/fsl_freqme.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_freqme/.
)

else()

message(SEND_ERROR "driver_lpc_freqme.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_puf_v3)
# Add set(CONFIG_USE_driver_puf_v3 true) in config.cmake to use this component

message("driver_puf_v3 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf_v3/fsl_puf_v3.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf_v3/.
)

else()

message(SEND_ERROR "driver_puf_v3.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_sctimer)
# Add set(CONFIG_USE_driver_sctimer true) in config.cmake to use this component

message("driver_sctimer component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer/fsl_sctimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer/.
)

else()

message(SEND_ERROR "driver_sctimer.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_syspm)
# Add set(CONFIG_USE_driver_syspm true) in config.cmake to use this component

message("driver_syspm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/syspm/fsl_syspm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/syspm/.
)

else()

message(SEND_ERROR "driver_syspm.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cache_xcache)
# Add set(CONFIG_USE_driver_cache_xcache true) in config.cmake to use this component

message("driver_cache_xcache component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE_ID STREQUAL cm33_core0) AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/xcache/fsl_cache.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/xcache/.
)

else()

message(SEND_ERROR "driver_cache_xcache.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_inputmux_connections)
# Add set(CONFIG_USE_driver_inputmux_connections true) in config.cmake to use this component

message("driver_inputmux_connections component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_inputmux_connections.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_common)
# Add set(CONFIG_USE_driver_common true) in config.cmake to use this component

message("driver_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_reset AND CONFIG_USE_driver_clock AND CONFIG_USE_device_MIMXRT798S_CMSIS)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common.c
)

if(CONFIG_CORE STREQUAL cm33)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common_arm.c
  )
endif()

if(CONFIG_CORE STREQUAL dsp)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common_dsp.c
  )
endif()

if(CONFIG_CORE STREQUAL ezhv)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common_riscv.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/.
)

else()

message(SEND_ERROR "driver_common.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_assert)
# Add set(CONFIG_USE_utility_assert true) in config.cmake to use this component

message("utility_assert component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_utility_debug_console AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/fsl_assert.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/.
)

else()

message(SEND_ERROR "utility_assert.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_assert_lite)
# Add set(CONFIG_USE_utility_assert_lite true) in config.cmake to use this component

message("utility_assert_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_utility_debug_console_lite AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/fsl_assert.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/.
)

else()

message(SEND_ERROR "utility_assert_lite.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_str)
# Add set(CONFIG_USE_utility_str true) in config.cmake to use this component

message("utility_str component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/str/fsl_str.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/str
)

else()

message(SEND_ERROR "utility_str.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_debug_console)
# Add set(CONFIG_USE_utility_debug_console true) in config.cmake to use this component

message("utility_debug_console component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_serial_manager AND CONFIG_USE_driver_common AND CONFIG_USE_utility_str)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
)

else()

message(SEND_ERROR "utility_debug_console.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_power_manager_core)
# Add set(CONFIG_USE_component_power_manager_core true) in config.cmake to use this component

message("component_power_manager_core component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/core/fsl_pm_core.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/core/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DGENERIC_LIST_LIGHT=1
  )

endif()

else()

message(SEND_ERROR "component_power_manager_core.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_power_manager_MIMXRT798S)
# Add set(CONFIG_USE_component_power_manager_MIMXRT798S true) in config.cmake to use this component

message("component_power_manager_MIMXRT798S component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_power_manager_core AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/devices/MIMXRT798S/fsl_pm_device.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/devices/MIMXRT798S/.
)

else()

message(SEND_ERROR "component_power_manager_MIMXRT798S.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_audio_sai_edma_adapter)
# Add set(CONFIG_USE_component_audio_sai_edma_adapter true) in config.cmake to use this component

message("component_audio_sai_edma_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_sai_edma)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/audio/fsl_adapter_sai.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/audio/.
)

else()

message(SEND_ERROR "component_audio_sai_edma_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_button)
# Add set(CONFIG_USE_component_button true) in config.cmake to use this component

message("component_button component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_timer_manager AND (CONFIG_USE_component_gpio_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/button/fsl_component_button.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/button/.
)

else()

message(SEND_ERROR "component_button.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_codec)
# Add set(CONFIG_USE_driver_codec true) in config.cmake to use this component

message("driver_codec component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_USE_component_wm8962_adapter OR CONFIG_USE_component_cs42448_adapter OR CONFIG_USE_component_codec_adapters))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/fsl_codec_common.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "driver_codec.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_codec_adapters)
# Add set(CONFIG_USE_component_codec_adapters true) in config.cmake to use this component

message("component_codec_adapters component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_USE_driver_codec AND CONFIG_USE_component_wm8962_adapter) OR (CONFIG_USE_driver_common AND CONFIG_USE_component_cs42448_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/fsl_codec_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DCODEC_MULTI_ADAPTERS=1
  )

endif()

else()

message(SEND_ERROR "component_codec_adapters.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_wm8962_adapter)
# Add set(CONFIG_USE_component_wm8962_adapter true) in config.cmake to use this component

message("component_wm8962_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_wm8962 AND CONFIG_USE_driver_codec)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8962/fsl_codec_wm8962_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8962
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port
)

else()

message(SEND_ERROR "component_wm8962_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_cs42448_adapter)
# Add set(CONFIG_USE_component_cs42448_adapter true) in config.cmake to use this component

message("component_cs42448_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_cs42448 AND CONFIG_USE_driver_codec)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/cs42448/fsl_codec_cs42448_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/cs42448
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port
)

else()

message(SEND_ERROR "component_cs42448_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_codec_i2c)
# Add set(CONFIG_USE_component_codec_i2c true) in config.cmake to use this component

message("component_codec_i2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_USE_component_lpi2c_adapter OR CONFIG_USE_component_i3c_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c/fsl_codec_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "component_codec_i2c.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_wm8962)
# Add set(CONFIG_USE_driver_wm8962 true) in config.cmake to use this component

message("driver_wm8962 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_codec_i2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8962/fsl_wm8962.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8962/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
    -DBOARD_USE_CODEC=1
    -DCODEC_WM8962_ENABLE
  )

endif()

else()

message(SEND_ERROR "driver_wm8962.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cs42448)
# Add set(CONFIG_USE_driver_cs42448 true) in config.cmake to use this component

message("driver_cs42448 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_codec_i2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42448/fsl_cs42448.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42448/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
    -DCODEC_CS42448_ENABLE
  )

endif()

else()

message(SEND_ERROR "driver_cs42448.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ektf2k)
# Add set(CONFIG_USE_driver_ektf2k true) in config.cmake to use this component

message("driver_ektf2k component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ektf2k/fsl_ektf2k.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ektf2k/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "driver_ektf2k.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_nor_flash-controller-lpspi)
# Add set(CONFIG_USE_driver_nor_flash-controller-lpspi true) in config.cmake to use this component

message("driver_nor_flash-controller-lpspi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_nor_flash-common AND CONFIG_USE_driver_lpspi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/lpspi/fsl_lpspi_nor_flash.c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/lpspi/fsl_lpspi_mem_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/lpspi/.
)

else()

message(SEND_ERROR "driver_nor_flash-controller-lpspi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_nor_flash-controller-xspi)
# Add set(CONFIG_USE_driver_nor_flash-controller-xspi true) in config.cmake to use this component

message("driver_nor_flash-controller-xspi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_nor_flash-common AND CONFIG_USE_driver_xspi AND CONFIG_USE_driver_sfdp_parser)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/xspi/fsl_xspi_nor_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/xspi/.
)

else()

message(SEND_ERROR "driver_nor_flash-controller-xspi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ft3267)
# Add set(CONFIG_USE_driver_ft3267 true) in config.cmake to use this component

message("driver_ft3267 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft3267/fsl_ft3267.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft3267/.
)

else()

message(SEND_ERROR "driver_ft3267.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ft5406)
# Add set(CONFIG_USE_driver_ft5406 true) in config.cmake to use this component

message("driver_ft5406 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406/fsl_ft5406.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406/.
)

else()

message(SEND_ERROR "driver_ft5406.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_fxos8700cq)
# Add set(CONFIG_USE_driver_fxos8700cq true) in config.cmake to use this component

message("driver_fxos8700cq component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq/fsl_fxos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq/.
)

else()

message(SEND_ERROR "driver_fxos8700cq.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_gpio_adapter)
# Add set(CONFIG_USE_component_gpio_adapter true) in config.cmake to use this component

message("component_gpio_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_gpio AND ((CONFIG_DEVICE_ID STREQUAL MIMXRT798S)))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio/fsl_adapter_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio/.
)

else()

message(SEND_ERROR "component_gpio_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_gt911)
# Add set(CONFIG_USE_driver_gt911 true) in config.cmake to use this component

message("driver_gt911 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911/fsl_gt911.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "driver_gt911.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpi2c_adapter)
# Add set(CONFIG_USE_component_lpi2c_adapter true) in config.cmake to use this component

message("component_lpi2c_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpi2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/fsl_adapter_lpi2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/.
)

else()

message(SEND_ERROR "component_lpi2c_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_i3c_adapter)
# Add set(CONFIG_USE_component_i3c_adapter true) in config.cmake to use this component

message("component_i3c_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_i3c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/fsl_adapter_i3c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I3C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "component_i3c_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_i3c_bus)
# Add set(CONFIG_USE_component_i3c_bus true) in config.cmake to use this component

message("component_i3c_bus component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus/fsl_component_i3c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus/.
)

else()

message(SEND_ERROR "component_i3c_bus.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_i3c_bus_adapter)
# Add set(CONFIG_USE_component_i3c_bus_adapter true) in config.cmake to use this component

message("component_i3c_bus_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_i3c AND CONFIG_USE_component_i3c_bus)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus/fsl_component_i3c_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus/.
)

else()

message(SEND_ERROR "component_i3c_bus_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_led)
# Add set(CONFIG_USE_component_led true) in config.cmake to use this component

message("component_led component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_timer_manager AND (CONFIG_USE_component_gpio_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/led/fsl_component_led.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/led/.
)

else()

message(SEND_ERROR "component_led.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lists)
# Add set(CONFIG_USE_component_lists true) in config.cmake to use this component

message("component_lists component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/lists/fsl_component_generic_list.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/lists/.
)

else()

message(SEND_ERROR "component_lists.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_log)
# Add set(CONFIG_USE_component_log true) in config.cmake to use this component

message("component_log component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_utility_str)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/fsl_component_log.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/.
)

else()

message(SEND_ERROR "component_log.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_log_backend_debugconsole)
# Add set(CONFIG_USE_component_log_backend_debugconsole true) in config.cmake to use this component

message("component_log_backend_debugconsole component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_log AND CONFIG_USE_utility_debug_console)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/fsl_component_log_backend_debugconsole.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/.
)

else()

message(SEND_ERROR "component_log_backend_debugconsole.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_log_backend_debugconsole_lite)
# Add set(CONFIG_USE_component_log_backend_debugconsole_lite true) in config.cmake to use this component

message("component_log_backend_debugconsole_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_log AND CONFIG_USE_utility_debug_console_lite)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/fsl_component_log_backend_debugconsole.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/.
)

else()

message(SEND_ERROR "component_log_backend_debugconsole_lite.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_log_backend_ringbuffer)
# Add set(CONFIG_USE_component_log_backend_ringbuffer true) in config.cmake to use this component

message("component_log_backend_ringbuffer component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_log)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/fsl_component_log_backend_ringbuffer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/log/.
)

else()

message(SEND_ERROR "component_log_backend_ringbuffer.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mflash_file)
# Add set(CONFIG_USE_component_mflash_file true) in config.cmake to use this component

message("component_mflash_file component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_mflash_rt700)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mflash_file.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/.
)

else()

message(SEND_ERROR "component_mflash_file.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mflash_dummy)
# Add set(CONFIG_USE_component_mflash_dummy true) in config.cmake to use this component

message("component_mflash_dummy component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_mflash_file)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mflash_dummy.c
)

else()

message(SEND_ERROR "component_mflash_dummy.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mflash_rt700)
# Add set(CONFIG_USE_component_mflash_rt700 true) in config.cmake to use this component

message("component_mflash_rt700 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_mflash_common AND (CONFIG_BOARD STREQUAL mimxrt700evk) AND (CONFIG_CORE_ID STREQUAL cm33_core0) AND CONFIG_USE_driver_xspi AND CONFIG_USE_driver_power)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt700/mflash_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt700/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DMFLASH_FILE_BASEADDR=7340032
  )

endif()

else()

message(SEND_ERROR "component_mflash_rt700.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_panic)
# Add set(CONFIG_USE_component_panic true) in config.cmake to use this component

message("component_panic component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/panic/fsl_component_panic.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/panic/.
)

else()

message(SEND_ERROR "component_panic.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pca9422)
# Add set(CONFIG_USE_driver_pca9422 true) in config.cmake to use this component

message("driver_pca9422 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_power)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pca9422/fsl_pca9422.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pca9422/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_I2C_BASED_COMPONENT_USED=1
  )

endif()

else()

message(SEND_ERROR "driver_pca9422.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_reset_adapter)
# Add set(CONFIG_USE_component_reset_adapter true) in config.cmake to use this component

message("component_reset_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/reset/fsl_adapter_reset.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/reset/.
)

else()

message(SEND_ERROR "component_reset_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_software_rng_adapter)
# Add set(CONFIG_USE_component_software_rng_adapter true) in config.cmake to use this component

message("component_software_rng_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rng/fsl_adapter_software_rng.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rng/.
)

else()

message(SEND_ERROR "component_software_rng_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager)
# Add set(CONFIG_USE_component_serial_manager true) in config.cmake to use this component

message("component_serial_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND (CONFIG_USE_component_serial_manager_uart OR CONFIG_USE_component_serial_manager_virtual OR CONFIG_USE_component_serial_manager_swo OR CONFIG_USE_component_serial_manager_spi))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

else()

message(SEND_ERROR "component_serial_manager.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_spi)
# Add set(CONFIG_USE_component_serial_manager_spi true) in config.cmake to use this component

message("component_serial_manager_spi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_serial_manager AND ((CONFIG_USE_driver_lpspi AND CONFIG_USE_component_lpspi_adapter)))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_port_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSERIAL_PORT_TYPE_SPI=1
    -DSERIAL_PORT_TYPE_SPI_MASTER=1
    -DSERIAL_PORT_TYPE_SPI_SLAVE=1
    -DSERIAL_MANAGER_NON_BLOCKING_MODE=1
  )

endif()

else()

message(SEND_ERROR "component_serial_manager_spi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_virtual)
# Add set(CONFIG_USE_component_serial_manager_virtual true) in config.cmake to use this component

message("component_serial_manager_virtual component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_serial_manager AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_port_virtual.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSERIAL_PORT_TYPE_VIRTUAL=1
    -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING
  )

endif()

else()

message(SEND_ERROR "component_serial_manager_virtual.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_swo)
# Add set(CONFIG_USE_component_serial_manager_swo true) in config.cmake to use this component

message("component_serial_manager_swo component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE STREQUAL cm33) AND CONFIG_USE_driver_common AND CONFIG_USE_component_serial_manager)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_port_swo.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSERIAL_PORT_TYPE_SWO=1
  )

endif()

else()

message(SEND_ERROR "component_serial_manager_swo.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_shell)
# Add set(CONFIG_USE_utility_shell true) in config.cmake to use this component

message("utility_shell component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_utility_str AND CONFIG_USE_component_lists AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/shell/fsl_shell.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/shell/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DDEBUG_CONSOLE_RX_ENABLE=0
  )

endif()

else()

message(SEND_ERROR "utility_shell.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpspi_adapter)
# Add set(CONFIG_USE_component_lpspi_adapter true) in config.cmake to use this component

message("component_lpspi_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpspi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/spi/fsl_adapter_lpspi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/spi/.
)

else()

message(SEND_ERROR "component_lpspi_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ssd1963)
# Add set(CONFIG_USE_driver_ssd1963 true) in config.cmake to use this component

message("driver_ssd1963 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dbi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ssd1963/fsl_ssd1963.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ssd1963/.
)

else()

message(SEND_ERROR "driver_ssd1963.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_ctimer_adapter)
# Add set(CONFIG_USE_component_ctimer_adapter true) in config.cmake to use this component

message("component_ctimer_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_ctimer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_ctimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_CTIMER=1
  )

endif()

else()

message(SEND_ERROR "component_ctimer_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mrt_adapter)
# Add set(CONFIG_USE_component_mrt_adapter true) in config.cmake to use this component

message("component_mrt_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_mrt)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_mrt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_MRT=1
  )

endif()

else()

message(SEND_ERROR "component_mrt_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_ostimer_adapter)
# Add set(CONFIG_USE_component_ostimer_adapter true) in config.cmake to use this component

message("component_ostimer_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_ostimer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_ostimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_OSTIMER=1
  )

endif()

else()

message(SEND_ERROR "component_ostimer_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_timer_manager)
# Add set(CONFIG_USE_component_timer_manager true) in config.cmake to use this component

message("component_timer_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND (CONFIG_USE_component_ctimer_adapter OR CONFIG_USE_component_mrt_adapter OR CONFIG_USE_component_ostimer_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/fsl_component_timer_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/.
)

else()

message(SEND_ERROR "component_timer_manager.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpuart_adapter)
# Add set(CONFIG_USE_component_lpuart_adapter true) in config.cmake to use this component

message("component_lpuart_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpuart)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/fsl_adapter_lpuart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/.
)

else()

message(SEND_ERROR "component_lpuart_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpuart_dma_adapter)
# Add set(CONFIG_USE_component_lpuart_dma_adapter true) in config.cmake to use this component

message("component_lpuart_dma_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_lpuart_adapter AND CONFIG_USE_component_timer_manager AND (CONFIG_USE_driver_lpuart_edma))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/fsl_adapter_lpuart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DHAL_UART_DMA_ENABLE=1
  )

endif()

else()

message(SEND_ERROR "component_lpuart_dma_adapter.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_gpio)
# Add set(CONFIG_USE_driver_gpio true) in config.cmake to use this component

message("driver_gpio component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio/fsl_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio/.
)

else()

message(SEND_ERROR "driver_gpio.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_inputmux)
# Add set(CONFIG_USE_driver_inputmux true) in config.cmake to use this component

message("driver_inputmux component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_inputmux_connections)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux/fsl_inputmux.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux/.
)

else()

message(SEND_ERROR "driver_inputmux.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_mu1)
# Add set(CONFIG_USE_driver_mu1 true) in config.cmake to use this component

message("driver_mu1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu1/fsl_mu.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu1/.
)

else()

message(SEND_ERROR "driver_mu1.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_sema42)
# Add set(CONFIG_USE_driver_sema42 true) in config.cmake to use this component

message("driver_sema42 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42/fsl_sema42.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42/.
)

else()

message(SEND_ERROR "driver_sema42.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pint)
# Add set(CONFIG_USE_driver_pint true) in config.cmake to use this component

message("driver_pint component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint/fsl_pint.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint/.
)

else()

message(SEND_ERROR "driver_pint.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_acmp)
# Add set(CONFIG_USE_driver_acmp true) in config.cmake to use this component

message("driver_acmp component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp/fsl_acmp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp/.
)

else()

message(SEND_ERROR "driver_acmp.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpadc)
# Add set(CONFIG_USE_driver_lpadc true) in config.cmake to use this component

message("driver_lpadc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc/fsl_lpadc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc/.
)

else()

message(SEND_ERROR "driver_lpadc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_xspi)
# Add set(CONFIG_USE_driver_xspi true) in config.cmake to use this component

message("driver_xspi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xspi/fsl_xspi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xspi/.
)

else()

message(SEND_ERROR "driver_xspi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio)
# Add set(CONFIG_USE_driver_flexio true) in config.cmake to use this component

message("driver_flexio component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/fsl_flexio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/.
)

else()

message(SEND_ERROR "driver_flexio.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_i2c_master)
# Add set(CONFIG_USE_driver_flexio_i2c_master true) in config.cmake to use this component

message("driver_flexio_i2c_master component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_flexio)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/i2c/fsl_flexio_i2c_master.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/i2c/.
)

else()

message(SEND_ERROR "driver_flexio_i2c_master.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_i2s)
# Add set(CONFIG_USE_driver_flexio_i2s true) in config.cmake to use this component

message("driver_flexio_i2s component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_flexio)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/i2s/fsl_flexio_i2s.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/i2s/.
)

else()

message(SEND_ERROR "driver_flexio_i2s.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_mculcd)
# Add set(CONFIG_USE_driver_flexio_mculcd true) in config.cmake to use this component

message("driver_flexio_mculcd component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_flexio AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/mculcd/fsl_flexio_mculcd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/mculcd/.
)

else()

message(SEND_ERROR "driver_flexio_mculcd.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_spi)
# Add set(CONFIG_USE_driver_flexio_spi true) in config.cmake to use this component

message("driver_flexio_spi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_flexio)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/spi/fsl_flexio_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/spi/.
)

else()

message(SEND_ERROR "driver_flexio_spi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flexio_uart)
# Add set(CONFIG_USE_driver_flexio_uart true) in config.cmake to use this component

message("driver_flexio_uart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_flexio)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/uart/fsl_flexio_uart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio/uart/.
)

else()

message(SEND_ERROR "driver_flexio_uart.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpflexcomm)
# Add set(CONFIG_USE_driver_lpflexcomm true) in config.cmake to use this component

message("driver_lpflexcomm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/fsl_lpflexcomm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/.
)

else()

message(SEND_ERROR "driver_lpflexcomm.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpi2c)
# Add set(CONFIG_USE_driver_lpi2c true) in config.cmake to use this component

message("driver_lpi2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpi2c/fsl_lpi2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpi2c/.
)

else()

message(SEND_ERROR "driver_lpi2c.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpuart)
# Add set(CONFIG_USE_driver_lpuart true) in config.cmake to use this component

message("driver_lpuart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpuart/fsl_lpuart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpuart/.
)

else()

message(SEND_ERROR "driver_lpuart.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpspi)
# Add set(CONFIG_USE_driver_lpspi true) in config.cmake to use this component

message("driver_lpspi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpflexcomm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpspi/fsl_lpspi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpflexcomm/lpspi/.
)

else()

message(SEND_ERROR "driver_lpspi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_sai)
# Add set(CONFIG_USE_driver_sai true) in config.cmake to use this component

message("driver_sai component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai/fsl_sai.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai/.
)

else()

message(SEND_ERROR "driver_sai.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_i3c_edma)
# Add set(CONFIG_USE_driver_i3c_edma true) in config.cmake to use this component

message("driver_i3c_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_i3c AND CONFIG_USE_driver_edma4)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/fsl_i3c_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/.
)

else()

message(SEND_ERROR "driver_i3c_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_i3c)
# Add set(CONFIG_USE_driver_i3c true) in config.cmake to use this component

message("driver_i3c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/fsl_i3c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/.
)

else()

message(SEND_ERROR "driver_i3c.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ctimer)
# Add set(CONFIG_USE_driver_ctimer true) in config.cmake to use this component

message("driver_ctimer component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer/fsl_ctimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer/.
)

else()

message(SEND_ERROR "driver_ctimer.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_mrt)
# Add set(CONFIG_USE_driver_mrt true) in config.cmake to use this component

message("driver_mrt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt/fsl_mrt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt/.
)

else()

message(SEND_ERROR "driver_mrt.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ostimer)
# Add set(CONFIG_USE_driver_ostimer true) in config.cmake to use this component

message("driver_ostimer component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer/fsl_ostimer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer/.
)

else()

message(SEND_ERROR "driver_ostimer.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ft5406_rt)
# Add set(CONFIG_USE_driver_ft5406_rt true) in config.cmake to use this component

message("driver_ft5406_rt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpi2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406_rt/fsl_ft5406_rt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406_rt/.
)

else()

message(SEND_ERROR "driver_ft5406_rt.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-rpi)
# Add set(CONFIG_USE_driver_display-rpi true) in config.cmake to use this component

message("driver_display-rpi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd AND (CONFIG_BOARD STREQUAL mimxrt700evk))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rpi/fsl_rpi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rpi/.
)

else()

message(SEND_ERROR "driver_display-rpi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-rm68200)
# Add set(CONFIG_USE_driver_display-rm68200 true) in config.cmake to use this component

message("driver_display-rm68200 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68200/fsl_rm68200.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68200/.
)

else()

message(SEND_ERROR "driver_display-rm68200.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-rm68191)
# Add set(CONFIG_USE_driver_display-rm68191 true) in config.cmake to use this component

message("driver_display-rm68191 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68191/fsl_rm68191.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68191/.
)

else()

message(SEND_ERROR "driver_display-rm68191.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-rm67162)
# Add set(CONFIG_USE_driver_display-rm67162 true) in config.cmake to use this component

message("driver_display-rm67162 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm67162/fsl_rm67162.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm67162/.
)

else()

message(SEND_ERROR "driver_display-rm67162.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-hx8394)
# Add set(CONFIG_USE_driver_display-hx8394 true) in config.cmake to use this component

message("driver_display-hx8394 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/hx8394/fsl_hx8394.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/hx8394/.
)

else()

message(SEND_ERROR "driver_display-hx8394.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dc-fb-dbi)
# Add set(CONFIG_USE_driver_dc-fb-dbi true) in config.cmake to use this component

message("driver_dc-fb-dbi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dc-fb-common AND CONFIG_USE_driver_dbi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/dbi/fsl_dc_fb_dbi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/dbi/.
)

else()

message(SEND_ERROR "driver_dc-fb-dbi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dc-fb-ssd1963)
# Add set(CONFIG_USE_driver_dc-fb-ssd1963 true) in config.cmake to use this component

message("driver_dc-fb-ssd1963 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dc-fb-common AND CONFIG_USE_driver_ssd1963)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/ssd1963/fsl_dc_fb_ssd1963.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/ssd1963/.
)

else()

message(SEND_ERROR "driver_dc-fb-ssd1963.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dc-fb-lcdif)
# Add set(CONFIG_USE_driver_dc-fb-lcdif true) in config.cmake to use this component

message("driver_dc-fb-lcdif component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dc-fb-common AND CONFIG_USE_driver_lcdif)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/lcdif/fsl_dc_fb_lcdif.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/lcdif/.
)

else()

message(SEND_ERROR "driver_dc-fb-lcdif.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-mipi-dsi-cmd)
# Add set(CONFIG_USE_driver_display-mipi-dsi-cmd true) in config.cmake to use this component

message("driver_display-mipi-dsi-cmd component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_USE_driver_mipi_dsi))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/mipi_dsi_cmd/fsl_mipi_dsi_cmd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/mipi_dsi_cmd/.
)

else()

message(SEND_ERROR "driver_display-mipi-dsi-cmd.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_display-common)
# Add set(CONFIG_USE_driver_display-common true) in config.cmake to use this component

message("driver_display-common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_video-common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/.
)

else()

message(SEND_ERROR "driver_display-common.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dc-fb-common)
# Add set(CONFIG_USE_driver_dc-fb-common true) in config.cmake to use this component

message("driver_dc-fb-common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_video-common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/.
)

else()

message(SEND_ERROR "driver_dc-fb-common.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dc-fb-dsi-cmd)
# Add set(CONFIG_USE_driver_dc-fb-dsi-cmd true) in config.cmake to use this component

message("driver_dc-fb-dsi-cmd component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dc-fb-common AND CONFIG_USE_driver_display-common AND CONFIG_USE_driver_display-mipi-dsi-cmd)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/dsi_cmd/fsl_dc_fb_dsi_cmd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/dsi_cmd/.
)

else()

message(SEND_ERROR "driver_dc-fb-dsi-cmd.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dbi)
# Add set(CONFIG_USE_driver_dbi true) in config.cmake to use this component

message("driver_dbi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/fsl_dbi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/.
)

else()

message(SEND_ERROR "driver_dbi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_dbi_flexio_edma)
# Add set(CONFIG_USE_driver_dbi_flexio_edma true) in config.cmake to use this component

message("driver_dbi_flexio_edma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_dbi AND CONFIG_USE_driver_flexio_mculcd AND CONFIG_USE_driver_flexio_mculcd_edma)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/flexio/fsl_dbi_flexio_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/flexio/.
)

else()

message(SEND_ERROR "driver_dbi_flexio_edma.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_video-common)
# Add set(CONFIG_USE_driver_video-common true) in config.cmake to use this component

message("driver_video-common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/fsl_video_common.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/video/.
)

else()

message(SEND_ERROR "driver_video-common.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_sdadc)
# Add set(CONFIG_USE_driver_sdadc true) in config.cmake to use this component

message("driver_sdadc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdadc/fsl_sdadc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdadc/.
)

else()

message(SEND_ERROR "driver_sdadc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_jpegdec)
# Add set(CONFIG_USE_driver_jpegdec true) in config.cmake to use this component

message("driver_jpegdec component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/jpegdec/fsl_jpegdec.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/jpegdec/.
)

else()

message(SEND_ERROR "driver_jpegdec.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pngdec)
# Add set(CONFIG_USE_driver_pngdec true) in config.cmake to use this component

message("driver_pngdec component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pngdec/fsl_pngdec.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pngdec/.
)

else()

message(SEND_ERROR "driver_pngdec.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_mipi_dsi)
# Add set(CONFIG_USE_driver_mipi_dsi true) in config.cmake to use this component

message("driver_mipi_dsi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_soc_mipi_dsi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi/fsl_mipi_dsi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi/.
)

else()

message(SEND_ERROR "driver_mipi_dsi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lcdif)
# Add set(CONFIG_USE_driver_lcdif true) in config.cmake to use this component

message("driver_lcdif component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdif/fsl_lcdif.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdif/.
)

else()

message(SEND_ERROR "driver_lcdif.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_usdhc)
# Add set(CONFIG_USE_driver_usdhc true) in config.cmake to use this component

message("driver_usdhc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc/fsl_usdhc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc/.
)

else()

message(SEND_ERROR "driver_usdhc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_glikey)
# Add set(CONFIG_USE_driver_glikey true) in config.cmake to use this component

message("driver_glikey component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/glikey/fsl_glikey.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/glikey/.
)

else()

message(SEND_ERROR "driver_glikey.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pdm)
# Add set(CONFIG_USE_driver_pdm true) in config.cmake to use this component

message("driver_pdm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm/fsl_pdm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm/.
)

else()

message(SEND_ERROR "driver_pdm.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cdog)
# Add set(CONFIG_USE_driver_cdog true) in config.cmake to use this component

message("driver_cdog component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog/fsl_cdog.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog/.
)

else()

message(SEND_ERROR "driver_cdog.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_irtc)
# Add set(CONFIG_USE_driver_irtc true) in config.cmake to use this component

message("driver_irtc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irtc/fsl_irtc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irtc/.
)

else()

message(SEND_ERROR "driver_irtc.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_wwdt)
# Add set(CONFIG_USE_driver_wwdt true) in config.cmake to use this component

message("driver_wwdt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt/fsl_wwdt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt/.
)

else()

message(SEND_ERROR "driver_wwdt.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_gdet)
# Add set(CONFIG_USE_driver_gdet true) in config.cmake to use this component

message("driver_gdet component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gdet/fsl_gdet.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gdet/.
)

else()

message(SEND_ERROR "driver_gdet.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_soc_mipi_dsi)
# Add set(CONFIG_USE_driver_soc_mipi_dsi true) in config.cmake to use this component

message("driver_soc_mipi_dsi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_soc_mipi_dsi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_clock)
# Add set(CONFIG_USE_driver_clock true) in config.cmake to use this component

message("driver_clock component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_clock.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_clock.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_reset)
# Add set(CONFIG_USE_driver_reset true) in config.cmake to use this component

message("driver_reset component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_reset.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_reset.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_power)
# Add set(CONFIG_USE_driver_power true) in config.cmake to use this component

message("driver_power component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_power.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_power.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_iopctl)
# Add set(CONFIG_USE_driver_lpc_iopctl true) in config.cmake to use this component

message("driver_lpc_iopctl component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND CONFIG_USE_driver_common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_lpc_iopctl.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_romapi)
# Add set(CONFIG_USE_driver_romapi true) in config.cmake to use this component

message("driver_romapi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_CORE_ID STREQUAL cm33_core0))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/bootloader/fsl_romapi.c
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/otp/fsl_romapi_otp.c
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/nboot/fsl_romapi_nboot.c
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/iap/fsl_romapi_iap.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/bootloader
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/otp
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/nboot
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/iap
  ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi/.
)

else()

message(SEND_ERROR "driver_romapi.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ezhv)
# Add set(CONFIG_USE_driver_ezhv true) in config.cmake to use this component

message("driver_ezhv component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_power AND (CONFIG_DEVICE_ID STREQUAL MIMXRT798S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_ezhv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_ezhv.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_rtt)
# Add set(CONFIG_USE_driver_rtt true) in config.cmake to use this component

message("driver_rtt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_rtt_template)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/RTT/SEGGER_RTT.c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/RTT/SEGGER_RTT_printf.c
)

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/Syscalls/SEGGER_RTT_Syscalls_GCC.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt/RTT
)

else()

message(SEND_ERROR "driver_rtt.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_cm33_core1)
# Add set(CONFIG_USE_device_MIMXRT798S_cm33_core1 true) in config.cmake to use this component

message("device_MIMXRT798S_cm33_core1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND ((CONFIG_USE_arch_RISCV_Include_core AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_CORE STREQUAL dsp)))

if(CONFIG_TOOLCHAIN STREQUAL xcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_cm33_core1.c
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL xcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_cm33_core1.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_ezhv)
# Add set(CONFIG_USE_device_MIMXRT798S_ezhv true) in config.cmake to use this component

message("device_MIMXRT798S_ezhv component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND ((CONFIG_USE_arch_RISCV_Include_core AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_CORE STREQUAL dsp)))

if(CONFIG_TOOLCHAIN STREQUAL xcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_ezhv.c
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL xcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_ezhv.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_hifi1)
# Add set(CONFIG_USE_device_MIMXRT798S_hifi1 true) in config.cmake to use this component

message("device_MIMXRT798S_hifi1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND ((CONFIG_USE_arch_RISCV_Include_core AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_CORE STREQUAL dsp)))

if(CONFIG_TOOLCHAIN STREQUAL xcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_hifi1.c
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL xcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_hifi1.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MIMXRT798S_hifi4)
# Add set(CONFIG_USE_device_MIMXRT798S_hifi4 true) in config.cmake to use this component

message("device_MIMXRT798S_hifi4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT798S) AND ((CONFIG_USE_arch_RISCV_Include_core AND (CONFIG_CORE STREQUAL ezhv)) OR (CONFIG_CORE STREQUAL dsp)))

if(CONFIG_TOOLCHAIN STREQUAL xcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./system_MIMXRT798S_hifi4.c
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL xcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)
endif()

else()

message(SEND_ERROR "device_MIMXRT798S_hifi4.MIMXRT798S dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

