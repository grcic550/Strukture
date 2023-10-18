#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

typedef struct _ante
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;

}Ante;

int readNorowsInFile() {
	int noRows = 0;
	FILE *f = NULL;
	char buffer[MAX_LINE] = { 0 };
	f = fopen("dat.txt", "r");
	if (!f) {
		printf("AAAAAAAAAAAAAAAAAA\n");
		return FILE_ERROR_OPEN;
	}
	while (!feof(f)) {
		fgets(buffer, MAX_LINE, f);
		noRows++;

	}
	fclose(f);
	return noRows;
}
int main() {
	int noRows=0;
	noRows = readNorowsInFile();
	printf("%d", noRows);
	return 0;
}