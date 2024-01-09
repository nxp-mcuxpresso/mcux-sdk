list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_cmsis_lpspi)
#    include(middleware_freertos-kernel_extension)
#    include(driver_tstmr)
#    include(driver_crc)
#    include(driver_lpspi_edma)
#    include(utility_assert)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_gpio)
#    include(driver_llwu)
#    include(driver_qspi)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_lpspi_freertos)
#    include(driver_lpi2c_edma)
#    include(driver_ltc_edma)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_lpi2c)
#    include(driver_snvs_lp)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(driver_xrdc)
#    include(utility_debug_console_lite)
#    include(driver_port)
#    include(driver_dmamux)
#    include(middleware_mbedtls_MCIMX7U5)
#    include(utility_debug_console)
#    include(driver_msmc)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_pmc0)
#    include(driver_sai_edma)
#    include(driver_ltc)
#    include(driver_lpuart)
#    include(driver_lpadc)
#    include(driver_trng)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(driver_sema42)
#    include(driver_tpm)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(driver_cache_lmem)
#    include(driver_snvs_hp)
#    include(driver_wdog32)
#    include(driver_flexio_i2c_master)
#    include(driver_flexio_uart)
#    include(device_CMSIS)
#    include(utilities_misc_utilities_MCIMX7U5)
#    include(component_lpuart_adapter)
#    include(driver_lpuart_freertos)
#    include(driver_dac12)
#    include(driver_qspi_edma)
#    include(driver_acmp)
#    include(driver_sai)
#    include(driver_flexio_uart_edma)
#    include(driver_ewm)
#    include(driver_flexio)
#    include(driver_trgmux)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(middleware_freertos-kernel_MCIMX7U5)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_lpspi)
#    include(driver_edma_MCIMX7U5)
#    include(driver_iomuxc)
#    include(driver_flexio_spi)
#    include(driver_common)
#    include(CMSIS_Include_core_cm)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_cmsis_lpi2c)
