// member_management.h

#ifndef MEMBER_MANAGEMENT_H
#define MEMBER_MANAGEMENT_H

// Structure to represent a user
struct User {
    char username[100];
    char password[100];
    struct User* next;  // Pointer to the next user in the linked list
};

// Declare functions related to member management
void addUser(struct User** userList);
void deleteUser(struct User** userList);
void displayUsers(struct User* userList);
//void freeUserList(struct User** userList);  // Pass a pointer to the head of the list
void memberManagement();

#endif
