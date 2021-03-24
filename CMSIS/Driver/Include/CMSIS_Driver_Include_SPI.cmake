if(NOT CMSIS_DRIVER_INCLUDE_SPI_INCLUDED)

    set(CMSIS_DRIVER_INCLUDE_SPI_INCLUDED true CACHE BOOL "CMSIS_Driver_Include_SPI component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(CMSIS_Driver_Include_Common)

endif()