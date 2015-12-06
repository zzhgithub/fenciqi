#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymaxtr.h"

typedef struct map
{
	char value[3];//储存中文字符 3个字节是 与本操作系统有关
	int key;
	map* next;
}MAP;

bool streq(char *a,char *b);

void add(char* value,int key,map *head)//将一组新索引加入到链表中
{
	map* tmp;
	tmp = (map*)malloc(sizeof(MAP));
	tmp->next = NULL;
	//tp = head;
	while(head->next != NULL)
		head = head->next;
	strcpy(tmp->value,value);
	tmp->key = key;
	head->next=tmp;

}

void putall(map* head)//打印 map中所有的值
{
	head = head->next;//跳过头节点进行
	while(head != NULL)
	{
		printf("%s ",head->value);
		printf("%d ",head->key);
		head = head->next;
	}
}

int findkey(char *value,map* head)//通过value找到key的值
{
	head = head->next;//跳过头节点
	while(head!=NULL)
	{
		if(streq(value,head->value))
			return head->key;
		head = head->next;
	}
	return 0;//0表示没有找到
}

bool streq(char *a,char *b)//比较两个汉字是否相等
{
	int i=0;
	while(a[i]!=NULL)
	{
		if(a[i] != b[i])
			return false;
		i++;
	}
	return true;
}

void putinfile(map* head,FILE* fp)//将所有内容存入到指定文件内
{
	head = head->next;//跳过头节点进行
	while(head != NULL)
	{
		fputs(head->value,fp);
		head = head->next;
	}
}

void checkfile(map* head,FILE* fp)//添加文件到map中进行扫描
{
	char ch[3];
	int i=1,key;
	do{
		fgets(ch,3,fp);
		if(ch[0]<0)//如果是汉字 存入map中
		{
			key = findkey(ch,head);
			if(key == 0)
			{
				add(ch,i,head);
				i++;
			}else{
				//填写 矩阵代码
				/*
				注：因为在扫描文件完毕之前无法知道矩阵的大小
				就几乎做不到  一边生成index一边生成矩阵
				（实际上是可以的需要后期的优化）
				这里暂时什么也不做。
				*/
			}
		}else{
			fseek(fp,-2,SEEK_CUR);//如果
			ch[0] = fgetc(fp);
		}
	}while(!feof(fp));
}

int getmaxkey(map* head)//获得map中key值最大的一个
{
	head = head->next;//跳过头节点进行
	while(head->next != NULL)
		head = head->next;
	return head->key;
}

void freemap(map* head)//释放map带来的存储空间
{
	//未完成
}

void fallmaxtr(map* head,FILE* fp,int **p)//扫面文件生成二维矩阵
{
	char ch[3];
	int key,prokey=0;
	do{
		fgets(ch,3,fp);
		if(ch[0]<0)//如果是汉字 
		{
			key = findkey(ch,head);
			incpot(prokey,key,p);
			//putpot(prokey,key,p);//（测试用）
			prokey = key;
		}else{
			fseek(fp,-2,SEEK_CUR);//如果不是汉字 忽略
			ch[0] = fgetc(fp);
		}
	}while(!feof(fp));
	//初始坐标轴
	initx_y(p,getmaxkey(head)+1);
}