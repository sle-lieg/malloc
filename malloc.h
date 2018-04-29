#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <sys/mman.h>
#include "libft/inc/libft.h"
#include "libft/inc/ft_printf.h"

#define TINY_MAX 992
#define SMALL_MAX 992
#define LARGE_MAX 992

typedef struct S_Tiny   T_Tiny;
typedef struct S_Small  T_Small;
typedef struct S_Large  T_Large;
typedef struct S_Pages_Pointers  T_PgePointers;

#define CTRL_STRUCT_SIZE sizeof(struct S_Tiny)

struct  S_Pages_Pointers
{
    T_Tiny  *firstT;
    T_Small *firstS;
    T_Large *firstL;
};

struct S_Tiny
{
    T_Tiny  *prev;
    T_Tiny  *next;
    size_t  size;
    int     free;
    char    block[1];
};

struct S_Small
{
    T_Tiny  *prev;
    T_Tiny  *next;
    size_t  size;    
    int     free;
    char    block[1];    
};

struct S_Large
{
    T_Tiny  *prev;
    T_Tiny  *next;
    size_t  size;    
    int     free;
    char    block[1];    
};

#endif