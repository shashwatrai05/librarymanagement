// member_management.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member_management.h"

// void freeUserList(struct User** head) {
//     struct User* current = *head;
//     struct User* next;

//     while (current != NULL) {
//         next = current->next;
//         free(current);
//         current = next;
//     }

//     *head = NULL;  // Set the head to NULL after freeing all nodes
// }


// Function to add a user
void addUser(struct User** userList) {
    printf("Enter new user details:\n");

    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        printf("Memory allocation failed. Unable to add user.\n");
        return;
    }

    printf("Username: ");
    scanf("%s", newUser->username);

    printf("Password: ");
    scanf("%s", newUser->password);

    newUser->next = *userList;
    *userList = newUser;

    printf("User added successfully.\n");
}

// Function to delete a user
void deleteUser(struct User** userList) {
    if (*userList == NULL) {
        printf("No users to delete.\n");
        return;
    }

    printf("Enter username to delete: ");
    char usernameToDelete[100];
    scanf("%s", usernameToDelete);

    struct User* current = *userList;
    struct User* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->username, usernameToDelete) == 0) {
            if (prev == NULL) {
                *userList = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            printf("User deleted successfully.\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("User not found.\n");
}

// Function for user login
int login(struct User* userList) {
    if (userList == NULL) {
        printf("No users available for login.\n");
        return -1;
    }

    printf("Enter username: ");
    char inputUsername[100];
    scanf("%s", inputUsername);

    printf("Enter password: ");
    char inputPassword[100];
    scanf("%s", inputPassword);

    // Check if the entered credentials match any user
    int index = 1;
    struct User* current = userList;
    while (current != NULL) {
        if (strcmp(current->username, inputUsername) == 0 &&
            strcmp(current->password, inputPassword) == 0) {
            return index; // Return index as user type
        }

        current = current->next;
        index++;
    }

    return -1; // Login failed
}

// Function to display all users
void displayUsers(struct User* userList) {
    if (userList == NULL) {
        printf("No users to display.\n");
        return;
    }

    printf("List of users:\n");
    struct User* current = userList;
    while (current != NULL) {
        printf("Username: %s\n", current->username);
        printf("---------------\n");
        current = current->next;
    }
}

// Function to free the memory used by the user list
void freeUserList(struct User* userList) {
    struct User* current = userList;
    struct User* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function for member management menu
void memberManagement() {
    struct User* userList = NULL;  // Initialize an empty linked list

    int choice;

    do {
        printf("\nMember Management Menu:\n");
        printf("1. Add User\n");
        printf("2. Delete User\n");
        printf("3. Display Users\n");
        printf("0. Go back to the main menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser(&userList);
                break;
            case 2:
                deleteUser(&userList);
                break;
            case 3:
                displayUsers(userList);
                break;
            case 0:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free the memory used by the user list before exiting
    //freeUserList(userList);
}
