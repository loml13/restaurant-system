#ifndef USER_H
#define USER_H

typedef enum {
    CONSUMER = 0,
    CASHIER = 1,
    CHEF = 2,
    WAITER =3,
    BOSS = 4,
    ADMIN = 5
} UserRole;

typedef struct {
    int id;
    char username[50];
    char password[50];
    UserRole role;
} User;

// 函数原型
int load_users(const char* filename, User users[], int max_users);
int authenticate_user(const char* username, const char* password, User* user, User users[], int user_count);

#endif // USER_H
