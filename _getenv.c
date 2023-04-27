#include "shell.h"

/**
 * main - simple shell
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL, *path = NULL, *cmd = NULL;
	size_t bufsize = 0;
	ssize_t n_read = 0;
	pid_t pid;
	char *argv[2] = {NULL, NULL};

	while (1)
	{
		printf("$ "); /* display prompt */
		n_read = getline(&buffer, &bufsize, stdin);
		if (n_read == EOF) /* handle end of file */
			break;
		buffer[n_read - 1] = '\0'; /* remove newline */
		path = _getenv("PATH");
		cmd = path_concat(path, buffer); /* add path to command */
		if (access(cmd, X_OK) == 0) /* check if command exists */
		{
			pid = fork();
			if (pid == -1) /* handle fork error */
				perror("Error");
			else if (pid == 0) /* child process */
			{
				argv[0] = cmd;
				execve(cmd, argv, environ);
			}
			else /* parent process */
				wait(NULL);
		}
		else /* command not found */
			printf("%s: command not found\n", buffer);
		free(path);
		free(cmd);
	}
	free(buffer);
	return (0);
}

