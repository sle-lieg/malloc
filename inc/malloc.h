#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_printf.h"
#include <sys/resource.h>

#include <assert.h>

#define TINY_MAX ( 128 )
#define SMALL_MAX ( 4096 )
#define MEM_ALIGN_SHIFT ( 4 )
// TODO : TRY WITH MEMORY ALIGN ON 8 AND 4
#define MEM_ALIGN ( 16 )
#define NB_PAGES ( 2 )

#define MMAP_BAD_ALLOC ( 0x1 )

typedef struct s_memory_ctrl		t_mem_ctrl;
typedef struct s_pages_control	t_pge_ctrl;

#define MEM_CTRL_SIZE sizeof(t_mem_ctrl)

struct	s_pages_control
{
	t_mem_ctrl* header_pge; 	// contains the address of the last created header
	t_mem_ctrl* header_pge_limit; 	// contains the address of the last created header
	
	t_mem_ctrl* root;	// contains the root header of all headers created
	t_mem_ctrl* lost_headers;	// list of headers lost after blocks fusion

	t_mem_ctrl* fst_tiny;		// contains the first header of	tiny
	t_mem_ctrl* lst_tiny;		// contains the last header of	tiny
	t_mem_ctrl* free_tiny;		// head of the list of free tiny's
	
	t_mem_ctrl* fst_small;		// 		"								small
	t_mem_ctrl* lst_small;		// 		"								small
	t_mem_ctrl* free_small;		// 		"								smalls

	t_mem_ctrl* ret;				// header that contains the address to return
	int			pages_id;		// to give an id to the header of the same pages

	size_t		tiny_zone;		// size to contains minimum 100 tiny
	size_t		small_zone;		// size to contains minimum 100 small

	char			errors;

	// // size_t count;
};

struct s_memory_ctrl
{
	t_mem_ctrl* father;		// tree links for the research by address
	t_mem_ctrl* lchild;
	t_mem_ctrl* rchild;
	t_mem_ctrl* prev;			// list links for the order of the memory blocks, to
	t_mem_ctrl* next;			// merge blocks together if they are free
	t_mem_ctrl* next_free; 	// link to the next free header, to speed up search
	char*			addr;			// point to the address to return from malloc
	size_t		size;
	int			height;		// height in the tree for balance factor
	char			free;			// booleen, is free: TRUE, else FALSE
	int			pge_id;		// allow fusion if eguals to other memCtrl
};

t_pge_ctrl	pges_ctrl;

/**
 *			MALLOC.C
 **/
void*			malloc(size_t size);
void			handle_tiny(size_t size);
void			handle_small(size_t size);
void			handle_large(size_t size);
int			checkLimit(size_t size);
size_t		align_memory(size_t size);
t_mem_ctrl*	split_memory(size_t size);
void			find_free_block(t_mem_ctrl* block, size_t size);
void			add_to_free(t_mem_ctrl** free_head, t_mem_ctrl* new_header);
void			remove_from_free(t_mem_ctrl* block);
int			extend_heap(t_mem_ctrl* last_mctrl);

/**
 *			INIT.C
 **/
int			extend_header_pge();
int			init_tiny();
int			init_small();
// int			initRootLarge();

/**
 *      ALLOCATOR.C
 **/
void*	create_new_page(size_t size);
// t_mem_ctrl*	createNewMemCtrl(t_mem_ctrl* memCtrlSplited);
t_mem_ctrl*	createNewTinyMemCtrl(t_mem_ctrl* memCtrlSplited);
t_mem_ctrl*	createNewSmallMemCtrl(t_mem_ctrl* memCtrlSplited);
t_mem_ctrl*	createNewLargeMemCtrl(t_mem_ctrl* memCtrlSplited);

t_mem_ctrl* splitMemory(size_t size);
void			setMemCtrl(t_mem_ctrl* newMemCtrl, t_mem_ctrl* memCtrlSplited);
t_mem_ctrl* popLostMemCtrl();

/**
 *      TREE_CHECKER.C
 **/
int         check_balance(t_mem_ctrl* node);
int         max_height(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB);
void        check_height(t_mem_ctrl* node);

/**
 *      TREE_GETTERS.C
 **/
t_mem_ctrl* getInOrderPredecessor(t_mem_ctrl* toReplace, t_mem_ctrl* node);
t_mem_ctrl* getInOrderSuccessor(t_mem_ctrl* toReplace, t_mem_ctrl* node);
// t_mem_ctrl* getInOrderPredecessor(t_mem_ctrl* node);
// t_mem_ctrl* getInOrderSuccessor(t_mem_ctrl* node);
int         get_height(t_mem_ctrl* node);

/**
 *      TREE_INSERTERS.C
 **/
void        add_node(t_mem_ctrl* newNode);
void        recursive_add(t_mem_ctrl* node, t_mem_ctrl* newNode);

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
void			linkNodes(t_mem_ctrl* father, t_mem_ctrl* child);
void			swapNodes(t_mem_ctrl* predecessor, t_mem_ctrl* node);
int			replaceIfRoot(t_mem_ctrl* node, t_mem_ctrl* newRoot);
int			isLastMemCtrl(t_mem_ctrl* ptr);
void			add_links(t_mem_ctrl* father, t_mem_ctrl* child);

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
void			free(void* ptr);
int			findMemCtrl(t_mem_ctrl* tmp, void* ptr);
void			freeMemCtrl(t_mem_ctrl* ptr);
void 			linkLostPrevNext(t_mem_ctrl* ptr);
void			pushToLost(t_mem_ctrl* ptr);
int			findLargeMemCtrl(t_mem_ctrl* tmp, void* ptr);


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
