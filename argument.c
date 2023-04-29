#include "shell.h"

/**
 * arguments - handles arguments
 * Return: 0
 */

int arguments(void)
{
	char *args[1024], *input;
	pid_t pid;
	size_t size = 0;
	int i, status;

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
			exit(EXIT_FAILURE); }
		if (pid == 0)
		{
			i = 0;
			args[i] = strtok(input, " ");
			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, " "); }
			if (execve(args[0], args, environ) == -1)
			{
				printf("%s: not found\n", args[0]);
				exit(EXIT_FAILURE); }
		} else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status)); }
	} return (0);
}
