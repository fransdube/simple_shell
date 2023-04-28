#include "shell.h"

/**
 * mfree - frees a pointer memory and NULLs the address
 * @ptr: address of the pointer to free its memory
 *
 * Return: 1 if freed, otherwise 0.
 */
int mfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
