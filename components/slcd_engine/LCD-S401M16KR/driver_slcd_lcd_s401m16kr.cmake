if(NOT DRIVER_SLCD_LCD_S401M16KR_INCLUDED)

    set(DRIVER_SLCD_LCD_S401M16KR_INCLUDED true CACHE BOOL "driver_slcd_lcd_s401m16kr component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/LCD-S401M16KR.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()