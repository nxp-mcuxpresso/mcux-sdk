list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/RTX/Library
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt685/flash_config
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/mimxrt685audevk/flash_config
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42448
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/tfa9xxx
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt685
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt685audevk
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i3c_bus
    ${CMAKE_CURRENT_LIST_DIR}/../../components/icm42688p
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/internal_flash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/mpi_loader
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/pca9420
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/sx1502
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/cache64
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/casper
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcomm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/fmeas
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/hashcrypt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i3c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iopctl
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otfad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../components/edgefast_wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/common/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite/third_party/cmsis
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/littlefs
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mcuboot_opensource/boot/bootutil
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(middleware_wifi_fwdnld_MIMXRT685S_cm33)
#    include(driver_ctimer)
#    include(driver_sema42)
#    include(component_flexspi_nor_flash_adapter_rt685evk)
#    include(middleware_lwip_apps_lwiperf)
#    include(middleware_usb_host_stack_MIMXRT685S_cm33)
#    include(driver_lpc_gpio)
#    include(middleware_wifi)
#    include(component_rt_gpio_adapter)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(middleware_usb_device_ip3511hs_MIMXRT685S_cm33)
#    include(component_mflash_common)
#    include(middleware_multicore_rpmsg_lite_bm)
#    include(middleware_baremetal)
#    include(component_cs42448_adapter)
#    include(component_audio_flexcomm_i2s_dma_adapter)
#    include(component_mflash_mimxrt685audevk)
#    include(middleware_sdmmc_host_usdhc)
#    include(middleware_mcuboot_bootutil)
#    include(component_log_backend_ringbuffer)
#    include(driver_flexcomm_usart)
#    include(driver_i3c)
#    include(middleware_lwip)
#    include(driver_sx1502)
#    include(driver_codec)
#    include(driver_ostimer)
#    include(driver_cmsis_flexcomm_i2c)
#    include(middleware_eiq_deepviewrt_deps_stb)
#    include(middleware_mbedtls_rt1)
#    include(middleware_mbedtls_MIMXRT685S_cm33)
#    include(component_mflash_rt685)
#    include(driver_inputmux)
#    include(CMSIS_RTOS2_Common OPTIONAL)
#    include(driver_flexcomm_i2c)
#    include(driver_iap)
#    include(component_serial_manager)
#    include(middleware_edgefast_wifi_nxp)
#    include(middleware_usb_device_cdc_external)
#    include(component_i3c_bus_adapter)
#    include(component_serial_manager_uart)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_flexcomm_i2s)
#    include(component_log_backend_debugconsole)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_freertos-kernel_cm33_secure_port)
#    include(middleware_wifi_common_files)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(driver_ili9341)
#    include(driver_pint)
#    include(middleware_lwip_contrib_ping)
#    include(driver_sctimer)
#    include(middleware_usb_device_common_header)
#    include(middleware_edgefast_wifi)
#    include(middleware_lwip_apps_httpsrv)
#    include(driver_flexcomm)
#    include(utility_shell)
#    include(device_startup)
#    include(driver_power)
#    include(middleware_eiq_deepviewrt_deps_flatcc)
#    include(component_panic)
#    include(driver_lpc_dma)
#    include(driver_dsp)
#    include(utility_assert)
#    include(driver_lpadc)
#    include(middleware_wifi_wifidriver)
#    include(driver_wm8904)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(middleware_eiq_audio_evkmimxrt685)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_cmsis_nn)
#    include(middleware_usb_common_header)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager_usb_cdc)
#    include(driver_clock)
#    include(device_CMSIS)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_multicore_erpc_doc)
#    include(utility_debug_console_lite)
#    include(middleware_multicore_erpc_common)
#    include(component_osa_bm)
#    include(component_codec_i2c_MIMXRT685S_cm33)
#    include(middleware_usb_host_common_header)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(driver_cache_cache64)
#    include(driver_flexspi_dma)
#    include(middleware_fatfs_MIMXRT685S_cm33)
#    include(middleware_multicore_rpmsg_lite_mimxrt685audevk_freertos)
#    include(driver_inputmux_connections)
#    include(component_osa_free_rtos)
#    include(middleware_multicore_rpmsg_lite_evkmimxrt685_freertos)
#    include(middleware_sdmmc_sd)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_lpc_crc)
#    include(middleware_wifi_sdio-2)
#    include(driver_hashcrypt)
#    include(middleware_sdmmc_sdio)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(component_usart_adapter)
#    include(driver_mpi_loader)
#    include(middleware_usb_host_msd)
#    include(driver_wwdt)
#    include(middleware_multicore_rpmsg_lite_MIMXRT685S_cm33)
#    include(component_mflash_file_MIMXRT685S_cm33)
#    include(component_log)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_cmsis_flexcomm_usart)
#    include(driver_flexcomm_i2s_dma)
#    include(component_mrt_adapter)
#    include(middleware_usb_host_printer)
#    include(middleware_eiq_audio_mimxrt685audevk)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_flexcomm_i2c_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(utility_assert_lite)
#    include(middleware_freertos-kernel_MIMXRT685S_cm33)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(driver_otfad)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33)
#    include(middleware_wifi_cli)
#    include(driver_flash_config_mimxrt685audevk)
#    include(component_lpc_gpio_adapter)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_cmsis_flexcomm_spi)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(driver_icm42688p)
#    include(middleware_usb_device_controller_driver_MIMXRT685S_cm33)
#    include(driver_puf)
#    include(driver_tfa9xxx)
#    include(driver_casper)
#    include(middleware_usb_phy)
#    include(CMSIS_DSP_Include OPTIONAL)
#    include(CMSIS_Device_API_RTOS2 OPTIONAL)
#    include(middleware_lwip_apps_httpssrv)
#    include(middleware_fatfs_usb)
#    include(driver_dmic_dma)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(driver_lpc_rtc)
#    include(middleware_sdmmc_common)
#    include(middleware_fatfs_sd)
#    include(driver_flexspi)
#    include(driver_dmic)
#    include(component_timer_manager)
#    include(driver_flash_config_evkmimxrt685)
#    include(component_common_task)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(component_i3c_bus)
#    include(driver_mrt)
#    include(driver_acmp)
#    include(CMSIS_RTOS2_NonSecure OPTIONAL)
#    include(component_osa)
#    include(driver_fmeas)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33)
#    include(middleware_littlefs)
#    include(middleware_usb_host_ip3516hs_MIMXRT685S_cm33)
#    include(middleware_wifi_sdio)
#    include(middleware_freertos-kernel_secure_context)
#    include(component_i3c_adapter)
#    include(driver_flexcomm_usart_dma)
#    include(utilities_misc_utilities_MIMXRT685S_cm33)
#    include(driver_pca9420)
#    include(component_tfa9xxx_adapter)
#    include(component_button_MIMXRT685S_cm33)
#    include(middleware_multicore_rpmsg_lite_evkmimxrt685_bm)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(driver_cs42448)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_powerquad_cmsis)
#    include(middleware_eiq_deepviewrt_deps_json)
#    include(driver_powerquad)
#    include(middleware_usb_host_phdc)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_usb_host_audio)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(driver_lpc_iopctl)
#    include(CMSIS_Device_API_OSTick OPTIONAL)
#    include(middleware_multicore_rpmsg_lite_mimxrt685audevk_bm)
#    include(driver_trng)
#    include(driver_usdhc)
#    include(middleware_eiq_deepviewrt)
#    include(component_wm8904_adapter)
#    include(driver_mu)
#    include(driver_reset)
#    include(middleware_usb_device_stack_external)
#    include(driver_ft6x06)
