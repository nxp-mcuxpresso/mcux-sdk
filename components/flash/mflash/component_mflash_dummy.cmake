#Description: dummy file; user_visible: False
include_guard(GLOBAL)
message("component_mflash_dummy component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mflash_dummy.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_mflash_file_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(component_mflash_file_MIMXRT1042)
endif()

