#include "shell.h"

/**
 * _main - Main entry
 *
 * Return: 0
 */

int _main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int n;
	pid_t pid;
	char *args[] = {NULL};
	char *env[] = {NULL};

	while (1)
	{
		printf("$ ");
		n = getline(&buffer, &bufsize, stdin);
		if (n == -1)
			break;
		buffer[n - 1] = '\0';

		pid = fork();

		if (pid == -1)
		{
			perror("fork error");
		}
		else if (pid == 0)
		{
			if (execve(buffer, args, env) == -1)
			{
				perror("execve error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(buffer);
	buffer = NULL;

	return (0);
}
