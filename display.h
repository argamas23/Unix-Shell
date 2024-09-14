#ifndef DISPLAY_H
#define DISPLAY_H

void get_home_directory(char *home_dir, size_t size);
void get_current_directory(char *current_dir, size_t size);
void display_prompt(const char *username, const char *hostname, const char *home_dir, const char *current_dir);

#endif
