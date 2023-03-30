CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)
# OR Logic component
if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK22F51212
    )

    include(all_lib_device_MK22F51212)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1062
    )

    include(all_lib_device_MIMXRT1062)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1042
    )

    include(all_lib_device_MIMXRT1042)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1176
    )

    include(all_lib_device_MIMXRT1176_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1176
    )

    include(all_lib_device_MIMXRT1176_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core0")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S66
    )

    include(all_lib_device_LPC55S66_cm33_core0)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S66
    )

    include(all_lib_device_LPC55S66_cm33_core1)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S69
    )

    include(all_lib_device_LPC55S69_cm33_core1)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S69
    )

    include(all_lib_device_LPC55S69_cm33_core0)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT595S
    )

    include(all_lib_device_MIMXRT595S_cm33)

endif()

