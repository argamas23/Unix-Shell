#include "headers.h"

void check_status( int sig)
{
    int status;
    pid_t pid;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("Process exited normally (%d)\n",pid);
        }
        else if (WIFSIGNALED (status))
        {
            printf("Process exited abnormally(%d)\n",  pid);
        }
    }
}

void syscommands(char** command_list, int background, int count, int time_flag)
{
    if (count == 0) {
        fprintf(stderr, "No command provided.\n");
        return;
    }

    // Allocate memory for execvp arguments
    char **args = malloc((count + 1) * sizeof(char*));
    if (args == NULL) {
        perror(RED"malloc failed"RESET);
        return;
    }

    // Copy the command_list to args
    for (int i = 0; i < count; i++) {
        args[i] = command_list[i];
    }
    args[count] = NULL; // NULL-terminate the array for execvp

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        execvp(args[0], args);
        perror(RED"execvp failed"RESET);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Parent process
        if (background)
        {
            printf("%d\n", pid); // Print the PID of the background process
            add_process(pid, command_list[0]);
        }
        else
        {
            struct timeval start, end;
            gettimeofday(&start, NULL);

            int status;
            waitpid(pid, &status, 0); // Wait for the child process to complete

            gettimeofday(&end, NULL);

            double duration = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
            if(time_flag != 1)
                printf("<%s : %.0fs>\n", command_list[0], duration);

            add_process(pid, command_list[0]);
        }
    }
    else
    {
        perror(RED"fork failed"RESET);
    }

    free(args); // Free the allocated memory
}
