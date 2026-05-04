#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int height;
    int data;
    struct node* left;
    struct node* right;
}*List;

List rotate_right(List root);
List rotate_left(List root);
List* insert(List* head);
List* delete(List* head);

int main(){

    return 0;
}

List rotate_right(List root){
    List temp = root->left;
    root->left = temp->right;
    temp->right = root;

    return temp;
}

List rotate_left(List root){
    List temp = root->right;
    root->right = temp->left;
    temp->left = root;

    return temp;
}

List* insert(List* head, int x){
    if(*head == NULL){
        return NULL;
    }else if(x < (*head)->data){
        insert((*head)->left, x);
    }else if(x > (*head)->data){
        insert((*head)->right, x);
    }else{
        
    }

}

List* delete(List* head){


}




