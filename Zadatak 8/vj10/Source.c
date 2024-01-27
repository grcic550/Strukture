#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


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
Node* deleteNode(Node*,int);

int main(){
    Node* root = NULL;
    int unos=0;
    while (1) {
        printf("1-insert\n2-inorder\n3-preorder\n4-postorder\n5-levelorder\n6-PronadiElement\n7-delete\n8-exit\n");
        scanf("%d", &unos);
        switch (unos)
        {
        case 1:
            printf("\nUnesite broj: ");
            scanf("%d", &unos);
            root=insert(root, unos);
            break;
        case 2:
            printf("\nInorder: ");
            inorder(root);
            break;
        case 3:
            printf("\nPreorder: ");
            preorder(root);
            break;
        case 4:
            printf("\nPostorder: ");
            postorder(root);
            break;
        case 5:
            printf("\nLevelorder: ");
            levelorder(root);
            break;
        case 6:
            printf("\nUnesite broj: ");
            scanf("%d", &unos);
            if (findInTree(root, unos)!=NULL)
                printf("\nPostoji u stablu");
            else
                printf("\nNe postoji u stablu");
            break;
        case 7:
            printf("\nUnesite broj: ");
            scanf("%d", &unos);
            deleteNode(root,unos);
            break;
        case 8:
            return 0;
            break;
        }
        printf("\n\n");
    }

}

void levelorder(Node* root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++) {
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


Node* deleteNode(Node* root, int val)
{

    if (root == NULL)
        return root;

    if (root->value > val) {
        root->left = deleteNode(root->left, val);
        return root;
    }
    else if (root->value < val) {
        root->right = deleteNode(root->right, val);
        return root;
    }

    if (root->left == NULL) {
        Node* temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        free(root);
        return temp;
    }
    else {

        Node* succParent = root;
        Node* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        root->value = succ->value;
        free(succ);
        return root;
    }
}

Node* insert(Node* root, int val) {
    Node* current = root;
    if (root==NULL) {
        return createNode(root, val);
    }
    while (1) {
        if (current->value > val) {
            if (current->left == NULL) {
                current->left = createNode(current->left, val);
                return root;
            }
            current = current->left;
        }
        else if (current->value <= val) {
            if (current->right == NULL) {
                current->right = createNode(current->right, val);
                return root;
            }
                current = current->right;
        }
    }
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

void inorder(Node* root) {
    Node* current = root;
    if (current->left != NULL)
        inorder(current->left);
    printf("%d ",current->value);
    if(current->right!=NULL)
        inorder(current->right);
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
