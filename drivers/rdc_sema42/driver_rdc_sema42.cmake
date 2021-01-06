if(NOT DRIVER_RDC_SEMA42_INCLUDED)

    set(DRIVER_RDC_SEMA42_INCLUDED true CACHE BOOL "driver_rdc_sema42 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_rdc_sema42.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()