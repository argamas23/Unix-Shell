#include "headers.h"

void ping(char** command_list)
{
    int signal = atoi(command_list[2])%32;
    pid_t pid = atoi(command_list[1]);

    if(kill(pid,0) == -1)
    {
        if(errno == ESRCH)
        {
            printf(RED"No Such Process Found\n"RESET);
            return;
        }
        else
        {
            perror(RED"Error Sending Signal"RESET);
            return;
        }
    }

    if(kill(pid, signal) == 0)
    {
        printf("Sent signal %d to process with pid %d\n", signal, pid);
    }
    else
        perror(RED"Error sending signal"RESET);
}