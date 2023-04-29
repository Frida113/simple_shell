#include "shell.h"

#define ARGS_MAX 100

/**
 * interpreter - Interpretes the command
 * Return: 0
 */

int interpreter(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int n, i;
	pid_t pid;
	char *args[ARGS_MAX];
	char *token;

	while (1)
	{
		printf("$ ");
		n = getline(&buffer, &bufsize, stdin);
		if (n == -1)
			break;
		buffer[n - 1] = '\0';
		i = 0;
		token = strtok(buffer, " ");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve error");
				exit(EXIT_FAILURE);
			}
		} else
			wait(NULL);
	} free(buffer);
	buffer = NULL;
	return (0);
}
