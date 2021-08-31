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
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/asmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dma3
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/esai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/intmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irqsteer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
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
include_ifdef(CONFIG_USE_driver_phy-device-ar8031	driver_phy-device-ar8031)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMX8QM6_cm4_core0	middleware_freertos-kernel_MIMX8QM6_cm4_core0)
include_ifdef(CONFIG_USE_driver_esai	driver_esai)
include_ifdef(CONFIG_USE_driver_mdio-enet	driver_mdio-enet)
include_ifdef(CONFIG_USE_driver_flexspi	driver_flexspi)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_CMSIS_Include_dsp	CMSIS_Include_dsp)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_driver_wdog32	driver_wdog32)
include_ifdef(CONFIG_USE_driver_lpspi	driver_lpspi)
include_ifdef(CONFIG_USE_driver_lpi2c_edma	driver_lpi2c_edma)
include_ifdef(CONFIG_USE_driver_sai_edma	driver_sai_edma)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_rgpio	driver_rgpio)
include_ifdef(CONFIG_USE_driver_lpit	driver_lpit)
include_ifdef(CONFIG_USE_driver_mdio-common	driver_mdio-common)
include_ifdef(CONFIG_USE_driver_wm8960	driver_wm8960)
include_ifdef(CONFIG_USE_component_cs42888_adapter	component_cs42888_adapter)
include_ifdef(CONFIG_USE_driver_gpt	driver_gpt)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_driver_enet	driver_enet)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8qm_m4_freertos	middleware_multicore_rpmsg_lite_imx8qm_m4_freertos)
include_ifdef(CONFIG_USE_middleware_mmcau_cm4_cm7	middleware_mmcau_cm4_cm7)
include_ifdef(CONFIG_USE_driver_lpspi_freertos	driver_lpspi_freertos)
include_ifdef(CONFIG_USE_driver_phy-common	driver_phy-common)
include_ifdef(CONFIG_USE_driver_ftm	driver_ftm)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_driver_dma3	driver_dma3)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_driver_flexcan_edma	driver_flexcan_edma)
include_ifdef(CONFIG_USE_driver_flexcan	driver_flexcan)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_sema42	driver_sema42)
include_ifdef(CONFIG_USE_driver_lpspi_edma	driver_lpspi_edma)
include_ifdef(CONFIG_USE_driver_sc_event	driver_sc_event)
include_ifdef(CONFIG_USE_driver_tstmr	driver_tstmr)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm4	CMSIS_Include_core_cm4)
include_ifdef(CONFIG_USE_driver_scfw_api	driver_scfw_api)
include_ifdef(CONFIG_USE_CMSIS_Include_common	CMSIS_Include_common)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_asmc	driver_asmc)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_component_wm8960_adapter	component_wm8960_adapter)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_driver_igpio	driver_igpio)
include_ifdef(CONFIG_USE_component_lpi2c_adapter	component_lpi2c_adapter)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_driver_cs42888	driver_cs42888)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_irqsteer	driver_irqsteer)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
include_ifdef(CONFIG_USE_driver_intmux	driver_intmux)
include_ifdef(CONFIG_USE_device_startup_MIMX8QM6_cm4_core0	device_startup_MIMX8QM6_cm4_core0)
include_ifdef(CONFIG_USE_driver_memory	driver_memory)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMX8QM6_cm4_core0	component_codec_i2c_MIMX8QM6_cm4_core0)
include_ifdef(CONFIG_USE_driver_esai_edma	driver_esai_edma)
