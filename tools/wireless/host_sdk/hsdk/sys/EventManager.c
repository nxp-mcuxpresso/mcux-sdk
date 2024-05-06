/*
 * \file EventManager.c
 * This is a source file for the EventManager module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdlib.h>

#include "EventManager.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static Observer *CreateObserver(void *callee, void (*Callback) (void *callee, void *object));
static void DestroyObserver(Observer *obs);

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

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

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
/*! *********************************************************************************
 * \brief Create a new event manager.
 * \details An EventMager is basically a linked list of Observers.
 *
 * \return pointer to the newly created EventManager
 ********************************************************************************* */
EventManager *CreateEventManager()
{
    EventManager *evt = (EventManager *) calloc(1, sizeof(EventManager));
    if (evt == NULL) {
        return NULL;
    }

    evt->obsList = CreateObserver(NULL, NULL);
    return evt;
}

/*! *********************************************************************************
 * \brief Destroy an event manager.
 * \details An EventMager is basically a linked list of Observers, so we destroy each
 * Observer and afterwards free the EventManager object.
 *
 * \param[in] evt  pointer to the EventManager to be destroyed
 *
 * \return None
 ********************************************************************************* */
void DestroyEventManager(EventManager *evt)
{
    Observer *crtObs;
    while (evt->obsList != NULL) {
        crtObs = evt->obsList;
        evt->obsList = crtObs->next;
        DestroyObserver(crtObs);
        crtObs = NULL;
    }

    free(evt);
}

/*! *********************************************************************************
 * \brief Adds a new Observer to the EventManager.
 *
 * \param[in] evt       pointer to the EventManager
 * \param[in] callee    the object to get notified
 * \param[in] Callback  pointer to a function that will be executed at notify
 *
 * \return None
 ********************************************************************************* */
void RegisterToEventManager(EventManager *evt, void *callee, void (*Callback) (void *callee, void *object))
{
    Observer *obs = CreateObserver(callee, Callback);
    obs->next = evt->obsList->next;
    evt->obsList->next = obs;
}

void DeregisterFromEvent(EventManager *evt, void *callee)
{
    Observer *crt = evt->obsList->next;
    Observer *prev = evt->obsList;
    while (crt != NULL && crt->callee != callee) {
        prev = crt;
        crt = crt->next;
    }

    if (crt != NULL) {
        prev->next = crt->next;
        DestroyObserver(crt);
        crt = NULL;
    }
}

void NotifyOnEvent(EventManager *evt, void *object)
{
    Observer *crt = evt->obsList->next;
    while (crt != NULL) {
        Observer *next = crt->next;
        if (crt->Callback != NULL) {
            crt->Callback(crt->callee, object);
        }
        crt = next;
    }
}

void NotifyOnSameEvent(EventManager *evt, void *object, void *(*func) (void *))
{
    Observer *crt = evt->obsList->next;
    while (crt != NULL) {
        if (crt->Callback != NULL) {
            crt->Callback(crt->callee, func(object));
        }
        crt = crt->next;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static Observer *CreateObserver(void *callee, void (*Callback) (void *callee, void *object))
{
    Observer *obs = (Observer *) calloc(1, sizeof(Observer));
    obs->callee = callee;
    obs->Callback = Callback;
    obs->next = NULL;
    return obs;
}
static void DestroyObserver(Observer *obs)
{
    obs->next = NULL;
    obs->callee = NULL;
    obs->Callback = NULL;
    free(obs);
}
