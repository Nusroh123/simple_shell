#include "main.h"

/**
 * getPathLocation - Gets the path of the inputted command
 * @buffer: a temporary storage for the inputted command
 * Return: Nothing
 *
 * Trying to handle path...
 * path gets the environment
 * pathCopy duplicates path
 * bufferLen get the length of the command(buffer)
 * pathToken breaks down the path into token
 * pathLen gets the length of each token
 * Create a file to hold the full length (filePath)
 * in a while loop:
 * copy pathToken into filePath i.e /bin
 * concatenate "/" i.e /bin/
 * concatenate the command(buffer) i.e /bin/ls
 *
 */
char *getPathLocation(char *buffer)
{
	char *path, *pathCopy, *pathToken, *filePath;
	int bufferLen, pathLen, i;
	struct stat statBuf;

	filePath = NULL;

	i = 0;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5; /** skip "PATH="**/
		}
	}

	if (path)
	{
		pathCopy = _strdup(path);
		bufferLen = _strlen(buffer);
		pathToken = strtok(pathCopy, ":");

		while (pathToken != NULL)
		{
			pathLen = _strlen(pathToken);
			filePath = malloc(bufferLen + pathLen + 2);
			_strcpy(filePath, pathToken);
			_strcat(filePath, "/");
			_strcat(filePath, buffer);
			if (stat(filePath, &statBuf) == 0 && filePath[1] != 'u')/*i.e successful*/
			{
				/**free(pathCopy);**/
				return (filePath);
			}
			else
			{
				free(filePath);
				pathToken = strtok(NULL, ":");
			}
		}
		free(pathCopy);
		if (stat(buffer, &statBuf) == 0)
		{
			return (buffer);
		}
		return (NULL);
	}
	return (NULL);
}
