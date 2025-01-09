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
int update_dish_status( const char* filename, Order orders[], int order_count, int order_id, int dish_id);
int updated_paid(const char* filename, Order order[], int order_count, int order_id  );
int delete_order_line(const char* filename, int order_id_to_delete);
double find_price(MenuItem menu[], int menu_count, int dish_id);
void customer_order(MenuItem menu[], int menu_count, const char* order_file);
int get_next_order_id(const char* filename);

#endif // ORDER_H
