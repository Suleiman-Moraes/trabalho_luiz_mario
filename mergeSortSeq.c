#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int a[],int i,int j);
void mergesortX(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);
void mergeX(int a[],int i1,int j1,int i2,int j2);

int main()
{
    int num = 500;
	while(num <= 4000000){
		num = num * 2;
		int *a, *b, i;

		a = (int *)malloc(sizeof(int) * num);
		b = (int *)malloc(sizeof(int) * num);
		for(i=0; i<num; i++){
			int dd = rand() % 100;
			a[i] = dd;
			b[i] = dd;
		}
			
		clock_t Ticks[2];
		Ticks[0] = clock();	
		
		mergesort(a, 0, num-1);
		
		Ticks[1] = clock();
		double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
		printf("\nCom Paralelismo %d elements => %g ms.", num, Tempo);
		getchar();
		
		clock_t Ticks2[2];
		Ticks2[0] = clock();
		
		mergesortX(b, 0, num-1);
		
		Ticks2[1] = clock();
		double Tempo2 = (Ticks2[1] - Ticks2[0]) * 1000.0 / CLOCKS_PER_SEC;
		printf("\nSem paralelismo %d elements => %g ms.", num, Tempo2);
		getchar();
	}
        
    return 0;
}
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,i,mid);        //left recursion
 		mergesort(a,mid+1,j);    //right recursion
        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
} 

void mergesortX(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        mergesortX(a,i,mid);        //left recursion
 		mergesortX(a,mid+1,j);    //right recursion
        mergeX(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
	#pragma omp parallel num_threads(4)
	{
		int temp[j2 + 1];    //array used for merging
		int i,j,k;
		i=i1;    //beginning of the first list
		j=i2;    //beginning of the second list
		k=0;
		
		while(i<=j1 && j<=j2)    //while elements in both lists
		{
			if(a[i]<a[j])
				temp[k++]=a[i++];
			else
				temp[k++]=a[j++];
		}
		
		while(i<=j1)    //copy remaining elements of the first list
			temp[k++]=a[i++];
		
		while(j<=j2)    //copy remaining elements of the second list
			temp[k++]=a[j++];
			
		for(i=i1,j=0;i<=j2;i++,j++)
			a[i]=temp[j];
	}
}

void mergeX(int a[],int i1,int j1,int i2,int j2)
{
    int temp[j2 + 1];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}