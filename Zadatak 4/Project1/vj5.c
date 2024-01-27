#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct _element
{
	int exponent;
	int coeficient;
	struct _element* next;

}Element;
void readFromFile(Element[]);
void setValues(Element*, int, int, Element*);
void sortList(Element*, int, int,char);
void addPoly(Element[], Element*);
void multiplyPoly(Element[], Element*);
void printList(Element*);


int main() {
	Element poly[2] = { {.exponent = 0, .coeficient = 0,.next = NULL}, {.exponent = 0, .coeficient = 0,.next = NULL } };
	Element polyAdd = { .exponent = 0, .coeficient = 0,.next = NULL };
	Element polyMultiply = { .exponent = 0, .coeficient = 0,.next = NULL };
	Element* temp = NULL;

	
	readFromFile(poly);
	addPoly(poly,&polyAdd);
	multiplyPoly(poly, &polyMultiply);
	printList(&poly[0]);
	printList(&poly[1]);
	printList(&polyAdd);
	printList(&polyMultiply);

	return 0;
}

void printList(Element* temp) {
	while (temp->next != NULL) {
		printf(" %dx^%d ", temp->next->coeficient, temp->next->exponent);
		temp = temp->next;
	}
	printf("\n");
}
void multiplyPoly(Element headP[], Element* headM) {
	Element* currentP = &headP[0], * currentM = headM, * temp = NULL;
	while (currentP->next != NULL) {
		setValues(currentM, currentP->next->coeficient, currentP->next->exponent, NULL);
		currentM = currentM->next;
		currentP = currentP->next;
	}
	currentP = &headP[1];
	while (currentP->next != NULL) {
		sortList(headM, currentP->next->coeficient, currentP->next->exponent,'*');
		currentP = currentP->next;
	}
}
void addPoly(Element headP[], Element* headM) {
	Element *currentP = &headP[0],*currentM=headM,*temp=NULL;
	while (currentP->next != NULL) {
		setValues(currentM, currentP->next->coeficient, currentP->next->exponent, NULL);
		currentM = currentM->next;
		currentP = currentP->next;
	}
	currentP = &headP[1];
	while (currentP->next != NULL) {
		sortList(headM, currentP->next->coeficient, currentP->next->exponent,'+');
		currentP = currentP->next;
	}
}
void setValues(Element* element, int coef, int exp, Element* next) {
	element->next = (Element*)malloc(sizeof(Element));
	element->next->exponent = exp;
	element->next->coeficient = coef;
	element->next->next = next;
}

void sortList(Element *head, int coef, int exp,char fun) {
	Element* current = NULL, *temp = NULL;
	current = head;
	while (1) {
		if (current->next == NULL) {
			setValues(current, coef, exp, NULL);
			break;
		}
		else if (exp > current->next->exponent) {
			temp = current->next;
			setValues(current, coef, exp, temp);
			break;
		}
		else if (exp == current->next->exponent) {
			if(fun=='+')
			current->next->coeficient += coef;
			else
			current->next->coeficient *= coef;
			if (current->next->coeficient == 0) {
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				temp = NULL;
			}
			break;
		}
		current = current->next;
	}
}

void readFromFile(Element poly[]) {
	int exp = 0, coef = 0, f = 0;
	
	char eol = '0';
	FILE* fptr = NULL;
	fptr= fopen("file.txt", "r");
	if (fptr == NULL)
		return -1;
	for(int i=0;i<=2;i++)
	while (fscanf(fptr, " %dx^%d%c", &coef, &exp, &eol) == 3) {
		sortList(&poly[i], coef, exp,'+');
		if (eol == '\n')
			break;
	}
}