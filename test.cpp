#include <stdio.h>
#include <stdlib.h>
#include "myhashmap.h"


int main()
{
	int **p;
	MAP *head;
	FILE *index,*maxtr;
	head = (map*)malloc(sizeof(MAP));
	head->next = NULL;//�˴����� Ϊ��
	if((index = fopen("index","r")) == NULL)
	{
		printf("can not find the file index!\n���ǵ�һ������index�ļ�\n");
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
		printf("�Բ��� maxtr�������ļ������ڣ�\n");
		exit(0);
	}else{	
		initmaxtrbyfile(maxtr,p);
	}
	printall(p,100);
    delete []p;
    printf("\n");
	return 0;
}