#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i,j;
	int dimension;
	double **array,**deterArray, **companionMatrix, *temp;

	printf("请输入方阵的阶数N:");
	scanf("%d",&dimension);
	
	array=(double**)malloc(dimension*sizeof(double*));
	deterArray=(double**)malloc(dimension*sizeof(double*));
	companionMatrix =(double**)malloc(dimension*sizeof(double*));
	
	//循环输入方阵
	for(i=0;i<dimension;i++)
	{
		temp=(double*)malloc(dimension*sizeof(double));
		deterArray[i]=(double*)malloc(dimension*sizeof(double));
		companionMatrix[i]=(double*)malloc(dimension*sizeof(double));

		printf("请输入方阵的第%d行:",i+1);
		for(j=0;j<dimension;j++)
			scanf("%lf",temp+j);
		array[i]=temp;
	}
	
}

//初等行变换
void primaryRowChange(int s, int n, double **array)
{
	int i,j,k,ii,kk,flag;
	double temp;
	for(i=0,j=0;i<s-1;i++,j++)//s行，最外围只需要变换s-1
	{
		
		ii=i;
		//如果行的首元为0，向下查找一个不为0的，然后换行
		if(*(*(array+i)+j) == 0)
		{
			flag=0;
			for(k=i+1;k<s;k++)
			{
				if(*(*(array+k)+j)!=0)//第k行与第i行交换
				{
					for(kk=j;kk<n;kk++)
					{	
						temp=*(*(array+k)+kk);
						*(*(array+k)+kk) = *(*(array+i)+kk);
						*(*(array+i)+kk) = temp;
					}			
					flag =1;
					break;
				}
			}		
			//判断是交换成功，如果没有成功，则i--
			if(!flag)
			{				
				i--;
				continue;
			}
			i--;
			j--;
			continue;
		}
		for(;ii<s-1;ii++)
		{
			if(*(*(array+ii+1)+j)==0)
				continue;
			temp =-*(*(array+ii+1)+j) / *(*(array+i)+j);
			for(k=j;k<n;k++)
				*(*(array+ii+1)+k) += *(*(array+i)+k) * temp;
				
		}
	}
}
