#Description: UTICK Driver; user_visible: True
include_guard(GLOBAL)
message("driver_utick component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_utick.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(driver_power)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(driver_power)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5506CPXXXX")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT633S_cm33")
    include(driver_power)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core0")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(driver_power)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5502")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm0plus")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54113_cm4")
    include(driver_common)
endif()

