#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

/* Global variables */
extern char **environ;

/* Functions */
int _putchar(char c);
int _strlen(char *s);
void _puts(char *s);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_getenv(char *var);
char **split_string(char *str, const char *delim);
char **find_path_dirs(void);
char *find_exec(char **paths, char *cmd);
char *get_cmd(char **argv);
int check_cmd(char *cmd);
int execute(char **argv, char **envp);
void prompt(void);
char **parse_cmdline(char *line, char **argv);
void sig_handler(int sig);
int _strcmp(char *s1, char *s2);
void free_grid(char **grid);
void free_argv(char **argv);
int main(void);
int interpreter(void);
int arguments(void);

#endif
