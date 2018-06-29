/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:52:12 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 16:36:13 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
# include "ft_printf.h"

# define TRUE 1
# define FALSE 0
# define TINY_MAX 128
# define SMALL_MAX 2048
# define ALIGN_16_SHIFT 4
# define MEM_ALIGN_16 16
# define ALIGN_PAGE_SHIFT 12
# define NB_PAGES 1
# define MMAP_BAD_ALLOC 0x1

typedef struct s_memory_ctrl	t_mem_ctrl;
typedef struct s_pages_control	t_pge_ctrl;

struct							s_pages_control
{
	t_mem_ctrl		*header_pge;
	t_mem_ctrl		*header_pge_limit;
	t_mem_ctrl		*root;
	t_mem_ctrl		*lost_mem_ctrl;
	t_mem_ctrl		*fst_tiny;
	t_mem_ctrl		*lst_tiny;
	t_mem_ctrl		*free_tiny;
	t_mem_ctrl		*fst_small;
	t_mem_ctrl		*lst_small;
	t_mem_ctrl		*free_small;
	t_mem_ctrl		*fst_large;
	t_mem_ctrl		*lst_large;
	t_mem_ctrl		*ret;
	int				pages_id;
	size_t			tiny_zone;
	size_t			small_zone;
	char			errors;
};

struct							s_memory_ctrl
{
	t_mem_ctrl		*father;
	t_mem_ctrl		*lchild;
	t_mem_ctrl		*rchild;
	t_mem_ctrl		*prev;
	t_mem_ctrl		*next;
	t_mem_ctrl		*next_free;
	char			*addr;
	size_t			size;
	int				height;
	unsigned short	pge_id;
	char			free;
};

t_pge_ctrl						g_pges_ctrl;
static pthread_mutex_t			g_mutex_alloc = PTHREAD_MUTEX_INITIALIZER;

/*
**	MALLOC.C
*/
void							*malloc(size_t size);
void							handle_tiny(size_t size);
void							handle_small(size_t size);
void							handle_large(size_t size);

/*
**	MEMORY_CTRL_TOOLS.C
*/
void							find_free_block(t_mem_ctrl *block, size_t size);
void							split_memory(size_t size);
void							add_to_free(t_mem_ctrl **free_head,\
												t_mem_ctrl *new_header);
void							remove_from_free(t_mem_ctrl *tmp,\
													t_mem_ctrl *block);
t_mem_ctrl						*pop_lost_mem_ctrl(void);

/*
**	HEAP_CTRL.C
*/
int								extend_header_pge(void);
void							*create_new_page(size_t size);
int								extend_heap(t_mem_ctrl *last_mctrl,\
									size_t size);
size_t							align_memory16(size_t size);
size_t							align_memory_page(size_t size);

/*
**	INIT.C
*/
int								init_tiny(void);
int								init_small(void);

/*
**	TREE_INSERTERS.C
*/
void							add_node(t_mem_ctrl *new_node);
void							recursive_add(t_mem_ctrl *node,\
												t_mem_ctrl *new_node);

/*
**	TREE_TOOLS.C
*/
void							add_links(t_mem_ctrl *father,\
											t_mem_ctrl *child);
void							swap_nodes(t_mem_ctrl *predecessor,\
											t_mem_ctrl *node);
void							link_nodes(t_mem_ctrl *father,\
											t_mem_ctrl *child);

/*
**	TREE_CHECKER.C
*/
int								check_balance(t_mem_ctrl *node);
int								max_height(t_mem_ctrl *nod_a,\
											t_mem_ctrl *nod_b);

/*
**	TREE_ROTATIONS.C
*/
void							rotate_left(t_mem_ctrl *node);
void							rotate_right(t_mem_ctrl *node);

/*
**	TREE_REMOVER.C
*/
void							remove_node(t_mem_ctrl *node);
void							remove_leaf(t_mem_ctrl *node);
void							remove_parent_of_children(t_mem_ctrl *node);
void							remove_orphan(t_mem_ctrl *node);
void							recursive_balance(t_mem_ctrl *node);

/*
**	TREE_GETTERS.C
*/
t_mem_ctrl						*get_predecessor(t_mem_ctrl *to_replace,\
												t_mem_ctrl *node);
t_mem_ctrl						*get_successor(t_mem_ctrl *to_replace,\
												t_mem_ctrl *node);
t_mem_ctrl						*find_mem_ctrl(t_mem_ctrl *node,\
												char *addr_to_free);

/*
**	FREE.C
*/
void							free(void *ptr);
void							free_mem_ctrl(t_mem_ctrl *to_f);
void							push_to_lost(t_mem_ctrl *ptr);

/*
**	REALLOC.C
*/
void							*realloc(void *ptr, size_t size);

/*
**	REALLOCF.C
*/
void							*reallocf(void *ptr, size_t size);

/*
**	CALLOC.C
*/
void							*calloc(size_t count, size_t size);

/*
**	DEBUG.C
*/
void							show_alloc_mem();

#endif
