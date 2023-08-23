#include "main.h"
int main(int ac, char *tok[], char **env)
{
	char *buffer, *pathBuffer;
	size_t charNum;
	int i, j, status;
	pid_t childPid;

	i = 0;
	j = 0;
	buffer = NULL;
	pathBuffer = NULL;
	charNum = 0;
	(void)ac;
	betty();
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)/**check if it is interactive i.e not piped**/
			write(STDOUT_FILENO, "> ", 3);/**Prompt**/

		if (getline(&buffer, &charNum, stdin) == -1)/**Handles EOF, no more input**/
			continue;
		while (buffer[j])/**Remove newline character**/
		{
			if (buffer[j] == '\n')
				buffer[j] = 0;
			j++;
		}

		tok[0] = strtok(buffer, " \n");/**Tokenize input**/
		i = 0;
		while (tok[i])/**i.e tok[i] != '\0'**/
		{
			i++;
			tok[i] = strtok(NULL, " \n");
		}

		if (i > 0)
		{
			tok[i] = NULL;

			pathBuffer = getPathLocation(buffer);
			if (pathBuffer)
			{
				childPid = fork();
				if (childPid < 0)
				{
					perror("fork failed");
					continue;
				}
				else if (childPid == 0)
				{
					if (execve(pathBuffer, tok, env) == -1)
					{
						perror("execve failed");
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					wait(&status);
				}
				free(pathBuffer);
			}
			else
				perror("Command not found");
		}
	}
	fflush(stdout);/*Display the content of buffer b4 storing another one*/
	free(buffer);
	return (0);
}
