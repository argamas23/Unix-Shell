#include "headers.h"


void iMan(char **command_list)
{
    char command[200];
    strcpy(command, command_list[1]);
    char *host = "man.he.net";


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf(RED"Socket error\n"RESET);
        return;
    }

    struct hostent *server = gethostbyname(host);
    if (server == NULL)
    {
        printf(RED"Host error\n"RESET);
        close(sock);
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf(RED"Connection error\n"RESET);
        close(sock);
        return;
    }

    char request[1000];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\n\r\n", command, host);

    if (send(sock, request, strlen(request), 0) < 0)
    {
        printf(RED"Request sending error\n"RESET);
        close(sock);
        return;
    }

    char response[1024];  
    ssize_t bytes_received;

   
    char *full_response = (char *)malloc(1);
    full_response[0] = '\0';
    size_t total_length = 0;

    
    while ((bytes_received = recv(sock, response, sizeof(response) - 1, 0)) > 0)
    {
        response[bytes_received] = '\0';

        
        total_length += bytes_received;
        full_response = (char *)realloc(full_response, total_length + 1);
        strcat(full_response, response); 
    }

    
    char *invalid_command_indicator = strstr(full_response, "No matches for");
    if (invalid_command_indicator != NULL)
    {
        
        printf(RED"ERROR: No matches for \"%s\" command\n"RESET, command);
    }
    else
    {
        
        char *name_section = strstr(full_response, "NAME\n");
        if (name_section != NULL)
        {
            char *end_section = strstr(name_section, "All Rights Reserved.");
            if (end_section != NULL)
            {
                *end_section = '\0';  
            }
            printf("%s", name_section);
        }
        else
        {
            printf(RED"ERROR\n\tNo such command\n"RESET);
        }
    }

    free(full_response); 
    close(sock);
}
