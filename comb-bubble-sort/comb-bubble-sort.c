#include <stdio.h>
#define MAX 10
#define SHRINK_FACTOR 1.3
#include <stdbool.h>


typedef struct{
    int data[MAX];
    int count;
}List;

void swap(int*, int*);
void bubbleSort(List *);
void combSort(List *);

int main(){
    List org = {{10,9,2,6,4,1,2,3}, 8};
    bubbleSort(&org);
    // combSort(&org);
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

void combSort(List* arr){
    int gap = arr->count/SHRINK_FACTOR;
    bool isSwapped = true;
    for(; gap >= 1 || isSwapped; gap /= SHRINK_FACTOR){
        if(gap < 1) gap = 1;
        int j;
        isSwapped = false;
        for(j = 0; j + gap < arr->count; j++){
            if(arr->data[j] > arr->data[j+gap]){
                swap(arr->data + j, arr->data + (j + gap));
                isSwapped = true;
            }
        }
    }
}

void bubbleSort(List* arr){
    bool isSwapped = true;
    for(int i = 0; i < arr->count - 1;  i++){
        bool isSwapped = false;
        for(int j = 0; j < arr->count - i - 1; j++){
            if(arr->data[j] > arr->data[j+1]){
                swap(&arr->data[j], &arr->data[j+1]);
                isSwapped = true;
            }
        }
    }
}