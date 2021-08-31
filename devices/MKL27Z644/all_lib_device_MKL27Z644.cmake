list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/mma8451q
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cop
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
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
include_ifdef(CONFIG_USE_CMSIS_Include_dsp	CMSIS_Include_dsp)
include_ifdef(CONFIG_USE_component_lpuart_adapter	component_lpuart_adapter)
include_ifdef(CONFIG_USE_driver_i2c	driver_i2c)
include_ifdef(CONFIG_USE_driver_i2c_freertos	driver_i2c_freertos)
include_ifdef(CONFIG_USE_driver_dmamux	driver_dmamux)
include_ifdef(CONFIG_USE_driver_lptmr	driver_lptmr)
include_ifdef(CONFIG_USE_driver_gpio	driver_gpio)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_flexio_uart_dma	driver_flexio_uart_dma)
include_ifdef(CONFIG_USE_driver_cop	driver_cop)
include_ifdef(CONFIG_USE_driver_tpm	driver_tpm)
include_ifdef(CONFIG_USE_driver_cmp	driver_cmp)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_adc16	driver_adc16)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_flexio_uart	driver_flexio_uart)
include_ifdef(CONFIG_USE_component_osa	component_osa)
include_ifdef(CONFIG_USE_driver_lpuart_dma	driver_lpuart_dma)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MKL27Z644	middleware_freertos-kernel_MKL27Z644)
include_ifdef(CONFIG_USE_driver_lpuart	driver_lpuart)
include_ifdef(CONFIG_USE_driver_flexio_spi	driver_flexio_spi)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_flexio	driver_flexio)
include_ifdef(CONFIG_USE_middleware_usb_device_common_header	middleware_usb_device_common_header)
include_ifdef(CONFIG_USE_utility_notifier	utility_notifier)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm0plus	CMSIS_Include_core_cm0plus)
include_ifdef(CONFIG_USE_driver_flexio_i2c_master	driver_flexio_i2c_master)
include_ifdef(CONFIG_USE_driver_pmc	driver_pmc)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_driver_spi	driver_spi)
include_ifdef(CONFIG_USE_driver_flash	driver_flash)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_driver_mma8451q	driver_mma8451q)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_uart	driver_uart)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_CMSIS_Include_common	CMSIS_Include_common)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_rtc	driver_rtc)
include_ifdef(CONFIG_USE_driver_uart_dma	driver_uart_dma)
include_ifdef(CONFIG_USE_driver_smc	driver_smc)
include_ifdef(CONFIG_USE_driver_crc	driver_crc)
include_ifdef(CONFIG_USE_driver_spi_dma	driver_spi_dma)
include_ifdef(CONFIG_USE_driver_dma	driver_dma)
include_ifdef(CONFIG_USE_driver_i2c_dma	driver_i2c_dma)
include_ifdef(CONFIG_USE_driver_sim	driver_sim)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_pit	driver_pit)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_flexio_spi_dma	driver_flexio_spi_dma)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_rcm	driver_rcm)
include_ifdef(CONFIG_USE_driver_spi_freertos	driver_spi_freertos)
include_ifdef(CONFIG_USE_middleware_usb_common_header	middleware_usb_common_header)
