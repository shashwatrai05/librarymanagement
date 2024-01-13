// book_circulation.c

#include <stdio.h>
#include <stdlib.h>
#include "book_circulation.h"

struct BookNode* catalogHead = NULL;



// void freeBookList(struct BookNode** head) {
//     struct BookNode* current = *head;
//     struct BookNode* next;

//     while (current != NULL) {
//         next = current->next;
//         free(current);
//         current = next;
//     }

//     *head = NULL;
// }

void addBook() {
    printf("Enter book details:\n");

    struct BookNode* newBookNode = (struct BookNode*)malloc(sizeof(struct BookNode));
    if (newBookNode == NULL) {
        printf("Memory allocation failed. Unable to add a book.\n");
        return;
    }

    printf("Title: ");
    scanf("%s", newBookNode->book.title);
    printf("Author: ");
    scanf("%s", newBookNode->book.author);
    printf("ISBN: ");
    scanf("%d", &newBookNode->book.ISBN);
    newBookNode->book.availability = 1; 
    newBookNode->next = catalogHead;
    catalogHead = newBookNode;

    printf("Book added to the catalog.\n");
}

void deleteBook() {
    int ISBN;

    printf("Enter the ISBN of the book to delete: ");
    scanf("%d", &ISBN);

    struct BookNode* current = catalogHead;
    struct BookNode* prev = NULL;
    int found = 0;

    while (current != NULL) {
        if (current->book.ISBN == ISBN) {
            if (prev == NULL) {
                // Deleting the first node
                catalogHead = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            found = 1;
            printf("Book deleted from the catalog.\n");
            break;
        }

        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("Book not found in the catalog.\n");
    }
}


void issueBook() {
    int ISBN;

    printf("Enter the ISBN of the book to issue: ");
    scanf("%d", &ISBN);

    struct BookNode* current = catalogHead;
    int found = 0;

    while (current != NULL) {
        if (current->book.ISBN == ISBN) {
            if (current->book.availability == 1) {
                current->book.availability = 0;  // Set book as unavailable
                printf("Book issued successfully.\n");
            } else {
                printf("Book is not available for issue.\n");
            }

            found = 1;
            break;
        }

        current = current->next;
    }

    if (!found) {
        printf("Book not found in the catalog.\n");
    }
}

void returnBook() {
    int ISBN;

    printf("Enter the ISBN of the book to return: ");
    scanf("%d", &ISBN);

    struct BookNode* current = catalogHead;
    int found = 0;

    while (current != NULL) {
        if (current->book.ISBN == ISBN) {
            if (current->book.availability == 0) {
                current->book.availability = 1;  // Set book as available
                printf("Book returned successfully.\n");
            } else {
                printf("Invalid operation. The book is not issued.\n");
            }

            found = 1;
            break;
        }

        current = current->next;
    }

    if (!found) {
        printf("Book not found in the catalog.\n");
    }
}


void adminBookCirculation() {
    int choice;

    do {
        printf("Catalog Management (Admin):\n");
        printf("1. Add a book\n");
        printf("2. Delete a book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 0:
                printf("Exiting Catalog Management.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void userBookCirculation() {
    int choice;

    do {
        printf("Catalog Management (User):\n");
        printf("1. Issue a book\n");
        printf("2. Return a book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                issueBook();
                break;
            case 2:
                returnBook();
                break;
            case 0:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}
