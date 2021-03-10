if(NOT DRIVER_CAMERA-RECEIVER-ISI_INCLUDED)

    set(DRIVER_CAMERA-RECEIVER-ISI_INCLUDED true CACHE BOOL "driver_camera-receiver-isi component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_isi_camera_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_camera-receiver-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_camera-receiver-common)
    endif()

    include(driver_camera-common)
    include(driver_video-common)
    include(driver_isi)

endif()