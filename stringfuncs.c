#include "shell.h"

/**
 * _strduplicate - duplicates a string
 * @str: the string
 *
 * Return: pointer to the duplicated string
 */
char *_strduplicate(const char *str)
{
	int length = 0;
	char *retn;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	retn = malloc(sizeof(char) * (length + 1));
	if (!retn)
		return (NULL);
	for (length++; length--;)
		retn[length] = *--str;
	return (retn);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _strcopy - copy a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcopy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITNG_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITNG_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}
