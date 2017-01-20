/***************************************************
 *
 *      Filename: dc.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2016-12-27 02:38:23
 * Last Modified: 2017-01-18 22:50:50
 *
 ***************************************************/
#include <string.h>

#include "dc_sort.h"
#include "debug.h"

static void _merge(MY_TYPE *a, int n, MY_TYPE *b, int m, MY_TYPE *c)
{
	int i, j, k;

	i = j = k = 0;
	while(i < n && j < m){
		if(a[i] < b[j]){
			c[k++] = a[i++];
		}else{
			c[k++] = b[j++];
		}
	}
	while(i < n){
		c[k++] = a[i++];
	}
	while(j < m){
		c[k++] = b[j++];
	}
}

static int _dc_sort(MY_TYPE *in, int len, MY_TYPE* out)
{
	MY_TYPE *pa, *pb;
	MY_TYPE *pc;
	int len1, len2;

	if(len <= 1)
		return 0;

	pa = in;
	pb = &(in[len/2]);
	pc = out;
	len1 = len/2;
	len2 = len-len/2;

	_dc_sort(pa, len/2, out);
	_dc_sort(pb, len-len/2, out);
	_merge(pa, len/2, pb, len-len/2, out);

	memcpy((char*)in, (char*)pc, len*sizeof(MY_TYPE));

	return 0;
}

int dc_sort(MY_TYPE* in, int len)
{
	MY_TYPE *out;

	out = (MY_TYPE*)malloc(len*sizeof(MY_TYPE));

	print_array(in, len);
	_dc_sort(in, len, out);
	print_array(in, len);

	free(out);

	return 0;
}

