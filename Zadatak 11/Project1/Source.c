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

typedef struct _hash {
	Node* buckets[11];
}Hash;

Hash* createHashTable();
void createNodeFirst(Hash*, int, char[]);
void createNode(Node*, char[]);
void placeInHash(Hash*, char[], char[]);
Branch* createTree(Branch*, char[], int);
Branch* placeInTree(Branch*, char[], int);
void treeMain(Node*, char[]);
void printHash(Hash*);
void printTree(Branch*);
void printHashVal(Hash*,int);
void printTreeVal(Branch*,int);


int main() {
	Hash* hashtable=createHashTable();
	int val = 0;
	FILE* fptr = fopen("drzave.txt","r");
	char cName[50]="", fName[50]="";

	while (!feof(fptr)) {
		fscanf(fptr,"%s %s", cName, fName);
		placeInHash(hashtable, cName, fName);
	}
	while (1) {
		printf("Odaberite sto zelite: 1-printanje svih drzava i gradova, 2-printanje gradova vecih od nekog broja, 3-izlaz");
		scanf("%d", &val);
		switch (val) {
		case 1:
			printHash(hashtable);
			break;
		case 2:
			printf("Unesite broj: ");
			scanf("%d", &val);
			printHashVal(hashtable, val);
			break;
		case 3:
			break;
		}
	}
	return 0;
}

Hash* createHashTable() {
	Hash* hashtable = (Hash*)malloc(sizeof(Hash));
	for (int i = 0; i < 11; i++) {
		hashtable->buckets[i] = NULL;
	}
	return hashtable;
}

void createNodeFirst(Hash* hashtable, int pos, char name[]) {
	hashtable->buckets[pos] = (Node*)malloc(sizeof(Node));
	strcpy(hashtable->buckets[pos]->name, name);
	hashtable->buckets[pos]->next = NULL;
	hashtable->buckets[pos]->tree = NULL;
}

void createNode(Node* head, char name[]) {
	Node* temp = NULL;
	temp = head->next;
	head->next = (Node*)malloc(sizeof(Node));
	strcpy(head->next->name, name);
	head->next->next = temp;
	head->next->tree = NULL;
}

void placeInHash(Hash* hashtable, char cName[], char fName[]) {
	int sum = 0;
	Node* head = NULL;
	for (int i = 0; i < 5; i++)
		sum += cName[i];
	if (hashtable->buckets[sum % 11] == NULL) {
		createNodeFirst(hashtable, sum % 11, cName);
		head = hashtable->buckets[sum % 11];
	}
	else {
		head = hashtable->buckets[sum % 11];
		while (head->next != NULL) {
			if (strcmp(head->next->name, cName) > 0) {
				createNode(head, cName);
				break;
			}
			head = head->next;
		}
	}
	treeMain(head, fName);

}

Branch* createTree(Branch* root, char name[], int pop) {
	root = (Branch*)malloc(sizeof(Branch));
	root->left = NULL;
	root->right = NULL;
	strcpy(root->name, name);
	root->pop = pop;
	return root;
}

Branch* placeInTree(Branch* root, char name[], int pop) {
	if (root == NULL) {
		return createTree(root, name, pop);
	}
	if (root->pop > pop)
		root->left=placeInTree(root->left, name, pop);
	if (root->pop < pop)
		root->right=placeInTree(root->right, name, pop);
	if (root->pop == pop) {
		if (strcmp(root->name, name) > 0)
			root->left = placeInTree(root->left, name, pop);
		if (strcmp(root->name, name) < 0)
			root->right = placeInTree(root->right, name, pop);
		if (strcmp(root->name, name) == 0) {
			return NULL;
		}
	}
	return root;
}

void treeMain(Node* head, char fName[]) {
	FILE* fptr = fopen(fName,"r");
	char cName[50] = "";
	int pop = 0;
	while (!feof(fptr)) {
		fscanf(fptr,"%s %d", cName, &pop);
		head->tree=placeInTree(head->tree, cName, pop);
	}
}

void printHash(Hash* hashtable) {
	Node* head = NULL;
	for (int i = 0; i < 11; i++) {
		head = hashtable->buckets[i];
		if (head != NULL);
			while (head != NULL) {
				printf("%s\n", head->name);
				printTree(head->tree);
				printf("\n");
				head = head->next;
		}
	}
}
void printHashVal(Hash* hashtable,int val) {
	Node* head = NULL;
	for (int i = 0; i < 11; i++) {
		head = hashtable->buckets[i];
		if (head != NULL);
		while (head != NULL) {
			printf("%s\n", head->name);
			printTreeVal(head->tree,val);
			printf("\n");
			head = head->next;
		}
	}
}
void printTree(Branch* root) {
	if (root->right != NULL)
		printTree(root->right);
	printf("%s %d ", root->name, root->pop);
	if (root->left != NULL)
		printTree(root->left);
}

void printTreeVal(Branch* root,int val) {
	if (root->right != NULL)
		printTreeVal(root->right,val);
	if(root->pop>val)
		printf("%s %d ", root->name, root->pop);
	if (root->left != NULL)
		printTreeVal(root->left,val);
}