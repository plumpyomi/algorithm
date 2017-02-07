/***************************************************
 *
 *      Filename: debug.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-01-11 22:30:12
 * Last Modified: 2017-01-18 22:40:05
 *
 ***************************************************/

#include <stdio.h>
#include "m_type.h"

void print_array(MY_TYPE* pa, int len)
{
    int i;

	for(i=0; i < len; ++i)
		printf("%d ", pa[i]);
	printf("\r\n");
}

