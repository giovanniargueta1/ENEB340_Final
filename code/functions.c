#include "datastructures.h"
#include "data_storage.c"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/* should go in datastructures.h
typedef struct ListNode {
    User data;
    struct ListNode* next;

} ListNode;

int countUsers(ListNode* head);
ListNode* searchUser(ListNode* head, const char* name);
void sortListByName(ListNode** head);
void insertUser(ListNode** head, const User* newUser);
void deleteUser(ListNode** head, const char* name);
void updateUser(ListNode* head, const char* name, const User* updatedUser);
void calculateAverages(ListNode* head);
ListNode* searchUser2(ListNode* head, const char* name);
void printList(ListNode* head);
ListNode* createNode(const User* userData);
void freeList(ListNode* head);
void loadDataFromCSV(const char* filename, ListNode** head);
void saveUpdatesToCSV(const char* filename, ListNode* head);
*/

ListNode* searchUser2(ListNode* head, const char* name){
     ListNode* current = head;

    while (current != NULL) {
        if (strcasecmp(current->data.name, name) == 0) {
           
            return current;
        }
        current = current->next;
    }

   
    return NULL;
}


ListNode* createNode(const User* userData) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode != NULL) {
        newNode->data = *userData;
        newNode->next = NULL;
    }
    return newNode;
}


void freeList(ListNode* head) {
    ListNode* current = head;
    ListNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}


int countUsers(ListNode* head) {
    int count = 0;
    ListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

ListNode* searchUser(ListNode* head, const char* name) {
ListNode* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcasecmp(current->data.name, name) == 0) {
            
            printf("Name: %s\nAge: %d\nHeight: %.2f meters\nWeight: %.2f lbs\n\n",
                   current->data.name, current->data.age,
                   current->data.height, current->data.weight);
            found  = 1;
        }
        current = current->next;
    }

    if (found == 0) {
        printf("User not found: %s\n", name);
    }
}
void sortListByName(ListNode** head) {
{
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    int swapped;
    ListNode* temp;
    ListNode* last = NULL;

    do {
        swapped = 0;
        ListNode* current = *head;

        while (current->next != last) {
            if (strcasecmp(current->data.name, current->next->data.name) > 0) {
                temp = createNode(&current->data);
                current->data = current->next->data;
                current->next->data = temp->data;
                free(temp);
                swapped = 1;
            }

            current = current->next;
        }

        last = current;
    } while (swapped);
}
}

void insertUser(ListNode** head, const User* newUser) {
    ListNode* newNode = createNode(newUser);

    if (*head == NULL || strcmp(newUser->name, (*head)->data.name) < 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        ListNode* current = *head;
        while (current->next != NULL && strcmp(newUser->name, current->next->data.name) > 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void deleteUser(ListNode** head, const char* name) {
    ListNode* current = *head;
    ListNode* prev = NULL;

    while (current != NULL && strcmp(current->data.name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    }
}

//DO NOT USE
void updateUser(ListNode* head, const char* name, const User* updatedUser) {
    ListNode* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcasecmp(current->data.name, name) == 0) {
            found = 1;
            strcpy(current->data.name, updatedUser->name);
            current->data.age = updatedUser->age;
            current->data.height = updatedUser->height;
            current->data.weight = updatedUser->weight;
        
            break;  
        }
        current = current->next;
    }

    if (found == 0) {
        printf("User not found: %s\n", name);
    }
}


void calculateAverages(ListNode* head) {
    int count = 0;
    float totalWeight = 0.0;
    float totalHeight = 0.0;

    ListNode* current = head;
    while (current != NULL) {
        count++;
        totalWeight += current->data.weight;
        totalHeight += current->data.height;
        current = current->next;
    }

    if (count > 0) {
        float avgWeight = totalWeight / count;
        float avgHeight = totalHeight / count;
        printf("Average Weight: %.2f lbs\n", avgWeight);
        printf("Average Height: %.2f meters\n", avgHeight);
    } else {
        printf("No users to calculate averages.\n");
    }
}

void printList(ListNode* head) {
    ListNode* current = head;

    while (current != NULL) {
        printf("Name: %s\nAge: %d\nHeight: %.2f meters\nWeight: %.2f lbs\n\n",
               current->data.name, current->data.age,
               current->data.height, current->data.weight);
        current = current->next;
    }
}
void saveUpdatesToCSV(const char* filename, ListNode* head) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Name,Age,Height,Weight\n");

    ListNode* current = head;
    while (current != NULL) {
        fprintf(file, "%s,%d,%.2f,%.2f\n", current->data.name, current->data.age, current->data.height, current->data.weight);
        current = current->next;
    }

    fclose(file);
}
void loadDataFromCSV(const char* filename, ListNode** head) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256]; 
    fgets(line, sizeof(line), file); 

    while (fgets(line, sizeof(line), file) != NULL) {
        
        User newUser;
        sscanf(line, "%49[^,],%d,%f,%f", newUser.name, &newUser.age, &newUser.height, &newUser.weight);

       
        insertUser(head, &newUser);
    }

    fclose(file);
}

