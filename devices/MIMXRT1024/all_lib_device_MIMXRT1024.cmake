list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1024/xip
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
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mimxrt1024
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/usb
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
#    include(middleware_usb_host_cdc_rndis)
#    include(middleware_azure_rtos_fx_template_MIMXRT1024)
#    include(driver_lpuart_freertos)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024)
#    include(middleware_sdmmc_osa_bm)
#    include(middleware_sdmmc_mmc)
#    include(driver_dmamux)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_lwip_apps_lwiperf)
#    include(driver_nor_flash-controller-flexspi)
#    include(driver_cmsis_lpuart)
#    include(middleware_azure_rtos_nxd)
#    include(device_system)
#    include(driver_snvs_lp)
#    include(driver_flexio_uart)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1024)
#    include(driver_wm8960)
#    include(driver_ewm)
#    include(middleware_usb_host_ehci_MIMXRT1024)
#    include(component_codec_i2c_MIMXRT1024)
#    include(driver_flexio)
#    include(driver_aoi)
#    include(driver_bee)
#    include(driver_flexio_i2c_master)
#    include(middleware_baremetal)
#    include(middleware_sdmmc_host_usdhc)
#    include(component_log_backend_ringbuffer)
#    include(driver_lpuart_edma)
#    include(driver_lpspi_edma)
#    include(driver_wdog01)
#    include(driver_flexio_uart_edma)
#    include(driver_ocotp)
#    include(driver_codec)
#    include(utilities_misc_utilities_MIMXRT1024)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_xip_device)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_serial_manager)
#    include(driver_phy-common_MIMXRT1024)
#    include(driver_pit)
#    include(middleware_freertos-kernel_MIMXRT1024)
#    include(middleware_azure_rtos_ux)
#    include(component_serial_manager_uart)
#    include(driver_lpspi_freertos)
#    include(middleware_mbedtls_port_ksdk)
#    include(component_log_backend_debugconsole)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(driver_ili9341)
#    include(driver_tempmon)
#    include(middleware_lwip_contrib_ping)
#    include(middleware_azure_rtos_nxd_template_MIMXRT1024)
#    include(component_lpuart_adapter)
#    include(driver_lpi2c_edma)
#    include(middleware_lwip_usb_ethernetif)
#    include(middleware_lwip_apps_mqtt)
#    include(middleware_lwip_apps_httpsrv)
#    include(middleware_usb_device_cdc_external)
#    include(driver_cmsis_enet)
#    include(utility_shell)
#    include(device_startup)
#    include(middleware_azure_rtos_tx_template_MIMXRT1024)
#    include(component_panic)
#    include(driver_phy-device-ksz8081)
#    include(driver_usdhc)
#    include(driver_gpt)
#    include(middleware_usb_host_stack_MIMXRT1024)
#    include(driver_enet)
#    include(driver_rtwdog)
#    include(middleware_freertos-kernel_extension)
#    include(component_serial_manager_swo)
#    include(driver_edma_MIMXRT1024)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_nor_flash-common)
#    include(middleware_usb_common_header)
#    include(component_silicon_id_MIMXRT1024)
#    include(driver_cmsis_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_soc_flexram_allocate)
#    include(component_serial_manager_usb_cdc)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(device_CMSIS)
#    include(driver_romapi)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_azure_rtos_fx)
#    include(component_osa_bm)
#    include(middleware_usb_device_controller_driver_MIMXRT1024)
#    include(driver_adc_12b1msps_sar)
#    include(middleware_usb_host_cdc)
#    include(driver_common)
#    include(middleware_fatfs_usb)
#    include(driver_kpp)
#    include(component_exception_handling_cm7)
#    include(middleware_lwip_apps_httpd_support)
#    include(component_osa_free_rtos)
#    include(driver_adc_etc)
#    include(component_lpi2c_adapter)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_dcdc_1)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT1024)
#    include(middleware_usb_device_ehci_MIMXRT1024)
#    include(middleware_lwip_apps_mdns)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(driver_snvs_hp)
#    include(middleware_usb_host_msd)
#    include(driver_lpspi)
#    include(driver_flexspi_edma)
#    include(component_gpt_adapter)
#    include(middleware_usb_host_common_header)
#    include(component_log)
#    include(driver_xip_board_evkmimxrt1024)
#    include(driver_clock)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(component_audio_sai_edma_adapter)
#    include(middleware_usb_host_phdc)
#    include(middleware_usb_host_printer)
#    include(driver_iomuxc)
#    include(middleware_usb_device_common_header)
#    include(driver_flexram)
#    include(utility_assert_lite)
#    include(driver_semc)
#    include(driver_xbarb)
#    include(driver_xbara)
#    include(middleware_usb_host_audio)
#    include(component_mflash_file_MIMXRT1024)
#    include(driver_flexcan)
#    include(utility_debug_console)
#    include(middleware_usb_host_hid)
#    include(component_osa_thread)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1024)
#    include(component_mflash_common)
#    include(driver_cmsis_lpspi)
#    include(middleware_azure_rtos_azure_iot)
#    include(component_wm8960_adapter)
#    include(component_mflash_rt1024)
#    include(driver_enc)
#    include(middleware_usb_phy)
#    include(driver_sai_edma)
#    include(driver_dcp)
#    include(component_silicon_id_rt10xx)
#    include(middleware_fatfs_sd)
#    include(middleware_sdmmc_osa_azurertos)
#    include(driver_flexspi)
#    include(driver_flexio_spi_edma)
#    include(driver_rtt_MIMXRT1024)
#    include(middleware_mbedtls_MIMXRT1024)
#    include(driver_lpi2c_freertos)
#    include(driver_qtmr_1)
#    include(driver_trng)
#    include(driver_gpc_1)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_cmp)
#    include(component_igpio_adapter)
#    include(component_osa)
#    include(driver_fxos8700cq)
#    include(driver_lpuart)
#    include(driver_flexio_spi)
#    include(component_pit_adapter)
#    include(middleware_mbedtls_rt)
#    include(middleware_fatfs_MIMXRT1024)
#    include(middleware_azure_rtos_ux_template_MIMXRT1024)
#    include(middleware_sdmmc_sd)
#    include(driver_src)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(utility_assert)
#    include(driver_flexio_i2s)
#    include(middleware_lwip)
#    include(middleware_azure_rtos_lx)
#    include(middleware_azure_rtos_tx)
#    include(driver_igpio)
#    include(driver_pwm)
#    include(middleware_sdmmc_host_usdhc_azurertos)
#    include(driver_sai)
#    include(driver_cache_armv7_m7)
#    include(middleware_usb_device_stack_external)
#    include(driver_ft6x06)
#    include(driver_flexio_i2s_edma)
