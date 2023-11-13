list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ldb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/scfw_api
)


# Copy the cmake components into projects
#    include(middleware_freertos-kernel_MIMX8QM6_cm4_core1)
#    include(driver_lpuart_freertos)
#    include(utilities_misc_utilities_MIMX8QM6_cm4_core1)
#    include(driver_camera-device-ov5640)
#    include(driver_sema42)
#    include(driver_wdog32)
#    include(driver_lpadc)
#    include(driver_dpu_irqsteer)
#    include(driver_phy-common_MIMX8QM6_cm4_core1)
#    include(driver_mdio-enet)
#    include(driver_wm8960)
#    include(middleware_mmcau_common_files)
#    include(middleware_freertos-kernel_extension)
#    include(driver_cache_lmem)
#    include(driver_display-common)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_codec)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(driver_esai_edma)
#    include(driver_enet)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(device_startup_MIMX8QM6_cm4_core1)
#    include(component_cs42888_adapter)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_prg)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_phy-device-ar8031)
#    include(driver_ftm)
#    include(driver_camera-receiver-common)
#    include(driver_flexcan_edma)
#    include(driver_display-mipi-dsi-cmd)
#    include(device_CMSIS)
#    include(driver_tstmr)
#    include(driver_sc_event)
#    include(driver_camera-device-sccb)
#    include(driver_scfw_api)
#    include(driver_common)
#    include(middleware_multicore_rpmsg_lite_MIMX8QM6_cm4_core1)
#    include(driver_camera-common)
#    include(driver_camera-device-common)
#    include(component_lpi2c_adapter)
#    include(driver_dpu)
#    include(driver_video-common)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_dpr)
#    include(driver_mipi_dsi)
#    include(driver_isi)
#    include(driver_lpspi)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_rgpio)
#    include(driver_mdio-common)
#    include(driver_camera-device-max9286)
#    include(utility_assert_lite)
#    include(driver_flexcan)
#    include(utility_debug_console)
#    include(driver_ldb)
#    include(driver_camera-receiver-isi)
#    include(component_wm8960_adapter)
#    include(driver_cs42888)
#    include(driver_irqsteer)
#    include(driver_esai)
#    include(driver_display-rm67191)
#    include(driver_flexspi)
#    include(driver_display-it6263)
#    include(driver_lpi2c_freertos)
#    include(driver_sai_edma)
#    include(component_lists)
#    include(driver_video-i2c)
#    include(driver_srtm_MIMX8QM6_cm4_core1)
#    include(driver_tpm)
#    include(driver_lpit)
#    include(driver_memory)
#    include(driver_lpuart)
#    include(middleware_multicore_rpmsg_lite_imx8qm_m4_freertos)
#    include(driver_dma3)
#    include(driver_srtm_freertos)
#    include(driver_lpi2c)
#    include(driver_asmc)
#    include(driver_igpio)
#    include(driver_mipi_csi2rx)
#    include(driver_sai)
#    include(driver_display-adv7535)
#    include(driver_mu)
#    include(driver_intmux)
#    include(component_codec_i2c_MIMX8QM6_cm4_core1)
