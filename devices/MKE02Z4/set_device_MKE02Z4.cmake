include_guard(GLOBAL)


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


if (CONFIG_USE_utilities_misc_utilities)
# Add set(CONFIG_USE_utilities_misc_utilities true) in config.cmake to use this component

message("utilities_misc_utilities component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_sbrk.c
      ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities/fsl_syscall_stub.c
  )
endif()


endif()


if (CONFIG_USE_DEVICES_Project_Template_MKE02Z4)
# Add set(CONFIG_USE_DEVICES_Project_Template_MKE02Z4 true) in config.cmake to use this component

message("DEVICES_Project_Template_MKE02Z4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_uart_adapter AND (CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_device_MKE02Z4_startup AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_gpio_1 AND CONFIG_USE_driver_port_ke02 AND CONFIG_USE_driver_uart AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.h "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.c "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.h "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.h "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.c "" DEVICES_Project_Template_MKE02Z4.MKE02Z4)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

else()

message(SEND_ERROR "DEVICES_Project_Template_MKE02Z4.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MKE02Z4_startup)
# Add set(CONFIG_USE_device_MKE02Z4_startup true) in config.cmake to use this component

message("device_MKE02Z4_startup component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_device_MKE02Z4_system)

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./gcc/startup_MKE02Z4.S "" device_MKE02Z4_startup.MKE02Z4)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mke02z4.c "" device_MKE02Z4_startup.MKE02Z4)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_mke02z4.cpp "" device_MKE02Z4_startup.MKE02Z4)
endif()

else()

message(SEND_ERROR "device_MKE02Z4_startup.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MKE02Z4_CMSIS)
# Add set(CONFIG_USE_device_MKE02Z4_CMSIS true) in config.cmake to use this component

message("device_MKE02Z4_CMSIS component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Include_core_cm AND (CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "device_MKE02Z4_CMSIS.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_RTE_Device)
# Add set(CONFIG_USE_RTE_Device true) in config.cmake to use this component

message("RTE_Device component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/template/RTE_Device.h "" RTE_Device.MKE02Z4)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/template/.
)

else()

message(SEND_ERROR "RTE_Device.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_clock)
# Add set(CONFIG_USE_driver_clock true) in config.cmake to use this component

message("driver_clock component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_clock.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_clock.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_uart)
# Add set(CONFIG_USE_component_serial_manager_uart true) in config.cmake to use this component

message("component_serial_manager_uart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_uart_adapter AND CONFIG_USE_component_serial_manager AND (CONFIG_USE_driver_uart))

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

message(SEND_ERROR "component_serial_manager_uart.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_debug_console_lite)
# Add set(CONFIG_USE_utility_debug_console_lite true) in config.cmake to use this component

message("utility_debug_console_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_uart_adapter AND (CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common AND CONFIG_USE_utility_str)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
)

else()

message(SEND_ERROR "utility_debug_console_lite.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_notifier)
# Add set(CONFIG_USE_utility_notifier true) in config.cmake to use this component

message("utility_notifier component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/notifier/fsl_notifier.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/notifier/.
)

else()

message(SEND_ERROR "utility_notifier.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_port_ke02)
# Add set(CONFIG_USE_driver_port_ke02 true) in config.cmake to use this component

message("driver_port_ke02 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_port.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_port_ke02.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_MKE02Z4_system)
# Add set(CONFIG_USE_device_MKE02Z4_system true) in config.cmake to use this component

message("device_MKE02Z4_system component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_device_MKE02Z4_CMSIS)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./system_MKE02Z4.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "device_MKE02Z4_system.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_assert.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_assert_lite.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_str.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_debug_console.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_i2c)
# Add set(CONFIG_USE_driver_cmsis_i2c true) in config.cmake to use this component

message("driver_cmsis_i2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_i2c AND CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c/fsl_i2c_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c/.
)

else()

message(SEND_ERROR "driver_cmsis_i2c.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_spi)
# Add set(CONFIG_USE_driver_cmsis_spi true) in config.cmake to use this component

message("driver_cmsis_spi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_spi AND CONFIG_USE_CMSIS_Driver_Include_SPI AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi/fsl_spi_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi/.
)

else()

message(SEND_ERROR "driver_cmsis_spi.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_cmsis_uart)
# Add set(CONFIG_USE_driver_cmsis_uart true) in config.cmake to use this component

message("driver_cmsis_uart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_uart AND CONFIG_USE_CMSIS_Driver_Include_USART AND CONFIG_USE_RTE_Device)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart/fsl_uart_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart/.
)

else()

message(SEND_ERROR "driver_cmsis_uart.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_software_crc_adapter)
# Add set(CONFIG_USE_component_software_crc_adapter true) in config.cmake to use this component

message("component_software_crc_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/crc/fsl_adapter_software_crc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/crc/.
)

else()

message(SEND_ERROR "component_software_crc_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_eeprom_AT25Fxxxx)
# Add set(CONFIG_USE_component_eeprom_AT25Fxxxx true) in config.cmake to use this component

message("component_eeprom_AT25Fxxxx component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_spi_adapter)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/extern_flash/fsl_adapter_eeprom_AT25Fxxxx.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/extern_flash/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSPI_DUMMYDATA=0
  )

endif()

else()

message(SEND_ERROR "component_eeprom_AT25Fxxxx.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_i2c_adapter)
# Add set(CONFIG_USE_component_i2c_adapter true) in config.cmake to use this component

message("component_i2c_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_i2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/fsl_adapter_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/.
)

else()

message(SEND_ERROR "component_i2c_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_lists.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_log.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_log_backend_debugconsole.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_log_backend_debugconsole_lite.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_log_backend_ringbuffer.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mem_manager)
# Add set(CONFIG_USE_component_mem_manager true) in config.cmake to use this component

message("component_mem_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/fsl_component_mem_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/.
)

else()

message(SEND_ERROR "component_mem_manager.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mem_manager_light)
# Add set(CONFIG_USE_component_mem_manager_light true) in config.cmake to use this component

message("component_mem_manager_light component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/fsl_component_mem_manager_light.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/.
)

else()

message(SEND_ERROR "component_mem_manager_light.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_panic.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_pwm_ftm_adapter)
# Add set(CONFIG_USE_component_pwm_ftm_adapter true) in config.cmake to use this component

message("component_pwm_ftm_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_ftm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm/fsl_adapter_pwm_ftm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm/.
)

else()

message(SEND_ERROR "component_pwm_ftm_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_pwm_tpm_adapter)
# Add set(CONFIG_USE_component_pwm_tpm_adapter true) in config.cmake to use this component

message("component_pwm_tpm_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_tpm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm/fsl_adapter_pwm_tpm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm/.
)

else()

message(SEND_ERROR "component_pwm_tpm_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_reset_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_software_rng_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager)
# Add set(CONFIG_USE_component_serial_manager true) in config.cmake to use this component

message("component_serial_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND (CONFIG_USE_component_serial_manager_uart OR CONFIG_USE_component_serial_manager_virtual OR CONFIG_USE_component_serial_manager_spi))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/fsl_component_serial_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager/.
)

else()

message(SEND_ERROR "component_serial_manager.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_spi)
# Add set(CONFIG_USE_component_serial_manager_spi true) in config.cmake to use this component

message("component_serial_manager_spi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_serial_manager AND ((CONFIG_USE_driver_spi AND CONFIG_USE_component_spi_adapter)))

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

message(SEND_ERROR "component_serial_manager_spi.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_serial_manager_virtual)
# Add set(CONFIG_USE_component_serial_manager_virtual true) in config.cmake to use this component

message("component_serial_manager_virtual component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((NOT (CONFIG_NOT STREQUAL MKE02Z16xxx4)) AND CONFIG_USE_component_serial_manager AND CONFIG_USE_driver_common)

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

message(SEND_ERROR "component_serial_manager_virtual.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_shell.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_spi_adapter)
# Add set(CONFIG_USE_component_spi_adapter true) in config.cmake to use this component

message("component_spi_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_spi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/spi/fsl_adapter_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/spi/.
)

else()

message(SEND_ERROR "component_spi_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_ftm_adapter)
# Add set(CONFIG_USE_component_ftm_adapter true) in config.cmake to use this component

message("component_ftm_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_ftm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_ftm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_FTM=1
  )

endif()

else()

message(SEND_ERROR "component_ftm_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_pit_adapter)
# Add set(CONFIG_USE_component_pit_adapter true) in config.cmake to use this component

message("component_pit_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_pit)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_pit.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_PIT=1
  )

endif()

else()

message(SEND_ERROR "component_pit_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_tpm_adapter)
# Add set(CONFIG_USE_component_tpm_adapter true) in config.cmake to use this component

message("component_tpm_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_tpm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/fsl_adapter_tpm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTIMER_PORT_TYPE_TMP=1
  )

endif()

else()

message(SEND_ERROR "component_tpm_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_timer_manager)
# Add set(CONFIG_USE_component_timer_manager true) in config.cmake to use this component

message("component_timer_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND (CONFIG_USE_component_tpm_adapter OR CONFIG_USE_component_ftm_adapter OR CONFIG_USE_component_pit_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/fsl_component_timer_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/.
)

else()

message(SEND_ERROR "component_timer_manager.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_uart_adapter)
# Add set(CONFIG_USE_component_uart_adapter true) in config.cmake to use this component

message("component_uart_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_uart)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/fsl_adapter_uart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/.
)

else()

message(SEND_ERROR "component_uart_adapter.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_common)
# Add set(CONFIG_USE_driver_common true) in config.cmake to use this component

message("driver_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_clock AND CONFIG_USE_device_MKE02Z4_CMSIS)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common.c
)

if(CONFIG_CORE STREQUAL cm0p)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/fsl_common_arm.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common/.
)

else()

message(SEND_ERROR "driver_common.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_acmp_1)
# Add set(CONFIG_USE_driver_acmp_1 true) in config.cmake to use this component

message("driver_acmp_1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp_1/fsl_acmp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp_1/.
)

else()

message(SEND_ERROR "driver_acmp_1.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_adc_5v12b_ll18_015)
# Add set(CONFIG_USE_driver_adc_5v12b_ll18_015 true) in config.cmake to use this component

message("driver_adc_5v12b_ll18_015 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_5v12b_ll18_015/fsl_adc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_5v12b_ll18_015/.
)

else()

message(SEND_ERROR "driver_adc_5v12b_ll18_015.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_flash_ftmr)
# Add set(CONFIG_USE_driver_flash_ftmr true) in config.cmake to use this component

message("driver_flash_ftmr component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash_ftmr/fsl_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash_ftmr/.
)

else()

message(SEND_ERROR "driver_flash_ftmr.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ftm)
# Add set(CONFIG_USE_driver_ftm true) in config.cmake to use this component

message("driver_ftm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm/fsl_ftm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm/.
)

else()

message(SEND_ERROR "driver_ftm.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_gpio_1)
# Add set(CONFIG_USE_driver_gpio_1 true) in config.cmake to use this component

message("driver_gpio_1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio_1/fsl_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio_1/.
)

else()

message(SEND_ERROR "driver_gpio_1.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_i2c)
# Add set(CONFIG_USE_driver_i2c true) in config.cmake to use this component

message("driver_i2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c/fsl_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c/.
)

else()

message(SEND_ERROR "driver_i2c.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_irq)
# Add set(CONFIG_USE_driver_irq true) in config.cmake to use this component

message("driver_irq component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irq/fsl_irq.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irq/.
)

else()

message(SEND_ERROR "driver_irq.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_kbi)
# Add set(CONFIG_USE_driver_kbi true) in config.cmake to use this component

message("driver_kbi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kbi/fsl_kbi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kbi/.
)

else()

message(SEND_ERROR "driver_kbi.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pit)
# Add set(CONFIG_USE_driver_pit true) in config.cmake to use this component

message("driver_pit component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit/fsl_pit.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit/.
)

else()

message(SEND_ERROR "driver_pit.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_rtc_1)
# Add set(CONFIG_USE_driver_rtc_1 true) in config.cmake to use this component

message("driver_rtc_1 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc_1/fsl_rtc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc_1/.
)

else()

message(SEND_ERROR "driver_rtc_1.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_spi)
# Add set(CONFIG_USE_driver_spi true) in config.cmake to use this component

message("driver_spi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi/fsl_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi/.
)

else()

message(SEND_ERROR "driver_spi.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_tpm)
# Add set(CONFIG_USE_driver_tpm true) in config.cmake to use this component

message("driver_tpm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm/fsl_tpm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm/.
)

else()

message(SEND_ERROR "driver_tpm.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_uart)
# Add set(CONFIG_USE_driver_uart true) in config.cmake to use this component

message("driver_uart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart/fsl_uart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart/.
)

else()

message(SEND_ERROR "driver_uart.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_wdog8)
# Add set(CONFIG_USE_driver_wdog8 true) in config.cmake to use this component

message("driver_wdog8 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE02Z16xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z32xxx4 OR CONFIG_DEVICE_ID STREQUAL MKE02Z64xxx4) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog8/fsl_wdog8.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog8/.
)

else()

message(SEND_ERROR "driver_wdog8.MKE02Z4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

