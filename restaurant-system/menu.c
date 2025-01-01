#include "menu.h"
#include <stdio.h>
#include <string.h>

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



