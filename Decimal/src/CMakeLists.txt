cmake_minimum_required(VERSION 3.8)
project(C5_s21_decimal_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(tests
        /src/s21_decimal_tests.c
        /src/s21_add.c
        /src/s21_round.c
        /src/s21_from_decimal_to_float.c
        /src/s21_dbinary.c
        /src/s21_sub.c)