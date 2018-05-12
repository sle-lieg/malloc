#include "malloc.h"

int main()
{
   // TODO: tester 2 malloc egaux, les free, puis reallouer
   char* ptr1 = ft_malloc(32);
   char* ptr2 = ft_malloc(32);
	ft_free(ptr1);
   char* ptr3 = ft_malloc(20);
	ft_free(ptr2);
	ft_free(ptr3);
	
   char* ptr4 = ft_malloc(55);
	ft_free(ptr4);

	printTree(pgePointers.rootTiny); 

   //  ptr = ft_malloc(4090);
    // ptr = ft_malloc(64);
    // ptr = ft_malloc(128);
    // ptr = ft_malloc(10);
    // ptr = ft_malloc(20);
    // ptr = ft_malloc(30);

	// show_alloc_mem();
	return(0);
}