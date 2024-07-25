list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/RTX/Library
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/els_pkc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/lpc55s3x
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/lpc55s3x_flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus
    ${CMAKE_CURRENT_LIST_DIR}/../../components/icm42688p
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/cache64
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hscmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/irtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/itrc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_freqme
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/opamp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf_v3
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sysctl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/vref_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/unity
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(component_mflash_lpc55s3x)
#    include(driver_cdog)
#    include(driver_ctimer)
#    include(driver_lpc_gpio)
#    include(device_system)
#    include(component_els_pkc_key)
#    include(driver_lpadc)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(component_els_pkc_flow_protection)
#    include(driver_opamp)
#    include(driver_aoi)
#    include(component_serial_manager_swo)
#    include(component_els_pkc_param_integrity)
#    include(middleware_baremetal)
#    include(driver_lpc_freqme)
#    include(driver_flexcomm_usart)
#    include(driver_i3c)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_ostimer)
#    include(driver_gint)
#    include(driver_cmsis_flexcomm_i2c)
#    include(middleware_freertos-kernel_LPC55S36)
#    include(component_els_pkc_secure_counter)
#    include(driver_inputmux)
#    include(component_codec_i2c_LPC55S36)
#    include(driver_flexcomm_i2c)
#    include(component_serial_manager)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_i2s)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_freertos-kernel_cm33_secure_port)
#    include(CMSIS_DSP_Library OPTIONAL)
#    include(driver_ili9341)
#    include(driver_pint)
#    include(driver_sctimer)
#    include(CMSIS_RTOS2_Common OPTIONAL)
#    include(driver_flashiap)
#    include(driver_flexcomm)
#    include(device_startup)
#    include(component_i3c_bus_adapter)
#    include(utility_assert)
#    include(component_mflash_lpc55s3x_flexspi)
#    include(driver_wm8904)
#    include(middleware_freertos-kernel_extension)
#    include(component_els_pkc_rsa)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(component_pkc)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(middleware_multicore_erpc_eRPC_spi_slave_transport)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_lpc_iocon)
#    include(middleware_multicore_erpc_doc)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_common)
#    include(driver_common)
#    include(driver_cache_cache64)
#    include(driver_flexspi_dma)
#    include(driver_vref_1)
#    include(driver_mem_interface)
#    include(component_els_pkc_common)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(component_els_pkc_pre_processor)
#    include(component_usart_adapter)
#    include(driver_wwdt)
#    include(utilities_unity)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_inputmux_connections)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_mcan)
#    include(driver_cmp_1)
#    include(driver_flexcomm_i2c_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(utility_assert_lite)
#    include(utility_shell)
#    include(middleware_multicore_erpc_eRPC_i2c_slave_c_wrapper)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_i2c_slave_transport)
#    include(component_mflash_common)
#    include(driver_crc)
#    include(component_css)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(driver_icm42688p)
#    include(driver_puf_v3)
#    include(driver_sysctl)
#    include(driver_enc)
#    include(driver_power)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(driver_dac_1)
#    include(driver_dmic_dma)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(component_els_pkc_math)
#    include(driver_flexspi)
#    include(driver_dmic)
#    include(driver_cmsis_flexcomm_spi)
#    include(component_lists)
#    include(component_i3c_bus)
#    include(driver_mrt)
#    include(component_els_pkc_mac)
#    include(driver_irtc)
#    include(CMSIS_RTOS2_NonSecure OPTIONAL)
#    include(component_els_pkc_ecc)
#    include(component_osa)
#    include(component_css_hash)
#    include(driver_itrc)
#    include(middleware_freertos-kernel_secure_context)
#    include(driver_flexcomm_usart_dma)
#    include(middleware_multicore_erpc_eRPC_spi_slave_c_wrapper)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_runbootloader)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_powerquad)
#    include(component_els_pkc_memory)
#    include(driver_flexcomm_usart_freertos)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(driver_pwm)
#    include(component_wm8904_adapter)
#    include(component_els_pkc_session)
#    include(driver_reset)
#    include(driver_hscmp)
#    include(driver_ft6x06)
