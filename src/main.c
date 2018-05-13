#include "malloc.h"

int main()
{
   // TODO: tester 2 malloc egaux, les free, puis reallouer
   char* ptr1 = ft_malloc(32);
	// printTree(pgePointers.rootTiny);
   char* ptr2 = ft_malloc(3902);
	// printTree(pgePointers.rootTiny);
   char* ptr3 = ft_malloc(320);
   char* ptr4 = ft_malloc(20);
   char* ptr5 = ft_malloc(20);
   char* ptr6= ft_malloc(20);
   char* ptr7 = ft_malloc(20);
   char* ptr8 = ft_malloc(20);
   char* ptr9 = ft_malloc(20);
   char* ptr10 = ft_malloc(20);
	ft_free(ptr2);
	printTree(pgePointers.rootTiny); 
	ft_free(ptr4);
	printTree(pgePointers.rootTiny); 
	ft_free(ptr6);
	printTree(pgePointers.rootTiny); 
	// printTree(pgePointers.rootTiny); 
	ft_free(ptr8);
	printTree(pgePointers.rootTiny); 
	// printTree(pgePointers.rootTiny);
	ft_free(ptr1);
	printTree(pgePointers.rootTiny);
	ft_free(ptr3);
	printTree(pgePointers.rootTiny);
	ft_free(ptr5);
	printTree(pgePointers.rootTiny); 
	ft_free(ptr7);
	printTree(pgePointers.rootTiny); 
	ft_free(ptr9);
	printTree(pgePointers.rootTiny); 
	ft_free(ptr10);	

   //  ptr = ft_malloc(4090);
    // ptr = ft_malloc(64);
    // ptr = ft_malloc(128);
    // ptr = ft_malloc(10);
    // ptr = ft_malloc(20);
    // ptr = ft_malloc(30);

	// show_alloc_mem();
	return(0);
}