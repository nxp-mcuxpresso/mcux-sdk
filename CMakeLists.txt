if(CONFIG_HAS_MCUX OR CONFIG_HAS_IMX_HAL)
  zephyr_library()
endif()

set(MCUX_SDK_PROJECT_NAME ${ZEPHYR_CURRENT_LIBRARY})
# Translate the SoC name and part number into the mcux device and cpu
# name respectively.
string(TOUPPER ${CONFIG_SOC} MCUX_DEVICE)

if("${MCUX_DEVICE}" STREQUAL "LPC54114")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm4)
elseif("${MCUX_DEVICE}" STREQUAL "LPC54114_M0")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm0plus)
  set(MCUX_DEVICE LPC54114)
elseif("${MCUX_DEVICE}" STREQUAL "LPC55S16")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER})
elseif("${MCUX_DEVICE}" STREQUAL "LPC55S28")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER})
elseif("${MCUX_DEVICE}" STREQUAL "LPC55S69_CPU0")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm33_core0)
  set(MCUX_DEVICE LPC55S69)
elseif("${MCUX_DEVICE}" STREQUAL "LPC55S69_CPU1")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm33_core1)
  set(MCUX_DEVICE LPC55S69)
elseif("${MCUX_DEVICE}" STREQUAL "MIMXRT1052")
  string(REGEX REPLACE "(.*)[AB]$" "CPU_\\1B" MCUX_CPU ${CONFIG_SOC_PART_NUMBER})
elseif("${MCUX_DEVICE}" STREQUAL "MIMXRT685S_CM33")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm33)
  set(MCUX_DEVICE MIMXRT685S)
elseif("${MCUX_DEVICE}" STREQUAL "MIMXRT1176_CM4")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm4)
  set(MCUX_DEVICE MIMXRT1176)
elseif("${MCUX_DEVICE}" STREQUAL "MIMXRT1176_CM7")
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER}_cm7)
  set(MCUX_DEVICE MIMXRT1176)
else()
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER})
endif()

zephyr_include_directories(devices/${MCUX_DEVICE})
zephyr_include_directories(devices/${MCUX_DEVICE}/drivers)
# The mcux uses the cpu name to expose SoC-specific features of a
# given peripheral. For example, the UART peripheral may be
# instantiated with/without a hardware FIFO, and the size of that FIFO
# may be different for each instance in a given SoC. See
# fsl_device_registers.h and ${MCUX_DEVICE}_features.h
zephyr_compile_definitions(${MCUX_CPU})

# Build mcux device-specific objects. Although it is not normal
# practice, drilling down like this avoids the need for repetitive
# build scripts for every mcux device.
zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_clock.c)
if (${MCUX_DEVICE} MATCHES "LPC|MIMXRT6")
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_power.c)
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_reset.c)

  if ((${MCUX_DEVICE} MATCHES "MIMXRT6") AND (CONFIG_PM))
    zephyr_code_relocate(devices/${MCUX_DEVICE}/drivers/fsl_power.c SRAM)
  endif()
endif()

if (${MCUX_DEVICE} MATCHES "MIMXRT117")
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_romapi.c)
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_pmu.c)
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_dcdc.c)
  zephyr_library_sources(devices/${MCUX_DEVICE}/drivers/fsl_anatop_ai.c)
  if ("${MCUX_DEVICE}" STREQUAL "MIMXRT1176_CM4")
    zephyr_include_directories(devices/${MCUX_DEVICE}/cm4/)
    zephyr_library_sources_ifdef(
      CONFIG_HAS_MCUX_CACHE
      devices/${MCUX_DEVICE}/cm4/fsl_cache.c
    )
  endif()
endif()

#Include Entry cmake component
include(${CMAKE_CURRENT_LIST_DIR}/zephyr/hal_nxp.cmake)
enable_language(C ASM)
