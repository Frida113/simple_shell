#include "shell.h"
/**
 * _interpreter - interpretes a unix command
 * Return: 0
 */

int _interpreter(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int pid = fork();

	while (1)
	{
		printf("$ ");
		getline(&buffer, &bufsize, stdin);
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (pid < 0)
			perror("fork() error");
		else if (pid == 0)
		{
			buffer[strcspn(buffer, "\n")] = 0;
			if (execlp(buffer, buffer, (char *) NULL) == -1)
			{
				printf("Command not found: %s\n", buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
	return (EXIT_SUCCESS);
}
