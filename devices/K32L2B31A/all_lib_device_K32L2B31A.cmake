list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/led
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/slcd_engine
    ${CMAKE_CURRENT_LIST_DIR}/../../components/slcd_engine/LCD-S401M16KR
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cop
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/slcd
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tpm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_lpuart_freertos)
#    include(driver_uart_freertos)
#    include(driver_dmamux)
#    include(driver_cmsis_lpuart)
#    include(driver_dac)
#    include(driver_cop)
#    include(driver_cmsis_spi)
#    include(driver_flexio_uart)
#    include(driver_flexio)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(component_log_backend_ringbuffer)
#    include(driver_uart)
#    include(component_tpm_adapter)
#    include(driver_rtc)
#    include(component_gpio_adapter)
#    include(component_serial_manager)
#    include(driver_slcd)
#    include(driver_pit)
#    include(middleware_usb_device_cdc_external)
#    include(component_serial_manager_uart)
#    include(component_log_backend_debugconsole)
#    include(driver_llwu)
#    include(device_system)
#    include(component_lpuart_adapter)
#    include(driver_spi_dma)
#    include(driver_lptmr)
#    include(device_startup)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(component_led)
#    include(middleware_usb_common_header)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_usb_device_common_header)
#    include(component_panic)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(middleware_multicore_erpc_eRPC_spi_master_c_wrapper)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(driver_common)
#    include(driver_uart_dma)
#    include(driver_smc)
#    include(component_osa_free_rtos)
#    include(middleware_freertos-kernel_K32L2B31A)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(driver_cmsis_uart)
#    include(component_button_K32L2B31A)
#    include(driver_port)
#    include(driver_gpio)
#    include(component_log)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_lpuart_dma)
#    include(driver_flexio_uart_dma)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(utility_shell)
#    include(utility_assert_lite)
#    include(driver_spi)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(middleware_usb_device_controller_driver_K32L2B31A)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_pmc)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_slcd_lcd_s401m16kr)
#    include(middleware_multicore_erpc_eRPC_spi_slave_transport)
#    include(component_timer_manager)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(component_lists)
#    include(driver_tpm)
#    include(driver_cmp)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(driver_cmsis_i2c)
#    include(middleware_usb_device_khci)
#    include(component_pit_adapter)
#    include(middleware_multicore_erpc_eRPC_spi_slave_c_wrapper)
#    include(utilities_misc_utilities_K32L2B31A)
#    include(utility_notifier)
#    include(driver_sim)
#    include(driver_dma)
#    include(driver_i2c_dma)
#    include(middleware_multicore_erpc_eRPC_spi_master_transport)
#    include(driver_flexio_spi_dma)
#    include(driver_slcd_engine)
#    include(driver_spi_freertos)
#    include(middleware_usb_device_stack_external)
