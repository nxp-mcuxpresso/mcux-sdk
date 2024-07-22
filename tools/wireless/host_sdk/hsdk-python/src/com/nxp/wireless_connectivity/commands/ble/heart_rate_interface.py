'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

# Heart Rate Service - Heart Rate Format
gHrs_8BitHeartRateFormat_c = 0x00
gHrs_16BitHeartRateFormat_c = 0x01

# Heart Rate Service - Sensor Contact detected status
gHrs_SensorContactNotDetected_c = 0x00
gHrs_SensorContactDetected_c = 0x02

# Heart Rate Service - Sensor Contact supported status
gHrs_SensorContactNotSupported_c = 0x00
gHrs_SensorContactSupported_c = 0x04

# Heart Rate Service - Energy expended status
gHrs_EnergyExpendedDisabled_c = 0x00
gHrs_EnergyExpendedEnabled_c = 0x08

# Heart Rate Service - RR Intervals status
gHrs_RrIntervalsDisabled_c = 0x00
gHrs_RrIntervalsEnabled_c = 0x10

# Heart Rate Service - Body Sensor Location
gHrs_BodySensorLocOther_c = 0x00
gHrs_BodySensorLocChest_c = 0x01
gHrs_BodySensorLocWrist_c = 0x02
gHrs_BodySensorLocFinger_c = 0x03
gHrs_BodySensorLocHand_c = 0x04
gHrs_BodySensorLocEarLobe_c = 0x05
gHrs_BodySensorLocFoot_c = 0x06


gFastConnMinAdvInterval_c = 32  # 20 ms
gFastConnMaxAdvInterval_c = 48  # 30 ms

# Advertising Type
gAdvConnectableUndirected_c = 0x00  # Answers to both connect and scan requests.
gAdvDirectedHighDutyCycle_c = 0x01  # Answers only to connect requests; smaller advertising interval for quicker connection.
gAdvScannable_c = 0x02  # Answers only to scan requests.
gAdvNonConnectable_c = 0x03  # Does not answer to connect nor scan requests.
gAdvDirectedLowDutyCycle_c = 0x04   # Answers only to connect requests; larger advertising interval.

# Bluetooth Device Address Types
gBleAddrTypePublic_c = 0x00  # Public Device Address - fixed into the Controller by the manufacturer.
gBleAddrTypeRandom_c = 0x01  # Random Device Address - set by the Host into the Controller for privacy reasons.

gAdvChanMapFlag37_c = 0x01  # Bit for channel 37.
gAdvChanMapFlag38_c = 0x02  # Bit for channel 38.
gAdvChanMapFlag39_c = 0x04  # Bit for channel 39.
gGapAdvertisingChannelMapDefault_c = gAdvChanMapFlag37_c | gAdvChanMapFlag38_c | gAdvChanMapFlag39_c

# Advertising Filter Policy values
gProcessAll_c = 0x00  # Default value: accept all connect and scan requests.
gProcessConnAllScanWL_c = 0x01  # Accept all connect requests, but scan requests only from devices in White List.
gProcessScanAllConnWL_c = 0x02  # Accept all scan requests, but connect requests only from devices in White List.
gProcessWhiteListOnly_c = 0x03  # Accept connect and scan requests only from devices in White List.
