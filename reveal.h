#ifndef REVEAL_H
#define REVEAL_H
void reveal(char **command_list, int count, char *home_dir, char *prev_dir);
void print_file_info(char *name, struct stat *info, int show_long);
#endif