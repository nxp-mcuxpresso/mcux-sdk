list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkbmimxrt1060/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1060/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42448
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1062
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406_rt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/internal_flash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/rt10xx
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/mt9m114
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/ov7725
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/sccb
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver/csi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/elcdif
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/fbdev
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_12b1msps_sar
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/bee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv7-m7
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/csi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcdc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/elcdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexram
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kpp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ocotp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pxp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qtmr_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtwdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/semc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/src
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempmon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbarb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/edgefast_wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite/third_party/cmsis
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/ogg
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/opus
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/opusfile
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/streamer
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mcuboot_opensource/boot/bootutil
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/azure-rtos
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_cmsis_nn)
#    include(middleware_lwip_contrib_tcpecho)
#    include(CMSIS_Driver_Include_Ethernet)
#    include(driver_dc-fb-common)
#    include(middleware_eiq_worker)
#    include(middleware_mcuboot_bootutil)
#    include(middleware_usb_host_ehci_MIMXRT1062)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(CMSIS_Driver_Include_I2C)
#    include(component_lpi2c_adapter)
#    include(middleware_wifi_fwdnld_MIMXRT1062)
#    include(middleware_usb_host_hid)
#    include(driver_camera-device-common)
#    include(driver_gpt)
#    include(driver_lpi2c_edma)
#    include(middleware_sdmmc_osa_azurertos)
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_kpp)
#    include(component_codec_adapters)
#    include(CMSIS_DSP_Source)
#    include(middleware_sdmmc_host_usdhc)
#    include(driver_src)
#    include(component_wm8960_adapter)
#    include(driver_flexspi_edma)
#    include(driver_dmamux)
#    include(driver_ft5406_rt)
#    include(driver_flexcan_edma)
#    include(middleware_wifi_wifidriver_MIMXRT1062)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_common_task)
#    include(driver_clock)
#    include(middleware_eiq_deepviewrt_deps_json)
#    include(driver_lpuart_edma)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(driver_bee)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(component_lpuart_adapter)
#    include(middleware_eiq_worker_audio)
#    include(middleware_lwip_empty_ethernetif)
#    include(middleware_maestro_framework_opus)
#    include(middleware_eiq_worker_video_MIMXRT1062)
#    include(middleware_usb_device_stack_external)
#    include(middleware_sdmmc_mmc)
#    include(component_flexspi_nor_flash_adapter_rt1060evkb)
#    include(middleware_mbedtls_MIMXRT1062)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(driver_lpspi)
#    include(middleware_lwip_apps_httpsrv_MIMXRT1062)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_iomuxc)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1062)
#    include(driver_common)
#    include(driver_flexcan)
#    include(middleware_lwip_usb_ethernetif_MIMXRT1062)
#    include(middleware_lwip_apps_httpssrv_MIMXRT1062)
#    include(component_mflash_common)
#    include(driver_cmp)
#    include(middleware_issdk_sensor_fxas21002)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1062)
#    include(driver_pxp)
#    include(driver_elcdif)
#    include(component_mflash_dummy)
#    include(middleware_azure_rtos_gx)
#    include(middleware_usb_device_controller_driver_MIMXRT1062)
#    include(middleware_lwip_contrib_ping)
#    include(middleware_wifi_cli_MIMXRT1062)
#    include(driver_cmsis_enet)
#    include(middleware_usb_host_stack_MIMXRT1062)
#    include(component_serial_manager_uart)
#    include(driver_pwm)
#    include(middleware_azure_rtos_tx_template_MIMXRT1062)
#    include(driver_flexio_i2s)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_xbarb)
#    include(driver_aoi)
#    include(driver_trng)
#    include(component_mflash_file_MIMXRT1062)
#    include(middleware_edgefast_wifi_nxp)
#    include(driver_csi)
#    include(device_startup)
#    include(middleware_sdmmc_osa_bm)
#    include(component_button_MIMXRT1062)
#    include(component_silicon_id_rt10xx)
#    include(driver_phy-device-ksz8081)
#    include(middleware_multicore_erpc_common)
#    include(component_log_backend_debugconsole_MIMXRT1062)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_edma_MIMXRT1062)
#    include(driver_snvs_hp)
#    include(driver_camera-common)
#    include(device_CMSIS)
#    include(driver_xip_device)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(middleware_fatfs_usb)
#    include(middleware_freertos-kernel_MIMXRT1062)
#    include(middleware_usb_host_common_header)
#    include(driver_rtwdog)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_sdmmc_common)
#    include(component_serial_manager_swo)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(middleware_lwip_MIMXRT1062)
#    include(middleware_issdk_sensor_interface_common)
#    include(middleware_eiq_gui_printf)
#    include(middleware_lwip_apps_httpd_support)
#    include(component_audio_sai_edma_adapter)
#    include(component_codec_i2c_MIMXRT1062)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1062)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_maestro_framework)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(middleware_sdmmc_sd)
#    include(driver_gpc_1)
#    include(driver_cmsis_lpspi)
#    include(middleware_maestro_framework_opusfile)
#    include(middleware_usb_device_ehci_MIMXRT1062)
#    include(driver_dc-fb-elcdif)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_soc_flexram_allocate)
#    include(middleware_fatfs_ram)
#    include(middleware_maestro_framework_streamer_MIMXRT1062)
#    include(driver_enc)
#    include(driver_adc_12b1msps_sar)
#    include(driver_nor_flash-controller-flexspi)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_lpspi_freertos)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(middleware_usb_host_msd)
#    include(driver_qtmr_1)
#    include(middleware_lwip_apps_mdns_MIMXRT1062)
#    include(middleware_wifi_sdio-2)
#    include(driver_dcp)
#    include(component_cs42448_adapter)
#    include(driver_wm8960)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_debug_console)
#    include(driver_dcdc_1)
#    include(middleware_azure_rtos_tx)
#    include(middleware_usb_phy)
#    include(component_igpio_adapter)
#    include(driver_camera-device-ov7725)
#    include(middleware_mbedtls_rt)
#    include(middleware_azure_rtos_nxd)
#    include(middleware_fatfs_MIMXRT1062)
#    include(middleware_issdk_sensor_fxos8700)
#    include(middleware_eiq_deepviewrt_modelrunner_server_flash)
#    include(driver_flexspi)
#    include(driver_flexio_uart)
#    include(component_osa_free_rtos_MIMXRT1062)
#    include(driver_cs42448)
#    include(driver_camera-device-sccb)
#    include(driver_usdhc)
#    include(driver_lpuart_freertos)
#    include(utilities_misc_utilities_MIMXRT1062)
#    include(driver_fbdev)
#    include(driver_flexram)
#    include(driver_adc_etc)
#    include(driver_ewm)
#    include(middleware_azure_rtos_lx)
#    include(middleware_azure_rtos_ux)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_usb_device_cdc_external)
#    include(middleware_eiq_deepviewrt_deps_stb)
#    include(component_osa)
#    include(driver_xip_board_evkmimxrt1060)
#    include(middleware_issdk_drivers_gpio_imx)
#    include(driver_rtt_MIMXRT1062)
#    include(CMSIS_Include_core_cm)
#    include(middleware_eiq_glow)
#    include(driver_enet)
#    include(driver_camera-receiver-common)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(middleware_usb_host_printer)
#    include(middleware_azure_rtos_ux_template_MIMXRT1062)
#    include(middleware_wifi_MIMXRT1062)
#    include(driver_lpspi_edma)
#    include(middleware_lwip_apps_mqtt)
#    include(driver_camera-receiver-csi)
#    include(middleware_edgefast_wifi)
#    include(component_osa_thread)
#    include(component_timer_manager)
#    include(driver_snvs_lp)
#    include(driver_tempmon)
#    include(middleware_baremetal)
#    include(middleware_eiq_deepviewrt)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(driver_cache_armv7_m7)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(utility_debug_console_lite)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_camera-device-mt9m114)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_sdmmc_sdio)
#    include(driver_gt911)
#    include(middleware_wifi_common_files)
#    include(driver_sai_edma)
#    include(driver_semc)
#    include(driver_nor_flash-common)
#    include(component_gpt_adapter)
#    include(device_system)
#    include(middleware_sdmmc_host_usdhc_azurertos)
#    include(utility_assert_lite)
#    include(component_mflash_rt1060)
#    include(middleware_azure_rtos_fx_template_MIMXRT1062)
#    include(middleware_eiq_deepviewrt_deps_flatcc)
#    include(middleware_maestro_framework_ogg)
#    include(middleware_usb_host_phdc)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(driver_flexio_i2s_edma)
#    include(driver_xip_board_evkbmimxrt1060)
#    include(middleware_maestro_framework_doc)
#    include(driver_romapi)
#    include(middleware_azure_rtos_azure_iot)
#    include(driver_igpio)
#    include(driver_sai)
#    include(driver_flexio_uart_edma)
#    include(driver_xbara)
#    include(driver_flexio)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(component_silicon_id_MIMXRT1062)
#    include(driver_video-common)
#    include(driver_video-i2c)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1062)
#    include(component_flexspi_nor_flash_adapter_rt1060)
#    include(driver_flexio_spi)
#    include(middleware_lwip_apps_lwiperf_MIMXRT1062)
#    include(middleware_wifi_sdio)
#    include(middleware_usb_common_header)
#    include(driver_wdog01)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1062)
#    include(component_serial_manager)
#    include(driver_phy-common_MIMXRT1062)
#    include(middleware_azure_rtos_fx)
#    include(middleware_littlefs)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_lpi2c)
