list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/IS42SM16800H
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ssd1963
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video/display/dbi/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdramc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysmpu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_driver_dspi	driver_dspi)
include_ifdef(CONFIG_USE_driver_vref	driver_vref)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_bm	middleware_sdmmc_osa_bm)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_dac	driver_dac)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_middleware_mmcau_cm4_cm7	middleware_mmcau_cm4_cm7)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_driver_sdramc	driver_sdramc)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_sdhc_interrupt	middleware_sdmmc_host_sdhc_interrupt)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_driver_flexio_uart_edma	driver_flexio_uart_edma)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm4	CMSIS_Include_core_cm4)
include_ifdef(CONFIG_USE_driver_rtc	driver_rtc)
include_ifdef(CONFIG_USE_driver_IS42SM16800H	driver_IS42SM16800H)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_pit	driver_pit)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_llwu	driver_llwu)
include_ifdef(CONFIG_USE_CMSIS_Include_dsp	CMSIS_Include_dsp)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lptmr	driver_lptmr)
include_ifdef(CONFIG_USE_driver_i2c_edma	driver_i2c_edma)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_dspi_freertos	driver_dspi_freertos)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_sdhc	middleware_sdmmc_host_sdhc)
include_ifdef(CONFIG_USE_driver_ssd1963	driver_ssd1963)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_ftm	driver_ftm)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_sdhc_freertos	middleware_sdmmc_host_sdhc_freertos)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_freertos	middleware_sdmmc_osa_freertos)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_ft5406	driver_ft5406)
include_ifdef(CONFIG_USE_component_osa_bm	component_osa_bm)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_smc	driver_smc)
include_ifdef(CONFIG_USE_component_osa_free_rtos	component_osa_free_rtos)
include_ifdef(CONFIG_USE_middleware_sdmmc_sd	middleware_sdmmc_sd)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_rcm	driver_rcm)
include_ifdef(CONFIG_USE_driver_flexio_mculcd	driver_flexio_mculcd)
include_ifdef(CONFIG_USE_driver_qspi	driver_qspi)
include_ifdef(CONFIG_USE_driver_port	driver_port)
include_ifdef(CONFIG_USE_driver_gpio	driver_gpio)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_driver_pdb	driver_pdb)
include_ifdef(CONFIG_USE_driver_adc16	driver_adc16)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_driver_dbi_flexio_edma	driver_dbi_flexio_edma)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_dbi	driver_dbi)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_flash	driver_flash)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_crc	driver_crc)
include_ifdef(CONFIG_USE_driver_flexio_mculcd_edma	driver_flexio_mculcd_edma)
include_ifdef(CONFIG_USE_driver_pmc	driver_pmc)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_sdhc_polling	middleware_sdmmc_host_sdhc_polling)
include_ifdef(CONFIG_USE_driver_flexio_spi_edma	driver_flexio_spi_edma)
include_ifdef(CONFIG_USE_driver_i2c	driver_i2c)
include_ifdef(CONFIG_USE_driver_i2c_freertos	driver_i2c_freertos)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_middleware_sdmmc_common	middleware_sdmmc_common)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_driver_cmp	driver_cmp)
include_ifdef(CONFIG_USE_driver_edma	driver_edma)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_driver_wdog	driver_wdog)
include_ifdef(CONFIG_USE_utility_notifier	utility_notifier)
include_ifdef(CONFIG_USE_driver_sim	driver_sim)
include_ifdef(CONFIG_USE_driver_qspi_edma	driver_qspi_edma)
include_ifdef(CONFIG_USE_CMSIS_Include_common	CMSIS_Include_common)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MK28FA15	middleware_freertos-kernel_MK28FA15)
include_ifdef(CONFIG_USE_driver_fxos8700cq	driver_fxos8700cq)
include_ifdef(CONFIG_USE_driver_trng	driver_trng)
include_ifdef(CONFIG_USE_driver_sdhc	driver_sdhc)
include_ifdef(CONFIG_USE_driver_sysmpu	driver_sysmpu)
include_ifdef(CONFIG_USE_driver_dspi_edma	driver_dspi_edma)
