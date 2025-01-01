#ifndef MENU_H
#define MENU_H

typedef enum
{
    DISH = 0,
    DRINK
} MenuType;

typedef enum
{
    NONE = 0,
    HAVE
}solve;

typedef struct {
    int id;
    char name[100];
    MenuType type;
    double price;
    solve status;
} MenuItem;

// 函数原型
int load_menu(const char* filename, MenuItem menu[], int max_items);


#endif // MENU_H
