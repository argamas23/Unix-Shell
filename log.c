#include "headers.h"
logque* init()
{
    logque* que = (logque*)malloc(sizeof(logque));
    que -> front = que -> rear = NULL;
    que -> count = 0;
    return que;
}

bool isEmpty(logque *que)
{
    if(que->count == 0)
        return true;
    return false;
}

int counter(logque* que)
{
    return que->count;
}

void enque(logque* que, char* input)
{
    
        lognode* new = (lognode*)malloc(sizeof(lognode));
        
        new -> command = strdup(input);
        new -> next = NULL;
        if(que-> count == 0)
        {
            que->front = que -> rear = new;
        }
        else
        {
            que->rear->next = new;
            que->rear = que->rear->next;
        }
        que ->count ++;
    
}

void dequeue (logque* que)
{
    if(!isEmpty(que)){
    lognode *temp = que->front;
    que->front = que->front->next;
    que->count--;
    free(temp);}
}

void display_log(logque* que)
{
    lognode* temp = que->front;
    int total_count = counter(que); 

    while (temp != NULL) {
        printf("%d: %s\n", total_count--, temp->command);
        temp = temp->next;
    }
}

void purge(logque* que)
{
    while (!isEmpty(que)) {
        dequeue(que);
    }
}

