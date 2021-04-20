#Description: Driver slcd_engine; user_visible: True
include_guard(GLOBAL)
message("driver_slcd_engine component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/slcd_engine.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    include(driver_slcd_lcd_s401m16kr)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    include(driver_slcd_gdh_1247wp)
endif()

