cmake_minimum_required(VERSION 3.17)
project(AI_Searching C)

set(CMAKE_C_STANDARD 99)

add_executable(AI_Searching main.c Stack_C.c Stack_C.h Queue_C.c Queue_C.h Method.c Method.h CheckerBoard.c CheckerBoard.h MinHeap_C.c MinHeap_C.h Random.c Random.h Layer.c Layer.h LinkedHash_C.c LinkedHash_C.h)