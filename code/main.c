#include "datastructures.h"
#include "functions.c"
#include "data_storage.c"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



int main() {
   

    ListNode* userList = NULL;

    loadDataFromCSV("ENEB340.csv", &userList);


    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        insertUser(&userList, &users[i]);
    }
    int choice;
    char searchName[50];
    User newUser, updatedUser;

    do {
        
        printf("\nMenu: Hey!!!! Select an Option to Perform\n");
        printf("----------------------------------\n");
        printf("1. Count the Number of Users\n");
        printf("2. Search for a User\n");
        printf("3. Sort List by Name\n");
        printf("4. Add a New User\n");
        printf("5. Remove a User\n");
        printf("6. Update User Information\n");
        printf("7. Calculate Averages\n");
        printf("8. Exit\n");


        scanf("%d", &choice);

      
        switch (choice) {
            case 1:
                printf("Number of Users: %d\n", countUsers(userList));
                while ((getchar()) != '\n');
                break;

            case 2:
                printf("Enter the name to search: ");
                scanf("%s", searchName);
                searchUser(userList, searchName);
                getchar();
                break;

            case 3:
                sortListByName(&userList);
                printf("List sorted by name:\n");
                printList(userList);
                break;

            case 4:
                printf("Enter user details:\n");
                printf("Name: ");
                scanf("%s", newUser.name);
                printf("Age: ");
                scanf("%d", &newUser.age);
                printf("Height: ");
                scanf("%f", &newUser.height);
                printf("Weight: ");
                scanf("%f", &newUser.weight);
            

                insertUser(&userList, &newUser);
                printf("User added.\n");

                saveUpdatesToCSV("ENEB340.csv", userList);
                break;

            case 5:
                printf("Enter the name to remove: ");
                scanf("%s", searchName);
                deleteUser(&userList, searchName);
                printf("User removed.\n");
                
                saveUpdatesToCSV("ENEB340.csv", userList);
                break;

            case 6:
                printf("Enter the User to update: ");
                scanf("%s", searchName);
                getchar();

                ListNode* foundUser = searchUser2(userList, searchName);

                if (foundUser != NULL) {
                    User updatedUser;

                    printf("Enter updated user details:\n");
                    printf("Name: ");
                    scanf("%s", updatedUser.name);
                    printf("Age: ");
                    scanf("%d", &updatedUser.age);
                    printf("Height: ");
                    scanf("%f", &updatedUser.height);
                    printf("Weight: ");
                    scanf("%f", &updatedUser.weight);

                    printf("Do you want to update this user? (Y/N): ");
                    char choice;
                    scanf(" %c", &choice);

                    if(toupper(choice) == 'Y'){
                       
                    deleteUser(&userList, searchName);
                    insertUser(&userList, &updatedUser);
                     
                     printf("User details updated:\n");
                     printf("Name: %s\nAge: %d\nHeight: %.2f meters\nWeight: %.2f lbs\n\n",
                   updatedUser.name, updatedUser.age,
                   updatedUser.height, updatedUser.weight);
                    }else {
                        
                        printf("User update canceled.\n");
                    }
                } else {
                   
                    printf("User not found: %s\n", searchName);
                }
                
                saveUpdatesToCSV("ENEB340.csv", userList);
                break;

            case 7:
                calculateAverages(userList);
                break;

            case 8:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }

    } while (choice != 8);

    saveUpdatesToCSV("ENEB340.csv", userList);
    freeList(userList);
   

    return 0;
}
