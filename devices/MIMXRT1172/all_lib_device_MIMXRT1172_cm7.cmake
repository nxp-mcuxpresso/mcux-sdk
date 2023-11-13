list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/button
    ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nand
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/nand/semc
    ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/log
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
    ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/acmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/aoi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/asrc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/caam
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/csi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac12
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcic
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/elcdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet_qos
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexram
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iee_apc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/key_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/kpp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lcdifv2
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpadc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mecc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_csi2rx
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mipi_dsi_split
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ocotp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pit
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pxp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qtmr_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc_sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rtwdog
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema4
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/semc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/spdif
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ssarc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempsensor
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbarb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xecc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xrdc2
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
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cm7
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_caam)
#    include(driver_lpuart_freertos)
#    include(driver_rdc)
#    include(driver_asrc)
#    include(driver_dmamux)
#    include(middleware_lwip_apps_httpd)
#    include(middleware_lwip_apps_lwiperf)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(device_system)
#    include(driver_snvs_lp)
#    include(driver_lpadc)
#    include(driver_soc_mipi_csi2rx)
#    include(driver_flexio_uart)
#    include(driver_ewm)
#    include(driver_flexio)
#    include(driver_aoi)
#    include(driver_phy-common_MIMXRT1176_cm7)
#    include(driver_enc)
#    include(driver_flexio_i2c_master)
#    include(driver_nand_flash-common)
#    include(middleware_sdmmc_osa_bm)
#    include(component_log_backend_ringbuffer)
#    include(driver_wdog01)
#    include(middleware_lwip)
#    include(driver_ocotp)
#    include(driver_pxp)
#    include(driver_mipi_dsi_split)
#    include(component_serial_manager)
#    include(driver_lcdifv2)
#    include(driver_pit)
#    include(component_serial_manager_uart)
#    include(middleware_mbedtls_port_ksdk)
#    include(component_log_backend_debugconsole)
#    include(driver_soc_src)
#    include(middleware_lwip_contrib_ping)
#    include(component_lpuart_adapter)
#    include(middleware_usb_device_common_header)
#    include(middleware_lwip_apps_mqtt)
#    include(middleware_mbedtls_MIMXRT1176_cm7)
#    include(middleware_lwip_apps_httpsrv)
#    include(driver_rdc_sema42)
#    include(device_startup)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_enet)
#    include(driver_rtwdog)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1176_cm7)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_enet_qos)
#    include(middleware_usb_common_header)
#    include(middleware_sdmmc_osa_freertos)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_soc_flexram_allocate)
#    include(component_panic)
#    include(driver_clock)
#    include(driver_anatop_ai)
#    include(device_CMSIS)
#    include(driver_mecc)
#    include(driver_romapi)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(middleware_lwip_apps_httpd_support)
#    include(driver_flexcan)
#    include(component_osa_bm)
#    include(middleware_fatfs_MIMXRT1176_cm7)
#    include(middleware_usb_host_common_header)
#    include(driver_common)
#    include(driver_kpp)
#    include(component_osa_free_rtos)
#    include(driver_adc_etc)
#    include(driver_key_manager)
#    include(middleware_freertos-kernel_heap_3)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_lwip_apps_mdns)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(driver_snvs_hp)
#    include(driver_pdm)
#    include(driver_lpspi)
#    include(component_gpt_adapter)
#    include(driver_csi)
#    include(component_log)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(utility_debug_console_lite)
#    include(driver_pgmc)
#    include(driver_iomuxc)
#    include(utility_shell)
#    include(driver_flexram)
#    include(utility_assert_lite)
#    include(driver_semc)
#    include(driver_xecc)
#    include(driver_xbarb)
#    include(driver_xbara)
#    include(driver_spdif)
#    include(driver_nand_flash-controller-semc)
#    include(utility_debug_console)
#    include(component_osa_thread)
#    include(driver_pmu_1)
#    include(middleware_fatfs_ram)
#    include(component_mflash_common)
#    include(driver_sema4)
#    include(middleware_freertos-kernel_MIMXRT1176_cm7)
#    include(driver_puf)
#    include(driver_dcic)
#    include(middleware_usb_phy)
#    include(driver_dcdc_soc)
#    include(utilities_misc_utilities_MIMXRT1176_cm7)
#    include(driver_iee)
#    include(middleware_sdmmc_osa_azurertos)
#    include(component_button_MIMXRT1176_cm7)
#    include(component_timer_manager)
#    include(driver_lpi2c_freertos)
#    include(driver_qtmr_1)
#    include(component_common_task)
#    include(driver_gpc_3)
#    include(driver_flexspi)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(driver_acmp)
#    include(component_igpio_adapter)
#    include(component_osa)
#    include(driver_lpuart)
#    include(middleware_littlefs)
#    include(driver_flexio_spi)
#    include(component_pit_adapter)
#    include(driver_dac12)
#    include(middleware_lwip_contrib_tcpecho)
#    include(driver_xrdc2)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(driver_ssarc)
#    include(driver_flexio_i2s)
#    include(driver_elcdif)
#    include(driver_igpio)
#    include(driver_pwm)
#    include(driver_mipi_csi2rx)
#    include(driver_sai)
#    include(driver_iee_apc)
#    include(driver_mu)
#    include(driver_cache_armv7_m7)
#    include(driver_tempsensor)
