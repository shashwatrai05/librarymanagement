// member_management.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member_management.h"

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

    FILE* file = fopen("user_data.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", newUser->username, newUser->password);
        fclose(file);
        printf("User added successfully.\n");
    } else {
        printf("Unable to open file for writing.\n");
    }
}

struct User* readUsersFromFile() {
    FILE* file = fopen("user_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    // Initialize variables
    char line[256];
    struct User* userList = NULL;
    struct User* tail = NULL;

    // Read lines from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line into username and password
        char username[100];
        char password[100];
        if (sscanf(line, "%s %s", username, password) == 2) {
            // Create a new user node
            struct User* newUser = (struct User*)malloc(sizeof(struct User));
            if (newUser == NULL) {
                perror("Memory allocation failed");
                fclose(file);
                freeUserList(userList);  // Free the memory allocated so far
                return NULL;
            }

            // Copy username and password to the new user node
            strcpy(newUser->username, username);
            strcpy(newUser->password, password);
            newUser->next = NULL;

            // Append the new user node to the user list
            if (userList == NULL) {
                userList = newUser;
                tail = newUser;
            } else {
                tail->next = newUser;
                tail = newUser;
            }
        }
    }

    fclose(file);

    return userList;
}


void writeUsersToFile(struct User* userList) {
    FILE* file = fopen("user_data.txt", "w");
    if (file != NULL) {
        struct User* current = userList;
        while (current != NULL) {
            fprintf(file, "%s %s\n", current->username, current->password);
            current = current->next;
        }
        fclose(file);
    } else {
        printf("Unable to open file for writing.\n");
    }
}

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

void freeUserList(struct User* userList) {
    struct User* current = userList;
    struct User* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void memberManagement(struct User** userList) {

    struct User* usersFromFile = readUsersFromFile();

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
                addUser(userList);
                break;
            case 2:
                deleteUser(userList);
                break;
            case 3:
                displayUsers(usersFromFile);  // Display users read from file
                break;
            case 0:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);


    writeUsersToFile(*userList);
    freeUserList(usersFromFile);
}
