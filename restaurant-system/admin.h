#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "menu.h"
#include "order.h"

// 管理员操作的函数原型
void admin_menu();
void view_all_users(User users[], int count);
void view_all_menu(MenuItem menu[], int count);
void view_all_orders(Order orders[], int count);
const char* status_name(OrderStatus status);
int change_dish_status(const char* filename, MenuItem menu[], int count, int id);
#endif // ADMIN_H
