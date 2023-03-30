#Description: Driver silicon_id; user_visible: True
include_guard(GLOBAL)
message("component_silicon_id component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_silicon_id.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_silicon_id_rt10xx)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(component_silicon_id_rt10xx)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(component_silicon_id_rt1170)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm4")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm4")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_silicon_id_rt1170)
endif()

include(driver_common)
