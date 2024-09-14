#ifndef SEEK_H
#define SEEK_H
void seek(char ** command_list, int count, char* home_dir, char* prev_dir);
void search_directory(char *path, char *target, char *targetword, int only_dirs, int only_files, int execute_flag, int *match_count, char *e_ans);
void printrelativepath(char* path, char* ans);
int check(char* input, char* targetword);
#endif