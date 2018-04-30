#include "malloc.h"

int main()
{
    T_Datas *tmp;
    T_Datas *tmp2;
    
    // ft_printf("tmp: %u\n", sizeof(tmp->block));

	tmp = (T_Datas*)mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    tmp->size = 256;
    
    // tmp2 = (T_Datas*)((char*)tmp + 48);
    ft_printf("tmp->datas:              %p\n", tmp->data);
    ft_printf("tmp->datas + tmp->size:  %p\n", tmp->data + tmp->size);

    // printf("tmp2 - tmp = %ld\n", ((char*)tmp2 - (char*)tmp));


    // ft_printf("tmp->prev: %p\n", &tmp->prev);
    // ft_printf("tmp->next: %p\n", &tmp->next);
    // ft_printf("tmp->size: %p\n", &tmp->size);
    // ft_printf("tmp->free: %p\n", &tmp->free);
    // // ft_printf("tmp->lost: %p\n", &tmp->lost);
    // ft_printf("tmp->block: %p\n", &tmp->block);
        
    // tmp = (T_Datas*)(tmp->block + 4032);
    // tmp->size = 10000;
    // tmp->free = 1;
    // ft_printf("tmp: %p\n", tmp);
    // ft_printf("tmp->size: %d\n", tmp->size);
    // ft_printf("tmp->free: %d\n", tmp->free);
    // ft_printf("tmp->block: %p\n", tmp->block);
    
    // for (int i = 0; i < 1000; ++i){
    //     tmp2 = tmp;
    // 	tmp = (T_Datas*)mmap(tmp, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    //     // printf("tmp: %p | tmp2: %p | tmp - tmp2 = %ld\n", tmp, tmp2, (tmp - tmp2) * sizeof(T_Datas));
    //     if (tmp - 4096 / sizeof(T_Datas) != tmp2)
    //         ft_printf("NOT CONSEQUITIVE !");
    // }

    // ft_printf("%u\n", sizeof(size_t));
    
	return(0);
}