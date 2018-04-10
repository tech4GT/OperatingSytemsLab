cmake_minimum_required(VERSION 3.10)
project(OsPracticals C)

set(CMAKE_C_STANDARD 99)

add_executable(OsPracticals main.c)
add_executable(Program1 Practical1/fcfs.c)
add_executable(sjfs Practical1/sjfs.c)
add_executable(priority Practical1/priority.c)