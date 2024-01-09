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
#    include(driver_i2c_dma)
#    include(utility_shell)
#    include(component_osa_bm)
#    include(utility_notifier)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_adc16)
#    include(driver_llwu)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_pmc)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(middleware_usb_device_controller_driver_K32L2B31A)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_clock)
#    include(driver_slcd)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(component_lpuart_adapter)
#    include(middleware_usb_device_stack_external)
#    include(driver_cop)
#    include(component_button_K32L2B31A)
#    include(driver_cmsis_lpuart)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_common)
#    include(driver_cmp)
#    include(driver_lpuart_dma)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(driver_uart)
#    include(driver_dac)
#    include(driver_gpio)
#    include(driver_flexio_spi_dma)
#    include(driver_flexio_uart_dma)
#    include(component_serial_manager_uart)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(driver_smc)
#    include(driver_cmsis_uart)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(device_startup)
#    include(middleware_multicore_erpc_common)
#    include(middleware_multicore_erpc_eRPC_spi_slave_transport)
#    include(CMSIS_Driver_Include_SPI)
#    include(device_CMSIS)
#    include(driver_cmsis_spi)
#    include(middleware_multicore_erpc_eRPC_spi_master_transport)
#    include(middleware_multicore_erpc_doc)
#    include(driver_cmsis_i2c)
#    include(driver_spi_dma)
#    include(component_osa_free_rtos_K32L2B31A)
#    include(middleware_usb_device_common_header)
#    include(driver_uart_freertos)
#    include(driver_rtc)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(component_lists)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_i2c_freertos)
#    include(driver_tpm)
#    include(driver_uart_dma)
#    include(driver_flexio_uart)
#    include(driver_lpuart_freertos)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(driver_dma)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(CMSIS_Include_core_cm)
#    include(driver_slcd_engine)
#    include(driver_spi_freertos)
#    include(middleware_multicore_erpc_eRPC_spi_slave_c_wrapper)
#    include(driver_slcd_lcd_s401m16kr)
#    include(driver_sim)
#    include(component_timer_manager)
#    include(component_gpio_adapter)
#    include(middleware_baremetal)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(middleware_usb_device_khci)
#    include(device_system)
#    include(utility_assert_lite)
#    include(component_led)
#    include(component_log_backend_debugconsole_K32L2B31A)
#    include(driver_flexio)
#    include(component_tpm_adapter)
#    include(driver_spi)
#    include(driver_i2c)
#    include(driver_flexio_spi)
#    include(middleware_freertos-kernel_K32L2B31A)
#    include(middleware_usb_common_header)
#    include(middleware_multicore_erpc_eRPC_spi_master_c_wrapper)
#    include(utilities_misc_utilities_K32L2B31A)
#    include(component_serial_manager)
#    include(driver_fxos8700cq)
