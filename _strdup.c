#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.  * @str: string
 * Return: pointer or NULL
 */
char *_strdup(char *str)
{
	size_t len;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	len = strlen(str);
	duplicate = (char *)malloc((len + 1) * sizeof(char));

	if (duplicate == NULL)
		return (NULL);
	if (duplicate != NULL)
	{
		strcpy(duplicate, str);
		return (duplicate);
	}
	else
		return (NULL);

	return (duplicate);
}
