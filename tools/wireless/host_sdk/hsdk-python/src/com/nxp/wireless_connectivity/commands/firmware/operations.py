'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.firmware.events import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.commands.fsci_operation import FsciOperation


class FSCIOTASupportSetKeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIOTASupportSetKeyRequestFrame
        self.observers = []
        super(FSCIOTASupportSetKeyOperation, self).subscribeToEvents()


class FSCIEnterBootloaderOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIEnterBootloaderRequestFrame
        self.observers = []
        super(FSCIEnterBootloaderOperation, self).subscribeToEvents()


class FSCICPUResetOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCICPUResetRequestFrame
        self.observers = []
        super(FSCICPUResetOperation, self).subscribeToEvents()


class FSCIFirmware_StartImageOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_StartImageRequestFrame
        self.observers = [FSCIFirmware_StartImageConfirmObserver('FSCIFirmware_StartImageConfirm'), ]
        super(FSCIFirmware_StartImageOperation, self).subscribeToEvents()


class FSCIFirmware_SetOperationModeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_SetOperationModeRequestFrame
        self.observers = [FSCIFirmware_SetOperationModeConfirmObserver('FSCIFirmware_SetOperationModeConfirm'), ]
        super(FSCIFirmware_SetOperationModeOperation, self).subscribeToEvents()


class FSCIFirmware_QueryImageRspOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_QueryImageRspRequestFrame
        self.observers = [FSCIFirmware_QueryImageRspConfirmObserver('FSCIFirmware_QueryImageRspConfirm'), ]
        super(FSCIFirmware_QueryImageRspOperation, self).subscribeToEvents()


class FSCIFirmware_PushImageChunkOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_PushImageChunkRequestFrame
        self.observers = [FSCIFirmware_PushImageChunkConfirmObserver('FSCIFirmware_PushImageChunkConfirm'), ]
        super(FSCIFirmware_PushImageChunkOperation, self).subscribeToEvents()


class FSCIFirmware_CancelProcessOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_CancelProcessRequestFrame
        self.observers = [FSCIFirmware_CancelProcessConfirmObserver('FSCIFirmware_CancelProcessConfirm'), ]
        super(FSCIFirmware_CancelProcessOperation, self).subscribeToEvents()


class FSCIFirmware_CommitImageOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_CommitImageRequestFrame
        self.observers = [FSCIFirmware_CommitImageConfirmObserver('FSCIFirmware_CommitImageConfirm'), ]
        super(FSCIFirmware_CommitImageOperation, self).subscribeToEvents()


class FSCIFirmware_ImageNotifyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_ImageNotifyRequestFrame
        self.observers = [FSCIFirmware_ImageNotifyConfirmObserver('FSCIFirmware_ImageNotifyConfirm'), ]
        super(FSCIFirmware_ImageNotifyOperation, self).subscribeToEvents()


class FSCIFirmware_SetFileVersionPolicyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_SetFileVersionPolicyRequestFrame
        self.observers = [FSCIFirmware_SetFileVersionPolicyConfirmObserver('FSCIFirmware_SetFileVersionPolicyConfirm'), ]
        super(FSCIFirmware_SetFileVersionPolicyOperation, self).subscribeToEvents()


class FSCIFirmware_AbortOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIFirmware_AbortRequestFrame
        self.observers = []
        super(FSCIFirmware_AbortOperation, self).subscribeToEvents()


class FSCIFirmware_QueryImageOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [FSCIFirmware_QueryImageIndicationObserver('FSCIFirmware_QueryImageIndication'), ]
        super(FSCIFirmware_QueryImageOperation, self).subscribeToEvents()


class FSCIFirmware_ChunkOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [FSCIFirmware_ChunkIndicationObserver('FSCIFirmware_ChunkIndication'), ]
        super(FSCIFirmware_ChunkOperation, self).subscribeToEvents()
