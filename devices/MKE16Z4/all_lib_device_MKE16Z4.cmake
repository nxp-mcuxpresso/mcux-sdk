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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mscan
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(middleware_freertos-kernel_MKE16Z4)
#    include(utilities_misc_utilities_MKE16Z4)
#    include(driver_lpuart_freertos)
#    include(utility_shell)
#    include(driver_mscan)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_freertos)
#    include(driver_port)
#    include(driver_wdog32)
#    include(driver_lpspi)
#    include(driver_lptmr)
#    include(driver_gpio)
#    include(component_lists)
#    include(device_system)
#    include(component_log)
#    include(driver_acmp)
#    include(device_startup)
#    include(driver_pdb)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_adc12)
#    include(driver_lpit)
#    include(driver_fxos8700cq)
#    include(driver_ewm)
#    include(utility_assert)
#    include(driver_lpuart)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ftm)
#    include(driver_trgmux)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(utility_assert_lite)
#    include(driver_tsi_v5)
#    include(driver_cmsis_lpi2c)
#    include(driver_flash)
#    include(component_panic)
#    include(driver_clock)
#    include(driver_mmdvsq)
#    include(driver_sim)
#    include(component_log_backend_ringbuffer)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_osa_bm)
#    include(driver_lpi2c)
#    include(driver_common)
#    include(driver_rtc)
#    include(driver_cmsis_lpspi)
#    include(driver_smc)
#    include(driver_crc)
#    include(utility_notifier)
#    include(component_serial_manager)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(driver_pwt)
#    include(driver_pmc)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_rcm)
#    include(component_log_backend_debugconsole)
#    include(driver_cmsis_lpuart)
