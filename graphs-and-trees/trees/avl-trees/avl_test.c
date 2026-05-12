#include <stdio.h>
#include <stdlib.h>

// Forward declarations from avl.c
typedef struct node{
    int height;
    int data;
    struct node* left;
    struct node* right;
}*List;

void insert(List* head, int x);
void delete(List* head, int x);
void breadth_first_print(List root);
void free_tree(List root);

static void run_insert_case(const char* label, int* values, int count){
    List root = NULL;
    printf("%s\n", label);
    for(int i = 0; i < count; i++){
        insert(&root, values[i]);
    }
    breadth_first_print(root);
    printf("\n");
    free_tree(root);
}

static void run_delete_case(const char* label, int* values, int valueCount, int* deletes, int deleteCount){
    List root = NULL;
    printf("%s\n", label);
    for(int i = 0; i < valueCount; i++){
        insert(&root, values[i]);
    }
    printf("Initial tree:\n");
    breadth_first_print(root);

    for(int i = 0; i < deleteCount; i++){
        printf("After delete %d:\n", deletes[i]);
        delete(&root, deletes[i]);
        breadth_first_print(root);
    }

    printf("\n");
    free_tree(root);
}

int main(){
    int ll_case[] = {30, 20, 10};
    int rr_case[] = {10, 20, 30};
    int lr_case[] = {30, 10, 20};
    int rl_case[] = {10, 30, 20};

    run_insert_case("Insert LL (30, 20, 10):", ll_case, 3);
    run_insert_case("Insert RR (10, 20, 30):", rr_case, 3);
    run_insert_case("Insert LR (30, 10, 20):", lr_case, 3);
    run_insert_case("Insert RL (10, 30, 20):", rl_case, 3);

    int base_values[] = {30, 20, 40, 10, 25, 35, 50};
    int base_deletes[] = {10, 20, 30};
    run_delete_case("Delete leaf/one-child/two-children:", base_values, 7, base_deletes, 3);

    int del_ll_values[] = {30, 20, 40, 10};
    int del_ll_deletes[] = {40};
    run_delete_case("Delete causing LL rotation:", del_ll_values, 4, del_ll_deletes, 1);

    int del_rr_values[] = {30, 20, 40, 50};
    int del_rr_deletes[] = {20};
    run_delete_case("Delete causing RR rotation:", del_rr_values, 4, del_rr_deletes, 1);

    int del_lr_values[] = {30, 10, 40, 5, 20};
    int del_lr_deletes[] = {40};
    run_delete_case("Delete causing LR rotation:", del_lr_values, 5, del_lr_deletes, 1);

    int del_rl_values[] = {30, 20, 50, 40};
    int del_rl_deletes[] = {20};
    run_delete_case("Delete causing RL rotation:", del_rl_values, 4, del_rl_deletes, 1);

    return 0;
}
