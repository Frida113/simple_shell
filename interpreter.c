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
	int status;

	while (1)
	{
		printf("$ ");
		if (getline(&input, &size, stdin) == -1)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		input[strcspn(input, "\n")] = 0;
		if (strcmp(input, "exit") == 0)
			exit(EXIT_SUCCESS);
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
		} else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	} return (0);
}
