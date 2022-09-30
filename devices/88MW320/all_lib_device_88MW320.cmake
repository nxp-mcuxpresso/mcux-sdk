list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/boot2_utils
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash
    ${CMAKE_CURRENT_LIST_DIR}/../../components/flash/mflash/mw320
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/acomp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/aes
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/dmac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/flashc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/qspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/rtc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/sdioc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/ssp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mw320/wdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/lwip
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/wifi
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_power)
#    include(utilities_misc_utilities)
#    include(middleware_sdmmc_sdio)
#    include(CMSIS_Include_dsp)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_mw_rtc)
#    include(middleware_lwip_apps_lwiperf)
#    include(middleware_mbedtls_port_mw)
#    include(component_lists)
#    include(middleware_sdmmc_common)
#    include(device_system)
#    include(middleware_lwip_apps_httpsrv)
#    include(driver_mw_pinmux)
#    include(driver_mw_uart)
#    include(device_startup)
#    include(driver_clock)
#    include(driver_mw_adc)
#    include(middleware_freertos-kernel_88MW320)
#    include(driver_mw_dac)
#    include(middleware_sdmmc_host_sdioc_freertos)
#    include(driver_mw_crc)
#    include(driver_mw_i2c)
#    include(middleware_sdmmc_host_sdioc)
#    include(middleware_wifi)
#    include(driver_mw_flashc)
#    include(driver_mw_dmac)
#    include(middleware_sdmmc_host_sdioc_interrupt)
#    include(driver_mw_sdioc)
#    include(driver_mw_gpt)
#    include(driver_mw_qspi)
#    include(driver_mw_ssp)
#    include(middleware_freertos-kernel_extension)
#    include(driver_mw_acomp)
#    include(driver_mw_i2c_dmac)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_mw_uart_dmac)
#    include(component_mw_uart_adapter)
#    include(component_mflash_file)
#    include(middleware_lwip)
#    include(component_osa_bm)
#    include(driver_mw_ssp_dmac)
#    include(CMSIS_Include_core_cm4)
#    include(middleware_wifi_cli)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(component_mflash_common)
#    include(utility_assert)
#    include(component_mflash_mw320)
#    include(driver_mw_wdt)
#    include(middleware_sdmmc_osa_freertos)
#    include(component_osa_free_rtos)
#    include(driver_mw_gpio)
#    include(middleware_mbedtls)
#    include(component_boot2_psm)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(driver_mw_aes)
#    include(middleware_freertos-kernel_heap_4)
#    include(component_boot2_partition)
