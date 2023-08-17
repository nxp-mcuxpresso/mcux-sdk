#!/usr/bin/env python3

# Copyright 2023 NXP
# SPDX-License-Identifier: BSD-3-Clause

import os
import argparse
import subprocess
import misc

def main():
    args = parse_args()

    print ("executing in mcux.py")

    PYTHON_EXECUTABLE = os.environ["PYTHON_EXECUTABLE"]
    KCONFIG_BASE = os.environ["KCONFIG_BASE"]
    KCONFIG_CONFIG = os.environ["KCONFIG_CONFIG"]
    if KCONFIG_CONFIG.endswith("config.cmake"):
        print ("Loading configuration {}".format(KCONFIG_CONFIG))
        os.environ["KCONFIG_CONFIG"] = misc.mcux_create_config_from_cmake(KCONFIG_CONFIG)

    script = os.path.join(KCONFIG_BASE, "scripts", "kconfig", "%s.py"%args.kconfig_target)
    command = "%s %s %s"%(PYTHON_EXECUTABLE,script,args.kconfig_root)
    print (command)
    p = subprocess.Popen(command)
    p.wait()

    # automatic generate config.cmake file
    misc.mcux_create_config_cmake(os.environ["KCONFIG_CONFIG"])


def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument("kconfig_target",
                        help="target kconfig script to call")
    parser.add_argument("kconfig_root",
                        help="top level kconfig file")
    return parser.parse_args()

main()