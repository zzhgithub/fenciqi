#include <stdio.h>
#include <stdlib.h>
#include "myhashmap.h"


int main()
{
	int **p;
	MAP *head;
	FILE *index,*maxtr;
	head = (map*)malloc(sizeof(MAP));
	head->next = NULL;//此处必须 为空
	if((index = fopen("index","r")) == NULL)
	{
		printf("can not find the file index!\n这是第一次生成index文件\n");
		exit(0);
	} 
	else
	{
		checkfile(head,index);
		fclose(index);
	}
	p = createmaxtr(getmaxkey(head)+1);
	if((maxtr = fopen("maxtr","r")) == NULL)
	{
		printf("对不起 maxtr（矩阵）文件不存在！\n");
		exit(0);
	}else{	
		initmaxtrbyfile(maxtr,p);
	}
	printall(p,100);
    delete []p;
    printf("\n");
	return 0;
}