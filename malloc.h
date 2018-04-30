#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft/inc/libft.h"
#include "libft/inc/ft_printf.h"

#define TINY_MAX 80
#define SMALL_MAX 245
#define MEM_ALIGN_SHIFT 5
#define MEM_ALIGN 16

#define MMAP_BAD_ALLOC 0x1

typedef struct S_Datas  T_Datas;
typedef struct S_Pages_Pointers  T_PgePointers;

#define DATAS_CTRL_SIZE sizeof(T_Datas)

struct  S_Pages_Pointers
{
    T_Datas *firstT;
    T_Datas *firstS;
    T_Datas *firstL;
    T_Datas *toReturn;
    int     pageSize;
    char    errors;
};

struct S_Datas
{
    T_Datas  *prev;
    T_Datas  *next;
    size_t  size;
    int     free;
    char    data[1];
};

T_PgePointers   pgePointers;

/**
 *      MALLOC.C
 **/
void        *malloc(size_t size);
void        handleTiny(size_t size);
void        handleSmall(size_t size);
void        handleLarge(size_t size);

/**
 *      ALLOCATOR.C
 **/
T_Datas*    getNewPage(T_Datas* lastBlock, size_t size);
void        initBlock(T_Datas* newBlock, T_Datas* lastBlock, size_t size);
void        findFreeBlock(T_Datas* block, size_t size);
void        splitBlock(T_Datas* block, size_t size);

#endif