if(NOT DRIVER_CAMERA-DEVICE-MT9M114_INCLUDED)

    set(DRIVER_CAMERA-DEVICE-MT9M114_INCLUDED true CACHE BOOL "driver_camera-device-mt9m114 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_mt9m114.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_camera-common)
    include(driver_video-common)
    include(driver_camera-device-common)
    include(driver_video-i2c)

endif()