#include "main.h"

/**
 * getPathLocation - Gets the path of the inputted command
 * @buffer: a temporary storage for the inputted command
 * Return: Nothing
 */
char *getPathLocation(char *buffer)
{
	char *path, *pathCopy, *result;
	int i;
	struct stat statBuf;

	i = 0;
	result = NULL;
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
		result = getPath(buffer, pathCopy);
		free(pathCopy);
	}
	if (result == NULL && stat(buffer, &statBuf) == 0)
	{
		result = _strdup(buffer);
	}
	return (result);
}

/**
 * getPath - get path;
 * @buffer: command inputted
 * Return: Nothing
 */
char *getPath(char *buffer, char *pathCopy)
{
	char *pathToken, *filePath, *result;
	int bufferLen, pathLen;
	struct stat statBuf;

	filePath = NULL;
	result = NULL;

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
			result = filePath;
			break;
		}
		else
		{
			free(filePath);
			pathToken = strtok(NULL, ":");
		}
	}
	return (result);
}

/**
 * createFilePath - create a full path by concatenating directory and command
 * @directory: directory from PATH
 * @command: command to execute
 * Return: the full path
 */
char *createFilePath(char *directory, char *command)
{
	int pathLen = _strlen(directory);
	int commandLen = _strlen(command);
	char *filePath = malloc(pathLen + commandLen + 2);

	if (filePath == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	_strcpy(filePath, directory);
	_strcat(filePath, "/");
	_strcat(filePath, command);

	return (filePath);
}
