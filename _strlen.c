/**
 * _strlen - Function that rturns the length of a string
 * @s: Length of the string
 * Return: The value of s
 */
int _strlen(char *s)
{
	int l = 0;

	while (*s++)
		l++;
	return (l);
}
