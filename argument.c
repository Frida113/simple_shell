#include "shell.h"

/**
 * arguments - handles arguments
 * Return: 0
 */

int arguments(void)
{
	char *args[10], *input;
	pid_t pid;
	size_t size = 0;
	int i;

	while (1)
	{
		printf("$ ");
		if (getline(&input, &size, stdin) == -1)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		input[strcspn(input, "\n")] = 0;

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			i = 0;
			args[i] = strtok(input, " ");
			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, " ");
			}
			args[i] = NULL;

			if (execve(args[0], args, environ) == -1)
			{
				printf("%s: not found\n", args[0]);
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
	} return (0);
}
