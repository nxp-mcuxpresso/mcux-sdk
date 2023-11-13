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
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/ak4497
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyar8031
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
    ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imx8
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
    ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/lmem
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
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
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/tmu_1
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog01
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/multicore
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/voice_seeker
    ${CMAKE_CURRENT_LIST_DIR}/../../../middleware/voice_seeker/rdsp_utilities_public
    ${CMAKE_CURRENT_LIST_DIR}/../../../rtos/freertos/freertos-kernel
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(middleware_freertos-kernel_extension)
#    include(driver_cmsis_ii2c)
#    include(driver_phy-common_MIMX8MM6)
#    include(component_silicon_id_imx8)
#    include(component_codec_adapters)
#    include(middleware_freertos-kernel_heap_4)
#    include(CMSIS_DSP_Source OPTIONAL)
#    include(middleware_multicore_rpmsg_lite_imx8mm_m4_freertos)
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
#    include(driver_ak4497)
#    include(CMSIS_Driver_Include_USART OPTIONAL)
#    include(CMSIS_Driver_Include_SPI OPTIONAL)
#    include(driver_ii2c_freertos)
#    include(middleware_voice_seeker_cm4)
#    include(driver_memory)
#    include(driver_gpt)
#    include(utility_assert)
#    include(driver_enet)
#    include(component_serial_manager_uart)
#    include(driver_iuart)
#    include(driver_ipwm)
#    include(driver_ecspi_sdma)
#    include(driver_phy-device-ar8031)
#    include(driver_ecspi)
#    include(driver_srtm_MIMX8MM6)
#    include(CMSIS_Driver_Include_I2C OPTIONAL)
#    include(driver_sdma)
#    include(utility_assert_lite)
#    include(driver_cache_lmem)
#    include(driver_tmu_1)
#    include(CMSIS_Driver_Include_Ethernet OPTIONAL)
#    include(driver_mu)
#    include(driver_clock)
#    include(component_ak4497_adapter)
#    include(driver_srtm_freertos)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_wdog01)
#    include(driver_sai_sdma)
#    include(CMSIS_Driver_Include_Common OPTIONAL)
#    include(component_iuart_adapter)
#    include(component_wm8524_adapter)
#    include(driver_codec)
#    include(component_silicon_id_MIMX8MM6)
#    include(utilities_misc_utilities_MIMX8MM6)
#    include(driver_common)
#    include(CMSIS_Driver_Include_Ethernet_PHY OPTIONAL)
#    include(driver_sema4)
#    include(middleware_multicore_rpmsg_lite_freertos)
#    include(component_ii2c_adapter)
#    include(component_serial_manager)
#    include(driver_igpio)
#    include(driver_pdm_sdma)
#    include(component_codec_i2c_MIMX8MM6)
#    include(driver_sai)
#    include(middleware_multicore_rpmsg_lite_MIMX8MM6)
#    include(CMSIS_Include_core_cm OPTIONAL)
#    include(driver_wm8524)
#    include(driver_pdm)
#    include(utility_debug_console_lite)
#    include(driver_cmsis_iuart)
#    include(component_lists)
#    include(middleware_freertos-kernel_MIMX8MM6)
#    include(middleware_voice_seeker_rdsp_utilities_public)
