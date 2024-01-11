// search_and_browse.c

#include <stdio.h>
#include <string.h>
#include "search_and_browse.h"
#include "book_circulation.h"

// Function to search for books by author's name
void searchByAuthor(const char authorName[], struct BookNode* catalogHead) {
    printf("Books by Author: %s\n", authorName);

    struct BookNode* current = catalogHead;

    while (current != NULL) {
        if (strcmp(current->book.author, authorName) == 0) {
            // Print the book's details
            printf("Title: %s\n", current->book.title);
            printf("Author: %s\n", current->book.author);
            printf("ISBN: %d\n", current->book.ISBN);

            // Check if the book is in circulation
            if (current->book.availability == 0) {
                printf("Book is available for circulation.\n");
            } else {
                printf("Book is not available for circulation.\n");
            }
            printf("\n"); // Add a newline for better readability
        }

        current = current->next;
    }
}

// Function to search for books by title
void searchByTitle(const char titleName[], struct BookNode* catalogHead) {
    printf("Books with Title: %s\n", titleName);

    struct BookNode* current = catalogHead;

    while (current != NULL) {
        // Check if the input title is a substring of the actual title
        if (strstr(current->book.title, titleName) != NULL) {
            // Print the book's details
            printf("Title: %s\n", current->book.title);
            printf("Author: %s\n", current->book.author);
            printf("ISBN: %d\n", current->book.ISBN);

            // Check if the book is in circulation
            if (current->book.availability == 0) {
                printf("Book is available for circulation.\n");
            } else {
                printf("Book is not available for circulation.\n");
            }
            printf("\n"); // Add a newline for better readability
        }

        current = current->next;
    }
}

// Function to search and browse books
void searchAndBrowse() {
    int choice;

    do {
        printf("\nSearch and Browse Menu:\n");
        printf("1. Search by Author\n");
        printf("2. Search by Title\n");
        printf("0. Go back to the main menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char authorName[100];
                printf("Enter author's name: ");
                scanf("%s", authorName);
                searchByAuthor(authorName, catalogHead);
                break;
            }
            case 2: {
                char titleName[100];
                printf("Enter title: ");
                scanf("%s", titleName);
                searchByTitle(titleName, catalogHead);
                break;
            }
            case 0:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}