#include "stdio.h"
#include "stdlib.h"

void init(int **p,int length);//��ʼ������
int** createmaxtr(int length)//������Ϊlength�ķ��� ����ֵΪint**�͵�ָ��
{
	int **p,i;
	if((p=(int **)malloc(sizeof(int *)*length))==NULL)
	{
        printf("Apply for level 1 pointer memory failure...\n�ڴ�ؼ�����ʧ��1\n");
        exit(0);
    }
    for(i=0;i<length;i++)
        if((*(p+i)=(int *)malloc(sizeof(int)*length))==NULL)
		{
            printf("Application data memory failure...\n�ڴ�ؼ�����ʧ��2\n");
            exit(0);
        }
		//���ó�ʼ������
		init(p,length);
	return p;
}

void incpot(int x,int y,int **p)//����x��y��λ���Լ�1
{
	p[x][y] += 1;
}

void changepot(int x,int y,int value,int **p)//����x��y��λ�õ�ֵ��Ϊvalue
{
	p[x][y] = value;
}

void putpot(int x,int y,int**p) //��ӡ��x��y��λ�õ�ֵ
{
	printf("(%d,%d) is %d\n",x,y,p[x][y]);
}

void initx_y(int **p,int length)
{
	int i;
	//���г�ʼ��
	for(i=0;i<length;i++)
		p[0][i] = i;
	//���г�ʼ��
	for(i=0;i<length;i++)
		p[i][0] = i;
}
void init(int **p,int length)//��ʼ������
{
	int i,j;
	initx_y(p,length);
	//�ڲ���ʼ��
	for(i=1;i<length;i++)
		for(j=1;j<length;j++)
			p[i][j] = 0;
}

void printall(int **p,int length)//��ӡ����ȫ�� 
{
	int i,j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
			printf("%d",p[i][j]);
		printf("\n");
	}
}

void createmaxtrfile(FILE* maxtr,int  **p,int length)//�����ļ�ָ�� ���������maxtr�洢�ļ�
{
	int i,j;
	for(i = 1;i<length;i++)
		for(j = 1;j<length;j++)
			if(p[i][j] != 0)
				fprintf(maxtr," %d %d %d",i,j,p[i][j]);
}

void initmaxtrbyfile(FILE* maxtr,int **p)//�����ļ� ��ʼ�� ����
{
	int i,j,k;
	do{
		//�ļ�ѭ��
		fscanf(maxtr,"%d%d%d",&i,&j,&k);
		p[i][j] = k;
	}while(!feof(maxtr));
}