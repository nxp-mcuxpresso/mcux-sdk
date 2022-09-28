'''
* Copyright 2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

class OTAFileHeader(object):

    def __init__(self, ota_bytes):

        self.fileIdentifier = ota_bytes[:4]
        self.headerVersion = ota_bytes[4:6]
        self.headerLength = ota_bytes[6:8]
        self.fieldControl = ota_bytes[8:10]
        self.manufacturerCode = ota_bytes[10:12]
        self.imageType = ota_bytes[12:14]
        self.fileVersion = ota_bytes[14:18]
        self.stackVersion = ota_bytes[18:20]
        self.headerString = ota_bytes[20:52]
        self.totalImageSize = ota_bytes[52:56]
        self.minHwVersion = ota_bytes[56:58]
        self.maxHwVersion = ota_bytes[58:60]
        self.imageSize = ota_bytes[62:66]
