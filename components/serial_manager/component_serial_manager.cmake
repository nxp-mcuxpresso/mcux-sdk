#Description: Serial Manager; user_visible: True
include_guard(GLOBAL)
message("component_serial_manager component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_serial_manager_usb_cdc) 
    include(component_serial_manager_usb_cdc)
endif()
if(CONFIG_USE_component_serial_manager_uart_MK22F51212) 
    include(component_serial_manager_uart_MK22F51212)
endif()
if(CONFIG_USE_component_serial_manager_uart_MIMXRT1062) 
    include(component_serial_manager_uart_MIMXRT1062)
endif()
if(CONFIG_USE_component_serial_manager_uart_MIMXRT1176_cm4) 
    include(component_serial_manager_uart_MIMXRT1176_cm4)
endif()
if(CONFIG_USE_component_serial_manager_uart_MIMXRT595S_cm33) 
    include(component_serial_manager_uart_MIMXRT595S_cm33)
endif()
if(CONFIG_USE_component_serial_manager_swo) 
    include(component_serial_manager_swo)
endif()
if(CONFIG_USE_component_serial_manager_uart_MIMXRT1042) 
    include(component_serial_manager_uart_MIMXRT1042)
endif()
if(CONFIG_USE_component_serial_manager_uart_LPC55S69_cm33_core1) 
    include(component_serial_manager_uart_LPC55S69_cm33_core1)
endif()
if(CONFIG_USE_component_serial_manager_uart_LPC55S69_cm33_core0) 
    include(component_serial_manager_uart_LPC55S69_cm33_core0)
endif()
if(CONFIG_USE_component_serial_manager_uart_MIMXRT1176_cm7) 
    include(component_serial_manager_uart_MIMXRT1176_cm7)
endif()

include(component_lists)
