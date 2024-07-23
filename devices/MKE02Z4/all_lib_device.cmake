# Copy variable into project config.cmake to use software component
#set.board.frdmke02z40m
#  # description: Board_project_template frdmke02z40m
#  set(CONFIG_USE_BOARD_Project_Template_frdmke02z40m true)

#set.device.MKE02Z4
#  # description: Middleware baremetal
#  set(CONFIG_USE_middleware_baremetal true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Devices_project_template MKE02Z4
#  set(CONFIG_USE_DEVICES_Project_Template_MKE02Z4 true)

#  # description: Device MKE02Z4_startup
#  set(CONFIG_USE_device_MKE02Z4_startup true)

#  # description: Device MKE02Z4_cmsis
#  set(CONFIG_USE_device_MKE02Z4_CMSIS true)

#  # description: Rte_device
#  set(CONFIG_USE_RTE_Device true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: Utility notifier
#  set(CONFIG_USE_utility_notifier true)

#  # description: PORT Driver
#  set(CONFIG_USE_driver_port_ke02 true)

#  # description: Device MKE02Z4_system
#  set(CONFIG_USE_device_MKE02Z4_system true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: I2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_i2c true)

#  # description: SPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_spi true)

#  # description: UART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_uart true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Component eeprom_at25fxxxx
#  set(CONFIG_USE_component_eeprom_AT25Fxxxx true)

#  # description: Component i2c_adapter
#  set(CONFIG_USE_component_i2c_adapter true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component log
#  set(CONFIG_USE_component_log true)

#  # description: Component log backend debug console
#  set(CONFIG_USE_component_log_backend_debugconsole true)

#  # description: Component log backend debug console lite
#  set(CONFIG_USE_component_log_backend_debugconsole_lite true)

#  # description: Component log backend ring buffer
#  set(CONFIG_USE_component_log_backend_ringbuffer true)

#  # description: Component mem_manager
#  set(CONFIG_USE_component_mem_manager true)

#  # description: Component mem_manager_light
#  set(CONFIG_USE_component_mem_manager_light true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Component pwm_ftm_adapter
#  set(CONFIG_USE_component_pwm_ftm_adapter true)

#  # description: Component pwm_tpm_adapter
#  set(CONFIG_USE_component_pwm_tpm_adapter true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Component serial_manager_spi
#  set(CONFIG_USE_component_serial_manager_spi true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Utility shell
#  set(CONFIG_USE_utility_shell true)

#  # description: Component spi_adapter
#  set(CONFIG_USE_component_spi_adapter true)

#  # description: Component ftm_adapter
#  set(CONFIG_USE_component_ftm_adapter true)

#  # description: Component pit_adapter
#  set(CONFIG_USE_component_pit_adapter true)

#  # description: Component tpm_adapter
#  set(CONFIG_USE_component_tpm_adapter true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component uart_adapter
#  set(CONFIG_USE_component_uart_adapter true)

#  # description: COMMON Driver
#  set(CONFIG_USE_driver_common true)

#  # description: ACMP Driver
#  set(CONFIG_USE_driver_acmp_1 true)

#  # description: ADC12 Driver
#  set(CONFIG_USE_driver_adc_5v12b_ll18_015 true)

#  # description: Flash Driver
#  set(CONFIG_USE_driver_flash_ftmr true)

#  # description: FTM Driver
#  set(CONFIG_USE_driver_ftm true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_gpio_1 true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_i2c true)

#  # description: IRQ Driver
#  set(CONFIG_USE_driver_irq true)

#  # description: KBI Driver
#  set(CONFIG_USE_driver_kbi true)

#  # description: PIT Driver
#  set(CONFIG_USE_driver_pit true)

#  # description: RTC Driver
#  set(CONFIG_USE_driver_rtc_1 true)

#  # description: SPI Driver
#  set(CONFIG_USE_driver_spi true)

#  # description: TPM Driver
#  set(CONFIG_USE_driver_tpm true)

#  # description: UART Driver
#  set(CONFIG_USE_driver_uart true)

#  # description: WDOG Driver
#  set(CONFIG_USE_driver_wdog8 true)

#set.CMSIS
#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_Secure true)

#  # description: CMSIS-RTOS2 RTX5 for Armv8-M Non-Secure Domain (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_NonSecure true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#set.component.osa
#  # description: Component osa_zephyr
#  set(CONFIG_USE_component_osa_zephyr true)

#  # description: Component common_task
#  set(CONFIG_USE_component_common_task true)

#  # description: Component osa_bm
#  set(CONFIG_USE_component_osa_bm true)

#  # description: Component osa
#  set(CONFIG_USE_component_osa true)

#  # description: Component osa interface
#  set(CONFIG_USE_component_osa_interface true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/project_template
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/frdmke02z40m
)

include(set_board_frdmke02z40m OPTIONAL)
include(set_CMSIS_DSP_Lib OPTIONAL)
include(set_CMSIS OPTIONAL)
include(set_device_MKE02Z4 OPTIONAL)
include(set_component_osa OPTIONAL)
