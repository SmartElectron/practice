#include <stdio.h>
#include "api.h"



int main()
{
	Memory_t *fstart=NULL,*ftemp;
	Memory_t *ustart=NULL,*utemp;
	utemp=ustart;
	ustart=(Memory_t*)create_node(utemp);//atleastt one node we want to allocation another block of memory
	
	ftemp=fstart;
	fstart=(Memory_t*)My_Init(ftemp);
	My_Print_free(fstart,ustart);
	printf("All node address of free meory:\n");
	ustart=(Memory_t*)My_alloc(fstart,ustart,7);
	My_Print_free(fstart,ustart);
	printf("*************************FREE MEMORY AFTER FREE FROM USABLE LIST********************************\n");
	fstart=(Memory_t*)My_free(fstart,ustart,2,7);
	My_Print_free(fstart,ustart);
	My_deinit(fstart,ustart);

	return 0;

}