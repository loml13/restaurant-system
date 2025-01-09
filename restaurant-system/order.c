#include "order.h"
#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_orders(const char* filename, Order orders[], int max_orders) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;  // 文件打开失败
    }

    int count = 0;
    while (count < max_orders) {
        int result = fscanf(file, "%d %d %d %lf %d %d",
                            &orders[count].order_id,
                            &orders[count].table_number,
                            &orders[count].consumer_id,
                            &orders[count].total,
                            &orders[count].dish_count,
                            &orders[count].status);
        if (result == 6) {


            // 加载订单中的每道菜
            for (int i = 0; i < orders[count].dish_count; i++) {
                int dish_result = fscanf(file, "%d %d",
                                         &orders[count].dishes[i].dish_id,
                                         (int*)&orders[count].dishes[i].status);
                if (dish_result != 2) {
                    printf("加载菜品失败，订单 ID=%d, 返回值=%d\n", orders[count].order_id, dish_result);
                    break;
                }
            }
            count++;
        } else {

            break;
        }
    }

    fclose(file);
    return count;  // 返回成功加载的订单数量
}


int save_order(const char* filename, Order* order ) {
    // 打开文件进行追加模式写入
    FILE* file = fopen(filename, "a");
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1;  // 无法打开文件
    }

    // 写入订单基本信息
    fprintf(file, "%d %d %d %.2lf %d %d",
            order->order_id,
            order->table_number,
            order->consumer_id,
            order->total,
            order->dish_count,
            order->status);

    // 遍历并写入菜品信息
    for (int i = 0; i < order->dish_count; i++) {
        fprintf(file, " %d %d", order->dishes[i].dish_id, order->dishes[i].status);
    }

    // 换行，表示一个订单结束
    fprintf(file, "\n");

    // 关闭文件
    fclose(file);

    return 0;  // 保存成功
}


int updated_paid(const char* filename, Order order[], int order_count, int order_id  ) {

    Order new_order[order_count];
    memcpy(new_order, order, order_count * sizeof(Order));
    int order_result = 0;
    for (int i = 0; i < order_count; i++)
    {
        if (order[i].order_id == order_id)
        {
            order_result = 1;
            new_order[i].status = PAID;
        }
    }
    if (!order_result)
    {
        printf("未找到订单 ID=%d\n", order_id);
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1;  // 无法打开文件
    }

    for (int i = 0; i < order_count; i++)
    {
        fprintf(file, "%d %d %d %.2lf %d %d",
            new_order[i].order_id,
            new_order[i].table_number,
            new_order[i].consumer_id,
            new_order[i].total,
            new_order[i].dish_count,
            new_order[i].status);

        // 遍历并写入菜品信息
        for (int j = 0; j < order->dish_count; j++) {
            fprintf(file, " %d %d", new_order[i].dishes[j].dish_id, new_order[i].dishes[j].status);
        }

    }
    // 换行表示一个订单结束
    fprintf(file, "\n");

    // 关闭文件
    fclose(file);

    return 0;  // 保存成功
}



int update_dish_status( const char* filename, Order orders[], int order_count, int order_id, int dish_id)
{
    Order updataed[MAX_ORDERS];
    memcpy(updataed, orders, sizeof(Order)* order_count);

    int order_found = 0;
    int dish_found = 0;

    for (int i = 0; i < order_count; i++)
    {
        if (orders[i].order_id == order_id)
        {
            order_found = 1;
            for (int j = 0; j < orders[i].dish_count; j++)
            {
                if (orders[i].dishes[j].dish_id == dish_id)
                {
                    dish_found = 1;
                    if (orders[i].dishes[j].status == 0)
                    {
                        printf("菜品已完成，无需修改 \n");
                        return 0;
                    }

                    updataed[i].dishes[j].status = 0;
                    printf("菜品状态更新完成: 订单ID: %d, 菜品ID: %d \n", order_id ,dish_id );
                }
            }
        }
    }
    if (!order_found)
    {
        printf("未找到订单ID: %d", order_id);
    }

    if (!dish_found)
    {
        printf("未找到菜品ID: %d", dish_id);
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1; // 文件打开失败
    }

    for (int i = 0; i < order_count; i++) {
        // 写入订单基本信息
        fprintf(file, "%d %d %d %.2lf %d %d",
                updataed[i].order_id,
                updataed[i].table_number,
                updataed[i].consumer_id,
                updataed[i].total,
                updataed[i].dish_count,
                updataed[i].status);

        // 写入订单中的每道菜
        for (int j = 0; j < updataed[i].dish_count; j++) {
            fprintf(file, " %d %d", updataed[i].dishes[j].dish_id, updataed[i].dishes[j].status);
        }

        // 换行，表示一个订单结束
        fprintf(file, "\n");
    }

    fclose(file);
    printf("订单文件更新成功按任意键返回系统。\n");
    system("pause");
    return 1; // 更新成功
}


int delete_order_line(const char* filename, int order_id_to_delete)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1; // 打开文件失败
    }

    FILE* temp_file = fopen("data/temp", "w");
    if (!temp_file) {
        printf("无法创建临时文件。\n");
        fclose(file);
        return -1; // 创建临时文件失败
    }

    char line[100];
    int line_deleted = 0;

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) {
        int order_id;
        sscanf(line, "%d", &order_id); // 读取订单ID

        if (order_id == order_id_to_delete) {
            printf("已删除订单ID: %d\n", order_id);
            line_deleted = 1;
            continue; // 跳过需要删除的行
        }

        fputs(line, temp_file); // 将其他行写入临时文件
    }

    fclose(file);
    fclose(temp_file);

    // 用临时文件覆盖原文件
    if (line_deleted) {
        if (remove(filename) == 0 && rename("data/temp", filename) == 0) {
            printf("订单删除成功按任意键退出系统。\n");
            system("pause");
            return 1; // 删除成功
        } else {
            printf("删除原文件或重命名临时文件失败。\n");
            return -1; // 文件操作失败
        }
    } else {
        remove("data/temp"); // 删除临时文件
        printf("未找到订单ID: %d。\n", order_id_to_delete);
        return -1; // 未找到需要删除的订单
    }
}

double find_price(MenuItem menu[], int menu_count, int dish_id) {
    for (int i = 0; i < menu_count; i++) {
        if (menu[i].id == dish_id) {
            return menu[i].price; // 找到菜品价格
        }
    }
    return 0.0; // 如果未找到，返回0
}

void customer_order(MenuItem menu[], int menu_count, const char* order_file) {
    Order order;

    // 从文件中获取下一个订单ID
    order.order_id = get_next_order_id(order_file);

    printf("您的订单ID为: %d\n", order.order_id);
    printf("请输入您的餐桌号: ");
    scanf("%d", &order.table_number);
    printf("请输入您的等位号: ");
    scanf("%d", &order.consumer_id);

    printf("当前菜单:\n");
    view_all_menu(menu, menu_count);

    printf("请输入您期望点的菜品数量: ");
    scanf("%d", &order.dish_count);

    order.total = 0.0; // 初始化总金额
    order.status = 2;

    for (int i = 0; i < order.dish_count; i++) {
        printf("请输入菜品ID (%d/%d): ", i + 1, order.dish_count);
        scanf("%d", &order.dishes[i].dish_id);

        double price = find_price(menu, menu_count, order.dishes[i].dish_id);
        if (price == 0.0) {
            printf("未找到菜品ID: %d，请重新输入。\n", order.dishes[i].dish_id);
            i--; // 重新输入
            continue;
        }

        order.dishes[i].status = 1; // 设置菜品为未完成
        order.total += price; // 累加总金额
        printf("菜品ID: %d, 单价: %.2lf, 当前总金额: %.2lf\n", order.dishes[i].dish_id, price, order.total);
    }

    printf("订单创建成功，总金额: %.2lf\n", order.total);

    // 保存订单到文件
    if (save_order(order_file, &order) == 0) {
        printf("订单已保存到文件。\n");
    } else {
        printf("订单保存失败。\n");
    }
}


int get_next_order_id(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开订单文件 %s，默认从订单ID=1开始。\n", filename);
        return 1; // 文件不存在时，返回初始订单ID
    }

    int max_id = 0;
    int current_id;

    // 逐行读取订单文件
    while (fscanf(file, "%d", &current_id) == 1) {
        if (current_id > max_id) {
            max_id = current_id; // 更新最大订单ID
        }
        // 跳过当前行剩余内容
        char line[512];
        fgets(line, sizeof(line), file);
    }

    fclose(file);
    return max_id + 1; // 返回下一个订单ID
}
