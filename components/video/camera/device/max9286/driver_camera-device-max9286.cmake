if(NOT DRIVER_CAMERA-DEVICE-MAX9286_INCLUDED)

    set(DRIVER_CAMERA-DEVICE-MAX9286_INCLUDED true CACHE BOOL "driver_camera-device-max9286 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_max9286.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_camera-common)
    include(driver_video-common)
    include(driver_camera-device-common)
    include(driver_video-i2c)

endif()