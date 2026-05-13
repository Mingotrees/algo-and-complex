#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_MAX 999
#define MAX 5    

//maypag di nalang i array ang edge fucking complicated

//0 - weight // 1 - vertex; 
typedef int Edge[2];

typedef struct{
    Edge arr[MAX];
    int size;
}PrioQueue;

typedef struct node{
    Edge data;
    struct node* next;
}*List;

typedef List AdjacencyList[MAX];

void heapify(PrioQueue* queue);
void heapifySubtreeR(PrioQueue* queue, int root);
Edge* dequeue(PrioQueue* queue);
void insertMin(PrioQueue* queue, Edge elem);
int* dijkstra(AdjacencyList list, Edge start);

int main(){
    // Create adjacency list: 5 vertices, edges (weight, vertex)
    AdjacencyList list = {0};
    
    // Vertex 0: edges to 1 (weight 4) and 2 (weight 2)
    list[0] = malloc(sizeof(struct node));
    list[0]->data[0] = 4; list[0]->data[1] = 1;
    list[0]->next = malloc(sizeof(struct node));
    list[0]->next->data[0] = 2; list[0]->next->data[1] = 2;
    list[0]->next->next = NULL;
    
    // Vertex 1: edge to 2 (weight 1)
    list[1] = malloc(sizeof(struct node));
    list[1]->data[0] = 1; list[1]->data[1] = 2;
    list[1]->next = NULL;
    
    // Vertex 2: edge to 3 (weight 5)
    list[2] = malloc(sizeof(struct node));
    list[2]->data[0] = 5; list[2]->data[1] = 3;
    list[2]->next = NULL;
    
    // Vertices 3, 4: no outgoing edges
    list[3] = NULL;
    list[4] = NULL;
    
    // Run Dijkstra from vertex 0
    Edge start = {0, 0};
    int* d = dijkstra(list, start);
    
    // Expected distances
    int expected[] = {0, 4, 2, 7, INT_MAX};
    
    // Print results
    printf("=== Dijkstra Test Case ===\n");
    printf("Graph: 0->1(4), 0->2(2), 1->2(1), 2->3(5)\n");
    printf("Start: Vertex 0\n\n");
    printf("Vertex | Expected | Actual | Status\n");
    printf("-------|----------|--------|--------\n");
    
    int passed = 0;
    for(int i = 0; i < MAX; i++){
        char status[10];
        if(d[i] == expected[i]){
            strcpy(status, "PASS");
            passed++;
        } else {
            strcpy(status, "FAIL");
        }
        
        printf("   %d   |", i);
        if(expected[i] == INT_MAX) printf("   INF    ");
        else printf("    %d    ", expected[i]);
        printf("|");
        if(d[i] == INT_MAX) printf("  INF   ");
        else printf("   %d   ", d[i]);
        printf("| %s\n", status);
    }
    
    printf("\n%d/%d tests passed\n", passed, MAX);
    
    // Cleanup
    free(list[0]->next);
    free(list[0]);
    free(list[1]);
    free(list[2]);
    free(d);
    
    return 0;
}

int* dijkstra(AdjacencyList list, Edge start){
    PrioQueue q = {.size = 0};
    int* d = (int*)malloc(sizeof(int)*MAX);
    for(int j = 0; j < MAX; j++) d[j] = INT_MAX;
    d[start[1]] = 0;
    insertMin(&q, start);
    while(q.size != 0){
        Edge* p = dequeue(&q);
        if(p == NULL) break;

        if((*p)[0] != d[(*p)[1]])
            continue;

        for(List i = list[(*p)[1]]; i != NULL; i = i->next){
            Edge uv;
            memcpy(uv, i->data, sizeof(Edge));
            
            if(d[(*p)[1]] + uv[0] < d[uv[1]]){
                d[uv[1]] = d[(*p)[1]] + uv[0];
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
        Edge temp;
        memcpy(temp, queue->arr[smallest], sizeof(Edge));
        memcpy(queue->arr[smallest], queue->arr[root], sizeof(Edge));
        memcpy(queue->arr[root], temp, sizeof(Edge));
        heapifySubtreeR(queue, smallest);
    }
}

Edge* dequeue(PrioQueue* queue){
    if(queue->size == 0){
        return NULL;
    }

    static Edge result;
    memcpy(result, queue->arr[0], sizeof(Edge));
    memcpy(queue->arr[0], queue->arr[queue->size-1], sizeof(Edge));
    queue->size--;
    heapifySubtreeR(queue, 0);

    return &result;
}

void insertMin(PrioQueue* queue, Edge elem){
    if(queue->size >= MAX){
        return;
    }

    int insertPos = queue->size++;
    int parent = (queue->size-1)/2;
    while(insertPos > 0 && elem[0] < queue->arr[parent][0]){
        memcpy(queue->arr[insertPos], queue->arr[parent], sizeof(Edge));
        insertPos = parent;
        parent = (parent-1)/2;
    }
    memcpy(queue->arr[insertPos], elem, sizeof(Edge));
}


