CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)
# OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1052
    )

    include(all_lib_device_MIMXRT1052)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1064
    )

    include(all_lib_device_MIMXRT1064)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC845")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC845
    )

    include(all_lib_device_LPC845)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC812")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC812
    )

    include(all_lib_device_LPC812)

endif()

if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK28FA15
    )

    include(all_lib_device_MK28FA15)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC802")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC802
    )

    include(all_lib_device_LPC802)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54114_cm0plus")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54114
    )

    include(all_lib_device_LPC54114_cm0plus)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54114
    )

    include(all_lib_device_LPC54114_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MQ6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MQ6
    )

    include(all_lib_device_MIMX8MQ6)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM6
    )

    include(all_lib_device_MIMX8MM6)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE15Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE15Z7
    )

    include(all_lib_device_MKE15Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2B31A
    )

    include(all_lib_device_K32L2B31A)

endif()

if(${MCUX_DEVICE} STREQUAL "MK64F12")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK64F12
    )

    include(all_lib_device_MK64F12)

endif()

if(${MCUX_DEVICE} STREQUAL "MK66F18")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK66F18
    )

    include(all_lib_device_MK66F18)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE16Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE16Z4
    )

    include(all_lib_device_MKE16Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QM6
    )

    include(all_lib_device_MIMX8QM6_cm4_core0)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QM6
    )

    include(all_lib_device_MIMX8QM6_cm4_core1)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV11Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV11Z7
    )

    include(all_lib_device_MKV11Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV31F51212")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV31F51212
    )

    include(all_lib_device_MKV31F51212)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54628")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54628
    )

    include(all_lib_device_LPC54628)

endif()

if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK22F51212
    )

    include(all_lib_device_MK22F51212)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE06Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE06Z4
    )

    include(all_lib_device_MKE06Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX6
    )

    include(all_lib_device_MIMX8QX6)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC824")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC824
    )

    include(all_lib_device_LPC824)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1021
    )

    include(all_lib_device_MIMXRT1021)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE02Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE02Z4
    )

    include(all_lib_device_MKE02Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S16")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S16
    )

    include(all_lib_device_LPC55S16)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1062
    )

    include(all_lib_device_MIMXRT1062)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN6
    )

    include(all_lib_device_MIMX8MN6)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54S018")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S018
    )

    include(all_lib_device_LPC54S018)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE04Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE04Z4
    )

    include(all_lib_device_MKE04Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC804")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC804
    )

    include(all_lib_device_LPC804)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L3A60
    )

    include(all_lib_device_K32L3A60_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm0plus")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L3A60
    )

    include(all_lib_device_K32L3A60_cm0plus)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S018M
    )

    include(all_lib_device_LPC54S018M)

endif()

if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM35Z7
    )

    include(all_lib_device_MKM35Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC51U68")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC51U68
    )

    include(all_lib_device_LPC51U68)

endif()

if(${MCUX_DEVICE} STREQUAL "MKL27Z644")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKL27Z644
    )

    include(all_lib_device_MKL27Z644)

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

if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MCIMX7U5
    )

    include(all_lib_device_MCIMX7U5)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1024
    )

    include(all_lib_device_MIMXRT1024)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1011
    )

    include(all_lib_device_MIMXRT1011)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S28")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S28
    )

    include(all_lib_device_LPC55S28)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2A41A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2A41A
    )

    include(all_lib_device_K32L2A41A)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT685S
    )

    include(all_lib_device_MIMXRT685S_cm33)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1015
    )

    include(all_lib_device_MIMXRT1015)

endif()

