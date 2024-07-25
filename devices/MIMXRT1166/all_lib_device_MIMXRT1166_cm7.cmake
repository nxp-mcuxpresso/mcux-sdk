list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1160/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1160
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406_rt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imxrt1170
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/ov5640
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/sccb
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver/csi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/elcdif
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dc/lcdifv2
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/fbdev
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/hx8394
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/mipi_dsi_cmd
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68191
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm68200
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/asrc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/caam
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/csi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcic
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iee_apc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/key_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kpp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdifv2
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mecc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_csi2rx
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi_split
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ocotp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pxp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qtmr_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc_sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtwdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema4
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/semc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smartcard
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ssarc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempsensor
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbarb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xecc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc2
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/vit
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/voice_seeker
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/voice_seeker/rdsp_utilities_public
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wireless/ethermind
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/azure-rtos
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm7
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(driver_caam)
#    include(middleware_usb_host_cdc_rndis)
#    include(utility_incbin)
#    include(driver_lpuart_freertos)
#    include(driver_cdog)
#    include(driver_asrc_edma)
#    include(driver_camera-device-ov5640)
#    include(driver_rdc)
#    include(middleware_multicore_rpmsg_lite_imxrt1160_bm)
#    include(driver_xip_board_evkmimxrt1160)
#    include(driver_asrc)
#    include(driver_dmamux)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_lwip_apps_lwiperf)
#    include(utility_shell)
#    include(driver_cmsis_lpuart)
#    include(middleware_azure_rtos_nxd)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_snvs_lp)
#    include(middleware_azure_rtos_tx_template_MIMXRT1166_cm7)
#    include(middleware_maestro_framework)
#    include(driver_dc-fb-common)
#    include(driver_lpadc)
#    include(driver_soc_mipi_csi2rx)
#    include(utilities_misc_utilities_MIMXRT1166_cm7)
#    include(middleware_usb_host_video)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(middleware_fatfs_MIMXRT1166_cm7)
#    include(driver_flexio_uart)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_eap_exapp)
#    include(middleware_wifi_sdio)
#    include(driver_sema4)
#    include(middleware_multicore_rpmsg_lite_bm)
#    include(middleware_voice_seeker_cm7)
#    include(driver_display-rm68200)
#    include(driver_aoi)
#    include(middleware_lwip)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(driver_enc)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(driver_display-common)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_sdmmc_osa_bm)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_wdog01)
#    include(middleware_multicore_erpc_eRPC_mu_rtos_transport)
#    include(driver_flexio_uart_edma)
#    include(middleware_usb_device_ehci_MIMXRT1166_cm7)
#    include(driver_ocotp)
#    include(middleware_mbedtls_rt2)
#    include(driver_codec)
#    include(middleware_maestro_framework_ogg)
#    include(middleware_usb_host_stack_MIMXRT1166_cm7)
#    include(driver_pxp)
#    include(driver_edma_MIMXRT1166_cm7)
#    include(driver_xip_device)
#    include(driver_mipi_dsi_split)
#    include(middleware_multicore_rpmsg_lite_MIMXRT1166_cm7)
#    include(middleware_eiq_deepviewrt_deps_stb)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager)
#    include(driver_lcdifv2)
#    include(driver_pit)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_cmsis_nn)
#    include(middleware_azure_rtos_ux)
#    include(component_serial_manager_uart)
#    include(driver_flexspi_edma)
#    include(middleware_mbedtls_port_ksdk)
#    include(utility_debug_console_lite)
#    include(component_log_backend_debugconsole)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(driver_soc_src)
#    include(middleware_wifi_common_files)
#    include(middleware_multicore_rpmsg_lite_imxrt1160_freertos)
#    include(middleware_lwip_contrib_ping)
#    include(component_lpuart_adapter)
#    include(middleware_edgefast_wifi_nxp)
#    include(driver_lpi2c_edma)
#    include(middleware_lwip_usb_ethernetif)
#    include(middleware_lwip_apps_mqtt)
#    include(component_silicon_id_rt1170)
#    include(middleware_lwip_apps_httpsrv)
#    include(driver_rdc_sema42)
#    include(middleware_maestro_framework_opus)
#    include(middleware_usb_device_cdc_external)
#    include(driver_cmsis_enet)
#    include(middleware_eiq_deepviewrt_modelrunner_server)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
#    include(middleware_usb_device_controller_driver_MIMXRT1166_cm7)
#    include(middleware_multicore_erpc_eRPC_mu_c_wrapper)
#    include(driver_display-rm68191)
#    include(component_panic)
#    include(driver_phy-device-ksz8081)
#    include(driver_usdhc)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_enet)
#    include(component_codec_i2c_MIMXRT1166_cm7)
#    include(middleware_wifi_wifidriver)
#    include(driver_rtwdog)
#    include(device_system_MIMXRT1166_cm7)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_wifi_fwdnld_MIMXRT1166_cm7)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_camera-receiver-common)
#    include(middleware_usb_common_header)
#    include(driver_cmsis_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_soc_flexram_allocate)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(driver_display-mipi-dsi-cmd)
#    include(driver_anatop_ai)
#    include(device_CMSIS)
#    include(driver_mecc)
#    include(driver_romapi)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(component_silicon_id_MIMXRT1166_cm7)
#    include(middleware_lwip_apps_httpd_support)
#    include(middleware_multicore_erpc_doc)
#    include(driver_ft5406_rt)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(middleware_multicore_mcmgr_imxrt1160)
#    include(driver_camera-device-sccb)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(middleware_eiq_gui_printf)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_kpp)
#    include(middleware_maestro_framework_opusfile)
#    include(component_osa_free_rtos)
#    include(driver_camera-common)
#    include(driver_camera-device-common)
#    include(component_lpi2c_adapter)
#    include(driver_dc-fb-lcdifv2)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_video-common)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_wifi_sdio-2)
#    include(middleware_voice_seeker_rdsp_utilities_public)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm7)
#    include(middleware_lwip_apps_mdns)
#    include(middleware_eap)
#    include(middleware_sdmmc_sdio)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1166_cm7)
#    include(middleware_eiq_deepviewrt_deps_json)
#    include(driver_snvs_hp)
#    include(middleware_usb_host_msd)
#    include(driver_pdm)
#    include(driver_lpspi)
#    include(driver_display-hx8394)
#    include(middleware_vit_cm7)
#    include(component_gpt_adapter)
#    include(driver_csi)
#    include(component_log)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1166_cm7)
#    include(middleware_eiq_worker)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_gt911)
#    include(component_audio_sai_edma_adapter)
#    include(driver_adc_etc)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_printer)
#    include(middleware_multicore_erpc_eRPC_mu_transport)
#    include(driver_pgmc)
#    include(driver_iomuxc)
#    include(middleware_usb_device_common_header)
#    include(driver_flexio_spi_edma)
#    include(driver_flexram)
#    include(middleware_azure_rtos_gx)
#    include(middleware_eap16_header)
#    include(driver_semc)
#    include(driver_flexio)
#    include(driver_xbarb)
#    include(driver_xbara)
#    include(driver_phy-common_MIMXRT1166_cm7)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(middleware_eiq_worker_video_MIMXRT1166_cm7)
#    include(driver_flexcan)
#    include(component_mflash_file_MIMXRT1166_cm7)
#    include(utility_debug_console)
#    include(middleware_sdmmc_osa_azurertos)
#    include(middleware_usb_host_hid)
#    include(component_osa_thread)
#    include(driver_pmu_1)
#    include(middleware_fatfs_ram)
#    include(middleware_usb_host_ehci_MIMXRT1166_cm7)
#    include(middleware_wifi_cli)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
#    include(middleware_multicore_mcmgr)
#    include(driver_smartcard_emvsim)
#    include(component_mflash_common)
#    include(driver_cmsis_lpspi)
#    include(driver_spdif_edma)
#    include(middleware_azure_rtos_azure_iot)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(utility_assert_lite)
#    include(driver_camera-receiver-csi)
#    include(component_wm8960_adapter)
#    include(driver_puf)
#    include(driver_dcic)
#    include(middleware_eiq_worker_audio)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(middleware_usb_phy)
#    include(driver_dcdc_soc)
#    include(middleware_azure_rtos_fx_template_MIMXRT1166_cm7)
#    include(driver_dc-fb-elcdif)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1166_cm7)
#    include(middleware_freertos-kernel_MIMXRT1166_cm7)
#    include(middleware_azure_rtos_fx)
#    include(middleware_fatfs_usb)
#    include(driver_xecc)
#    include(driver_iee)
#    include(middleware_maestro_framework_doc)
#    include(driver_phy-device-rtl8211f)
#    include(middleware_edgefast_wifi)
#    include(middleware_fatfs_sd)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1166_cm7)
#    include(driver_flexspi)
#    include(device_startup_MIMXRT1166_cm7)
#    include(driver_lpi2c_freertos)
#    include(driver_qtmr_1)
#    include(middleware_azure_rtos_tx)
#    include(component_common_task)
#    include(driver_gpc_3)
#    include(driver_sai_edma)
#    include(component_lists)
#    include(driver_video-i2c)
#    include(middleware_sdmmc_common)
#    include(driver_smartcard_phy_emvsim)
#    include(driver_acmp)
#    include(driver_spdif)
#    include(driver_key_manager)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(component_igpio_adapter)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_memory)
#    include(driver_lpuart)
#    include(middleware_littlefs)
#    include(driver_flexio_spi)
#    include(middleware_wifi)
#    include(component_pit_adapter)
#    include(middleware_eiq_deepviewrt)
#    include(middleware_eap_arm_lib)
#    include(middleware_edgefast_bluetooth_k32w061_controller)
#    include(driver_dac12)
#    include(driver_fbdev)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(middleware_lwip_empty_ethernetif)
#    include(middleware_azure_rtos_ux_template_MIMXRT1166_cm7)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(middleware_sdmmc_sd)
#    include(middleware_mbedtls_MIMXRT1166_cm7)
#    include(driver_xrdc2)
#    include(driver_lpi2c)
#    include(middleware_eiq_deepviewrt_deps_flatcc)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(driver_ssarc)
#    include(driver_flexio_i2s)
#    include(component_mflash_rt1160)
#    include(middleware_usb_host_audio)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(middleware_maestro_framework_streamer)
#    include(middleware_azure_rtos_lx)
#    include(driver_elcdif)
#    include(driver_igpio)
#    include(driver_pwm)
#    include(driver_mipi_csi2rx)
#    include(middleware_sdmmc_host_usdhc_azurertos)
#    include(driver_sai)
#    include(middleware_eiq_glow)
#    include(driver_pdm_edma)
#    include(driver_iee_apc)
#    include(driver_mu)
#    include(driver_cache_armv7_m7)
#    include(driver_tempsensor)
#    include(middleware_usb_device_stack_external)
#    include(middleware_lwip_apps_httpssrv)
#    include(driver_flexio_i2s_edma)
