
#include "headers.h"


void get_home_directory(char *home_dir, size_t size) {
    if (getcwd(home_dir, size) == NULL) {
        perror(RED"getcwd"RESET);
        exit(1);
    }
}

void get_current_directory(char *current_dir, size_t size) {
    if (getcwd(current_dir, size) == NULL) {
        perror(RED"getcwd"RESET);
        exit(1);
    }
}

void display_prompt(const char *username, const char *hostname, const char *home_dir, const char *current_dir) {
    char *relative_path = strstr(current_dir, home_dir);
    if (relative_path && relative_path == current_dir) {
        // Inside or at home directory
        printf(PINK "<%s@%s:~%s>" RESET " ", username, hostname, current_dir + strlen(home_dir));
    } else {
        // Outside home directory
        printf(PINK "<%s@%s:%s>" RESET " ", username, hostname, current_dir);
    }
}
