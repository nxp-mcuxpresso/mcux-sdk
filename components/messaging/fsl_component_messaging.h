/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MESSAGING_H__
#define __MESSAGING_H__

#include "fsl_common.h"
#include "fsl_component_generic_list.h"

/*! @brief Definition to determine whether use message macro define. */
#ifndef MSG_USE_MACRO
#define MSG_USE_MACRO (1)
#endif

#if (defined(MSG_USE_MACRO) && (MSG_USE_MACRO == 1U))
#define MSG_QueueInit(anchor) LIST_Init(anchor, 0)
#define MSG_QueueDeinit(anchor)                        \
    while (MSG_QueueGetHead(anchor))                   \
    {                                                  \
        (void)MEM_BufferFree(LIST_RemoveHead(anchor)); \
    }
#endif
/*!
 * @addtogroup Messaging
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The msg status */
typedef enum _messaging_status
{
    kMSG_Success = kStatus_Success,                  /*!< Success */
    kMSG_Error   = MAKE_STATUS(kStatusGroup_MSG, 1), /*!< Error */
} messaging_status_t;

typedef list_label_t messaging_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

#if (defined(MSG_USE_MACRO) && (MSG_USE_MACRO == 0U))
/*!
 * @brief Initializes the message queue.
 *
 * This function initializes the message queue.
 *
 * @param msgQueue The message queue pointer.
 * @retval kMSG_Success Initialization is successful.
 */
void MSG_QueueInit(messaging_t *msgQueue);

/*!
 * @brief De-initializes the message queue.
 *
 * This function de-initializes the message queue.
 *
 * @param msgQueue The message queue pointer.
 */
void MSG_QueueDeinit(messaging_t *msgQueue);
#endif
/*!
 * @brief Allocates a message node with the length.
 *
 * This function allocates a message node with the length.
 *
 * @param length The length of the message.
 * @retval The allocated memory buffer address.
 */
void *MSG_Alloc(uint32_t length);

/*!
 * @brief frees a buffer allocated by #MSG_Alloc.
 *
 * This function frees a buffer allocated by #MSG_Alloc.
 *
 * @param buffer The buffer address.
 */
void MSG_Free(void *buffer);

/*!
 * @brief Links a message to the tail of the message queue.
 *
 * The function links a message to the tail of the message queue.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msgQueue The message queue pointer.
 * @param msg The pointer of the message allocated by the #MSG_Alloc.
 * @retval kMSG_Success The message is added.
 * @retval kMSG_Error The message addition failed.
 */
messaging_status_t MSG_QueueAddTail(messaging_t *msgQueue, void *msg);

/*!
 * @brief Links a message to the head of the message queue.
 *
 * The function links a message to the head of the message queue.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msgQueue The message queue pointer.
 * @param msg The pointer of the message allocated by the #MSG_Alloc.
 * @retval kMSG_Success The message is added.
 * @retval kMSG_Error The message addition failed.
 */
messaging_status_t MSG_QueueAddHead(messaging_t *msgQueue, void *msg);

/*!
 * @brief Links a message to the previous of the given message.
 *
 * The function links a message to the previous of the given message.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msg The given message pointer.
 * @param newMsg A new message pointer needs to be added.
 * @retval kMSG_Success The message is added.
 * @retval kMSG_Error The message addition failed.
 */
messaging_status_t MSG_QueueAddPrev(void *msg, void *newMsg);

/*!
 * @brief Unlinks a message from its message queue.
 *
 * The function unlinks a message from its message queue.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msg The message pointer.
 * @retval kMSG_Success The message is removed.
 * @retval kMSG_Error The message removal failed.
 */
messaging_status_t MSG_QueueRemove(void *msg);

/*!
 * @brief Unlinks the head from the message queue.
 *
 * The function unlinks the head from the message queue.
 *
 * @param msgQueue The message queue pointer.
 * @retval NULL if the message queue is empty, or the pointer of removed message if removal was successful.
 */
void *MSG_QueueRemoveHead(messaging_t *msgQueue);

/*!
 * @brief Gets the head of the message queue.
 *
 * The function gets the head of the message queue.
 *
 * @param msgQueue The message queue pointer.
 * @retval The pointer of the message if the head is not NULL, or NULL.
 */
void *MSG_QueueGetHead(messaging_t *msgQueue);

/*!
 * @brief Gets the next node of a given message.
 *
 * The function gets the next node of a given message.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msg The message pointer.
 * @retval The pointer of the message if the next pointer is not NULL, or NULL.
 */
void *MSG_QueueGetNext(void *msg);

/*!
 * @brief Gets the previous node of a given message.
 *
 * The function gets the previous node of a given message.
 * The memory space of the message must be allocated by calling the function
 * #MSG_Alloc. And the memory space of the message must be freed by calling
 * the function #MSG_Free.
 *
 * @param msg The message pointer.
 * @retval The pointer of the message if the previous pointer is not NULL, or NULL.
 */
void *MSG_QueueGetPrev(void *msg);

#if defined(__cplusplus)
}
#endif
/*! @}*/
#endif /* __MESSAGING_H__ */
