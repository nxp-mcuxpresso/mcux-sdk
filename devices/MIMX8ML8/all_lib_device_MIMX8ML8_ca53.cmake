list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core_AArch64/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/pcm186x
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/pcm512x
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
    ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/mdio/enet_qos
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cache/armv8-a
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/enet_qos
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ii2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/igpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iuart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sai
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(component_codec_i2c_MIMX8ML8)
#    include(driver_ii2c)
#    include(component_iuart_adapter)
#    include(component_lists)
#    include(component_serial_manager)
#    include(component_serial_manager_uart)
#    include(device_startup)
#    include(device_system)
#    include(driver_cache_armv8a)
#    include(driver_common)
#    include(driver_enet)
#    include(driver_ii2c_freertos)
#    include(component_codec_i2c_MIMX8ML8)
#    include(driver_flexcan)
#    include(driver_gpt)
#    include(driver_igpio)
#    include(driver_ii2c)
#    include(driver_iuart)
#    include(driver_mdio-enet)
#    include(driver_phy-device-rtl8211f)
#    include(driver_sai)
#    include(driver_wm8960)
#    include(driver_pcm186x)
#    include(driver_pcm512x)
#    include(middleware_freertos-kernel_ca53)
#    include(middleware_freertos-kernel_extension)
#    include(middleware_freertos-kernel_heap_4)
#    include(utilities_misc_utilities)
#    include(utility_assert)
#    include(utility_debug_console)
#    include(utility_debug_console_lite)
