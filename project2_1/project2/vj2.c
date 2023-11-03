#define _CRT_SECURE_NO_WARNINGS
#define MAX 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person {
    char name[MAX];
    char surname[MAX];
    int birth_year;
	struct _person* next;
}Person;

void pushToStart(Person** head) {
    Person* new_person = (Person*)malloc(sizeof(Person));
    printf("Unesite ime prezime i godinu rodenja\n");
    scanf("%s %s %d", new_person->name, new_person->surname,&new_person->birth_year);
    new_person->next = *head;
    *head = new_person;
}
void pushToBack(Person* head) {
    Person* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (Person*)malloc(sizeof(Person));
    current = current->next;
    printf("Unesite ime prezime i godinu rodenja\n");
    scanf("%s %s %d", current->name, current->surname, &current->birth_year);
    current->next = NULL;
}
void printList(Person* head) {
    Person* current = head;
    while (current != NULL) {
        printf("%s %s %d\n", current->name,current->surname,current->birth_year);
        current = current->next;
    }
}
void findInList(Person* current) {
    char input[MAX];
    printf("Unesite prezime osobe koju trazite\n");
    scanf("%s", input);
    while (current != NULL) {
        if(strcmp(input,current->surname)==0)
        printf("%s %s %d\n", current->name, current->surname, current->birth_year);
        current = current->next;
    }
}
void deleteFromList(Person** head) {
    int input=0,counter=2;
    Person* current = *head;
    printf("Unesite koji element zelite izbrisati po poziciji\n");
    scanf("%d", &input);
    if (input == 1) {
        *head = current->next;
        free(current);
    }
    else{
        while (current != NULL) {
            if (counter == input) {
                Person* del = current->next;
                current->next = current->next->next;
                free(del);
                break;
            }
            counter++;
            current = current->next;
        }
    }

}

void menu() {
    Person* head = NULL;
    int input = 0;
    do{
        printf("Odaberite sto zelite:\n"
            "1-Dodavanje na pocetak liste\n"
            "2-Dodavanje na kraj liste\n"
            "3-Ispis liste\n"
            "4-Trazenje po listi prezimenom\n"
            "5-Brisanje iz liste po poziciji\n"
            "0-Izlaz\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                pushToStart(&head);
                break;
            case 2:
                pushToBack(head);
                break;
            case 3:
                printList(head);
                break;
            case 4:
                findInList(head);
                break;
            case 5:
                deleteFromList(&head);
                break;
            }
        }while (input != 0);
    
}
int main() {
    
    menu();
    return 0;
}
