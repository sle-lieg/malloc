// #include <stdio.h>
// #include <sys/mman.h>
// #include <stdlib.h>
#include "malloc.h"

int main()
{
	char* p1 = malloc(30);
	char* p2 = malloc(30);
	char* p3 = malloc(30);
	char* p4= malloc(30);
	char* p5 = malloc(30);
	char* p6 = malloc(30);
	// printAll();
	// printTree2(pgePointers.rootTiny);
	ft_printf("***************************\n");
	free(p5);
	free(p6);
	// printAll();
	// printTree2(pgePointers.rootTiny);
	ft_printf("***************************\n");
	
	p5 = malloc(4050);
	p6 = malloc(30);
	// printAll();
	// printTree2(pgePointers.rootTiny);
	ft_printf("***************************\n");
	
	char* p7 = malloc(30);
	char* p8 = malloc(30);
	// printAll();
	// printTree2(pgePointers.rootTiny);
	return (0);
}