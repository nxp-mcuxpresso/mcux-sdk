#!/usr/bin/env python3
#/*
# * Copyright 2024 NXP
# * 
# * SPDX-License-Identifier: BSD-3-Clause
# * The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
# */

# import OS module

import os
import argparse
import codecs
import gzip
import io

base_path = os.getcwd()

src_path = base_path

dest_path = base_path + "/inc"

def get_nice_string(list_or_iterator):
    return ", ".join( "0x" + str(x) for x in list_or_iterator)

def make_hex(chunk, outfp):
    hexdata = codecs.encode(chunk, 'hex').decode("utf-8")
    hexlist = map(''.join, zip(*[iter(hexdata)]*2))
    outfp.write(get_nice_string(hexlist) + ',')

for d in os.listdir(src_path):

    if '.bin' in d:

        # Prints only text file present in My Folder

        print("Convert: "+src_path+"/"+d +" => "+dest_path+"/"+d+".inc")

        outfp = open(dest_path+"/"+d+".inc", "w")

        with open(src_path+"/"+d, "rb") as fp:
            for chunk in iter(lambda: fp.read(8), b''):
                make_hex(chunk, outfp)