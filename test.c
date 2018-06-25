// #include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{	
	char* p1 = malloc(1);
	char *p2 = realloc(p1 + 1, 32);

	printf("%p\n", p2);
	return (0);
}
