# Copy variable into project config.cmake to use software component
#set.board.lpcxpresso54s018m
#  # description: Board_project_template lpcxpresso54s018m
#  set(CONFIG_USE_BOARD_Project_Template_lpcxpresso54s018m true)

#set.device.LPC54S018M
#  # description: Middleware baremetal
#  set(CONFIG_USE_middleware_baremetal true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: mflash common
#  set(CONFIG_USE_component_mflash_common true)

#  # description: Driver mx25r_flash
#  set(CONFIG_USE_driver_mx25r_flash true)

#  # description: Driver pf3000
#  set(CONFIG_USE_driver_pf3000 true)

#  # description: Driver phy-common
#  set(CONFIG_USE_driver_phy-common true)

#  # description: Devices_project_template LPC54S018M
#  set(CONFIG_USE_DEVICES_Project_Template_LPC54S018M true)

#  # description: Device LPC54S018M_startup
#  set(CONFIG_USE_device_LPC54S018M_startup true)

#  # description: Device LPC54S018M_cmsis
#  set(CONFIG_USE_device_LPC54S018M_CMSIS true)

#  # description: Rte_device
#  set(CONFIG_USE_RTE_Device true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: DMIC DMA Driver
#  set(CONFIG_USE_driver_dmic_dma true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_flexcomm_i2c_dma true)

#  # description: I2S Driver
#  set(CONFIG_USE_driver_flexcomm_i2s_dma true)

#  # description: SPIFI Driver
#  set(CONFIG_USE_driver_spifi_dma true)

#  # description: SPI Driver
#  set(CONFIG_USE_driver_flexcomm_spi_dma true)

#  # description: USART Driver
#  set(CONFIG_USE_driver_flexcomm_usart_dma true)

#  # description: Utility notifier
#  set(CONFIG_USE_utility_notifier true)

#  # description: Inputmux_connections Driver
#  set(CONFIG_USE_driver_inputmux_connections true)

#  # description: Power driver
#  set(CONFIG_USE_driver_power true)

#  # description: FRO calibration Lib
#  set(CONFIG_USE_driver_fro_calib true)

#  # description: COMMON Driver
#  set(CONFIG_USE_driver_common true)

#  # description: Device LPC54S018M_system
#  set(CONFIG_USE_device_LPC54S018M_system true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: I2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_flexcomm_i2c true)

#  # description: SPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_flexcomm_spi true)

#  # description: USART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_flexcomm_usart true)

#  # description: Component flexcomm_i2s_dma_adapter
#  set(CONFIG_USE_component_audio_flexcomm_i2s_dma_adapter true)

#  # description: Component button
#  set(CONFIG_USE_component_button true)

#  # description: Driver codec
#  set(CONFIG_USE_driver_codec true)

#  # description: Component codec adapters for multi codec
#  set(CONFIG_USE_component_codec_adapters true)

#  # description: Component wm8904 adapter for single codec
#  set(CONFIG_USE_component_wm8904_adapter true)

#  # description: Component wm8960 adapter for single codecs
#  set(CONFIG_USE_component_wm8960_adapter true)

#  # description: Component cs42888 adapter for single codec
#  set(CONFIG_USE_component_cs42888_adapter true)

#  # description: Component sgtl5000 adapter for single codec
#  set(CONFIG_USE_component_sgtl_adapter true)

#  # description: Component da7212 adapter for single codec
#  set(CONFIG_USE_component_da7212_adapter true)

#  # description: Component codec_i2c
#  set(CONFIG_USE_component_codec_i2c true)

#  # description: Component lpc_crc_adapter
#  set(CONFIG_USE_component_lpc_crc_adapter true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Driver cs42888
#  set(CONFIG_USE_driver_cs42888 true)

#  # description: Driver dialog7212
#  set(CONFIG_USE_driver_dialog7212 true)

#  # description: Driver ft5406
#  set(CONFIG_USE_driver_ft5406 true)

#  # description: Driver ft6x06
#  set(CONFIG_USE_driver_ft6x06 true)

#  # description: Driver fxos8700cq
#  set(CONFIG_USE_driver_fxos8700cq true)

#  # description: Component lpc_gpio_adapter
#  set(CONFIG_USE_component_lpc_gpio_adapter true)

#  # description: Component gint_adapter
#  set(CONFIG_USE_component_gint_adapter true)

#  # description: Driver gt911
#  set(CONFIG_USE_driver_gt911 true)

#  # description: Component flexcomm_i2c_adapter
#  set(CONFIG_USE_component_flexcomm_i2c_adapter true)

#  # description: Driver ili9341
#  set(CONFIG_USE_driver_ili9341 true)

#  # description: Component led
#  set(CONFIG_USE_component_led true)

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

#  # description: Component mem_manager_freertos
#  set(CONFIG_USE_component_mem_manager_freertos true)

#  # description: mflash file
#  set(CONFIG_USE_component_mflash_file true)

#  # description: dummy file for overwriting mflash when dowloading
#  set(CONFIG_USE_component_mflash_dummy true)

#  # description: mflash lpc54s018m
#  set(CONFIG_USE_component_mflash_lpc54s018m true)

#  # description: Driver mma8451q
#  set(CONFIG_USE_driver_mma8451q true)

#  # description: Driver mma8652fc
#  set(CONFIG_USE_driver_mma8652fc true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Driver phy-device-lan8720a
#  set(CONFIG_USE_driver_phy-device-lan8720a true)

#  # description: Component pwm_ctimer_adapter
#  set(CONFIG_USE_component_pwm_ctimer_adapter true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component rng_adapter
#  set(CONFIG_USE_component_rng_adapter true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component lpcrtc
#  set(CONFIG_USE_component_lpcrtc true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Component serial_manager_spi
#  set(CONFIG_USE_component_serial_manager_spi true)

#  # description: Component serial_manager_usb_cdc
#  set(CONFIG_USE_component_serial_manager_usb_cdc true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Component serial_manager_swo
#  set(CONFIG_USE_component_serial_manager_swo true)

#  # description: Driver sgtl5000
#  set(CONFIG_USE_driver_sgtl5000 true)

#  # description: Utility shell
#  set(CONFIG_USE_utility_shell true)

#  # description: Driver silicon_id
#  set(CONFIG_USE_component_silicon_id true)

#  # description: Component flexcomm_spi_adapter
#  set(CONFIG_USE_component_flexcomm_spi_adapter true)

#  # description: Component ctimer_adapter
#  set(CONFIG_USE_component_ctimer_adapter true)

#  # description: Component mrt_adapter
#  set(CONFIG_USE_component_mrt_adapter true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component usart_adapter
#  set(CONFIG_USE_component_usart_adapter true)

#  # description: Component usart_dma_adapter
#  set(CONFIG_USE_component_usart_dma_adapter true)

#  # description: Driver video-common
#  set(CONFIG_USE_driver_video-common true)

#  # description: Driver wm8904
#  set(CONFIG_USE_driver_wm8904 true)

#  # description: Driver wm8960
#  set(CONFIG_USE_driver_wm8960 true)

#  # description: AES Driver
#  set(CONFIG_USE_driver_aes true)

#  # description: CRC Driver
#  set(CONFIG_USE_driver_lpc_crc true)

#  # description: CTimer Driver
#  set(CONFIG_USE_driver_ctimer true)

#  # description: DMIC Driver
#  set(CONFIG_USE_driver_dmic true)

#  # description: DMIC HWVAD Driver
#  set(CONFIG_USE_driver_dmic_hwvad true)

#  # description: EMC Driver
#  set(CONFIG_USE_driver_emc true)

#  # description: enet Driver
#  set(CONFIG_USE_driver_lpc_enet true)

#  # description: FLEXCOMM Driver
#  set(CONFIG_USE_driver_flexcomm true)

#  # description: FMEAS Driver
#  set(CONFIG_USE_driver_fmeas true)

#  # description: GINT Driver
#  set(CONFIG_USE_driver_gint true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_flexcomm_i2c true)

#  # description: FLEXCOMM I2C FreeRTOS Driver
#  set(CONFIG_USE_driver_flexcomm_i2c_freertos true)

#  # description: I2S Driver
#  set(CONFIG_USE_driver_flexcomm_i2s true)

#  # description: IAP Driver
#  set(CONFIG_USE_driver_iap true)

#  # description: INPUTMUX Driver
#  set(CONFIG_USE_driver_inputmux true)

#  # description: ADC Driver
#  set(CONFIG_USE_driver_lpc_adc true)

#  # description: DMA Driver
#  set(CONFIG_USE_driver_lpc_dma true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_lpc_gpio true)

#  # description: IOCON Driver
#  set(CONFIG_USE_driver_lpc_iocon true)

#  # description: LCDC Driver
#  set(CONFIG_USE_driver_lpc_lcdc true)

#  # description: MCAN Driver
#  set(CONFIG_USE_driver_mcan true)

#  # description: MRT Driver
#  set(CONFIG_USE_driver_mrt true)

#  # description: OTP Driver
#  set(CONFIG_USE_driver_otp true)

#  # description: PINT Driver
#  set(CONFIG_USE_driver_pint true)

#  # description: PUF Driver
#  set(CONFIG_USE_driver_puf true)

#  # description: Reset Driver
#  set(CONFIG_USE_driver_reset true)

#  # description: RIT Driver
#  set(CONFIG_USE_driver_rit true)

#  # description: RNG Driver
#  set(CONFIG_USE_driver_rng true)

#  # description: RTC Driver
#  set(CONFIG_USE_driver_lpc_rtc true)

#  # description: SCT Driver
#  set(CONFIG_USE_driver_sctimer true)

#  # description: sdif Driver
#  set(CONFIG_USE_driver_sdif true)

#  # description: SHA Driver
#  set(CONFIG_USE_driver_sha true)

#  # description: SPI Driver
#  set(CONFIG_USE_driver_flexcomm_spi true)

#  # description: FLEXCOMM SPI FreeRTOS Driver
#  set(CONFIG_USE_driver_flexcomm_spi_freertos true)

#  # description: SPIFI Driver
#  set(CONFIG_USE_driver_spifi true)

#  # description: USART Driver
#  set(CONFIG_USE_driver_flexcomm_usart true)

#  # description: FLEXCOMM USART FreeRTOS Driver
#  set(CONFIG_USE_driver_flexcomm_usart_freertos true)

#  # description: UTICK Driver
#  set(CONFIG_USE_driver_utick true)

#  # description: WWDT Driver
#  set(CONFIG_USE_driver_wwdt true)

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

#set.middleware.littlefs
#  # description: littlefs
#  set(CONFIG_USE_middleware_littlefs true)

#set.middleware.lwip
#  # description: lwIP Template
#  set(CONFIG_USE_middleware_lwip_template true)

#  # description: Empty ethernet interface
#  set(CONFIG_USE_middleware_lwip_empty_ethernetif true)

#  # description: lwIP - A Lightweight TCP/IP Stack
#  set(CONFIG_USE_middleware_lwip true)

#  # description: Enet ethernet interface
#  set(CONFIG_USE_middleware_lwip_enet_ethernetif true)

#  # description: EtherCAT EOE ethernet interface
#  set(CONFIG_USE_middleware_lwip_eoe_ethernetif true)

#  # description: USB network layer
#  set(CONFIG_USE_middleware_lwip_usb_ethernetif true)

#  # description: lwIP HTTP Daemon Implementation Support Files
#  set(CONFIG_USE_middleware_lwip_apps_httpd_support true)

#  # description: lwIP HTTP Daemon
#  set(CONFIG_USE_middleware_lwip_apps_httpd true)

#  # description: lwIP HTTP Server Implementation
#  set(CONFIG_USE_middleware_lwip_apps_httpsrv true)

#  # description: lwIP HTTPS Server Implementation
#  set(CONFIG_USE_middleware_lwip_apps_httpssrv true)

#  # description: lwIP mDNS Implementation
#  set(CONFIG_USE_middleware_lwip_apps_mdns true)

#  # description: lwIP IPERF Implementation
#  set(CONFIG_USE_middleware_lwip_apps_lwiperf true)

#  # description: lwIP MQTT Client
#  set(CONFIG_USE_middleware_lwip_apps_mqtt true)

#  # description: lwIP SNTP
#  set(CONFIG_USE_middleware_lwip_apps_sntp true)

#  # description: lwIP Ping Sender contrib
#  set(CONFIG_USE_middleware_lwip_contrib_ping true)

#  # description: lwIP TCP Echo contrib
#  set(CONFIG_USE_middleware_lwip_contrib_tcpecho true)

#  # description: lwIP TCP Echo Raw API contrib
#  set(CONFIG_USE_middleware_lwip_contrib_tcpecho_raw true)

#  # description: lwIP UDP Echo contrib
#  set(CONFIG_USE_middleware_lwip_contrib_udpecho true)

#  # description: lwIP UDP Echo Raw API contrib
#  set(CONFIG_USE_middleware_lwip_contrib_udpecho_raw true)

#set.middleware.mbedtls
#  # description: mbedTLS Template
#  set(CONFIG_USE_middleware_mbedtls_template true)

#  # description: els_pkc config
#  set(CONFIG_USE_middleware_mbedtls_els_pkc_config true)

#  # description: mbedTLS test suite
#  set(CONFIG_USE_middleware_mbedtls_tests true)

#  # description: mbedTLS 3rdparty code
#  set(CONFIG_USE_middleware_mbedtls_3rdparty true)

#  # description: mbedTLS port library for KPSDK
#  set(CONFIG_USE_middleware_mbedtls_port_ksdk true)

#  # description: mbedTLS library
#  set(CONFIG_USE_middleware_mbedtls true)

#set.middleware.sdmmc
#  # description: Middleware sdmmc common
#  set(CONFIG_USE_middleware_sdmmc_common true)

#  # description: Template configuration file to be edited by user.
#  set(CONFIG_USE_middleware_sdmmc_sdhc_template true)

#  # description: Template configuration file to be edited by user.
#  set(CONFIG_USE_middleware_sdmmc_sdif_template true)

#  # description: Template configuration file to be edited by user.
#  set(CONFIG_USE_middleware_sdmmc_usdhc_template true)

#  # description: Middleware sdmmc osa_bm
#  set(CONFIG_USE_middleware_sdmmc_osa_bm true)

#  # description: Middleware sdmmc osa_freertos
#  set(CONFIG_USE_middleware_sdmmc_osa_freertos true)

#  # description: Middleware sdmmc sd
#  set(CONFIG_USE_middleware_sdmmc_sd true)

#  # description: Middleware sdmmc mmc
#  set(CONFIG_USE_middleware_sdmmc_mmc true)

#  # description: Middleware sdmmc sdio
#  set(CONFIG_USE_middleware_sdmmc_sdio true)

#  # description: Middleware sdmmc host sdif
#  set(CONFIG_USE_middleware_sdmmc_host_sdif true)

#  # description: Middleware sdmmc host sdif freertos
#  set(CONFIG_USE_middleware_sdmmc_host_sdif_freertos true)

#  # description: Middleware sdmmc host sdif interrupt
#  set(CONFIG_USE_middleware_sdmmc_host_sdif_interrupt true)

#  # description: Middleware sdmmc host sdif polling
#  set(CONFIG_USE_middleware_sdmmc_host_sdif_polling true)

#  # description: SDMMC host controller cache dependency
#  set(CONFIG_USE_middleware_sdmmc_host_usdhc_cache true)

#set.middleware.usb
#  # description: USB device phydcd config header
#  set(CONFIG_USE_middleware_usb_phydcd_config_header true)

#  # description: USB device hsdcd config header
#  set(CONFIG_USE_middleware_usb_hsdcd_config_header true)

#  # description: USB device ip3511fs config header
#  set(CONFIG_USE_middleware_usb_device_ip3511fs_config_header true)

#  # description: USB device ip3511hs config header
#  set(CONFIG_USE_middleware_usb_device_ip3511hs_config_header true)

#  # description: Middleware usb common_header
#  set(CONFIG_USE_middleware_usb_common_header true)

#  # description: Middleware usb device common_header
#  set(CONFIG_USE_middleware_usb_device_common_header true)

#  # description: Middleware usb device ip3511fs
#  set(CONFIG_USE_middleware_usb_device_ip3511fs true)

#  # description: Middleware usb device ip3511hs
#  set(CONFIG_USE_middleware_usb_device_ip3511hs true)

#  # description: Middleware usb device stack external
#  set(CONFIG_USE_middleware_usb_device_stack_external true)

#  # description: Middleware usb device audio external
#  set(CONFIG_USE_middleware_usb_device_audio_external true)

#  # description: Middleware usb device cdc external
#  set(CONFIG_USE_middleware_usb_device_cdc_external true)

#  # description: Middleware usb device cdc rndis external
#  set(CONFIG_USE_middleware_usb_device_cdc_rndis_external true)

#  # description: Middleware usb device hid external
#  set(CONFIG_USE_middleware_usb_device_hid_external true)

#  # description: Middleware usb device dfu external
#  set(CONFIG_USE_middleware_usb_device_dfu_external true)

#  # description: Middleware usb device msd external
#  set(CONFIG_USE_middleware_usb_device_msd_external true)

#  # description: Middleware usb device phdc external
#  set(CONFIG_USE_middleware_usb_device_phdc_external true)

#  # description: Middleware usb device video external
#  set(CONFIG_USE_middleware_usb_device_video_external true)

#  # description: Middleware usb device ccid external
#  set(CONFIG_USE_middleware_usb_device_ccid_external true)

#  # description: Middleware usb device printer external
#  set(CONFIG_USE_middleware_usb_device_printer_external true)

#  # description: Middleware usb device controller driver
#  set(CONFIG_USE_middleware_usb_device_controller_driver true)

#  # description: Middleware usb host ohci
#  set(CONFIG_USE_middleware_usb_host_ohci true)

#  # description: Middleware usb host ip3516hs
#  set(CONFIG_USE_middleware_usb_host_ip3516hs true)

#  # description: Middleware usb host audio
#  set(CONFIG_USE_middleware_usb_host_audio true)

#  # description: Middleware usb host cdc
#  set(CONFIG_USE_middleware_usb_host_cdc true)

#  # description: Middleware usb host cdc_ecm
#  set(CONFIG_USE_middleware_usb_host_cdc_ecm true)

#  # description: Middleware usb host cdc_rndis
#  set(CONFIG_USE_middleware_usb_host_cdc_rndis true)

#  # description: Middleware usb host hid
#  set(CONFIG_USE_middleware_usb_host_hid true)

#  # description: Middleware usb host msd
#  set(CONFIG_USE_middleware_usb_host_msd true)

#  # description: Middleware usb host video
#  set(CONFIG_USE_middleware_usb_host_video true)

#  # description: Middleware usb host phdc
#  set(CONFIG_USE_middleware_usb_host_phdc true)

#  # description: Middleware usb host printer
#  set(CONFIG_USE_middleware_usb_host_printer true)

#  # description: Middleware usb host common_header
#  set(CONFIG_USE_middleware_usb_host_common_header true)

#  # description: USB host ohci config header
#  set(CONFIG_USE_middleware_usb_host_ohci_config_header true)

#  # description: USB host ip3516hs config header
#  set(CONFIG_USE_middleware_usb_host_ip3516hs_config_header true)

#  # description: Middleware usb host stack
#  set(CONFIG_USE_middleware_usb_host_stack true)

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

#set.middleware.fatfs
#  # description: FatFs
#  set(CONFIG_USE_middleware_fatfs true)

#  # description: FatFs_MMC
#  set(CONFIG_USE_middleware_fatfs_mmc true)

#  # description: FatFs_RAM
#  set(CONFIG_USE_middleware_fatfs_ram true)

#  # description: FatFs_SD
#  set(CONFIG_USE_middleware_fatfs_sd true)

#  # description: FatFs template MMC
#  set(CONFIG_USE_middleware_fatfs_template_mmc true)

#  # description: FatFs template RAM
#  set(CONFIG_USE_middleware_fatfs_template_ram true)

#  # description: FatFs template SD
#  set(CONFIG_USE_middleware_fatfs_template_sd true)

#  # description: FatFs template USB
#  set(CONFIG_USE_middleware_fatfs_template_usb true)

#  # description: FatFs_USB
#  set(CONFIG_USE_middleware_fatfs_usb true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
  ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
  ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/project_template
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/lpcxpresso54s018m
)

include(set_board_lpcxpresso54s018m OPTIONAL)
include(set_CMSIS_DSP_Lib OPTIONAL)
include(set_CMSIS OPTIONAL)
include(set_device_LPC54S018M OPTIONAL)
include(set_component_osa OPTIONAL)
include(set_middleware_fatfs OPTIONAL)
include(set_middleware_freertos-kernel OPTIONAL)
include(set_middleware_littlefs OPTIONAL)
include(set_middleware_lwip OPTIONAL)
include(set_middleware_mbedtls OPTIONAL)
include(set_middleware_sdmmc OPTIONAL)
include(set_middleware_usb OPTIONAL)
