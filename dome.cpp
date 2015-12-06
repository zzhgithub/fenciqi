#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myhashmap.h"

/*
执行逻辑顺序：
先读取之前的index文件到map中
在加载新的语料文件test
保存新的index文件
*/

int main()
{
	FILE *fp,*index,*maxtr;
	MAP *head;
	int max=0,**p;
	head = (map*)malloc(sizeof(MAP));
	head->next = NULL;//此处必须 为空
	//先读取之前的index文件到map中
	if((index = fopen("index","r")) == NULL)
	{
		printf("can not find the file index!\n这是第一次生成index文件\n");
	} 
	else
	{
		checkfile(head,index);
		fclose(index);
		max = getmaxkey(head);
	}
	//在加载新的语料文件test
	if((fp = fopen("test","r")) == NULL)
	{
		printf("can not find the file test!\n找不到您需要的语料！\n");
		exit(0);
	}
	checkfile(head,fp);
	//fclose(fp);
	//保存新的index文件     此处保存的可以优化ok
	if(getmaxkey(head) > max)
	{
		index = fopen("index","w");
		putinfile(head,index);
		fclose(index);
	}
	else
	{
		printf("\n本次并未使index得到更新！\n");
	}
	putall(head);
	//此时要初始文件指针（其实可以用指令移到文件开头）
	fseek(fp,0,SEEK_SET);
	p = createmaxtr(getmaxkey(head)+1);//得到的key是比总共个数多一！！！
	fallmaxtr(head,fp,p);//生成矩阵完成
	//maxtr文件打开
	if((maxtr = fopen("maxtr","w")) == NULL)
	{
		printf("this is the frist time create maxtr file!\n这是您第一次生成矩阵文件\n");
	}
	createmaxtrfile(maxtr,p,getmaxkey(head)+1);
	printf("\n");
	printall(p,100);
	fclose(fp);
	return 0;
}