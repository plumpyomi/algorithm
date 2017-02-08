/***************************************************
 *
 *      Filename: heap_sort.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-02-03 19:39:06
 * Last Modified: 2017-02-08 09:36:30
 *
 ***************************************************/

#include "heap_sort.h"
#include "debug.h"

#define CHANGE_TWO_NODE(x, y) do{(x)^=(y);(y)^=(x);(x)^=(y);}while(0)

static int _exchange_with_left(MY_TYPE* in, int node, int len)
{
	int left;

	left = node*2+1;
	if(left >= len)
		return -1;

	if(in[node] < in[left]){
		CHANGE_TWO_NODE(in[node], in[left]);
		return 0;
	}

	return 1;
}

static int _exchange_with_right(MY_TYPE* in, int node, int len)
{
	int right;

	right = node*2+2;
	if(right >= len)
		return -1;

	if(in[node] < in[right]){
		CHANGE_TWO_NODE(in[node], in[right]);
		return 0;
	}

	return 1;
}

static int _re_adjust_heap(MY_TYPE* in, int pos, int len)
{
	if(len <= 2)
		return -1;

	while(pos < len){
		int left, right;

		left = pos*2+1;
		right= pos*2+2;
		if(left >= len)
			break;
		if(right >= len && in[pos]<in[left]){
			_exchange_with_left(in, pos, len);
			break;
		}
		if(in[pos] > in[left] && in[pos] > in[right])
			break;
		if(in[left] > in[pos] && in[left] > in[right]){
			_exchange_with_left(in, pos, len);
			pos = left;
			continue;
		}
		if(in[right] > in[pos] && in[right] > in[left]){
			_exchange_with_right(in, pos, len);
			pos = right;
			continue;
		}
	}
}

static int _create_max_heap(MY_TYPE* in, int len)
{
	int t_node;

	if(len%2 == 0)
		t_node = (len-1)/2;
	else
		t_node = (len-2)/2;

	while(t_node >= 0){
		_re_adjust_heap(in, t_node, len);
		t_node--;
		//print_array(in, len);
	}

	return 0;
}

int heap_sort(MY_TYPE* in, int len)
{
	int pos;

	print_array(in, len);
	_create_max_heap(in, len);
	print_array(in, len);
	pos = len-1;
	while(pos > 1){
		//printf("pos = %d\r\n", pos);
		CHANGE_TWO_NODE(in[0], in[pos]);
		_re_adjust_heap(in, 0, pos);
		pos--;
	}
	if(in[0] > in[1])
		CHANGE_TWO_NODE(in[0], in[1]);
	print_array(in, len);

	return 0;
}

