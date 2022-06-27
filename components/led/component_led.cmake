#Description: Component led; user_visible: True
include_guard(GLOBAL)
message("component_led component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_led.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    include(component_gpio_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MK64F12")
    include(component_gpio_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54628")
    include(component_lpc_gpio_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    include(component_gpio_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2A41A")
    include(component_gpio_adapter)
endif()

include(component_timer_manager)
