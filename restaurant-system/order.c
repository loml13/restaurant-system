#include "order.h"
#include <stdio.h>
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
    FILE* file = fopen(filename, "a");  // 或者 "w" 用于覆盖写入
    if (!file) {
        printf("无法打开文件 %s。\n", filename);
        return -1;  // 无法打开文件
    }

    // 写入订单基本信息
    fprintf(file, "%d %d %d %.2lf %d",
            order->order_id,
            order->table_number,
            order->consumer_id,
            order->total,
            order->dish_count);

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
        // 换行表示一个订单结束
        fprintf(file, "\n");
    }


    // 关闭文件
    fclose(file);

    return 0;  // 保存成功
}




int add_order(Order orders[], int* order_count, Order order) {
    orders[*order_count] = order;  // 将新订单添加到数组
    (*order_count)++;  // 增加订单计数
    save_order("data/orders", &order);  // 将订单保存到文件
    return 0;
}



int update_order_status( const char* filename, Order orders[], int order_count, int order_id, int dish_id)
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
    printf("订单文件更新成功。\n");
    return 1; // 更新成功
}




