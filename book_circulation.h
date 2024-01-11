// book_circulation.h

#ifndef BOOK_CIRCULATION_H
#define BOOK_CIRCULATION_H

struct Book {
    char title[100];
    char author[100];
    int ISBN;
    int availability;
    struct Book* next;
};

struct BookNode {
    struct Book book;
    struct BookNode* next;
};

extern struct BookNode* catalogHead;

void addBook();
void deleteBook();
void issueBook();
void returnBook();
void adminBookCirculation();
void userBookCirculation();

#endif
