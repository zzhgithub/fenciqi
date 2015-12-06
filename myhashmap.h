#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymaxtr.h"

typedef struct map
{
	char value[3];//���������ַ� 3���ֽ��� �뱾����ϵͳ�й�
	int key;
	map* next;
}MAP;

bool streq(char *a,char *b);

void add(char* value,int key,map *head)//��һ�����������뵽������
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

void putall(map* head)//��ӡ map�����е�ֵ
{
	head = head->next;//����ͷ�ڵ����
	while(head != NULL)
	{
		printf("%s ",head->value);
		printf("%d ",head->key);
		head = head->next;
	}
}

int findkey(char *value,map* head)//ͨ��value�ҵ�key��ֵ
{
	head = head->next;//����ͷ�ڵ�
	while(head!=NULL)
	{
		if(streq(value,head->value))
			return head->key;
		head = head->next;
	}
	return 0;//0��ʾû���ҵ�
}

bool streq(char *a,char *b)//�Ƚ����������Ƿ����
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

void putinfile(map* head,FILE* fp)//���������ݴ��뵽ָ���ļ���
{
	head = head->next;//����ͷ�ڵ����
	while(head != NULL)
	{
		fputs(head->value,fp);
		head = head->next;
	}
}

void checkfile(map* head,FILE* fp)//����ļ���map�н���ɨ��
{
	char ch[3];
	int i=1,key;
	do{
		fgets(ch,3,fp);
		if(ch[0]<0)//����Ǻ��� ����map��
		{
			key = findkey(ch,head);
			if(key == 0)
			{
				add(ch,i,head);
				i++;
			}else{
				//��д �������
				/*
				ע����Ϊ��ɨ���ļ����֮ǰ�޷�֪������Ĵ�С
				�ͼ���������  һ������indexһ�����ɾ���
				��ʵ�����ǿ��Ե���Ҫ���ڵ��Ż���
				������ʱʲôҲ������
				*/
			}
		}else{
			fseek(fp,-2,SEEK_CUR);//���
			ch[0] = fgetc(fp);
		}
	}while(!feof(fp));
}

int getmaxkey(map* head)//���map��keyֵ����һ��
{
	head = head->next;//����ͷ�ڵ����
	while(head->next != NULL)
		head = head->next;
	return head->key;
}

void freemap(map* head)//�ͷ�map�����Ĵ洢�ռ�
{
	//δ���
}

void fallmaxtr(map* head,FILE* fp,int **p)//ɨ���ļ����ɶ�ά����
{
	char ch[3];
	int key,prokey=0;
	do{
		fgets(ch,3,fp);
		if(ch[0]<0)//����Ǻ��� 
		{
			key = findkey(ch,head);
			incpot(prokey,key,p);
			//putpot(prokey,key,p);//�������ã�
			prokey = key;
		}else{
			fseek(fp,-2,SEEK_CUR);//������Ǻ��� ����
			ch[0] = fgetc(fp);
		}
	}while(!feof(fp));
	//��ʼ������
	initx_y(p,getmaxkey(head)+1);
}