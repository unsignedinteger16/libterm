cmake_minimum_required(VERSION 3.30)
project(libterm)

add_executable(alternate alternate.c)
target_link_libraries(alternate PRIVATE libterm)

add_executable(clear clear.c)
target_link_libraries(clear PRIVATE libterm)

add_executable(colorful colorful.c)
target_link_libraries(colorful PRIVATE libterm m)

add_executable(menu menu.c)
target_link_libraries(menu PRIVATE libterm m)