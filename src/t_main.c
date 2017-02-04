/***************************************************
 *
 *      Filename: t_main.c
 *
 *        Author: ZhiChao Dong - mars_don@163.com
 *   Description: ---
 *        Create: 2017-01-11 21:49:09
 * Last Modified: 2017-02-04 17:11:47
 *
 ***************************************************/
#include<stdlib.h>
#include<time.h>

#include "dc_sort.h"
#include "heap_sort.h"

#define TEST_LEN	12

int main(int argc, char* argv[])
{
	int t_a[TEST_LEN];
	int len = TEST_LEN;

	srand(time(0));
	
	for(int i=0; i<TEST_LEN; ++i)
		t_a[i] = rand()%1000;

	//dc_sort(t_a, len);
	heap_sort(t_a, len);

	return 0;
}

