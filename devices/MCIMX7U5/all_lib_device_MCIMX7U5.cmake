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
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_driver_pmc0	driver_pmc0)
include_ifdef(CONFIG_USE_driver_sema42	driver_sema42)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_snvs_lp	driver_snvs_lp)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_driver_wm8960	driver_wm8960)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_driver_msmc	driver_msmc)
include_ifdef(CONFIG_USE_driver_crc	driver_crc)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_middleware_mmcau_cm4_cm7	middleware_mmcau_cm4_cm7)
include_ifdef(CONFIG_USE_driver_flexio_uart_edma	driver_flexio_uart_edma)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_wdog32	driver_wdog32)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_lpspi_freertos	driver_lpspi_freertos)
include_ifdef(CONFIG_USE_driver_llwu	driver_llwu)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MCIMX7U5	middleware_freertos-kernel_MCIMX7U5)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lpi2c_edma	driver_lpi2c_edma)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_transport	middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_transport)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_pf1550	driver_pf1550)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_CMSIS_Driver_Include_I2C	CMSIS_Driver_Include_I2C)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_CMSIS_Driver_Include_Common	CMSIS_Driver_Include_Common)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_doc	middleware_multicore_erpc_doc)
include_ifdef(CONFIG_USE_driver_tstmr	driver_tstmr)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_common	middleware_multicore_erpc_common)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_component_lpi2c_adapter	component_lpi2c_adapter)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_qspi	driver_qspi)
include_ifdef(CONFIG_USE_driver_ltc	driver_ltc)
include_ifdef(CONFIG_USE_driver_trgmux	driver_trgmux)
include_ifdef(CONFIG_USE_driver_snvs_hp	driver_snvs_hp)
include_ifdef(CONFIG_USE_driver_port	driver_port)
include_ifdef(CONFIG_USE_driver_lpspi	driver_lpspi)
include_ifdef(CONFIG_USE_driver_gpio	driver_gpio)
include_ifdef(CONFIG_USE_middleware_issdk_sensor_allregdefs	middleware_issdk_sensor_allregdefs)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_server	middleware_multicore_erpc_eRPC_server)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_CMSIS_Driver_Include_SPI	CMSIS_Driver_Include_SPI)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_remote_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_remote_c_wrapper)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imx7ulp_m4_freertos	middleware_multicore_rpmsg_lite_imx7ulp_m4_freertos)
include_ifdef(CONFIG_USE_component_wm8960_adapter	component_wm8960_adapter)
include_ifdef(CONFIG_USE_driver_lptmr	driver_lptmr)
include_ifdef(CONFIG_USE_middleware_issdk_algorithms_pedometer_lib_cm4	middleware_issdk_algorithms_pedometer_lib_cm4)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_freertos	middleware_multicore_erpc_eRPC_port_freertos)
include_ifdef(CONFIG_USE_driver_flexio_spi_edma	driver_flexio_spi_edma)
include_ifdef(CONFIG_USE_component_codec_i2c_MCIMX7U5	component_codec_i2c_MCIMX7U5)
include_ifdef(CONFIG_USE_driver_sai_edma	driver_sai_edma)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_middleware_issdk_algorithms_pedometer_common	middleware_issdk_algorithms_pedometer_common)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_driver_acmp	driver_acmp)
include_ifdef(CONFIG_USE_driver_lpit	driver_lpit)
include_ifdef(CONFIG_USE_driver_edma	driver_edma)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_driver_xrdc	driver_xrdc)
include_ifdef(CONFIG_USE_driver_srtm_MCIMX7U5	driver_srtm_MCIMX7U5)
include_ifdef(CONFIG_USE_driver_dac12	driver_dac12)
include_ifdef(CONFIG_USE_driver_lpspi_edma	driver_lpspi_edma)
include_ifdef(CONFIG_USE_driver_srtm_freertos	driver_srtm_freertos)
include_ifdef(CONFIG_USE_driver_qspi_edma	driver_qspi_edma)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_driver_fxos8700cq	driver_fxos8700cq)
include_ifdef(CONFIG_USE_driver_trng	driver_trng)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
include_ifdef(CONFIG_USE_driver_ltc_edma	driver_ltc_edma)
