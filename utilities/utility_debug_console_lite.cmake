#Description: Utility debug_console_lite; user_visible: True
include_guard(GLOBAL)
message("utility_debug_console_lite component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_console_lite/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/debug_console_lite
    ${CMAKE_CURRENT_LIST_DIR}/str
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5506CPXXXX")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    include(component_uart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core0")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core1")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core1")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(component_usart_adapter)
endif()

