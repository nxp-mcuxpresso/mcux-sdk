list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
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
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(middleware_freertos-kernel_LPC54114_cm4)
#    include(middleware_baremetal)
#    include(driver_lpc_rtc)
#    include(driver_pint)
#    include(driver_ctimer)
#    include(utility_debug_console)
#    include(CMSIS_Include_dsp OPTIONAL)
#    include(component_usart_adapter)
#    include(utility_assert_lite)
#    include(middleware_multicore_erpc_eRPC_arbitrator)
#    include(driver_wwdt)
#    include(middleware_multicore_mcmgr_lpc54114)
#    include(middleware_usb_device_common_header)
#    include(component_lists)
#    include(driver_lpc_gpio)
#    include(driver_mrt)
#    include(utilities_misc_utilities_LPC54114_cm4)
#    include(middleware_freertos-kernel_heap_3)
#    include(driver_lpc_adc)
#    include(driver_flashiap)
#    include(driver_flexcomm)
#    include(middleware_multicore_mcmgr)
#    include(driver_flexcomm_usart_dma)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_bm)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_common)
#    include(driver_flexcomm_i2s_dma)
#    include(component_osa)
#    include(driver_fmeas)
#    include(driver_mx25r_flash)
#    include(driver_lpc_crc)
#    include(utility_assert)
#    include(middleware_multicore_erpc_eRPC_client)
#    include(component_codec_i2c_LPC54114_cm4)
#    include(middleware_freertos-kernel_extension)
#    include(driver_flexcomm_i2c_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(utility_incbin)
#    include(middleware_multicore_rpmsg_lite_lpc5411x_freertos)
#    include(device_system_LPC54114_cm4)
#    include(middleware_usb_common_header)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_multicore_rpmsg_lite_LPC54114_cm4)
#    include(driver_dmic)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_shell)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_master_c_wrapper)
#    include(driver_sctimer)
#    include(driver_flexcomm_usart)
#    include(device_CMSIS)
#    include(component_ctimer_adapter)
#    include(driver_lpc_iocon)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_dmic_hwvad)
#    include(driver_codec)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_master_c_wrapper)
#    include(driver_common)
#    include(driver_gint)
#    include(middleware_multicore_erpc_eRPC_port_freertos)
#    include(middleware_multicore_erpc_eRPC_rpmsg_lite_transport)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(device_startup_LPC54114_cm4)
#    include(driver_inputmux)
#    include(driver_inputmux_connections)
#    include(driver_flexcomm_i2c)
#    include(driver_iap)
#    include(component_serial_manager)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_multicore_erpc_doc)
#    include(driver_power)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(component_wm8904_adapter)
#    include(driver_flexcomm_i2s)
#    include(driver_mailbox)
#    include(driver_wm8904)
#    include(driver_reset)
#    include(driver_flexcomm_spi_dma)
#    include(driver_dmic_dma)
