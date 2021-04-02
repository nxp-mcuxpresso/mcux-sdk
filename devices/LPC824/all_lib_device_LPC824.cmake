list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/iap
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/inputmux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_acomp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_adc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_iocon_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_minispi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lpc_miniusart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mrt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pint
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sctimer
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/swm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/syscon
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wkt
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wwdt
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
)


# Copy the cmake components into projects
#    include(driver_lpc_miniusart)
#    include(CMSIS_Include_dsp)
#    include(driver_sctimer)
#    include(driver_wwdt)
#    include(driver_swm)
#    include(driver_lpc_gpio)
#    include(driver_mrt)
#    include(device_system)
#    include(driver_lpc_adc)
#    include(device_startup)
#    include(driver_pint)
#    include(driver_clock)
#    include(driver_wkt)
#    include(driver_inputmux_connections)
#    include(driver_lpc_crc)
#    include(CMSIS_Include_core_cm0plus)
#    include(component_miniusart_adapter)
#    include(driver_lpc_acomp)
#    include(driver_swm_connections)
#    include(device_CMSIS)
#    include(driver_power_no_lib)
#    include(utility_debug_console_lite)
#    include(utilities_misc_utilities)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_syscon_connections)
#    include(utility_assert_lite)
#    include(driver_inputmux)
#    include(driver_iap)
#    include(driver_lpc_dma)
#    include(driver_syscon)
#    include(driver_reset)
#    include(driver_lpc_i2c)
#    include(driver_lpc_minispi)
#    include(driver_lpc_iocon_lite)
