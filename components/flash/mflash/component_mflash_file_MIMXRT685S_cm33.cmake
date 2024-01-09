#Description: statically allocated file system for mflash; user_visible: False
include_guard(GLOBAL)
message("component_mflash_file component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mflash_file.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_component_mflash_mimxrt685audevk) 
    include(component_mflash_mimxrt685audevk)
endif()
if(CONFIG_USE_component_mflash_rt685) 
    include(component_mflash_rt685)
endif()

