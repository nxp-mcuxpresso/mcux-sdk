list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rgpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpi2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sema42
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog32
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos_kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_cmsis_lpi2c)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_lpuart_dma)
#    include(driver_lpuart_edma)
#    include(driver_flexcan)
#    include(driver_lpi2c)
#    include(driver_lpi2c_edma)
#    include(driver_lpuart_freertos)
#    include(component_lists)
#    include(device_system)
#    include(device_startup)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_lpi2c_freertos)
#    include(driver_memory)
#    include(driver_audiomix)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_lpuart)
#    include(middleware_freertos-kernel_extension)
#    include(driver_tmu_2)
#    include(middleware_freertos-kernel_MIMX9352)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(utility_assert_lite)
#    include(driver_mu)
#    include(driver_clock)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog32)
#    include(driver_sai_sdma)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_lpuart_adapter)
#    include(utility_debug_console_lite)
#    include(driver_common)
#    include(driver_sema42)
#    include(utility_assert)
#    include(component_lpi2c_adapter)
#    include(component_serial_manager)
#    include(driver_rgpio)
#    include(driver_pdm_sdma)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_pdm)
#    include(driver_cmsis_lpuart)
#    include(driver_lptmr)
