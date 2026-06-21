#include "headers.h"

void reveal(char **command_list, int count, char *home_dir, char *prev_dir) {
    int show_hidden = 0, show_long = 0;
    char *path = ".";

   
    for (int i = 0; i < count; i++) {
        if (command_list[i][0] == '-') {
            if(command_list[i][1] == '\0')
            {
                path = prev_dir;
            }
            for (int j = 1; command_list[i][j] != '\0'; j++) {
                if (command_list[i][j] == 'a') show_hidden = 1;
                if (command_list[i][j] == 'l') show_long = 1;
            }
        } else {
            path = command_list[i];
        }
    }

    
    if (count == 0 || (count == 1  && strlen(command_list[0]) > 1)) {
        path = ".";
    }

    
    if (strcmp(path, "~") == 0) {
        path = home_dir;
    }
    // else if (strcmp(path, "-") == 0) {
    //     path = prev_dir;
    // }

    
    DIR *dir = opendir(path);
    if (!dir) {
        perror(RED"opendir"RESET);
        return;
    }

    struct dirent *entry;
    struct stat info;
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if -a is not provided
        if (!show_hidden && entry->d_name[0] == '.') continue;

        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &info) == -1) {
            perror(RED"stat"RESET);
            continue;
        }

        print_file_info(entry->d_name, &info, show_long);
    }

    closedir(dir);
}

void print_file_info(char *name, struct stat *info, int show_long) {
    // Determine file type and apply color coding
    if (S_ISDIR(info->st_mode)) {
        printf(BLUE "%s" RESET, name);
    } else if (info->st_mode & S_IXUSR) {
        printf(GREEN "%s" RESET, name);
    } else {
        printf(WHITE "%s" RESET, name);
    }

    if (show_long) {
        // Print detailed file information
        printf(" %lu", info->st_nlink);

        // Owner and group
        struct passwd *pw = getpwuid(info->st_uid);
        struct group *gr = getgrgid(info->st_gid);
        printf(" %s %s", pw->pw_name, gr->gr_name);

        // File size and modification time
        printf(" %5ld", info->st_size);
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&info->st_mtime));
        printf(" %s", timebuf);
    }

    printf("\n");
}