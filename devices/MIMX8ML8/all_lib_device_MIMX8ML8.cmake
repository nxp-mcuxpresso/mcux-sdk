list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../cmsis_drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imx8
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/easrc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ecspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
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
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_tmu_2)
#    include(CMSIS_Driver_Include_Ethernet_MAC)
#    include(driver_cmsis_ecspi)
#    include(driver_codec)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(component_iuart_adapter)
#    include(driver_sema4)
#    include(CMSIS_Driver_Include_Ethernet)
#    include(driver_gpc_2)
#    include(utility_assert)
#    include(CMSIS_Driver_Include_Ethernet_PHY)
#    include(CMSIS_Driver_Include_I2C)
#    include(driver_cmsis_enet)
#    include(driver_ecspi_sdma)
#    include(driver_ipwm)
#    include(component_silicon_id_MIMX8ML8)
#    include(driver_iuart)
#    include(driver_mu)
#    include(driver_srtm_MIMX8ML8)
#    include(driver_gpt)
#    include(component_serial_manager_uart)
#    include(component_lists)
#    include(driver_cache_armv7_m7)
#    include(component_codec_adapters)
#    include(CMSIS_Driver_Include_Common)
#    include(CMSIS_DSP_Source)
#    include(driver_rdc_sema42)
#    include(middleware_multicore_rpmsg_lite_MIMX8ML8)
#    include(component_wm8960_adapter)
#    include(utility_debug_console_lite)
#    include(driver_iuart_sdma)
#    include(utility_debug_console)
#    include(driver_enet)
#    include(driver_wm8960)
#    include(middleware_freertos-kernel_heap_4)
#    include(driver_ii2c)
#    include(driver_ii2c_freertos)
#    include(driver_sai_sdma)
#    include(driver_pdm_sdma)
#    include(device_system)
#    include(utility_assert_lite)
#    include(driver_iuart_freertos)
#    include(device_startup)
#    include(driver_srtm_freertos)
#    include(component_ii2c_adapter)
#    include(driver_cmsis_ii2c)
#    include(driver_cmsis_iuart)
#    include(CMSIS_Driver_Include_SPI)
#    include(driver_clock)
#    include(driver_phy-common_MIMX8ML8)
#    include(device_CMSIS)
#    include(driver_easrc_sdma)
#    include(driver_sdma)
#    include(driver_pdm)
#    include(middleware_multicore_rpmsg_lite_imx8mp_m7_freertos)
#    include(utilities_misc_utilities_MIMX8ML8)
#    include(driver_ecspi_freertos)
#    include(driver_igpio)
#    include(driver_easrc)
#    include(driver_phy-device-rtl8211f)
#    include(driver_sai)
#    include(component_silicon_id_imx8)
#    include(driver_rdc)
#    include(driver_memory)
#    include(CMSIS_Driver_Include_USART)
#    include(driver_audiomix)
#    include(driver_common)
#    include(middleware_freertos-kernel_MIMX8ML8)
#    include(CMSIS_Include_core_cm)
#    include(driver_wdog01)
#    include(component_serial_manager)
#    include(driver_flexcan)
#    include(component_codec_i2c_MIMX8ML8)
#    include(driver_ecspi)
