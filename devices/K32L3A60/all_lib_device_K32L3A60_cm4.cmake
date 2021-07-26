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
#    include(utility_incbin)
#    include(driver_lpuart_freertos)
#    include(driver_sema42)
#    include(driver_dmamux)
#    include(middleware_sdmmc_host_usdhc_freertos_K32L3A60_cm4)
#    include(driver_lpadc)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(driver_flexio_uart)
#    include(middleware_multicore_rpmsg_lite_k32l3a6_freertos)
#    include(driver_ewm)
#    include(driver_cache_lpcac)
#    include(driver_flexio)
#    include(driver_msmc)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(middleware_sdmmc_host_usdhc_interrupt_K32L3A60_cm4)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_lpcmp)
#    include(driver_flexio_uart_edma)
#    include(utilities_misc_utilities)
#    include(driver_rtc)
#    include(driver_wdog32)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(device_system_K32L3A60_cm4)
#    include(driver_llwu)
#    include(device_startup_K32L3A60_cm4)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
#    include(driver_usdhc)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_sdmmc_osa_freertos)
#    include(utility_assert)
#    include(device_CMSIS)
#    include(middleware_multicore_erpc_doc)
#    include(driver_tstmr)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(driver_common)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(CMSIS_Include_core_cm)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_port)
#    include(driver_lpspi)
#    include(driver_gpio)
#    include(middleware_multicore_erpc_eRPC_mu_c_wrapper)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(middleware_sdmmc_host_usdhc_polling_K32L3A60_cm4)
#    include(utility_shell)
#    include(utility_assert_lite)
#    include(driver_flash)
#    include(driver_spm)
#    include(utility_debug_console)
#    include(driver_lptmr)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
#    include(middleware_multicore_mcmgr)
#    include(middleware_freertos-kernel_K32L3A60_cm4)
#    include(driver_crc)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_dac_1)
#    include(middleware_multicore_mcmgr_k32l3a6)
#    include(middleware_multicore_erpc_eRPC_mu_transport)
#    include(driver_flexio_spi_edma)
#    include(driver_lpi2c_freertos)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_tpm)
#    include(middleware_multicore_rpmsg_lite_k32l3a6_bm)
#    include(driver_cau3)
#    include(driver_lpit)
#    include(driver_edma)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(driver_xrdc)
#    include(driver_sim)
#    include(driver_lpi2c)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_fxos8700cq)
#    include(driver_trng)
#    include(middleware_multicore_erpc_eRPC_mu_rtos_transport)
#    include(driver_mu)
