list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_lpuart_freertos)
#    include(driver_pmc0)
#    include(driver_sema42)
#    include(driver_dmamux)
#    include(driver_snvs_lp)
#    include(driver_lpadc)
#    include(driver_flexio_uart)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_mmcau_common_files)
#    include(driver_flexio)
#    include(driver_msmc)
#    include(driver_crc)
#    include(driver_cache_lmem)
#    include(driver_lpuart_edma)
#    include(middleware_mmcau_cm4_cm7)
#    include(driver_flexio_uart_edma)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_wdog32)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(driver_llwu)
#    include(middleware_freertos-kernel_MCIMX7U5)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_transport)
#    include(device_startup)
#    include(driver_pf1550)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Driver_Include_I2C)
#    include(utility_assert)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common)
#    include(middleware_multicore_erpc_doc)
#    include(driver_tstmr)
#    include(middleware_multicore_erpc_common)
#    include(driver_common)
#    include(component_lpi2c_adapter)
#    include(CMSIS_Include_core_cm)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_qspi)
#    include(driver_ltc)
#    include(driver_trgmux)
#    include(driver_snvs_hp)
#    include(driver_port)
#    include(driver_lpspi)
#    include(driver_gpio)
#    include(middleware_issdk_sensor_allregdefs)
#    include(driver_flexio_i2c_master)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(driver_clock)
#    include(CMSIS_Driver_Include_SPI)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_remote_c_wrapper)
#    include(utility_shell)
#    include(utility_assert_lite)
#    include(utility_debug_console)
#    include(driver_lpi2c_freertos)
#    include(middleware_multicore_rpmsg_lite_imx7ulp_m4_freertos)
#    include(component_wm8960_adapter)
#    include(driver_lptmr)
#    include(middleware_issdk_algorithms_pedometer_lib_cm4)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_flexio_spi_edma)
#    include(component_codec_i2c_MCIMX7U5)
#    include(driver_sai_edma)
#    include(component_lists)
#    include(middleware_issdk_algorithms_pedometer_common)
#    include(driver_tpm)
#    include(driver_acmp)
#    include(driver_lpit)
#    include(driver_edma)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(driver_xrdc)
#    include(driver_srtm_MCIMX7U5)
#    include(driver_dac12)
#    include(driver_lpspi_edma)
#    include(driver_srtm_freertos)
#    include(driver_qspi_edma)
#    include(driver_lpi2c)
#    include(driver_fxos8700cq)
#    include(driver_trng)
#    include(driver_sai)
#    include(driver_mu)
#    include(driver_ltc_edma)
