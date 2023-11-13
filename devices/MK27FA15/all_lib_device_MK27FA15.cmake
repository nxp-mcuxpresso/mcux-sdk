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
#    include(driver_dspi)
#    include(driver_vref)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_dmamux)
#    include(driver_dac)
#    include(device_system)
#    include(driver_lpuart_freertos)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_flexio_uart)
#    include(driver_ewm)
#    include(driver_sdramc)
#    include(middleware_mmcau_common_files)
#    include(middleware_sdmmc_host_sdhc_interrupt)
#    include(driver_flexio)
#    include(driver_cache_lmem)
#    include(driver_lpuart_edma)
#    include(driver_flexio_uart_edma)
#    include(CMSIS_Include_core_cm4 OPTIONAL)
#    include(driver_port)
#    include(driver_rtc)
#    include(driver_IS42SM16800H)
#    include(component_serial_manager)
#    include(driver_pit)
#    include(component_serial_manager_uart)
#    include(driver_llwu)
#    include(CMSIS_Include_dsp OPTIONAL)
#    include(component_lpuart_adapter)
#    include(driver_lptmr)
#    include(driver_i2c_edma)
#    include(device_startup)
#    include(driver_dspi_freertos)
#    include(middleware_sdmmc_host_sdhc)
#    include(driver_ssd1963)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(middleware_sdmmc_host_sdhc_freertos)
#    include(middleware_sdmmc_osa_freertos)
#    include(utility_assert)
#    include(device_CMSIS)
#    include(driver_ft5406)
#    include(component_osa_bm)
#    include(driver_common)
#    include(driver_smc)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(driver_flexio_mculcd)
#    include(driver_qspi)
#    include(utilities_misc_utilities_MK28FA15)
#    include(driver_gpio)
#    include(driver_flexio_i2c_master)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(driver_clock)
#    include(driver_dbi_flexio_edma)
#    include(utility_debug_console_lite)
#    include(driver_dbi)
#    include(utility_shell)
#    include(utility_assert_lite)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(driver_crc)
#    include(driver_flexio_mculcd_edma)
#    include(driver_pmc)
#    include(middleware_sdmmc_host_sdhc_polling)
#    include(driver_flexio_spi_edma)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_tpm)
#    include(driver_cmp)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(driver_wdog)
#    include(utility_notifier)
#    include(driver_sim)
#    include(driver_qspi_edma)
#    include(CMSIS_Include_common OPTIONAL)
#    include(middleware_freertos-kernel_MK28FA15)
#    include(driver_edma_MK28FA15)
#    include(driver_trng)
#    include(driver_sdhc)
#    include(driver_sysmpu)
#    include(driver_dspi_edma)
