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
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/edgefast_wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/common/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/eiq/tensorflow-lite/third_party/cmsis
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
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
#    include(utility_shell)
#    include(driver_flexcomm_i2c_freertos)
#    include(middleware_wifi_fwdnld_MIMXRT685S_cm33)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_cmsis_nn)
#    include(driver_ili9341)
#    include(driver_lpc_rtc)
#    include(middleware_mcuboot_bootutil)
#    include(driver_flexcomm_spi)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_fatfs_MIMXRT685S_cm33)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33)
#    include(middleware_usb_host_hid)
#    include(middleware_multicore_rpmsg_lite_MIMXRT685S_cm33)
#    include(middleware_eiq_audio_mimxrt685audevk)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(middleware_multicore_rpmsg_lite_mimxrt685audevk_freertos)
#    include(component_button_MIMXRT685S_cm33)
#    include(middleware_issdk_drivers_gpio_imxrt600)
#    include(CMSIS_DSP_Source)
#    include(middleware_sdmmc_host_usdhc)
#    include(component_log_backend_debugconsole_MIMXRT685S_cm33)
#    include(driver_sctimer)
#    include(middleware_mbedtls_MIMXRT685S_cm33)
#    include(driver_ctimer)
#    include(CMSIS_DSP_Include)
#    include(driver_flash_config_evkmimxrt685)
#    include(driver_lpadc)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_codec_i2c_MIMXRT685S_cm33)
#    include(middleware_wifi_MIMXRT685S_cm33)
#    include(driver_reset)
#    include(component_rt_gpio_adapter)
#    include(component_common_task)
#    include(component_osa_free_rtos_MIMXRT685S_cm33)
#    include(driver_clock)
#    include(middleware_eiq_deepviewrt_deps_json)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_flatbuffers)
#    include(middleware_usb_device_stack_external)
#    include(driver_flexcomm_usart_dma)
#    include(driver_powerquad_cmsis)
#    include(driver_acmp)
#    include(driver_flexcomm_spi_dma)
#    include(CMSIS_Driver_Include_USART)
#    include(middleware_lwip_apps_httpsrv_MIMXRT685S_cm33)
#    include(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
#    include(driver_otfad)
#    include(driver_common)
#    include(component_mflash_common)
#    include(driver_flexcomm_i2c_dma)
#    include(middleware_issdk_sensor_fxas21002)
#    include(middleware_multicore_erpc_eRPC_server)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_usb_device_ip3511hs_MIMXRT685S_cm33)
#    include(driver_i3c)
#    include(middleware_lwip_contrib_ping)
#    include(driver_power)
#    include(component_usart_adapter)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_usart)
#    include(component_i3c_adapter)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_trng)
#    include(driver_flexspi_dma)
#    include(middleware_edgefast_wifi_nxp)
#    include(driver_lpc_crc)
#    include(component_i3c_bus_adapter)
#    include(device_startup)
#    include(driver_dmic)
#    include(component_flexspi_nor_flash_adapter_rt685evk)
#    include(middleware_eiq_audio_evkmimxrt685)
#    include(middleware_multicore_erpc_common)
#    include(middleware_sdmmc_osa_bm)
#    include(component_mflash_mimxrt685audevk)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_lpc_dma)
#    include(driver_wwdt)
#    include(middleware_usb_device_controller_driver_MIMXRT685S_cm33)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_eiq_tensorflow_lite_micro_cmsis_nn)
#    include(driver_iap)
#    include(middleware_wifi_wifidriver_MIMXRT685S_cm33)
#    include(middleware_usb_host_common_header)
#    include(middleware_multicore_erpc_doc)
#    include(driver_casper)
#    include(middleware_sdmmc_common)
#    include(driver_flexcomm_i2s)
#    include(middleware_multicore_rpmsg_lite_mimxrt685audevk_bm)
#    include(component_serial_manager_swo)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_gemmlowp)
#    include(middleware_issdk_sensor_interface_common)
#    include(CMSIS_RTOS2_NonSecure)
#    include(driver_dsp)
#    include(middleware_usb_device_common_header)
#    include(driver_flash_config_mimxrt685audevk)
#    include(middleware_eiq_tensorflow_lite_micro_third_party_ruy)
#    include(middleware_multicore_rpmsg_lite_evkmimxrt685_bm)
#    include(middleware_sdmmc_sd)
#    include(driver_cmsis_flexcomm_i2c)
#    include(driver_flexcomm_i2c)
#    include(driver_cmsis_flexcomm_spi)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(driver_ft6x06)
#    include(driver_mpi_loader)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(middleware_lwip_apps_lwiperf_MIMXRT685S_cm33)
#    include(middleware_usb_host_ip3516hs_MIMXRT685S_cm33)
#    include(middleware_usb_host_video)
#    include(component_lists)
#    include(middleware_mbedtls_rt1)
#    include(middleware_usb_host_msd)
#    include(middleware_freertos-kernel_MIMXRT685S_cm33)
#    include(middleware_wifi_sdio-2)
#    include(utility_debug_console)
#    include(CMSIS_Device_API_OSTick)
#    include(component_cs42448_adapter)
#    include(component_wm8904_adapter)
#    include(driver_lpc_iopctl)
#    include(middleware_freertos-kernel_heap_4)
#    include(component_mflash_rt685)
#    include(middleware_usb_phy)
#    include(middleware_issdk_sensor_fxos8700)
#    include(driver_pca9420)
#    include(driver_wm8904)
#    include(driver_flexspi)
#    include(CMSIS_RTOS2_Common)
#    include(driver_flexcomm)
#    include(driver_cs42448)
#    include(driver_flexcomm_spi_freertos)
#    include(driver_usdhc)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33)
#    include(middleware_usb_host_stack_MIMXRT685S_cm33)
#    include(driver_mrt)
#    include(middleware_multicore_erpc_eRPC_port_stdlib)
#    include(middleware_usb_device_cdc_external)
#    include(middleware_eiq_deepviewrt_deps_stb)
#    include(component_osa)
#    include(CMSIS_Include_core_cm)
#    include(driver_lpc_gpio)
#    include(middleware_lwip_MIMXRT685S_cm33)
#    include(middleware_freertos-kernel_cm33_secure_port)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(driver_cache_cache64)
#    include(driver_flexcomm_usart_freertos)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(driver_icm42688p)
#    include(middleware_usb_host_printer)
#    include(middleware_wifi_cli_MIMXRT685S_cm33)
#    include(driver_utick)
#    include(driver_hashcrypt)
#    include(driver_powerquad)
#    include(driver_cmsis_flexcomm_usart)
#    include(component_lpc_gpio_adapter)
#    include(component_tfa9xxx_adapter)
#    include(component_timer_manager)
#    include(driver_sx1502)
#    include(middleware_baremetal)
#    include(middleware_edgefast_wifi)
#    include(middleware_eiq_deepviewrt)
#    include(middleware_eiq_tensorflow_lite_micro)
#    include(middleware_multicore_rpmsg_lite_bm)
#    include(middleware_multicore_rpmsg_lite_evkmimxrt685_freertos)
#    include(CMSIS_Driver_Include_Common)
#    include(component_mrt_adapter)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33)
#    include(middleware_sdmmc_osa_freertos)
#    include(utility_debug_console_lite)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_sdmmc_sdio)
#    include(driver_pint)
#    include(middleware_wifi_common_files)
#    include(utility_assert_lite)
#    include(driver_sema42)
#    include(middleware_eiq_deepviewrt_deps_flatcc)
#    include(driver_dmic_dma)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(component_flexcomm_i2c_adapter)
#    include(driver_tfa9xxx)
#    include(middleware_usb_host_phdc)
#    include(CMSIS_Device_API_RTOS2)
#    include(driver_flexcomm_i2s_dma)
#    include(component_mflash_file_MIMXRT685S_cm33)
#    include(middleware_freertos-kernel_secure_context)
#    include(driver_fmeas)
#    include(component_audio_flexcomm_i2s_dma_adapter)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(driver_inputmux_connections)
#    include(driver_ostimer)
#    include(middleware_wifi_sdio)
#    include(middleware_usb_common_header)
#    include(driver_puf)
#    include(middleware_lwip_apps_httpssrv_MIMXRT685S_cm33)
#    include(component_i3c_bus)
#    include(component_serial_manager)
#    include(utilities_misc_utilities_MIMXRT685S_cm33)
#    include(middleware_littlefs)
#    include(driver_inputmux)
