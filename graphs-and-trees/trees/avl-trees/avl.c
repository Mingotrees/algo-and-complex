//to run code 
// gcc avl.c avl_test.c -o avl_test
// ./avl_test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct node{
    int height;
    int data;
    struct node* left;
    struct node* right;
}*List;

void rotate_right(List* root);
void rotate_left(List* root);
void insert(List* head, int x);
void balance(List* head);
void delete(List* head, int x);
void calculateHeight(List root);
int calculateSkew(List root);
int count_nodes(List root);
void breadth_first_print(List root);
void free_tree(List root);

void calculateHeight(List root){
    int leftHeight, rightHeight;
    if(root->left == NULL){
        leftHeight = -1;
    }else{
        leftHeight = root->left->height;
    }

    if(root->right == NULL){
        rightHeight = -1;
    }else{
        rightHeight = root->right->height;
    }


    root->height = MAX(leftHeight, rightHeight) + 1;
}

int calculateSkew(List root){
    int leftHeight, rightHeight;
    if(root->left == NULL){
        leftHeight = -1;
    }else{
        leftHeight = root->left->height;
    }

    if(root->right == NULL){
        rightHeight = -1;
    }else{
        rightHeight = root->right->height;
    }

    return leftHeight - rightHeight;
}

int count_nodes(List root){
    if(root == NULL){
        return 0;
    }

    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void breadth_first_print(List root){
    if(root == NULL){
        printf("Tree is empty.\n");
        return;
    }

    int count = count_nodes(root);
    List* queue = (List*)malloc(sizeof(List) * count);
    if(queue == NULL){
        printf("Queue allocation failed.\n");
        return;
    }

    int front = 0;
    int back = 0;
    queue[back++] = root;

    while(front < back){
        int levelCount = back - front;
        for(int i = 0; i < levelCount; i++){
            List current = queue[front++];
            printf("%d ", current->data);

            if(current->left != NULL){
                queue[back++] = current->left;
            }
            if(current->right != NULL){
                queue[back++] = current->right;
            }
        }
        printf("\n");
    }
    free(queue);
}

void free_tree(List root){
    if(root == NULL){
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void rotate_right(List* root){
    List temp = (*root)->left;
    (*root)->left = temp->right;
    temp->right = *root;
    calculateHeight(*root);
    calculateHeight(temp);
    *root = temp;
}

void rotate_left(List* root){
    List temp = (*root)->right;
    (*root)->right = temp->left;
    temp->left = *root;
    calculateHeight(*root);
    calculateHeight(temp);
    *root = temp;
}

void insert(List* head, int x){
    if(*head == NULL){
        List temp = (List)malloc(sizeof(struct node)); 
        temp->data = x;
        temp->left = temp->right = NULL;
        temp->height = 0;
        *head = temp;
    }else if(x < (*head)->data){
        insert(&(*head)->left, x);
    }else{
        insert(&(*head)->right, x);
    }

    calculateHeight(*head);
    balance(head);
}

void balance(List* head){
    int balanceFactor = calculateSkew(*head);
    int childBalance;
    if(balanceFactor > 1){
        if(balanceFactor > 1){
            childBalance = calculateSkew((*head)->left);
            if(childBalance > 0){
                rotate_right(head);
            }else{
                rotate_left(&(*head)->left);
                rotate_right(head);
            }
        }
    }else if(balanceFactor < -1){
        childBalance = calculateSkew((*head)->right);
        if(childBalance < 0){
            rotate_left(head);
        }else{
            rotate_right(&(*head)->right);
            rotate_left(head);
        }
    }
}

void delete(List* head, int x){
    if(*head == NULL){
        return;
    }else if(x < (*head)->data){
        delete(&(*head)->left, x);
    }else if(x > (*head)->data ){
        delete(&(*head)->right, x);
    }else{
         //foundW
         //case 1: leaf and 2: one child
        if((*head)->left == NULL || (*head)->right == NULL){
            List child = (*head)->left == NULL ? (*head)->right : (*head)->left;
            free(*head);
            *head = child;
        }else{
            //immediate ancestor
            List temp;
            for(temp = (*head)->right; temp->left != NULL; temp=temp->left){}
            (*head)->data = temp->data;
            delete(&(*head)->right, temp->data);
        }

    }
    if(*head != NULL){
        calculateHeight(*head);
        balance(head);
    }
}




