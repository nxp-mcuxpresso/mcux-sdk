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


if (CONFIG_USE_driver_icm42688p)
# Add set(CONFIG_USE_driver_icm42688p true) in config.cmake to use this component

message("driver_icm42688p component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/icm42688p/fsl_icm42688p.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/icm42688p/.
)


endif()


if (CONFIG_USE_DEVICES_Project_Template_LPC865)
# Add set(CONFIG_USE_DEVICES_Project_Template_LPC865 true) in config.cmake to use this component

message("DEVICES_Project_Template_LPC865 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_miniusart_adapter AND (CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_device_LPC865_startup AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_lpc_gpio AND CONFIG_USE_driver_lpc_iocon_lite AND CONFIG_USE_driver_lpc_miniusart AND CONFIG_USE_driver_power_no_lib AND CONFIG_USE_driver_reset AND CONFIG_USE_driver_swm AND CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.h "" DEVICES_Project_Template_LPC865.LPC865)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c "" DEVICES_Project_Template_LPC865.LPC865)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h "" DEVICES_Project_Template_LPC865.LPC865)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" DEVICES_Project_Template_LPC865.LPC865)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.h "" DEVICES_Project_Template_LPC865.LPC865)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.c "" DEVICES_Project_Template_LPC865.LPC865)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

else()

message(SEND_ERROR "DEVICES_Project_Template_LPC865.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_LPC865_startup)
# Add set(CONFIG_USE_device_LPC865_startup true) in config.cmake to use this component

message("device_LPC865_startup component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_device_LPC865_system)

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./gcc/startup_LPC865.S "" device_LPC865_startup.LPC865)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_lpc865.c "" device_LPC865_startup.LPC865)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/./mcuxpresso/startup_lpc865.cpp "" device_LPC865_startup.LPC865)
endif()

else()

message(SEND_ERROR "device_LPC865_startup.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_LPC865_CMSIS)
# Add set(CONFIG_USE_device_LPC865_CMSIS true) in config.cmake to use this component

message("device_LPC865_CMSIS component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Include_core_cm AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "device_LPC865_CMSIS.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_clock)
# Add set(CONFIG_USE_driver_clock true) in config.cmake to use this component

message("driver_clock component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_power_no_lib AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_clock.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_clock.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_assert_lite)
# Add set(CONFIG_USE_utility_assert_lite true) in config.cmake to use this component

message("utility_assert_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_miniusart_adapter AND CONFIG_USE_utility_debug_console_lite AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/fsl_assert.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert/.
)

else()

message(SEND_ERROR "utility_assert_lite.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpc_gpio_adapter)
# Add set(CONFIG_USE_component_lpc_gpio_adapter true) in config.cmake to use this component

message("component_lpc_gpio_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_syscon AND CONFIG_USE_driver_lpc_gpio AND CONFIG_USE_driver_inputmux AND CONFIG_USE_driver_pint)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio/fsl_adapter_lpc_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio/.
)

else()

message(SEND_ERROR "component_lpc_gpio_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_utility_debug_console_lite)
# Add set(CONFIG_USE_utility_debug_console_lite true) in config.cmake to use this component

message("utility_debug_console_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_miniusart_adapter AND (CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common AND CONFIG_USE_utility_str)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
)

else()

message(SEND_ERROR "utility_debug_console_lite.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_i2c_dma)
# Add set(CONFIG_USE_driver_lpc_i2c_dma true) in config.cmake to use this component

message("driver_lpc_i2c_dma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_lpc_dma AND CONFIG_USE_driver_lpc_i2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_i2c/fsl_i2c_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_i2c/.
)

else()

message(SEND_ERROR "driver_lpc_i2c_dma.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_inputmux_connections)
# Add set(CONFIG_USE_driver_inputmux_connections true) in config.cmake to use this component

message("driver_inputmux_connections component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_inputmux_connections.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_swm_connections)
# Add set(CONFIG_USE_driver_swm_connections true) in config.cmake to use this component

message("driver_swm_connections component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_swm_connections.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_syscon_connections)
# Add set(CONFIG_USE_driver_syscon_connections true) in config.cmake to use this component

message("driver_syscon_connections component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_syscon_connections.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_power_no_lib)
# Add set(CONFIG_USE_driver_power_no_lib true) in config.cmake to use this component

message("driver_power_no_lib component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_power.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_power_no_lib.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_common)
# Add set(CONFIG_USE_driver_common true) in config.cmake to use this component

message("driver_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_reset AND CONFIG_USE_driver_clock AND CONFIG_USE_device_LPC865_CMSIS)

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

message(SEND_ERROR "driver_common.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_device_LPC865_system)
# Add set(CONFIG_USE_device_LPC865_system true) in config.cmake to use this component

message("device_LPC865_system component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_device_LPC865_CMSIS)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./system_LPC865.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "device_LPC865_system.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "utility_str.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_button)
# Add set(CONFIG_USE_component_button true) in config.cmake to use this component

message("component_button component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_timer_manager AND (CONFIG_USE_component_lpc_gpio_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/button/fsl_component_button.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/button/.
)

else()

message(SEND_ERROR "component_button.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpc_crc_adapter)
# Add set(CONFIG_USE_component_lpc_crc_adapter true) in config.cmake to use this component

message("component_lpc_crc_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpc_crc)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/crc/fsl_adapter_lpc_crc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/crc/.
)

else()

message(SEND_ERROR "component_lpc_crc_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_software_crc_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_lpc_i2c_adapter)
# Add set(CONFIG_USE_component_lpc_i2c_adapter true) in config.cmake to use this component

message("component_lpc_i2c_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpc_i2c)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/fsl_adapter_lpc_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/.
)

else()

message(SEND_ERROR "component_lpc_i2c_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_i3c_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_led)
# Add set(CONFIG_USE_component_led true) in config.cmake to use this component

message("component_led component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_timer_manager AND (CONFIG_USE_component_lpc_gpio_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/led/fsl_component_led.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/led/.
)

else()

message(SEND_ERROR "component_led.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_lists.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_mem_manager.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_mem_manager_light.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_mem_manager_freertos)
# Add set(CONFIG_USE_component_mem_manager_freertos true) in config.cmake to use this component

message("component_mem_manager_freertos component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_middleware_freertos-kernel)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/fsl_component_mem_manager_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager/.
)

else()

message(SEND_ERROR "component_mem_manager_freertos.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_panic.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_pwm_ftm_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_reset_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_software_rng_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_ftm_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_mrt_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_timer_manager)
# Add set(CONFIG_USE_component_timer_manager true) in config.cmake to use this component

message("component_timer_manager component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND (CONFIG_USE_component_ftm_adapter OR CONFIG_USE_component_mrt_adapter))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/fsl_component_timer_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager/.
)

else()

message(SEND_ERROR "component_timer_manager.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_miniusart_adapter)
# Add set(CONFIG_USE_component_miniusart_adapter true) in config.cmake to use this component

message("component_miniusart_adapter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_lpc_miniusart)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/fsl_adapter_miniusart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart/.
)

else()

message(SEND_ERROR "component_miniusart_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_crc)
# Add set(CONFIG_USE_driver_lpc_crc true) in config.cmake to use this component

message("driver_lpc_crc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc/fsl_crc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc/.
)

else()

message(SEND_ERROR "driver_lpc_crc.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_iap)
# Add set(CONFIG_USE_driver_iap true) in config.cmake to use this component

message("driver_iap component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap/fsl_iap.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap/.
)

else()

message(SEND_ERROR "driver_iap.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_inputmux)
# Add set(CONFIG_USE_driver_inputmux true) in config.cmake to use this component

message("driver_inputmux component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_inputmux_connections)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux/fsl_inputmux.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux/.
)

else()

message(SEND_ERROR "driver_inputmux.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_acomp)
# Add set(CONFIG_USE_driver_lpc_acomp true) in config.cmake to use this component

message("driver_lpc_acomp component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_acomp/fsl_acomp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_acomp/.
)

else()

message(SEND_ERROR "driver_lpc_acomp.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_adc)
# Add set(CONFIG_USE_driver_lpc_adc true) in config.cmake to use this component

message("driver_lpc_adc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc/fsl_adc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc/.
)

else()

message(SEND_ERROR "driver_lpc_adc.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_dma)
# Add set(CONFIG_USE_driver_lpc_dma true) in config.cmake to use this component

message("driver_lpc_dma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma/fsl_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma/.
)

else()

message(SEND_ERROR "driver_lpc_dma.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_gpio)
# Add set(CONFIG_USE_driver_lpc_gpio true) in config.cmake to use this component

message("driver_lpc_gpio component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio/fsl_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio/.
)

else()

message(SEND_ERROR "driver_lpc_gpio.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_i2c)
# Add set(CONFIG_USE_driver_lpc_i2c true) in config.cmake to use this component

message("driver_lpc_i2c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_i2c/fsl_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_i2c/.
)

else()

message(SEND_ERROR "driver_lpc_i2c.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_iocon_lite)
# Add set(CONFIG_USE_driver_lpc_iocon_lite true) in config.cmake to use this component

message("driver_lpc_iocon_lite component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon_lite/.
)

else()

message(SEND_ERROR "driver_lpc_iocon_lite.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_minispi)
# Add set(CONFIG_USE_driver_lpc_minispi true) in config.cmake to use this component

message("driver_lpc_minispi component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_minispi/fsl_spi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_minispi/.
)

else()

message(SEND_ERROR "driver_lpc_minispi.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_lpc_miniusart)
# Add set(CONFIG_USE_driver_lpc_miniusart true) in config.cmake to use this component

message("driver_lpc_miniusart component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_miniusart/fsl_usart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_miniusart/.
)

else()

message(SEND_ERROR "driver_lpc_miniusart.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_mrt)
# Add set(CONFIG_USE_driver_mrt true) in config.cmake to use this component

message("driver_mrt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt/fsl_mrt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt/.
)

else()

message(SEND_ERROR "driver_mrt.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_pint)
# Add set(CONFIG_USE_driver_pint true) in config.cmake to use this component

message("driver_pint component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint/fsl_pint.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint/.
)

else()

message(SEND_ERROR "driver_pint.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_reset)
# Add set(CONFIG_USE_driver_reset true) in config.cmake to use this component

message("driver_reset component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/drivers/fsl_reset.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/drivers/.
)

else()

message(SEND_ERROR "driver_reset.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_swm)
# Add set(CONFIG_USE_driver_swm true) in config.cmake to use this component

message("driver_swm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_swm_connections)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/swm/fsl_swm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/swm/.
)

else()

message(SEND_ERROR "driver_swm.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_syscon)
# Add set(CONFIG_USE_driver_syscon true) in config.cmake to use this component

message("driver_syscon component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_syscon_connections)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/syscon/fsl_syscon.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/syscon/.
)

else()

message(SEND_ERROR "driver_syscon.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_wkt)
# Add set(CONFIG_USE_driver_wkt true) in config.cmake to use this component

message("driver_wkt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wkt/fsl_wkt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wkt/.
)

else()

message(SEND_ERROR "driver_wkt.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_wwdt)
# Add set(CONFIG_USE_driver_wwdt true) in config.cmake to use this component

message("driver_wwdt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt/fsl_wwdt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt/.
)

else()

message(SEND_ERROR "driver_wwdt.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_i3c)
# Add set(CONFIG_USE_driver_i3c true) in config.cmake to use this component

message("driver_i3c component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL LPC865))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/fsl_i3c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/.
)

else()

message(SEND_ERROR "driver_i3c.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_i3c_dma)
# Add set(CONFIG_USE_driver_i3c_dma true) in config.cmake to use this component

message("driver_i3c_dma component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_i3c AND CONFIG_USE_driver_lpc_dma)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/fsl_i3c_dma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c/.
)

else()

message(SEND_ERROR "driver_i3c_dma.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_i3c_bus.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

message(SEND_ERROR "component_i3c_bus_adapter.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_driver_ftm)
# Add set(CONFIG_USE_driver_ftm true) in config.cmake to use this component

message("driver_ftm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC865) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm/fsl_ftm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm/.
)

else()

message(SEND_ERROR "driver_ftm.LPC865 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

