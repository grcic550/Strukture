#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _element {
	double a;
	struct _element* next;
} Element;

void readFromFile(Element*);
void push(Element* elem, double num);
double pull(Element* elem);
void calc(Element* elem, char symb);

int main() {
	Element elem = { .a = 0,.next = NULL };
	readFromFile(&elem);
	return 0;
}

double pull(Element* elem) {
	double tempdouble=0;
	Element* temp = NULL;
	tempdouble=elem->next->a;
	temp = elem->next;
	elem->next = elem->next->next;
	free(temp);
	temp = NULL;
	return tempdouble;
}

void calc(Element* elem, char symb) {
	double num[2] = {0,0};
	for (int i = 0; i < 2; i++) {
		num[i] = pull(elem);
	}
	if (symb == '+')
		push(elem, num[0] + num[1]);
	if (symb == '-')
		push(elem, num[0] - num[1]);
	if (symb == '*')
		push(elem, num[0] * num[1]);
	if (symb == '/')
		push(elem, num[0] / num[1]);
}

void push(Element* elem,double num) {
	Element* temp = NULL;
	temp = elem->next;
	elem->next = (Element*)malloc(sizeof(Element));
	elem->next->a = num;
	elem->next->next = temp;
}

void readFromFile(Element *elem) {
	
	double num=0;
	Element* current = elem;
	char symb = ' ';
	FILE* fptr=fopen("data.txt","r");
	while (1) {
		if (fscanf(fptr, " %lf ", &num) == 1) {
			push(elem,num);
		}
		else {
			fseek(fptr, -1, SEEK_CUR);
			fscanf(fptr, " %c ", &symb);
			calc(elem,symb);
		}
		
		printf("Stanje na STOG-u:");
		while (current->next != NULL) {
			printf(" %lf ", current->next->a);
			current = current->next;
		}
		printf("\n");
		current = elem;
		if (feof(fptr) != 0) {
			break;
		}
	}
}