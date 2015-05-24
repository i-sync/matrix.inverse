#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i,j,k,l,m,n,o;
	int dimension;
	int flag;//标志代数余子式的符号
	double deterValue;
	double **array,**companionMatrix,*temp;
	
	//声明函数
	void printfDouble2Dimension(int s, int n, double **array);
	double deter(int dimension, double **array);

	printf("请输入方阵的阶数N:");
	scanf("%d",&dimension);

	array=(double**)malloc(dimension*sizeof(double*));
	companionMatrix =(double**)malloc((dimension-1)*sizeof(double*));
	//循环输入方阵
	for(i=0;i<dimension;i++)
	{
		temp=(double*)malloc(dimension*sizeof(double));
		printf("请输入方阵的第%d行",i+1);
		for(j=0;j<dimension;j++)
			scanf("%lf",temp+j);
		array[i]=temp;
	}
	//打印方阵
	printf("方阵如下:\n");
	printfDouble2Dimension(dimension,dimension,array);
	
	deterValue = deter(dimension,array);
	if(deterValue==0)
	{
		printf("方阵行列式值为零.\n");
		return ;
	}		
	printf("行列式的值:%lf",deterValue);
	
	//求伴随矩阵
	for(i=0;i<dimension;i++)
	{
		for(j=0;j<dimension;j++)
		{
			flag=(i+j)%2==0?1:-1;
			for(k=0,m=0;k<dimension;k++)
			{
				if(k==i)continue;
	                        temp=(double*)malloc((dimension-1)*sizeof(double));

				for(l=0,n=0;l<dimension;l++)
				{
					if(l==j)continue;
					*(temp+n)=*(*(array+k)+l);
					n++;	
				}
				for(o=0;o<dimension-1;o++)
					*(*(companionMatrix+o)+m)=*(temp+m);	
				m++;
			}
			printfDouble2Dimension(dimension-1,dimension-1,companionMatrix);
		}
	}
}

/*
 * calculate the determinant value
 */
double deter(int dimension,double **array)
{
	int i,j,k,l,b;
	int flag =1;
	double sum=1;
	double temp;
	for(i=0,j;i<dimension-1;i++)
	{
		j=i;
		if(array[i][j]==0)
		{
			b=0;
			for(k=i+1;k<dimension;k++)
			{
				if(array[k][j]!=0)//找到一行不为0的,然后换行 
				{
					for(l=j;l<dimension;l++)
					{
						temp=array[k][l];
						array[k][l]=array[i][l];
						array[i][l]=temp;
					}
					flag*=-1;
					b=1;
					break;
				}
			}
			if(!b)
			{
				return 0;
			}
			i--;
			continue;
		}
		for(;j<dimension-1;j++)
		{
			if(array[j+1][i]==0) 
				continue;
			temp = -array[j+1][i]/array[i][i];
			for(k=i;k<dimension;k++)
				array[j+1][k]+=array[i][k]*temp;
		}
	}
	
	for(i=0;i<dimension;i++)
		sum*=array[i][i];
	return sum*flag;
}

//打印数组
void printfDouble2Dimension(int s, int n, double **array)
{
	//printf("%d,%d",s,n);
	int i,j;
	for(i=0;i<s;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%6.2lf",*(*(array+i)+j));	
		}
		printf("\n");
	}
}
