
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "api.h"

#define TOTAL_BLOCKS 15
#define SIZE 512


void freeList(Memory_t* start)
{
   Memory_t* temp;

   while (start != NULL)
    {
       temp = start;
       start = start->link;
       free(temp);
    }

}

void Check_memory_size(Memory_t *start)
{
	Memory_t *temp;
	temp=start;
	printf("**********************Size fo each memory block is****************************\n");
	while(temp != NULL)
	{
		printf("Each_block_size=%ld\n",malloc_usable_size(temp));
		temp=temp->link;
	}
	printf("******************************************************************************\n");
}

Memory_t *add_at_beg(Memory_t *fstart)
{
	Memory_t *fp,*ftemp;
	fp=fstart;
	ftemp=(Memory_t*)malloc(sizeof(Memory_t)+SIZE);
	ftemp->link=fp;
	fp=ftemp;
	return fstart;
}

Memory_t *create_node(Memory_t *fstart)
{
    Memory_t *fp;
    fp=(Memory_t*)malloc(SIZE+sizeof(Memory_t));
	fstart=add_at_beg(fp);
    return fstart;
}

Memory_t *add_at_end(Memory_t *fstart)
{
	Memory_t *fp,*ftemp=fstart;
	fp=(Memory_t*)malloc(SIZE+sizeof(Memory_t));
	while(ftemp->link != NULL)
	{
		ftemp=ftemp->link;
	}
	
	fp->link=ftemp->link;
	ftemp->link=fp;
	fstart=ftemp;
	//free(fp);
	return fstart;
}

Memory_t *My_alloc(Memory_t *fstart,Memory_t *ustart,int blocks_request)
{
    Memory_t *fp,*ftemp,*up,*utemp,*extra;
    fp=fstart;
    up=ustart;
    int i,count=15;
    printf("Last address of free memory:%p \nUsable address:%p  count=%d\n",fp,ustart,count);
    for(i=1;i<count-blocks_request;i++)
        fp=fp->link;
    
    ftemp=fp;
    extra=ftemp;
    utemp=ustart;
    
    while(extra != NULL)
    {
        extra=extra->link;
        utemp->link=extra;
        utemp=utemp->link;
    }
    fp->link=NULL;
    return ustart;
}

Memory_t *My_free(Memory_t *fstart,Memory_t *ustart,int blocks_free,int total_block_used)
{
    Memory_t *fp,*ftemp,*up,*utemp,*extra;
    fp=fstart;
    up=ustart;
    int i;
    for(i=1;i<=(TOTAL_BLOCKS-total_block_used)-1;i++)
        fp=fp->link;
    printf("Address of block=%p\n",up);  
    utemp=up;
    extra=utemp;
    ftemp=fp;
    
    for(i=0;i<blocks_free;i++)
    {

        extra=extra->link;
        extra->Data=0;
        ftemp->link=extra;
        ftemp=ftemp->link;
        if(i==blocks_free-1)
        {
        	extra=extra->link;
        	utemp->link=extra;
        	ftemp->link=NULL;
        	break;
        }

    }
    
    return fstart;
}





void My_Print_free(Memory_t *fstart,Memory_t *ustart)
{
	Memory_t *fp,*up;
	fp=fstart;
	up=ustart;

	int count=0;
	printf("Free_Aemory_Address: \t\t\t\t\t Usable_Memory_Addresses:\n");
	while((fp != NULL))
	{
	    ++count;
	    if(up != NULL)
		{
			printf("Address_%d=%p \t data=%d \t\t\t Address_%d=%p \t data=%d \n",count,fp,fp->Data,count,up,up->Data);
			up=up->link;
		}
		else
		{
			printf("Address_%d=%p \t data=%d \n",count,fp,fp->Data);
		}		
		fp=fp->link;
		
	}

}

void My_deinit(Memory_t *fstart,Memory_t *ustart)
{
	freeList(fstart);
	freeList(ustart);
	printf("De-Initialization of Memory is Done\n");

}


Memory_t *My_Init(Memory_t *fstart)
{
	Memory_t *fp,*ftemp;
	Memory_t *up,*utemp;
	int i;
	fp=fstart;
	fstart=create_node(fp);
	ftemp=fstart;
	for(i=1;i<TOTAL_BLOCKS;i++)
	{
	   ftemp=add_at_end(ftemp);
	}
	Check_memory_size(fstart);
	return fstart;
	
}