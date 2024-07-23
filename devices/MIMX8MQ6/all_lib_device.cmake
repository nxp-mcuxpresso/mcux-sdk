# Copy variable into project config.cmake to use software component
#set.board.evkmimx8mq
#  # description: Board_project_template evkmimx8mq
#  set(CONFIG_USE_BOARD_Project_Template_evkmimx8mq true)

#set.device.MIMX8MQ6
#  # description: Middleware baremetal
#  set(CONFIG_USE_middleware_baremetal true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Devices_project_template MIMX8MQ6
#  set(CONFIG_USE_DEVICES_Project_Template_MIMX8MQ6 true)

#  # description: Device MIMX8MQ6_cmsis
#  set(CONFIG_USE_device_MIMX8MQ6_CMSIS true)

#  # description: Rte_device
#  set(CONFIG_USE_RTE_Device true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: IOMUXC Driver
#  set(CONFIG_USE_driver_iomuxc true)

#  # description: Device MIMX8MQ6_system
#  set(CONFIG_USE_device_MIMX8MQ6_system true)

#  # description: Device MIMX8MQ6_startup
#  set(CONFIG_USE_device_MIMX8MQ6_startup true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: ECSPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ecspi true)

#  # description: I2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ii2c true)

#  # description: UART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_iuart true)

#  # description: IO expander PCA6416A driver
#  set(CONFIG_USE_driver_pca6416a true)

#  # description: Component button
#  set(CONFIG_USE_component_button true)

#  # description: Driver codec
#  set(CONFIG_USE_driver_codec true)

#  # description: Component codec adapters for multi codec
#  set(CONFIG_USE_component_codec_adapters true)

#  # description: Component wm8524 adapter for single codec
#  set(CONFIG_USE_component_wm8524_adapter true)

#  # description: Component codec_i2c
#  set(CONFIG_USE_component_codec_i2c true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Component igpio_adapter
#  set(CONFIG_USE_component_igpio_adapter true)

#  # description: Component ii2c_adapter
#  set(CONFIG_USE_component_ii2c_adapter true)

#  # description: Component led
#  set(CONFIG_USE_component_led true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component mem_manager
#  set(CONFIG_USE_component_mem_manager true)

#  # description: Component mem_manager_light
#  set(CONFIG_USE_component_mem_manager_light true)

#  # description: Component mem_manager_freertos
#  set(CONFIG_USE_component_mem_manager_freertos true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Component serial_manager_swo
#  set(CONFIG_USE_component_serial_manager_swo true)

#  # description: Component gpt_adapter
#  set(CONFIG_USE_component_gpt_adapter true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component iuart_adapter
#  set(CONFIG_USE_component_iuart_adapter true)

#  # description: Driver wm8524
#  set(CONFIG_USE_driver_wm8524 true)

#  # description: COMMON Driver
#  set(CONFIG_USE_driver_common true)

#  # description: CACHE LMEM Driver
#  set(CONFIG_USE_driver_cache_lmem true)

#  # description: ECSPI Driver
#  set(CONFIG_USE_driver_ecspi true)

#  # description: ECSPI FreeRTOS Driver
#  set(CONFIG_USE_driver_ecspi_freertos true)

#  # description: GPT Driver
#  set(CONFIG_USE_driver_gpt true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_igpio true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_ii2c true)

#  # description: I2C Freertos Driver
#  set(CONFIG_USE_driver_ii2c_freertos true)

#  # description: PWM Driver
#  set(CONFIG_USE_driver_ipwm true)

#  # description: IUART Driver
#  set(CONFIG_USE_driver_iuart true)

#  # description: IUART Freertos Driver
#  set(CONFIG_USE_driver_iuart_freertos true)

#  # description: MU Driver
#  set(CONFIG_USE_driver_mu true)

#  # description: QSPI Driver
#  set(CONFIG_USE_driver_qspi true)

#  # description: RDC Driver
#  set(CONFIG_USE_driver_rdc true)

#  # description: RDC SEMA42 Driver
#  set(CONFIG_USE_driver_rdc_sema42 true)

#  # description: SAI Driver
#  set(CONFIG_USE_driver_sai true)

#  # description: SEMA4 Driver
#  set(CONFIG_USE_driver_sema4 true)

#  # description: TMU Driver
#  set(CONFIG_USE_driver_tmu true)

#  # description: wdog01 Driver
#  set(CONFIG_USE_driver_wdog01 true)

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

#set.middleware.freertos-kernel
#  # description: FreeRTOS NXP extension
#  set(CONFIG_USE_middleware_freertos-kernel_extension true)

#  # description: Template configuration file to be edited by user. Provides also memory allocator (heap_x), change variant if needed.
#  set(CONFIG_USE_middleware_freertos-kernel_template true)

#  # description: FreeRTOS kernel
#  set(CONFIG_USE_middleware_freertos-kernel true)

#  # description: FreeRTOS heap 1
#  set(CONFIG_USE_middleware_freertos-kernel_heap_1 true)

#  # description: FreeRTOS heap 2
#  set(CONFIG_USE_middleware_freertos-kernel_heap_2 true)

#  # description: FreeRTOS heap 3
#  set(CONFIG_USE_middleware_freertos-kernel_heap_3 true)

#  # description: FreeRTOS heap 4
#  set(CONFIG_USE_middleware_freertos-kernel_heap_4 true)

#  # description: FreeRTOS heap 5
#  set(CONFIG_USE_middleware_freertos-kernel_heap_5 true)

#  # description: new V2 FreeRTOS MPU wrappers introduced in V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers_v2 true)

#  # description: old FreeRTOS MPU wrappers used before V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers true)

#set.middleware.multicore
#  # description: Multicore SDK
#  set(CONFIG_USE_middleware_multicore true)

#  # description: remoteproc-load script
#  set(CONFIG_USE_middleware_multicore_remoteproc_loadscript true)

#  # description: RPMsg-Lite BM environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_bm true)

#  # description: RPMsg-Lite FreeRTOS environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_freertos true)

#  # description: RPMsg-Lite XOS environment layer sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_xos true)

#  # description: RPMsg-Lite Azure RTOS environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_azurertos true)

#  # description: RPMsg-Lite for evkmimx8mq baremetal application
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8mq_m4_bm true)

#  # description: RPMsg-Lite for evkmimx8mq FreeRTOS application
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8mq_m4_freertos true)

#  # description: RPMsg-Lite baremetal for evkmimx8mq board
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_bm_config true)

#  # description: RPMsg-Lite FreeRTOS for evkmimx8mq board
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_freertos_config true)

#  # description: RPMsg-Lite Zephyr environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_zephyr true)

#  # description: RPMsg-Lite
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite true)

#set.middleware.usb
#  # description: USB device phydcd config header
#  set(CONFIG_USE_middleware_usb_phydcd_config_header true)

#  # description: USB device hsdcd config header
#  set(CONFIG_USE_middleware_usb_hsdcd_config_header true)

#  # description: Middleware usb common_header
#  set(CONFIG_USE_middleware_usb_common_header true)

#  # description: Middleware usb device common_header
#  set(CONFIG_USE_middleware_usb_device_common_header true)

#set.component.osa
#  # description: Component osa_zephyr
#  set(CONFIG_USE_component_osa_zephyr true)

#  # description: Component common_task
#  set(CONFIG_USE_component_common_task true)

#  # description: Component osa_bm
#  set(CONFIG_USE_component_osa_bm true)

#  # description: Component osa_free_rtos
#  set(CONFIG_USE_component_osa_free_rtos true)

#  # description: Component osa
#  set(CONFIG_USE_component_osa true)

#  # description: Component osa interface
#  set(CONFIG_USE_component_osa_interface true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
  ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/project_template
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimx8mq
)

include(set_board_evkmimx8mq OPTIONAL)
include(set_CMSIS_DSP_Lib OPTIONAL)
include(set_CMSIS OPTIONAL)
include(set_device_MIMX8MQ6 OPTIONAL)
include(set_component_osa OPTIONAL)
include(set_middleware_freertos-kernel OPTIONAL)
include(set_middleware_multicore OPTIONAL)
include(set_middleware_usb OPTIONAL)
