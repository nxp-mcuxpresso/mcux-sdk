list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkbimxrt1050/xip
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
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1052
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/EAP
    ${CMAKE_CURRENT_LIST_DIR}/../../../components/edgefast_wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite/third_party/cmsis
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/ogg
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/opus
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/mcu-audio/opusfile
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/maestro/streamer
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mcuboot_opensource/boot/bootutil
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/vit
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wireless/ethermind
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
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_lpuart_freertos)
#    include(middleware_maestro_framework_opus)
#    include(driver_trng)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_sdmmc_mmc)
#    include(driver_dmamux)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_lwip_apps_lwiperf)
#    include(driver_nor_flash-controller-flexspi)
#    include(driver_cmsis_lpuart)
#    include(middleware_azure_rtos_nxd)
#    include(device_system)
#    include(driver_snvs_lp)
#    include(component_button_MIMXRT1052)
#    include(middleware_maestro_framework)
#    include(driver_dc-fb-common)
#    include(driver_camera-device-mt9m114)
#    include(middleware_wifi_wifidriver)
#    include(driver_flexio_uart)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_eap_exapp)
#    include(middleware_wifi_sdio)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1052)
#    include(middleware_maestro_framework_opusfile)
#    include(driver_flexio)
#    include(driver_aoi)
#    include(driver_bee)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(component_cs42448_adapter)
#    include(middleware_eap_arm_lib)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_mcuboot_bootutil)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_wdog01)
#    include(driver_flexio_uart_edma)
#    include(driver_ocotp)
#    include(driver_codec)
#    include(driver_pxp)
#    include(driver_xip_device)
#    include(middleware_eiq_deepviewrt_deps_stb)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager)
#    include(driver_camera-device-ov7725)
#    include(driver_pit)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_cmsis_nn)
#    include(middleware_azure_rtos_ux)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(middleware_mbedtls_port_ksdk)
#    include(utility_debug_console_lite)
#    include(component_log_backend_debugconsole)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(driver_rtt_MIMXRT1052)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1052)
#    include(middleware_wifi_common_files)
#    include(driver_tempmon)
#    include(middleware_lwip_contrib_ping)
#    include(component_lpuart_adapter)
#    include(middleware_edgefast_wifi_nxp)
#    include(driver_lpi2c_edma)
#    include(middleware_azure_rtos_tx_template_MIMXRT1052)
#    include(middleware_lwip_apps_mqtt)
#    include(middleware_edgefast_wifi)
#    include(middleware_lwip_apps_httpsrv)
#    include(middleware_usb_device_cdc_external)
#    include(driver_cmsis_enet)
#    include(utility_shell)
#    include(device_startup)
#    include(middleware_eiq_deepviewrt_modelrunner_server)
#    include(component_mflash_rt1050)
#    include(middleware_eiq_deepviewrt_deps_flatcc)
#    include(component_panic)
#    include(driver_phy-device-ksz8081)
#    include(driver_usdhc)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_enet)
#    include(middleware_wifi)
#    include(component_mflash_file_MIMXRT1052)
#    include(driver_rtwdog)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_camera-receiver-common)
#    include(driver_nor_flash-common)
#    include(middleware_usb_common_header)
#    include(driver_cmsis_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_soc_flexram_allocate)
#    include(component_serial_manager_usb_cdc)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1052)
#    include(device_CMSIS)
#    include(driver_romapi)
#    include(middleware_usb_host_stack_MIMXRT1052)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_azure_rtos_fx)
#    include(driver_ft5406_rt)
#    include(component_osa_bm)
#    include(driver_camera-device-sccb)
#    include(driver_adc_12b1msps_sar)
#    include(component_mflash_dummy)
#    include(driver_common)
#    include(middleware_eiq_gui_printf)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(driver_kpp)
#    include(middleware_wifi_fwdnld_MIMXRT1052)
#    include(driver_edma_MIMXRT1052)
#    include(middleware_lwip_apps_httpd_support)
#    include(component_osa_free_rtos)
#    include(driver_camera-common)
#    include(driver_camera-device-common)
#    include(component_lpi2c_adapter)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_video-common)
#    include(driver_xip_board_evkbimxrt1050)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_dcdc_1)
#    include(middleware_usb_device_stack_external)
#    include(middleware_azure_rtos_tx)
#    include(middleware_azure_rtos_fx_template_MIMXRT1052)
#    include(middleware_lwip_apps_mdns)
#    include(middleware_eap)
#    include(middleware_sdmmc_sdio)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(middleware_eiq_deepviewrt_deps_json)
#    include(driver_snvs_hp)
#    include(middleware_usb_host_msd)
#    include(middleware_usb_device_ehci_MIMXRT1052)
#    include(driver_lpspi)
#    include(middleware_usb_device_controller_driver_MIMXRT1052)
#    include(component_gpt_adapter)
#    include(middleware_usb_host_common_header)
#    include(driver_csi)
#    include(component_log)
#    include(middleware_usb_host_cdc)
#    include(middleware_eiq_worker)
#    include(driver_clock)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_gt911)
#    include(component_audio_sai_edma_adapter)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_printer)
#    include(driver_iomuxc)
#    include(middleware_azure_rtos_ux_template_MIMXRT1052)
#    include(middleware_usb_device_common_header)
#    include(driver_flexio_spi_edma)
#    include(driver_flexram)
#    include(middleware_azure_rtos_gx)
#    include(middleware_eap16_header)
#    include(driver_semc)
#    include(driver_xbarb)
#    include(driver_xbara)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(middleware_lwip_usb_ethernetif)
#    include(driver_flexcan)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_osa_thread)
#    include(middleware_freertos-kernel_MIMXRT1052)
#    include(middleware_fatfs_ram)
#    include(middleware_wifi_cli)
#    include(middleware_wifi_sdio-2)
#    include(component_mflash_common)
#    include(driver_cmsis_lpspi)
#    include(middleware_azure_rtos_azure_iot)
#    include(component_flexspi_hyper_flash_adapter_rt1050)
#    include(utility_assert_lite)
#    include(driver_camera-receiver-csi)
#    include(middleware_vit_cm7)
#    include(component_wm8960_adapter)
#    include(middleware_eiq_worker_audio)
#    include(driver_enc)
#    include(middleware_usb_phy)
#    include(driver_sai_edma)
#    include(driver_dc-fb-elcdif)
#    include(driver_dcp)
#    include(component_silicon_id_rt10xx)
#    include(middleware_maestro_framework_doc)
#    include(middleware_fatfs_sd)
#    include(middleware_sdmmc_osa_azurertos)
#    include(driver_flexspi)
#    include(driver_adc_etc)
#    include(component_timer_manager)
#    include(driver_lpi2c_freertos)
#    include(driver_qtmr_1)
#    include(driver_pwm)
#    include(component_common_task)
#    include(middleware_usb_host_video)
#    include(driver_gpc_1)
#    include(component_lists)
#    include(driver_video-i2c)
#    include(middleware_sdmmc_common)
#    include(utilities_misc_utilities_MIMXRT1052)
#    include(middleware_maestro_framework_ogg)
#    include(driver_cmp)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(component_igpio_adapter)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(middleware_littlefs)
#    include(driver_flexio_spi)
#    include(component_pit_adapter)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1052)
#    include(middleware_eiq_worker_video_MIMXRT1052)
#    include(component_silicon_id_MIMXRT1052)
#    include(middleware_mbedtls_rt)
#    include(middleware_edgefast_bluetooth_k32w061_controller)
#    include(driver_fbdev)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(middleware_usb_host_ehci_MIMXRT1052)
#    include(middleware_fatfs_usb)
#    include(middleware_lwip_empty_ethernetif)
#    include(middleware_lwip_contrib_tcpecho)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(driver_cs42448)
#    include(middleware_sdmmc_sd)
#    include(driver_src)
#    include(middleware_eiq_mpp_MIMXRT1052)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1052)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(middleware_fatfs_MIMXRT1052)
#    include(driver_flexio_i2s)
#    include(middleware_lwip)
#    include(middleware_usb_host_audio)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(middleware_maestro_framework_streamer)
#    include(middleware_azure_rtos_lx)
#    include(driver_elcdif)
#    include(driver_igpio)
#    include(component_codec_i2c_MIMXRT1052)
#    include(middleware_sdmmc_host_usdhc_azurertos)
#    include(driver_sai)
#    include(middleware_eiq_glow)
#    include(middleware_eiq_deepviewrt)
#    include(driver_cache_armv7_m7)
#    include(middleware_mbedtls_MIMXRT1052)
#    include(driver_phy-common_MIMXRT1052)
#    include(middleware_lwip_apps_httpssrv)
#    include(driver_flexio_i2s_edma)
