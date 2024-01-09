#Description: Middleware Edgefast Wi-Fi; user_visible: True
include_guard(GLOBAL)
message("middleware_edgefast_wifi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(middleware_wifi_RW612)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(middleware_wifi_MIMXRT1166_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(middleware_wifi_MIMXRT1052)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(middleware_wifi_MIMXRT1064)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(middleware_wifi_MIMXRT1062)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(middleware_wifi_MIMXRT1042)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(middleware_wifi_MIMXRT1176_cm7)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(middleware_wifi_MIMXRT685S_cm33)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(middleware_wifi_MIMXRT595S_cm33)
endif()

