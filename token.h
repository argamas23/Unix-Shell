#ifndef TOKEN_H
#define TOKEN_H
#include "headers.h"
#include "log.h"
void restore_output(int a_r, int o_r, int original_output);
char *tokenize(char* username, char* hostname, char* home_dir, char* command, char* prev_dir, logque* log);
#endif