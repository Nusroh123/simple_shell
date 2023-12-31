#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;
int shell(void);
void nonIShell(int argc, char *argv[] __attribute__((unused)));
void processIS(char *line);
int _strlen(char *s);
char *getPathLocation(char *buffer);
void executePath(char *buffer, char *tok[], char **env);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *getPath(char *buffer, char *pathCopy);
char *createFilePath(char *directory, char *command);
#endif
