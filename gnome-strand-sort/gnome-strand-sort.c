#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}List;

typedef struct node{
    int data;
    struct node* next;
}*LinkedList;

//discontinued
// typedef struct{
//     LinkedList head;
//     LinkedList tail;
// }StackLList;

LinkedList convertToLinkedList(int* arr, int count);
void gnomeSort(List*);
void swap(int*, int*);
void strandSort1(List* arr);
void merge1(List* L1, List* L2);
void gnomeSort1(List* arr);
void strandSort(int* arr, int count);
void gnomeSort2(List* arr);
void merge(int* L1, int L1count, int* L2, int *L2count);

int main(){
    List org = {{10,9,2,6,4,1,2}, 7};
    // gnomeSort1(&org);
    // gnomeSort2(&org);
    // strandSort(&org);
    strandSort(org.data, 7);
    for(int i = 0; i < org.count; i++){
        printf("%d ", org.data[i]);
    }
    
    return 0;
}

void gnomeSort(List* arr){
    int pos = 1;
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



void gnomeSort2(List* arr){
    int ndx;
    for(ndx = 1; ndx < arr->count;){
        if(arr->data[ndx] < arr->data[ndx-1]){
            swap(&arr->data[ndx], &arr->data[ndx-1]);
            if(ndx > 1){
                ndx--;
            }
        }else{
            ndx++;
        }
    }
}

//discontinued
// LinkedList convertToLinkedList(int* arr, int count){
//     LinkedList list = NULL;
//     LinkedList* listPtr = &list;
//     for(int i = 0; i < count; i++){
//         LinkedList temp = (LinkedList)malloc(sizeof(struct node)); 
//         if(temp != NULL){
//             temp->data = arr[i];
//             *listPtr = temp;
//             listPtr = &(*listPtr)->next;
//         }
//     } 
//     *listPtr = NULL;

//     return list;
// }

//three parts
/*
    1. extract strand
    2. merge strand and out arr
    3. repeat until org arr count == 0
*/
void strandSort1(List* arr){
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
        merge1(&out, &strand);
    }
    memcpy(arr->data, out.data, sizeof(int)*(out.count));
    arr->count = out.count;
}

void merge1(List* L1, List* L2){
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

void strandSort(int* arr, int count){
    int newCount, sCount, oCount = 0;
    int* strand = (int*)malloc(sizeof(int)*MAX);
    int* output = (int*)malloc(sizeof(int)*MAX);
    while(count > 0){
        newCount = 0;
        sCount = 0;
        int largest = arr[0];
        strand[sCount++] = largest;
        for(int i = 1; i < count; i++){
            if(arr[i] > largest){
                strand[sCount++] = arr[i];
                largest = arr[i];
            }else{
                arr[newCount++] = arr[i];
            }
        }
        count = newCount;
        merge(strand, sCount, output, &oCount);
    }
    memcpy(arr, output, sizeof(int)*oCount);
    free(strand);
    free(output);
}

void merge(int* L1, int L1count, int* L2, int *L2count){
    int mergeAr[MAX];
    int mergeCount = 0;
    int i = 0, j = 0;
    while(i < L1count && j < *L2count){
        if(L1[i] < L2[j]){
            mergeAr[mergeCount++] = L1[i++];
        }else{
            mergeAr[mergeCount++] = L2[j++];
        }
    }

    while(i < L1count) { mergeAr[mergeCount++] = L1[i++];};
    while(j < *L2count) { mergeAr[mergeCount++] = L2[j++];};
    memcpy(L2, mergeAr, sizeof(int)*mergeCount);
    *L2count = mergeCount;
}