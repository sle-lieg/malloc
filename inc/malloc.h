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

typedef struct s_memory_ctrl    t_mem_ctrl;
typedef struct s_pagesPointers  t_pagesPointers;

#define DATAS_CTRL_SIZE sizeof(t_mem_ctrl)

struct  s_pagesPointers
{
    t_mem_ctrl* rootTiny;
    t_mem_ctrl* rootSmall;
    t_mem_ctrl* rootLarge;
    void*       tinyPage;
    void*       smallPage;
    void*       largePage;
    size_t      size;
    int         pageSize;
    
    char*       toReturn;

    char        errors;
};

struct s_memory_ctrl
{
    t_mem_ctrl* lnode;
    t_mem_ctrl* rnode;    
    t_mem_ctrl* prev;
    t_mem_ctrl* next;
    char*       pageAddr;
    size_t      allocatedSize;
    size_t      requiredSize;
    int         free; 
    int         pageSerie; // allow fusion if eguals to other memCtrl
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
t_mem_ctrl*    getNewPage(t_mem_ctrl* lastBlock, size_t size);
void        initBlock(t_mem_ctrl* newBlock, t_mem_ctrl* lastBlock, size_t size);
void        findFreeBlock(t_mem_ctrl* block, size_t size);
void        splitBlock(t_mem_ctrl* block, size_t size);

#endif