'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

class FsciParameter(object):

    '''
    Class that maps on parameters present in the XML files describing a protocol.
    '''

    def __init__(self, name, size, dependency=None, selectDict=None, description=None):
        '''
        Constructor for a FsciParameter.

        @param name: the name of the parameter
        @param size: the size in bytes of the parameter
        @param dependency: if the current parameter size depends on another parameter, this is the
                            name of the latter
        @param selectDict: a dictionary used for inferring dependencies between parameters
        @param description: a brief additional description of the parameter, usually not used
        '''
        self.name = name
        self.size = size
        self.dependency = dependency
        self.selectDict = selectDict
        self.description = description
        self.endianness = FsciParameterType.LittleEndianBytes

    def __repr__(self):
        return self.name + ' [' + str(self.size) + ' byte(s)] -> ' + str(self.dependency)

    def __str__(self):
        return self.name + ' [' + str(self.size) + ' byte(s)] -> ' + str(self.dependency)


class FsciParameterType(object):
    LittleEndianBytes = 0
    BigEndianBytes = 1
