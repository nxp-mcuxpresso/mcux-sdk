/* Source file generated from BLE_1.8.9.xml */
/*
 * Copyright 2018-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*==================================================================================================
Include Files
==================================================================================================*/
#include "cmd_ble.h"

/*==================================================================================================
Public Functions
==================================================================================================*/
#if L2CAP_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t L2CAPInitRequest(void *arg, uint8_t fsciInterface)
\brief	L2CAP initialization function

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t L2CAPInitRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x41, 0x01, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPSendAttDataRequest(L2CAPSendAttDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a data packet through ATT Channel

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPSendAttDataRequest(L2CAPSendAttDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // PacketLength
	msgLen += req->PacketLength;  // Packet

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->PacketLength), sizeof(req->PacketLength)); idx += sizeof(req->PacketLength);
	FLib_MemCpy(pMsg + idx, req->Packet, req->PacketLength); idx += req->PacketLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x41, 0x03, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPSendSmpDataRequest(L2CAPSendSmpDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a data packet through SM Channel

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPSendSmpDataRequest(L2CAPSendSmpDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // PacketLength
	msgLen += req->PacketLength;  // Packet

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->PacketLength), sizeof(req->PacketLength)); idx += sizeof(req->PacketLength);
	FLib_MemCpy(pMsg + idx, req->Packet, req->PacketLength); idx += req->PacketLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x41, 0x04, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPRegisterAttCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Register callback for receiving ATT data

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t L2CAPRegisterAttCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x41, 0x06, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPRegisterSmpCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Register callback for receiving SM data

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t L2CAPRegisterSmpCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x41, 0x07, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* L2CAP_ENABLE */

#if L2CAPCB_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBRegisterLeCbCallbacksRequest(void *arg, uint8_t fsciInterface)
\brief	Registers callbacks for credit based data and control events on L2CAP.

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t L2CAPCBRegisterLeCbCallbacksRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x42, 0x01, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBRegisterLePsmRequest(L2CAPCBRegisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Register LePsm

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBRegisterLePsmRequest(L2CAPCBRegisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x02, req, sizeof(L2CAPCBRegisterLePsmRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBDeregisterLePsmRequest(L2CAPCBDeregisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Deregister LePsm

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBDeregisterLePsmRequest(L2CAPCBDeregisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x03, req, sizeof(L2CAPCBDeregisterLePsmRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBConnectLePsmRequest(L2CAPCBConnectLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	L2CAP connect

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBConnectLePsmRequest(L2CAPCBConnectLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x04, req, sizeof(L2CAPCBConnectLePsmRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBDisconnectLeCbChannelRequest(L2CAPCBDisconnectLeCbChannelRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	L2CAP disconnect

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBDisconnectLeCbChannelRequest(L2CAPCBDisconnectLeCbChannelRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x05, req, sizeof(L2CAPCBDisconnectLeCbChannelRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBCancelConnectionRequest(L2CAPCBCancelConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Termination of an L2CAP channel

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBCancelConnectionRequest(L2CAPCBCancelConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x06, req, sizeof(L2CAPCBCancelConnectionRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBSendLeCbDataRequest(L2CAPCBSendLeCbDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a data packet through a Credit Based Channel

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBSendLeCbDataRequest(L2CAPCBSendLeCbDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // ChannelId
	msgLen += sizeof(uint16_t);  // PacketLength
	msgLen += req->PacketLength;  // Packet

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->ChannelId), sizeof(req->ChannelId)); idx += sizeof(req->ChannelId);
	FLib_MemCpy(pMsg + idx, &(req->PacketLength), sizeof(req->PacketLength)); idx += sizeof(req->PacketLength);
	FLib_MemCpy(pMsg + idx, req->Packet, req->PacketLength); idx += req->PacketLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x42, 0x07, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBSendLeCreditRequest(L2CAPCBSendLeCreditRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends credits to a device when capable of receiving additional LE-frames

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBSendLeCreditRequest(L2CAPCBSendLeCreditRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x42, 0x08, req, sizeof(L2CAPCBSendLeCreditRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBEnhancedConnectLePsmRequest(L2CAPCBEnhancedConnectLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initiates a connection with a peer device for a registered LE_PSM, enhanced mode

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBEnhancedConnectLePsmRequest(L2CAPCBEnhancedConnectLePsmRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // LePsm
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Mtu
	msgLen += sizeof(uint16_t);  // InitialCredits
	msgLen += sizeof(uint8_t);  // NoOfChannels
	msgLen += req->NoOfChannels;  // Cids

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->LePsm), sizeof(req->LePsm)); idx += sizeof(req->LePsm);
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Mtu), sizeof(req->Mtu)); idx += sizeof(req->Mtu);
	FLib_MemCpy(pMsg + idx, &(req->InitialCredits), sizeof(req->InitialCredits)); idx += sizeof(req->InitialCredits);
	pMsg[idx] = req->NoOfChannels; idx++;
	FLib_MemCpy(pMsg + idx, req->Cids, req->NoOfChannels); idx += req->NoOfChannels;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x42, 0x09, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBEnhancedChannelReconfigureRequest(L2CAPCBEnhancedChannelReconfigureRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Reconfigures up to 5 channels with new values for MTU and/or MPS

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBEnhancedChannelReconfigureRequest(L2CAPCBEnhancedChannelReconfigureRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // NewMtu
	msgLen += sizeof(uint16_t);  // NewMps
	msgLen += sizeof(uint8_t);  // NoOfChannels
	msgLen += req->NoOfChannels;  // Cids

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->NewMtu), sizeof(req->NewMtu)); idx += sizeof(req->NewMtu);
	FLib_MemCpy(pMsg + idx, &(req->NewMps), sizeof(req->NewMps)); idx += sizeof(req->NewMps);
	pMsg[idx] = req->NoOfChannels; idx++;
	FLib_MemCpy(pMsg + idx, req->Cids, req->NoOfChannels); idx += req->NoOfChannels;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x42, 0x0A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t L2CAPCBEnhancedCancelConnectionRequest(L2CAPCBEnhancedCancelConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Terminates pending L2CAP channels

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t L2CAPCBEnhancedCancelConnectionRequest(L2CAPCBEnhancedCancelConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // LePsm
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // RefuseReason
	msgLen += sizeof(uint8_t);  // NoOfChannels
	msgLen += req->NoOfChannels;  // Cids

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->LePsm), sizeof(req->LePsm)); idx += sizeof(req->LePsm);
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &req->RefuseReason, sizeof(uint16_t)); idx += sizeof(uint16_t);
	pMsg[idx] = req->NoOfChannels; idx++;
	FLib_MemCpy(pMsg + idx, req->Cids, req->NoOfChannels); idx += req->NoOfChannels;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x42, 0x0B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t GATTInitRequest(void *arg, uint8_t fsciInterface)
\brief	Initializes the GATT module

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTInitRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x01, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTGetMtuRequest(GATTGetMtuRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Retrieves the MTU used with a given connected device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTGetMtuRequest(GATTGetMtuRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x02, req, sizeof(GATTGetMtuRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientInitRequest(void *arg, uint8_t fsciInterface)
\brief	Initializes the GATT Client functionality

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientInitRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x03, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientResetProcedureRequest(void *arg, uint8_t fsciInterface)
\brief	Resets any ongoing GATT Client procedure

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientResetProcedureRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x04, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterProcedureCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for the GATT Client module Procedures

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterProcedureCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x05, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Server Notifications

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x06, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterMultipleValueNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Server Multiple Handle Value Notifications

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterMultipleValueNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x23, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterIndicationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Server Indications

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterIndicationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x07, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientExchangeMtuRequest(GATTClientExchangeMtuRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the MTU Exchange procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientExchangeMtuRequest(GATTClientExchangeMtuRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x08, req, sizeof(GATTClientExchangeMtuRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientDiscoverAllPrimaryServicesRequest(GATTClientDiscoverAllPrimaryServicesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Primary Service Discovery procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientDiscoverAllPrimaryServicesRequest(GATTClientDiscoverAllPrimaryServicesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x09, req, sizeof(GATTClientDiscoverAllPrimaryServicesRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientDiscoverPrimaryServicesByUuidRequest(GATTClientDiscoverPrimaryServicesByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Primary Service Discovery By UUID procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientDiscoverPrimaryServicesByUuidRequest(GATTClientDiscoverPrimaryServicesByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // MaxNbOfServices

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->MaxNbOfServices; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientFindIncludedServicesRequest(GATTClientFindIncludedServicesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Find Included Services procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientFindIncludedServicesRequest(GATTClientFindIncludedServicesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfIncludedServices

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfIncludedServices; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientDiscoverAllCharacteristicsOfServiceRequest(GATTClientDiscoverAllCharacteristicsOfServiceRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Discovery procedure for a given Service

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientDiscoverAllCharacteristicsOfServiceRequest(GATTClientDiscoverAllCharacteristicsOfServiceRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfCharacteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfCharacteristics; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0C, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientDiscoverCharacteristicOfServiceByUuidRequest(GATTClientDiscoverCharacteristicOfServiceByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Discovery procedure for a given Service, with a given UUID

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientDiscoverCharacteristicOfServiceByUuidRequest(GATTClientDiscoverCharacteristicOfServiceByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfCharacteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfCharacteristics; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientDiscoverAllCharacteristicDescriptorsRequest(GATTClientDiscoverAllCharacteristicDescriptorsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Discovery procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientDiscoverAllCharacteristicDescriptorsRequest(GATTClientDiscoverAllCharacteristicDescriptorsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // EndingHandle
	msgLen += sizeof(uint8_t);  // MaxNbOfDescriptors

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->EndingHandle), sizeof(req->EndingHandle)); idx += sizeof(req->EndingHandle);
	pMsg[idx] = req->MaxNbOfDescriptors; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0E, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientReadCharacteristicValueRequest(GATTClientReadCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientReadCharacteristicValueRequest(GATTClientReadCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x0F, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientReadUsingCharacteristicUuidRequest(GATTClientReadUsingCharacteristicUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read By UUID procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientReadUsingCharacteristicUuidRequest(GATTClientReadUsingCharacteristicUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(bool_t);  // HandleRangeIncluded

	if (req->HandleRangeIncluded)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
	}	// HandleRange

	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->HandleRangeIncluded; idx++;

	if (req->HandleRangeIncluded)
	{
		FLib_MemCpy(pMsg + idx, &(req->HandleRange.StartHandle), sizeof(req->HandleRange.StartHandle)); idx += sizeof(req->HandleRange.StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->HandleRange.EndHandle), sizeof(req->HandleRange.EndHandle)); idx += sizeof(req->HandleRange.EndHandle);
	}
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x10, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientReadMultipleCharacteristicValuesRequest(GATTClientReadMultipleCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read Multiple procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientReadMultipleCharacteristicValuesRequest(GATTClientReadMultipleCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.Handle), sizeof(req->Characteristics[i].Value.Handle)); idx += sizeof(req->Characteristics[i].Value.Handle);
		pMsg[idx] = req->Characteristics[i].Value.UuidType; idx++;

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.ValueLength), sizeof(req->Characteristics[i].Value.ValueLength)); idx += sizeof(req->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.MaxValueLength), sizeof(req->Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].Handle), sizeof(req->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x11, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientWriteCharacteristicValueRequest(GATTClientWriteCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Write procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientWriteCharacteristicValueRequest(GATTClientWriteCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value
	msgLen += sizeof(bool_t);  // WithoutResponse
	msgLen += sizeof(bool_t);  // SignedWrite
	msgLen += sizeof(bool_t);  // ReliableLongCharWrites
	msgLen += 16;  // Csrk

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;
	pMsg[idx] = req->WithoutResponse; idx++;
	pMsg[idx] = req->SignedWrite; idx++;
	pMsg[idx] = req->ReliableLongCharWrites; idx++;
	FLib_MemCpy(pMsg + idx, req->Csrk, 16); idx += 16;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x12, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientReadCharacteristicDescriptorRequest(GATTClientReadCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Read procedure for a given Characteristic Descriptor

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientReadCharacteristicDescriptorRequest(GATTClientReadCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.Handle), sizeof(req->Descriptor.Handle)); idx += sizeof(req->Descriptor.Handle);
	pMsg[idx] = req->Descriptor.UuidType; idx++;

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.ValueLength), sizeof(req->Descriptor.ValueLength)); idx += sizeof(req->Descriptor.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.MaxValueLength), sizeof(req->Descriptor.MaxValueLength)); idx += sizeof(req->Descriptor.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Descriptor.Value, 0); idx += 0;
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x13, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientWriteCharacteristicDescriptorRequest(GATTClientWriteCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Write procedure for a given Characteristic Descriptor

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientWriteCharacteristicDescriptorRequest(GATTClientWriteCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.Handle), sizeof(req->Descriptor.Handle)); idx += sizeof(req->Descriptor.Handle);
	pMsg[idx] = req->Descriptor.UuidType; idx++;

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.ValueLength), sizeof(req->Descriptor.ValueLength)); idx += sizeof(req->Descriptor.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.MaxValueLength), sizeof(req->Descriptor.MaxValueLength)); idx += sizeof(req->Descriptor.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Descriptor.Value, 0); idx += 0;
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x14, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerInitRequest(void *arg, uint8_t fsciInterface)
\brief	Initializes the GATT Server module

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTServerInitRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x15, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerRegisterCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs an application callback for the GATT Server module

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTServerRegisterCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x16, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerRegisterHandlesForWriteNotificationsRequest(GATTServerRegisterHandlesForWriteNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Registers the attribute handles that will be notified through the GATT Server callback when a GATT Client attempts to modify the attributes' values

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerRegisterHandlesForWriteNotificationsRequest(GATTServerRegisterHandlesForWriteNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // HandleCount
	msgLen += req->HandleCount * sizeof(uint16_t);  // AttributeHandles

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->HandleCount; idx++;
	FLib_MemCpy(pMsg + idx, req->AttributeHandles, req->HandleCount * sizeof(uint16_t)); idx += req->HandleCount * sizeof(uint16_t);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x17, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendAttributeWrittenStatusRequest(GATTServerSendAttributeWrittenStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Responds to a Control Point write operation

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendAttributeWrittenStatusRequest(GATTServerSendAttributeWrittenStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x18, req, sizeof(GATTServerSendAttributeWrittenStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendNotificationRequest(GATTServerSendNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendNotificationRequest(GATTServerSendNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x19, req, sizeof(GATTServerSendNotificationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendIndicationRequest(GATTServerSendIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends an indication to a peer GATT Client

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendIndicationRequest(GATTServerSendIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x1A, req, sizeof(GATTServerSendIndicationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendInstantValueNotificationRequest(GATTServerSendInstantValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client with data given as parameter, ignoring the GATT Database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendInstantValueNotificationRequest(GATTServerSendInstantValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Handle), sizeof(req->Handle)); idx += sizeof(req->Handle);
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x1B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendInstantValueIndicationRequest(GATTServerSendInstantValueIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends an indication to a peer GATT Client with data given as parameter, ignoring the GATT Databas

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendInstantValueIndicationRequest(GATTServerSendInstantValueIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Handle), sizeof(req->Handle)); idx += sizeof(req->Handle);
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x1C, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendMultipleHandleValueNotificationRequest(GATTServerSendMultipleHandleValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client with data given as parameter, ignoring the GATT Database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendMultipleHandleValueNotificationRequest(GATTServerSendMultipleHandleValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // HandleCount

	for (uint32_t i = 0; i < req->HandleCount; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += req->HandleLengthValueList[i].ValueLength;  // Value
	}	// HandleLengthValueList

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->HandleCount; idx++;

	for (uint32_t i = 0; i < req->HandleCount; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->HandleLengthValueList[i].Handle), sizeof(req->HandleLengthValueList[i].Handle)); idx += sizeof(req->HandleLengthValueList[i].Handle);
		FLib_MemCpy(pMsg + idx, &(req->HandleLengthValueList[i].ValueLength), sizeof(req->HandleLengthValueList[i].ValueLength)); idx += sizeof(req->HandleLengthValueList[i].ValueLength);
		FLib_MemCpy(pMsg + idx, req->HandleLengthValueList[i].Value, req->HandleLengthValueList[i].ValueLength); idx += req->HandleLengthValueList[i].ValueLength;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x22, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerRegisterHandlesForReadNotificationsRequest(GATTServerRegisterHandlesForReadNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Registers the attribute handles that will be notified through the GATT Server callback when a GATT Client attempts to read the attributes' values

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerRegisterHandlesForReadNotificationsRequest(GATTServerRegisterHandlesForReadNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // HandleCount
	msgLen += req->HandleCount * sizeof(uint16_t);  // AttributeHandles

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->HandleCount; idx++;
	FLib_MemCpy(pMsg + idx, req->AttributeHandles, req->HandleCount * sizeof(uint16_t)); idx += req->HandleCount * sizeof(uint16_t);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x1D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerSendAttributeReadStatusRequest(GATTServerSendAttributeReadStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Responds to an intercepted attribute read operation

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerSendAttributeReadStatusRequest(GATTServerSendAttributeReadStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x1E, req, sizeof(GATTServerSendAttributeReadStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerRegisterUniqueHandlesForNotificationsRequest(GATTServerRegisterUniqueHandlesForNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Registers all attribute handles with unique value buffers to be notified through the GATT Server callback when a GATT Client attempts to read/write the attributes' values.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerRegisterUniqueHandlesForNotificationsRequest(GATTServerRegisterUniqueHandlesForNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x1F, req, sizeof(GATTServerRegisterUniqueHandlesForNotificationsRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerUnregisterHandlesForWriteNotificationsRequest(GATTServerUnregisterHandlesForWriteNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Unregisters the attribute handles that will be notified through the GATT Server callback when a GATT Client attempts to write the attributes' values

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerUnregisterHandlesForWriteNotificationsRequest(GATTServerUnregisterHandlesForWriteNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // HandleCount
	msgLen += req->HandleCount * sizeof(uint16_t);  // AttributeHandles

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->HandleCount; idx++;
	FLib_MemCpy(pMsg + idx, req->AttributeHandles, req->HandleCount * sizeof(uint16_t)); idx += req->HandleCount * sizeof(uint16_t);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x20, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerUnregisterHandlesForReadNotificationsRequest(GATTServerUnregisterHandlesForReadNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Unregisters the attribute handles that will be notified through the GATT Server callback when a GATT Client attempts to read the attributes' values

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerUnregisterHandlesForReadNotificationsRequest(GATTServerUnregisterHandlesForReadNotificationsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // HandleCount
	msgLen += req->HandleCount * sizeof(uint16_t);  // AttributeHandles

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->HandleCount; idx++;
	FLib_MemCpy(pMsg + idx, req->AttributeHandles, req->HandleCount * sizeof(uint16_t)); idx += req->HandleCount * sizeof(uint16_t);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x21, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientReadMultipleVariableCharacteristicValuesRequest(GATTClientReadMultipleVariableCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Unregisters the attribute handles that will be notified through the GATT Server callback when a GATT Client attempts to read the attributes' values

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientReadMultipleVariableCharacteristicValuesRequest(GATTClientReadMultipleVariableCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.Handle), sizeof(req->Characteristics[i].Value.Handle)); idx += sizeof(req->Characteristics[i].Value.Handle);
		pMsg[idx] = req->Characteristics[i].Value.UuidType; idx++;

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.ValueLength), sizeof(req->Characteristics[i].Value.ValueLength)); idx += sizeof(req->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.MaxValueLength), sizeof(req->Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].Handle), sizeof(req->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x24, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterEnhancedProcedureCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for the GATT Client module Procedures on Enhanced ATT bearers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterEnhancedProcedureCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x25, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterEnhancedNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Server Notifications on Enhanced ATT bearers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterEnhancedNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x26, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterEnhancedIndicationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Server Indications on Enhanced ATT bearers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterEnhancedIndicationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x27, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientRegisterEnhancedMultipleValueNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs the application callback for Multiple Value Notifications on Enhanced ATT bearers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTClientRegisterEnhancedMultipleValueNotificationCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x28, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedDiscoverAllPrimaryServicesRequest(GATTClientEnhancedDiscoverAllPrimaryServicesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Primary Service Discovery procedure on an enhanced ATT bearer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedDiscoverAllPrimaryServicesRequest(GATTClientEnhancedDiscoverAllPrimaryServicesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x29, req, sizeof(GATTClientEnhancedDiscoverAllPrimaryServicesRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedDiscoverPrimaryServicesByUuidRequest(GATTClientEnhancedDiscoverPrimaryServicesByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Primary Service Discovery By UUID procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedDiscoverPrimaryServicesByUuidRequest(GATTClientEnhancedDiscoverPrimaryServicesByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // MaxNbOfServices

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->MaxNbOfServices; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedFindIncludedServicesRequest(GATTClientEnhancedFindIncludedServicesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Find Included Services procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedFindIncludedServicesRequest(GATTClientEnhancedFindIncludedServicesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfIncludedServices

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfIncludedServices; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest(GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Discovery procedure for a given Service

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest(GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfCharacteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfCharacteristics; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2C, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest(GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Discovery procedure for a given Service, with a given UUID

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest(GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint16_t);  // EndHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics
	msgLen += sizeof(uint8_t);  // NbOfIncludedServices

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint8_t);  // NbOfCharacteristics
		msgLen += sizeof(uint8_t);  // NbOfIncludedServices
	}	// IncludedServices
	msgLen += sizeof(uint8_t);  // MaxNbOfCharacteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Service.StartHandle), sizeof(req->Service.StartHandle)); idx += sizeof(req->Service.StartHandle);
	FLib_MemCpy(pMsg + idx, &(req->Service.EndHandle), sizeof(req->Service.EndHandle)); idx += sizeof(req->Service.EndHandle);
	pMsg[idx] = req->Service.UuidType; idx++;

	switch (req->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Service.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->Service.NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Service.Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.Handle), sizeof(req->Service.Characteristics[i].Value.Handle)); idx += sizeof(req->Service.Characteristics[i].Value.Handle);
		pMsg[idx] = req->Service.Characteristics[i].Value.UuidType; idx++;

		switch (req->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.ValueLength), sizeof(req->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Value.MaxValueLength), sizeof(req->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Service.Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].Handle), sizeof(req->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Service.Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Service.Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Service.Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Service.Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}
	pMsg[idx] = req->Service.NbOfIncludedServices; idx++;

	for (uint32_t i = 0; i < req->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].StartHandle), sizeof(req->Service.IncludedServices[i].StartHandle)); idx += sizeof(req->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->Service.IncludedServices[i].EndHandle), sizeof(req->Service.IncludedServices[i].EndHandle)); idx += sizeof(req->Service.IncludedServices[i].EndHandle);
		pMsg[idx] = req->Service.IncludedServices[i].UuidType; idx++;

		switch (req->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Service.IncludedServices[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		pMsg[idx] = req->Service.IncludedServices[i].NbOfCharacteristics; idx++;
		pMsg[idx] = req->Service.IncludedServices[i].NbOfIncludedServices; idx++;
	}
	pMsg[idx] = req->MaxNbOfCharacteristics; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest(GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Discovery procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest(GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // EndingHandle
	msgLen += sizeof(uint8_t);  // MaxNbOfDescriptors

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->EndingHandle), sizeof(req->EndingHandle)); idx += sizeof(req->EndingHandle);
	pMsg[idx] = req->MaxNbOfDescriptors; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2E, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedReadCharacteristicValueRequest(GATTClientEnhancedReadCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedReadCharacteristicValueRequest(GATTClientEnhancedReadCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x2F, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedReadUsingCharacteristicUuidRequest(GATTClientEnhancedReadUsingCharacteristicUuidRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read By UUID procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedReadUsingCharacteristicUuidRequest(GATTClientEnhancedReadUsingCharacteristicUuidRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(bool_t);  // HandleRangeIncluded

	if (req->HandleRangeIncluded)
	{
		msgLen += sizeof(uint16_t);  // StartHandle
		msgLen += sizeof(uint16_t);  // EndHandle
	}	// HandleRange

	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->HandleRangeIncluded; idx++;

	if (req->HandleRangeIncluded)
	{
		FLib_MemCpy(pMsg + idx, &(req->HandleRange.StartHandle), sizeof(req->HandleRange.StartHandle)); idx += sizeof(req->HandleRange.StartHandle);
		FLib_MemCpy(pMsg + idx, &(req->HandleRange.EndHandle), sizeof(req->HandleRange.EndHandle)); idx += sizeof(req->HandleRange.EndHandle);
	}
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x30, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedReadMultipleCharacteristicValuesRequest(GATTClientEnhancedReadMultipleCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Read Multiple procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedReadMultipleCharacteristicValuesRequest(GATTClientEnhancedReadMultipleCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.Handle), sizeof(req->Characteristics[i].Value.Handle)); idx += sizeof(req->Characteristics[i].Value.Handle);
		pMsg[idx] = req->Characteristics[i].Value.UuidType; idx++;

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.ValueLength), sizeof(req->Characteristics[i].Value.ValueLength)); idx += sizeof(req->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.MaxValueLength), sizeof(req->Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].Handle), sizeof(req->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x31, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedWriteCharacteristicValueRequest(GATTClientEnhancedWriteCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Write procedure for a given Characteristic

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedWriteCharacteristicValueRequest(GATTClientEnhancedWriteCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // Properties
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint8_t);  // NbOfDescriptors

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
	}	// Descriptors
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value
	msgLen += sizeof(bool_t);  // WithoutResponse
	msgLen += sizeof(bool_t);  // SignedWrite
	msgLen += sizeof(bool_t);  // ReliableLongCharWrites
	msgLen += 16;  // Csrk

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->Characteristic.Properties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.Handle), sizeof(req->Characteristic.Value.Handle)); idx += sizeof(req->Characteristic.Value.Handle);
	pMsg[idx] = req->Characteristic.Value.UuidType; idx++;

	switch (req->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.ValueLength), sizeof(req->Characteristic.Value.ValueLength)); idx += sizeof(req->Characteristic.Value.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Characteristic.Value.MaxValueLength), sizeof(req->Characteristic.Value.MaxValueLength)); idx += sizeof(req->Characteristic.Value.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Characteristic.Value.Value, 0); idx += 0;
	pMsg[idx] = req->Characteristic.NbOfDescriptors; idx++;

	for (uint32_t i = 0; i < req->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].Handle), sizeof(req->Characteristic.Descriptors[i].Handle)); idx += sizeof(req->Characteristic.Descriptors[i].Handle);
		pMsg[idx] = req->Characteristic.Descriptors[i].UuidType; idx++;

		switch (req->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].ValueLength), sizeof(req->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristic.Descriptors[i].MaxValueLength), sizeof(req->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(req->Characteristic.Descriptors[i].MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristic.Descriptors[i].Value, 0); idx += 0;
	}
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;
	pMsg[idx] = req->WithoutResponse; idx++;
	pMsg[idx] = req->SignedWrite; idx++;
	pMsg[idx] = req->ReliableLongCharWrites; idx++;
	FLib_MemCpy(pMsg + idx, req->Csrk, 16); idx += 16;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x32, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedReadCharacteristicDescriptorRequest(GATTClientEnhancedReadCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Read procedure for a given Characteristic Descriptor

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedReadCharacteristicDescriptorRequest(GATTClientEnhancedReadCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint16_t);  // MaxReadBytes

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.Handle), sizeof(req->Descriptor.Handle)); idx += sizeof(req->Descriptor.Handle);
	pMsg[idx] = req->Descriptor.UuidType; idx++;

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.ValueLength), sizeof(req->Descriptor.ValueLength)); idx += sizeof(req->Descriptor.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.MaxValueLength), sizeof(req->Descriptor.MaxValueLength)); idx += sizeof(req->Descriptor.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Descriptor.Value, 0); idx += 0;
	FLib_MemCpy(pMsg + idx, &(req->MaxReadBytes), sizeof(req->MaxReadBytes)); idx += sizeof(req->MaxReadBytes);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x33, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedWriteCharacteristicDescriptorRequest(GATTClientEnhancedWriteCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Characteristic Descriptor Write procedure for a given Characteristic Descriptor

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedWriteCharacteristicDescriptorRequest(GATTClientEnhancedWriteCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += 0;  // Value
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.Handle), sizeof(req->Descriptor.Handle)); idx += sizeof(req->Descriptor.Handle);
	pMsg[idx] = req->Descriptor.UuidType; idx++;

	switch (req->Descriptor.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Descriptor.Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.ValueLength), sizeof(req->Descriptor.ValueLength)); idx += sizeof(req->Descriptor.ValueLength);
	FLib_MemCpy(pMsg + idx, &(req->Descriptor.MaxValueLength), sizeof(req->Descriptor.MaxValueLength)); idx += sizeof(req->Descriptor.MaxValueLength);
	FLib_MemCpy(pMsg + idx, req->Descriptor.Value, 0); idx += 0;
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x34, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest(GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initializes the Read Multiple Variable Length Characteristic Values procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest(GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint8_t);  // NbOfCharacteristics

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		msgLen += sizeof(uint8_t);  // Properties
		msgLen += sizeof(uint16_t);  // Handle
		msgLen += sizeof(uint8_t);  // UuidType

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				msgLen += 2;  // Uuid16Bits
				break;

			case Uuid128Bits:
				msgLen += 16;  // Uuid128Bits
				break;

			case Uuid32Bits:
				msgLen += 4;  // Uuid32Bits
				break;
		}		// Uuid
		msgLen += sizeof(uint16_t);  // ValueLength
		msgLen += sizeof(uint16_t);  // MaxValueLength
		msgLen += 0;  // Value
		msgLen += sizeof(uint8_t);  // NbOfDescriptors

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			msgLen += sizeof(uint16_t);  // Handle
			msgLen += sizeof(uint8_t);  // UuidType

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					msgLen += 2;  // Uuid16Bits
					break;

				case Uuid128Bits:
					msgLen += 16;  // Uuid128Bits
					break;

				case Uuid32Bits:
					msgLen += 4;  // Uuid32Bits
					break;
			}			// Uuid
			msgLen += sizeof(uint16_t);  // ValueLength
			msgLen += sizeof(uint16_t);  // MaxValueLength
			msgLen += 0;  // Value
		}		// Descriptors
	}	// Characteristics

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	pMsg[idx] = req->NbOfCharacteristics; idx++;

	for (uint32_t i = 0; i < req->NbOfCharacteristics; i++)
	{
		pMsg[idx] = req->Characteristics[i].Properties; idx++;
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.Handle), sizeof(req->Characteristics[i].Value.Handle)); idx += sizeof(req->Characteristics[i].Value.Handle);
		pMsg[idx] = req->Characteristics[i].Value.UuidType; idx++;

		switch (req->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid16Bits, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid128Bits, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Uuid.Uuid32Bits, 4); idx += 4;
				break;
		}
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.ValueLength), sizeof(req->Characteristics[i].Value.ValueLength)); idx += sizeof(req->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Value.MaxValueLength), sizeof(req->Characteristics[i].Value.MaxValueLength)); idx += sizeof(req->Characteristics[i].Value.MaxValueLength);
		FLib_MemCpy(pMsg + idx, req->Characteristics[i].Value.Value, 0); idx += 0;
		pMsg[idx] = req->Characteristics[i].NbOfDescriptors; idx++;

		for (uint32_t j = 0; j < req->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].Handle), sizeof(req->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(req->Characteristics[i].Descriptors[j].Handle);
			pMsg[idx] = req->Characteristics[i].Descriptors[j].UuidType; idx++;

			switch (req->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, 4); idx += 4;
					break;
			}
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].ValueLength), sizeof(req->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(pMsg + idx, &(req->Characteristics[i].Descriptors[j].MaxValueLength), sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(req->Characteristics[i].Descriptors[j].MaxValueLength);
			FLib_MemCpy(pMsg + idx, req->Characteristics[i].Descriptors[j].Value, 0); idx += 0;
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x35, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerRegisterEnhancedCallbackRequest(void *arg, uint8_t fsciInterface)
\brief	Installs an application callback for the GATT Server module

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTServerRegisterEnhancedCallbackRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x45, 0x36, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendAttributeWrittenStatusRequest(GATTServerEnhancedSendAttributeWrittenStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Responds to a Control Point write operation

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendAttributeWrittenStatusRequest(GATTServerEnhancedSendAttributeWrittenStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x37, req, sizeof(GATTServerEnhancedSendAttributeWrittenStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendNotificationRequest(GATTServerEnhancedSendNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendNotificationRequest(GATTServerEnhancedSendNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x38, req, sizeof(GATTServerEnhancedSendNotificationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendIndicationRequest(GATTServerEnhancedSendIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends an indication to a peer GATT Client

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendIndicationRequest(GATTServerEnhancedSendIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x39, req, sizeof(GATTServerEnhancedSendIndicationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendInstantValueNotificationRequest(GATTServerEnhancedSendInstantValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client with data given as parameter, ignoring the GATT Database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendInstantValueNotificationRequest(GATTServerEnhancedSendInstantValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Handle), sizeof(req->Handle)); idx += sizeof(req->Handle);
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x3A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendInstantValueIndicationRequest(GATTServerEnhancedSendInstantValueIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends an indication to a peer GATT Client with data given as parameter, ignoring the GATT Databas

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendInstantValueIndicationRequest(GATTServerEnhancedSendInstantValueIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Handle), sizeof(req->Handle)); idx += sizeof(req->Handle);
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x3B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendAttributeReadStatusRequest(GATTServerEnhancedSendAttributeReadStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Responds to an intercepted attribute read operation

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendAttributeReadStatusRequest(GATTServerEnhancedSendAttributeReadStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x3C, req, sizeof(GATTServerEnhancedSendAttributeReadStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTServerEnhancedSendMultipleHandleValueNotificationRequest(GATTServerEnhancedSendMultipleHandleValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends a notification to a peer GATT Client with data given as parameter,
                ignoring the GATT Database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTServerEnhancedSendMultipleHandleValueNotificationRequest(GATTServerEnhancedSendMultipleHandleValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // BearerId
	msgLen += sizeof(req->TotalLength);  // TotalLength
	msgLen += req->TotalLength;  // HandleLengthValueList

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->BearerId; idx++;
	FLib_MemCpy(pMsg + idx, req->TotalLength, sizeof(req->TotalLength)); idx += sizeof(req->TotalLength);
	FLib_MemCpy(pMsg + idx, req->HandleLengthValueList, req->TotalLength); idx += req->TotalLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x45, 0x3D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTClientGetDatabaseHashRequest(GATTClientGetDatabaseHashRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Updates the gatt database hash value for the peer server

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTClientGetDatabaseHashRequest(GATTClientGetDatabaseHashRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x45, 0x3E, req, sizeof(GATTClientGetDatabaseHashRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t GATTDBWriteAttributeRequest(GATTDBWriteAttributeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Writes an attribute from the application level

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBWriteAttributeRequest(GATTDBWriteAttributeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // Handle
	msgLen += sizeof(uint16_t);  // ValueLength
	msgLen += req->ValueLength;  // Value

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->Handle), sizeof(req->Handle)); idx += sizeof(req->Handle);
	FLib_MemCpy(pMsg + idx, &(req->ValueLength), sizeof(req->ValueLength)); idx += sizeof(req->ValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->ValueLength); idx += req->ValueLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x02, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBReadAttributeRequest(GATTDBReadAttributeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Reads an attribute from application level

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBReadAttributeRequest(GATTDBReadAttributeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x46, 0x03, req, sizeof(GATTDBReadAttributeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBFindServiceHandleRequest(GATTDBFindServiceHandleRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Finds the handle of a Service Declaration with a given UUID inside the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBFindServiceHandleRequest(GATTDBFindServiceHandleRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // StartHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->StartHandle), sizeof(req->StartHandle)); idx += sizeof(req->StartHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x04, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBFindCharValueHandleInServiceRequest(GATTDBFindCharValueHandleInServiceRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Finds the handle of a Characteristic Value with a given UUID inside a service

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBFindCharValueHandleInServiceRequest(GATTDBFindCharValueHandleInServiceRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // ServiceHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->ServiceHandle), sizeof(req->ServiceHandle)); idx += sizeof(req->ServiceHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x05, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBFindCccdHandleForCharValueHandleRequest(GATTDBFindCccdHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Finds the handle of a Characteristic's CCCD given the Characteristic's Value handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBFindCccdHandleForCharValueHandleRequest(GATTDBFindCccdHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x46, 0x06, req, sizeof(GATTDBFindCccdHandleForCharValueHandleRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBFindDescriptorHandleForCharValueHandleRequest(GATTDBFindDescriptorHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Finds the handle of a Characteristic Descriptor given the Characteristic's Value handle and Descriptor's UUID

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBFindDescriptorHandleForCharValueHandleRequest(GATTDBFindDescriptorHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // CharValueHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->CharValueHandle), sizeof(req->CharValueHandle)); idx += sizeof(req->CharValueHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x07, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicInitRequest(void *arg, uint8_t fsciInterface)
\brief	Allocates smallest possible buffers and initializes an empty database.

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTDBDynamicInitRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x46, 0x08, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicReleaseDatabaseRequest(void *arg, uint8_t fsciInterface)
\brief	Releases the allocated buffers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTDBDynamicReleaseDatabaseRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x46, 0x09, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddPrimaryServiceDeclarationRequest(GATTDBDynamicAddPrimaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Primary Service declaration into the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddPrimaryServiceDeclarationRequest(GATTDBDynamicAddPrimaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // DesiredHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->DesiredHandle), sizeof(req->DesiredHandle)); idx += sizeof(req->DesiredHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x0A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddSecondaryServiceDeclarationRequest(GATTDBDynamicAddSecondaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Secondary Service declaration into the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddSecondaryServiceDeclarationRequest(GATTDBDynamicAddSecondaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // DesiredHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->DesiredHandle), sizeof(req->DesiredHandle)); idx += sizeof(req->DesiredHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x0B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddIncludeDeclarationRequest(GATTDBDynamicAddIncludeDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds an Include declaration into the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddIncludeDeclarationRequest(GATTDBDynamicAddIncludeDeclarationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // IncludedServiceHandle
	msgLen += sizeof(uint16_t);  // EndGroupHandle
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->IncludedServiceHandle), sizeof(req->IncludedServiceHandle)); idx += sizeof(req->IncludedServiceHandle);
	FLib_MemCpy(pMsg + idx, &(req->EndGroupHandle), sizeof(req->EndGroupHandle)); idx += sizeof(req->EndGroupHandle);
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x0C, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Characteristic declaration and its Value into the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // CharacteristicProperties
	msgLen += sizeof(uint16_t);  // MaxValueLength
	msgLen += sizeof(uint16_t);  // InitialValueLength
	msgLen += req->InitialValueLength;  // InitialValue
	msgLen += sizeof(uint8_t);  // ValueAccessPermissions

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->CharacteristicProperties; idx++;
	FLib_MemCpy(pMsg + idx, &(req->MaxValueLength), sizeof(req->MaxValueLength)); idx += sizeof(req->MaxValueLength);
	FLib_MemCpy(pMsg + idx, &(req->InitialValueLength), sizeof(req->InitialValueLength)); idx += sizeof(req->InitialValueLength);
	FLib_MemCpy(pMsg + idx, req->InitialValue, req->InitialValueLength); idx += req->InitialValueLength;
	pMsg[idx] = req->ValueAccessPermissions; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x0D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddCharacteristicDescriptorRequest(GATTDBDynamicAddCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Characteristic descriptor into the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddCharacteristicDescriptorRequest(GATTDBDynamicAddCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint16_t);  // DescriptorValueLength
	msgLen += req->DescriptorValueLength;  // Value
	msgLen += sizeof(uint8_t);  // DescriptorAccessPermissions

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	FLib_MemCpy(pMsg + idx, &(req->DescriptorValueLength), sizeof(req->DescriptorValueLength)); idx += sizeof(req->DescriptorValueLength);
	FLib_MemCpy(pMsg + idx, req->Value, req->DescriptorValueLength); idx += req->DescriptorValueLength;
	pMsg[idx] = req->DescriptorAccessPermissions; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x0E, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddCccdRequest(void *arg, uint8_t fsciInterface)
\brief	Adds a CCCD in the database

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTDBDynamicAddCccdRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x46, 0x0F, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Characteristic declaration with a Value contained in an universal value buffer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // CharacteristicProperties
	msgLen += sizeof(uint8_t);  // ValueAccessPermissions

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->CharacteristicProperties; idx++;
	pMsg[idx] = req->ValueAccessPermissions; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x10, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicRemoveServiceRequest(GATTDBDynamicRemoveServiceRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Removes a Service from the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicRemoveServiceRequest(GATTDBDynamicRemoveServiceRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x46, 0x11, req, sizeof(GATTDBDynamicRemoveServiceRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicRemoveCharacteristicRequest(GATTDBDynamicRemoveCharacteristicRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Removes a Characteristic from the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicRemoveCharacteristicRequest(GATTDBDynamicRemoveCharacteristicRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x46, 0x12, req, sizeof(GATTDBDynamicRemoveCharacteristicRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicAddCharDescriptorWithUniqueValueRequest(GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a Characteristic descriptor into the database with an unique 512-byte value buffer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBDynamicAddCharDescriptorWithUniqueValueRequest(GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // UuidType

	switch (req->UuidType)
	{
		case Uuid16Bits:
			msgLen += 2;  // Uuid16Bits
			break;

		case Uuid128Bits:
			msgLen += 16;  // Uuid128Bits
			break;

		case Uuid32Bits:
			msgLen += 4;  // Uuid32Bits
			break;
	}	// Uuid
	msgLen += sizeof(uint8_t);  // DescriptorAccessPermissions

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->UuidType; idx++;

	switch (req->UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid16Bits, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid128Bits, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(pMsg + idx, req->Uuid.Uuid32Bits, 4); idx += 4;
			break;
	}
	pMsg[idx] = req->DescriptorAccessPermissions; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x46, 0x13, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBDynamicEndDatabaseUpdateRequest(void *arg, uint8_t fsciInterface)
\brief	Informs the peers of the changes produced in the database

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GATTDBDynamicEndDatabaseUpdateRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x46, 0x14, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* GATTDB_APP_ENABLE */

#if GATTDB_ATT_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttFindInformationRequest(GATTDBAttFindInformationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Find information request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttFindInformationRequest(GATTDBAttFindInformationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x47, 0x01, req, sizeof(GATTDBAttFindInformationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttFindByTypeValueRequest(GATTDBAttFindByTypeValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Find by type value request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttFindByTypeValueRequest(GATTDBAttFindByTypeValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // StartingHandle
	msgLen += sizeof(uint16_t);  // EndingHandle
	msgLen += sizeof(uint16_t);  // AttributeType
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.StartingHandle), sizeof(req->Params.StartingHandle)); idx += sizeof(req->Params.StartingHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.EndingHandle), sizeof(req->Params.EndingHandle)); idx += sizeof(req->Params.EndingHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeType), sizeof(req->Params.AttributeType)); idx += sizeof(req->Params.AttributeType);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x02, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttReadByTypeRequest(GATTDBAttReadByTypeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read by type request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttReadByTypeRequest(GATTDBAttReadByTypeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // StartingHandle
	msgLen += sizeof(uint16_t);  // EndingHandle
	msgLen += sizeof(uint8_t);  // Format

	switch (req->Params.Format)
	{
		case GATTDBAttReadByTypeRequest_Params_Format_Uuid16BitFormat:
			msgLen += sizeof(uint16_t);  // Uuid16BitFormat
			break;

		case GATTDBAttReadByTypeRequest_Params_Format_Uuid128BitFormat:
			msgLen += sizeof(req->Params.AttributeType.Uuid128BitFormat);  // Uuid128BitFormat
			break;
	}	// AttributeType

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.StartingHandle), sizeof(req->Params.StartingHandle)); idx += sizeof(req->Params.StartingHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.EndingHandle), sizeof(req->Params.EndingHandle)); idx += sizeof(req->Params.EndingHandle);
	pMsg[idx] = req->Params.Format; idx++;

	switch (req->Params.Format)
	{
		case GATTDBAttReadByTypeRequest_Params_Format_Uuid16BitFormat:
			FLib_MemCpy(pMsg + idx, &(req->Params.AttributeType.Uuid16BitFormat), sizeof(req->Params.AttributeType.Uuid16BitFormat)); idx += sizeof(req->Params.AttributeType.Uuid16BitFormat);
			break;

		case GATTDBAttReadByTypeRequest_Params_Format_Uuid128BitFormat:
			FLib_MemCpy(pMsg + idx, req->Params.AttributeType.Uuid128BitFormat, sizeof(req->Params.AttributeType.Uuid128BitFormat)); idx += sizeof(req->Params.AttributeType.Uuid128BitFormat);
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x03, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttReadRequest(GATTDBAttReadRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttReadRequest(GATTDBAttReadRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x47, 0x04, req, sizeof(GATTDBAttReadRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttReadBlobRequest(GATTDBAttReadBlobRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read blob request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttReadBlobRequest(GATTDBAttReadBlobRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x47, 0x05, req, sizeof(GATTDBAttReadBlobRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttReadMultipleRequest(GATTDBAttReadMultipleRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read multiple request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttReadMultipleRequest(GATTDBAttReadMultipleRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // HandleCount
	msgLen += req->Params.HandleCount * sizeof(uint16_t);  // ListOfHandles

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.HandleCount), sizeof(req->Params.HandleCount)); idx += sizeof(req->Params.HandleCount);
	FLib_MemCpy(pMsg + idx, req->Params.ListOfHandles, req->Params.HandleCount * sizeof(uint16_t)); idx += req->Params.HandleCount * sizeof(uint16_t);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x06, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttReadByGroupTypeRequest(GATTDBAttReadByGroupTypeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read by group type

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttReadByGroupTypeRequest(GATTDBAttReadByGroupTypeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // StartingHandle
	msgLen += sizeof(uint16_t);  // EndingHandle
	msgLen += sizeof(uint8_t);  // Format

	switch (req->Params.Format)
	{
		case GATTDBAttReadByGroupTypeRequest_Params_Format_Uuid16BitFormat:
			msgLen += sizeof(uint16_t);  // Uuid16BitFormat
			break;

		case GATTDBAttReadByGroupTypeRequest_Params_Format_Uuid128BitFormat:
			msgLen += sizeof(req->Params.AttributeType.Uuid128BitFormat);  // Uuid128BitFormat
			break;
	}	// AttributeType

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.StartingHandle), sizeof(req->Params.StartingHandle)); idx += sizeof(req->Params.StartingHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.EndingHandle), sizeof(req->Params.EndingHandle)); idx += sizeof(req->Params.EndingHandle);
	pMsg[idx] = req->Params.Format; idx++;

	switch (req->Params.Format)
	{
		case GATTDBAttReadByGroupTypeRequest_Params_Format_Uuid16BitFormat:
			FLib_MemCpy(pMsg + idx, &(req->Params.AttributeType.Uuid16BitFormat), sizeof(req->Params.AttributeType.Uuid16BitFormat)); idx += sizeof(req->Params.AttributeType.Uuid16BitFormat);
			break;

		case GATTDBAttReadByGroupTypeRequest_Params_Format_Uuid128BitFormat:
			FLib_MemCpy(pMsg + idx, req->Params.AttributeType.Uuid128BitFormat, sizeof(req->Params.AttributeType.Uuid128BitFormat)); idx += sizeof(req->Params.AttributeType.Uuid128BitFormat);
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x07, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttWriteRequest(GATTDBAttWriteRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Write request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttWriteRequest(GATTDBAttWriteRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x08, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttWriteCommandRequest(GATTDBAttWriteCommandRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Write command

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttWriteCommandRequest(GATTDBAttWriteCommandRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x09, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttSignedWriteCommandRequest(GATTDBAttSignedWriteCommandRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Signed write command

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttSignedWriteCommandRequest(GATTDBAttSignedWriteCommandRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue
	msgLen += 12;  // AuthenticationSignature

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;
	FLib_MemCpy(pMsg + idx, req->Params.AuthenticationSignature, 12); idx += 12;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x0A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttPrepareWriteRequest(GATTDBAttPrepareWriteRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Prepare write request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttPrepareWriteRequest(GATTDBAttPrepareWriteRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // ValueOffset
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.ValueOffset), sizeof(req->Params.ValueOffset)); idx += sizeof(req->Params.ValueOffset);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x0B, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttExecuteWriteRequest(GATTDBAttExecuteWriteRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Execute write request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttExecuteWriteRequest(GATTDBAttExecuteWriteRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x47, 0x0C, req, sizeof(GATTDBAttExecuteWriteRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttExecuteWriteFromQueueRequest(GATTDBAttExecuteWriteFromQueueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Executes an operation from a Prepare Write queue

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttExecuteWriteFromQueueRequest(GATTDBAttExecuteWriteFromQueueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // ValueOffset
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.ValueOffset), sizeof(req->Params.ValueOffset)); idx += sizeof(req->Params.ValueOffset);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x0D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GATTDBAttPrepareNotificationIndicationRequest(GATTDBAttPrepareNotificationIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Prepare notification/indication

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GATTDBAttPrepareNotificationIndicationRequest(GATTDBAttPrepareNotificationIndicationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // AttributeHandle
	msgLen += sizeof(uint16_t);  // AttributeLength
	msgLen += req->Params.AttributeLength;  // AttributeValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeHandle), sizeof(req->Params.AttributeHandle)); idx += sizeof(req->Params.AttributeHandle);
	FLib_MemCpy(pMsg + idx, &(req->Params.AttributeLength), sizeof(req->Params.AttributeLength)); idx += sizeof(req->Params.AttributeLength);
	FLib_MemCpy(pMsg + idx, req->Params.AttributeValue, req->Params.AttributeLength); idx += req->Params.AttributeLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x47, 0x0E, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

#endif  /* GATTDB_ATT_ENABLE */

#if GAP_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t BLEHostInitializeRequest(void *arg, uint8_t fsciInterface)
\brief	Performs central initialization of the BLE Host stack

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t BLEHostInitializeRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x01, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRegisterDeviceSecurityRequirementsRequest(GAPRegisterDeviceSecurityRequirementsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Registers the device security requirements

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRegisterDeviceSecurityRequirementsRequest(GAPRegisterDeviceSecurityRequirementsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // SecurityRequirementsIncluded

	if (req->SecurityRequirementsIncluded)
	{
		msgLen += sizeof(uint8_t);  // SecurityModeLevel
		msgLen += sizeof(bool_t);  // Authorization
		msgLen += sizeof(uint16_t);  // MinimumEncryptionKeySize
		msgLen += sizeof(uint8_t);  // NbOfServices

		for (uint32_t i = 0; i < req->SecurityRequirements.NbOfServices; i++)
		{
			msgLen += sizeof(uint16_t);  // ServiceHandle
			msgLen += sizeof(uint8_t);  // SecurityModeLevel
			msgLen += sizeof(bool_t);  // Authorization
			msgLen += sizeof(uint16_t);  // MinimumEncryptionKeySize
		}		// GapServiceSecurityRequirements
	}	// SecurityRequirements


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->SecurityRequirementsIncluded; idx++;

	if (req->SecurityRequirementsIncluded)
	{
		pMsg[idx] = req->SecurityRequirements.CentralSecurityRequirements.SecurityModeLevel; idx++;
		pMsg[idx] = req->SecurityRequirements.CentralSecurityRequirements.Authorization; idx++;
		FLib_MemCpy(pMsg + idx, &(req->SecurityRequirements.CentralSecurityRequirements.MinimumEncryptionKeySize), sizeof(req->SecurityRequirements.CentralSecurityRequirements.MinimumEncryptionKeySize)); idx += sizeof(req->SecurityRequirements.CentralSecurityRequirements.MinimumEncryptionKeySize);
		pMsg[idx] = req->SecurityRequirements.NbOfServices; idx++;

		for (uint32_t i = 0; i < req->SecurityRequirements.NbOfServices; i++)
		{
			FLib_MemCpy(pMsg + idx, &(req->SecurityRequirements.GapServiceSecurityRequirements[i].ServiceHandle), sizeof(req->SecurityRequirements.GapServiceSecurityRequirements[i].ServiceHandle)); idx += sizeof(req->SecurityRequirements.GapServiceSecurityRequirements[i].ServiceHandle);
			pMsg[idx] = req->SecurityRequirements.GapServiceSecurityRequirements[i].Requirements.SecurityModeLevel; idx++;
			pMsg[idx] = req->SecurityRequirements.GapServiceSecurityRequirements[i].Requirements.Authorization; idx++;
			FLib_MemCpy(pMsg + idx, &(req->SecurityRequirements.GapServiceSecurityRequirements[i].Requirements.MinimumEncryptionKeySize), sizeof(req->SecurityRequirements.GapServiceSecurityRequirements[i].Requirements.MinimumEncryptionKeySize)); idx += sizeof(req->SecurityRequirements.GapServiceSecurityRequirements[i].Requirements.MinimumEncryptionKeySize);
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x02, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetAdvertisingParametersRequest(GAPSetAdvertisingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the advertising parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetAdvertisingParametersRequest(GAPSetAdvertisingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x03, req, sizeof(GAPSetAdvertisingParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetAdvertisingDataRequest(GAPSetAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the advertising and scan response data

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetAdvertisingDataRequest(GAPSetAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // AdvertisingDataIncluded

	if (req->AdvertisingDataIncluded)
	{
		msgLen += sizeof(uint8_t);  // NbOfAdStructures

		for (uint32_t i = 0; i < req->AdvertisingData.NbOfAdStructures; i++)
		{
			msgLen += sizeof(uint8_t);  // Length
			msgLen += sizeof(uint8_t);  // Type
			msgLen += req->AdvertisingData.AdStructures[i].Length;  // Data
		}		// AdStructures
	}	// AdvertisingData

	msgLen += sizeof(bool_t);  // ScanResponseDataIncluded

	if (req->ScanResponseDataIncluded)
	{
		msgLen += sizeof(uint8_t);  // NbOfAdStructures

		for (uint32_t i = 0; i < req->ScanResponseData.NbOfAdStructures; i++)
		{
			msgLen += sizeof(uint8_t);  // Length
			msgLen += sizeof(uint8_t);  // Type
			msgLen += req->ScanResponseData.AdStructures[i].Length;  // Data
		}		// AdStructures
	}	// ScanResponseData


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->AdvertisingDataIncluded; idx++;

	if (req->AdvertisingDataIncluded)
	{
		pMsg[idx] = req->AdvertisingData.NbOfAdStructures; idx++;

		for (uint32_t i = 0; i < req->AdvertisingData.NbOfAdStructures; i++)
		{
			pMsg[idx] = req->AdvertisingData.AdStructures[i].Length; idx++;
			pMsg[idx] = req->AdvertisingData.AdStructures[i].Type; idx++;
			FLib_MemCpy(pMsg + idx, req->AdvertisingData.AdStructures[i].Data, req->AdvertisingData.AdStructures[i].Length); idx += req->AdvertisingData.AdStructures[i].Length;
		}
	}
	pMsg[idx] = req->ScanResponseDataIncluded; idx++;

	if (req->ScanResponseDataIncluded)
	{
		pMsg[idx] = req->ScanResponseData.NbOfAdStructures; idx++;

		for (uint32_t i = 0; i < req->ScanResponseData.NbOfAdStructures; i++)
		{
			pMsg[idx] = req->ScanResponseData.AdStructures[i].Length; idx++;
			pMsg[idx] = req->ScanResponseData.AdStructures[i].Type; idx++;
			FLib_MemCpy(pMsg + idx, req->ScanResponseData.AdStructures[i].Data, req->ScanResponseData.AdStructures[i].Length); idx += req->ScanResponseData.AdStructures[i].Length;
		}
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x04, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStartAdvertisingRequest(void *arg, uint8_t fsciInterface)
\brief	Commands the controller to start advertising

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPStartAdvertisingRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x05, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStopAdvertisingRequest(void *arg, uint8_t fsciInterface)
\brief	Commands the controller to stop advertising

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPStopAdvertisingRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x06, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPAuthorizeRequest(GAPAuthorizeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Authorizes a peer for a certain attribute in the database

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPAuthorizeRequest(GAPAuthorizeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x07, req, sizeof(GAPAuthorizeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSaveCccdRequest(GAPSaveCccdRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Save the CCCD value for a specific client and CCCD handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSaveCccdRequest(GAPSaveCccdRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x08, req, sizeof(GAPSaveCccdRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPCheckNotificationStatusRequest(GAPCheckNotificationStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Retrieves the notification status for a given client and a given CCCD handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPCheckNotificationStatusRequest(GAPCheckNotificationStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x09, req, sizeof(GAPCheckNotificationStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPCheckIndicationStatusRequest(GAPCheckIndicationStatusRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Retrieves the indication status for a given client and a given CCCD handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPCheckIndicationStatusRequest(GAPCheckIndicationStatusRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x0A, req, sizeof(GAPCheckIndicationStatusRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPairRequest(GAPPairRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initiate pairing with a peer device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPairRequest(GAPPairRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x0C, req, sizeof(GAPPairRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSendPeripheralSecurityRequestRequest(GAPSendPeripheralSecurityRequestRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Informs the peer Central about local security requirements

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSendPeripheralSecurityRequestRequest(GAPSendPeripheralSecurityRequestRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x0D, req, sizeof(GAPSendPeripheralSecurityRequestRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEncryptLinkRequest(GAPEncryptLinkRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Encrypts the link with a bonded peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEncryptLinkRequest(GAPEncryptLinkRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x0E, req, sizeof(GAPEncryptLinkRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPAcceptPairingRequestRequest(GAPAcceptPairingRequestRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Accepts the pairing request from a peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPAcceptPairingRequestRequest(GAPAcceptPairingRequestRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x0F, req, sizeof(GAPAcceptPairingRequestRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRejectPairingRequest(GAPRejectPairingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Rejects the peer's authentication request

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRejectPairingRequest(GAPRejectPairingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x10, req, sizeof(GAPRejectPairingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnterPasskeyRequest(GAPEnterPasskeyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enters the passkey requested by a peer during the pairing process

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnterPasskeyRequest(GAPEnterPasskeyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x11, req, sizeof(GAPEnterPasskeyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPProvideOobRequest(GAPProvideOobRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Provides the Out Of Band data for SMP pairing process

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPProvideOobRequest(GAPProvideOobRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x12, req, sizeof(GAPProvideOobRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRejectPasskeyRequestRequest(GAPRejectPasskeyRequestRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Rejects the passkey request from a peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRejectPasskeyRequestRequest(GAPRejectPasskeyRequestRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x13, req, sizeof(GAPRejectPasskeyRequestRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSendSmpKeysRequest(GAPSendSmpKeysRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sends the SMP keys during SMP Key Exchange procedure

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSendSmpKeysRequest(GAPSendSmpKeysRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(bool_t);  // LtkIncluded

	if (req->Keys.LtkIncluded)
	{
		msgLen += sizeof(uint8_t);  // LtkSize
		msgLen += req->Keys.LtkInfo.LtkSize;  // Ltk
	}	// LtkInfo

	msgLen += sizeof(bool_t);  // IrkIncluded

	if (req->Keys.IrkIncluded)
	{
		msgLen += 16;
	}  // Irk

	msgLen += sizeof(bool_t);  // CsrkIncluded

	if (req->Keys.CsrkIncluded)
	{
		msgLen += 16;
	}  // Csrk


	if (req->Keys.LtkIncluded)
	{
		msgLen += sizeof(uint8_t);  // RandSize
		msgLen += req->Keys.RandEdivInfo.RandSize;  // Rand
		msgLen += sizeof(uint16_t);  // Ediv
	}	// RandEdivInfo

	msgLen += sizeof(bool_t);  // AddressIncluded


	if (req->Keys.AddressIncluded)
	{
		msgLen += sizeof(uint8_t);  // DeviceAddressType
		msgLen += 6;  // DeviceAddress
	}	// AddressInfo


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->Keys.LtkIncluded; idx++;

	if (req->Keys.LtkIncluded)
	{
		pMsg[idx] = req->Keys.LtkInfo.LtkSize; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.LtkInfo.Ltk, req->Keys.LtkInfo.LtkSize); idx += req->Keys.LtkInfo.LtkSize;
	}
	pMsg[idx] = req->Keys.IrkIncluded; idx++;

	if (req->Keys.IrkIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->Keys.Irk, 16); idx += 16;
	}

	pMsg[idx] = req->Keys.CsrkIncluded; idx++;

	if (req->Keys.CsrkIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->Keys.Csrk, 16); idx += 16;
	}


	if (req->Keys.LtkIncluded)
	{
		pMsg[idx] = req->Keys.RandEdivInfo.RandSize; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.RandEdivInfo.Rand, req->Keys.RandEdivInfo.RandSize); idx += req->Keys.RandEdivInfo.RandSize;
		FLib_MemCpy(pMsg + idx, &(req->Keys.RandEdivInfo.Ediv), sizeof(req->Keys.RandEdivInfo.Ediv)); idx += sizeof(req->Keys.RandEdivInfo.Ediv);
	}

	if (req->Keys.IrkIncluded)
	{
		pMsg[idx] = req->Keys.AddressIncluded; idx++;
	}


	if (req->Keys.AddressIncluded)
	{
		pMsg[idx] = req->Keys.AddressInfo.DeviceAddressType; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.AddressInfo.DeviceAddress, 6); idx += 6;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x14, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRejectKeyExchangeRequestRequest(GAPRejectKeyExchangeRequestRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Rejects the Key Exchange procedure with a paired peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRejectKeyExchangeRequestRequest(GAPRejectKeyExchangeRequestRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x15, req, sizeof(GAPRejectKeyExchangeRequestRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPProvideLongTermKeyRequest(GAPProvideLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Provides the Long Term Key to the controller for encryption setup

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPProvideLongTermKeyRequest(GAPProvideLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // LtkSize
	msgLen += req->LtkSize;  // Ltk

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->LtkSize; idx++;
	FLib_MemCpy(pMsg + idx, req->Ltk, req->LtkSize); idx += req->LtkSize;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x16, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPDenyLongTermKeyRequest(GAPDenyLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Rejects a long term key request from the controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPDenyLongTermKeyRequest(GAPDenyLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x17, req, sizeof(GAPDenyLongTermKeyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLoadEncryptionInformationRequest(GAPLoadEncryptionInformationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Loads encryption key for a bonded device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLoadEncryptionInformationRequest(GAPLoadEncryptionInformationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x18, req, sizeof(GAPLoadEncryptionInformationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetLocalPasskeyRequest(GAPSetLocalPasskeyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the SMP passkey for this device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetLocalPasskeyRequest(GAPSetLocalPasskeyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x19, req, sizeof(GAPSetLocalPasskeyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStartScanningRequest(GAPStartScanningRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the scanning parameters (optionally) and begins scanning

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPStartScanningRequest(GAPStartScanningRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // ScanningParametersIncluded

	if (req->ScanningParametersIncluded)
	{
		msgLen += sizeof(uint8_t);  // Type
		msgLen += sizeof(uint16_t);  // Interval
		msgLen += sizeof(uint16_t);  // Window
		msgLen += sizeof(uint8_t);  // OwnAddressType
		msgLen += sizeof(uint8_t);  // FilterPolicy
	}	// ScanningParameters

	msgLen += sizeof(uint8_t);  // FilterDuplicates
	msgLen += 1;  // gLePhyCoded_c|gLePhy2M_c|gLePhy1M_c  // ScanningPHYs
	msgLen += sizeof(uint16_t);  // Duration
	msgLen += sizeof(uint16_t);  // Period

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->ScanningParametersIncluded; idx++;

	if (req->ScanningParametersIncluded)
	{
		pMsg[idx] = req->ScanningParameters.Type; idx++;
		FLib_MemCpy(pMsg + idx, &(req->ScanningParameters.Interval), sizeof(req->ScanningParameters.Interval)); idx += sizeof(req->ScanningParameters.Interval);
		FLib_MemCpy(pMsg + idx, &(req->ScanningParameters.Window), sizeof(req->ScanningParameters.Window)); idx += sizeof(req->ScanningParameters.Window);
		pMsg[idx] = req->ScanningParameters.OwnAddressType; idx++;
		pMsg[idx] = req->ScanningParameters.FilterPolicy; idx++;
	}
	pMsg[idx] = req->FilterDuplicates; idx++;
	pMsg[idx] = req->ScanningPHYs; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Duration), sizeof(req->Duration)); idx += sizeof(req->Duration);
	FLib_MemCpy(pMsg + idx, &(req->Period), sizeof(req->Period)); idx += sizeof(req->Period);

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x1A, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStopScanningRequest(void *arg, uint8_t fsciInterface)
\brief	Commands the controller to stop scanning

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPStopScanningRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x1B, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPConnectRequest(GAPConnectRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Connects to a scanned device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPConnectRequest(GAPConnectRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x1C, req, sizeof(GAPConnectRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPDisconnectRequest(GAPDisconnectRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Initiates disconnection from a connected peer device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPDisconnectRequest(GAPDisconnectRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x1D, req, sizeof(GAPDisconnectRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSaveCustomPeerInformationRequest(GAPSaveCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Saves custom peer information in raw data format

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSaveCustomPeerInformationRequest(GAPSaveCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // Offset
	msgLen += sizeof(uint16_t);  // InfoSize
	msgLen += req->InfoSize;  // Info

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->Offset), sizeof(req->Offset)); idx += sizeof(req->Offset);
	FLib_MemCpy(pMsg + idx, &(req->InfoSize), sizeof(req->InfoSize)); idx += sizeof(req->InfoSize);
	FLib_MemCpy(pMsg + idx, req->Info, req->InfoSize); idx += req->InfoSize;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x1E, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLoadCustomPeerInformationRequest(GAPLoadCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Loads the custom peer information in raw data format

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLoadCustomPeerInformationRequest(GAPLoadCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x1F, req, sizeof(GAPLoadCustomPeerInformationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPCheckIfBondedRequest(GAPCheckIfBondedRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Verifies if a connected peer device is bonded

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPCheckIfBondedRequest(GAPCheckIfBondedRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x20, req, sizeof(GAPCheckIfBondedRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadFilterAcceptListSizeRequest(void *arg, uint8_t fsciInterface)
\brief	Retrieves the size of the Filter Accept List

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPReadFilterAcceptListSizeRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x21, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPClearFilterAcceptListRequest(void *arg, uint8_t fsciInterface)
\brief	Removes all addresses from the Filter Accept List

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPClearFilterAcceptListRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x22, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPAddDeviceToFilterAcceptListRequest(GAPAddDeviceToFilterAcceptListRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Adds a device address to the Filter Accept List

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPAddDeviceToFilterAcceptListRequest(GAPAddDeviceToFilterAcceptListRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x23, req, sizeof(GAPAddDeviceToFilterAcceptListRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRemoveDeviceFromFilterAcceptListRequest(GAPRemoveDeviceFromFilterAcceptListRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Removes a device address from the Filter Accept List

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRemoveDeviceFromFilterAcceptListRequest(GAPRemoveDeviceFromFilterAcceptListRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x24, req, sizeof(GAPRemoveDeviceFromFilterAcceptListRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadPublicDeviceAddressRequest(void *arg, uint8_t fsciInterface)
\brief	Reads the device's public address from the controller

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPReadPublicDeviceAddressRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x25, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPCreateRandomDeviceAddressRequest(GAPCreateRandomDeviceAddressRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Requests the controller to create a random address

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPCreateRandomDeviceAddressRequest(GAPCreateRandomDeviceAddressRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // IrkIncluded

	if (req->IrkIncluded)
	{
		msgLen += 16;
	}  // Irk

	msgLen += sizeof(bool_t);  // RandomPartIncluded


	if (req->RandomPartIncluded)
	{
		msgLen += 3;
	}  // RandomPart


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->IrkIncluded; idx++;

	if (req->IrkIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->Irk, 16); idx += 16;
	}


	if (req->IrkIncluded)
	{
		pMsg[idx] = req->RandomPartIncluded; idx++;
	}


	if (req->RandomPartIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->RandomPart, sizeof(req->RandomPart)); idx += sizeof(req->RandomPart);
	}


	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x26, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSaveDeviceNameRequest(GAPSaveDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Saves the name of a bonded device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSaveDeviceNameRequest(GAPSaveDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // NameSize
	msgLen += req->NameSize;  // Name

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->NameSize; idx++;
	FLib_MemCpy(pMsg + idx, req->Name, req->NameSize); idx += req->NameSize;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x27, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGetBondedDevicesCountRequest(void *arg, uint8_t fsciInterface)
\brief	Retrieves the number of bonded devices

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPGetBondedDevicesCountRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x28, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGetBondedDeviceNameRequest(GAPGetBondedDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Retrieves the name of a bonded device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPGetBondedDeviceNameRequest(GAPGetBondedDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x29, req, sizeof(GAPGetBondedDeviceNameRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRemoveBondRequest(GAPRemoveBondRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Removes the bond with a device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRemoveBondRequest(GAPRemoveBondRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x2A, req, sizeof(GAPRemoveBondRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRemoveAllBondsRequest(void *arg, uint8_t fsciInterface)
\brief	Removes all bonds with other devices

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPRemoveAllBondsRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x2B, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadRadioPowerLevelRequest(GAPReadRadioPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Reads the power level of the controller's radio

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPReadRadioPowerLevelRequest(GAPReadRadioPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x2C, req, sizeof(GAPReadRadioPowerLevelRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPVerifyPrivateResolvableAddressRequest(GAPVerifyPrivateResolvableAddressRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Verifies a Private Resolvable Address with a bonded device's IRK

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPVerifyPrivateResolvableAddressRequest(GAPVerifyPrivateResolvableAddressRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x2D, req, sizeof(GAPVerifyPrivateResolvableAddressRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetRandomAddressRequest(GAPSetRandomAddressRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets a random address into the controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetRandomAddressRequest(GAPSetRandomAddressRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x2E, req, sizeof(GAPSetRandomAddressRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetScanModeRequest(GAPSetScanModeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets internal scan filters and actions

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetScanModeRequest(GAPSetScanModeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // ScanMode
	msgLen += sizeof(uint8_t);  // NbOfAddresses
	msgLen += sizeof(bool_t);  // WriteInFilterAcceptList

	for (uint32_t i = 0; i < req->AutoConnectParams.NbOfAddresses; i++)
	{
		msgLen += sizeof(uint16_t);  // ScanInterval
		msgLen += sizeof(uint16_t);  // ScanWindow
		msgLen += sizeof(uint8_t);  // FilterPolicy
		msgLen += sizeof(uint8_t);  // OwnAddressType
		msgLen += sizeof(uint8_t);  // PeerAddressType
		msgLen += 6;  // PeerAddress
		msgLen += sizeof(uint16_t);  // ConnIntervalMin
		msgLen += sizeof(uint16_t);  // ConnIntervalMax
		msgLen += sizeof(uint16_t);  // ConnLatency
		msgLen += sizeof(uint16_t);  // SupervisionTimeout
		msgLen += sizeof(uint16_t);  // ConnEventLengthMin
		msgLen += sizeof(uint16_t);  // ConnEventLengthMax
		msgLen += sizeof(bool_t);  // usePeerIdentityAddress
		msgLen += 1;  // gLePhyCoded_c|gLePhy2M_c|gLePhy1M_c  // Initiating_PHYs
	}	// AutoConnectData

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->ScanMode; idx++;
	pMsg[idx] = req->AutoConnectParams.NbOfAddresses; idx++;
	pMsg[idx] = req->AutoConnectParams.WriteInFilterAcceptList; idx++;

	for (uint32_t i = 0; i < req->AutoConnectParams.NbOfAddresses; i++)
	{
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ScanInterval), sizeof(req->AutoConnectParams.AutoConnectData[i].ScanInterval)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ScanInterval);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ScanWindow), sizeof(req->AutoConnectParams.AutoConnectData[i].ScanWindow)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ScanWindow);
		pMsg[idx] = req->AutoConnectParams.AutoConnectData[i].FilterPolicy; idx++;
		pMsg[idx] = req->AutoConnectParams.AutoConnectData[i].OwnAddressType; idx++;
		pMsg[idx] = req->AutoConnectParams.AutoConnectData[i].PeerAddressType; idx++;
		FLib_MemCpy(pMsg + idx, req->AutoConnectParams.AutoConnectData[i].PeerAddress, 6); idx += 6;
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMin), sizeof(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMin)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMin);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMax), sizeof(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMax)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ConnIntervalMax);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ConnLatency), sizeof(req->AutoConnectParams.AutoConnectData[i].ConnLatency)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ConnLatency);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].SupervisionTimeout), sizeof(req->AutoConnectParams.AutoConnectData[i].SupervisionTimeout)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].SupervisionTimeout);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMin), sizeof(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMin)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMin);
		FLib_MemCpy(pMsg + idx, &(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMax), sizeof(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMax)); idx += sizeof(req->AutoConnectParams.AutoConnectData[i].ConnEventLengthMax);
		pMsg[idx] = req->AutoConnectParams.AutoConnectData[i].usePeerIdentityAddress; idx++;
		pMsg[idx] = req->AutoConnectParams.AutoConnectData[i].Initiating_PHYs; idx++;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x2F, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetDefaultPairingParametersRequest(GAPSetDefaultPairingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the default pairing parameters to be used by automatic pairing procedures

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetDefaultPairingParametersRequest(GAPSetDefaultPairingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // PairingParametersIncluded

	if (req->PairingParametersIncluded)
	{
		msgLen += sizeof(bool_t);  // WithBonding
		msgLen += sizeof(uint8_t);  // SecurityModeAndLevel
		msgLen += sizeof(uint8_t);  // MaxEncryptionKeySize
		msgLen += sizeof(uint8_t);  // LocalIoCapabilities
		msgLen += sizeof(bool_t);  // OobAvailable
		msgLen += 1;  // 0x04|0x02|0x01  // CentralKeys
		msgLen += 1;  // 0x04|0x02|0x01  // PeripheralKeys
		msgLen += sizeof(bool_t);  // LeSecureConnectionSupported
		msgLen += sizeof(bool_t);  // UseKeypressNotifications
	}	// PairingParameters


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->PairingParametersIncluded; idx++;

	if (req->PairingParametersIncluded)
	{
		pMsg[idx] = req->PairingParameters.WithBonding; idx++;
		pMsg[idx] = req->PairingParameters.SecurityModeAndLevel; idx++;
		pMsg[idx] = req->PairingParameters.MaxEncryptionKeySize; idx++;
		pMsg[idx] = req->PairingParameters.LocalIoCapabilities; idx++;
		pMsg[idx] = req->PairingParameters.OobAvailable; idx++;
		pMsg[idx] = req->PairingParameters.CentralKeys; idx++;
		pMsg[idx] = req->PairingParameters.PeripheralKeys; idx++;
		pMsg[idx] = req->PairingParameters.LeSecureConnectionSupported; idx++;
		pMsg[idx] = req->PairingParameters.UseKeypressNotifications; idx++;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x30, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPUpdateConnectionParametersRequest(GAPUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Request a set of new connection parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPUpdateConnectionParametersRequest(GAPUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x31, req, sizeof(GAPUpdateConnectionParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableUpdateConnectionParametersRequest(GAPEnableUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Update the connection parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableUpdateConnectionParametersRequest(GAPEnableUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x32, req, sizeof(GAPEnableUpdateConnectionParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GapUpdateLeDataLengthRequest(GapUpdateLeDataLengthRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Update the Tx Data parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GapUpdateLeDataLengthRequest(GapUpdateLeDataLengthRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x33, req, sizeof(GapUpdateLeDataLengthRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableHostPrivacyRequest(GAPEnableHostPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enables or disables Host Privacy (automatic regeneration of a Private Address)

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableHostPrivacyRequest(GAPEnableHostPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // Enable

	if (req->Enable)
	{
		msgLen += 16;
	}  // Irk


	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->Enable; idx++;

	if (req->Enable)
	{
		FLib_MemCpy(pMsg + idx, req->Irk, 16); idx += 16;
	}


	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x35, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableControllerPrivacyRequest(GAPEnableControllerPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enables or disables Controller Privacy (Enhanced Privacy feature)

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableControllerPrivacyRequest(GAPEnableControllerPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(bool_t);  // Enable

	if (req->Enable)
	{
		msgLen += 16;
	}  // OwnIrk


	if (req->Enable)
	{
		msgLen += 1;
	}  // PeerIdCount


	for (uint32_t i = 0; i < req->PeerIdCount; i++)
	{
		msgLen += sizeof(uint8_t);  // IdentityAddressType
		msgLen += 6;  // IdentityAddress
		msgLen += 16;  // Irk
		msgLen += sizeof(uint8_t);  // PrivacyMode
	}	// PeerIdentities

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->Enable; idx++;

	if (req->Enable)
	{
		FLib_MemCpy(pMsg + idx, req->OwnIrk, 16); idx += 16;
	}


	if (req->Enable)
	{
		pMsg[idx] = req->PeerIdCount; idx++;
	}


	for (uint32_t i = 0; i < req->PeerIdCount; i++)
	{
		pMsg[idx] = req->PeerIdentities[i].IdentityAddressType; idx++;
		FLib_MemCpy(pMsg + idx, req->PeerIdentities[i].IdentityAddress, 6); idx += 6;
		FLib_MemCpy(pMsg + idx, req->PeerIdentities[i].Irk, 16); idx += 16;
		pMsg[idx] = req->PeerIdentities[i].PrivacyMode; idx++;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x36, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeScRegeneratePublicKeyRequest(void *arg, uint8_t fsciInterface)
\brief	Regenerate the private/public key pair used for LE Secure Connections pairing

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPLeScRegeneratePublicKeyRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x37, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeScValidateNumericValueRequest(GAPLeScValidateNumericValueRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Validate the numeric value during the Numeric Comparison LE Secure Connections pairing

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLeScValidateNumericValueRequest(GAPLeScValidateNumericValueRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x38, req, sizeof(GAPLeScValidateNumericValueRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeScGetLocalOobDataRequest(void *arg, uint8_t fsciInterface)
\brief	Retrieve local OOB data used for LE Secure Connections pairing

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPLeScGetLocalOobDataRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x39, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeScSetPeerOobDataRequest(GAPLeScSetPeerOobDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set peer OOB data used for LE Secure Connections pairing

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLeScSetPeerOobDataRequest(GAPLeScSetPeerOobDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3A, req, sizeof(GAPLeScSetPeerOobDataRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeScSendKeypressNotificationPrivacyRequest(GAPLeScSendKeypressNotificationPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Send a Keypress Notification to the peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLeScSendKeypressNotificationPrivacyRequest(GAPLeScSendKeypressNotificationPrivacyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3B, req, sizeof(GAPLeScSendKeypressNotificationPrivacyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGetBondedDevicesIdentityInformationRequest(GAPGetBondedDevicesIdentityInformationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Retrieves a list of the identity information of bonded devices, if any

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPGetBondedDevicesIdentityInformationRequest(GAPGetBondedDevicesIdentityInformationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3C, req, sizeof(GAPGetBondedDevicesIdentityInformationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetTxPowerLevelRequest(GAPSetTxPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets a Transmission power level in the controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetTxPowerLevelRequest(GAPSetTxPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3D, req, sizeof(GAPSetTxPowerLevelRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeReadPhyRequest(GAPLeReadPhyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read the Tx and Rx Phy on the connection with a device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLeReadPhyRequest(GAPLeReadPhyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3E, req, sizeof(GAPLeReadPhyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLeSetPhyRequest(GAPLeSetPhyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set the Tx and Rx Phy preferences on the connection with a device or all subsequent connections

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLeSetPhyRequest(GAPLeSetPhyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x3F, req, sizeof(GAPLeSetPhyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPControllerEnhancedNotificationRequest(GAPControllerEnhancedNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Configure enhanced ADV/SCAN/CONN events in the controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPControllerEnhancedNotificationRequest(GAPControllerEnhancedNotificationRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x40, req, sizeof(GAPControllerEnhancedNotificationRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPLoadKeysRequest(GAPLoadKeysRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Load the bond keys from an NVM index

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPLoadKeysRequest(GAPLoadKeysRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x41, req, sizeof(GAPLoadKeysRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSaveKeysRequest(GAPSaveKeysRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Save the bond keys to an NVM index

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSaveKeysRequest(GAPSaveKeysRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // NvmIndex
	msgLen += sizeof(bool_t);  // LtkIncluded

	if (req->Keys.LtkIncluded)
	{
		msgLen += sizeof(uint8_t);  // LtkSize
		msgLen += req->Keys.LtkInfo.LtkSize;  // Ltk
	}	// LtkInfo

	msgLen += sizeof(bool_t);  // IrkIncluded

	if (req->Keys.IrkIncluded)
	{
		msgLen += 16;
	}  // Irk

	msgLen += sizeof(bool_t);  // CsrkIncluded

	if (req->Keys.CsrkIncluded)
	{
		msgLen += 16;
	}  // Csrk


	if (req->Keys.LtkIncluded)
	{
		msgLen += sizeof(uint8_t);  // RandSize
		msgLen += req->Keys.RandEdivInfo.RandSize;  // Rand
		msgLen += sizeof(uint16_t);  // Ediv
	}	// RandEdivInfo

	msgLen += sizeof(bool_t);  // AddressIncluded


	if (req->Keys.AddressIncluded)
	{
		msgLen += sizeof(uint8_t);  // DeviceAddressType
		msgLen += 6;  // DeviceAddress
	}	// AddressInfo

	msgLen += sizeof(bool_t);  // LeSc
	msgLen += sizeof(bool_t);  // Authenticated

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->NvmIndex; idx++;
	pMsg[idx] = req->Keys.LtkIncluded; idx++;

	if (req->Keys.LtkIncluded)
	{
		pMsg[idx] = req->Keys.LtkInfo.LtkSize; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.LtkInfo.Ltk, req->Keys.LtkInfo.LtkSize); idx += req->Keys.LtkInfo.LtkSize;
	}
	pMsg[idx] = req->Keys.IrkIncluded; idx++;

	if (req->Keys.IrkIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->Keys.Irk, 16); idx += 16;
	}

	pMsg[idx] = req->Keys.CsrkIncluded; idx++;

	if (req->Keys.CsrkIncluded)
	{
		FLib_MemCpy(pMsg + idx, req->Keys.Csrk, 16); idx += 16;
	}


	if (req->Keys.LtkIncluded)
	{
		pMsg[idx] = req->Keys.RandEdivInfo.RandSize; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.RandEdivInfo.Rand, req->Keys.RandEdivInfo.RandSize); idx += req->Keys.RandEdivInfo.RandSize;
		FLib_MemCpy(pMsg + idx, &(req->Keys.RandEdivInfo.Ediv), sizeof(req->Keys.RandEdivInfo.Ediv)); idx += sizeof(req->Keys.RandEdivInfo.Ediv);
	}

	if (req->Keys.IrkIncluded)
	{
		pMsg[idx] = req->Keys.AddressIncluded; idx++;
	}


	if (req->Keys.AddressIncluded)
	{
		pMsg[idx] = req->Keys.AddressInfo.DeviceAddressType; idx++;
		FLib_MemCpy(pMsg + idx, req->Keys.AddressInfo.DeviceAddress, 6); idx += 6;
	}
	pMsg[idx] = req->LeSc; idx++;
	pMsg[idx] = req->Authenticated; idx++;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x42, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetChannelMapRequest(GAPSetChannelMapRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set a channel classification in the Controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetChannelMapRequest(GAPSetChannelMapRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x43, req, sizeof(GAPSetChannelMapRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadChannelMapRequest(GAPReadChannelMapRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read the channel map from a connected peer

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPReadChannelMapRequest(GAPReadChannelMapRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x44, req, sizeof(GAPReadChannelMapRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetPrivacyModeRequest(GAPSetPrivacyModeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set the privacy mode for an NVM index

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetPrivacyModeRequest(GAPSetPrivacyModeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x45, req, sizeof(GAPSetPrivacyModeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t ControllerSetScanDupFiltModeRequest(ControllerSetScanDupFiltModeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Configure Duplicate Filtering Behavior

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t ControllerSetScanDupFiltModeRequest(ControllerSetScanDupFiltModeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x46, req, sizeof(ControllerSetScanDupFiltModeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadControllerLocalRPARequest(GAPReadControllerLocalRPARequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read Controller Local Resolvable Private Address

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPReadControllerLocalRPARequest(GAPReadControllerLocalRPARequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x47, req, sizeof(GAPReadControllerLocalRPARequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPCheckNvmIndexRequest(GAPCheckNvmIndexRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Verifies if an NVM index is free or contains a bond

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPCheckNvmIndexRequest(GAPCheckNvmIndexRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x49, req, sizeof(GAPCheckNvmIndexRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGetDeviceIdFromConnHandleRequest(GAPGetDeviceIdFromConnHandleRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Get the device id corresponding to the given connection handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPGetDeviceIdFromConnHandleRequest(GAPGetDeviceIdFromConnHandleRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x4A, req, sizeof(GAPGetDeviceIdFromConnHandleRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGetConnectionHandleFromDeviceId(GAPGetConnectionHandleFromDeviceId_t *req, void *arg, uint8_t fsciInterface)
\brief	Get the connection handle corresponding to the given device id

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPGetConnectionHandleFromDeviceId(GAPGetConnectionHandleFromDeviceId_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x4B, req, sizeof(GAPGetConnectionHandleFromDeviceId_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPAdvIndexChangeRequest(GAPAdvIndexChangeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Configures advertising index type.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPAdvIndexChangeRequest(GAPAdvIndexChangeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x4C, req, sizeof(GAPAdvIndexChangeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPGetHostVersion(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x4D, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetExtAdvertisingParametersRequest(GAPSetExtAdvertisingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the advertising parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetExtAdvertisingParametersRequest(GAPSetExtAdvertisingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x50, req, sizeof(GAPSetExtAdvertisingParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStartExtAdvertisingRequest(GAPStartExtAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Commands the controller to start advertising

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPStartExtAdvertisingRequest(GAPStartExtAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x51, req, sizeof(GAPStartExtAdvertisingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPRemoveAdvertisingSetRequest(GAPRemoveAdvertisingSetRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Remove an advertising set from the Controller

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPRemoveAdvertisingSetRequest(GAPRemoveAdvertisingSetRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x52, req, sizeof(GAPRemoveAdvertisingSetRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStopExtAdvertisingRequest(GAPStopExtAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Commands the controller to stop advertising

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPStopExtAdvertisingRequest(GAPStopExtAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x53, req, sizeof(GAPStopExtAdvertisingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPUpdatePeriodicAdvListRequest(GAPUpdatePeriodicAdvListRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Commands the controller to update the periodic advertiser list

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPUpdatePeriodicAdvListRequest(GAPUpdatePeriodicAdvListRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // Operation

	switch (req->Operation)
	{
		case GAPUpdatePeriodicAdvListRequest_Operation_gAddDevice_c:
			msgLen += sizeof(uint8_t);  // DeviceAddressType
			msgLen += 6;  // DeviceAddress
			msgLen += sizeof(uint8_t);  // SID
			break;

		case GAPUpdatePeriodicAdvListRequest_Operation_gRemoveDevice_c:
			msgLen += sizeof(uint8_t);  // DeviceAddressType
			msgLen += 6;  // DeviceAddress
			msgLen += sizeof(uint8_t);  // SID
			break;

		case GAPUpdatePeriodicAdvListRequest_Operation_gRemoveAllDevices_c:
			break;
	}  // OperationValue

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->Operation; idx++;

	switch (req->Operation)
	{
		case GAPUpdatePeriodicAdvListRequest_Operation_gAddDevice_c:
			pMsg[idx] = req->OperationValue.gAddDevice_c.DeviceAddressType; idx++;
			FLib_MemCpy(pMsg + idx, req->OperationValue.gAddDevice_c.DeviceAddress, 6); idx += 6;
			pMsg[idx] = req->OperationValue.gAddDevice_c.SID; idx++;
			break;

		case GAPUpdatePeriodicAdvListRequest_Operation_gRemoveDevice_c:
			pMsg[idx] = req->OperationValue.gRemoveDevice_c.DeviceAddressType; idx++;
			FLib_MemCpy(pMsg + idx, req->OperationValue.gRemoveDevice_c.DeviceAddress, 6); idx += 6;
			pMsg[idx] = req->OperationValue.gRemoveDevice_c.SID; idx++;
			break;

		case GAPUpdatePeriodicAdvListRequest_Operation_gRemoveAllDevices_c:
			break;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x54, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetPeriodicAdvParametersRequest(GAPSetPeriodicAdvParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the advertising parameters

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetPeriodicAdvParametersRequest(GAPSetPeriodicAdvParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x55, req, sizeof(GAPSetPeriodicAdvParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStartPeriodicAdvertisingRequest(GAPStartPeriodicAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Start Periodic Advertising for a set Id

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPStartPeriodicAdvertisingRequest(GAPStartPeriodicAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x56, req, sizeof(GAPStartPeriodicAdvertisingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPStopPeriodicAdvertisingRequest(GAPStopPeriodicAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Stop Periodic Advertising for a set Id

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPStopPeriodicAdvertisingRequest(GAPStopPeriodicAdvertisingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x57, req, sizeof(GAPStopPeriodicAdvertisingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetExtAdvertisingDataRequest(GAPSetExtAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the extended advertising and extended scan response data

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetExtAdvertisingDataRequest(GAPSetExtAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x58, req, sizeof(GAPSetExtAdvertisingDataRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetPeriodicAdvertisingDataRequest(GAPSetPeriodicAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Sets the extended advertising and extended scan response data

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetPeriodicAdvertisingDataRequest(GAPSetPeriodicAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // Handle
	msgLen += sizeof(uint8_t);  // NbOfAdStructures

	for (uint32_t i = 0; i < req->PeriodicAdvertisingData.NbOfAdStructures; i++)
	{
		msgLen += sizeof(uint8_t);  // Length
		msgLen += sizeof(uint8_t);  // Type
		msgLen += req->PeriodicAdvertisingData.AdStructures[i].Length;  // Data
	}	// AdStructures

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->Handle; idx++;
	pMsg[idx] = req->PeriodicAdvertisingData.NbOfAdStructures; idx++;

	for (uint32_t i = 0; i < req->PeriodicAdvertisingData.NbOfAdStructures; i++)
	{
		pMsg[idx] = req->PeriodicAdvertisingData.AdStructures[i].Length; idx++;
		pMsg[idx] = req->PeriodicAdvertisingData.AdStructures[i].Type; idx++;
		FLib_MemCpy(pMsg + idx, req->PeriodicAdvertisingData.AdStructures[i].Data, req->PeriodicAdvertisingData.AdStructures[i].Length); idx += req->PeriodicAdvertisingData.AdStructures[i].Length;
	}

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x59, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvCreateSyncRequest(GAPPeriodicAdvCreateSyncRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Synchronize with a periodic advertiser

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvCreateSyncRequest(GAPPeriodicAdvCreateSyncRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x5A, req, sizeof(GAPPeriodicAdvCreateSyncRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvTerminateSyncRequest(GAPPeriodicAdvTerminateSyncRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Stop reception of the periodic advertising identified by the SID parameter

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvTerminateSyncRequest(GAPPeriodicAdvTerminateSyncRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x5B, req, sizeof(GAPPeriodicAdvTerminateSyncRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPGenerateDHKeyV2Request(GAPGenerateDHKeyV2Request_t *req, void *arg, uint8_t fsciInterface)
\brief	Generate DH Key

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPGenerateDHKeyV2Request(GAPGenerateDHKeyV2Request_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x65, req, sizeof(GAPGenerateDHKeyV2Request_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPModifySleepClockAccuracyRequest(GAPModifySleepClockAccuracyRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Modify Sleep Clock Accuracy

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPModifySleepClockAccuracyRequest(GAPModifySleepClockAccuracyRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x66, req, sizeof(GAPModifySleepClockAccuracyRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t ControllerConfigureAdvCodingSchemeRequest(ControllerConfigureAdvCodingSchemeRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Configure Advertising Coding Scheme

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t ControllerConfigureAdvCodingSchemeRequest(ControllerConfigureAdvCodingSchemeRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x5C, req, sizeof(ControllerConfigureAdvCodingSchemeRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetConnectionlessCteTransmitParametersRequest(GAPSetConnectionlessCteTransmitParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set Connectionless CTE Transmit Parameters for an advertising set

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetConnectionlessCteTransmitParametersRequest(GAPSetConnectionlessCteTransmitParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // Handle
	msgLen += sizeof(uint8_t);  // CteLength
	msgLen += sizeof(uint8_t);  // CteType
	msgLen += sizeof(uint8_t);  // CteCount
	msgLen += sizeof(uint8_t);  // SwitchingPatternLength
	msgLen += req->SwitchingPatternLength;  // AntennaIds

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->Handle; idx++;
	pMsg[idx] = req->CteLength; idx++;
	pMsg[idx] = req->CteType; idx++;
	pMsg[idx] = req->CteCount; idx++;
	pMsg[idx] = req->SwitchingPatternLength; idx++;
	FLib_MemCpy(pMsg + idx, req->AntennaIds, req->SwitchingPatternLength); idx += req->SwitchingPatternLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x5D, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableConnectionlessCteTransmitRequest(GAPEnableConnectionlessCteTransmitRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable Connectionless CTE Transmit for an advertising set

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableConnectionlessCteTransmitRequest(GAPEnableConnectionlessCteTransmitRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x5E, req, sizeof(GAPEnableConnectionlessCteTransmitRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableConnectionlessIqSamplingRequest(GAPEnableConnectionlessIqSamplingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable Connectionless IQ sampling for an advertising train

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableConnectionlessIqSamplingRequest(GAPEnableConnectionlessIqSamplingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint16_t);  // SyncHandle
	msgLen += sizeof(uint8_t);  // IqSamplingEnable
	msgLen += sizeof(uint8_t);  // SlotDurations
	msgLen += sizeof(uint8_t);  // MaxSampledCtes
	msgLen += sizeof(uint8_t);  // SwitchingPatternLength
	msgLen += req->pIqSamplingParams.SwitchingPatternLength;  // AntennaIds

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	FLib_MemCpy(pMsg + idx, &(req->SyncHandle), sizeof(req->SyncHandle)); idx += sizeof(req->SyncHandle);
	pMsg[idx] = req->pIqSamplingParams.IqSamplingEnable; idx++;
	pMsg[idx] = req->pIqSamplingParams.SlotDurations; idx++;
	pMsg[idx] = req->pIqSamplingParams.MaxSampledCtes; idx++;
	pMsg[idx] = req->pIqSamplingParams.SwitchingPatternLength; idx++;
	FLib_MemCpy(pMsg + idx, req->pIqSamplingParams.AntennaIds, req->pIqSamplingParams.SwitchingPatternLength); idx += req->pIqSamplingParams.SwitchingPatternLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x5F, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetConnectionCteReceiveParametersRequest(GAPSetConnectionCteReceiveParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set CTE Receive Parameters for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetConnectionCteReceiveParametersRequest(GAPSetConnectionCteReceiveParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint8_t);  // IqSamplingEnable
	msgLen += sizeof(uint8_t);  // SlotDurations
	msgLen += sizeof(uint8_t);  // SwitchingPatternLength
	msgLen += req->pReceiveParams.SwitchingPatternLength;  // AntennaIds

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->pReceiveParams.IqSamplingEnable; idx++;
	pMsg[idx] = req->pReceiveParams.SlotDurations; idx++;
	pMsg[idx] = req->pReceiveParams.SwitchingPatternLength; idx++;
	FLib_MemCpy(pMsg + idx, req->pReceiveParams.AntennaIds, req->pReceiveParams.SwitchingPatternLength); idx += req->pReceiveParams.SwitchingPatternLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x60, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetConnectionCteTransmitParametersRequest(GAPSetConnectionCteTransmitParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set CTE Transmit Parameters for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetConnectionCteTransmitParametersRequest(GAPSetConnectionCteTransmitParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += 1;  // 0x04|0x02|0x01  // CteTypes
	msgLen += sizeof(uint8_t);  // SwitchingPatternLength
	msgLen += req->pTransmitParams.SwitchingPatternLength;  // AntennaIds

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	pMsg[idx] = req->pTransmitParams.CteTypes; idx++;
	pMsg[idx] = req->pTransmitParams.SwitchingPatternLength; idx++;
	FLib_MemCpy(pMsg + idx, req->pTransmitParams.AntennaIds, req->pTransmitParams.SwitchingPatternLength); idx += req->pTransmitParams.SwitchingPatternLength;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x61, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableConnectionCteRequestRequest(GAPEnableConnectionCteRequestRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable CTE Request procedure for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableConnectionCteRequestRequest(GAPEnableConnectionCteRequestRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x62, req, sizeof(GAPEnableConnectionCteRequestRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableConnectionCteResponseRequest(GAPEnableConnectionCteResponseRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable sending CTE Responses for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableConnectionCteResponseRequest(GAPEnableConnectionCteResponseRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x63, req, sizeof(GAPEnableConnectionCteResponseRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadAntennaInformationRequest(void *arg, uint8_t fsciInterface)
\brief	Read Antenna Information

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t GAPReadAntennaInformationRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0x48, 0x64, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t WritePublicDeviceAddressRequest(WritePublicDeviceAddressRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Store the Public Device Address parameters to Flash

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t WritePublicDeviceAddressRequest(WritePublicDeviceAddressRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x48, req, sizeof(WritePublicDeviceAddressRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvReceiveEnableRequest(GAPPeriodicAdvReceiveEnableRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable reports for the periodic advertising train identified by the Sync_Handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvReceiveEnableRequest(GAPPeriodicAdvReceiveEnableRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x67, req, sizeof(GAPPeriodicAdvReceiveEnableRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvReceiveDisableRequest(GAPPeriodicAdvReceiveDisableRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Disable reports for the periodic advertising train identified by the Sync_Handle

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvReceiveDisableRequest(GAPPeriodicAdvReceiveDisableRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x68, req, sizeof(GAPPeriodicAdvReceiveDisableRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvSyncTransferRequest(GAPPeriodicAdvSyncTransferRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Instruct the Controller to send synchronization information about the periodic advertising train identified by the sync handle to a connected device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvSyncTransferRequest(GAPPeriodicAdvSyncTransferRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x69, req, sizeof(GAPPeriodicAdvSyncTransferRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPPeriodicAdvSetInfoTransferRequest(GAPPeriodicAdvSetInfoTransferRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Instruct the Controller to send synchronization information about the periodic advertising to a connected device

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPPeriodicAdvSetInfoTransferRequest(GAPPeriodicAdvSetInfoTransferRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6A, req, sizeof(GAPPeriodicAdvSetInfoTransferRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetPeriodicAdvSyncTransferParamsRequest(GAPSetPeriodicAdvSyncTransferParamsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Specify how the Controller will process periodic advertising synchronization information received from the device identified by the device id

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetPeriodicAdvSyncTransferParamsRequest(GAPSetPeriodicAdvSyncTransferParamsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6B, req, sizeof(GAPSetPeriodicAdvSyncTransferParamsRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetDefaultPeriodicAdvSyncTransferParamsRequest(GAPSetDefaultPeriodicAdvSyncTransferParamsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Specify the initial value for the mode, skip, timeout, and Constant Tone Extension type (set by the Gap_SetPeriodicAdvSyncTransferParams command) to be used for all subsequent connections over the LE transport.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetDefaultPeriodicAdvSyncTransferParamsRequest(GAPSetDefaultPeriodicAdvSyncTransferParamsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6C, req, sizeof(GAPSetDefaultPeriodicAdvSyncTransferParamsRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnhancedReadTransmitPowerLevelRequest(GAPEnhancedReadTransmitPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read local current and maximum tx power levels for a certain connection and PHY

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnhancedReadTransmitPowerLevelRequest(GAPEnhancedReadTransmitPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6D, req, sizeof(GAPEnhancedReadTransmitPowerLevelRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPReadRemoteTransmitPowerLevelRequest(GAPReadRemoteTransmitPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Read remote tx power for a certain connection and PHY

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPReadRemoteTransmitPowerLevelRequest(GAPReadRemoteTransmitPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6E, req, sizeof(GAPReadRemoteTransmitPowerLevelRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPSetPathLossReportingParametersRequest(GAPSetPathLossReportingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Set path loss threshold reporting parameters for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPSetPathLossReportingParametersRequest(GAPSetPathLossReportingParametersRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x6F, req, sizeof(GAPSetPathLossReportingParametersRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnablePathLossReportingRequest(GAPEnablePathLossReportingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable path loss threshold reporting for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnablePathLossReportingRequest(GAPEnablePathLossReportingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x70, req, sizeof(GAPEnablePathLossReportingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEnableTransmitPowerReportingRequest(GAPEnableTransmitPowerReportingRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Enable or disable tx power reporting for a certain connection

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEnableTransmitPowerReportingRequest(GAPEnableTransmitPowerReportingRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x71, req, sizeof(GAPEnableTransmitPowerReportingRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEattConnectionRequest(GAPEattConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Open up to 5 Enhanced ATT bearers.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEattConnectionRequest(GAPEattConnectionRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x72, req, sizeof(GAPEattConnectionRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEattConnectionAccept(GAPEattConnectionAccept_t *req, void *arg, uint8_t fsciInterface)
\brief	Open up to 5 Enhanced ATT bearers.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEattConnectionAccept(GAPEattConnectionAccept_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x73, req, sizeof(GAPEattConnectionAccept_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEattReconfigureRequest(GAPEattReconfigureRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Change the MTU of up to 5 Enhanced ATT bearers.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEattReconfigureRequest(GAPEattReconfigureRequest_t *req, void *arg, uint8_t fsciInterface)
{
	uint8_t *pMsg = NULL;
	uint16_t msgLen = 0, idx = 0;

	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	/* Compute the size of the request */
	msgLen += sizeof(uint8_t);  // DeviceId
	msgLen += sizeof(uint16_t);  // MTU
	msgLen += sizeof(uint16_t);  // MPS
	msgLen += sizeof(uint8_t);  // NoOfBearers
	msgLen += req->NoOfBearers;  // BearerIds

	/* Allocate memory for the marshalled payload */
	pMsg = MEM_BufferAlloc(msgLen);
	if (!pMsg)
	{
		return MEM_ALLOC_ERROR_c;
	}

	/* Serialize */
	pMsg[idx] = req->DeviceId; idx++;
	FLib_MemCpy(pMsg + idx, &(req->MTU), sizeof(req->MTU)); idx += sizeof(req->MTU);
	FLib_MemCpy(pMsg + idx, &(req->MPS), sizeof(req->MPS)); idx += sizeof(req->MPS);
	pMsg[idx] = req->NoOfBearers; idx++;
	FLib_MemCpy(pMsg + idx, req->BearerIds, req->NoOfBearers); idx += req->NoOfBearers;

	/* Send the request */
	FSCI_transmitPayload(arg, 0x48, 0x74, pMsg, msgLen, fsciInterface);
	MEM_BufferFree(pMsg);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t GAPEattSendCreditsRequest(GAPEattSendCreditsRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	Open up to 5 Enhanced ATT bearers.

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t GAPEattSendCreditsRequest(GAPEattSendCreditsRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0x48, 0x75, req, sizeof(GAPEattSendCreditsRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* GAP_ENABLE */

#if FSCI_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t FSCICPUResetRequest(void *arg, uint8_t fsciInterface)
\brief	Reset CPU

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t FSCICPUResetRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0xA3, 0x08, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t FSCIGetNumberOfFreeBuffersRequest(void *arg, uint8_t fsciInterface)
\brief	Get the number of free buffers

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t FSCIGetNumberOfFreeBuffersRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0xA3, 0x09, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t FSCIAllowDeviceToSleepRequest(FSCIAllowDeviceToSleepRequest_t *req, void *arg, uint8_t fsciInterface)
\brief	FSCI-AllowDeviceToSleep.Request description

\return	memStatus_t			MEM_SUCCESS_c, MEM_ALLOC_ERROR_c, MEM_FREE_ERROR_c
							MEM_UNKNOWN_ERROR_c if req is NULL
***************************************************************************************************/
memStatus_t FSCIAllowDeviceToSleepRequest(FSCIAllowDeviceToSleepRequest_t *req, void *arg, uint8_t fsciInterface)
{
	/* Sanity check */
	if (!req)
	{
		return MEM_UNKNOWN_ERROR_c;
	}

	FSCI_transmitPayload(arg, 0xA3, 0x70, req, sizeof(FSCIAllowDeviceToSleepRequest_t), fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t FSCIGetWakeupReasonRequest(void *arg, uint8_t fsciInterface)
\brief	FSCI-GetWakeupReason.Request description

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t FSCIGetWakeupReasonRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0xA3, 0x72, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		memStatus_t FSCIGetNbuVersionRequest(void *arg, uint8_t fsciInterface)
\brief	FSCI-GetNbuVersion.Request description

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t FSCIGetNbuVersionRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0xA3, 0xB3, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* FSCI_ENABLE */

#if NVM_ENABLE
/*!*************************************************************************************************
\fn		memStatus_t FSCINVGetNvVPSizeRequest(void *arg, uint8_t fsciInterface)
\brief	Get the NVM Virtual Page Size

\return	memStatus_t			MEM_SUCCESS_c
***************************************************************************************************/
memStatus_t FSCINVGetNvVPSizeRequest(void *arg, uint8_t fsciInterface)
{
	FSCI_transmitPayload(arg, 0xA7, 0xE7, NULL, 0, fsciInterface);
	return MEM_SUCCESS_c;
}

#endif  /* NVM_ENABLE */
