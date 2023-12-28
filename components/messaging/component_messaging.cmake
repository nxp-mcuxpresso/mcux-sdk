#Description: Component messaging; user_visible: True
include_guard(GLOBAL)
message("component_messaging component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_messaging.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(component_mem_manager_light)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(component_mem_manager_light)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_mem_manager)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_mem_manager)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(component_mem_manager)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(component_mem_manager)
endif()

