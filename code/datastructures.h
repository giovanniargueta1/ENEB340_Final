#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct {
    char name [50];
    int age;
    float height;
    float weight;
} User;

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

#endif

