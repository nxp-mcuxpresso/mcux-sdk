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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/scfw_api
)


# Copy the cmake components into projects
#    include(middleware_multicore_rpmsg_lite_imx8qm_m4_freertos)
#    include(driver_phy-device-ar8031)
#    include(driver_codec)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_dsp)
#    include(driver_tstmr)
#    include(driver_dma3)
#    include(driver_sc_event)
#    include(driver_lpspi_edma)
#    include(middleware_freertos-kernel_MIMX8QM6_cm4_core0)
#    include(driver_scfw_api)
#    include(utility_assert)
#    include(component_lpi2c_adapter)
#    include(driver_mdio-common)
#    include(driver_mu)
#    include(driver_gpt)
#    include(driver_lpi2c_edma)
#    include(driver_lpspi_freertos)
#    include(component_codec_i2c_MIMX8QM6_cm4_core0)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_lpi2c)
#    include(utility_debug_console_lite)
#    include(driver_mdio-enet)
#    include(component_wm8960_adapter)
#    include(utility_debug_console)
#    include(driver_enet)
#    include(driver_wm8960)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_sai_edma)
#    include(driver_cs42888)
#    include(driver_flexcan_edma)
#    include(driver_lpuart)
#    include(driver_lpadc)
#    include(utility_assert_lite)
#    include(utilities_misc_utilities_MIMX8QM6_cm4_core0)
#    include(driver_sema42)
#    include(driver_tpm)
#    include(middleware_mmcau_common_files)
#    include(middleware_multicore_rpmsg_lite_MIMX8QM6_cm4_core0)
#    include(driver_flexspi)
#    include(driver_clock)
#    include(driver_phy-common_MIMX8QM6_cm4_core0)
#    include(driver_lpuart_edma)
#    include(driver_cache_lmem)
#    include(driver_wdog32)
#    include(device_CMSIS)
#    include(component_lpuart_adapter)
#    include(driver_flexcan)
#    include(middleware_mmcau_cm4_cm7)
#    include(CMSIS_Include_common)
#    include(driver_lpuart_freertos)
#    include(driver_igpio)
#    include(driver_sai)
#    include(component_cs42888_adapter)
#    include(driver_irqsteer)
#    include(CMSIS_Include_core_cm4)
#    include(device_startup_MIMX8QM6_cm4_core0)
#    include(driver_asmc)
#    include(driver_esai_edma)
#    include(driver_lpi2c_freertos)
#    include(driver_lpspi)
#    include(driver_memory)
#    include(driver_common)
#    include(driver_ftm)
#    include(driver_rgpio)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_esai)
#    include(driver_intmux)
