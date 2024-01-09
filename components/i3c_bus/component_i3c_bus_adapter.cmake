#Description: Component i3c_bus_adapter; user_visible: True
include_guard(GLOBAL)
message("component_i3c_bus_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_i3c_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_i3c)
include(component_i3c_bus)
