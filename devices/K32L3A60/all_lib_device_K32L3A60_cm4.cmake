list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cau3
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpcmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/msmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tstmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm4
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_utility_incbin	utility_incbin)
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_driver_sema42	driver_sema42)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_K32L3A60_cm4	middleware_sdmmc_host_usdhc_freertos_K32L3A60_cm4)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_k32l3a6_freertos	middleware_multicore_rpmsg_lite_k32l3a6_freertos)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_driver_cache_lpcac	driver_cache_lpcac)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_driver_msmc	driver_msmc)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_client	middleware_multicore_erpc_eRPC_client)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_K32L3A60_cm4	middleware_sdmmc_host_usdhc_interrupt_K32L3A60_cm4)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_bm	middleware_sdmmc_osa_bm)
include_ifdef(CONFIG_USE_driver_lpuart_edma	driver_lpuart_edma)
include_ifdef(CONFIG_USE_driver_lpspi_edma	driver_lpspi_edma)
include_ifdef(CONFIG_USE_driver_lpcmp	driver_lpcmp)
include_ifdef(CONFIG_USE_driver_flexio_uart_edma	driver_flexio_uart_edma)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_rtc	driver_rtc)
include_ifdef(CONFIG_USE_driver_wdog32	driver_wdog32)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_lpspi_freertos	driver_lpspi_freertos)
include_ifdef(CONFIG_USE_device_system_K32L3A60_cm4	device_system_K32L3A60_cm4)
include_ifdef(CONFIG_USE_driver_llwu	driver_llwu)
include_ifdef(CONFIG_USE_device_startup_K32L3A60_cm4	device_startup_K32L3A60_cm4)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_lpi2c_edma	driver_lpi2c_edma)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
include_ifdef(CONFIG_USE_driver_usdhc	driver_usdhc)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_freertos	middleware_sdmmc_osa_freertos)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_doc	middleware_multicore_erpc_doc)
include_ifdef(CONFIG_USE_driver_tstmr	driver_tstmr)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_common	middleware_multicore_erpc_common)
include_ifdef(CONFIG_USE_component_osa_bm	component_osa_bm)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_component_osa_free_rtos	component_osa_free_rtos)
include_ifdef(CONFIG_USE_middleware_sdmmc_sd	middleware_sdmmc_sd)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_port	driver_port)
include_ifdef(CONFIG_USE_driver_lpspi	driver_lpspi)
include_ifdef(CONFIG_USE_driver_gpio	driver_gpio)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_c_wrapper	middleware_multicore_erpc_eRPC_mu_c_wrapper)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_polling_K32L3A60_cm4	middleware_sdmmc_host_usdhc_polling_K32L3A60_cm4)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_flash	driver_flash)
include_ifdef(CONFIG_USE_driver_spm	driver_spm)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_lptmr	driver_lptmr)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr	middleware_multicore_mcmgr)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_K32L3A60_cm4	middleware_freertos-kernel_K32L3A60_cm4)
include_ifdef(CONFIG_USE_driver_crc	driver_crc)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc	middleware_sdmmc_host_usdhc)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_stdlib	middleware_multicore_erpc_eRPC_port_stdlib)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_arbitrator	middleware_multicore_erpc_eRPC_arbitrator)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_freertos	middleware_multicore_erpc_eRPC_port_freertos)
include_ifdef(CONFIG_USE_driver_dac_1	driver_dac_1)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr_k32l3a6	middleware_multicore_mcmgr_k32l3a6)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_transport	middleware_multicore_erpc_eRPC_mu_transport)
include_ifdef(CONFIG_USE_driver_flexio_spi_edma	driver_flexio_spi_edma)
include_ifdef(CONFIG_USE_driver_lpi2c_freertos	driver_lpi2c_freertos)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_middleware_sdmmc_common	middleware_sdmmc_common)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_k32l3a6_bm	middleware_multicore_rpmsg_lite_k32l3a6_bm)
include_ifdef(CONFIG_USE_driver_cau3	driver_cau3)
include_ifdef(CONFIG_USE_driver_lpit	driver_lpit)
include_ifdef(CONFIG_USE_driver_edma	driver_edma)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_driver_xrdc	driver_xrdc)
include_ifdef(CONFIG_USE_driver_sim	driver_sim)
include_ifdef(CONFIG_USE_driver_lpi2c	driver_lpi2c)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
include_ifdef(CONFIG_USE_driver_fxos8700cq	driver_fxos8700cq)
include_ifdef(CONFIG_USE_driver_trng	driver_trng)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_rtos_transport	middleware_multicore_erpc_eRPC_mu_rtos_transport)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
