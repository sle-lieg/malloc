#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_printf.h"

#define TINY_MAX 80
#define SMALL_MAX 245
#define MEM_ALIGN_SHIFT 5
#define MEM_ALIGN 16

#define MMAP_BAD_ALLOC 0x1

typedef struct s_datas          t_datas;
typedef struct s_pagesPointers t_pagesPointers;

#define DATAS_CTRL_SIZE sizeof(t_datas)

struct  s_pagesPointers
{
    t_datas *firstT;
    t_datas *firstS;
    t_datas *firstL;

    void*   tinyPage;
    void*   smallPage;
    void*   largePage;
    
    t_datas *toReturn;
    int     requiredSize;
    int     pageSize;
    char    errors;
};

struct s_datas
{
    t_datas*    prev;
    t_datas*    next;
    char*       pageAddr;
    size_t      size;
    size_t      requiredSize;
    int         free;
};

t_pagesPointers   pgePointers;

/**
 *      MALLOC.C
 **/
void*       ft_malloc(size_t size);
void        handleTiny(size_t size);
// void        handleSmall(size_t size);
// void        handleLarge(size_t size);
void        show_alloc_mem();

/**
 *      ALLOCATOR.C
 **/
t_datas*    getNewPage(t_datas* lastBlock, size_t size);
void        initBlock(t_datas* newBlock, t_datas* lastBlock, size_t size);
void        findFreeBlock(t_datas* block, size_t size);
void        splitBlock(t_datas* block, size_t size);

#endif