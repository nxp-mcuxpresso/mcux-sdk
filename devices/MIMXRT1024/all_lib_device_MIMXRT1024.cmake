list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1024/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_12b1msps_sar
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/bee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv7-m7
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcdc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024	middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_bm	middleware_sdmmc_osa_bm)
include_ifdef(CONFIG_USE_middleware_sdmmc_mmc	middleware_sdmmc_mmc)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_phy-common	driver_phy-common)
include_ifdef(CONFIG_USE_middleware_sdmmc_sd	middleware_sdmmc_sd)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_driver_snvs_lp	driver_snvs_lp)
include_ifdef(CONFIG_USE_driver_mdio-enet	driver_mdio-enet)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_driver_wm8960	driver_wm8960)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMXRT1024	component_codec_i2c_MIMXRT1024)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_driver_aoi	driver_aoi)
include_ifdef(CONFIG_USE_driver_bee	driver_bee)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_driver_lpspi_edma	driver_lpspi_edma)
include_ifdef(CONFIG_USE_driver_wdog01	driver_wdog01)
include_ifdef(CONFIG_USE_driver_flexio_uart_edma	driver_flexio_uart_edma)
include_ifdef(CONFIG_USE_driver_ocotp	driver_ocotp)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_xip_device	driver_xip_device)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_pit	driver_pit)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMXRT1024	middleware_freertos-kernel_MIMXRT1024)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_lpspi_freertos	driver_lpspi_freertos)
include_ifdef(CONFIG_USE_CMSIS_DSP_Library	CMSIS_DSP_Library)
include_ifdef(CONFIG_USE_driver_tempmon	driver_tempmon)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_MIMXRT1024	middleware_sdmmc_host_usdhc_freertos_MIMXRT1024)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lpi2c_edma	driver_lpi2c_edma)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_phy-device-ksz8081	driver_phy-device-ksz8081)
include_ifdef(CONFIG_USE_driver_usdhc	driver_usdhc)
include_ifdef(CONFIG_USE_driver_gpt	driver_gpt)
include_ifdef(CONFIG_USE_driver_enet	driver_enet)
include_ifdef(CONFIG_USE_driver_rtwdog	driver_rtwdog)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_freertos	middleware_sdmmc_osa_freertos)
include_ifdef(CONFIG_USE_driver_soc_flexram_allocate	driver_soc_flexram_allocate)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_romapi	driver_romapi)
include_ifdef(CONFIG_USE_component_osa_bm	component_osa_bm)
include_ifdef(CONFIG_USE_driver_adc_12b1msps_sar	driver_adc_12b1msps_sar)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_kpp	driver_kpp)
include_ifdef(CONFIG_USE_component_osa_free_rtos	component_osa_free_rtos)
include_ifdef(CONFIG_USE_driver_adc_etc	driver_adc_etc)
include_ifdef(CONFIG_USE_component_lpi2c_adapter	component_lpi2c_adapter)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_dcdc_1	driver_dcdc_1)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_polling_MIMXRT1024	middleware_sdmmc_host_usdhc_polling_MIMXRT1024)
include_ifdef(CONFIG_USE_driver_snvs_hp	driver_snvs_hp)
include_ifdef(CONFIG_USE_driver_lpspi	driver_lpspi)
include_ifdef(CONFIG_USE_driver_flexspi_edma	driver_flexspi_edma)
include_ifdef(CONFIG_USE_driver_xip_board_evkmimxrt1024	driver_xip_board_evkmimxrt1024)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_mdio-common	driver_mdio-common)
include_ifdef(CONFIG_USE_driver_iomuxc	driver_iomuxc)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_driver_flexram	driver_flexram)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_semc	driver_semc)
include_ifdef(CONFIG_USE_driver_xbarb	driver_xbarb)
include_ifdef(CONFIG_USE_driver_xbara	driver_xbara)
include_ifdef(CONFIG_USE_driver_flexcan	driver_flexcan)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc	middleware_sdmmc_host_usdhc)
include_ifdef(CONFIG_USE_component_wm8960_adapter	component_wm8960_adapter)
include_ifdef(CONFIG_USE_driver_enc	driver_enc)
include_ifdef(CONFIG_USE_driver_gpc_1	driver_gpc_1)
include_ifdef(CONFIG_USE_driver_dcp	driver_dcp)
include_ifdef(CONFIG_USE_driver_flexspi	driver_flexspi)
include_ifdef(CONFIG_USE_driver_flexio_spi_edma	driver_flexio_spi_edma)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_driver_qtmr_1	driver_qtmr_1)
include_ifdef(CONFIG_USE_driver_pwm	driver_pwm)
include_ifdef(CONFIG_USE_driver_sai_edma	driver_sai_edma)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_middleware_sdmmc_common	middleware_sdmmc_common)
include_ifdef(CONFIG_USE_driver_cmp	driver_cmp)
include_ifdef(CONFIG_USE_component_osa	component_osa)
include_ifdef(CONFIG_USE_driver_edma	driver_edma)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_driver_src	driver_src)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_driver_flexio_i2s	driver_flexio_i2s)
include_ifdef(CONFIG_USE_driver_fxos8700cq	driver_fxos8700cq)
include_ifdef(CONFIG_USE_driver_igpio	driver_igpio)
include_ifdef(CONFIG_USE_driver_trng	driver_trng)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_driver_cache_armv7_m7	driver_cache_armv7_m7)
include_ifdef(CONFIG_USE_driver_flexio_i2s_edma	driver_flexio_i2s_edma)
