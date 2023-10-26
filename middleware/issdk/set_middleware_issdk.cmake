include_guard(GLOBAL)


if (CONFIG_USE_middleware_issdk_sensor_tools)
# Add set(CONFIG_USE_middleware_issdk_sensor_tools true) in config.cmake to use this component

message("middleware_issdk_sensor_tools component is included from ${CMAKE_CURRENT_LIST_FILE}.")


endif()


if (CONFIG_USE_middleware_issdk_drivers_systick_utils)
# Add set(CONFIG_USE_middleware_issdk_drivers_systick_utils true) in config.cmake to use this component

message("middleware_issdk_drivers_systick_utils component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/systick/systick_utils.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/systick
)


endif()


if (CONFIG_USE_middleware_issdk_sensor_allregdefs)
# Add set(CONFIG_USE_middleware_issdk_sensor_allregdefs true) in config.cmake to use this component

message("middleware_issdk_sensor_allregdefs component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_allregdefs dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxas21002)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxas21002 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxas21002 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxas21002_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxas21002 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxos8700)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxos8700 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxos8700 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxos8700_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxos8700 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mpl3115)
# Add set(CONFIG_USE_middleware_issdk_sensor_mpl3115 true) in config.cmake to use this component

message("middleware_issdk_sensor_mpl3115 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mpl3115_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mpl3115 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxlc95000)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxlc95000 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxlc95000 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxlc95000_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxlc95000 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mma8491q)
# Add set(CONFIG_USE_middleware_issdk_sensor_mma8491q true) in config.cmake to use this component

message("middleware_issdk_sensor_mma8491q component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mma8491q_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mma8491q dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls8471q)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls8471q true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls8471q component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls8471q_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls8471q dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mag3110)
# Add set(CONFIG_USE_middleware_issdk_sensor_mag3110 true) in config.cmake to use this component

message("middleware_issdk_sensor_mag3110 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mag3110_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mag3110 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mma845x)
# Add set(CONFIG_USE_middleware_issdk_sensor_mma845x true) in config.cmake to use this component

message("middleware_issdk_sensor_mma845x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mma845x_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mma845x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mma865x)
# Add set(CONFIG_USE_middleware_issdk_sensor_mma865x true) in config.cmake to use this component

message("middleware_issdk_sensor_mma865x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mma865x_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mma865x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxpq3115)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxpq3115 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxpq3115 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxpq3115_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxpq3115 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls8962)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls8962 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls8962 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls8962_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls8962 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_mma9553)
# Add set(CONFIG_USE_middleware_issdk_sensor_mma9553 true) in config.cmake to use this component

message("middleware_issdk_sensor_mma9553 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/mma9553_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_mma9553 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_nps300x)
# Add set(CONFIG_USE_middleware_issdk_sensor_nps300x true) in config.cmake to use this component

message("middleware_issdk_sensor_nps300x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/diff_p_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_nps300x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_isl29023)
# Add set(CONFIG_USE_middleware_issdk_sensor_isl29023 true) in config.cmake to use this component

message("middleware_issdk_sensor_isl29023 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/isl29023_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_isl29023 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxps7250d4)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxps7250d4 true) in config.cmake to use this component

message("middleware_issdk_sensor_fxps7250d4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/dbap_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxps7250d4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls896xaf)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls896xaf true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls896xaf component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls896x_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls896xaf dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls8974cf)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls8974cf true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls8974cf component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls8974_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls8974cf dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls8961af)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls8961af true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls8961af component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls8961_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls8961af dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_fxls8971cf)
# Add set(CONFIG_USE_middleware_issdk_sensor_fxls8971cf true) in config.cmake to use this component

message("middleware_issdk_sensor_fxls8971cf component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/fxls8971_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_fxls8971cf dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_nmh1000)
# Add set(CONFIG_USE_middleware_issdk_sensor_nmh1000 true) in config.cmake to use this component

message("middleware_issdk_sensor_nmh1000 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/nmh1000_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_nmh1000 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_sensor_interface_common)
# Add set(CONFIG_USE_middleware_issdk_sensor_interface_common true) in config.cmake to use this component

message("middleware_issdk_sensor_interface_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/register_io_i2c.c
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/register_io_spi.c
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/sensor_io_spi.c
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/sensor_io_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
)

else()

message(SEND_ERROR "middleware_issdk_sensor_interface_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_kinetis)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_kinetis true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_kinetis component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MK22FN128xxx10 OR CONFIG_DEVICE_ID STREQUAL MK22FN128xxx12 OR CONFIG_DEVICE_ID STREQUAL MK22FN256xxx12 OR CONFIG_DEVICE_ID STREQUAL MK22FN512xxx12 OR CONFIG_DEVICE_ID STREQUAL MK02FN128xxx10 OR CONFIG_DEVICE_ID STREQUAL MK02FN64xxx10 OR CONFIG_DEVICE_ID STREQUAL MKE14Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE14Z128xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z128xxx7 OR CONFIG_DEVICE_ID STREQUAL K32L3A60xxx))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis/gpio_driver_irq.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_kinetis dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_kinetis_ke15z)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_kinetis_ke15z true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_kinetis_ke15z component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MKE14Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE14Z128xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z128xxx7))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis/gpio_driver_irq_ke15z.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/kinetis
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_kinetis_ke15z dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_lpc)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_lpc true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_lpc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S69 OR CONFIG_DEVICE_ID STREQUAL LPC55S66 OR CONFIG_DEVICE_ID STREQUAL LPC55S16 OR CONFIG_DEVICE_ID STREQUAL LPC55S14 OR CONFIG_DEVICE_ID STREQUAL LPC5512 OR CONFIG_DEVICE_ID STREQUAL LPC5514 OR CONFIG_DEVICE_ID STREQUAL LPC5516 OR CONFIG_DEVICE_ID STREQUAL LPC5502 OR CONFIG_DEVICE_ID STREQUAL LPC5504 OR CONFIG_DEVICE_ID STREQUAL LPC5506 OR CONFIG_DEVICE_ID STREQUAL LPC55S04 OR CONFIG_DEVICE_ID STREQUAL LPC55S06))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/lpc/gpio_driver_irq.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/lpc/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/lpc
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_imx)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imx true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imx component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1051xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1052xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1021xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1024xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1041xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1042xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1064xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1011xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT685S OR CONFIG_DEVICE_ID STREQUAL MIMXRT633S OR CONFIG_DEVICE_ID STREQUAL MIMXRT1171xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1172xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1173xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1175xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1165xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT533S OR CONFIG_DEVICE_ID STREQUAL MIMXRT555S OR CONFIG_DEVICE_ID STREQUAL MIMXRT595S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/gpio_driver_irq.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_imx dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_imx8)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imx8 true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imx8 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1051xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1052xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1021xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1024xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1041xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1042xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1064xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1011xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT685S OR CONFIG_DEVICE_ID STREQUAL MIMXRT633S OR CONFIG_DEVICE_ID STREQUAL MIMXRT1171xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1172xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1173xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1175xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1165xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT533S OR CONFIG_DEVICE_ID STREQUAL MIMXRT555S OR CONFIG_DEVICE_ID STREQUAL MIMXRT595S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_imx8 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_imxrt600)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imxrt600 true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imxrt600 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1051xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1052xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1021xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1024xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1041xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1042xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1064xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1011xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT685S OR CONFIG_DEVICE_ID STREQUAL MIMXRT633S OR CONFIG_DEVICE_ID STREQUAL MIMXRT1171xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1172xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1173xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1175xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1165xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT533S OR CONFIG_DEVICE_ID STREQUAL MIMXRT555S OR CONFIG_DEVICE_ID STREQUAL MIMXRT595S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/i.mxrt600/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/i.mxrt600
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_imxrt600 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_imxrt1180)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imxrt1180 true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imxrt1180 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1051xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1052xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1021xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1024xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1041xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1042xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1064xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1011xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT685S OR CONFIG_DEVICE_ID STREQUAL MIMXRT633S OR CONFIG_DEVICE_ID STREQUAL MIMXRT1171xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1172xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1173xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1175xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1165xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT533S OR CONFIG_DEVICE_ID STREQUAL MIMXRT555S OR CONFIG_DEVICE_ID STREQUAL MIMXRT595S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/i.mxrt1180/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/i.mxrt1180
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_imxrt1180 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_gpio_imxrt)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imxrt true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imxrt component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1051xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1052xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1021xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1024xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1041xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1042xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1064xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1015xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1011xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT685S OR CONFIG_DEVICE_ID STREQUAL MIMXRT633S OR CONFIG_DEVICE_ID STREQUAL MIMXRT1171xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1172xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1173xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1175xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1165xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT1166xxxxx OR CONFIG_DEVICE_ID STREQUAL MIMXRT533S OR CONFIG_DEVICE_ID STREQUAL MIMXRT555S OR CONFIG_DEVICE_ID STREQUAL MIMXRT595S))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio/i.mx
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/gpio
)

else()

message(SEND_ERROR "middleware_issdk_drivers_gpio_imxrt dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_ads)
# Add set(CONFIG_USE_middleware_issdk_drivers_ads true) in config.cmake to use this component

message("middleware_issdk_drivers_ads component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MK22FN128xxx10 OR CONFIG_DEVICE_ID STREQUAL MK22FN128xxx12 OR CONFIG_DEVICE_ID STREQUAL MK22FN256xxx12 OR CONFIG_DEVICE_ID STREQUAL MK22FN512xxx12 OR CONFIG_DEVICE_ID STREQUAL MK02FN128xxx10 OR CONFIG_DEVICE_ID STREQUAL MK02FN64xxx10 OR CONFIG_DEVICE_ID STREQUAL MKE14Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE14Z128xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z256xxx7 OR CONFIG_DEVICE_ID STREQUAL MKE15Z128xxx7 OR CONFIG_DEVICE_ID STREQUAL K32L3A60xxx))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads/kinetis/auto_detection_service.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads/kinetis
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads
)

else()

message(SEND_ERROR "middleware_issdk_drivers_ads dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_ads_lpc)
# Add set(CONFIG_USE_middleware_issdk_drivers_ads_lpc true) in config.cmake to use this component

message("middleware_issdk_drivers_ads_lpc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S69 OR CONFIG_DEVICE_ID STREQUAL LPC55S66 OR CONFIG_DEVICE_ID STREQUAL LPC55S16 OR CONFIG_DEVICE_ID STREQUAL LPC55S14 OR CONFIG_DEVICE_ID STREQUAL LPC5512 OR CONFIG_DEVICE_ID STREQUAL LPC5514 OR CONFIG_DEVICE_ID STREQUAL LPC5516 OR CONFIG_DEVICE_ID STREQUAL LPC5502 OR CONFIG_DEVICE_ID STREQUAL LPC5504 OR CONFIG_DEVICE_ID STREQUAL LPC5506 OR CONFIG_DEVICE_ID STREQUAL LPC55S04 OR CONFIG_DEVICE_ID STREQUAL LPC55S06))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads/lpc/auto_detection_service.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads/lpc
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/ads
)

else()

message(SEND_ERROR "middleware_issdk_drivers_ads_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_drivers_host)
# Add set(CONFIG_USE_middleware_issdk_drivers_host true) in config.cmake to use this component

message("middleware_issdk_drivers_host component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./sensors/host_io_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/host/comm_if_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/host/data_format_hdlc.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/host/data_format_json.c
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/host/host_interface_service.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./sensors
  ${CMAKE_CURRENT_LIST_DIR}/./drivers/host
)

else()

message(SEND_ERROR "middleware_issdk_drivers_host dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agm01_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agm01_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_agm01_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXOS8700.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MPL3115.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_pit.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_agm01_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_lpc_agm01_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_lpc_agm01_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_lpc_agm01_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control_lpc.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXOS8700.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MPL3115.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_lpc_agm01_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agm04_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agm04_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_agm04_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MMA8652.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MAG3110.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_pit.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_agm04_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agmp03_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_agmp03_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_agmp03_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXLS8962.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MAG3110.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MPL3115.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_pit.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_agmp03_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_lpc_agmp03_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_lpc_agmp03_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_lpc_agmp03_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control_lpc.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXLS8962.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MAG3110.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MPL3115.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_lpc_agmp03_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_mult2b_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_sensor_fusion_mult2b_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_sensor_fusion_mult2b_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/approximations.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/calibration_storage.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/control.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/debug.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/DecodeCommandBytes.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXAS21002.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_FXOS8700.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_MPL3115.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_KSDK_NVM.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_pit.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/driver_systick.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/hal_frdm_fxs_mult2_b.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/magnetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/orientation.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/output_stream.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/precisionAccelerometer.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/sensor_fusion.c
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources/status.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/sensorfusion/sources
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_sensor_fusion_mult2b_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_pedometer_common)
# Add set(CONFIG_USE_middleware_issdk_algorithms_pedometer_common true) in config.cmake to use this component

message("middleware_issdk_algorithms_pedometer_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_CMSIS_Driver_Include_I2C AND CONFIG_USE_CMSIS_Driver_Include_SPI)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/pedometer/source/pedometer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/pedometer/include
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/pedometer/include/libinclude
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_pedometer_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_pedometer_lib_cm4)
# Add set(CONFIG_USE_middleware_issdk_algorithms_pedometer_lib_cm4 true) in config.cmake to use this component

message("middleware_issdk_algorithms_pedometer_lib_cm4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE STREQUAL cm4f))

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
  -Wl,--start-group
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/pedometer/lib/libpedometerm4.a
  -Wl,--end-group
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_pedometer_lib_cm4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_issdk_algorithms_pedometer_lib_cm0)
# Add set(CONFIG_USE_middleware_issdk_algorithms_pedometer_lib_cm0 true) in config.cmake to use this component

message("middleware_issdk_algorithms_pedometer_lib_cm0 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE STREQUAL cm0p))

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
  -Wl,--start-group
  ${CMAKE_CURRENT_LIST_DIR}/./algorithms/pedometer/lib/libpedometerm0.a
  -Wl,--end-group
)

else()

message(SEND_ERROR "middleware_issdk_algorithms_pedometer_lib_cm0 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

