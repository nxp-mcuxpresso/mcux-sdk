CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)
# OR Logic component
if(${MCUX_DEVICE} STREQUAL "MKV58F24")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV58F24
    )

    include(all_lib_device_MKV58F24)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE18F16")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE18F16
    )

    include(all_lib_device_MKE18F16)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S36")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S36
    )

    include(all_lib_device_LPC55S36)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1166
    )

    include(all_lib_device_MIMXRT1166_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1166
    )

    include(all_lib_device_MIMXRT1166_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5506CPXXXX")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5506CPXXXX
    )

    include(all_lib_device_LPC5506CPXXXX)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1052
    )

    include(all_lib_device_MIMXRT1052)

endif()

if(${MCUX_DEVICE} STREQUAL "MK22F12810")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK22F12810
    )

    include(all_lib_device_MK22F12810)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV10Z1287")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV10Z1287
    )

    include(all_lib_device_MKV10Z1287)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT633S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT633S
    )

    include(all_lib_device_MIMXRT633S_cm33)

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

if(${MCUX_DEVICE} STREQUAL "LPC5526")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5526
    )

    include(all_lib_device_LPC5526)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5504CPXXXX")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5504CPXXXX
    )

    include(all_lib_device_LPC5504CPXXXX)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54607")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54607
    )

    include(all_lib_device_LPC54607)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54S016")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S016
    )

    include(all_lib_device_LPC54S016)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC802")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC802
    )

    include(all_lib_device_LPC802)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54606")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54606
    )

    include(all_lib_device_LPC54606)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54616")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54616
    )

    include(all_lib_device_LPC54616)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN5
    )

    include(all_lib_device_MIMX8MN5)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN4
    )

    include(all_lib_device_MIMX8MN4)

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

if(${MCUX_DEVICE} STREQUAL "MIMX8MM6_ca53")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM6
    )

    include(all_lib_device_MIMX8MM6_ca53)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE15Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE15Z7
    )

    include(all_lib_device_MKE15Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S04")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S04
    )

    include(all_lib_device_LPC55S04)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM1
    )

    include(all_lib_device_MIMX8MM1)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2B31A
    )

    include(all_lib_device_K32L2B31A)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE16Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE16Z4
    )

    include(all_lib_device_MKE16Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S06")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S06
    )

    include(all_lib_device_LPC55S06)

endif()

if(${MCUX_DEVICE} STREQUAL "MKM14ZA5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM14ZA5
    )

    include(all_lib_device_MKM14ZA5)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54016")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54016
    )

    include(all_lib_device_LPC54016)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC832")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC832
    )

    include(all_lib_device_LPC832)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV11Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV11Z7
    )

    include(all_lib_device_MKV11Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54018")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54018
    )

    include(all_lib_device_LPC54018)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV31F51212")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV31F51212
    )

    include(all_lib_device_MKV31F51212)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE12Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE12Z7
    )

    include(all_lib_device_MKE12Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54628")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54628
    )

    include(all_lib_device_LPC54628)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5502CPXXXX")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5502CPXXXX
    )

    include(all_lib_device_LPC5502CPXXXX)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM5
    )

    include(all_lib_device_MIMX8MM5)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5512")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5512
    )

    include(all_lib_device_LPC5512)

endif()

if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK22F51212
    )

    include(all_lib_device_MK22F51212)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM2")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM2
    )

    include(all_lib_device_MIMX8MM2)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8ML3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8ML3
    )

    include(all_lib_device_MIMX8ML3)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5516")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5516
    )

    include(all_lib_device_LPC5516)

endif()

if(${MCUX_DEVICE} STREQUAL "MKM34ZA5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM34ZA5
    )

    include(all_lib_device_MKM34ZA5)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54605")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54605
    )

    include(all_lib_device_LPC54605)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1051")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1051
    )

    include(all_lib_device_MIMXRT1051)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54618")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54618
    )

    include(all_lib_device_LPC54618)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE13Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE13Z7
    )

    include(all_lib_device_MKE13Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE14Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE14Z7
    )

    include(all_lib_device_MKE14Z7)

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

if(${MCUX_DEVICE} STREQUAL "MKV10Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV10Z7
    )

    include(all_lib_device_MKV10Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM3
    )

    include(all_lib_device_MIMX8MM3)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT555S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT555S
    )

    include(all_lib_device_MIMXRT555S_cm33)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54018M")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54018M
    )

    include(all_lib_device_LPC54018M)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5506")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5506
    )

    include(all_lib_device_LPC5506)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5514")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5514
    )

    include(all_lib_device_LPC5514)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S16")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S16
    )

    include(all_lib_device_LPC55S16)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2B11A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2B11A
    )

    include(all_lib_device_K32L2B11A)

endif()

if(${MCUX_DEVICE} STREQUAL "MK02F12810")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK02F12810
    )

    include(all_lib_device_MK02F12810)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MQ7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MQ7
    )

    include(all_lib_device_MIMX8MQ7)

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

if(${MCUX_DEVICE} STREQUAL "MIMX8MN6_ca53")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN6
    )

    include(all_lib_device_MIMX8MN6_ca53)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8ML6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8ML6
    )

    include(all_lib_device_MIMX8ML6)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54S018")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S018
    )

    include(all_lib_device_LPC54S018)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE15Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE15Z4
    )

    include(all_lib_device_MKE15Z4)

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

if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S018M
    )

    include(all_lib_device_LPC54S018M)

endif()

if(${MCUX_DEVICE} STREQUAL "MK22F25612")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK22F25612
    )

    include(all_lib_device_MK22F25612)

endif()

if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM35Z7
    )

    include(all_lib_device_MKM35Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2B21A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2B21A
    )

    include(all_lib_device_K32L2B21A)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC51U68")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC51U68
    )

    include(all_lib_device_LPC51U68)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1061")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1061
    )

    include(all_lib_device_MIMXRT1061)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN2")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN2
    )

    include(all_lib_device_MIMX8MN2)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5528")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5528
    )

    include(all_lib_device_LPC5528)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1165_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1165
    )

    include(all_lib_device_MIMXRT1165_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1165_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1165
    )

    include(all_lib_device_MIMXRT1165_cm7)

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

if(${MCUX_DEVICE} STREQUAL "MIMX8ML4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8ML4
    )

    include(all_lib_device_MIMX8ML4)

endif()

if(${MCUX_DEVICE} STREQUAL "MKM34Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM34Z7
    )

    include(all_lib_device_MKM34Z7)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV31F12810")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV31F12810
    )

    include(all_lib_device_MKV31F12810)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MD6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MD6
    )

    include(all_lib_device_MIMX8MD6)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54S005")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54S005
    )

    include(all_lib_device_LPC54S005)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE17Z7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE17Z7
    )

    include(all_lib_device_MKE17Z7)

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

if(${MCUX_DEVICE} STREQUAL "K32L2A31A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2A31A
    )

    include(all_lib_device_K32L2A31A)

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

if(${MCUX_DEVICE} STREQUAL "MKM33ZA5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKM33ZA5
    )

    include(all_lib_device_MKM33ZA5)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1011
    )

    include(all_lib_device_MIMXRT1011)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54005")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54005
    )

    include(all_lib_device_LPC54005)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MM4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MM4
    )

    include(all_lib_device_MIMX8MM4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC834")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC834
    )

    include(all_lib_device_LPC834)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC822")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC822
    )

    include(all_lib_device_LPC822)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S28")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S28
    )

    include(all_lib_device_LPC55S28)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE14Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE14Z4
    )

    include(all_lib_device_MKE14Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN1
    )

    include(all_lib_device_MIMX8MN1)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC844")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC844
    )

    include(all_lib_device_LPC844)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT533S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT533S
    )

    include(all_lib_device_MIMXRT533S_cm33)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8ML8")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8ML8
    )

    include(all_lib_device_MIMX8ML8)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8ML8_ca53")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8ML8
    )

    include(all_lib_device_MIMX8ML8_ca53)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S14")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S14
    )

    include(all_lib_device_LPC55S14)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV31F25612")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV31F25612
    )

    include(all_lib_device_MKV31F25612)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV30F12810")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV30F12810
    )

    include(all_lib_device_MKV30F12810)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC55S26")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC55S26
    )

    include(all_lib_device_LPC55S26)

endif()

if(${MCUX_DEVICE} STREQUAL "K32L2A41A")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/K32L2A41A
    )

    include(all_lib_device_K32L2A41A)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5504")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5504
    )

    include(all_lib_device_LPC5504)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MN3
    )

    include(all_lib_device_MIMX8MN3)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54608")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54608
    )

    include(all_lib_device_LPC54608)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MD7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MD7
    )

    include(all_lib_device_MIMX8MD7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT685S
    )

    include(all_lib_device_MIMXRT685S_cm33)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT595S
    )

    include(all_lib_device_MIMXRT595S_cm33)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MQ5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8MQ5
    )

    include(all_lib_device_MIMX8MQ5)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5502")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5502
    )

    include(all_lib_device_LPC5502)

endif()

if(${MCUX_DEVICE} STREQUAL "MCIMX7U3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MCIMX7U3
    )

    include(all_lib_device_MCIMX7U3)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1015
    )

    include(all_lib_device_MIMXRT1015)

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

if(${MCUX_DEVICE} STREQUAL "MKE06Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE06Z4
    )

    include(all_lib_device_MKE06Z4)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE04Z4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE04Z4
    )

    include(all_lib_device_MKE04Z4)

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

if(${MCUX_DEVICE} STREQUAL "LPC812")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC812
    )

    include(all_lib_device_LPC812)

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

if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX6
    )

    include(all_lib_device_MIMX8QX6)

endif()

if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK28FA15
    )

    include(all_lib_device_MK28FA15)

endif()

if(${MCUX_DEVICE} STREQUAL "MKL27Z644")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKL27Z644
    )

    include(all_lib_device_MKL27Z644)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX1
    )

    include(all_lib_device_MIMX8DX1)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX3
    )

    include(all_lib_device_MIMX8DX3)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX2")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX2
    )

    include(all_lib_device_MIMX8DX2)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX5
    )

    include(all_lib_device_MIMX8DX5)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX4
    )

    include(all_lib_device_MIMX8DX4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8DX6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8DX6
    )

    include(all_lib_device_MIMX8DX6)

endif()

if(${MCUX_DEVICE} STREQUAL "MK24F12")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK24F12
    )

    include(all_lib_device_MK24F12)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX1")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX1
    )

    include(all_lib_device_MIMX8QX1)

endif()

if(${MCUX_DEVICE} STREQUAL "MK26F18")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK26F18
    )

    include(all_lib_device_MK26F18)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1175
    )

    include(all_lib_device_MIMXRT1175_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1175
    )

    include(all_lib_device_MIMXRT1175_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1172_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1172
    )

    include(all_lib_device_MIMXRT1172_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1173
    )

    include(all_lib_device_MIMXRT1173_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1173
    )

    include(all_lib_device_MIMXRT1173_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMXRT1171_cm7")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMXRT1171
    )

    include(all_lib_device_MIMXRT1171_cm7)

endif()

if(${MCUX_DEVICE} STREQUAL "MK63F12")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK63F12
    )

    include(all_lib_device_MK63F12)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC810")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC810
    )

    include(all_lib_device_LPC810)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC811")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC811
    )

    include(all_lib_device_LPC811)

endif()

if(${MCUX_DEVICE} STREQUAL "MK65F18")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK65F18
    )

    include(all_lib_device_MK65F18)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX4
    )

    include(all_lib_device_MIMX8QX4)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX5
    )

    include(all_lib_device_MIMX8QX5)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5536")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5536
    )

    include(all_lib_device_LPC5536)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX2")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX2
    )

    include(all_lib_device_MIMX8QX2)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE14F16")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE14F16
    )

    include(all_lib_device_MKE14F16)

endif()

if(${MCUX_DEVICE} STREQUAL "MK27FA15")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MK27FA15
    )

    include(all_lib_device_MK27FA15)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC54113_cm4")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC54113
    )

    include(all_lib_device_LPC54113_cm4)

endif()

if(${MCUX_DEVICE} STREQUAL "LPC5534")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/LPC5534
    )

    include(all_lib_device_LPC5534)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE04Z1284")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE04Z1284
    )

    include(all_lib_device_MKE04Z1284)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8QX3")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8QX3
    )

    include(all_lib_device_MIMX8QX3)

endif()

if(${MCUX_DEVICE} STREQUAL "MKL17Z644")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKL17Z644
    )

    include(all_lib_device_MKL17Z644)

endif()

if(${MCUX_DEVICE} STREQUAL "MKV56F24")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKV56F24
    )

    include(all_lib_device_MKV56F24)

endif()

if(${MCUX_DEVICE} STREQUAL "MKE16F16")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MKE16F16
    )

    include(all_lib_device_MKE16F16)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8UX5")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8UX5
    )

    include(all_lib_device_MIMX8UX5)

endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8UX6")
    list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/devices/MIMX8UX6
    )

    include(all_lib_device_MIMX8UX6)

endif()
