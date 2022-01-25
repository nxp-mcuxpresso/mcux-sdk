list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/ak4497
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpc_2
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ipwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc_sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sdma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema4
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tmu_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
include_ifdef(CONFIG_USE_component_codec_adapters	component_codec_adapters)
include_ifdef(CONFIG_USE_utility_debug_console_lite	utility_debug_console_lite)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8mm_m4_freertos	middleware_multicore_rpmsg_lite_imx8mm_m4_freertos)
include_ifdef(CONFIG_USE_driver_iuart_sdma	driver_iuart_sdma)
include_ifdef(CONFIG_USE_driver_rdc	driver_rdc)
include_ifdef(CONFIG_USE_driver_ii2c	driver_ii2c)
include_ifdef(CONFIG_USE_driver_ecspi_freertos	driver_ecspi_freertos)
include_ifdef(CONFIG_USE_driver_gpc_2	driver_gpc_2)
include_ifdef(CONFIG_USE_driver_iuart_freertos	driver_iuart_freertos)
include_ifdef(CONFIG_USE_component_lists	component_lists)
include_ifdef(CONFIG_USE_device_system	device_system)
include_ifdef(CONFIG_USE_device_startup	device_startup)
include_ifdef(CONFIG_USE_driver_ak4497	driver_ak4497)
include_ifdef(CONFIG_USE_driver_clock	driver_clock)
include_ifdef(CONFIG_USE_driver_ii2c_freertos	driver_ii2c_freertos)
include_ifdef(CONFIG_USE_driver_memory	driver_memory)
include_ifdef(CONFIG_USE_driver_gpt	driver_gpt)
include_ifdef(CONFIG_USE_component_serial_manager_uart	component_serial_manager_uart)
include_ifdef(CONFIG_USE_driver_iuart	driver_iuart)
include_ifdef(CONFIG_USE_driver_ipwm	driver_ipwm)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_extension	middleware_freertos-kernel_extension)
include_ifdef(CONFIG_USE_driver_ecspi	driver_ecspi)
include_ifdef(CONFIG_USE_driver_srtm_MIMX8MM6	driver_srtm_MIMX8MM6)
include_ifdef(CONFIG_USE_driver_sdma	driver_sdma)
include_ifdef(CONFIG_USE_utility_assert_lite	utility_assert_lite)
include_ifdef(CONFIG_USE_driver_cache_lmem	driver_cache_lmem)
include_ifdef(CONFIG_USE_driver_tmu_1	driver_tmu_1)
include_ifdef(CONFIG_USE_driver_rdc_sema42	driver_rdc_sema42)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_heap_4	middleware_freertos-kernel_heap_4)
include_ifdef(CONFIG_USE_utility_assert	utility_assert)
include_ifdef(CONFIG_USE_component_ak4497_adapter	component_ak4497_adapter)
include_ifdef(CONFIG_USE_driver_srtm_freertos	driver_srtm_freertos)
include_ifdef(CONFIG_USE_utility_debug_console	utility_debug_console)
include_ifdef(CONFIG_USE_device_CMSIS	device_CMSIS)
include_ifdef(CONFIG_USE_driver_wdog01	driver_wdog01)
include_ifdef(CONFIG_USE_driver_sai_sdma	driver_sai_sdma)
include_ifdef(CONFIG_USE_component_iuart_adapter	component_iuart_adapter)
include_ifdef(CONFIG_USE_component_wm8524_adapter	component_wm8524_adapter)
include_ifdef(CONFIG_USE_driver_codec	driver_codec)
include_ifdef(CONFIG_USE_utilities_misc_utilities	utilities_misc_utilities)
include_ifdef(CONFIG_USE_driver_common	driver_common)
include_ifdef(CONFIG_USE_driver_sema4	driver_sema4)
include_ifdef(CONFIG_USE_component_ii2c_adapter	component_ii2c_adapter)
include_ifdef(CONFIG_USE_component_serial_manager	component_serial_manager)
include_ifdef(CONFIG_USE_middleware_multicore_rpmsg_lite	middleware_multicore_rpmsg_lite)
include_ifdef(CONFIG_USE_driver_igpio	driver_igpio)
include_ifdef(CONFIG_USE_driver_pdm_sdma	driver_pdm_sdma)
include_ifdef(CONFIG_USE_component_codec_i2c_MIMX8MM6	component_codec_i2c_MIMX8MM6)
include_ifdef(CONFIG_USE_driver_sai	driver_sai)
include_ifdef(CONFIG_USE_CMSIS_Include_core_cm	CMSIS_Include_core_cm)
include_ifdef(CONFIG_USE_driver_wm8524	driver_wm8524)
include_ifdef(CONFIG_USE_driver_pdm	driver_pdm)
include_ifdef(CONFIG_USE_driver_mu	driver_mu)
include_ifdef(CONFIG_USE_middleware_freertos-kernel_MIMX8MM6	middleware_freertos-kernel_MIMX8MM6)
