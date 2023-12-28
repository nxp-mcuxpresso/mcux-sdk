#Description: wireless_imu_adapter; user_visible: True
include_guard(GLOBAL)
message("component_wireless_imu_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_rfimu.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_osa_free_rtos_RW612) 
    include(component_osa_free_rtos_RW612)
endif()
if(CONFIG_USE_component_osa_bm) 
    include(component_osa_bm)
endif()

include(driver_gdma)
include(driver_imu)
