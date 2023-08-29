#Description: FLEXIO CAMERA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexio_camera component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/camera/fsl_flexio_camera.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/camera/.
)


include(driver_flexio)
