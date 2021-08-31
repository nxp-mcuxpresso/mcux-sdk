list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42888
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/cs42888
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyar8031
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/max9286
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/ov5640
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/device/sccb
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/camera/receiver/isi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/adv7535
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/it6263
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/mipi_dsi_cmd
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/rm67191
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/asmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ci_pi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dma3
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dpr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dpu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dpu_irqsteer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/esai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/intmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irqsteer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/isi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ldb_combo_phy
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_csi2rx
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/prg
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rgpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tstmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/scfw_api
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_driver_camera-device-ov5640	driver_camera-device-ov5640)
include_ifdef(CONFIG_USE_driver_sema42	driver_sema42)
include_ifdef(CONFIG_USE_driver_wdog32	driver_wdog32)
include_ifdef(CONFIG_USE_driver_phy-common	driver_phy-common)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_driver_dpu_irqsteer	driver_dpu_irqsteer)
include_ifdef(CONFIG_USE_driver_mdio-enet	driver_mdio-enet)
include_ifdef(CONFIG_USE_driver_wm8960	driver_wm8960)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_driver_phy-device-ar8031	driver_phy-device-ar8031)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_driver_display-common	driver_display-common)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_driver_srtm_freertos	driver_srtm_freertos)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8qx_m4_freertos	middleware_multicore_rpmsg_lite_imx8qx_m4_freertos)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm4	CMSIS_Include_core_cm4)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMX8QX6	component_codec_i2c_MIMX8QX6)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_esai_edma	driver_esai_edma)
include_ifdef(CONFIG_USE_driver_enet	driver_enet)
include_ifdef(CONFIG_USE_CMSIS_Include_dsp	CMSIS_Include_dsp)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lpi2c_edma	driver_lpi2c_edma)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_component_cs42888_adapter	component_cs42888_adapter)
include_ifdef(CONFIG_USE_driver_gpt	driver_gpt)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_driver_prg	driver_prg)
include_ifdef(CONFIG_USE_middleware_mmcau_cm4_cm7	middleware_mmcau_cm4_cm7)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_ftm	driver_ftm)
include_ifdef(CONFIG_USE_driver_ldb_combo_phy	driver_ldb_combo_phy)
include_ifdef(CONFIG_USE_driver_camera-receiver-common	driver_camera-receiver-common)
include_ifdef(CONFIG_USE_driver_flexcan_edma	driver_flexcan_edma)
include_ifdef(CONFIG_USE_driver_display-mipi-dsi-cmd	driver_display-mipi-dsi-cmd)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_tstmr	driver_tstmr)
include_ifdef(CONFIG_USE_driver_camera-device-sccb	driver_camera-device-sccb)
include_ifdef(CONFIG_USE_driver_scfw_api	driver_scfw_api)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_camera-common	driver_camera-common)
include_ifdef(CONFIG_USE_driver_camera-device-common	driver_camera-device-common)
include_ifdef(CONFIG_USE_component_lpi2c_adapter	component_lpi2c_adapter)
include_ifdef(CONFIG_USE_driver_dpu	driver_dpu)
include_ifdef(CONFIG_USE_driver_video-common	driver_video-common)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_dpr	driver_dpr)
include_ifdef(CONFIG_USE_driver_mipi_dsi	driver_mipi_dsi)
include_ifdef(CONFIG_USE_driver_isi	driver_isi)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_rgpio	driver_rgpio)
include_ifdef(CONFIG_USE_driver_mdio-common	driver_mdio-common)
include_ifdef(CONFIG_USE_driver_camera-device-max9286	driver_camera-device-max9286)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMX8QX6	middleware_freertos-kernel_MIMX8QX6)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_srtm_MIMX8QX6	driver_srtm_MIMX8QX6)
include_ifdef(CONFIG_USE_driver_flexcan	driver_flexcan)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_display-adv7535	driver_display-adv7535)
include_ifdef(CONFIG_USE_driver_camera-receiver-isi	driver_camera-receiver-isi)
include_ifdef(CONFIG_USE_component_wm8960_adapter	component_wm8960_adapter)
include_ifdef(CONFIG_USE_driver_cs42888	driver_cs42888)
include_ifdef(CONFIG_USE_driver_irqsteer	driver_irqsteer)
include_ifdef(CONFIG_USE_driver_esai	driver_esai)
include_ifdef(CONFIG_USE_driver_display-rm67191	driver_display-rm67191)
include_ifdef(CONFIG_USE_driver_flexspi	driver_flexspi)
include_ifdef(CONFIG_USE_driver_display-it6263	driver_display-it6263)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_driver_ci_pi	driver_ci_pi)
include_ifdef(CONFIG_USE_driver_sai_edma	driver_sai_edma)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_video-i2c	driver_video-i2c)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_driver_lpit	driver_lpit)
include_ifdef(CONFIG_USE_driver_memory	driver_memory)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_dma3	driver_dma3)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_CMSIS_Include_common	CMSIS_Include_common)
include_ifdef(CONFIG_USE_driver_asmc	driver_asmc)
include_ifdef(CONFIG_USE_driver_igpio	driver_igpio)
include_ifdef(CONFIG_USE_driver_mipi_csi2rx	driver_mipi_csi2rx)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
include_ifdef(CONFIG_USE_driver_intmux	driver_intmux)
