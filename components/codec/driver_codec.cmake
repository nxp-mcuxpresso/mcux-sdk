#Description: Driver codec; user_visible: True
include_guard(GLOBAL)
message("driver_codec component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_common.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_codec_wm8524_adapter) 
    include(component_codec_wm8524_adapter)
endif()
if(CONFIG_USE_component_tfa9xxx_adapter) 
    include(component_tfa9xxx_adapter)
endif()
if(CONFIG_USE_component_wm8960_adapter) 
    include(component_wm8960_adapter)
endif()
if(CONFIG_USE_component_cs42888_adapter) 
    include(component_cs42888_adapter)
endif()
if(CONFIG_USE_component_codec_ak4497_adapter) 
    include(component_codec_ak4497_adapter)
endif()
if(CONFIG_USE_component_wm8524_adapter) 
    include(component_wm8524_adapter)
endif()
if(CONFIG_USE_component_wm8904_adapter) 
    include(component_wm8904_adapter)
endif()
if(CONFIG_USE_component_da7212_adapter) 
    include(component_da7212_adapter)
endif()

include(driver_common)
