list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
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
#    include(driver_dmamux)
#    include(utility_shell)
#    include(driver_cmsis_lpuart)
#    include(driver_dac)
#    include(device_system)
#    include(driver_lpuart_freertos)
#    include(driver_ewm)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_uart)
#    include(utilities_misc_utilities_MK22F51212)
#    include(driver_rtc)
#    include(component_gpio_adapter)
#    include(component_serial_manager)
#    include(middleware_freertos-kernel_MK22F51212)
#    include(middleware_usb_device_cdc_external)
#    include(component_serial_manager_uart)
#    include(middleware_usb_host_stack_MK22F51212)
#    include(component_log_backend_debugconsole)
#    include(driver_llwu)
#    include(driver_lptmr)
#    include(driver_pit)
#    include(driver_i2c_edma)
#    include(device_startup)
#    include(driver_dspi_freertos)
#    include(component_panic)
#    include(utility_assert)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(component_led)
#    include(middleware_usb_common_header)
#    include(middleware_fatfs_MK22F51212)
#    include(middleware_usb_device_common_header)
#    include(component_uart_adapter)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_osa_bm)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(driver_cmsis_uart)
#    include(driver_smc)
#    include(component_osa_free_rtos)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_1)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(middleware_usb_host_msd)
#    include(driver_port)
#    include(driver_gpio)
#    include(component_log)
#    include(driver_rnga)
#    include(driver_edma_MK22F51212)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(middleware_usb_host_printer)
#    include(middleware_usb_host_audio)
#    include(utility_assert_lite)
#    include(driver_flash)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(driver_crc)
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
#    include(driver_lpuart)
#    include(driver_cmsis_i2c)
#    include(middleware_usb_device_khci)
#    include(component_pit_adapter)
#    include(driver_wdog)
#    include(utility_notifier)
#    include(driver_sim)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_device_stack_external)
#    include(driver_dspi_edma)
