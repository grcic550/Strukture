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
int isEmpty(Person**);
void pushBeforePerson(Person**);
void pushAfterPerson(Person**);
void pushToStart(Person**);
void pushToBack(Person**);
void printList(Person*);
Person* findInList(Person*);
void deleteFromList(Person**);
void menu();


int main() {
    
    menu();
    return 0;
}
int isEmpty(Person** head) {
    if (*head == NULL) {
        pushToStart(head);
        return 1;
    }
    return 0;
}

void pushBeforePerson(Person** head) {
    Person *current = NULL, *temp = NULL;
    if (isEmpty(head) == 1)
        return;
    do {
        current = findInList(*head);
    } while (current == NULL);
    temp = *head;
    if (current == *head) {
        pushToStart(head);
    }
    else {
        while (head != NULL) {
            if (temp->next == current) {
                break;
            }
            temp = temp->next;
        }
        temp->next = (Person*)malloc(sizeof(Person));
        printf("Unesite ime prezime i godinu rodenja\n");
        scanf("%s %s %d", temp->next->name, temp->next->surname, &temp->next->birth_year);
        temp->next->next = current;
    }

}

void pushAfterPerson(Person** head) {
    Person *current = NULL, *temp = NULL;
    if (isEmpty(head) == 1)
        return;
    do {
        current = findInList(*head);
    } while (current == NULL);
    temp = current->next;
    current->next = (Person*)malloc(sizeof(Person));
    printf("Unesite ime prezime i godinu rodenja\n");
    scanf("%s %s %d", current->next->name, current->next->surname, &current->next->birth_year);
    current->next->next = temp;

}

void pushToStart(Person** head) {
    Person* new_person = (Person*)malloc(sizeof(Person));
    printf("Unesite ime prezime i godinu rodenja\n");
    scanf("%s %s %d", new_person->name, new_person->surname, &new_person->birth_year);
    new_person->next = *head;
    *head = new_person;
}

void pushToBack(Person** head) {
    Person* current = NULL;
    if (isEmpty(head) == 1)
        return;
    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (Person*)malloc(sizeof(Person));
    current = current->next;
    printf("Unesite ime prezime i godinu rodenja\n");
    scanf("%s %s %d", current->name, current->surname, &current->birth_year);
    current->next = NULL;
}

void printList(Person* current) {
    while (current != NULL) {
        printf("%s %s %d\n", current->name, current->surname, current->birth_year);
        current = current->next;
    }
    printf("\n");
}

Person* findInList(Person* current) {
    char input[MAX];
    if (!current)
        return 0;
    printf("Unesite prezime osobe koju trazite\n");
    scanf("%s", input);
    while (current != NULL) {
        if (strcmp(input, current->surname) == 0) {
            printf("%s %s %d\n", current->name, current->surname, current->birth_year);
            break;
    }
        current = current->next;
    }
    return current;
    printf("\n");
}

void deleteFromList(Person** head) {
    Person *current = NULL, *del = NULL;
    if (!*head)
        return ;
    char input[MAX] = {0};
    current = *head;
    printf("Unesite prezime elemente kojeg zelite izbrisati\n");
    scanf("%s", input);
    if (strcmp(input,current->surname)==0) {
        *head = current->next;
        free(current);
    }
    else {
        while (current != NULL) {
            if (strcmp(input,current->next->surname)==0) {
                del = current->next;
                current->next = current->next->next;
                free(del);
                break;
            }
            current = current->next;
        }
    }

}

void menu() {
    Person *head = NULL, *current = NULL, *next = NULL;
    int input = 0;
    do {
        printf("Odaberite sto zelite:\n"
            "1-Dodavanje na pocetak liste\n"
            "2-Dodavanje na kraj liste\n"
            "3-Ispis liste\n"
            "4-Trazenje po listi prezimenom\n"
            "5-Brisanje iz liste po prezimenu\n"
            "6-Dodavanje iza elementa po prezimenu\n"
            "7-Dodavanje ispred elementa po prezimenu\n"
            "0-Izlaz\n");
        scanf("%d", &input);
        switch (input) {
        case 1:
            pushToStart(&head);
            break;
        case 2:
            pushToBack(&head);
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
        case 6:
            pushAfterPerson(&head);
            break;
        case 7:
            pushBeforePerson(&head);
            break;
        }
    } while (input != 0);
    current = head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        head = NULL;
    }
}
