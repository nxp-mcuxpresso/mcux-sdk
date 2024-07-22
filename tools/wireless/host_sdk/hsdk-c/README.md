# FSCI Host Sample Interface for a Kinetis-W Black Box

## demo

Heart Rate Sensor profile supported.
```bash
$ make; ./HeartRateSensor /dev/ttyACM1
[...]
GAPGenericEventInitializationCompleteIndication
[...]
-->  Setup finished, please open IoT Toolbox -> Heart Rate -> HSDK_HRS
GAPConnectionEventConnectedIndication -> gRandom_c
        Peer Address: 43 E3 DE F2 78 7F
-->  Started to send HRS measurements to IoT Toolbox
[User terminates connection]
GAPConnectionEventDisconnectedIndication -> gHciRemoteUserTerminatedConnection_c
-->  Stopped sending HRS measurements to IoT Toolbox. Re-advertising..

-->  Setup finished, please open IoT Toolbox -> Heart Rate -> HSDK_HRS
```

## inc

Header file cmd_<name>.h is generated from the correspondent <NAME>.xml FSCI XML file.
- Enumerations
```c
/* Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device */
typedef enum GAPConnectRequest_FilterPolicy_tag {
    GAPConnectRequest_FilterPolicy_gUseDeviceAddress_c = 0x00,
    GAPConnectRequest_FilterPolicy_gUseWhiteList_c = 0x01
} GAPConnectRequest_FilterPolicy_t;
```

- Structures
```c
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
} GAPConnectRequest_t;
```
- Container for all possible event types
```c
typedef struct bleEvtContainer_tag
{
    uint16_t id;
    union {
        [...]
        GAPConnectionEventConnectedIndication_t GAPConnectionEventConnectedIndication;
        [...]
    } Data
} bleEvtContainer_t;
```
- Prototypes for sending commands
```c
    memStatus_t GAPConnectRequest(GAPConnectRequest_t *req, void *arg, uint8_t fsciInterface);
```

Header file os_abstraction.h provides the required symbols for building the generated interface.
When integrating in a project different that Host SDK, the user needs to provide the implementation for
```c
void FSCI_transmitPayload(void *arg,            /* Optional argument passed to the function */
                          uint8_t og,           /* FSCI operation group */
                          uint8_t oc,           /* FSCI operation code */
                          void *msg,            /* Pointer to payload */
                          uint16_t msgLen,      /* Payload length */
                          uint8_t fsciInterface /* FSCI interface ID */
                         );
```

that creates and sends the FSCI packet: 0x02 | og | oc | msgLen | msg | crc +- fsciInterface

## res

Source files cmd_<name>.c, evt_<name>.c and evt_printer_<name>.c are generated from the
correspondent <NAME>.xml FSCI XML file.

cmd_<name>.c
- Functions that handle command serialization
```c
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
```

evt_<name>.c
- Event dispatcher
```c
void KHC_BLE_RX_MsgHandler(void *pData, void *param, uint8_t fsciInterface)
{
    if (!pData || !param)
    {
        return;
    }

    fsciPacket_t *frame = (fsciPacket_t *)pData;
    bleEvtContainer_t *container = (bleEvtContainer_t *)param;
    uint8_t og = frame->opGroup;
    uint8_t oc = frame->opCode;
    uint8_t *pPayload = frame->data;
    uint16_t id = (og << 8) + oc, i;

    for (i = 0; i < sizeof(evtHandlerTbl) / sizeof(evtHandlerTbl[0]); i++)
    {
        if (evtHandlerTbl[i].id == id)
        {
            evtHandlerTbl[i].handlerFunc(container, pPayload);
            break;
        }
    }
}
```
- Handler functions to perform event de-serialization
```c
static memStatus_t Load_GAPConnectionEventConnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
    GAPConnectionEventConnectedIndication_t *evt = &(container->Data.GAPConnectionEventConnectedIndication);

    uint32_t idx = 0;

    /* Store (OG, OC) in ID */
    container->id = 0x489D;

    evt->DeviceId = pPayload[idx]; idx++;
    FLib_MemCpy(&(evt->ConnectionParameters.ConnInterval), pPayload + idx, sizeof(evt->ConnectionParameters.ConnInterval)); idx += sizeof(evt->ConnectionParameters.ConnInterval);
    FLib_MemCpy(&(evt->ConnectionParameters.ConnLatency), pPayload + idx, sizeof(evt->ConnectionParameters.ConnLatency)); idx += sizeof(evt->ConnectionParameters.ConnLatency);
    FLib_MemCpy(&(evt->ConnectionParameters.SupervisionTimeout), pPayload + idx, sizeof(evt->ConnectionParameters.SupervisionTimeout)); idx += sizeof(evt->ConnectionParameters.SupervisionTimeout);
    evt->ConnectionParameters.MasterClockAccuracy = (GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_t)pPayload[idx]; idx++;
    evt->PeerAddressType = (GAPConnectionEventConnectedIndication_PeerAddressType_t)pPayload[idx]; idx++;
    FLib_MemCpy(evt->PeerAddress, pPayload + idx, 6); idx += 6;
    evt->peerRpaResolved = (bool_t)pPayload[idx]; idx++;
    evt->localRpaUsed = (bool_t)pPayload[idx]; idx++;

    return MEM_SUCCESS_c;
}
```

evt_printer_<name>.c
- Prints events statuses to the console
```c
void SHELL_BleEventNotify(void *param)
{
    bleEvtContainer_t *container = (bleEvtContainer_t *)param;

    switch (container->id) {
        [...]
        case 0x489D:
            shell_write("GAPConnectionEventConnectedIndication");
            shell_write(" -> ");
            switch (container->Data.GAPConnectionEventConnectedIndication.PeerAddressType)
            {
                case GAPConnectionEventConnectedIndication_PeerAddressType_gPublic_c:
                    shell_write(gPublic_c);
                    break;
                case GAPConnectionEventConnectedIndication_PeerAddressType_gRandom_c:
                    shell_write(gRandom_c);
                    break;
                default:
                    shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventConnectedIndication.PeerAddressType);
                    break;
            }
            break;
        [...]
    }
```
