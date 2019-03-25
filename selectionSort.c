#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);
void selectionSort(int* A, int n);
void selectionSortB(int* B, int n);

int main(){

	int number = 500;
	while(number <= 4000000){
		number = number * 2;
		int iter =0;
		int* Arr;
		int* Brr;
		
		
		
		
		int number2 = number;
		
		Arr = (int *)malloc( number * sizeof(int));
		Brr = (int *)malloc( number2 * sizeof(int));
		

		for(int iter=0; iter<number; iter++){
			int dd = rand() % 100;
			Arr[iter] = dd;
			Brr[iter] = dd;
		}
		
		clock_t Ticks[2];
		Ticks[0] = clock();
		
		selectionSort(Arr, number);
		
		Ticks[1] = clock();
		double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
		printf("\nCom Paralelismo %d elements => %g ms.", number, Tempo);
		getchar();
		
		clock_t Ticks2[2];
		Ticks2[0] = clock();
		
		selectionSortB(Brr, number2);
		
		Ticks2[1] = clock();
		double Tempo2 = (Ticks2[1] - Ticks2[0]) * 1000.0 / CLOCKS_PER_SEC;
		printf("\nSem paralelismo %d elements => %g ms.", number, Tempo2);
		getchar();
	}
	
	printf("\n\n Fim dos paranauê.");

	return 0;
}

void selectionSort(int* A, int n){

	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for(int startpos =0; startpos < n; startpos++){
			int maxpos = startpos;
			for(int i=startpos +1; i< n; ++i){
				if(A[i] < A[maxpos]){
					maxpos = i;
				}
			}
			swap(&A[startpos], &A[maxpos]);
		}
	}
}

void selectionSortB(int* B, int n){

	for(int startpos =0; startpos < n; startpos++){
		int maxpos = startpos;
		for(int i=startpos +1; i< n; ++i){
			if(B[i] < B[maxpos]){
				maxpos = i;
			}
		}
		swap(&B[startpos], &B[maxpos]);
	}
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}