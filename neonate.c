#include "headers.h"

int get_recent_pid() {
    struct dirent* entry;
    DIR* proc_dir = opendir("/proc");
    int pid = 0;
    if (proc_dir == NULL) {
        perror(RED "opendir failed" RESET);
        return -1;
    }
    while ((entry = readdir(proc_dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            int p = atoi(entry->d_name);
            if (p > pid)
                pid = p;
        }
    }
    closedir(proc_dir);
    return pid;
}

void neonate(char** command_list) {
    int tim = atoi(command_list[2]);
    if (tim <= 0) {
        printf(RED "Invalid time interval\n" RESET);
        return;
    }

    setbuf(stdout, NULL);

    
    struct termios orig_termios, raw;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror(RED "tcgetattr" RESET);
        return;
    }
    raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror(RED "tcsetattr" RESET);
        return;
    }

    int pid = fork();
    if (pid == 0) {
        
        while (1) {
            int recent = get_recent_pid();
            if (recent > 0)
                printf("%d\n", recent);
            else
                printf(RED "FAILED TO FETCH RECENT PID\n" RESET);
            fflush(stdout);
            sleep(tim);
        }
    } else if (pid > 0) {
       
        char c = 0;
        while (read(STDIN_FILENO, &c, 1) == 1 && c != 'x') {
            
        }
        kill(pid, SIGKILL);

        
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
            perror(RED "tcsetattr" RESET);
        }
    } else {
        perror(RED "Fork failed" RESET);
    }
}