#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


typedef struct _node {
    int value;
    struct _node* left;
    struct _node* right;
} Node;

Node* insert(Node*, int);
Node* createNode(Node*, int);
void inorder(Node*);
void preorder(Node*);
void postorder(Node*);
void levelorder(Node*);
void printCurrentLevel(Node*, int);
int height(Node*);
Node* findInTree(Node*, int);
Node* delete(Node*, int);

int main() {
    Node* root = NULL;
    FILE* fptr= fopen("filename.txt", "w");
    root=insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    insert(root, (rand() %
        (90 - 10 + 1)) + 10);
    inorder(root,fptr);
    replace(root);
    inorder(root, fptr);
    fclose(fptr);
}

int replace(Node* root) {
    int val = 0;
    if (root == NULL)
        return 0;
    val = root->value;
    root->value = 0;
    root->value += replace(root->left);
    root->value += replace(root->right);
    return root->value+val;
}

void levelorder(Node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        printf("\n");
    }

}

void printCurrentLevel(Node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->value);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int height(Node* root)
{
    if (root == NULL)
        return 0;
    else {
        int lheight = height(root->left);
        int rheight = height(root->right);
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}


Node* insert(Node* root, int val) {
    if (root == NULL)
        return createNode(root, val);

    if (root->value <= val) 
        root->left=insert(root->left,val);
    if (root->value > val)
        root->right=insert(root->right,val);
    return root;
}

Node* findInTree(Node* root, int val) {
    if (root == NULL || root->value == val)
        return root;

    if (root->value < val)
        return findInTree(root->right, val);

    return findInTree(root->left, val);
}

Node* createNode(Node* node, int val) {
    node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->value = val;
    return node;
}





void inorder(Node* root, FILE* fptr) {
    if (root->left != NULL)
        inorder(root->left,fptr);
    fprintf(fptr,"%d ", root->value);
    if (root->right != NULL)
        inorder(root->right,fptr);
}

void preorder(Node* root) {
    Node* current = root;
    printf("%d ", current->value);
    if (current->left != NULL)
        preorder(current->left);
    if (current->right != NULL)
        preorder(current->right);
}

void postorder(Node* root) {
    Node* current = root;
    if (current->left != NULL)
        postorder(current->left);
    if (current->right != NULL)
        postorder(current->right);
    printf("%d ", current->value);
}
