#include <stdio.h>
#include <string.h>

typedef struct
{
	int check;
}insert;

int main()
{
	insert t1={10};
	insert t2={20};
	printf("t1.check=%d\tt2.check=%d\n",t1.check,t2.check);
	
	memcpy(&t1,&t2,sizeof(insert));
	
	printf("t1.ckeck=%d \t t2.check=%d\n",t1.check,t2.check);
	return 0;
}
