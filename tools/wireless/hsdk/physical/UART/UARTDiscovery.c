/*
 * \file UARTDiscovery.c
 * This is a source file for the UARTDiscovery module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "UARTDiscovery.h"

#include "hsdkError.h"
#include "utils.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define MAXNAME                 257
#define KNOWN_VID_PID_PAIRS     12  /* increment whenever a new device is added */

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef struct _list {
    void *data;         /**< Generic pointer to data stored into the node. */
    uint8_t found;      /**< Self-explanatory flag. */
    struct _list *next; /**< Pointer to the next element in the list. */
} Node;

//! A pair type for more complex embedding of structures
typedef struct _tuple {
    void *fst;
    void *snd;
} Pair;

/**
 * @brief A structure for the framer object.
 */
typedef struct {
    EventManager *evtManager;
    Thread thread;      /**< The thread of the framer. */
    Event stopThread;   /**< Event to stop the thread on destruction. */
    Node *currentActiveDevices;
    Node *listOfFSIdentities;
} DeviceManager;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void *DeviceNotificationRoutine(void *lpParameter);
static Node *CreateNode(void *pData);
static DeviceNotification *CreateNotification(Node *oldNode, DeviceNotificationEvent notification);
static int DestroyNode(Node *pNode);
static void UpdateListOfDevices(Node **head, Node *data, uint8_t notify);
static void RemoveNotFound(Node **head, uint8_t notify);
static void SetState(DeviceState *device);
static void CreateListOfKinetisWIdentities();
static void CreateInitialList();
static void DestroyIdentifierNode(void *data);

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static DeviceManager *deviceManager = NULL;
static Lock listLock;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief Creates and starts the DeviceManager. It also creates an initial list of all
* devices already present in the system.
*
* \return nothing
********************************************************************************** */
void InitializeDeviceManager()
{
    listLock = HSDKCreateLock();

    deviceManager = (DeviceManager *)calloc(1, sizeof(DeviceManager));
    if (deviceManager == NULL) {
        return;
    }

    deviceManager->evtManager = CreateEventManager();
    deviceManager->stopThread = HSDKCreateEvent(0);
    deviceManager->currentActiveDevices = NULL;
    deviceManager->listOfFSIdentities = NULL;

    CreateListOfKinetisWIdentities();
    CreateInitialList();

    deviceManager->thread = HSDKCreateThread(DeviceNotificationRoutine, deviceManager);
}

/*! *********************************************************************************
* \brief Stops and deallocates the DeviceManager
*
* \return nothing
********************************************************************************** */
void DestroyDeviceManager()
{
    HSDKSignalEvent(deviceManager->stopThread);

    HSDKDestroyThread(deviceManager->thread);
    DestroyEventManager(deviceManager->evtManager);

    HSDKAcquireLock(listLock);

    Node *crt = deviceManager->currentActiveDevices;
    while (crt != NULL) {
        DestroyDeviceState((DeviceState *)crt->data);
        crt->data = NULL;

        crt = crt->next;
    }

    crt = deviceManager->currentActiveDevices;
    while (crt != NULL) {
        DestroyIdentifierNode(crt->data);
        crt->data = NULL;

        crt = crt->next;
    }

    HSDKReleaseLock(listLock);

    free(deviceManager);

    HSDKDestroyLock(listLock);
}

/*! *********************************************************************************
* \brief  Subscribe to receive device state change notifications.
*
* \param[in] observer   the element that subscribes to device. Used as an identifier for the callback.
* \param[in] Callback   a function pointer to the callback
*
* \return nothing
********************************************************************************** */
void AttachToDeviceNotification(void *observer, void(*Callback) (void *, void *))
{
    RegisterToEventManager(deviceManager->evtManager, observer, Callback);
}

/*! *********************************************************************************
* \brief  Unsubscribe from the change notification stream
*
* \param[in] observer   the observer who unsubscribes
*
* \return nothing
********************************************************************************** */
void DetachFromDeviceNotification(void *observer)
{
    DeregisterFromEvent(deviceManager->evtManager, observer);
}

/*! *********************************************************************************
* \brief  Deallocates a DeviceState
*
* \param[in] deviceState    a DeviceState value
*
* \return nothing
********************************************************************************** */
void DestroyDeviceState(DeviceState *deviceState)
{
    if (deviceState != NULL) {
        if (deviceState->friendlyName != NULL) {
            free(deviceState->friendlyName);
        }

        if (deviceState->deviceName != NULL) {
            free(deviceState->deviceName);
        }

#ifdef _WIN32
        if (deviceState->vid != NULL) {
            free(deviceState->vid);
        }

        if (deviceState->pid != NULL) {
            free(deviceState->pid);
        }
#endif
        free(deviceState);
    }
}

/*! *********************************************************************************
* \brief  Deallocates a DeviceNotification
*
* \param[in] deviceNotification a DeviceNotification value
*
* \return nothing
********************************************************************************** */
void DestroyDeviceNotification(DeviceNotification *deviceNotification)
{
    DestroyDeviceState(deviceNotification->state);
    free(deviceNotification);
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief  Allocates a wrapper Node for the data.
*
* \param[in] pData  a generic pointer value to be added in a list
*
* \return Node
********************************************************************************** */
static Node *CreateNode(void *pData)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = pData;
    node->found = 0;
    node->next = NULL;

    return node;
}

/*! *********************************************************************************
* \brief  Deallocates a Node
*
* \param[in] pNode  a Node value
*
* \return HSDK_ERROR_SUCCESS
********************************************************************************** */
static int DestroyNode(Node *pNode)
{
    pNode->data = NULL;
    pNode->next = NULL;

    free(pNode);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Deallocates a DeviceNotification
*
* \param[in] oldNode    the node containing the data in the notification
* \param[in] notification   the type of notification
*
* \return nothing
********************************************************************************** */
static DeviceNotification *CreateNotification(Node *oldNode, DeviceNotificationEvent notification)
{
    DeviceState *oldState = (DeviceState *)oldNode->data;
    DeviceNotification *deviceNotification = (DeviceNotification *)calloc(1, sizeof(DeviceNotification));
    deviceNotification->notifyEvent = notification;
    deviceNotification->state = (DeviceState *)calloc(1, sizeof(DeviceState));
    DeviceState *state = deviceNotification->state;

    state->deviceName = strdup(oldState->deviceName);
    state->friendlyName = strdup(oldState->friendlyName);
    state->isKinetisWDevice = oldState->isKinetisWDevice;
#ifdef _WIN32
    state->vid = strdup(oldState->vid);
    state->pid = strdup(oldState->pid);
#endif
    state->state = oldState->state;
    return deviceNotification;
}

/*! *********************************************************************************
* \brief  Updates the a list when an event happens to a node
*
* \param[in] head       the head of the list
* \param[in] newNode    the node that sparked the update
* \param[in] notify     bool -> should notify if changed
*
* \return nothing
********************************************************************************** */
static void UpdateListOfDevices(Node **head, Node *newNode, uint8_t notify)
{
    HSDKAcquireLock(listLock);
    Node *crt = *head;

    while (crt != NULL) {
        if (!strncmp(((DeviceState *)crt->data)->deviceName, ((DeviceState *)newNode->data)->deviceName, MAXNAME)) {
            crt->found = 1;
            DestroyNode(newNode);
            break;
        }

        crt = crt->next;
    }

    if (crt == NULL) {
        newNode->found = 1;
        newNode->next = *head;
        *head = newNode;

        if (notify) {
            NotifyOnEvent(deviceManager->evtManager, CreateNotification(newNode, DeviceAdded));
        }
    }

    HSDKReleaseLock(listLock);
}

/*! *********************************************************************************
* \brief  Remove all nodes from the list that aren't in the system anymore
*
* \param[in] head       the head of the list
* \param[in] notify     bool -> should notify if changed
*
* \return nothing
********************************************************************************** */
static void RemoveNotFound(Node **head, uint8_t notify)
{
    HSDKAcquireLock(listLock);
    if ((head == NULL) || (*head == NULL)) {
        HSDKReleaseLock(listLock);
        return;
    }
    Node *crt = (*head)->next;
    Node *prev = *head;
    while (crt != NULL) {
        if (crt->found) {
            crt->found = 0;
            prev = crt;
        } else {
            if (notify) {
                NotifyOnEvent(deviceManager->evtManager, CreateNotification(crt, DeviceRemoved));
            }
            prev->next = crt->next;
            DestroyNode(crt);
        }

        crt = prev->next;
    }

    if ((*head)->found) {
        (*head)->found = 0;
    } else {
        crt = *head;
        *head = (*head)->next;
        if (notify) {
            NotifyOnEvent(deviceManager->evtManager, CreateNotification(crt, DeviceRemoved));
        }

        DestroyNode(crt);
    }

    HSDKReleaseLock(listLock);
}

/*! *********************************************************************************
* \brief  Deallocates an IdentifierNode
*
* \param[in] data   an IdentifierNode value -> a pair of type (Name (VID PID))
*
* \return nothing
********************************************************************************** */
static void DestroyIdentifierNode(void *data)
{
    if (data == NULL) {
        return;
    }

    Pair *namedPair = (Pair *)data;
    Pair *idPair = (Pair *)namedPair->snd;
    free(namedPair->fst);
    free(idPair->fst);
    free(idPair->snd);
    free(idPair);
    free(namedPair);
}


#ifdef _WIN32

#include <Windows.h>

/*! *********************************************************************************
* \brief  Returns an array of all devices that the DeviceManager knows about from its
* currentActiveDevices list.
*
* \param[out] size  the size of the array.
*
* \return the array containing all devices from currentActiveDevices list.
********************************************************************************** */
DeviceState *GetAllDevices(uint32_t *size)
{
    File fd;
    uint32_t localSize = 0;

    HSDKAcquireLock(listLock);

    Node *crt = deviceManager->currentActiveDevices;
    while (crt != NULL) {
        crt = crt->next;
        localSize++;
    }

    DeviceState *allDevices = (DeviceState *)calloc(localSize, sizeof(DeviceState));
    int i = 0;
    crt = deviceManager->currentActiveDevices;
    while (crt != NULL) {
        DeviceState *tempDevice = (DeviceState *)crt->data;
        allDevices[i].deviceName = strdup(tempDevice->deviceName);
        allDevices[i].friendlyName = strdup(tempDevice->friendlyName);
        allDevices[i].isKinetisWDevice = tempDevice->isKinetisWDevice;
        allDevices[i].pid = strdup(tempDevice->pid);
        allDevices[i].vid = strdup(tempDevice->vid);

        if (allDevices[i].isKinetisWDevice) {
            /* check if port is opened by other programs */
            fd = HSDKOpenFile(UARTSystemPath(allDevices[i].deviceName));

            if (fd == INVALID_HANDLE_VALUE) {
                allDevices[i].state = DeviceError;
            } else {
                allDevices[i].state = tempDevice->state;
                HSDKCloseFile(fd);
            }
        } else {
            allDevices[i].state = tempDevice->state;
        }

        crt = crt->next;
        i++;
    }

    HSDKReleaseLock(listLock);

    *size = localSize;

    return allDevices;
}


/*! *********************************************************************************
* \brief  Checks the availability of a device
*
* \param[in] device a pointer to a DeviceState
*
* \return nothing
********************************************************************************** */
static void SetState(DeviceState *device)
{
    Availability response = Available;

    char *path = (char *)calloc(MAXNAME, sizeof(char));
    sprintf(path, "\\\\.\\%s", device->deviceName);

    HANDLE hTemp = CreateFileA(path,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL
                              );

    if (hTemp == INVALID_HANDLE_VALUE) {
        DWORD dwRet = GetLastError();

        switch (dwRet) {
            case ERROR_ACCESS_DENIED:
                response = InUse;
                break;
            case ERROR_FILE_NOT_FOUND:
                response = NotPluggedIn;
                break;
            default:
                response = DeviceError;
        }
    } else {
        CloseHandle(hTemp);
    }

    device->state = response;
    free(path);
}

/*! *********************************************************************************
* \brief  Searches the registry and adds elements by vid and pid. The way it works is this:
* on a Windows system when a device is plugged in it is registered in 2 places
* in the system, in one place permanently with a VID and PID allocated for a COMPORT number, the other
* as a list of current devices. Thus it goes through the permanent list and creates a correspondence of
* VID and PID to a COMPORT number
*
* \param[in] vidPidList an array of strings with VID on even numbered indexes and PID on odd.
* \param[in] listSize size of the array of strings
*
* \return nothing
********************************************************************************** */
static void AddDeviceIdentity(char **vidPidList, int listSize)
{
    const int devParamSubkeyLength = (int)strlen("\\Device Parameters");

    // The registry key handle for enumerating in SYSTEM\CurrentControlSet\Enum for each vid pid
    HKEY hEnumSubkey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum", 0, KEY_READ, &hEnumSubkey) == ERROR_SUCCESS) {
        // USB level queries on subkeys
        DWORD dwEnumSubKeys;
        DWORD dwEnumMaxSubKeyLen;
        DWORD dwEnumQueryInfo = RegQueryInfoKey(hEnumSubkey, NULL, NULL, NULL, &dwEnumSubKeys, &dwEnumMaxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL);
        if (dwEnumQueryInfo == ERROR_SUCCESS) {
            DWORD iEnumSubKeys;

            for (iEnumSubKeys = 0; iEnumSubKeys < dwEnumSubKeys; iEnumSubKeys++) {
                DWORD cEnumSubkeyName = dwEnumMaxSubKeyLen + 1;
                char *lpEnumSubkeyName = (char *)calloc(cEnumSubkeyName, sizeof(char));

                RegEnumKeyEx(hEnumSubkey,
                             iEnumSubKeys,
                             lpEnumSubkeyName,
                             &cEnumSubkeyName,
                             NULL,
                             NULL,
                             NULL,
                             NULL
                            );

                HKEY hUSBSubkey;
                if (RegOpenKeyEx(hEnumSubkey, lpEnumSubkeyName, 0, KEY_READ, &hUSBSubkey) == ERROR_SUCCESS) {
                    // USB level queries on subkeys
                    DWORD dwUSBSubKeys;
                    DWORD dwUSBMaxSubKeyLen;
                    DWORD dwUSBQueryInfo = RegQueryInfoKey(hUSBSubkey, NULL, NULL, NULL, &dwUSBSubKeys, &dwUSBMaxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL);
                    if (dwUSBQueryInfo == ERROR_SUCCESS) {
                        DWORD iUSBSubKeys;

                        for (iUSBSubKeys = 0; iUSBSubKeys < dwUSBSubKeys; iUSBSubKeys++) {
                            DWORD cUSBSubkeyName = dwUSBMaxSubKeyLen + 1;
                            char *lpUSBSubkeyName = (char *)calloc(cUSBSubkeyName, sizeof(char));

                            RegEnumKeyEx(hUSBSubkey,
                                         iUSBSubKeys,
                                         lpUSBSubkeyName,
                                         &cUSBSubkeyName,
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL
                                        );

                            char *vid, *pid;
                            // Index in the vid pid list
                            int iVidPid;
                            // Whether the current subkey contains any of the vid pid pairs given
                            uint8_t foundVP = 0;

                            for (iVidPid = 0; iVidPid < listSize && !foundVP; iVidPid += 2) {
                                if (strstr(lpUSBSubkeyName, vidPidList[iVidPid]) != NULL && strstr(lpUSBSubkeyName, vidPidList[iVidPid + 1]) != NULL) {
                                    foundVP = 1;
                                    vid = vidPidList[iVidPid];
                                    pid = vidPidList[iVidPid + 1];
                                }
                            }

                            if (foundVP) {
                                HKEY hVPSubkey;

                                if (RegOpenKeyEx(hUSBSubkey, lpUSBSubkeyName, 0, KEY_READ, &hVPSubkey) == ERROR_SUCCESS) {
                                    // Vid Pid level queries on subkeys
                                    DWORD dwVPSubKeys;
                                    DWORD dwVPMaxSubKeyLen;
                                    DWORD dwVPQueryInfo = RegQueryInfoKey(hVPSubkey, NULL, NULL, NULL, &dwVPSubKeys, &dwVPMaxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL);
                                    if (dwVPQueryInfo == ERROR_SUCCESS) {
                                        DWORD iVidPidSubkeys;

                                        for (iVidPidSubkeys = 0; iVidPidSubkeys < dwVPSubKeys; iVidPidSubkeys++) {
                                            DWORD cVPSubkeyName = dwVPMaxSubKeyLen + 1 + devParamSubkeyLength;
                                            char *lpVPSubkeyName = (char *)calloc(cVPSubkeyName, sizeof(char));

                                            RegEnumKeyEx(hVPSubkey,
                                                         iVidPidSubkeys,
                                                         lpVPSubkeyName,
                                                         &cVPSubkeyName,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         NULL
                                                        );

                                            lpVPSubkeyName = strcat(lpVPSubkeyName, "\\Device Parameters");
                                            HKEY hDevParamsSubkey;
                                            if (RegOpenKeyEx(hVPSubkey, lpVPSubkeyName, 0, KEY_READ, &hDevParamsSubkey) == ERROR_SUCCESS) {
                                                DWORD cValues;
                                                DWORD dwMaxValueNameLen;
                                                DWORD dwMaxValueLen;
                                                DWORD dwValueQueryInfo = RegQueryInfoKey(hDevParamsSubkey, NULL, NULL, NULL, NULL, NULL, NULL, &cValues, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
                                                if (dwValueQueryInfo == ERROR_SUCCESS) {
                                                    DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1; //Include space for the NULL terminator
                                                    DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars * sizeof(char);
                                                    DWORD dwMaxValueDataSizeInChars = dwMaxValueLen / sizeof(char) + 1; //Include space for the NULL terminator
                                                    DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars * sizeof(char);

                                                    DWORD dwIndex = 0;
                                                    DWORD dwType;
                                                    DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
                                                    DWORD dwDataSize = dwMaxValueDataSizeInBytes;

                                                    char *szValueName = (char *)calloc(dwMaxValueNameSizeInBytes, sizeof(char));
                                                    BYTE *data = (BYTE *)calloc(dwMaxValueDataSizeInBytes, sizeof(BYTE));
                                                    BYTE found = 0;
                                                    LONG nEnum = RegEnumValue(hDevParamsSubkey, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, data, &dwDataSize);
                                                    while (dwIndex < cValues && nEnum == ERROR_SUCCESS && !found) {
                                                        //If the value is of the correct type, then add it to the array
                                                        if (dwType == REG_SZ && !strncmp(szValueName, "PortName", strlen("PortName"))) {
                                                            char *deviceName = (char *)calloc(dwDataSize + 1, sizeof(char));
                                                            if (deviceName) {
                                                                memcpy(deviceName, data, dwDataSize);
                                                                Pair *namePair = (Pair *)malloc(sizeof(Pair));
                                                                namePair->fst = deviceName;
                                                                Pair *idPair = (Pair *)malloc(sizeof(Pair));
                                                                namePair->snd = idPair;
                                                                idPair->fst = strdup(vid);
                                                                idPair->snd = strdup(pid);

                                                                Node *node = CreateNode(namePair);
                                                                node->next = deviceManager->listOfFSIdentities;

                                                                deviceManager->listOfFSIdentities = node;
                                                                found = 1;
                                                            }
                                                        }

                                                        //Prepare for the next time around
                                                        dwValueNameSize = dwMaxValueNameSizeInChars;
                                                        dwDataSize = dwMaxValueDataSizeInBytes;
                                                        ++dwIndex;
                                                        nEnum = RegEnumValue(hDevParamsSubkey, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, data, &dwDataSize);
                                                    }
                                                    free(data);
                                                    free(szValueName);
                                                }

                                            }

                                            RegCloseKey(hDevParamsSubkey);

                                            free(lpVPSubkeyName);
                                        }
                                    }
                                }

                                RegCloseKey(hVPSubkey);
                            }

                            free(lpUSBSubkeyName);
                        }
                    }
                }

                RegCloseKey(hUSBSubkey);
                free(lpEnumSubkeyName);
            }
        }

        RegCloseKey(hEnumSubkey);
    }
}


/*! *********************************************************************************
* \brief  Creates a list of all known NXP Kinetis-W device VID and PID pairs
*
* \return nothing
********************************************************************************** */
static void CreateListOfKinetisWIdentities()
{
    char **list = (char **)calloc(KNOWN_VID_PID_PAIRS * 2, sizeof(char *));
    list[0] = "VID_2504";
    list[1] = "PID_0300";
    list[2] = "VID_15A2"; // Virtual Com Port Freescale VID
    list[3] = "PID_0300"; // Virtual Com Port PID
    list[4] = "VID_15A2";
    list[5] = "PID_005A";
    list[6] = "VID_1357";
    list[7] = "PID_0089";
    list[8] = "VID_0403";
    list[9] = "PID_6001";
    list[10] = "VID_1357";
    list[11] = "PID_0707";
    list[12] = "VID_1366";
    list[13] = "PID_0105";
    list[14] = "VID_0D28"; // FRDM-KW40Z VID
    list[15] = "PID_0204"; // FRDM-KW40Z PID
    list[16] = "VID_1366"; // J-Link CDC UART VID
    list[17] = "PID_1015"; // J-Link CDC UART PID
    list[18] = "VID_1FC9"; // Virtual Com Port NXP VID
    list[19] = "PID_0300"; // Virtual Com Port PID
    list[20] = "VID_0403"; // OM15028-1 / JN5179 VID
    list[21] = "PID_6015"; // OM15028-1 / JN5179 PID
    list[22] = "VID_1FC9"; // QN9080 DK VID
    list[23] = "PID_0090"; // QN9080 DK PID

    AddDeviceIdentity(list, KNOWN_VID_PID_PAIRS * 2);
    free(list);
}

/*! *********************************************************************************
* \brief  Verify if the device is a NXP Kinetis-W one.
*
* \param[in] device a pointer to a DeviceState
*
* \return nothing
********************************************************************************** */
void VerifyIfKinetisW(DeviceState *device)
{
    Node *crt = deviceManager->listOfFSIdentities;

    device->isKinetisWDevice = 0;

    while (crt != NULL) {

        Pair *namePair = (Pair *)crt->data;
        char *name = (char *)namePair->fst;

        Pair *idPair = (Pair *)namePair->snd;
        device->vid = strdup((char *)idPair->fst);
        device->pid = strdup((char *)idPair->snd);

        if (!strcmp(device->deviceName, name)) {
            device->isKinetisWDevice = 1;
            return;
        }
        crt = crt->next;
    }
}

/*! *********************************************************************************
* \brief  Check the temporary registry for the current devices. Check and open
*         registry key folder: "HARDWARE\\DEVICEMAP\\SERIALCOMM". Iterate
          through all enum items and add all enum keys to a serial port list. After
          scan, remove from global list all serial ports that no longer exist.
*
* \param[in] state   whether to notify the subscribers on each device change found
*
* \return nothing
********************************************************************************** */
void CheckRegistry(uint8_t state)
{
    // Variable to hold return codes.
    LONG rc;

    // RegOpenKeyEx - Opens the specified registry key.
    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPCTSTR lpSubKey = "HARDWARE\\DEVICEMAP\\SERIALCOMM";
    DWORD ulOptions = 0;
    REGSAM samDesired = KEY_QUERY_VALUE;
    HKEY hkResult;

    rc = RegOpenKeyEx(hKey, lpSubKey, ulOptions, samDesired, &hkResult);
    if (rc != ERROR_SUCCESS) {
        return;
    }

    // RegQueryInfoKey - Retrieves information about the specified registry key.
    LPTSTR lpClass = NULL;
    LPDWORD lpcClass = NULL, lpReserved = NULL, lpcSubKeys = NULL, lpcMaxSubKeyLen = NULL, lpcMaxClassLen = NULL;
    DWORD dwValues, dwMaxValueNameLen, dwMaxValueLen;
    LPDWORD lpcbSecurityDescriptor = NULL;
    PFILETIME lpftLastWriteTime = NULL;

    rc = RegQueryInfoKey(hkResult, lpClass, lpcClass, lpReserved, lpcSubKeys, lpcMaxSubKeyLen, lpcMaxClassLen,
                         &dwValues, &dwMaxValueNameLen, &dwMaxValueLen,  // arguments of interest
                         lpcbSecurityDescriptor, lpftLastWriteTime);
    if (rc != ERROR_SUCCESS) {
        return;
    }

    // Prepare for calling RegEnumValue.
    DWORD dwIndex = 0;
    DWORD dwValueName = dwMaxValueNameLen + 1;
    LPTSTR lpValueName = (LPTSTR)calloc(dwValueName, sizeof(char));
    DWORD dwType;
    DWORD dwDataLen = dwMaxValueLen + 1;
    LPBYTE lpData = (LPBYTE)calloc(dwDataLen, sizeof(BYTE));

    // Iterate through all the items in the serial port registry keys.
    do {
        // RegEnumValue - Enumerates the values for the specified open registry key.
        // The function copies one indexed value name and data block for the key each time it is called
        rc = RegEnumValue(hkResult, dwIndex, lpValueName, &dwValueName, lpReserved, &dwType, lpData, &dwDataLen);
        if (rc == ERROR_SUCCESS && dwType == REG_SZ) {
            DeviceState *deviceState = (DeviceState *)calloc(1, sizeof(DeviceState));

            deviceState->friendlyName = (char *)calloc(dwValueName + 1, sizeof(char));
            memcpy(deviceState->friendlyName, lpValueName, dwValueName);

            deviceState->deviceName = (char *)calloc(dwDataLen + 1, sizeof(char));
            memcpy(deviceState->deviceName, lpData, dwDataLen);

            SetState(deviceState);
            VerifyIfKinetisW(deviceState);

            Node *serialPortNode = CreateNode(deviceState);
            UpdateListOfDevices(&deviceManager->currentActiveDevices, serialPortNode, state);
        }

        // set back the original values for the next iteration
        dwValueName = dwMaxValueNameLen + 1;
        dwDataLen = dwMaxValueLen + 1;

        // increment the index
        dwIndex++;

    } while (dwIndex < dwValues);

    // Free allocated memory.
    free(lpValueName);
    free(lpData);

    // Check current serial port list and remove all items that no longer exist
    RemoveNotFound(&(deviceManager->currentActiveDevices), state);

    // RegCloseKey - Closes a handle to the specified registry key.
    RegCloseKey(hkResult);
}


/*! *********************************************************************************
* \brief  Creates the initial list of devices
*
* \return nothing
********************************************************************************** */
static void CreateInitialList()
{
    CheckRegistry(0);
}

/*! *********************************************************************************
* \brief  The routine for the DeviceManager thread on Windows
*
* \param[in] lpParameter    a pointer to the thread parameter
*
* \return nothing
********************************************************************************** */
static void *DeviceNotificationRoutine(void *lpParameter)
{
    int triggeredEvent;
    int loop = 1;

    HKEY hSERIALCOMM;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hSERIALCOMM) != ERROR_SUCCESS) {
        return NULL;
    }

    Event deviceNotification = HSDKCreateEvent(0);
    DWORD err = RegNotifyChangeKeyValue(hSERIALCOMM, FALSE, REG_NOTIFY_CHANGE_LAST_SET, deviceNotification, TRUE);
    if (err != ERROR_SUCCESS) {
        HSDKDestroyEvent(deviceNotification);
        return NULL;
    }

    Event eventArray[2];
    eventArray[0] = deviceManager->stopThread;
    eventArray[1] = deviceNotification;

    while (loop) {
        int rc = HSDKWaitMultipleEvents(eventArray, 2, INFINITE_WAIT, &triggeredEvent);

        if (rc != HSDK_ERROR_SUCCESS) {
            loop = 0;
            continue;
        }

        switch (triggeredEvent) {
            case 0:
                loop = 0;
                break;
            case 1:
                CheckRegistry(1);
                RegNotifyChangeKeyValue(hSERIALCOMM, TRUE, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, deviceNotification, TRUE);
                break;
        }
    }

    RegCloseKey(hSERIALCOMM);
    return NULL;
}

#elif __linux__

#include <termios.h>
#include <string.h>
#include <stdlib.h>
#ifdef __linux__udev__
#   include <libudev.h>
#endif

static void SetState(DeviceState *device) {}
static void CreateListOfKinetisWIdentities() {}
static void CreateInitialList() {}
static void *DeviceNotificationRoutine(void *lpParameter)
{
    return NULL;
}

char **vendorList;
char **productList;

int isKinetisWDevice(const char *idVendor, const char *idProduct)
{
    int i;

    if (vendorList == NULL) {
        vendorList = (char **)calloc(KNOWN_VID_PID_PAIRS, sizeof(char *));
        productList = (char **)calloc(KNOWN_VID_PID_PAIRS, sizeof(char *));

        vendorList[0] = strdup("2504"); productList[0] = strdup("0300");
        vendorList[1] = strdup("15A2"); productList[1] = strdup("0300");    // VCP Freescale
        vendorList[2] = strdup("15A2"); productList[2] = strdup("005A");
        vendorList[3] = strdup("1357"); productList[3] = strdup("0089");
        vendorList[4] = strdup("0403"); productList[4] = strdup("6001");
        vendorList[5] = strdup("1357"); productList[5] = strdup("0707");
        vendorList[6] = strdup("1366"); productList[6] = strdup("0105");
        vendorList[7] = strdup("0D28"); productList[7] = strdup("0204");    // FRDM-KW40Z
        vendorList[8] = strdup("1366"); productList[8] = strdup("1015");    // J-Link CDC UART
        vendorList[9] = strdup("1FC9"); productList[9] = strdup("0300");    // VCP NXP
        vendorList[10] = strdup("0403"); productList[10] = strdup("6015");  // OM15028-1 / JN5179
        vendorList[11] = strdup("1FC9"); productList[11] = strdup("0090");  // QN9080 DK
    }

    for (i = 0; i < KNOWN_VID_PID_PAIRS; i++) {
        if (strcmp(vendorList[i], idVendor) && strcmp(productList[i], idProduct)) {
            return 1;
        }
    }

    return 0;
}

/*
 * Overriding GetAllDevices feature for Linux.
 */
DeviceState *GetAllDevices(uint32_t *size)
{
#ifdef __linux__udev__
    *size = 0;

    HSDKAcquireLock(listLock);

    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;

    /* Get the number of connected devices. */
    udev = udev_new();

    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        *size = *size + 1;
    }

    udev_enumerate_unref(enumerate);

    udev_unref(udev);

    /* Get info about devices. */
    DeviceState *allDevices = (DeviceState *)calloc(*size, sizeof(DeviceState));
    int i = 0;

    udev = udev_new();

    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        File fd;
        const char *path;
        const char *devFile;

        path = udev_list_entry_get_name(dev_list_entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);

        devFile = udev_device_get_devnode(dev);

        dev = udev_device_get_parent_with_subsystem_devtype(
                  dev,
                  "usb",
                  "usb_device");

        if (dev) {
            DeviceState *deviceState = (DeviceState *)calloc(1, sizeof(DeviceState));

            deviceState->friendlyName = (char *) devFile;
            deviceState->deviceName = (char *) devFile;
            deviceState->isKinetisWDevice = 0;
            deviceState->vid = strdup(udev_device_get_sysattr_value(dev, "idVendor"));
            deviceState->pid = strdup(udev_device_get_sysattr_value(dev, "idProduct"));

            if (isKinetisWDevice(deviceState->vid, deviceState->pid)) {
                deviceState->isKinetisWDevice = 1;
            }

            if (deviceState->isKinetisWDevice) {
                /* check if port is opened by other programs */
                fd = HSDKOpenFile(deviceState->deviceName);

                if (fd == INVALID_HANDLE_VALUE) {
                    deviceState->state = DeviceError;
                } else {
                    deviceState->state = Available;
                    HSDKCloseFile(fd);
                }
            } else {
                deviceState->state = Available;
            }

            allDevices[i] = *deviceState;
            free(deviceState);
            i++;
        }
    }

    udev_enumerate_unref(enumerate);

    udev_unref(udev);

    HSDKReleaseLock(listLock);

    return allDevices;
#else
    fprintf(stderr, "[HSDK-Warning] "
            "UART library is compiled w/o udev (device detection) support. "
            "Define UDEV?=yes in Makefile to enable it.\n"
           );
    return NULL;
#endif
}


#elif __APPLE__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <paths.h>
#include <termios.h>
#include <sysexits.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/serial/ioss.h>
#include <IOKit/usb/USBSpec.h>
#include <IOKit/IOBSD.h>

static void SetState(DeviceState *device) {}
static void CreateListOfKinetisWIdentities() {}
static void CreateInitialList() {}
static void *DeviceNotificationRoutine(void *lpParameter)
{
    return NULL;
}

/**
 * FIXME: Not implemented.
 */
DeviceState *GetAllDevices(uint32_t *size)
{
    return NULL;
}

#endif
