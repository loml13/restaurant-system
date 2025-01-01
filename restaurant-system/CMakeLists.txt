cmake_minimum_required(VERSION 3.29)
project(restaurant_system C)

set(CMAKE_C_STANDARD 11)



add_library(restaurant_lib STATIC
        menu.c
        order.c
        user.c
        admin.c
        cashier.c)

add_executable(restaurant_system main.c)
add_executable(admin admin.c)
add_executable(menu menu.c)
add_executable(order order.c)
add_executable(user user.c)
add_executable(cashier cashier.c)

target_link_libraries(restaurant_system restaurant_lib)
target_link_libraries(admin restaurant_lib)
target_link_libraries(menu restaurant_lib)
target_link_libraries(order restaurant_lib)
target_link_libraries(user restaurant_lib)
target_link_libraries(cashier restaurant_lib)


