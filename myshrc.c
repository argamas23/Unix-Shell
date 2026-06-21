#include "headers.h"

Alias* aliases = NULL;
int alias_count = 0;

void load_myshrc() {
    FILE *file = fopen(".myshrc", "r");
    if (!file) {
        perror(RED"Could not open .myshrc"RESET);
        return;
    }

    aliases = (Alias*) malloc(100 * sizeof(Alias));
    if (!aliases) {
        perror("Memory allocation failed for aliases");
        fclose(file);
        return;
    }

    char line[SIZE];
    while (fgets(line, sizeof(line), file)) {
        
        if (line[0] == '#' || line[0] == '\n') continue;

        char* alias_name = strtok(line, "=");
        char* command = strtok(NULL, "\n");

        if (alias_name && command) {
            
            while (isspace(*alias_name)) alias_name++;
            char* end = alias_name + strlen(alias_name) - 1;
            while (end > alias_name && isspace(*end)) end--;
            *(end + 1) = '\0';

            while (isspace(*command)) command++;
            end = command + strlen(command) - 1;
            while (end > command && isspace(*end)) end--;
            *(end + 1) = '\0';

            aliases[alias_count].alias = strdup(alias_name);
            aliases[alias_count].command = strdup(command);

            if (aliases[alias_count].alias && aliases[alias_count].command) {
                alias_count++;
            }

            if (alias_count >= 100) {
                printf("Warning: Maximum number of aliases reached.\n");
                break;
            }
        }
    }
    // for(int i = 0; i<alias_count;i++)
    // {
    //     printf("%s //// %s\n",aliases[i].alias, aliases[i].command);
    // }
    fclose(file);
}

char* find_alias(char *input) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(input, aliases[i].alias) == 0) {
            return aliases[i].command;
        }
    }
    return NULL;
}