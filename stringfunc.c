#include "shell.h"

/**
 * _strlength - finds a string's
 * @s: the string whose length
 *
 * Return: integer of length
 */
int _strlength(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strconcat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 *
 * Return: pointer to destination buffer
 */
char *_strconcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcompare - performs comparison of two strings.
 * @s1:  first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcompare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


