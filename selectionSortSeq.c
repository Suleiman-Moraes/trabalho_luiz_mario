#include <stdio.h>
#include <stdlib.h>
#include "time.h"

void swap(int* a, int* b);
void selectionSort(int* A, int n);

int main(){

	int number, iter =0;
	int* Arr;
	
	
	printf("Defina o tamanho do vetor: ");
	scanf("%d", &number);
	
	srand(time(NULL));
	
	Arr = (int *)malloc( number * sizeof(int));
	

	for(int iter=0; iter<number; iter++){
		Arr[iter] = rand() % 100;
	}
	
	printf("\nVetor nao-ordenado:\n");
	for(int iter=0; iter<number; iter++){
		printf("%d | ", Arr[iter]);
	}
	
	selectionSort(Arr, number);
	
	printf("\n\nVetor ordenado:\n");
	for(int iter=0; iter<number; iter++){
		printf("%d | ", Arr[iter]);
	}

	return 0;
}

void selectionSort(int* A, int n){

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

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}