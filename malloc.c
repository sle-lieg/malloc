#include "malloc.h"

void	*malloc(size_t size)
{
	/*
		- check the size to allocate to know wich allocation to call (Tiny, Small, Large)
		- align the size required to be multiple of 16(8) bytes 
		- check if there has already been a call to mmap for the allocation to call
			(if there is already a page available for the calling process)
		- if not:
			* call mmap of the size asked, and store the return in the appropriate pointer
			* store a 'control structure' at the begining of the page, and initialise it with the
				appropriate values. ('free' to 0, 'size' to size...)
			*return block to return the first octet located right after the control structure.
		- if yes:
			* search for a struct control that has its 'size' value greater or egual to the size asked, AND that has
				its 'free' value set to TRUE (1).
			* split the available block by adding a struct ctrl at the struct ctrl found -> block + size (+1) and setting
				the new struct ctrl and current struct ctrl variables
			return the addr of the found struct ctrl
	*/
	pgePointers.toReturn = NULL;
	pgePointers.pageSize = getpagesize();
	size = (size % MEM_ALIGN) ?  ((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
	if (size <= TINY_MAX)
		handleTiny(size);
	else if (size < SMALL_MAX)
		handleSmall(size);
	else
		handleLarge(size);
	if (pgePointers.errors)
		return NULL;
	return pgePointers.toReturn->data;
}

void	handleTiny(size_t size)
{
	if (!pgePointers.firstT)
		if (!(pgePointers.firstT = getNewPage(NULL, size)))
			return;
	findFreeBlock(pgePointers.firstT, size);
}

// void	handleSmall(size_t size)
// {
// 	if (!pgePointers.firstS)
// 		if (!(pgePointers.firstS = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstS, size);
// }

// void	handleLarge(size_t size)
// {
// 	if (!pgePointers.firstL)
// 		if (!(pgePointers.firstL = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstL, size);
// }
