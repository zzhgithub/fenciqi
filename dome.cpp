#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myhashmap.h"

/*
ִ���߼�˳��
�ȶ�ȡ֮ǰ��index�ļ���map��
�ڼ����µ������ļ�test
�����µ�index�ļ�
*/

int main()
{
	FILE *fp,*index,*maxtr;
	MAP *head;
	int max=0,**p;
	head = (map*)malloc(sizeof(MAP));
	head->next = NULL;//�˴����� Ϊ��
	//�ȶ�ȡ֮ǰ��index�ļ���map��
	if((index = fopen("index","r")) == NULL)
	{
		printf("can not find the file index!\n���ǵ�һ������index�ļ�\n");
	} 
	else
	{
		checkfile(head,index);
		fclose(index);
		max = getmaxkey(head);
	}
	//�ڼ����µ������ļ�test
	if((fp = fopen("test","r")) == NULL)
	{
		printf("can not find the file test!\n�Ҳ�������Ҫ�����ϣ�\n");
		exit(0);
	}
	checkfile(head,fp);
	//fclose(fp);
	//�����µ�index�ļ�     �˴�����Ŀ����Ż�ok
	if(getmaxkey(head) > max)
	{
		index = fopen("index","w");
		putinfile(head,index);
		fclose(index);
	}
	else
	{
		printf("\n���β�δʹindex�õ����£�\n");
	}
	putall(head);
	//��ʱҪ��ʼ�ļ�ָ�루��ʵ������ָ���Ƶ��ļ���ͷ��
	fseek(fp,0,SEEK_SET);
	p = createmaxtr(getmaxkey(head)+1);//�õ���key�Ǳ��ܹ�������һ������
	fallmaxtr(head,fp,p);//���ɾ������
	//maxtr�ļ���
	if((maxtr = fopen("maxtr","w")) == NULL)
	{
		printf("this is the frist time create maxtr file!\n��������һ�����ɾ����ļ�\n");
	}
	createmaxtrfile(maxtr,p,getmaxkey(head)+1);
	printf("\n");
	printall(p,100);
	fclose(fp);
	return 0;
}