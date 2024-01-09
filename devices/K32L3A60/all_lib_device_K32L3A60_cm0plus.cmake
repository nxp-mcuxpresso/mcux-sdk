list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/intmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpcmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/msmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tstmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm0plus
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(utilities_misc_utilities_K32L3A60_cm0plus)
#    include(component_osa_bm)
#    include(driver_crc)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_remote_c_wrapper)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_lpi2c_edma)
#    include(middleware_sdmmc_host_usdhc)
#    include(driver_xrdc)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(middleware_sdmmc_host_usdhc_interrupt_K32L3A60_cm0plus)
#    include(driver_lpuart)
#    include(driver_lpadc)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_clock)
#    include(middleware_multicore_erpc_eRPC_mu_transport)
#    include(driver_lpuart_edma)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(middleware_sdmmc_host_usdhc_freertos_K32L3A60_cm0plus)
#    include(component_lpuart_adapter)
#    include(middleware_multicore_rpmsg_lite_K32L3A60_cm0plus)
#    include(driver_cmsis_lpuart)
#    include(CMSIS_Driver_Include_USART)
#    include(device_system_K32L3A60_cm0plus)
#    include(driver_lpspi)
#    include(driver_common)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(driver_gpio)
#    include(component_serial_manager_uart)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(middleware_multicore_rpmsg_lite_k32l3a6_freertos)
#    include(driver_trng)
#    include(driver_edma_K32L3A60_cm0plus)
#    include(middleware_multicore_erpc_eRPC_mu_rtos_transport)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_multicore_erpc_common)
#    include(CMSIS_Driver_Include_SPI)
#    include(device_CMSIS)
#    include(middleware_fatfs_K32L3A60_cm0plus)
#    include(middleware_mbedtls_kinetis3)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_sdmmc_common)
#    include(driver_intmux)
#    include(middleware_sdmmc_sd)
#    include(driver_cmsis_lpspi)
#    include(driver_mmdvsq)
#    include(driver_rtc)
#    include(utility_assert)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_lpspi_freertos)
#    include(middleware_mbedtls_K32L3A60_cm0plus)
#    include(component_lists)
#    include(middleware_multicore_erpc_eRPC_mu_c_wrapper)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_msmc)
#    include(middleware_freertos-kernel_heap_4)
#    include(component_osa_free_rtos_K32L3A60_cm0plus)
#    include(component_log_backend_debugconsole_K32L3A60_cm0plus)
#    include(driver_tpm)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper)
#    include(driver_flexio_uart)
#    include(driver_dac_1)
#    include(driver_usdhc)
#    include(driver_lpuart_freertos)
#    include(driver_ewm)
#    include(middleware_freertos-kernel_K32L3A60_cm0plus)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(CMSIS_Include_core_cm)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(driver_tstmr)
#    include(driver_lpspi_edma)
#    include(driver_sim)
#    include(middleware_multicore_rpmsg_lite_bm)
#    include(middleware_baremetal)
#    include(component_gpio_adapter)
#    include(driver_lptmr)
#    include(middleware_multicore_mcmgr_k32l3a6)
#    include(utility_debug_console_lite)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_cache_lplmem)
#    include(driver_cau3)
#    include(utility_assert_lite)
#    include(middleware_sdmmc_host_usdhc_polling_K32L3A60_cm0plus)
#    include(device_startup_K32L3A60_cm0plus)
#    include(driver_sema42)
#    include(driver_lpcmp)
#    include(middleware_multicore_mcmgr)
#    include(driver_flexio_uart_edma)
#    include(driver_flexio)
#    include(middleware_multicore_rpmsg_lite_k32l3a6_bm)
#    include(driver_flexio_spi)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_lpi2c)
