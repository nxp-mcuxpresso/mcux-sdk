list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/port/wm8524
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/easrc
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
#    include(component_codec_wm8524_adapter)
#    include(utility_debug_console_lite)
#    include(CMSIS_Include_dsp)
#    include(driver_rdc)
#    include(driver_ii2c)
#    include(driver_ecspi_freertos)
#    include(driver_gpc_2)
#    include(driver_iuart_freertos)
#    include(component_lists)
#    include(device_system)
#    include(device_startup)
#    include(driver_clock)
#    include(driver_ii2c_freertos)
#    include(middleware_freertos-kernel_MIMX8MN6)
#    include(driver_memory)
#    include(driver_gpt)
#    include(driver_easrc)
#    include(driver_iuart)
#    include(driver_ipwm)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ecspi)
#    include(driver_sdma)
#    include(utility_assert_lite)
#    include(driver_tmu_1)
#    include(driver_iuart_sdma)
#    include(driver_rdc_sema42)
#    include(middleware_freertos-kernel_heap_4)
#    include(utility_assert)
#    include(driver_srtm_freertos)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog01)
#    include(driver_sai_sdma)
#    include(component_iuart_adapter)
#    include(component_wm8524_adapter)
#    include(CMSIS_Include_core_cm7)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_easrc_sdma)
#    include(driver_sema4)
#    include(middleware_multicore_rpmsg_lite_imx8mn_m7_freertos)
#    include(driver_pdm)
#    include(driver_srtm)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(driver_igpio)
#    include(driver_pdm_sdma)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_wm8524)
#    include(driver_mu)
