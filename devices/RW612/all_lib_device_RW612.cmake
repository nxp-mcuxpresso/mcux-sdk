list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/RTX/Library
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/rdrw612bga/flash_config
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/conn_fwloader
    ${CMAKE_CURRENT_LIST_DIR}/../../components/els_pkc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/rdrw612bga
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/messaging
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/core
    ${CMAKE_CURRENT_LIST_DIR}/../../components/power_manager/devices/RW612
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rng
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rpmsg
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/rw610
    ${CMAKE_CURRENT_LIST_DIR}/../../components/time_stamp
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/cache64
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cns_acomp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cns_adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cns_dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gdma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/imu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/itrc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smartcard
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/edgefast_bluetooth
    ${CMAKE_CURRENT_LIST_DIR}/../../components/edgefast_wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/streamer
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mcuboot_opensource/boot/bootutil
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/vit
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/voice_seeker/ARM_CortexM33_noDSP
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wireless/ethermind
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wireless/framework
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wireless/wpa_supplicant-rtos
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/shell
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/romapi
)


# Copy the cmake components into projects
#    include(component_ostimer_time_stamp_adapter)
#    include(middleware_edgefast_bluetooth_btble_ethermind_cm33nodsp)
#    include(driver_iped)
#    include(utility_shell)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(middleware_edgefast_bluetooth_porting_net)
#    include(driver_ili9341)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_lpc_rtc)
#    include(component_els_pkc_secure_counter)
#    include(middleware_mcuboot_bootutil)
#    include(component_els_pkc_psa_driver)
#    include(component_els_pkc_aead_modes)
#    include(component_els_pkc_toolchain)
#    include(driver_flexcomm_spi)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(component_els_pkc_trng)
#    include(component_silicon_id_rw610)
#    include(component_els_pkc_trng_type_rng4)
#    include(driver_i2s_bridge)
#    include(middleware_edgefast_bluetooth_profile_hrs)
#    include(middleware_usb_host_hid)
#    include(component_mflash_rdrw610)
#    include(component_els_pkc_pre_processor)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(component_els_pkc_pkc)
#    include(driver_gdma)
#    include(middleware_usb_host_cdc_rndis)
#    include(component_els_pkc_examples)
#    include(middleware_edgefast_bluetooth_profile_hps)
#    include(middleware_wireless_framework_Common)
#    include(utilities_misc_utilities_RW612)
#    include(driver_smartcard_phy_usim)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(driver_sctimer)
#    include(component_power_manager_core)
#    include(component_els_pkc_standalone_keyManagement)
#    include(driver_rtt_RW612)
#    include(driver_ctimer)
#    include(component_els_pkc_els_common)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(middleware_freertos-kernel_heap_3)
#    include(middleware_wireless_framework_platform_common)
#    include(middleware_edgefast_bluetooth_ble_ethermind_cm33nodsp)
#    include(middleware_edgefast_bluetooth_porting_list)
#    include(driver_reset)
#    include(middleware_mbedtls_port_els)
#    include(middleware_edgefast_bluetooth_profile_wu)
#    include(component_els_pkc_platform_rw61x)
#    include(component_common_task)
#    include(component_els_pkc_core)
#    include(middleware_usb_host_ehci_RW612)
#    include(driver_clock)
#    include(component_log)
#    include(utility_str)
#    include(component_els_pkc_random_modes)
#    include(middleware_wifi_wps)
#    include(middleware_lwip_usb_ethernetif_RW612)
#    include(driver_flexcomm_usart_dma)
#    include(driver_powerquad_cmsis)
#    include(component_silicon_id_RW612)
#    include(driver_flexcomm_spi_dma)
#    include(middleware_usb_device_stack_external)
#    include(middleware_wifi_cli_RW612)
#    include(middleware_wifi_dpp)
#    include(middleware_wifi_imu)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(middleware_edgefast_bluetooth_porting)
#    include(driver_common)
#    include(middleware_voice_seeker_cm33_nodsp)
#    include(middleware_wireless_Sensors)
#    include(middleware_wireless_framework_LPM_systicks)
#    include(driver_cns_io_mux)
#    include(component_mflash_file_RW612)
#    include(component_mflash_common)
#    include(component_els_pkc_aes)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_wireless_framework_platform_sensors)
#    include(driver_imu)
#    include(component_els_pkc_aead)
#    include(middleware_edgefast_bluetooth_pal)
#    include(middleware_freertos-kernel_extension)
#    include(component_els_pkc_key)
#    include(middleware_wireless_framework_fwk_debug)
#    include(component_els_pkc_math)
#    include(component_software_rng_adapter)
#    include(middleware_wifi_jsmn)
#    include(component_els_pkc_hmac)
#    include(middleware_lwip_contrib_ping)
#    include(driver_power)
#    include(middleware_edgefast_bluetooth_pal_platform_ethermind)
#    include(component_els_pkc_padding)
#    include(middleware_edgefast_bluetooth_shell_ble)
#    include(component_els_pkc_els)
#    include(component_els_pkc_ecc)
#    include(component_usart_adapter)
#    include(component_log_backend_debugconsole_RW612)
#    include(middleware_edgefast_bluetooth_pal_host_msd_fatfs_ethermind)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(component_els_pkc_els_header_only)
#    include(driver_trng)
#    include(driver_flexspi_dma)
#    include(middleware_edgefast_wifi_nxp)
#    include(driver_lpc_crc)
#    include(middleware_lwip_RW612)
#    include(device_startup)
#    include(driver_dmic)
#    include(component_els_pkc_platform_rw61x_interface_files)
#    include(driver_phy-device-ksz8081)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(component_els_pkc_prng)
#    include(middleware_edgefast_bluetooth_extension_common_ethermind)
#    include(middleware_wireless_framework_platform)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_edgefast_bluetooth_config_ethermind)
#    include(middleware_maestro_framework_streamer_RW612)
#    include(middleware_usb_host_common_header)
#    include(component_messaging)
#    include(driver_flexcomm_i2s)
#    include(driver_itrc_1)
#    include(component_osa_free_rtos_RW612)
#    include(middleware_lwip_apps_httpd_support)
#    include(CMSIS_RTOS2_NonSecure OPTIONAL)
#    include(component_button_RW612)
#    include(middleware_mbedtls_port_els_pkc)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_httpd)
#    include(driver_lcdic)
#    include(driver_cns_acomp)
#    include(middleware_maestro_framework)
#    include(middleware_usb_device_controller_driver_RW612)
#    include(middleware_edgefast_bluetooth_porting_toolchain)
#    include(middleware_vit_cm33-rw61x)
#    include(middleware_edgefast_bluetooth_profile_pxr)
#    include(component_els_pkc_standalone_gdet)
#    include(driver_smartcard_usim)
#    include(driver_cmsis_flexcomm_i2c)
#    include(component_els_pkc_param_integrity)
#    include(driver_cmsis_flexcomm_spi)
#    include(driver_cns_dac)
#    include(driver_flexcomm_i2c)
#    include(middleware_wireless_framework_function_lib)
#    include(component_serial_manager_usb_cdc)
#    include(middleware_wireless_framework_platform_ble)
#    include(utility_assert)
#    include(middleware_fatfs_ram)
#    include(component_els_pkc_hashmodes)
#    include(middleware_wireless_framework_platform_coex)
#    include(middleware_edgefast_bluetooth_common_ethermind_hci_platform)
#    include(middleware_edgefast_bluetooth_ble_ethermind_lib_cm33nodsp)
#    include(middleware_edgefast_bluetooth_pal_db_gen_ethermind)
#    include(component_mem_manager_light)
#    include(component_els_pkc_cipher_modes)
#    include(driver_ft6x06)
#    include(driver_nor_flash-controller-flexspi)
#    include(driver_phy-common_RW612)
#    include(middleware_lwip_apps_httpsrv_RW612)
#    include(component_power_manager_rdrw610)
#    include(middleware_lwip_apps_lwiperf_RW612)
#    include(middleware_lwip_apps_mdns_RW612)
#    include(component_lists)
#    include(component_osa_interface)
#    include(middleware_usb_host_msd)
#    include(driver_lcdic_dma)
#    include(component_codec_i2c_RW612)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(component_wireless_imu_adapter)
#    include(component_wm8904_adapter)
#    include(middleware_edgefast_bluetooth_profile_fmp)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_usb_host_stack_RW612)
#    include(utility_debug_console)
#    include(middleware_lwip_apps_httpssrv_RW612)
#    include(middleware_usb_phy)
#    include(middleware_freertos-kernel_RW612)
#    include(middleware_lwip_enet_ethernetif_RW612)
#    include(middleware_wireless_framework_platform_lowpower_timer)
#    include(middleware_wifi_wls)
#    include(driver_wm8904)
#    include(driver_flexcomm)
#    include(CMSIS_RTOS2_Common OPTIONAL)
#    include(component_els_pkc_cipher)
#    include(driver_flexspi)
#    include(driver_cdog)
#    include(component_els_pkc_rsa)
#    include(middleware_edgefast_bluetooth_btble_ethermind_lib_cm33nodsp)
#    include(middleware_mbedtls_els_pkc_config)
#    include(middleware_wifi_wmtime)
#    include(middleware_wireless_wpa_supplicant_rtos)
#    include(middleware_usb_device_ehci_RW612)
#    include(component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor)
#    include(driver_mrt)
#    include(driver_memory)
#    include(middleware_usb_device_cdc_external)
#    include(component_els_pkc_random)
#    include(component_osa)
#    include(middleware_wireless_framework_platform_lowpower)
#    include(middleware_edgefast_bluetooth_rw610_controller)
#    include(middleware_wireless_wpa_supplicant_dpp)
#    include(component_mem_manager)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_edgefast_bluetooth_profile_tip)
#    include(driver_lpc_gpio)
#    include(driver_enet)
#    include(component_els_pkc_session)
#    include(middleware_edgefast_bluetooth_profile_hts)
#    include(component_els_pkc_flow_protection)
#    include(component_els_pkc_mac)
#    include(middleware_wireless_framework_board_lp)
#    include(driver_cache_cache64)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_usb_host_printer)
#    include(middleware_edgefast_bluetooth_profile_ipsp)
#    include(driver_conn_fwloader)
#    include(driver_utick)
#    include(middleware_lwip_apps_mqtt)
#    include(middleware_wifi_wmcrypto)
#    include(driver_powerquad)
#    include(middleware_edgefast_bluetooth_profile_dis)
#    include(middleware_wifi_wifidriver_RW612)
#    include(middleware_wifi_RW612)
#    include(driver_cmsis_flexcomm_usart)
#    include(component_lpc_gpio_adapter)
#    include(middleware_edgefast_bluetooth_profile_bas)
#    include(component_timer_manager)
#    include(middleware_baremetal)
#    include(middleware_edgefast_wifi)
#    include(driver_cns_adc)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_mrt_adapter)
#    include(middleware_edgefast_bluetooth_common_ethermind_hci)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(component_els_pkc_data_integrity)
#    include(driver_pint)
#    include(middleware_wifi_common_files)
#    include(driver_nor_flash-common)
#    include(middleware_edgefast_bluetooth_porting_work_queue)
#    include(middleware_fatfs_RW612)
#    include(utility_assert_lite)
#    include(component_els_pkc_hash)
#    include(middleware_edgefast_bluetooth_porting_atomic)
#    include(driver_dmic_dma)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(component_flexcomm_i2c_adapter)
#    include(middleware_maestro_framework_doc)
#    include(middleware_usb_host_phdc)
#    include(component_els_pkc)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(driver_romapi)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_fmeas)
#    include(component_audio_flexcomm_i2s_dma_adapter)
#    include(component_els_pkc_mac_modes)
#    include(driver_inputmux_connections)
#    include(driver_ostimer)
#    include(middleware_mbedtls_RW612)
#    include(middleware_usb_common_header)
#    include(driver_flash_config_rdrw612bga)
#    include(component_serial_manager)
#    include(component_els_pkc_memory)
#    include(middleware_littlefs)
#    include(driver_inputmux)
#    include(middleware_edgefast_bluetooth_common_ethermind)
