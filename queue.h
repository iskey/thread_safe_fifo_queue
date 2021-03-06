#ifndef __QUEUE__
#define __QUEUE__

#include <semaphore.h>
#include <pthread.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif //__cplusplus

#define QUEUE_LENGTH 0 /** not use queue length indicator */
#if QUEUE_LENGTH
    #define QUEUE_LENGTH_MUX 1
#endif
#define QUEUE_MUX 0
#define QUEUE_SEM 1

typedef struct _QList QList;

struct _QList{
    unsigned int len;
    void *data;
    QList *next;
    QList *prev;
};

typedef struct _FIFO_Queue FIFO_Queue;

struct _FIFO_Queue{
    QList *head;
    QList *tail;
#if QUEUE_MUX
    /** queue mutex to avoid access conflict,
     this mutex is to avoid read bad member's data when another thread is doing queue_push_head.
    */
    pthread_mutex_t head_mux;
#endif
#if QUEUE_LENGTH
    /** queue length indicator */
    unsigned int length;
#endif
#if QUEUE_LENGTH_MUX
    /** mutex to protect variable:length from unwanted conflict  */
    pthread_mutex_t length_mux;
#endif

#if QUEUE_SEM
    sem_t sem;
    int (* q_sem_init)(sem_t *sem);
    int (* q_sem_add)(sem_t *sem);
    int (* q_sem_get)(sem_t *sem);
#endif
};

#define slice_malloc(mem, mem_size)  \
do{ \
    mem= malloc(mem_size);    \
    if(!mem){   \
        printf("alloc memory error!\n");    \
        }   \
}while(0);
#define slice_dup_s(dst, src, size) \
do{ \
    if(!memcpy(dst, src, size))    \
        printf("string copy error!\n"); \
}while(0);
#define slice_free(mem)  do{if(mem!= NULL)free(mem);}while(0);

extern FIFO_Queue* queue_new();
extern void queue_init(FIFO_Queue *queue);
extern void queue_push_head(FIFO_Queue * queue, unsigned int len, void *data);
extern void* queue_pop_tail(FIFO_Queue *queue, unsigned int *len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif //__cplusplus

#endif //__QUEUE__
