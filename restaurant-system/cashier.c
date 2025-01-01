#include <stdio.h>
#include "cashier.h"

#include <stdlib.h>

#include "order.h"

void payment(Order orders[] , int order_count)
    {
  int order_id;
  printf("请输入要结账的订单id: ");
  scanf("%d", &order_id);
  for(int i= 0 ; i < order_count ; i++){
    if(orders[i].order_id == order_id){
      if(orders[i].status == PAID){
        printf("订单已结账 \n");
        return;
       }

      printf("订单总额:  ￥%.2lf\n", orders[i].total);
      int c;
      printf("是否结账,结账请输入1: ");
      scanf("%d", &c);
      if(c == 1){
        orders[i].status = PAID;
        updated_paid("data/orders", orders, order_count, order_id);
        printf("结账成功 \n"
              "按任意键返回菜单 \n");
        system("pause");
        return;
      }
      else{
        printf("结账取消，客户选择刷盘子 \n");
        return;
      }
    }
  }
}