#ifndef __QUEUE__
#define __QUEUE__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif //__cplusplus

typedef struct _QList QList;

struct _QList{
    void *data;
    QList *next;
    QList *prev;
};

typedef struct _FIFO_Queue FIFO_Queue;

struct _FIFO_Queue{
    QList *head;
    QList *tail;
    unsigned int length;
};

#define slice_malloc(mem, mem_size)  \
do{ \
    mem= malloc(mem_size);    \
    if(!mem){   \
        printf("alloc memory error!\n");    \
        }   \
}while(0);
#define slice_free(mem)  do{if(mem!= NULL)free(mem);}while(0);

extern FIFO_Queue* queue_new();
extern void queue_init(FIFO_Queue *queue);
extern void queue_push_head(FIFO_Queue * queue, void * data);
extern void* queue_pop_tail(FIFO_Queue *queue);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif //__cplusplus

#endif //__QUEUE__