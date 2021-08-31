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
include_ifdef(CONFIG_USE_driver_caam	driver_caam)
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMXRT1166_cm4	component_codec_i2c_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_driver_rdc	driver_rdc)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imxrt1160_bm	middleware_multicore_rpmsg_lite_imxrt1160_bm)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_phy-common	driver_phy-common)
include_ifdef(CONFIG_USE_middleware_sdmmc_sd	middleware_sdmmc_sd)
include_ifdef(CONFIG_USE_driver_snvs_lp	driver_snvs_lp)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_polling_MIMXRT1166_cm4	middleware_sdmmc_host_usdhc_polling_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_driver_dc-fb-common	driver_dc-fb-common)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_driver_soc_mipi_csi2rx	driver_soc_mipi_csi2rx)
include_ifdef(CONFIG_USE_driver_mdio-enet	driver_mdio-enet)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_driver_wm8960	driver_wm8960)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_driver_display-rm68200	driver_display-rm68200)
include_ifdef(CONFIG_USE_driver_camera-device-ov5640	driver_camera-device-ov5640)
include_ifdef(CONFIG_USE_driver_aoi	driver_aoi)
include_ifdef(CONFIG_USE_driver_enc	driver_enc)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_driver_display-common	driver_display-common)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_bm	middleware_sdmmc_osa_bm)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_driver_lpspi_edma	driver_lpspi_edma)
include_ifdef(CONFIG_USE_driver_flexio_uart_edma	driver_flexio_uart_edma)
include_ifdef(CONFIG_USE_driver_ocotp	driver_ocotp)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_pxp	driver_pxp)
include_ifdef(CONFIG_USE_driver_xip_device	driver_xip_device)
include_ifdef(CONFIG_USE_driver_mipi_dsi_split	driver_mipi_dsi_split)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_driver_lcdifv2	driver_lcdifv2)
include_ifdef(CONFIG_USE_driver_pit	driver_pit)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr_imxrt1160	middleware_multicore_mcmgr_imxrt1160)
include_ifdef(CONFIG_USE_driver_soc_src	driver_soc_src)
include_ifdef(CONFIG_USE_CMSIS_DSP_Library	CMSIS_DSP_Library)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_display-rm68191	driver_display-rm68191)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm4	middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_driver_phy-device-ksz8081	driver_phy-device-ksz8081)
include_ifdef(CONFIG_USE_driver_usdhc	driver_usdhc)
include_ifdef(CONFIG_USE_driver_gpt	driver_gpt)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_driver_enet	driver_enet)
include_ifdef(CONFIG_USE_middleware_mmcau_cm4_cm7	middleware_mmcau_cm4_cm7)
include_ifdef(CONFIG_USE_device_system_MIMXRT1166_cm4	device_system_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_camera-receiver-common	driver_camera-receiver-common)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMXRT1166_cm4	middleware_freertos-kernel_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_freertos	middleware_sdmmc_osa_freertos)
include_ifdef(CONFIG_USE_driver_rdc_sema42	driver_rdc_sema42)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
include_ifdef(CONFIG_USE_driver_display-mipi-dsi-cmd	driver_display-mipi-dsi-cmd)
include_ifdef(CONFIG_USE_driver_anatop_ai	driver_anatop_ai)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_romapi	driver_romapi)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_doc	middleware_multicore_erpc_doc)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_common	middleware_multicore_erpc_common)
include_ifdef(CONFIG_USE_component_osa_bm	component_osa_bm)
include_ifdef(CONFIG_USE_driver_camera-device-sccb	driver_camera-device-sccb)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_kpp	driver_kpp)
include_ifdef(CONFIG_USE_component_osa_free_rtos	component_osa_free_rtos)
include_ifdef(CONFIG_USE_driver_camera-common	driver_camera-common)
include_ifdef(CONFIG_USE_driver_camera-device-common	driver_camera-device-common)
include_ifdef(CONFIG_USE_component_lpi2c_adapter	component_lpi2c_adapter)
include_ifdef(CONFIG_USE_driver_key_manager	driver_key_manager)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_driver_video-common	driver_video-common)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_MIMXRT1166_cm4	middleware_sdmmc_host_usdhc_interrupt_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_driver_snvs_hp	driver_snvs_hp)
include_ifdef(CONFIG_USE_driver_pdm	driver_pdm)
include_ifdef(CONFIG_USE_driver_lpspi	driver_lpspi)
include_ifdef(CONFIG_USE_driver_flexspi_edma	driver_flexspi_edma)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imxrt1160_freertos	middleware_multicore_rpmsg_lite_imxrt1160_freertos)
include_ifdef(CONFIG_USE_driver_csi	driver_csi)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_c_wrapper	middleware_multicore_erpc_eRPC_mu_c_wrapper)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_server	middleware_multicore_erpc_eRPC_server)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_adc_etc	driver_adc_etc)
include_ifdef(CONFIG_USE_driver_mdio-common	driver_mdio-common)
include_ifdef(CONFIG_USE_driver_pgmc	driver_pgmc)
include_ifdef(CONFIG_USE_driver_iomuxc	driver_iomuxc)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_semc	driver_semc)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_driver_xbarb	driver_xbarb)
include_ifdef(CONFIG_USE_driver_xbara	driver_xbara)
include_ifdef(CONFIG_USE_driver_spdif	driver_spdif)
include_ifdef(CONFIG_USE_driver_flexcan	driver_flexcan)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_pmu_1	driver_pmu_1)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr	middleware_multicore_mcmgr)
include_ifdef(CONFIG_USE_driver_smartcard_emvsim	driver_smartcard_emvsim)
include_ifdef(CONFIG_USE_driver_sema4	driver_sema4)
include_ifdef(CONFIG_USE_driver_spdif_edma	driver_spdif_edma)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc	middleware_sdmmc_host_usdhc)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_stdlib	middleware_multicore_erpc_eRPC_port_stdlib)
include_ifdef(CONFIG_USE_driver_camera-receiver-csi	driver_camera-receiver-csi)
include_ifdef(CONFIG_USE_component_wm8960_adapter	component_wm8960_adapter)
include_ifdef(CONFIG_USE_driver_puf	driver_puf)
include_ifdef(CONFIG_USE_driver_dcic	driver_dcic)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_arbitrator	middleware_multicore_erpc_eRPC_arbitrator)
include_ifdef(CONFIG_USE_driver_dcdc_soc	driver_dcdc_soc)
include_ifdef(CONFIG_USE_driver_dc-fb-elcdif	driver_dc-fb-elcdif)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_freertos	middleware_multicore_erpc_eRPC_port_freertos)
include_ifdef(CONFIG_USE_driver_xecc	driver_xecc)
include_ifdef(CONFIG_USE_driver_iee	driver_iee)
include_ifdef(CONFIG_USE_driver_phy-device-rtl8211f	driver_phy-device-rtl8211f)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_transport	middleware_multicore_erpc_eRPC_mu_transport)
include_ifdef(CONFIG_USE_driver_flexspi	driver_flexspi)
include_ifdef(CONFIG_USE_driver_flexio_spi_edma	driver_flexio_spi_edma)
include_ifdef(CONFIG_USE_device_startup_MIMXRT1166_cm4	device_startup_MIMXRT1166_cm4)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_driver_qtmr_1	driver_qtmr_1)
include_ifdef(CONFIG_USE_driver_gpc_3	driver_gpc_3)
include_ifdef(CONFIG_USE_driver_sai_edma	driver_sai_edma)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_middleware_sdmmc_common	middleware_sdmmc_common)
include_ifdef(CONFIG_USE_driver_smartcard_phy_emvsim	driver_smartcard_phy_emvsim)
include_ifdef(CONFIG_USE_driver_acmp	driver_acmp)
include_ifdef(CONFIG_USE_driver_dc-fb-lcdifv2	driver_dc-fb-lcdifv2)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
include_ifdef(CONFIG_USE_component_osa	component_osa)
include_ifdef(CONFIG_USE_driver_edma	driver_edma)
include_ifdef(CONFIG_USE_driver_memory	driver_memory)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_rtos_transport	middleware_multicore_erpc_eRPC_mu_rtos_transport)
include_ifdef(CONFIG_USE_driver_dac12	driver_dac12)
include_ifdef(CONFIG_USE_driver_xrdc2	driver_xrdc2)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_driver_ssarc	driver_ssarc)
include_ifdef(CONFIG_USE_driver_flexio_i2s	driver_flexio_i2s)
include_ifdef(CONFIG_USE_driver_fxos8700cq	driver_fxos8700cq)
include_ifdef(CONFIG_USE_driver_elcdif	driver_elcdif)
include_ifdef(CONFIG_USE_driver_xip_board	driver_xip_board)
include_ifdef(CONFIG_USE_driver_igpio	driver_igpio)
include_ifdef(CONFIG_USE_driver_pwm	driver_pwm)
include_ifdef(CONFIG_USE_driver_mipi_csi2rx	driver_mipi_csi2rx)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_driver_pdm_edma	driver_pdm_edma)
include_ifdef(CONFIG_USE_driver_iee_apc	driver_iee_apc)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
include_ifdef(CONFIG_USE_driver_tempsensor	driver_tempsensor)
include_ifdef(CONFIG_USE_driver_flexio_i2s_edma	driver_flexio_i2s_edma)
