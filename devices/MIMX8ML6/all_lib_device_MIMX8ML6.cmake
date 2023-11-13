list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/easrc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tmu_2
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_cmsis_ii2c)
#    include(middleware_freertos-kernel_heap_4)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(driver_iuart_sdma)
#    include(driver_rdc)
#    include(driver_ii2c)
#    include(driver_ecspi_freertos)
#    include(driver_gpc_2)
#    include(driver_iuart_freertos)
#    include(CMSIS_Driver_Include_Ethernet_MAC OPTIONAL)
#    include(driver_cmsis_ecspi)
#    include(device_system)
#    include(driver_rdc_sema42)
#    include(driver_cmsis_enet)
#    include(device_startup)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_ii2c_freertos)
#    include(driver_easrc_sdma)
#    include(driver_audiomix)
#    include(driver_easrc)
#    include(driver_enet)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_iuart)
#    include(driver_ipwm)
#    include(driver_ecspi_sdma)
#    include(middleware_freertos-kernel_extension)
#    include(driver_ecspi)
#    include(driver_tmu_2)
#    include(middleware_freertos-kernel_MIMX8ML8)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_sdma)
#    include(utility_assert_lite)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_mu)
#    include(driver_clock)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog01)
#    include(driver_sai_sdma)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(driver_phy-common_MIMX8ML8)
#    include(component_iuart_adapter)
#    include(utility_debug_console_lite)
#    include(driver_common)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(driver_sema4)
#    include(utility_assert)
#    include(driver_pdm)
#    include(component_serial_manager)
#    include(driver_igpio)
#    include(driver_pdm_sdma)
#    include(driver_sai)
#    include(component_serial_manager_uart)
#    include(driver_cmsis_iuart)
#    include(driver_cache_armv7_m7)
#    include(utilities_misc_utilities_MIMX8ML8)
#    include(component_lists)
#    include(driver_memory)
#    include(driver_gpt)
