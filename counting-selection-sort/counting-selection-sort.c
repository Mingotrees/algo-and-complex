#include <stdio.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}List;

void swap(int*, int*);
void countingSort(List*);
void selectionSort(List*);

int main(){

    return 0;
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;    
}

void countingSort(List*);
void selectionSort(List*);