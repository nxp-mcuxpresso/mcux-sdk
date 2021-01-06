#ifndef KEYNETIKPEDOMETER_H
#define KEYNETIKPEDOMETER_H
/*
============================================================================
 Name        : KeynetikPedometer.h
 Author      : KEYnetik, Inc.
 Version     :
 Copyright   : Copyright 2011 by KEYnetik, Inc.
 Description : Pedometry interface for Freescale MMA9553L Pedometer project
============================================================================
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct KeynetikConfig
{
    uint8_t steplength; /* Step length in centimeters. If the value is 0 it will automatically calculate the user's step
                           length from their gender and height. */
    uint8_t height;     /* Height in centimeters. This is used to estimate the step length if steplength is set to 0. */
    uint8_t weight;     /* Weight in kilograms. This is used to estimate the calories burned. */
    uint8_t filtersteps; /* Number of steps that must occur within the filtertime in order to decide that the user is
                            making steps. If this is set to 0, then the step filtering is disabled. */
    struct
    {
        uint8_t
            filtertime : 7; /* Number of seconds in which filtersteps occur to decide that the user is making steps. If
                               this is set to 0, then the step filtering is disabled. */
        uint8_t male : 1;   /* Set to 1 for a male user, or 0 for a female user. */
    } bits;
    uint8_t
        speedperiod; /* Length of the time window for speed calculation, in seconds. The allowable range is from 1 to 5.
                        If the value specified is greater than 5, it will be reset to 5, 0 will be reset to 1 */
    uint8_t stepthreshold; /* Step threshold value, in 1000ths of G. Set to 0 to use the default of 130 (0.13G). */
    /* Higher values will make the pedometer less sensitive, lower values may lead to false positives. */
} KeynetikConfig;

/*
* Pedometry staistcics (since last KeynetikInitialize), populated by the latest call to KeynetikHandleIncomingEvent:
*/
/*
* Step count
*/
extern unsigned int keynetikStepCount;
/*
* Distance covered (in meters)
*/
extern unsigned int keynetikDistance;
/*
* Average speed (in meters per hour).
*/
extern unsigned short keynetikSpeed;
/*
* Calories buirned (since last KeynetikInitialize), populated by the latest call to KeynetikHandleIncomingEvent.
*/
extern unsigned int keynetikCalories;

/*
* Current activity level, updated with every call to KeynetikHandleIncomingEvent
*/
typedef enum
{
    KeynetikActivityUnknown = 0,
    KeynetikActivityRest = 1,
    KeynetikActivityWalking = 2,
    KeynetikActivityJogging = 3,
    KeynetikActivityRunning = 4
} KeynetikActivityLevel;
extern KeynetikActivityLevel keynetikActivityLevel;

/**
* Initialize the Keynetik library.
* \param oneG Value of 1G
* \param frequencyHz Accelerometer polling frequency, in readings per second
* \param isMale User's gender: 0 for female, non-0 for male
* \param heightCm User's height in centimeters. May be 0 if a custom stride length is to be used
* \param weightCm User's weight in kilograms
* \param strideCm Custom stride length in centimeters, or 0 for a standard stride length based on gender and height
* \param stepDelay Number of steps to expect before counting any steps (0 to turn off step filtering)
* \param delayWindow Amount of time within which these steps must be detected (in seconds; 0 to turn off step filtering)
*/
void KeynetikInitialize(unsigned short oneG, unsigned short frequencyHz, KeynetikConfig *config);

#define KEYNETIK_STEP 1
#define KEYNETIK_ACTIVITYCHANGED 2
/**
* Process an accelerometer reading and report detected events if any.
* \param x X axis reading
* \param y Y axis reading
* \param z Z axis reading
* \return combination of flags KEYNETIK_STEP and KEYNETIK_ACTIVITYCHANGED
*/
unsigned int KeynetikHandleIncomingEvent(int x, int y, int z);

/**
* Clear the collected data. Can be used after a period of skipped readings to re-initialize processing.
*/
void KeynetikReset();

/**
* Finalize the Keynetik library.
*/
void KeynetikTerminate();

#ifdef __cplusplus
}
#endif

#endif
