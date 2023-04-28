#include "shell.h"

/**
 * arguments - Can handle arguments
 *
 * Return: 0
 */

int arguments(void)
{
	char *args[10], *command, *buffer;
	size_t characters, bufsize = 32;
	pid_t pid;
	int status, i = 0;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		printf("$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (buffer[characters - 1] == '\n')
			buffer[characters - 1] = '\0';

		command = strtok(buffer, " ");
		i = 0;

		while (command != NULL)
		{
			args[i] = command;
			command = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("Execve failed");
			exit(1);
		} else if (pid < 0)
			perror("Fork failed");
		else
			waitpid(pid, &status, 0);
	} free(buffer);
	return (0);
}
