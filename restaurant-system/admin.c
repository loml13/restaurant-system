#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* status_name(OrderStatus status)
{
    switch (status)
    {
        case WAITING:
            return "等待处理";
        case COMPLETED:
            return "已完成";
        case PAID:
            return "已支付";
    }
}

void view_all_users(User users[], int count) {
    printf("用户列表:\n");
    for(int i = 0; i < count; i++) {
        printf("ID: %d, 用户名: %s \n, 密码: %s \n" ,
            users[i].id, users[i].username, users[i].password);
    }
}

void view_all_menu(MenuItem menu[], int count) {
    printf("菜单项:\n");
    for(int i = 0; i < count; i++) {
        printf("ID: %d 名称: %s 类型: %s 价格: ￥%.2lf\n 售卖状态: %s",
            menu[i].id, menu[i].name,
            menu[i].type == DISH ? "菜品" : "酒水",
            menu[i].price,
            menu[i].status == NONE ? "已售罄" : "在售中");
        printf("\n");
    }
}

void view_all_orders(Order orders[], int count) {
    printf("订单列表:\n");
    for(int i = 0; i < count; i++) {
        printf("订单ID: %d 餐桌: %d 消费者ID: %d 总金额: ￥%.2lf, 菜品数量: %d\n , 订单状态: %s\n",
            orders[i].order_id, orders[i].table_number,
            orders[i].consumer_id, orders[i].total, orders[i].dish_count,status_name(orders[i].status));

            for (int j = 0 ; j < orders[j].dish_count; j++)
            {
                printf("餐品ID: %d 餐品状态: %s\n", orders[i].dishes[j].dish_id, orders[i].dishes[j].status == DONE ? "已出餐" : "正在制作");
            }
    }


}
int change_dish_status(const char* filename, MenuItem menu[], int count, int id)
{
    MenuItem updated_dish[count];
    memcpy(updated_dish, menu, count * sizeof(MenuItem));
    int dish_result = 0;
    for (int i = 0; i < count; i++)
    {
        if (menu[i].id == id)
        {
            dish_result = 1;
            if (updated_dish[i].status == HAVE)
            {
                printf("目前餐品状态为在售 \n");
            }
            else if (updated_dish[i].status != HAVE)
            {
                int a = 0;
                printf("是否修改菜品状态为在售？ 确认请按1 : ");
                scanf("%d",&a );
                if (a == 1)
                {
                    printf("餐品状态已为在售 \n");
                    updated_dish[i].status = HAVE;
                }
            }
        }
    }
    if (!dish_result)
    {
        printf("未找到菜品 ID=%d\n", id);
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1;  // 无法打开文件
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d %s %d %lf %d",
            updated_dish[i].id,
            updated_dish[i].name,
            updated_dish[i].type,
            updated_dish[i].price,
            updated_dish[i].status);
    fprintf(file, "\n");
    }

    // 关闭文件
    fclose(file);
    system("pause");

    return 0;  // 保存成功
}
