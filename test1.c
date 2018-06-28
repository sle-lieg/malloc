#include <stdlib.h>
#include "malloc.h"

int main()
{
	int i;
	char *addr;
	ft_printf("SIZE: %lu\n", sizeof(t_mem_ctrl));

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024); 
		addr[0] = 42;
		i++;
	}
return (0);
}
