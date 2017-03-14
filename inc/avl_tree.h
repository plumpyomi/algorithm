/***************************************************
 *
 *      Filename: inc/avl_tree.h
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-03-13 17:31:41
 * Last Modified: 2017-03-14 14:32:22
 *
 ***************************************************/
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "m_type.h"

typedef struct avl_tree_node{
	MY_TYPE	val;
	int		depth;
	struct avl_tree_node* p_left;
	struct avl_tree_node* p_right;
} avl_tree_node_t;

int avl_tree_show(avl_tree_node_t *p_root);
int avl_tree_destroy(avl_tree_node_t *p_root);
avl_tree_node_t* avl_tree_construct(MY_TYPE* in, int len);

#endif
