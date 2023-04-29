#include "shell.h"

/**
 * paths - handles paths
 * Return: 0
 */

int paths(void)
{
	char *args[2], *input, *path, *path_copy, *dir, *cmd_path;
	pid_t pid;
	size_t size = 0;
	int status;

	while (1)
	{
		printf("$ ");
		if (getline(&input, &size, stdin) == -1)
		{
			printf("\n");
			exit(EXIT_SUCCESS); }
		input[strcspn(input, "\n")] = 0;
		if (strcmp(input, "exit") == 0)
			exit(EXIT_SUCCESS);
		if (access(input, F_OK) != -1)
		{
			args[0] = input;
			args[1] = NULL;
		} else
		{
			path = getenv("PATH");
			path_copy = strdup(path);
			dir = strtok(path_copy, ":");
			while (dir)
			{
				cmd_path = malloc(strlen(dir) + strlen(input) + 2);
				sprintf(cmd_path, "%s/%s", dir, input);
				if (access(cmd_path, F_OK) != -1)
				{
					args[0] = cmd_path;
					args[1] = NULL;
					break; }
				free(cmd_path);
				dir = strtok(NULL, ":"); }
			free(path_copy);
			if (!args[0])
			{
				printf("%s: command not found\n", input);
				continue; }
		} pid = fork();
		if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE); }
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("Error");
				exit(EXIT_FAILURE); }
		} else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status)); }
	} return (0);
}
