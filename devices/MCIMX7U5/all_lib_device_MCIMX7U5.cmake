list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/pf1550
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ltc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/msmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc0
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tstmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_llwu)
#    include(middleware_issdk_algorithms_pedometer_common)
#    include(driver_pmc0)
#    include(driver_ltc)
#    include(driver_flexio_spi_edma)
#    include(CMSIS_Include_dsp)
#    include(component_lpuart_adapter)
#    include(component_codec_i2c_MCIMX7U5)
#    include(driver_port)
#    include(driver_dmamux)
#    include(driver_lpspi)
#    include(driver_lpi2c_edma)
#    include(driver_gpio)
#    include(component_lists)
#    include(driver_snvs_hp)
#    include(driver_snvs_lp)
#    include(driver_lpit)
#    include(driver_pf1550)
#    include(utilities_misc_utilities)
#    include(driver_acmp)
#    include(device_startup)
#    include(driver_clock)
#    include(CMSIS_Driver_Include_SPI)
#    include(utility_debug_console_lite)
#    include(driver_flexio_uart)
#    include(driver_edma)
#    include(driver_ewm)
#    include(driver_trng)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(driver_lpadc)
#    include(driver_flexio)
#    include(utility_shell)
#    include(driver_trgmux)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_wm8960)
#    include(driver_dac12)
#    include(utility_assert_lite)
#    include(driver_cache_lmem)
#    include(utility_debug_console)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_lpi2c)
#    include(driver_wdog32)
#    include(driver_xrdc)
#    include(driver_lpspi_edma)
#    include(middleware_issdk_sensor_allregdefs)
#    include(driver_lpuart_edma)
#    include(device_CMSIS)
#    include(driver_sema42)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_tstmr)
#    include(driver_codec)
#    include(driver_qspi_edma)
#    include(CMSIS_Include_core_cm4)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_msmc)
#    include(driver_crc)
#    include(driver_flexio_uart_edma)
#    include(driver_srtm)
#    include(middleware_issdk_algorithms_pedometer_lib_cm4)
#    include(component_wm8960_adapter)
#    include(component_serial_manager)
#    include(middleware_mmcau_common_files)
#    include(driver_tpm)
#    include(driver_fxos8700cq)
#    include(driver_lptmr)
#    include(component_lpi2c_adapter)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_sai_edma)
#    include(driver_flexio_i2c_master)
#    include(driver_mu)
#    include(driver_srtm_freertos)
#    include(driver_ltc_edma)
#    include(driver_qspi)
