#include "shell.h"

/**
 * _arguments - Can handle arguments
 *
 * Return: 0
 */

int _arguments(void)
{
	char *args[1024], *command, *buffer;
	size_t bufsize = 32;
	ssize_t characters;
	pid_t pid;
	int status, i = 0;

	buffer = malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
		{
			perror("getline failed");
			exit(EXIT_FAILURE);
		}
		if (buffer[characters - 1] == '\n')
			buffer[characters - 1] = '\0';
		command = strtok(buffer, " ");
		while (command != NULL && i < 1023)
		{
			args[i] = command;
			command = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror(args[0]);
			exit(EXIT_FAILURE);
		} else
		{
			waitpid(pid, &status, 0);
			free(buffer);
			bufsize = 32;
			buffer = malloc(bufsize * sizeof(char));
			if (buffer == NULL)
			{
				perror("Unable to allocate buffer");
				exit(EXIT_FAILURE);
			}
		}
	} return (0);
}
