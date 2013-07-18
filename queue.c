/******************************************************************************

           This is Iskey.

 ******************************************************************************/
/**
 * @file    queue.c
 * @brief   simple queue.
 * @author  xyc@outlook.com
 * @version Initial Draft
 * @note    none
 * @date    2013/7/17
 */
/******************************************************************************
 *  Function List :
 *  History       :
 *  1.Date        : 2013/7/17
 *    Author      : xyc
 *    Modification: Created file
 *
******************************************************************************/

/** external variables */

/** external routine prototypes */

/** internal routine prototypes */

/** project-wide global variables */

/** module-wide global variables */

/** constants */

/** macros */

/** routines' implementations */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "queue.h"

#undef NULL
#define NULL 0
#define slice_new(type) ((type*)slice_alloc0(sizeof(type)))

#define QList_new() slice_new(QList)
#define QList_free()

#define q_return_if_fail(q) {if(!q)return;}
#define q_assert(q) {if(!q){printf("assertion failed: %s, file %s line %s\n", #q, __FILE__, __LINE__);}}

void* slice_alloc0(unsigned int mem_size)
{
    void *mem = calloc(1, mem_size);
    if(mem){
        memset(mem, 0, mem_size);
    }
    else{
        printf("alloc memory error!\n");
    }
    return mem;
}
void
list_free(QList *list)
{
//    slice_free(list->data);
    slice_free(list);
}
QList*
list_last(QList *list)
{
    if(list)
    {
        while(list->next)
        list = list->next;
    }
    return list;
}

QList*
list_prepend(QList *list, void *data)
{
    QList *new_list;

    new_list = slice_new(QList);
    new_list->data = data;
    new_list->next = list;

    if(list)
    {
        new_list->prev = list->prev;
        if(list->prev){
            list->prev->next = new_list;
        }
        list->prev= new_list;
    }
    else {
        new_list->prev = NULL;
    }

    return new_list;
}
QList*
list_append(QList *list, void *data)
{
    QList *new_list;
    QList *last;

    new_list = slice_new(QList);
    new_list->data = data;
    new_list->next = NULL;

    if(list)
    {
        last = list_last(list);
        last->next = new_list;
        new_list->prev = last;

        return list;
    }
    else {
        new_list->prev = NULL;
        return new_list;
    }
}

/**
 * @brief Create a new FIFO_Queue
 * @param [in] void
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/17
 *    Author       : xyc
 *    Modification : Created function
 */
FIFO_Queue*
queue_new(void)
{
    return slice_new(FIFO_Queue);
}
void
queue_free(FIFO_Queue *queue)
{
    q_return_if_fail(queue!= NULL);
    /*
    real free need to do here.
    */
}
void
queue_init(FIFO_Queue *queue)
{
    q_return_if_fail(queue != NULL);

    queue->head= queue->tail = NULL;
    queue->length= 0;
}
void
queue_push_head(FIFO_Queue *queue, void *data)
{
    q_return_if_fail(queue != NULL);

    queue->head = list_prepend(queue->head, data);
    if(!queue->tail){//head equals tail
        queue->tail = queue->head;
    }
    queue->length++;
}
void
queue_push_tail(FIFO_Queue *queue, void *data)
{

}
void *
queue_pop_head(FIFO_Queue *queue)
{

}
void *
queue_pop_tail(FIFO_Queue *queue)
{
    q_return_if_fail(queue!= NULL);

    if(queue->tail)
    {
        QList *node = queue->tail;
        void *data = node->data;

        queue->tail = node->prev;
        if(queue->tail){
            queue->tail->next = NULL;
        }
        else {
            queue->head = NULL;
        }
        queue->length--;
        list_free(node);

        return data;
    }

    return NULL;
}

