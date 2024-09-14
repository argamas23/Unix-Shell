#ifndef _Header_H
#define _Header_H

#define SIZE 4097
#define LOGSIZE 15
#define PORT 80
#define MAX_PIPES 10
#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#define PINK "\033[1;35m"
#define RED "\033[1;31m"
typedef struct Alias {
    char* alias;
    char* command;
} Alias;

extern Alias* aliases;
extern int alias_count;
extern int dir_count;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include "display.h"
#include "token.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"
#include "syscommands.h"
#include "seek.h"
#include "proclore.h"
#include "activities.h"
#include "ping.h"
#include "shortcuts.h"
#include "fgbg.h"
#include "iMan.h"
#include "piping.h"
#include "neonate.h"
#include "myshrc.h"

#endif