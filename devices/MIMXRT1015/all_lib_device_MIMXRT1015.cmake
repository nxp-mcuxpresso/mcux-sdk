list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt1015/xip
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_12b1msps_sar
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc_etc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/bee
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv7-m7
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcdc_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dcp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_hp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/snvs_lp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/src
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tempmon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/xbara
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../middleware/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/xip
)


# Copy the cmake components into projects
#    include(driver_igpio)
#    include(driver_rtwatchdog)
#    include(driver_flexspi)
#    include(driver_flexio_spi_edma)
#    include(CMSIS_Include_dsp)
#    include(component_lpuart_adapter)
#    include(driver_qtmr_1)
#    include(driver_trng)
#    include(driver_dmamux)
#    include(driver_lpspi)
#    include(driver_lpi2c_edma)
#    include(driver_flexspi_edma)
#    include(component_lists)
#    include(driver_snvs_hp)
#    include(device_system)
#    include(driver_snvs_lp)
#    include(utility_debug_console)
#    include(utility_shell)
#    include(device_startup)
#    include(driver_tempmon)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_flexio_uart)
#    include(component_osa)
#    include(driver_edma)
#    include(driver_ewm)
#    include(driver_gpt)
#    include(driver_lpuart)
#    include(driver_wdog01)
#    include(driver_flexio_spi)
#    include(driver_iomuxc)
#    include(driver_flexio)
#    include(middleware_usb_device_common_header)
#    include(driver_wm8960)
#    include(driver_flexram)
#    include(utility_assert_lite)
#    include(driver_bee)
#    include(driver_flexio_i2c_master)
#    include(middleware_usb_common_header)
#    include(middleware_baremetal)
#    include(driver_sai_edma)
#    include(driver_soc_flexram_allocate)
#    include(utility_assert)
#    include(driver_lpspi_edma)
#    include(driver_lpuart_edma)
#    include(device_CMSIS)
#    include(driver_enc)
#    include(driver_romapi)
#    include(driver_src)
#    include(driver_flexio_uart_edma)
#    include(driver_dcp)
#    include(driver_ocotp)
#    include(CMSIS_Include_core_cm7)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_lpi2c)
#    include(driver_adc_12b1msps_sar)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_flexio_i2s)
#    include(driver_xip_device)
#    include(driver_kpp)
#    include(component_codec_i2c_MIMXRT1015)
#    include(component_wm8960_adapter)
#    include(component_serial_manager)
#    include(driver_xip_board)
#    include(driver_fxos8700cq)
#    include(driver_adc_etc)
#    include(driver_pwm)
#    include(driver_pit)
#    include(component_lpi2c_adapter)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_gpc_1)
#    include(driver_cache_armv7_m7)
#    include(driver_dcdc_1)
#    include(driver_xbara)
#    include(driver_flexio_i2s_edma)
