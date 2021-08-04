list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1160/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
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
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm4
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(driver_caam)
#    include(driver_lpuart_freertos)
#    include(component_codec_i2c_MIMXRT1166_cm4)
#    include(driver_rdc)
#    include(middleware_multicore_rpmsg_lite_imxrt1160_bm)
#    include(driver_dmamux)
#    include(driver_phy-common)
#    include(middleware_sdmmc_sd)
#    include(driver_snvs_lp)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1166_cm4)
#    include(driver_dc-fb-common)
#    include(driver_lpadc)
#    include(driver_soc_mipi_csi2rx)
#    include(driver_mdio-enet)
#    include(driver_flexio_uart)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_mmcau_common_files)
#    include(driver_display-rm68200)
#    include(driver_camera-device-ov5640)
#    include(driver_aoi)
#    include(driver_enc)
#    include(driver_cache_lmem)
#    include(middleware_baremetal)
#    include(driver_display-common)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_flexio_uart_edma)
#    include(driver_ocotp)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_pxp)
#    include(driver_xip_device)
#    include(driver_mipi_dsi_split)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(driver_lcdifv2)
#    include(driver_pit)
#    include(component_serial_manager_uart)
#    include(middleware_multicore_mcmgr_imxrt1160)
#    include(driver_soc_src)
#    include(CMSIS_DSP_Library)
#    include(component_lpuart_adapter)
#    include(driver_display-rm68191)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm4)
#    include(driver_phy-device-ksz8081)
#    include(driver_usdhc)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_enet)
#    include(middleware_mmcau_cm4_cm7)
#    include(device_system_MIMXRT1166_cm4)
#    include(middleware_freertos-kernel_extension)
#    include(driver_camera-receiver-common)
#    include(middleware_freertos-kernel_MIMXRT1166_cm4)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_rdc_sema42)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(driver_display-mipi-dsi-cmd)
#    include(driver_anatop_ai)
#    include(device_CMSIS)
#    include(driver_romapi)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(driver_camera-device-sccb)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(driver_common)
#    include(driver_kpp)
#    include(component_osa_free_rtos)
#    include(driver_camera-common)
#    include(driver_camera-device-common)
#    include(component_lpi2c_adapter)
#    include(driver_key_manager)
#    include(CMSIS_Include_core_cm)
#    include(driver_video-common)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1166_cm4)
#    include(driver_snvs_hp)
#    include(driver_pdm)
#    include(driver_lpspi)
#    include(driver_flexspi_edma)
#    include(middleware_multicore_rpmsg_lite_imxrt1160_freertos)
#    include(driver_csi)
#    include(middleware_multicore_erpc_eRPC_mu_c_wrapper)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_adc_etc)
#    include(driver_mdio-common)
#    include(driver_pgmc)
#    include(driver_iomuxc)
#    include(utility_shell)
#    include(utility_assert_lite)
#    include(driver_semc)
#    include(driver_flexio)
#    include(driver_xbarb)
#    include(driver_xbara)
#    include(driver_spdif)
#    include(driver_flexcan)
#    include(utility_debug_console)
#    include(driver_pmu_1)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(middleware_multicore_mcmgr)
#    include(driver_smartcard_emvsim)
#    include(driver_sema4)
#    include(driver_spdif_edma)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(driver_camera-receiver-csi)
#    include(component_wm8960_adapter)
#    include(driver_puf)
#    include(driver_dcic)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_dcdc_soc)
#    include(driver_dc-fb-elcdif)
#    include(driver_flexio_i2c_master)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_xecc)
#    include(driver_iee)
#    include(driver_phy-device-rtl8211f)
#    include(middleware_multicore_erpc_eRPC_mu_transport)
#    include(driver_flexspi)
#    include(driver_flexio_spi_edma)
#    include(device_startup_MIMXRT1166_cm4)
#    include(driver_lpi2c_freertos)
#    include(driver_qtmr_1)
#    include(driver_gpc_3)
#    include(driver_sai_edma)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_smartcard_phy_emvsim)
#    include(driver_acmp)
#    include(driver_dc-fb-lcdifv2)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(component_osa)
#    include(driver_edma)
#    include(driver_memory)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(middleware_multicore_erpc_eRPC_mu_rtos_transport)
#    include(driver_dac12)
#    include(driver_xrdc2)
#    include(driver_lpi2c)
#    include(driver_ssarc)
#    include(driver_flexio_i2s)
#    include(driver_fxos8700cq)
#    include(driver_elcdif)
#    include(driver_xip_board)
#    include(driver_igpio)
#    include(driver_pwm)
#    include(driver_mipi_csi2rx)
#    include(driver_sai)
#    include(driver_pdm_edma)
#    include(driver_iee_apc)
#    include(driver_mu)
#    include(driver_tempsensor)
#    include(driver_flexio_i2s_edma)
