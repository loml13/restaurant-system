#include "menu.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

int load_menu(const char* filename, MenuItem menu[], int max_items) {
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }
    int count = 0;
    int type;
    int status;
    while (count < max_items && fscanf(file, "%d %s %d %lf %d",
        &menu[count].id, menu[count].name,
        &type,
        &menu[count].price,
        &status) != EOF)
        {
            menu[count].type = (MenuType)type;
            menu[count].status = (solve)status;
            count++;
        }
    fclose(file);
    return count;
}

int add_menu(const char* filename)
{
    // setlocale(LC_ALL, "zh_CN.UTF-8");
    MenuItem menu;

    printf("请输入想要添加的菜品ID: ");
    scanf("%d", &menu.id);
    printf("请输入想要添加的菜品名字: ");
    scanf("%s", menu.name);
    printf("请输入新菜品的价格:");
    scanf("%lf", &menu.price);
    printf("请输入新菜品的售卖状态: ");
    scanf("%d", &menu.status);
    printf("请输入菜品or酒水: ");
    scanf("%d", &menu.type);


    FILE* file = fopen(filename, "a");
    if (!file)
    {
        printf("无法打开文件 %s。\n", filename);
        return -1;  // 无法打开文件
    }


        fprintf(file, "%d %s %d %lf %d\n",
            menu.id,
            menu.name,
            menu.type,
            menu.price,
            menu.status);

    fprintf(file, "\n");
    fclose(file);

    printf("添加菜品成功\n");
    system("pause");
    return 0;

}

