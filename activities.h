#ifndef ACTIVITIES_H
#define ACTIVITIES_H
#include "headers.h"
typedef struct Process{
    char command[SIZE];
    pid_t pid;
    char state [LOGSIZE];  // R, S, Z, etc.
} Process;

extern Process processes[SIZE];

extern int p_count;

void add_process(pid_t pid, char* command);
void status(pid_t pid);

void activities();

#endif