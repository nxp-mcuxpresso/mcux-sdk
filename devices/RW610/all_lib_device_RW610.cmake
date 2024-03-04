list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/els_pkc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/messaging
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rng
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rpmsg
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/time_stamp
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mcuboot_opensource/boot/bootutil
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
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
#    include(utility_shell)
#    include(driver_iped)
#    include(component_osa_bm)
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
#    include(component_els_pkc_trng_type_rng4)
#    include(driver_i2s_bridge)
#    include(middleware_usb_host_hid)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(component_els_pkc_pre_processor)
#    include(middleware_usb_host_cdc_rndis)
#    include(component_els_pkc_pkc)
#    include(driver_gdma)
#    include(component_els_pkc_examples)
#    include(utilities_misc_utilities_RW612)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(driver_sctimer)
#    include(component_els_pkc_standalone_keyManagement)
#    include(driver_ctimer)
#    include(component_els_pkc_els_common)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(middleware_freertos-kernel_heap_3)
#    include(middleware_mbedtls_port_els)
#    include(driver_reset)
#    include(component_els_pkc_platform_rw61x)
#    include(component_common_task)
#    include(component_els_pkc_core)
#    include(middleware_usb_host_ehci_RW612)
#    include(driver_clock)
#    include(component_log)
#    include(utility_str)
#    include(component_els_pkc_random_modes)
#    include(middleware_lwip_usb_ethernetif_RW612)
#    include(driver_flexcomm_usart_dma)
#    include(driver_powerquad_cmsis)
#    include(driver_flexcomm_spi_dma)
#    include(middleware_usb_device_stack_external)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(driver_common)
#    include(driver_cns_io_mux)
#    include(component_mflash_common)
#    include(component_els_pkc_aes)
#    include(driver_flexcomm_i2c_dma)
#    include(driver_imu)
#    include(component_els_pkc_aead)
#    include(middleware_freertos-kernel_extension)
#    include(component_els_pkc_key)
#    include(component_els_pkc_math)
#    include(component_software_rng_adapter)
#    include(component_els_pkc_hmac)
#    include(middleware_lwip_contrib_ping)
#    include(driver_power)
#    include(component_els_pkc_padding)
#    include(component_els_pkc_els)
#    include(component_els_pkc_ecc)
#    include(component_usart_adapter)
#    include(component_log_backend_debugconsole_RW612)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(component_els_pkc_els_header_only)
#    include(driver_trng)
#    include(driver_flexspi_dma)
#    include(driver_lpc_crc)
#    include(middleware_lwip_RW612)
#    include(device_startup)
#    include(driver_dmic)
#    include(component_els_pkc_platform_rw61x_interface_files)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(component_els_pkc_prng)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_usb_host_common_header)
#    include(component_messaging)
#    include(driver_flexcomm_i2s)
#    include(driver_itrc_1)
#    include(component_osa_free_rtos_RW612)
#    include(middleware_lwip_apps_httpd_support)
#    include(component_button_RW612)
#    include(middleware_mbedtls_port_els_pkc)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_httpd)
#    include(driver_lcdic)
#    include(driver_cns_acomp)
#    include(middleware_usb_device_controller_driver_RW612)
#    include(component_els_pkc_standalone_gdet)
#    include(driver_cmsis_flexcomm_i2c)
#    include(component_els_pkc_param_integrity)
#    include(driver_cmsis_flexcomm_spi)
#    include(driver_cns_dac)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(middleware_fatfs_ram)
#    include(component_els_pkc_hashmodes)
#    include(component_mem_manager_light)
#    include(component_els_pkc_cipher_modes)
#    include(driver_phy-common_RW612)
#    include(middleware_lwip_apps_httpsrv_RW612)
#    include(middleware_lwip_apps_mdns_RW612)
#    include(middleware_lwip_apps_lwiperf_RW612)
#    include(component_lists)
#    include(component_osa_interface)
#    include(middleware_usb_host_msd)
#    include(driver_lcdic_dma)
#    include(component_wireless_imu_adapter)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_debug_console)
#    include(middleware_usb_host_stack_RW612)
#    include(middleware_usb_phy)
#    include(middleware_freertos-kernel_RW612)
#    include(middleware_lwip_enet_ethernetif_RW612)
#    include(driver_flexcomm)
#    include(component_els_pkc_cipher)
#    include(driver_flexspi)
#    include(driver_cdog)
#    include(component_els_pkc_rsa)
#    include(middleware_mbedtls_els_pkc_config)
#    include(middleware_usb_device_ehci_RW612)
#    include(component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor)
#    include(driver_mrt)
#    include(driver_memory)
#    include(middleware_usb_device_cdc_external)
#    include(component_els_pkc_random)
#    include(component_osa)
#    include(component_mem_manager)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_lpc_gpio)
#    include(driver_enet)
#    include(component_els_pkc_session)
#    include(component_els_pkc_flow_protection)
#    include(component_els_pkc_mac)
#    include(driver_cache_cache64)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_usb_host_printer)
#    include(driver_utick)
#    include(middleware_lwip_apps_mqtt)
#    include(driver_powerquad)
#    include(driver_cmsis_flexcomm_usart)
#    include(component_lpc_gpio_adapter)
#    include(component_timer_manager)
#    include(driver_cns_adc)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_mrt_adapter)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(component_els_pkc_data_integrity)
#    include(driver_pint)
#    include(middleware_fatfs_RW612)
#    include(utility_assert_lite)
#    include(component_els_pkc_hash)
#    include(driver_dmic_dma)
#    include(middleware_usb_host_phdc)
#    include(component_els_pkc)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(driver_romapi)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_fmeas)
#    include(component_els_pkc_mac_modes)
#    include(driver_inputmux_connections)
#    include(driver_ostimer)
#    include(middleware_mbedtls_RW612)
#    include(middleware_usb_common_header)
#    include(component_serial_manager)
#    include(component_els_pkc_memory)
#    include(middleware_littlefs)
#    include(driver_inputmux)
