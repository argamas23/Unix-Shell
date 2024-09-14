#include "headers.h"

char* piping(char* username, char* hostname, char* home_dir, char* command, char* prev_dir, logque* log) {
    char* to_tokenize = (char*)calloc(SIZE, sizeof(char));
    int pip_count = 0;

    
    for (int i = 0; i < strlen(command); i++) {
        if (command[i] == '|') {
            pip_count++;
        }
    }

    // char pip_command[pip_count+1][4097];
    char** pip_command = (char**)malloc((pip_count + 1) * sizeof(char*));
    for (int i = 0; i < pip_count + 1; i++) {
        pip_command[i] = (char*)malloc(SIZE * sizeof(char));
    }

    
    int tok = 0;
    // printf("Here2 %s\n",command);
    char* pip_token = strtok(command, "|");
    while (pip_token != NULL) {
        strcpy(pip_command[tok++], pip_token);
        pip_token = strtok(NULL, "|");
    }

    
    char* end = (char*)calloc(5, sizeof(char));
    strcpy(end, "\0");

    int original_output = dup(STDOUT_FILENO);
    int original_input = dup(STDIN_FILENO);
    int current[2], previous[2];
    // printf("%d\n", tok);
    // for(int i = 0; i<tok;i++)
    // {
    // printf("%s\n",pip_command[i]);
    // }
    // Process each piped command
    for (int i = 0; i < pip_count; i++) {
        if (pipe(current) == -1) {
            printf(RED"Error in creating pipe\n"RESET);
            return end;
        }

        pid_t pid = fork();
        if (pid == -1) {
            printf(RED"Unable to create a child process\n"RESET);
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            close(current[0]);

            if (i > 0) {
                // Redirect input from the previous pipe
                if (dup2(previous[0], STDIN_FILENO) == -1) {
                    printf(RED"Error in redirecting input\n"RESET);
                    exit(EXIT_FAILURE);
                }
                close(previous[0]);
            }

            // Redirect output to the current pipe
            if (dup2(current[1], STDOUT_FILENO) == -1) {
                printf(RED"Error in redirecting output\n"RESET);
                exit(EXIT_FAILURE);
            }
            close(current[1]);

            // Tokenize and execute the command
            to_tokenize = tokenize(username, hostname, home_dir, pip_command[i], prev_dir, log);
            exit(EXIT_SUCCESS);
        } else { // Parent process
            wait(NULL);
            close(current[1]);

            if (i > 0) {
                close(previous[0]);
            }
            previous[0] = current[0];
            previous[1] = current[1];
        }
    }

    // Handle the last command
    if (dup2(original_output, STDOUT_FILENO) == -1) {
        printf(RED"Error in restoring output\n"RESET);
        return end;
    }

    if (dup2(previous[0], STDIN_FILENO) == -1) {
        printf(RED"Error in redirecting input\n"RESET);
        return end;
    }
    close(previous[0]);

    to_tokenize = tokenize(username, hostname, home_dir, pip_command[pip_count], prev_dir, log);

    // Restore original input/output
    if (dup2(original_input, STDIN_FILENO) == -1) {
        printf(RED"Error in restoring input\n"RESET);
        return end;
    }

    // Free allocated memory
    for (int i = 0; i < pip_count + 1; i++) {
        free(pip_command[i]);
    }
    free(pip_command);
    free(end);

    return to_tokenize;
}
