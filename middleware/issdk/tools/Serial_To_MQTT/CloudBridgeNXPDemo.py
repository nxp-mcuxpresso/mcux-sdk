# Copyright 2018 NXP
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

'''
@author    : Shubhadip.Paul@nxp.com
@name      : ISSDKCloudBridge

********************************************************************************
This script is used to read Data Logger Samples from a File and send to Cloud.

Requiremets:
    python-2.7.3
    paho-mqtt-1.1
********************************************************************************
'''

from ScrolledText import ScrolledText
from Tkconstants import END, NORMAL, DISABLED, E, W, N, S
from Tkinter import Tk, Button, Label, Entry, PhotoImage, Grid

import sys
import time
import threading
import serial.tools.list_ports
import paho.mqtt.client as mqtt

# Cloud Communication Parameters.
exitCommand       = "Exit"
topicSample       = "iot-2/evt/Acceleration3D/fmt/json"
sampleClientID    = "d:quickstart:iotqs-sensor:F8B156CA590B"
cloudServerURL    = "quickstart.messaging.internetofthings.ibmcloud.com"
cloudServerPort   = 1883
keepAliveDuration = 10
jsonFmtResponse   = "{\"d\":{\"Type\":\"Response\",\"Data\":%s}}"
jsonFmtSample     = "{\"d\":{\"Type\":\"Sample\",\"Data\":%s}}"
jsonFmtEvent      = "{\"d\":{\"Type\":\"Event\",\"Data\":%s}}"
username          = ""
password          = ""

# Serial Communication Parameters.
UART_MSG_BUFFER_SIZE      = 64
STATE_GETTINGPACKETDATA   = 0
STATE_WAITFORPACKETMARKER = 1
STREAMING_PKT_ID          = 0x40
EVENT_STREAM_ID           = 0xFF
HDLC_PKT_MARKER           = "7E"
START_STREAMING_CMD       = "\x7E\x21\x00\x00\x02\x01\x01\x7E"
STOP_STREAMING_CMD        = "\x7E\x21\x01\x00\x02\x02\x01\x7E"
BOARD_COM_STR_MBED        = "mbed Serial Port"
BOARD_COM_STR_DAPLINK     = "USB Serial Device"
BOARD_COM_STR_BLUETOOTH   = "Standard Serial over Bluetooth link"

# UI Lables
WINDOW_TITLE    = "IoT Adapter - Dashboard"
BANNER_STR      = "ISSDK   Cloud   Bridge"
SERVER_URL_STR  = "Server URL :"
SERVER_PORT_STR = "Cloud Port :"
COM_PORT_STR    = "COM Port :"
CLIENT_ID_STR   = "Client ID :"
USER_NAME_STR   = "User Name :"
PASSWORD_STR    = "Password :"
COPYRIGHT_STR   = "Copyright (c) 2018, NXP Semiconductors."
TOPIC_STR       = "Topic Name :"

# Global Variables.
threadHandle     = None
sampleHandle     = None
sampleConnected  = False
isRunning        = False
comHandle        = None
comPort          = 'COM4'
sampleCount      = 0
prevChar         = 0
packetIndex      = 0
uartPacket       = [None] * UART_MSG_BUFFER_SIZE
packetState      = STATE_WAITFORPACKETMARKER

# Function to Log Messages into the GUI TextBox.
def LogToTextBox(message):
    textBox.configure(state=NORMAL)
    textBox.insert(END, "%s\n" % message)
    textBox.configure(state=DISABLED)
    textBox.see(END)

# Function to publish Samples to Cloud.
def ConnectIoTAdapter():
    global comHandle
    global sampleHandle
    global sampleConnected
    global keepAliveDuration

    if(comHandle == None):
        try:
            # Open COM Port for reading samples over UART from Board.
            comHandle = serial.Serial(port=comPortEntry.get(), baudrate=115200)
            if (comHandle.isOpen()):
                comHandle.flushInput()
                comHandle.flushOutput()
                LogToTextBox("Connected to Board @ %s..." % comPortEntry.get())
                comPortEntry.configure(state=DISABLED)
            else:
                LogToTextBox("Error: Connection to Board @ %s Failed..." % comPortEntry.get())
                comPortEntry.configure(fg='red')
                return
        except:
            pass
            LogToTextBox("Error: Failed opening COM Port [%s]..." % comPortEntry.get())
            comPortEntry.configure(fg='red')
            return

    if(sampleHandle == None):
        # Client settings for Sending Samples.
        sampleHandle = mqtt.Client()
        sampleHandle.on_connect = ConnectSampleHandler
        sampleHandle.on_disconnect = DisconnectHandler
        sampleHandle._client_id = clientIdEntry.get()
        if userNameEntry.get():
            sampleHandle.username_pw_set(userNameEntry.get(), passwordEntry.get())

        # Open Cloud connections.
        sampleHandle.connect(cloudURLEntry.get(), int(cloudPortEntry.get()), keepAliveDuration)

        # Start listening for Events from Cloud.
        sampleHandle.loop_start()
        while(sampleConnected == False):
            time.sleep(1)

    goButton.configure(text="START", command=StartReadingFormComPort)

def StartReadingFormComPort():
    global isRunning
    global comHandle
    global threadHandle

    if not isRunning:
        status = SendCommandToBoard(comHandle, START_STREAMING_CMD)
        if not status:
            LogToTextBox("Error: Failed Starting Reading of samples from Board.")
            goButton.configure(text="EXIT", command=ExitDashboard)
            return
        isRunning = True
        goButton.configure(text="STOP", command=StopReadingFromComPort)
        threadHandle = threading.Thread(target=ReadFromComPort)
        threadHandle.start()
    LogToTextBox("Started reading of samples from Board.")

def SendCommandToBoard(handle, hexCmd):
    strCmd = hexCmd.encode("hex")
    lenCmd = len(strCmd)/2

    printCmd = "Sending Command   ["
    for byte in range(lenCmd):
        printCmd += "'0x"
        printCmd += strCmd[byte*2].upper()
        printCmd += strCmd[byte*2+1].upper()
        printCmd += "', "
    printCmd = printCmd[:-2] + "] to Board."

    LogToTextBox(printCmd)
    try:
        handle.write(hexCmd)
        return True
    except:
        pass
        LogToTextBox("Error: Failed Writing to COM Port...")
        return False

def ReadFromComPort():
    global isRunning
    global comHandle
    global uartPacket
    global topicSample
    global sampleCount
    global sampleHandle

    try:
        while(True):
            if ProcessHdlcByte(comHandle.read(1)):
                (jsonPayload, sampleList) = GetJsonFormattedSample()
                (retCode, _) = sampleHandle.publish(topicSample, jsonPayload, 0, False)
                if (retCode != mqtt.MQTT_ERR_SUCCESS):
                    LogToTextBox("Error: Publishing Sample to Topic for sending Samples Failed! [Error Code = %d]" % retCode)
                else:
                    sampleCount += 1
                if not isRunning:
                    strSample = ''
                    for e in sampleList:
                        strSample = "%s%02X" % (strSample, e)
                    if (strSample[:2] == STOP_STREAMING_RSP_HDR and strSample[4:] == STOP_STREAMING_RSP_MSG):
                        break
    except:
        LogToTextBox("Error: Failed reading from COM Port and Publishing to Cloud...")
        goButton.configure(text="EXIT", command=ExitDashboard)
        comPortEntry.configure(fg='blue')
        comPortEntry.configure(state=NORMAL)
        pass

def StopReadingFromComPort():
    global threadHandle
    global isRunning
    global comHandle
    global sampleCount
    global commandCount
    global packetState
    global packetIndex
    global uartPacket
    global prevChar

    if isRunning:
        status = SendCommandToBoard(comHandle, STOP_STREAMING_CMD)
        if not status:
            LogToTextBox("Error: Failed Stopping Reading of samples from Board.")
            goButton.configure(text="EXIT", command=ExitDashboard)
            return
        isRunning = False
        threadHandle.join(5)
        if threadHandle.isAlive():
            LogToTextBox("Error: Time out waiting for Response, Reset the board and Try again.")
            comHandle.close()
            threadHandle.join()
            comHandle        = None
            prevChar         = 0
            packetIndex      = 0
            uartPacket       = [None] * UART_MSG_BUFFER_SIZE
            packetState      = STATE_WAITFORPACKETMARKER
            ConnectIoTAdapter()
        goButton.configure(text="START", command=StartReadingFormComPort)
    LogToTextBox("Stopped with %d samples sent and %d commands received.\n" % (sampleCount, commandCount))

# This function will free the resources and terminate the GUI.
def ExitDashboard(pauseBeforeExit=False):
    global isRunning
    global comHandle
    global topicCommand
    global sampleHandle

    if isRunning:
        StopReadingFromComPort()
    if comHandle != None:
        comHandle.close()
    if sampleHandle != None:
        sampleHandle.loop_stop()
        sampleHandle.disconnect()

    if pauseBeforeExit:
        time.sleep(3)
    root.quit()

# Function to handle incoming HDLC encoded bytes form the Board over UART.
def ProcessHdlcByte(cByte):
    global packetState
    global packetIndex
    global uartPacket
    global prevChar

    byte = ord(cByte)

    escapeChar     = False
    packetError    = False
    packetReceived = False

    # Start of a packet.
    if (packetState == STATE_WAITFORPACKETMARKER):
        if (byte == 0x7E):
            packetIndex = 0
            packetState = STATE_GETTINGPACKETDATA
    # Packet payload.
    elif (packetState == STATE_GETTINGPACKETDATA):
        # Process actual payload bytes.
        if (byte != 0x7E):
            # Process escape sequences.
            if (byte == 0x7D):
                prevChar = byte;
                escapeChar = True
            elif (prevChar == 0x7D):
                if (byte == 0x5D):
                    byte = 0x7D
                elif (byte == 0x5E):
                    byte = 0x7E
                else:
                    packetError = True
                prevChar = 0
                escapeChar = False
            if (escapeChar == False):
                # Populate packet.
                uartPacket[packetIndex] = byte
                packetIndex += 1
        else:
            # Packet end, receive complete.
            if (packetIndex > 0):
                packetState = STATE_WAITFORPACKETMARKER
                packetReceived = True
            # Blank packet received, restart.
            else:
                packetState = STATE_GETTINGPACKETDATA
                packetIndex = 0
    else:
        packetError = True

    # Incase of error, restart.
    if (packetError == True):
        packetIndex = 0
        packetState = STATE_WAITFORPACKETMARKER

    return packetReceived

# Function to convert sample bytes to Values and then create JSON format payload.
def GetJsonFormattedSample():
    global uartPacket
    strSample = []
    strResponse = []

    for byteOffset in range(packetIndex):
        strSample.append(uartPacket[byteOffset])
        strResponse.append("0x%02X" % uartPacket[byteOffset])

    if (uartPacket[0] == STREAMING_PKT_ID):
        if (uartPacket[3] == EVENT_STREAM_ID):
            payload = jsonFmtEvent % strSample
            LogToTextBox("Received Event %s from Board." % (["0x7E"] + strResponse + ["0x7E"]))
        else:
            payload = jsonFmtSample % strSample
    else:
        payload = jsonFmtResponse % strSample
        LogToTextBox("Received Response %s from Board." % (["0x7E"] + strResponse + ["0x7E"]))

    return (payload, strSample)

# The callback for when the client receives a CONNACK response from the server.
def ConnectSampleHandler(client, userData, flags, rC):
    global sampleConnected
    if (rC != mqtt.MQTT_ERR_SUCCESS):
        LogToTextBox("Error: Connection with Cloud Service for Samples Failed ! [Error Code = %d]" % rC)
    else:
        LogToTextBox("Connected to Cloud Service for Sending Samples...")
        sampleConnected = True
    return (client, userData, flags)

# The callback for when the client receives a disconnection from the server or network error.
def DisconnectHandler(client, userdata, rC):
    if rC != mqtt.MQTT_ERR_SUCCESS:
        LogToTextBox("Error: Network Error, Unexpected disconnection of connection.")
        StopReadingFromComPort()
    goButton.configure(text="EXIT", command=ExitDashboard)


# Build GUI and add elements to create dashboard.
root = Tk()
root.resizable(0, 0)
root.geometry("800x600")

nxpLogo = PhotoImage(file="NXP_Logo.gif")
Button(root, font=('times', 14, 'bold'), state=DISABLED, text=BANNER_STR, disabledforeground='black', bg='orange').grid(row=0, column=0, rowspan=2, columnspan=17, sticky=W + E + N + S)
Button(root, image=nxpLogo, bg='white').grid(row=0, column=17, rowspan=2, columnspan=1, sticky=W + E + N + S)

textBox = ScrolledText(root, font=('times', 10), height=30, fg='green', bg='black', state=DISABLED)
textBox.grid(row=2, column=0, rowspan=4, columnspan=18, sticky=W + E + N + S)

Label(root, font=('times', 12, 'bold'), height=2, disabledforeground='black', text=USER_NAME_STR, bg='lightyellow', state=DISABLED, anchor=W).grid(row=6, column=0, rowspan=2, columnspan=1, sticky=W + E + N + S)
userNameEntry = Entry(root, bd=4, font=('times', 10))
userNameEntry.grid(row=6, column=1, rowspan=2, columnspan=8, sticky=W + E + N + S)
userNameEntry.insert(0, username)
Label(root, font=('times', 12, 'bold'), disabledforeground='black', text=PASSWORD_STR, bg='lightyellow', state=DISABLED, anchor=W).grid(row=6, column=9, rowspan=2, columnspan=1, sticky=W + E + N + S)
passwordEntry = Entry(root, bd=4, font=('times', 10), show="*")
passwordEntry.grid(row=6, column=10, rowspan=2, columnspan=8, sticky=W + E + N + S)
passwordEntry.insert(0, password)

Label(root, font=('times', 12, 'bold'), disabledforeground='black', text=CLIENT_ID_STR, bg='lightyellow', state=DISABLED, anchor=W).grid(row=8, column=9, rowspan=2, columnspan=1, sticky=W + E + N + S)
clientIdEntry = Entry(root, bd=4, font=('times', 10))
clientIdEntry.grid(row=8, column=10, rowspan=2, columnspan=8, sticky=W + E + N + S)
clientIdEntry.insert(0, sampleClientID)

Label(root, font=('times', 12, 'bold'), height=2, disabledforeground='black', text=TOPIC_STR, bg='lightyellow', state=DISABLED, anchor=W).grid(row=8, column=0, rowspan=2, columnspan=1, sticky=W + E + N + S)
topicEntry = Entry(root, bd=4, font=('times', 10))
topicEntry.insert(0, topicSample)
topicEntry.grid(row=8, column=1, rowspan=2, columnspan=8, sticky=W + E + N + S)

Label(root, font=('times', 12, 'bold'), height=2, disabledforeground='black', text=SERVER_URL_STR, bg='lightyellow', state=DISABLED, anchor=W).grid(row=12, column=0, rowspan=2, columnspan=1, sticky=W + E + N + S)
cloudURLEntry = Entry(root, bd=4, font=('times', 10))
cloudURLEntry.grid(row=12, column=1, rowspan=2, columnspan=12, sticky=W + E + N + S)
cloudURLEntry.insert(0, cloudServerURL)
Label(root, font=('times', 12, 'bold'), disabledforeground='black', text=SERVER_PORT_STR, bg='lightyellow', state=DISABLED, width=10).grid(row=12, column=13, rowspan=2, columnspan=1, sticky=W + E + N + S)
cloudPortEntry = Entry(root, bd=4, font=('times', 10), width=5)
cloudPortEntry.grid(row=12, column=14, rowspan=2, columnspan=1, sticky=W + E + N + S)
cloudPortEntry.insert(0, cloudServerPort)
Label(root, font=('times', 12, 'bold'), disabledforeground='black', text=COM_PORT_STR, bg='lightyellow', state=DISABLED, width=10).grid(row=12, column=15, rowspan=2, columnspan=1, sticky=W + E + N + S)
comPortEntry = Entry(root, bd=4, fg='blue', font=('times', 10), width=7)
comPortEntry.grid(row=12, column=16, rowspan=2, columnspan=1, sticky=W + E + N + S)
for port_no, description, _ in list(serial.tools.list_ports.comports()):
    if (BOARD_COM_STR_DAPLINK in description) or (BOARD_COM_STR_MBED in description) or (BOARD_COM_STR_BLUETOOTH in description):
        LogToTextBox("Detected Board @ %s..." % port_no)
        comPortEntry.insert(0, port_no)
if not comPortEntry.get():
    comPortEntry.configure(fg='red')
    comPortEntry.insert(0, 'NONE')
goButton = Button(root, bd=4, font=('times', 12, 'bold'), text="CONNECT", bg='greenyellow', command=ConnectIoTAdapter)
goButton.grid(row=12, column=17, rowspan=2, columnspan=1, sticky=W + E + N + S)

Button(root, state=DISABLED, text=COPYRIGHT_STR).grid(row=14, column=0, rowspan=1, columnspan=18, sticky=W + E + N + S)

# Fill elements in the whole frame
for x in range(18):
    Grid.columnconfigure(root, x, weight=1)
for y in range(16):
    Grid.rowconfigure(root, y, weight=1)

# Update Title, install Close event handlers and Launch the GUI.
root.title(WINDOW_TITLE)
root.protocol('WM_DELETE_WINDOW', ExitDashboard)
root.mainloop()

sys.exit(0)
