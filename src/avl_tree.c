/***************************************************
 *
 *      Filename: src/avl_tree.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-03-02 11:43:15
 * Last Modified: 2017-03-14 17:05:38
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

static rotate_type_t __check_avl_tree_rotate(avl_tree_node_t *p_node, int l_depth, int r_depth)
{
	int t_ld, t_rd;

	if(l_depth == 2 && r_depth == 0){
		__get_avl_lr_depth(p_node->p_left, &t_ld, &t_rd);
		if(t_ld == 1 && t_rd == 0)
			return L_ROTATE;
		if(t_ld == 0 && t_rd == 1)
			return R_L_ROTATE;
	}
	if(l_depth == 0 && r_depth == 2){
		__get_avl_lr_depth(p_node->p_right, &t_ld, &t_rd);
		if(t_ld == 0 && t_rd == 1)
			return R_ROTATE;
		if(t_ld == 1 && t_rd == 0)
			return L_R_ROTATE;
	}
	if(l_depth == 3 && r_depth == 1){
		__get_avl_lr_depth(p_node->p_left, &t_ld, &t_rd);
		if(t_ld == 2 && t_rd == 1)
			return L_ROTATE;
		if(t_ld == 1 && t_rd == 2)
			return R_L_ROTATE;
	}
	if(l_depth == 1 && r_depth == 3){
		__get_avl_lr_depth(p_node->p_right, &t_ld, &t_rd);
		if(t_ld == 1 && t_rd == 2)
			return R_ROTATE;
		if(t_ld == 2 && t_rd == 1)
			return L_R_ROTATE;
	}

	return UNDEFINED;
}

static avl_tree_node_t* __left_rotate(avl_tree_node_t *p_node)
{
	avl_tree_node_t* p_root;

	if(p_node == NULL)
		return NULL;

	p_root = p_node;
	p_node = p_root->p_left;
	p_root->p_left = p_node->p_right;
	p_node->p_right = p_root;

	return p_node;
}

static avl_tree_node_t* __right_rotate(avl_tree_node_t *p_node)
{
	avl_tree_node_t* p_root;

	if(p_node == NULL)
		return NULL;

	p_root = p_node;
	p_node = p_root->p_right;
	p_root->p_right = p_node->p_left;
	p_node->p_left = p_root;

	return p_node;
}

static avl_tree_node_t* __avl_tree_rotate(avl_tree_node_t *p_node, rotate_type_t type)
{
	if(p_node == NULL)
		return NULL;
	p_node->depth -= 2;
	switch(type){
		case L_ROTATE:
			p_node = __left_rotate(p_node);
			break;
		case R_ROTATE:
			p_node = __right_rotate(p_node);
			break;
		case R_L_ROTATE:
			p_node->p_left->depth -= 1;
			p_node->p_left->p_right->depth += 1;
			p_node->p_left = __right_rotate(p_node->p_left);
			p_node = __left_rotate(p_node);
			break;
		case L_R_ROTATE:
			p_node->p_right->depth -= 1;
			p_node->p_right->p_left->depth += 1;
			p_node->p_right = __left_rotate(p_node->p_right);
			p_node = __right_rotate(p_node);
			break;
		default:
			p_node->depth += 2;
			break;
	}

	return p_node;
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
		rotate_type_t t_type;

		if(val < p_node->val){
			p_node->p_left = __avl_tree_insert(p_node->p_left, val);
		}else{
			p_node->p_right = __avl_tree_insert(p_node->p_right, val);
		}
		__get_avl_lr_depth(p_node, &l_depth, &r_depth);
		p_node->depth = ((l_depth>r_depth)?l_depth:r_depth)+1;

		t_type = __check_avl_tree_rotate(p_node, l_depth, r_depth);
		if(t_type != UNDEFINED){
			p_node = __avl_tree_rotate(p_node, t_type);
		}
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

