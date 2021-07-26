list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ipwm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/qspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rdc_sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema4
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tmu
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
#    include(utility_debug_console_lite)
#    include(driver_rdc)
#    include(driver_ii2c)
#    include(driver_ecspi_freertos)
#    include(component_lists)
#    include(device_system)
#    include(driver_iuart_freertos)
#    include(driver_clock)
#    include(driver_ii2c_freertos)
#    include(driver_gpt)
#    include(CMSIS_Include_core_cm)
#    include(driver_iuart)
#    include(driver_ipwm)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ecspi)
#    include(utility_assert_lite)
#    include(driver_cache_lmem)
#    include(driver_rdc_sema42)
#    include(middleware_freertos-kernel_heap_4)
#    include(middleware_multicore_rpmsg_lite_imx8mq_m4_freertos)
#    include(utility_assert)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog01)
#    include(component_iuart_adapter)
#    include(component_wm8524_adapter)
#    include(driver_codec)
#    include(utilities_misc_utilities)
#    include(driver_common)
#    include(device_startup)
#    include(driver_sema4)
#    include(driver_tmu)
#    include(component_serial_manager)
#    include(middleware_multicore_rpmsg_lite)
#    include(driver_igpio)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_wm8524)
#    include(middleware_freertos-kernel_MIMX8MQ6)
#    include(driver_mu)
#    include(driver_qspi)
