#include "user.h"
#include <stdio.h>
#include <string.h>

int load_users(const char* filename, User users[], int max_users) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;  // 文件打开失败
    }

    int count = 0;
    while (count < max_users) {
        int result = fscanf(file, "%d %49s %49s %d",
                            &users[count].id,
                            users[count].username,
                            users[count].password,
                            (int*)&users[count].role);
        if (result == 4) {

            count++;
        } else {
            break;  // 停止读取
        }
    }

    fclose(file);
    return count;  // 返回成功加载的用户数量
}


int authenticate_user(const char* username, const char* password, User* user, User users[], int user_count) {
    for(int i = 0; i < user_count; i++) {
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            *user = users[i];
            return 1;
        }
    }
    return 0;
}
