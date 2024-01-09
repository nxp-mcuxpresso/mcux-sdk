list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1020/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/audio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/exception_handling
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1021
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nor/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ft6x06
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/ili9341
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
    ${CMAKE_CURRENT_LIST_DIR}/../../components/rtt
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/rt10xx
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/wifi_bt_module
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_12b1msps_sar
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/bee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv7-m7
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcdc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexram
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kpp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ocotp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qtmr_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtwdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/semc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/src
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempmon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbarb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/issdk
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi_nxp
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/azure-rtos
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(utility_shell)
#    include(driver_codec)
#    include(component_osa_bm)
#    include(driver_ili9341)
#    include(middleware_lwip_contrib_tcpecho)
#    include(CMSIS_Driver_Include_Ethernet)
#    include(middleware_wifi_MIMXRT1021)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(CMSIS_Driver_Include_I2C)
#    include(middleware_azure_rtos_ux_template_MIMXRT1021)
#    include(component_lpi2c_adapter)
#    include(middleware_usb_host_hid)
#    include(middleware_wifi_fwdnld_MIMXRT1021)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1021)
#    include(driver_gpt)
#    include(driver_lpi2c_edma)
#    include(middleware_sdmmc_osa_azurertos)
#    include(middleware_usb_host_cdc_rndis)
#    include(driver_kpp)
#    include(CMSIS_DSP_Source)
#    include(middleware_sdmmc_host_usdhc)
#    include(driver_src)
#    include(component_wm8960_adapter)
#    include(driver_flexspi_edma)
#    include(driver_dmamux)
#    include(driver_lpuart)
#    include(driver_pit)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_exception_handling_cm7)
#    include(driver_phy-common_MIMXRT1021)
#    include(middleware_freertos-kernel_MIMXRT1021)
#    include(driver_clock)
#    include(driver_lpuart_edma)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1021)
#    include(middleware_fatfs_sd)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(driver_bee)
#    include(component_lpuart_adapter)
#    include(middleware_usb_device_stack_external)
#    include(middleware_sdmmc_mmc)
#    include(middleware_lwip_apps_lwiperf_MIMXRT1021)
#    include(driver_cmsis_lpuart)
#    include(driver_lpi2c_freertos)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(driver_lpspi)
#    include(driver_iomuxc)
#    include(driver_common)
#    include(driver_flexcan)
#    include(component_mflash_common)
#    include(middleware_lwip_apps_httpsrv_MIMXRT1021)
#    include(driver_cmp)
#    include(middleware_issdk_sensor_fxas21002)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_lwip_MIMXRT1021)
#    include(middleware_lwip_contrib_ping)
#    include(driver_cmsis_enet)
#    include(component_codec_i2c_MIMXRT1021)
#    include(middleware_azure_rtos_tx_template_MIMXRT1021)
#    include(middleware_lwip_apps_mdns_MIMXRT1021)
#    include(component_serial_manager_uart)
#    include(driver_pwm)
#    include(driver_flexio_i2s)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(driver_xbarb)
#    include(driver_aoi)
#    include(driver_trng)
#    include(middleware_mbedtls_MIMXRT1021)
#    include(device_startup)
#    include(middleware_sdmmc_osa_bm)
#    include(component_silicon_id_rt10xx)
#    include(driver_phy-device-ksz8081)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_snvs_hp)
#    include(driver_xip_device)
#    include(device_CMSIS)
#    include(middleware_fatfs_usb)
#    include(middleware_usb_host_common_header)
#    include(driver_rtwdog)
#    include(middleware_sdmmc_common)
#    include(component_serial_manager_swo)
#    include(middleware_issdk_sensor_interface_common)
#    include(middleware_lwip_apps_httpd_support)
#    include(middleware_usb_host_ehci_MIMXRT1021)
#    include(component_audio_sai_edma_adapter)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_sdmmc_sd)
#    include(driver_gpc_1)
#    include(driver_cmsis_lpspi)
#    include(middleware_azure_rtos_fx_template_MIMXRT1021)
#    include(component_serial_manager_usb_cdc)
#    include(utility_assert)
#    include(component_mflash_rt1020)
#    include(driver_soc_flexram_allocate)
#    include(middleware_wifi_cli_MIMXRT1021)
#    include(driver_enc)
#    include(utilities_misc_utilities_MIMXRT1021)
#    include(driver_adc_12b1msps_sar)
#    include(driver_ft6x06)
#    include(driver_nor_flash-controller-flexspi)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_lpspi_freertos)
#    include(component_lists)
#    include(middleware_usb_host_msd)
#    include(driver_qtmr_1)
#    include(middleware_wifi_sdio-2)
#    include(driver_dcp)
#    include(middleware_usb_device_controller_driver_MIMXRT1021)
#    include(driver_wm8960)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_debug_console)
#    include(driver_dcdc_1)
#    include(middleware_azure_rtos_tx)
#    include(middleware_lwip_usb_ethernetif_MIMXRT1021)
#    include(middleware_usb_phy)
#    include(component_igpio_adapter)
#    include(middleware_mbedtls_rt)
#    include(middleware_azure_rtos_nxd)
#    include(middleware_issdk_sensor_fxos8700)
#    include(middleware_fatfs_MIMXRT1021)
#    include(driver_flexspi)
#    include(driver_rtt_MIMXRT1021)
#    include(driver_flexio_uart)
#    include(driver_usdhc)
#    include(driver_lpuart_freertos)
#    include(driver_flexram)
#    include(driver_adc_etc)
#    include(driver_ewm)
#    include(middleware_azure_rtos_lx)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1021)
#    include(middleware_azure_rtos_ux)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1021)
#    include(middleware_wifi_wifidriver_MIMXRT1021)
#    include(middleware_usb_device_cdc_external)
#    include(component_osa)
#    include(middleware_issdk_drivers_gpio_imx)
#    include(CMSIS_Include_core_cm)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1021)
#    include(driver_enet)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(component_osa_free_rtos_MIMXRT1021)
#    include(middleware_usb_host_stack_MIMXRT1021)
#    include(middleware_usb_host_printer)
#    include(driver_lpspi_edma)
#    include(middleware_usb_device_ehci_MIMXRT1021)
#    include(middleware_lwip_apps_mqtt)
#    include(driver_edma_MIMXRT1021)
#    include(component_osa_thread)
#    include(driver_snvs_lp)
#    include(driver_tempmon)
#    include(middleware_baremetal)
#    include(utility_debug_console_lite)
#    include(driver_cache_armv7_m7)
#    include(component_mflash_file_MIMXRT1021)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_flexio_spi_edma)
#    include(driver_lpi2c)
#    include(middleware_sdmmc_osa_freertos)
#    include(middleware_usb_host_audio)
#    include(middleware_usb_host_cdc)
#    include(middleware_sdmmc_sdio)
#    include(middleware_wifi_common_files)
#    include(component_silicon_id_MIMXRT1021)
#    include(driver_sai_edma)
#    include(driver_semc)
#    include(driver_nor_flash-common)
#    include(component_gpt_adapter)
#    include(device_system)
#    include(middleware_sdmmc_host_usdhc_azurertos)
#    include(utility_assert_lite)
#    include(middleware_usb_host_phdc)
#    include(component_wifi_bt_module_tx_pwr_limits)
#    include(driver_flexio_i2s_edma)
#    include(driver_romapi)
#    include(middleware_azure_rtos_azure_iot)
#    include(driver_igpio)
#    include(driver_sai)
#    include(driver_flexio_uart_edma)
#    include(driver_xbara)
#    include(driver_flexio)
#    include(middleware_issdk_drivers_cmsis_drivers)
#    include(middleware_wifi_sdio)
#    include(driver_flexio_spi)
#    include(component_log_backend_debugconsole_MIMXRT1021)
#    include(middleware_usb_common_header)
#    include(driver_wdog01)
#    include(component_serial_manager)
#    include(middleware_azure_rtos_fx)
#    include(driver_xip_board_evkmimxrt1020)
#    include(driver_fxos8700cq)
#    include(driver_cmsis_lpi2c)
