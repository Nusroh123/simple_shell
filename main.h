#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;
int betty(void);
int shell(void);
void nonIShell(int argc, char *argv[] __attribute__((unused)));
void processIS(char *line);
int _strlen(char *s);
char *_strcpy(char *dest, const char *src);
char *getPathLocation(char *buffer);

#endif
