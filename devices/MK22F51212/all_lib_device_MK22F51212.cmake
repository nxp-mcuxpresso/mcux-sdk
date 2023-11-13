list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/led
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rnga
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
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
#    include(component_button_MK22F51212)
#    include(driver_dspi)
#    include(driver_uart_freertos)
#    include(driver_vref)
#    include(middleware_issdk_algorithms_sensor_fusion_agmp03_common)
#    include(driver_dmamux)
#    include(utility_shell)
#    include(driver_cmsis_lpuart)
#    include(driver_dac)
#    include(middleware_issdk_sensor_fxos8700)
#    include(device_system)
#    include(driver_lpuart_freertos)
#    include(driver_ewm)
#    include(driver_rtc)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(middleware_baremetal)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_uart)
#    include(utilities_misc_utilities)
#    include(middleware_issdk_drivers_gpio_kinetis)
#    include(component_gpio_adapter)
#    include(component_serial_manager)
#    include(middleware_issdk_sensor_fxas21002)
#    include(middleware_freertos-kernel_MK22F51212)
#    include(middleware_usb_device_cdc_external)
#    include(middleware_usb_host_stack_MK22F51212)
#    include(component_log_backend_debugconsole)
#    include(driver_llwu)
#    include(driver_ili9341)
#    include(driver_lptmr)
#    include(driver_pit)
#    include(middleware_issdk_algorithms_sensor_fusion_agm01_common)
#    include(driver_i2c_edma)
#    include(device_startup)
#    include(driver_dspi_freertos)
#    include(component_panic)
#    include(utility_assert)
#    include(middleware_issdk_sensor_interface_common)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(CMSIS_Driver_Include_I2C)
#    include(component_led)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_c_wrapper)
#    include(middleware_usb_common_header)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_usb_device_common_header)
#    include(component_uart_adapter)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_issdk_sensor_fxls896xaf)
#    include(component_osa_bm)
#    include(middleware_usb_host_common_header)
#    include(driver_rnga)
#    include(driver_common)
#    include(driver_cmsis_uart)
#    include(driver_smc)
#    include(middleware_issdk_drivers_host)
#    include(component_osa_free_rtos)
#    include(middleware_freertos-kernel_heap_1)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(middleware_multicore_erpc_common)
#    include(component_serial_manager_uart_MK22F51212)
#    include(middleware_usb_host_msd)
#    include(driver_port)
#    include(middleware_multicore_erpc_eRPC_dspi_master_c_wrapper)
#    include(driver_gpio)
#    include(middleware_issdk_sensor_allregdefs)
#    include(component_log)
#    include(middleware_usb_host_cdc)
#    include(driver_edma_MK22F51212)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART)
#    include(CMSIS_Driver_Include_SPI)
#    include(utility_debug_console_lite)
#    include(middleware_usb_host_printer)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(middleware_usb_host_audio)
#    include(utility_assert_lite)
#    include(middleware_fatfs)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(driver_crc)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_issdk_drivers_ads)
#    include(middleware_issdk_sensor_fxlc95000)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(middleware_issdk_drivers_systick_utils)
#    include(driver_pmc)
#    include(middleware_usb_device_controller_driver_MK22F51212)
#    include(component_pwm_ftm_adapter)
#    include(middleware_fatfs_usb)
#    include(component_serial_manager_usb_cdc)
#    include(driver_cmsis_dspi)
#    include(driver_uart_edma)
#    include(middleware_usb_host_khci)
#    include(component_timer_manager)
#    include(driver_i2c)
#    include(driver_i2c_freertos)
#    include(component_lists)
#    include(driver_cmp)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(driver_cmsis_i2c)
#    include(middleware_usb_device_khci)
#    include(middleware_issdk_sensor_fxls8962)
#    include(component_pit_adapter)
#    include(driver_wdog)
#    include(utility_notifier)
#    include(middleware_issdk_sensor_mpl3115)
#    include(driver_sim)
#    include(middleware_issdk_sensor_mag3110)
#    include(middleware_issdk_sensor_fxls8974cf)
#    include(middleware_usb_host_phdc)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_transport)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(middleware_multicore_erpc_eRPC_dspi_master_transport)
#    include(middleware_usb_device_stack_external)
#    include(driver_ft6x06)
#    include(driver_dspi_edma)
