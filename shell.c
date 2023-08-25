#include "main.h"

void executePath(char *buffer, char *tok[], char **env);
/**
 * main - entry point
 * @ac: argument count
 * @tok: argument variable
 * @env: environment variable
 * Return: 0 on success
 */
int main(int ac __attribute__((unused)), char *tok[], char **env)
{
	char *buffer, *argvTok[64];
	size_t charNum;
	int i;

	i = 0;
	buffer = NULL;
	charNum = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)/**check if it is interactive i.e not piped**/
			write(STDOUT_FILENO, "> ", 3);/**Prompt**/
		if (getline(&buffer, &charNum, stdin) == -1)/**Handles EOF, no more input**/
		{
			free(buffer);
			buffer = NULL;
			exit(0);
		}
		if (_strlen(buffer) > 0 && buffer[_strlen(buffer) - 1] == '\n')
			buffer[_strlen(buffer) - 1] = '\0';

		tok[0] = strtok(buffer, " \n\t\r");/**Tokenize input**/
		i = 0;
		while (tok[i])/**i.e tok[i] != '\0'**/
		{
			argvTok[i] = tok[i];
			i++;
			tok[i] = strtok(NULL, " \n\t\r");
		}
		argvTok[i] = NULL;

		if (i > 0)
		{
			executePath(buffer, argvTok, env);
		}

		else
		{
			if (buffer)
			{
				free(buffer);
				buffer = NULL;
			}
		}
		fflush(stdout);/**Display the content of buffer b4 storing another one**/
		free(buffer);
		buffer = NULL;
	}
	return (0);
}


/**
 * executePath - execute Path
 * @buffer: command inputted
 * @tok: argument vector
 * @env: environment variable
 * Return: nothing
 */
void executePath(char *buffer, char *tok[], char **env)
{
	char *pathBuffer;
	pid_t childPid;
	int status;

	pathBuffer = NULL;

	pathBuffer = getPathLocation(buffer);
	if (pathBuffer)
	{
		childPid = fork();
		if (childPid < 0)
		{
			free(pathBuffer);
			pathBuffer = NULL;
			exit(EXIT_FAILURE);
		}
		else if (childPid == 0)
		{
			if (execve(pathBuffer, tok, env) == -1)
			{
				free(pathBuffer);
				pathBuffer = NULL;
				perror("execve failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			free(pathBuffer);
			pathBuffer = NULL;
		}
	}
}
