// date_management.h

#ifndef DATE_MANAGEMENT_H
#define DATE_MANAGEMENT_H

#include "book_circulation.h"

#define CHECKOUT_PERIOD 14

struct Date {
    int day;
    int month;
    int year;
};

struct DateNode {
    struct Date date;
    struct DateNode* next;
};

void dueDate(struct Date issueDate);
void lateFine(struct Date returnDate, struct Date dueDate);
void dateManagement(struct Book* catalog, int catalogSize);

#endif
