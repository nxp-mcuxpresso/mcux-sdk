#Description: Driver silicon_id_rt1170; user_visible: True
include_guard(GLOBAL)
message("component_silicon_id_rt1170 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_silicon_id_soc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(component_silicon_id_MIMXRT1166_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(component_silicon_id_MIMXRT1166_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(component_silicon_id_MIMXRT1176_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_silicon_id_MIMXRT1176_cm7)
endif()

