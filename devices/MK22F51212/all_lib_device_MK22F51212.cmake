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
#    include(utility_shell)
#    include(driver_dspi_edma)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(driver_ili9341)
#    include(middleware_issdk_sensor_fxls8974cf)
#    include(utility_notifier)
#    include(driver_cmsis_dspi)
#    include(driver_crc)
#    include(middleware_multicore_erpc_eRPC_dspi_master_c_wrapper)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_adc16)
#    include(driver_llwu)
#    include(middleware_usb_host_hid)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_pmc)
#    include(middleware_issdk_algorithms_sensor_fusion_agm01_common)
#    include(utilities_misc_utilities_MK22F51212)
#    include(driver_flash)
#    include(driver_dmamux)
#    include(middleware_issdk_sensor_mpl3115)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(component_log)
#    include(middleware_usb_device_stack_external)
#    include(driver_dspi)
#    include(driver_cmsis_lpuart)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(middleware_issdk_sensor_fxls8962)
#    include(middleware_issdk_drivers_gpio_kinetis)
#    include(driver_common)
#    include(middleware_issdk_drivers_host)
#    include(driver_cmp)
#    include(middleware_issdk_sensor_fxas21002)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(driver_uart)
#    include(driver_dac)
#    include(component_log_backend_debugconsole_MK22F51212)
#    include(driver_rnga)
#    include(driver_gpio)
#    include(component_button_MK22F51212)
#    include(component_serial_manager_uart)
#    include(middleware_usb_host_stack_MK22F51212)
#    include(component_pwm_ftm_adapter)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(driver_smc)
#    include(driver_i2c_edma)
#    include(driver_cmsis_uart)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(device_startup)
#    include(middleware_multicore_erpc_common)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_edma_MK22F51212)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_usb_host_common_header)
#    include(middleware_multicore_erpc_doc)
#    include(middleware_fatfs_MK22F51212)
#    include(middleware_issdk_sensor_interface_common)
#    include(driver_cmsis_i2c)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_c_wrapper)
#    include(driver_ftm)
#    include(middleware_freertos-kernel_heap_1)
#    include(middleware_usb_device_common_header)
#    include(driver_uart_freertos)
#    include(driver_rtc)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_ft6x06)
#    include(component_lists)
#    include(driver_dspi_freertos)
#    include(middleware_usb_host_msd)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_i2c_freertos)
#    include(middleware_issdk_sensor_fxos8700)
#    include(middleware_issdk_algorithms_sensor_fusion_agmp03_common)
#    include(middleware_usb_device_controller_driver_MK22F51212)
#    include(driver_wdog)
#    include(driver_lpuart_freertos)
#    include(driver_uart_edma)
#    include(middleware_issdk_drivers_ads)
#    include(driver_ewm)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(middleware_multicore_erpc_eRPC_dspi_slave_transport)
#    include(CMSIS_Include_core_cm)
#    include(middleware_freertos-kernel_MK22F51212)
#    include(middleware_usb_host_printer)
#    include(driver_sim)
#    include(middleware_issdk_sensor_allregdefs)
#    include(middleware_issdk_sensor_mag3110)
#    include(component_timer_manager)
#    include(component_gpio_adapter)
#    include(middleware_baremetal)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(driver_vref)
#    include(middleware_usb_device_khci)
#    include(device_system)
#    include(middleware_usb_host_khci)
#    include(utility_assert_lite)
#    include(middleware_usb_host_phdc)
#    include(component_uart_adapter)
#    include(component_led)
#    include(middleware_issdk_sensor_fxls896xaf)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(middleware_multicore_erpc_eRPC_dspi_master_transport)
#    include(driver_i2c)
#    include(component_osa_free_rtos_MK22F51212)
#    include(middleware_usb_common_header)
#    include(middleware_issdk_drivers_systick_utils)
#    include(component_serial_manager)
#    include(middleware_issdk_sensor_fxlc95000)
#    include(driver_fxos8700cq)
