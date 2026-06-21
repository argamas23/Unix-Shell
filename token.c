#include "headers.h"
#include"myshrc.h"

void restore(int a_r, int o_r, int original_output);


char * tokenize(char* username, char* hostname, char* home_dir, char* command, char* prev_dir,logque* log)
{
    char* original_command = strdup(command);
    char *delimit = " \t\n\0";
    char *token = strtok(command, delimit);
    char **command_list = (char**)calloc(6,sizeof(char*));
    char *end = (char*)malloc(6*sizeof(char));
    strcpy(end, "\0");
    int i,count = 0;
    int input_redirect = 0, output_redirect = 0, append_redirect = 0;
    char *input_file = NULL, *output_file = NULL;
    int original_stdout = dup(STDOUT_FILENO);
    int original_stdin = dup(STDIN_FILENO);
    int redirect_flags;
    static int time_flag = 0;
    for(i=0;i<6;i++)
    {
        command_list[i] = (char*)calloc(SIZE,sizeof(char));
    }
    while (token != NULL)
    {
        command_list[count++] = token;
        token = strtok(NULL, delimit);
    }
    // printf("%s\n",command_to_use);
    // for(i=0; i<count;i++)
    // {
    //     printf("%s\n", command_list[i]);
    // }
    for(i = 0; i < alias_count; i++)
    {
        if(strcmp(command_list[0], aliases[i].alias) == 0)
        {
            char* alias_command = find_alias(command_list[0]);
                strcpy(command_list[0], alias_command);
            }
            char* new_command = (char*)malloc(SIZE * sizeof(char));
            if (new_command == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return end;
            }
            new_command[0] = '\0';
            for(int j=0;j<count;j++)
            {
                strcat(new_command, command_list[j]);
                strcat(new_command, " ");
            }
            // printf("%s", new_command);
            char* again = tokenize(username,hostname,home_dir,new_command,prev_dir, log);
            return end;
        }


    }
    for(i=0;i<count;i++)
    {
        if(strcmp(command_list[i], "|") == 0)
        {
            if(strcmp(command_list[count - 1], "|") == 0 || (strcmp(command_list[0],"|") == 0))
            {
                printf(RED"INVALID USE OF PIPES"RESET);
                return end;
            }
            time_flag = 1;
            // printf("Here1 %s\n",command_to_use);
            char* a = piping(username, hostname, home_dir, original_command, prev_dir, log);
            restore(append_redirect, output_redirect, original_stdout);
            return end;
        }
        if(strcmp(command_list[i], ">") == 0)
        {
            time_flag = 1;
            output_redirect = 1;
            redirect_flags = O_WRONLY | O_CREAT | O_TRUNC;
            output_file = command_list[i + 1];
            command_list[i] = NULL; 
            command_list[i+1] = NULL;
            count = count - 2;
        }
        else if(strcmp(command_list[i], ">>") == 0)
        {
            time_flag = 1;
            append_redirect = 1;
            redirect_flags = O_WRONLY | O_CREAT | O_APPEND;
            output_file = command_list[i + 1];
            command_list[i] = NULL; 
            command_list[i+1] = NULL;
            count = count - 2;
        }
        else if(strcmp(command_list[i], "<") == 0)
        {
            time_flag = 1;
            input_redirect = 1;
            const char* custom[] = {"log", "hop", "reveal", "proclore", "seek", "iMan", "ping", "activities", "fg", "bg"};
            int is_custom = 0;
            for(int j = 0; j< sizeof(custom)/ sizeof(custom[0]); j++)
            {
                if(strcmp(command_list[0], custom[j]) == 0)
                {
                    is_custom = 1;
                    break;
                }
            }
            if(is_custom)
            {
                FILE *input_file_opener = fopen(command_list[i + 1], "r");
                if (input_file_opener == NULL)
                {
                    perror(RED"Error Opening file"RESET);
                    return end;
                }

                // Read the entire file content
                fseek(input_file_opener, 0, SEEK_END);
                long in_size = ftell(input_file_opener);
                rewind(input_file_opener);
                
                char *buffer = (char *)malloc(in_size + 1);
                if (buffer == NULL)
                {
                    perror(RED"Memory allocation failed"RESET);
                    fclose(input_file_opener);
                    return end;
                }

                fread(buffer, 1, in_size, input_file_opener);
                buffer[in_size] = '\0';
                fclose(input_file_opener);

                // Tokenize the file content
                char *inp_tok;
                char **inp_redir_list = (char **)malloc(sizeof(char *) * 50);  
                int inp_redir_Count = 0;
                int inp_redir_flag=0;
                inp_tok = strtok(buffer, delimit);
                while (inp_tok != NULL)
                {
                    inp_redir_list[inp_redir_Count++] = strdup(inp_tok);  // Duplicate token string
                    inp_tok = strtok(NULL, delimit);
                }

                
                free(command_list[i]);
                free(command_list[i + 1]);

                // Shift existing tokens in `command_list` to make space for the new tokens
                for (int j = i + 2; j < count; j++)
                {
                    command_list[j - 2 + inp_redir_Count] = command_list[j];
                }
                inp_redir_flag=1;
                // Insert the new tokens in place of `<` and the file name
                for (int j = 0; j < inp_redir_Count; j++)
                {
                    command_list[i + j] = inp_redir_list[j];
                }

                
                count += inp_redir_Count - 2;

               
                free(inp_redir_list);
                free(buffer);
            }
        }
        // if(strcmp(command_list[i],"<") == 0 || strcmp(command_list[i],">") == 0 || strcmp(command_list[i], ">>") == 0)
        // {
            
        //     io_redirect(command_list, count);
        //     return end;
        // }
        // if(strcmp(command_list[i],"|") == 0)
        // {
        //     piping(command_list, command, count);
        //     return end;
        // }
    }
    int out_fd;
    if(output_redirect == 1 || append_redirect == 1)
    {
        out_fd = open(output_file, redirect_flags, 0644);
        if(out_fd == -1)
        {
            printf(RED"ERROR : Unable to open file descriptor for Output Redirection"RESET);
            return end;
        }
        if(dup2(out_fd, STDOUT_FILENO) == -1)
        {
            printf(RED"ERROR : Unable to change Output Stream"RESET);
            return end;
        }
        close(out_fd);
    }

    if(strcmp(command_list[0],"hop") == 0)
    {
        hop(command_list, count, home_dir, prev_dir);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if(strcmp(command_list[0], "reveal") == 0)
    {
        // if(strcmp(command_list[1], "-l") == 0 || strcmp(command_list[1], "-a") == 0 || strcmp(command_list[1], "-al") == 0 || strcmp(command_list[1], "-la") == 0)
        //     reveal_flag_count++;
        reveal(command_list, count,home_dir,prev_dir);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if(strcmp(command_list[0], "seek") == 0)
    {
        seek(command_list, count, home_dir, prev_dir);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if (strcmp(command_list[0], "proclore") == 0)
    {
        proclore(command_list, count);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if (strcmp(command_list[0], "activities") == 0)
    {
        activities();
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if(strcmp(command_list[0], "fg") == 0)
    {
        fg(command_list,count);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if(strcmp(command_list[0], "bg") == 0)
    {
        bg(command_list);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }

    if (strcmp(command_list[0], "ping") == 0)
    {
        ping(command_list);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if (strcmp(command_list[0], "iMan") == 0)
    {
        iMan(command_list);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if (strcmp(command_list[0], "neonate") == 0)
    {
        neonate(command_list);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    if (strcmp(command_list[0], "log") == 0)
    {
        if(strcmp(command_list[1], "purge") == 0)
        {
            purge(log);
        }
        else if(strcmp(command_list[1], "execute") == 0)
        {
            int idx = counter(log) - atoi(command_list[2]);
            if(idx >= 0 && idx <= counter(log))
            {
                lognode* temp = log->front;
                for(int j = 0; j < idx;j++)
                {
                    temp = temp -> next;
                }
                strcpy(command, temp->command);
                char* call = tokenize(username,hostname,home_dir,command,prev_dir,log);
            }
        }
        else
            display_log(log);
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    else
    {
        struct sigaction sa;
        sa.sa_handler = &check_status;
        sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
        sigaction(SIGCHLD, &sa, NULL);
        int background = 0;
        background = (strcmp(command_list[count-1],"&") == 0);
        if(background)
        {
            // free(command_list[count-1]);
            command_list[count -1] = NULL;
        }
        
        syscommands(command_list,background,count,time_flag);
        check_status();
        restore(append_redirect, output_redirect, original_stdout);
        return end;
    }
    restore(append_redirect, output_redirect, original_stdout);
    if (input_redirect == 1)
    {
        if (dup2(original_stdin, STDIN_FILENO) == -1)
        {
            perror("error redirecting back to terminal");
        }
    }
    return end;
    
}

void restore(int a_r, int o_r, int original_output)
{
    if (a_r || o_r)
    {
        if (dup2(original_output, STDOUT_FILENO) != -1)
            return; 
        fprintf(stderr, RED"ERROR: Unable to restore output back to terminal\n"RESET);
    }
}