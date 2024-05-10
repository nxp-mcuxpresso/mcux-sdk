'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.fsci_parameter import FsciParameterType


class FsciDataPacket(object):

    '''
    Class that can construct a packet based on a specification.
    '''

    def __init__(self, fsciFrameDescription):
        '''
        Constructor for the FsciDataPacket.

        @param fsciFrameDescription: The packet specification used.
        '''
        self.fsciFrameDescription = fsciFrameDescription
        self.values = {}  # Map<String, bytearray>

        for param in fsciFrameDescription.cmdParams:
            if param.selectDict is not None:
                for selectList in param.selectDict.values():
                    for subParam in selectList:
                        self.values[subParam.name] = None
            self.values[param.name] = None

    def setParamValue(self, param, value):
        '''
        Sets a value for a parameter.

        @param param: The name of the parameter, String.
        @param value: The value of the parameter, bytearray

        @return: False if the name does not appear in the specification, True otherwise.
        '''
        if param not in self.values:
            return False
        else:
            self.values[param] = value
            return True

    def getParamValue(self, param):
        '''
        @param param: String type key of self.values
        @return: bytearray
        '''
        if param in self.values:
            return self.values[param]
        return None

    def setParamValueAsNumber(self, param, value):
        '''
        @param param: String
        @param value: integer, bytearray or list
        @return: True - success, False otherwise
        '''
        if param not in self.values:
            return False

        paramObj = self.fsciFrameDescription.getParam(param)
        bytesToAllocate = 0

        if paramObj.selectDict is not None:
            if paramObj.dependency is not None:
                if self.getParamValue(paramObj.dependency.name) is not None:
                    dictValue = self.getParamValueAsNumber(paramObj.dependency.name)
                    if dictValue in paramObj.selectDict:
                        selectedParameters = paramObj.selectDict[dictValue]
                        for selectedParam in selectedParameters:
                            size = 0
                            # if subparam is an array, get the length from the
                            # LengthValueDependency param value and multiply with unit size,
                            # otherwise it's just unit size
                            if selectedParam.dependency is not None:
                                size = self.getParamValueAsNumber(
                                    selectedParam.dependency.name) * selectedParam.size
                            else:
                                size = selectedParam.size

                    bytesToAllocate = size
                else:
                    return False
            else:
                bytesToAllocate = paramObj.size

        else:
            if paramObj.dependency is not None:
                if self.getParamValue(paramObj.dependency.name) is not None:
                    bytesToAllocate = self.getParamValueAsNumber(
                        paramObj.dependency.name) * paramObj.size
                else:
                    return False
            else:
                bytesToAllocate = paramObj.size

        if bytesToAllocate == 0 or value is None:
            return False

        if type(value) is bytearray and len(value) != 0:
            self.values[param] = value
            return True
        elif type(value) is list and len(value) != 0:
            self.values[param] = bytearray(value)
            return True
        elif (type(value) is bytearray or type(value) is list) and len(value) == 0:
            # Zero-fill not completed field values with with bytesToAllocate # of bytes.
            self.values[param] = bytearray(bytesToAllocate)
            return True
        elif type(value) == str:
            self.values[param] = bytearray(value, 'utf-8')
            return True
        else:
            self.values[param] = bytearray(bytesToAllocate)

        if paramObj.endianness == FsciParameterType.LittleEndianBytes:
            for i in range(bytesToAllocate):
                self.values[param][i] = value >> (8 * i) & 0xFF
            return True
        else:
            for i in range(bytesToAllocate - 1, -1, -1):
                self.values[param][i] = value >> (8 * i) & 0xFF
            return True

    def getParamValueAsNumber(self, param):
        '''
        @param param: String type key of self.values
        @return: integer
        '''
        val = 0

        if (param not in self.values) or (self.values[param] is None):
            return val
        else:
            paramObj = self.fsciFrameDescription.getParam(param)

            paramValue = self.values[param]
            assert type(paramValue) is bytearray

            if paramObj.endianness == FsciParameterType.LittleEndianBytes:
                for i in range(len(paramValue)):
                    val += paramValue[i] << (8 * i)
            else:
                for i in range(len(paramValue) - 1, -1, -1):
                    val += paramValue[i] << (8 * i)

        return val

    def getParamValueAsList(self, param):
        '''
        @param param: String type key of self.values
        @return: list
        '''
        val = []

        if (param not in self.values) or (self.values[param] is None):
            return []
        else:
            paramObj = self.fsciFrameDescription.getParam(param)

            paramValue = self.values[param]
            assert type(paramValue) is bytearray

            for i in range(len(paramValue)):
                val.append(paramValue[i])

            if paramObj.endianness == FsciParameterType.LittleEndianBytes:
                return val[::-1]
            else:
                return val

    def fillFromBytes(self, payload, payloadLength):
        '''
        This method will be called from the observers' observeEvent methods.
        This is why payload has a ctypes type.

        @param payload: ctypes LP_c_ubyte_Array
        @param length: number of bytes in payload
        '''
        copyCursor = 0

        for parameter in self.fsciFrameDescription.cmdParams:
            if parameter.selectDict is not None:
                if parameter.dependency is not None:
                    if self.getParamValue(parameter.dependency.name) is not None:

                        dictValue = self.getParamValueAsNumber(parameter.dependency.name)
                        if dictValue in parameter.selectDict:

                            selectedParameters = parameter.selectDict[dictValue]
                            for selectedParam in selectedParameters:

                                size = 0
                                if selectedParam.dependency is not None:
                                    size = self.getParamValueAsNumber(
                                        selectedParam.dependency.name) * selectedParam.size
                                else:
                                    size = selectedParam.size

                                try:
                                    value = bytearray(size)
                                except OverflowError:
                                    print ('[fillFromBytes] This error should not cause problems to complex events.')

                                if payloadLength >= copyCursor + size:
                                    for i in range(size):
                                        value[i] = payload[copyCursor + i]
                                else:
                                    return

                                self.values[parameter.name] = value
                                copyCursor += size
            else:
                size = 0
                if parameter.dependency is not None:
                    size = self.getParamValueAsNumber(parameter.dependency.name) * parameter.size
                else:
                    size = parameter.size

                try:
                    value = bytearray(size)
                except OverflowError:
                    print ('[fillFromBytes] This error should not cause problems to complex events.')

                if payloadLength >= copyCursor + size:
                    for i in range(size):
                        value[i] = payload[copyCursor + i]
                else:
                    return

                self.values[parameter.name] = value
                copyCursor += size

    def getFrameSize(self):
        '''
        Knows to retrieve the size of a frame. Can detect parameter dependencies.

        @return: the size as an integer
        '''

        frameSize = 0

        for parameter in self.fsciFrameDescription.cmdParams:
            # if this is a "union" type parameter (where you need to select from
            # several different param formats based on an enum value)
            if parameter.selectDict is not None:
                # check the enum value that the union param depends on
                if parameter.dependency is not None:
                    # try to get the enumeration value for the union param
                    if self.getParamValue(parameter.dependency.name) is not None:
                        dictValue = self.getParamValueAsNumber(parameter.dependency.name)
                        # check that SelectParams dictionary of the current param contains the
                        # enum value
                        if dictValue in parameter.selectDict:
                            # get the format of the union type parameter - actually a list of
                            # subparameters
                            selectedParameters = parameter.selectDict[dictValue]
                            for selectedParam in selectedParameters:
                                # get the value of the subparam
                                paramValue = self.getParamValue(selectedParam.name)
                                # subparam length depends on another param
                                if selectedParam.dependency is not None:
                                    # get value of the param specifying the length and add the
                                    # length to frame size after multiplying it with the current
                                    # subparam unit length
                                    if self.getParamValue(selectedParam.dependency.name) is not None:
                                        frameSize += self.getParamValueAsNumber(
                                            selectedParam.dependency.name) * selectedParam.size
                                    else:
                                        if paramValue is not None:
                                            # the length dependency param has not been set; we can
                                            # try to set it automatically from the length of the
                                            # actual subparam byte array size
                                            if not self.setParamValueAsNumber(
                                                    selectedParam.dependency.name, len(paramValue) / selectedParam.size):
                                                pass
                                        else:
                                            # the subparam value is null and the length dependency is
                                            # also not set so we'll set the value of this subparam
                                            # as 0
                                            if not self.setParamValueAsNumber(selectedParam.dependency.name, 0):
                                                pass
                                else:
                                    # current sub param length does not depend on another actual
                                    # length is specified in the Size member which we add to the
                                    # frameSize
                                    frameSize += selectedParam.size

            # parameter is not a "union" type param
            else:
                # get the value of the param
                paramValue = self.getParamValue(parameter.name)
                # param length depends on another param
                if parameter.dependency is not None:
                    # get value of the param specifying the length and add the length to frame
                    # size after multiplying it with the current param unit length
                    if self.getParamValue(parameter.dependency.name) is not None:
                        frameSize += self.getParamValueAsNumber(
                            parameter.dependency.name) * parameter.size
                    else:
                        if paramValue is not None:
                            # the length dependency param has not been set; we can
                            # try to set it automatically from the length of the
                            # actual subparam byte array size
                            if not self.setParamValueAsNumber(
                                    parameter.dependency.name, len(paramValue) / parameter.size):
                                pass
                        else:
                            # the param value is null and the length dependency is
                            # also not set so we'll set the value of this param as 0
                            if not self.setParamValueAsNumber(parameter.dependency.name, 0):
                                pass
                else:
                    # current param length does not depend on another actual length is
                    # specified in the Size member which we add to the frameSize, except for
                    # None values
                    if paramValue is not None:
                        frameSize += parameter.size

        return frameSize

    def getBytes(self):
        '''
        Retrieves the byte array representation of the packet. Useful when deciding
        to send the packet on the wire.
        '''
        # now we now the length of the byte array and we can allocate it
        frameSize = self.getFrameSize()
        if frameSize == 0:
            return None

        byteList = bytearray(frameSize)
        # then proceed to actually copying data to it from the values dictionary
        copyCursor = 0

        for parameter in self.fsciFrameDescription.cmdParams:
            if parameter.selectDict is not None:
                if parameter.dependency is not None:
                    if self.getParamValue(parameter.dependency.name) is not None:
                        dictValue = self.getParamValueAsNumber(parameter.dependency.name)
                        # check if SelectParams dictionary for the current param contains the
                        # value of the param dependency
                        if dictValue in parameter.selectDict:
                            selectedParameters = parameter.selectDict[dictValue]
                            for selectedParam in selectedParameters:
                                size = 0
                                # if subparam is an array, get the length from the
                                # LengthValueDependency param value and multiply with unit size,
                                # otherwise it's just unit size
                                if selectedParam.dependency is not None:
                                    size = self.getParamValueAsNumber(
                                        selectedParam.dependency.name) * selectedParam.size
                                else:
                                    size = selectedParam.size

                                paramValue = self.getParamValue(parameter.name)
                                # if there's something there, copy it to the output frame array set
                                # byte array for param may be shorter than actual size so we pad
                                # with 0s which remain from the initial frame allocation as we only
                                # copy the bytes that were set
                                if paramValue is not None:
                                    for i in range(size):
                                        if copyCursor + i < frameSize:
                                            byteList[copyCursor + i] = paramValue[i]
                                # increment position for next copy operation in output buffer
                                copyCursor += size

                                # go to the next subparam
            else:
                size = 0
                if parameter.dependency is not None:
                    size = self.getParamValueAsNumber(parameter.dependency.name) * parameter.size
                else:
                    size = parameter.size

                paramValue = self.getParamValue(parameter.name)
                if paramValue is not None:
                    for i in range(len(paramValue)):
                        if copyCursor + i < frameSize:
                            byteList[copyCursor + i] = paramValue[i]
                # increment position for next copy operation in output buffer
                copyCursor += size

                # go to next param

        return byteList
