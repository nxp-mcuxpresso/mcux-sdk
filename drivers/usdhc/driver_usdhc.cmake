#Description: USDHC Driver; user_visible: True
include_guard(GLOBAL)
message("driver_usdhc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_usdhc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(driver_memory)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(driver_memory)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm0plus")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm4")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(driver_memory)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(driver_memory)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(driver_common)
endif()

