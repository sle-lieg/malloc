#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_printf.h"
#include <sys/resource.h>

#define TINY_MAX UINTMAX_MAX
// #define TINY_MAX 2147483648
#define SMALL_MAX 245
#define MEM_ALIGN_SHIFT 4
// TODO : TRY WITH MEMORY ALIGN ON 8 AND 4
#define MEM_ALIGN 16
#define NB_PAGES 10

#define MMAP_BAD_ALLOC 0x1

typedef struct s_memory_ctrl    t_mem_ctrl;
typedef struct s_pagesPointers  t_pagesPointers;

#define MEM_CTRL_SIZE sizeof(t_mem_ctrl)

struct  s_pagesPointers
{
    t_mem_ctrl* rootTiny;       // contains the root with average size available
    t_mem_ctrl* rootSmall;      // to sort by size
    t_mem_ctrl* rootLarge;
    t_mem_ctrl* firstTinyCtrl;   // contains the first memCtrl created
    t_mem_ctrl* firstSmallCtrl;
    t_mem_ctrl* firstLargeCtrl;
    t_mem_ctrl* lastTinyCtrl;   // phisically last memCtrl on the heap (used to create new mem_ctrl from its address + mem_ctrl size)
    t_mem_ctrl* lastSmallCtrl;
    t_mem_ctrl* lastLargeCtrl;
    size_t      memCtrlSizeLeft;
    size_t      size;
    int         pageSize;
    int         pageSerieCount;

    t_mem_ctrl* toReturn;

    char        errors;
    
    t_mem_ctrl* lost_mem_ctrl; // PROTOTYPE list of lost t_mem_ctrl after blocks-fusion

	// size_t count;
};

struct s_memory_ctrl
{
    t_mem_ctrl* father; // tree links for the research by free space
    t_mem_ctrl* lchild;
    t_mem_ctrl* rchild;
    t_mem_ctrl* prev; // list links for the order of the memory blocks, to
    t_mem_ctrl* next; // merge blocks together if they are free
    char*       pageAddr;   // point to the address to return to caller
    size_t      allocatedSize;
    size_t      requiredSize;
    int         height; // height in the tree for balance factor
    int         free;
    int         pageSerie; // allow fusion if eguals to other memCtrl
};

t_pagesPointers   pgePointers;

/**
 *      MALLOC.C
 **/
void*       malloc(size_t size);
void        handleTiny(size_t size);
// void        handleSmall(size_t size);
// void        handleLarge(size_t size);
int			initRootTiny(size_t size);
int			checkLimit(size_t size);

/**
 *      ALLOCATOR.C
 **/
void*       getNewPage(t_mem_ctrl* pageMemCtrl, size_t size);
t_mem_ctrl*	createNewMemCtrl(t_mem_ctrl* memCtrlSplited);
t_mem_ctrl* splitMemory(size_t size);
void			setMemCtrl(t_mem_ctrl* newMemCtrl, t_mem_ctrl* memCtrlSplited);
t_mem_ctrl* popLostMemCtrl();

/**
 *      TREE_CHECKER.C
 **/
void        findFreeBlock(t_mem_ctrl* node, size_t size);
int         checkBalance(t_mem_ctrl* node);
int         maxHeight(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB);
void        checkHeight(t_mem_ctrl* node);

/**
 *      TREE_GETTERS.C
 **/
t_mem_ctrl* getInOrderPredecessor(t_mem_ctrl* toReplace, t_mem_ctrl* node);
t_mem_ctrl* getInOrderSuccessor(t_mem_ctrl* toReplace, t_mem_ctrl* node);
// t_mem_ctrl* getInOrderPredecessor(t_mem_ctrl* node);
// t_mem_ctrl* getInOrderSuccessor(t_mem_ctrl* node);
int         getHeight(t_mem_ctrl* node);

/**
 *      TREE_INSERTERS.C
 **/
void        addNode(t_mem_ctrl** root, t_mem_ctrl* newNode);
void        recursiveAdd(t_mem_ctrl* node, t_mem_ctrl* newNode);

/**
 *      TREE_REMOVER.C
 **/
void        removeNode(t_mem_ctrl* node);
void        removeLeaf(t_mem_ctrl* node);
void        removeParentOfChildren(t_mem_ctrl* node);
void        removeParentOfOrphan(t_mem_ctrl* node);
void			recursiveBalance(t_mem_ctrl* node);

/**
 *      TREE_ROTATIONS.C
 **/
void        rotateLeft(t_mem_ctrl* node);
void        rotateRight(t_mem_ctrl* node);

/**
 *      TREE_TOOLS.C
 **/
void        linkNodes(t_mem_ctrl* father, t_mem_ctrl* child);
void        swapNodes(t_mem_ctrl* predecessor, t_mem_ctrl* node);
void        replaceIfRoot(t_mem_ctrl* node);
int			isLastMemCtrl(t_mem_ctrl* ptr);
void        addLinks(t_mem_ctrl* father, t_mem_ctrl* child);

/**
 *      DEBUG.C
 **/
void        show_alloc_mem();
void			printTree2(t_mem_ctrl* root);
void			printTree(t_mem_ctrl* root);
void			printLevels(t_mem_ctrl* node, int i);
void			printAll();
void			printLosts();
void			checkFree();
void			checkGoodHeight(t_mem_ctrl* node);


/**
 *      FREE.C
 **/
void			free(void* ptr);;
void			checkTiny(void* ptr);
void			freeMemCtrl(t_mem_ctrl* ptr);
void 			linkLostPrevNext(t_mem_ctrl* ptr);
void			pushToLost(t_mem_ctrl* ptr);

/**
 *      REALLOC.C
 **/
void*			realloc(void *ptr, size_t size);
t_mem_ctrl* getMemCtrl(void* ptr);
void*			checkSize(size_t size);

/**
 *      REALLOCF.C
 **/
void*			reallocf(void *ptr, size_t size);
// t_mem_ctrl* getMemCtrl(void* ptr);
void			checkSizeF(size_t size);

#endif