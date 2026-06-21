#include "headers.h"

void fg(char** command_list, int count)
{
    int pid = 0;
    pid = atoi(command_list[1]);
    if (kill(pid, SIGCONT) == -1)
        perror(RED"kill"RESET);

    if (waitpid(pid, NULL, WUNTRACED) == -1)
        perror(RED"waitpid"RESET);
}

void bg(char** command_list)
{
    int pid = 0;
    pid = atoi(command_list[1]);
    if(kill(pid, SIGCONT) == -1)
        perror(RED"kill"RESET);
}