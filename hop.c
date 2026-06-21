#include "headers.h"
int dir_count = 0;
void hop(char **command_list, int count, char *home_dir, char *prev_dir)
{
    char *cwd = (char*)malloc(SIZE*sizeof(char));
    char* current_dir = (char*)malloc(SIZE*sizeof(char));
    
    if (count == 1) {
        chdir(home_dir);
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }

    if (strcmp(command_list[1], "-") == 0)
    {
        if (dir_count == 0)
            printf("OLPWD not set\n");
        else
        {
            getcwd(cwd,SIZE);
            chdir(prev_dir);
            strcpy(prev_dir,cwd);
            getcwd(current_dir,SIZE);
            printf("%s\n", current_dir);
        }
    }
    else{
        if (strcmp(command_list[1], "~") == 0)
        {
            chdir(home_dir);
            getcwd(current_dir,SIZE);
            printf("%s\n", current_dir);
            dir_count ++;
        }
        else if(strcmp(command_list[1], "..") == 0)
        {
            chdir("..");
            getcwd(current_dir,SIZE);
            printf("%s\n",current_dir);
            dir_count++;
            if (command_list[2] != NULL && strcmp(command_list[2], "\0") != 0)
            {
                if (chdir(command_list[2]) != 0) {
                printf(RED); 
                perror(RED"hop"RESET);
                printf(RESET);
                return;
                }
            getcwd(current_dir,SIZE);
            printf("%s\n",current_dir);
            dir_count++;
            
            }
        }
        else if(strncmp(command_list[1], "~/", 2) == 0)
        {
            getcwd(prev_dir,SIZE);
            chdir(home_dir);
            printf("%s\n",home_dir);
            if (chdir(command_list[2]) != 0) {
                printf(RED);
                perror(RED"hop"RESET);
                printf(RESET);
                return;
            }
            getcwd(current_dir,SIZE);
            printf("%s\n",current_dir);
            dir_count++;
        
            
        }
        else
        {
            getcwd(prev_dir,SIZE);
            if (chdir(command_list[1]) != 0) {
                printf(RED);
                perror(RED"hop"RESET);
                printf(RESET);
                return;
                }
            getcwd(current_dir,SIZE);
            printf("%s\n",current_dir);
            dir_count++;
        }
    
    }
}

