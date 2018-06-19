#include <stdio.h>
// #include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
// #include "malloc.h"

int main()
{
	char* p1 = malloc(0);
	char* p2 = malloc(0);
	char* p3 = malloc(0);

	struct rlimit limit;

	getrlimit(RLIMIT_DATA, &limit);
	printf("MAX= %llu\n", limit.rlim_max);

	// strcpy(p1, "aaaaaaaaaaaaaaa\0");
	// strcpy(p2, "bbbbbbbbbbbbbbb\0");
	// strcpy(p3, "ccccccccccccccc\0");
	printf("%p: %s\n", p1, p1);
	printf("%p: %s\n", p2, p2);
	printf("%p: %s\n", p3, p3);
	// *(p1 + 4096) = 'X';
	// *(p1 + 4098) = 'X';
	// *(p1 + 16) = 'X';
	// printf("%p: %s\n", p1, p1);
	// printf("%p: %s\n", p2, p2);
	
	free(p1);
	free(p2);
	free(p3);
	// char* p1 = malloc(30);
	// char* p2 = malloc(30);
	// char* p3 = malloc(30);
	// char* p4= malloc(30);
	// char* p5 = malloc(30);
	// char* p6 = malloc(30);
	// // printAll();
	// // printTree2(pgePointers.rootTiny);
	// ft_printf("***************************\n");
	// free(p5);
	// free(p6);
	// // printAll();
	// // printTree2(pgePointers.rootTiny);
	// ft_printf("***************************\n");
	
	// p5 = malloc(4050);
	// p6 = malloc(30);
	// // printAll();
	// // printTree2(pgePointers.rootTiny);
	// ft_printf("***************************\n");
	
	// char* p7 = malloc(30);
	// char* p8 = malloc(30);
	// printAll();
	// printTree2(pgePointers.rootTiny);
	return (0);
}
