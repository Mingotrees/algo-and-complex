#include <stdio.h>
#include <stdlib.h>
#define MAX 5    

typedef struct{
    Edge arr[MAX];
    int size;
}PrioQueue;

typedef struct node{
    Edge data;
    struct node* next;
}*List;

//0 - weight // 1 - vertex; 
typedef int Edge[2];

typedef List AdjacencyList[MAX];

void heapify(PrioQueue* queue);
void heapifySubtreeR(PrioQueue* queue, int root);
Edge dequeue(PrioQueue* queue);
void insertMin(PrioQueue* queue, Edge elem);
int* dijkstra(AdjacencyList list, int start);

int main(){
    return 0;
}

int* dijkstra(AdjacencyList list, Edge start){
    PrioQueue q = {.size = 0};
    int* d = (int*)malloc(sizeof(int)*MAX);
    d[start[1]] = 0;
    insertMin(&q, start);
    while(q.size != 0){
        Edge p = dequeue(&q);

        if(p[0] != d[p[1]])
            continue;

        for(List i = list[p[1]]; i != NULL; i = i->next){
            Edge uv = i;
            
            if(d[p[0]] + uv[0] < d[p[0]]){
                d[uv[1]] = d[p[0]] + uv[0];
                Edge new_edge = {d[uv[1]], uv[1]};
                insertMin(&q, new_edge);
            }
        }
    }
    return d;
}



void heapifySubtreeR(PrioQueue* queue, int root){
    int left = root*2 + 1;
    int right = left + 1;
    int smallest = root;
    if(left < queue->size && queue->arr[left][0] < queue->arr[smallest][0]){
        smallest = left;
    }
    
    if(right < queue->size && queue->arr[right][0] < queue->arr[smallest][0]){
        smallest =  right;
    }

    if(smallest != root){
        Edge temp = queue->arr[smallest];
        queue->arr[smallest] = queue->arr[root];
        queue->arr[root] = temp;
        heapifySubtreeR(queue, smallest);
    }
}

int dequeue(PrioQueue* queue){
    if(queue->size == 0){
        return -1;
    }

    int retVal = queue->arr[0];
    queue->arr[0] = queue->arr[queue->size-1];
    queue->size--;
    heapifySubtreeR(queue, 0);

    return retVal;
}

void insertMin(PrioQueue* queue, Edge elem){
    if(queue->size >= MAX){
        return;
    }

    int insertPos = queue->size++;
    int parent = (queue->size-1)/2;
    while(insertPos > 0 && elem < queue->arr[parent]){
        queue->arr[insertPos] = queue->arr[parent];
        insertPos = parent;
        parent = (parent-1)/2;
    }
    queue->arr[insertPos] = elem;
}


