#include "headers.h"

void seek(char **command_list, int count, char *home_dir, char *prev_dir)
{
    int only_dirs = 0, only_files = 0, execute_flag = 0;
    int flag_count = 0;
    char *targetword = NULL;
    char *path = "."; // Default to the current directory
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%s ", command_list[i]);
    // }
    // printf("\n");
    // Parse flags and arguments
    for (int i = 0; i < count; i++)
    {
        if (command_list[i][0] == '-')
        {
            for (int j = 1; command_list[i][j] != '\0'; j++)
            {
                if (command_list[i][j] == 'd')
                {
                    only_dirs = 1;
                    flag_count++;
                }
                if (command_list[i][j] == 'f')
                {
                    only_files = 1;
                    flag_count++;
                }
                if (command_list[i][j] == 'e')
                {
                    execute_flag = 1;
                    flag_count++;
                }
            }
        }
    }
    int target_Cap=0;
    for(int i=0;i<count;i++)
    {
        if(strcmp(command_list[i],"seek")==0)
        {
            continue;
        }
        else if(command_list[i][0]=='-')
        {
            continue;
        }
        else if(target_Cap==0)
        {
            targetword=command_list[i];
            target_Cap=1;
        }
        else
        {
            path=command_list[i];
        }
    }
    // printf("target: %s path : %s flag_c:%d\n", targetword, path, flag_count);
    // Check for invalid flag combination
    if (only_dirs && only_files)
    {
        printf(RED"Invalid flags!\n"RESET);
        return;
    }

    // Handle special paths (., .., ~, -)
    if (strcmp(path, "~") == 0)
    {
        path = home_dir;
    }
    else if (strcmp(path, "-") == 0)
    {
        path = prev_dir;
    }

    int match_count = 0;
    char *e_ans = (char *)calloc(SIZE, sizeof(char));

    // Initiate the search
    search_directory(path, path, targetword, only_dirs, only_files, execute_flag, &match_count, e_ans);

    // Handle execution flag after search
    if (execute_flag == 1 && match_count == 1)
    {
        struct stat fd;
        if (stat(e_ans, &fd) == -1)
        {
            printf(RED"Error: Cannot stat file/directory\n"RESET);
            free(e_ans);
            return;
        }
        if (S_ISDIR(fd.st_mode))
        {
            if (access(e_ans, X_OK) == -1)
            {
                printf(RED"Missing permissions for task!\n"RESET);
            }
            else
            {
                chdir(e_ans);
            }
        }
        else
        {
            if (access(e_ans, R_OK) == -1)
            {
                printf(RED"Missing permissions for task!\n"RESET);
            }
            else
            {
                FILE *file_ptr = fopen(e_ans, "r");
                if (file_ptr == NULL)
                {
                    printf(RED"Error Opening File\n"RESET);
                    free(e_ans);
                    return;
                }
                char c;
                while ((c = getc(file_ptr)) != EOF)
                {
                    printf("%c", c);
                }
                printf("\n");
                fclose(file_ptr);
            }
        }
    }

    free(e_ans);
}

void search_directory(char *path, char *target, char *targetword, int only_dirs, int only_files, int execute_flag, int *match_count, char *e_ans)
{
    struct dirent **entry;
    int scan = scandir(path, &entry, NULL, alphasort);
    if (scan == -1)
    {
        perror(RED"scandir"RESET);
        return;
    }

    for (int i = 0; i < scan; i++)
    {   
        
        if (strcmp(entry[i]->d_name, "..") == 0 || strcmp(entry[i]->d_name, ".") == 0)
            continue;

        struct stat info;
        char *full_path = (char *)malloc(SIZE * sizeof(char));
        snprintf(full_path, SIZE, "%s/%s", path, entry[i]->d_name);
        if (stat(full_path, &info) == -1)
        {
            perror(RED"stat"RESET);
            free(entry[i]);
            free(full_path);
            continue;
        }

        int rm_dot = check(entry[i]->d_name, targetword);
        // printf("here %s %s\n",entry[i]->d_name,targetword);
        if (strcmp(entry[i]->d_name, targetword) == 0 || rm_dot == 0)
        {
            if (only_dirs && S_ISDIR(info.st_mode))
            {
                *match_count += 1;
                strcpy(e_ans, full_path);
                printf(BLUE);
                printrelativepath(path, full_path);
                printf(RESET);
            }
            if (only_files && !S_ISDIR(info.st_mode))
            {
                *match_count += 1;
                strcpy(e_ans, full_path);
                printf(GREEN);
                printrelativepath(path, full_path);
                printf(RESET);
            }
            if (!only_files && !only_dirs)
            {
                *match_count += 1;
                strcpy(e_ans, full_path);
                if (S_ISDIR(info.st_mode))
                {
                    printf(BLUE);
                }
                else
                {
                    printf(GREEN);
                }
                printrelativepath(path, full_path);
                printf(RESET);
            }
        }

        if (S_ISDIR(info.st_mode))
        {
            search_directory(full_path, target, targetword, only_dirs, only_files, execute_flag, match_count, e_ans);
        }

        free(entry[i]);
        free(full_path);
    }

    free(entry);
}

void printrelativepath(char *path, char *ans)
{
    printf(".");
    for (int i = strlen(path); i < strlen(ans); i++)
    {
        printf("%c", ans[i]);
    }
    printf("\n");
}

int check(char *input, char *targetword)
{
    char *temp = strdup(input);
    for (int i = 0; i < strlen(temp); i++)
    {
        if (temp[i] == '.')
        {
            temp[i] = '\0';
            break;
        }
    }
    int comp = strcmp(temp, targetword);
    free(temp);
    return comp;
}
