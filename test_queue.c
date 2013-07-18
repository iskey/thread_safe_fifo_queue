#include "string.h"
#include "stdlib.h"
#include "queue.h"
#include "stdio.h"

int main()
{
    FIFO_Queue *queue= queue_new();
    queue_init(queue);

    char *tmp1="11111111111111";
    char *tmp2="22222222222222";
    char *tmp3="33333333333333";
    char *tmp4="44444444444444";
    char *tmp5="55555555555555";
//    queue_push_head(queue,tmp1);
//    queue_push_head(queue,tmp2);
//    queue_push_head(queue,tmp3);
//    queue_push_head(queue,tmp4);
//    queue_push_head(queue,tmp5);

    {
        char *ttt;
        slice_malloc(ttt, 100);
        strcpy(ttt, tmp1);
        queue_push_head(queue, ttt);
    }

    {
        char *ttt;
        slice_malloc(ttt, 100);
        strcpy(ttt, tmp2);
        queue_push_head(queue, ttt);
    }


    int i;
    for(i= 0; i<10; i++){
        char *data;
        data= queue_pop_tail(queue);
        printf("data is %s\n",(char*)data);
//        printf("data addr is 0x%0x\n",data);
        slice_free(data);
    }

    queue_free(queue);
}

