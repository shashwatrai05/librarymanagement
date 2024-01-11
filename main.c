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
int userCount = 0;

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

void userBookCirculation();
void adminBookCirculation();
void searchAndBrowse();
void dateManagement(struct Book* catalog, int catalogSize);

// Function to display the login menu
int displayLoginMenu() {
    int choice;
    printf("Login Menu:\n");
    printf("\t 1. Log in as Admin\n");
    printf("\t 2. Log in as User\n");
    printf("\t 0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    int choice;
    int userType = -1;

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
            case 1:
                {
                    char inputUsername[100];
                    char inputPassword[100];

                    printf("Enter Admin username: ");
                    scanf("%s", inputUsername);

                    printf("Enter Admin password: ");
                    scanf("%s", inputPassword);

                    if (strcmp(inputUsername, ADMIN_USERNAME) == 0 && strcmp(inputPassword, ADMIN_PASSWORD) == 0) {
                        userType = 0;
                    } else {
                        printf("Admin login failed. Invalid username or password.\n");
                    }

                    if (userType == 0) {
                        printf("Admin login successful.\n");
                    }
                }
                break;
            case 2:
                {
                    char inputUsername[100];
                    char inputPassword[100];

                    printf("Enter User username: ");
                    scanf("%s", inputUsername);

                    printf("Enter User password: ");
                    scanf("%s", inputPassword);

                    int userIndex;
                    for (userIndex = 0; userIndex < userCount; userIndex++) {
                        if (strcmp(users[userIndex].username, inputUsername) == 0 && strcmp(users[userIndex].password, inputPassword) == 0) {
                            userType = 1;
                            break;
                        }
                    }

                    if (userIndex == userCount) {
                        printf("User login failed. Invalid username or password.\n");
                    }

                    if (userType == 1) {
                        printf("User login successful. Welcome, %s!\n", users[userIndex].username);
                    }
                }
                break;
            case 0:
                printf("\nGoodbye! Exiting the program.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (userType == -1 && choice != 0);

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
            printf("\t 99. Back to Login\n");  // Added option to go back to login
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

    // Free memory used by linked lists before exiting
    //freeBookList(&catalog);
    //freeUserList(&users);

    return 0;
}
