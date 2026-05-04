#include <stdio.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}List;

void shellSort(List* data);
void swap(int* x, int* y);
void insertionSort(List* arr);

int main(){
    List org = {{10,9,2,6,4,1,2}, 7};
    insertionSort(&org);
    // shellSort(&org);
    for(int i = 0; i < org.count; i++){
        printf("%d ", org.data[i]);
    }
    
    return 0;
}

void shellSort(List* arr){
    int gap = arr->count/2, idx;
    for(;gap >= 1; gap /= 2){
        for(idx = gap; idx < arr->count; idx++){
            int temp = arr->data[idx], j;
            for(j = idx ;j >= gap && arr->data[j-gap] > temp; j -= gap){
                arr->data[j] = arr->data[j-gap];
            }
            arr->data[j] = temp;
        }
    }
}

void insertionSort(List* arr){
    int i, j, temp;
    for(i = 1; i < arr->count; i++){
        temp = arr->data[i];
        for(j = i; j > 0 && arr->data[j - 1] > temp; j--){
            arr->data[j] = arr->data[j-1];
        } 
        arr->data[j] = temp;
    }
}


void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}