#Description: Component button; user_visible: True
include_guard(GLOBAL)
message("component_button component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_button.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_rt_gpio_adapter) 
    include(component_rt_gpio_adapter)
endif()

include(component_timer_manager)
