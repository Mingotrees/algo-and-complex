#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INF 999

//offline tournament sort
typedef struct{
    int arr[MAX];
    int count;
}ArrayList;

void offlineTournamentSort(ArrayList *arr);

int main(){
    ArrayList orig = {{4,3,2,1}, 4};
    offlineTournamentSort(&orig);
    for(int ndx = 0; ndx < orig.count; ndx++){
        printf("%d ", orig.arr[ndx]);
    }
}

void offlineTournamentSort(ArrayList *temp){
    if(temp->count > 0){
        int size = temp->count*2-1;
        int* arr = (int*)calloc(size, sizeof(int));
        
        //load players
        for(int i = temp->count - 1, j = size - 1; i >= 0; i--, j--){
            arr[j] = temp->arr[i];
            // printf("[%d]: %d", j, arr[j]);
        }

        temp->count = 0;
        int ndx = size - 1;
        int parent = (ndx-1)/2;
        while(arr[0] != INF){
            //duel logic
            for(;parent >= 0 ;parent = (ndx-1)/2){
                //winner
                if(ndx%2 == 0){
                    arr[parent] = arr[ndx] < arr[ndx-1] ? ndx :  ndx-1;
                    ndx -=2; 
                }else{
                    arr[parent] = arr[ndx] < arr[ndx+1] ? ndx :  ndx+1; 
                    ndx -=1;
                }
            }

            ndx = arr[parent];
            temp->arr[temp->count++] = arr[parent];
            arr[parent] = INF;
            parent = (ndx-1)/2;
        }
        free(arr);
    }
}