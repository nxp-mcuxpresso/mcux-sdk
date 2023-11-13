list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/lpc54xxx
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft5406
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gt911
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phylan8720a
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/video
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aes
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/emc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_lcdc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sha
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spifi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_ctimer)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_sdmmc_mmc)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_lwip_apps_lwiperf)
#    include(utility_shell)
#    include(driver_lpc_gpio)
#    include(device_system)
#    include(component_silicon_id_LPC54S018)
#    include(driver_lpc_crc)
#    include(driver_otp)
#    include(driver_spifi_dma)
#    include(middleware_baremetal)
#    include(component_audio_flexcomm_i2s_dma_adapter)
#    include(component_log_backend_ringbuffer)
#    include(driver_flexcomm_usart)
#    include(driver_lpc_lcdc)
#    include(middleware_lwip)
#    include(driver_codec)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_gint)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(driver_iap)
#    include(component_serial_manager)
#    include(middleware_lwip_apps_mqtt)
#    include(middleware_usb_device_cdc_external)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_flexcomm_i2s)
#    include(component_log_backend_debugconsole)
#    include(middleware_lwip_enet_ethernetif_LPC54S018)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_sdmmc_host_sdif_polling)
#    include(driver_pint)
#    include(middleware_lwip_contrib_ping)
#    include(driver_lpc_enet)
#    include(driver_sctimer)
#    include(middleware_lwip_usb_ethernetif)
#    include(middleware_lwip_apps_httpsrv)
#    include(driver_lpc_adc)
#    include(driver_flexcomm)
#    include(driver_phy-device-lan8720a)
#    include(device_startup)
#    include(component_panic)
#    include(utility_assert)
#    include(middleware_usb_device_ip3511hs_LPC54S018)
#    include(driver_aes)
#    include(driver_wm8904)
#    include(middleware_freertos-kernel_extension)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(middleware_usb_common_header)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_lpc_iocon)
#    include(driver_spifi)
#    include(driver_ft5406)
#    include(component_osa_bm)
#    include(middleware_usb_host_ohci)
#    include(middleware_usb_host_common_header)
#    include(component_mflash_file_LPC54S018)
#    include(driver_gt911)
#    include(component_mrt_adapter)
#    include(middleware_lwip_apps_httpd_support)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(middleware_freertos-kernel_LPC54S018)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_video-common)
#    include(driver_common)
#    include(middleware_usb_device_ip3511fs)
#    include(middleware_lwip_apps_mdns)
#    include(driver_sha)
#    include(middleware_sdmmc_sdio)
#    include(utility_debug_console_lite)
#    include(component_usart_adapter)
#    include(middleware_usb_host_msd)
#    include(driver_wwdt)
#    include(component_log)
#    include(component_mflash_lpc54xxx)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_phy-common_LPC54S018)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_inputmux_connections)
#    include(middleware_usb_host_printer)
#    include(driver_mcan)
#    include(middleware_fatfs_mmc)
#    include(driver_flexcomm_i2c_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(utility_assert_lite)
#    include(middleware_usb_host_audio)
#    include(driver_flexcomm_usart_freertos)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_ctimer_adapter)
#    include(driver_rit)
#    include(middleware_mbedtls_LPC54S018)
#    include(component_mflash_common)
#    include(component_lpc_gpio_adapter)
#    include(middleware_sdmmc_host_sdif)
#    include(middleware_usb_host_ip3516hs_LPC54S018)
#    include(driver_puf)
#    include(driver_power)
#    include(driver_emc)
#    include(middleware_fatfs_usb)
#    include(driver_dmic_dma)
#    include(middleware_usb_device_controller_driver_LPC54S018)
#    include(middleware_usb_device_common_header)
#    include(driver_lpc_rtc)
#    include(middleware_sdmmc_common)
#    include(middleware_fatfs_sd)
#    include(driver_dmic)
#    include(driver_cmsis_flexcomm_spi)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(driver_mrt)
#    include(component_codec_i2c_LPC54S018)
#    include(driver_rng)
#    include(middleware_fatfs_LPC54S018)
#    include(utilities_misc_utilities_LPC54S018)
#    include(component_osa)
#    include(driver_fmeas)
#    include(middleware_littlefs)
#    include(driver_sdif)
#    include(middleware_mbedtls_lpc2)
#    include(middleware_sdmmc_host_sdif_interrupt)
#    include(driver_flexcomm_usart_dma)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_flexcomm_i2c_freertos)
#    include(middleware_sdmmc_host_sdif_freertos)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_stack_LPC54S018)
#    include(driver_fro_calib)
#    include(component_wm8904_adapter)
#    include(middleware_usb_host_cdc)
#    include(driver_reset)
#    include(middleware_usb_device_stack_external)
