#Description: Serial Manager; user_visible: True
include_guard(GLOBAL)
message("component_serial_manager component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_serial_manager_uart) 
    include(component_serial_manager_uart)
endif()
if(CONFIG_USE_component_serial_manager_swo) 
    include(component_serial_manager_swo)
endif()

include(component_lists)
