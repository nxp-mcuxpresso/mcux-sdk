list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/mx25r_flash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mailbox
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_middleware_freertos-kernel_LPC54114_cm4	middleware_freertos-kernel_LPC54114_cm4)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_driver_lpc_rtc	driver_lpc_rtc)
include_ifdef(CONFIG_USE_driver_pint	driver_pint)
include_ifdef(CONFIG_USE_driver_ctimer	driver_ctimer)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_CMSIS_Include_dsp	CMSIS_Include_dsp)
include_ifdef(CONFIG_USE_component_usart_adapter	component_usart_adapter)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_arbitrator	middleware_multicore_erpc_eRPC_arbitrator)
include_ifdef(CONFIG_USE_driver_wwdt	driver_wwdt)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr_lpc54114	middleware_multicore_mcmgr_lpc54114)
include_ifdef(CONFIG_USE_middleware_usb_device_common_header	middleware_usb_device_common_header)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_lpc_gpio	driver_lpc_gpio)
include_ifdef(CONFIG_USE_driver_mrt	driver_mrt)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_3	middleware_freertos-kernel_heap_3)
include_ifdef(CONFIG_USE_driver_lpc_adc	driver_lpc_adc)
include_ifdef(CONFIG_USE_driver_flashiap	driver_flashiap)
include_ifdef(CONFIG_USE_driver_flexcomm	driver_flexcomm)
include_ifdef(CONFIG_USE_middleware_multicore_mcmgr	middleware_multicore_mcmgr)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_dma	driver_flexcomm_usart_dma)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_lpc5411x_bm	middleware_multicore_rpmsg_lite_lpc5411x_bm)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_common	middleware_multicore_erpc_common)
include_ifdef(CONFIG_USE_driver_flexcomm_i2s_dma	driver_flexcomm_i2s_dma)
include_ifdef(CONFIG_USE_component_osa	component_osa)
include_ifdef(CONFIG_USE_driver_fmeas	driver_fmeas)
include_ifdef(CONFIG_USE_driver_mx25r_flash	driver_mx25r_flash)
include_ifdef(CONFIG_USE_driver_lpc_crc	driver_lpc_crc)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_client	middleware_multicore_erpc_eRPC_client)
include_ifdef(CONFIG_USE_component_codec_i2c_LPC54114_cm4	component_codec_i2c_LPC54114_cm4)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_dma	driver_flexcomm_i2c_dma)
include_ifdef(CONFIG_USE_component_flexcomm_i2c_adapter	component_flexcomm_i2c_adapter)
include_ifdef(CONFIG_USE_utility_incbin	utility_incbin)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_lpc5411x_freertos	middleware_multicore_rpmsg_lite_lpc5411x_freertos)
include_ifdef(CONFIG_USE_device_system_LPC54114_cm4	device_system_LPC54114_cm4)
include_ifdef(CONFIG_USE_middleware_usb_common_header	middleware_usb_common_header)
include_ifdef(CONFIG_USE_driver_flexcomm_spi	driver_flexcomm_spi)
include_ifdef(CONFIG_USE_driver_utick	driver_utick)
include_ifdef(CONFIG_USE_driver_dmic	driver_dmic)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
include_ifdef(CONFIG_USE_driver_sctimer	driver_sctimer)
include_ifdef(CONFIG_USE_driver_flexcomm_usart	driver_flexcomm_usart)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_component_ctimer_adapter	component_ctimer_adapter)
include_ifdef(CONFIG_USE_driver_lpc_iocon	driver_lpc_iocon)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_freertos	driver_flexcomm_i2c_freertos)
include_ifdef(CONFIG_USE_driver_dmic_hwvad	driver_dmic_hwvad)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm4	CMSIS_Include_core_cm4)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper	middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
include_ifdef(CONFIG_USE_CMSIS_Include_common	CMSIS_Include_common)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_gint	driver_gint)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_freertos	middleware_multicore_erpc_eRPC_port_freertos)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_transport	middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_freertos	driver_flexcomm_usart_freertos)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_eRPC_port_stdlib	middleware_multicore_erpc_eRPC_port_stdlib)
include_ifdef(CONFIG_USE_device_startup_LPC54114_cm4	device_startup_LPC54114_cm4)
include_ifdef(CONFIG_USE_driver_inputmux	driver_inputmux)
include_ifdef(CONFIG_USE_driver_inputmux_connections	driver_inputmux_connections)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c	driver_flexcomm_i2c)
include_ifdef(CONFIG_USE_driver_iap	driver_iap)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_freertos	driver_flexcomm_spi_freertos)
include_ifdef(CONFIG_USE_middleware_multicore_erpc_doc	middleware_multicore_erpc_doc)
include_ifdef(CONFIG_USE_driver_power	driver_power)
include_ifdef(CONFIG_USE_driver_lpc_dma	driver_lpc_dma)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_component_wm8904_adapter	component_wm8904_adapter)
include_ifdef(CONFIG_USE_driver_flexcomm_i2s	driver_flexcomm_i2s)
include_ifdef(CONFIG_USE_driver_mailbox	driver_mailbox)
include_ifdef(CONFIG_USE_driver_wm8904	driver_wm8904)
include_ifdef(CONFIG_USE_driver_reset	driver_reset)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_dma	driver_flexcomm_spi_dma)
include_ifdef(CONFIG_USE_driver_dmic_dma	driver_dmic_dma)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
