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


if (CONFIG_USE_middleware_issdk_drivers_gpio_imx)
# Add set(CONFIG_USE_middleware_issdk_drivers_gpio_imx true) in config.cmake to use this component

message("middleware_issdk_drivers_gpio_imx component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB))

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

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB))

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

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB))

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

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB))

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

if((CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1061xxxxB OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxA OR CONFIG_DEVICE_ID STREQUAL MIMXRT1062xxxxB))

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

