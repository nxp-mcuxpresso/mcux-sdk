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
include_ifdef(CONFIG_USE_driver_ctimer	driver_ctimer)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_bm	middleware_sdmmc_osa_bm)
include_ifdef(CONFIG_USE_driver_flash_config	driver_flash_config)
include_ifdef(CONFIG_USE_driver_lpc_gpio	driver_lpc_gpio)
include_ifdef(CONFIG_USE_driver_lpadc	driver_lpadc)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_cm33_nonsecure_port	middleware_freertos-kernel_cm33_nonsecure_port)
include_ifdef(CONFIG_USE_driver_lpc_crc	driver_lpc_crc)
include_ifdef(CONFIG_USE_middleware_baremetal	middleware_baremetal)
include_ifdef(CONFIG_USE_driver_flexcomm_usart	driver_flexcomm_usart)
include_ifdef(CONFIG_USE_driver_i3c	driver_i3c)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_ostimer	driver_ostimer)
include_ifdef(CONFIG_USE_driver_inputmux	driver_inputmux)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c	driver_flexcomm_i2c)
include_ifdef(CONFIG_USE_driver_iap	driver_iap)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_driver_lpc_dma	driver_lpc_dma)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_flexcomm_i2s	driver_flexcomm_i2s)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_dma	driver_flexcomm_spi_dma)
include_ifdef(CONFIG_USE_driver_flexcomm_spi_freertos	driver_flexcomm_spi_freertos)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_cm33_secure_port	middleware_freertos-kernel_cm33_secure_port)
include_ifdef(CONFIG_USE_CMSIS_DSP_Library	CMSIS_DSP_Library)
include_ifdef(CONFIG_USE_driver_pint	driver_pint)
include_ifdef(CONFIG_USE_driver_sctimer	driver_sctimer)
include_ifdef(CONFIG_USE_driver_flexcomm	driver_flexcomm)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_casper	driver_casper)
include_ifdef(CONFIG_USE_driver_usdhc	driver_usdhc)
include_ifdef(CONFIG_USE_component_cs42888_adapter	component_cs42888_adapter)
include_ifdef(CONFIG_USE_driver_wm8904	driver_wm8904)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_flexcomm_spi	driver_flexcomm_spi)
include_ifdef(CONFIG_USE_driver_utick	driver_utick)
include_ifdef(CONFIG_USE_middleware_sdmmc_osa_freertos	middleware_sdmmc_osa_freertos)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_component_osa_bm	component_osa_bm)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMXRT685S_cm33	component_codec_i2c_MIMXRT685S_cm33)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_cache_cache64	driver_cache_cache64)
include_ifdef(CONFIG_USE_driver_flexspi_dma	driver_flexspi_dma)
include_ifdef(CONFIG_USE_component_osa_free_rtos	component_osa_free_rtos)
include_ifdef(CONFIG_USE_middleware_sdmmc_sd	middleware_sdmmc_sd)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33	middleware_sdmmc_host_usdhc_interrupt_MIMXRT685S_cm33)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_driver_hashcrypt	driver_hashcrypt)
include_ifdef(CONFIG_USE_middleware_sdmmc_sdio	middleware_sdmmc_sdio)
include_ifdef(CONFIG_USE_component_usart_adapter	component_usart_adapter)
include_ifdef(CONFIG_USE_driver_wwdt	driver_wwdt)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_driver_flexcomm_i2s_dma	driver_flexcomm_i2s_dma)
include_ifdef(CONFIG_USE_driver_inputmux_connections	driver_inputmux_connections)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_dma	driver_flexcomm_i2c_dma)
include_ifdef(CONFIG_USE_component_flexcomm_i2c_adapter	component_flexcomm_i2c_adapter)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMXRT685S_cm33	middleware_freertos-kernel_MIMXRT685S_cm33)
include_ifdef(CONFIG_USE_utility_shell	utility_shell)
include_ifdef(CONFIG_USE_driver_otfad	driver_otfad)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33	middleware_sdmmc_host_usdhc_polling_MIMXRT685S_cm33)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc	middleware_sdmmc_host_usdhc)
include_ifdef(CONFIG_USE_driver_puf	driver_puf)
include_ifdef(CONFIG_USE_driver_tfa9xxx	driver_tfa9xxx)
include_ifdef(CONFIG_USE_driver_power	driver_power)
include_ifdef(CONFIG_USE_driver_cs42888	driver_cs42888)
include_ifdef(CONFIG_USE_driver_dmic_dma	driver_dmic_dma)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers	middleware_freertos-kernel_mpu_wrappers)
include_ifdef(CONFIG_USE_driver_lpc_rtc	driver_lpc_rtc)
include_ifdef(CONFIG_USE_middleware_sdmmc_common	middleware_sdmmc_common)
include_ifdef(CONFIG_USE_driver_flexspi	driver_flexspi)
include_ifdef(CONFIG_USE_driver_dmic	driver_dmic)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_driver_mrt	driver_mrt)
include_ifdef(CONFIG_USE_driver_acmp	driver_acmp)
include_ifdef(CONFIG_USE_component_osa	component_osa)
include_ifdef(CONFIG_USE_driver_fmeas	driver_fmeas)
include_ifdef(CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33	middleware_sdmmc_host_usdhc_freertos_MIMXRT685S_cm33)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_secure_context	middleware_freertos-kernel_secure_context)
include_ifdef(CONFIG_USE_component_i3c_adapter	component_i3c_adapter)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_dma	driver_flexcomm_usart_dma)
include_ifdef(CONFIG_USE_driver_pca9420	driver_pca9420)
include_ifdef(CONFIG_USE_component_tfa9xxx_adapter	component_tfa9xxx_adapter)
include_ifdef(CONFIG_USE_driver_flexcomm_i2c_freertos	driver_flexcomm_i2c_freertos)
include_ifdef(CONFIG_USE_driver_powerquad	driver_powerquad)
include_ifdef(CONFIG_USE_driver_flexcomm_usart_freertos	driver_flexcomm_usart_freertos)
include_ifdef(CONFIG_USE_driver_lpc_iopctl	driver_lpc_iopctl)
include_ifdef(CONFIG_USE_driver_trng	driver_trng)
include_ifdef(CONFIG_USE_component_wm8904_adapter	component_wm8904_adapter)
include_ifdef(CONFIG_USE_driver_reset	driver_reset)
