list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trgmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_adc12)
#    include(driver_cmsis_lpspi)
#    include(component_osa_bm)
#    include(driver_pdb)
#    include(middleware_freertos-kernel_extension)
#    include(driver_rcm)
#    include(utility_notifier)
#    include(driver_mmdvsq)
#    include(driver_rtc)
#    include(driver_crc)
#    include(utilities_misc_utilities_MKE16Z4)
#    include(utility_assert)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_gpio)
#    include(component_log_backend_debugconsole_MKE16Z4)
#    include(driver_pwt)
#    include(driver_sim)
#    include(driver_lpspi_freertos)
#    include(driver_pmc)
#    include(driver_lptmr)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_lpi2c)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(component_log_backend_ringbuffer)
#    include(driver_port)
#    include(component_panic)
#    include(driver_flash)
#    include(driver_smc)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_lpuart)
#    include(middleware_freertos-kernel_heap_3)
#    include(device_system)
#    include(utility_assert_lite)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(driver_wdog32)
#    include(component_log)
#    include(device_CMSIS)
#    include(component_lpuart_adapter)
#    include(driver_lpuart_freertos)
#    include(driver_acmp)
#    include(driver_trgmux)
#    include(driver_ewm)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(middleware_freertos-kernel_MKE16Z4)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_lpspi)
#    include(driver_common)
#    include(CMSIS_Include_core_cm)
#    include(driver_ftm)
#    include(component_serial_manager)
#    include(driver_lpit)
#    include(driver_cmsis_lpi2c)
