#!/usr/bin/env python3

# Copyright 2023 NXP
# All rights reserved.
# 
# SPDX-License-Identifier: BSD-3-Clause

import os

def write_file(filename, content, mode="w"):
    with open(filename, mode, encoding='utf-8') as f:
        f.write(content)

    if not os.path.exists(filename):
        return "NA"
    else:
        return os.path.abspath(filename)

def read_file(filename):
    content = ""
    with open(filename, "r", encoding='utf-8') as f:
        content = f.read()

    return content

def make_board_name(config_data):
    
    board = ""
    core = ""
    for line in config_data.splitlines():
        if line and not line.startswith("#"):
            name, val = line[4:-1].split(" ", 1)
            if name == "CONFIG_BOARD":
                board = val
            elif name == "CONFIG_CORE_ID":
                core = val
    
    board_name = board.upper()
    if core:
        board_name = "%s_%s"%(board_name,core.upper())

    return board_name

def mcux_create_config_cmake(config_out,kconfig_namespace='CONFIG_MCUX'):
    newlines = "set(CONFIG_COMPILER gcc)\nset(CONFIG_TOOLCHAIN armgcc)\n#config.cmake generated from .config".splitlines()

    config_data = read_file(config_out)
    config_cmake = os.path.join(os.path.dirname(config_out), "config.cmake")
    for line in config_data.splitlines():
        # if line and line[:7] == "CONFIG_" and "MCUX_Family" not in line:
         if line and line[:7] == "CONFIG_":
            name, val = line.split("=")

            if val == 'y':
                if "%s_HAS"%kconfig_namespace not in name:
                    newlines.append('set({} true)'.format(name.replace("%s_"%kconfig_namespace, "CONFIG_")))
            else:
                newlines.append('set({} {})'.format(name.replace("%s_"%kconfig_namespace, "CONFIG_"), val))

    if os.path.exists(config_cmake):
        config_cmake_old = config_cmake.replace("config.cmake","config.cmake.old")
        if os.path.exists(config_cmake_old):
            os.remove(config_cmake_old)
        os.rename(config_cmake, config_cmake_old)
    
    write_file(config_cmake,'\n'.join(newlines))

def mcux_create_config_from_cmake(config_cmake,kconfig_namespace='CONFIG_MCUX'):
    newlines = []
    config_data = read_file(config_cmake)
    config_dot = os.path.join(os.path.dirname(config_cmake), ".config")
    for line in config_data.splitlines():
        if line and not line.startswith("#"):
            # print (line)
            # print (line[4:-1].split(" "))
            name, val = line[4:-1].split(" ", 1)
            if val == "true":
                newlines.append('{}={}'.format(name.replace("CONFIG_","%s_"%kconfig_namespace),'y'))
            else:
                newlines.append('{}="{}"'.format(name.replace("CONFIG_","%s_"%kconfig_namespace),val))
    
    if "CONFIG_USE_BOARD" not in config_data:
        board_name = make_board_name(config_data)
        newlines.append("%s_USE_BOARD_%s=y"%(kconfig_namespace, board_name))

    if os.path.exists(config_dot):
        os.remove(config_dot)
    
    write_file(config_dot,'\n'.join(newlines))

    return config_dot
