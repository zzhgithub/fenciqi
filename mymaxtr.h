#include "stdio.h"
#include "stdlib.h"

void init(int **p,int length);//初始化矩阵
int** createmaxtr(int length)//创建长为length的方阵 返回值为int**型的指针
{
	int **p,i;
	if((p=(int **)malloc(sizeof(int *)*length))==NULL)
	{
        printf("Apply for level 1 pointer memory failure...\n内存控件不足失败1\n");
        exit(0);
    }
    for(i=0;i<length;i++)
        if((*(p+i)=(int *)malloc(sizeof(int)*length))==NULL)
		{
            printf("Application data memory failure...\n内存控件不足失败2\n");
            exit(0);
        }
		//调用初始化函数
		init(p,length);
	return p;
}

void incpot(int x,int y,int **p)//矩阵（x，y）位置自加1
{
	p[x][y] += 1;
}

void changepot(int x,int y,int value,int **p)//矩阵（x，y）位置的值改为value
{
	p[x][y] = value;
}

void putpot(int x,int y,int**p) //打印（x，y）位置的值
{
	printf("(%d,%d) is %d\n",x,y,p[x][y]);
}

void initx_y(int **p,int length)
{
	int i;
	//横行初始化
	for(i=0;i<length;i++)
		p[0][i] = i;
	//纵行初始化
	for(i=0;i<length;i++)
		p[i][0] = i;
}
void init(int **p,int length)//初始化矩阵
{
	int i,j;
	initx_y(p,length);
	//内部初始化
	for(i=1;i<length;i++)
		for(j=1;j<length;j++)
			p[i][j] = 0;
}

void printall(int **p,int length)//打印矩阵全部 
{
	int i,j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
			printf("%d",p[i][j]);
		printf("\n");
	}
}

void createmaxtrfile(FILE* maxtr,int  **p,int length)//根据文件指针 与矩阵生成maxtr存储文件
{
	int i,j;
	for(i = 1;i<length;i++)
		for(j = 1;j<length;j++)
			if(p[i][j] != 0)
				fprintf(maxtr," %d %d %d",i,j,p[i][j]);
}

void initmaxtrbyfile(FILE* maxtr,int **p)//根据文件 初始化 矩阵
{
	int i,j,k;
	do{
		//文件循环
		fscanf(maxtr,"%d%d%d",&i,&j,&k);
		p[i][j] = k;
	}while(!feof(maxtr));
}