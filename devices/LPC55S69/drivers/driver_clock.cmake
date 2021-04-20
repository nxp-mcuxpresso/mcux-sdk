#Description: Clock Driver; user_visible: True
include_guard(GLOBAL)
message("driver_clock component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_clock.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(CONFIG_USE_driver_power) 
    include(driver_power)
endif()

