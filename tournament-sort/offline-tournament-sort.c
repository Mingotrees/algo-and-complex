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
    if(temp->count <= 0){
        return;
    }

    int n = temp->count;
    int size = (2 * n) - 1;
    int leafStart = n - 1;
    int values[MAX];
    int tree[(2 * MAX) - 1];

    for(int i = 0; i < n; i++){
        values[i] = temp->arr[i];
    }

    // Leaves store source indices. Internal nodes also store winner indices.
    for(int i = 0; i < n; i++){
        tree[leafStart + i] = i;
    }

    for(int i = leafStart - 1; i >= 0; i--){
        int left = tree[(2 * i) + 1];
        int right = tree[(2 * i) + 2];
        tree[i] = (values[left] <= values[right]) ? left : right;
    }

    temp->count = 0;

    while(values[tree[0]] != INF){
        int winnerIndex = tree[0];
        temp->arr[temp->count++] = values[winnerIndex];
        values[winnerIndex] = INF;

        int node = leafStart + winnerIndex;
        tree[node] = winnerIndex;

        while(node > 0){
            int parent = (node - 1) / 2;
            int left = tree[(2 * parent) + 1];
            int right = tree[(2 * parent) + 2];
            tree[parent] = (values[left] <= values[right]) ? left : right;
            node = parent;
        }
    }
}