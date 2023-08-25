#include "main.h"

void executePath(char *buffer, char *argvTok[], char **env);
void signalHandler(int sig);
void executeEnv(char **env);
/**
 * main - entry point
 * @ac: argument count
 * @tok: argument variable
 * @env: environment variable
 * Return: 0 on success
 */
int main(int ac __attribute__((unused)), char *tok[], char **env)
{
	char *buffer = NULL, *argvTok[128], *token = NULL, *command = "bin/ls";
	size_t charNum;
	int i = 0, lsCount = 0;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signalHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	(void)tok;
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)/**check if it is interactive i.e not piped**/
			write(STDOUT_FILENO, "$ ", 3);/**Prompt*/
		if (getline(&buffer, &charNum, stdin) == -1)/**Handles EOF, no more input**/
		{
			free(buffer);
			buffer = NULL;
			exit(0);
		}
		if (_strlen(buffer) > 0 && buffer[_strlen(buffer) - 1] == '\n')
			buffer[_strlen(buffer) - 1] = '\0';

		token = strtok(buffer, " \n\t\r");/**Tokenize input**/
		i = 0;
		if (token == NULL)
			continue;

		while (token)/**i.e tok[i] != '\0'**/
		{
			argvTok[i] = token;
			i++;
			token = strtok(NULL, " \n\t\r");
		}
		argvTok[i] = NULL;
		if (_strcmp(argvTok[0], "exit") == 0)
		{
			free(buffer);
			buffer = NULL;
			exit(0);
		}
		if (_strcmp(argvTok[0], "env") == 0)
		{
			executeEnv(env);
			continue;
		}

		if (i > 0)
		{
			executePath(buffer, argvTok, env);
			if (_strcmp(argvTok[0], command) == 0)
				lsCount++;
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
	exit(2);
	return (0);
}

/**
 * executePath - execute Path
 * @buffer: command inputted
 * @argvTok: argument vector
 * @env: environment variable
 * Return: nothing
 */
void executePath(char *buffer, char *argvTok[], char **env)
{
	char *pathBuffer;
	pid_t childPid;
	int status;

	pathBuffer = NULL;

	pathBuffer = getPathLocation(buffer);
	if (access(pathBuffer, X_OK) == 0)
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
			if (execve(pathBuffer, argvTok, env) == -1)
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
	else
	{
		free(pathBuffer);
		pathBuffer = NULL;
		return;
	}
}
/**
 * signalHandler - handler signal during exit
 * @sig: sigal number
 * Return: Nothing
 */
void signalHandler(int sig)
{
	if (sig == SIGINT || sig == SIGTERM)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * executeEnv - execute environment variable
 * @env: environment variable
 * Return: nothing
 */
void executeEnv(char **env)
{
	int i = 0, j;

	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
