#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _branch {
	char name[50];
	int pop;
	struct _branch* left;
	struct _branch* right;
}Branch;

typedef struct _node {
	char name[50];
	struct _node* next;
	Branch* tree;
}Node;

Node* list(Node*, char[], char[]);
void createNode(Node*, char[]);
void printList(Node*);
void tree(Node*, char[]);
Branch* sortTree(Branch*, char[], int);
Branch* createBranch(Branch*, char[], int);
void inorder(Branch*);
void findInorder(Branch*, int);
void find(Node*, int);



int main() {
	Node head = { .name = "",.next = NULL };
	FILE* fptr = fopen("drzave.txt", "r");
	int val = 0;
	char cName[50] = "", fName[50] = "";
	while (!feof(fptr)) {
		fscanf(fptr, "%s %s", cName, fName);
		list(&head, cName, fName);
	}
	printf("Odaberite sto zelite: 1-printanje svih drzava i gradova, 2-printanje gradova vecih od nekog broja, 3-izlaz");
	scanf("%d", &val);
	switch (val) {
	case 1:
		printList(&head);
		break;
	case 2:
		printf("Unesite broj: ");
		scanf("%d", &val);
		find(&head, val);
		break;
	case 3:
		break;
	}

}

Node* list(Node* head, char cName[], char fName[]) {
	if (head->next == NULL) {
		createNode(head, cName);
	}
	else {
		while (head->next != NULL) {
			if (strcmp(head->next->name, cName) > 0) {
				createNode(head, cName);
				tree(head->next, fName);
				return NULL;
			}
			head = head->next;
		}
		createNode(head, cName);
	}
	tree(head->next, fName);
	return NULL;
}

void createNode(Node* node, char name[]) {
	Node* temp = node->next;
	node->next = (Node*)malloc(sizeof(Node));
	strcpy(node->next->name, name);
	node->next->next = temp;
	node->next->tree = NULL;
}
void printList(Node* head) {
	while (head->next != NULL) {
		printf("%s ", head->next->name);
		printf("\n");
		inorder(head->next->tree);
		head = head->next;
		printf("\n");
	}
}

void find(Node* head, int val) {
	while (head->next != NULL) {
		findInorder(head->next->tree, val);
		head = head->next;
	}
}
void findInorder(Branch* root, int val) {
	Branch* current = root;
	if (current->left != NULL)
		findInorder(current->left, val);
	if (current->pop > val)
		printf("%s %d ", current->name, current->pop);
	if (current->right != NULL)
		findInorder(current->right, val);

}

void inorder(Branch* root) {
	Branch* current = root;
	if (current->left != NULL)
		inorder(current->left);
	printf("%s ", current->name);
	if (current->right != NULL)
		inorder(current->right);

}
void tree(Node* node, char fName[]) {
	int pop;
	char name[50];
	FILE* fptr = fopen(fName, "r");
	while (!feof(fptr)) {
		fscanf(fptr, "%s %d", name, &pop);
		node->tree = sortTree(node->tree, name, pop);
	}
}
Branch* sortTree(Branch* head, char name[], int pop) {
	if (head == NULL)
		return createBranch(head, name, pop);

	if (head->pop < pop)
		head->left = sortTree(head->left, name, pop);
	if (head->pop > pop)
		head->right = sortTree(head->right, name, pop);
	if (head->pop == pop) {
		if (strcmp(head->name, name) > 0)
			head->right = sortTree(head->right, name, pop);
		else
			head->left = sortTree(head->right, name, pop);
	}
	return head;
}

Branch* createBranch(Branch* branch, char name[], int pop) {
	branch = (Branch*)malloc(sizeof(Branch));
	strcpy(branch->name, name);
	branch->pop = pop;
	branch->left = NULL;
	branch->right = NULL;
	return branch;
}