/*
 * \file EventManager.h
 * This is the header file for the EventManager module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __EVTMGR__
#define __EVTMGR__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief An observer structure, containing a callee, callback and a pointer to the
 * next structure of its kind. Element of a linked list.
 */
typedef struct _observer {
    void *callee; /**< User defined object to be notified upon reception. */
    void (*Callback) (void *callee, void *object); /**< Function pointer to be executed upon reception. */
    struct _observer *next; /**< Pointer to the next object of its kind. */
} Observer;

/**
 * @brief The event manager is equivalent to a list of observers.
 */
typedef struct {
    Observer *obsList;	/**< A Linked List with Observer nodes. */
} EventManager;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
DLLEXPORT EventManager *CreateEventManager();
DLLEXPORT void DestroyEventManager(EventManager *);
DLLEXPORT void RegisterToEventManager(EventManager *evt, void *callee, void(*Callback) (void *callee, void *object));
DLLEXPORT void DeregisterFromEvent(EventManager *evt, void *callee);
DLLEXPORT void NotifyOnEvent(EventManager *evt, void *object);
DLLEXPORT void NotifyOnSameEvent(EventManager *evt, void *object, void *(*func) (void *));

#ifdef __cplusplus
}
#endif

#endif
