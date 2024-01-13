// date_management.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date_management.h"

struct DateNode* dateList = NULL;


void addDate(struct Date date) {
    struct DateNode* newDateNode = (struct DateNode*)malloc(sizeof(struct DateNode));
    if (newDateNode == NULL) {
        printf("Memory allocation failed. Unable to add date.\n");
        return;
    }

    newDateNode->date = date;
    newDateNode->next = dateList;
    dateList = newDateNode;
}

void dueDate(struct Date issueDate) {
    struct tm tm_issueDate = {.tm_year = issueDate.year - 1900,
                              .tm_mon = issueDate.month - 1,
                              .tm_mday = issueDate.day};
    time_t t_issueDate = mktime(&tm_issueDate);

    time_t t_dueDate = t_issueDate + CHECKOUT_PERIOD * 24 * 60 * 60; // seconds in a day

    struct tm* tm_dueDate = localtime(&t_dueDate);
    printf("Due Date: %02d/%02d/%04d\n", tm_dueDate->tm_mday, tm_dueDate->tm_mon + 1, tm_dueDate->tm_year + 1900);

   
    addDate(issueDate);
}


void lateFine(struct Date returnDate, struct Date issueDate) {
    struct tm tm_returnDate = {.tm_year = returnDate.year - 1900,
                                .tm_mon = returnDate.month - 1,
                                .tm_mday = returnDate.day};
    time_t t_returnDate = mktime(&tm_returnDate);

    struct tm tm_issueDate = {.tm_year = issueDate.year - 1900,
                              .tm_mon = issueDate.month - 1,
                              .tm_mday = issueDate.day};
    time_t t_issueDate = mktime(&tm_issueDate);

    int daysLate = (t_returnDate - t_issueDate) / (24 * 60 * 60); // seconds in a day

    if (daysLate > 0) {
        int fine = daysLate * 2; // Adjust the fine calculation as needed
        printf("Late Fine: %d\n", fine);
    } else {
        printf("No late fine.\n");
    }
}

void dateManagement(struct Book* catalog, int catalogSize) {
    struct Date issueDate;
    struct Date returnDate;

    printf("Enter the issue date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &issueDate.day, &issueDate.month, &issueDate.year);

    dueDate(issueDate);

    printf("Enter the return date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &returnDate.day, &returnDate.month, &returnDate.year);

    lateFine(returnDate, issueDate);
}
