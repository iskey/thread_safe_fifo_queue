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
/**
 * @brief free one list structure
 * @param [in] QList *list
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
void list_free(QList *list)
{
    slice_free(list);
}
/**
 * @brief search to last list
 * @param [in] QList *list
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
QList* list_last(QList *list)
{
    if(list)
    {
        while(list->next)
        list = list->next;
    }
    return list;
}
/**
 * @brief add one list member infront of the list head
 * @param [in] QList *list
 * @param [in] unsigned int len
 * @param [in] void *data
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
QList* list_prepend(QList *list, unsigned int len, void *data)
{
    QList *new_list;
//    printf("func %s, len is %d, data is %s\n", __func__, len, data);
    new_list = slice_new(QList);
    new_list->len = len;
    slice_malloc(new_list->data, new_list->len);
    slice_dup_s(new_list->data, data, new_list->len);
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
/**
 * @brief add one list member after list tail
 * @param [in] QList *list
 * @param [in] unsigned int len
 * @param [in] void *data
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
QList* list_append(QList *list, unsigned int len, void *data)
{
    QList *new_list;
    QList *last;

    new_list = slice_new(QList);
    new_list->len = len;
    new_list->next = NULL;
    slice_malloc(new_list->data, new_list->len);
    slice_dup_s(new_list->data, data, new_list->len);

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
FIFO_Queue* queue_new(void)
{
    return slice_new(FIFO_Queue);
}
/**
 * @brief free a queue structure
 * @param [in] FIFO_Queue *queue
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
void queue_free(FIFO_Queue *queue)
{
    q_return_if_fail(queue!= NULL);

    slice_free(queue);
}
/**
 * @brief initial a queue
 * @param [in] FIFO_Queue *queue
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
void queue_init(FIFO_Queue *queue)
{
    q_return_if_fail(queue != NULL);

    queue->head= queue->tail = NULL;
#if QUEUE_LENGTH
    queue->length= 0;
#endif
#if QUEUE_LENGTH_MUX
    pthread_mutex_init(&(queue->length_mux), NULL);
#endif
#if QUEUE_MUX
    pthread_mutex_init(&(queue->head_mux), NULL);
#endif
}
int queue_lock(FIFO_Queue *queue)
{
#if QUEUE_MUX
    pthread_mutex_lock(&(queue->head_mux));
#endif
    return 0;
}
int queue_unlock(FIFO_Queue *queue)
{
#if QUEUE_MUX
    pthread_mutex_unlock(&(queue->head_mux));
#endif
    return 0;
}
int queue_len_lock(FIFO_Queue *queue)
{
#if QUEUE_LENGTH_MUX
    pthread_mutex_lock(&(queue->length_mux));
#endif  //QUEUE_LENGTH_MUX
    return 0;
}
int queue_len_unlock(FIFO_Queue *queue)
{
#if QUEUE_LENGTH_MUX
    pthread_mutex_unlock(&(queue->length_mux));
#endif  //QUEUE_LENGTH_MUX
    return 0;
}
/**
 * @brief push a data member to a queue's head
 * @param [in] FIFO_Queue *queue
 * @param [in] unsigned int len
 * @param [in] void *data
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
void queue_push_head(FIFO_Queue *queue, unsigned int len, void *data)
{
    q_return_if_fail(queue != NULL);

    queue_lock(queue);
    queue->head = list_prepend(queue->head, len, data);
    if(!queue->tail){//head equals tail
        queue->tail = queue->head;
    }
    queue_unlock(queue);

#if QUEUE_LENGTH
    queue_len_lock(queue);
    queue->length++;
    queue_len_unlock(queue);
#endif //QUEUE_LENGTH
}
void queue_push_tail(FIFO_Queue *queue, void *data)
{

}
void* queue_pop_head(FIFO_Queue *queue)
{

}
/**
 * @brief pop a member from queue's tail
 * @param [in] FIFO_Queue *queue
 * @param [in] unsigned int *len
 * @param [out] None
 * @return
 * @note
 *  Calls      :
 *  Called By  :
 *
 *  History        :
 *  1.Date         : 2013/7/19
 *    Author       : xyc
 *    Modification : Created function
 */
void* queue_pop_tail(FIFO_Queue *queue, unsigned int *len)
{
    q_return_if_fail(queue!= NULL);

    if(queue->tail)
    {
        queue_lock(queue);
        QList *lst_node = queue->tail;
        void *data= lst_node->data;
        *len= lst_node->len;

        queue->tail = lst_node->prev;
        if(queue->tail){
            queue->tail->next = NULL;
        }
        else {
            queue->head = NULL;
        }
        list_free(lst_node);
        queue_unlock(queue);

#if QUEUE_LENGTH
        queue_len_lock(queue);
        queue->length--;
        queue_len_unlock(queue);
#endif //QUEUE_LENGTH

        return data;
    }

    return NULL;
}

