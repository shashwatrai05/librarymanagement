// member_management.h

#ifndef MEMBER_MANAGEMENT_H
#define MEMBER_MANAGEMENT_H

struct User {
    char username[100];
    char password[100];
    struct User* next;  
};

extern struct User* readUsersFromFile();
extern int countUsers(struct User* userList);
extern void freeUserList(struct User* userList);
extern void memberManagement(struct User** userList);

void addUser(struct User** userList);
void deleteUser(struct User** userList);
void displayUsers(struct User* userList);

#endif
