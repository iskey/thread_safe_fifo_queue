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

    queue_push_head(queue, strlen(tmp1), tmp1);
    queue_push_head(queue, strlen(tmp2), tmp2);
    queue_push_head(queue, strlen(tmp3), tmp3);
    queue_push_head(queue, strlen(tmp4), tmp4);
    queue_push_head(queue, strlen(tmp5), tmp5);
    queue_push_head(queue, strlen(tmp2), tmp2);
    queue_push_head(queue, strlen(tmp2), tmp2);
    queue_push_head(queue, strlen(tmp3), tmp3);
    queue_push_head(queue, strlen(tmp4), tmp4);
    queue_push_head(queue, strlen(tmp5), tmp5);

    int i;
    for(i= 0; i<14; i++){
        char *data;
        unsigned int len;
        data= queue_pop_tail(queue, &len);
        printf("date length is %d, data is %s\n",len, (char*)data);
        slice_free(data);
    }

    queue_free(queue);
}

