# SPDX-License-Identifier: Apache-2.0

# Folders needed for conf/mconf files (kconfig has no method of redirecting all output files).
# conf/mconf needs to be run from a different directory because of: GH-3408
file(MAKE_DIRECTORY ${APPLICATION_BINARY_DIR}/kconfig/include/generated)
file(MAKE_DIRECTORY ${APPLICATION_BINARY_DIR}/kconfig/include/config)

if(KCONFIG_ROOT)
  # KCONFIG_ROOT has either been specified as a CMake variable or is
  # already in the CMakeCache.txt. This has precedence.
elseif(EXISTS   ${APPLICATION_SOURCE_DIR}/Kconfig)
  set(KCONFIG_ROOT ${APPLICATION_SOURCE_DIR}/Kconfig)
endif()

if (EXISTS ${BOARD_DIR}/${BOARD}_defconfig)
set(BOARD_DEFCONFIG ${BOARD_DIR}/${BOARD}_defconfig)
endif()

if(EXISTS ${APPLICATION_SOURCE_DIR}/config.cmake)
  set(DOTCONFIG_IN                ${APPLICATION_SOURCE_DIR}/config.cmake)
else()
  set(DOTCONFIG_IN                ${APPLICATION_SOURCE_DIR}/.config)
endif()
set(DOTCONFIG_OUT                ${APPLICATION_SOURCE_DIR}/.config)
set(PARSED_KCONFIG_SOURCES_TXT ${APPLICATION_BINARY_DIR}/kconfig/sources.txt)

if(CONF_FILE)
string(REPLACE " " ";" CONF_FILE_AS_LIST "${CONF_FILE}")
endif()

if(OVERLAY_CONFIG)
  string(REPLACE " " ";" OVERLAY_CONFIG_AS_LIST "${OVERLAY_CONFIG}")
endif()

# DTS_ROOT_BINDINGS is a semicolon separated list, this causes
# problems when invoking kconfig_target since semicolon is a special
# character in the C shell, so we make it into a question-mark
# separated list instead.
string(REPLACE ";" "?" DTS_ROOT_BINDINGS "${DTS_ROOT_BINDINGS}")

set(ENV{srctree}            ${PROJECT_ROOT})
set(ENV{KCONFIG_BASE}       ${PROJECT_ROOT})

# Not used in current MCUXpresso SDK, take from zephyr cmake build system
set(ENV{KERNELVERSION}      ${KERNELVERSION})

set(ENV{KCONFIG_CONFIG}     ${DOTCONFIG_IN})
set(ENV{PYTHON_EXECUTABLE}  ${PYTHON_EXECUTABLE})

message("project root: ${PROJECT_ROOT}")

# Set environment variables so that Kconfig can prune Kconfig source
# files for other architectures
set(ENV{BOARD_DIR} ${BOARD_DIR})

# Below environment variables currently not used in MCUXpresso SDK, take from zephyr cmake build system, remain it for future use.
set(ENV{ARCH}      ${ARCH})
set(ENV{SOC_DIR}   ${SOC_DIR})
set(ENV{SHIELD_AS_LIST} "${SHIELD_AS_LIST}")
set(ENV{CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR})
set(ENV{ARCH_DIR}   ${ARCH_DIR})
set(ENV{DEVICETREE_CONF} ${DEVICETREE_CONF})
set(ENV{DTS_POST_CPP} ${DTS_POST_CPP})
set(ENV{DTS_ROOT_BINDINGS} "${DTS_ROOT_BINDINGS}")
set(ENV{TOOLCHAIN_KCONFIG_DIR} "${TOOLCHAIN_KCONFIG_DIR}")

# Allow out-of-tree users to add their own Kconfig python frontend
# targets by appending targets to the CMake list
# 'EXTRA_KCONFIG_TARGETS' and setting variables named
# 'EXTRA_KCONFIG_TARGET_COMMAND_FOR_<target>'
#
# e.g.
# cmake -DEXTRA_KCONFIG_TARGETS=cli
# -DEXTRA_KCONFIG_TARGET_COMMAND_FOR_cli=cli_kconfig_frontend.py

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_menuconfig
  ${PROJECT_ROOT}/scripts/kconfig/menuconfig.py
  )

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_guiconfig
  ${PROJECT_ROOT}/scripts/kconfig/guiconfig.py
  )

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_hardenconfig
  ${PROJECT_ROOT}/scripts/kconfig/hardenconfig.py
  )

foreach(kconfig_target
    menuconfig
    guiconfig
    hardenconfig
    ${EXTRA_KCONFIG_TARGETS}
    )
  add_custom_target(
    ${kconfig_target}
    ${CMAKE_COMMAND} -E env
    PYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}
    KCONFIG_BASE=${PROJECT_ROOT}
    KCONFIG_CONFIG=${DOTCONFIG_IN}
    ARCH=$ENV{ARCH}
    BOARD_DIR=$ENV{BOARD_DIR}
    SOC_DIR=$ENV{SOC_DIR}
    SHIELD_AS_LIST=$ENV{SHIELD_AS_LIST}
    CMAKE_BINARY_DIR=$ENV{CMAKE_BINARY_DIR}
    TOOLCHAIN_KCONFIG_DIR=${TOOLCHAIN_KCONFIG_DIR}
    ARCH_DIR=$ENV{ARCH_DIR}
    DEVICETREE_CONF=${DEVICETREE_CONF}
    DTS_POST_CPP=${DTS_POST_CPP}
    DTS_ROOT_BINDINGS=${DTS_ROOT_BINDINGS}
    ${PYTHON_EXECUTABLE}
    ${PROJECT_ROOT}/scripts/kconfig/mcux.py
    ${kconfig_target}
    ${KCONFIG_ROOT}
    WORKING_DIRECTORY ${APPLICATION_BINARY_DIR}/kconfig
    USES_TERMINAL
    )
endforeach()

# Support assigning Kconfig symbols on the command-line with CMake
# cache variables prefixed with 'CONFIG_'. This feature is
# experimental and undocumented until it has undergone more
# user-testing.
unset(EXTRA_KCONFIG_OPTIONS)
get_cmake_property(cache_variable_names CACHE_VARIABLES)
foreach (name ${cache_variable_names})
  if("${name}" MATCHES "^CONFIG_")
    # When a cache variable starts with 'CONFIG_', it is assumed to be
    # a Kconfig symbol assignment from the CMake command line.
    set(EXTRA_KCONFIG_OPTIONS
      "${EXTRA_KCONFIG_OPTIONS}\n${name}=${${name}}"
      )
  endif()
endforeach()

if(EXTRA_KCONFIG_OPTIONS)
  set(EXTRA_KCONFIG_OPTIONS_FILE ${APPLICATION_BINARY_DIR}/misc/generated/extra_kconfig_options.conf)
  file(WRITE
    ${EXTRA_KCONFIG_OPTIONS_FILE}
    ${EXTRA_KCONFIG_OPTIONS}
    )
endif()

# Bring in extra configuration files dropped in by the user or anyone else;
# make sure they are set at the end so we can override any other setting
set(config_files ${APPLICATION_SOURCE_DIR}/config.cmake)
set(
  merge_config_files
  ${BOARD_DEFCONFIG}
  ${CONF_FILE_AS_LIST}
  ${shield_conf_files}
  ${OVERLAY_CONFIG_AS_LIST}
  ${EXTRA_KCONFIG_OPTIONS_FILE}
  ${config_files}
)

# Create a list of absolute paths to the .config sources from
# merge_config_files, which is a mix of absolute and relative paths.
set(merge_config_files_with_absolute_paths "")
foreach(f ${merge_config_files})
  if(IS_ABSOLUTE ${f})
    set(path ${f})
  else()
    set(path ${APPLICATION_SOURCE_DIR}/${f})
  endif()

  list(APPEND merge_config_files_with_absolute_paths ${path})
endforeach()

foreach(f ${merge_config_files_with_absolute_paths})
  if(NOT EXISTS ${f} OR IS_DIRECTORY ${f})
    message(FATAL_ERROR "File not found: ${f}")
  endif()
endforeach()

# Calculate a checksum of merge_config_files to determine if we need
# to re-generate .config
set(merge_config_files_checksum "")
foreach(f ${merge_config_files_with_absolute_paths})
  file(MD5 ${f} checksum)
  set(merge_config_files_checksum "${merge_config_files_checksum}${checksum}")
endforeach()

# Create a new .config if it does not exists, or if the checksum of
# the dependencies has changed
set(merge_config_files_checksum_file ${APPLICATION_BINARY_DIR}/.cmake.dotconfig.checksum)
set(CREATE_NEW_DOTCONFIG 1)
# Check if the checksum file exists too before trying to open it, though it
# should under normal circumstances
if(EXISTS ${DOTCONFIG_OUT} AND EXISTS ${merge_config_files_checksum_file})
  # Read out what the checksum was previously
  file(READ
    ${merge_config_files_checksum_file}
    merge_config_files_checksum_prev
    )
  if(
      ${merge_config_files_checksum} STREQUAL
      ${merge_config_files_checksum_prev}
      )
    # Checksum is the same as before
    set(CREATE_NEW_DOTCONFIG 0)
  endif()
endif()

if(CREATE_NEW_DOTCONFIG)
#  set(input_configs_are_handwritten --handwritten-input-configs="")
  set(input_configs ${merge_config_files})
else()
  set(input_configs ${DOTCONFIG_IN})
endif()


message(
  ${PYTHON_EXECUTABLE}
  ${PROJECT_ROOT}/scripts/kconfig/kconfig.py
  ${input_configs_are_handwritten}
  ${KCONFIG_ROOT}
  ${DOTCONFIG_OUT}
  ${AUTOCONF_H}
  ${PARSED_KCONFIG_SOURCES_TXT}
  ${input_configs}
  )
execute_process(
  COMMAND
  ${PYTHON_EXECUTABLE}
  ${PROJECT_ROOT}/scripts/kconfig/kconfig.py
  ${input_configs_are_handwritten}
  ${KCONFIG_ROOT}
  ${DOTCONFIG_OUT}
  ${AUTOCONF_H}
  ${PARSED_KCONFIG_SOURCES_TXT}
  ${input_configs}
  WORKING_DIRECTORY ${PROJECT_ROOT}
  # The working directory is set to the app dir such that the user
  # can use relative paths in CONF_FILE, e.g. CONF_FILE=nrf5.conf
  RESULT_VARIABLE ret
  )
if(NOT "${ret}" STREQUAL "0")
  message(FATAL_ERROR "command failed with return code: ${ret}")
endif()

if(CREATE_NEW_DOTCONFIG)
  # Write the new configuration fragment checksum. Only do this if kconfig.py
  # succeeds, to avoid marking APPLICATION_BINARY_DIR/.config as up-to-date when it hasn't been
  # regenerated.
  file(WRITE ${merge_config_files_checksum_file}
             ${merge_config_files_checksum})
endif()

# Read out the list of 'Kconfig' sources that were used by the engine.
file(STRINGS ${PARSED_KCONFIG_SOURCES_TXT} PARSED_KCONFIG_SOURCES_LIST)

# Force CMAKE configure when the Kconfig sources or configuration files changes.
foreach(kconfig_input
    ${merge_config_files}
    ${DOTCONFIG_IN}
    ${PARSED_KCONFIG_SOURCES_LIST}
    )
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${kconfig_input})
endforeach()

add_custom_target(config-sanitycheck DEPENDS ${DOTCONFIG_OUT})

# Remove the CLI Kconfig symbols from the namespace and
# CMakeCache.txt. If the symbols end up in DOTCONFIG they will be
# re-introduced to the namespace through 'import_kconfig'.
foreach (name ${cache_variable_names})
  if("${name}" MATCHES "^CONFIG_")
    unset(${name})
    unset(${name} CACHE)
  endif()
endforeach()

# Parse the lines prefixed with CONFIG_ in the .config file from Kconfig
import_kconfig("^CONFIG_" ${DOTCONFIG_OUT})

# Re-introduce the CLI Kconfig symbols that survived
foreach (name ${cache_variable_names})
  if("${name}" MATCHES "^CONFIG_")
    if(DEFINED ${name})
      set(${name} ${${name}} CACHE STRING "")
    endif()
  endif()
endforeach()
