#ifndef LOG_H
#define LOG_H

typedef struct lognode {
    char* command;
    struct lognode* next;
}lognode;

typedef struct logque
{
    lognode* rear;
    lognode* front;
    int count;
}logque;

logque* init();
bool isEmpty(logque* que);
int counter(logque* que);
void enque(logque* que, char* input);
void dequeue(logque* que);
void display_log(logque* que);
char* get_log_command(logque* log, int index);
void purge(logque* que);

#endif