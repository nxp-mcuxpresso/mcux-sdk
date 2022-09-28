/* Header file generated from BLE_1.7.1.xml */
/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _BLE_CMD_H
#define _BLE_CMD_H
/*==================================================================================================
Include Files
==================================================================================================*/
#include "os_abstraction.h"

/*==================================================================================================
Public macros
==================================================================================================*/
#define GATT_ENABLE TRUE
#define GATTDB_APP_ENABLE TRUE
#define FSCI_ENABLE TRUE
#define L2CAPCB_ENABLE TRUE
#define GAP_ENABLE TRUE

/*==================================================================================================
Public type definitions
==================================================================================================*/
#if L2CAPCB_ENABLE
typedef PACKED_STRUCT L2CAPCBRegisterLePsmRequest_tag {
	uint16_t LePsm;  // Bluetooth SIG or Vendor LE_PSM
	uint16_t LePsmMtu;  // MTU value
} L2CAPCBRegisterLePsmRequest_t;

typedef PACKED_STRUCT L2CAPCBDeregisterLePsmRequest_tag {
	uint16_t LePsm;  // Bluetooth SIG or Vendor LE_PSM
} L2CAPCBDeregisterLePsmRequest_t;

typedef PACKED_STRUCT L2CAPCBConnectLePsmRequest_tag {
	uint16_t LePsm;  // Bluetooth SIG or Vendor LE_PSM
	uint8_t DeviceId;  // The DeviceId for which the command is intended
	uint16_t InitialCredits;  // Initial credits
} L2CAPCBConnectLePsmRequest_t;

typedef PACKED_STRUCT L2CAPCBDisconnectLeCbChannelRequest_tag {
	uint8_t DeviceId;  // The DeviceId for which the command is intended
	uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
} L2CAPCBDisconnectLeCbChannelRequest_t;

/* Refuse reason */
typedef enum L2CAPCBCancelConnectionRequest_RefuseReason_tag {
	L2CAPCBCancelConnectionRequest_RefuseReason_gSuccessful_c = 0x0000,
	L2CAPCBCancelConnectionRequest_RefuseReason_gLePsmNotSupported_c = 0x0002,
	L2CAPCBCancelConnectionRequest_RefuseReason_gNoResourcesAvailable_c = 0x0004,
	L2CAPCBCancelConnectionRequest_RefuseReason_gInsufficientAuthentication_c = 0x0005,
	L2CAPCBCancelConnectionRequest_RefuseReason_gInsufficientAuthorization_c = 0x0006,
	L2CAPCBCancelConnectionRequest_RefuseReason_gInsufficientEncryptionKeySize_c = 0x0007,
	L2CAPCBCancelConnectionRequest_RefuseReason_gInsufficientEncryption_c = 0x0008,
	L2CAPCBCancelConnectionRequest_RefuseReason_gInvalidSourceCid_c = 0x0009,
	L2CAPCBCancelConnectionRequest_RefuseReason_gSourceCidAlreadyAllocated_c = 0x000A,
	L2CAPCBCancelConnectionRequest_RefuseReason_gTimerError_c = 0x000B,
	L2CAPCBCancelConnectionRequest_RefuseReason_gCommandRejected_c = 0x0100,
	L2CAPCBCancelConnectionRequest_RefuseReason_gResponseTimeout_c = 0xFFFE
} L2CAPCBCancelConnectionRequest_RefuseReason_t;

typedef PACKED_STRUCT L2CAPCBCancelConnectionRequest_tag {
	uint16_t LePsm;  // Bluetooth SIG or Vendor LE_PSM
	uint8_t DeviceId;  // The DeviceId for which the command is intended
	L2CAPCBCancelConnectionRequest_RefuseReason_t RefuseReason;  // Refuse reason
} L2CAPCBCancelConnectionRequest_t;

typedef struct L2CAPCBSendLeCbDataRequest_tag {
	uint8_t DeviceId;  // The DeviceId for which the command is intended
	uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
	uint16_t PacketLength;  // Length of the data packet to be sent
	uint8_t *Packet;  // The data packet to be transmitted
} L2CAPCBSendLeCbDataRequest_t;

typedef PACKED_STRUCT L2CAPCBSendLeCreditRequest_tag {
	uint8_t DeviceId;  // The DeviceID to which credits are given
	uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
	uint16_t Credits;  // Number of credits to be given
} L2CAPCBSendLeCreditRequest_t;

#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
typedef PACKED_STRUCT GATTGetMtuRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
} GATTGetMtuRequest_t;

typedef PACKED_STRUCT GATTClientExchangeMtuRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
} GATTClientExchangeMtuRequest_t;

typedef PACKED_STRUCT GATTClientDiscoverAllPrimaryServicesRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	uint8_t MaxNbOfServices;  // Maximum number of services to be filled
} GATTClientDiscoverAllPrimaryServicesRequest_t;

/* UUID type */
typedef enum UuidType_tag {
	Uuid16Bits = 0x01,
	Uuid128Bits = 0x02,
	Uuid32Bits = 0x03
} UuidType_t;

typedef struct GATTClientDiscoverPrimaryServicesByUuidRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	uint8_t MaxNbOfServices;  // Maximum number of services to be filled
} GATTClientDiscoverPrimaryServicesByUuidRequest_t;

/* Characteristic Properties as defined by GATT */
typedef enum Properties_tag {
	gNone_c = 0x00,
	gBroadcast_c = 0x01,
	gRead_c = 0x02,
	gWriteWithoutRsp_c = 0x04,
	gWrite_c = 0x08,
	gNotify_c = 0x10,
	gIndicate_c = 0x20,
	gAuthSignedWrites_c = 0x40,
	gExtendedProperties_c = 0x80
} Properties_t;

typedef struct GATTClientFindIncludedServicesRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} Service;  // The service within which inclusions should be searched
	uint8_t MaxNbOfIncludedServices;  // Maximum number of included services to be filled
} GATTClientFindIncludedServicesRequest_t;

typedef struct GATTClientDiscoverAllCharacteristicsOfServiceRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} Service;  // The service within which characteristics should be searched
	uint8_t MaxNbOfCharacteristics;  // Maximum number of characteristics to be filled
} GATTClientDiscoverAllCharacteristicsOfServiceRequest_t;

typedef struct GATTClientDiscoverCharacteristicOfServiceByUuidRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t Value[0];  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} Service;  // The service within which characteristics should be searched
	uint8_t MaxNbOfCharacteristics;  // Maximum number of characteristics to be filled
} GATTClientDiscoverCharacteristicOfServiceByUuidRequest_t;

typedef struct GATTClientDiscoverAllCharacteristicDescriptorsRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} Characteristic;  // The characteristic within which descriptors should be searched
	uint16_t EndingHandle;  // The last handle of the Characteristic
	uint8_t MaxNbOfDescriptors;  // Maximum number of descriptors to be filled
} GATTClientDiscoverAllCharacteristicDescriptorsRequest_t;

typedef struct GATTClientReadCharacteristicValueRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} Characteristic;  // The characteristic whose value must be read
	uint16_t MaxReadBytes;  // Maximum number of bytes to be read
} GATTClientReadCharacteristicValueRequest_t;

typedef struct GATTClientReadUsingCharacteristicUuidRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	bool_t HandleRangeIncluded;  // Boolean value which indicates if handle range is included or not
	struct {
		uint16_t StartHandle;  // Start handle
		uint16_t EndHandle;  // End handle
	} HandleRange;  // Handle range for the search
	uint16_t MaxReadBytes;  // Maximum number of bytes to be read
} GATTClientReadUsingCharacteristicUuidRequest_t;

typedef struct GATTClientReadMultipleCharacteristicValuesRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	uint8_t NbOfCharacteristics;  // Number of characteristics in the array
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} *Characteristics;  // Array of the characteristics whose values are to be read
} GATTClientReadMultipleCharacteristicValuesRequest_t;

typedef struct GATTClientWriteCharacteristicValueRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t Value[0];  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} Characteristic;  // The characteristic whose value must be written
	uint16_t ValueLength;  // Number of bytes to be written
	uint8_t *Value;  // Array of bytes to be written
	bool_t WithoutResponse;  // Indicates if a Write Command will be used
	bool_t SignedWrite;  // Indicates if a Signed Write will be performed
	bool_t ReliableLongCharWrites;  // Indicates Reliable Long Writes
	uint8_t Csrk[16];  // The CSRK if signedWrite is TRUE, ignored otherwise
} GATTClientWriteCharacteristicValueRequest_t;

typedef struct GATTClientReadCharacteristicDescriptorRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		uint16_t Handle;  // Attribute handle
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint16_t ValueLength;  // Length of the attribute value array
		uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
		uint8_t Value[0];  // Attribute value array
	} Descriptor;  // The characteristic descriptor whose value must be read
	uint16_t MaxReadBytes;  // Maximum number of bytes to be read
} GATTClientReadCharacteristicDescriptorRequest_t;

typedef struct GATTClientWriteCharacteristicDescriptorRequest_tag {
	uint8_t DeviceId;  // Device ID of the connected peer
	struct {
		uint16_t Handle;  // Attribute handle
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint16_t ValueLength;  // Length of the attribute value array
		uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
		uint8_t Value[0];  // Attribute value array
	} Descriptor;  // The characteristic descriptor whose value must be written
	uint16_t ValueLength;  // Number of bytes to be written
	uint8_t *Value;  // Array of bytes to be written
} GATTClientWriteCharacteristicDescriptorRequest_t;

typedef struct GATTServerRegisterHandlesForWriteNotificationsRequest_tag {
	uint8_t HandleCount;  // Number of handles in array
	uint16_t *AttributeHandles;

} GATTServerRegisterHandlesForWriteNotificationsRequest_t;

typedef PACKED_STRUCT GATTServerSendAttributeWrittenStatusRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t AttributeHandle;  // The attribute handle that was written
	uint8_t Status;  // The status of the write operation
} GATTServerSendAttributeWrittenStatusRequest_t;

typedef PACKED_STRUCT GATTServerSendNotificationRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t Handle;  // Handle of the Value of the Characteristic to be notified
} GATTServerSendNotificationRequest_t;

typedef PACKED_STRUCT GATTServerSendIndicationRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t Handle;  // Handle of the Value of the Characteristic to be indicated
} GATTServerSendIndicationRequest_t;

typedef struct GATTServerSendInstantValueNotificationRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t Handle;  // Handle of the Value of the Characteristic to be notified
	uint16_t ValueLength;  // Length of data to be notified
	uint8_t *Value;  // Data to be notified
} GATTServerSendInstantValueNotificationRequest_t;

typedef struct GATTServerSendInstantValueIndicationRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t Handle;  // Handle of the Value of the Characteristic to be indicated
	uint16_t ValueLength;  // Length of data to be indicated
	uint8_t *Value;  // Data to be indicated
} GATTServerSendInstantValueIndicationRequest_t;

typedef struct GATTServerRegisterHandlesForReadNotificationsRequest_tag {
	uint8_t HandleCount;  // Number of handles in array
	uint16_t *AttributeHandles;

} GATTServerRegisterHandlesForReadNotificationsRequest_t;

typedef PACKED_STRUCT GATTServerSendAttributeReadStatusRequest_tag {
	uint8_t DeviceId;  // The device ID of the connected peer
	uint16_t AttributeHandle;  // The attribute handle that was read
	uint8_t Status;  // The status of the read operation
} GATTServerSendAttributeReadStatusRequest_t;

typedef PACKED_STRUCT GATTServerRegisterUniqueHandlesForNotificationsRequest_tag {
	bool_t bWrite;  // Boolean value which indicates unique handles are notified for write or not
	bool_t bRead;  // Boolean value which indicates unique handles are notified for read or not
} GATTServerRegisterUniqueHandlesForNotificationsRequest_t;

#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
typedef struct GATTDBWriteAttributeRequest_tag {
	uint16_t Handle;  // The handle of the attribute to be written
	uint16_t ValueLength;  // The number of bytes to be written
	uint8_t *Value;  // The value to be written
} GATTDBWriteAttributeRequest_t;

typedef PACKED_STRUCT GATTDBReadAttributeRequest_tag {
	uint16_t Handle;  // The handle of the attribute to be read
	uint16_t MaxBytes;  // The maximum number of bytes to be read
} GATTDBReadAttributeRequest_t;

typedef struct GATTDBFindServiceHandleRequest_tag {
	uint16_t StartHandle;  // The handle to start the search. Should be 0x0001 on the first call
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBFindServiceHandleRequest_t;

typedef struct GATTDBFindCharValueHandleInServiceRequest_tag {
	uint16_t ServiceHandle;  // The handle of the Service declaration
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBFindCharValueHandleInServiceRequest_t;

typedef PACKED_STRUCT GATTDBFindCccdHandleForCharValueHandleRequest_tag {
	uint16_t CharValueHandle;  // The handle of the characteristic value
} GATTDBFindCccdHandleForCharValueHandleRequest_t;

typedef struct GATTDBFindDescriptorHandleForCharValueHandleRequest_tag {
	uint16_t CharValueHandle;  // The handle of the characteristic value
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBFindDescriptorHandleForCharValueHandleRequest_t;

typedef struct GATTDBDynamicAddPrimaryServiceDeclarationRequest_tag {
	uint16_t DesiredHandle;  // The desired handle for the Primary Service declaration
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBDynamicAddPrimaryServiceDeclarationRequest_t;

typedef struct GATTDBDynamicAddSecondaryServiceDeclarationRequest_tag {
	uint16_t DesiredHandle;  // The desired handle for the Secondary Service declaration
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBDynamicAddSecondaryServiceDeclarationRequest_t;

typedef struct GATTDBDynamicAddIncludeDeclarationRequest_tag {
	uint16_t IncludedServiceHandle;  // Handle of the included Service declaration
	uint16_t EndGroupHandle;  // Last handle of the included Service
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
} GATTDBDynamicAddIncludeDeclarationRequest_t;

/* Characteristic properties */
typedef enum GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_tag {
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gNone_c = 0x00,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gBroadcast_c = 0x01,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gRead_c = 0x02,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gWriteWithoutRsp_c = 0x04,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gWrite_c = 0x08,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gNotify_c = 0x10,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gIndicate_c = 0x20,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gAuthSignedWrites_c = 0x40,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_gExtendedProperties_c = 0x80
} GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_t;

/* Access permissions for the value attribute */
typedef enum GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_tag {
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionNone_c = 0x00,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c = 0x01,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadWithEncryption_c = 0x02,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadWithAuthentication_c = 0x04,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadWithAuthorization_c = 0x08,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagWritable_c = 0x10,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithEncryption_c = 0x20,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithAuthentication_c = 0x40,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithAuthorization_c = 0x80
} GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_t;

typedef struct GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_tag {
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_CharacteristicProperties_t CharacteristicProperties;  // Characteristic properties
	uint16_t MaxValueLength;  // If the Characteristic Value length is variable, this is the maximum length; for fixed lengths this must be set to 0
	uint16_t InitialValueLength;  // Value length at initialization; remains fixed if maxValueLength is set to 0, otherwise cannot be greater than maxValueLength
	uint8_t *InitialValue;  // Contains the initial value of the Characteristic
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_t ValueAccessPermissions;  // Access permissions for the value attribute
} GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_t;

/* Access permissions for the descriptor attribute */
typedef enum GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_tag {
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionNone_c = 0x00,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagReadable_c = 0x01,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagReadWithEncryption_c = 0x02,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagReadWithAuthentication_c = 0x04,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagReadWithAuthorization_c = 0x08,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagWritable_c = 0x10,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithEncryption_c = 0x20,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithAuthentication_c = 0x40,
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithAuthorization_c = 0x80
} GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_t;

typedef struct GATTDBDynamicAddCharacteristicDescriptorRequest_tag {
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	uint16_t DescriptorValueLength;  // Fixed length of the descriptor attribute value
	uint8_t *Value;  // Initial value of the descriptor attribute
	GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_t DescriptorAccessPermissions;  // Access permissions for the descriptor attribute
} GATTDBDynamicAddCharacteristicDescriptorRequest_t;

/* Characteristic properties */
typedef enum GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_tag {
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gNone_c = 0x00,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gBroadcast_c = 0x01,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gRead_c = 0x02,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gWriteWithoutRsp_c = 0x04,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gWrite_c = 0x08,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gNotify_c = 0x10,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gIndicate_c = 0x20,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gAuthSignedWrites_c = 0x40,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_gExtendedProperties_c = 0x80
} GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_t;

/* Access permissions for the value attribute */
typedef enum GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_tag {
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionNone_c = 0x00,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c = 0x01,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagReadWithEncryption_c = 0x02,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagReadWithAuthentication_c = 0x04,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagReadWithAuthorization_c = 0x08,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagWritable_c = 0x10,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithEncryption_c = 0x20,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithAuthentication_c = 0x40,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_gPermissionFlagWriteWithAuthorization_c = 0x80
} GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_t;

typedef struct GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_tag {
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_CharacteristicProperties_t CharacteristicProperties;  // Characteristic properties
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_ValueAccessPermissions_t ValueAccessPermissions;  // Access permissions for the value attribute
} GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_t;

typedef PACKED_STRUCT GATTDBDynamicRemoveServiceRequest_tag {
	uint16_t ServiceHandle;  // Attribute handle of the Service declaration
} GATTDBDynamicRemoveServiceRequest_t;

typedef PACKED_STRUCT GATTDBDynamicRemoveCharacteristicRequest_tag {
	uint16_t CharacteristicHandle;  // Attribute handle of the Characteristic declaration
} GATTDBDynamicRemoveCharacteristicRequest_t;

/* Access permissions for the descriptor attribute */
typedef enum GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_tag {
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionNone_c = 0x00,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagReadable_c = 0x01,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagReadWithEncryption_c = 0x02,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagReadWithAuthentication_c = 0x04,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagReadWithAuthorization_c = 0x08,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagWritable_c = 0x10,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithEncryption_c = 0x20,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithAuthentication_c = 0x40,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_gPermissionFlagWriteWithAuthorization_c = 0x80
} GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_t;

typedef struct GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_tag {
	UuidType_t UuidType;  // UUID type
	union {
		uint8_t Uuid16Bits[2];  // UUID 16 bits
		uint8_t Uuid128Bits[16];  // UUID 128 bits
		uint8_t Uuid32Bits[4];  // UUID 32 bits
	} Uuid;  // UUID value
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_DescriptorAccessPermissions_t DescriptorAccessPermissions;  // Access permissions for the descriptor attribute
} GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_t;

#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
/* Security mode and level */
typedef enum GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_tag {
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode1Level1_c = 0x10,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode1Level2_c = 0x11,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode1Level3_c = 0x12,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode1Level4_c = 0x13,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode2Level1_c = 0x21,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_gMode2Level2_c = 0x22
} GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_t;

/* Security mode and level */
typedef enum GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_tag {
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode1Level1_c = 0x10,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode1Level2_c = 0x11,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode1Level3_c = 0x12,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode1Level4_c = 0x13,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode2Level1_c = 0x21,
	GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_gMode2Level2_c = 0x22
} GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_t;

typedef struct GAPRegisterDeviceSecurityRequirementsRequest_tag {
	bool_t SecurityRequirementsIncluded;  // Boolean value which indicates if security requirements are included or not
	struct {
		struct {
			GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_MasterSecurityRequirements_SecurityModeLevel_t SecurityModeLevel;  // Security mode and level
			bool_t Authorization;  // Authorization required
			uint16_t MinimumEncryptionKeySize;  // Minimum encryption key (LTK) size
		} MasterSecurityRequirements;  // Security requirements added to all services
		uint8_t NbOfServices;  // Number of service-specific requirements
		struct {
			uint16_t ServiceHandle;  // Handle of the Service declaration in the GATT Database
			struct {
				GAPRegisterDeviceSecurityRequirementsRequest_SecurityRequirements_GapServiceSecurityRequirements_Requirements_SecurityModeLevel_t SecurityModeLevel;  // Security mode and level
				bool_t Authorization;  // Authorization required
				uint16_t MinimumEncryptionKeySize;  // Minimum encryption key (LTK) size
			} Requirements;  // Requirements for all attributes in this service
		} *GapServiceSecurityRequirements;  // Array of service-specific requirements
	} SecurityRequirements;  // Device security requirements
} GAPRegisterDeviceSecurityRequirementsRequest_t;

/* Advertising type - default connectable undirected */
typedef enum GAPSetAdvertisingParametersRequest_AdvertisingType_tag {
	GAPSetAdvertisingParametersRequest_AdvertisingType_gConnectableUndirected_c = 0x00,
	GAPSetAdvertisingParametersRequest_AdvertisingType_gDirectedHighDutyCycle_c = 0x01,
	GAPSetAdvertisingParametersRequest_AdvertisingType_gScannable_c = 0x02,
	GAPSetAdvertisingParametersRequest_AdvertisingType_gNonConnectable_c = 0x03,
	GAPSetAdvertisingParametersRequest_AdvertisingType_gDirectedLowDutyCycle_c = 0x04
} GAPSetAdvertisingParametersRequest_AdvertisingType_t;

/* Indicates whether the advertising address will be the public address or the random address */
typedef enum GAPSetAdvertisingParametersRequest_OwnAddressType_tag {
	GAPSetAdvertisingParametersRequest_OwnAddressType_gPublic_c = 0x00,
	GAPSetAdvertisingParametersRequest_OwnAddressType_gRandom_c = 0x01
} GAPSetAdvertisingParametersRequest_OwnAddressType_t;

/* Address type of the peer; only used in directed advertising and Enhanced Privacy */
typedef enum GAPSetAdvertisingParametersRequest_PeerAddressType_tag {
	GAPSetAdvertisingParametersRequest_PeerAddressType_gPublic_c = 0x00,
	GAPSetAdvertisingParametersRequest_PeerAddressType_gRandom_c = 0x01
} GAPSetAdvertisingParametersRequest_PeerAddressType_t;

/* Indicates whether the connect and scan requests are filtered using the White List - default does not use White List */
typedef enum GAPSetAdvertisingParametersRequest_FilterPolicy_tag {
	GAPSetAdvertisingParametersRequest_FilterPolicy_gProcessAll_c = 0x00,
	GAPSetAdvertisingParametersRequest_FilterPolicy_gProcessConnAllScanWL_c = 0x01,
	GAPSetAdvertisingParametersRequest_FilterPolicy_gProcessScanAllConnWL_c = 0x02,
	GAPSetAdvertisingParametersRequest_FilterPolicy_gProcessWhiteListOnly_c = 0x03
} GAPSetAdvertisingParametersRequest_FilterPolicy_t;

typedef PACKED_STRUCT GAPSetAdvertisingParametersRequest_tag {
	uint16_t MinInterval;  // Minimum desired advertising interval - default 1.28s
	uint16_t MaxInterval;  // Maximum desired advertising interval - default 1.28s
	GAPSetAdvertisingParametersRequest_AdvertisingType_t AdvertisingType;  // Advertising type - default connectable undirected
	GAPSetAdvertisingParametersRequest_OwnAddressType_t OwnAddressType;  // Indicates whether the advertising address will be the public address or the random address
	GAPSetAdvertisingParametersRequest_PeerAddressType_t PeerAddressType;  // Address type of the peer; only used in directed advertising and Enhanced Privacy
	uint8_t PeerAddress[6];  // Address of the peer
	uint8_t ChannelMap;  // 0x04|0x02|0x01  // Bit mask indicating which of the three advertising channels will be used - default all three
	GAPSetAdvertisingParametersRequest_FilterPolicy_t FilterPolicy;  // Indicates whether the connect and scan requests are filtered using the White List - default does not use White List
} GAPSetAdvertisingParametersRequest_t;

/* Advertising data type */
typedef enum GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_tag {
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdFlags_c = 0x01,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdIncomplete16bitServiceList_c = 0x02,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdComplete16bitServiceList_c = 0x03,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdIncomplete32bitServiceList_c = 0x04,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdComplete32bitServiceList_c = 0x05,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdIncomplete128bitServiceList_c = 0x06,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdComplete128bitServiceList_c = 0x07,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdShortenedLocalName_c = 0x08,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdCompleteLocalName_c = 0x09,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdTxPowerLevel_c = 0x0A,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdClassOfDevice_c = 0x0D,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSimplePairingHashC192_c = 0x0E,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSimplePairingRandomizerR192_c = 0x0F,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSecurityManagerTkValue_c = 0x10,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSecurityManagerOobFlags_c = 0x11,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSlaveConnectionIntervalRange_c = 0x12,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceSolicitationList16bit_c = 0x14,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceSolicitationList128bit_c = 0x15,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceData16bit_c = 0x16,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdPublicTargetAddress_c = 0x17,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdRandomTargetAddress_c = 0x18,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdAppearance_c = 0x19,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdAdvertisingInterval_c = 0x1A,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdLeDeviceAddress_c = 0x1B,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdLeRole_c = 0x1C,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSimplePairingHashC256_c = 0x1D,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdSimplePairingRandomizerR256_c = 0x1E,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceSolicitationList32bit_c = 0x1F,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceData32bit_c = 0x20,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdServiceData128bit_c = 0x21,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAd3dInformationData_c = 0x3D,
	GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdManufacturerSpecificData_c = 0xFF
} GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_t;

/* Advertising data type */
typedef enum GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_tag {
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdFlags_c = 0x01,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdIncomplete16bitServiceList_c = 0x02,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdComplete16bitServiceList_c = 0x03,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdIncomplete32bitServiceList_c = 0x04,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdComplete32bitServiceList_c = 0x05,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdIncomplete128bitServiceList_c = 0x06,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdComplete128bitServiceList_c = 0x07,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdShortenedLocalName_c = 0x08,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdCompleteLocalName_c = 0x09,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdTxPowerLevel_c = 0x0A,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdClassOfDevice_c = 0x0D,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSimplePairingHashC192_c = 0x0E,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSimplePairingRandomizerR192_c = 0x0F,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSecurityManagerTkValue_c = 0x10,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSecurityManagerOobFlags_c = 0x11,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSlaveConnectionIntervalRange_c = 0x12,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceSolicitationList16bit_c = 0x14,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceSolicitationList128bit_c = 0x15,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceData16bit_c = 0x16,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdPublicTargetAddress_c = 0x17,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdRandomTargetAddress_c = 0x18,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdAppearance_c = 0x19,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdAdvertisingInterval_c = 0x1A,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdLeDeviceAddress_c = 0x1B,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdLeRole_c = 0x1C,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSimplePairingHashC256_c = 0x1D,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdSimplePairingRandomizerR256_c = 0x1E,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceSolicitationList32bit_c = 0x1F,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceData32bit_c = 0x20,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdServiceData128bit_c = 0x21,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAd3dInformationData_c = 0x3D,
	GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdManufacturerSpecificData_c = 0xFF
} GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_t;

typedef struct GAPSetAdvertisingDataRequest_tag {
	bool_t AdvertisingDataIncluded;  // Boolean value which indicates if advertising data is included or not
	struct {
		uint8_t NbOfAdStructures;  // Number of advertising data structures
		struct {
			uint8_t Length;  // Advertising data length
			GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_t Type;  // Advertising data type
			uint8_t *Data;  // Advertising data
		} *AdStructures;  // Advertising data structures
	} AdvertisingData;  // Advertising data
	bool_t ScanResponseDataIncluded;  // Boolean value which indicates if scan response data is included or not
	struct {
		uint8_t NbOfAdStructures;  // Number of advertising data structures
		struct {
			uint8_t Length;  // Advertising data length
			GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_t Type;  // Advertising data type
			uint8_t *Data;  // Advertising data
		} *AdStructures;  // Advertising data structures
	} ScanResponseData;  // Scan response data
} GAPSetAdvertisingDataRequest_t;

/* GATT Database access type (the type of access granted - read or write) */
typedef enum GAPAuthorizeRequest_Access_tag {
	GAPAuthorizeRequest_Access_gRead_c = 0x00,
	GAPAuthorizeRequest_Access_gWrite_c = 0x01
} GAPAuthorizeRequest_Access_t;

typedef PACKED_STRUCT GAPAuthorizeRequest_tag {
	uint8_t DeviceId;  // The peer being authorized
	uint16_t Handle;  // The attribute handle
	GAPAuthorizeRequest_Access_t Access;  // GATT Database access type (the type of access granted - read or write)
} GAPAuthorizeRequest_t;

/* The bit mask representing the CCCD value to be saved */
typedef enum GAPSaveCccdRequest_Cccd_tag {
	GAPSaveCccdRequest_Cccd_gEmpty_c = 0x00,
	GAPSaveCccdRequest_Cccd_gNotification_c = 0x01,
	GAPSaveCccdRequest_Cccd_gIndication_c = 0x02
} GAPSaveCccdRequest_Cccd_t;

typedef PACKED_STRUCT GAPSaveCccdRequest_tag {
	uint8_t DeviceId;  // The peer GATT client
	uint16_t Handle;  // The handle of the CCCD as defined in the GATT Database
	GAPSaveCccdRequest_Cccd_t Cccd;  // The bit mask representing the CCCD value to be saved
} GAPSaveCccdRequest_t;

typedef PACKED_STRUCT GAPCheckNotificationStatusRequest_tag {
	uint8_t DeviceId;  // The peer GATT client
	uint16_t Handle;  // The handle of the CCCD
} GAPCheckNotificationStatusRequest_t;

typedef PACKED_STRUCT GAPCheckIndicationStatusRequest_tag {
	uint8_t DeviceId;  // The peer GATT client
	uint16_t Handle;  // The handle of the CCCD
} GAPCheckIndicationStatusRequest_t;

/* The desired security mode-level */
typedef enum GAPPairRequest_PairingParameters_SecurityModeAndLevel_tag {
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPPairRequest_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPPairRequest_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPPairRequest_PairingParameters_LocalIoCapabilities_tag {
	GAPPairRequest_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPPairRequest_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPPairRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPPairRequest_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPPairRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPPairRequest_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPPairRequest_PairingParameters_CentralKeys_tag {
	GAPPairRequest_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPPairRequest_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPPairRequest_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPPairRequest_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPPairRequest_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPPairRequest_PairingParameters_PeripheralKeys_tag {
	GAPPairRequest_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPPairRequest_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPPairRequest_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPPairRequest_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPPairRequest_PairingParameters_PeripheralKeys_t;

typedef PACKED_STRUCT GAPPairRequest_tag {
	uint8_t DeviceId;  // The peer to pair with
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPPairRequest_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPPairRequest_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPPairRequest_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPPairRequest_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters as required by the SMP
} GAPPairRequest_t;

/* The desired security mode-level */
typedef enum GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_tag {
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_tag {
	GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_tag {
	GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_tag {
	GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_t;

typedef PACKED_STRUCT GAPSendSlaveSecurityRequestRequest_tag {
	uint8_t DeviceId;  // The GAP peer to pair with
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPSendSlaveSecurityRequestRequest_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPSendSlaveSecurityRequestRequest_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPSendSlaveSecurityRequestRequest_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPSendSlaveSecurityRequestRequest_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters as required by the SMP (MaxEncryptionKeySize, CentralKeys and PeripheralKeys are not used by this command)
} GAPSendSlaveSecurityRequestRequest_t;

typedef PACKED_STRUCT GAPEncryptLinkRequest_tag {
	uint8_t DeviceId;  // Device ID of the peer
} GAPEncryptLinkRequest_t;

/* The desired security mode-level */
typedef enum GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_tag {
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_tag {
	GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_tag {
	GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_tag {
	GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_t;

typedef PACKED_STRUCT GAPAcceptPairingRequestRequest_tag {
	uint8_t DeviceId;  // The peer requesting authentication
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPAcceptPairingRequestRequest_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPAcceptPairingRequestRequest_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPAcceptPairingRequestRequest_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPAcceptPairingRequestRequest_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters as required by the SMP
} GAPAcceptPairingRequestRequest_t;

/* Pairing reject reason */
typedef enum GAPRejectPairingRequest_Reason_tag {
	GAPRejectPairingRequest_Reason_gOobNotAvailable_c = 0x02,
	GAPRejectPairingRequest_Reason_gIncompatibleIoCapabilities_c = 0x03,
	GAPRejectPairingRequest_Reason_gPairingNotSupported_c = 0x05,
	GAPRejectPairingRequest_Reason_gLowEncryptionKeySize_c = 0x06,
	GAPRejectPairingRequest_Reason_gUnspecifiedReason_c = 0x08,
	GAPRejectPairingRequest_Reason_gRepeatedAttempts_c = 0x09,
	GAPRejectPairingRequest_Reason_gLinkEncryptionFailed_c = 0xF0
} GAPRejectPairingRequest_Reason_t;

typedef PACKED_STRUCT GAPRejectPairingRequest_tag {
	uint8_t DeviceId;  // The GAP peer who requested authentication
	GAPRejectPairingRequest_Reason_t Reason;  // Pairing reject reason
} GAPRejectPairingRequest_t;

typedef PACKED_STRUCT GAPEnterPasskeyRequest_tag {
	uint8_t DeviceId;  // The GAP peer that requested a passkey entry
	uint32_t Passkey;  // The peer's secret passkey
} GAPEnterPasskeyRequest_t;

typedef PACKED_STRUCT GAPProvideOobRequest_tag {
	uint8_t DeviceId;  // The pairing device
	uint8_t Oob[16];  // OOB data
} GAPProvideOobRequest_t;

typedef PACKED_STRUCT GAPRejectPasskeyRequestRequest_tag {
	uint8_t DeviceId;  // The GAP peer that requested a passkey entry
} GAPRejectPasskeyRequestRequest_t;

/* Public or Random address */
typedef enum GAPSendSmpKeysRequest_Keys_AddressInfo_DeviceAddressType_tag {
	GAPSendSmpKeysRequest_Keys_AddressInfo_DeviceAddressType_gPublic_c = 0x00,
	GAPSendSmpKeysRequest_Keys_AddressInfo_DeviceAddressType_gRandom_c = 0x01
} GAPSendSmpKeysRequest_Keys_AddressInfo_DeviceAddressType_t;

typedef struct GAPSendSmpKeysRequest_tag {
	uint8_t DeviceId;  // The GAP peer who initiated the procedure
	struct {
		bool_t LtkIncluded;  // Boolean value which indicates if LTK size and LTK are included or not
		struct {
			uint8_t LtkSize;  // Encryption Key Size
			uint8_t *Ltk;  // Long Term (Encryption) Key
		} LtkInfo;  // LTK information (size and value)
		bool_t IrkIncluded;  // Boolean value which indicates if IRK is included or not
		uint8_t Irk[16];  // Identity Resolving Key
		bool_t CsrkIncluded;  // Boolean value which indicates if CSRK is included or not
		uint8_t Csrk[16];  // Connection Signature Resolving Key
		struct {
			uint8_t RandSize;  // Random value size
			uint8_t *Rand;  // Random value used to identify the LTK
			uint16_t Ediv;  // EDIV value used to identify the LTK
		} RandEdivInfo;  // Rand information (size and value) and Ediv
		bool_t AddressIncluded;  // Boolean value which indicates if Address is included or not
		struct {
			GAPSendSmpKeysRequest_Keys_AddressInfo_DeviceAddressType_t DeviceAddressType;  // Public or Random address
			uint8_t DeviceAddress[6];  // Device Address
		} AddressInfo;  // Address information (type and value)
	} Keys;  // The SMP keys of the local device
} GAPSendSmpKeysRequest_t;

typedef PACKED_STRUCT GAPRejectKeyExchangeRequestRequest_tag {
	uint8_t DeviceId;  // The GAP peer who requested the Key Exchange procedure
} GAPRejectKeyExchangeRequestRequest_t;

typedef struct GAPProvideLongTermKeyRequest_tag {
	uint8_t DeviceId;  // The GAP peer who requested encryption
	uint8_t LtkSize;  // The Long Term Key size
	uint8_t *Ltk;  // The Long Term Key
} GAPProvideLongTermKeyRequest_t;

typedef PACKED_STRUCT GAPDenyLongTermKeyRequest_tag {
	uint8_t DeviceId;  // The GAP peer who requested encryption
} GAPDenyLongTermKeyRequest_t;

typedef PACKED_STRUCT GAPLoadEncryptionInformationRequest_tag {
	uint8_t DeviceId;  // Device ID of the peer
} GAPLoadEncryptionInformationRequest_t;

typedef PACKED_STRUCT GAPSetLocalPasskeyRequest_tag {
	uint32_t Passkey;  // The SMP passkey
} GAPSetLocalPasskeyRequest_t;

/* Scanning type - default passive */
typedef enum GAPStartScanningRequest_ScanningParameters_Type_tag {
	GAPStartScanningRequest_ScanningParameters_Type_gPassive_c = 0x00,
	GAPStartScanningRequest_ScanningParameters_Type_gActive_c = 0x01
} GAPStartScanningRequest_ScanningParameters_Type_t;

/* Indicates whether the address used in scan requests will be the public address or the random address - default public address */
typedef enum GAPStartScanningRequest_ScanningParameters_OwnAddressType_tag {
	GAPStartScanningRequest_ScanningParameters_OwnAddressType_gPublic_c = 0x00,
	GAPStartScanningRequest_ScanningParameters_OwnAddressType_gRandom_c = 0x01
} GAPStartScanningRequest_ScanningParameters_OwnAddressType_t;

/* Indicates whether the advertising packets are filtered using the White List - default does not use White List */
typedef enum GAPStartScanningRequest_ScanningParameters_FilterPolicy_tag {
	GAPStartScanningRequest_ScanningParameters_FilterPolicy_gScanAll_c = 0x00,
	GAPStartScanningRequest_ScanningParameters_FilterPolicy_gScanWithWhiteList_c = 0x01
} GAPStartScanningRequest_ScanningParameters_FilterPolicy_t;

/* Indicates whether duplicate advertising report filtering is enabled. For BLE 5.0 adds the possibility to reset filtering for each scan period */
typedef enum GAPStartScanningRequest_FilterDuplicates_tag {
	GAPStartScanningRequest_FilterDuplicates_Disable = 0x00,
	GAPStartScanningRequest_FilterDuplicates_Enable = 0x01,
	GAPStartScanningRequest_FilterDuplicates_PeriodicEnable = 0x02
} GAPStartScanningRequest_FilterDuplicates_t;

typedef struct GAPStartScanningRequest_tag {
	bool_t ScanningParametersIncluded;  // Boolean value which indicates if scanning parameters are included or not
	struct {
		GAPStartScanningRequest_ScanningParameters_Type_t Type;  // Scanning type - default passive
		uint16_t Interval;  // Scanning interval - default 10ms
		uint16_t Window;  // Scanning window - default 10ms
		GAPStartScanningRequest_ScanningParameters_OwnAddressType_t OwnAddressType;  // Indicates whether the address used in scan requests will be the public address or the random address - default public address
		GAPStartScanningRequest_ScanningParameters_FilterPolicy_t FilterPolicy;  // Indicates whether the advertising packets are filtered using the White List - default does not use White List
	} ScanningParameters;  // The scanning parameters
	GAPStartScanningRequest_FilterDuplicates_t FilterDuplicates;  // Indicates whether duplicate advertising report filtering is enabled. For BLE 5.0 adds the possibility to reset filtering for each scan period
	uint8_t ScanningPHYs;  // gLePhyCoded_c|gLePhy2M_c|gLePhy1M_c  // ScanningPHYs
	uint16_t Duration;  // Scan duration - Time = N * 10ms
	uint16_t Period;  // Periodic scanning - Time = N * 1.28s
} GAPStartScanningRequest_t;

/* Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device */
typedef enum GAPConnectRequest_FilterPolicy_tag {
	GAPConnectRequest_FilterPolicy_gUseDeviceAddress_c = 0x00,
	GAPConnectRequest_FilterPolicy_gUseWhiteList_c = 0x01
} GAPConnectRequest_FilterPolicy_t;

/* Indicates whether the address used in connection requests will be the public address or the random address - default public address */
typedef enum GAPConnectRequest_OwnAddressType_tag {
	GAPConnectRequest_OwnAddressType_gPublic_c = 0x00,
	GAPConnectRequest_OwnAddressType_gRandom_c = 0x01
} GAPConnectRequest_OwnAddressType_t;

/* When connecting to a specific device, this indicates that device's address type - default public address */
typedef enum GAPConnectRequest_PeerAddressType_tag {
	GAPConnectRequest_PeerAddressType_gPublic_c = 0x00,
	GAPConnectRequest_PeerAddressType_gRandom_c = 0x01
} GAPConnectRequest_PeerAddressType_t;

typedef PACKED_STRUCT GAPConnectRequest_tag {
	uint16_t ScanInterval;  // Scanning interval - default 10ms
	uint16_t ScanWindow;  // Scanning window - default 10ms
	GAPConnectRequest_FilterPolicy_t FilterPolicy;  // Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device
	GAPConnectRequest_OwnAddressType_t OwnAddressType;  // Indicates whether the address used in connection requests will be the public address or the random address - default public address
	GAPConnectRequest_PeerAddressType_t PeerAddressType;  // When connecting to a specific device, this indicates that device's address type - default public address
	uint8_t PeerAddress[6];  // When connecting to a specific device, this indicates that device's address
	uint16_t ConnIntervalMin;  // The minimum desired connection interval - default 100ms
	uint16_t ConnIntervalMax;  // The maximum desired connection interval - default 200ms
	uint16_t ConnLatency;  // The desired connection latency (the maximum number of consecutive connection events the Slave is allowed to ignore) - default 0
	uint16_t SupervisionTimeout;  // The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped - default 10s
	uint16_t ConnEventLengthMin;  // The minimum desired connection event length - default 0ms
	uint16_t ConnEventLengthMax;  // The maximum desired connection event length - default maximum possible, ~41 s
	bool_t usePeerIdentityAddress;  // TRUE if the address defined in the peerAddressType and peerAddress is an identity address
	uint8_t Initiating_PHYs;  // gLePhyCoded_c|gLePhy2M_c|gLePhy1M_c  // Phy Flags
} GAPConnectRequest_t;

typedef PACKED_STRUCT GAPDisconnectRequest_tag {
	uint8_t DeviceId;  // The connected peer to disconnect from
} GAPDisconnectRequest_t;

typedef struct GAPSaveCustomPeerInformationRequest_tag {
	uint8_t DeviceId;  // Device ID of the GAP peer
	uint16_t Offset;  // Data offset (offset from the beginning)
	uint16_t InfoSize;  // Data size
	uint8_t *Info;  // Data
} GAPSaveCustomPeerInformationRequest_t;

typedef PACKED_STRUCT GAPLoadCustomPeerInformationRequest_tag {
	uint8_t DeviceId;  // Device ID of the GAP peer
	uint16_t Offset;  // Data offset (offset from the beginning)
	uint16_t InfoSize;  // Data size
} GAPLoadCustomPeerInformationRequest_t;

typedef PACKED_STRUCT GAPCheckIfBondedRequest_tag {
	uint8_t DeviceId;  // Device ID of the GAP peer
} GAPCheckIfBondedRequest_t;

/* The address type (public or random) */
typedef enum GAPAddDeviceToWhiteListRequest_AddressType_tag {
	GAPAddDeviceToWhiteListRequest_AddressType_gPublic_c = 0x00,
	GAPAddDeviceToWhiteListRequest_AddressType_gRandom_c = 0x01
} GAPAddDeviceToWhiteListRequest_AddressType_t;

typedef PACKED_STRUCT GAPAddDeviceToWhiteListRequest_tag {
	GAPAddDeviceToWhiteListRequest_AddressType_t AddressType;  // The address type (public or random)
	uint8_t Address[6];  // The address of the white-listed device
} GAPAddDeviceToWhiteListRequest_t;

/* The address type (public or random) */
typedef enum GAPRemoveDeviceFromWhiteListRequest_AddressType_tag {
	GAPRemoveDeviceFromWhiteListRequest_AddressType_gPublic_c = 0x00,
	GAPRemoveDeviceFromWhiteListRequest_AddressType_gRandom_c = 0x01
} GAPRemoveDeviceFromWhiteListRequest_AddressType_t;

typedef PACKED_STRUCT GAPRemoveDeviceFromWhiteListRequest_tag {
	GAPRemoveDeviceFromWhiteListRequest_AddressType_t AddressType;  // The address type (public or random)
	uint8_t Address[6];  // The address of the white-listed device
} GAPRemoveDeviceFromWhiteListRequest_t;

typedef struct GAPCreateRandomDeviceAddressRequest_tag {
	bool_t IrkIncluded;  // Boolean value which indicates if IRK is included or not
	uint8_t Irk[16];  // The Identity Resolving Key to be used for a private resolvable address
	bool_t RandomPartIncluded;  // Boolean value which indicates if random part is included or not
	uint8_t RandomPart[3];  // Array containing the random part of a Private Resolvable Address
} GAPCreateRandomDeviceAddressRequest_t;

typedef struct GAPSaveDeviceNameRequest_tag {
	uint8_t DeviceId;  // Device ID for the active peer which name is saved
	uint8_t NameSize;  // Number of characters to be saved
	uint8_t *Name;  // Array of characters holding the name
} GAPSaveDeviceNameRequest_t;

typedef PACKED_STRUCT GAPGetBondedDeviceNameRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
	uint8_t MaxNameSize;  // Maximum number of characters to be copied, including the terminating NULL character
} GAPGetBondedDeviceNameRequest_t;

typedef PACKED_STRUCT GAPRemoveBondRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
} GAPRemoveBondRequest_t;

/* Transmission read type */
typedef enum GAPReadRadioPowerLevelRequest_TxReadType_tag {
	GAPReadRadioPowerLevelRequest_TxReadType_gTxPowerCurrentLevelInConnection_c = 0x00,
	GAPReadRadioPowerLevelRequest_TxReadType_gTxPowerMaximumLevelInConnection_c = 0x01,
	GAPReadRadioPowerLevelRequest_TxReadType_gTxPowerLevelForAdvertising_c = 0x02,
	GAPReadRadioPowerLevelRequest_TxReadType_gRssi_c = 0x03
} GAPReadRadioPowerLevelRequest_TxReadType_t;

typedef PACKED_STRUCT GAPReadRadioPowerLevelRequest_tag {
	GAPReadRadioPowerLevelRequest_TxReadType_t TxReadType;  // Transmission read type
	uint8_t DeviceId;  // The DeviceId for which the command is intended
} GAPReadRadioPowerLevelRequest_t;

typedef PACKED_STRUCT GAPVerifyPrivateResolvableAddressRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area whose IRK must be checked
	uint8_t Address[6];  // The Private Resolvable Address to be verified
} GAPVerifyPrivateResolvableAddressRequest_t;

typedef PACKED_STRUCT GAPSetRandomAddressRequest_tag {
	uint8_t Address[6];  // The Private Resolvable, Private Non-Resolvable, or Static Random Address
} GAPSetRandomAddressRequest_t;

/* The scan mode to be activated. */
typedef enum GAPSetScanModeRequest_ScanMode_tag {
	GAPSetScanModeRequest_ScanMode_gDefaultScan_c = 0x00,
	GAPSetScanModeRequest_ScanMode_gLimitedDiscovery_c = 0x01,
	GAPSetScanModeRequest_ScanMode_gGeneralDiscovery_c = 0x02,
	GAPSetScanModeRequest_ScanMode_gAutoConnect_c = 0x03
} GAPSetScanModeRequest_ScanMode_t;

/* Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device */
typedef enum GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_FilterPolicy_tag {
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_FilterPolicy_gUseDeviceAddress_c = 0x00,
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_FilterPolicy_gUseWhiteList_c = 0x01
} GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_FilterPolicy_t;

/* Indicates whether the address used in connection requests will be the public address or the random address - default public address */
typedef enum GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_OwnAddressType_tag {
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_OwnAddressType_gPublic_c = 0x00,
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_OwnAddressType_gRandom_c = 0x01
} GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_OwnAddressType_t;

/* When connecting to a specific device, this indicates that device's address type - default public address */
typedef enum GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_PeerAddressType_tag {
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_PeerAddressType_gPublic_c = 0x00,
	GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_PeerAddressType_gRandom_c = 0x01
} GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_PeerAddressType_t;

typedef struct GAPSetScanModeRequest_tag {
	GAPSetScanModeRequest_ScanMode_t ScanMode;  // The scan mode to be activated.
	struct {
		uint8_t NbOfAddresses;  // Number of device addresses to automatically connect to
		bool_t WriteInWhiteList;  // If set to TRUE, the device addresses will be written in the White List before scanning is enabled
		struct {
			uint16_t ScanInterval;  // Scanning interval - default 10ms
			uint16_t ScanWindow;  // Scanning window - default 10ms
			GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_FilterPolicy_t FilterPolicy;  // Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device
			GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_OwnAddressType_t OwnAddressType;  // Indicates whether the address used in connection requests will be the public address or the random address - default public address
			GAPSetScanModeRequest_AutoConnectParams_AutoConnectData_PeerAddressType_t PeerAddressType;  // When connecting to a specific device, this indicates that device's address type - default public address
			uint8_t PeerAddress[6];  // When connecting to a specific device, this indicates that device's address
			uint16_t ConnIntervalMin;  // The minimum desired connection interval - default 100ms
			uint16_t ConnIntervalMax;  // The maximum desired connection interval - default 200ms
			uint16_t ConnLatency;  // The desired connection latency (the maximum number of consecutive connection events the Slave is allowed to ignore) - default 0
			uint16_t SupervisionTimeout;  // The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped - default 10s
			uint16_t ConnEventLengthMin;  // The minimum desired connection event length - default 0ms
			uint16_t ConnEventLengthMax;  // The maximum desired connection event length - default maximum possible, ~41 s
			bool_t usePeerIdentityAddress;  // TRUE if the address defined in the peerAddressType and peerAddress is an identity address
			uint8_t Initiating_PHYs;  // gLePhyCoded_c|gLePhy2M_c|gLePhy1M_c  // Phy Flags
		} *AutoConnectData;  // The connection request parameters
	} AutoConnectParams;  // Parameters for the Auto Connect Scan Mode
} GAPSetScanModeRequest_t;

/* The desired security mode-level */
typedef enum GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_tag {
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_tag {
	GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_tag {
	GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_tag {
	GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_t;

typedef struct GAPSetDefaultPairingParametersRequest_tag {
	bool_t PairingParametersIncluded;  // Boolean value which indicates if pairing parameters are included or not
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPSetDefaultPairingParametersRequest_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPSetDefaultPairingParametersRequest_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPSetDefaultPairingParametersRequest_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPSetDefaultPairingParametersRequest_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters as required by the SMP
} GAPSetDefaultPairingParametersRequest_t;

typedef PACKED_STRUCT GAPUpdateConnectionParametersRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	uint16_t IntervalMin;  // The minimum value for the connection event interval
	uint16_t IntervalMax;  // The maximum value for the connection event interval
	uint16_t SlaveLatency;  // The slave latency parameter
	uint16_t TimeoutMultiplier;  // The connection timeout parameter
	uint16_t MinCeLength;  // The minimum connection event length
	uint16_t MaxCeLength;  // The maximum connection event length
} GAPUpdateConnectionParametersRequest_t;

typedef PACKED_STRUCT GAPEnableUpdateConnectionParametersRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	bool_t Enable;  // Allow/dissalow the parameters update
} GAPEnableUpdateConnectionParametersRequest_t;

typedef PACKED_STRUCT GapUpdateLeDataLengthRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	uint16_t TxOctets;  // Maximum transmission number of payload octets
	uint16_t TxTime;  // Maximum transmission time
} GapUpdateLeDataLengthRequest_t;

typedef struct GAPEnableHostPrivacyRequest_tag {
	bool_t Enable;  // Enables or disables Host Privacy
	uint8_t Irk[16];  // Local IRK to be used for Resolvable Private Address generation
} GAPEnableHostPrivacyRequest_t;

/* Identity Address Type */
typedef enum GAPEnableControllerPrivacyRequest_PeerIdentities_IdentityAddressType_tag {
	GAPEnableControllerPrivacyRequest_PeerIdentities_IdentityAddressType_gPublic_c = 0x00,
	GAPEnableControllerPrivacyRequest_PeerIdentities_IdentityAddressType_gRandom_c = 0x01
} GAPEnableControllerPrivacyRequest_PeerIdentities_IdentityAddressType_t;

/* Privacy Mode */
typedef enum GAPEnableControllerPrivacyRequest_PeerIdentities_PrivacyMode_tag {
	GAPEnableControllerPrivacyRequest_PeerIdentities_PrivacyMode_gNetworkPrivacy_c = 0x00,
	GAPEnableControllerPrivacyRequest_PeerIdentities_PrivacyMode_gDevicePrivacy_c = 0x01
} GAPEnableControllerPrivacyRequest_PeerIdentities_PrivacyMode_t;

typedef struct GAPEnableControllerPrivacyRequest_tag {
	bool_t Enable;  // Enables or disables Controller Privacy
	uint8_t OwnIrk[16];  // Local IRK
	uint8_t PeerIdCount;  // Size of PeerIdentities array
	struct {
		GAPEnableControllerPrivacyRequest_PeerIdentities_IdentityAddressType_t IdentityAddressType;  // Identity Address Type
		uint8_t IdentityAddress[6];  // Identity Address
		uint8_t Irk[16];  // Identity Resolving Key
		GAPEnableControllerPrivacyRequest_PeerIdentities_PrivacyMode_t PrivacyMode;  // Privacy Mode
	} *PeerIdentities;  // Array of peer identity addresses and IRKs
} GAPEnableControllerPrivacyRequest_t;

typedef PACKED_STRUCT GAPLeScValidateNumericValueRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	bool_t Valid;  // TRUE if user has indicated that numeric values are matched, FALSE otherwise
} GAPLeScValidateNumericValueRequest_t;

typedef PACKED_STRUCT GAPLeScSetPeerOobDataRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	uint8_t RandomValue[16];  // LE SC OOB r (Random value)
	uint8_t ConfirmValue[16];  // LE SC OOB Cr (Random Confirm value)
} GAPLeScSetPeerOobDataRequest_t;

/* keypressNotifType */
typedef enum GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_tag {
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyEntryStarted_c = 0x00,
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyDigitStarted_c = 0x01,
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyDigitErased_c = 0x02,
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyCleared_c = 0x03,
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyEntryCompleted_c = 0x04
} GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_t;

typedef PACKED_STRUCT GAPLeScSendKeypressNotificationPrivacyRequest_tag {
	uint8_t DeviceId;  // The DeviceID for which the command is intended
	GAPLeScSendKeypressNotificationPrivacyRequest_GapLeScKeypressNotificationParams_keypressNotifType_t GapLeScKeypressNotificationParams_keypressNotifType;

} GAPLeScSendKeypressNotificationPrivacyRequest_t;

typedef PACKED_STRUCT GAPGetBondedDevicesIdentityInformationRequest_tag {
	uint8_t maxDevices;  // Maximum number of addresses to be obtained
} GAPGetBondedDevicesIdentityInformationRequest_t;

/* Advertising or Connection channel type for the Tx power level */
typedef enum GAPSetTxPowerLevelRequest_channelType_tag {
	GAPSetTxPowerLevelRequest_channelType_Advertising = 0x00,
	GAPSetTxPowerLevelRequest_channelType_Connection = 0x01
} GAPSetTxPowerLevelRequest_channelType_t;

typedef PACKED_STRUCT GAPSetTxPowerLevelRequest_tag {
	uint8_t powerLevel;  // power level value as described by the controller interface
	GAPSetTxPowerLevelRequest_channelType_t channelType;  // Advertising or Connection channel type for the Tx power level
} GAPSetTxPowerLevelRequest_t;

typedef PACKED_STRUCT GAPLeReadPhyRequest_tag {
	uint8_t DeviceId;  // Device ID of the peer.
} GAPLeReadPhyRequest_t;

/* Host preferences on Coded Phy */
typedef enum GAPLeSetPhyRequest_phyOptions_tag {
	GAPLeSetPhyRequest_phyOptions_gLeCodingNoPreference_c = 0x00,
	GAPLeSetPhyRequest_phyOptions_gLeCodingS2_c = 0x01,
	GAPLeSetPhyRequest_phyOptions_gLeCodingS8_c = 0x02
} GAPLeSetPhyRequest_phyOptions_t;

typedef PACKED_STRUCT GAPLeSetPhyRequest_tag {
	bool_t defaultMode;  // Use the provided values for all subsequent connections or provide a device ID for a single connection
	uint8_t DeviceId;  // Device ID of the peer.
	uint8_t allPhys;  // 0x02|0x01  // Bit mask indicating Host preferences on Tx and Rx Phy
	uint8_t txPhys;  // 0x04|0x02|0x01  // Bit mask indicating Host preferences on Tx Phy
	uint8_t rxPhys;  // 0x04|0x02|0x01  // Bit mask indicating Host preferences on Rx Phy
	GAPLeSetPhyRequest_phyOptions_t phyOptions;  // Host preferences on Coded Phy
} GAPLeSetPhyRequest_t;

typedef PACKED_STRUCT GAPLoadKeysRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
} GAPLoadKeysRequest_t;

/* Public or Random address */
typedef enum GAPSaveKeysRequest_Keys_AddressInfo_DeviceAddressType_tag {
	GAPSaveKeysRequest_Keys_AddressInfo_DeviceAddressType_gPublic_c = 0x00,
	GAPSaveKeysRequest_Keys_AddressInfo_DeviceAddressType_gRandom_c = 0x01
} GAPSaveKeysRequest_Keys_AddressInfo_DeviceAddressType_t;

typedef struct GAPSaveKeysRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
	struct {
		bool_t LtkIncluded;  // Boolean value which indicates if LTK size and LTK are included or not
		struct {
			uint8_t LtkSize;  // Encryption Key Size
			uint8_t *Ltk;  // Long Term (Encryption) Key
		} LtkInfo;  // LTK information (size and value)
		bool_t IrkIncluded;  // Boolean value which indicates if IRK is included or not
		uint8_t Irk[16];  // Identity Resolving Key
		bool_t CsrkIncluded;  // Boolean value which indicates if CSRK is included or not
		uint8_t Csrk[16];  // Connection Signature Resolving Key
		struct {
			uint8_t RandSize;  // Random value size
			uint8_t *Rand;  // Random value used to identify the LTK
			uint16_t Ediv;  // EDIV value used to identify the LTK
		} RandEdivInfo;  // Rand information (size and value) and Ediv
		bool_t AddressIncluded;  // Boolean value which indicates if Address is included or not
		struct {
			GAPSaveKeysRequest_Keys_AddressInfo_DeviceAddressType_t DeviceAddressType;  // Public or Random address
			uint8_t DeviceAddress[6];  // Device Address
		} AddressInfo;  // Address information (type and value)
	} Keys;  // The SMP keys distributed by the peer
	bool_t LeSc;  // LE SC connections pairing
	bool_t Authenticated;  // Peer was authenticated during pairing
} GAPSaveKeysRequest_t;

typedef PACKED_STRUCT GAPSetChannelMapRequest_tag {
	uint8_t ChannelMap[5];  // Channel Map
} GAPSetChannelMapRequest_t;

typedef PACKED_STRUCT GAPReadChannelMapRequest_tag {
	uint8_t DeviceId;  // Device ID of the peer.
} GAPReadChannelMapRequest_t;

/* Privacy Mode */
typedef enum GAPSetPrivacyModeRequest_PrivacyMode_tag {
	GAPSetPrivacyModeRequest_PrivacyMode_gNetworkPrivacy_c = 0x00,
	GAPSetPrivacyModeRequest_PrivacyMode_gDevicePrivacy_c = 0x01
} GAPSetPrivacyModeRequest_PrivacyMode_t;

typedef PACKED_STRUCT GAPSetPrivacyModeRequest_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
	GAPSetPrivacyModeRequest_PrivacyMode_t PrivacyMode;  // Privacy Mode
} GAPSetPrivacyModeRequest_t;

#endif  /* GAP_ENABLE */

#if FSCI_ENABLE
/* Signal Host When Wake Up */
typedef enum FSCIAllowDeviceToSleepRequest_SignalHostWhenWakeUp_tag {
	FSCIAllowDeviceToSleepRequest_SignalHostWhenWakeUp_FALSE = 0x00,
	FSCIAllowDeviceToSleepRequest_SignalHostWhenWakeUp_TRUE = 0x01
} FSCIAllowDeviceToSleepRequest_SignalHostWhenWakeUp_t;

typedef PACKED_STRUCT FSCIAllowDeviceToSleepRequest_tag {
	FSCIAllowDeviceToSleepRequest_SignalHostWhenWakeUp_t SignalHostWhenWakeUp;  // Signal Host When Wake Up
	uint32_t DeepSleepDuration;  // Deep sleep duration in units of 16 us. Default value is 5 s
	uint8_t DeepSleepMode;  // Deep sleep mode selection.
} FSCIAllowDeviceToSleepRequest_t;

typedef PACKED_STRUCT FSCIAckIndication_tag {
	uint8_t Checksum;  // Checksum of the FSCI packet being acknowledged
} FSCIAckIndication_t;

/* Occurred error */
typedef enum FSCIErrorIndication_Status_tag {
	FSCIErrorIndication_Status_gFsciSuccess_c = 0x00,
	FSCIErrorIndication_Status_gFsciSAPDisabled_c = 0xF0,
	FSCIErrorIndication_Status_gFsciAppMsgTooBig_c = 0xF3,
	FSCIErrorIndication_Status_gFsciOutOfMessages_c = 0xF4,
	FSCIErrorIndication_Status_gFsciUnknownOpcodeGroup_c = 0xF7,
	FSCIErrorIndication_Status_gFsciOpcodeGroupIsDisabled_c = 0xF8,
	FSCIErrorIndication_Status_gFsciUnknownOpcode_c = 0xFD,
	FSCIErrorIndication_Status_gFsciTooBig_c = 0xFE,
	FSCIErrorIndication_Status_gFsciError_c = 0xFF
} FSCIErrorIndication_Status_t;

typedef PACKED_STRUCT FSCIErrorIndication_tag {
	FSCIErrorIndication_Status_t Status;  // Occurred error
} FSCIErrorIndication_t;

/* Status */
typedef enum FSCIAllowDeviceToSleepConfirm_Status_tag {
	FSCIAllowDeviceToSleepConfirm_Status_gSuccess = 0x00,
	FSCIAllowDeviceToSleepConfirm_Status_gError = 0xFF
} FSCIAllowDeviceToSleepConfirm_Status_t;

typedef PACKED_STRUCT FSCIAllowDeviceToSleepConfirm_tag {
	FSCIAllowDeviceToSleepConfirm_Status_t Status;  // Status
} FSCIAllowDeviceToSleepConfirm_t;

typedef PACKED_STRUCT FSCIWakeUpIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} FSCIWakeUpIndication_t;

typedef PACKED_STRUCT FSCIGetWakeupReasonResponse_tag {
	uint8_t WakeUpReason;  // 0x80|0x40|0x20|0x10|0x08|0x04|0x02|0x01  // Wake Up Reason
} FSCIGetWakeupReasonResponse_t;

#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
/* The status of the L2CAP request */
typedef enum L2CAPCBConfirm_Status_tag {
	L2CAPCBConfirm_Status_gBleSuccess_c = 0x0000,
	L2CAPCBConfirm_Status_gBleInvalidParameter_c = 0x0001,
	L2CAPCBConfirm_Status_gBleOverflow_c = 0x0002,
	L2CAPCBConfirm_Status_gBleUnavailable_c = 0x0003,
	L2CAPCBConfirm_Status_gBleFeatureNotSupported_c = 0x0004,
	L2CAPCBConfirm_Status_gBleOutOfMemory_c = 0x0005,
	L2CAPCBConfirm_Status_gBleAlreadyInitialized_c = 0x0006,
	L2CAPCBConfirm_Status_gBleOsError_c = 0x0007,
	L2CAPCBConfirm_Status_gBleUnexpectedError_c = 0x0008,
	L2CAPCBConfirm_Status_gBleInvalidState_c = 0x0009,
	L2CAPCBConfirm_Status_gBleTimerError_c = 0x000A,
	L2CAPCBConfirm_Status_gHciUnknownHciCommand_c = 0x0101,
	L2CAPCBConfirm_Status_gHciUnknownConnectionIdentifier_c = 0x0102,
	L2CAPCBConfirm_Status_gHciHardwareFailure_c = 0x0103,
	L2CAPCBConfirm_Status_gHciPageTimeout_c = 0x0104,
	L2CAPCBConfirm_Status_gHciAuthenticationFailure_c = 0x0105,
	L2CAPCBConfirm_Status_gHciPinOrKeyMissing_c = 0x0106,
	L2CAPCBConfirm_Status_gHciMemoryCapacityExceeded_c = 0x0107,
	L2CAPCBConfirm_Status_gHciConnectionTimeout_c = 0x0108,
	L2CAPCBConfirm_Status_gHciConnectionLimitExceeded_c = 0x0109,
	L2CAPCBConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	L2CAPCBConfirm_Status_gHciAclConnectionAlreadyExists_c = 0x010B,
	L2CAPCBConfirm_Status_gHciCommandDisallowed_c = 0x010C,
	L2CAPCBConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	L2CAPCBConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	L2CAPCBConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	L2CAPCBConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	L2CAPCBConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	L2CAPCBConfirm_Status_gHciInvalidHciCommandParameters_c = 0x0112,
	L2CAPCBConfirm_Status_gHciRemoteUserTerminatedConnection_c = 0x0113,
	L2CAPCBConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	L2CAPCBConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	L2CAPCBConfirm_Status_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	L2CAPCBConfirm_Status_gHciRepeatedAttempts_c = 0x0117,
	L2CAPCBConfirm_Status_gHciPairingNotAllowed_c = 0x0118,
	L2CAPCBConfirm_Status_gHciUnknownLpmPdu_c = 0x0119,
	L2CAPCBConfirm_Status_gHciUnsupportedRemoteFeature_c = 0x011A,
	L2CAPCBConfirm_Status_gHciScoOffsetRejected_c = 0x011B,
	L2CAPCBConfirm_Status_gHciScoIntervalRejected_c = 0x011C,
	L2CAPCBConfirm_Status_gHciScoAirModeRejected_c = 0x011D,
	L2CAPCBConfirm_Status_gHciInvalidLpmParameters_c = 0x011E,
	L2CAPCBConfirm_Status_gHciUnspecifiedError_c = 0x011F,
	L2CAPCBConfirm_Status_gHciUnsupportedLpmParameterValue_c = 0x0120,
	L2CAPCBConfirm_Status_gHciRoleChangeNotAllowed_c = 0x0121,
	L2CAPCBConfirm_Status_gHciLLResponseTimeout_c = 0x0122,
	L2CAPCBConfirm_Status_gHciLmpErrorTransactionCollision_c = 0x0123,
	L2CAPCBConfirm_Status_gHciLmpPduNotAllowed_c = 0x0124,
	L2CAPCBConfirm_Status_gHciEncryptionModeNotAcceptable_c = 0x0125,
	L2CAPCBConfirm_Status_gHciLinkKeyCannotBeChanged_c = 0x0126,
	L2CAPCBConfirm_Status_gHciRequestedQosNotSupported_c = 0x0127,
	L2CAPCBConfirm_Status_gHciInstantPassed_c = 0x0128,
	L2CAPCBConfirm_Status_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	L2CAPCBConfirm_Status_gHciDifferentTransactionCollision_c = 0x012A,
	L2CAPCBConfirm_Status_gHciReserved_0x2B_c = 0x012B,
	L2CAPCBConfirm_Status_gHciQosNotAcceptableParameter_c = 0x012C,
	L2CAPCBConfirm_Status_gHciQosRejected_c = 0x012D,
	L2CAPCBConfirm_Status_gHciChannelClassificationNotSupported_c = 0x012E,
	L2CAPCBConfirm_Status_gHciInsufficientSecurity_c = 0x012F,
	L2CAPCBConfirm_Status_gHciParameterOutOfMandatoryRange_c = 0x0130,
	L2CAPCBConfirm_Status_gHciReserved_0x31_c = 0x0131,
	L2CAPCBConfirm_Status_gHciRoleSwitchPending_c = 0x0132,
	L2CAPCBConfirm_Status_gHciReserved_0x33_c = 0x0133,
	L2CAPCBConfirm_Status_gHciReservedSlotViolation_c = 0x0134,
	L2CAPCBConfirm_Status_gHciRoleSwitchFailed_c = 0x0135,
	L2CAPCBConfirm_Status_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	L2CAPCBConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	L2CAPCBConfirm_Status_gHciHostBusyPairing_c = 0x0138,
	L2CAPCBConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	L2CAPCBConfirm_Status_gHciControllerBusy_c = 0x013A,
	L2CAPCBConfirm_Status_gHciUnacceptableConnectionParameters_c = 0x013B,
	L2CAPCBConfirm_Status_gHciDirectedAdvertisingTimeout_c = 0x013C,
	L2CAPCBConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	L2CAPCBConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	L2CAPCBConfirm_Status_gHciMacConnectionFailed_c = 0x013F,
	L2CAPCBConfirm_Status_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	L2CAPCBConfirm_Status_gHciType0SubmapNotDefined_c = 0x0141,
	L2CAPCBConfirm_Status_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	L2CAPCBConfirm_Status_gHciLimitReached_c = 0x0143,
	L2CAPCBConfirm_Status_gHciOperationCancelledByHost_c = 0x0144,
	L2CAPCBConfirm_Status_gHciAlreadyInit_c = 0x01A0,
	L2CAPCBConfirm_Status_gHciInvalidParameter_c = 0x01A1,
	L2CAPCBConfirm_Status_gHciCallbackNotInstalled_c = 0x01A2,
	L2CAPCBConfirm_Status_gHciCallbackAlreadyInstalled_c = 0x01A3,
	L2CAPCBConfirm_Status_gHciCommandNotSupported_c = 0x01A4,
	L2CAPCBConfirm_Status_gHciEventNotSupported_c = 0x01A5,
	L2CAPCBConfirm_Status_gHciTransportError_c = 0x01A6,
	L2CAPCBConfirm_Status_gL2caAlreadyInit_c = 0x03F0,
	L2CAPCBConfirm_Status_gL2caInsufficientResources_c = 0x03F1,
	L2CAPCBConfirm_Status_gL2caCallbackNotInstalled_c = 0x03F2,
	L2CAPCBConfirm_Status_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	L2CAPCBConfirm_Status_gL2caLePsmInvalid_c = 0x03F4,
	L2CAPCBConfirm_Status_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	L2CAPCBConfirm_Status_gL2caLePsmNotRegistered_c = 0x03F6,
	L2CAPCBConfirm_Status_gL2caLePsmInsufficientResources_c = 0x03F7,
	L2CAPCBConfirm_Status_gL2caChannelInvalid_c = 0x03F8,
	L2CAPCBConfirm_Status_gL2caChannelClosed_c = 0x03F9,
	L2CAPCBConfirm_Status_gL2caChannelAlreadyConnected_c = 0x03FA,
	L2CAPCBConfirm_Status_gL2caConnectionParametersRejected_c = 0x03FB,
	L2CAPCBConfirm_Status_gL2caChannelBusy_c = 0x03FC,
	L2CAPCBConfirm_Status_gL2caInvalidParameter_c = 0x03FE,
	L2CAPCBConfirm_Status_gL2caError_c = 0x03FF,
	L2CAPCBConfirm_Status_gSmNullCBFunction_c = 0x0401,
	L2CAPCBConfirm_Status_gSmCommandNotSupported_c = 0x0402,
	L2CAPCBConfirm_Status_gSmUnexpectedCommand_c = 0x0403,
	L2CAPCBConfirm_Status_gSmInvalidCommandCode_c = 0x0404,
	L2CAPCBConfirm_Status_gSmInvalidCommandLength_c = 0x0405,
	L2CAPCBConfirm_Status_gSmInvalidCommandParameter_c = 0x0406,
	L2CAPCBConfirm_Status_gSmInvalidDeviceId_c = 0x0407,
	L2CAPCBConfirm_Status_gSmInvalidInternalOperation_c = 0x0408,
	L2CAPCBConfirm_Status_gSmInvalidConnectionHandle_c = 0x0409,
	L2CAPCBConfirm_Status_gSmInproperKeyDistributionField_c = 0x040A,
	L2CAPCBConfirm_Status_gSmUnexpectedKeyType_c = 0x040B,
	L2CAPCBConfirm_Status_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	L2CAPCBConfirm_Status_gSmUnexpectedKeyset_c = 0x040D,
	L2CAPCBConfirm_Status_gSmSmpTimeoutOccurred_c = 0x040E,
	L2CAPCBConfirm_Status_gSmUnknownSmpPacketType_c = 0x040F,
	L2CAPCBConfirm_Status_gSmInvalidSmpPacketLength_c = 0x0410,
	L2CAPCBConfirm_Status_gSmInvalidSmpPacketParameter_c = 0x0411,
	L2CAPCBConfirm_Status_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	L2CAPCBConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	L2CAPCBConfirm_Status_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	L2CAPCBConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	L2CAPCBConfirm_Status_gSmInvalidHciEventParameter_c = 0x0416,
	L2CAPCBConfirm_Status_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	L2CAPCBConfirm_Status_gSmLlConnectionEncryptionFailure_c = 0x0418,
	L2CAPCBConfirm_Status_gSmInsufficientResources_c = 0x0419,
	L2CAPCBConfirm_Status_gSmOobDataAddressMismatch_c = 0x041A,
	L2CAPCBConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	L2CAPCBConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	L2CAPCBConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	L2CAPCBConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	L2CAPCBConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	L2CAPCBConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	L2CAPCBConfirm_Status_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	L2CAPCBConfirm_Status_gSmPairingErrorCommandNotSupported_c = 0x0433,
	L2CAPCBConfirm_Status_gSmPairingErrorInvalidParameters_c = 0x0434,
	L2CAPCBConfirm_Status_gSmPairingErrorUnknownReason_c = 0x0435,
	L2CAPCBConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	L2CAPCBConfirm_Status_gSmTbInvalidDataSignature_c = 0x0461,
	L2CAPCBConfirm_Status_gAttInvalidHandle_c = 0x0501,
	L2CAPCBConfirm_Status_gAttReadNotPermitted_c = 0x0502,
	L2CAPCBConfirm_Status_gAttWriteNotPermitted_c = 0x0503,
	L2CAPCBConfirm_Status_gAttInvalidPdu_c = 0x0504,
	L2CAPCBConfirm_Status_gAttInsufficientAuthentication_c = 0x0505,
	L2CAPCBConfirm_Status_gAttRequestNotSupported_c = 0x0506,
	L2CAPCBConfirm_Status_gAttInvalidOffset_c = 0x0507,
	L2CAPCBConfirm_Status_gAttInsufficientAuthorization_c = 0x0508,
	L2CAPCBConfirm_Status_gAttPrepareQueueFull_c = 0x0509,
	L2CAPCBConfirm_Status_gAttAttributeNotFound_c = 0x050A,
	L2CAPCBConfirm_Status_gAttAttributeNotLong_c = 0x050B,
	L2CAPCBConfirm_Status_gAttInsufficientEncryptionKeySize_c = 0x050C,
	L2CAPCBConfirm_Status_gAttInvalidAttributeValueLength_c = 0x050D,
	L2CAPCBConfirm_Status_gAttUnlikelyor_c = 0x050E,
	L2CAPCBConfirm_Status_gAttInsufficientEncryption_c = 0x050F,
	L2CAPCBConfirm_Status_gAttUnsupportedGroupType_c = 0x0510,
	L2CAPCBConfirm_Status_gAttInsufficientResources_c = 0x0511,
	L2CAPCBConfirm_Status_gGattAnotherProcedureInProgress_c = 0x0601,
	L2CAPCBConfirm_Status_gGattLongAttributePacketsCorrupted_c = 0x0602,
	L2CAPCBConfirm_Status_gGattMultipleAttributesOverflow_c = 0x0603,
	L2CAPCBConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	L2CAPCBConfirm_Status_gGattInvalidValueLength_c = 0x0605,
	L2CAPCBConfirm_Status_gGattServerTimeout_c = 0x0606,
	L2CAPCBConfirm_Status_gGattIndicationAlreadyInProgress_c = 0x0607,
	L2CAPCBConfirm_Status_gGattClientConfirmationTimeout_c = 0x0608,
	L2CAPCBConfirm_Status_gGapAdvDataTooLong_c = 0x0701,
	L2CAPCBConfirm_Status_gGapScanRspDataTooLong_c = 0x0702,
	L2CAPCBConfirm_Status_gGapDeviceNotBonded_c = 0x0703,
	L2CAPCBConfirm_Status_gGapAnotherProcedureInProgress_c = 0x0704,
	L2CAPCBConfirm_Status_gDevDbCccdLimitReached_c = 0x0801,
	L2CAPCBConfirm_Status_gDevDbCccdNotFound_c = 0x0802,
	L2CAPCBConfirm_Status_gGattDbInvalidHandle_c = 0x0901,
	L2CAPCBConfirm_Status_gGattDbCharacteristicNotFound_c = 0x0902,
	L2CAPCBConfirm_Status_gGattDbCccdNotFound_c = 0x0903,
	L2CAPCBConfirm_Status_gGattDbServiceNotFound_c = 0x0904,
	L2CAPCBConfirm_Status_gGattDbDescriptorNotFound_c = 0x0905
} L2CAPCBConfirm_Status_t;

typedef PACKED_STRUCT L2CAPCBConfirm_tag {
	L2CAPCBConfirm_Status_t Status;  // The status of the L2CAP request
} L2CAPCBConfirm_t;

typedef struct L2CAPCBLePsmConnectionRequestIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		uint16_t LePsm;  // Bluetooth SIG or Vendor LE_PSM
		uint16_t PeerMtu;  // Peer MTU
		uint16_t PeerMps;  // Peer MPS
		uint16_t InitialCredits;  // Initial credits
	} LeCbConnectionRequest;  // Connection request event data
} L2CAPCBLePsmConnectionRequestIndication_t;

/* Connection result */
typedef enum L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_tag {
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gSuccessful_c = 0x0000,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gLePsmNotSupported_c = 0x0002,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gNoResourcesAvailable_c = 0x0004,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gInsufficientAuthentication_c = 0x0005,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gInsufficientAuthorization_c = 0x0006,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gInsufficientEncryptionKeySize_c = 0x0007,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gInsufficientEncryption_c = 0x0008,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gInvalidSourceCid_c = 0x0009,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gSourceCidAlreadyAllocated_c = 0x000A,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gTimerError_c = 0x000B,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gCommandRejected_c = 0x0100,
	L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_gResponseTimeout_c = 0xFFFE
} L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_t;

typedef struct L2CAPCBLePsmConnectionCompleteIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
		uint16_t PeerMtu;  // Peer's MTU
		uint16_t PeerMps;  // Peer's MPS
		uint16_t InitialCredits;  // Initial credits
		L2CAPCBLePsmConnectionCompleteIndication_LeCbConnectionComplete_Result_t Result;  // Connection result
	} LeCbConnectionComplete;  // Connection complete event data
} L2CAPCBLePsmConnectionCompleteIndication_t;

typedef struct L2CAPCBLePsmDisconnectNotificationIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
	} LeCbDisconnection;  // Disconnection event data
} L2CAPCBLePsmDisconnectNotificationIndication_t;

typedef struct L2CAPCBNoPeerCreditsIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
	} LeCbNoPeerCredits;  // No peer credits event data
} L2CAPCBNoPeerCreditsIndication_t;

typedef struct L2CAPCBLocalCreditsNotificationIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		uint16_t ChannelId;  // The L2CAP Channel Id assigned on the initiator
		uint16_t LocalCredits;  // Local credits
	} LeCbLocalCreditsNotification;  // Local credits notification event data
} L2CAPCBLocalCreditsNotificationIndication_t;

typedef struct L2CAPCBLeCbDataIndication_tag {
	uint8_t DeviceId;  // The DeviceId from which data packet is received
	uint16_t SrcCid;  // Source Channel Id
	uint16_t PacketLength;  // Length of the received data packet
	uint8_t *Packet;  // The received data packet
} L2CAPCBLeCbDataIndication_t;

/* Internal error reported by the L2CAP layer */
typedef enum L2CAPCBErrorIndication_LeCbError_Error_tag {
	L2CAPCBErrorIndication_LeCbError_Error_gBleSuccess_c = 0x0000,
	L2CAPCBErrorIndication_LeCbError_Error_gBleInvalidParameter_c = 0x0001,
	L2CAPCBErrorIndication_LeCbError_Error_gBleOverflow_c = 0x0002,
	L2CAPCBErrorIndication_LeCbError_Error_gBleUnavailable_c = 0x0003,
	L2CAPCBErrorIndication_LeCbError_Error_gBleFeatureNotSupported_c = 0x0004,
	L2CAPCBErrorIndication_LeCbError_Error_gBleOutOfMemory_c = 0x0005,
	L2CAPCBErrorIndication_LeCbError_Error_gBleAlreadyInitialized_c = 0x0006,
	L2CAPCBErrorIndication_LeCbError_Error_gBleOsError_c = 0x0007,
	L2CAPCBErrorIndication_LeCbError_Error_gBleUnexpectedError_c = 0x0008,
	L2CAPCBErrorIndication_LeCbError_Error_gBleInvalidState_c = 0x0009,
	L2CAPCBErrorIndication_LeCbError_Error_gBleTimerError_c = 0x000A,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnknownHciCommand_c = 0x0101,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	L2CAPCBErrorIndication_LeCbError_Error_gHciHardwareFailure_c = 0x0103,
	L2CAPCBErrorIndication_LeCbError_Error_gHciPageTimeout_c = 0x0104,
	L2CAPCBErrorIndication_LeCbError_Error_gHciAuthenticationFailure_c = 0x0105,
	L2CAPCBErrorIndication_LeCbError_Error_gHciPinOrKeyMissing_c = 0x0106,
	L2CAPCBErrorIndication_LeCbError_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionTimeout_c = 0x0108,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionLimitExceeded_c = 0x0109,
	L2CAPCBErrorIndication_LeCbError_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	L2CAPCBErrorIndication_LeCbError_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	L2CAPCBErrorIndication_LeCbError_Error_gHciCommandDisallowed_c = 0x010C,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	L2CAPCBErrorIndication_LeCbError_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRepeatedAttempts_c = 0x0117,
	L2CAPCBErrorIndication_LeCbError_Error_gHciPairingNotAllowed_c = 0x0118,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnknownLpmPdu_c = 0x0119,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	L2CAPCBErrorIndication_LeCbError_Error_gHciScoOffsetRejected_c = 0x011B,
	L2CAPCBErrorIndication_LeCbError_Error_gHciScoIntervalRejected_c = 0x011C,
	L2CAPCBErrorIndication_LeCbError_Error_gHciScoAirModeRejected_c = 0x011D,
	L2CAPCBErrorIndication_LeCbError_Error_gHciInvalidLpmParameters_c = 0x011E,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnspecifiedError_c = 0x011F,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	L2CAPCBErrorIndication_LeCbError_Error_gHciLLResponseTimeout_c = 0x0122,
	L2CAPCBErrorIndication_LeCbError_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	L2CAPCBErrorIndication_LeCbError_Error_gHciLmpPduNotAllowed_c = 0x0124,
	L2CAPCBErrorIndication_LeCbError_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	L2CAPCBErrorIndication_LeCbError_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRequestedQosNotSupported_c = 0x0127,
	L2CAPCBErrorIndication_LeCbError_Error_gHciInstantPassed_c = 0x0128,
	L2CAPCBErrorIndication_LeCbError_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	L2CAPCBErrorIndication_LeCbError_Error_gHciDifferentTransactionCollision_c = 0x012A,
	L2CAPCBErrorIndication_LeCbError_Error_gHciReserved_0x2B_c = 0x012B,
	L2CAPCBErrorIndication_LeCbError_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	L2CAPCBErrorIndication_LeCbError_Error_gHciQosRejected_c = 0x012D,
	L2CAPCBErrorIndication_LeCbError_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	L2CAPCBErrorIndication_LeCbError_Error_gHciInsufficientSecurity_c = 0x012F,
	L2CAPCBErrorIndication_LeCbError_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	L2CAPCBErrorIndication_LeCbError_Error_gHciReserved_0x31_c = 0x0131,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRoleSwitchPending_c = 0x0132,
	L2CAPCBErrorIndication_LeCbError_Error_gHciReserved_0x33_c = 0x0133,
	L2CAPCBErrorIndication_LeCbError_Error_gHciReservedSlotViolation_c = 0x0134,
	L2CAPCBErrorIndication_LeCbError_Error_gHciRoleSwitchFailed_c = 0x0135,
	L2CAPCBErrorIndication_LeCbError_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	L2CAPCBErrorIndication_LeCbError_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	L2CAPCBErrorIndication_LeCbError_Error_gHciHostBusyPairing_c = 0x0138,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	L2CAPCBErrorIndication_LeCbError_Error_gHciControllerBusy_c = 0x013A,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	L2CAPCBErrorIndication_LeCbError_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	L2CAPCBErrorIndication_LeCbError_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	L2CAPCBErrorIndication_LeCbError_Error_gHciMacConnectionFailed_c = 0x013F,
	L2CAPCBErrorIndication_LeCbError_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	L2CAPCBErrorIndication_LeCbError_Error_gHciType0SubmapNotDefined_c = 0x0141,
	L2CAPCBErrorIndication_LeCbError_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	L2CAPCBErrorIndication_LeCbError_Error_gHciLimitReached_c = 0x0143,
	L2CAPCBErrorIndication_LeCbError_Error_gHciOperationCancelledByHost_c = 0x0144,
	L2CAPCBErrorIndication_LeCbError_Error_gHciAlreadyInit_c = 0x01A0,
	L2CAPCBErrorIndication_LeCbError_Error_gHciInvalidParameter_c = 0x01A1,
	L2CAPCBErrorIndication_LeCbError_Error_gHciCallbackNotInstalled_c = 0x01A2,
	L2CAPCBErrorIndication_LeCbError_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	L2CAPCBErrorIndication_LeCbError_Error_gHciCommandNotSupported_c = 0x01A4,
	L2CAPCBErrorIndication_LeCbError_Error_gHciEventNotSupported_c = 0x01A5,
	L2CAPCBErrorIndication_LeCbError_Error_gHciTransportError_c = 0x01A6,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caAlreadyInit_c = 0x03F0,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caInsufficientResources_c = 0x03F1,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caLePsmInvalid_c = 0x03F4,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caChannelInvalid_c = 0x03F8,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caChannelClosed_c = 0x03F9,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caChannelBusy_c = 0x03FC,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caInvalidParameter_c = 0x03FE,
	L2CAPCBErrorIndication_LeCbError_Error_gL2caError_c = 0x03FF,
	L2CAPCBErrorIndication_LeCbError_Error_gSmNullCBFunction_c = 0x0401,
	L2CAPCBErrorIndication_LeCbError_Error_gSmCommandNotSupported_c = 0x0402,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnexpectedCommand_c = 0x0403,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidCommandCode_c = 0x0404,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidCommandLength_c = 0x0405,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidCommandParameter_c = 0x0406,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidDeviceId_c = 0x0407,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidInternalOperation_c = 0x0408,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidConnectionHandle_c = 0x0409,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInproperKeyDistributionField_c = 0x040A,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnexpectedKeyType_c = 0x040B,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnexpectedKeyset_c = 0x040D,
	L2CAPCBErrorIndication_LeCbError_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnknownSmpPacketType_c = 0x040F,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	L2CAPCBErrorIndication_LeCbError_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	L2CAPCBErrorIndication_LeCbError_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	L2CAPCBErrorIndication_LeCbError_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	L2CAPCBErrorIndication_LeCbError_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInvalidHciEventParameter_c = 0x0416,
	L2CAPCBErrorIndication_LeCbError_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	L2CAPCBErrorIndication_LeCbError_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	L2CAPCBErrorIndication_LeCbError_Error_gSmInsufficientResources_c = 0x0419,
	L2CAPCBErrorIndication_LeCbError_Error_gSmOobDataAddressMismatch_c = 0x041A,
	L2CAPCBErrorIndication_LeCbError_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	L2CAPCBErrorIndication_LeCbError_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	L2CAPCBErrorIndication_LeCbError_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	L2CAPCBErrorIndication_LeCbError_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	L2CAPCBErrorIndication_LeCbError_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	L2CAPCBErrorIndication_LeCbError_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	L2CAPCBErrorIndication_LeCbError_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	L2CAPCBErrorIndication_LeCbError_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	L2CAPCBErrorIndication_LeCbError_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	L2CAPCBErrorIndication_LeCbError_Error_gSmTbInvalidDataSignature_c = 0x0461,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInvalidHandle_c = 0x0501,
	L2CAPCBErrorIndication_LeCbError_Error_gAttReadNotPermitted_c = 0x0502,
	L2CAPCBErrorIndication_LeCbError_Error_gAttWriteNotPermitted_c = 0x0503,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInvalidPdu_c = 0x0504,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInsufficientAuthentication_c = 0x0505,
	L2CAPCBErrorIndication_LeCbError_Error_gAttRequestNotSupported_c = 0x0506,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInvalidOffset_c = 0x0507,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInsufficientAuthorization_c = 0x0508,
	L2CAPCBErrorIndication_LeCbError_Error_gAttPrepareQueueFull_c = 0x0509,
	L2CAPCBErrorIndication_LeCbError_Error_gAttAttributeNotFound_c = 0x050A,
	L2CAPCBErrorIndication_LeCbError_Error_gAttAttributeNotLong_c = 0x050B,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	L2CAPCBErrorIndication_LeCbError_Error_gAttUnlikelyor_c = 0x050E,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInsufficientEncryption_c = 0x050F,
	L2CAPCBErrorIndication_LeCbError_Error_gAttUnsupportedGroupType_c = 0x0510,
	L2CAPCBErrorIndication_LeCbError_Error_gAttInsufficientResources_c = 0x0511,
	L2CAPCBErrorIndication_LeCbError_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	L2CAPCBErrorIndication_LeCbError_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	L2CAPCBErrorIndication_LeCbError_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	L2CAPCBErrorIndication_LeCbError_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	L2CAPCBErrorIndication_LeCbError_Error_gGattInvalidValueLength_c = 0x0605,
	L2CAPCBErrorIndication_LeCbError_Error_gGattServerTimeout_c = 0x0606,
	L2CAPCBErrorIndication_LeCbError_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	L2CAPCBErrorIndication_LeCbError_Error_gGattClientConfirmationTimeout_c = 0x0608,
	L2CAPCBErrorIndication_LeCbError_Error_gGapAdvDataTooLong_c = 0x0701,
	L2CAPCBErrorIndication_LeCbError_Error_gGapScanRspDataTooLong_c = 0x0702,
	L2CAPCBErrorIndication_LeCbError_Error_gGapDeviceNotBonded_c = 0x0703,
	L2CAPCBErrorIndication_LeCbError_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	L2CAPCBErrorIndication_LeCbError_Error_gDevDbCccdLimitReached_c = 0x0801,
	L2CAPCBErrorIndication_LeCbError_Error_gDevDbCccdNotFound_c = 0x0802,
	L2CAPCBErrorIndication_LeCbError_Error_gGattDbInvalidHandle_c = 0x0901,
	L2CAPCBErrorIndication_LeCbError_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	L2CAPCBErrorIndication_LeCbError_Error_gGattDbCccdNotFound_c = 0x0903,
	L2CAPCBErrorIndication_LeCbError_Error_gGattDbServiceNotFound_c = 0x0904,
	L2CAPCBErrorIndication_LeCbError_Error_gGattDbDescriptorNotFound_c = 0x0905
} L2CAPCBErrorIndication_LeCbError_Error_t;

typedef struct L2CAPCBErrorIndication_tag {
	bool_t InformationIncluded;  // Information is included or not
	struct {
		uint8_t DeviceId;  // The DeviceId for which the command is intended
		L2CAPCBErrorIndication_LeCbError_Error_t Error;  // Internal error reported by the L2CAP layer
	} LeCbError;  // Internal error event data
} L2CAPCBErrorIndication_t;

#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
/* The status of the GATT request */
typedef enum GATTConfirm_Status_tag {
	GATTConfirm_Status_gBleSuccess_c = 0x0000,
	GATTConfirm_Status_gBleInvalidParameter_c = 0x0001,
	GATTConfirm_Status_gBleOverflow_c = 0x0002,
	GATTConfirm_Status_gBleUnavailable_c = 0x0003,
	GATTConfirm_Status_gBleFeatureNotSupported_c = 0x0004,
	GATTConfirm_Status_gBleOutOfMemory_c = 0x0005,
	GATTConfirm_Status_gBleAlreadyInitialized_c = 0x0006,
	GATTConfirm_Status_gBleOsError_c = 0x0007,
	GATTConfirm_Status_gBleUnexpectedError_c = 0x0008,
	GATTConfirm_Status_gBleInvalidState_c = 0x0009,
	GATTConfirm_Status_gBleTimerError_c = 0x000A,
	GATTConfirm_Status_gHciUnknownHciCommand_c = 0x0101,
	GATTConfirm_Status_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTConfirm_Status_gHciHardwareFailure_c = 0x0103,
	GATTConfirm_Status_gHciPageTimeout_c = 0x0104,
	GATTConfirm_Status_gHciAuthenticationFailure_c = 0x0105,
	GATTConfirm_Status_gHciPinOrKeyMissing_c = 0x0106,
	GATTConfirm_Status_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTConfirm_Status_gHciConnectionTimeout_c = 0x0108,
	GATTConfirm_Status_gHciConnectionLimitExceeded_c = 0x0109,
	GATTConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTConfirm_Status_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTConfirm_Status_gHciCommandDisallowed_c = 0x010C,
	GATTConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTConfirm_Status_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTConfirm_Status_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTConfirm_Status_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTConfirm_Status_gHciRepeatedAttempts_c = 0x0117,
	GATTConfirm_Status_gHciPairingNotAllowed_c = 0x0118,
	GATTConfirm_Status_gHciUnknownLpmPdu_c = 0x0119,
	GATTConfirm_Status_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTConfirm_Status_gHciScoOffsetRejected_c = 0x011B,
	GATTConfirm_Status_gHciScoIntervalRejected_c = 0x011C,
	GATTConfirm_Status_gHciScoAirModeRejected_c = 0x011D,
	GATTConfirm_Status_gHciInvalidLpmParameters_c = 0x011E,
	GATTConfirm_Status_gHciUnspecifiedError_c = 0x011F,
	GATTConfirm_Status_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTConfirm_Status_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTConfirm_Status_gHciLLResponseTimeout_c = 0x0122,
	GATTConfirm_Status_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTConfirm_Status_gHciLmpPduNotAllowed_c = 0x0124,
	GATTConfirm_Status_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTConfirm_Status_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTConfirm_Status_gHciRequestedQosNotSupported_c = 0x0127,
	GATTConfirm_Status_gHciInstantPassed_c = 0x0128,
	GATTConfirm_Status_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTConfirm_Status_gHciDifferentTransactionCollision_c = 0x012A,
	GATTConfirm_Status_gHciReserved_0x2B_c = 0x012B,
	GATTConfirm_Status_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTConfirm_Status_gHciQosRejected_c = 0x012D,
	GATTConfirm_Status_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTConfirm_Status_gHciInsufficientSecurity_c = 0x012F,
	GATTConfirm_Status_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTConfirm_Status_gHciReserved_0x31_c = 0x0131,
	GATTConfirm_Status_gHciRoleSwitchPending_c = 0x0132,
	GATTConfirm_Status_gHciReserved_0x33_c = 0x0133,
	GATTConfirm_Status_gHciReservedSlotViolation_c = 0x0134,
	GATTConfirm_Status_gHciRoleSwitchFailed_c = 0x0135,
	GATTConfirm_Status_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTConfirm_Status_gHciHostBusyPairing_c = 0x0138,
	GATTConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTConfirm_Status_gHciControllerBusy_c = 0x013A,
	GATTConfirm_Status_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTConfirm_Status_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTConfirm_Status_gHciMacConnectionFailed_c = 0x013F,
	GATTConfirm_Status_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTConfirm_Status_gHciType0SubmapNotDefined_c = 0x0141,
	GATTConfirm_Status_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTConfirm_Status_gHciLimitReached_c = 0x0143,
	GATTConfirm_Status_gHciOperationCancelledByHost_c = 0x0144,
	GATTConfirm_Status_gHciAlreadyInit_c = 0x01A0,
	GATTConfirm_Status_gHciInvalidParameter_c = 0x01A1,
	GATTConfirm_Status_gHciCallbackNotInstalled_c = 0x01A2,
	GATTConfirm_Status_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTConfirm_Status_gHciCommandNotSupported_c = 0x01A4,
	GATTConfirm_Status_gHciEventNotSupported_c = 0x01A5,
	GATTConfirm_Status_gHciTransportError_c = 0x01A6,
	GATTConfirm_Status_gL2caAlreadyInit_c = 0x03F0,
	GATTConfirm_Status_gL2caInsufficientResources_c = 0x03F1,
	GATTConfirm_Status_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTConfirm_Status_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTConfirm_Status_gL2caLePsmInvalid_c = 0x03F4,
	GATTConfirm_Status_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTConfirm_Status_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTConfirm_Status_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTConfirm_Status_gL2caChannelInvalid_c = 0x03F8,
	GATTConfirm_Status_gL2caChannelClosed_c = 0x03F9,
	GATTConfirm_Status_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTConfirm_Status_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTConfirm_Status_gL2caChannelBusy_c = 0x03FC,
	GATTConfirm_Status_gL2caInvalidParameter_c = 0x03FE,
	GATTConfirm_Status_gL2caError_c = 0x03FF,
	GATTConfirm_Status_gSmNullCBFunction_c = 0x0401,
	GATTConfirm_Status_gSmCommandNotSupported_c = 0x0402,
	GATTConfirm_Status_gSmUnexpectedCommand_c = 0x0403,
	GATTConfirm_Status_gSmInvalidCommandCode_c = 0x0404,
	GATTConfirm_Status_gSmInvalidCommandLength_c = 0x0405,
	GATTConfirm_Status_gSmInvalidCommandParameter_c = 0x0406,
	GATTConfirm_Status_gSmInvalidDeviceId_c = 0x0407,
	GATTConfirm_Status_gSmInvalidInternalOperation_c = 0x0408,
	GATTConfirm_Status_gSmInvalidConnectionHandle_c = 0x0409,
	GATTConfirm_Status_gSmInproperKeyDistributionField_c = 0x040A,
	GATTConfirm_Status_gSmUnexpectedKeyType_c = 0x040B,
	GATTConfirm_Status_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTConfirm_Status_gSmUnexpectedKeyset_c = 0x040D,
	GATTConfirm_Status_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTConfirm_Status_gSmUnknownSmpPacketType_c = 0x040F,
	GATTConfirm_Status_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTConfirm_Status_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTConfirm_Status_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTConfirm_Status_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTConfirm_Status_gSmInvalidHciEventParameter_c = 0x0416,
	GATTConfirm_Status_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTConfirm_Status_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTConfirm_Status_gSmInsufficientResources_c = 0x0419,
	GATTConfirm_Status_gSmOobDataAddressMismatch_c = 0x041A,
	GATTConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTConfirm_Status_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTConfirm_Status_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTConfirm_Status_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTConfirm_Status_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTConfirm_Status_gSmTbInvalidDataSignature_c = 0x0461,
	GATTConfirm_Status_gAttInvalidHandle_c = 0x0501,
	GATTConfirm_Status_gAttReadNotPermitted_c = 0x0502,
	GATTConfirm_Status_gAttWriteNotPermitted_c = 0x0503,
	GATTConfirm_Status_gAttInvalidPdu_c = 0x0504,
	GATTConfirm_Status_gAttInsufficientAuthentication_c = 0x0505,
	GATTConfirm_Status_gAttRequestNotSupported_c = 0x0506,
	GATTConfirm_Status_gAttInvalidOffset_c = 0x0507,
	GATTConfirm_Status_gAttInsufficientAuthorization_c = 0x0508,
	GATTConfirm_Status_gAttPrepareQueueFull_c = 0x0509,
	GATTConfirm_Status_gAttAttributeNotFound_c = 0x050A,
	GATTConfirm_Status_gAttAttributeNotLong_c = 0x050B,
	GATTConfirm_Status_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTConfirm_Status_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTConfirm_Status_gAttUnlikelyor_c = 0x050E,
	GATTConfirm_Status_gAttInsufficientEncryption_c = 0x050F,
	GATTConfirm_Status_gAttUnsupportedGroupType_c = 0x0510,
	GATTConfirm_Status_gAttInsufficientResources_c = 0x0511,
	GATTConfirm_Status_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTConfirm_Status_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTConfirm_Status_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTConfirm_Status_gGattInvalidValueLength_c = 0x0605,
	GATTConfirm_Status_gGattServerTimeout_c = 0x0606,
	GATTConfirm_Status_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTConfirm_Status_gGattClientConfirmationTimeout_c = 0x0608,
	GATTConfirm_Status_gGapAdvDataTooLong_c = 0x0701,
	GATTConfirm_Status_gGapScanRspDataTooLong_c = 0x0702,
	GATTConfirm_Status_gGapDeviceNotBonded_c = 0x0703,
	GATTConfirm_Status_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTConfirm_Status_gDevDbCccdLimitReached_c = 0x0801,
	GATTConfirm_Status_gDevDbCccdNotFound_c = 0x0802,
	GATTConfirm_Status_gGattDbInvalidHandle_c = 0x0901,
	GATTConfirm_Status_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTConfirm_Status_gGattDbCccdNotFound_c = 0x0903,
	GATTConfirm_Status_gGattDbServiceNotFound_c = 0x0904,
	GATTConfirm_Status_gGattDbDescriptorNotFound_c = 0x0905
} GATTConfirm_Status_t;

typedef PACKED_STRUCT GATTConfirm_tag {
	GATTConfirm_Status_t Status;  // The status of the GATT request
} GATTConfirm_t;

typedef PACKED_STRUCT GATTGetMtuIndication_tag {
	uint16_t Mtu;  // MTU value
} GATTGetMtuIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureExchangeMtuIndication_ProcedureResult_tag {
	GATTClientProcedureExchangeMtuIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureExchangeMtuIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureExchangeMtuIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureExchangeMtuIndication_Error_tag {
	GATTClientProcedureExchangeMtuIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureExchangeMtuIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureExchangeMtuIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureExchangeMtuIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureExchangeMtuIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureExchangeMtuIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureExchangeMtuIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureExchangeMtuIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureExchangeMtuIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureExchangeMtuIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureExchangeMtuIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureExchangeMtuIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureExchangeMtuIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureExchangeMtuIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureExchangeMtuIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureExchangeMtuIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureExchangeMtuIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureExchangeMtuIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureExchangeMtuIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureExchangeMtuIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureExchangeMtuIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureExchangeMtuIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureExchangeMtuIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureExchangeMtuIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureExchangeMtuIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureExchangeMtuIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureExchangeMtuIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureExchangeMtuIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureExchangeMtuIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureExchangeMtuIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureExchangeMtuIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureExchangeMtuIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureExchangeMtuIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureExchangeMtuIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureExchangeMtuIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureExchangeMtuIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureExchangeMtuIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureExchangeMtuIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureExchangeMtuIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureExchangeMtuIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureExchangeMtuIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureExchangeMtuIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureExchangeMtuIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureExchangeMtuIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureExchangeMtuIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureExchangeMtuIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureExchangeMtuIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureExchangeMtuIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureExchangeMtuIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureExchangeMtuIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureExchangeMtuIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureExchangeMtuIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureExchangeMtuIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureExchangeMtuIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureExchangeMtuIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureExchangeMtuIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureExchangeMtuIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureExchangeMtuIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureExchangeMtuIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureExchangeMtuIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureExchangeMtuIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureExchangeMtuIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureExchangeMtuIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureExchangeMtuIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureExchangeMtuIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureExchangeMtuIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureExchangeMtuIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureExchangeMtuIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureExchangeMtuIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureExchangeMtuIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureExchangeMtuIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureExchangeMtuIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureExchangeMtuIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureExchangeMtuIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureExchangeMtuIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureExchangeMtuIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureExchangeMtuIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureExchangeMtuIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureExchangeMtuIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureExchangeMtuIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureExchangeMtuIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureExchangeMtuIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureExchangeMtuIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureExchangeMtuIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureExchangeMtuIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureExchangeMtuIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureExchangeMtuIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureExchangeMtuIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureExchangeMtuIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureExchangeMtuIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureExchangeMtuIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureExchangeMtuIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureExchangeMtuIndication_Error_t;

typedef PACKED_STRUCT GATTClientProcedureExchangeMtuIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureExchangeMtuIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureExchangeMtuIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
} GATTClientProcedureExchangeMtuIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_tag {
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_tag {
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_t;

typedef struct GATTClientProcedureDiscoverAllPrimaryServicesIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	uint8_t NbOfDiscoveredServices;  // Number of discovered services
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} *DiscoveredServices;  // Discovered services
} GATTClientProcedureDiscoverAllPrimaryServicesIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_tag {
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_tag {
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_t;

typedef struct GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	uint8_t NbOfDiscoveredServices;  // Number of discovered services
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} *DiscoveredServices;  // Discovered services
} GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_tag {
	GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureFindIncludedServicesIndication_Error_tag {
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureFindIncludedServicesIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureFindIncludedServicesIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureFindIncludedServicesIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureFindIncludedServicesIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureFindIncludedServicesIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureFindIncludedServicesIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureFindIncludedServicesIndication_Error_t;

typedef struct GATTClientProcedureFindIncludedServicesIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureFindIncludedServicesIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} Service;  // The service within which inclusions were searched
} GATTClientProcedureFindIncludedServicesIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_tag {
	GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_tag {
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_t;

typedef struct GATTClientProcedureDiscoverAllCharacteristicsIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	struct {
		uint16_t StartHandle;  // The handle of the Service Declaration attribute
		uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint8_t NbOfCharacteristics;  // Size of the Characteristic array
		struct {
			Properties_t Properties;  // Characteristic Properties as defined by GATT
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} Value;  // Characteristic Value attribute
			uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
			struct {
				uint16_t Handle;  // Attribute handle
				UuidType_t UuidType;  // UUID type
				union {
					uint8_t Uuid16Bits[2];  // UUID 16 bits
					uint8_t Uuid128Bits[16];  // UUID 128 bits
					uint8_t Uuid32Bits[4];  // UUID 32 bits
				} Uuid;  // UUID value
				uint16_t ValueLength;  // Length of the attribute value array
				uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
				uint8_t *Value;  // Attribute value array
			} *Descriptors;  // Characteristic Descriptors array
		} *Characteristics;  // Characteristic array
		uint8_t NbOfIncludedServices;  // Size of the Included Services array
		struct {
			uint16_t StartHandle;  // The handle of the Service Declaration attribute
			uint16_t EndHandle;  // The last handle belonging to this Service (followed by another Service declaration of the end of the database)
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint8_t NbOfCharacteristics;  // Size of the Characteristic array
			uint8_t NbOfIncludedServices;  // Size of the Included Services array
		} *IncludedServices;  // Included Services array
	} Service;  // The service within which characteristics were searched
} GATTClientProcedureDiscoverAllCharacteristicsIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_tag {
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_tag {
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_t;

typedef struct GATTClientProcedureDiscoverCharacteristicByUuidIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	uint8_t NbOfCharacteristics;  // Number of discovered characteristics
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} *Characteristics;  // Characteristics that were filled
} GATTClientProcedureDiscoverCharacteristicByUuidIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_tag {
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_tag {
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_t;

typedef struct GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} Characteristic;  // The characteristic within which descriptors were searched
} GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_tag {
	GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureReadCharacteristicValueIndication_Error_tag {
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureReadCharacteristicValueIndication_Error_t;

typedef struct GATTClientProcedureReadCharacteristicValueIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureReadCharacteristicValueIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} Characteristic;  // The characteristic whose value was read
} GATTClientProcedureReadCharacteristicValueIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_tag {
	GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_tag {
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_t;

typedef struct GATTClientProcedureReadUsingCharacteristicUuidIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	uint16_t NbOfReadBytes;  // The number of bytes that were read
	uint8_t *ReadBytes;  // The bytes that were read
} GATTClientProcedureReadUsingCharacteristicUuidIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_tag {
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_tag {
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_t;

typedef struct GATTClientProcedureReadMultipleCharacteristicValuesIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	uint8_t NbOfCharacteristics;  // Number of characteristics whose values were read
	struct {
		Properties_t Properties;  // Characteristic Properties as defined by GATT
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} Value;  // Characteristic Value attribute
		uint8_t NbOfDescriptors;  // Size of the Characteristic Descriptors array
		struct {
			uint16_t Handle;  // Attribute handle
			UuidType_t UuidType;  // UUID type
			union {
				uint8_t Uuid16Bits[2];  // UUID 16 bits
				uint8_t Uuid128Bits[16];  // UUID 128 bits
				uint8_t Uuid32Bits[4];  // UUID 32 bits
			} Uuid;  // UUID value
			uint16_t ValueLength;  // Length of the attribute value array
			uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
			uint8_t *Value;  // Attribute value array
		} *Descriptors;  // Characteristic Descriptors array
	} *Characteristics;  // Characteristics whose values were read
} GATTClientProcedureReadMultipleCharacteristicValuesIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_tag {
	GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureWriteCharacteristicValueIndication_Error_tag {
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureWriteCharacteristicValueIndication_Error_t;

typedef PACKED_STRUCT GATTClientProcedureWriteCharacteristicValueIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureWriteCharacteristicValueIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
} GATTClientProcedureWriteCharacteristicValueIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_tag {
	GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureReadCharacteristicDescriptorIndication_Error_tag {
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureReadCharacteristicDescriptorIndication_Error_t;

typedef struct GATTClientProcedureReadCharacteristicDescriptorIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureReadCharacteristicDescriptorIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
	struct {
		uint16_t Handle;  // Attribute handle
		UuidType_t UuidType;  // UUID type
		union {
			uint8_t Uuid16Bits[2];  // UUID 16 bits
			uint8_t Uuid128Bits[16];  // UUID 128 bits
			uint8_t Uuid32Bits[4];  // UUID 32 bits
		} Uuid;  // UUID value
		uint16_t ValueLength;  // Length of the attribute value array
		uint16_t MaxValueLength;  // Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
		uint8_t *Value;  // Attribute value array
	} Descriptor;  // The characteristic descriptor whose value was read
} GATTClientProcedureReadCharacteristicDescriptorIndication_t;

/* The result of the completed procedure */
typedef enum GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_tag {
	GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_gGattProcSuccess_c = 0x00,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_gProcedureError_c = 0x01
} GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_t;

/* If procedureResult is not gSuccess_c, this contains the error that terminated the procedure */
typedef enum GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_tag {
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleSuccess_c = 0x0000,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleInvalidParameter_c = 0x0001,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOverflow_c = 0x0002,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleUnavailable_c = 0x0003,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOutOfMemory_c = 0x0005,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOsError_c = 0x0007,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleUnexpectedError_c = 0x0008,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleInvalidState_c = 0x0009,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleTimerError_c = 0x000A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciHardwareFailure_c = 0x0103,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPageTimeout_c = 0x0104,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTimeout_c = 0x0108,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCommandDisallowed_c = 0x010C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnspecifiedError_c = 0x011F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInstantPassed_c = 0x0128,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x2B_c = 0x012B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciQosRejected_c = 0x012D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x31_c = 0x0131,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x33_c = 0x0133,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciHostBusyPairing_c = 0x0138,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciControllerBusy_c = 0x013A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLimitReached_c = 0x0143,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAlreadyInit_c = 0x01A0,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidParameter_c = 0x01A1,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciEventNotSupported_c = 0x01A5,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciTransportError_c = 0x01A6,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelClosed_c = 0x03F9,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelBusy_c = 0x03FC,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caError_c = 0x03FF,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmNullCBFunction_c = 0x0401,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmCommandNotSupported_c = 0x0402,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInsufficientResources_c = 0x0419,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidHandle_c = 0x0501,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttReadNotPermitted_c = 0x0502,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidPdu_c = 0x0504,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttRequestNotSupported_c = 0x0506,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidOffset_c = 0x0507,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttAttributeNotFound_c = 0x050A,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttAttributeNotLong_c = 0x050B,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttUnlikelyor_c = 0x050E,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientResources_c = 0x0511,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattInvalidValueLength_c = 0x0605,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattServerTimeout_c = 0x0606,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_t;

typedef PACKED_STRUCT GATTClientProcedureWriteCharacteristicDescriptorIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_t ProcedureResult;  // The result of the completed procedure
	GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_t Error;  // If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
} GATTClientProcedureWriteCharacteristicDescriptorIndication_t;

typedef struct GATTClientNotificationIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	uint16_t CharacteristicValueHandle;  // Handle of the Characteristic Value attribute to be notified
	uint16_t ValueLength;  // Value array size
	uint8_t *Value;  // The Characteristic value array
} GATTClientNotificationIndication_t;

typedef struct GATTClientIndicationIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	uint16_t CharacteristicValueHandle;  // Handle of the Characteristic Value attribute to be indicated
	uint16_t ValueLength;  // Value array size
	uint8_t *Value;  // The Characteristic value array
} GATTClientIndicationIndication_t;

typedef PACKED_STRUCT GATTServerMtuChangedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	uint16_t MtuChangedEvent_NewMtu;

} GATTServerMtuChangedIndication_t;

typedef PACKED_STRUCT GATTServerHandleValueConfirmationIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
} GATTServerHandleValueConfirmationIndication_t;

typedef struct GATTServerAttributeWrittenIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	struct {
		uint16_t Handle;  // Handle of the attribute
		uint16_t ValueLength;  // Length of the attribute value array
		uint8_t *Value;  // Attribute value array attempted to be written
	} AttributeWrittenEvent;  // Attribute written event
} GATTServerAttributeWrittenIndication_t;

/* New value of the CCCD */
typedef enum GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_tag {
	GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_gCccdEmpty_c = 0x00,
	GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_gCccdNotification_c = 0x01,
	GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_gCccdIndication_c = 0x02
} GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_t;

typedef PACKED_STRUCT GATTServerCharacteristicCccdWrittenIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	struct {
		uint16_t Handle;  // Handle of the CCCD attribute
		GATTServerCharacteristicCccdWrittenIndication_CharCccdWrittenEvent_NewCccd_t NewCccd;  // New value of the CCCD
	} CharCccdWrittenEvent;  // Characteristic cccd written event
} GATTServerCharacteristicCccdWrittenIndication_t;

typedef struct GATTServerAttributeWrittenWithoutResponseIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	struct {
		uint16_t Handle;  // Handle of the attribute
		uint16_t ValueLength;  // Length of the attribute value array
		uint8_t *Value;  // Attribute value array attempted to be written
	} AttributeWrittenEvent;  // Attribute written event
} GATTServerAttributeWrittenWithoutResponseIndication_t;

/* Procedure that generated error */
typedef enum GATTServerErrorIndication_ProcedureError_ProcedureType_tag {
	GATTServerErrorIndication_ProcedureError_ProcedureType_gSendAttributeWrittenStatus_c = 0x00,
	GATTServerErrorIndication_ProcedureError_ProcedureType_gSendAttributeReadStatus_c = 0x01,
	GATTServerErrorIndication_ProcedureError_ProcedureType_gSendNotification_c = 0x02,
	GATTServerErrorIndication_ProcedureError_ProcedureType_gSendIndication_c = 0x03
} GATTServerErrorIndication_ProcedureError_ProcedureType_t;

/* Error generated */
typedef enum GATTServerErrorIndication_ProcedureError_Error_tag {
	GATTServerErrorIndication_ProcedureError_Error_gBleSuccess_c = 0x0000,
	GATTServerErrorIndication_ProcedureError_Error_gBleInvalidParameter_c = 0x0001,
	GATTServerErrorIndication_ProcedureError_Error_gBleOverflow_c = 0x0002,
	GATTServerErrorIndication_ProcedureError_Error_gBleUnavailable_c = 0x0003,
	GATTServerErrorIndication_ProcedureError_Error_gBleFeatureNotSupported_c = 0x0004,
	GATTServerErrorIndication_ProcedureError_Error_gBleOutOfMemory_c = 0x0005,
	GATTServerErrorIndication_ProcedureError_Error_gBleAlreadyInitialized_c = 0x0006,
	GATTServerErrorIndication_ProcedureError_Error_gBleOsError_c = 0x0007,
	GATTServerErrorIndication_ProcedureError_Error_gBleUnexpectedError_c = 0x0008,
	GATTServerErrorIndication_ProcedureError_Error_gBleInvalidState_c = 0x0009,
	GATTServerErrorIndication_ProcedureError_Error_gBleTimerError_c = 0x000A,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnknownHciCommand_c = 0x0101,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTServerErrorIndication_ProcedureError_Error_gHciHardwareFailure_c = 0x0103,
	GATTServerErrorIndication_ProcedureError_Error_gHciPageTimeout_c = 0x0104,
	GATTServerErrorIndication_ProcedureError_Error_gHciAuthenticationFailure_c = 0x0105,
	GATTServerErrorIndication_ProcedureError_Error_gHciPinOrKeyMissing_c = 0x0106,
	GATTServerErrorIndication_ProcedureError_Error_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionTimeout_c = 0x0108,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionLimitExceeded_c = 0x0109,
	GATTServerErrorIndication_ProcedureError_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTServerErrorIndication_ProcedureError_Error_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTServerErrorIndication_ProcedureError_Error_gHciCommandDisallowed_c = 0x010C,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTServerErrorIndication_ProcedureError_Error_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTServerErrorIndication_ProcedureError_Error_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTServerErrorIndication_ProcedureError_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTServerErrorIndication_ProcedureError_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTServerErrorIndication_ProcedureError_Error_gHciRepeatedAttempts_c = 0x0117,
	GATTServerErrorIndication_ProcedureError_Error_gHciPairingNotAllowed_c = 0x0118,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnknownLpmPdu_c = 0x0119,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTServerErrorIndication_ProcedureError_Error_gHciScoOffsetRejected_c = 0x011B,
	GATTServerErrorIndication_ProcedureError_Error_gHciScoIntervalRejected_c = 0x011C,
	GATTServerErrorIndication_ProcedureError_Error_gHciScoAirModeRejected_c = 0x011D,
	GATTServerErrorIndication_ProcedureError_Error_gHciInvalidLpmParameters_c = 0x011E,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnspecifiedError_c = 0x011F,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTServerErrorIndication_ProcedureError_Error_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTServerErrorIndication_ProcedureError_Error_gHciLLResponseTimeout_c = 0x0122,
	GATTServerErrorIndication_ProcedureError_Error_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTServerErrorIndication_ProcedureError_Error_gHciLmpPduNotAllowed_c = 0x0124,
	GATTServerErrorIndication_ProcedureError_Error_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTServerErrorIndication_ProcedureError_Error_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTServerErrorIndication_ProcedureError_Error_gHciRequestedQosNotSupported_c = 0x0127,
	GATTServerErrorIndication_ProcedureError_Error_gHciInstantPassed_c = 0x0128,
	GATTServerErrorIndication_ProcedureError_Error_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTServerErrorIndication_ProcedureError_Error_gHciDifferentTransactionCollision_c = 0x012A,
	GATTServerErrorIndication_ProcedureError_Error_gHciReserved_0x2B_c = 0x012B,
	GATTServerErrorIndication_ProcedureError_Error_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTServerErrorIndication_ProcedureError_Error_gHciQosRejected_c = 0x012D,
	GATTServerErrorIndication_ProcedureError_Error_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTServerErrorIndication_ProcedureError_Error_gHciInsufficientSecurity_c = 0x012F,
	GATTServerErrorIndication_ProcedureError_Error_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTServerErrorIndication_ProcedureError_Error_gHciReserved_0x31_c = 0x0131,
	GATTServerErrorIndication_ProcedureError_Error_gHciRoleSwitchPending_c = 0x0132,
	GATTServerErrorIndication_ProcedureError_Error_gHciReserved_0x33_c = 0x0133,
	GATTServerErrorIndication_ProcedureError_Error_gHciReservedSlotViolation_c = 0x0134,
	GATTServerErrorIndication_ProcedureError_Error_gHciRoleSwitchFailed_c = 0x0135,
	GATTServerErrorIndication_ProcedureError_Error_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTServerErrorIndication_ProcedureError_Error_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTServerErrorIndication_ProcedureError_Error_gHciHostBusyPairing_c = 0x0138,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTServerErrorIndication_ProcedureError_Error_gHciControllerBusy_c = 0x013A,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTServerErrorIndication_ProcedureError_Error_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTServerErrorIndication_ProcedureError_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTServerErrorIndication_ProcedureError_Error_gHciMacConnectionFailed_c = 0x013F,
	GATTServerErrorIndication_ProcedureError_Error_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTServerErrorIndication_ProcedureError_Error_gHciType0SubmapNotDefined_c = 0x0141,
	GATTServerErrorIndication_ProcedureError_Error_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTServerErrorIndication_ProcedureError_Error_gHciLimitReached_c = 0x0143,
	GATTServerErrorIndication_ProcedureError_Error_gHciOperationCancelledByHost_c = 0x0144,
	GATTServerErrorIndication_ProcedureError_Error_gHciAlreadyInit_c = 0x01A0,
	GATTServerErrorIndication_ProcedureError_Error_gHciInvalidParameter_c = 0x01A1,
	GATTServerErrorIndication_ProcedureError_Error_gHciCallbackNotInstalled_c = 0x01A2,
	GATTServerErrorIndication_ProcedureError_Error_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTServerErrorIndication_ProcedureError_Error_gHciCommandNotSupported_c = 0x01A4,
	GATTServerErrorIndication_ProcedureError_Error_gHciEventNotSupported_c = 0x01A5,
	GATTServerErrorIndication_ProcedureError_Error_gHciTransportError_c = 0x01A6,
	GATTServerErrorIndication_ProcedureError_Error_gL2caAlreadyInit_c = 0x03F0,
	GATTServerErrorIndication_ProcedureError_Error_gL2caInsufficientResources_c = 0x03F1,
	GATTServerErrorIndication_ProcedureError_Error_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTServerErrorIndication_ProcedureError_Error_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTServerErrorIndication_ProcedureError_Error_gL2caLePsmInvalid_c = 0x03F4,
	GATTServerErrorIndication_ProcedureError_Error_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTServerErrorIndication_ProcedureError_Error_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTServerErrorIndication_ProcedureError_Error_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTServerErrorIndication_ProcedureError_Error_gL2caChannelInvalid_c = 0x03F8,
	GATTServerErrorIndication_ProcedureError_Error_gL2caChannelClosed_c = 0x03F9,
	GATTServerErrorIndication_ProcedureError_Error_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTServerErrorIndication_ProcedureError_Error_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTServerErrorIndication_ProcedureError_Error_gL2caChannelBusy_c = 0x03FC,
	GATTServerErrorIndication_ProcedureError_Error_gL2caInvalidParameter_c = 0x03FE,
	GATTServerErrorIndication_ProcedureError_Error_gL2caError_c = 0x03FF,
	GATTServerErrorIndication_ProcedureError_Error_gSmNullCBFunction_c = 0x0401,
	GATTServerErrorIndication_ProcedureError_Error_gSmCommandNotSupported_c = 0x0402,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnexpectedCommand_c = 0x0403,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidCommandCode_c = 0x0404,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidCommandLength_c = 0x0405,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidCommandParameter_c = 0x0406,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidDeviceId_c = 0x0407,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidInternalOperation_c = 0x0408,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidConnectionHandle_c = 0x0409,
	GATTServerErrorIndication_ProcedureError_Error_gSmInproperKeyDistributionField_c = 0x040A,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnexpectedKeyType_c = 0x040B,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnexpectedKeyset_c = 0x040D,
	GATTServerErrorIndication_ProcedureError_Error_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnknownSmpPacketType_c = 0x040F,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTServerErrorIndication_ProcedureError_Error_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTServerErrorIndication_ProcedureError_Error_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTServerErrorIndication_ProcedureError_Error_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTServerErrorIndication_ProcedureError_Error_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTServerErrorIndication_ProcedureError_Error_gSmInvalidHciEventParameter_c = 0x0416,
	GATTServerErrorIndication_ProcedureError_Error_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTServerErrorIndication_ProcedureError_Error_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTServerErrorIndication_ProcedureError_Error_gSmInsufficientResources_c = 0x0419,
	GATTServerErrorIndication_ProcedureError_Error_gSmOobDataAddressMismatch_c = 0x041A,
	GATTServerErrorIndication_ProcedureError_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTServerErrorIndication_ProcedureError_Error_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTServerErrorIndication_ProcedureError_Error_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTServerErrorIndication_ProcedureError_Error_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTServerErrorIndication_ProcedureError_Error_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTServerErrorIndication_ProcedureError_Error_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTServerErrorIndication_ProcedureError_Error_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTServerErrorIndication_ProcedureError_Error_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTServerErrorIndication_ProcedureError_Error_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTServerErrorIndication_ProcedureError_Error_gSmTbInvalidDataSignature_c = 0x0461,
	GATTServerErrorIndication_ProcedureError_Error_gAttInvalidHandle_c = 0x0501,
	GATTServerErrorIndication_ProcedureError_Error_gAttReadNotPermitted_c = 0x0502,
	GATTServerErrorIndication_ProcedureError_Error_gAttWriteNotPermitted_c = 0x0503,
	GATTServerErrorIndication_ProcedureError_Error_gAttInvalidPdu_c = 0x0504,
	GATTServerErrorIndication_ProcedureError_Error_gAttInsufficientAuthentication_c = 0x0505,
	GATTServerErrorIndication_ProcedureError_Error_gAttRequestNotSupported_c = 0x0506,
	GATTServerErrorIndication_ProcedureError_Error_gAttInvalidOffset_c = 0x0507,
	GATTServerErrorIndication_ProcedureError_Error_gAttInsufficientAuthorization_c = 0x0508,
	GATTServerErrorIndication_ProcedureError_Error_gAttPrepareQueueFull_c = 0x0509,
	GATTServerErrorIndication_ProcedureError_Error_gAttAttributeNotFound_c = 0x050A,
	GATTServerErrorIndication_ProcedureError_Error_gAttAttributeNotLong_c = 0x050B,
	GATTServerErrorIndication_ProcedureError_Error_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTServerErrorIndication_ProcedureError_Error_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTServerErrorIndication_ProcedureError_Error_gAttUnlikelyor_c = 0x050E,
	GATTServerErrorIndication_ProcedureError_Error_gAttInsufficientEncryption_c = 0x050F,
	GATTServerErrorIndication_ProcedureError_Error_gAttUnsupportedGroupType_c = 0x0510,
	GATTServerErrorIndication_ProcedureError_Error_gAttInsufficientResources_c = 0x0511,
	GATTServerErrorIndication_ProcedureError_Error_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTServerErrorIndication_ProcedureError_Error_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTServerErrorIndication_ProcedureError_Error_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTServerErrorIndication_ProcedureError_Error_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTServerErrorIndication_ProcedureError_Error_gGattInvalidValueLength_c = 0x0605,
	GATTServerErrorIndication_ProcedureError_Error_gGattServerTimeout_c = 0x0606,
	GATTServerErrorIndication_ProcedureError_Error_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTServerErrorIndication_ProcedureError_Error_gGattClientConfirmationTimeout_c = 0x0608,
	GATTServerErrorIndication_ProcedureError_Error_gGapAdvDataTooLong_c = 0x0701,
	GATTServerErrorIndication_ProcedureError_Error_gGapScanRspDataTooLong_c = 0x0702,
	GATTServerErrorIndication_ProcedureError_Error_gGapDeviceNotBonded_c = 0x0703,
	GATTServerErrorIndication_ProcedureError_Error_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTServerErrorIndication_ProcedureError_Error_gDevDbCccdLimitReached_c = 0x0801,
	GATTServerErrorIndication_ProcedureError_Error_gDevDbCccdNotFound_c = 0x0802,
	GATTServerErrorIndication_ProcedureError_Error_gGattDbInvalidHandle_c = 0x0901,
	GATTServerErrorIndication_ProcedureError_Error_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTServerErrorIndication_ProcedureError_Error_gGattDbCccdNotFound_c = 0x0903,
	GATTServerErrorIndication_ProcedureError_Error_gGattDbServiceNotFound_c = 0x0904,
	GATTServerErrorIndication_ProcedureError_Error_gGattDbDescriptorNotFound_c = 0x0905
} GATTServerErrorIndication_ProcedureError_Error_t;

typedef PACKED_STRUCT GATTServerErrorIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	struct {
		GATTServerErrorIndication_ProcedureError_ProcedureType_t ProcedureType;  // Procedure that generated error
		GATTServerErrorIndication_ProcedureError_Error_t Error;  // Error generated
	} ProcedureError;  // Procedure error
} GATTServerErrorIndication_t;

typedef struct GATTServerLongCharacteristicWrittenIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	struct {
		uint16_t Handle;  // Handle of the characteristic value
		uint16_t ValueLength;  // Length of the characteristic value
		uint8_t *Value;  // Characteristic value array
	} LongCharacteristicWrittenEvent;  // Long characteristic written event
} GATTServerLongCharacteristicWrittenIndication_t;

typedef PACKED_STRUCT GATTServerAttributeReadIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the active connection
	uint16_t AttributeReadEvent_Handle;

} GATTServerAttributeReadIndication_t;

#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
/* The status of the GATT Database request */
typedef enum GATTDBConfirm_Status_tag {
	GATTDBConfirm_Status_gBleSuccess_c = 0x0000,
	GATTDBConfirm_Status_gBleInvalidParameter_c = 0x0001,
	GATTDBConfirm_Status_gBleOverflow_c = 0x0002,
	GATTDBConfirm_Status_gBleUnavailable_c = 0x0003,
	GATTDBConfirm_Status_gBleFeatureNotSupported_c = 0x0004,
	GATTDBConfirm_Status_gBleOutOfMemory_c = 0x0005,
	GATTDBConfirm_Status_gBleAlreadyInitialized_c = 0x0006,
	GATTDBConfirm_Status_gBleOsError_c = 0x0007,
	GATTDBConfirm_Status_gBleUnexpectedError_c = 0x0008,
	GATTDBConfirm_Status_gBleInvalidState_c = 0x0009,
	GATTDBConfirm_Status_gBleTimerError_c = 0x000A,
	GATTDBConfirm_Status_gHciUnknownHciCommand_c = 0x0101,
	GATTDBConfirm_Status_gHciUnknownConnectionIdentifier_c = 0x0102,
	GATTDBConfirm_Status_gHciHardwareFailure_c = 0x0103,
	GATTDBConfirm_Status_gHciPageTimeout_c = 0x0104,
	GATTDBConfirm_Status_gHciAuthenticationFailure_c = 0x0105,
	GATTDBConfirm_Status_gHciPinOrKeyMissing_c = 0x0106,
	GATTDBConfirm_Status_gHciMemoryCapacityExceeded_c = 0x0107,
	GATTDBConfirm_Status_gHciConnectionTimeout_c = 0x0108,
	GATTDBConfirm_Status_gHciConnectionLimitExceeded_c = 0x0109,
	GATTDBConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GATTDBConfirm_Status_gHciAclConnectionAlreadyExists_c = 0x010B,
	GATTDBConfirm_Status_gHciCommandDisallowed_c = 0x010C,
	GATTDBConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GATTDBConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GATTDBConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GATTDBConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GATTDBConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GATTDBConfirm_Status_gHciInvalidHciCommandParameters_c = 0x0112,
	GATTDBConfirm_Status_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GATTDBConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GATTDBConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GATTDBConfirm_Status_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GATTDBConfirm_Status_gHciRepeatedAttempts_c = 0x0117,
	GATTDBConfirm_Status_gHciPairingNotAllowed_c = 0x0118,
	GATTDBConfirm_Status_gHciUnknownLpmPdu_c = 0x0119,
	GATTDBConfirm_Status_gHciUnsupportedRemoteFeature_c = 0x011A,
	GATTDBConfirm_Status_gHciScoOffsetRejected_c = 0x011B,
	GATTDBConfirm_Status_gHciScoIntervalRejected_c = 0x011C,
	GATTDBConfirm_Status_gHciScoAirModeRejected_c = 0x011D,
	GATTDBConfirm_Status_gHciInvalidLpmParameters_c = 0x011E,
	GATTDBConfirm_Status_gHciUnspecifiedError_c = 0x011F,
	GATTDBConfirm_Status_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GATTDBConfirm_Status_gHciRoleChangeNotAllowed_c = 0x0121,
	GATTDBConfirm_Status_gHciLLResponseTimeout_c = 0x0122,
	GATTDBConfirm_Status_gHciLmpErrorTransactionCollision_c = 0x0123,
	GATTDBConfirm_Status_gHciLmpPduNotAllowed_c = 0x0124,
	GATTDBConfirm_Status_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GATTDBConfirm_Status_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GATTDBConfirm_Status_gHciRequestedQosNotSupported_c = 0x0127,
	GATTDBConfirm_Status_gHciInstantPassed_c = 0x0128,
	GATTDBConfirm_Status_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GATTDBConfirm_Status_gHciDifferentTransactionCollision_c = 0x012A,
	GATTDBConfirm_Status_gHciReserved_0x2B_c = 0x012B,
	GATTDBConfirm_Status_gHciQosNotAcceptableParameter_c = 0x012C,
	GATTDBConfirm_Status_gHciQosRejected_c = 0x012D,
	GATTDBConfirm_Status_gHciChannelClassificationNotSupported_c = 0x012E,
	GATTDBConfirm_Status_gHciInsufficientSecurity_c = 0x012F,
	GATTDBConfirm_Status_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GATTDBConfirm_Status_gHciReserved_0x31_c = 0x0131,
	GATTDBConfirm_Status_gHciRoleSwitchPending_c = 0x0132,
	GATTDBConfirm_Status_gHciReserved_0x33_c = 0x0133,
	GATTDBConfirm_Status_gHciReservedSlotViolation_c = 0x0134,
	GATTDBConfirm_Status_gHciRoleSwitchFailed_c = 0x0135,
	GATTDBConfirm_Status_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GATTDBConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GATTDBConfirm_Status_gHciHostBusyPairing_c = 0x0138,
	GATTDBConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GATTDBConfirm_Status_gHciControllerBusy_c = 0x013A,
	GATTDBConfirm_Status_gHciUnacceptableConnectionParameters_c = 0x013B,
	GATTDBConfirm_Status_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GATTDBConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GATTDBConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GATTDBConfirm_Status_gHciMacConnectionFailed_c = 0x013F,
	GATTDBConfirm_Status_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GATTDBConfirm_Status_gHciType0SubmapNotDefined_c = 0x0141,
	GATTDBConfirm_Status_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GATTDBConfirm_Status_gHciLimitReached_c = 0x0143,
	GATTDBConfirm_Status_gHciOperationCancelledByHost_c = 0x0144,
	GATTDBConfirm_Status_gHciAlreadyInit_c = 0x01A0,
	GATTDBConfirm_Status_gHciInvalidParameter_c = 0x01A1,
	GATTDBConfirm_Status_gHciCallbackNotInstalled_c = 0x01A2,
	GATTDBConfirm_Status_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GATTDBConfirm_Status_gHciCommandNotSupported_c = 0x01A4,
	GATTDBConfirm_Status_gHciEventNotSupported_c = 0x01A5,
	GATTDBConfirm_Status_gHciTransportError_c = 0x01A6,
	GATTDBConfirm_Status_gL2caAlreadyInit_c = 0x03F0,
	GATTDBConfirm_Status_gL2caInsufficientResources_c = 0x03F1,
	GATTDBConfirm_Status_gL2caCallbackNotInstalled_c = 0x03F2,
	GATTDBConfirm_Status_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GATTDBConfirm_Status_gL2caLePsmInvalid_c = 0x03F4,
	GATTDBConfirm_Status_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GATTDBConfirm_Status_gL2caLePsmNotRegistered_c = 0x03F6,
	GATTDBConfirm_Status_gL2caLePsmInsufficientResources_c = 0x03F7,
	GATTDBConfirm_Status_gL2caChannelInvalid_c = 0x03F8,
	GATTDBConfirm_Status_gL2caChannelClosed_c = 0x03F9,
	GATTDBConfirm_Status_gL2caChannelAlreadyConnected_c = 0x03FA,
	GATTDBConfirm_Status_gL2caConnectionParametersRejected_c = 0x03FB,
	GATTDBConfirm_Status_gL2caChannelBusy_c = 0x03FC,
	GATTDBConfirm_Status_gL2caInvalidParameter_c = 0x03FE,
	GATTDBConfirm_Status_gL2caError_c = 0x03FF,
	GATTDBConfirm_Status_gSmNullCBFunction_c = 0x0401,
	GATTDBConfirm_Status_gSmCommandNotSupported_c = 0x0402,
	GATTDBConfirm_Status_gSmUnexpectedCommand_c = 0x0403,
	GATTDBConfirm_Status_gSmInvalidCommandCode_c = 0x0404,
	GATTDBConfirm_Status_gSmInvalidCommandLength_c = 0x0405,
	GATTDBConfirm_Status_gSmInvalidCommandParameter_c = 0x0406,
	GATTDBConfirm_Status_gSmInvalidDeviceId_c = 0x0407,
	GATTDBConfirm_Status_gSmInvalidInternalOperation_c = 0x0408,
	GATTDBConfirm_Status_gSmInvalidConnectionHandle_c = 0x0409,
	GATTDBConfirm_Status_gSmInproperKeyDistributionField_c = 0x040A,
	GATTDBConfirm_Status_gSmUnexpectedKeyType_c = 0x040B,
	GATTDBConfirm_Status_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GATTDBConfirm_Status_gSmUnexpectedKeyset_c = 0x040D,
	GATTDBConfirm_Status_gSmSmpTimeoutOccurred_c = 0x040E,
	GATTDBConfirm_Status_gSmUnknownSmpPacketType_c = 0x040F,
	GATTDBConfirm_Status_gSmInvalidSmpPacketLength_c = 0x0410,
	GATTDBConfirm_Status_gSmInvalidSmpPacketParameter_c = 0x0411,
	GATTDBConfirm_Status_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GATTDBConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GATTDBConfirm_Status_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GATTDBConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GATTDBConfirm_Status_gSmInvalidHciEventParameter_c = 0x0416,
	GATTDBConfirm_Status_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GATTDBConfirm_Status_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GATTDBConfirm_Status_gSmInsufficientResources_c = 0x0419,
	GATTDBConfirm_Status_gSmOobDataAddressMismatch_c = 0x041A,
	GATTDBConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GATTDBConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GATTDBConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GATTDBConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GATTDBConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GATTDBConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GATTDBConfirm_Status_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GATTDBConfirm_Status_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GATTDBConfirm_Status_gSmPairingErrorInvalidParameters_c = 0x0434,
	GATTDBConfirm_Status_gSmPairingErrorUnknownReason_c = 0x0435,
	GATTDBConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GATTDBConfirm_Status_gSmTbInvalidDataSignature_c = 0x0461,
	GATTDBConfirm_Status_gAttInvalidHandle_c = 0x0501,
	GATTDBConfirm_Status_gAttReadNotPermitted_c = 0x0502,
	GATTDBConfirm_Status_gAttWriteNotPermitted_c = 0x0503,
	GATTDBConfirm_Status_gAttInvalidPdu_c = 0x0504,
	GATTDBConfirm_Status_gAttInsufficientAuthentication_c = 0x0505,
	GATTDBConfirm_Status_gAttRequestNotSupported_c = 0x0506,
	GATTDBConfirm_Status_gAttInvalidOffset_c = 0x0507,
	GATTDBConfirm_Status_gAttInsufficientAuthorization_c = 0x0508,
	GATTDBConfirm_Status_gAttPrepareQueueFull_c = 0x0509,
	GATTDBConfirm_Status_gAttAttributeNotFound_c = 0x050A,
	GATTDBConfirm_Status_gAttAttributeNotLong_c = 0x050B,
	GATTDBConfirm_Status_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GATTDBConfirm_Status_gAttInvalidAttributeValueLength_c = 0x050D,
	GATTDBConfirm_Status_gAttUnlikelyor_c = 0x050E,
	GATTDBConfirm_Status_gAttInsufficientEncryption_c = 0x050F,
	GATTDBConfirm_Status_gAttUnsupportedGroupType_c = 0x0510,
	GATTDBConfirm_Status_gAttInsufficientResources_c = 0x0511,
	GATTDBConfirm_Status_gGattAnotherProcedureInProgress_c = 0x0601,
	GATTDBConfirm_Status_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GATTDBConfirm_Status_gGattMultipleAttributesOverflow_c = 0x0603,
	GATTDBConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GATTDBConfirm_Status_gGattInvalidValueLength_c = 0x0605,
	GATTDBConfirm_Status_gGattServerTimeout_c = 0x0606,
	GATTDBConfirm_Status_gGattIndicationAlreadyInProgress_c = 0x0607,
	GATTDBConfirm_Status_gGattClientConfirmationTimeout_c = 0x0608,
	GATTDBConfirm_Status_gGapAdvDataTooLong_c = 0x0701,
	GATTDBConfirm_Status_gGapScanRspDataTooLong_c = 0x0702,
	GATTDBConfirm_Status_gGapDeviceNotBonded_c = 0x0703,
	GATTDBConfirm_Status_gGapAnotherProcedureInProgress_c = 0x0704,
	GATTDBConfirm_Status_gDevDbCccdLimitReached_c = 0x0801,
	GATTDBConfirm_Status_gDevDbCccdNotFound_c = 0x0802,
	GATTDBConfirm_Status_gGattDbInvalidHandle_c = 0x0901,
	GATTDBConfirm_Status_gGattDbCharacteristicNotFound_c = 0x0902,
	GATTDBConfirm_Status_gGattDbCccdNotFound_c = 0x0903,
	GATTDBConfirm_Status_gGattDbServiceNotFound_c = 0x0904,
	GATTDBConfirm_Status_gGattDbDescriptorNotFound_c = 0x0905
} GATTDBConfirm_Status_t;

typedef PACKED_STRUCT GATTDBConfirm_tag {
	GATTDBConfirm_Status_t Status;  // The status of the GATT Database request
} GATTDBConfirm_t;

typedef struct GATTDBReadAttributeIndication_tag {
	uint16_t ValueLength;  // Attribute value length
	uint8_t *Value;  // Attribute value
} GATTDBReadAttributeIndication_t;

typedef PACKED_STRUCT GATTDBFindServiceHandleIndication_tag {
	uint16_t ServiceHandle;  // Service handle
} GATTDBFindServiceHandleIndication_t;

typedef PACKED_STRUCT GATTDBFindCharValueHandleInServiceIndication_tag {
	uint16_t CharValueHandle;  // Characteristic value handle
} GATTDBFindCharValueHandleInServiceIndication_t;

typedef PACKED_STRUCT GATTDBFindCccdHandleForCharValueHandleIndication_tag {
	uint16_t CccdHandle;  // CCCD handle
} GATTDBFindCccdHandleForCharValueHandleIndication_t;

typedef PACKED_STRUCT GATTDBFindDescriptorHandleForCharValueHandleIndication_tag {
	uint16_t DescriptorHandle;  // Descriptor handle
} GATTDBFindDescriptorHandleForCharValueHandleIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddPrimaryServiceDeclarationIndication_tag {
	uint16_t ServiceHandle;  // Handle of the Service declaration
} GATTDBDynamicAddPrimaryServiceDeclarationIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddSecondaryServiceDeclarationIndication_tag {
	uint16_t ServiceHandle;  // Handle of the Service declaration
} GATTDBDynamicAddSecondaryServiceDeclarationIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddIncludeDeclarationIndication_tag {
	uint16_t IncludeHandle;  // Handle of the Include declaration
} GATTDBDynamicAddIncludeDeclarationIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_tag {
	uint16_t CharacteristicHandle;  // Handle of the Characteristic declaration
} GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddCharacteristicDescriptorIndication_tag {
	uint16_t DescriptorHandle;  // Handle of the Descriptor declaration
} GATTDBDynamicAddCharacteristicDescriptorIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddCccdIndication_tag {
	uint16_t CCCDHandle;  // Handle of the CCCD declaration
} GATTDBDynamicAddCccdIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_tag {
	uint16_t CharacteristicHandle;  // Handle of the Characteristic declaration
} GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_t;

typedef PACKED_STRUCT GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_tag {
	uint16_t DescriptorHandle;  // Handle of the Descriptor declaration
} GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_t;

#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
/* The status of the GAP request */
typedef enum GAPConfirm_Status_tag {
	GAPConfirm_Status_gBleSuccess_c = 0x0000,
	GAPConfirm_Status_gBleInvalidParameter_c = 0x0001,
	GAPConfirm_Status_gBleOverflow_c = 0x0002,
	GAPConfirm_Status_gBleUnavailable_c = 0x0003,
	GAPConfirm_Status_gBleFeatureNotSupported_c = 0x0004,
	GAPConfirm_Status_gBleOutOfMemory_c = 0x0005,
	GAPConfirm_Status_gBleAlreadyInitialized_c = 0x0006,
	GAPConfirm_Status_gBleOsError_c = 0x0007,
	GAPConfirm_Status_gBleUnexpectedError_c = 0x0008,
	GAPConfirm_Status_gBleInvalidState_c = 0x0009,
	GAPConfirm_Status_gBleTimerError_c = 0x000A,
	GAPConfirm_Status_gHciUnknownHciCommand_c = 0x0101,
	GAPConfirm_Status_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConfirm_Status_gHciHardwareFailure_c = 0x0103,
	GAPConfirm_Status_gHciPageTimeout_c = 0x0104,
	GAPConfirm_Status_gHciAuthenticationFailure_c = 0x0105,
	GAPConfirm_Status_gHciPinOrKeyMissing_c = 0x0106,
	GAPConfirm_Status_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConfirm_Status_gHciConnectionTimeout_c = 0x0108,
	GAPConfirm_Status_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConfirm_Status_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConfirm_Status_gHciCommandDisallowed_c = 0x010C,
	GAPConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConfirm_Status_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConfirm_Status_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConfirm_Status_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConfirm_Status_gHciRepeatedAttempts_c = 0x0117,
	GAPConfirm_Status_gHciPairingNotAllowed_c = 0x0118,
	GAPConfirm_Status_gHciUnknownLpmPdu_c = 0x0119,
	GAPConfirm_Status_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConfirm_Status_gHciScoOffsetRejected_c = 0x011B,
	GAPConfirm_Status_gHciScoIntervalRejected_c = 0x011C,
	GAPConfirm_Status_gHciScoAirModeRejected_c = 0x011D,
	GAPConfirm_Status_gHciInvalidLpmParameters_c = 0x011E,
	GAPConfirm_Status_gHciUnspecifiedError_c = 0x011F,
	GAPConfirm_Status_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConfirm_Status_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConfirm_Status_gHciLLResponseTimeout_c = 0x0122,
	GAPConfirm_Status_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConfirm_Status_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConfirm_Status_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConfirm_Status_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConfirm_Status_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConfirm_Status_gHciInstantPassed_c = 0x0128,
	GAPConfirm_Status_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConfirm_Status_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConfirm_Status_gHciReserved_0x2B_c = 0x012B,
	GAPConfirm_Status_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConfirm_Status_gHciQosRejected_c = 0x012D,
	GAPConfirm_Status_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConfirm_Status_gHciInsufficientSecurity_c = 0x012F,
	GAPConfirm_Status_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConfirm_Status_gHciReserved_0x31_c = 0x0131,
	GAPConfirm_Status_gHciRoleSwitchPending_c = 0x0132,
	GAPConfirm_Status_gHciReserved_0x33_c = 0x0133,
	GAPConfirm_Status_gHciReservedSlotViolation_c = 0x0134,
	GAPConfirm_Status_gHciRoleSwitchFailed_c = 0x0135,
	GAPConfirm_Status_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConfirm_Status_gHciHostBusyPairing_c = 0x0138,
	GAPConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConfirm_Status_gHciControllerBusy_c = 0x013A,
	GAPConfirm_Status_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConfirm_Status_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConfirm_Status_gHciMacConnectionFailed_c = 0x013F,
	GAPConfirm_Status_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConfirm_Status_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConfirm_Status_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConfirm_Status_gHciLimitReached_c = 0x0143,
	GAPConfirm_Status_gHciOperationCancelledByHost_c = 0x0144,
	GAPConfirm_Status_gHciAlreadyInit_c = 0x01A0,
	GAPConfirm_Status_gHciInvalidParameter_c = 0x01A1,
	GAPConfirm_Status_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConfirm_Status_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConfirm_Status_gHciCommandNotSupported_c = 0x01A4,
	GAPConfirm_Status_gHciEventNotSupported_c = 0x01A5,
	GAPConfirm_Status_gHciTransportError_c = 0x01A6,
	GAPConfirm_Status_gL2caAlreadyInit_c = 0x03F0,
	GAPConfirm_Status_gL2caInsufficientResources_c = 0x03F1,
	GAPConfirm_Status_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConfirm_Status_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConfirm_Status_gL2caLePsmInvalid_c = 0x03F4,
	GAPConfirm_Status_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConfirm_Status_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConfirm_Status_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConfirm_Status_gL2caChannelInvalid_c = 0x03F8,
	GAPConfirm_Status_gL2caChannelClosed_c = 0x03F9,
	GAPConfirm_Status_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConfirm_Status_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConfirm_Status_gL2caChannelBusy_c = 0x03FC,
	GAPConfirm_Status_gL2caInvalidParameter_c = 0x03FE,
	GAPConfirm_Status_gL2caError_c = 0x03FF,
	GAPConfirm_Status_gSmNullCBFunction_c = 0x0401,
	GAPConfirm_Status_gSmCommandNotSupported_c = 0x0402,
	GAPConfirm_Status_gSmUnexpectedCommand_c = 0x0403,
	GAPConfirm_Status_gSmInvalidCommandCode_c = 0x0404,
	GAPConfirm_Status_gSmInvalidCommandLength_c = 0x0405,
	GAPConfirm_Status_gSmInvalidCommandParameter_c = 0x0406,
	GAPConfirm_Status_gSmInvalidDeviceId_c = 0x0407,
	GAPConfirm_Status_gSmInvalidInternalOperation_c = 0x0408,
	GAPConfirm_Status_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConfirm_Status_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConfirm_Status_gSmUnexpectedKeyType_c = 0x040B,
	GAPConfirm_Status_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConfirm_Status_gSmUnexpectedKeyset_c = 0x040D,
	GAPConfirm_Status_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConfirm_Status_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConfirm_Status_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConfirm_Status_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConfirm_Status_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConfirm_Status_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConfirm_Status_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConfirm_Status_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConfirm_Status_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConfirm_Status_gSmInsufficientResources_c = 0x0419,
	GAPConfirm_Status_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConfirm_Status_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConfirm_Status_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConfirm_Status_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConfirm_Status_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConfirm_Status_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConfirm_Status_gAttInvalidHandle_c = 0x0501,
	GAPConfirm_Status_gAttReadNotPermitted_c = 0x0502,
	GAPConfirm_Status_gAttWriteNotPermitted_c = 0x0503,
	GAPConfirm_Status_gAttInvalidPdu_c = 0x0504,
	GAPConfirm_Status_gAttInsufficientAuthentication_c = 0x0505,
	GAPConfirm_Status_gAttRequestNotSupported_c = 0x0506,
	GAPConfirm_Status_gAttInvalidOffset_c = 0x0507,
	GAPConfirm_Status_gAttInsufficientAuthorization_c = 0x0508,
	GAPConfirm_Status_gAttPrepareQueueFull_c = 0x0509,
	GAPConfirm_Status_gAttAttributeNotFound_c = 0x050A,
	GAPConfirm_Status_gAttAttributeNotLong_c = 0x050B,
	GAPConfirm_Status_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConfirm_Status_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConfirm_Status_gAttUnlikelyor_c = 0x050E,
	GAPConfirm_Status_gAttInsufficientEncryption_c = 0x050F,
	GAPConfirm_Status_gAttUnsupportedGroupType_c = 0x0510,
	GAPConfirm_Status_gAttInsufficientResources_c = 0x0511,
	GAPConfirm_Status_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConfirm_Status_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConfirm_Status_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConfirm_Status_gGattInvalidValueLength_c = 0x0605,
	GAPConfirm_Status_gGattServerTimeout_c = 0x0606,
	GAPConfirm_Status_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConfirm_Status_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConfirm_Status_gGapAdvDataTooLong_c = 0x0701,
	GAPConfirm_Status_gGapScanRspDataTooLong_c = 0x0702,
	GAPConfirm_Status_gGapDeviceNotBonded_c = 0x0703,
	GAPConfirm_Status_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConfirm_Status_gDevDbCccdLimitReached_c = 0x0801,
	GAPConfirm_Status_gDevDbCccdNotFound_c = 0x0802,
	GAPConfirm_Status_gGattDbInvalidHandle_c = 0x0901,
	GAPConfirm_Status_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConfirm_Status_gGattDbCccdNotFound_c = 0x0903,
	GAPConfirm_Status_gGattDbServiceNotFound_c = 0x0904,
	GAPConfirm_Status_gGattDbDescriptorNotFound_c = 0x0905
} GAPConfirm_Status_t;

typedef PACKED_STRUCT GAPConfirm_tag {
	GAPConfirm_Status_t Status;  // The status of the GAP request
} GAPConfirm_t;

typedef PACKED_STRUCT GAPCheckNotificationStatusIndication_tag {
	bool_t IsActive;  // Notification status
} GAPCheckNotificationStatusIndication_t;

typedef PACKED_STRUCT GAPCheckIndicationStatusIndication_tag {
	bool_t IsActive;  // Indication status
} GAPCheckIndicationStatusIndication_t;

/* Public or Random address */
typedef enum GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_tag {
	GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_gPublic_c = 0x00,
	GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_gRandom_c = 0x01
} GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_t;

/* Mask identifying the keys stored */
typedef enum GAPLoadKeysIndication_KeyFlags_tag {
	GAPLoadKeysIndication_KeyFlags_gNoKeys_c = 0x00,
	GAPLoadKeysIndication_KeyFlags_gLtk_c = 0x01,
	GAPLoadKeysIndication_KeyFlags_gIrk_c = 0x02,
	GAPLoadKeysIndication_KeyFlags_gCsrk_c = 0x04
} GAPLoadKeysIndication_KeyFlags_t;

typedef struct GAPLoadKeysIndication_tag {
	struct {
		bool_t LtkIncluded;  // Boolean value which indicates if LTK size and LTK are included or not
		struct {
			uint8_t LtkSize;  // Encryption Key Size
			uint8_t *Ltk;  // Long Term (Encryption) Key
		} LtkInfo;  // LTK information (size and value)
		bool_t IrkIncluded;  // Boolean value which indicates if IRK is included or not
		uint8_t Irk[16];  // Identity Resolving Key
		bool_t CsrkIncluded;  // Boolean value which indicates if CSRK is included or not
		uint8_t Csrk[16];  // Connection Signature Resolving Key
		struct {
			uint8_t RandSize;  // Random value size
			uint8_t *Rand;  // Random value used to identify the LTK
			uint16_t Ediv;  // EDIV value used to identify the LTK
		} RandEdivInfo;  // Rand information (size and value) and Ediv
		bool_t AddressIncluded;  // Boolean value which indicates if Address is included or not
		struct {
			GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_t DeviceAddressType;  // Public or Random address
			uint8_t DeviceAddress[6];  // Device Address
		} AddressInfo;  // Address information (type and value)
	} Keys;  // The SMP keys distributed by the peer
	GAPLoadKeysIndication_KeyFlags_t KeyFlags;  // Mask identifying the keys stored
	bool_t LeSc;  // LE SC pairing
	bool_t Authenticated;  // Peer is authenticated during pairing
} GAPLoadKeysIndication_t;

typedef struct GAPLoadEncryptionInformationIndication_tag {
	uint8_t LtkSize;  // LTK size
	uint8_t *Ltk;  // LTK value
} GAPLoadEncryptionInformationIndication_t;

typedef struct GAPLoadCustomPeerInformationIndication_tag {
	uint16_t InfoSize;  // Data size
	uint8_t *Info;  // Data value
} GAPLoadCustomPeerInformationIndication_t;

typedef PACKED_STRUCT GAPCheckIfBondedIndication_tag {
	bool_t IsBonded;  // Bonded flag
} GAPCheckIfBondedIndication_t;

typedef PACKED_STRUCT GAPGetBondedDevicesCountIndication_tag {
	uint8_t NbOfBondedDevices;  // Number of bonded devices
} GAPGetBondedDevicesCountIndication_t;

typedef struct GAPGetBondedDeviceNameIndication_tag {
	uint8_t NameSize;  // The name size
	uint8_t *Name;  // The name value
} GAPGetBondedDeviceNameIndication_t;

typedef PACKED_STRUCT GAPGenericEventInitializationCompleteIndication_tag {
	uint32_t SupportedFeatures;  // local supported features
	uint16_t MaxAdvDataSize;  // The maximum length of data supported by the Controller for use as advertisement data or scan response data in an advertising event or as periodic advertisement data
	uint8_t NumOfSupportedAdvSets;  // number of supported advertising sets
	uint8_t PeriodicAdvListSize;  // periodic advertiser list size
} GAPGenericEventInitializationCompleteIndication_t;

/* Error code */
typedef enum GAPGenericEventInternalErrorIndication_ErrorCode_tag {
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleSuccess_c = 0x0000,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleInvalidParameter_c = 0x0001,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleOverflow_c = 0x0002,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleUnavailable_c = 0x0003,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleFeatureNotSupported_c = 0x0004,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleOutOfMemory_c = 0x0005,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleAlreadyInitialized_c = 0x0006,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleOsError_c = 0x0007,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleUnexpectedError_c = 0x0008,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleInvalidState_c = 0x0009,
	GAPGenericEventInternalErrorIndication_ErrorCode_gBleTimerError_c = 0x000A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownHciCommand_c = 0x0101,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciHardwareFailure_c = 0x0103,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciPageTimeout_c = 0x0104,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciAuthenticationFailure_c = 0x0105,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciPinOrKeyMissing_c = 0x0106,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTimeout_c = 0x0108,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionLimitExceeded_c = 0x0109,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciCommandDisallowed_c = 0x010C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRepeatedAttempts_c = 0x0117,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciPairingNotAllowed_c = 0x0118,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownLpmPdu_c = 0x0119,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoOffsetRejected_c = 0x011B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoIntervalRejected_c = 0x011C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoAirModeRejected_c = 0x011D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidLpmParameters_c = 0x011E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnspecifiedError_c = 0x011F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciLLResponseTimeout_c = 0x0122,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciLmpPduNotAllowed_c = 0x0124,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRequestedQosNotSupported_c = 0x0127,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciInstantPassed_c = 0x0128,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciDifferentTransactionCollision_c = 0x012A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x2B_c = 0x012B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciQosRejected_c = 0x012D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciInsufficientSecurity_c = 0x012F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x31_c = 0x0131,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleSwitchPending_c = 0x0132,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x33_c = 0x0133,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciReservedSlotViolation_c = 0x0134,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleSwitchFailed_c = 0x0135,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciHostBusyPairing_c = 0x0138,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciControllerBusy_c = 0x013A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciMacConnectionFailed_c = 0x013F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciType0SubmapNotDefined_c = 0x0141,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciLimitReached_c = 0x0143,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciOperationCancelledByHost_c = 0x0144,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciAlreadyInit_c = 0x01A0,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidParameter_c = 0x01A1,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciCallbackNotInstalled_c = 0x01A2,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciCommandNotSupported_c = 0x01A4,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciEventNotSupported_c = 0x01A5,
	GAPGenericEventInternalErrorIndication_ErrorCode_gHciTransportError_c = 0x01A6,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caAlreadyInit_c = 0x03F0,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caInsufficientResources_c = 0x03F1,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmInvalid_c = 0x03F4,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelInvalid_c = 0x03F8,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelClosed_c = 0x03F9,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelBusy_c = 0x03FC,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caInvalidParameter_c = 0x03FE,
	GAPGenericEventInternalErrorIndication_ErrorCode_gL2caError_c = 0x03FF,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmNullCBFunction_c = 0x0401,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmCommandNotSupported_c = 0x0402,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedCommand_c = 0x0403,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandCode_c = 0x0404,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandLength_c = 0x0405,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandParameter_c = 0x0406,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidDeviceId_c = 0x0407,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidInternalOperation_c = 0x0408,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidConnectionHandle_c = 0x0409,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInproperKeyDistributionField_c = 0x040A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedKeyType_c = 0x040B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedKeyset_c = 0x040D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnknownSmpPacketType_c = 0x040F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidHciEventParameter_c = 0x0416,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmInsufficientResources_c = 0x0419,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmOobDataAddressMismatch_c = 0x041A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPGenericEventInternalErrorIndication_ErrorCode_gSmTbInvalidDataSignature_c = 0x0461,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidHandle_c = 0x0501,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttReadNotPermitted_c = 0x0502,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttWriteNotPermitted_c = 0x0503,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidPdu_c = 0x0504,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientAuthentication_c = 0x0505,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttRequestNotSupported_c = 0x0506,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidOffset_c = 0x0507,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientAuthorization_c = 0x0508,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttPrepareQueueFull_c = 0x0509,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttAttributeNotFound_c = 0x050A,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttAttributeNotLong_c = 0x050B,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttUnlikelyor_c = 0x050E,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientEncryption_c = 0x050F,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttUnsupportedGroupType_c = 0x0510,
	GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientResources_c = 0x0511,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattInvalidValueLength_c = 0x0605,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattServerTimeout_c = 0x0606,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattClientConfirmationTimeout_c = 0x0608,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGapAdvDataTooLong_c = 0x0701,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGapScanRspDataTooLong_c = 0x0702,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGapDeviceNotBonded_c = 0x0703,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPGenericEventInternalErrorIndication_ErrorCode_gDevDbCccdLimitReached_c = 0x0801,
	GAPGenericEventInternalErrorIndication_ErrorCode_gDevDbCccdNotFound_c = 0x0802,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbInvalidHandle_c = 0x0901,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbCccdNotFound_c = 0x0903,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbServiceNotFound_c = 0x0904,
	GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbDescriptorNotFound_c = 0x0905
} GAPGenericEventInternalErrorIndication_ErrorCode_t;

/* Error source */
typedef enum GAPGenericEventInternalErrorIndication_ErrorSource_tag {
	GAPGenericEventInternalErrorIndication_ErrorSource_gHciCommandStatus_c = 0x00,
	GAPGenericEventInternalErrorIndication_ErrorSource_gCheckPrivateResolvableAddress_c = 0x01,
	GAPGenericEventInternalErrorIndication_ErrorSource_gVerifySignature_c = 0x02,
	GAPGenericEventInternalErrorIndication_ErrorSource_gAddNewConnection_c = 0x03,
	GAPGenericEventInternalErrorIndication_ErrorSource_gResetController_c = 0x04,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSetEventMask_c = 0x05,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadLeBufferSize_c = 0x06,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSetLeEventMask_c = 0x07,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadDeviceAddress_c = 0x08,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadLocalSupportedFeatures_c = 0x09,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadWhiteListSize_c = 0x0A,
	GAPGenericEventInternalErrorIndication_ErrorSource_gClearWhiteList_c = 0x0B,
	GAPGenericEventInternalErrorIndication_ErrorSource_gAddDeviceToWhiteList_c = 0x0C,
	GAPGenericEventInternalErrorIndication_ErrorSource_gRemoveDeviceFromWhiteList_c = 0x0D,
	GAPGenericEventInternalErrorIndication_ErrorSource_gCancelCreateConnection_c = 0x0E,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadRadioPower_c = 0x0F,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSetRandomAddress_c = 0x10,
	GAPGenericEventInternalErrorIndication_ErrorSource_gCreateRandomAddress_c = 0x11,
	GAPGenericEventInternalErrorIndication_ErrorSource_gEncryptLink_c = 0x12,
	GAPGenericEventInternalErrorIndication_ErrorSource_gProvideLongTermKey_c = 0x13,
	GAPGenericEventInternalErrorIndication_ErrorSource_gDenyLongTermKey_c = 0x14,
	GAPGenericEventInternalErrorIndication_ErrorSource_gConnect_c = 0x15,
	GAPGenericEventInternalErrorIndication_ErrorSource_gDisconnect_c = 0x16,
	GAPGenericEventInternalErrorIndication_ErrorSource_gTerminatePairing_c = 0x17,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSendSlaveSecurityRequest_c = 0x18,
	GAPGenericEventInternalErrorIndication_ErrorSource_gEnterPasskey_c = 0x19,
	GAPGenericEventInternalErrorIndication_ErrorSource_gProvideOob_c = 0x1A,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSendSmpKeys_c = 0x1B,
	GAPGenericEventInternalErrorIndication_ErrorSource_gWriteSuggestedDefaultDataLength_c = 0x1C,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadSuggestedDefaultDataLength_c = 0x1D,
	GAPGenericEventInternalErrorIndication_ErrorSource_gUpdateLeDataLength_c = 0x1E,
	GAPGenericEventInternalErrorIndication_ErrorSource_gEnableHostPrivacy_c = 0x1F,
	GAPGenericEventInternalErrorIndication_ErrorSource_gEnableControllerPrivacy_c = 0x20,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeScSendKeypressNotification_c = 0x21,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeScSetPeerOobData_c = 0x22,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeScGetLocalOobData_c = 0x23,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeScValidateNumericValue_c = 0x24,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeScRegeneratePublicKey_c = 0x25,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeSetResolvablePrivateAddressTimeout_c = 0x26,
	GAPGenericEventInternalErrorIndication_ErrorSource_gDefaultPairingProcedure_c = 0x27,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeControllerTest_c = 0x28,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadPhy_c = 0x29,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeSetPhy_c = 0x2A,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSaveKeys_c = 0x2B,
	GAPGenericEventInternalErrorIndication_ErrorSource_gSetChannelMap_c = 0x2C,
	GAPGenericEventInternalErrorIndication_ErrorSource_gReadLocalSupportedCommands_c = 0x2D,
	GAPGenericEventInternalErrorIndication_ErrorSource_gEnableLdmTimer_c = 0x2E,
	GAPGenericEventInternalErrorIndication_ErrorSource_gRemoveAdvertisingSet_c = 0x2F,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLePeriodicAdvSyncEstb_c = 0x30,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLePeriodicAdvSyncLost_c = 0x31,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeRemoveDeviceFromPeriodicAdvList_c = 0x32,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeClearPeriodicAdvList_c = 0x33,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeAddDeviceToPeriodicAdvList_c = 0x34,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadNumOfSupportedAdvSets_c = 0x35,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadPeriodicAdvListSize_c = 0x36,
	GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadMaxAdvDataLen_c = 0x37,
	GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvCreateSync = 0x38,
	GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvCancelSync = 0x39,
	GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvTerminateSync = 0x3A
} GAPGenericEventInternalErrorIndication_ErrorSource_t;

typedef PACKED_STRUCT GAPGenericEventInternalErrorIndication_tag {
	GAPGenericEventInternalErrorIndication_ErrorCode_t ErrorCode;  // Error code
	GAPGenericEventInternalErrorIndication_ErrorSource_t ErrorSource;  // Error source
	uint16_t HciCommandOpcode;  // HCI command operation code
} GAPGenericEventInternalErrorIndication_t;

/* Setup fail reason */
typedef enum GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_tag {
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleSuccess_c = 0x0000,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleInvalidParameter_c = 0x0001,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOverflow_c = 0x0002,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleUnavailable_c = 0x0003,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOutOfMemory_c = 0x0005,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOsError_c = 0x0007,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleUnexpectedError_c = 0x0008,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleInvalidState_c = 0x0009,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleTimerError_c = 0x000A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciHardwareFailure_c = 0x0103,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPageTimeout_c = 0x0104,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTimeout_c = 0x0108,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCommandDisallowed_c = 0x010C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnspecifiedError_c = 0x011F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInstantPassed_c = 0x0128,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x2B_c = 0x012B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciQosRejected_c = 0x012D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x31_c = 0x0131,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x33_c = 0x0133,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciHostBusyPairing_c = 0x0138,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciControllerBusy_c = 0x013A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLimitReached_c = 0x0143,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAlreadyInit_c = 0x01A0,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidParameter_c = 0x01A1,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciEventNotSupported_c = 0x01A5,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciTransportError_c = 0x01A6,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelClosed_c = 0x03F9,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelBusy_c = 0x03FC,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caError_c = 0x03FF,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmNullCBFunction_c = 0x0401,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmCommandNotSupported_c = 0x0402,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInsufficientResources_c = 0x0419,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidHandle_c = 0x0501,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttReadNotPermitted_c = 0x0502,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidPdu_c = 0x0504,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttRequestNotSupported_c = 0x0506,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidOffset_c = 0x0507,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttAttributeNotFound_c = 0x050A,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttAttributeNotLong_c = 0x050B,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttUnlikelyor_c = 0x050E,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientResources_c = 0x0511,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattInvalidValueLength_c = 0x0605,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattServerTimeout_c = 0x0606,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_t;

typedef PACKED_STRUCT GAPGenericEventAdvertisingSetupFailedIndication_tag {
	GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_t SetupFailReason;  // Setup fail reason
} GAPGenericEventAdvertisingSetupFailedIndication_t;

typedef PACKED_STRUCT GAPGenericEventAdvertisingParametersSetupCompleteIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventAdvertisingParametersSetupCompleteIndication_t;

typedef PACKED_STRUCT GAPGenericEventAdvertisingDataSetupCompleteIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventAdvertisingDataSetupCompleteIndication_t;

typedef PACKED_STRUCT GAPGenericEventWhiteListSizeReadIndication_tag {
	uint8_t WhiteListSize;  // White list size
} GAPGenericEventWhiteListSizeReadIndication_t;

typedef PACKED_STRUCT GAPGenericEventDeviceAddedToWhiteListIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventDeviceAddedToWhiteListIndication_t;

typedef PACKED_STRUCT GAPGenericEventDeviceRemovedFromWhiteListIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventDeviceRemovedFromWhiteListIndication_t;

typedef PACKED_STRUCT GAPGenericEventWhiteListClearedIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventWhiteListClearedIndication_t;

typedef PACKED_STRUCT GAPGenericEventRandomAddressReadyIndication_tag {
	uint8_t Address[6];  // Random address
} GAPGenericEventRandomAddressReadyIndication_t;

typedef PACKED_STRUCT GAPGenericEventCreateConnectionCanceledIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventCreateConnectionCanceledIndication_t;

typedef PACKED_STRUCT GAPGenericEventPublicAddressReadIndication_tag {
	uint8_t Address[6];  // Public address
} GAPGenericEventPublicAddressReadIndication_t;

typedef PACKED_STRUCT GAPGenericEventAdvTxPowerLevelReadIndication_tag {
	uint8_t AdvTxPowerLevel;  // Advertising transmission power level (in dBm)
} GAPGenericEventAdvTxPowerLevelReadIndication_t;

typedef PACKED_STRUCT GAPGenericEventPrivateResolvableAddressVerifiedIndication_tag {
	bool_t Verified;  // Private Resolvable Address verified
} GAPGenericEventPrivateResolvableAddressVerifiedIndication_t;

typedef PACKED_STRUCT GAPGenericEventRandomAddressSetIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventRandomAddressSetIndication_t;

typedef PACKED_STRUCT GAPAdvertisingEventStateChangedIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPAdvertisingEventStateChangedIndication_t;

/* The reason of failure */
typedef enum GAPAdvertisingEventCommandFailedIndication_FailReason_tag {
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleSuccess_c = 0x0000,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleInvalidParameter_c = 0x0001,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOverflow_c = 0x0002,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleUnavailable_c = 0x0003,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOutOfMemory_c = 0x0005,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOsError_c = 0x0007,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleUnexpectedError_c = 0x0008,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleInvalidState_c = 0x0009,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gBleTimerError_c = 0x000A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciHardwareFailure_c = 0x0103,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPageTimeout_c = 0x0104,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTimeout_c = 0x0108,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCommandDisallowed_c = 0x010C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnspecifiedError_c = 0x011F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInstantPassed_c = 0x0128,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x2B_c = 0x012B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciQosRejected_c = 0x012D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x31_c = 0x0131,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x33_c = 0x0133,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciHostBusyPairing_c = 0x0138,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciControllerBusy_c = 0x013A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLimitReached_c = 0x0143,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAlreadyInit_c = 0x01A0,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidParameter_c = 0x01A1,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciEventNotSupported_c = 0x01A5,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gHciTransportError_c = 0x01A6,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelClosed_c = 0x03F9,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelBusy_c = 0x03FC,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caError_c = 0x03FF,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmNullCBFunction_c = 0x0401,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmCommandNotSupported_c = 0x0402,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInsufficientResources_c = 0x0419,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidHandle_c = 0x0501,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttReadNotPermitted_c = 0x0502,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidPdu_c = 0x0504,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttRequestNotSupported_c = 0x0506,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidOffset_c = 0x0507,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttAttributeNotFound_c = 0x050A,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttAttributeNotLong_c = 0x050B,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttUnlikelyor_c = 0x050E,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientResources_c = 0x0511,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattInvalidValueLength_c = 0x0605,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattServerTimeout_c = 0x0606,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPAdvertisingEventCommandFailedIndication_FailReason_t;

typedef PACKED_STRUCT GAPAdvertisingEventCommandFailedIndication_tag {
	GAPAdvertisingEventCommandFailedIndication_FailReason_t FailReason;  // The reason of failure
} GAPAdvertisingEventCommandFailedIndication_t;

typedef PACKED_STRUCT GAPScanningEventStateChangedIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPScanningEventStateChangedIndication_t;

/* The reason of failure */
typedef enum GAPScanningEventCommandFailedIndication_FailReason_tag {
	GAPScanningEventCommandFailedIndication_FailReason_gBleSuccess_c = 0x0000,
	GAPScanningEventCommandFailedIndication_FailReason_gBleInvalidParameter_c = 0x0001,
	GAPScanningEventCommandFailedIndication_FailReason_gBleOverflow_c = 0x0002,
	GAPScanningEventCommandFailedIndication_FailReason_gBleUnavailable_c = 0x0003,
	GAPScanningEventCommandFailedIndication_FailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPScanningEventCommandFailedIndication_FailReason_gBleOutOfMemory_c = 0x0005,
	GAPScanningEventCommandFailedIndication_FailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPScanningEventCommandFailedIndication_FailReason_gBleOsError_c = 0x0007,
	GAPScanningEventCommandFailedIndication_FailReason_gBleUnexpectedError_c = 0x0008,
	GAPScanningEventCommandFailedIndication_FailReason_gBleInvalidState_c = 0x0009,
	GAPScanningEventCommandFailedIndication_FailReason_gBleTimerError_c = 0x000A,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPScanningEventCommandFailedIndication_FailReason_gHciHardwareFailure_c = 0x0103,
	GAPScanningEventCommandFailedIndication_FailReason_gHciPageTimeout_c = 0x0104,
	GAPScanningEventCommandFailedIndication_FailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPScanningEventCommandFailedIndication_FailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPScanningEventCommandFailedIndication_FailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTimeout_c = 0x0108,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPScanningEventCommandFailedIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPScanningEventCommandFailedIndication_FailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPScanningEventCommandFailedIndication_FailReason_gHciCommandDisallowed_c = 0x010C,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPScanningEventCommandFailedIndication_FailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPScanningEventCommandFailedIndication_FailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPScanningEventCommandFailedIndication_FailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPScanningEventCommandFailedIndication_FailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnspecifiedError_c = 0x011F,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPScanningEventCommandFailedIndication_FailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPScanningEventCommandFailedIndication_FailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPScanningEventCommandFailedIndication_FailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPScanningEventCommandFailedIndication_FailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPScanningEventCommandFailedIndication_FailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPScanningEventCommandFailedIndication_FailReason_gHciInstantPassed_c = 0x0128,
	GAPScanningEventCommandFailedIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPScanningEventCommandFailedIndication_FailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x2B_c = 0x012B,
	GAPScanningEventCommandFailedIndication_FailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPScanningEventCommandFailedIndication_FailReason_gHciQosRejected_c = 0x012D,
	GAPScanningEventCommandFailedIndication_FailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPScanningEventCommandFailedIndication_FailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPScanningEventCommandFailedIndication_FailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x31_c = 0x0131,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x33_c = 0x0133,
	GAPScanningEventCommandFailedIndication_FailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPScanningEventCommandFailedIndication_FailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPScanningEventCommandFailedIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPScanningEventCommandFailedIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPScanningEventCommandFailedIndication_FailReason_gHciHostBusyPairing_c = 0x0138,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPScanningEventCommandFailedIndication_FailReason_gHciControllerBusy_c = 0x013A,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPScanningEventCommandFailedIndication_FailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPScanningEventCommandFailedIndication_FailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPScanningEventCommandFailedIndication_FailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPScanningEventCommandFailedIndication_FailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPScanningEventCommandFailedIndication_FailReason_gHciLimitReached_c = 0x0143,
	GAPScanningEventCommandFailedIndication_FailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPScanningEventCommandFailedIndication_FailReason_gHciAlreadyInit_c = 0x01A0,
	GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidParameter_c = 0x01A1,
	GAPScanningEventCommandFailedIndication_FailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPScanningEventCommandFailedIndication_FailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPScanningEventCommandFailedIndication_FailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPScanningEventCommandFailedIndication_FailReason_gHciEventNotSupported_c = 0x01A5,
	GAPScanningEventCommandFailedIndication_FailReason_gHciTransportError_c = 0x01A6,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelClosed_c = 0x03F9,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelBusy_c = 0x03FC,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPScanningEventCommandFailedIndication_FailReason_gL2caError_c = 0x03FF,
	GAPScanningEventCommandFailedIndication_FailReason_gSmNullCBFunction_c = 0x0401,
	GAPScanningEventCommandFailedIndication_FailReason_gSmCommandNotSupported_c = 0x0402,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPScanningEventCommandFailedIndication_FailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPScanningEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPScanningEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPScanningEventCommandFailedIndication_FailReason_gSmInsufficientResources_c = 0x0419,
	GAPScanningEventCommandFailedIndication_FailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPScanningEventCommandFailedIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPScanningEventCommandFailedIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPScanningEventCommandFailedIndication_FailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidHandle_c = 0x0501,
	GAPScanningEventCommandFailedIndication_FailReason_gAttReadNotPermitted_c = 0x0502,
	GAPScanningEventCommandFailedIndication_FailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidPdu_c = 0x0504,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPScanningEventCommandFailedIndication_FailReason_gAttRequestNotSupported_c = 0x0506,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidOffset_c = 0x0507,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPScanningEventCommandFailedIndication_FailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPScanningEventCommandFailedIndication_FailReason_gAttAttributeNotFound_c = 0x050A,
	GAPScanningEventCommandFailedIndication_FailReason_gAttAttributeNotLong_c = 0x050B,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPScanningEventCommandFailedIndication_FailReason_gAttUnlikelyor_c = 0x050E,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPScanningEventCommandFailedIndication_FailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientResources_c = 0x0511,
	GAPScanningEventCommandFailedIndication_FailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPScanningEventCommandFailedIndication_FailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPScanningEventCommandFailedIndication_FailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPScanningEventCommandFailedIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPScanningEventCommandFailedIndication_FailReason_gGattInvalidValueLength_c = 0x0605,
	GAPScanningEventCommandFailedIndication_FailReason_gGattServerTimeout_c = 0x0606,
	GAPScanningEventCommandFailedIndication_FailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPScanningEventCommandFailedIndication_FailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPScanningEventCommandFailedIndication_FailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPScanningEventCommandFailedIndication_FailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPScanningEventCommandFailedIndication_FailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPScanningEventCommandFailedIndication_FailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPScanningEventCommandFailedIndication_FailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPScanningEventCommandFailedIndication_FailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPScanningEventCommandFailedIndication_FailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPScanningEventCommandFailedIndication_FailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPScanningEventCommandFailedIndication_FailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPScanningEventCommandFailedIndication_FailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPScanningEventCommandFailedIndication_FailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPScanningEventCommandFailedIndication_FailReason_t;

typedef PACKED_STRUCT GAPScanningEventCommandFailedIndication_tag {
	GAPScanningEventCommandFailedIndication_FailReason_t FailReason;  // The reason of failure
} GAPScanningEventCommandFailedIndication_t;

/* Device's advertising address type */
typedef enum GAPScanningEventDeviceScannedIndication_AddressType_tag {
	GAPScanningEventDeviceScannedIndication_AddressType_gPublic_c = 0x00,
	GAPScanningEventDeviceScannedIndication_AddressType_gRandom_c = 0x01
} GAPScanningEventDeviceScannedIndication_AddressType_t;

/* Advertising report type, indicating what type of event generated this data (advertising, scan response) */
typedef enum GAPScanningEventDeviceScannedIndication_AdvEventType_tag {
	GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvInd_c = 0x00,
	GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvDirectInd_c = 0x01,
	GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvScanInd_c = 0x02,
	GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvNonconnInd_c = 0x03,
	GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepScanRsp_c = 0x04
} GAPScanningEventDeviceScannedIndication_AdvEventType_t;

typedef struct GAPScanningEventDeviceScannedIndication_tag {
	GAPScanningEventDeviceScannedIndication_AddressType_t AddressType;  // Device's advertising address type
	uint8_t Address[6];  // Device's advertising address
	uint8_t Rssi;  // RSSI on the advertising channel; may be compared to the TX power contained in the AD Structure of type gAdTxPowerLevel_c to estimate distance from the advertiser
	uint8_t DataLength;  // Length of the advertising or scan response data
	uint8_t *Data;  // Advertising or scan response data
	GAPScanningEventDeviceScannedIndication_AdvEventType_t AdvEventType;  // Advertising report type, indicating what type of event generated this data (advertising, scan response)
	bool_t DirectRpaUsed;  // TRUE if directed advertising with Resolvable Private Address as Direct Address was detected while Enhanced Privacy is enabled
	uint8_t DirectRpa[6];  // Resolvable Private Address set as Direct Address for directed advertising
	bool_t advertisingAddressResolved;  // TRUE if the address contained in the addressType and aAddress fields is the identity address of a resolved RPA from the Advertising Address field
} GAPScanningEventDeviceScannedIndication_t;

/* Accuracy of master's clock, allowing for frame detection optimizations */
typedef enum GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_tag {
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc500ppm_c = 0x00,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc250ppm_c = 0x01,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc150ppm_c = 0x02,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc100ppm_c = 0x03,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc75ppm_c = 0x04,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc50ppm_c = 0x05,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc30ppm_c = 0x06,
	GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_gMasterClkAcc20ppm_c = 0x07
} GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_t;

/* Connected device's address type */
typedef enum GAPConnectionEventConnectedIndication_PeerAddressType_tag {
	GAPConnectionEventConnectedIndication_PeerAddressType_gPublic_c = 0x00,
	GAPConnectionEventConnectedIndication_PeerAddressType_gRandom_c = 0x01
} GAPConnectionEventConnectedIndication_PeerAddressType_t;

typedef struct GAPConnectionEventConnectedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		uint16_t ConnInterval;  // Interval between connection events
		uint16_t ConnLatency;  // Number of consecutive connection events the Slave may ignore
		uint16_t SupervisionTimeout;  // The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped
		GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_t MasterClockAccuracy;  // Accuracy of master's clock, allowing for frame detection optimizations
	} ConnectionParameters;  // Connection parameters established by the Controller
	GAPConnectionEventConnectedIndication_PeerAddressType_t PeerAddressType;  // Connected device's address type
	uint8_t PeerAddress[6];  // Connected device's address
	bool_t peerRpaResolved;  // TRUE if the address defined by peerAddressType and peerAddress is the identity address of the peer, and the peer used an RPA that was resolved by the Controller and is contained in the peerRpa field
	uint8_t peerRpa[6];  // Peer Resolvable Private Address if Controller Privacy is active and peerRpaResolved is TRUE
	bool_t localRpaUsed;  // TRUE if the Controller has used an RPA contained in the localRpa field
	uint8_t localRpa[6];  // Local Resolvable Private Address if Controller Privacy is active and localRpaUsed is TRUE
} GAPConnectionEventConnectedIndication_t;

/* The desired security mode-level */
typedef enum GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_tag {
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_tag {
	GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_tag {
	GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_tag {
	GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_t;

typedef PACKED_STRUCT GAPConnectionEventPairingRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPConnectionEventPairingRequestIndication_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPConnectionEventPairingRequestIndication_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPConnectionEventPairingRequestIndication_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPConnectionEventPairingRequestIndication_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters
} GAPConnectionEventPairingRequestIndication_t;

typedef PACKED_STRUCT GAPConnectionEventSlaveSecurityRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		bool_t BondAfterPairing;  // TRUE if the Slave supports bonding, FALSE otherwise
		bool_t bAuthenticationRequired;  // TRUE if the slave requires authentication for MITM protection, FALSE otherwise
	} SlaveSecurityRequestParameters;  // Slave security request parameters
} GAPConnectionEventSlaveSecurityRequestIndication_t;

/* The desired security mode-level */
typedef enum GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_tag {
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode1Level1_c = 0x10,
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode1Level2_c = 0x11,
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode1Level3_c = 0x12,
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode1Level4_c = 0x13,
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode2Level1_c = 0x21,
	GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_gMode2Level2_c = 0x22
} GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_t;

/* I/O capabilities used to determine the pairing method */
typedef enum GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_tag {
	GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_gIoDisplayOnly_c = 0x00,
	GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_gIoDisplayYesNo_c = 0x01,
	GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_gIoKeyboardOnly_c = 0x02,
	GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_gIoNone_c = 0x03,
	GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_gIoKeyboardDisplay_c = 0x04
} GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_t;

/* SMP keys to be distributed by the Central */
typedef enum GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_tag {
	GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_gNoKeys_c = 0x00,
	GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_gLtk_c = 0x01,
	GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_gIrk_c = 0x02,
	GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_gCsrk_c = 0x04
} GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_t;

/* SMP keys to be distributed by the Peripheral */
typedef enum GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_tag {
	GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_gNoKeys_c = 0x00,
	GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_gLtk_c = 0x01,
	GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_gIrk_c = 0x02,
	GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_gCsrk_c = 0x04
} GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_t;

typedef PACKED_STRUCT GAPConnectionEventPairingResponseIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		bool_t WithBonding;  // TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
		GAPConnectionEventPairingResponseIndication_PairingParameters_SecurityModeAndLevel_t SecurityModeAndLevel;  // The desired security mode-level
		uint8_t MaxEncryptionKeySize;  // Maximum LTK size supported by the device
		GAPConnectionEventPairingResponseIndication_PairingParameters_LocalIoCapabilities_t LocalIoCapabilities;  // I/O capabilities used to determine the pairing method
		bool_t OobAvailable;  // TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
		GAPConnectionEventPairingResponseIndication_PairingParameters_CentralKeys_t CentralKeys;  // SMP keys to be distributed by the Central
		GAPConnectionEventPairingResponseIndication_PairingParameters_PeripheralKeys_t PeripheralKeys;  // SMP keys to be distributed by the Peripheral
		bool_t LeSecureConnectionSupported;  // indicates if device supports LE Secure Connections pairing
		bool_t UseKeypressNotifications;  // Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
	} PairingParameters;  // Pairing parameters
} GAPConnectionEventPairingResponseIndication_t;

/* The reason of the rejection */
typedef enum GAPConnectionEventAuthenticationRejectedIndication_RejectReason_tag {
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gOobNotAvailable_c = 0x02,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gIncompatibleIoCapabilities_c = 0x03,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gPairingNotSupported_c = 0x05,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gLowEncryptionKeySize_c = 0x06,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gUnspecifiedReason_c = 0x08,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gRepeatedAttempts_c = 0x09,
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gLinkEncryptionFailed_c = 0xF0
} GAPConnectionEventAuthenticationRejectedIndication_RejectReason_t;

typedef PACKED_STRUCT GAPConnectionEventAuthenticationRejectedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventAuthenticationRejectedIndication_RejectReason_t RejectReason;  // The reason of the rejection
} GAPConnectionEventAuthenticationRejectedIndication_t;

typedef PACKED_STRUCT GAPConnectionEventPasskeyRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
} GAPConnectionEventPasskeyRequestIndication_t;

typedef PACKED_STRUCT GAPConnectionEventOobRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
} GAPConnectionEventOobRequestIndication_t;

typedef PACKED_STRUCT GAPConnectionEventPasskeyDisplayIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint32_t PasskeyForDisplay;  // Passkey to be displayed by this Slave
} GAPConnectionEventPasskeyDisplayIndication_t;

/* Mask identifying the keys being requested */
typedef enum GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_tag {
	GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gNoKeys_c = 0x00,
	GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gLtk_c = 0x01,
	GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gIrk_c = 0x02,
	GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gCsrk_c = 0x04
} GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_t;

typedef PACKED_STRUCT GAPConnectionEventKeyExchangeRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_t RequestedKeys;  // Mask identifying the keys being requested
	uint8_t RequestedLtkSize;  // Requested size of the encryption key
} GAPConnectionEventKeyExchangeRequestIndication_t;

/* Public or Random address */
typedef enum GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_tag {
	GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_gPublic_c = 0x00,
	GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_gRandom_c = 0x01
} GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_t;

typedef struct GAPConnectionEventKeysReceivedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		bool_t LtkIncluded;  // Boolean value which indicates if LTK size and LTK are included or not
		struct {
			uint8_t LtkSize;  // Encryption Key Size
			uint8_t *Ltk;  // Long Term (Encryption) Key
		} LtkInfo;  // LTK information (size and value)
		bool_t IrkIncluded;  // Boolean value which indicates if IRK is included or not
		uint8_t Irk[16];  // Identity Resolving Key
		bool_t CsrkIncluded;  // Boolean value which indicates if CSRK is included or not
		uint8_t Csrk[16];  // Connection Signature Resolving Key
		struct {
			uint8_t RandSize;  // Random value size
			uint8_t *Rand;  // Random value used to identify the LTK
			uint16_t Ediv;  // EDIV value used to identify the LTK
		} RandEdivInfo;  // Rand information (size and value) and Ediv
		bool_t AddressIncluded;  // Boolean value which indicates if Address is included or not
		struct {
			GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_t DeviceAddressType;  // Public or Random address
			uint8_t DeviceAddress[6];  // Device Address
		} AddressInfo;  // Address information (type and value)
	} Keys;  // The SMP keys distributed by the peer
} GAPConnectionEventKeysReceivedIndication_t;

typedef struct GAPConnectionEventLongTermKeyRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint16_t Ediv;  // The Encryption Diversifier, as defined by the SMP
	uint8_t RandSize;  // Random number size
	uint8_t *Rand;  // The Random number, as defined by the SMP
} GAPConnectionEventLongTermKeyRequestIndication_t;

typedef PACKED_STRUCT GAPConnectionEventEncryptionChangedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	bool_t NewEncryptionState;  // TRUE if link has been encrypted, FALSE if encryption was paused or removed
} GAPConnectionEventEncryptionChangedIndication_t;

/* Pairing status */
typedef enum GAPConnectionEventPairingCompleteIndication_PairingStatus_tag {
	GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingSuccessful = 0x01,
	GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingFailed = 0x00
} GAPConnectionEventPairingCompleteIndication_PairingStatus_t;

/* The reason of failure */
typedef enum GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_tag {
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleSuccess_c = 0x0000,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleInvalidParameter_c = 0x0001,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleOverflow_c = 0x0002,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleUnavailable_c = 0x0003,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleOutOfMemory_c = 0x0005,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleOsError_c = 0x0007,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleUnexpectedError_c = 0x0008,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleInvalidState_c = 0x0009,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gBleTimerError_c = 0x000A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciHardwareFailure_c = 0x0103,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciPageTimeout_c = 0x0104,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionTimeout_c = 0x0108,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciCommandDisallowed_c = 0x010C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnspecifiedError_c = 0x011F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciInstantPassed_c = 0x0128,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciReserved_0x2B_c = 0x012B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciQosRejected_c = 0x012D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciReserved_0x31_c = 0x0131,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciReserved_0x33_c = 0x0133,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciHostBusyPairing_c = 0x0138,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciControllerBusy_c = 0x013A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciLimitReached_c = 0x0143,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciAlreadyInit_c = 0x01A0,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciInvalidParameter_c = 0x01A1,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciEventNotSupported_c = 0x01A5,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gHciTransportError_c = 0x01A6,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caChannelClosed_c = 0x03F9,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caChannelBusy_c = 0x03FC,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gL2caError_c = 0x03FF,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmNullCBFunction_c = 0x0401,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmCommandNotSupported_c = 0x0402,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmInsufficientResources_c = 0x0419,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInvalidHandle_c = 0x0501,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttReadNotPermitted_c = 0x0502,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInvalidPdu_c = 0x0504,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttRequestNotSupported_c = 0x0506,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInvalidOffset_c = 0x0507,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttAttributeNotFound_c = 0x050A,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttAttributeNotLong_c = 0x050B,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttUnlikelyor_c = 0x050E,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gAttInsufficientResources_c = 0x0511,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattInvalidValueLength_c = 0x0605,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattServerTimeout_c = 0x0606,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_t;

typedef struct GAPConnectionEventPairingCompleteIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventPairingCompleteIndication_PairingStatus_t PairingStatus;  // Pairing status
	union {
		bool_t PairingSuccessful_WithBonding;

		GAPConnectionEventPairingCompleteIndication_PairingData_PairingFailed_FailReason_t PairingFailed_FailReason;

	} PairingData;  // Information of pairing completion
} GAPConnectionEventPairingCompleteIndication_t;

/* Reason for disconnection */
typedef enum GAPConnectionEventDisconnectedIndication_Reason_tag {
	GAPConnectionEventDisconnectedIndication_Reason_gBleSuccess_c = 0x0000,
	GAPConnectionEventDisconnectedIndication_Reason_gBleInvalidParameter_c = 0x0001,
	GAPConnectionEventDisconnectedIndication_Reason_gBleOverflow_c = 0x0002,
	GAPConnectionEventDisconnectedIndication_Reason_gBleUnavailable_c = 0x0003,
	GAPConnectionEventDisconnectedIndication_Reason_gBleFeatureNotSupported_c = 0x0004,
	GAPConnectionEventDisconnectedIndication_Reason_gBleOutOfMemory_c = 0x0005,
	GAPConnectionEventDisconnectedIndication_Reason_gBleAlreadyInitialized_c = 0x0006,
	GAPConnectionEventDisconnectedIndication_Reason_gBleOsError_c = 0x0007,
	GAPConnectionEventDisconnectedIndication_Reason_gBleUnexpectedError_c = 0x0008,
	GAPConnectionEventDisconnectedIndication_Reason_gBleInvalidState_c = 0x0009,
	GAPConnectionEventDisconnectedIndication_Reason_gBleTimerError_c = 0x000A,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownHciCommand_c = 0x0101,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConnectionEventDisconnectedIndication_Reason_gHciHardwareFailure_c = 0x0103,
	GAPConnectionEventDisconnectedIndication_Reason_gHciPageTimeout_c = 0x0104,
	GAPConnectionEventDisconnectedIndication_Reason_gHciAuthenticationFailure_c = 0x0105,
	GAPConnectionEventDisconnectedIndication_Reason_gHciPinOrKeyMissing_c = 0x0106,
	GAPConnectionEventDisconnectedIndication_Reason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTimeout_c = 0x0108,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConnectionEventDisconnectedIndication_Reason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConnectionEventDisconnectedIndication_Reason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConnectionEventDisconnectedIndication_Reason_gHciCommandDisallowed_c = 0x010C,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRepeatedAttempts_c = 0x0117,
	GAPConnectionEventDisconnectedIndication_Reason_gHciPairingNotAllowed_c = 0x0118,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownLpmPdu_c = 0x0119,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConnectionEventDisconnectedIndication_Reason_gHciScoOffsetRejected_c = 0x011B,
	GAPConnectionEventDisconnectedIndication_Reason_gHciScoIntervalRejected_c = 0x011C,
	GAPConnectionEventDisconnectedIndication_Reason_gHciScoAirModeRejected_c = 0x011D,
	GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidLpmParameters_c = 0x011E,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnspecifiedError_c = 0x011F,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConnectionEventDisconnectedIndication_Reason_gHciLLResponseTimeout_c = 0x0122,
	GAPConnectionEventDisconnectedIndication_Reason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConnectionEventDisconnectedIndication_Reason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConnectionEventDisconnectedIndication_Reason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConnectionEventDisconnectedIndication_Reason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConnectionEventDisconnectedIndication_Reason_gHciInstantPassed_c = 0x0128,
	GAPConnectionEventDisconnectedIndication_Reason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConnectionEventDisconnectedIndication_Reason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x2B_c = 0x012B,
	GAPConnectionEventDisconnectedIndication_Reason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConnectionEventDisconnectedIndication_Reason_gHciQosRejected_c = 0x012D,
	GAPConnectionEventDisconnectedIndication_Reason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConnectionEventDisconnectedIndication_Reason_gHciInsufficientSecurity_c = 0x012F,
	GAPConnectionEventDisconnectedIndication_Reason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x31_c = 0x0131,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRoleSwitchPending_c = 0x0132,
	GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x33_c = 0x0133,
	GAPConnectionEventDisconnectedIndication_Reason_gHciReservedSlotViolation_c = 0x0134,
	GAPConnectionEventDisconnectedIndication_Reason_gHciRoleSwitchFailed_c = 0x0135,
	GAPConnectionEventDisconnectedIndication_Reason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConnectionEventDisconnectedIndication_Reason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConnectionEventDisconnectedIndication_Reason_gHciHostBusyPairing_c = 0x0138,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConnectionEventDisconnectedIndication_Reason_gHciControllerBusy_c = 0x013A,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConnectionEventDisconnectedIndication_Reason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConnectionEventDisconnectedIndication_Reason_gHciMacConnectionFailed_c = 0x013F,
	GAPConnectionEventDisconnectedIndication_Reason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConnectionEventDisconnectedIndication_Reason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConnectionEventDisconnectedIndication_Reason_gHciLimitReached_c = 0x0143,
	GAPConnectionEventDisconnectedIndication_Reason_gHciOperationCancelledByHost_c = 0x0144,
	GAPConnectionEventDisconnectedIndication_Reason_gHciAlreadyInit_c = 0x01A0,
	GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidParameter_c = 0x01A1,
	GAPConnectionEventDisconnectedIndication_Reason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConnectionEventDisconnectedIndication_Reason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConnectionEventDisconnectedIndication_Reason_gHciCommandNotSupported_c = 0x01A4,
	GAPConnectionEventDisconnectedIndication_Reason_gHciEventNotSupported_c = 0x01A5,
	GAPConnectionEventDisconnectedIndication_Reason_gHciTransportError_c = 0x01A6,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caAlreadyInit_c = 0x03F0,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caInsufficientResources_c = 0x03F1,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmInvalid_c = 0x03F4,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelInvalid_c = 0x03F8,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelClosed_c = 0x03F9,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelBusy_c = 0x03FC,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caInvalidParameter_c = 0x03FE,
	GAPConnectionEventDisconnectedIndication_Reason_gL2caError_c = 0x03FF,
	GAPConnectionEventDisconnectedIndication_Reason_gSmNullCBFunction_c = 0x0401,
	GAPConnectionEventDisconnectedIndication_Reason_gSmCommandNotSupported_c = 0x0402,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedCommand_c = 0x0403,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandCode_c = 0x0404,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandLength_c = 0x0405,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandParameter_c = 0x0406,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidDeviceId_c = 0x0407,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidInternalOperation_c = 0x0408,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedKeyType_c = 0x040B,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedKeyset_c = 0x040D,
	GAPConnectionEventDisconnectedIndication_Reason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConnectionEventDisconnectedIndication_Reason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConnectionEventDisconnectedIndication_Reason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConnectionEventDisconnectedIndication_Reason_gSmInsufficientResources_c = 0x0419,
	GAPConnectionEventDisconnectedIndication_Reason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConnectionEventDisconnectedIndication_Reason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConnectionEventDisconnectedIndication_Reason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConnectionEventDisconnectedIndication_Reason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidHandle_c = 0x0501,
	GAPConnectionEventDisconnectedIndication_Reason_gAttReadNotPermitted_c = 0x0502,
	GAPConnectionEventDisconnectedIndication_Reason_gAttWriteNotPermitted_c = 0x0503,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidPdu_c = 0x0504,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientAuthentication_c = 0x0505,
	GAPConnectionEventDisconnectedIndication_Reason_gAttRequestNotSupported_c = 0x0506,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidOffset_c = 0x0507,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientAuthorization_c = 0x0508,
	GAPConnectionEventDisconnectedIndication_Reason_gAttPrepareQueueFull_c = 0x0509,
	GAPConnectionEventDisconnectedIndication_Reason_gAttAttributeNotFound_c = 0x050A,
	GAPConnectionEventDisconnectedIndication_Reason_gAttAttributeNotLong_c = 0x050B,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConnectionEventDisconnectedIndication_Reason_gAttUnlikelyor_c = 0x050E,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientEncryption_c = 0x050F,
	GAPConnectionEventDisconnectedIndication_Reason_gAttUnsupportedGroupType_c = 0x0510,
	GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientResources_c = 0x0511,
	GAPConnectionEventDisconnectedIndication_Reason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConnectionEventDisconnectedIndication_Reason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConnectionEventDisconnectedIndication_Reason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConnectionEventDisconnectedIndication_Reason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConnectionEventDisconnectedIndication_Reason_gGattInvalidValueLength_c = 0x0605,
	GAPConnectionEventDisconnectedIndication_Reason_gGattServerTimeout_c = 0x0606,
	GAPConnectionEventDisconnectedIndication_Reason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConnectionEventDisconnectedIndication_Reason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConnectionEventDisconnectedIndication_Reason_gGapAdvDataTooLong_c = 0x0701,
	GAPConnectionEventDisconnectedIndication_Reason_gGapScanRspDataTooLong_c = 0x0702,
	GAPConnectionEventDisconnectedIndication_Reason_gGapDeviceNotBonded_c = 0x0703,
	GAPConnectionEventDisconnectedIndication_Reason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConnectionEventDisconnectedIndication_Reason_gDevDbCccdLimitReached_c = 0x0801,
	GAPConnectionEventDisconnectedIndication_Reason_gDevDbCccdNotFound_c = 0x0802,
	GAPConnectionEventDisconnectedIndication_Reason_gGattDbInvalidHandle_c = 0x0901,
	GAPConnectionEventDisconnectedIndication_Reason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConnectionEventDisconnectedIndication_Reason_gGattDbCccdNotFound_c = 0x0903,
	GAPConnectionEventDisconnectedIndication_Reason_gGattDbServiceNotFound_c = 0x0904,
	GAPConnectionEventDisconnectedIndication_Reason_gGattDbDescriptorNotFound_c = 0x0905
} GAPConnectionEventDisconnectedIndication_Reason_t;

typedef PACKED_STRUCT GAPConnectionEventDisconnectedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventDisconnectedIndication_Reason_t Reason;  // Reason for disconnection
} GAPConnectionEventDisconnectedIndication_t;

typedef PACKED_STRUCT GAPConnectionEventRssiReadIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint8_t Rssi;  // Value of the RSSI
} GAPConnectionEventRssiReadIndication_t;

typedef PACKED_STRUCT GAPConnectionEventTxPowerLevelReadIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint8_t TxPowerLevel;  // Value of the TX power
} GAPConnectionEventTxPowerLevelReadIndication_t;

/* Reason for power reading failure */
typedef enum GAPConnectionEventPowerReadFailureIndication_FailReason_tag {
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleSuccess_c = 0x0000,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleInvalidParameter_c = 0x0001,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOverflow_c = 0x0002,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleUnavailable_c = 0x0003,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOutOfMemory_c = 0x0005,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOsError_c = 0x0007,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleUnexpectedError_c = 0x0008,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleInvalidState_c = 0x0009,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gBleTimerError_c = 0x000A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciHardwareFailure_c = 0x0103,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPageTimeout_c = 0x0104,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTimeout_c = 0x0108,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCommandDisallowed_c = 0x010C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnspecifiedError_c = 0x011F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInstantPassed_c = 0x0128,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x2B_c = 0x012B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciQosRejected_c = 0x012D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x31_c = 0x0131,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x33_c = 0x0133,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciHostBusyPairing_c = 0x0138,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciControllerBusy_c = 0x013A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLimitReached_c = 0x0143,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAlreadyInit_c = 0x01A0,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidParameter_c = 0x01A1,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciEventNotSupported_c = 0x01A5,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gHciTransportError_c = 0x01A6,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelClosed_c = 0x03F9,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelBusy_c = 0x03FC,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caError_c = 0x03FF,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmNullCBFunction_c = 0x0401,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmCommandNotSupported_c = 0x0402,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInsufficientResources_c = 0x0419,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidHandle_c = 0x0501,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttReadNotPermitted_c = 0x0502,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidPdu_c = 0x0504,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttRequestNotSupported_c = 0x0506,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidOffset_c = 0x0507,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttAttributeNotFound_c = 0x050A,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttAttributeNotLong_c = 0x050B,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttUnlikelyor_c = 0x050E,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientResources_c = 0x0511,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattInvalidValueLength_c = 0x0605,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattServerTimeout_c = 0x0606,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPConnectionEventPowerReadFailureIndication_FailReason_t;

typedef PACKED_STRUCT GAPConnectionEventPowerReadFailureIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventPowerReadFailureIndication_FailReason_t FailReason;  // Reason for power reading failure
} GAPConnectionEventPowerReadFailureIndication_t;

typedef PACKED_STRUCT GAPConnectionEventParameterUpdateRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		uint16_t IntervalMin;  // Minimum interval
		uint16_t IntervalMax;  // Maximum interval
		uint16_t SlaveLatency;  // Slave latency
		uint16_t TimeoutMultiplier;  // Timeout multiplier
	} ConnectionParameterUpdateRequest;  // Connection parameter update request event data
} GAPConnectionEventParameterUpdateRequestIndication_t;

/* The status of the request */
typedef enum GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_tag {
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleSuccess_c = 0x0000,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleInvalidParameter_c = 0x0001,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleOverflow_c = 0x0002,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleUnavailable_c = 0x0003,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleFeatureNotSupported_c = 0x0004,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleOutOfMemory_c = 0x0005,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleAlreadyInitialized_c = 0x0006,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleOsError_c = 0x0007,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleUnexpectedError_c = 0x0008,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleInvalidState_c = 0x0009,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gBleTimerError_c = 0x000A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnknownHciCommand_c = 0x0101,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciHardwareFailure_c = 0x0103,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciPageTimeout_c = 0x0104,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciAuthenticationFailure_c = 0x0105,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciPinOrKeyMissing_c = 0x0106,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionTimeout_c = 0x0108,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciCommandDisallowed_c = 0x010C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRepeatedAttempts_c = 0x0117,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciPairingNotAllowed_c = 0x0118,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnknownLpmPdu_c = 0x0119,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciScoOffsetRejected_c = 0x011B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciScoIntervalRejected_c = 0x011C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciScoAirModeRejected_c = 0x011D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciInvalidLpmParameters_c = 0x011E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnspecifiedError_c = 0x011F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciLLResponseTimeout_c = 0x0122,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciInstantPassed_c = 0x0128,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciReserved_0x2B_c = 0x012B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciQosRejected_c = 0x012D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciInsufficientSecurity_c = 0x012F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciReserved_0x31_c = 0x0131,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRoleSwitchPending_c = 0x0132,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciReserved_0x33_c = 0x0133,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciReservedSlotViolation_c = 0x0134,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciRoleSwitchFailed_c = 0x0135,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciHostBusyPairing_c = 0x0138,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciControllerBusy_c = 0x013A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciMacConnectionFailed_c = 0x013F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciLimitReached_c = 0x0143,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciOperationCancelledByHost_c = 0x0144,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciAlreadyInit_c = 0x01A0,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciInvalidParameter_c = 0x01A1,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciCommandNotSupported_c = 0x01A4,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciEventNotSupported_c = 0x01A5,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gHciTransportError_c = 0x01A6,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caAlreadyInit_c = 0x03F0,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caInsufficientResources_c = 0x03F1,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caLePsmInvalid_c = 0x03F4,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caChannelInvalid_c = 0x03F8,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caChannelClosed_c = 0x03F9,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caChannelBusy_c = 0x03FC,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caInvalidParameter_c = 0x03FE,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gL2caError_c = 0x03FF,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmNullCBFunction_c = 0x0401,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmCommandNotSupported_c = 0x0402,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnexpectedCommand_c = 0x0403,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidCommandCode_c = 0x0404,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidCommandLength_c = 0x0405,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidCommandParameter_c = 0x0406,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidDeviceId_c = 0x0407,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidInternalOperation_c = 0x0408,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnexpectedKeyType_c = 0x040B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnexpectedKeyset_c = 0x040D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmInsufficientResources_c = 0x0419,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInvalidHandle_c = 0x0501,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttReadNotPermitted_c = 0x0502,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttWriteNotPermitted_c = 0x0503,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInvalidPdu_c = 0x0504,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInsufficientAuthentication_c = 0x0505,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttRequestNotSupported_c = 0x0506,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInvalidOffset_c = 0x0507,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInsufficientAuthorization_c = 0x0508,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttPrepareQueueFull_c = 0x0509,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttAttributeNotFound_c = 0x050A,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttAttributeNotLong_c = 0x050B,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttUnlikelyor_c = 0x050E,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInsufficientEncryption_c = 0x050F,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttUnsupportedGroupType_c = 0x0510,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gAttInsufficientResources_c = 0x0511,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattInvalidValueLength_c = 0x0605,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattServerTimeout_c = 0x0606,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGapAdvDataTooLong_c = 0x0701,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGapScanRspDataTooLong_c = 0x0702,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGapDeviceNotBonded_c = 0x0703,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gDevDbCccdLimitReached_c = 0x0801,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gDevDbCccdNotFound_c = 0x0802,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattDbInvalidHandle_c = 0x0901,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattDbCccdNotFound_c = 0x0903,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattDbServiceNotFound_c = 0x0904,
	GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_gGattDbDescriptorNotFound_c = 0x0905
} GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_t;

typedef PACKED_STRUCT GAPConnectionEventParameterUpdateCompleteIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		GAPConnectionEventParameterUpdateCompleteIndication_ConnectionParameterUpdateComplete_Status_t Status;  // The status of the request
		uint16_t ConnInterval;  // Connection interval
		uint16_t ConnLatency;  // Connection latency
		uint16_t SupervisionTimeout;  // Supervision timeout
	} ConnectionParameterUpdateComplete;  // Connection parameter update complete event data
} GAPConnectionEventParameterUpdateCompleteIndication_t;

typedef PACKED_STRUCT GAPConnectionEventLeDataLengthChangedIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	struct {
		uint16_t MaxTxOctets;  // The maximum number of payload octets in a Link Layer Data Channel PDU to transmit on this connection
		uint16_t MaxTxTime;  // The maximum time that the local Controller will take to send a Link Layer Data Channel PDU on this connection
		uint16_t MaxRxOctets;  // The maximum number of payload octets in a Link Layer Data Channel PDU to receive on this connection
		uint16_t MaxRxTime;  // The maximum time that the local Controller will take to receive a Link Layer Data Channel PDU on this connection
	} LeDataLengthChanged;  // Connection Le Data Length Changed Event data
} GAPConnectionEventLeDataLengthChangedIndication_t;

typedef PACKED_STRUCT GAPConnectionEventLeScOobDataRequestIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
} GAPConnectionEventLeScOobDataRequestIndication_t;

typedef PACKED_STRUCT GAPConnectionEventLeScDisplayNumericValueIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint32_t ncValue;  // A number between 0 and 999999 decimal which must be confirmed by the user on both pairing devices
} GAPConnectionEventLeScDisplayNumericValueIndication_t;

/* keypressNotifType */
typedef enum GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_tag {
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyEntryStarted_c = 0x00,
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyDigitStarted_c = 0x01,
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyDigitErased_c = 0x02,
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyCleared_c = 0x03,
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_gKnPasskeyEntryCompleted_c = 0x04
} GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_t;

typedef PACKED_STRUCT GAPConnectionEventLeScKeypressNotificationIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPConnectionEventLeScKeypressNotificationIndication_GapLeScKeypressNotificationParams_keypressNotifType_t GapLeScKeypressNotificationParams_keypressNotifType;

} GAPConnectionEventLeScKeypressNotificationIndication_t;

typedef PACKED_STRUCT GAPGenericEventControllerResetCompleteIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventControllerResetCompleteIndication_t;

typedef PACKED_STRUCT GAPLeScPublicKeyRegeneratedIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPLeScPublicKeyRegeneratedIndication_t;

typedef PACKED_STRUCT GAPGenericEventLeScLocalOobDataIndication_tag {
	uint8_t RandomValue[16];  // LE SC OOB r (Random value)
	uint8_t ConfirmValue[16];  // LE SC OOB Cr (Random Confirm value)
} GAPGenericEventLeScLocalOobDataIndication_t;

typedef PACKED_STRUCT GAPGenericEventHostPrivacyStateChangedIndication_tag {
	bool_t NewHostPrivacyState;  // Indicates the new state of the host privacy: TRUE if enabled, FALSE if disabled
} GAPGenericEventHostPrivacyStateChangedIndication_t;

typedef PACKED_STRUCT GAPGenericEventControllerPrivacyStateChangedIndication_tag {
	bool_t NewControllerPrivacyState;  // Indicates the new state of the controller privacy: TRUE if enabled, FALSE if disabled
} GAPGenericEventControllerPrivacyStateChangedIndication_t;

typedef PACKED_STRUCT GAPGenericEventTxPowerLevelSetCompleteIndication_tag {
	uint8_t status;  // Indicates the status of the Set Tx Power Level request
} GAPGenericEventTxPowerLevelSetCompleteIndication_t;

/* Specifies the Phy event type */
typedef enum GAPGenericEventLePhyEventIndication_eventType_tag {
	GAPGenericEventLePhyEventIndication_eventType_gPhySetDefaultComplete_c = 0x00,
	GAPGenericEventLePhyEventIndication_eventType_gPhyRead_c = 0x01,
	GAPGenericEventLePhyEventIndication_eventType_gPhyUpdateComplete_c = 0x02
} GAPGenericEventLePhyEventIndication_eventType_t;

/* Specifies the Tx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type. */
typedef enum GAPGenericEventLePhyEventIndication_txPhy_tag {
	GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhy1M_c = 0x01,
	GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhy2M_c = 0x02,
	GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhyCoded_c = 0x03
} GAPGenericEventLePhyEventIndication_txPhy_t;

/* Specifies the Rx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type. */
typedef enum GAPGenericEventLePhyEventIndication_rxPhy_tag {
	GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhy1M_c = 0x01,
	GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhy2M_c = 0x02,
	GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhyCoded_c = 0x03
} GAPGenericEventLePhyEventIndication_rxPhy_t;

typedef PACKED_STRUCT GAPGenericEventLePhyEventIndication_tag {
	GAPGenericEventLePhyEventIndication_eventType_t eventType;  // Specifies the Phy event type
	uint8_t DeviceId;  // Device ID identifying the connection
	GAPGenericEventLePhyEventIndication_txPhy_t txPhy;  // Specifies the Tx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type.
	GAPGenericEventLePhyEventIndication_rxPhy_t rxPhy;  // Specifies the Rx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type.
} GAPGenericEventLePhyEventIndication_t;

/* Identity Address Type */
typedef enum GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_tag {
	GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_gPublic_c = 0x00,
	GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_gRandom_c = 0x01
} GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_t;

/* Privacy Mode */
typedef enum GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_tag {
	GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_gNetworkPrivacy_c = 0x00,
	GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_gDevicePrivacy_c = 0x01
} GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_t;

typedef struct GAPGetBondedDevicesIdentityInformationIndication_tag {
	uint8_t NbOfDeviceIdentityAddresses;  // The number of device identity addresses
	struct {
		GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_t IdentityAddressType;  // Identity Address Type
		uint8_t IdentityAddress[6];  // Identity Address
		uint8_t Irk[16];  // Identity Resolving Key
		GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_t PrivacyMode;  // Privacy Mode
	} *IdentityAddresses;  // Identity addresses list
} GAPGetBondedDevicesIdentityInformationIndication_t;

/* Event type */
typedef enum GAPControllerNotificationIndication_EventType_tag {
	GAPControllerNotificationIndication_EventType_gNotifConnEventOver_c = 0x01,
	GAPControllerNotificationIndication_EventType_gNotifConnRxPdu_c = 0x02,
	GAPControllerNotificationIndication_EventType_gNotifAdvEventOver_c = 0x04,
	GAPControllerNotificationIndication_EventType_gNotifAdvTx_c = 0x08,
	GAPControllerNotificationIndication_EventType_gNotifAdvScanReqRx_c = 0x10,
	GAPControllerNotificationIndication_EventType_gNotifAdvConnReqRx_c = 0x20,
	GAPControllerNotificationIndication_EventType_gNotifScanEventOver_c = 0x40,
	GAPControllerNotificationIndication_EventType_gNotifScanAdvPktRx_c = 0x80,
	GAPControllerNotificationIndication_EventType_gNotifScanRspRx_c = 0x0100,
	GAPControllerNotificationIndication_EventType_gNotifScanReqTx_c = 0x0200,
	GAPControllerNotificationIndication_EventType_gNotifConnCreated_c = 0x0400
} GAPControllerNotificationIndication_EventType_t;

typedef PACKED_STRUCT GAPControllerNotificationIndication_tag {
	GAPControllerNotificationIndication_EventType_t EventType;  // Event type
	uint8_t DeviceId;  // Device ID identifying the connection
	uint8_t RSSI;  // RSSI, valid for Rx event types
	uint8_t Channel;  // Channel, valid for conn event over or Rx/Tx events
	uint16_t ConnEvCounter;  // Connection event counter, valid for conn event over or Conn Rx event
	uint8_t Status;  // Status of the request to select which events to be enabled/disabled
	uint16_t Timestamp;  // Timestamp of the event, valid for conn created or Conn Rx event
	uint8_t AdvHandle;  // Advertising Handle, valid for advertising events from multiple sets
} GAPControllerNotificationIndication_t;

/* BLE Address Type */
typedef enum GAPBondCreatedIndication_AddrType_tag {
	GAPBondCreatedIndication_AddrType_gPublic_c = 0x00,
	GAPBondCreatedIndication_AddrType_gRandom_c = 0x01
} GAPBondCreatedIndication_AddrType_t;

typedef PACKED_STRUCT GAPBondCreatedIndication_tag {
	uint8_t NvmIndex;  // Index of the device in NVM bonding area
	GAPBondCreatedIndication_AddrType_t AddrType;  // BLE Address Type
	uint8_t Addr[6];  // BLE Address
} GAPBondCreatedIndication_t;

typedef PACKED_STRUCT GAPGenericEventChannelMapSetIndication_tag {
	uint16_t PayloadLength;  // The FSCI length field
} GAPGenericEventChannelMapSetIndication_t;

typedef PACKED_STRUCT GAPConnectionEventChannelMapReadIndication_tag {
	uint8_t DeviceId;  // Device ID identifying the connection
	uint8_t ChannelMap[5];  // Channel Map
} GAPConnectionEventChannelMapReadIndication_t;

/* Reason for channel read failure */
typedef enum GAPConnectionEventChannelMapReadFailureIndication_FailReason_tag {
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleSuccess_c = 0x0000,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleInvalidParameter_c = 0x0001,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOverflow_c = 0x0002,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleUnavailable_c = 0x0003,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleFeatureNotSupported_c = 0x0004,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOutOfMemory_c = 0x0005,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleAlreadyInitialized_c = 0x0006,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOsError_c = 0x0007,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleUnexpectedError_c = 0x0008,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleInvalidState_c = 0x0009,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleTimerError_c = 0x000A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownHciCommand_c = 0x0101,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownConnectionIdentifier_c = 0x0102,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciHardwareFailure_c = 0x0103,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPageTimeout_c = 0x0104,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAuthenticationFailure_c = 0x0105,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPinOrKeyMissing_c = 0x0106,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciMemoryCapacityExceeded_c = 0x0107,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTimeout_c = 0x0108,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionLimitExceeded_c = 0x0109,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c = 0x010A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAclConnectionAlreadyExists_c = 0x010B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCommandDisallowed_c = 0x010C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c = 0x010D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c = 0x010E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c = 0x010F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c = 0x0110,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c = 0x0111,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidHciCommandParameters_c = 0x0112,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteUserTerminatedConnection_c = 0x0113,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c = 0x0114,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c = 0x0115,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTerminatedByLocalHost_c = 0x0116,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRepeatedAttempts_c = 0x0117,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPairingNotAllowed_c = 0x0118,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownLpmPdu_c = 0x0119,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedRemoteFeature_c = 0x011A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoOffsetRejected_c = 0x011B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoIntervalRejected_c = 0x011C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoAirModeRejected_c = 0x011D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidLpmParameters_c = 0x011E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnspecifiedError_c = 0x011F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedLpmParameterValue_c = 0x0120,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleChangeNotAllowed_c = 0x0121,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLLResponseTimeout_c = 0x0122,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLmpErrorTransactionCollision_c = 0x0123,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLmpPduNotAllowed_c = 0x0124,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciEncryptionModeNotAcceptable_c = 0x0125,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLinkKeyCannotBeChanged_c = 0x0126,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRequestedQosNotSupported_c = 0x0127,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInstantPassed_c = 0x0128,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c = 0x0129,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciDifferentTransactionCollision_c = 0x012A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x2B_c = 0x012B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciQosNotAcceptableParameter_c = 0x012C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciQosRejected_c = 0x012D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciChannelClassificationNotSupported_c = 0x012E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInsufficientSecurity_c = 0x012F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciParameterOutOfMandatoryRange_c = 0x0130,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x31_c = 0x0131,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleSwitchPending_c = 0x0132,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x33_c = 0x0133,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReservedSlotViolation_c = 0x0134,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleSwitchFailed_c = 0x0135,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c = 0x0136,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c = 0x0137,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciHostBusyPairing_c = 0x0138,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c = 0x0139,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciControllerBusy_c = 0x013A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnacceptableConnectionParameters_c = 0x013B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciDirectedAdvertisingTimeout_c = 0x013C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c = 0x013D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = 0x013E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciMacConnectionFailed_c = 0x013F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCoarseClockAdjustmentRejected_c = 0x0140,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciType0SubmapNotDefined_c = 0x0141,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownAdvertisingIdentifier_c = 0x0142,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLimitReached_c = 0x0143,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciOperationCancelledByHost_c = 0x0144,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAlreadyInit_c = 0x01A0,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidParameter_c = 0x01A1,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCallbackNotInstalled_c = 0x01A2,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCallbackAlreadyInstalled_c = 0x01A3,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCommandNotSupported_c = 0x01A4,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciEventNotSupported_c = 0x01A5,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciTransportError_c = 0x01A6,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caAlreadyInit_c = 0x03F0,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caInsufficientResources_c = 0x03F1,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caCallbackNotInstalled_c = 0x03F2,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caCallbackAlreadyInstalled_c = 0x03F3,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmInvalid_c = 0x03F4,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmAlreadyRegistered_c = 0x03F5,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmNotRegistered_c = 0x03F6,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmInsufficientResources_c = 0x03F7,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelInvalid_c = 0x03F8,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelClosed_c = 0x03F9,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelAlreadyConnected_c = 0x03FA,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caConnectionParametersRejected_c = 0x03FB,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelBusy_c = 0x03FC,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caInvalidParameter_c = 0x03FE,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caError_c = 0x03FF,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmNullCBFunction_c = 0x0401,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmCommandNotSupported_c = 0x0402,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedCommand_c = 0x0403,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandCode_c = 0x0404,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandLength_c = 0x0405,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandParameter_c = 0x0406,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidDeviceId_c = 0x0407,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidInternalOperation_c = 0x0408,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidConnectionHandle_c = 0x0409,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInproperKeyDistributionField_c = 0x040A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedKeyType_c = 0x040B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedPairingTerminationReason_c = 0x040C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedKeyset_c = 0x040D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmSmpTimeoutOccurred_c = 0x040E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnknownSmpPacketType_c = 0x040F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidSmpPacketLength_c = 0x0410,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidSmpPacketParameter_c = 0x0411,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c = 0x0412,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c = 0x0413,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedUnexpectedHciEvent_c = 0x0414,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c = 0x0415,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidHciEventParameter_c = 0x0416,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmLlConnectionEncryptionInProgress_c = 0x0417,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmLlConnectionEncryptionFailure_c = 0x0418,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInsufficientResources_c = 0x0419,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmOobDataAddressMismatch_c = 0x041A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c = 0x041B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c = 0x041C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c = 0x041D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c = 0x041E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c = 0x041F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c = 0x0431,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorConfirmValueFailed_c = 0x0432,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorCommandNotSupported_c = 0x0433,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorInvalidParameters_c = 0x0434,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorUnknownReason_c = 0x0435,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c = 0x0460,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmTbInvalidDataSignature_c = 0x0461,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidHandle_c = 0x0501,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttReadNotPermitted_c = 0x0502,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttWriteNotPermitted_c = 0x0503,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidPdu_c = 0x0504,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientAuthentication_c = 0x0505,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttRequestNotSupported_c = 0x0506,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidOffset_c = 0x0507,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientAuthorization_c = 0x0508,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttPrepareQueueFull_c = 0x0509,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttAttributeNotFound_c = 0x050A,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttAttributeNotLong_c = 0x050B,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientEncryptionKeySize_c = 0x050C,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidAttributeValueLength_c = 0x050D,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttUnlikelyor_c = 0x050E,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientEncryption_c = 0x050F,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttUnsupportedGroupType_c = 0x0510,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientResources_c = 0x0511,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattAnotherProcedureInProgress_c = 0x0601,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattLongAttributePacketsCorrupted_c = 0x0602,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattMultipleAttributesOverflow_c = 0x0603,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c = 0x0604,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattInvalidValueLength_c = 0x0605,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattServerTimeout_c = 0x0606,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattIndicationAlreadyInProgress_c = 0x0607,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattClientConfirmationTimeout_c = 0x0608,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapAdvDataTooLong_c = 0x0701,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapScanRspDataTooLong_c = 0x0702,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapDeviceNotBonded_c = 0x0703,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapAnotherProcedureInProgress_c = 0x0704,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gDevDbCccdLimitReached_c = 0x0801,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gDevDbCccdNotFound_c = 0x0802,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbInvalidHandle_c = 0x0901,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbCharacteristicNotFound_c = 0x0902,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbCccdNotFound_c = 0x0903,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbServiceNotFound_c = 0x0904,
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbDescriptorNotFound_c = 0x0905
} GAPConnectionEventChannelMapReadFailureIndication_FailReason_t;

typedef PACKED_STRUCT GAPConnectionEventChannelMapReadFailureIndication_tag {
	GAPConnectionEventChannelMapReadFailureIndication_FailReason_t FailReason;  // Reason for channel read failure
} GAPConnectionEventChannelMapReadFailureIndication_t;

typedef PACKED_STRUCT GAPConnectionEventChannelSelectionAlgorithm2Indication_tag {
	uint8_t DeviceId;  // The DeviceId for which the command is intended
} GAPConnectionEventChannelSelectionAlgorithm2Indication_t;

typedef PACKED_STRUCT GAPGenericEventTxEntryAvailableIndication_tag {
	uint8_t DeviceId;  // The DeviceId for which the command is intended
} GAPGenericEventTxEntryAvailableIndication_t;

#endif  /* GAP_ENABLE */

typedef enum bleFsciIds_tag
{
	L2CAPCBRegisterLeCbCallbacksRequest_FSCI_ID = 0x4201,
	L2CAPCBRegisterLePsmRequest_FSCI_ID = 0x4202,
	L2CAPCBDeregisterLePsmRequest_FSCI_ID = 0x4203,
	L2CAPCBConnectLePsmRequest_FSCI_ID = 0x4204,
	L2CAPCBDisconnectLeCbChannelRequest_FSCI_ID = 0x4205,
	L2CAPCBCancelConnectionRequest_FSCI_ID = 0x4206,
	L2CAPCBSendLeCbDataRequest_FSCI_ID = 0x4207,
	L2CAPCBSendLeCreditRequest_FSCI_ID = 0x4208,
	GATTInitRequest_FSCI_ID = 0x4501,
	GATTGetMtuRequest_FSCI_ID = 0x4502,
	GATTClientInitRequest_FSCI_ID = 0x4503,
	GATTClientResetProcedureRequest_FSCI_ID = 0x4504,
	GATTClientRegisterProcedureCallbackRequest_FSCI_ID = 0x4505,
	GATTClientRegisterNotificationCallbackRequest_FSCI_ID = 0x4506,
	GATTClientRegisterIndicationCallbackRequest_FSCI_ID = 0x4507,
	GATTClientExchangeMtuRequest_FSCI_ID = 0x4508,
	GATTClientDiscoverAllPrimaryServicesRequest_FSCI_ID = 0x4509,
	GATTClientDiscoverPrimaryServicesByUuidRequest_FSCI_ID = 0x450A,
	GATTClientFindIncludedServicesRequest_FSCI_ID = 0x450B,
	GATTClientDiscoverAllCharacteristicsOfServiceRequest_FSCI_ID = 0x450C,
	GATTClientDiscoverCharacteristicOfServiceByUuidRequest_FSCI_ID = 0x450D,
	GATTClientDiscoverAllCharacteristicDescriptorsRequest_FSCI_ID = 0x450E,
	GATTClientReadCharacteristicValueRequest_FSCI_ID = 0x450F,
	GATTClientReadUsingCharacteristicUuidRequest_FSCI_ID = 0x4510,
	GATTClientReadMultipleCharacteristicValuesRequest_FSCI_ID = 0x4511,
	GATTClientWriteCharacteristicValueRequest_FSCI_ID = 0x4512,
	GATTClientReadCharacteristicDescriptorRequest_FSCI_ID = 0x4513,
	GATTClientWriteCharacteristicDescriptorRequest_FSCI_ID = 0x4514,
	GATTServerInitRequest_FSCI_ID = 0x4515,
	GATTServerRegisterCallbackRequest_FSCI_ID = 0x4516,
	GATTServerRegisterHandlesForWriteNotificationsRequest_FSCI_ID = 0x4517,
	GATTServerSendAttributeWrittenStatusRequest_FSCI_ID = 0x4518,
	GATTServerSendNotificationRequest_FSCI_ID = 0x4519,
	GATTServerSendIndicationRequest_FSCI_ID = 0x451A,
	GATTServerSendInstantValueNotificationRequest_FSCI_ID = 0x451B,
	GATTServerSendInstantValueIndicationRequest_FSCI_ID = 0x451C,
	GATTServerRegisterHandlesForReadNotificationsRequest_FSCI_ID = 0x451D,
	GATTServerSendAttributeReadStatusRequest_FSCI_ID = 0x451E,
	GATTServerRegisterUniqueHandlesForNotificationsRequest_FSCI_ID = 0x451F,
	GATTDBWriteAttributeRequest_FSCI_ID = 0x4602,
	GATTDBReadAttributeRequest_FSCI_ID = 0x4603,
	GATTDBFindServiceHandleRequest_FSCI_ID = 0x4604,
	GATTDBFindCharValueHandleInServiceRequest_FSCI_ID = 0x4605,
	GATTDBFindCccdHandleForCharValueHandleRequest_FSCI_ID = 0x4606,
	GATTDBFindDescriptorHandleForCharValueHandleRequest_FSCI_ID = 0x4607,
	GATTDBDynamicInitRequest_FSCI_ID = 0x4608,
	GATTDBDynamicReleaseDatabaseRequest_FSCI_ID = 0x4609,
	GATTDBDynamicAddPrimaryServiceDeclarationRequest_FSCI_ID = 0x460A,
	GATTDBDynamicAddSecondaryServiceDeclarationRequest_FSCI_ID = 0x460B,
	GATTDBDynamicAddIncludeDeclarationRequest_FSCI_ID = 0x460C,
	GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_FSCI_ID = 0x460D,
	GATTDBDynamicAddCharacteristicDescriptorRequest_FSCI_ID = 0x460E,
	GATTDBDynamicAddCccdRequest_FSCI_ID = 0x460F,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_FSCI_ID = 0x4610,
	GATTDBDynamicRemoveServiceRequest_FSCI_ID = 0x4611,
	GATTDBDynamicRemoveCharacteristicRequest_FSCI_ID = 0x4612,
	GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_FSCI_ID = 0x4613,
	BLEHostInitializeRequest_FSCI_ID = 0x4801,
	GAPRegisterDeviceSecurityRequirementsRequest_FSCI_ID = 0x4802,
	GAPSetAdvertisingParametersRequest_FSCI_ID = 0x4803,
	GAPSetAdvertisingDataRequest_FSCI_ID = 0x4804,
	GAPStartAdvertisingRequest_FSCI_ID = 0x4805,
	GAPStopAdvertisingRequest_FSCI_ID = 0x4806,
	GAPAuthorizeRequest_FSCI_ID = 0x4807,
	GAPSaveCccdRequest_FSCI_ID = 0x4808,
	GAPCheckNotificationStatusRequest_FSCI_ID = 0x4809,
	GAPCheckIndicationStatusRequest_FSCI_ID = 0x480A,
	GAPPairRequest_FSCI_ID = 0x480C,
	GAPSendSlaveSecurityRequestRequest_FSCI_ID = 0x480D,
	GAPEncryptLinkRequest_FSCI_ID = 0x480E,
	GAPAcceptPairingRequestRequest_FSCI_ID = 0x480F,
	GAPRejectPairingRequest_FSCI_ID = 0x4810,
	GAPEnterPasskeyRequest_FSCI_ID = 0x4811,
	GAPProvideOobRequest_FSCI_ID = 0x4812,
	GAPRejectPasskeyRequestRequest_FSCI_ID = 0x4813,
	GAPSendSmpKeysRequest_FSCI_ID = 0x4814,
	GAPRejectKeyExchangeRequestRequest_FSCI_ID = 0x4815,
	GAPProvideLongTermKeyRequest_FSCI_ID = 0x4816,
	GAPDenyLongTermKeyRequest_FSCI_ID = 0x4817,
	GAPLoadEncryptionInformationRequest_FSCI_ID = 0x4818,
	GAPSetLocalPasskeyRequest_FSCI_ID = 0x4819,
	GAPStartScanningRequest_FSCI_ID = 0x481A,
	GAPStopScanningRequest_FSCI_ID = 0x481B,
	GAPConnectRequest_FSCI_ID = 0x481C,
	GAPDisconnectRequest_FSCI_ID = 0x481D,
	GAPSaveCustomPeerInformationRequest_FSCI_ID = 0x481E,
	GAPLoadCustomPeerInformationRequest_FSCI_ID = 0x481F,
	GAPCheckIfBondedRequest_FSCI_ID = 0x4820,
	GAPReadWhiteListSizeRequest_FSCI_ID = 0x4821,
	GAPClearWhiteListRequest_FSCI_ID = 0x4822,
	GAPAddDeviceToWhiteListRequest_FSCI_ID = 0x4823,
	GAPRemoveDeviceFromWhiteListRequest_FSCI_ID = 0x4824,
	GAPReadPublicDeviceAddressRequest_FSCI_ID = 0x4825,
	GAPCreateRandomDeviceAddressRequest_FSCI_ID = 0x4826,
	GAPSaveDeviceNameRequest_FSCI_ID = 0x4827,
	GAPGetBondedDevicesCountRequest_FSCI_ID = 0x4828,
	GAPGetBondedDeviceNameRequest_FSCI_ID = 0x4829,
	GAPRemoveBondRequest_FSCI_ID = 0x482A,
	GAPRemoveAllBondsRequest_FSCI_ID = 0x482B,
	GAPReadRadioPowerLevelRequest_FSCI_ID = 0x482C,
	GAPVerifyPrivateResolvableAddressRequest_FSCI_ID = 0x482D,
	GAPSetRandomAddressRequest_FSCI_ID = 0x482E,
	GAPSetScanModeRequest_FSCI_ID = 0x482F,
	GAPSetDefaultPairingParametersRequest_FSCI_ID = 0x4830,
	GAPUpdateConnectionParametersRequest_FSCI_ID = 0x4831,
	GAPEnableUpdateConnectionParametersRequest_FSCI_ID = 0x4832,
	GapUpdateLeDataLengthRequest_FSCI_ID = 0x4833,
	GAPControllerResetRequest_FSCI_ID = 0x4834,
	GAPEnableHostPrivacyRequest_FSCI_ID = 0x4835,
	GAPEnableControllerPrivacyRequest_FSCI_ID = 0x4836,
	GAPLeScRegeneratePublicKeyRequest_FSCI_ID = 0x4837,
	GAPLeScValidateNumericValueRequest_FSCI_ID = 0x4838,
	GAPLeScGetLocalOobDataRequest_FSCI_ID = 0x4839,
	GAPLeScSetPeerOobDataRequest_FSCI_ID = 0x483A,
	GAPLeScSendKeypressNotificationPrivacyRequest_FSCI_ID = 0x483B,
	GAPGetBondedDevicesIdentityInformationRequest_FSCI_ID = 0x483C,
	GAPSetTxPowerLevelRequest_FSCI_ID = 0x483D,
	GAPLeReadPhyRequest_FSCI_ID = 0x483E,
	GAPLeSetPhyRequest_FSCI_ID = 0x483F,
	GAPLoadKeysRequest_FSCI_ID = 0x4841,
	GAPSaveKeysRequest_FSCI_ID = 0x4842,
	GAPSetChannelMapRequest_FSCI_ID = 0x4843,
	GAPReadChannelMapRequest_FSCI_ID = 0x4844,
	GAPSetPrivacyModeRequest_FSCI_ID = 0x4845,
	FSCICPUResetRequest_FSCI_ID = 0xA308,
	FSCIAllowDeviceToSleepRequest_FSCI_ID = 0xA370,
	FSCIGetWakeupReasonRequest_FSCI_ID = 0xA372,
	FSCIAckIndication_FSCI_ID = 0xA4FD,
	FSCIErrorIndication_FSCI_ID = 0xA4FE,
	FSCIAllowDeviceToSleepConfirm_FSCI_ID = 0xA470,
	FSCIWakeUpIndication_FSCI_ID = 0xA471,
	FSCIGetWakeupReasonResponse_FSCI_ID = 0xA472,
	L2CAPCBConfirm_FSCI_ID = 0x4280,
	L2CAPCBLePsmConnectionRequestIndication_FSCI_ID = 0x4281,
	L2CAPCBLePsmConnectionCompleteIndication_FSCI_ID = 0x4282,
	L2CAPCBLePsmDisconnectNotificationIndication_FSCI_ID = 0x4283,
	L2CAPCBNoPeerCreditsIndication_FSCI_ID = 0x4284,
	L2CAPCBLocalCreditsNotificationIndication_FSCI_ID = 0x4285,
	L2CAPCBLeCbDataIndication_FSCI_ID = 0x4286,
	L2CAPCBErrorIndication_FSCI_ID = 0x4287,
	GATTConfirm_FSCI_ID = 0x4580,
	GATTGetMtuIndication_FSCI_ID = 0x4581,
	GATTClientProcedureExchangeMtuIndication_FSCI_ID = 0x4582,
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_FSCI_ID = 0x4583,
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_FSCI_ID = 0x4584,
	GATTClientProcedureFindIncludedServicesIndication_FSCI_ID = 0x4585,
	GATTClientProcedureDiscoverAllCharacteristicsIndication_FSCI_ID = 0x4586,
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_FSCI_ID = 0x4587,
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_FSCI_ID = 0x4588,
	GATTClientProcedureReadCharacteristicValueIndication_FSCI_ID = 0x4589,
	GATTClientProcedureReadUsingCharacteristicUuidIndication_FSCI_ID = 0x458A,
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_FSCI_ID = 0x458B,
	GATTClientProcedureWriteCharacteristicValueIndication_FSCI_ID = 0x458C,
	GATTClientProcedureReadCharacteristicDescriptorIndication_FSCI_ID = 0x458D,
	GATTClientProcedureWriteCharacteristicDescriptorIndication_FSCI_ID = 0x458E,
	GATTClientNotificationIndication_FSCI_ID = 0x458F,
	GATTClientIndicationIndication_FSCI_ID = 0x4590,
	GATTServerMtuChangedIndication_FSCI_ID = 0x4591,
	GATTServerHandleValueConfirmationIndication_FSCI_ID = 0x4592,
	GATTServerAttributeWrittenIndication_FSCI_ID = 0x4593,
	GATTServerCharacteristicCccdWrittenIndication_FSCI_ID = 0x4594,
	GATTServerAttributeWrittenWithoutResponseIndication_FSCI_ID = 0x4595,
	GATTServerErrorIndication_FSCI_ID = 0x4596,
	GATTServerLongCharacteristicWrittenIndication_FSCI_ID = 0x4597,
	GATTServerAttributeReadIndication_FSCI_ID = 0x4598,
	GATTDBConfirm_FSCI_ID = 0x4680,
	GATTDBReadAttributeIndication_FSCI_ID = 0x4681,
	GATTDBFindServiceHandleIndication_FSCI_ID = 0x4682,
	GATTDBFindCharValueHandleInServiceIndication_FSCI_ID = 0x4683,
	GATTDBFindCccdHandleForCharValueHandleIndication_FSCI_ID = 0x4684,
	GATTDBFindDescriptorHandleForCharValueHandleIndication_FSCI_ID = 0x4685,
	GATTDBDynamicAddPrimaryServiceDeclarationIndication_FSCI_ID = 0x4686,
	GATTDBDynamicAddSecondaryServiceDeclarationIndication_FSCI_ID = 0x4687,
	GATTDBDynamicAddIncludeDeclarationIndication_FSCI_ID = 0x4688,
	GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_FSCI_ID = 0x4689,
	GATTDBDynamicAddCharacteristicDescriptorIndication_FSCI_ID = 0x468A,
	GATTDBDynamicAddCccdIndication_FSCI_ID = 0x468B,
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_FSCI_ID = 0x468C,
	GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_FSCI_ID = 0x468D,
	GAPConfirm_FSCI_ID = 0x4880,
	GAPCheckNotificationStatusIndication_FSCI_ID = 0x4881,
	GAPCheckIndicationStatusIndication_FSCI_ID = 0x4882,
	GAPLoadKeysIndication_FSCI_ID = 0x4883,
	GAPLoadEncryptionInformationIndication_FSCI_ID = 0x4884,
	GAPLoadCustomPeerInformationIndication_FSCI_ID = 0x4885,
	GAPCheckIfBondedIndication_FSCI_ID = 0x4886,
	GAPGetBondedDevicesCountIndication_FSCI_ID = 0x4887,
	GAPGetBondedDeviceNameIndication_FSCI_ID = 0x4888,
	GAPGenericEventInitializationCompleteIndication_FSCI_ID = 0x4889,
	GAPGenericEventInternalErrorIndication_FSCI_ID = 0x488A,
	GAPGenericEventAdvertisingSetupFailedIndication_FSCI_ID = 0x488B,
	GAPGenericEventAdvertisingParametersSetupCompleteIndication_FSCI_ID = 0x488C,
	GAPGenericEventAdvertisingDataSetupCompleteIndication_FSCI_ID = 0x488D,
	GAPGenericEventWhiteListSizeReadIndication_FSCI_ID = 0x488E,
	GAPGenericEventDeviceAddedToWhiteListIndication_FSCI_ID = 0x488F,
	GAPGenericEventDeviceRemovedFromWhiteListIndication_FSCI_ID = 0x4890,
	GAPGenericEventWhiteListClearedIndication_FSCI_ID = 0x4891,
	GAPGenericEventRandomAddressReadyIndication_FSCI_ID = 0x4892,
	GAPGenericEventCreateConnectionCanceledIndication_FSCI_ID = 0x4893,
	GAPGenericEventPublicAddressReadIndication_FSCI_ID = 0x4894,
	GAPGenericEventAdvTxPowerLevelReadIndication_FSCI_ID = 0x4895,
	GAPGenericEventPrivateResolvableAddressVerifiedIndication_FSCI_ID = 0x4896,
	GAPGenericEventRandomAddressSetIndication_FSCI_ID = 0x4897,
	GAPAdvertisingEventStateChangedIndication_FSCI_ID = 0x4898,
	GAPAdvertisingEventCommandFailedIndication_FSCI_ID = 0x4899,
	GAPScanningEventStateChangedIndication_FSCI_ID = 0x489A,
	GAPScanningEventCommandFailedIndication_FSCI_ID = 0x489B,
	GAPScanningEventDeviceScannedIndication_FSCI_ID = 0x489C,
	GAPConnectionEventConnectedIndication_FSCI_ID = 0x489D,
	GAPConnectionEventPairingRequestIndication_FSCI_ID = 0x489E,
	GAPConnectionEventSlaveSecurityRequestIndication_FSCI_ID = 0x489F,
	GAPConnectionEventPairingResponseIndication_FSCI_ID = 0x48A0,
	GAPConnectionEventAuthenticationRejectedIndication_FSCI_ID = 0x48A1,
	GAPConnectionEventPasskeyRequestIndication_FSCI_ID = 0x48A2,
	GAPConnectionEventOobRequestIndication_FSCI_ID = 0x48A3,
	GAPConnectionEventPasskeyDisplayIndication_FSCI_ID = 0x48A4,
	GAPConnectionEventKeyExchangeRequestIndication_FSCI_ID = 0x48A5,
	GAPConnectionEventKeysReceivedIndication_FSCI_ID = 0x48A6,
	GAPConnectionEventLongTermKeyRequestIndication_FSCI_ID = 0x48A7,
	GAPConnectionEventEncryptionChangedIndication_FSCI_ID = 0x48A8,
	GAPConnectionEventPairingCompleteIndication_FSCI_ID = 0x48A9,
	GAPConnectionEventDisconnectedIndication_FSCI_ID = 0x48AA,
	GAPConnectionEventRssiReadIndication_FSCI_ID = 0x48AB,
	GAPConnectionEventTxPowerLevelReadIndication_FSCI_ID = 0x48AC,
	GAPConnectionEventPowerReadFailureIndication_FSCI_ID = 0x48AD,
	GAPConnectionEventParameterUpdateRequestIndication_FSCI_ID = 0x48AE,
	GAPConnectionEventParameterUpdateCompleteIndication_FSCI_ID = 0x48AF,
	GAPConnectionEventLeDataLengthChangedIndication_FSCI_ID = 0x48B0,
	GAPConnectionEventLeScOobDataRequestIndication_FSCI_ID = 0x48B1,
	GAPConnectionEventLeScDisplayNumericValueIndication_FSCI_ID = 0x48B2,
	GAPConnectionEventLeScKeypressNotificationIndication_FSCI_ID = 0x48B3,
	GAPGenericEventControllerResetCompleteIndication_FSCI_ID = 0x48B4,
	GAPLeScPublicKeyRegeneratedIndication_FSCI_ID = 0x48B5,
	GAPGenericEventLeScLocalOobDataIndication_FSCI_ID = 0x48B6,
	GAPGenericEventHostPrivacyStateChangedIndication_FSCI_ID = 0x48B7,
	GAPGenericEventControllerPrivacyStateChangedIndication_FSCI_ID = 0x48B8,
	GAPGenericEventTxPowerLevelSetCompleteIndication_FSCI_ID = 0x48B9,
	GAPGenericEventLePhyEventIndication_FSCI_ID = 0x48BA,
	GAPGetBondedDevicesIdentityInformationIndication_FSCI_ID = 0x48BB,
	GAPControllerNotificationIndication_FSCI_ID = 0x48BC,
	GAPBondCreatedIndication_FSCI_ID = 0x48BD,
	GAPGenericEventChannelMapSetIndication_FSCI_ID = 0x48BE,
	GAPConnectionEventChannelMapReadIndication_FSCI_ID = 0x48BF,
	GAPConnectionEventChannelMapReadFailureIndication_FSCI_ID = 0x48C0,
	GAPConnectionEventChannelSelectionAlgorithm2Indication_FSCI_ID = 0x48D1,
	GAPGenericEventTxEntryAvailableIndication_FSCI_ID = 0x48D2,
} bleFsciIds_t;

typedef struct bleEvtContainer_tag
{
	uint16_t id;
	union {
#if FSCI_ENABLE
		FSCIAckIndication_t FSCIAckIndication;
		FSCIErrorIndication_t FSCIErrorIndication;
		FSCIAllowDeviceToSleepConfirm_t FSCIAllowDeviceToSleepConfirm;
		FSCIWakeUpIndication_t FSCIWakeUpIndication;
		FSCIGetWakeupReasonResponse_t FSCIGetWakeupReasonResponse;
#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
		L2CAPCBConfirm_t L2CAPCBConfirm;
		L2CAPCBLePsmConnectionRequestIndication_t L2CAPCBLePsmConnectionRequestIndication;
		L2CAPCBLePsmConnectionCompleteIndication_t L2CAPCBLePsmConnectionCompleteIndication;
		L2CAPCBLePsmDisconnectNotificationIndication_t L2CAPCBLePsmDisconnectNotificationIndication;
		L2CAPCBNoPeerCreditsIndication_t L2CAPCBNoPeerCreditsIndication;
		L2CAPCBLocalCreditsNotificationIndication_t L2CAPCBLocalCreditsNotificationIndication;
		L2CAPCBLeCbDataIndication_t L2CAPCBLeCbDataIndication;
		L2CAPCBErrorIndication_t L2CAPCBErrorIndication;
#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
		GATTConfirm_t GATTConfirm;
		GATTGetMtuIndication_t GATTGetMtuIndication;
		GATTClientProcedureExchangeMtuIndication_t GATTClientProcedureExchangeMtuIndication;
		GATTClientProcedureDiscoverAllPrimaryServicesIndication_t GATTClientProcedureDiscoverAllPrimaryServicesIndication;
		GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_t GATTClientProcedureDiscoverPrimaryServicesByUuidIndication;
		GATTClientProcedureFindIncludedServicesIndication_t GATTClientProcedureFindIncludedServicesIndication;
		GATTClientProcedureDiscoverAllCharacteristicsIndication_t GATTClientProcedureDiscoverAllCharacteristicsIndication;
		GATTClientProcedureDiscoverCharacteristicByUuidIndication_t GATTClientProcedureDiscoverCharacteristicByUuidIndication;
		GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_t GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication;
		GATTClientProcedureReadCharacteristicValueIndication_t GATTClientProcedureReadCharacteristicValueIndication;
		GATTClientProcedureReadUsingCharacteristicUuidIndication_t GATTClientProcedureReadUsingCharacteristicUuidIndication;
		GATTClientProcedureReadMultipleCharacteristicValuesIndication_t GATTClientProcedureReadMultipleCharacteristicValuesIndication;
		GATTClientProcedureWriteCharacteristicValueIndication_t GATTClientProcedureWriteCharacteristicValueIndication;
		GATTClientProcedureReadCharacteristicDescriptorIndication_t GATTClientProcedureReadCharacteristicDescriptorIndication;
		GATTClientProcedureWriteCharacteristicDescriptorIndication_t GATTClientProcedureWriteCharacteristicDescriptorIndication;
		GATTClientNotificationIndication_t GATTClientNotificationIndication;
		GATTClientIndicationIndication_t GATTClientIndicationIndication;
		GATTServerMtuChangedIndication_t GATTServerMtuChangedIndication;
		GATTServerHandleValueConfirmationIndication_t GATTServerHandleValueConfirmationIndication;
		GATTServerAttributeWrittenIndication_t GATTServerAttributeWrittenIndication;
		GATTServerCharacteristicCccdWrittenIndication_t GATTServerCharacteristicCccdWrittenIndication;
		GATTServerAttributeWrittenWithoutResponseIndication_t GATTServerAttributeWrittenWithoutResponseIndication;
		GATTServerErrorIndication_t GATTServerErrorIndication;
		GATTServerLongCharacteristicWrittenIndication_t GATTServerLongCharacteristicWrittenIndication;
		GATTServerAttributeReadIndication_t GATTServerAttributeReadIndication;
#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
		GATTDBConfirm_t GATTDBConfirm;
		GATTDBReadAttributeIndication_t GATTDBReadAttributeIndication;
		GATTDBFindServiceHandleIndication_t GATTDBFindServiceHandleIndication;
		GATTDBFindCharValueHandleInServiceIndication_t GATTDBFindCharValueHandleInServiceIndication;
		GATTDBFindCccdHandleForCharValueHandleIndication_t GATTDBFindCccdHandleForCharValueHandleIndication;
		GATTDBFindDescriptorHandleForCharValueHandleIndication_t GATTDBFindDescriptorHandleForCharValueHandleIndication;
		GATTDBDynamicAddPrimaryServiceDeclarationIndication_t GATTDBDynamicAddPrimaryServiceDeclarationIndication;
		GATTDBDynamicAddSecondaryServiceDeclarationIndication_t GATTDBDynamicAddSecondaryServiceDeclarationIndication;
		GATTDBDynamicAddIncludeDeclarationIndication_t GATTDBDynamicAddIncludeDeclarationIndication;
		GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_t GATTDBDynamicAddCharacteristicDeclarationAndValueIndication;
		GATTDBDynamicAddCharacteristicDescriptorIndication_t GATTDBDynamicAddCharacteristicDescriptorIndication;
		GATTDBDynamicAddCccdIndication_t GATTDBDynamicAddCccdIndication;
		GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_t GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication;
		GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_t GATTDBDynamicAddCharDescriptorWithUniqueValueIndication;
#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
		GAPConfirm_t GAPConfirm;
		GAPCheckNotificationStatusIndication_t GAPCheckNotificationStatusIndication;
		GAPCheckIndicationStatusIndication_t GAPCheckIndicationStatusIndication;
		GAPLoadKeysIndication_t GAPLoadKeysIndication;
		GAPLoadEncryptionInformationIndication_t GAPLoadEncryptionInformationIndication;
		GAPLoadCustomPeerInformationIndication_t GAPLoadCustomPeerInformationIndication;
		GAPCheckIfBondedIndication_t GAPCheckIfBondedIndication;
		GAPGetBondedDevicesCountIndication_t GAPGetBondedDevicesCountIndication;
		GAPGetBondedDeviceNameIndication_t GAPGetBondedDeviceNameIndication;
		GAPGenericEventInitializationCompleteIndication_t GAPGenericEventInitializationCompleteIndication;
		GAPGenericEventInternalErrorIndication_t GAPGenericEventInternalErrorIndication;
		GAPGenericEventAdvertisingSetupFailedIndication_t GAPGenericEventAdvertisingSetupFailedIndication;
		GAPGenericEventAdvertisingParametersSetupCompleteIndication_t GAPGenericEventAdvertisingParametersSetupCompleteIndication;
		GAPGenericEventAdvertisingDataSetupCompleteIndication_t GAPGenericEventAdvertisingDataSetupCompleteIndication;
		GAPGenericEventWhiteListSizeReadIndication_t GAPGenericEventWhiteListSizeReadIndication;
		GAPGenericEventDeviceAddedToWhiteListIndication_t GAPGenericEventDeviceAddedToWhiteListIndication;
		GAPGenericEventDeviceRemovedFromWhiteListIndication_t GAPGenericEventDeviceRemovedFromWhiteListIndication;
		GAPGenericEventWhiteListClearedIndication_t GAPGenericEventWhiteListClearedIndication;
		GAPGenericEventRandomAddressReadyIndication_t GAPGenericEventRandomAddressReadyIndication;
		GAPGenericEventCreateConnectionCanceledIndication_t GAPGenericEventCreateConnectionCanceledIndication;
		GAPGenericEventPublicAddressReadIndication_t GAPGenericEventPublicAddressReadIndication;
		GAPGenericEventAdvTxPowerLevelReadIndication_t GAPGenericEventAdvTxPowerLevelReadIndication;
		GAPGenericEventPrivateResolvableAddressVerifiedIndication_t GAPGenericEventPrivateResolvableAddressVerifiedIndication;
		GAPGenericEventRandomAddressSetIndication_t GAPGenericEventRandomAddressSetIndication;
		GAPAdvertisingEventStateChangedIndication_t GAPAdvertisingEventStateChangedIndication;
		GAPAdvertisingEventCommandFailedIndication_t GAPAdvertisingEventCommandFailedIndication;
		GAPScanningEventStateChangedIndication_t GAPScanningEventStateChangedIndication;
		GAPScanningEventCommandFailedIndication_t GAPScanningEventCommandFailedIndication;
		GAPScanningEventDeviceScannedIndication_t GAPScanningEventDeviceScannedIndication;
		GAPConnectionEventConnectedIndication_t GAPConnectionEventConnectedIndication;
		GAPConnectionEventPairingRequestIndication_t GAPConnectionEventPairingRequestIndication;
		GAPConnectionEventSlaveSecurityRequestIndication_t GAPConnectionEventSlaveSecurityRequestIndication;
		GAPConnectionEventPairingResponseIndication_t GAPConnectionEventPairingResponseIndication;
		GAPConnectionEventAuthenticationRejectedIndication_t GAPConnectionEventAuthenticationRejectedIndication;
		GAPConnectionEventPasskeyRequestIndication_t GAPConnectionEventPasskeyRequestIndication;
		GAPConnectionEventOobRequestIndication_t GAPConnectionEventOobRequestIndication;
		GAPConnectionEventPasskeyDisplayIndication_t GAPConnectionEventPasskeyDisplayIndication;
		GAPConnectionEventKeyExchangeRequestIndication_t GAPConnectionEventKeyExchangeRequestIndication;
		GAPConnectionEventKeysReceivedIndication_t GAPConnectionEventKeysReceivedIndication;
		GAPConnectionEventLongTermKeyRequestIndication_t GAPConnectionEventLongTermKeyRequestIndication;
		GAPConnectionEventEncryptionChangedIndication_t GAPConnectionEventEncryptionChangedIndication;
		GAPConnectionEventPairingCompleteIndication_t GAPConnectionEventPairingCompleteIndication;
		GAPConnectionEventDisconnectedIndication_t GAPConnectionEventDisconnectedIndication;
		GAPConnectionEventRssiReadIndication_t GAPConnectionEventRssiReadIndication;
		GAPConnectionEventTxPowerLevelReadIndication_t GAPConnectionEventTxPowerLevelReadIndication;
		GAPConnectionEventPowerReadFailureIndication_t GAPConnectionEventPowerReadFailureIndication;
		GAPConnectionEventParameterUpdateRequestIndication_t GAPConnectionEventParameterUpdateRequestIndication;
		GAPConnectionEventParameterUpdateCompleteIndication_t GAPConnectionEventParameterUpdateCompleteIndication;
		GAPConnectionEventLeDataLengthChangedIndication_t GAPConnectionEventLeDataLengthChangedIndication;
		GAPConnectionEventLeScOobDataRequestIndication_t GAPConnectionEventLeScOobDataRequestIndication;
		GAPConnectionEventLeScDisplayNumericValueIndication_t GAPConnectionEventLeScDisplayNumericValueIndication;
		GAPConnectionEventLeScKeypressNotificationIndication_t GAPConnectionEventLeScKeypressNotificationIndication;
		GAPGenericEventControllerResetCompleteIndication_t GAPGenericEventControllerResetCompleteIndication;
		GAPLeScPublicKeyRegeneratedIndication_t GAPLeScPublicKeyRegeneratedIndication;
		GAPGenericEventLeScLocalOobDataIndication_t GAPGenericEventLeScLocalOobDataIndication;
		GAPGenericEventHostPrivacyStateChangedIndication_t GAPGenericEventHostPrivacyStateChangedIndication;
		GAPGenericEventControllerPrivacyStateChangedIndication_t GAPGenericEventControllerPrivacyStateChangedIndication;
		GAPGenericEventTxPowerLevelSetCompleteIndication_t GAPGenericEventTxPowerLevelSetCompleteIndication;
		GAPGenericEventLePhyEventIndication_t GAPGenericEventLePhyEventIndication;
		GAPGetBondedDevicesIdentityInformationIndication_t GAPGetBondedDevicesIdentityInformationIndication;
		GAPControllerNotificationIndication_t GAPControllerNotificationIndication;
		GAPBondCreatedIndication_t GAPBondCreatedIndication;
		GAPGenericEventChannelMapSetIndication_t GAPGenericEventChannelMapSetIndication;
		GAPConnectionEventChannelMapReadIndication_t GAPConnectionEventChannelMapReadIndication;
		GAPConnectionEventChannelMapReadFailureIndication_t GAPConnectionEventChannelMapReadFailureIndication;
		GAPConnectionEventChannelSelectionAlgorithm2Indication_t GAPConnectionEventChannelSelectionAlgorithm2Indication;
		GAPGenericEventTxEntryAvailableIndication_t GAPGenericEventTxEntryAvailableIndication;
#endif  /* GAP_ENABLE */
	} Data;
} bleEvtContainer_t;

typedef memStatus_t (*pfnBleEvtHandler)(bleEvtContainer_t *container, uint8_t *pPayload);

typedef struct bleEvtHandler_tag
{
	uint16_t id;
	pfnBleEvtHandler handlerFunc;
} bleEvtHandler_t;


/*==================================================================================================
Public function prototypes
==================================================================================================*/
#if L2CAPCB_ENABLE
memStatus_t L2CAPCBRegisterLeCbCallbacksRequest(void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBRegisterLePsmRequest(L2CAPCBRegisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBDeregisterLePsmRequest(L2CAPCBDeregisterLePsmRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBConnectLePsmRequest(L2CAPCBConnectLePsmRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBDisconnectLeCbChannelRequest(L2CAPCBDisconnectLeCbChannelRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBCancelConnectionRequest(L2CAPCBCancelConnectionRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBSendLeCbDataRequest(L2CAPCBSendLeCbDataRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t L2CAPCBSendLeCreditRequest(L2CAPCBSendLeCreditRequest_t *req, void *arg, uint8_t fsciInterface);
#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
memStatus_t GATTInitRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTGetMtuRequest(GATTGetMtuRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientInitRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTClientResetProcedureRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTClientRegisterProcedureCallbackRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTClientRegisterNotificationCallbackRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTClientRegisterIndicationCallbackRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTClientExchangeMtuRequest(GATTClientExchangeMtuRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientDiscoverAllPrimaryServicesRequest(GATTClientDiscoverAllPrimaryServicesRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientDiscoverPrimaryServicesByUuidRequest(GATTClientDiscoverPrimaryServicesByUuidRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientFindIncludedServicesRequest(GATTClientFindIncludedServicesRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientDiscoverAllCharacteristicsOfServiceRequest(GATTClientDiscoverAllCharacteristicsOfServiceRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientDiscoverCharacteristicOfServiceByUuidRequest(GATTClientDiscoverCharacteristicOfServiceByUuidRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientDiscoverAllCharacteristicDescriptorsRequest(GATTClientDiscoverAllCharacteristicDescriptorsRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientReadCharacteristicValueRequest(GATTClientReadCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientReadUsingCharacteristicUuidRequest(GATTClientReadUsingCharacteristicUuidRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientReadMultipleCharacteristicValuesRequest(GATTClientReadMultipleCharacteristicValuesRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientWriteCharacteristicValueRequest(GATTClientWriteCharacteristicValueRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientReadCharacteristicDescriptorRequest(GATTClientReadCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTClientWriteCharacteristicDescriptorRequest(GATTClientWriteCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerInitRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTServerRegisterCallbackRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTServerRegisterHandlesForWriteNotificationsRequest(GATTServerRegisterHandlesForWriteNotificationsRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendAttributeWrittenStatusRequest(GATTServerSendAttributeWrittenStatusRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendNotificationRequest(GATTServerSendNotificationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendIndicationRequest(GATTServerSendIndicationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendInstantValueNotificationRequest(GATTServerSendInstantValueNotificationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendInstantValueIndicationRequest(GATTServerSendInstantValueIndicationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerRegisterHandlesForReadNotificationsRequest(GATTServerRegisterHandlesForReadNotificationsRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerSendAttributeReadStatusRequest(GATTServerSendAttributeReadStatusRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTServerRegisterUniqueHandlesForNotificationsRequest(GATTServerRegisterUniqueHandlesForNotificationsRequest_t *req, void *arg, uint8_t fsciInterface);
#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
memStatus_t GATTDBWriteAttributeRequest(GATTDBWriteAttributeRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBReadAttributeRequest(GATTDBReadAttributeRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBFindServiceHandleRequest(GATTDBFindServiceHandleRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBFindCharValueHandleInServiceRequest(GATTDBFindCharValueHandleInServiceRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBFindCccdHandleForCharValueHandleRequest(GATTDBFindCccdHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBFindDescriptorHandleForCharValueHandleRequest(GATTDBFindDescriptorHandleForCharValueHandleRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicInitRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicReleaseDatabaseRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddPrimaryServiceDeclarationRequest(GATTDBDynamicAddPrimaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddSecondaryServiceDeclarationRequest(GATTDBDynamicAddSecondaryServiceDeclarationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddIncludeDeclarationRequest(GATTDBDynamicAddIncludeDeclarationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddCharacteristicDescriptorRequest(GATTDBDynamicAddCharacteristicDescriptorRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddCccdRequest(void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicRemoveServiceRequest(GATTDBDynamicRemoveServiceRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicRemoveCharacteristicRequest(GATTDBDynamicRemoveCharacteristicRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GATTDBDynamicAddCharDescriptorWithUniqueValueRequest(GATTDBDynamicAddCharDescriptorWithUniqueValueRequest_t *req, void *arg, uint8_t fsciInterface);
#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
memStatus_t BLEHostInitializeRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPRegisterDeviceSecurityRequirementsRequest(GAPRegisterDeviceSecurityRequirementsRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetAdvertisingParametersRequest(GAPSetAdvertisingParametersRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetAdvertisingDataRequest(GAPSetAdvertisingDataRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPStartAdvertisingRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPStopAdvertisingRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPAuthorizeRequest(GAPAuthorizeRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSaveCccdRequest(GAPSaveCccdRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPCheckNotificationStatusRequest(GAPCheckNotificationStatusRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPCheckIndicationStatusRequest(GAPCheckIndicationStatusRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPPairRequest(GAPPairRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSendSlaveSecurityRequestRequest(GAPSendSlaveSecurityRequestRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPEncryptLinkRequest(GAPEncryptLinkRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPAcceptPairingRequestRequest(GAPAcceptPairingRequestRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRejectPairingRequest(GAPRejectPairingRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPEnterPasskeyRequest(GAPEnterPasskeyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPProvideOobRequest(GAPProvideOobRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRejectPasskeyRequestRequest(GAPRejectPasskeyRequestRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSendSmpKeysRequest(GAPSendSmpKeysRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRejectKeyExchangeRequestRequest(GAPRejectKeyExchangeRequestRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPProvideLongTermKeyRequest(GAPProvideLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPDenyLongTermKeyRequest(GAPDenyLongTermKeyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLoadEncryptionInformationRequest(GAPLoadEncryptionInformationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetLocalPasskeyRequest(GAPSetLocalPasskeyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPStartScanningRequest(GAPStartScanningRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPStopScanningRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPConnectRequest(GAPConnectRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPDisconnectRequest(GAPDisconnectRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSaveCustomPeerInformationRequest(GAPSaveCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLoadCustomPeerInformationRequest(GAPLoadCustomPeerInformationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPCheckIfBondedRequest(GAPCheckIfBondedRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPReadWhiteListSizeRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPClearWhiteListRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPAddDeviceToWhiteListRequest(GAPAddDeviceToWhiteListRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRemoveDeviceFromWhiteListRequest(GAPRemoveDeviceFromWhiteListRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPReadPublicDeviceAddressRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPCreateRandomDeviceAddressRequest(GAPCreateRandomDeviceAddressRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSaveDeviceNameRequest(GAPSaveDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPGetBondedDevicesCountRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPGetBondedDeviceNameRequest(GAPGetBondedDeviceNameRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRemoveBondRequest(GAPRemoveBondRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPRemoveAllBondsRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPReadRadioPowerLevelRequest(GAPReadRadioPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPVerifyPrivateResolvableAddressRequest(GAPVerifyPrivateResolvableAddressRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetRandomAddressRequest(GAPSetRandomAddressRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetScanModeRequest(GAPSetScanModeRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetDefaultPairingParametersRequest(GAPSetDefaultPairingParametersRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPUpdateConnectionParametersRequest(GAPUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPEnableUpdateConnectionParametersRequest(GAPEnableUpdateConnectionParametersRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GapUpdateLeDataLengthRequest(GapUpdateLeDataLengthRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPControllerResetRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPEnableHostPrivacyRequest(GAPEnableHostPrivacyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPEnableControllerPrivacyRequest(GAPEnableControllerPrivacyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLeScRegeneratePublicKeyRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPLeScValidateNumericValueRequest(GAPLeScValidateNumericValueRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLeScGetLocalOobDataRequest(void *arg, uint8_t fsciInterface);
memStatus_t GAPLeScSetPeerOobDataRequest(GAPLeScSetPeerOobDataRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLeScSendKeypressNotificationPrivacyRequest(GAPLeScSendKeypressNotificationPrivacyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPGetBondedDevicesIdentityInformationRequest(GAPGetBondedDevicesIdentityInformationRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetTxPowerLevelRequest(GAPSetTxPowerLevelRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLeReadPhyRequest(GAPLeReadPhyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLeSetPhyRequest(GAPLeSetPhyRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPLoadKeysRequest(GAPLoadKeysRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSaveKeysRequest(GAPSaveKeysRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetChannelMapRequest(GAPSetChannelMapRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPReadChannelMapRequest(GAPReadChannelMapRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t GAPSetPrivacyModeRequest(GAPSetPrivacyModeRequest_t *req, void *arg, uint8_t fsciInterface);
#endif  /* GAP_ENABLE */

#if FSCI_ENABLE
memStatus_t FSCICPUResetRequest(void *arg, uint8_t fsciInterface);
memStatus_t FSCIAllowDeviceToSleepRequest(FSCIAllowDeviceToSleepRequest_t *req, void *arg, uint8_t fsciInterface);
memStatus_t FSCIGetWakeupReasonRequest(void *arg, uint8_t fsciInterface);
#endif  /* FSCI_ENABLE */

void KHC_BLE_RX_MsgHandler(void *pData, void *param, uint8_t fsciInterface);

#endif  /* _BLE_CMD_H */
