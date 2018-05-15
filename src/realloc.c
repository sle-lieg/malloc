#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	char* newPtr;
	return (malloc(size));
	if (!(newPtr = malloc(size)))
		return NULL;
	ft_strncpy(newPtr, ptr, size);
	return newPtr;
}