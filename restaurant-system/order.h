#ifndef ORDER_H
#define ORDER_H

#include "menu.h"

#define MAX_DISHES 100
#define MAX_ORDERS 1000

typedef enum {
    PENDING = 1,
    DONE = 0
} DishStatus;

typedef enum
{
    WAITING = 2,
    COMPLETED = 1,
    PAID = 0
} OrderStatus;

typedef struct {
    int dish_id;
    DishStatus status;
} OrderDish;

typedef struct {
    int order_id;
    int table_number;
    int consumer_id;
    OrderDish dishes[MAX_DISHES];
    int dish_count;
    double total;
    OrderStatus status;
} Order;

// 函数原型
int load_orders(const char* filename, Order orders[], int max_orders);
int save_order(const char* filename, Order* order );
int add_order(Order orders[], int* order_count, Order order);
int update_order_status( const char* filename, Order orders[], int order_count, int order_id, int dish_id);
int updated_paid(const char* filename, Order order[], int order_count, int order_id  );

#endif // ORDER_H
