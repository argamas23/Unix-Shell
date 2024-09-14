#include "headers.h"
#include "activities.h"

Process processes[SIZE];  
int p_count = 0;  


void add_process(pid_t pid, char* command)
{
    processes[p_count].pid = pid;
    strncpy(processes[p_count].command, command, SIZE);
    strcpy(processes[p_count].state, "Running");
    p_count++;
}


void status(pid_t pid)
{
    char stat_path[SIZE];
    snprintf(stat_path, SIZE, "/proc/%d/stat", pid);  

    FILE* file = fopen(stat_path, "r");
    if (!file)
    {
        
        for (int i = 0; i < p_count; i++)
        {
            if (processes[i].pid == pid)
            {
                strcpy(processes[i].state, "Terminated");
            }
        }
        return;
    }


    int unused;
    char state;
    fscanf(file, "%d %*s %c", &unused, &state);  

    
    for (int i = 0; i < p_count; i++)
    {
        if (processes[i].pid == pid)
        {
            switch (state)
            {
                case 'R':
                    strcpy(processes[i].state, "Running");
                    break;
                case 'S':
                    strcpy(processes[i].state, "Sleeping");
                    break;
                case 'T':
                    strcpy(processes[i].state, "Stopped");
                    break;
                case 'Z':
                    strcpy(processes[i].state, "Zombie");
                    break;
                default:
                    strcpy(processes[i].state, "Unknown");
            }
        }
    }

    fclose(file);
}

int compare_processes(const void *a, const void *b)
{
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return strcmp(processA->command, processB->command);
}


void activities()
{
    
    qsort(processes, p_count, sizeof(Process), compare_processes);

    
    for (int i = 0; i < p_count; i++)
    {
        status(processes[i].pid);  
        printf("%d : %s - %s\n", processes[i].pid, processes[i].command, processes[i].state);
    }
}


