#include "headers.h"

void proclore(char** command_list, int count)
{
    FILE* stat_file;
    char state;
    pid_t tpid;
    if (count > 1)
        tpid = (pid_t) atoi(command_list[1]);
    else
        tpid = getpid();

    char* stat_path = (char*)malloc(SIZE*sizeof(char));
    char* buffer = (char*)malloc(SIZE*sizeof(char));
    int pg;

    snprintf(stat_path,SIZE, "/proc/%d/stat", tpid);
    stat_file = fopen(stat_path, "r");

    if(fgets(buffer,SIZE, stat_file) != NULL)
    {
        sscanf(buffer, "%*d %*s %c %*d %d", &state, &pg);
        
        
        printf("PID: %d\n", tpid);
        int fg_check = tcgetpgrp(STDIN_FILENO);
        if(pg == fg_check && (state == 'R'|| state == 'S'))
            printf("Process Status: %c+\n", state);
        else
            printf("Process Status: %c\n", state);
        printf("Process Group: %d\n", pg);
    }
    else {
        perror(RED"Failed to read stat file"RESET);
    }

    // Close the stat file
    fclose(stat_file);

    snprintf(stat_path, SIZE, "/proc/%d/status", tpid);
    stat_file = fopen(stat_path, "r");

    while(fgets(buffer,SIZE,stat_file))
    {
        if(strncmp(buffer, "VmSize:", 7) == 0)
        {
            char* size_str = buffer + 7;
            int size_kb = atoi(size_str);
            long size_bytes = (long)size_kb * 1024;
            printf("Virtual Memory : %ld\n", size_bytes);
            break;
        }
    }

    fclose(stat_file);

    snprintf(stat_path, SIZE, "/proc/%d/exe", tpid);
    ssize_t len = readlink(stat_path,buffer,SIZE-1);
    if(len != -1)
    {
        buffer[len] = '\0';
        printf("Executable Path: %s\n", buffer);
    }
    else
    {
        perror(RED"Failed to read executable path"RESET);
    }
}
