list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tsi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(middleware_issdk_sensor_nps300x)
#    include(utility_notifier)
#    include(driver_crc)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_pmc)
#    include(driver_lpi2c_edma)
#    include(component_log_backend_debugconsole_MKE15Z7)
#    include(driver_dmamux)
#    include(driver_flash)
#    include(driver_lpuart)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(component_lpuart_adapter)
#    include(driver_acmp)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_lpspi)
#    include(driver_common)
#    include(middleware_issdk_drivers_host)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(utilities_misc_utilities_MKE15Z7)
#    include(middleware_issdk_drivers_gpio_kinetis_ke15z)
#    include(driver_gpio)
#    include(driver_pwt)
#    include(component_serial_manager_uart)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(driver_smc)
#    include(driver_edma_MKE15Z7)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(device_CMSIS)
#    include(middleware_issdk_sensor_interface_common)
#    include(driver_ftm)
#    include(driver_adc12)
#    include(driver_cmsis_lpspi)
#    include(driver_mmdvsq)
#    include(driver_rtc)
#    include(utility_assert)
#    include(driver_lpspi_freertos)
#    include(component_lists)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_wdog32)
#    include(driver_flexio_uart)
#    include(driver_lpuart_freertos)
#    include(middleware_issdk_drivers_ads)
#    include(driver_ewm)
#    include(CMSIS_Include_core_cm)
#    include(middleware_freertos-kernel_MKE15Z7)
#    include(driver_lpspi_edma)
#    include(driver_sim)
#    include(middleware_issdk_sensor_allregdefs)
#    include(driver_lptmr)
#    include(utility_debug_console_lite)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(middleware_issdk_sensor_fxps7250d4)
#    include(device_system)
#    include(utility_assert_lite)
#    include(component_osa_free_rtos_MKE15Z7)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(driver_trgmux)
#    include(driver_flexio_uart_edma)
#    include(driver_tsi_v5)
#    include(driver_flexio)
#    include(driver_flexio_spi)
#    include(middleware_issdk_drivers_systick_utils)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_lpi2c)
