#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

typedef struct node{
    int data;
    struct node** next;
}*List;

typedef struct{
    int max_level;
    int level;
    float p;
    List header;
}Skiplist;
//0 head 1 tails

List createNode(int data, int level){
    List n = (List)malloc(sizeof(struct node));
    n->data = data;

    n->next = (List*)malloc(sizeof(List)*(level + 1));
    return n;
}

int randomLevel(Skiplist* list){
    int lvl = 0;
    while((float)rand()/RAND_MAX < list->p && lvl < list->max_level){
        lvl++;
    }
    return lvl;
}

void insert(Skiplist *list, int data){
    List update[list->max_level + 1];
    List curr = list->header;

    for(int i = list->level; i >=0; i--){
        while(curr->next[i] != NULL && curr->next[i]->data < data){
            curr = curr->next[i];
        }
        update[i] = curr;
    }

    int rLevel = randomLevel(list);
    if(rLevel > list->level){
        for(int i = list->level + 1; i <= rLevel; i++){
            update[i] = list->header;
        }
    }

    List n = createNode(data, rLevel);

    for(int i = 0; i <= rLevel; i++){
        n->next[i] = update[i]->next[i];
        update[i]->next[i] = n;
    }
}

void deleteNode(Skiplist *list, int data){
    List update[list->max_level + 1];
    List curr = list->header;

    for(int i = list->level; i >=0; i--){
        while(curr->next[i] != NULL && curr->next[i]->data < data){
            curr = curr->next[i];
        }
        update[i] = curr;
    }

    curr = curr->next[0];

    if(curr != NULL && curr->data == data){
        for(int i =0; i <= list->level; i++){
            if(update[i]->next[i] != curr) break;

            update[i]->next[i] = curr->next[i];
        }

        free(curr->next);
        free(curr);
    }

    while (list->level > 0 && list->header->next[list->level] == NULL){
        list->level--;
    }
}

void initSkiplist(Skiplist *list, int max_level, float p){
    list->max_level = max_level;
    list->level = 0;
    list->p = p;
    list->header = createNode(INT_MIN, max_level);
    for(int i = 0; i <= max_level; i++){
        list->header->next[i] = NULL;
    }
}

void freeSkiplist(Skiplist *list){
    List curr = list->header->next[0];
    while(curr != NULL){
        List next = curr->next[0];
        free(curr->next);
        free(curr);
        curr = next;
    }
    free(list->header->next);
    free(list->header);
    list->header = NULL;
}

void printLevel0(Skiplist *list){
    List curr = list->header->next[0];
    printf("Level-0: ");
    while(curr != NULL){
        printf("%d ", curr->data);
        curr = curr->next[0];
    }
    printf("\n");
}



#ifndef SKIPLIST_NO_MAIN
int main(){
    srand((unsigned)time(NULL));

    Skiplist list;
    initSkiplist(&list, 4, 0.0f);

    insert(&list, 3);
    insert(&list, 1);
    insert(&list, 2);
    printLevel0(&list);

    deleteNode(&list, 2);
    printLevel0(&list);

    freeSkiplist(&list);
    return 0;
}
#endif