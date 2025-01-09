#include "user.h"
#include "menu.h"
#include "order.h"
#include "admin.h"
#include "cashier.h"
#include <stdio.h>


#define MAX_USERS 100
#define MAX_MENU 100
#define MAX_ORDERS 1000

User users[MAX_USERS];
MenuItem menu[MAX_MENU];
Order orders[MAX_ORDERS];


int main() {

    printf("顾客用户名:consumer || 密码:cons123 \n");

    int user_count = load_users("data/users", users, MAX_USERS);
    int menu_count = load_menu("data/menu", menu, MAX_MENU);
    int order_count = load_orders("data/orders", orders, MAX_ORDERS);

    if(user_count < 0 || menu_count < 0 || order_count < 0) {
        printf("加载数据文件时出错。\n");
        if (user_count < 0) printf("%i\n", user_count);
        if (menu_count < 0) printf("%i\n", menu_count);
        if (order_count < 0) printf("%i\n", order_count);
        return 1;
    }

    char username[50];
    char password[50];
    printf("登录:\n用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);

    User current_user;
    if(!authenticate_user(username, password, &current_user, users, user_count)) {
        printf("认证失败。\n");
        return 1;
    }

    printf("欢迎, %s!\n", current_user.username);

    switch(current_user.role) {
    case ADMIN:
        int choice;

        while(1)
        {
            printf("1.查询系统用户 \n"
               "2.查询所有菜单 \n"
               "3.查询所有订单 \n"
               "4.修改餐品售卖状态 \n"
               "5.删除订单内容 \n"
               "6.退出系统 \n"
               "输入选项: ");
            scanf("%d", &choice);
            switch(choice)
            {
            case 1:
                view_all_users(users, user_count);
                break;

            case 2:
                view_all_menu(menu, menu_count);
                break;

            case 3:
                view_all_orders(orders, order_count);
                break;

            case 4:
                int dish_id;
                printf("请输入想修改的菜品ID");
                scanf("%d", &dish_id);

                change_dish_status("data/menu", menu, menu_count, dish_id );
                break;

                case 5:
                    int order_id_to_delete;
                    printf("请输入想删除的订单ID");
                    scanf("%d", &order_id_to_delete);

                    delete_order_line("data/orders", order_id_to_delete);
                    break;
            case 6:
                return 0;

            default:
                printf("输入错误");

            }
        }

    break;

    case CASHIER:

        while(1)
        {
            printf("请选择操作: \n"
                "1. 查看所有订单\n"
                "2. 结账\n"
                "3.退出系统\n"
                "输入选项: ");
            scanf("%d", &choice);
            switch (choice)
            {
                case 1:
                    view_all_orders(orders, order_count);
                    break;
                case 2:
                    payment(orders , order_count);
                    break;
                case 3:
                    return 0;

                default:
                printf("该去刷盘子了 \n" );

            }
        }

    case CHEF:
        while(1)
        {
            printf("1.查看所有订单 \n"
                     "2.更改菜品状态 \n"
                     "3.退出系统 \n"
                     "请输入选项: ");
            scanf("%d" , &choice);

            switch(choice)
            {
                case 1:
                    view_all_orders(orders, order_count);

                    break;

                case 2:
                    int order_id , dish_id;

                printf("请输入想要修改的订单ID和菜品ID: ");
                if (scanf("%d %d", &order_id, &dish_id) != 2) {
                    printf("输入无效，请输入数字。\n");
                    while (getchar() != '\n'); // 清除输入缓冲区
                    continue;
                }
                if (order_id < 0 || order_id > order_count) {
                    printf("订单ID无效。\n");
                    continue;
                }

                update_dish_status("data/orders",orders, order_count, order_id, dish_id);
                    break;
                case 3:
                    return 0;

                default:

        break;
            }
        }
    case WAITER:
        view_all_orders(orders, order_count);
        break;
    case BOSS:

        while (1)
        {
            printf("1.查询系统用户 \n"
               "2.查询所有菜单 \n"
               "3.查询所有订单 \n"
               "4.修改餐品售卖状态 \n"
               "5.添加新菜品 \n"
               "6.删除订单内容 \n"
               "7.退出系统 \n"
               "输入选项: ");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                view_all_users(users, user_count);
                break;

            case 2:
                view_all_menu(menu, menu_count);
                break;

            case 3:
                view_all_orders(orders, order_count);
                break;

            case 4:
                int dish_id;
                printf("请输入想修改的菜品ID");
                scanf("%d", &dish_id);

                change_dish_status("data/menu", menu, menu_count, dish_id );
                break;

            case 5:
                add_menu("data/menu");
                break;

            case 6:
                int order_id_to_delete;
                printf("请输入想删除的订单ID");
                scanf("%d", &order_id_to_delete);

                delete_order_line("data/orders", order_id_to_delete);
                break;

            case 7:
                return 0;

            default:printf("下班");

            }

        }

    case CONSUMER:
        Order order;

        customer_order(menu,  menu_count, "data/orders");

        break;
    default:
        printf("恭喜触发隐藏剧情，请前往后厨刷一百个盘子。\n");
    }

    return 0;
}
