#include "main.h"

/**
 * _strcpy - copies the string pointed to by src,
 *  including the terminating null byte (\0),
 *  to the buffer pointed to by dest.
 * @dest: destination string
 * @src: source string
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	unsigned long int i;

	for (i = 0; i < strlen(src) && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[strlen(src)] = '\0';
	return (dest);
}
