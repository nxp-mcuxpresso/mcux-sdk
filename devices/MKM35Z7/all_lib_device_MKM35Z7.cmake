list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_driver_llwu	driver_llwu)
include_ifdef(CONFIG_USE_driver_port	driver_port)
include_ifdef(CONFIG_USE_driver_lpuart_freertos	driver_lpuart_freertos)
include_ifdef(CONFIG_USE_driver_uart_freertos	driver_uart_freertos)
include_ifdef(CONFIG_USE_driver_slcd_gdh_1247wp	driver_slcd_gdh_1247wp)
include_ifdef(CONFIG_USE_driver_i2c	driver_i2c)
include_ifdef(CONFIG_USE_driver_i2c_freertos	driver_i2c_freertos)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_lptmr	driver_lptmr)
include_ifdef(CONFIG_USE_driver_gpio	driver_gpio)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_driver_irtc	driver_irtc)
include_ifdef(CONFIG_USE_driver_cmp	driver_cmp)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_pdb	driver_pdb)
include_ifdef(CONFIG_USE_driver_adc16	driver_adc16)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_i2c_dma	driver_i2c_dma)
include_ifdef(CONFIG_USE_driver_lpuart_dma	driver_lpuart_dma)
include_ifdef(CONFIG_USE_driver_ewm	driver_ewm)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_middleware_mmcau_common_files	middleware_mmcau_common_files)
include_ifdef(CONFIG_USE_driver_xbar	driver_xbar)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_notifier	utility_notifier)
include_ifdef(CONFIG_USE_driver_wdog	driver_wdog)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_sysmpu	driver_sysmpu)
include_ifdef(CONFIG_USE_driver_vref	driver_vref)
include_ifdef(CONFIG_USE_driver_mmau	driver_mmau)
include_ifdef(CONFIG_USE_driver_spi	driver_spi)
include_ifdef(CONFIG_USE_driver_flash	driver_flash)
include_ifdef(CONFIG_USE_component_uart_adapter	component_uart_adapter)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_middleware_mmcau_cm0p	middleware_mmcau_cm0p)
include_ifdef(CONFIG_USE_driver_sim	driver_sim)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_uart	driver_uart)
include_ifdef(CONFIG_USE_driver_qtmr_2	driver_qtmr_2)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_rnga	driver_rnga)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_uart_dma	driver_uart_dma)
include_ifdef(CONFIG_USE_driver_smc	driver_smc)
include_ifdef(CONFIG_USE_driver_crc	driver_crc)
include_ifdef(CONFIG_USE_driver_spi_dma	driver_spi_dma)
include_ifdef(CONFIG_USE_driver_dma	driver_dma)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_slcd	driver_slcd)
include_ifdef(CONFIG_USE_driver_pit	driver_pit)
include_ifdef(CONFIG_USE_driver_afe	driver_afe)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_pmc	driver_pmc)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_rcm	driver_rcm)
include_ifdef(CONFIG_USE_driver_slcd_engine	driver_slcd_engine)
include_ifdef(CONFIG_USE_driver_spi_freertos	driver_spi_freertos)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MKM35Z7	middleware_freertos-kernel_MKM35Z7)
