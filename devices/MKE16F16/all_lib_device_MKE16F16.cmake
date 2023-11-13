list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac32
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysmpu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
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
#    include(driver_flexio_spi_edma)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_freertos)
#    include(driver_port)
#    include(driver_dmamux)
#    include(driver_lpspi)
#    include(driver_lpi2c_edma)
#    include(driver_gpio)
#    include(component_lists)
#    include(device_system)
#    include(driver_lpit)
#    include(driver_acmp)
#    include(device_startup)
#    include(driver_pdb)
#    include(driver_clock)
#    include(utility_notifier)
#    include(utility_debug_console_lite)
#    include(driver_adc12)
#    include(driver_flexio_uart)
#    include(driver_edma)
#    include(driver_ewm)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_flexio_spi)
#    include(driver_lpspi_edma)
#    include(middleware_freertos-kernel_extension)
#    include(driver_dac32)
#    include(driver_flexio)
#    include(driver_ftm)
#    include(driver_trgmux)
#    include(utility_assert_lite)
#    include(driver_cache_lmem)
#    include(driver_pmc)
#    include(middleware_freertos-kernel_MKE18F16)
#    include(utility_debug_console)
#    include(driver_sysmpu)
#    include(driver_flash)
#    include(driver_flexcan_edma)
#    include(driver_flexcan)
#    include(driver_lpuart_edma)
#    include(device_CMSIS)
#    include(driver_flexio_uart_edma)
#    include(utilities_misc_utilities)
#    include(driver_lpi2c)
#    include(driver_common)
#    include(driver_rtc)
#    include(driver_smc)
#    include(driver_crc)
#    include(driver_wdog32)
#    include(driver_sim)
#    include(component_serial_manager)
#    include(driver_fxos8700cq)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(driver_pwt)
#    include(driver_flexio_i2c_master)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(utility_shell)
