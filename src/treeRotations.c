#include "malloc.h"

void  rotateLeft(t_mem_ctrl* node)
{
   t_mem_ctrl* tmp;

   tmp = node->rchild;
   linkNodes(node, tmp->lchild);
   linkNodes(tmp, node->father);
   linkNodes(tmp, node);
}

void  rotateRight(t_mem_ctrl* node)
{
   t_mem_ctrl* tmp;

   tmp = node->lchild;
   linkNodes(node, tmp->rchild);
   linkNodes(tmp, node->father);
   linkNodes(tmp, node);
}