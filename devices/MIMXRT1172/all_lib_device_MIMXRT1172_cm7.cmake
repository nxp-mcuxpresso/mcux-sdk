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
#    include(utility_shell)
#    include(component_osa_bm)
#    include(middleware_freertos-kernel_MIMXRT1176_cm7)
#    include(middleware_lwip_apps_mdns_MIMXRT1176_cm7)
#    include(middleware_lwip_contrib_tcpecho)
#    include(CMSIS_Driver_Include_Ethernet)
#    include(middleware_lwip_enet_ethernetif_MIMXRT1176_cm7)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_gpt)
#    include(middleware_sdmmc_osa_azurertos)
#    include(driver_kpp)
#    include(CMSIS_DSP_Source)
#    include(driver_dmamux)
#    include(driver_pmu_1)
#    include(driver_lpuart)
#    include(driver_lpadc)
#    include(driver_pit)
#    include(middleware_freertos-kernel_heap_3)
#    include(component_common_task)
#    include(driver_clock)
#    include(component_log)
#    include(driver_flexio_i2c_master)
#    include(component_lpuart_adapter)
#    include(driver_pdm)
#    include(driver_phy-common_MIMXRT1176_cm7)
#    include(driver_acmp)
#    include(driver_caam)
#    include(driver_iee_apc)
#    include(driver_lpi2c_freertos)
#    include(driver_ocotp)
#    include(CMSIS_Driver_Include_USART)
#    include(component_pit_adapter)
#    include(driver_lpspi)
#    include(driver_xecc)
#    include(driver_iomuxc)
#    include(driver_common)
#    include(driver_flexcan)
#    include(component_log_backend_debugconsole_MIMXRT1176_cm7)
#    include(component_mflash_common)
#    include(driver_tempsensor)
#    include(driver_nand_flash-common)
#    include(driver_mipi_dsi_split)
#    include(middleware_freertos-kernel_extension)
#    include(driver_pxp)
#    include(driver_anatop_ai)
#    include(driver_elcdif)
#    include(middleware_lwip_contrib_ping)
#    include(middleware_lwip_apps_lwiperf_MIMXRT1176_cm7)
#    include(driver_enet_qos)
#    include(component_serial_manager_uart)
#    include(driver_mipi_csi2rx)
#    include(driver_pwm)
#    include(driver_rdc_sema42)
#    include(driver_flexio_i2s)
#    include(component_log_backend_ringbuffer)
#    include(component_panic)
#    include(component_button_MIMXRT1176_cm7)
#    include(driver_xbarb)
#    include(middleware_lwip_apps_httpsrv_MIMXRT1176_cm7)
#    include(driver_aoi)
#    include(driver_csi)
#    include(device_startup)
#    include(middleware_sdmmc_osa_bm)
#    include(component_osa_free_rtos_MIMXRT1176_cm7)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_snvs_hp)
#    include(device_CMSIS)
#    include(driver_soc_mipi_csi2rx)
#    include(driver_dac12)
#    include(middleware_usb_host_common_header)
#    include(driver_rtwdog)
#    include(middleware_sdmmc_common)
#    include(middleware_lwip_apps_httpd_support)
#    include(middleware_usb_device_common_header)
#    include(driver_asrc)
#    include(middleware_lwip_apps_httpd)
#    include(utility_assert)
#    include(driver_soc_flexram_allocate)
#    include(middleware_fatfs_ram)
#    include(driver_enc)
#    include(driver_lcdifv2)
#    include(driver_mu)
#    include(middleware_mbedtls_port_ksdk)
#    include(driver_gpc_3)
#    include(component_lists)
#    include(driver_nand_flash-controller-semc)
#    include(driver_qtmr_1)
#    include(utility_debug_console)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_usb_phy)
#    include(component_igpio_adapter)
#    include(driver_flexspi)
#    include(driver_flexio_uart)
#    include(utilities_misc_utilities_MIMXRT1176_cm7)
#    include(driver_lpuart_freertos)
#    include(driver_pgmc)
#    include(driver_flexram)
#    include(driver_adc_etc)
#    include(driver_ewm)
#    include(middleware_mbedtls_MIMXRT1176_cm7)
#    include(component_osa)
#    include(driver_ssarc)
#    include(driver_key_manager)
#    include(CMSIS_Include_core_cm)
#    include(driver_dcdc_soc)
#    include(driver_enet)
#    include(middleware_lwip_MIMXRT1176_cm7)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(driver_sema4)
#    include(driver_soc_src)
#    include(middleware_lwip_apps_mqtt)
#    include(component_osa_thread)
#    include(component_timer_manager)
#    include(driver_snvs_lp)
#    include(utility_debug_console_lite)
#    include(driver_cache_armv7_m7)
#    include(driver_lpi2c)
#    include(CMSIS_Driver_Include_Common)
#    include(driver_dcic)
#    include(middleware_sdmmc_osa_freertos)
#    include(driver_semc)
#    include(component_gpt_adapter)
#    include(device_system)
#    include(utility_assert_lite)
#    include(driver_iee)
#    include(driver_romapi)
#    include(driver_mecc)
#    include(driver_xrdc2)
#    include(driver_spdif)
#    include(driver_igpio)
#    include(driver_sai)
#    include(driver_xbara)
#    include(driver_flexio)
#    include(middleware_fatfs_MIMXRT1176_cm7)
#    include(driver_flexio_spi)
#    include(middleware_usb_common_header)
#    include(driver_puf)
#    include(driver_wdog01)
#    include(component_serial_manager)
#    include(driver_rdc)
#    include(middleware_littlefs)
