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
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1160
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406_rt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/caam
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbarb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xecc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc2
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite/third_party/cmsis
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm4
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
#    include(middleware_multicore_rpmsg_lite_imxrt1160_bm)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(component_lpi2c_adapter)
#    include(driver_smartcard_emvsim)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(middleware_usb_host_hid)
#    include(driver_camera-device-common)
#    include(driver_gpt)
#    include(driver_lpi2c_edma)
#    include(driver_kpp)
#    include(CMSIS_DSP_Source)
#    include(middleware_sdmmc_host_usdhc)
#    include(component_wm8960_adapter)
#    include(driver_flexspi_edma)
#    include(driver_dmamux)
#    include(middleware_lwip_apps_mdns_MIMXRT1166_cm4)
#    include(driver_ft5406_rt)
#    include(component_codec_i2c_MIMXRT1166_cm4)
#    include(driver_pmu_1)
#    include(driver_lpuart)
#    include(driver_lpadc)
#    include(driver_pit)
#    include(middleware_freertos-kernel_heap_3)
#    include(middleware_mmcau_common_files)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(middleware_multicore_mcmgr_imxrt1160)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1166_cm4)
#    include(driver_clock)
#    include(middleware_multicore_erpc_eRPC_mu_transport)
#    include(driver_lpuart_edma)
#    include(middleware_fatfs_sd)
#    include(driver_flexio_i2c_master)
#    include(driver_display-common)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(middleware_eiq_worker_audio)
#    include(component_lpuart_adapter)
#    include(driver_pdm)
#    include(middleware_mmcau_cm4_cm7)
#    include(middleware_usb_device_stack_external)
#    include(driver_acmp)
#    include(driver_caam)
#    include(driver_iee_apc)
#    include(middleware_lwip_MIMXRT1166_cm4)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(driver_lpspi)
#    include(driver_xecc)
#    include(middleware_lwip_apps_lwiperf_MIMXRT1166_cm4)
#    include(driver_iomuxc)
#    include(middleware_mbedtls_MIMXRT1166_cm4)
#    include(driver_dc-fb-lcdifv2)
#    include(driver_common)
#    include(driver_pdm_edma)
#    include(driver_flexcan)
#    include(component_mflash_common)
#    include(driver_tempsensor)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_mipi_dsi_split)
#    include(middleware_freertos-kernel_extension)
#    include(driver_pxp)
#    include(driver_anatop_ai)
#    include(component_osa_free_rtos_MIMXRT1166_cm4)
#    include(driver_elcdif)
#    include(driver_smartcard_phy_emvsim)
#    include(middleware_lwip_contrib_ping)
#    include(driver_cmsis_enet)
#    include(component_serial_manager_uart)
#    include(driver_mipi_csi2rx)
#    include(driver_pwm)
#    include(driver_rdc_sema42)
#    include(driver_flexio_i2s)
#    include(component_silicon_id_rt1170)
#    include(driver_xbarb)
#    include(driver_aoi)
#    include(driver_csi)
#    include(middleware_multicore_erpc_eRPC_mu_rtos_transport)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_multicore_erpc_common)
#    include(device_startup_MIMXRT1166_cm4)
#    include(driver_phy-device-ksz8081)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_phy-common_MIMXRT1166_cm4)
#    include(driver_cache_lmem)
#    include(driver_snvs_hp)
#    include(driver_camera-common)
#    include(device_CMSIS)
#    include(driver_xip_device)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(driver_soc_mipi_csi2rx)
#    include(driver_dac12)
#    include(middleware_usb_host_common_header)
#    include(driver_phy-device-rtl8211f)
#    include(middleware_multicore_erpc_doc)
#    include(device_system_MIMXRT1166_cm4)
#    include(middleware_sdmmc_common)
#    include(middleware_usb_device_ehci_MIMXRT1166_cm4)
#    include(middleware_lwip_apps_httpsrv_MIMXRT1166_cm4)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(driver_camera-device-ov5640)
#    include(middleware_lwip_apps_httpd_support)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_mbedtls_rt2)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(middleware_sdmmc_sd)
#    include(driver_cmsis_lpspi)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1166_cm4)
#    include(middleware_usb_host_ehci_MIMXRT1166_cm4)
#    include(driver_display-mipi-dsi-cmd)
#    include(driver_dc-fb-elcdif)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_enc)
#    include(driver_lcdifv2)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_gpc_3)
#    include(component_lists)
#    include(driver_xip_board_evkmimxrt1160)
#    include(driver_qtmr_1)
#    include(middleware_multicore_erpc_eRPC_mu_c_wrapper)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_wm8960)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm4)
#    include(middleware_freertos-kernel_MIMXRT1166_cm4)
#    include(component_silicon_id_MIMXRT1166_cm4)
#    include(middleware_fatfs_MIMXRT1166_cm4)
#    include(middleware_usb_phy)
#    include(component_igpio_adapter)
#    include(driver_edma_MIMXRT1166_cm4)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(driver_flexspi)
#    include(driver_flexio_uart)
#    include(driver_camera-device-sccb)
#    include(driver_usdhc)
#    include(driver_lpuart_freertos)
#    include(driver_fbdev)
#    include(driver_pgmc)
#    include(driver_adc_etc)
#    include(driver_ewm)
#    include(driver_memory)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(middleware_multicore_rpmsg_lite_MIMXRT1166_cm4)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(driver_ssarc)
#    include(driver_key_manager)
#    include(CMSIS_Include_core_cm)
#    include(driver_dcdc_soc)
#    include(driver_enet)
#    include(driver_display-rm68200)
#    include(driver_camera-receiver-common)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(middleware_lwip_apps_httpssrv_MIMXRT1166_cm4)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(driver_sema4)
#    include(driver_soc_src)
#    include(driver_display-rm68191)
#    include(driver_lpspi_edma)
#    include(middleware_lwip_apps_mqtt)
#    include(driver_camera-receiver-csi)
#    include(middleware_multicore_rpmsg_lite_bm)
#    include(driver_snvs_lp)
#    include(middleware_baremetal)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(utility_debug_console_lite)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(driver_dcic)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_gt911)
#    include(middleware_usb_host_stack_MIMXRT1166_cm4)
#    include(driver_sai_edma)
#    include(driver_semc)
#    include(utility_assert_lite)
#    include(middleware_multicore_rpmsg_lite_imxrt1160_freertos)
#    include(driver_iee)
#    include(driver_flexio_i2s_edma)
#    include(component_mflash_rt1160)
#    include(driver_romapi)
#    include(driver_xrdc2)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1166_cm4)
#    include(driver_spdif)
#    include(driver_spdif_edma)
#    include(middleware_multicore_mcmgr)
#    include(driver_igpio)
#    include(driver_sai)
#    include(driver_flexio_uart_edma)
#    include(driver_xbara)
#    include(driver_flexio)
#    include(driver_display-hx8394)
#    include(driver_video-common)
#    include(driver_flexio_spi)
#    include(utilities_misc_utilities_MIMXRT1166_cm4)
#    include(middleware_usb_common_header)
#    include(middleware_usb_device_controller_driver_MIMXRT1166_cm4)
#    include(driver_puf)
#    include(component_serial_manager)
#    include(driver_rdc)
#    include(middleware_littlefs)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_lpi2c)
