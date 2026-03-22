//base 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}*List;

typedef struct{
    List head;
    List last;
}Stack; //kind of?

typedef Stack Buckets[MAX];

void freeList(List* headRef);
void bucketSort(int* arr, int count);
void radixSort(int* arr, int count);
List convertToLinkedList(int* arr, int count);
void copyIntoArray(List* temp, int* arr);
int getMaxNumber(int* arr, int count);

int main(){
    int forBucketSort[MAX] = {9,2,6,4,1,2,3};
    int forRadixSort[MAX] = {802,10,90,32,61,4,1,2,3};
    int bCount = 7;
    int rCount = 9;

    bucketSort(forBucketSort, bCount);
    radixSort(forRadixSort, rCount);
    for(int i = 0; i < bCount; i++){
        printf("%d ", forBucketSort[i]);
    }
    printf("\n");
    for(int i = 0; i < rCount; i++){
        printf("%d ", forRadixSort[i]);
    }

    return 0;
}

List convertToLinkedList(int* arr, int count){
    List list = NULL;
    List* listPtr = &list;
    for(int i = 0; i < count; i++){
        List temp = (List)malloc(sizeof(struct node)); 
        if(temp != NULL){
            temp->data = arr[i];
            *listPtr = temp;
            listPtr = &(*listPtr)->next;
        }
    } 
    *listPtr = NULL;

    return list;
}


//iz just one pass
void bucketSort(int* arr, int count){
    Buckets basket = {NULL};
    /*
        Steps:
        1. put everything in bucket based on their number
        2. turn into one list
        3. put back into array ig
    */
    int index;
    //1.
    List temp;
    for(int i = 0; i < count; i++){
        index = arr[i] % 10;
        temp = (List)malloc(sizeof(struct node));
        temp->data = arr[i];
        temp->next = NULL;
        if(basket[index].head == NULL){
            basket[index].head = basket[index].last = temp;
        }else{
            basket[index].last->next = temp;
            basket[index].last = temp;
        }

        temp = NULL;
    }

    //2. turn into one list
    Stack mainList;
    int ndx;
    for(ndx = 0; ndx < MAX && basket[ndx].head == NULL; ndx++){}
    if(ndx < MAX){
        mainList = basket[ndx++];
    }
    while(ndx < MAX){
        if(basket[ndx].head != NULL){
            mainList.last->next = basket[ndx].head;
            mainList.last = basket[ndx].last;
        }
        ndx++;
    }

    //3. Copy back to original array
    copyIntoArray(&mainList.head, arr);

}


void radixSort(int* arr, int count){
    List head = convertToLinkedList(arr, count);
    Buckets basket ={NULL};
    /*
        1. find max number
        3. inner loop get digit by digit = (M % (10 * e)/e);
           3.1 put in buckets according to digit
             3.1.1 if no digit assume 0
           3.2 connect into one list
           3.3 update head and clean baskets
           3.4 loop again for next digit
    */
   int max = getMaxNumber(arr, count); 
   int e = 1; int index;
   List temp;    
   Stack mainList;
   while(max/e != 0){
        //3.1
        while(head != NULL){
            temp = head;
            index = (temp->data % (10 * e))/e;
            head = temp->next;
            temp->next = NULL;
            if(basket[index].head == NULL){
                basket[index].head = basket[index].last = temp;
            }else{
                basket[index].last->next = temp;
                basket[index].last = temp;
            }
        }

        //3.2 turn into one list
        int ndx;
        for(ndx = 0; ndx < MAX && basket[ndx].head == NULL; ndx++){}
        if(ndx < MAX){
            mainList = basket[ndx++];
        }
        while(ndx < MAX){
            if(basket[ndx].head != NULL){
                mainList.last->next = basket[ndx].head;
                mainList.last = basket[ndx].last;
            }
            ndx++;
        }

        head = mainList.head;
        //3.3
        for(ndx = 0; ndx < MAX; ndx++){
            basket[ndx].head = basket[ndx].last = NULL;
        }
        
        e*=10;
   }
   copyIntoArray(&head, arr);
}

void copyIntoArray(List* temp, int* arr){
    int ndx = 0;
    List freeNode;
    while(*temp != NULL){
        freeNode = *temp;
        arr[ndx++] = freeNode->data;
        *temp = freeNode->next;
        free(freeNode);
    }
}

int getMaxNumber(int* arr, int count){
    int max = arr[0];
    for(int i = 1; i < count; i++){
        max = arr[i] > max ? arr[i] : max;
    }

    return max;
}

void freeList(List* headRef){
    List current = *headRef;
    while(current != NULL){
        List next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}


