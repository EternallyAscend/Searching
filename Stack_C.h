//
// Created by MagicBook on 2020/10/22.
//

#ifndef AI_SEARCHING_STACK_C_H
#define AI_SEARCHING_STACK_C_H

#include "CheckerBoard.h"

// Stack.

struct Stack_C {
    int tail;
    int size;
    struct CheckerBoard** stack;
};

struct Stack_C* copyStack(struct Stack_C* stack);

int isEmptyStack(struct Stack_C* stack);

int initStack(struct Stack_C* stack);

void extendStack(struct Stack_C* stack);

int pushStack(struct Stack_C* stack, struct CheckerBoard* checkerBoard);

struct CheckerBoard* popStack(struct Stack_C* stack);

void destroyStack(struct Stack_C* stack);

void displayStack(struct Stack_C* stack);

void testStack();

#endif //AI_SEARCHING_STACK_C_H
