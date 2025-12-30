# Only for CLion compatibility


cmake_minimum_required(VERSION 3.22)
project(easylogin C)

set(CMAKE_C_STANDARD 23)


add_executable(easylogin-cli cli.c dataloader.c)

add_library(easylogin MODULE library.c dataloader.c)
