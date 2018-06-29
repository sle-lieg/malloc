// #include "inc/malloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>


int main()
{
	char* p1 = malloc(5);
	char* p2 = malloc(31000);
	char* p3 = malloc(1000);
	
	free(p1);
	free(p2);
	free(p3);
	return (0);
   // char* ptr3 = malloc(20);
   // char* ptr4 = malloc(20);
   // char* ptr5 = malloc(20);
	// free(ptr1);
	// free(ptr2);
	// free(ptr3);
	// free(ptr4);
	// free(ptr5);
   // char* ptr6= malloc(20);
   // char* ptr7 = malloc(20);
   // char* ptr8 = malloc(20);
   // char* ptr9 = malloc(20);
   // char* ptr10 = malloc(20);
	// free(ptr6);
	// free(ptr7);
	// free(ptr8);
	// free(ptr9);
	// free(ptr10);

   // char* ptr1;
	// for (int i = 0; i < 60; i++)
	// {
	// 	if (i == 50)
	// 		// ft_printf("51");
	// 	ptr1 = malloc(16);
	// 	// printTree(g_pges_ctrl.rootTiny);
	// 	// ft_printf("--------------\n\n");	
	// }
	// free(ptr1);
	// // ft_printf("1\n");
	// // printTree(g_pges_ctrl.rootTiny);
   // char* ptr2 = malloc(3902);
	// // ft_printf("2\n");
	// // printTree(g_pges_ctrl.rootTiny);
   // char* ptr3 = malloc(320);
	// // ft_printf("3\n");
	// // printTree(g_pges_ctrl.rootTiny); 	
   // char* ptr4 = malloc(20);
	// // ft_printf("4\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr5 = malloc(20);
	// // ft_printf("5\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr6= malloc(20);
	// // ft_printf("6\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr7 = malloc(20);
	// // ft_printf("7\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr8 = malloc(20);
	// // ft_printf("8\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr9 = malloc(20);
	// // ft_printf("9\n");
	// // printTree(g_pges_ctrl.rootTiny); 
   // char* ptr10 = malloc(20);
	// free(ptr2);
	// // ft_printf("10\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr4);
	// // ft_printf("11\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr6);
	// // ft_printf("12\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr8);
	// // ft_printf("13\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// // printTree(g_pges_ctrl.rootTiny);
	// free(ptr1);
	// // ft_printf("14\n");
	// // printTree(g_pges_ctrl.rootTiny);
	// free(ptr3);
	// // ft_printf("16\n");
	// // printTree(g_pges_ctrl.rootTiny);
   // char* ptr11 = malloc(20);
	// // ft_printf("17--\n");
	// // printTree(g_pges_ctrl.rootTiny);	
	// free(ptr5);
	// // ft_printf("17\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr7);
	// // ft_printf("18\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr9);
   // char* ptr12 = malloc(20);
	// // ft_printf("19--\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// // ft_printf("19\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr10);
	// // ft_printf("20\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr11);
	// // ft_printf("21\n");
	// // printTree(g_pges_ctrl.rootTiny); 
	// free(ptr12);
	// // ft_printf("22\n");
	// // printTree(g_pges_ctrl.rootTiny); 	


   // TODO: tester 2 malloc egaux, les free, puis reallouer
   // char* ptr1;
	// for (int i = 0; i < 60; i++)
	// {
	// 	if (i == 50)
			// ft_printf("51");
	// 	ptr1 = ft_malloc(16);
	// 	printTree(g_pges_ctrl.rootTiny);
	// 	ft_printf("--------------\n\n");	
	// }
	// ft_free(ptr1);
	// ft_printf("1\n");
	// printTree(g_pges_ctrl.rootTiny);
   // char* ptr2 = ft_malloc(3902);
	// ft_printf("2\n");
	// printTree(g_pges_ctrl.rootTiny);
   // char* ptr3 = ft_malloc(320);
	// ft_printf("3\n");
	// printTree(g_pges_ctrl.rootTiny); 	
   // char* ptr4 = ft_malloc(20);
	// ft_printf("4\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr5 = ft_malloc(20);
	// ft_printf("5\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr6= ft_malloc(20);
	// ft_printf("6\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr7 = ft_malloc(20);
	// ft_printf("7\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr8 = ft_malloc(20);
	// ft_printf("8\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr9 = ft_malloc(20);
	// ft_printf("9\n");
	// printTree(g_pges_ctrl.rootTiny); 
   // char* ptr10 = ft_malloc(20);
	// ft_free(ptr2);
	// ft_printf("10\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr4);
	// ft_printf("11\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr6);
	// ft_printf("12\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// // printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr8);
	// ft_printf("13\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// // printTree(g_pges_ctrl.rootTiny);
	// ft_free(ptr1);
	// ft_printf("14\n");
	// printTree(g_pges_ctrl.rootTiny);
	// ft_free(ptr3);
	// ft_printf("16\n");
	// printTree(g_pges_ctrl.rootTiny);
   // char* ptr11 = ft_malloc(20);
	// ft_printf("17--\n");
	// printTree(g_pges_ctrl.rootTiny);	
	// ft_free(ptr5);
	// ft_printf("17\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr7);
	// ft_printf("18\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr9);
   // char* ptr12 = ft_malloc(20);
	// ft_printf("19--\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_printf("19\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr10);
	// ft_printf("20\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr11);
	// ft_printf("21\n");
	// printTree(g_pges_ctrl.rootTiny); 
	// ft_free(ptr12);
	// ft_printf("22\n");
	// printTree(g_pges_ctrl.rootTiny); 	

   // //  ptr = ft_malloc(4090);
   // //  ptr = ft_malloc(64);
   // //  ptr = ft_malloc(128);
   // //  ptr = ft_malloc(10);
   // //  ptr = ft_malloc(20);
   // //  ptr = ft_malloc(30);

	// // show_alloc_mem();
	return(0);
}
