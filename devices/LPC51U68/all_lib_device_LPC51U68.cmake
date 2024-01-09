list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flashiap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
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
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(driver_ili9341)
#    include(driver_lpc_rtc)
#    include(middleware_freertos-kernel_LPC51U68)
#    include(driver_flexcomm_spi)
#    include(component_ctimer_adapter)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_sctimer)
#    include(driver_ctimer)
#    include(driver_flashiap)
#    include(component_codec_i2c_LPC51U68)
#    include(component_osa_free_rtos_LPC51U68)
#    include(driver_reset)
#    include(driver_clock)
#    include(component_log)
#    include(driver_flexcomm_usart_dma)
#    include(driver_flexcomm_spi_dma)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_common)
#    include(driver_flexcomm_i2c_dma)
#    include(driver_lpc_iocon)
#    include(middleware_freertos-kernel_extension)
#    include(driver_power)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_lpc_crc)
#    include(device_startup)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(device_CMSIS)
#    include(driver_iap)
#    include(driver_flexcomm_i2s)
#    include(component_log_backend_debugconsole_LPC51U68)
#    include(driver_fro_calib)
#    include(middleware_usb_device_common_header)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_flexcomm_i2c)
#    include(driver_cmsis_flexcomm_spi)
#    include(utility_assert)
#    include(driver_ft6x06)
#    include(utilities_misc_utilities_LPC51U68)
#    include(component_lists)
#    include(utility_debug_console)
#    include(component_wm8904_adapter)
#    include(driver_gint)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_wm8904)
#    include(driver_flexcomm)
#    include(driver_flexcomm_spi_freertos)
#    include(driver_mrt)
#    include(component_osa)
#    include(middleware_usb_device_controller_driver_LPC51U68)
#    include(CMSIS_Include_core_cm)
#    include(driver_lpc_gpio)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_usb_device_ip3511fs)
#    include(driver_utick)
#    include(driver_cmsis_flexcomm_usart)
#    include(middleware_baremetal)
#    include(utility_debug_console_lite)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_pint)
#    include(device_system)
#    include(driver_lpc_adc)
#    include(utility_assert_lite)
#    include(component_flexcomm_i2c_adapter)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_fmeas)
#    include(driver_inputmux_connections)
#    include(middleware_usb_common_header)
#    include(component_serial_manager)
#    include(driver_inputmux)
