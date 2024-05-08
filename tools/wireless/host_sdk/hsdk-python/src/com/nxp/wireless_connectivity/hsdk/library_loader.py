'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import cdll
import os
import sys

from .singleton import singleton


extension = {'linux': '.so', 'linux2': '.so', 'linux3': '.so', 'darwin': '.dylib', 'win': '.dll'}


@singleton
class LibraryLoader(object):

    '''
    Class that loads the native C code libraries.
    '''

    def __init__(self):

        if sys.platform.startswith('linux') or sys.platform == 'darwin':
            try:
                self.lib_dir = os.popen('ldconfig -p | grep fsci').read().split('\n')[0].split('=>')[1].split('libfsci')[0].lstrip().rstrip()
            except:
                sys.exit("[ERROR] The system could not find the Host SDK shared libraries. Please make sure that `ldconfig -p` displays them.")
            self.ext = extension[sys.platform]

            try:
                self.CSpiLibrary = cdll.LoadLibrary(self.lib_dir + 'libspi' + self.ext)
            except:
                print ("[WARNING] Could not find libspi.so, SPI support is disabled.")
                self.CSpiLibrary = None

            self.CUartLibrary = cdll.LoadLibrary(self.lib_dir + 'libuart' + self.ext)
            self.CPhysicalLibrary = cdll.LoadLibrary(self.lib_dir + 'libphysical' + self.ext)
            self.CSysLibrary = cdll.LoadLibrary(self.lib_dir + 'libsys' + self.ext)
            self.CFramerLibrary = cdll.LoadLibrary(self.lib_dir + 'libframer' + self.ext)
            self.CFsciLibrary = cdll.LoadLibrary(self.lib_dir + 'libfsci' + self.ext)

        elif sys.platform.startswith('win'):
            self.HSDKLibrary = cdll.LoadLibrary(sys.prefix + '\DLLs\HSDK' + extension['win'])
            self.CUartLibrary = self.HSDKLibrary
            self.CSpiLibrary = None  # not available on Windows
            self.CPhysicalLibrary = self.HSDKLibrary
            self.CSysLibrary = self.HSDKLibrary
            self.CFramerLibrary = self.HSDKLibrary
            self.CFsciLibrary = self.HSDKLibrary

        else:
            raise Exception(sys.platform + ' is not supported yet.')
