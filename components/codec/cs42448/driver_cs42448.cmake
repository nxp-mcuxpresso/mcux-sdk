#Description: Driver cs42448; user_visible: True
include_guard(GLOBAL)
message("driver_cs42448 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_cs42448.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(component_codec_i2c_MIMXRT1052)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_codec_i2c_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(component_codec_i2c_MIMXRT685S_cm33)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(component_codec_i2c_MIMXRT595S_cm33)
endif()

