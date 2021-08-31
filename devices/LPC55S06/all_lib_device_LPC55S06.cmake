list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_driver_anactrl	driver_anactrl)
include_ifdef(CONFIG_USE_driver_power	driver_power)
include_ifdef(CONFIG_USE_driver_lpc_rtc	driver_lpc_rtc)
include_ifdef(CONFIG_USE_driver_hashcrypt	driver_hashcrypt)
include_ifdef(CONFIG_USE_driver_cdog	driver_cdog)
include_ifdef(CONFIG_USE_driver_ctimer	driver_ctimer)
include_ifdef(CONFIG_USE_driver_utick	driver_utick)
include_ifdef(CONFIG_USE_component_usart_adapter	component_usart_adapter)
include_ifdef(CONFIG_USE_driver_wwdt	driver_wwdt)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_lpc_gpio	driver_lpc_gpio)
include_ifdef(CONFIG_USE_driver_mrt	driver_mrt)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_driver_flexcomm	driver_flexcomm)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_pint	driver_pint)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_cm33_nonsecure_port	middleware_freertos-kernel_cm33_nonsecure_port)
include_ifdef(CONFIG_USE_driver_inputmux_connections	driver_inputmux_connections)
include_ifdef(CONFIG_USE_driver_lpc_crc	driver_lpc_crc)
include_ifdef(CONFIG_USE_driver_mcan	driver_mcan)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_driver_rng_1	driver_rng_1)
include_ifdef(CONFIG_USE_driver_cmp_1	driver_cmp_1)
include_ifdef(CONFIG_USE_component_serial_manager_swo	component_serial_manager_swo)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_dma	driver_flexcomm_i2c_dma)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_dma	driver_flexcomm_usart_dma)
include_ifdef(CONFIG_USE_driver_iap1	driver_iap1)
include_ifdef(CONFIG_USE_driver_flexcomm_spi	driver_flexcomm_spi)
include_ifdef(CONFIG_USE_driver_puf	driver_puf)
include_ifdef(CONFIG_USE_driver_prince	driver_prince)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_driver_sctimer	driver_sctimer)
include_ifdef(CONFIG_USE_driver_flexcomm_usart	driver_flexcomm_usart)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_lpc_iocon	driver_lpc_iocon)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_freertos	driver_flexcomm_i2c_freertos)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_ostimer	driver_ostimer)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_gint	driver_gint)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_freertos	driver_flexcomm_usart_freertos)
include_ifdef(CONFIG_USE_driver_inputmux	driver_inputmux)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c	driver_flexcomm_i2c)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_casper	driver_casper)
include_ifdef(CONFIG_USE_driver_lpc_dma	driver_lpc_dma)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_LPC55S06	middleware_freertos-kernel_LPC55S06)
include_ifdef(CONFIG_USE_driver_reset	driver_reset)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_dma	driver_flexcomm_spi_dma)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_freertos	driver_flexcomm_spi_freertos)
