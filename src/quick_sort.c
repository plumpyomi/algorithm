/***************************************************
 *
 *      Filename: quick_sort.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-02-17 17:22:06
 * Last Modified: 2017-02-20 16:55:46
 *
 ***************************************************/

#include "quick_sort.h"
#include "debug.h"
#include "public.h"

static int __partition(MY_TYPE* in, int p, int r)
{
	int i, j, k;

	k = r;
	for(i = p-1, j = p; j < r; ++j){
		if(in[j] <= in[k]){
			++i;
			if(i != j)
				CHANGE_TWO_NODE(in[i], in[j]);
		}
		//print_array(in, 12);
	}
	if(i+1 != k)
		CHANGE_TWO_NODE(in[i+1], in[k]);

	return i+1;
}

static void __quick_sort(MY_TYPE* in, int p, int r)
{
	if(p < r){
		int q;

		q = __partition(in, p, r);
		__quick_sort(in, p, q-1);
		__quick_sort(in, q+1, r);
	}
}

int quick_sort(MY_TYPE* in, int len)
{
	print_array(in, len);
	__quick_sort(in, 0, len-1);
	print_array(in, len);

	return 0;
}

