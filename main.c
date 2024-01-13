// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_circulation.h"
#include "date_management.h"
#include "search_and_browse.h"
#include "member_management.h"

struct Book* catalog = NULL;
int catalogSize = 0;

struct User* users = NULL;
int userCount=0;

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

void userBookCirculation();
void adminBookCirculation();
void searchAndBrowse();
void dateManagement(struct Book* catalog, int catalogSize);

int countUsers(struct User* userList) {
    int count = 0;
    struct User* current = userList;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

int displayLoginMenu() {
    int choice;
    printf("Login Menu:\n");
    printf("\t 1. Log in as Admin\n");
    printf("\t 2. Log in as User\n");
    printf("\t 0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Return the user type based on successful login
    if (choice == 1) {
        char inputUsername[100];
        char inputPassword[100];

        printf("Enter Admin username: ");
        scanf("%s", inputUsername);

        printf("Enter Admin password: ");
        scanf("%s", inputPassword);

        if (strcmp(inputUsername, ADMIN_USERNAME) == 0 && strcmp(inputPassword, ADMIN_PASSWORD) == 0) {
            printf("Admin login successful.\n");
            return 0; // Admin user type
        } else {
            printf("Admin login failed. Invalid username or password.\n");
        }
    } else if (choice == 2) {
        users = readUsersFromFile();  // Read users from the file
        userCount = countUsers(users); // Update userCount

        if (userCount == 0) {
            printf("No users available. Please contact the administrator.\n");
            return -1; // Login failed
        }

        char inputUsername[100];
        char inputPassword[100];
        int loggedIn = 0;

        do {
            printf("Enter User username: ");
            scanf("%s", inputUsername);

            printf("Enter User password: ");
            scanf("%s", inputPassword);

            int userIndex;
            for (userIndex = 0; userIndex < userCount; userIndex++) {
                if (strcmp(users[userIndex].username, inputUsername) == 0 && strcmp(users[userIndex].password, inputPassword) == 0) {
                    printf("User login successful. Welcome, %s!\n", users[userIndex].username);
                    loggedIn = 1;
                    break;
                }
            }

            if (!loggedIn) {
                printf("User login failed. Invalid username or password. Please try again.\n");
            }
        } while (!loggedIn);

        // Free the memory allocated for the user list after the loop
        freeUserList(users);

        return 1; // Regular user type
    }

    return -1; // Login failed
}



int main() {
    int choice;
    int userType = -1;

    // Assuming users array is correctly initialized before calling displayLoginMenu
    // Initialize the users array for testing
    users = readUsersFromFile();  // This should read the users from the file

    do {
        system("clear || cls");

        printf("\x1B[32m");
        printf("\n");
        printf("*************************************************\n");
        printf("*************************************************\n");
        printf("************ LIBRARY MANAGEMENT SYSTEM ************\n");
        printf("*************************************************\n");
        printf("*************************************************\n");
        printf("\n");

        printf("\x1B[0m");

        choice = displayLoginMenu();

        switch (choice) {
            case 0:
                userType = 0; // Admin user type
                break;
            case 1:
                userType = 1; // Regular user type
                break;
            case -1:
                return 0; // Exit the program if login fails
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (userType == -1);

    if (userType != -1) {
        do {
            system("clear || cls");

            printf("\x1B[32m");
            printf("\n");
            printf("*************************************************\n");
            printf("*************************************************\n");
            printf("************ LIBRARY MANAGEMENT SYSTEM ************\n");
            printf("*************************************************\n");
            printf("*************************************************\n");
            printf("\n");

            printf("\x1B[0m");

            printf("Menu:\n");
            printf("\x1B[36m");
            printf("\t 1. Book Circulation\n");
            printf("\t 2. Members management\n");
            printf("\t 3. Search for a Book\n");
            printf("\t 4. Date Management\n");
            printf("\x1B[0m");
            printf("\t 0. Exit\n");
            printf("\t 99. Back to Login\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    if (userType == 1) {
                        userBookCirculation();
                    } else if (userType == 0) {
                        adminBookCirculation();
                    } else {
                        printf("Please log in as a user or admin first.\n");
                    }
                    break;
                case 2:
                    if (userType == 1) {
                        printf("This feature is only available for admins.\n");
                    } else if (userType == 0) {
                        memberManagement(&users);
                    } else {
                        printf("Please log in as an admin or user to access this feature.\n");
                    }
                    break;
                case 3:
                    if (userType == 1 || userType == 0) {
                        searchAndBrowse(catalog, catalogSize);
                    } else {
                        printf("Please log in as a user first.\n");
                    }
                    break;
                case 4:
                    if (userType == 1 || userType == 0) {
                        dateManagement(catalog, catalogSize);
                    } else {
                        printf("Please log in as a user or admin first.\n");
                    }
                    break;
                case 0:
                    printf("\nGoodbye! Exiting the program.\n");
                    break;
                case 99:
                    // Option to go back to login
                    userType = -1;
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    break;
            }
        } while (choice != 0 && userType != -1);
    }

    //freeBookList(&catalog);
    //freeUserList(&users);

    return 0;
}
