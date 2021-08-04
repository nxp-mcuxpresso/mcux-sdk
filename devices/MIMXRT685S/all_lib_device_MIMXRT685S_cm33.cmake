list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimxrt685/flash_config
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42888
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/tfa9xxx
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
    ${CMAKE_CURRENT_LIST_DIR}/../../components/pca9420
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ostimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/otfad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/powerquad
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/puf
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/trng
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/usdhc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/utick
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/sdmmc
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(driver_ctimer)
#    include(middleware_sdmmc_osa_bm)
#    include(driver_flash_config)
#    include(driver_lpc_gpio)
#    include(driver_lpadc)
#    include(middleware_freertos-kernel_cm33_nonsecure_port)
#    include(driver_lpc_crc)
#    include(middleware_baremetal)
#    include(driver_flexcomm_usart)
#    include(driver_i3c)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_ostimer)
#    include(driver_inputmux)
#    include(driver_flexcomm_i2c)
#    include(driver_iap)
#    include(component_serial_manager)
#    include(driver_lpc_dma)
#    include(component_serial_manager_uart)
#    include(driver_flexcomm_i2s)
#    include(driver_flexcomm_spi_dma)
#    include(driver_flexcomm_spi_freertos)
#    include(middleware_freertos-kernel_cm33_secure_port)
#    include(CMSIS_DSP_Library)
#    include(driver_pint)
#    include(driver_sctimer)
#    include(driver_flexcomm)
#    include(device_startup)
#    include(driver_casper)
#    include(driver_usdhc)
#    include(component_cs42888_adapter)
#    include(driver_wm8904)
#    include(middleware_freertos-kernel_extension)
#    include(driver_flexcomm_spi)
#    include(driver_utick)
#    include(middleware_sdmmc_osa_freertos)
#    include(utility_assert)
#    include(device_CMSIS)
#    include(component_osa_bm)
#    include(component_codec_i2c_MIMXRT685S_cm33)
#    include(driver_common)
#    include(driver_cache_cache64)
#    include(driver_flexspi_dma)
#    include(component_osa_free_rtos)
#    include(middleware_sdmmc_sd)
#    include(CMSIS_Include_core_cm)
#    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_hashcrypt)
#    include(middleware_sdmmc_sdio)
#    include(component_usart_adapter)
#    include(driver_wwdt)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_flexcomm_i2s_dma)
#    include(driver_inputmux_connections)
#    include(driver_flexcomm_i2c_dma)
#    include(component_flexcomm_i2c_adapter)
#    include(utility_assert_lite)
#    include(middleware_freertos-kernel_MIMXRT685S_cm33)
#    include(utility_shell)
#    include(driver_otfad)
#    include(utility_debug_console)
#    include(middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33)
#    include(middleware_sdmmc_host_usdhc)
#    include(driver_puf)
#    include(driver_tfa9xxx)
#    include(driver_power)
#    include(driver_cs42888)
#    include(driver_dmic_dma)
#    include(middleware_freertos-kernel_mpu_wrappers)
#    include(driver_lpc_rtc)
#    include(middleware_sdmmc_common)
#    include(driver_flexspi)
#    include(driver_dmic)
#    include(component_lists)
#    include(driver_mrt)
#    include(driver_acmp)
#    include(component_osa)
#    include(driver_fmeas)
#    include(middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33)
#    include(middleware_freertos-kernel_secure_context)
#    include(component_i3c_adapter)
#    include(driver_flexcomm_usart_dma)
#    include(driver_pca9420)
#    include(component_tfa9xxx_adapter)
#    include(driver_flexcomm_i2c_freertos)
#    include(driver_powerquad)
#    include(driver_flexcomm_usart_freertos)
#    include(driver_lpc_iopctl)
#    include(driver_trng)
#    include(component_wm8904_adapter)
#    include(driver_reset)
