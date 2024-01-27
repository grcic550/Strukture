#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

typedef struct _student
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;

}Student;

int readNorowsInFile() {
	int noRows = 0;
	FILE* f = NULL;
	char buffer[MAX_LINE] = { 0 };
	f = fopen("dat.txt", "r");
	if (!f) {
		return FILE_ERROR_OPEN;
	}
	while (!feof(f)) {
		fgets(buffer, MAX_LINE, f);
		noRows++;

	}
	fclose(f);
	return noRows;
}
void readFromFile(Student *s) {
	FILE* f = NULL;
	int i = 0;
	f = fopen("dat.txt", "r");
	if (!f) {
		return FILE_ERROR_OPEN;
	}
	while (!feof(f)) {
		fscanf(f, "%s %s %lf", s[i].name, s[i].surname, &s[i].points);
		i++;
	}
}
void writeFromStructure(Student* s,int x) {
	int i = 0;
	while (i<x) {
		printf("%s %s %f\n", s[i].name, s[i].surname, s[i].points);
		i++;
	}
}
int main() {
	int noRows = 0;
	Student *students=NULL;
	noRows = readNorowsInFile();
	students =(Student*)malloc(sizeof(Student)*noRows);
	readFromFile(students);
	writeFromStructure(students,noRows);

	
	
	free(students);
	return 0;
}