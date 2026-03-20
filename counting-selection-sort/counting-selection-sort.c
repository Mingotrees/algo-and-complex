#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}List;

void swap(int*, int*);
void countingSort(List*);
void selectionSort(List*);
int findRange(List* arr);

int main(){
    List org = {{70, 72, 73, 75, 77, 79, 80}, 7};
    // selectionSort(&org);
    countingSort(&org);
    for(int i = 0; i < org.count; i++){
        printf("%d ", org.data[i]);
    }
    
    return 0;
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;    
}


//ascending
void countingSort(List* arr){
    int min, max;
    min = max = arr->data[0];
    for(int i = 1; i < arr->count; i++){
        min = arr->data[i] < min ? arr->data[i] : min;
        max = arr->data[i] > max ? arr->data[i] : max;
    }
    int range = max - min + 1;

    int* countingArr = (int*)calloc(range, sizeof(int));
    int* outputArr = (int*)malloc(sizeof(int)*arr->count);
    
    //count
    for(int i = 0; i < arr->count; i++){
        int index = arr->data[i] - min;
        countingArr[index] += 1;
    }

    //cumulative sum
    //ascending
    // for(int i = 1; i < range; i++){
    //     countingArr[i] += countingArr[i-1];
    // }

    //descending
    for(int i = range - 1; i > 0; i--){
        countingArr[i-1] += countingArr[i];
    }

    //put in place
    for(int i = arr->count - 1; i >= 0; i--){
        int index = arr->data[i] - min;
        outputArr[--countingArr[index]] = arr->data[i];
    }

    memcpy(arr->data, outputArr, sizeof(int)*arr->count);
    free(countingArr);
    free(outputArr);
}

int findRange(List* arr){
    
}

void selectionSort(List* arr){
    for(int i = 0; i < arr->count - 1; i++){
        int smallNdx = i;
        for(int j = smallNdx + 1;  j < arr->count; j++){
            if(arr->data[smallNdx] > arr->data[j]){
                smallNdx = j;
            }
        }
        if(smallNdx != i) swap(arr->data + smallNdx, arr->data + i);
    }
}