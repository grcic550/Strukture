#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct _directory {
    char name[MAX_NAME_LENGTH];
    struct _directory* subDirectories;
    struct _directory* next;
} Directory;

typedef struct _levelStack {
    Directory* directoryLevel;
    struct _levelStack* next;
} LevelStack;

Directory* mkdir(Directory*, char[]);
Directory* createmkdir(Directory*, Directory*, char[]);
Directory* cdDir(Directory*, char[]);
LevelStack* push(LevelStack*, Directory*);
LevelStack* createStack(LevelStack*, LevelStack*, Directory*);
Directory* pop(LevelStack*);
void printDir(Directory*);

int main() {
    Directory headDir = { .name = " ",.subDirectories = NULL,.next = NULL };
    LevelStack headStack = { .directoryLevel = NULL, .next = NULL };
    Directory* rootDirectory=createmkdir(&headDir, headDir.next, "C:/");
    Directory* currentDir = rootDirectory,*temp=rootDirectory;
    int input = 0;
    char name[MAX_NAME_LENGTH] = " ";
    while (1) {
        printf("Unesite izbor 1-mkdir 2-cd dir 3-cd.. 4-dir 5-izlaz\n");
        printf("");
        scanf("%d", &input);
        if (input == 1) {
            printf("Unesite ime direktorija koji stvarate\n");
            scanf("%s", name);
            if (mkdir(currentDir, name) == NULL)
                return 405;
        }
        else if (input == 2) {
            printf("Unesite ime direktorija u koji ulazite\n");
            scanf("%s", name);
            temp = currentDir;
            currentDir=cdDir(currentDir,name);
            if (currentDir != temp)
                if (push(&headStack, temp) == NULL)
                    return 404;
        }
        else if (input == 3) {
            if(currentDir!=rootDirectory)
                currentDir = pop(&headStack);
        }
        else if (input == 4) {
            printDir(currentDir);
        }
        else if (input == 5) {
            return 0;
        }
    }
}

void printDir(Directory* currentDir) {
    Directory* temp = currentDir->subDirectories;
    while (temp != NULL) {
        printf("%s \n", temp->name);
            if (temp->next != NULL)
                temp = temp->next;
            else
                break;
    }
}

Directory* pop(LevelStack* head) {
    Directory* tempDir = head->next->directoryLevel;
    LevelStack* tempStack = head->next;
    head->next = head->next->next;
    free(tempStack);
    tempStack = NULL;
    return tempDir;
}

LevelStack* push(LevelStack* head, Directory* currentDir) {
    if (head->next == NULL) {
        if (createStack(head, NULL, currentDir) == NULL)
            return NULL;
    }
    else {
        if (createStack(head, head->next, currentDir) == NULL)
            return NULL;
    }
    
}

LevelStack* createStack(LevelStack* head, LevelStack* next, Directory* currentDir) {
    head->next = (LevelStack*)malloc(sizeof(LevelStack));
    if (head->next == NULL) {
        return NULL;
    }
    head->next->directoryLevel = currentDir;
    head->next->next = next;
}
Directory* cdDir(Directory* currentDir, char name[MAX_NAME_LENGTH]) {
    Directory* temp = currentDir->subDirectories;
    while (temp != NULL) {
        if (!strcmp(temp->name, name))
            return temp;
        if (temp->next != NULL)
            temp = temp->next;
        else
            return currentDir;
    }
}

Directory* createmkdir(Directory* currentDir,Directory* nextDir, char name[MAX_NAME_LENGTH]) {
    currentDir->subDirectories = (Directory*)malloc(sizeof(Directory));
    if (currentDir->subDirectories == NULL) {
        return NULL;
    }
    currentDir->subDirectories->next = nextDir;
    currentDir->subDirectories->subDirectories = NULL;
    strcpy(currentDir->subDirectories->name, name);
}
Directory* mkdir(Directory* currentDir, char name[MAX_NAME_LENGTH]) {
    if (currentDir->subDirectories == NULL) {
        if (createmkdir(currentDir, NULL, name) == NULL)
            return NULL;
    }
    else {
        if (createmkdir(currentDir, currentDir->subDirectories, name) == NULL)
            return NULL;
    }
    
}

