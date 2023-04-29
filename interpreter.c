#include "shell.h"

/**
 * interpreter - Interpretes the command
 * Return: 0
 */

int interpreter(void)
{
	char *args[MAX_ARGS], *input;
	size_t bufsize = 0;
	ssize_t getline_return;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		getline_return = getline(&input, &bufsize, stdin);
		if (getline_return == EOF)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (input[getline_return - 1] == '\n')
		{
			input[getline_return - 1] = '\0';
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			args[0] = input;
			args[1] = NULL;
			execve(args[0], args, environ);
			perror(input);
			exit(EXIT_FAILURE);
		} else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	} free(input);
	return (EXIT_SUCCESS);
}
