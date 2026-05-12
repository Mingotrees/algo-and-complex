#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

typedef enum{
    RED,
    BLACK
} Color;

typedef struct node{
    int key;
    Color color;
    struct node* parent;
    struct node* left;
    struct node* right;
} *Node;

typedef struct{
    Node head;
    Node NIL;
} RBTree;

Node search(RBTree head, int key);
void insert(RBTree *tree, int key);
void delete(RBTree *tree, int key);
void initialize(RBTree *tree);

void leftRotate(RBTree* tree, Node x);
void rightRotate(RBTree* tree, Node x);

Node getParent(Node node);
Node getGrandParent(Node node);
Node getUncle(Node node);
Node getSibling(Node node);
Node minimum(Node node);
void transplant(RBTree* tree, Node u, Node v);
int validateRBTree(const RBTree* tree);
void printTree(const RBTree* tree);
void printInorderWithColor(const RBTree* tree);

int main(){
    RBTree tree;
    initialize(&tree);

    printf("Test 1: insert 10, 20, 30\n");
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);
    assert(validateRBTree(&tree));

    printf("Expected inorder: 10(R) 20(B) 30(R)\n");
    printf("Actual inorder:   ");
    printInorderWithColor(&tree);
    printf("\n");

    printf("Tree structure (sideways):\n");
    printTree(&tree);

    printf("\nTest 2: insert 15, 25, 5, 1, 8, 6, 7\n");
    int keys[] = {15, 25, 5, 1, 8, 6, 7};
    size_t count = sizeof(keys) / sizeof(keys[0]);
    for(size_t i = 0; i < count; i++){
        insert(&tree, keys[i]);
        assert(validateRBTree(&tree));
    }

    printf("Expected inorder: (sorted keys with colors)\n");
    printf("Actual inorder:   ");
    printInorderWithColor(&tree);
    printf("\n");

    printf("Tree structure (sideways):\n");
    printTree(&tree);

    printf("\nRB tree insert tests passed.\n");
    return 0;
}

void initialize(RBTree *tree){
    tree->NIL = (Node)malloc(sizeof(struct node));
    if(tree->NIL != NULL){
        tree->NIL->color = BLACK;
        tree->NIL->left = tree->NIL->right = tree->NIL;
        tree->NIL->parent = tree->NIL;
        tree->NIL->key = -1;
    }
    tree->head = tree->NIL;
}


//find proper position
/*
    newNode is always first red
    if parent is black then we gud
    if parent is red, red-red conflict
        1. check color of uncle node
         1.1 if red recolor the parent, uncle, and grandparent (recolor means flipping their colors)
         repeat this process upwards with next iteration being
         z = z->P->P (next grandparent)

        1.2 if Uncle is Black do rotations
         1.2.1 if z is right child of parent and left grandchild of grandparent(LR ROTATION)
            1.2.1.1 perform left rotate at parent
            1.2.1.2 perform right rotate at grandparent
            1.2.1.3 set parent color to black and grandparent to red.
        1.2.2 if z is left child of parent and left grandchild of grandparent (LL ROTATION)
            1.2.1.1 perform right rotate at grandparent
            1.2.1.2 set parent color to black and grandparent to red.
        1.2.3 if z is right child of parent and right grandchild of grandparent (RR ROTATION)
            1.2.1.1 perform left rotate at grandparent
            1.2.1.2 set parent color to black and grandparent to red.
        1.2.3 if z is right child of parent and left grandchild of grandparent (RL ROTATION)
                1.2.1.1 perform right rotate at parent
                1.2.1.1 perform left rotate at grandparent
                1.2.1.2 set parent color to black and grandparent to red.
        

*/
void insert(RBTree *tree, int key){
    //standard BST
    Node new = (Node)malloc(sizeof(struct node));
    new->color = RED;
    new->key = key;
    new->left = new->right = tree->NIL;

    Node y = tree->NIL;
    Node x = tree->head;
    while(x != tree->NIL){
        y = x;
        if(new->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }

    new->parent = y;
    if(y == tree->NIL){
        tree->head = new;
    }else if(new->key < y->key){
        y->left = new;
    }else{
        y->right = new;
    }

    //rebalance
    while(new->parent->color == RED){
        Node P = new->parent;
        Node G = P->parent;
        if(P == G->left){
            Node U = G->right;
            if(U->color == RED){
                P->color = BLACK;
                U->color = BLACK;
                G->color = RED;
                new = G;
            }else{
                if(new == P->right){
                    new = P;
                    leftRotate(tree, new);
                    P = new->parent;
                    G = P->parent;
                }
                P->color = BLACK;
                G->color = RED;
                rightRotate(tree, G);
            }
        }else{
            Node U = G->left;
            if(U->color == RED){
                P->color = BLACK;
                U->color = BLACK;
                G->color = RED;
                new = G;
            }else{
                if(new == P->left){
                    new = P;
                    rightRotate(tree, new);
                    P = new->parent;
                    G = P->parent;
                }
                P->color = BLACK;
                G->color = RED;
                leftRotate(tree, G);
            }
        }
    }
    tree->head->color = BLACK;
}

static int validateBST(Node node, Node NIL, long long min, long long max){
    if(node == NIL){
        return 1;
    }

    if((long long)node->key < min || (long long)node->key > max){
        return 0;
    }

    if(!validateBST(node->left, NIL, min, (long long)node->key - 1)){
        return 0;
    }

    if(!validateBST(node->right, NIL, (long long)node->key, max)){
        return 0;
    }

    return 1;
}

static int validateRedProperty(Node node, Node NIL){
    if(node == NIL){
        return 1;
    }

    if(node->color == RED){
        if(node->left->color != BLACK || node->right->color != BLACK){
            return 0;
        }
    }

    return validateRedProperty(node->left, NIL) && validateRedProperty(node->right, NIL);
}

static int blackHeight(Node node, Node NIL){
    if(node == NIL){
        return 1;
    }

    int left = blackHeight(node->left, NIL);
    int right = blackHeight(node->right, NIL);
    if(left == 0 || right == 0 || left != right){
        return 0;
    }

    return left + (node->color == BLACK ? 1 : 0);
}

int validateRBTree(const RBTree* tree){
    if(tree->head == tree->NIL){
        return 1;
    }

    if(tree->head->color != BLACK){
        return 0;
    }

    if(!validateBST(tree->head, tree->NIL, LLONG_MIN, LLONG_MAX)){
        return 0;
    }

    if(!validateRedProperty(tree->head, tree->NIL)){
        return 0;
    }

    if(blackHeight(tree->head, tree->NIL) == 0){
        return 0;
    }

    return 1;
}

static void printTreeInternal(Node node, Node NIL, int depth){
    if(node == NIL){
        return;
    }

    printTreeInternal(node->right, NIL, depth + 1);
    for(int i = 0; i < depth; i++){
        printf("    ");
    }
    printf("%d(%c)\n", node->key, node->color == RED ? 'R' : 'B');
    printTreeInternal(node->left, NIL, depth + 1);
}

void printTree(const RBTree* tree){
    if(tree->head == tree->NIL){
        printf("<empty>\n");
        return;
    }
    printTreeInternal(tree->head, tree->NIL, 0);
}

static void printInorderInternal(Node node, Node NIL){
    if(node == NIL){
        return;
    }

    printInorderInternal(node->left, NIL);
    printf("%d(%c) ", node->key, node->color == RED ? 'R' : 'B');
    printInorderInternal(node->right, NIL);
}

void printInorderWithColor(const RBTree* tree){
    printInorderInternal(tree->head, tree->NIL);
}


Node getParent(Node node){
    return node->parent;
}

Node getGrandParent(Node node){
    return node->parent->parent;
}

Node getUncle(Node node){
    Node G = getGrandParent(node);
    if(getParent(node) == G->right){
        return G->left;
    }else{
        return G->right;
    }
}

Node getSibling(Node node){
    Node P = getParent(node);
    if(P->right == node){
        return P->left;
    }else{
        return P->right;
    }
}



void leftRotate(RBTree* tree, Node x){
    Node temp = x->right;
    x->right = temp->left;    
    
    if(temp->left != tree->NIL){
        temp->left->parent = x;
    }


    temp->parent = x->parent;
    if(temp->parent == tree->NIL){
        tree->head = temp;
    }else if(x == x->parent->left){ //left cild
        x->parent->left = temp;
    }else{ //right child
        x->parent->right = temp;
    }
        
    temp->left = x;
    x->parent = temp;
}

void rightRotate(RBTree* tree, Node x){
    Node temp = x->left;
    x->left = temp->right;

    if(temp->right != tree->NIL){
        temp->right->parent = x;
    }
    temp->parent = x->parent;
    if(x->parent == tree->NIL){
        tree->head = temp;
    }else if(x->parent->left == x){
        x->parent->left = temp;
    }else{
        x->parent->right = temp;
    }

    temp->right = x;
    x->parent = temp;
}

