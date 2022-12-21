#Description: Utility debug_console_lite; user_visible: True
include_guard(GLOBAL)
message("utility_debug_console_lite component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_debug_console.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MK64F12")
    include(component_uart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MK66F18")
    include(component_uart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE06Z4")
    include(component_uart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE04Z4")
    include(component_uart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm0plus")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
    include(component_usart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC812")
    include(component_miniusart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    include(component_lpuart_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MKL27Z644")
    include(component_lpuart_adapter)
endif()

