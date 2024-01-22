#Description: Component timer_manager; user_visible: True
include_guard(GLOBAL)
message("component_timer_manager component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_timer_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_pit_adapter) 
    include(component_pit_adapter)
endif()
if(CONFIG_USE_component_ctimer_adapter) 
    include(component_ctimer_adapter)
endif()
if(CONFIG_USE_component_tpm_adapter) 
    include(component_tpm_adapter)
endif()
if(CONFIG_USE_component_lpit_adapter) 
    include(component_lpit_adapter)
endif()
if(CONFIG_USE_component_mrt_adapter) 
    include(component_mrt_adapter)
endif()
if(CONFIG_USE_component_ftm_adapter) 
    include(component_ftm_adapter)
endif()
if(CONFIG_USE_component_gpt_adapter) 
    include(component_gpt_adapter)
endif()

include(component_lists)
