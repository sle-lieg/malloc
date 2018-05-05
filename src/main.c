#include "malloc.h"

int main()
{
    // TODO: tester 2 malloc egaux, les free, puis reallouer
    char* ptr = ft_malloc(50);

    (void)ptr;
    show_alloc_mem();
	return(0);
}