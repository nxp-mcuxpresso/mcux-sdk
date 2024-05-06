/*
 * \file HeartRateSensor.c
 * Source file that demonstrates the Heart Rate Sensor profile for the
 * BLE stack, using C bindings generated from the BLE FSCI XML.
 *
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*==================================================================================================
Include Files
==================================================================================================*/
#define _BSD_SOURCE

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "FSCIFrame.h"
#include "Framer.h"
#include "PhysicalDevice.h"
#include "UARTConfiguration.h"

#include "ble_sig_defines.h"
#include "cmd_ble.h"

/*==================================================================================================
Private macros
==================================================================================================*/
#define FSCI_BLE_IF                         0

#define UuidToArray(arr, value) \
        arr[1] = value >> 8; \
        arr[0] = value & 0x00FF;

#define mMaxCharValueLength_d               23
#define mMaxGapAdStructures_d               5
#define mFastConnMinAdvInterval_c           32
#define mFastConnMaxAdvInterval_c           48
#define mAdvFullChannelMap                  (BIT2 | BIT1 | BIT0)

#define INVALID_HANDLE                      0xFFFF
#define INVALID_DEVICE_ID                   0xFF
#define HRS_SHORTENED_LOCAL_NAME            "HSDK_HRS"
#define HRS_DEMO_TIMEOUT                    100     /* time to sleep between commands in ms */
#define HRS_HEART_RATE_REPORT_INTERVAL      1       /* heart rate report interval in seconds  */
#define HRS_BATTERY_LEVEL_REPORT_INTERVAL   10      /* battery level report interval in seconds  */

/*==================================================================================================
Private type definitions
==================================================================================================*/
typedef enum hrsDemoState_tag {
    gHrsDemoAddServiceGatt_c,
    gHrsDemoAddServiceGap_c,
    gHrsDemoAddServiceHeartRate_c,
    gHrsDemoAddServiceBattery_c,
    gHrsDemoAddServiceDeviceInfo_c,
    gHrsDemoReadPublicAddress_c,
    gHrsDemoSetAdvData_c,
    gHrsDemoFindBatteryServiceHandle_c,
    gHrsDemoRegisterHandlesForWriteNotif_c,
    gHrsDemoFindHeartRateServiceHandle_c,
    gHrsDemoFindHrMeasurementHandle_c,
    gHrsDemoFindBodySensorLocationHandle_c,
    gHrsDemoFindBatteryLevelHandle_c,
    gHrsDemoWriteHrMeasurement_c,
    gHrsDemoWriteBodyLocation_c,
    gHrsDemoWriteBatteryLevel_c,
    gHrsDemoSetAdvParameters_c,
    gHrsDemoStartAdvertising_c,
    gHrsDemoSetupFinishedMessage,
    gHrsDemoWaitingConnection_c,
    gHrsDemoConnectionEstablished_c,
    gHrsDemoStartSendMeasurements,
    gHrsDemoStopSendMeasurements,
    gHrsDemoError_c
} hrsDemoState_t;

typedef enum hrsGattNotifyState_tag {
    gGetCccd_c,
    gGetNotificationStatus_c
} hrsGattNotifyState_t;

/*! Heart Rate Service - Energy expended status */
typedef enum {
    gHrs_EnergyExpendedDisabled_c = 0x00,
    gHrs_EnergyExpendedEnabled_c  = BIT3
} hrsFlagsEnergyExpended_tag;

/*! Heart Rate Service - Sensor Contact supported status */
typedef enum {
    gHrs_SensorContactNotSupported_c    = 0x00,
    gHrs_SensorContactSupported_c       = BIT2
} hrsFlagsSensorContactSupported_tag;

/*! Heart Rate Service - Sensor Contact detected status */
typedef enum {
    gHrs_SensorContactNotDetected_c    = 0x00,
    gHrs_SensorContactDetected_c       = BIT1
} hrsFlagsSensorContactDetected_tag;

/*! Heart Rate Service - Body Sensor Location */
typedef enum {
    gHrs_BodySensorLocOther_c = 0x00,
    gHrs_BodySensorLocChest_c = 0x01,
    gHrs_BodySensorLocWrist_c = 0x02,
    gHrs_BodySensorLocFinger_c = 0x03,
    gHrs_BodySensorLocHand_c = 0x04,
    gHrs_BodySensorLocEarLobe_c = 0x05,
    gHrs_BodySensorLocFoot_c = 0x06
} hrsBodySensorLoc_tag;

/*! Heart Rate Service - Heart Rate Format */
typedef enum {
    gHrs_8BitHeartRateFormat_c = 0x00,
    gHrs_16BitHeartRateFormat_c = BIT0
} hrsFlagsHeartRateFormat_tag;

/*==================================================================================================
Private prototypes
==================================================================================================*/
static void BleApp_Dispatcher(bleEvtContainer_t *container);
static void BleApp_DemoHrs(void);
static void BleApp_DemoHrsSm(void);

/*==================================================================================================
Private variables declarations
==================================================================================================*/
/* Framework variables */
static PhysicalDevice *mpDevice = NULL;
static Framer *mpFramer = NULL;
static UARTConfigurationData *mpUartConfig = NULL;

/* Scanning and Advertising Data */
static GAPSetAdvertisingDataRequest_t mAppAdvertisingData = { 0 };
static GAPSetAdvertisingParametersRequest_t mAdvParams = {
    /* minInterval */           mFastConnMinAdvInterval_c, \
    /* maxInterval */           mFastConnMaxAdvInterval_c, \
    /* advertisingType */       GAPSetAdvertisingParametersRequest_AdvertisingType_gConnectableUndirected_c, \
    /* addressType */           GAPSetAdvertisingParametersRequest_OwnAddressType_gPublic_c, \
    /* directedAddressType */   GAPSetAdvertisingParametersRequest_PeerAddressType_gPublic_c, \
    /* directedAddress */       {0, 0, 0, 0, 0, 0}, \
    /* channelMap */            mAdvFullChannelMap, \
    /* filterPolicy */          GAPSetAdvertisingParametersRequest_FilterPolicy_gProcessAll_c \
};

/* HRS variables */
static bool_t mSuppressBleEventPrint = FALSE;
static bool_t mbIsNotificationActive = FALSE;
static uint8_t mPeerDeviceId = INVALID_DEVICE_ID;
static uint8_t mHrsReportedValue = 0;
static uint16_t mLatestHandle = INVALID_HANDLE;
static uint16_t mNotifyHandle = INVALID_HANDLE;
static uint16_t mCccdHandle = INVALID_HANDLE;
static uint16_t mhServiceBattery;
static uint16_t mhServiceHeartRate;
static uint16_t mhValueHrMeasurement;
static uint16_t mhValueBodyLocation;
static uint16_t mhValueBatteryLevel;
static hrsDemoState_t mHrsDemoState = gHrsDemoAddServiceGatt_c;
static pthread_t mHrsReportThread;


/* GATT-DB */
static uint8_t mGattDbDynamic_GattServiceChangedInitValue[]                 = {0x00, 0x00, 0x00, 0x00};
static uint8_t mGattDbDynamic_GapServiceDeviceNameInitValue[]               = "Kinetis BLE";
static uint8_t mGattDbDynamic_GapServiceAppearanceInitValue[]               = {UuidArray(0)}; /* gUnknown_c */
static uint8_t mGattDbDynamic_GapServicePpcpInitValue[]                     = {0x0A, 0x00, 0x10, 0x00, 0x64, 0x00, 0xE2, 0x04};
static uint8_t mGattDbDynamic_HRServiceHrMeasurementInitValue[]             = {0x00, 0xB4};
static uint8_t mGattDbDynamic_HRServiceBodySensorLocationInitValue[]        = {0x01};
static uint8_t mGattDbDynamic_HRServiceHrControlPointInitValue[]            = {0x00};
static uint8_t mGattDbDynamic_BServiceLevelInitValue[]                      = {0x5A};
static uint8_t mGattDbDynamic_BServiceCharPresFormatDescriptorInitValue[]   = {0x04, 0x00, 0xAD, 0x27, 0x01, 0x00, 0x00};
static uint8_t mGattDbDynamic_DIServiceManufNameInitValue[]                 = "NXP";
static uint8_t mGattDbDynamic_DIServiceModelNbInitValue[]                   = "Kinetis BLE";
static uint8_t mGattDbDynamic_DIServiceSerialNoInitValue[]                  = "BLESN01";
static uint8_t mGattDbDynamic_DIServiceHwRevInitValue[]                     = "FRDM-KW36";
static uint8_t mGattDbDynamic_DIServiceFwRevInitValue[]                     = "1.3.2";
static uint8_t mGattDbDynamic_DIServiceSwRevInitValue[]                     = "1.3.2";
static uint8_t mGattDbDynamic_DIServiceSysIdInitValue[]                     = {0x00, 0x00, 0x00, 0xFE, 0xFF, 0x9F, 0x04, 0x00};
static uint8_t mGattDbDynamic_DIServiceIeeeRcdlInitValue[]                  = {0x00, 0x00, 0x00, 0x00};

/*==================================================================================================
Public prototypes
==================================================================================================*/
extern void SHELL_BleEventNotify(void *param);

/*==================================================================================================
Public global variables declarations
==================================================================================================*/

/*==================================================================================================
Private functions
==================================================================================================*/
/* Free resources when Ctrl-C is pressed. */
static void sig_handler(int signo)
{
    if (signo == SIGINT) {
        DestroyFramer(mpFramer);
        DestroyPhysicalDevice(mpDevice);
        freeConfigurationData(mpUartConfig);

        exit(0);
    }
}

/* Called on every received FSCI packet from the board. */
static void FSCI_RX_Callback(void *callee, void *response)
{
    static bleEvtContainer_t container;
    KHC_BLE_RX_MsgHandler(response, &container, FSCI_BLE_IF);
    DestroyFSCIFrame(response);

    if (!mSuppressBleEventPrint) {
        SHELL_BleEventNotify(&container);
    }

    BleApp_Dispatcher(&container);
}

/* Prints a buffer as space delimited hex numbers. */
static void NWKU_PrintArray(const char *tag, uint8_t *buf, int size)
{
    shell_printf("%s: ", tag);

    for (int i = 0; i < size; i++) {
        shell_printf("%02X ", buf[i]);
    }

    shell_printf("\n");
}

/* Prints a buffer as space delimited hex numbers, reversed. */
static void NWKU_PrintArrayReversed(const char *tag, uint8_t *buf, int size)
{
    shell_printf("%s: ", tag);

    for (int i = size - 1; i >= 0; i--) {
        shell_printf("%02X ", buf[i]);
    }

    shell_printf("\n");
}

/* Reverts a 32 bit numeric value. */
static uint32_t NWKU_Revert32(uint32_t value)
{
    return (uint32_t)(
               (value >> 24) |
               (value << 24) |
               ((value >> 8) & 0x0000FF00) |
               ((value << 8) & 0x00FF0000));
}

/* Converts a string into hex. */
static uint32_t NWKU_AsciiToHex
(
    uint8_t *pString,
    uint32_t strLen
)
{
    uint32_t length = strLen;
    uint32_t retValue = 0, hexDig = 0;
    bool_t validChar;

    while (length && pString) {
        hexDig = 0;
        validChar = FALSE;

        if (*pString >= '0' && *pString <= '9') {
            hexDig = *pString - '0';
            validChar = TRUE;
        }

        if (*pString >= 'a' && *pString <= 'f') {
            hexDig = *pString - 'a' + 10;
            validChar = TRUE;
        }

        if (*pString >= 'A' && *pString <= 'F') {
            hexDig = *pString - 'A' + 10;
            validChar = TRUE;
        }

        if (validChar == TRUE) {
            retValue = (retValue << 4) ^ hexDig;
        }

        pString++;
        length--;
    }

    return retValue;
}

/* Add advertising data to the global list. */
static void Gap_AppendAdvData
(
    GAPSetAdvertisingDataRequest_t *pAdvData,
    GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_t type,
    char *pData
)
{
    uint8_t i, advIdx = 0;
    uint8_t length;
    uint32_t number;

    if (pAdvData->AdvertisingData.AdStructures == NULL) {
        pAdvData->AdvertisingData.AdStructures =
            MEM_BufferAlloc(mMaxGapAdStructures_d * sizeof(pAdvData->AdvertisingData.AdStructures[0]));

        if (pAdvData->AdvertisingData.AdStructures == NULL) {
            shell_write("-->  GATTDB Event: Insufficient memory.\n");
            return;
        }

        FLib_MemSet(pAdvData->AdvertisingData.AdStructures, 0,
                    mMaxGapAdStructures_d * sizeof(pAdvData->AdvertisingData.AdStructures[0]));
    }

    advIdx = pAdvData->AdvertisingData.NbOfAdStructures;

    /* find existing entry */
    for (i = 0; i < pAdvData->AdvertisingData.NbOfAdStructures; i++) {
        if (pAdvData->AdvertisingData.AdStructures[i].Type == type) {
            advIdx = i;
            MEM_BufferFree(pAdvData->AdvertisingData.AdStructures[advIdx].Data);
            break;
        }
    }

    length = strlen(pData);

    switch (type) {
        case GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdShortenedLocalName_c:
        case GAPSetAdvertisingDataRequest_ScanResponseData_AdStructures_Type_gAdCompleteLocalName_c: {
            if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                pAdvData->AdvertisingData.AdStructures[advIdx].Data = MEM_BufferAlloc(length);

                if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                    shell_write("-->  GATTDB Event: Insufficient memory.\n");
                    return;
                }
            }

            FLib_MemCpy(pAdvData->AdvertisingData.AdStructures[advIdx].Data, pData, length);
        }
        break;

        case GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdIncomplete128bitServiceList_c:
        case GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdComplete128bitServiceList_c: {
            uint8_t serviceUuid[16];

            if (length != 32) {
                shell_write("-->  GATTDB Event: Bad formatting of 128-bit service value in hex.\n");
                return;
            }

            /* process 8 hex digits at a time, i.e uint32_t */
            for (i = 0; i < length; i += 8) {
                number = NWKU_Revert32(NWKU_AsciiToHex((uint8_t *)pData + i, 8));
                FLib_MemCpy(serviceUuid + i / 2, &number, sizeof(uint32_t));
            }

            if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                pAdvData->AdvertisingData.AdStructures[advIdx].Data = MEM_BufferAlloc(sizeof(serviceUuid));

                if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                    shell_write("-->  GATTDB Event: Insufficient memory.\n");
                    return;
                }
            }

            FLib_MemCpy(pAdvData->AdvertisingData.AdStructures[advIdx].Data, serviceUuid, sizeof(serviceUuid));
            length = length / 2;
        }
        break;

        default: {
            number = NWKU_AsciiToHex((uint8_t *)pData, length);
            /* halfen length - hex string */
            length = (length % 2) ? (length / 2) + 1 : (length / 2);

            if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                pAdvData->AdvertisingData.AdStructures[advIdx].Data = MEM_BufferAlloc(length);

                if (!pAdvData->AdvertisingData.AdStructures[advIdx].Data) {
                    shell_write("-->  GATTDB Event: Insufficient memory.\n");
                    return;
                }
            }

            FLib_MemCpy(pAdvData->AdvertisingData.AdStructures[advIdx].Data, &number, length);
        }
        break;
    }

    pAdvData->AdvertisingData.AdStructures[advIdx].Type = type;
    pAdvData->AdvertisingData.AdStructures[advIdx].Length = length;

    if (advIdx == pAdvData->AdvertisingData.NbOfAdStructures) {
        pAdvData->AdvertisingData.NbOfAdStructures += 1;
    }

    pAdvData->AdvertisingDataIncluded = TRUE;
}

/* Add a primary service declaration. */
static void GattDb_AddPrimaryServiceDecl(uint16_t serviceUuid)
{
    GATTDBDynamicAddPrimaryServiceDeclarationRequest_t req = { 0 };
    req.UuidType = Uuid16Bits;
    UuidToArray(req.Uuid.Uuid16Bits, serviceUuid);

    if (GATTDBDynamicAddPrimaryServiceDeclarationRequest(&req, mpFramer, FSCI_BLE_IF) != MEM_SUCCESS_c) {
        shell_write("-->  GATTDB Event: Insufficient memory.\n");
        SHELL_NEWLINE();
    }
}

/* Add a characteristic declaration with value. */
static void GattDb_AddCharDeclValue
(
    uint16_t charUuid,
    uint8_t properties,
    uint16_t length,
    uint8_t *value,
    GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_t permissions,
    bool_t varlen
)
{
    GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_t req;
    req.UuidType = Uuid16Bits;
    UuidToArray(req.Uuid.Uuid16Bits, charUuid);
    req.CharacteristicProperties = properties;

    if (varlen) {
        req.MaxValueLength = length < mMaxCharValueLength_d ? mMaxCharValueLength_d : length;
    } else {
        req.MaxValueLength = 0;  /* for fixed lengths this must be set to 0 */
    }

    req.InitialValueLength = length;
    req.InitialValue = value;
    req.ValueAccessPermissions = permissions;

    if (GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(&req, mpFramer, FSCI_BLE_IF) != MEM_SUCCESS_c) {
        shell_write("-->  GATTDB Event: Insufficient memory.\n");
        SHELL_NEWLINE();
    }
}

/* Add a characteristic descriptor. */
static void GattDb_AddCharDesc
(
    uint16_t charUuid,
    uint16_t length,
    uint8_t *value,
    GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_t permissions
)
{
    GATTDBDynamicAddCharacteristicDescriptorRequest_t req;
    req.UuidType = Uuid16Bits;
    UuidToArray(req.Uuid.Uuid16Bits, charUuid);
    req.DescriptorValueLength = length;
    req.Value = value;
    req.DescriptorAccessPermissions = permissions;

    if (GATTDBDynamicAddCharacteristicDescriptorRequest(&req, mpFramer, FSCI_BLE_IF) != MEM_SUCCESS_c) {
        shell_write("-->  GATTDB Event: Insufficient memory.\n");
        SHELL_NEWLINE();
    }
}

/* Add the GATT service. */
static void GattDb_AddServiceGatt(void)
{
    GattDb_AddPrimaryServiceDecl(gBleSig_GenericAttributeProfile_d);

    GattDb_AddCharDeclValue(
        gBleSig_GattServiceChanged_d,
        gRead_c | gNotify_c,
        sizeof(mGattDbDynamic_GattServiceChangedInitValue),
        mGattDbDynamic_GattServiceChangedInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionNone_c,
        FALSE
    );

    GATTDBDynamicAddCccdRequest(mpFramer, FSCI_BLE_IF);
}

/* Add the GAP service. */
static void GattDb_AddServiceGap(void)
{
    GattDb_AddPrimaryServiceDecl(gBleSig_GenericAccessProfile_d);

    GattDb_AddCharDeclValue(
        gBleSig_GapDeviceName_d,
        gRead_c,
        sizeof(mGattDbDynamic_GapServiceDeviceNameInitValue),
        mGattDbDynamic_GapServiceDeviceNameInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        TRUE
    );

    GattDb_AddCharDeclValue(
        gBleSig_GapAppearance_d,
        gRead_c,
        sizeof(mGattDbDynamic_GapServiceAppearanceInitValue),
        mGattDbDynamic_GapServiceAppearanceInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );

    GattDb_AddCharDeclValue(
        gBleSig_GapPpcp_d,
        gRead_c,
        sizeof(mGattDbDynamic_GapServicePpcpInitValue),
        mGattDbDynamic_GapServicePpcpInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );

    GATTDBDynamicAddCccdRequest(mpFramer, FSCI_BLE_IF);
}

/* Add the Heart Rate service. */
static void GattDb_AddServiceHeartRate(void)
{
    GattDb_AddPrimaryServiceDecl(gBleSig_HeartRateService_d);

    GattDb_AddCharDeclValue(
        gBleSig_HrMeasurement_d,
        gNotify_c,
        sizeof(mGattDbDynamic_HRServiceHrMeasurementInitValue),
        mGattDbDynamic_HRServiceHrMeasurementInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionNone_c,
        TRUE
    );
    GATTDBDynamicAddCccdRequest(mpFramer, FSCI_BLE_IF);

    GattDb_AddCharDeclValue(
        gBleSig_BodySensorLocation_d,
        gRead_c,
        sizeof(mGattDbDynamic_HRServiceBodySensorLocationInitValue),
        mGattDbDynamic_HRServiceBodySensorLocationInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );

    GattDb_AddCharDeclValue(
        gBleSig_HrControlPoint_d,
        gWrite_c,
        sizeof(mGattDbDynamic_HRServiceHrControlPointInitValue),
        mGattDbDynamic_HRServiceHrControlPointInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagWritable_c,
        FALSE
    );
}

/* Add the Battery service. */
static void GattDb_AddServiceBattery(void)
{
    GattDb_AddPrimaryServiceDecl(gBleSig_BatteryService_d);

    GattDb_AddCharDeclValue(
        gBleSig_BatteryLevel_d,
        gRead_c | gNotify_c,
        sizeof(mGattDbDynamic_BServiceLevelInitValue),
        mGattDbDynamic_BServiceLevelInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );

    GattDb_AddCharDesc(
        gBleSig_CharPresFormatDescriptor_d,
        sizeof(mGattDbDynamic_BServiceCharPresFormatDescriptorInitValue),
        mGattDbDynamic_BServiceCharPresFormatDescriptorInitValue,
        GATTDBDynamicAddCharacteristicDescriptorRequest_DescriptorAccessPermissions_gPermissionFlagReadable_c
    );

    GATTDBDynamicAddCccdRequest(mpFramer, FSCI_BLE_IF);
}

/* Add the Device Information service. */
static void GattDb_AddServiceDeviceInfo(void)
{
    GattDb_AddPrimaryServiceDecl(gBleSig_DeviceInformationService_d);

    GattDb_AddCharDeclValue(
        gBleSig_ManufacturerNameString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceManufNameInitValue),
        mGattDbDynamic_DIServiceManufNameInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_ModelNumberString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceModelNbInitValue),
        mGattDbDynamic_DIServiceModelNbInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_SerialNumberString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceSerialNoInitValue),
        mGattDbDynamic_DIServiceSerialNoInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_HardwareRevisionString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceHwRevInitValue),
        mGattDbDynamic_DIServiceHwRevInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_FirmwareRevisionString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceFwRevInitValue),
        mGattDbDynamic_DIServiceFwRevInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_SoftwareRevisionString_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceSwRevInitValue),
        mGattDbDynamic_DIServiceSwRevInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_SystemId_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceSysIdInitValue),
        mGattDbDynamic_DIServiceSysIdInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
    GattDb_AddCharDeclValue(
        gBleSig_IeeeRcdl_d,
        gRead_c,
        sizeof(mGattDbDynamic_DIServiceIeeeRcdlInitValue),
        mGattDbDynamic_DIServiceIeeeRcdlInitValue,
        GATTDBDynamicAddCharacteristicDeclarationAndValueRequest_ValueAccessPermissions_gPermissionFlagReadable_c,
        FALSE
    );
}

/* Check whether notifying is active and send the actual notification. */
static void Gatt_NotifySm(void *param)
{
    if ((hrsGattNotifyState_t)param == gGetCccd_c) {

        if (mCccdHandle == INVALID_HANDLE) {
            shell_write("-->  No CCCD found!\n");
        } else {
            GAPCheckNotificationStatusRequest_t req;
            req.DeviceId = mPeerDeviceId;
            req.Handle = mCccdHandle;
            GAPCheckNotificationStatusRequest(&req, mpFramer, FSCI_BLE_IF);

            mCccdHandle = INVALID_HANDLE;

            /* get to next state */
            usleep(HRS_DEMO_TIMEOUT * 1000);
            Gatt_NotifySm((void *)gGetNotificationStatus_c);
        }
    }

    else if ((hrsGattNotifyState_t)(param) == gGetNotificationStatus_c) {
        if (mbIsNotificationActive) {
            GATTServerSendNotificationRequest_t req;
            req.DeviceId = mPeerDeviceId;
            req.Handle = mNotifyHandle;
            GATTServerSendNotificationRequest(&req, mpFramer, FSCI_BLE_IF);

            mbIsNotificationActive = FALSE;
        }
    }
}

/* Get the CCCD handle and notify on it. */
static void Gatt_Notify(uint16_t handle)
{
    GATTDBFindCccdHandleForCharValueHandleRequest_t req;

    if (mPeerDeviceId == INVALID_DEVICE_ID) {
        shell_write("\t-->  Please connect the node first...\n");
        return;
    }

    mNotifyHandle = handle;

    /* Get handle of CCCD */
    req.CharValueHandle = mNotifyHandle;
    GATTDBFindCccdHandleForCharValueHandleRequest(&req, mpFramer, FSCI_BLE_IF);

    usleep(HRS_DEMO_TIMEOUT * 1000);
    Gatt_NotifySm((void *)gGetCccd_c);
}

/* Dispatcher for the events that are of interest for the Heart Rate demo. */
static void BleApp_Dispatcher(bleEvtContainer_t *container)
{
    switch (container->id) {

        case GATTDBDynamicAddPrimaryServiceDeclarationIndication_FSCI_ID:
            shell_printf("\tService Handle --> %d\n",
                         container->Data.GATTDBDynamicAddPrimaryServiceDeclarationIndication.ServiceHandle);
            break;

        case GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_FSCI_ID:
            shell_printf("\tCharacteristic Handle --> %d\n",
                         container->Data.GATTDBDynamicAddCharacteristicDeclarationAndValueIndication.CharacteristicHandle);
            break;

        case GATTDBDynamicAddCharacteristicDescriptorIndication_FSCI_ID:
            shell_printf("\tCharacteristic Descriptor Handle --> %d\n",
                         container->Data.GATTDBDynamicAddCharacteristicDescriptorIndication.DescriptorHandle);
            break;

        case GATTDBDynamicAddCccdIndication_FSCI_ID:
            shell_printf("\tCCCD Handle --> %d\n", container->Data.GATTDBDynamicAddCccdIndication.CCCDHandle);
            break;

        case GAPGenericEventPublicAddressReadIndication_FSCI_ID:
            NWKU_PrintArrayReversed("\tPublic Address", container->Data.GAPGenericEventPublicAddressReadIndication.Address,
                                    sizeof(container->Data.GAPGenericEventPublicAddressReadIndication.Address));
            break;

        case GATTDBFindServiceHandleIndication_FSCI_ID:
            mLatestHandle = container->Data.GATTDBFindServiceHandleIndication.ServiceHandle;
            shell_printf("\tService Handle --> %d\n", mLatestHandle);
            break;

        case GATTDBFindCharValueHandleInServiceIndication_FSCI_ID:
            mLatestHandle = container->Data.GATTDBFindCharValueHandleInServiceIndication.CharValueHandle;
            shell_printf("\tCharacteristic Value Handle --> %d\n", mLatestHandle);
            break;

        case GATTDBFindCccdHandleForCharValueHandleIndication_FSCI_ID:
            mCccdHandle = container->Data.GATTDBFindCccdHandleForCharValueHandleIndication.CccdHandle;
            break;

        case GAPCheckNotificationStatusIndication_FSCI_ID:
            mbIsNotificationActive = container->Data.GAPCheckNotificationStatusIndication.IsActive;
            break;

        case GAPConnectionEventConnectedIndication_FSCI_ID:
            mPeerDeviceId = container->Data.GAPConnectionEventConnectedIndication.DeviceId;
            NWKU_PrintArray("\tPeer Address", container->Data.GAPConnectionEventConnectedIndication.PeerAddress,
                            sizeof(container->Data.GAPConnectionEventConnectedIndication.PeerAddress));

            if (mHrsDemoState == gHrsDemoWaitingConnection_c) {
                mHrsDemoState = gHrsDemoStartSendMeasurements;
                mSuppressBleEventPrint = TRUE;
                BleApp_DemoHrsSm();
            }

            break;

        case GAPConnectionEventDisconnectedIndication_FSCI_ID:
            SHELL_BleEventNotify(container);

            mPeerDeviceId = INVALID_DEVICE_ID;

            if (mHrsDemoState == gHrsDemoConnectionEstablished_c) {
                mHrsDemoState = gHrsDemoStopSendMeasurements;
                mSuppressBleEventPrint = FALSE;
                BleApp_DemoHrsSm();
            }

            break;

        default:
            break;
    }
}

/* Function called periodically to notify Heart Rate values. */
static void BleApp_DemoHrsNotifyHr(void)
{
    if (mHrsDemoState != gHrsDemoConnectionEstablished_c) {
        shell_write("\t-->  Please connect the node first...\n");
        return;
    }

    uint8_t value[2];
    GATTDBWriteAttributeRequest_t req;

    req.Handle = mhValueHrMeasurement;
    req.ValueLength = 2;
    value[0] = gHrs_8BitHeartRateFormat_c;
    value[1] = mHrsReportedValue++;

    req.Value = value;
    GATTDBWriteAttributeRequest(&req, mpFramer, FSCI_BLE_IF);

    Gatt_Notify(mhValueHrMeasurement);
}

/* Function called periodically to notify Battery values. */
static void BleApp_DemoHrsNotifyBattery(void)
{
    if (mHrsDemoState != gHrsDemoConnectionEstablished_c) {
        shell_write("\t-->  Please connect the node first...\n");
        return;
    }

    GATTDBWriteAttributeRequest_t req;
    req.Handle = mhValueBatteryLevel;
    req.ValueLength = 1;
    req.Value = &mHrsReportedValue;

    GATTDBWriteAttributeRequest(&req, mpFramer, FSCI_BLE_IF);
}

/* HRS thread routine. */
static void *BleApp_DemoHrsThread(void *arg)
{
    uint64_t counter = 0;

    while (1) {
        sleep(1);
        counter++;

        /* check to see what we need to notify */
        if (counter % HRS_HEART_RATE_REPORT_INTERVAL == 0) {
            BleApp_DemoHrsNotifyHr();
        }

        if (counter % HRS_BATTERY_LEVEL_REPORT_INTERVAL == 0) {
            BleApp_DemoHrsNotifyBattery();
        }
    }

    return NULL;
}

/* HRS state machine. */
static void BleApp_DemoHrsSm(void)
{
    switch (mHrsDemoState) {
        case gHrsDemoAddServiceGatt_c:
            GattDb_AddServiceGatt();
            mHrsDemoState = gHrsDemoAddServiceGap_c;
            break;

        case gHrsDemoAddServiceGap_c:
            GattDb_AddServiceGap();
            mHrsDemoState = gHrsDemoAddServiceHeartRate_c;
            break;

        case gHrsDemoAddServiceHeartRate_c:
            GattDb_AddServiceHeartRate();
            mHrsDemoState = gHrsDemoAddServiceBattery_c;
            break;

        case gHrsDemoAddServiceBattery_c:
            GattDb_AddServiceBattery();
            mHrsDemoState = gHrsDemoAddServiceDeviceInfo_c;
            break;

        case gHrsDemoAddServiceDeviceInfo_c:
            GattDb_AddServiceDeviceInfo();
            mHrsDemoState = gHrsDemoReadPublicAddress_c;
            break;

        case gHrsDemoReadPublicAddress_c:
            GAPReadPublicDeviceAddressRequest(mpFramer, FSCI_BLE_IF);
            mHrsDemoState = gHrsDemoFindBatteryServiceHandle_c;
            break;

        case gHrsDemoFindBatteryServiceHandle_c: {
            GATTDBFindServiceHandleRequest_t req;
            req.StartHandle = 0x0001;  /* should be 0x0001 on the first call */
            req.UuidType = Uuid16Bits;
            UuidToArray(req.Uuid.Uuid16Bits, gBleSig_BatteryService_d);

            mLatestHandle = INVALID_HANDLE;
            GATTDBFindServiceHandleRequest(&req, mpFramer, FSCI_BLE_IF);
            mHrsDemoState = gHrsDemoRegisterHandlesForWriteNotif_c;
            break;
        }

        case gHrsDemoRegisterHandlesForWriteNotif_c: {
            if (mLatestHandle != INVALID_HANDLE) {
                uint16_t attrHandles[1] = {mLatestHandle};
                GATTServerRegisterHandlesForWriteNotificationsRequest_t req;
                req.HandleCount = 1;
                req.AttributeHandles = attrHandles;

                GATTServerRegisterHandlesForWriteNotificationsRequest(&req, mpFramer, FSCI_BLE_IF);
                GATTServerRegisterCallbackRequest(mpFramer, FSCI_BLE_IF);

                mhServiceBattery = mLatestHandle;
                mHrsDemoState = gHrsDemoFindHeartRateServiceHandle_c;
            } else {
                shell_write("-->  GATT DB: Could not find service handle for Battery.\n");
                mHrsDemoState = gHrsDemoError_c;
            }

            break;
        }

        case gHrsDemoFindHeartRateServiceHandle_c: {
            GATTDBFindServiceHandleRequest_t req;
            req.StartHandle = 0x0001;  /* should be 0x0001 on the first call */
            req.UuidType = Uuid16Bits;
            UuidToArray(req.Uuid.Uuid16Bits, gBleSig_HeartRateService_d);

            mLatestHandle = INVALID_HANDLE;
            GATTDBFindServiceHandleRequest(&req, mpFramer, FSCI_BLE_IF);
            mHrsDemoState = gHrsDemoFindHrMeasurementHandle_c;
            break;
        }

        case gHrsDemoFindHrMeasurementHandle_c: {
            if (mLatestHandle != INVALID_HANDLE) {
                GATTDBFindCharValueHandleInServiceRequest_t req;
                /* save previous handle requested */
                mhServiceHeartRate = mLatestHandle;

                req.ServiceHandle = mhServiceHeartRate;
                req.UuidType = Uuid16Bits;
                UuidToArray(req.Uuid.Uuid16Bits, gBleSig_HrMeasurement_d);

                mLatestHandle = INVALID_HANDLE;
                GATTDBFindCharValueHandleInServiceRequest(&req, mpFramer, FSCI_BLE_IF);

                mHrsDemoState = gHrsDemoFindBodySensorLocationHandle_c;
            } else {
                shell_write("-->  GATT DB: Could not find service handle for Heart Rate.\n");
                mHrsDemoState = gHrsDemoError_c;
            }

            break;
        }

        case gHrsDemoFindBodySensorLocationHandle_c: {
            if (mLatestHandle != INVALID_HANDLE) {
                GATTDBFindCharValueHandleInServiceRequest_t req;
                /* save previous handle requested */
                mhValueHrMeasurement = mLatestHandle;

                req.ServiceHandle = mhServiceHeartRate;
                req.UuidType = Uuid16Bits;
                UuidToArray(req.Uuid.Uuid16Bits, gBleSig_BodySensorLocation_d);

                mLatestHandle = INVALID_HANDLE;
                GATTDBFindCharValueHandleInServiceRequest(&req, mpFramer, FSCI_BLE_IF);

                mHrsDemoState = gHrsDemoFindBatteryLevelHandle_c;
            } else {
                shell_write("-->  GATT DB: Could not find char handle for Heart Rate Measurement.\n");
                mHrsDemoState = gHrsDemoError_c;
            }

            break;
        }

        case gHrsDemoFindBatteryLevelHandle_c: {
            if (mLatestHandle != INVALID_HANDLE) {
                /* save previous handle requested */
                mhValueBodyLocation = mLatestHandle;

                GATTDBFindCharValueHandleInServiceRequest_t req;
                req.ServiceHandle = mhServiceBattery;
                req.UuidType = Uuid16Bits;
                UuidToArray(req.Uuid.Uuid16Bits, gBleSig_BatteryLevel_d);

                mLatestHandle = INVALID_HANDLE;
                GATTDBFindCharValueHandleInServiceRequest(&req, mpFramer, FSCI_BLE_IF);

                mHrsDemoState = gHrsDemoWriteHrMeasurement_c;
            } else {
                shell_write("-->  GATT DB: Could not find char handle for Heart Rate Body Sensor Location.\n");
                mHrsDemoState = gHrsDemoError_c;
            }

            break;
        }

        case gHrsDemoWriteHrMeasurement_c: {
            if (mLatestHandle != INVALID_HANDLE) {
                GATTDBWriteAttributeRequest_t req;
                uint8_t value = (uint8_t)gHrs_EnergyExpendedEnabled_c | (uint8_t)gHrs_SensorContactSupported_c | (uint8_t)gHrs_SensorContactDetected_c;

                /* save previous handle requested */
                mhValueBatteryLevel = mLatestHandle;

                req.Handle = mhValueHrMeasurement;
                req.ValueLength = sizeof(value);
                req.Value = &value;

                GATTDBWriteAttributeRequest(&req, mpFramer, FSCI_BLE_IF);

                mHrsDemoState = gHrsDemoWriteBodyLocation_c;
            } else {
                shell_write("-->  GATT DB: Could not find char handle for Battery Level.\n");
                mHrsDemoState = gHrsDemoError_c;
            }

            break;
        }

        case gHrsDemoWriteBodyLocation_c: {
            GATTDBWriteAttributeRequest_t req;
            uint8_t value = gHrs_BodySensorLocChest_c;

            req.Handle = mhValueBodyLocation;
            req.ValueLength = sizeof(value);
            req.Value = &value;
            GATTDBWriteAttributeRequest(&req, mpFramer, FSCI_BLE_IF);

            mHrsDemoState = gHrsDemoWriteBatteryLevel_c;
            break;
        }

        case gHrsDemoWriteBatteryLevel_c: {
            GATTDBWriteAttributeRequest_t req;
            uint8_t value = 100;  /* 100% battery level */

            req.Handle = mhValueBatteryLevel;
            req.ValueLength = sizeof(value);
            req.Value = &value;
            GATTDBWriteAttributeRequest(&req, mpFramer, FSCI_BLE_IF);

            mHrsDemoState = gHrsDemoSetAdvParameters_c;
            break;
        }

        case gHrsDemoSetAdvParameters_c:
            GAPSetAdvertisingParametersRequest(&mAdvParams, mpFramer, FSCI_BLE_IF);
            mHrsDemoState = gHrsDemoSetAdvData_c;
            break;
        
        case gHrsDemoSetAdvData_c: {
            char gBleSig_HeartRateService_d_str[5];
            sprintf(gBleSig_HeartRateService_d_str, "%04X", gBleSig_HeartRateService_d);

            Gap_AppendAdvData(&mAppAdvertisingData,
                              GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdFlags_c,
                              "6");    /* gLeGeneralDiscoverableMode_c | gBrEdrNotSupported_c */
            Gap_AppendAdvData(&mAppAdvertisingData,
                              GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdIncomplete16bitServiceList_c,
                              gBleSig_HeartRateService_d_str);
            Gap_AppendAdvData(&mAppAdvertisingData,
                              GAPSetAdvertisingDataRequest_AdvertisingData_AdStructures_Type_gAdShortenedLocalName_c,
                              HRS_SHORTENED_LOCAL_NAME);
            GAPSetAdvertisingDataRequest(&mAppAdvertisingData, mpFramer, FSCI_BLE_IF);

            mHrsDemoState = gHrsDemoStartAdvertising_c;
            break;
        }

        

        case gHrsDemoStartAdvertising_c:
            GAPStartAdvertisingRequest(mpFramer, FSCI_BLE_IF);
            mHrsDemoState = gHrsDemoSetupFinishedMessage;
            break;

        case gHrsDemoSetupFinishedMessage:
            shell_printf("\n-->  Setup finished, please open IoT Toolbox -> Heart Rate -> %s\n", HRS_SHORTENED_LOCAL_NAME);
            mHrsDemoState = gHrsDemoWaitingConnection_c;
            break;

        case gHrsDemoWaitingConnection_c:
            shell_write("\n-->  Waiting connection from a smartphone..\n");
            break;

        case gHrsDemoStartSendMeasurements:

            /* start HRS thread */
            if (pthread_create(&mHrsReportThread, NULL, &BleApp_DemoHrsThread, NULL) != 0) {
                shell_printf("HRS thread creation failed!\n");
                return;
            } else {
                shell_write("-->  Started to send HRS measurements to IoT Toolbox\n");
            }

            mHrsDemoState = gHrsDemoConnectionEstablished_c;
            return;

        case gHrsDemoStopSendMeasurements:
            if (pthread_cancel(mHrsReportThread) != 0) {
                shell_printf("HRS thread cancellation failed!\n");
            } else {
                shell_write("-->  Stopped sending HRS measurements to IoT Toolbox. Re-advertising..\n");
            }

            mHrsDemoState = gHrsDemoStartAdvertising_c;
            break;

        default:
            break;
    }

    if ((mHrsDemoState != gHrsDemoError_c) && (mHrsDemoState != gHrsDemoWaitingConnection_c)) {
        usleep(HRS_DEMO_TIMEOUT * 1000);
        BleApp_DemoHrsSm();
    }
}

/* HRS demo entry point. */
static void BleApp_DemoHrs(void)
{
    FSCICPUResetRequest(mpFramer, FSCI_BLE_IF);
    sleep(7);
    BleApp_DemoHrsSm();

    while (1) {
        sleep(1);
    }
}

/*==================================================================================================
Private debug functions
==================================================================================================*/

/*==================================================================================================
Public functions
==================================================================================================*/
int main(int argc, char **argv)
{
    /* Check number of arguments. */
    if (argc < 2) {
        shell_printf("Usage: # %s </dev/ttyACMx | /dev/ttymxcx>\n", argv[0]);
        exit(1);
    }

    /* Add signal handler for SIGINT. */
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        shell_printf("Cannot catch SIGINT\n");
    }

    /* Open device and create FSCI framer. */
    mpUartConfig = defaultConfigurationData();
    mpDevice = InitPhysicalDevice(UART, mpUartConfig, argv[1], GLOBAL);
    mpFramer = InitializeFramer(mpDevice, FSCI, FSCI_LENGTH_FIELD_SIZE, 1, _LITTLE_ENDIAN);
    OpenPhysicalDevice(mpDevice);
    AttachToFramer(mpFramer, NULL, FSCI_RX_Callback);

    /* Run Demo */
    BleApp_DemoHrs();

    return 0;
}
