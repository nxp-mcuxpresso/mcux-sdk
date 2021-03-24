/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_LIST_H__
#define __SRTM_LIST_H__

#include <assert.h>

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief Get SRTM list object structure pointer.
 */
#define SRTM_LIST_OBJ(type, field, list) (type)((uint32_t)(list) - (uint32_t)(&((type)0)->field))

/**
 * @brief SRTM list fields
 */
typedef struct _srtm_list
{
    struct _srtm_list *prev; /*!< previous list node */
    struct _srtm_list *next; /*!< next list node */
} srtm_list_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize SRTM list head.
 *
 * @param list SRTM list head pointer.
 */
static inline void SRTM_List_Init(srtm_list_t *list)
{
    assert(list);

    list->prev = list;
    list->next = list;
}

/*!
 * @brief Check whether SRTM list is empty.
 *
 * @param list SRTM list head pointer.
 * @return TRUE when list is empty, FALSE otherwise.
 */
static inline bool SRTM_List_IsEmpty(srtm_list_t *list)
{
    assert(list);

    return list->next == list;
}

/*!
 * @brief Add list node at list head.
 *
 * @param list SRTM list head pointer.
 * @param node SRTM list node pointer to add.
 */
static inline void SRTM_List_AddHead(srtm_list_t *list, srtm_list_t *node)
{
    assert(list);
    assert(node);

    node->next       = list->next;
    node->prev       = list;
    list->next->prev = node;
    list->next       = node;
}

/*!
 * @brief Add list node at list tail.
 *
 * @param list SRTM list head pointer.
 * @param node SRTM list node pointer to add.
 */
static inline void SRTM_List_AddTail(srtm_list_t *list, srtm_list_t *node)
{
    assert(list);
    assert(node);

    node->prev       = list->prev;
    node->next       = list;
    list->prev->next = node;
    list->prev       = node;
}

/*!
 * @brief Insert list node before another.
 *
 * @param anchor SRTM list anchor node pointer.
 * @param node SRTM list node pointer to insert.
 */
static inline void SRTM_List_InsertBefore(srtm_list_t *anchor, srtm_list_t *node)
{
    SRTM_List_AddTail(anchor, node);
}

/*!
 * @brief Insert list node after another.
 *
 * @param anchor SRTM list anchor node pointer.
 * @param node SRTM list node pointer to insert.
 */
static inline void SRTM_List_InsertAfter(srtm_list_t *anchor, srtm_list_t *node)
{
    SRTM_List_AddHead(anchor, node);
}

/*!
 * @brief Remove list node from list.
 *
 * @param node SRTM list node pointer to remove.
 */
static inline void SRTM_List_Remove(srtm_list_t *node)
{
    assert(node);

    node->prev->next = node->next;
    node->next->prev = node->prev;
    /* clear node */
    SRTM_List_Init(node);
}

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_LIST_H__ */
