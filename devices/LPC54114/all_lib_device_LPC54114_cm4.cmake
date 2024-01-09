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
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_codec)
#    include(driver_lpc_rtc)
#    include(driver_flexcomm_spi)
#    include(component_ctimer_adapter)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(driver_sctimer)
#    include(driver_ctimer)
#    include(driver_flashiap)
#    include(middleware_freertos-kernel_heap_3)
#    include(driver_reset)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_clock)
#    include(driver_dmic_hwvad)
#    include(driver_flexcomm_usart_dma)
#    include(driver_flexcomm_spi_dma)
#    include(driver_common)
#    include(middleware_multicore_rpmsg_lite_LPC54114_cm4)
#    include(driver_flexcomm_i2c_dma)
#    include(driver_lpc_iocon)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Include_dsp)
#    include(driver_power)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(driver_lpc_crc)
#    include(driver_dmic)
#    include(middleware_multicore_erpc_common)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(device_CMSIS)
#    include(driver_iap)
#    include(CMSIS_Include_common)
#    include(middleware_multicore_erpc_doc)
#    include(driver_flexcomm_i2s)
#    include(middleware_multicore_mcmgr_lpc54114)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_bm)
#    include(middleware_usb_device_common_header)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
#    include(driver_flexcomm_i2c)
#    include(utility_assert)
#    include(component_lists)
#    include(utility_debug_console)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(component_wm8904_adapter)
#    include(device_system_LPC54114_cm4)
#    include(driver_gint)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_freertos)
#    include(utilities_misc_utilities_LPC54114_cm4)
#    include(driver_wm8904)
#    include(driver_flexcomm)
#    include(driver_flexcomm_spi_freertos)
#    include(component_codec_i2c_LPC54114_cm4)
#    include(driver_mrt)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(component_osa)
#    include(driver_lpc_gpio)
#    include(utility_incbin)
#    include(driver_flexcomm_usart_freertos)
#    include(driver_utick)
#    include(driver_mailbox)
#    include(middleware_baremetal)
#    include(utility_debug_console_lite)
#    include(driver_pint)
#    include(device_startup_LPC54114_cm4)
#    include(driver_lpc_adc)
#    include(utility_assert_lite)
#    include(driver_dmic_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
#    include(middleware_freertos-kernel_LPC54114_cm4)
#    include(driver_flexcomm_i2s_dma)
#    include(middleware_multicore_mcmgr)
#    include(driver_fmeas)
#    include(CMSIS_Include_core_cm4)
#    include(driver_inputmux_connections)
#    include(middleware_usb_common_header)
#    include(driver_mx25r_flash)
#    include(component_serial_manager)
#    include(driver_inputmux)
