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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
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
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_dsp)
#    include(driver_spi_freertos)
#    include(driver_rcm)
#    include(utility_notifier)
#    include(driver_rtc)
#    include(driver_uart)
#    include(driver_crc)
#    include(utility_assert)
#    include(driver_adc16)
#    include(middleware_freertos-kernel_MKL27Z644)
#    include(driver_gpio)
#    include(driver_llwu)
#    include(driver_flexio_spi_dma)
#    include(driver_sim)
#    include(driver_flexio_uart_dma)
#    include(driver_pmc)
#    include(middleware_baremetal)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(utility_debug_console_lite)
#    include(driver_port)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(driver_smc)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_lpuart)
#    include(driver_i2c_freertos)
#    include(device_system)
#    include(driver_pit)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(driver_tpm)
#    include(driver_clock)
#    include(driver_uart_dma)
#    include(driver_flexio_i2c_master)
#    include(driver_flexio_uart)
#    include(device_CMSIS)
#    include(component_lpuart_adapter)
#    include(CMSIS_Include_core_cm0plus)
#    include(CMSIS_Include_common)
#    include(driver_lpuart_freertos)
#    include(driver_cop)
#    include(driver_flexio)
#    include(driver_dma)
#    include(component_osa)
#    include(driver_spi)
#    include(driver_i2c)
#    include(driver_flexio_spi)
#    include(driver_mma8451q)
#    include(driver_common)
#    include(driver_spi_dma)
#    include(middleware_usb_common_header)
#    include(utilities_misc_utilities_MKL27Z644)
#    include(component_serial_manager)
#    include(middleware_usb_device_common_header)
