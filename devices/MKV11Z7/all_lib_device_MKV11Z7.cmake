list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/../../components/fxos8700cq
    ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
    ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
    ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/adc16
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/cmp
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/common
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/crc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dac
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dmamux
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/dspi
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/edma
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ewm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/flexcan
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/ftm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/llwu
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/lptmr
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/mmdvsq
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pdb
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/pmc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/port
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/rcm
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/sim
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/smc
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../drivers/wdog
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/assert
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/../../utilities/misc_utilities
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/utilities
)


# Copy the cmake components into projects
#    include(component_serial_manager_MKV11Z7)
#    include(driver_llwu)
#    include(utility_assert_lite_MKV11Z7)
#    include(driver_dspi)
#    include(driver_uart_edma)
#    include(CMSIS_Include_dsp)
#    include(driver_flexcan)
#    include(driver_i2c)
#    include(component_serial_manager_uart_MKV11Z7)
#    include(driver_port)
#    include(driver_dmamux)
#    include(driver_lptmr)
#    include(driver_gpio)
#    include(component_lists)
#    include(driver_dac)
#    include(device_system)
#    include(driver_cmp)
#    include(device_startup)
#    include(driver_pdb)
#    include(driver_adc16)
#    include(driver_clock)
#    include(utility_debug_console_lite)
#    include(driver_edma)
#    include(driver_ewm)
#    include(utility_assert)
#    include(driver_ftm)
#    include(utility_notifier)
#    include(driver_wdog)
#    include(CMSIS_Include_core_cm0plus)
#    include(utility_shell)
#    include(driver_flash)
#    include(component_uart_adapter)
#    include(driver_flexcan_edma)
#    include(driver_mmdvsq)
#    include(driver_sim)
#    include(utility_debug_console)
#    include(device_CMSIS)
#    include(driver_uart)
#    include(utilities_misc_utilities)
#    include(CMSIS_Include_common)
#    include(driver_common)
#    include(driver_smc)
#    include(driver_crc)
#    include(driver_fxos8700cq)
#    include(driver_pmc)
#    include(driver_rcm)
#    include(driver_dspi_edma)
