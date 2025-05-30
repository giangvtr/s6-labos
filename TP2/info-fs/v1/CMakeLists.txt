cmake_minimum_required(VERSION 3.21)
project(HelloWorld-fd C)

set(CMAKE_C_STANDARD 99)

add_executable(HelloWorld-fd programme-principal.c helloworld.c)
