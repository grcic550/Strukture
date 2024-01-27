#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct _element
{
	int exponent;
	int coeficient;
	struct _element *next;

}Element;
int main() {
	Element poly1 = {.exponent = 0, .coeficient = 0,.next = NULL};
	Element poly2 = { .exponent = 0, .coeficient = 0,.next = NULL };
	Element polyAdd = { .exponent = 0, .coeficient = 0,.next = NULL };
	Element polyMultiply = { .exponent = 0, .coeficient = 0,.next = NULL };

	FILE* fileptr = open("dat.txt");
	int exp=0,coef=0;
	while (fscanf(fileptr, " %d %d ", coef, exp) == 2) {
		printf("%d %d", coef, exp);
	}
		

	return 0;
}
