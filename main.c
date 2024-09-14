

#include "headers.h"


int main() {
    int i = 1;
    load_myshrc();
    int log_count = 0;
    logque* log = init();
    char* username = (char*)malloc(SIZE*sizeof(char));
    char* hostname = (char*)malloc(SIZE*sizeof(char));
    char* home_dir = (char*)malloc(SIZE*sizeof(char));
    char* current_dir = (char*)malloc(SIZE*sizeof(char));
    char* return_val = (char*)malloc(SIZE*sizeof(char));
    char* prev_dir = (char*)malloc(SIZE*sizeof(char));

    getcwd(prev_dir, SIZE);

    get_home_directory(home_dir, SIZE);

    if (getlogin_r(username, SIZE) != 0) {
        perror("getlogin_r");
        exit(1);
    }

    if (gethostname(hostname, SIZE) != 0) {
        perror("gethostname");
        exit(1);
    }

    struct sigaction sa_int, sa_eof, sa_tstp;
    
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_eof.sa_handler = handle_eof;
    sigemptyset(&sa_eof.sa_mask);
    sa_eof.sa_flags = 0;
    sigaction(SIGQUIT, &sa_eof, NULL); // Using SIGQUIT for Ctrl-D in this case

    sa_tstp.sa_handler = handle_sigtstp;
    sigemptyset(&sa_tstp.sa_mask);
    sa_tstp.sa_flags = 0;
    sigaction(SIGTSTP, &sa_tstp, NULL);

    for(i=1;i>0;i++) {

        log_count = counter(log);

        // Get current directory for prompt
        get_current_directory(current_dir, SIZE);

        // Display the prompt
        display_prompt(username, hostname, home_dir, current_dir);

        // Wait for user input
        char command[SIZE];

        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle input error
            if (feof(stdin)) {
                printf("\n");
                exit(0);
            }
            continue;
        }

        // Remove the newline character from the command, if present
        command[strcspn(command, "\n")] = 0;

    
        

        if (strstr(command, "log") == NULL) {
            if (log_count == LOGSIZE) {
                dequeue(log);
                enque(log, command);
            } else {
                if (log_count == 0) {
                    enque(log, command);
                } else if (strcmp(log->rear->command, command) != 0) {
                    enque(log, command);
                }
    }
}


        int semi_colon=0;
        for(int j=0;j<strlen(command);j++)
        {
            if(command[j]==';')
            {
                semi_colon++;
            }
        }
        char **inputrequire=(char ** )calloc(semi_colon+1,sizeof(char *));
        char *semicolonstr=";";
        char *token_semi=strtok(command,semicolonstr);
        int i_input=0;
        for(int j=0;j<semi_colon+1;j++)
        {
            inputrequire[j]=(char *)calloc(SIZE,sizeof(char));
        }
        while(token_semi!=NULL)
        {   
            // printf("%s\n",token_semi);
            inputrequire[i_input++]=token_semi;
            token_semi=strtok(NULL,semicolonstr);
        }
        for(int j=0;j<semi_colon+1;j++)
        { 
            // printf("here inputre %s\n",inputrequire[j]);
        return_val = tokenize(username,hostname,home_dir,inputrequire[j],prev_dir,log);

        }
            
    }

    return 0;
}

