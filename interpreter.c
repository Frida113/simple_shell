#include "shell.h"

/**
 * interpreter - Interpretes the command
 * Return: 0
 */

int interpreter(void)
{
	char *args[2], *input;
	pid_t pid;
	size_t size = 0;

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
			args[0] = input;
			args[1] = NULL;

			if (execve(args[0], args, environ) == -1)
			{
				printf("%s: not found\n", args[0]);
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
	}
	return (0);
}
