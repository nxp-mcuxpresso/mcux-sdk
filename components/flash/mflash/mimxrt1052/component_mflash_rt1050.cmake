#Description: mflash rt1050; user_visible: True
include_guard(GLOBAL)
message("component_mflash_rt1050 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mflash_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_mflash_common)
include(driver_cache_armv7_m7)
include(driver_flexspi)
