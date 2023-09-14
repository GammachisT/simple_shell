#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free
 *
 * @ptr: Pointer to the memory previously allocated
 * @old_size: Size, in bytes, of the allocated space for ptr
 * @new_size: New size, in bytes of the new memory block
 *
 * Return: Memory reallocated
 **/
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char *s, *aux;
	unsigned int a;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		s = malloc(new_size);
		if (s == NULL)
			return (NULL);

		return (s);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	s = malloc(new_size);
	if (s == NULL)
		return (NULL);

	aux = ptr;
	for (a = 0; a < old_size; a++)
		s[a] = aux[a];

	free(ptr);

	return (s);
}

/**
 * free_memory_p - Free a pointer
 *
 * @ptr: Pointer to free
 **/
void free_memory_p(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}

	ptr = NULL;
}

/**
 * free_memory_pp - Free a double pointer
 *
 * @ptr: Double pointer to free
 **/
void free_memory_pp(void **ptr)
{
	void **tmp;

	for (tmp = ptr; *tmp != NULL; tmp++)
		free_memory_p(*tmp);

	free_memory_p(ptr);
}
