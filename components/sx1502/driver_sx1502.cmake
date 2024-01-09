#Description: Driver sx1502; user_visible: True
include_guard(GLOBAL)
message("driver_sx1502 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_sx1502.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_flexcomm_i2c_adapter) 
    include(component_flexcomm_i2c_adapter)
endif()
if(CONFIG_USE_component_i3c_adapter) 
    include(component_i3c_adapter)
endif()

