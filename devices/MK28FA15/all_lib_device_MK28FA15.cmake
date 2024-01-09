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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_dspi_edma)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(utility_notifier)
#    include(driver_crc)
#    include(driver_adc16)
#    include(driver_llwu)
#    include(driver_pmc)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(driver_ssd1963)
#    include(middleware_mmcau_common_files)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(driver_flexio_i2c_master)
#    include(component_lpuart_adapter)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_dspi)
#    include(driver_IS42SM16800H)
#    include(driver_common)
#    include(driver_flexio_mculcd_edma)
#    include(driver_cmp)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_dsp)
#    include(driver_rcm)
#    include(driver_dac)
#    include(driver_gpio)
#    include(component_serial_manager_uart)
#    include(utilities_misc_utilities_MK28FA15)
#    include(driver_dbi)
#    include(driver_port)
#    include(driver_sdhc)
#    include(driver_smc)
#    include(driver_i2c_edma)
#    include(driver_trng)
#    include(device_startup)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_cache_lmem)
#    include(device_CMSIS)
#    include(CMSIS_Include_common)
#    include(middleware_sdmmc_host_sdhc)
#    include(driver_dbi_flexio_edma)
#    include(middleware_sdmmc_common)
#    include(middleware_sdmmc_host_sdhc_interrupt)
#    include(component_osa_free_rtos_MK28FA15)
#    include(driver_ftm)
#    include(middleware_sdmmc_sd)
#    include(driver_rtc)
#    include(utility_assert)
#    include(driver_sysmpu)
#    include(driver_sdramc)
#    include(component_lists)
#    include(driver_dspi_freertos)
#    include(utility_debug_console)
#    include(middleware_sdmmc_host_sdhc_polling)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_i2c_freertos)
#    include(driver_tpm)
#    include(driver_flexio_uart)
#    include(driver_wdog)
#    include(driver_lpuart_freertos)
#    include(driver_qspi_edma)
#    include(driver_ewm)
#    include(driver_flexio_mculcd)
#    include(middleware_freertos-kernel_MK28FA15)
#    include(driver_sim)
#    include(driver_qspi)
#    include(driver_edma_MK28FA15)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(driver_flexio_spi_edma)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_vref)
#    include(middleware_sdmmc_host_sdhc_freertos)
#    include(device_system)
#    include(utility_assert_lite)
#    include(driver_flexio_uart_edma)
#    include(CMSIS_Include_core_cm4)
#    include(driver_flexio)
#    include(driver_ft5406)
#    include(driver_i2c)
#    include(driver_flexio_spi)
#    include(component_serial_manager)
#    include(driver_fxos8700cq)
