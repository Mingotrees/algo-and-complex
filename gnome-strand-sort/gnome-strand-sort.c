#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}List;

void gnomeSort(List*);
void swap(int*, int*);
void strandSort(List* arr);
void merge(List* L1, List* L2);

int main(){
    List org = {{10,9,2,6,4,1,2}, 7};
    // gnomeSort(&org);
    strandSort(&org);
    for(int i = 0; i < org.count; i++){
        printf("%d ", org.data[i]);
    }
    
    return 0;
}

void gnomeSort(List* arr){
    int pos = 0;
    while(pos < arr->count){
        if(pos == 0 || arr->data[pos] >= arr->data[pos-1]){
            pos++;
        }else{
            int temp = arr->data[pos];
            arr->data[pos] = arr->data[pos-1];
            arr->data[pos-1] = temp;
            pos--;
        }
    }
}

//three parts
/*
    1. extract strand
    2. merge strand and out arr
    3. repeat until org arr count == 0
*/
void strandSort(List* arr){
    List out = {.count = 0};
    List strand = {.count = 0};

    while(arr->count > 0){
        int ref = arr->data[0] - 1;
        int write = 0;
        strand.count = 0;

        for(int i = 0; i < arr->count; i++){
            if(arr->data[i] > ref){
                strand.data[strand.count++] = arr->data[i];
                ref = arr->data[i];
            }else{
                arr->data[write++] = arr->data[i];
            }
        }
        arr->count = write;
        merge(&out, &strand);
    }
    memcpy(arr->data, out.data, sizeof(int)*(out.count));
    arr->count = out.count;
}

void merge(List* L1, List* L2){
    int temp[MAX];
    int i = 0, j = 0, k = 0;

    while(i < L1->count && j < L2->count){
        if(L1->data[i] <= L2->data[j]){
            temp[k++] = L1->data[i++];
        } else {
            temp[k++] = L2->data[j++];
        }
    }

    while(i < L1->count) temp[k++] = L1->data[i++];
    while(j < L2->count) temp[k++] = L2->data[j++];

    memcpy(L1->data, temp, sizeof(int) * k);
    L1->count = k;
}


void swap(int* x, int*y){
    int temp = *x;
    *x = *y;
    *y = temp;
}