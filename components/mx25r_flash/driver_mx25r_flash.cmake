if(NOT DRIVER_MX25R_FLASH_INCLUDED)

    set(DRIVER_MX25R_FLASH_INCLUDED true CACHE BOOL "driver_mx25r_flash component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/mx25r_flash.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()