#include "malloc.h"

int main()
{
    // TODO: tester 2 malloc egaux, les free, puis reallouer
    char* ptr = ft_malloc(16);
    ptr = ft_malloc(32);
    ptr = ft_malloc(4090);    
    // ptr = ft_malloc(64);
    // ptr = ft_malloc(128);
    // ptr = ft_malloc(10);
    // ptr = ft_malloc(20);
    // ptr = ft_malloc(30);

    (void)ptr;
    show_alloc_mem();
	return(0);
}