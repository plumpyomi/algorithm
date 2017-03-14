/***************************************************
 *
 *      Filename: src/avl_tree.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-03-02 11:43:15
 * Last Modified: 2017-03-14 14:55:50
 *
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "debug.h"
#include "public.h"

static int __avl_tree_depth(avl_tree_node_t *p_node)
{
	int ret;

	if(p_node == NULL){
		ret = 0;
	}else{
		int l_depth, r_depth;

		l_depth = __avl_tree_depth(p_node->p_left);
		r_depth = __avl_tree_depth(p_node->p_right);
		
		ret = ((l_depth>r_depth)?l_depth:r_depth)+1;
	}

	return ret;
}

static int __get_avl_lr_depth(avl_tree_node_t *p_node, int* p_ld, int* p_rd)
{
	*p_ld = *p_rd = 0;
	if(p_node == NULL){
		return -1;
	}
	if(p_node->p_left != NULL){
		*p_ld = p_node->p_left->depth;
	}
	if(p_node->p_right != NULL){
		*p_rd = p_node->p_right->depth;
	}

	return 0;
}

static avl_tree_node_t* __avl_tree_insert(avl_tree_node_t *p_node, MY_TYPE val)
{
	if(p_node == NULL){
		p_node = (avl_tree_node_t*)malloc(sizeof(avl_tree_node_t));
		if(p_node == NULL)
			return NULL;
		p_node->val		= val;
		p_node->depth	= 1;
		p_node->p_left	= NULL;
		p_node->p_right	= NULL;
	}else{
		int l_depth, r_depth;

		if(val < p_node->val){
			p_node->p_left = __avl_tree_insert(p_node->p_left, val);
		}else{
			p_node->p_right = __avl_tree_insert(p_node->p_right, val);
		}
		__get_avl_lr_depth(p_node, &l_depth, &r_depth);
		p_node->depth = ((l_depth>r_depth)?l_depth:r_depth)+1;
	}
	
	return p_node;
}

avl_tree_node_t* avl_tree_construct(MY_TYPE* in, int len)
{
	int i;
	avl_tree_node_t *p_root;

	p_root = NULL;
	for(i = 0; i < len; ++i){
		printf("insert a[%d] = %d\n", i, in[i]);
		p_root = __avl_tree_insert(p_root, in[i]);
	}
	
	return p_root;
}

int avl_tree_destroy(avl_tree_node_t *p_root)
{
	if(p_root == NULL)
		return 0;
	if(p_root->p_left == NULL && p_root->p_right == NULL){
		free(p_root);
	}else{
		avl_tree_destroy(p_root->p_left);
		p_root->p_left = NULL;
		avl_tree_destroy(p_root->p_right);
		p_root->p_right= NULL;
	}

	return 0;
}

int avl_tree_show(avl_tree_node_t *p_root)
{
	if(p_root == NULL){
		printf("NULL ");
		return 0;
	}
	printf("%d(%d) ", p_root->val, p_root->depth);
	avl_tree_show(p_root->p_left);
	avl_tree_show(p_root->p_right);
	
	return 0;
}

