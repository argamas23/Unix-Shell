#include "headers.h"

pid_t fg_pid = -1;
void handle_sigint(int sig) {
    printf("\n");
    if (fg_pid > 0) {
        kill(fg_pid, SIGINT);
    }
}

void handle_eof(int sig) {
    
    printf("\n");
    exit(0); // Exit the shell
}

void handle_sigtstp(int sig) {
    printf("\n");
    if (fg_pid > 0) {
        kill(fg_pid, SIGTSTP);
        fg_pid  = -1;
        // Update process state to "Stopped"
    }
}