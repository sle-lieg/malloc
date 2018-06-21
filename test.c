#include "malloc.h"

int main()
{	
	char* p1 = malloc(1);
	char* p2 = malloc(128);
	char* p3 = malloc(129);
	char* p4 = malloc(4096);
	// char* p5 = malloc(4097);
	// char* p6 = malloc(50000);

	// char* p7 = malloc(50);
	// char* p8 = malloc(1280);
	// char* p9 = malloc(120);
	// char* p10 = malloc(4096);
	// char* p11 = malloc(8192);
	// char* p12 = malloc(3);

	ft_printf("p1->%p\n", p1);
	ft_printf("p2->%p\n", p2);
	ft_printf("p3->%p\n", p3);
	ft_printf("p4->%p\n", p4);
	// // ft_printf("p5->%p\n", p5);
	// // ft_printf("p6->%p\n", p6);
	// show_alloc_mem();

	free(p1);
	free(p2);
	free(p3);
	free(p4);
	// free(p5);
	// free(p6);
	// free(p7);
	// free(p8);
	// free(p9);
	// free(p10);
	// free(p11);
	// free(p12);
	return (0);
}
