list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/anactrl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/casper
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hashcrypt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/prince
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rng_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_anactrl)
#    include(driver_power)
#    include(driver_lpc_rtc)
#    include(driver_hashcrypt)
#    include(driver_cdog)
#    include(driver_ctimer)
#    include(driver_utick)
#    include(component_usart_adapter)
#    include(driver_cmsis_flexcomm_spi)
#    include(component_lists)
#    include(driver_lpc_gpio)
#    include(driver_mrt)
#    include(device_system)
#    include(utility_debug_console)
#    include(driver_flexcomm)
#    include(driver_lpadc)
#    include(device_startup)
#    include(driver_pint)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_inputmux_connections)
#    include(driver_lpc_crc)
#    include(driver_mcan)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_wwdt)
#    include(driver_rng_1)
#    include(driver_cmp_1)
#    include(component_serial_manager_swo)
#    include(driver_flexcomm_i2c_dma)
#    include(utility_shell)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(middleware_mbedtls_port_ksdk)
#    include(utility_assert)
#    include(driver_flexcomm_usart_dma)
#    include(driver_iap1)
#    include(driver_flexcomm_spi)
#    include(driver_puf)
#    include(driver_prince)
#    include(middleware_freertos-kernel_extension)
#    include(driver_clock)
#    include(driver_sctimer)
#    include(driver_flexcomm_usart)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_lpc_iocon)
#    include(driver_flexcomm_i2c_freertos)
#    include(utility_debug_console_lite)
#    include(middleware_mbedtls_LPC55S06)
#    include(driver_ostimer)
#    include(utilities_misc_utilities_LPC55S06)
#    include(driver_common)
#    include(driver_gint)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_flexcomm_usart_freertos)
#    include(utility_assert_lite)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(driver_casper)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_freertos-kernel_LPC55S06)
#    include(driver_reset)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
