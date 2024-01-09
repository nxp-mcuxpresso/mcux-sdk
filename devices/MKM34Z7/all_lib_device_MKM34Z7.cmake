list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/slcd_engine
    ${CMAKE_CURRENT_LIST_DIR}/../../components/slcd_engine/GDH-1247WP
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/afe
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmau
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qtmr_2
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rnga
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/slcd
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysmpu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbar
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/mmcau
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_i2c_dma)
#    include(driver_uart_freertos)
#    include(utility_shell)
#    include(driver_cmp)
#    include(driver_lpuart_dma)
#    include(driver_slcd_gdh_1247wp)
#    include(driver_pdb)
#    include(middleware_freertos-kernel_extension)
#    include(driver_spi_freertos)
#    include(driver_rcm)
#    include(utility_notifier)
#    include(driver_uart)
#    include(driver_crc)
#    include(utility_assert)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_gpio)
#    include(driver_llwu)
#    include(driver_rnga)
#    include(driver_sim)
#    include(driver_sysmpu)
#    include(driver_pmc)
#    include(driver_qtmr_2)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(component_log_backend_ringbuffer)
#    include(utilities_misc_utilities_MKM34Z7)
#    include(driver_port)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(driver_mmau)
#    include(driver_smc)
#    include(middleware_freertos-kernel_heap_4)
#    include(component_log_backend_debugconsole_MKM34Z7)
#    include(driver_cmsis_uart)
#    include(driver_vref)
#    include(utility_debug_console)
#    include(driver_lpuart)
#    include(driver_afe)
#    include(device_system)
#    include(driver_i2c_freertos)
#    include(driver_pit)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(middleware_mmcau_common_files)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(middleware_freertos-kernel_MKM34Z7)
#    include(driver_uart_dma)
#    include(driver_slcd)
#    include(component_log)
#    include(component_uart_adapter)
#    include(device_CMSIS)
#    include(driver_wdog)
#    include(driver_cmsis_spi)
#    include(driver_lpuart_freertos)
#    include(driver_ewm)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_dma)
#    include(middleware_mmcau_cm0p)
#    include(driver_spi)
#    include(driver_i2c)
#    include(driver_common)
#    include(driver_cmsis_i2c)
#    include(driver_irtc)
#    include(CMSIS_Include_core_cm)
#    include(driver_spi_dma)
#    include(driver_xbar)
#    include(component_serial_manager)
#    include(driver_slcd_engine)
